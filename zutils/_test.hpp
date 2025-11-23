#pragma once

#include "./_log.hpp"

#ifndef USING_CUSTOM

#define TEST_PASS_TEXT    "[PASS]"
#define TEST_FAIL_TEXT    "[FAIL]"

#endif

namespace zutils::internal {

#if ENABLE_COLOR_CODE
static constexpr const char* PASS {"\033[32m" TEST_PASS_TAG "\033[0m"};
static constexpr const char* FAIL {"\033[31m" TEST_FAIL_TAG "\033[0m"};
#else
static constexpr const char* PASS {TEST_PASS_TEXT};
static constexpr const char* FAIL {TEST_FAIL_TEXT};
#endif

} // namespace zutils::internal

#define ZTEST(CONDITION) do {                                           \
  ZLOG_RAW                                                              \
    << zutils::internal::ColorText{34, TEST_TAG}                        \
    << ((CONDITION) ? zutils::internal::PASS : zutils::internal::FAIL)  \
    << " : " #CONDITION;                                                \
} while (0)

#define ZTEST_EQ(ACTUAL, EXPECTED)  ZTEST((ACTUAL) == (EXPECTED))
#define ZTEST_NE(ACTUAL, EXPECTED)  ZTEST((ACTUAL) != (EXPECTED))

#define ZVALIDATE(CONDITION, TAG, KILL_FLAG) do {  \
    if (!(CONDITION)) {                            \
      if constexpr (KILL_FLAG) {                   \
        ZLOGF                                      \
          << zutils::internal::ColorText{41, TAG}  \
          << " : " #CONDITION;                     \
        zutils::internal::killProcess();           \
      } else {                                     \
        ZLOGE                                      \
          << zutils::internal::ColorText{31, TAG}  \
          << " : " #CONDITION;                     \
      }                                            \
    }                                              \
} while (0)

#define ZASSERT(CONDITION)  ZVALIDATE(CONDITION, ASSERT_TAG, true)
#define ZASSERT_EQ(ACTUAL, EXPECTED)  ZASSERT((ACTUAL) == (EXPECTED))
#define ZASSERT_NE(ACTUAL, EXPECTED)  ZASSERT((ACTUAL) != (EXPECTED))

#define ZEXPECT(CONDITION)  ZVALIDATE(CONDITION, EXPECT_TAG, false)
#define ZEXPECT_EQ(ACTUAL, EXPECTED)  ZEXPECT((ACTUAL) == (EXPECTED))
#define ZEXPECT_NE(ACTUAL, EXPECTED)  ZEXPECT((ACTUAL) != (EXPECTED))
