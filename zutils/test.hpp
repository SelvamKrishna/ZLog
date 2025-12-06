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
    std::string_view desc,
    const SourceLoc& loc
) noexcept {
    return desc.empty()
    ? std::format(
        "{}{}{}",
        _TAG_COMM(tag),
        loc
    )
    : std::format(
        "{}{}{}{}{}",
        _TAG_COMM(tag),
        _TAG_COMM(loc),
        _DESC(desc)
    );
}

[[nodiscard]]
inline std::string _fmtComplexStr(
    const ColorText& tag,
    std::string_view expr,
    std::string_view desc,
    const SourceLoc& loc
) noexcept {
    return desc.empty()
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
        _DESC(desc)
    );
}

} // namespace internal

/// Unit test assertion (always runs in tests)

inline void test(bool condition, std::string_view desc) noexcept
{
    ZOUT
    << _TAG_OS(config::TEST_TAG)
    << _TAG_OS(condition ? config::PASS_TAG : config::FAIL_TAG)
    << _EXPR(desc);
}

inline void test(bool condition, std::string_view expr, std::string_view desc) noexcept
{
    ZOUT
    << _TAG_OS(config::TEST_TAG)
    << _TAG_OS(condition ? config::PASS_TAG : config::FAIL_TAG)
    << _TAG_OS(_EXPR(expr))
    << _DESC(desc);
}

#undef _TAG_OS
#undef _TAG_COMM
#undef _EXPR
#undef _DESC

/// expectation (non-fatal, always runs)

inline void expect(
    bool condition,
    std::string_view desc,
    SourceLoc loc = {}
) noexcept
{
    if (condition) return;
    ZWARN(internal::_fmtSimpleStr(config::EXPECT_TAG, desc, loc));
}

inline void expect(
    bool condition,
    std::string_view expr,
    std::string_view desc,
    SourceLoc loc = {}
) noexcept
{
    if (condition) return;
    ZWARN(internal::_fmtComplexStr(config::EXPECT_TAG, expr, desc, loc));
}

/// assertion (fatal, only in debug builds)

inline void assert(
    bool condition,
    std::string_view desc,
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
    std::string_view desc,
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
    std::string_view desc,
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
    std::string_view desc,
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
inline void panic(std::string_view desc, SourceLoc loc = {}) noexcept
{
    ZFATAL(internal::_fmtSimpleStr(config::PANIC_TAG, desc, loc));
    config::killProcess();
}

} // namespace zutils::test

/// MACROS:

// Unit testing
#define      ZTEST(COND)         ::zutils::test::test((COND), #COND)
#define    ZTEST_S(COND, DESC)   ::zutils::test::test((COND), #COND, DESC)
#define   ZTEST_EQ(ACT, EXP)     ZTEST(ACT == EXP)
#define   ZTEST_NE(ACT, EXP)     ZTEST(ACT != EXP)
// Non fatal checking
#define    ZEXPECT(COND)         ::zutils::test::expect((COND), #COND, ZLOC)
#define  ZEXPECT_S(COND, DESC)   ::zutils::test::expect((COND), #COND, DESC, ZLOC)
#define ZEXPECT_EQ(ACT, EXP)     ZEXPECT(ACT == EXP)
#define ZEXPECT_NE(ACT, EXP)     ZEXPECT(ACT != EXP)

#ifdef NDEBUG

#define    ZASSERT(COND)         (void(0))
#define  ZASSERT_S(COND, DESC)   (void(0))
#define ZASSERT_EQ(ACT, EXP)     (void(0))
#define ZASSERT_NE(ACT, EXP)     (void(0))

#else

// Fatal debug only checking
#define    ZASSERT(COND)         ::zutils::test::assert((COND), #COND, ZLOC)
#define  ZASSERT_S(COND, DESC)   ::zutils::test::assert((COND), #COND, DESC, ZLOC)
#define ZASSERT_EQ(ACT, EXP)     ZASSERT(ACT == EXP)
#define ZASSERT_NE(ACT, EXP)     ZASSERT(ACT != EXP)

#endif

// Fatal checking
#define    ZVERIFY(COND)         ::zutils::test::verify((COND), #COND, ZLOC)
#define  ZVERIFY_S(COND, DESC)   ::zutils::test::verify((COND), #COND, DESC, ZLOC)
#define ZVERIFY_EQ(ACT, EXP)     ZVERIFY(ACT == EXP)
#define ZVERIFY_NE(ACT, EXP)     ZVERIFY(ACT != EXP)

// Terminates process with message
#define    ZPANIC(DESC)                  ::zutils::test::panic(DESC, ZLOC)
#define ZPANIC_IF(COND, DESC)  if (COND) ::zutils::test::panic(DESC, ZLOC)
