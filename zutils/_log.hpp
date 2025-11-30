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

namespace zutils {

namespace internal {

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

static std::ostream s_null_stream {nullptr};

[[nodiscard]]
static inline constexpr std::string_view openColor(LogLevel level) noexcept
{
#if ENABLE_COLOR_CODE
  return COLOR_TABLE[level];
#else
  return "";
#endif
}

[[nodiscard]]
static inline constexpr const char* closeColor() noexcept
{
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

inline LogGaurd logStream(LogLevel level)
{
  static std::mutex s_log_mutex {};

  return LogGaurd {
    .lock = std::scoped_lock {s_log_mutex},
    .os   = (level < L_WARN) ? std::cout : std::cerr,
  };
}

[[nodiscard]] static inline std::string_view getTimestamp() noexcept
{
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

} // namespace internal

[[nodiscard]]
static inline constexpr std::ostream& log(LogLevel lvl) {
#if DISABLE_LOGGING
  return internal::s_null_stream;
#else
  return (lvl >= internal::MIN_LOG_LEVEL)
  ? internal::logStream(lvl).os
    << "\n"
    << internal::openColor(lvl) << internal::getTimestamp()
    << internal::LEVEL_STR[lvl] << internal::closeColor()
  : internal::s_null_stream;
#endif
}

[[nodiscard]] static inline constexpr std::ostream& trace() { return log(L_TRACE); }
[[nodiscard]] static inline constexpr std::ostream& debug() { return log(L_DEBUG); }
[[nodiscard]] static inline constexpr std::ostream& info () { return log(L_INFO) ; }
[[nodiscard]] static inline constexpr std::ostream& warn () { return log(L_WARN) ; }
[[nodiscard]] static inline constexpr std::ostream& error() { return log(L_ERROR); }
[[nodiscard]] static inline constexpr std::ostream& fatal() { return log(L_FATAL); }

[[nodiscard]]
static inline constexpr std::ostream& logIf(LogLevel lvl, bool condition) {
if (!condition) return internal::s_null_stream;

#if DISABLE_LOGGING
  return internal::s_null_stream;
#else
  return (lvl >= internal::MIN_LOG_LEVEL)
  ? internal::logStream(lvl).os
    << "\n"
    << internal::openColor(lvl) << internal::getTimestamp()
    << internal::LEVEL_STR[lvl] << internal::closeColor()
  : internal::s_null_stream;
#endif
}

[[nodiscard]] static inline constexpr std::ostream& traceIf(bool condition) { return logIf(L_TRACE, condition); }
[[nodiscard]] static inline constexpr std::ostream& debugIf(bool condition) { return logIf(L_DEBUG, condition); }
[[nodiscard]] static inline constexpr std::ostream& infoIf (bool condition) { return logIf(L_INFO , condition); }
[[nodiscard]] static inline constexpr std::ostream& warnIf (bool condition) { return logIf(L_WARN , condition); }
[[nodiscard]] static inline constexpr std::ostream& errorIf(bool condition) { return logIf(L_ERROR, condition); }
[[nodiscard]] static inline constexpr std::ostream& fatalIf(bool condition) { return logIf(L_FATAL, condition); }

} // namespace zutils

#define ZLOGT  zutils::log(L_TRACE)
#define ZLOGD  zutils::log(L_DEBUG)
#define ZLOGI  zutils::log(L_INFO)
#define ZLOGW  zutils::log(L_WARN)
#define ZLOGE  zutils::log(L_ERROR)
#define ZLOGF  zutils::log(L_FATAL)

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
