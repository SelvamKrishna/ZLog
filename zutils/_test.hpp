#pragma once

#include "./config.hpp"
#include "./log.hpp"

#include <iostream>

namespace zutils::test {

inline void defaultUnit(bool condition, std::string_view desc) noexcept
{
  std::cout
    << config::TEST_TAG << config::TAG_TAG
    << (condition ? config::PASS_TAG : config::FAIL_TAG)
    << config::TAG_TAG << desc << "\n";
}

inline void check(bool condition, std::string_view desc) noexcept
{

  if (condition) return;
  ZWARN("");
}

} // namespace zutils::test

#define ZTEST(CONDITION)  ::zutils::test::defaultUnit((CONDITION), #CONDITION)

#define ZTEST_EQ(ACTUAL, EXPECTED)  ZTEST((ACTUAL) == (EXPECTED))
#define ZTEST_NE(ACTUAL, EXPECTED)  ZTEST((ACTUAL) != (EXPECTED))

#ifdef NDEBUG

#define ZVALIDATE(CONDITION, TAG, KILL_FLAG) do {  \
} while (0)

#else

#define ZVALIDATE(CONDITION, TAG, KILL_FLAG) do {  \
  if (!(CONDITION)) {                              \
    if constexpr (KILL_FLAG) {                     \
      ZLOGF                                        \
        << zutils::internal::ColorText{41, TAG}    \
        << " : " #CONDITION << "\n";               \
      zutils::internal::killProcess();             \
    } else {                                       \
      ZLOGE                                        \
        << zutils::internal::ColorText{31, TAG}    \
        << " : " #CONDITION;                       \
    }                                              \
  }                                                \
} while (0)

#endif

#define ZASSERT(CONDITION)  ZVALIDATE(CONDITION, ASSERT_TAG, true)
#define ZASSERT_EQ(ACTUAL, EXPECTED)  ZASSERT((ACTUAL) == (EXPECTED))
#define ZASSERT_NE(ACTUAL, EXPECTED)  ZASSERT((ACTUAL) != (EXPECTED))

#define ZEXPECT(CONDITION)  ZVALIDATE(CONDITION, EXPECT_TAG, false)
#define ZEXPECT_EQ(ACTUAL, EXPECTED)  ZEXPECT((ACTUAL) == (EXPECTED))
#define ZEXPECT_NE(ACTUAL, EXPECTED)  ZEXPECT((ACTUAL) != (EXPECTED))
