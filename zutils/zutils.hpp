#pragma once

#include <ostream>
#include <string_view>

namespace zutils {

enum class LogLevel : uint8_t { Trace, Debug, Info, Warn, Error, Fatal, };

} // namespace zutils

/// MODIFY: Change variables
namespace zutils::config {

static constexpr LogLevel MIN_LVL_RLS = LogLevel::Info;
static constexpr LogLevel MIN_LVL_DBG = LogLevel::Trace;

static_assert(static_cast<int>(MIN_LVL_RLS) >= 0 && static_cast<int>(MIN_LVL_RLS) <= 5);
static_assert(static_cast<int>(MIN_LVL_DBG) >= 0 && static_cast<int>(MIN_LVL_DBG) <= 5);

#ifdef NDEBUG
static constexpr LogLevel MIN_LEVEL     = MIN_LVL_RLS;
static constexpr bool     IS_MODE_DEBUG = false;
#else
static constexpr LogLevel MIN_LEVEL     = MIN_LVL_DBG;
static constexpr bool     IS_MODE_DEBUG = true;
#endif

/// Compile-time configuration
static constexpr bool DISABLE_LOGGING   = false;
static constexpr bool ENABLE_TIMESTAMP  = true;
static constexpr bool ENABLE_COLOR      = true;
static constexpr bool ENABLE_TRACE_DULL = true;

/// Tags

struct ColorText {
  const std::string_view TEXT;
  const int              COLOR;
};

inline std::ostream& operator<<(std::ostream& os, const ColorText& ct)
{
  return (ENABLE_COLOR)
  ? os << "\033[" << ct.COLOR << "m" << ct.TEXT << "\033[0m"
  : os << ct.TEXT;
}

static constexpr ColorText TAG_CTX[] = {
  {"[TRCE]", 90},
  {"[DEBG]", 36},
  {"[INFO]", 32},
  {"[WARN]", 33},
  {"[ERRO]", 31},
  {"[FATL]", 41},
};

static constexpr std::string_view SCOPE_ENTER_TAG = "--{";
static constexpr std::string_view SCOPE_LEAVE_TAG = "}--";

static constexpr std::string_view COLOR_RESET = "\033[0m";
static constexpr std::string_view TAB_TAG     = "  ";

/// Platform detection
#ifdef _WIN32
static constexpr bool IS_WINDOWS = true;
#else
static constexpr bool IS_WINDOWS = false;
#endif

[[noreturn]]
static inline void killProcess() noexcept { std::abort(); }

} // namespace zutils::config
