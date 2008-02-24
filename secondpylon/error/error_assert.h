#ifndef SPERROR_ASSERT_H
#define SPERROR_ASSERT_H

#include <cassert>

namespace secondpylon {
namespace error {

}
}

#define SPERROR_ASSERT(x) assert(x)
#define SPERROR_UNREFERENCED(x) (x)

#endif // SPERROR_ASSERT_H
