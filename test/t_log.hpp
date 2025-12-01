#pragma once

#include "zutils/log.hpp"

#include <vector>
#include <string>

namespace test {

inline void log_basic() {
  std::cout << ("=== Testing Basic Logging ===") << "\n";
  // Test all log levels
  ZDBG("This is a DEBUG message");
  ZINFO("This is an INFO message");
  ZWARN("This is a WARNING message");
  ZERR("This is an ERROR message");
  ZFATAL("This is a FATAL message");
}

inline void log_args() {
  std::cout <<("=== Testing Logging with Arguments ===") << "\n";

  int number = 42;
  std::string text = "hello world";
  double pi = 3.14159;

  ZDBG("Number: {}, Text: {}, Pi: {:.2f}", number, text, pi);
  ZINFO("The answer is {}", number);
  ZWARN("Value {} is suspicious", number * 2);
  ZERR("Value {} is suspicious", zutils::ColorText {"SOMETHING", zutils::ANSI::EX_Magenta});
}

inline void log_cond() {
  std::cout <<("=== Testing Conditional Logging ===") << "\n";

  bool condition_true = true;
  bool condition_false = false;
  int value = 15;

  ZDBG_IF(condition_true, "This should appear - condition is true");
  ZDBG_IF(condition_false, "This should NOT appear - condition is false");
  ZINFO_IF(value > 10, "Value {} is greater than 10", value);
  ZWARN_IF(value < 5, "Value {} is less than 5", value); // Should not appear
}

inline void log_vars() {
  std::cout <<("=== Testing Expression Debugging ===") << "\n";

  int x = 10;
  int y = 20;
  std::string name = "Alice";

  ZVAR(x);
  ZVAR(y);
  ZVAR(x + y);
  ZVAR(x * y + 5);
  ZVAR(name.length());
  ZVAR(x > y);
  ZVAR(name == "Alice");
}

inline void log_vars_complex() {
  std::cout <<("=== Testing Complex Types ===") << "\n";

  std::vector<int> numbers = {1, 2, 3, 4, 5};
  std::pair<std::string, int> person = {"John", 25};

  ZDBG("Vector size: {}", numbers.size());
  ZDBG("First element: {}", numbers.front());
  ZINFO("Person: {} is {} years old", person.first, person.second);

  // Test with different types
  ZDBG("Boolean: {}, Char: {}, Float: {}", true, 'A', 3.14f);
}

class LogTestClass {
private:
  int value_;

public:
  LogTestClass(int v) : value_(v) {
    ZDBG("TestClass constructor called with value: {}", value_);
  }

  void set_value(int v) {
    ZDBG("Changing value from {} to {}", value_, v);
    value_ = v;
  }

  void display() const { ZINFO("TestClass value: {}", value_); }
};

inline void log_class() {
  std::cout <<("=== Testing Class Logging ===") << "\n";

  LogTestClass obj(100);
  obj.display();
  obj.set_value(200);
  obj.display();
}

inline void log_edge_case() {
  std::cout <<("=== Testing Edge Cases ===") << "\n";

  // Empty message
  ZDBG("");

  // Many arguments
  ZDBG("Multiple: {} {} {} {} {}", 1, 2, 3, 4, 5);

  // Special characters
  ZINFO("Special chars: \\t \\n \\\" {}", "quoted");

  // Very long message
  ZDBG("This is a very long message that might wrap around in the terminal: {}",
       "additional information here");
}

inline void log_all() {
  std::cout <<("=== Testing all Logging features ===") << "\n";
  test::log_basic();
  test::log_args();
  test::log_cond();
  test::log_vars();
  test::log_vars_complex();
  test::log_class();
  test::log_edge_case();
}

} // namespace test
