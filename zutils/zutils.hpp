#pragma once

// Does not affect testing
#define DISABLE_LOGGING         0

// Minimum supported logging level for different builds
#define MIN_LOG_LVL_DEBUG       L_TRACE
#define MIN_LOG_LVL_RELEASE     L_INFO

// Logging configuration flags
#define ENABLE_TIMESTAMP        1
#define ENABLE_COLOR_CODE       1
#define ENABLE_TRACE_DULL       1

// Logging level tags
#define TRACE_TAG               "[TRCE]"
#define DEBUG_TAG               "[DEBG]"
#define INFO_TAG                "[INFO]"
#define WARN_TAG                "[WARN]"
#define ERROR_TAG               "[ERRO]"
#define FATAL_TAG               "[FATL]"

// Testing tags
#define TEST_TAG                "[TEST]"
#define TEST_PASS_TAG           "[PASS]"
#define TEST_FAIL_TAG           "[FAIL]"

// Tracing tags
#define SCOPE_ENTER_TAG         "--{"
#define SCOPE_LEAVE_TAG         "}--"

// Misc tags
#define ASSERT_TAG              "[ASRT]"
#define EXPECT_TAG              "[EXPC]"
#define TODO_TAG                "[TODO]"
#define UNREACHABLE_TAG         "[UNRC]"
#define TAB_TAG                 "  "

// Do Not Touch
#define USING_CUSTOM

#include "./_log.hpp"       // IWYU pragma: keep
#include "./_trace.hpp"     // IWYU pragma: keep
#include "./_test.hpp"      // IWYU pragma: keep
#include "./_dev_tools.hpp" // IWYU pragma: keep
