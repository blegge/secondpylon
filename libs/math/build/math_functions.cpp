#include <secondpylon/math/math_functions.h>

namespace secondpylon {
namespace math {

plat::float32 Functions::Sqrt(plat::float32 source)
{
    SPDIAG_ASSERT(source >= 0.0f);
    return sqrtf(source);
}

plat::float32 Functions::Abs(plat::float32 source)
{
	return fabsf(source);
}

plat::float32 Functions::DegreeToRadian(plat::float32 degrees)
{
	SPDIAG_ASSERT(Functions::Abs(degrees) <= 360.0f);
    return ((degrees * static_cast<plat::float32>(Functions::PI())) / 180.0F);
}

plat::float32 RadianToDegree(plat::float32 radians)
{
    SPDIAG_ASSERT(Functions::Abs(radians) <= Functions::PI()*2.0f);
    return ((180.0F*radians ) / static_cast<plat::float32>(Functions::PI()));;
}

}
}
