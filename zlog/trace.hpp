#pragma once

#include "./config.hpp"
#include "./log.hpp"

#include <format>
#include <string>

namespace zlog {

// Uses RAII to log tracing messages of a scope
struct ScopeTracer {
private:
    const std::string STR_TEXT;  //< Owned tracing message

public:
    const ColorText TEXT;  //< Colored tracing message

    // Scope IN
    explicit ScopeTracer(internal::ProString text)
        : STR_TEXT{std::move(text.TEXT)}
        , TEXT{STR_TEXT, (config::ENABLE_TRACE_DULL) ? ANSI::EX_Black : ANSI::Reset}
    {
        internal::_log(
            LogLevel::Trace,
            {"{}{}{}", config::TRACE_IN_TAG, config::TAG_TAG, TEXT}
        );
    }

    // Scope OUT
    ~ScopeTracer()
    {
        internal::_log(
            LogLevel::Trace,
            {"{}{}{}", config::TRACE_OUT_TAG, config::TAG_TAG, TEXT}
        );
    }
};

} // namespace zlog

/// MACROS:

// For proper `ScopeTracer` construction
#define _ZTRC_ANON  ::zlog::ScopeTracer ZTRACE_tracer_##__COUNTER__

// Scope tracing
#define ZTRC         _ZTRC_ANON { {     "{}()",       __FUNCTION__} }
#define ZTRC_C(CLS)  _ZTRC_ANON { { "{}::{}()", #CLS, __FUNCTION__} }
#define ZTRC_S(...)  _ZTRC_ANON { {__VA_ARGS__} }
