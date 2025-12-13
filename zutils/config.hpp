#pragma once

#include <format>
#include <ostream>
#include <string_view>

namespace zutils {

// Logging severity levels
enum class LogLevel : uint8_t {
    Trace,  //< Detailed trace information for debugging
    Debug,  //< Debug-level information for development
    Info,   //< General informational messages
    Warn,   //< Warning messages indicating potential issues
    Error,  //< Error messages indicating failures
    Fatal,  //< Fatal errors causing program termination
};

// ANSI escape codes for terminal styling
enum class ANSI : uint8_t {
// =============== TEXT ATTRIBUTES ===============
    Reset          = 0,
    Bold           = 1,
    Dim            = 2,
    Italic         = 3,
    Underline      = 4,
    Blink          = 5,
    Inverse        = 7,
    Hidden         = 8,
    Strikethrough  = 9,
// =============== REGULAR COLORS ===============
    Black          = 30,
    Red            = 31,
    Green          = 32,
    Yellow         = 33,
    Blue           = 34,
    Magenta        = 35,
    Cyan           = 36,
    White          = 37,
// =============== BACKGROUND COLORS ===============
    BG_Black       = 40,
    BG_Red         = 41,
    BG_Green       = 42,
    BG_Yellow      = 43,
    BG_Blue        = 44,
    BG_Magenta     = 45,
    BG_Cyan        = 46,
    BG_White       = 47,
// =============== BRIGHT COLORS ===============
    EX_Black       = 90,
    EX_Red         = 91,
    EX_Green       = 92,
    EX_Yellow      = 93,
    EX_Blue        = 94,
    EX_Magenta     = 95,
    EX_Cyan        = 96,
    EX_White       = 97,
// =============== BRIGHT BACKGROUND COLORS ===============
    BG_EX_Black    = 100,
    BG_EX_Red      = 101,
    BG_EX_Green    = 102,
    BG_EX_Yellow   = 103,
    BG_EX_Blue     = 104,
    BG_EX_Magenta  = 105,
    BG_EX_Cyan     = 106,
    BG_EX_White    = 107,
};

// ANSI color coded text with associated text and color code.
struct ColorText {
    const std::string_view TEXT;   //< The text content to display
    const ANSI             COLOR;  //< ANSI color code for the text
};

namespace config {

// === MODIFY THESE VALUES ===

// General flags
static constexpr bool DISABLE_LOGGING   = false;  // Completely disable logging
static constexpr bool ENABLE_TIMESTAMP  = false;  // Add [HH:MM:SS] to logs
static constexpr bool ENABLE_COLOR      = true;   // Enable ANSI colors
static constexpr bool ENABLE_TRACE_DULL = true;   // Make trace messages gray

// Minimum log levels
static constexpr LogLevel MIN_LVL_RLS = LogLevel::Info;   // Release builds
static constexpr LogLevel MIN_LVL_DBG = LogLevel::Trace;  // Debug builds

// Log level tags with colors
static constexpr ColorText TAG_CTX[] = {
    { "[TRCE]", ANSI::EX_Black },
    { "[DEBG]", ANSI::Cyan     },
    { "[INFO]", ANSI::Green    },
    { "[WARN]", ANSI::Yellow   },
    { "[ERRO]", ANSI::Red      },
    { "[FATL]", ANSI::BG_Red   },
};

// Scope tracing tags
static constexpr ColorText TRACE_IN_TAG  = {"--{", ANSI::EX_Green};
static constexpr ColorText TRACE_OUT_TAG = {"}--", ANSI::EX_Red};

// Testing tags
static constexpr ColorText TEST_TAG      = {"[TEST]", ANSI::Blue};
static constexpr ColorText PASS_TAG      = {"[PASS]", ANSI::Green};
static constexpr ColorText FAIL_TAG      = {"[FAIL]", ANSI::Red};

// Validation tags
static constexpr ColorText EXPECT_TAG    = {"[EXPC]", ANSI::Yellow};
static constexpr ColorText ASSERT_TAG    = {"[ASRT]", ANSI::Red};
static constexpr ColorText VERIFY_TAG    = {"[VRFY]", ANSI::BG_Red};
static constexpr ColorText PANIC_TAG     = {"[PANC]", ANSI::BG_Red};

// Formatting
static constexpr std::string_view TAB_TAG  = "    ";  // Indentation
static constexpr std::string_view TAG_TAG  = " : ";   // Separator

// === END MODIFIABLE VALUES ===

// ANSI reset code
static constexpr std::string_view COLOR_RESET = "\033[0m";

// Auto-detect build type
#ifdef NDEBUG
static constexpr LogLevel MIN_LEVEL = MIN_LVL_RLS; // Release
static constexpr bool IS_MODE_DEBUG = false;
#else
static constexpr LogLevel MIN_LEVEL = MIN_LVL_DBG; // Debug
static constexpr bool IS_MODE_DEBUG = true;
#endif

// Platform detection
#ifdef _WIN32
static constexpr bool IS_WINDOWS = true;
#else
static constexpr bool IS_WINDOWS = false;
#endif

// Process termination (throws in test mode, aborts in production)
#ifdef ZUTILS_T
inline void killProcess() noexcept {} // Test mode - no termination
#else
[[noreturn]]
inline void killProcess() noexcept { std::abort(); } // Production
#endif

} // namespace config

// Output ColorText to stream (respects ENABLE_COLOR config)
inline std::ostream &operator<<(std::ostream &os, const ColorText &ct)
{
    if constexpr (!config::ENABLE_COLOR) return os << ct.TEXT;
    return os << "\033[" << static_cast<int>(ct.COLOR) << "m" << ct.TEXT << "\033[0m";
}

// Source code location tracking
struct SourceLoc {
    const bool        EMPTY;  //< True if default-constructed
    const std::string TEXT;   //< Formatted as "[FILE:LINE]"

    // Empty location
    SourceLoc() : TEXT{""}, EMPTY{true} {}

    // Create from file and line
    SourceLoc(std::string_view file, int line)
        : TEXT{std::format("[{}:{}]", file, line)}
        , EMPTY{false}
    {}

    // Output location in gray
    friend std::ostream &operator<<(std::ostream &os, const SourceLoc &sl)
    {
        return sl.EMPTY ? os : os << ColorText{sl.TEXT, ANSI::EX_Black};
    }
};

} // namespace zutils

// std::format support for ColorText
template <>
struct std::formatter<zutils::ColorText> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const zutils::ColorText &ct, std::format_context &ctx) const
  {
    return (!zutils::config::ENABLE_COLOR)
    ? std::format_to(ctx.out(), "{}", ct.TEXT)
    : std::format_to(
      ctx.out(),
      "\033[{}m{}\033[0m",
      static_cast<int>(ct.COLOR), ct.TEXT
    );
  }
};

// std::format support for SourceLoc
template <>
struct std::formatter<zutils::SourceLoc> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const zutils::SourceLoc &sl, std::format_context &ctx) const
    {
        return std::format_to(
            ctx.out(),
            "{}",
            zutils::ColorText{sl.TEXT, zutils::ANSI::EX_Black}
        );
    }
};

/// MACROS:

// Create `SourceLoc` for current location
#define ZLOC \
    { ::zutils::SourceLoc {__FILE__, __LINE__} }
