#ifndef __FUCK_AUTOTOOLS
#define __FUCK_AUTOTOOLS

#define __FUCK_AUTOTOOLS_STR(a)  #a
#define __FUCK_AUTOTOOLS_XSTR(a) __FUCK_AUTOTOOLS_STR(a)

#include __FUCK_AUTOTOOLS_XSTR(__FUCK_AUTOTOOLS_REAL_CONFIG_H)

#endif