#pragma once

#include "./_common.hpp"

#include <mutex>
#include <iostream>
#include <string_view>

#if ENABLE_TIMESTAMP
#include <chrono>
#endif

#ifndef USING_CUSTOM

#define MIN_LOG_LVL_DEBUG      L_TRACE
#define MIN_LOG_LVL_RELEASE    L_INFO

#define TRACE_TAG    "[TRCE]"
#define DEBUG_TAG    "[DEBG]"
#define INFO_TAG     "[INFO]"
#define WARN_TAG     "[WARN]"
#define ERROR_TAG    "[ERRO]"
#define FATAL_TAG    "[FATL]"

#endif

namespace zutils::internal {

#ifdef NDEBUG
static constexpr LogLevel MIN_LOG_LEVEL = MIN_LOG_LVL_RELEASE;
#else
static constexpr LogLevel MIN_LOG_LEVEL = MIN_LOG_LVL_DEBUG;
#endif

static constexpr const char* LEVEL_STR[] {
  TRACE_TAG,
  DEBUG_TAG,
  INFO_TAG,
  WARN_TAG,
  ERROR_TAG,
  FATAL_TAG,
};

#if ENABLE_COLOR_CODE
static constexpr const char* COLOR_TABLE[] {
  "\033[90m",
  "\033[36m",
  "\033[32m",
  "\033[33m",
  "\033[31m",
  "\033[41m",
};
#endif

[[nodiscard]] static constexpr inline std::string_view openColor(LogLevel level) noexcept {
#if ENABLE_COLOR_CODE
  return COLOR_TABLE[level];
#else
  return "";
#endif
}

[[nodiscard]] static constexpr inline const char* closeColor() noexcept {
#if ENABLE_COLOR_CODE
  return "\033[0m : ";
#else
  return " : ";
#endif
}

struct LogGaurd {
  std::scoped_lock<std::mutex> lock;
  std::ostream&                os;
};

inline LogGaurd logStream(LogLevel level) {
  static std::mutex s_log_mutex {};
  return LogGaurd{
    .lock = std::scoped_lock {s_log_mutex},
    .os   = (level < L_WARN) ? std::cout : std::cerr,
  };
}

[[nodiscard]] static inline std::string_view getTimestamp() noexcept {
#if ENABLE_TIMESTAMP
  std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::tm tm_struct{};

  thread_local char buf[sizeof("[HH:MM:SS]")] {};

#ifdef _WIN32
  localtime_s(&tm_struct, &t);
#else
  localtime_r(&t, &tm_struct);
#endif

  std::strftime(buf, sizeof(buf), "[%H:%M:%S]", &tm_struct);
  return buf;
#else
  return "";
#endif
}

} // namespace zutils::internal

#if DISABLE_LOGGING

#define ZLOG(LVL) \
  if constexpr (false) std::cout

#else

#define ZLOG(LVL)                                        \
  if constexpr (LVL >= zutils::internal::MIN_LOG_LEVEL)  \
    zutils::internal::logStream(LVL).os                  \
      << "\n"                                            \
      << zutils::internal::openColor(LVL)                \
      << zutils::internal::getTimestamp()                \
      << zutils::internal::LEVEL_STR[LVL]                \
      << zutils::internal::closeColor()                  \

#endif

#define ZLOGT  ZLOG(L_TRACE)
#define ZLOGD  ZLOG(L_DEBUG)
#define ZLOGI  ZLOG(L_INFO)
#define ZLOGW  ZLOG(L_WARN)
#define ZLOGE  ZLOG(L_ERROR)
#define ZLOGF  ZLOG(L_FATAL)

#define ZLOG_V(VALUE) \
  ZLOGD << zutils::internal::ColorText {35, #VALUE} << " = " << (VALUE)

#define ZLOG_IF(LVL, CONDITION) \
  if (CONDITION) ZLOG(LVL)

#define ZLOGT_IF(CONDITION)  ZLOG_IF(L_TRACE, CONDITION)
#define ZLOGD_IF(CONDITION)  ZLOG_IF(L_DEBUG, CONDITION)
#define ZLOGI_IF(CONDITION)  ZLOG_IF(L_INFO , CONDITION)
#define ZLOGW_IF(CONDITION)  ZLOG_IF(L_WARN , CONDITION)
#define ZLOGE_IF(CONDITION)  ZLOG_IF(L_ERROR, CONDITION)
#define ZLOGF_IF(CONDITION)  ZLOG_IF(L_FATAL, CONDITION)

#define ZLOG_RAW \
  std::cout << "\n\033[0m"

#define ZTAB  TAB_TAG
