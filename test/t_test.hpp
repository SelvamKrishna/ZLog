#include "zutils/test.hpp"

#include <vector>
#include <string>
#include <memory>

// ==================== Basic Unit Tests ====================

namespace test {

inline void test_basic_arithmetic() {
  std::cout << "\n=== Testing Basic Arithmetic ===" << std::endl;

  ZTEST(1 + 1 == 2);
  ZTEST(2 * 2 == 4);
  ZTEST(10 - 5 == 5);
  ZTEST(20 / 4 == 5);

  ZTEST_S(3 * 3 == 9, "Multiplication works");
  ZTEST_S(100 > 50, "Greater than comparison");
}

inline void test_string_operations() {
  std::cout << "\n=== Testing String Operations ===" << std::endl;

  std::string hello = "Hello";
  std::string world = "World";
  std::string hello_world = hello + " " + world;

  ZTEST_EQ(hello.length(), 5);
  ZTEST_NE(hello, world);
  ZTEST_S(hello_world == "Hello World", "String concatenation works");
}

// ==================== Expectation Tests ====================

inline void test_expectations() {
  std::cout << "\n=== Testing Expectations (Non-Fatal) ===" << std::endl;

  std::vector<int> numbers = {1, 2, 3, 4, 5};

  // These will warn but not stop execution
  ZEXPECT(numbers.size() > 0);
  ZEXPECT_S(!numbers.empty(), "Vector should not be empty");
  ZEXPECT_EQ(numbers.front(), 1);
  ZEXPECT_NE(numbers.back(), 0);

  // This one will fail and print a warning
  ZEXPECT(numbers.size() == 10); // Will warn: "numbers.size() == 10"

  std::cout << "Continued execution after failed expectation" << std::endl;
}

// ==================== Debug Assertions ====================

inline void test_debug_assertions() {
  std::cout << "\n=== Testing Debug Assertions ===" << std::endl;

  int *ptr = new int(42);

  // These only run in debug builds
  ZASSERT(ptr != nullptr);
  ZASSERT_S(*ptr == 42, "Pointer should point to 42");
  ZASSERT_EQ(*ptr, 42);
  ZASSERT_NE(*ptr, 0);

  delete ptr;

  std::cout << "Debug assertions passed (or skipped in release)" << std::endl;
}

// ==================== Runtime Requirements ====================

inline void process_user_input(int value) {
  std::cout << "\n=== Testing Runtime Requirements ===" << std::endl;

  // These will abort the program if they fail
  ZREQUIRE(value >= 0);
  ZREQUIRE_S(value <= 100, "Value must be <= 100");
  ZREQUIRE_EQ(value % 2, 0); // Only accept even numbers

  std::cout << "Input validation passed: " << value << std::endl;
}

// ==================== Complex Types ====================

class User {
private:
  std::string name_;
  int age_;

public:
  User(std::string name, int age) : name_(std::move(name)), age_(age) {}

  const std::string &name() const { return name_; }
  int age() const { return age_; }

  bool is_adult() const { return age_ >= 18; }
};

inline void test_complex_types() {
  std::cout << "\n=== Testing Complex Types ===" << std::endl;

  User alice("Alice", 25);
  User bob("Bob", 16);

  ZTEST_EQ(alice.name(), "Alice");
  ZTEST_EQ(bob.name(), "Bob");
  ZTEST_S(alice.is_adult(), "Alice should be adult");
  ZTEST_S(!bob.is_adult(), "Bob should not be adult");

  ZEXPECT(alice.age() > bob.age());
  ZEXPECT_EQ(alice.age(), 25);
}

// ==================== Edge Cases ====================

inline void test_edge_cases() {
  std::cout << "\n=== Testing Edge Cases ===" << std::endl;

  // Empty collections
  std::vector<int> empty_vec;
  ZEXPECT(empty_vec.empty());

  // Null pointers
  std::unique_ptr<int> null_ptr;
  ZEXPECT(null_ptr == nullptr);

  // Floating point comparisons (careful!)
  double a = 0.1 + 0.2;
  double b = 0.3;
  ZTEST_S(std::abs(a - b) < 0.000001, "Floating point comparison with epsilon");

  // String edge cases
  std::string empty_str;
  ZTEST_EQ(empty_str.length(), 0);
  ZTEST(empty_str.empty());
}

// ==================== Integration Tests ====================

inline int add(int a, int b) {
  return a + b;
}

inline int divide(int a, int b) {
  ZREQUIRE_S(b != 0, "Cannot divide by zero");
  return a / b;
}

inline void test_integrated_functions() {
  std::cout << "\n=== Testing Integrated Functions ===" << std::endl;

  // Test add function
  ZTEST_EQ(add(2, 3), 5);
  ZTEST_EQ(add(0, 0), 0);

  // Test divide function
  ZTEST_EQ(divide(10, 2), 5);
  ZTEST_EQ(divide(0, 5), 0);

  // These would Fail
  ZTEST_EQ(add(-1, 5), 4);
  // ZTEST_EQ(divide(5, 0), 0);
}

// ==================== Error Handling ====================

inline void test_error_conditions() {
  std::cout << "\n=== Testing Error Conditions ===" << std::endl;

  try {
    // Simulate an error condition
    throw std::runtime_error("Test error");
  } catch (const std::exception &e) {
    ZTEST_S(false, std::string("Exception caught: ") + e.what());
  }

  // Test with custom error message
  bool should_fail = false;
  ZEXPECT_S(!should_fail, "This should not fail");
}

// ==================== Panic Tests ====================

inline void test_critical_errors() {
  std::cout << "\n=== Testing Critical Errors (Commented Out) ===" << std::endl;

  // Uncomment to test panic - will terminate program
  // bool critical_failure = true;
  // if (critical_failure) {
  //     ZPANIC("Critical system failure - shutting down");
  // }

  std::cout << "Panic test skipped (would terminate)" << std::endl;
}

// ==================== Performance Tests ====================

inline void test_performance() {
  std::cout << "\n=== Testing Performance ===" << std::endl;

  const int N = 1000;
  std::vector<int> numbers(N);

  // Fill with values
  for (int i = 0; i < N; ++i) {
    numbers[i] = i * 2;
  }

  // Verify all values
  for (int i = 0; i < N; ++i) {
    ZEXPECT_EQ(numbers[i], i * 2);
  }

  std::cout << "Verified " << N << " elements" << std::endl;
}

// ==================== Main Test Runner ====================

inline void test_all() {
  std::cout << "Starting ZUtils Test Framework Demonstration\n" << std::endl;

  // Run all test categories
  test_basic_arithmetic();
  test_string_operations();
  test_expectations();
  test_debug_assertions();

  // Test with valid input
  process_user_input(42);

  // Uncomment to test failure (will abort):
  // process_user_input(-5);  // Would fail ZREQUIRE(value >= 0)
  // process_user_input(101); // Would fail ZREQUIRE(value <= 100)
  // process_user_input(43);  // Would fail ZREQUIRE_EQ(value % 2, 0)

  test_complex_types();
  test_edge_cases();
  test_integrated_functions();
  test_error_conditions();
  test_critical_errors();
  test_performance();

  std::cout << "\n=========================================" << std::endl;
  std::cout << "All tests completed successfully!" << std::endl;
  std::cout << "=========================================" << std::endl;
}

} // namespace test
