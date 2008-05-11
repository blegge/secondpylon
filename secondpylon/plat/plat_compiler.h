#ifndef SPPLAT_COMPILER_H
#define SPPLAT_COMPILER_H

// Strongly request the compiler inline the tagged function. Note there is no way to completely force the compiler to
// inline or error out. If this is critical, verify the disassembly.
#define SPPLAT_INLINE __forceinline

// Prevents the compiler from inlining this function. This can be useful when inlining causes large amounts of stack
// use or performance issues.
#define SPPLAT_NOINLINE __declspec(noinline)

// Specifies a variable is not aliased within this scope. This can enables the compiler to perform additional
// optimizations. For example, if a function takes two arguments of type float*, it is highly likely that every use of
// one of these variable will require rereading the value from memory, as the compiler typically don't know if the
// arrays overlap.
//
// Use caution when using this modifier, as it can easily cause bugs if used incorrectly (ie if there is aliasing within
// the scope)
#if _MSC_VER >= 1400
    #define SPPLAT_RESTRICT __restrict // introduced in msvc 2005
#else
    #define SPPLAT_RESTRICT
#endif

// Prefetches the cache line at the passed in address. This can be used to avoid a cache miss when data access patterns
// are somewhat predictable. Hardware prefetching support is low level - the specific constraints of this method need
// to be better documented.
#define SPPLAT_PREFETCH(address)

// This is macro serves two purposes:
//
// 1)  Describe a class as uncopyable for documentation purposes.
// 2)  Suppress 'copy constructor could not be generated' and 'assignment operator could not be generated' errors.
//
// The initial implementation was a trait base class. This didn't work cleanly when we had multiple classes in a
// hierarchy that needed to be uncopyable as this generates errors about deriving multiple times from a class.
//
// @todo This is a really belongs in a 'common' library as it shouldn't need to vary compiler to compiler. We haven't  
// standardized what what the common lib will be yet.
#define SPPLAT_UNCOPYABLE(ClassName) \
    private: \
        ClassName(ClassName&); \
        ClassName& operator=(ClassName&)

#endif // SPPLAT_COMPILER_H
