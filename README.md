# ZUtils (*v2*): A Modern C++ Utility Library

A lightweight, header-only C++ utility library providing logging, testing, tracing, and debugging tools with zero dependencies.

Customizable via `zutils/config.hpp` for flexible integration into various projects.

|Overview|Features|
|---|---|
|[Logging System](#logging-system-zutilsloghpp)|Thread-safe logging with multiple log levels, ANSI color support, timestamp formatting, conditional logging macros, variable debugging, and default logging.|
|[Testing Framework](#testing-framework-zutilstesthpp)|Multi-level assertions, automatic expression stringification, comparison macros, custom descriptions, and panic handling.|
|[Development Tools](#more-development-tools-zutilstoolshpp)|Caution and critical macros for marking code sections with specific intentions.|
|[Tracing System](#tracing-system-zutilstracehpp)|Tracing macros for function entry and exit, customizable via `zutils/config.hpp`.|

## Logging System `zutils/log.hpp`

- **Thread-safe logging** with mutex protection
- **Six log levels**:
  - `ZDBG`: For debugging messages
  - `ZINFO`: For informational messages
  - `ZWARN`: For warnings
  - `ZERR`: For error reporting
  - `ZFATAL`: For fatal errors

- **ANSI color support** further configurable via `zutils/config.hpp`
- **Timestamp formatting** togglable via `zutils::config::ENABLE_TIMESTAMP`
- **Conditional logging macros** with *prefix* `_IF`
- **Variable debugging** with `ZVAR` macro
- **Default logging** with `ZOUT` macro

## Testing Framework `zutils/test.hpp`

- **Multi-level assertions**:
  - `ZTEST`: For general unit tests
  - `ZEXPECT`: For expected conditions (non-fatal warnings)
  - `ZASSERT`: For critical assertions (fatal errors, only in debug builds)
  - `ZVERIFY`: For verifications (always active, fatal errors)

- **Automatic expression stringification**
- **Custom description** with *prefix* `_S`
- **Panic handling** with `ZPANIC` macro and `ZPANIC_IF` for conditional panics

## More Development Tools `zutils/tools.hpp`

- **Caution macro**: Warns about potentially dangerous code sections
  - `ZTODO`: Marks unfinished code sections
  - `ZDEPRECATED`: Marks deprecated code sections
  - `ZOPTIMIZE`: Marks code sections for optimization
  - `ZSECURITY`: Marks security-related code sections
  - `ZPERFORMANCE`: Marks performance-related code sections

- **Critical macro**: Highlights critical code sections and aborts execution
  - `ZUNREACHABLE`: Marks code sections that should never be reached
  - `ZUNIMPLEMENTED`: Marks unimplemented code sections
  - `ZFIXME`: Marks code sections that need fixing
  - `ZMEMORY`: Marks code sections related to memory management
  - `ZTHREAD_SAFETY`: Marks code sections related to thread safety

## Tracing System `zutils/trace.hpp`

- **Tracing macros** for function entry and exit
  - `ZTRC`: Marks function entry and exit points
  - `ZTRC_C`: Marks function entry and exit with class context
  - `ZTRC_S`: Marks function entry and exit with a custom description
