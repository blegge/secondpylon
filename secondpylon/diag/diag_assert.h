#ifndef SPDIAG_ASSERT_H
#define SPDIAG_ASSERT_H

#include <cassert>

namespace secondpylon {
namespace diag {

}
}

// Compile time assert, soon to be replaced by C++0x standard assert.
#define SPDIAG_CTASSERT(x)

#define SPDIAG_ASSERT(x) assert(x)

#define SPDIAG_ERROR() assert(0)

// Helper to invoke a crash in the case of a truly unrecoverable situation. A common use is forcing a crash to occur 
// early. This can be used to create a crash dump at a point with more information. For example, a NaN fed into a 
// physics system may cause a crash much later. Tracking the source back may be difficult. Asserts work on dev machines,
// but not if the bug only repros in the wild.
#define SPDIAG_FATAL(x) *(void*)0 = 0;

// This macro can be used to suppress unused variable warnings in cases where the variable can't be easily removed.
#define SPDIAG_UNREFERENCED(x) (x)

#endif // SPDIAG_ASSERT_H
