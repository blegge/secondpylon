#include <secondpylon/math/math_utils.h>

namespace secondpylon {
namespace math {

plat::float32 Utils::Sqrt(plat::float32 source)
{
    SPDIAG_ASSERT(source >= 0.0f);
    return sqrtf(source);
}

plat::float32 Utils::Abs(plat::float32 source)
{
	return fabsf(source);
}

plat::float32 Utils::DegreeToRadian(plat::float32 degrees)
{
	SPDIAG_ASSERT(Utils::Abs(degrees) <= 360.0f);
    return ((degrees * static_cast<plat::float32>(Utils::PI())) / 180.0F);
}

plat::float32 Utils::RadianToDegree(plat::float32 radians)
{
    SPDIAG_ASSERT(Utils::Abs(radians) <= Utils::PI()*2.0f);
    return ((180.0F*radians ) / static_cast<plat::float32>(Utils::PI()));;
}

}
}
