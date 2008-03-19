#ifndef SPMATH_FUNCTIONS_H
#define SPMATH_FUNCTIONS_H

#include <secondpylon/plat/plat_compiler.h>
#include <secondpylon/plat/plat_types.h>
#include <secondpylon/diag/diag_assert.h>
#include <cmath>

namespace secondpylon {
namespace math {

struct Functions
{
    static plat::float32 PI() { return 3.1415926535897931F; }

    static plat::float32 Sqrt(plat::float32 fSource);
    static plat::float32 Abs(plat::float32 x);
    static plat::float32 DegreeToRadian(plat::float32  degrees);
    static plat::float32 RadianToDegree(plat::float32  radians);
};

}
}

#endif // SPMATH_FUNCTIONS_H
