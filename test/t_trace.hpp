#pragma once

#include "zutils/trace.hpp"

#include <thread>
#include <chrono>

namespace test {

inline void trace_basic() {
  ZTRC; // Automatic function name tracing

  ZDBG("Doing some work in simple_function");
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

inline void function_with_args(int a, const std::string &b) {
  ZTRC_S(std::format("function_with_args({}, {})", a, b)); // Custom description

  ZDBG("Processing arguments: {} and {}", a, b);
  std::this_thread::sleep_for(std::chrono::milliseconds(15));
}

class TraceTestClass {
public:
  void method1() {
    ZTRC_C(TestClass); // Class::method format

    ZDBG("Inside TestClass::method1");
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }

  void method2(int value) {
    ZTRC_S(std::format("TestClass::method2({})", value)); // Custom with args

    ZDBG("Processing value: {}", value);
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
  }
};

inline void trace_scope() {
  ZTRC;

  ZDBG("Entering nested_functions");

  {
    ZTRC_S("Inner scope 1");
    ZDBG("Inside inner scope 1");
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }

  {
    ZTRC_S("Inner scope 2");
    ZDBG("Inside inner scope 2");
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }

  ZDBG("Exiting nested_functions");
}

inline void trace_except() {
  ZTRC;

  try {
    ZDBG("Before potential exception");
    // This will show the stack unwinding
    throw std::runtime_error("Test exception");
  } catch (const std::exception &e) {
    ZERR("Caught exception: {}", e.what());
  }
}

inline void trace_recurse(int depth) {
  if (depth <= 0)
    return;

  ZTRC_S(std::format("recursive_function(depth={})", depth));

  ZDBG("Recursive call at depth {}", depth);
  std::this_thread::sleep_for(std::chrono::milliseconds(5));

  trace_recurse(depth - 1);
}

inline void trace_all() {
  std::cout << "Starting Scope Tracing Tests...\n" << std::endl;

  ZTRC_S("main() - Starting tests");

  std::cout << "\n=== Testing Simple Function ===" << std::endl;
  trace_basic();

  std::cout << "\n=== Testing Function with Args ===" << std::endl;
  function_with_args(42, "hello");

  std::cout << "\n=== Testing Class Methods ===" << std::endl;
  TraceTestClass obj;
  obj.method1();
  obj.method2(100);

  std::cout << "\n=== Testing Nested Scopes ===" << std::endl;
  trace_scope();

  std::cout << "\n=== Testing Exception Safety ===" << std::endl;
  trace_except();

  std::cout << "\n=== Testing Recursion ===" << std::endl;
  trace_recurse(3);

  ZDBG("All tests completed");
}

} // namespace test
