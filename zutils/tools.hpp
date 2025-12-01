#pragma once

#include "./log.hpp"  // IWYU pragma: keep
#include "./test.hpp" // IWYU pragma: keep

namespace zutils::tools {} // namespace zutils::tools
/// Mark incomplete code - warning level
#define ZTODO(...) ::zutils::log::warn("TODO: " __VA_ARGS__ " {}", ZLOC)

/// Mark code that should never be reached - fatal
#define ZUNREACHABLE(MSG)                                                      \
  ::zutils::test::panic(MSG, ZLOC)

/// Mark not yet implemented features - error level
#define ZUNIMPLEMENTED(...)                                                    \
  ::zutils::log::err("UNIMPLEMENTED: " __VA_ARGS__ " {}", ZLOC)

/// Mark deprecated functionality - warning level
#define ZDEPRECATED(...)                                                       \
  ::zutils::log::warn("DEPRECATED: " __VA_ARGS__ " {}", ZLOC)

/// Mark bugs that need fixing - error level
#define ZFIXME(...) ::zutils::log::err("FIXME: " __VA_ARGS__ " {}", ZLOC)

/// Mark optimization opportunities - debug level
#define ZOPTIMIZE(...)                                                         \
  ::zutils::log::dbg("OPTIMIZE: " __VA_ARGS__ " {}", ZLOC)

/// Mark security review needed - warning level
#define ZSECURITY(...) ::zutils::log::warn("SECURITY: " __VA_ARGS__ " {}", ZLOC)

/// Mark performance issues - warning level
#define ZPERFORMANCE(...)                                                      \
  ::zutils::log::warn("PERFORMANCE: " __VA_ARGS__ " {}", ZLOC)

/// Mark memory issues - error level
#define ZMEMORY(...) ::zutils::log::err("MEMORY: " __VA_ARGS__ " {}", ZLOC)

/// Mark thread safety issues - error level
#define ZTHREAD_SAFETY(...)                                                    \
  ::zutils::log::err("THREAD_SAFETY: " __VA_ARGS__ " {}", ZLOC)

#define ZON_DEBUG \
  if constexpr (::zutils::config::IS_MODE_DEBUG)

#define ZON_RELEASE \
  if constexpr (!::zutils::config::IS_MODE_DEBUG)
