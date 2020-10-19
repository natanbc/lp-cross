#ifndef __FUCK_AUTOTOOLS_MPG123_H
#define __FUCK_AUTOTOOLS_MPG123_H

#include <tchar.h>
#include <stdlib.h>
#include <sys/types.h>

// Needed for Visual Studio versions before VS 2010.
#if (_MSC_VER < 1600)
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
#define PRIiMAX "I64i"
typedef __int64 intmax_t;
#else
#include <stdint.h>
#include <inttypes.h>
#endif


#define MPG123_NO_CONFIGURE
#include "mpg123.h.in"

#endif