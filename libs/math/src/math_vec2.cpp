#include <secondpylon\math\math_vec2.h>

using namespace secondpylon::plat;

namespace secondpylon {
namespace math {

float32 vec2::Length() const
{
    return 0.0F;
}

plat::uint32 vec2::MaxComponent() const
{
	if (y > x)
		return 1;
	else
		return 0;
}

plat::uint32 vec2::MinComponent() const
{
	if (y < x)
		return 1;
	else
		return 0;
}

vec2 vec2::Normal() const
{
	float32 flLength = Length();
	float32 flInvLength = 0;
	if (flLength != 0.0f)
		flInvLength = 1.0f / flLength;

	return vec2(x * flInvLength, y * flInvLength);
}

bool8 vec2::Equals(const vec2& p, float32 epsilon)
{
	if (p.x > x-epsilon && p.x < x+epsilon &&
		p.y > y-epsilon && p.y < y+epsilon)
		return 1;
	else
		return 0;
}

vec2& vec2::Unify()
{
	float32 flLength = Length();
	float32 flInvLength = 0;
	if (flLength != 0.0f)
		flInvLength = 1.0f / flLength;

	x *= flInvLength;
	y *= flInvLength;
	return *this;
}

}
}
