#include "zutils/_log.hpp"

//-----------------------------------------------------
// Entry point
//-----------------------------------------------------
int main() {
  ZDBG("Hwllo {}", 1);
  ZDBG_IF(true, "Bye1");
  ZDBG_IF(false, "Bye2");
  ZDBG_EXPR(1 == 1);

  return 0;
}
