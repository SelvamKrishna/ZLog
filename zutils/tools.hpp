#pragma once

#include "./config.hpp"
#include "./log.hpp"

namespace zutils::tools {

enum class CautionCode : uint8_t {
    Todo,
    Deprecated,
    Optimization,
    Security,
    Performance,
};

enum class CriticalCode : uint8_t {
    Unreachable,
    Unimplemented,
    FixMe,
    Memory,
    ThreadSafety,
};

static constexpr std::string_view CAUTION_TAGS[] = {
    "[TODO]",
    "[DEPR]",
    "[OPTM]",
    "[SCRT]",
    "[PERF]",
};

static constexpr std::string_view CRITICAL_TAGS[] = {
    "[UNRC]",
    "[NIMP]",
    "[FIXM]",
    "[MEMO]",
    "[THRD]",
};

inline void caution(
    CautionCode              code,
    SourceLoc                loc,
    log::internal::ProString msg
) noexcept {
    log::internal::_log(
        LogLevel::Warn,
        log::internal::ProString {
            "{}{}{}{}{}",
            ColorText{CAUTION_TAGS[static_cast<size_t>(code)], ANSI::Yellow},
            config::TAG_TAG,
            loc,
            config::TAG_TAG,
            msg
        }
    );
}

#ifndef ZUTILS_T
[[noreturn]]
#endif
inline void critical(
    CriticalCode             code,
    SourceLoc                loc,
    log::internal::ProString msg
) noexcept {
    log::internal::_log(
        LogLevel::Fatal,
        {
            "{}{}{}{}{}",
            ColorText{CRITICAL_TAGS[static_cast<size_t>(code)], ANSI::BG_Red},
            config::TAG_TAG,
            loc,
            config::TAG_TAG,
            msg
        }
    );
#ifndef ZUTILS_T
    config::killProcess();
#endif
}

} // namespace zutils::tools

/// MACROS:

#define   ZON_DEBUG  if constexpr ( ::zutils::config::IS_MODE_DEBUG)
#define ZON_RELEASE  if constexpr (!::zutils::config::IS_MODE_DEBUG)

#define  ZCAUTION(code, ...)  ::zutils::tools::caution (code, ZLOC, {__VA_ARGS__})
#define ZCRITICAL(code, ...)  ::zutils::tools::critical(code, ZLOC, {__VA_ARGS__})

#define        ZTODO(...)  ZCAUTION(::zutils::tools::CautionCode::Todo        , __VA_ARGS__)
#define  ZDEPRECATED(...)  ZCAUTION(::zutils::tools::CautionCode::Deprecated  , __VA_ARGS__)
#define    ZOPTIMIZE(...)  ZCAUTION(::zutils::tools::CautionCode::Optimization, __VA_ARGS__)
#define    ZSECURITY(...)  ZCAUTION(::zutils::tools::CautionCode::Security    , __VA_ARGS__)
#define ZPERFORMANCE(...)  ZCAUTION(::zutils::tools::CautionCode::Performance , __VA_ARGS__)

#define   ZUNREACHABLE(...)  ZCRITICAL(::zutils::tools::CriticalCode::Unreachable  , __VA_ARGS__)
#define ZUNIMPLEMENTED(...)  ZCRITICAL(::zutils::tools::CriticalCode::Unimplemented, __VA_ARGS__)
#define         ZFIXME(...)  ZCRITICAL(::zutils::tools::CriticalCode::FixMe        , __VA_ARGS__)
#define        ZMEMORY(...)  ZCRITICAL(::zutils::tools::CriticalCode::Memory       , __VA_ARGS__)
#define ZTHREAD_SAFETY(...)  ZCRITICAL(::zutils::tools::CriticalCode::ThreadSafety , __VA_ARGS__)
