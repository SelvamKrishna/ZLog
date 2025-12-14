#pragma once

/*

. modify `zlog_v2/config.hpp` for customization

=== ZLOG -> C++ 23 LOGGING LIBRARY ===

--- Featrues ---

- Color coded terminal output
- Timestamped messages
- Code control flow tracing
- Unit testing tools
- Assertion tools
- Pre-defined error templates:

--- Details ---

version: 2.0
date:    14.12.2025
author:  SelvamKrishna
link:    https://www.github.com/SelvamKrishna

--- What's new ---

. FEAT: zlog::internal::ProString

A class which takes regular texts and std::format_string and converts them to std::string,
Due to its implicit cconstruction and conversion there is no need for mulitple function definitions,

. FIX: unwanted zlog::config::TAG_TAG before Timestamp even when zlog::config::ENABLE_TIMESTAMP is false

. FEAT: Testing macros to integrate `zlog::internal::ProString`

. REFACTOR: removed _EQ, _NE & _S

Macros in `zlog/test.hpp` now directly uses `zlog::internal::ProString`,
This provides built in support over formatted, un-formatted and un-provided description

*/

#include "./zlog/log.hpp"   // IWYU pragma: keep
#include "./zlog/test.hpp"  // IWYU pragma: keep
#include "./zlog/tools.hpp" // IWYU pragma: keep
#include "./zlog/trace.hpp" // IWYU pragma: keep
