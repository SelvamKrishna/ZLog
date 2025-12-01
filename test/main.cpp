// #include "test/t_log.hpp"   // IWYU pragma: keep
// #include "test/t_trace.hpp" // IWYU pragma: keep
// #include "test/t_test.hpp" // IWYU pragma: keep

#include "zutils/tools.hpp"

int main() {
  /// test::test_all();
  ZTODO("Example {}", "Error (404)");
  ZDEPRECATED("Example {}", "Error (404)");
  ZOPTIMIZE("Example {}", "Error (404)");
  ZSECURITY("Example {}", "Error (404)");
  ZPERFORMANCE("Example {}", "Error (404)");
}
