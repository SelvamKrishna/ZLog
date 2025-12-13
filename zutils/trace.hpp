#pragma once

#include "./config.hpp"
#include "./log.hpp"

#include <format>
#include <string>

namespace zutils::trace {

// Uses RAII to log tracing messages of a scope
struct ScopeTracer {
private:
    const std::string STR_TEXT;  //< Owned tracing message

public:
    const ColorText TEXT;  //< Colored tracing message

    // Scope IN
    explicit ScopeTracer(std::string text)
        : STR_TEXT{std::move(text)}
        , TEXT{STR_TEXT, (config::ENABLE_TRACE_DULL) ? ANSI::EX_Black : ANSI::Reset}
    {
        log::internal::_log(
            LogLevel::Trace,
            {"{}{}{}", config::TRACE_IN_TAG, config::TAG_TAG, TEXT}
        );
    }

    // Scope OUT
    ~ScopeTracer()
    {
        log::internal::_log(
            LogLevel::Trace,
            {"{}{}{}", config::TRACE_OUT_TAG, config::TAG_TAG, TEXT}
        );
    }
};

} // namespace zutils::trace

/// MACROS:

// For proper `ScopeTracer` construction
#define ZTRC_ANON  ::zutils::trace::ScopeTracer ZTRACE_tracer_##__COUNTER__

// Scope tracing
#define ZTRC         ZTRC_ANON {std::format("{}()", __FUNCTION__)}
#define ZTRC_C(CLS)  ZTRC_ANON {std::format("{}::{}()", #CLS, __FUNCTION__)}
#define ZTRC_S(DSC)  ZTRC_ANON {DSC}
