#pragma once

#include "./_log.hpp"

#ifdef NDEBUG

#define ZTODO(MSG)    {}
#define ZUNREACHABLE  {}

#else

#define ZTODO(MSG) do {                           \
  ZLOGW                                           \
    << zutils::internal::ColorText{33, TODO_TAG}  \
    << " : " MSG " : (" << __FILE__               \
    << ") @ " << __FUNCTION__                     \
    << "() : " << __LINE__ << "\n";               \
  zutils::internal::killProcess();                \
} while(0)

#define ZUNREACHABLE do {                                \
  ZLOGF                                                  \
    << zutils::internal::ColorText{41, UNREACHABLE_TAG}  \
    << " : (" << __FILE__                                \
    << ") @ " << __FUNCTION__                            \
    << "() : " << __LINE__ << "\n";                      \
  zutils::internal::killProcess();                       \
} while(0)

#endif
