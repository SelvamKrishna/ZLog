#pragma once

#include "zutils/_test.hpp"
#include <memory>
#include <string>
#include <vector>

namespace test {

  // Test functions that demonstrate various features
inline void test_basic_assertions() {
  ZINFO("=== Testing Basic Assertions ===");

  // Basic equality
  ZTEST_EQ(2 + 2, 4);
  ZTEST_NE(5, 10);

  // With descriptions
  ZTEST_S(2 + 2 == 4, "Basic arithmetic should work");
  ZTEST_S(10 > 5, "Comparison operators should work");

  ZINFO("Basic assertions test completed\n");
}

inline void test_pointer_assertions() {
  ZINFO("=== Testing Pointer Assertions ===");

  int value = 42;
  int *valid_ptr = &value;
  int *null_ptr = nullptr;

  ZTEST_NOT_NULL(valid_ptr);
  ZTEST_NULL(null_ptr);

  std::unique_ptr<int> smart_ptr = std::make_unique<int>(100);
  ZTEST_NOT_NULL(smart_ptr.get());

  ZTEST_S(valid_ptr != nullptr, "Valid pointer should not be null");

  ZINFO("Pointer assertions test completed\n");
}

inline void test_string_operations() {
  ZINFO("=== Testing String Operations ===");

  std::string hello = "Hello";
  std::string world = "World";
  std::string hello_world = "Hello World";

  // String equality
  ZTEST_S(hello == "Hello", "String equality should work");
  ZTEST_S(hello != world, "String inequality should work");

  // String operations
  ZTEST_S(hello + " " + world == hello_world,
          "String concatenation should work");
  ZTEST_S(hello_world.find("World") != std::string::npos,
          "String find should work");

  ZINFO("String operations test completed\n");
}

inline void test_container_operations() {
  ZINFO("=== Testing Container Operations ===");

  std::vector<int> numbers = {1, 2, 3, 4, 5};
  std::vector<std::string> words = {"apple", "banana", "cherry"};

  // Vector operations
  ZTEST_S(numbers.size() == 5, "Vector size should be correct");
  ZTEST_S(numbers[0] == 1, "Vector access should work");
  ZTEST_S(numbers.back() == 5, "Vector back should work");

  // String vector
  ZTEST_S(words[1] == "banana", "String vector access should work");

  ZINFO("Container operations test completed\n");
}

inline void test_floating_point_operations() {
  ZINFO("=== Testing Floating Point Operations ===");

  double a = 0.1;
  double b = 0.2;
  double c = 0.3;

  // Direct comparison (might fail due to floating point precision)
  ZTEST_S(a + b != c,
          "Floating point direct comparison might show precision issues");

  // Comparison with tolerance
  double tolerance = 1e-10;
  ZTEST_S(std::abs((a + b) - c) < tolerance,
          "Floating point with tolerance should work");

  // More floating point tests
  ZTEST_S(1.0 / 3.0 > 0.333, "Floating point division should work");
  ZTEST_S(100.0 * 0.01 == 1.0, "Some floating point operations are exact");

  ZINFO("Floating point operations test completed\n");
}

inline void test_check_operations() {
  ZINFO("=== Testing Check Operations (Non-fatal) ===");

  // These will warn but not stop execution
  ZCHECK_EQ(2 + 2, 4);
  ZCHECK_NE(5, 10);
  ZCHECK_NOT_NULL("valid string");

  // This might fail but execution continues
  ZCHECK_EQ(2 + 2, 5);

  ZINFO("Check operations should continue after failures\n");
}

inline void test_conditional_logic() {
  ZINFO("=== Testing Conditional Logic ===");

  int x = 10;
  int y = 20;

  // Complex conditions
  ZTEST_S((x < y) && (y > 15), "Logical AND should work");
  ZTEST_S((x == 10) || (y == 30), "Logical OR should work");
  ZTEST_S(!(x == y), "Logical NOT should work");

  // Ternary operations
  ZTEST_S((x > 5) ? true : false, "Ternary operator should work");

  // Bitwise operations
  ZTEST_S((x & 1) == 0, "Bitwise AND should work");
  ZTEST_S((y | 1) == 21, "Bitwise OR should work");

  ZINFO("Conditional logic test completed\n");
}

inline void test_function_calls() {
  ZINFO("=== Testing Function Calls ===");

  auto add = [](int a, int b) { return a + b; };
  auto multiply = [](int a, int b) { return a * b; };

  ZTEST_S(add(2, 3) == 5, "Lambda addition should work");
  ZTEST_S(multiply(4, 5) == 20, "Lambda multiplication should work");

  // String functions
  auto get_length = [](const std::string &str) { return str.length(); };
  ZTEST_S(get_length("hello") == 5, "String length function should work");

  ZINFO("Function calls test completed\n");
}

inline void test_edge_cases() {
  ZINFO("=== Testing Edge Cases ===");

  // Zero and negative numbers
  ZTEST_EQ(0, 0);
  ZTEST_NE(-1, 1);
  ZTEST_S(-5 < 0, "Negative number comparison should work");

  // Empty strings
  std::string empty;
  ZTEST_S(empty.empty(), "Empty string should be empty");
  ZTEST_S(empty == "", "Empty string should equal empty literal");

  ZINFO("Edge cases test completed\n");
}

inline void test_real_world_scenario() {
  ZINFO("=== Testing Real World Scenario ===");

  // Simulate a user class
  struct User {
    int id;
    std::string name;
    bool active;

    User(int i, std::string n, bool a) : id(i), name(std::move(n)), active(a) {}

    bool is_valid() const { return id > 0 && !name.empty(); }
  };

  User valid_user(1, "John Doe", true);
  User invalid_user(-1, "", false);

  // Test user validation
  ZTEST_S(valid_user.is_valid(), "Valid user should pass validation");
  ZTEST_S(!invalid_user.is_valid(), "Invalid user should fail validation");

  // Test user properties
  ZTEST_S(valid_user.id == 1, "User ID should be correct");
  ZTEST_S(valid_user.name == "John Doe", "User name should be correct");
  ZTEST_S(valid_user.active, "User should be active");

  ZINFO("Real world scenario test completed\n");
}

inline void test_performance_simple() {
  ZINFO("=== Testing Performance (Simple) ===");

  // Test basic operations performance
  auto start = std::chrono::high_resolution_clock::now();

  // Perform some operations
  int sum = 0;
  // for (int i = 0; i < 1000; ++i) {
    // sum += i;
    // ZTEST_S(i >= 0, "Loop index should be non-negative"); // Fast assertion
  // }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);

  ZTEST_S(sum == 499500, "Sum should be correct");
  ZTEST_S(duration.count() < 1000000,
          "Operations should complete quickly"); // Less than 1 second

  ZINFO("Performance test completed in {} microseconds\n", duration.count());
}

// This function demonstrates ASSERT (will terminate in debug mode)
inline void test_assert_behavior() {
  ZINFO("=== Testing Assert Behavior ===");

  // These only run in debug mode
  ZASSERT_EQ(2 + 2, 4);
  ZASSERT_NE(5, 10);
  ZASSERT_NOT_NULL("valid");

  ZINFO("If you see this, all asserts passed (in debug mode)\n");
}

inline void demo_panic() {
  ZINFO("=== Demonstrating Panic (Comment out to run other tests) ===");
  ZPANIC("This is a panic situation!");
  ZINFO("Panic demonstration skipped (commented out)\n");
}

inline void demo_assert() {
  ZINFO("=== Demonstrating Assert (Comment out to run other tests) ===");
  ZASSERT_EQ(1, 2); // This will terminate the program in debug mode
  ZINFO("Assert demonstration skipped (commented out)\n");
}

inline void test_all() {
  ZINFO("Starting Comprehensive Test Framework Validation...\n");

  // Run all test suites
  test_basic_assertions();
  test_pointer_assertions();
  test_string_operations();
  test_container_operations();
  test_floating_point_operations();
  test_check_operations();
  test_conditional_logic();
  test_function_calls();
  test_edge_cases();
  test_real_world_scenario();
  test_performance_simple();
  test_assert_behavior();

  ZINFO("=== Test Framework Validation Complete ===");
  ZINFO("All test suites executed successfully!");
  ZINFO("Check the output above for any failed tests (marked with [FAIL]).");
}

} // namespace test
