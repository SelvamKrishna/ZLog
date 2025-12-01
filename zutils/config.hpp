#pragma once

#include <format>
#include <ostream>
#include <string_view>

namespace zutils {

enum class LogLevel : uint8_t { Trace, Debug, Info, Warn, Error, Fatal, };

enum class ANSI : uint8_t {
/// Text Attributes
  Reset         = 0,
  Bold          = 1,
  Dim           = 2,
  Italic        = 3,
  Underline     = 4,
  Blink         = 5,
  Inverse       = 7,
  Hidden        = 8,
  Strikethrough = 9,
/// Regular Colors
  Black         = 30,
  Red           = 31,
  Green         = 32,
  Yellow        = 33,
  Blue          = 34,
  Magenta       = 35,
  Cyan          = 36,
  White         = 37,
/// Background Colors
  BG_Black      = 40,
  BG_Red        = 41,
  BG_Green      = 42,
  BG_Yellow     = 43,
  BG_Blue       = 44,
  BG_Magenta    = 45,
  BG_Cyan       = 46,
  BG_White      = 47,
/// Bright Colors
  EX_Black      = 90,
  EX_Red        = 91,
  EX_Green      = 92,
  EX_Yellow     = 93,
  EX_Blue       = 94,
  EX_Magenta    = 95,
  EX_Cyan       = 96,
  EX_White      = 97,
/// Bright Background Colors
  BG_EX_Black   = 100,
  BG_EX_Red     = 101,
  BG_EX_Green   = 102,
  BG_EX_Yellow  = 103,
  BG_EX_Blue    = 104,
  BG_EX_Magenta = 105,
  BG_EX_Cyan    = 106,
  BG_EX_White   = 107,
};

struct ColorText {
  const std::string_view TEXT;
  const ANSI             COLOR;
};

namespace config {

/// MODIFY: Change variables vvv

/// Utility flags
static constexpr LogLevel MIN_LVL_RLS = LogLevel::Info;
static constexpr LogLevel MIN_LVL_DBG = LogLevel::Trace;

static_assert(static_cast<int>(MIN_LVL_RLS) >= 0 && static_cast<int>(MIN_LVL_RLS) <= 5);
static_assert(static_cast<int>(MIN_LVL_DBG) >= 0 && static_cast<int>(MIN_LVL_DBG) <= 5);

static constexpr bool DISABLE_LOGGING   = false;
static constexpr bool ENABLE_TIMESTAMP  = true;
static constexpr bool ENABLE_COLOR      = true;
static constexpr bool ENABLE_TRACE_DULL = true;

/// Tags
static constexpr ColorText TAG_CTX[] = {
  {"[TRCE]", ANSI::EX_Black},
  {"[DEBG]", ANSI::Cyan    },
  {"[INFO]", ANSI::Green   },
  {"[WARN]", ANSI::Yellow  },
  {"[ERRO]", ANSI::Red     },
  {"[FATL]", ANSI::BG_Red  },
};

static constexpr ColorText SCOPE_ENTER_TAG = {"--{", ANSI::EX_Green};
static constexpr ColorText SCOPE_LEAVE_TAG = {"}--", ANSI::EX_Red  };

static constexpr ColorText TEST_TAG        = {"[TEST]", ANSI::Blue };
static constexpr ColorText PASS_TAG        = {"[PASS]", ANSI::Green};
static constexpr ColorText FAIL_TAG        = {"[FAIL]", ANSI::Red  };

static constexpr ColorText EXPECT_TAG      = {"[CHCK]", ANSI::Yellow};
static constexpr ColorText ASSERT_TAG      = {"[ASRT]", ANSI::Red   };
static constexpr ColorText PANIC_TAG       = {"[PANC]", ANSI::BG_Red};

static constexpr std::string_view TAB_TAG = "  ";
static constexpr std::string_view TAG_TAG = " : ";

/// MODIFY: Change Variables ^^^

static constexpr std::string_view COLOR_RESET = "\033[0m";

#ifdef NDEBUG
static constexpr LogLevel MIN_LEVEL     = MIN_LVL_RLS;
static constexpr bool     IS_MODE_DEBUG = false;
#else
static constexpr LogLevel MIN_LEVEL     = MIN_LVL_DBG;
static constexpr bool     IS_MODE_DEBUG = true;
#endif

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
  ? os << "\033[" << static_cast<int>(ct.COLOR) << "m" << ct.TEXT << "\033[0m"
  : os << ct.TEXT;
}

struct SourceLoc {
  const bool EMPTY;
  const std::string TEXT;

  SourceLoc() : TEXT {}, EMPTY {true} {}

  SourceLoc(std::string_view file, int line)
    : TEXT  {std::format("[{}:{}]", file, line)}
    , EMPTY {false}
  {}

  friend std::ostream &operator<<(std::ostream &os, const SourceLoc &sl)
  {
    return (sl.EMPTY) ? os : os << ColorText {sl.TEXT, ANSI::EX_Black};
  }
};

} // namespace zutils

template<>
struct std::formatter<zutils::ColorText>
{
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

  auto format(const zutils::ColorText &ct, std::format_context &ctx) const {
    return (zutils::config::ENABLE_COLOR)
    ? std::format_to(ctx.out(), "\033[{}m{}\033[0m", static_cast<int>(ct.COLOR), ct.TEXT)
    : std::format_to(ctx.out(), "{}", ct.TEXT);
  }
};

template<>
struct std::formatter<zutils::SourceLoc>
{
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

  auto format(const zutils::SourceLoc &sl, std::format_context &ctx) const {
    return (sl.EMPTY)
    ? std::format_to(ctx.out(), "")
    : std::format_to(ctx.out(), "{}", zutils::ColorText {sl.TEXT, zutils::ANSI::EX_Black});
  }
};

/// MACROS:

#define ZLOC  ::zutils::SourceLoc {__FILE__, __LINE__}
