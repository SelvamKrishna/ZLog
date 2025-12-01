#pragma once

#include "./config.hpp"
#include "./log.hpp"

#include <format>
#include <string>

namespace zutils::trace {

struct ScopeTracer {
  const std::string _STR_TEXT;
  const ColorText   TEXT;

  constexpr explicit ScopeTracer(std::string text)
    : _STR_TEXT {std::move(text)}
    , TEXT      {_STR_TEXT ,(config::ENABLE_TRACE_DULL) ? ANSI::EX_Black : ANSI::Reset}
  {
    log::_log(
      LogLevel::Trace,
      "{}{}{}", config::SCOPE_ENTER_TAG, config::TAG_TAG, TEXT
    );
  }

  ~ScopeTracer()
  {
    log::_log(
      LogLevel::Trace,
      "{}{}{}", config::SCOPE_LEAVE_TAG, config::TAG_TAG, TEXT
    );
  }
};

} // namespace zutils::trace

/// MACROS:

#define ZTRC_ANON \
  ::zutils::trace::ScopeTracer ZTRACE_tracer_##__COUNTER__

#define ZTRC         ZTRC_ANON {std::format("{}()", __FUNCTION__)}
#define ZTRC_C(CLS)  ZTRC_ANON {std::format("{}::{}()", #CLS, __FUNCTION__)}
#define ZTRC_S(DSC)  ZTRC_ANON {DSC}
