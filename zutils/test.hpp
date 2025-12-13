#pragma once

#include "./config.hpp"
#include "./log.hpp"

#include <string_view>

namespace zutils::test {

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
inline std::string _fmtSimpleStr(
    const ColorText& tag,
    log::internal::ProString& desc,
    const SourceLoc& loc
) noexcept {
    return desc.isEmpty()
    ? std::format(
        "{}{}{}",
        _TAG_COMM(tag),
        loc
    )
    : std::format(
        "{}{}{}{}{}",
        _TAG_COMM(tag),
        _TAG_COMM(loc),
        _DESC(desc.TEXT)
    );
}

[[nodiscard]]
inline std::string _fmtComplexStr(
    const ColorText& tag,
    std::string_view expr,
    log::internal::ProString& desc,
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

inline void test(bool condition, log::internal::ProString desc) noexcept
{
    ZOUT
    << _TAG_OS(config::TEST_TAG)
    << _TAG_OS(condition ? config::PASS_TAG : config::FAIL_TAG)
    << _EXPR(desc.TEXT);
}

inline void test(bool condition, std::string_view expr, log::internal::ProString desc) noexcept
{
    ZOUT
    << _TAG_OS(config::TEST_TAG)
    << _TAG_OS(condition ? config::PASS_TAG : config::FAIL_TAG)
    << _TAG_OS(_EXPR(expr))
    << _DESC(desc.TEXT);
}

#undef _TAG_OS
#undef _TAG_COMM
#undef _EXPR
#undef _DESC

/// expectation (non-fatal, always runs)

inline void expect(
    bool condition,
    log::internal::ProString desc,
    SourceLoc loc = {}
) noexcept
{
    if (condition) return;
    ZWARN(internal::_fmtSimpleStr(config::EXPECT_TAG, desc, loc));
}

inline void expect(
    bool condition,
    std::string_view expr,
    log::internal::ProString desc,
    SourceLoc loc = {}
) noexcept
{
    if (condition) return;
    ZWARN(internal::_fmtComplexStr(config::EXPECT_TAG, expr, desc, loc));
}

/// assertion (fatal, only in debug builds)

inline void assert(
    bool condition,
    log::internal::ProString desc,
    SourceLoc loc = {}
) noexcept
{
    if constexpr (!config::IS_MODE_DEBUG) return; // only on debug
    if (condition) return;
    ZERR(internal::_fmtSimpleStr(config::ASSERT_TAG, desc, loc));
    config::killProcess();
}

inline void assert(
    bool condition,
    std::string_view expr,
    log::internal::ProString desc,
    SourceLoc loc = {}
) noexcept
{
    if constexpr (!config::IS_MODE_DEBUG) return; // only on debug
    if (condition) return;
    ZERR(internal::_fmtComplexStr(config::ASSERT_TAG, expr, desc, loc));
    config::killProcess();
}

/// verify (fatal, always)

inline void verify(
    bool condition,
    log::internal::ProString desc,
    SourceLoc loc = {}
) noexcept
{
    if (condition) return;
    ZFATAL(internal::_fmtSimpleStr(config::VERIFY_TAG, desc, loc));
    config::killProcess();
}

inline void verify(
    bool condition,
    std::string_view expr,
    log::internal::ProString desc,
    SourceLoc loc = {}
) noexcept
{
    if (condition) return;
    ZFATAL(internal::_fmtComplexStr(config::VERIFY_TAG, expr, desc, loc));
    config::killProcess();
}

/// Panic with message (always fatal)
#ifndef ZUTILS_T
[[noreturn]]
#endif
inline void panic(log::internal::ProString desc, SourceLoc loc = {}) noexcept
{
    ZFATAL(internal::_fmtSimpleStr(config::PANIC_TAG, desc, loc));
    config::killProcess();
}

} // namespace zutils::test

/// MACROS:

// Unit testing
#define      ZTEST(COND)       do { ::zutils::test::test((COND), {#COND});                } while (0)
#define    ZTEST_S(COND, ...)  do { ::zutils::test::test((COND), (#COND), {__VA_ARGS__}); } while (0)

// Non fatal checking
#define    ZEXPECT(COND)       do { ::zutils::test::expect((COND), {#COND},                ZLOC); } while (0)
#define  ZEXPECT_S(COND, ...)  do { ::zutils::test::expect((COND), (#COND), {__VA_ARGS__}, ZLOC); } while (0)

#ifdef NDEBUG

#define    ZASSERT(COND)       (void(0))
#define  ZASSERT_S(COND, ...)  (void(0))

#else

// Fatal debug only checking
#define    ZASSERT(COND)       do { ::zutils::test::assert((COND), {#COND},                ZLOC); } while (0)
#define  ZASSERT_S(COND, ...)  do { ::zutils::test::assert((COND), (#COND), {__VA_ARGS__}, ZLOC); } while (0)

#endif

// Fatal checking
#define    ZVERIFY(COND)       do { ::zutils::test::verify((COND), {#COND},                ZLOC); } while (0)
#define  ZVERIFY_S(COND, ...)  do { ::zutils::test::verify((COND), (#COND), {__VA_ARGS__}, ZLOC); } while (0)

// Terminates process with message
#define    ZPANIC(...)        do {           ::zutils::test::panic({__VA_ARGS__}, ZLOC); } while (0)
#define ZPANIC_IF(COND, ...)  do { if (COND) ::zutils::test::panic({__VA_ARGS__}, ZLOC); } while (0)
