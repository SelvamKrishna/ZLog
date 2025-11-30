#include "test/logging.hpp"

//-----------------------------------------------------
// Entry point
//-----------------------------------------------------
int main() {

  test::logging_basic();
  test::logging_args();
  test::logging_cond();
  test::logging_vars();
  test::logging_vars_complex();
  test::logging_class();
  test::logging_edge_cases();

  return 0;
}
