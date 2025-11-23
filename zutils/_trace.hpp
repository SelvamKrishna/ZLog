#pragma once

#include "./_log.hpp"

#include <string>
#include <string_view>

#ifndef USING_CUSTOM

#define SCOPE_ENTER_TEXT    "--{"
#define SCOPE_LEAVE_TEXT    "}--"

#endif

namespace zutils::internal {

struct ScopeTracer {
  const std::string FN_NAME;

#if ENABLE_COLOR_CODE
  static constexpr const char* ENTER_TEXT {"\033[92m" SCOPE_ENTER_TAG "\033[0m"};
  static constexpr const char* LEAVE_TEXT {"\033[91m" SCOPE_LEAVE_TAG "\033[0m"};
#else
  static constexpr const char* ENTER_TEXT {SCOPE_ENTER_TEXT};
  static constexpr const char* LEAVE_TEXT {SCOPE_LEAVE_TEXT};
#endif

  explicit ScopeTracer(std::string_view fn_name) : FN_NAME {fn_name} {
    ZLOGT << ENTER_TEXT << " : " << FN_NAME;
  }

  ~ScopeTracer() {
    ZLOGT << LEAVE_TEXT << " : " << FN_NAME;
  }

};

} // namespace zutils::internal

#if ((ENABLE_COLOR_CODE) && (ENABLE_TRACE_DULL))

#define ZTRACE \
  zutils::internal::ScopeTracer __trace {std::format("\033[90m{}()\033[0m", __FUNCTION__)}

#define ZTRACE_C(CLASS) \
  zutils::internal::ScopeTracer __trace {std::format("\033[90m{}::{}()\033[0m", #CLASS, __FUNCTION__)}

#else

#define ZTRACE \
  zutils::internal::ScopeTracer __trace {std::format("{}()", __FUNCTION__)}

#define ZTRACE_C(CLASS) \
  zutils::internal::ScopeTracer __trace {std::format("{}::{}()", #CLASS, __FUNCTION__)}

#endif
