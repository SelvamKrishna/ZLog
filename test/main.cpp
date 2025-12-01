#include "test/t_log.hpp"   // IWYU pragma: keep
#include "test/t_trace.hpp" // IWYU pragma: keep
#include "test/t_test.hpp" // IWYU pragma: keep

#include "zutils/tools.hpp"

#include <iostream>
#include <vector>

namespace demo {

// ==================== TODO EXAMPLES ====================

void process_data(std::vector<int> &data) {
  ZTODO("Implement data validation");
  ZTODO("Add error handling for empty vectors");

  if (data.empty()) {
    ZTODO("Handle empty vector case");
    return;
  }

  // Process data
  for (auto &item : data) {
    item *= 2;
  }
}

class UserManager {
public:
  void add_user(const std::string &name) {
    ZTODO("Validate user name format");
    ZTODO("Check for duplicate users");

    users_.push_back(name);
  }

  void remove_user(const std::string &name) {
    ZTODO("Implement user removal logic");
    ZUNIMPLEMENTED("User removal not yet implemented");
  }

private:
  std::vector<std::string> users_;
};

// ==================== UNREACHABLE EXAMPLES ====================

enum class State { Idle, Running, Paused, Stopped };

std::string state_to_string(State state) {
  switch (state) {
  case State::Idle:
    return "Idle";
  case State::Running:
    return "Running";
  case State::Paused:
    return "Paused";
  case State::Stopped:
    return "Stopped";
  default:
    ZUNREACHABLE("Invalid state enum value: {}");
  }
}

int safe_divide(int a, int b) {
  if (b == 0) {
    ZUNREACHABLE("Division by zero should have been caught earlier");
  }
  return a / b;
}

// ==================== DEPRECATED EXAMPLES ====================

[[deprecated("Use new_calculate() instead")]]
int old_calculate(int x, int y) {
  ZDEPRECATED("old_calculate is deprecated, use new_calculate");
  return x + y * 2; // Old algorithm
}

int new_calculate(int x, int y) {
  return (x + y) * 2; // New algorithm
}

// ==================== FIXME EXAMPLES ====================

void process_file(const std::string &filename) {
  // FIXME: This doesn't handle file locking
  ZFIXME("Add file locking to prevent concurrent access");

  // FIXME: Memory leak if exception is thrown
  ZFIXME("Use RAII or smart pointers for resource management");

  // Current implementation
  std::cout << "Processing: " << filename << std::endl;
}

// ==================== PERFORMANCE & OPTIMIZATION ====================

void slow_function(const std::vector<int> &data) {
  ZPERFORMANCE("This function uses O(n²) algorithm");
  ZOPTIMIZE("Consider using hash map for O(1) lookups");

  // Inefficient algorithm
  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = 0; j < data.size(); ++j) {
      if (data[i] == data[j]) {
        // Found duplicate
      }
    }
  }
}

// ==================== MEMORY & THREAD SAFETY ====================

class UnsafeBuffer {
public:
  UnsafeBuffer(size_t size) : data_(new int[size]), size_(size) {
    ZMEMORY("Potential memory leak - no destructor");
    ZTHREAD_SAFETY("Not thread-safe for concurrent access");
  }

  // Missing destructor - would leak memory
  // Missing copy constructor/assignment - would double free

private:
  int *data_;
  size_t size_;
};

// ==================== SECURITY EXAMPLES ====================

void handle_user_input(const std::string &input) {
  ZSECURITY("Input not sanitized for SQL injection");
  ZSECURITY("No rate limiting implemented");

  // Direct concatenation - SQL injection vulnerability
  std::string query = "SELECT * FROM users WHERE name = '" + input + "'";

  // No input validation
  std::cout << "Query: " << query << std::endl;
}

// ==================== COMPREHENSIVE DEMO ====================

void run_all_demos() {
  std::cout << "🚀 DEVELOPMENT MACROS DEMONSTRATION\n";
  std::cout << "====================================\n\n";

  std::cout << "1. TODO Macros:\n";
  std::cout << "----------------\n";
  std::vector<int> data = {1, 2, 3};
  process_data(data);

  UserManager manager;
  manager.add_user("Alice");
  // manager.remove_user("Bob");  // Would show UNIMPLEMENTED

  std::cout << "\n2. UNREACHABLE Macros:\n";
  std::cout << "----------------------\n";
  std::cout << "State: " << state_to_string(State::Running) << std::endl;
  // Uncomment to test unreachable:
  // std::cout << state_to_string(static_cast<State>(999)) << std::endl;

  std::cout << "\n3. DEPRECATED Macros:\n";
  std::cout << "---------------------\n";
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
  std::cout << "Old calc: " << old_calculate(5, 3) << std::endl;
#pragma GCC diagnostic pop
  std::cout << "New calc: " << new_calculate(5, 3) << std::endl;

  std::cout << "\n4. FIXME Macros:\n";
  std::cout << "----------------\n";
  process_file("test.txt");

  std::cout << "\n5. Performance/Resource Macros:\n";
  std::cout << "--------------------------------\n";
  slow_function(data);

  std::cout << "\n6. Security Macros:\n";
  std::cout << "-------------------\n";
  handle_user_input("test' OR '1'='1");

  std::cout << "\n" << std::string(50, '=') << std::endl;
  std::cout << "✅ All development macros demonstrated!\n";
  std::cout << std::string(50, '=') << std::endl;

  std::cout << "\n📋 Summary of Development Macros:\n";
  std::cout << "=================================\n";
  std::cout << "ZTODO(...)        - Mark incomplete code (Warning)\n";
  std::cout << "ZUNREACHABLE(...) - Mark unreachable code (Fatal)\n";
  std::cout << "ZUNIMPLEMENTED(...)- Not implemented features (Error)\n";
  std::cout << "ZDEPRECATED(...)  - Deprecated functionality (Warning)\n";
  std::cout << "ZFIXME(...)       - Bugs needing fix (Error)\n";
  std::cout << "ZOPTIMIZE(...)    - Optimization opportunities (Debug)\n";
  std::cout << "ZSECURITY(...)    - Security concerns (Warning)\n";
  std::cout << "ZPERFORMANCE(...) - Performance issues (Warning)\n";
  std::cout << "ZMEMORY(...)      - Memory issues (Error)\n";
  std::cout << "ZTHREAD_SAFETY(...)- Thread safety issues (Error)\n";
}

} // namespace demo

int main() {
    // Enable colors on Windows
    #ifdef _WIN32
        system("color");
    #endif

    try {
        demo::run_all_demos();
        return 0;
    } catch (...) {
        std::cerr << "\n❌ Demo interrupted by fatal error\n";
        return 1;
    }
}
