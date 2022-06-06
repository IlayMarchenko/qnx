/*
 * Copyright (c) 2013-2017, NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA Corporation is strictly prohibited.
 */

#ifndef INCLUDED_NVCOMMON_H
#define INCLUDED_NVCOMMON_H

#if !defined(__ASSEMBLY__) && !defined(__LDINCLUDE__)
#ifndef QB_BL_BUILD
#include <flashtools_nverror.h>
#else
#include <nverror.h>
#endif
#include <stddef.h>

#ifndef QB_BL_BUILD
#include <unistd.h>
#endif
#endif

#if defined(__aarch64__)
#define NVCPU_IS_AARCH64 1
#else
#define NVCPU_IS_AARCH64 0
#endif

#define RSA_KEY_SIZE 256

#define CRYPTO_HASH_SIZE 16

#if NVCPU_IS_AARCH64
#define NVCPU_IS_64_BITS 1
#else
#define NVCPU_IS_64_BITS 0
#endif

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

#if !defined(__ASSEMBLY__) && !defined(__LDINCLUDE__)

#undef NvU64
#undef NvU32
#undef NvU16
#undef NvU8
#undef NvBool

typedef unsigned char      NvU8;
typedef unsigned short     NvU16;
typedef unsigned int       NvU32;
typedef unsigned long long NvU64;
typedef char               NvS8;
typedef signed short       NvS16;
typedef signed int         NvS32;
typedef signed long long   NvS64;
typedef NvU8               NvBool;

typedef float              NvF32;
typedef double             NvF64;


/// Pointer-sized signed and unsigned ints
#if NVCPU_IS_64_BITS
typedef NvU64 NvUPtr;
typedef NvS64 NvSPtr;
#else
typedef NvU32 NvUPtr;
typedef NvS32 NvSPtr;
#endif
#ifdef QB_BL_BUILD

typedef __builtin_va_list   va_list;
#ifndef va_start
#define va_start(v, l)				__builtin_va_start((v),(l))
#endif

#ifndef va_end
#define va_end						__builtin_va_end
#endif

#ifndef va_arg
#define va_arg						__builtin_va_arg
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef QB_INT_MAX
#define QB_INT_MAX (2147483647)
#endif

#endif

enum { NV_FALSE = 0, NV_TRUE = 1 };

#endif // !__ASSEMBLY__ || !__LDINCLUDE__

#define NV_INLINE __inline__
#define NV_FORCE_INLINE __attribute__((always_inline)) __inline__
#define NV_NAKED
#define NV_LIKELY(c)   __builtin_expect((c), 1)
#define NV_UNLIKELY(c) __builtin_expect((c), 0)
#define NV_ALIGN_SIZE(size, align) (((size) + (align - 1)) & (~((align) - 1)))
#define NV_ALIGN_DOWN(size, align) (((size)) & (~((align) - 1)))
#define NV_IS_ALIGNED(size, align) (((size) & ((align) - 1)) == 0)

#define NV_ALIGN(size) __attribute__((aligned(size)))

#define NV_WEAK __attribute__((weak))
#define NV_PACKED __attribute__((packed))
#define NV_UNUSED __attribute__((unused))

#define NV_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define NV_MAX(a, b) (((a) > (b)) ? (a) : (b))

/*
 * check if _val lies between (_start, _end)
 */
#define NV_IS_BETWEEN(_val, _start, _end) \
            ((((_val) >= (_start)) && ((_val) <= (_end))) ? (NV_TRUE) : (NV_FALSE))

/* return true if a region (addr, addr + size - 1) overlaps with region (start, end) */
#define NV_LIES_BETWEEN(addr, size, start, end) \
            (NV_IS_BETWEEN(addr, start, end)? NV_TRUE : \
            NV_IS_BETWEEN(((addr) + (size) - 1), start, end) ? NV_TRUE : \
            ((((addr) <= (start)) && ((addr + (size - 1)) >= (end))) ? (NV_TRUE) : (NV_FALSE)))

/** Macro for determining offset of element e in struct s */
#define NV_OFFSETOF(s, e)        ((NvUPtr)(void *)(&(((s*)0)->e)))

#define MB  (1024 * 1024)
#define KB  (1024)
#define MBLog2 (20)

#endif // INCLUDED_NVCOMMON_H
