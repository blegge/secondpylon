// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_MATH_MATH_UTILS_INL_H_
#define SECONDPYLON_MATH_MATH_UTILS_INL_H_

#include <cmath>

namespace secondpylon {
namespace math {

SPPLAT_INLINE plat::float32 Utils::Sqrt(plat::float32 source) {
    SPDIAG_ASSERT(source >= 0.0f,
        "Values passed to Srt must be zero or positive.");
    return sqrtf(source);
}

SPPLAT_INLINE plat::float32 Utils::Abs(plat::float32 source) {
    return fabsf(source);
}

SPPLAT_INLINE plat::float32 Utils::DegreeToRadian(plat::float32 degrees) {
    SPDIAG_ASSERT(Utils::Abs(degrees) <= 360.0f,
        "Values passed to DegreeToRadian must be "
        "in the range [-360, 360] to avoid percision problems.");
    return ((degrees * static_cast<plat::float32>(Utils::PI())) / 180.0F);
}

SPPLAT_INLINE plat::float32 Utils::RadianToDegree(plat::float32 radians) {
    SPDIAG_ASSERT(Utils::Abs(radians) <= Utils::PI()*2.0f,
        "Values passed to RadianToDegree must be in the range [-2*PI, 2*PI] to "
        "avoid precision problems.");
    return ((180.0F*radians ) / static_cast<plat::float32>(Utils::PI()));
}

}  // namespace math
}  // namespace secondpylon

#endif  // SECONDPYLON_MATH_MATH_UTILS_INL_H_
