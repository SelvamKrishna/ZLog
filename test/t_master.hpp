#include "zutils/test.hpp"
#include <algorithm>
#include <cmath>
#include <memory>
#include <string>
#include <vector>
#include <array>

namespace test_suite {

// ==================== Basic Unit Tests ====================

inline void test_basic_types() {
  std::cout << "\n=== Testing Basic Types ===" << std::endl;

  ZTEST(true == true);
  ZTEST(false == false);
  ZTEST('A' == 65);
  ZTEST(100 == 100);
  ZTEST(3.14 > 3.0);

  ZTEST_S(sizeof(int) >= 4, "int should be at least 4 bytes");
  ZTEST_S(sizeof(char) == 1, "char should be 1 byte");
}

inline void test_containers() {
  std::cout << "\n=== Testing Containers ===" << std::endl;

  std::vector<int> vec = {1, 2, 3, 4, 5};
  std::array<int, 3> arr = {10, 20, 30};
  std::string str = "Hello";

  ZTEST_EQ(vec.size(), 5);
  ZTEST_EQ(arr.size(), 3);
  ZTEST_EQ(str.length(), 5);

  ZEXPECT(!vec.empty());
  ZEXPECT(!arr.empty());
  ZEXPECT(!str.empty());

  ZTEST_EQ(vec[0], 1);
  ZTEST_EQ(arr[2], 30);
  ZTEST_EQ(str[0], 'H');
}

// ==================== Smart Pointers ====================

inline void test_smart_pointers() {
  std::cout << "\n=== Testing Smart Pointers ===" << std::endl;

  auto ptr = std::make_unique<int>(42);
  auto shared = std::make_shared<std::string>("shared");

  ZASSERT(ptr != nullptr);
  ZASSERT(shared != nullptr);
  ZTEST_EQ(*ptr, 42);
  ZTEST_EQ(*shared, "shared");

  // Move semantics
  auto moved = std::move(ptr);
  ZTEST(moved != nullptr);
  ZEXPECT(ptr == nullptr);

  ZTEST_EQ(*moved, 42);
}

// ==================== Algorithms ====================

inline void test_algorithms() {
  std::cout << "\n=== Testing Algorithms ===" << std::endl;

  std::vector<int> numbers = {5, 2, 8, 1, 9, 3};
  std::vector<int> sorted = {1, 2, 3, 5, 8, 9};

  // Sort and verify
  std::sort(numbers.begin(), numbers.end());
  ZTEST(std::is_sorted(numbers.begin(), numbers.end()));
  ZTEST_EQ(numbers, sorted);

  // Find elements
  auto it = std::find(numbers.begin(), numbers.end(), 5);
  ZTEST(it != numbers.end());
  ZTEST_EQ(*it, 5);

  // Count
  int count = std::count(numbers.begin(), numbers.end(), 3);
  ZTEST_EQ(count, 1);

  // Transform
  std::vector<int> doubled(numbers.size());
  std::transform(numbers.begin(), numbers.end(), doubled.begin(),
                 [](int x) { return x * 2; });

  ZEXPECT_EQ(doubled[0], 2);
  ZEXPECT_EQ(doubled.back(), 18);
}

// ==================== Math Operations ====================

inline void test_math_operations() {
  std::cout << "\n=== Testing Math Operations ===" << std::endl;

  ZTEST_EQ(std::abs(-5), 5);
  ZTEST_EQ(std::pow(2, 3), 8);
  ZTEST_EQ(std::sqrt(16), 4);
  ZTEST_EQ(std::max(10, 20), 20);
  ZTEST_EQ(std::min(10, 20), 10);

  // Floating point precision
  double pi = 3.141592653589793;
  ZEXPECT(std::abs(pi - 3.14159) < 0.00001);

  // Trigonometric functions
  ZTEST_EQ(std::sin(0), 0);
  ZTEST_EQ(std::cos(0), 1);
}

// ==================== String Operations ====================

inline void test_string_advanced() {
  std::cout << "\n=== Testing Advanced String Operations ===" << std::endl;

  std::string text = "The quick brown fox jumps over the lazy dog";

  ZTEST_EQ(text.find("fox"), 16);
  ZTEST_EQ(text.find("cat"), std::string::npos);

  // Substring
  std::string sub = text.substr(16, 3);
  ZTEST_EQ(sub, "fox");

  // Replace
  std::string replaced = text;
  replaced.replace(16, 3, "wolf");
  ZTEST_EQ(replaced.find("wolf"), 16);

  // Case conversion
  std::string upper = text;
  std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
  ZEXPECT(upper.find("THE") != std::string::npos);

  // Split simulation
  size_t space_count = std::count(text.begin(), text.end(), ' ');
  ZTEST_EQ(space_count, 8);
}

// ==================== File System ====================

inline void test_filesystem_simulation() {
  std::cout << "\n=== Testing File System Simulation ===" << std::endl;

  struct FileInfo {
    std::string name;
    size_t size;
    bool is_directory;
  };

  std::vector<FileInfo> files = {{"document.txt", 1024, false},
                                 {"image.jpg", 2048576, false},
                                 {"src", 0, true},
                                 {"README.md", 512, false}};

  ZTEST_EQ(files.size(), 4);
  ZTEST(files[0].name == "document.txt");
  ZTEST(files[2].is_directory);
  ZEXPECT(files[1].size > 0);

  // Find directories
  auto dir_count =
      std::count_if(files.begin(), files.end(),
                    [](const FileInfo &f) { return f.is_directory; });
  ZTEST_EQ(dir_count, 1);

  // Total size
  size_t total_size = 0;
  for (const auto &file : files) {
    total_size += file.size;
  }
  ZTEST_EQ(total_size, 1024 + 2048576 + 512);
}

// ==================== Network Simulation ====================

inline void test_network_simulation() {
  std::cout << "\n=== Testing Network Simulation ===" << std::endl;

  struct Packet {
    int id;
    std::string source;
    std::string destination;
    size_t size;
    bool delivered;
  };

  std::vector<Packet> packets = {{1, "192.168.1.1", "192.168.1.2", 1500, true},
                                 {2, "192.168.1.1", "192.168.1.3", 1024, false},
                                 {3, "192.168.1.2", "192.168.1.1", 512, true}};

  ZTEST_EQ(packets.size(), 3);
  ZTEST(packets[0].delivered);
  ZEXPECT(!packets[1].delivered);

  // Statistics
  int delivered_count =
      std::count_if(packets.begin(), packets.end(),
                    [](const Packet &p) { return p.delivered; });
  ZTEST_EQ(delivered_count, 2);

  // Total data
  size_t total_data = 0;
  for (const auto &packet : packets) {
    total_data += packet.size;
  }
  ZTEST_EQ(total_data, 1500 + 1024 + 512);
}

// ==================== Database Simulation ====================

inline void test_database_simulation() {
  std::cout << "\n=== Testing Database Simulation ===" << std::endl;

  class UserRecord {
  public:
    int id;
    std::string username;
    std::string email;
    int age;

    UserRecord(int i, std::string u, std::string e, int a)
        : id(i), username(std::move(u)), email(std::move(e)), age(a) {}
  };

  std::vector<UserRecord> users = {{1, "alice", "alice@example.com", 25},
                                   {2, "bob", "bob@example.com", 30},
                                   {3, "charlie", "charlie@example.com", 22}};

  ZTEST_EQ(users.size(), 3);
  ZTEST(users[0].username == "alice");
  ZEXPECT(users[1].age > 18);

  // Find user by ID
  auto it = std::find_if(users.begin(), users.end(),
                         [](const UserRecord &u) { return u.id == 2; });
  ZASSERT(it != users.end());
  ZTEST_EQ(it->username, "bob");

  // Average age
  double total_age = 0;
  for (const auto &user : users) {
    total_age += user.age;
  }
  double average_age = total_age / users.size();
  ZEXPECT(average_age > 20 && average_age < 30);
}

// ==================== Performance Validation ====================

inline void test_performance_validation() {
  std::cout << "\n=== Testing Performance Validation ===" << std::endl;

  const size_t ELEMENT_COUNT = 10000;
  std::vector<int> data(ELEMENT_COUNT);

  // Fill with sequential values
  for (size_t i = 0; i < ELEMENT_COUNT; ++i) {
    data[i] = static_cast<int>(i);
  }

  ZTEST_EQ(data.size(), ELEMENT_COUNT);
  ZTEST_EQ(data[0], 0);
  ZTEST_EQ(data.back(), ELEMENT_COUNT - 1);

  // Verify all values
  for (size_t i = 0; i < ELEMENT_COUNT; ++i) {
    ZEXPECT_EQ(data[i], static_cast<int>(i));
  }

  std::cout << "Validated " << ELEMENT_COUNT << " elements" << std::endl;
}

// ==================== Security Validation ====================

inline void test_security_validation() {
  std::cout << "\n=== Testing Security Validation ===" << std::endl;

  // Password strength simulation
  auto is_strong_password = [](const std::string &password) -> bool {
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    bool has_special = false;

    for (char c : password) {
      if (std::isupper(c))
        has_upper = true;
      if (std::islower(c))
        has_lower = true;
      if (std::isdigit(c))
        has_digit = true;
      if (!std::isalnum(c))
        has_special = true;
    }

    return password.length() >= 8 && has_upper && has_lower && has_digit &&
           has_special;
  };

  ZTEST(is_strong_password("StrongP@ss1"));
  ZTEST(!is_strong_password("weak"));
  ZTEST(!is_strong_password("NoSpecial1"));
  ZTEST(!is_strong_password("nouppercase1!"));

  // Input validation
  auto validate_email = [](const std::string &email) -> bool {
    return email.find('@') != std::string::npos &&
           email.find('.') != std::string::npos && email.length() > 5;
  };

  ZTEST(validate_email("user@example.com"));
  ZTEST(!validate_email("invalid"));
  ZTEST(!validate_email("user@com"));
}

// ==================== Main Test Runner ====================

inline void run_all_tests() {
  std::cout << "==========================================" << std::endl;
  std::cout << "   ZUtils Comprehensive Test Suite" << std::endl;
  std::cout << "==========================================" << std::endl;

  try {
    test_basic_types();
    test_containers();
    test_smart_pointers();
    test_algorithms();
    test_math_operations();
    test_string_advanced();
    test_filesystem_simulation();
    test_network_simulation();
    test_database_simulation();
    test_performance_validation();
    test_security_validation();

    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "🎉 ALL TESTS PASSED SUCCESSFULLY!" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

  } catch (const std::exception &e) {
    std::cerr << "\n❌ TEST SUITE FAILED: " << e.what() << std::endl;
    std::exit(1);
  }
}

} // namespace test
