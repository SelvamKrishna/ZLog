#pragma once

#include "./config.hpp"
#include "./log.hpp"

namespace zlog {

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
    "[TODO]"        ,
    "[DEPRECATED]"  ,
    "[OPTIMIZATION]",
    "[SECURITY]"    ,
    "[PERFORMANCE]" ,
};

static constexpr std::string_view CRITICAL_TAGS[] = {
    "[UNREACHABLE]"   ,
    "[UNIMPLEMENTED]" ,
    "[FIX_ME]"        ,
    "[MEMORY]"        ,
    "[THREAD_SAFETY]" ,
};

inline void caution(
    CautionCode code,
    SourceLoc loc,
    internal::ProString msg
) noexcept {
    internal::_log(
        LogLevel::Warn,
        internal::ProString {
            "{}{}{}{}{}",
            ColorText{CAUTION_TAGS[static_cast<size_t>(code)], ANSI::Yellow},
            config::TAG_TAG,
            loc,
            config::TAG_TAG,
            msg
        }
    );
}

#ifndef ZLOG_T
[[noreturn]]
#endif
inline void critical(
    CriticalCode code,
    SourceLoc loc,
    internal::ProString msg
) noexcept {
    internal::_log(
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
#ifndef ZLOG_T
    config::killProcess();
#endif
}

} // namespace zlog

/// MACROS:

#define   ZON_DEBUG  if constexpr ( ::zlog::config::IS_MODE_DEBUG)
#define ZON_RELEASE  if constexpr (!::zlog::config::IS_MODE_DEBUG)

#define  ZCAUTION(code, ...)  do { ::zlog::caution (code, _ZSL, {__VA_ARGS__}); } while (0)
#define ZCRITICAL(code, ...)  do { ::zlog::critical(code, _ZSL, {__VA_ARGS__}); } while (0)

#define        ZTODO(...)  ZCAUTION(::zlog::CautionCode::Todo        , __VA_ARGS__)
#define  ZDEPRECATED(...)  ZCAUTION(::zlog::CautionCode::Deprecated  , __VA_ARGS__)
#define    ZOPTIMIZE(...)  ZCAUTION(::zlog::CautionCode::Optimization, __VA_ARGS__)
#define    ZSECURITY(...)  ZCAUTION(::zlog::CautionCode::Security    , __VA_ARGS__)
#define ZPERFORMANCE(...)  ZCAUTION(::zlog::CautionCode::Performance , __VA_ARGS__)

#define   ZUNREACHABLE(...)  ZCRITICAL(::zlog::CriticalCode::Unreachable  , __VA_ARGS__)
#define ZUNIMPLEMENTED(...)  ZCRITICAL(::zlog::CriticalCode::Unimplemented, __VA_ARGS__)
#define         ZFIXME(...)  ZCRITICAL(::zlog::CriticalCode::FixMe        , __VA_ARGS__)
#define        ZMEMORY(...)  ZCRITICAL(::zlog::CriticalCode::Memory       , __VA_ARGS__)
#define ZTHREAD_SAFETY(...)  ZCRITICAL(::zlog::CriticalCode::ThreadSafety , __VA_ARGS__)
