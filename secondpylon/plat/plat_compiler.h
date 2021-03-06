// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_PLAT_PLAT_COMPILER_H_
#define SECONDPYLON_PLAT_PLAT_COMPILER_H_

#include <intrin.h>  // required for __debugbreak

namespace secondpylon {
}

// Strongly request the compiler inline the tagged function. Note there is no
// way to completely force the compiler to inline or error out. If this is
// critical, verify the disassembly.
#define SPPLAT_INLINE __forceinline

// Prevents the compiler from inlining this function. This can be useful when
// inlining causes large amounts of stack use or performance issues.
#define SPPLAT_NOINLINE __declspec(noinline)

// Specifies a variable is not aliased within this scope. This can enables the
// compiler to perform additional optimizations. For example, if a function
// takes two arguments of type float*, it is highly likely that every use of
// one of these variable will require rereading the value from memory, as the
// compiler typically don't know if the arrays overlap.
//
// Use caution when using this modifier, as it can easily cause bugs if used
// incorrectly (ie if there is aliasing within the scope)
#if _MSC_VER >= 1400
  #define SPPLAT_RESTRICT __restrict  // introduced in msvc 2005
#else
  #define SECONDPYLON_PLAT_PLAT_RESTRICT
#endif

// Prefetches the cache line at the passed in address. This can be used to
// avoid a cache miss when data access patterns are somewhat predictable.
// Hardware prefetching support is low level - the specific constraints of
// this method need to be better documented.
#define SECONDPYLON_PLAT_PLAT_PREFETCH(address)

// Immediate, unconditional hard break used to help with debugging. This is
// similar to asm { int 3 } for win32 programmers.
#define SPPLAT_BREAK() __debugbreak()

#endif  // SECONDPYLON_PLAT_PLAT_COMPILER_H_
