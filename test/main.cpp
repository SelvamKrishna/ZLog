#include "zutils/log.hpp"

namespace test {

void log()
{
  // Basic usage examples
  ZDBG("Debug message: x = {}", 42);
  ZINFO("Info message about {}", "initialization");
  ZWARN("Warning: value {} is nearing limit", 99);
  ZERR("Error: could not open file '{}'", "config.txt");
  ZFATAL("Fatal error: {} failed unexpectedly", "system call");

  // Conditional logging
  bool condition = true;
  ZINFO_IF(condition, "Conditional log triggered: {}", condition);
  ZWARN_IF(!condition, "This will not be shown");

  // Variable dump helper
  int value = 123;
  ZVAR(value);
}

} // namespace test

int main()
{
  return 0;
}
