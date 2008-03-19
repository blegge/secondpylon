#ifndef SPPLAT_COMPILER_H
#define SPPLAT_COMPILER_H

// Provide internal compiler defines for consistency.
// @todo This is a stub for consistency before the the real interface is built.

#define SPPLAT_INLINE inline
#define SPPLAT_NOINLINE
#define SPPLAT_RESTRICT

// Prefetches the cache line at the passed in address. This can be used to avoid a cache miss when data access patterns
// are somewhat predictable. Hardware prefetching support is low level - the specific constraints of this method need
// to be better documented.
#define SPPLAT_PREFETCH(address)

#endif // SPPLAT_COMPILER_H
