#ifndef EGLCOMPILER_INCLUDED
#define EGLCOMPILER_INCLUDED


/**
 * Get standard integer types
 */
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
#  include <stdint.h>
#elif defined(_MSC_VER)
   typedef __int8             int8_t;
   typedef unsigned __int8    uint8_t;
   typedef __int16            int16_t;
   typedef unsigned __int16   uint16_t;
#  ifndef __eglplatform_h_
     typedef __int32            int32_t;
#  endif
   typedef unsigned __int32   uint32_t;
   typedef __int64            int64_t;
   typedef unsigned __int64   uint64_t;

#  if defined(_WIN64)
     typedef __int64            intptr_t;
     typedef unsigned __int64   uintptr_t;
#  else
     typedef __int32            intptr_t;
     typedef unsigned __int32   uintptr_t;
#  endif

#  define INT64_C(__val) __val##i64
#  define UINT64_C(__val) __val##ui64
#else
/* hope the best instead of adding a bunch of ifdef's */
#  include <stdint.h>
#endif


/**
 * Function inlining
 */
#if defined(__GNUC__)
#  define INLINE __inline__
#elif defined(__MSC__)
#  define INLINE __inline
#elif defined(_MSC_VER)
#  define INLINE __inline
#elif defined(__ICL)
#  define INLINE __inline
#elif defined(__INTEL_COMPILER)
#  define INLINE inline
#elif defined(__WATCOMC__) && (__WATCOMC__ >= 1100)
#  define INLINE __inline
#elif defined(__SUNPRO_C) && defined(__C99FEATURES__)
#  define INLINE inline
#  define __inline inline
#  define __inline__ inline
#elif (__STDC_VERSION__ >= 199901L) /* C99 */
#  define INLINE inline
#else
#  define INLINE
#endif


#endif /* EGLCOMPILER_INCLUDED */