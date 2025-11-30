#include "zutils/log.hpp"

#include <vector>
#include <string>

namespace test {

inline void logging_basic() {
  std::cout << "=== Testing Basic Logging ===" << std::endl;

  // Test all log levels
  ZDBG("This is a DEBUG message");
  ZINFO("This is an INFO message");
  ZWARN("This is a WARNING message");
  ZERR("This is an ERROR message");
  ZFATAL("This is a FATAL message");

  std::cout << std::endl;
}

inline void logging_args() {
  std::cout << "=== Testing Logging with Arguments ===" << std::endl;

  int number = 42;
  std::string text = "hello world";
  double pi = 3.14159;

  ZDBG("Number: {}, Text: {}, Pi: {:.2f}", number, text, pi);
  ZINFO("The answer is {}", number);
  ZWARN("Value {} is suspicious", number * 2);
  ZERR("Value {} is suspicious", zutils::ColorText {"SOMETHING", 31});

  std::cout << std::endl;
}

inline void logging_cond() {
  std::cout << "=== Testing Conditional Logging ===" << std::endl;

  bool condition_true = true;
  bool condition_false = false;
  int value = 15;

  ZDBG_IF(condition_true, "This should appear - condition is true");
  ZDBG_IF(condition_false, "This should NOT appear - condition is false");
  ZINFO_IF(value > 10, "Value {} is greater than 10", value);
  ZWARN_IF(value < 5, "Value {} is less than 5", value); // Should not appear

  std::cout << std::endl;
}

inline void logging_vars() {
  std::cout << "=== Testing Expression Debugging ===" << std::endl;

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

  std::cout << std::endl;
}

inline void logging_vars_complex() {
  std::cout << "=== Testing Complex Types ===" << std::endl;

  std::vector<int> numbers = {1, 2, 3, 4, 5};
  std::pair<std::string, int> person = {"John", 25};

  ZDBG("Vector size: {}", numbers.size());
  ZDBG("First element: {}", numbers.front());
  ZINFO("Person: {} is {} years old", person.first, person.second);

  // Test with different types
  ZDBG("Boolean: {}, Char: {}, Float: {}", true, 'A', 3.14f);

  std::cout << std::endl;
}

void test_function_tracing() {
  ZTRACE;
  std::cout << "=== Testing Function Tracing ===" << std::endl;

  // Simulate some work
  int result = 0;
  for (int i = 0; i < 5; ++i) {
    ZDBG("Loop iteration: {}", i);
    result += i;
  }

  ZVAR(result);
  std::cout << std::endl;
}

class TestClass {
private:
  int value_;

public:
  TestClass(int v) : value_(v) {
    ZDBG("TestClass constructor called with value: {}", value_);
  }

  void set_value(int v) {
    ZDBG("Changing value from {} to {}", value_, v);
    value_ = v;
  }

  void display() const { ZINFO("TestClass value: {}", value_); }
};

inline void logging_class() {
  std::cout << "=== Testing Class Logging ===" << std::endl;

  TestClass obj(100);
  obj.display();
  obj.set_value(200);
  obj.display();

  std::cout << std::endl;
}

inline void logging_edge_cases() {
  std::cout << "=== Testing Edge Cases ===" << std::endl;

  // Empty message
  ZDBG("");

  // Many arguments
  ZDBG("Multiple: {} {} {} {} {}", 1, 2, 3, 4, 5);

  // Special characters
  ZINFO("Special chars: \\t \\n \\\" {}", "quoted");

  // Very long message
  ZDBG("This is a very long message that might wrap around in the terminal: {}",
       "additional information here");

  std::cout << std::endl;
}

} // namespace test
