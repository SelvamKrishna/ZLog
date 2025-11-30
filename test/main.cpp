#include "zutils/zutils.hpp" // IWYU pragma: keep

using namespace zutils;

//-----------------------------------------------------
// Log level tests
//-----------------------------------------------------
void test_log_levels() {
  ZTRACE;

  ZLOGT << "Trace message";
  ZLOGD << "Debug message";
  ZLOGI << "Info message";
  ZLOGW << "Warning message";
  ZLOGE << "Error message";
  ZLOGF << "Fatal message";
}

//-----------------------------------------------------
// Conditional logging
//-----------------------------------------------------
void test_conditional_logging() {
  ZTRACE;

  bool debug_enabled = true;
  bool error_condition = false;

  ZLOGD_IF(debug_enabled) << "This debug log should appear";
  ZLOGE_IF(error_condition) << "This error log should NOT appear";
  ZLOGW_IF(!error_condition) << "Warning printed because !error_condition == true";
}

//-----------------------------------------------------
// Variable logging
//-----------------------------------------------------
void test_var_logging() {
  ZTRACE;

  struct P { float x, y; };
  P player_pos {.x = 100.2F, .y = 200.4F};

  float velocity = 123.2;

  void* some_ptr = &player_pos;

  ZLOG_V(player_pos.x);
  ZLOG_V(velocity);
  ZLOG_V(some_ptr);
}

//-----------------------------------------------------
// Scope tracing (automatic entry/exit logs)
//-----------------------------------------------------
void inner_function() {
  ZTRACE;
  ZLOGI << "Doing some work inside inner_function()";
}

void test_scope_tracing() {
  ZTRACE_C(TestScope);
  inner_function();
}

//-----------------------------------------------------
// Basic tests (PASS/FAIL style output)
//-----------------------------------------------------
void test_ztest_macros() {
  ZTRACE;

  int a = 5, b = 5, c = 10;

  ZTEST(a == b);
  ZTEST_EQ(a, b);
  ZTEST_EQ(a, c);
  ZTEST_NE(a, c);

  ZTEST_EQ(a + c, 15);
  ZTEST_EQ(a + b, 12);
  ZTEST_NE(a + b, 12);
}

//-----------------------------------------------------
// Assertions (will abort on failure!)
//-----------------------------------------------------
void test_assertions() {
  ZTRACE;
  int x = 42;

  ZASSERT(x == 42);     // should pass
  ZASSERT_EQ(x, 42);    // should pass

  // Uncomment to test failure:
  ZASSERT_NE(x, 42);  // will abort program
}

//-----------------------------------------------------
// Expection (will log error on fail!)
//-----------------------------------------------------
void test_expections() {
  ZTRACE;
  int x = 42;

  ZEXPECT(x == 42);     // should pass
  ZEXPECT_EQ(x, 42);    // should pass

  // Uncomment to test failure:
  // ZEXPECT_NE(x, 42);
}

//-----------------------------------------------------
// Todo Test (will warn and exit on call)
//-----------------------------------------------------
void test_todo() {
  ZTRACE;
  ZTODO("This function needs to be implemented");
}

//-----------------------------------------------------
// Unreachable Test (will log fatal and exit on call)
//-----------------------------------------------------
void test_unreachable() {
  ZTRACE;
  ZUNREACHABLE;
}

//-----------------------------------------------------
// Debug and Release mode dev tools
//-----------------------------------------------------
void test_debug_and_release() {
  ZTRACE;

  ZON_DEBUG ZLOGI   << "Text will print on Debug Mode";
  ZON_RELEASE ZLOGI << "Text will print on Release Mode";
}

//-----------------------------------------------------
// Entry point
//-----------------------------------------------------
int main() {
  ZON_DEBUG {
    ZLOGI << "=== Warp Mini Logger Tests ===";
    // test_log_levels();
    // test_conditional_logging();
    // test_var_logging();
    // test_scope_tracing();
    // test_ztest_macros();
    test_assertions();
    // test_expections();
    // test_todo(); // kills process
    // test_unreachable(); // kills process
    // test_debug_and_release();
    ZLOGI << "=== All tests completed ===";
  }

  return 0;
}
