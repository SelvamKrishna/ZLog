#pragma once

#include <iostream>

namespace zutils {

struct ResetTerminal {
  ResetTerminal() noexcept
  {
    std::atexit([] { std::cout << "\033[0m" << std::endl; });
  }
};

static ResetTerminal s_reset_terminal {};

} // namespace zutils
