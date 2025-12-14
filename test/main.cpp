#include <zlog_v2.hpp>

#if 1

namespace demo_log {

void run() {
    ZOUT << "=== LOGGING SHOWCASE ===\n\n";

    int x = 42;
    const char* phase = "initializing";
    int near_limit = 95;
    const char* missing = "config.ini";
    const char* component = "Renderer";

    ZDBG("Debug message: x = {}", x);
    ZINFO("Info: startup phase {}", phase);
    ZWARN("Warning: value {} near limit", near_limit);
    ZERR("Error: missing file '{}'", missing);
    ZFATAL("Fatal: component {} failed", component);

    bool ok = true;
    ZINFO_IF(ok, "Conditional log when ok = {}", ok);
    ZWARN_IF(!ok, "This warning will not appear (ok = {})", ok);

    int counter = 123;
    ZVAR(counter);

    ZOUT << "=== LOGGING COMPLETE ===\n";
}

} // namespace demo_log

namespace demo_trace {

void simple() {
    ZTRC;
    ZINFO("Inside {}() function", "simple");
}

void custom() {
    ZTRC_S("Loading Resources");
    ZDBG("Pretend resource loading: {} items", 3);
}

struct DemoClass {
    void method() {
        ZTRC_C(DemoClass);
        ZINFO("Inside {}::{}()", "DemoClass", "method");
    }
};

void nested() {
    ZTRC_S("Outer Scope");

    {
        ZTRC_S("Inner A");
        ZDBG("Working inside {}", "A");
    }
    {
        ZTRC_S("Inner B");
        ZDBG("Working inside {}", "B");
    }
}

void lambdaTest() {
    auto fn = []() {
        ZTRC_S("Lambda Execution");
        ZINFO("Inside {}", "lambda");
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

    ZOUT << "\n-- UNIT TESTS ---\n";
    ZTEST(1 + 1 == 2);
    ZTEST(2 * 3 == 6, "{}", "multiplication");
    ZTEST(2 + 2 == 5, "intentional fail: {} + {} != {}", 2, 2, 5);

    ZOUT << "\n-- EXPECTATIONS ---\n";
    ZEXPECT(10 > 1);
    ZEXPECT(4 > 9, "intentional expect warn: {} > {}", 4, 9);

    ZOUT << "\n-- ASSERTS ---\n";
    ZASSERT(3 * 3 == 9);
    ZASSERT(3 * 3 == 8, "intentional assert fail: {} * {} != {}", 3, 3, 8);

    ZOUT << "\n-- VERIFIES ---\n";
    ZVERIFY(3 * 3 == 9);
    ZVERIFY(3 * 3 == 8, "intentional verify fail: {} * {} != {}", 3, 3, 8);

    ZOUT << "\n-- PANIC ---\n";
    ZPANIC("demonstration panic: code {}", 1);
    ZPANIC_IF(false, "Shouldn't show: flag = {}", false);
    ZPANIC_IF(true, "Should show: flag = {}", true);

    ZOUT << "=== TESTING COMPLETE ===\n";
}

} // namespace demo_test

namespace demo_tools {

void run() {
    ZOUT << "\n--- CAUTION EXAMPLES ---\n";

    ZTODO("{}", "Implement proper input validation");
    ZDEPRECATED("{}", "This function will be removed in the next release");
    ZOPTIMIZE("{}", "Loop can be vectorized for better performance");
    ZSECURITY("{}", "Check user authentication before proceeding");
    ZPERFORMANCE("{}", "Consider caching results to reduce computation");

    ZOUT << "\n--- CRITICAL EXAMPLES ---\n";

    ZUNREACHABLE("Reached supposedly unreachable code block: {}", 0xDEAD);
    ZUNIMPLEMENTED("This feature '{}' is not implemented yet", "Hot Reload");
    ZFIXME("Fix edge case when input is {}", "negative");
    ZMEMORY("Detected potential memory leak in {}", "buffer allocation");
    ZTHREAD_SAFETY("Potential data race on {}", "shared resource");

    ZOUT << "\n--- SHOWCASE COMPLETE ---\n";
}

} // namespace demo_tools

#endif

int main() {
    demo_log  ::run();
    demo_trace::run();
    demo_test ::run();
    demo_tools::run();

    return 0;
}
