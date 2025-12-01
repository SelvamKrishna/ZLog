#pragma once

#include "./config.hpp"
#include "./log.hpp"

#include <string_view>
#include <iostream>

namespace zutils::test {

/// Unit test assertion (always runs in tests)

inline void test(bool condition, std::string_view desc) noexcept
{
  std::cout
    << config::TEST_TAG << config::TAG_TAG
    << (condition ? config::PASS_TAG : config::FAIL_TAG)
    << config::TAG_TAG << ColorText{desc, ANSI::Magenta} << "\n";
}

inline void test(bool condition, std::string_view expr, std::string_view desc) noexcept
{
  std::cout
    << config::TEST_TAG << config::TAG_TAG
    << (condition ? config::PASS_TAG : config::FAIL_TAG) << config::TAG_TAG
    << ColorText{expr, ANSI::Magenta} << config::TAG_TAG
    << ColorText{desc, ANSI::Italic} << "\n";
}

/// Expectation check (non-fatal, always runs)

inline void expect(bool condition, std::string_view desc) noexcept
{
  if (condition) return;
  ZWARN(
    "{}{}{}",
    config::EXPECT_TAG, config::TAG_TAG, ColorText{desc, ANSI::Bold}
  );
}

inline void expect(bool condition, std::string_view expr, std::string_view desc) noexcept
{
  if (condition) return;
  ZWARN(
    "{}{}{}{}{}",
    config::EXPECT_TAG, config::TAG_TAG,
    ColorText{expr, ANSI::Magenta}, config::TAG_TAG,
    ColorText{desc, ANSI::Bold}
  );
}

/// Debug assertion (only in debug builds)

inline void assert(bool condition, std::string_view desc) noexcept
{
  if constexpr (!config::IS_MODE_DEBUG) return;
  if (condition) return;

  ZERR(
    "{}{}{}",
    config::ASSERT_TAG, config::TAG_TAG, ColorText{desc, ANSI::Bold}
  );

  config::killProcess();
}

inline void assert(bool condition, std::string_view expr, std::string_view desc) noexcept
{
  if constexpr (!config::IS_MODE_DEBUG) return;
  if (condition) return;

  ZERR(
    "{}{}{}{}{}",
    config::ASSERT_TAG, config::TAG_TAG,
    ColorText{expr, ANSI::Magenta}, config::TAG_TAG,
    ColorText{desc, ANSI::Bold}
  );

  config::killProcess();
}

/// Runtime assertion (always fatal)

inline void require(bool condition, std::string_view desc) noexcept
{
  if (condition) return;

  ZERR(
    "{}{}{}",
    config::ASSERT_TAG, config::TAG_TAG, ColorText{desc, ANSI::Bold}
  );
  config::killProcess();
}

inline void require(bool condition, std::string_view expr, std::string_view desc) noexcept
{
  if (condition) return;

  ZERR(
    "{}{}{}{}{}",
    config::ASSERT_TAG, config::TAG_TAG,
    ColorText{expr, ANSI::Magenta}, config::TAG_TAG,
    ColorText{desc, ANSI::Bold}
  );
  config::killProcess();
}

/// Panic with message (always fatal)
inline void panic(std::string_view desc) noexcept
{
  ZFATAL(
    "{}{}{}",
    config::PANIC_TAG, config::TAG_TAG, ColorText{desc, ANSI::Bold}
  );
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
#define    ZEXPECT(COND)         ::zutils::test::expect((COND), #COND)
#define  ZEXPECT_S(COND, DESC)   ::zutils::test::expect((COND), #COND, DESC)
#define ZEXPECT_EQ(ACT, EXP)     ZEXPECT(ACT == EXP)
#define ZEXPECT_NE(ACT, EXP)     ZEXPECT(ACT != EXP)

#ifdef NDEBUG

#define    ZASSERT(COND)         (void(0))
#define  ZASSERT_S(COND, DESC)   (void(0))
#define ZASSERT_EQ(ACT, EXP)     (void(0))
#define ZASSERT_NE(ACT, EXP)     (void(0))

#else

#define    ZASSERT(COND)         ::zutils::test::assert((COND), #COND)
#define  ZASSERT_S(COND, DESC)   ::zutils::test::assert((COND), #COND, DESC)
#define ZASSERT_EQ(ACT, EXP)     ZASSERT(ACT == EXP)
#define ZASSERT_NE(ACT, EXP)     ZASSERT(ACT != EXP)

#endif

// Fatal runtime checking
#define    ZREQUIRE(COND)        ::zutils::test::require((COND), #COND)
#define  ZREQUIRE_S(COND, DESC)  ::zutils::test::require((COND), #COND, DESC)
#define ZREQUIRE_EQ(ACT, EXP)    ZREQUIRE(ACT == EXP)
#define ZREQUIRE_NE(ACT, EXP)    ZREQUIRE(ACT != EXP)

#define ZPANIC(DESC)  ::zutils::test::panic(DESC)
