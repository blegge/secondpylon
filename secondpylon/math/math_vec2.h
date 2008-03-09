#ifndef SPMATH_VEC2_H
#define SPMATH_VEC2_H

#include <secondpylon/plat/plat_types.h>
#include <secondpylon/plat/plat_compiler.h>
#include <secondpylon/math/math_functions.h>

namespace secondpylon {
namespace math {
 
template <typename TStorage>
class vec2
{
public:
	TStorage x;
    TStorage y;

	// Default construct doesn't do any initialization for performance reasons.
    vec2() { }
	vec2(const vec2<TStorage >& p) { x = p.x; y = p.y; }
	vec2(TStorage X, TStorage Y)   { x = X; y = Y;  }

	// Access operators
    float& operator[](plat::uint32 i) { return (&x)[i]; }     
	const float& operator[](plat::uint32 i) const { return (&x)[i]; }  
	
	// Unary operators
	vec2<TStorage> operator-() const { return vec2<TStorage >(-x,-y); } 
	vec2<TStorage> operator+() const { return *this; }
    
    // Property functions
    plat::float32 Length() const;
	vec2 Normal() const;

	// Assignment operators
	SPPLAT_INLINE vec2<TStorage>& operator-=(const vec2<TStorage >&);
	SPPLAT_INLINE vec2<TStorage>& operator+=(const vec2<TStorage >&);
    SPPLAT_INLINE vec2<TStorage>& operator*=(TStorage);
	SPPLAT_INLINE vec2<TStorage>& operator/=(TStorage);

	// Relational operators
    plat::bool8 operator==(const vec2<TStorage>& p) const { return ((x == p.x) && (y == p.y)); }
	plat::bool8 operator!=(const vec2<TStorage>& p) const { return ((x != p.x) || (y != p.y)); }
	
    // Returns true if the vector components are within the specified epsilon. Note that this epsilon is applied
    // per-part, the vectors vec2(0,0) and vec2(1,1) are equal under an epsilon of 1.
    plat::bool8 Equals(const vec2<TStorage>& p, TStorage epsilon = 1E-6f);

	// Binary operators
	SPPLAT_INLINE vec2 operator-(const vec2&) const;
	SPPLAT_INLINE vec2 operator+(const vec2&) const;

    // Static functions
    static SPPLAT_INLINE TStorage DotProduct(const vec2<TStorage>& a, const vec2<TStorage>& b);
    static SPPLAT_INLINE vec2<TStorage> Interpolate(const vec2<TStorage>& p1, const vec2<TStorage>& p2, TStorage t);
};

//
// vec2 template function implementations
// 
template <typename TStorage>
SPPLAT_INLINE vec2<TStorage>& vec2<TStorage>::operator-=(const vec2<TStorage>& a)
{
	x -= a.x;
	y -= a.y;
	return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage >& vec2<TStorage>::operator+=(const vec2<TStorage >& a)
{
	x += a.x;
	y += a.y;
	return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage >& vec2<TStorage>::operator*=(TStorage f)
{
	x *= f;
	y *= f;
	return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage >& vec2<TStorage>::operator/=(TStorage f)
{
	x /= f;
	y /= f;
	return *this; 
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage > vec2<TStorage>::operator-(const vec2& b) const
{
	return vec2(x-b.x, y-b.y);
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage > vec2<TStorage>::operator+(const vec2& b) const
{
	return vec2(x+b.x, y+b.y);
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage> operator*(TStorage f, const vec2<TStorage>& a)
{
	return vec2<TStorage>(a.x*f, a.y*f);
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage> operator*(const vec2<TStorage>& a, TStorage f)
{
	return vec2<TStorage>(a.x*f, a.y*f);
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage> operator/(const vec2<TStorage>& a, TStorage f)
{
	return vec2<TStorage>(a.x/f, a.y/f);
}

template <typename TStorage>
SPPLAT_INLINE TStorage vec2<TStorage>::DotProduct(const vec2& a, const vec2& b)
{
	return (a.x*b.x + a.y*b.y);
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage> vec2<TStorage>::Interpolate(const vec2<TStorage>& p1, const vec2<TStorage>& p2, TStorage t)
{
	return p1 + t*(p2-p1);
}

template <typename TStorage>
plat::float32 vec2<TStorage>::Length() const
{
    return Functions::Sqrt(x*x+y*y);
}

template <typename TStorage>
vec2<TStorage> vec2<TStorage>::Normal() const
{
    plat::float32 flLength = Length();
	plat::float32 flInvLength = 0;
	if (flLength != 0.0F)
		flInvLength = 1.0F / flLength;

	return vec2(x * flInvLength, y * flInvLength);
}

template <typename TStorage>
plat::bool8 vec2<TStorage>::Equals(const vec2<TStorage>& p, TStorage epsilon)
{
	if (p.x > x-epsilon && p.x < x+epsilon &&
		p.y > y-epsilon && p.y < y+epsilon)
		return 1;
	else
		return 0;
}

//
// Common vec2 types.
//

// @todo should these be moved to another location? They seem out of place in this header but we don't have a more
//       suitable header yet.
typedef vec2<plat::float32> vec2f;
typedef vec2<plat::uint32> vec2i;

}
}

#endif // SPMATH_VEC2_H
