#pragma once

#include "./config.hpp"

#include <mutex>
#include <format>
#include <utility>
#include <iostream>
#include <string_view>
#include <chrono>
#include <ctime>

namespace zutils::log {

namespace internal {

class ProString final {
public:
    const std::string TEXT;

    ProString(std::string_view text) noexcept : TEXT {text} {}

    template <typename... Args>
    ProString(
        std::format_string<Args...> f_str,
        Args&&... args
    ) noexcept : TEXT {std::format(f_str, std::forward<Args>(args)...)} {}

    friend std::ostream &operator<<(std::ostream &os, const ProString &ps)
    {
        return os << ps.TEXT;
    }

    [[nodiscard]]
    constexpr bool isEmpty() const noexcept { return TEXT == ""; }
};

// Thread-safe logging guard with mutex lock
struct LogGuard {
    std::scoped_lock<std::mutex> lock;  //< RAII mutex lock
    std::ostream&                os;    //< Reference to output stream

    LogGuard(std::mutex& mutex, std::ostream& os) : lock{mutex}, os{os} {}
};

// Returns thread-safe `LogGuard` for logging
[[nodiscard]]
inline LogGuard logStream(LogLevel level) noexcept
{
    static std::mutex s_log_mutex {};

    // Use cout for Trace/Debug/Info, cerr for Warn/Error/Fatal
    return LogGuard {
        s_log_mutex,
        static_cast<int>(level) < static_cast<int>(LogLevel::Warn)
        ? std::cout
        : std::cerr
    };
}

// Returns current timestamp as "[HH:MM:SS]" string
[[nodiscard]]
static inline std::string_view getTimestamp() noexcept
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm_struct{};

    thread_local char buf[sizeof("[HH:MM:SS]")] {};

#ifdef _WIN32
    localtime_s(&tm_struct, &t);
#else
    localtime_r(&t, &tm_struct);
#endif

    std::strftime(buf, sizeof(buf), "[%H:%M:%S]", &tm_struct);
    return std::string_view{buf, sizeof("[HH:MM:SS]")};
}

// Internal log function
inline void _log(LogLevel lvl, ProString msg) noexcept
{
    if (config::DISABLE_LOGGING || lvl < config::MIN_LEVEL) return;

    LogGuard log_gaurd = internal::logStream(lvl);
    log_gaurd.os << config::COLOR_RESET;

    if constexpr (config::ENABLE_TIMESTAMP)
    {
        log_gaurd.os
            << ColorText{internal::getTimestamp(), ANSI::EX_Black}
            << config::TAG_TAG;
    }

    log_gaurd.os
        << config::TAG_CTX[static_cast<int>(lvl)]
        << config::TAG_TAG << msg << "\n";
}

} // namespace internal

// Macro to generate logging functions for each level
#define _LOG_FN(FN_NAME, LOG_LVL)                         \
    inline void FN_NAME(internal::ProString message)      \
    { ::zutils::log::internal::_log(LOG_LVL, message); }  \

    // Generate logging functions for each level
    _LOG_FN(trace, LogLevel::Trace)  //< Trace level logging
    _LOG_FN(dbg  , LogLevel::Debug)  //< Debug level logging
    _LOG_FN(info , LogLevel::Info)   //< Info level logging
    _LOG_FN(warn , LogLevel::Warn)   //< Warning level logging
    _LOG_FN(err  , LogLevel::Error)  //< Error level logging
    _LOG_FN(fatal, LogLevel::Fatal)  //< Fatal level logging

#undef _LOG_FN

} // namespace zutils::log

template <>
struct std::formatter<zutils::log::internal::ProString> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(
        const zutils::log::internal::ProString &ps,
        std::format_context &ctx
    ) const
    {
        return std::format_to(ctx.out(), "{}", ps.TEXT);
    }
};

/// MACROS:

// Raw output with color reset
#define ZOUT  std::cout << "\n" << ::zutils::config::COLOR_RESET

// Standard logging
#define   ZDBG(...)  ::zutils::log::dbg  ({__VA_ARGS__})
#define  ZINFO(...)  ::zutils::log::info ({__VA_ARGS__})
#define  ZWARN(...)  ::zutils::log::warn ({__VA_ARGS__})
#define   ZERR(...)  ::zutils::log::err  ({__VA_ARGS__})
#define ZFATAL(...)  ::zutils::log::fatal({__VA_ARGS__})

// Conditional logging
#define   ZDBG_IF(COND, ...)  do { if (COND)   ZDBG(__VA_ARGS__); } while (0)
#define  ZINFO_IF(COND, ...)  do { if (COND)  ZINFO(__VA_ARGS__); } while (0)
#define  ZWARN_IF(COND, ...)  do { if (COND)  ZWARN(__VA_ARGS__); } while (0)
#define   ZERR_IF(COND, ...)  do { if (COND)   ZERR(__VA_ARGS__); } while (0)
#define ZFATAL_IF(COND, ...)  do { if (COND) ZFATAL(__VA_ARGS__); } while (0)

// Debug variable with name and value
#define ZVAR(VAR) \
    ZDBG("({}) = {}", ::zutils::ColorText {#VAR, ::zutils::ANSI::Magenta}, (VAR))
