#pragma once

#include "./config.hpp"
#include "./log.hpp"

#include <iostream>
#include <string_view>
#include <format>

namespace zutils::test {

inline void test(bool flag, std::string_view desc) noexcept {
  std::cout
    << config::TEST_TAG << config::TAG_TAG
    << (flag ? config::PASS_TAG : config::FAIL_TAG)
    << config::TAG_TAG << ColorText{desc, ANSI::Magenta} << "\n";
}

inline void test(bool flag, std::string_view expr, std::string_view desc) noexcept {
  std::cout
    << config::TEST_TAG << config::TAG_TAG
    << (flag ? config::PASS_TAG : config::FAIL_TAG)
    << config::TAG_TAG << ColorText{expr, ANSI::Magenta} << " - " << ColorText{desc, ANSI::Italic} << "\n";
}

inline void check(bool flag, std::string_view desc) noexcept {
  if (flag) return;
  ZWARN("{}{}{}", config::CHECK_TAG, config::TAG_TAG, ColorText{desc, ANSI::Bold});
}

inline void check(bool flag, std::string_view expr, std::string_view desc) noexcept {
  if (flag) return;
  ZWARN("{}{}{} - {}", config::CHECK_TAG, config::TAG_TAG, expr, ColorText{desc, ANSI::Bold});
}

inline void assert(bool flag, std::string_view desc) noexcept {
  if constexpr (!config::IS_MODE_DEBUG) return;
  if (flag) return;

  ZERR("{}{}{}", config::ASSERT_TAG, config::TAG_TAG, ColorText{desc, ANSI::Bold});
  config::killProcess();
}

inline void assert(bool flag, std::string_view expr, std::string_view desc) noexcept {
  if constexpr (!config::IS_MODE_DEBUG) return;
  if (flag) return;

  ZERR("{}{}{} - {}", config::ASSERT_TAG, config::TAG_TAG, expr, ColorText{desc, ANSI::Bold});
  config::killProcess();
}

inline void panic(std::string_view desc) noexcept {
  ZFATAL("{}{}{}", config::PANIC_TAG, config::TAG_TAG, ColorText{desc, ANSI::Bold});
  config::killProcess();
}

} // namespace zutils::test

/// MACROS:

#define     ZTEST(FLAG)       ::zutils::test::test  ((FLAG), #FLAG)
#define   ZTEST_S(FLAG, DESC) ::zutils::test::test  ((FLAG), #FLAG, DESC)
#define    ZCHECK(FLAG)       ::zutils::test::check ((FLAG), #FLAG)
#define  ZCHECK_S(FLAG, DESC) ::zutils::test::check ((FLAG), #FLAG, DESC)
#define   ZASSERT(FLAG)       ::zutils::test::assert((FLAG), #FLAG)
#define ZASSERT_S(FLAG, DESC) ::zutils::test::assert((FLAG), #FLAG, DESC)
#define    ZPANIC(DESC)       ::zutils::test::panic(DESC)

#define   ZTEST_EQ(ACTUAL, EXPECTED)    ZTEST((ACTUAL) == (EXPECTED))
#define   ZTEST_NE(ACTUAL, EXPECTED)    ZTEST((ACTUAL) != (EXPECTED))
#define  ZCHECK_EQ(ACTUAL, EXPECTED)   ZCHECK((ACTUAL) == (EXPECTED))
#define  ZCHECK_NE(ACTUAL, EXPECTED)   ZCHECK((ACTUAL) != (EXPECTED))
#define ZASSERT_EQ(ACTUAL, EXPECTED)  ZASSERT((ACTUAL) == (EXPECTED))
#define ZASSERT_NE(ACTUAL, EXPECTED)  ZASSERT((ACTUAL) != (EXPECTED))

#define       ZTEST_NULL(PTR)    ZTEST((PTR) == nullptr)
#define   ZTEST_NOT_NULL(PTR)    ZTEST((PTR) != nullptr)
#define      ZCHECK_NULL(PTR)   ZCHECK((PTR) == nullptr)
#define  ZCHECK_NOT_NULL(PTR)   ZCHECK((PTR) != nullptr)
#define     ZASSERT_NULL(PTR)  ZASSERT((PTR) == nullptr)
#define ZASSERT_NOT_NULL(PTR)  ZASSERT((PTR) != nullptr)
