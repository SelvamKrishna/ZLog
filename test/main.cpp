#include "zutils/log.hpp"
#include "zutils/test.hpp"
#include "zutils/trace.hpp"


// -----------------------------------------------------------
// LOGGING DEMO
// -----------------------------------------------------------
namespace demo_log {

void run() {
  ZOUT << "\n=== LOGGING SHOWCASE ===\n";

  ZDBG("Debug message: x = {}", 42);
  ZINFO("Info: startup phase {}", "initializing");
  ZWARN("Warning: value {} near limit", 95);
  ZERR("Error: missing file '{}'", "config.ini");
  ZFATAL("Fatal: component {} failed", "Renderer");

  bool ok = true;
  ZINFO_IF(ok, "Conditional log when ok = {}", ok);
  ZWARN_IF(!ok, "This warning will not appear");

  int counter = 123;
  ZVAR(counter);
}

} // namespace demo_log

// -----------------------------------------------------------
// TRACING DEMO
// -----------------------------------------------------------
namespace demo_trace {

void simple() {
  ZTRC;
  ZINFO("Inside simple() function");
}

void custom() {
  ZTRC_S("Loading Resources");
  ZDBG("Pretend resource loading here...");
}

struct DemoClass {
  void method() {
    ZTRC_C(DemoClass);
    ZINFO("Inside DemoClass::method()");
  }
};

void nested() {
  ZTRC_S("Outer Scope");

  {
    ZTRC_S("Inner A");
    ZDBG("Working inside A");
  }
  {
    ZTRC_S("Inner B");
    ZDBG("Working inside B");
  }
}

void lambdaTest() {
  auto fn = []() {
    ZTRC_S("Lambda Execution");
    ZINFO("Inside lambda");
  };
  fn();
}

void run() {
  ZOUT << "\n=== TRACE SHOWCASE ===\n";

  simple();
  custom();

  DemoClass d;
  d.method();

  nested();
  lambdaTest();

  ZINFO("Trace demo complete.");
}

} // namespace demo_trace

// -----------------------------------------------------------
// TEST / ASSERTION DEMO
// -----------------------------------------------------------
namespace demo_test {

void run() {
  ZOUT << "\n=== TESTING SHOWCASE ===\n";

  // Unit Tests
  ZOUT << "\n-- UNIT TESTS --\n";
  ZTEST(1 + 1 == 2);
  ZTEST_S(2 * 3 == 6, "multiplication");
  ZTEST_EQ(5, 5);
  ZTEST_NE(5, 7);

  // Example intentional fail
  ZTEST_S(2 + 2 == 5, "intentional fail example");

  // Expectations
  ZOUT << "\n-- EXPECTATIONS --\n";
  ZEXPECT(10 > 1);
  ZEXPECT_S(4 > 9, "intentional expect warn");

  // Debug Asserts
  ZOUT << "\n-- DEBUG ASSERTS --\n";
  ZASSERT(3 * 3 == 9);
  ZASSERT_S(3 * 3 == 8, "intentional debug assert fail");

  // Runtime Requirements
  ZOUT << "\n-- REQUIRE --\n";
  ZREQUIRE(100 > 3);
  ZREQUIRE_S(0 != 0, "intentional require fail");

  // Panic
  ZOUT << "\n-- PANIC --\n";
  ZPANIC("demonstration panic");

  ZOUT << "\n=== TESTING COMPLETE ===\n";
}

} // namespace demo_test

// -----------------------------------------------------------
// MAIN
// -----------------------------------------------------------
int main() {
  demo_log  ::run();
  demo_trace::run();
  demo_test ::run();
  return 0;
}
