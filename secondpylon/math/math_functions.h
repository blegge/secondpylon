#ifndef SPMATH_FUNCTIONS_H
#define SPMATH_FUNCTIONS_H

#include <secondpylon/plat/plat_types.h>
#include <secondpylon/diag/error_assert.h>
#include <cmath>

namespace secondpylon {
namespace math {

struct Functions
{
    static plat::float32 Sqrt(plat::float32 fSource)
    {
        SPERROR_ASSERT(fSource >= 0.0f);
        return sqrtf(fSource);
    }
};

}
}

#endif // SPMATH_FUNCTIONS_H
