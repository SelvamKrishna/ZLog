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

struct NullBuffer : std::streambuf {
  int overflow(int c) override { return 0; }
};

static NullBuffer   s_null_buf    {};
static std::ostream s_null_stream {&s_null_buf};

struct LogGuard {
  std::scoped_lock<std::mutex> lock;
  std::ostream&                os;

  LogGuard(std::mutex& mutex, std::ostream& os)
    : lock {mutex}
    , os   {os}
  {}
};

[[nodiscard]]
inline LogGuard logStream(LogLevel level) noexcept
{
  static std::mutex s_log_mutex {};

  return LogGuard {
    s_log_mutex,
    (
      static_cast<int>(level) < static_cast<int>(LogLevel::Warn)
    ) ? std::cout : std::cerr
  };
}

[[nodiscard]]
static inline std::string_view getTimestamp() noexcept
{
  if constexpr (!config::ENABLE_TIMESTAMP) return "";

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
  return std::string_view{buf, 10};
}

} // namespace internal

template <typename... Args>
inline constexpr void _log(LogLevel lvl, std::format_string<Args...> f_str, Args&&... args) {
  if (config::DISABLE_LOGGING || lvl < config::MIN_LEVEL) return;
  ColorText   time = {internal::getTimestamp(), ANSI::EX_Black};
  std::string msg  = std::format(f_str, std::forward<Args>(args)...);

  internal::logStream(lvl).os
    << config::COLOR_RESET
    << time << config::TAG_TAG
    << config::getLogLevel(lvl) << config::TAG_TAG
    << msg << "\n";
}

#define LOGGING_FN(FN_NAME, LOG_LVL) \
  template <typename... Args> \
  inline constexpr void FN_NAME(std::format_string<Args...> f_str, Args&&... args) \
  { \
    _log(LOG_LVL, f_str, std::forward<Args>(args)...); \
  }

LOGGING_FN(dbg  , LogLevel::Debug)
LOGGING_FN(info , LogLevel::Info)
LOGGING_FN(warn , LogLevel::Warn)
LOGGING_FN(err  , LogLevel::Error)
LOGGING_FN(fatal, LogLevel::Fatal)

#undef LOGGING_FN

} // namespace zutils

/// MACROS:

#define   ZDBG(...)  ::zutils::log::dbg  (__VA_ARGS__)
#define  ZINFO(...)  ::zutils::log::info (__VA_ARGS__)
#define  ZWARN(...)  ::zutils::log::warn (__VA_ARGS__)
#define   ZERR(...)  ::zutils::log::err  (__VA_ARGS__)
#define ZFATAL(...)  ::zutils::log::fatal(__VA_ARGS__)

#define   ZDBG_IF(COND, ...)  do { if (COND) ::zutils::log::dbg  (__VA_ARGS__); } while (0)
#define  ZINFO_IF(COND, ...)  do { if (COND) ::zutils::log::info (__VA_ARGS__); } while (0)
#define  ZWARN_IF(COND, ...)  do { if (COND) ::zutils::log::warn (__VA_ARGS__); } while (0)
#define   ZERR_IF(COND, ...)  do { if (COND) ::zutils::log::err  (__VA_ARGS__); } while (0)
#define ZFATAL_IF(COND, ...)  do { if (COND) ::zutils::log::fatal(__VA_ARGS__); } while (0)

#define ZVAR(VAR)  ZDBG("({}) = {}", ::zutils::ColorText{#VAR, ::zutils::ANSI::Magenta}, (VAR))

#define ZOUT  std::cout << "\n" << ::zutils::config::COLOR_RESET
