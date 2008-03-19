#ifndef SPERROR_ASSERT_H
#define SPERROR_ASSERT_H

#include <cassert>

namespace secondpylon {
namespace error {

}
}

// The argument msgscope provides varadic macro like support.
#define SPERROR_ASSERT(x, msgscope) assert(x)
#define SPERROR_UNREFERENCED(x) (x)

// Static asserst don't have any overhead. SP_STATICASSERT attempts to create one of the two StaticAssertFailed types
// depending on the passed in value. Only a specialization of true will compile successfully - false will result in a
// compile time failure.
//
// c++0x has a built in static assert. Replace this assert with it in the future. This implementation doesn't produce
// the most descriptive error messages, but it is simpler/produces fewer symbols than more complex versions.
template <bool> struct StaticAssertFailed;
template <> struct StaticAssertFailed<true>{};
#define SPERROR_CTASSERT(x) StaticAssertFailed<x>();

#endif // SPERROR_ASSERT_H
