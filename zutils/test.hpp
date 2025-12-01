#pragma once

#include "./config.hpp"
#include "./log.hpp"

#include <string_view>

namespace zutils::test {

#define  _TAG(TAG)   (TAG) << config::TAG_TAG
#define _EXPR(EXPR)  ColorText{(EXPR), ANSI::Magenta}

#define _SIMPLE_MSG(TAG)      \
  "{}{}{}{}{}",               \
  (TAG), config::TAG_TAG,     \
  loc, config::TAG_TAG,       \
  ColorText{desc, ANSI::Bold} \

#define _COMPLX_MSG(TAG)                           \
  "{}{}{}{}{}{}",                                  \
  (TAG), config::TAG_TAG,                          \
  loc, config::TAG_TAG,                            \
  ColorText{expr, ANSI::Magenta}, config::TAG_TAG, \
  ColorText{desc, ANSI::Bold}                      \

/// Unit test assertion (always runs in tests)

inline void test(bool condition, std::string_view desc) noexcept
{
  ZOUT
    << _TAG(config::TEST_TAG)
    << _TAG(condition ? config::PASS_TAG : config::FAIL_TAG)
    << _TAG(_EXPR(desc));
}

inline void test(bool condition, std::string_view expr, std::string_view desc) noexcept
{
  ZOUT
    << _TAG(config::TEST_TAG)
    << _TAG(condition ? config::PASS_TAG : config::FAIL_TAG)
    << _TAG(_EXPR(expr))
    << _TAG(desc);
}

#undef _TAG
#undef _EXPR

/// Expectation check (non-fatal, always runs)

inline void expect(bool condition, std::string_view desc, SourceLoc loc = {}) noexcept
{
  if (condition) return;
  ZWARN(_SIMPLE_MSG(config::EXPECT_TAG));
}

inline void expect(bool condition, std::string_view expr, std::string_view desc, SourceLoc loc = {}) noexcept
{
  if (condition) return;
  ZWARN(_COMPLX_MSG(config::EXPECT_TAG));
}

/// Debug assertion (only in debug builds)

inline void assert(bool condition, std::string_view desc, SourceLoc loc = {}) noexcept
{
  if constexpr (!config::IS_MODE_DEBUG) return;
  if (condition) return;
  ZERR(_SIMPLE_MSG(config::ASSERT_TAG));
  config::killProcess();
}

inline void assert(bool condition, std::string_view expr, std::string_view desc, SourceLoc loc = {}) noexcept
{
  if constexpr (!config::IS_MODE_DEBUG) return;
  if (condition) return;
  ZERR(_COMPLX_MSG(config::ASSERT_TAG));
  config::killProcess();
}

/// Runtime assertion (always fatal)

inline void require(bool condition, std::string_view desc, SourceLoc loc = {}) noexcept
{
  if (condition) return;
  ZERR(_SIMPLE_MSG(config::ASSERT_TAG));
  config::killProcess();
}

inline void require(bool condition, std::string_view expr, std::string_view desc, SourceLoc loc = {}) noexcept
{
  if (condition) return;
  ZERR(_COMPLX_MSG(config::ASSERT_TAG));
  config::killProcess();
}

/// Panic with message (always fatal)
[[noreturn]]
inline void panic(std::string_view desc, SourceLoc loc = {}) noexcept
{
  ZFATAL(_SIMPLE_MSG(config::PANIC_TAG));
  config::killProcess();
}

#undef _SIMPLE_MSG
#undef _COMPLX_MSG

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

// Fatal runtime checking
#define    ZREQUIRE(COND)        ::zutils::test::require((COND), #COND, ZLOC)
#define  ZREQUIRE_S(COND, DESC)  ::zutils::test::require((COND), #COND, DESC, ZLOC)
#define ZREQUIRE_EQ(ACT, EXP)    ZREQUIRE(ACT == EXP)
#define ZREQUIRE_NE(ACT, EXP)    ZREQUIRE(ACT != EXP)

#define ZPANIC(DESC)  ::zutils::test::panic(DESC, ZLOC)
