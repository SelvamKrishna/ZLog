#pragma once

#include <format>
#include <ostream>
#include <string_view>

namespace zutils {

enum class LogLevel : uint8_t { Trace, Debug, Info, Warn, Error, Fatal, };

struct ColorText {
  const std::string_view TEXT;
  const int              COLOR;
};

/// MODIFY: Change variables
namespace config {

/// Utility flags
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

static constexpr bool DISABLE_LOGGING   = false;
static constexpr bool ENABLE_TIMESTAMP  = true;
static constexpr bool ENABLE_COLOR      = true;
static constexpr bool ENABLE_TRACE_DULL = true;

/// Tags
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
static constexpr std::string_view TAG_TAG     = " : ";

/// Platform detection
#ifdef _WIN32
static constexpr bool IS_WINDOWS = true;
#else
static constexpr bool IS_WINDOWS = false;
#endif

[[noreturn]]
inline void killProcess() noexcept { std::abort(); }

[[nodiscard]]
constexpr inline const ColorText& getLogLevel(LogLevel lvl) noexcept
{
  return TAG_CTX[static_cast<int>(lvl)];
}

} // namespace config

inline std::ostream& operator<<(std::ostream& os, const ColorText& ct)
{
  return (config::ENABLE_COLOR)
  ? os << "\033[" << ct.COLOR << "m" << ct.TEXT << "\033[0m"
  : os << ct.TEXT;
}

} // namespace zutils

template<>
struct std::formatter<zutils::ColorText> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

  auto format(const zutils::ColorText &ct, std::format_context &ctx) const {
    return (zutils::config::ENABLE_COLOR)
    ? std::format_to(ctx.out(), "\033[{}m{}\033[0m", ct.COLOR, ct.TEXT)
    : std::format_to(ctx.out(), "{}", ct.TEXT);
  }
};
