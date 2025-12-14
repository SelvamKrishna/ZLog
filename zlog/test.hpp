#pragma once

#include "./config.hpp"
#include "./log.hpp"

#include <string_view>

namespace zlog {

#define _TAG_OS(TAG) \
    (TAG) << config::TAG_TAG

#define _TAG_COMM(TAG) \
    (TAG), config::TAG_TAG

#define _EXPR(EXPR) \
    ColorText{(EXPR), ANSI::Magenta}

#define _DESC(DESC) \
    ColorText{(DESC), ANSI::Bold}

namespace internal {

[[nodiscard]]
inline std::string _testFmt(
    const ColorText& tag,
    std::string_view expr,
    ProString& desc,
    const SourceLoc& loc
) noexcept {
    return desc.isEmpty()
    ? std::format(
        "{}{}{}{}{}",
        _TAG_COMM(tag),
        _TAG_COMM(loc),
        _EXPR(expr)
    )
    : std::format(
        "{}{}{}{}{}{}{}",
        _TAG_COMM(tag),
        _TAG_COMM(loc),
        _TAG_COMM(_EXPR(expr)),
        _DESC(desc.TEXT)
    );
}

} // namespace internal

/// Unit test assertion (always runs in tests)

inline void test(bool condition, std::string_view expr, internal::ProString desc) noexcept
{
    ZOUT
    << _TAG_OS(config::TEST_TAG)
    << _TAG_OS(condition ? config::PASS_TAG : config::FAIL_TAG)
    << _EXPR(expr)
    << (desc.isEmpty() ? "" : config::TAG_TAG)
    << _DESC(desc.TEXT);
}

/// expectation (non-fatal, always runs)
inline void expect(
    bool condition,
    std::string_view expr,
    internal::ProString desc,
    SourceLoc loc = {}
) noexcept
{
    if (condition) return;
    ZWARN(internal::_testFmt(config::EXPECT_TAG, expr, desc, loc));
}

/// assertion (fatal, only in debug builds)
inline void assert(
    bool condition,
    std::string_view expr,
    internal::ProString desc,
    SourceLoc loc = {}
) noexcept
{
#ifndef NDEBUG
    if constexpr (!config::IS_MODE_DEBUG) return; // only on debug
    if (condition) return;
    ZERR(internal::_testFmt(config::ASSERT_TAG, expr, desc, loc));
    config::killProcess();
#endif
}

/// verify (fatal, always)
inline void verify(
    bool condition,
    std::string_view expr,
    internal::ProString desc,
    SourceLoc loc = {}
) noexcept
{
    if (condition) return;
    ZFATAL(internal::_testFmt(config::VERIFY_TAG, expr, desc, loc));
    config::killProcess();
}

/// Panic with message (always fatal)
#ifndef ZLOG_T
[[noreturn]]
#endif
inline void panic(internal::ProString desc, SourceLoc loc = {}) noexcept
{
    if (desc.isEmpty())
        ZFATAL("{}{}{}", _TAG_COMM(config::PANIC_TAG), loc);
    else
        ZFATAL("{}{}{}{}{}", _TAG_COMM(config::PANIC_TAG), _TAG_COMM(loc), _DESC(desc.TEXT));

    config::killProcess();
}

#undef _TAG_OS
#undef _TAG_COMM
#undef _EXPR
#undef _DESC


} // namespace zlog

/// MACROS:

#define   ZTEST(COND, ...)  do { ::zlog::test  ((COND), (#COND), {__VA_ARGS__}      ); } while (0)
#define ZEXPECT(COND, ...)  do { ::zlog::expect((COND), (#COND), {__VA_ARGS__}, _ZSL); } while (0)
#define ZASSERT(COND, ...)  do { ::zlog::assert((COND), (#COND), {__VA_ARGS__}, _ZSL); } while (0)
#define ZVERIFY(COND, ...)  do { ::zlog::verify((COND), (#COND), {__VA_ARGS__}, _ZSL); } while (0)

#define    ZPANIC(...)        do {           ::zlog::panic({__VA_ARGS__}, _ZSL); } while (0)
#define ZPANIC_IF(COND, ...)  do { if (COND) ::zlog::panic({__VA_ARGS__}, _ZSL); } while (0)
