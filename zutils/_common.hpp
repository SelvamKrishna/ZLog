#pragma once

#include <iostream>
#include <cstdint>

enum LogLevel : uint8_t {
  L_TRACE,
  L_DEBUG,
  L_INFO,
  L_WARN,
  L_ERROR,
  L_FATAL,
};

namespace zutils::internal {

struct ColorText {
  const int   ANSI_CODE;
  const char* TEXT;
};

inline std::ostream& operator<<(std::ostream& os, const ColorText& ct) {
#if ENABLE_COLOR_CODE
  return os << "\033[" << ct.ANSI_CODE << "m" << ct.TEXT << "\033[0m";
#else
  return os << ct.TEXT;
#endif
}

struct ResetTerminal {
  ResetTerminal() noexcept {
    std::atexit([] { std::cout << "\033[0m" << std::endl; });
  }
};

static ResetTerminal s_reset_terminal {};

[[noreturn]] static inline void killProcess() noexcept { std::abort(); }

}
