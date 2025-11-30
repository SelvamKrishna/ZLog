#pragma once

#include "./config.hpp"
#include "./log.hpp"

#include <format>
#include <string>

namespace zutils::trace::internal {

struct ScopeTracer {
  const std::string _STR_TEXT;
  const ColorText   TEXT;

  static constexpr ColorText ENTER_TAG = {config::SCOPE_ENTER_TAG, 92};
  static constexpr ColorText LEAVE_TAG = {config::SCOPE_LEAVE_TAG, 91};

  constexpr explicit ScopeTracer(std::string text)
    : _STR_TEXT {std::move(text)}
    , TEXT      {_STR_TEXT ,(config::ENABLE_TRACE_DULL) ? 90 : 0}
  {
    log::_log(
      LogLevel::Trace,
      "{}{}{}", ENTER_TAG, config::TAG_TAG, TEXT
    );
  }

  ~ScopeTracer()
  {
    log::_log(
      LogLevel::Trace,
      "{}{}{}", LEAVE_TAG, config::TAG_TAG, TEXT
    );
  }
};

} // namespace zutils::trace::internal

/// MACROS:

#define ZTRC_ANON \
  ::zutils::trace::internal::ScopeTracer ZTRACE_tracer_##__COUNTER__

#define ZTRC         ZTRC_ANON {std::format("{}()", __FUNCTION__)}
#define ZTRC_C(CLS)  ZTRC_ANON {std::format("{}::{}", #CLS, __FUNCTION__)}
#define ZTRC_S(DSC)  ZTRC_ANON {DSC}
