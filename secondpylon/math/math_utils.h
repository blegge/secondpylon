// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_MATH_MATH_UTILS_H_
#define SECONDPYLON_MATH_MATH_UTILS_H_

#include "secondpylon/plat/plat_compiler.h"
#include "secondpylon/plat/plat_types.h"
#include "secondpylon/diag/diag_assert.h"

namespace secondpylon {
namespace math {

class Utils {
public:
  static plat::float32 PI() { return 3.1415926535897931F; }

  static plat::float32 Sqrt(plat::float32 fSource);
  static plat::float32 Abs(plat::float32 x);
  static plat::float32 DegreeToRadian(plat::float32 degrees);
  static plat::float32 RadianToDegree(plat::float32 radians);
};

}  // namespace math
}  // namespace secondpylon

#include "secondpylon\math\math_utils-inl.h"

#endif  // SECONDPYLON_MATH_MATH_UTILS_H_
