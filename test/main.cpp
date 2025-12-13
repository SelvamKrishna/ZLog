#include "zutils/log.hpp"   // IWYU pragma: keep
#include "zutils/test.hpp"  // IWYU pragma: keep
#include "zutils/tools.hpp" // IWYU pragma: keep
#include "zutils/trace.hpp" // IWYU pragma: keep

#if 1

namespace demo_log {

void run() {
    ZOUT << "=== LOGGING SHOWCASE ===\n\n";

    ZDBG("Debug message: x = {}", 42);
    ZINFO("Info: startup phase {}", "initializing");
    ZWARN("Warning: value {} near limit", 95);
    ZERR("Error: missing file '{}'", "config.ini");
    ZFATAL("Fatal: component {} failed", "Renderer");

    bool ok = true;
    ZINFO_IF(ok, "Conditional log when ok = {}", ok);
    ZWARN_IF(!ok, "This warning will not appear");

    int counter = 123;
    // ZVAR(counter);

    ZOUT << "=== LOGGING COMPLETE ===\n";
}

} // namespace demo_log

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
    ZOUT << "=== TRACE SHOWCASE ===\n\n";

    simple();
    custom();

    DemoClass d;
    d.method();

    nested();
    lambdaTest();

    ZOUT << "=== TRACE COMPLETE ===\n";
}

} // namespace demo_trace

namespace demo_test {

void run() {
    ZOUT << "=== TESTING SHOWCASE ===\n\n";

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

    // Asserts
    ZOUT << "\n-- ASSERTS --\n";
    ZASSERT(3 * 3 == 9);
    ZASSERT_S(3 * 3 == 8, "intentional debug assert fail");

    // Verifies
    ZOUT << "\n-- VERIFIES --\n";
    ZVERIFY(3 * 3 == 9);
    ZVERIFY_S(3 * 3 == 8, "intentional verify fail");

    // Panic
    ZOUT << "\n-- PANIC --\n";
    ZPANIC("demonstration panic");
    ZPANIC_IF(false, "Shouldn't show");
    ZPANIC_IF(true, "Should show");

    ZOUT << "=== TESTING COMPLETE ===\n";
}

} // namespace demo_test

namespace demo_tools {

void run()
{
    ZOUT << "\n--- CAUTION EXAMPLES ---\n";

    ZTODO("Implement proper input validation");
    ZDEPRECATED("This function will be removed in the next release");
    ZOPTIMIZE("Loop can be vectorized for better performance");
    ZSECURITY("Check user authentication before proceeding");
    ZPERFORMANCE("Consider caching results to reduce computation");

    ZOUT << "\n--- CRITICAL EXAMPLES ---\n";

    // The following normally abort, but in demo/testing builds
    // killProcess() can be no-op for showcase purposes.
    ZUNREACHABLE("Reached supposedly unreachable code block");
    ZUNIMPLEMENTED("This feature is not implemented yet");
    ZFIXME("Fix edge case when input is negative");
    ZMEMORY("Detected potential memory leak in buffer allocation");
    ZTHREAD_SAFETY("Potential data race detected on shared resource");

    ZOUT << "\n--- SHOWCASE COMPLETE ---\n";
}

} // namespace demo_tools

#endif

int main() {
    demo_log  ::run();
    // demo_trace::run();
    // demo_test ::run();
    // demo_tools::run();

    return 0;
}
