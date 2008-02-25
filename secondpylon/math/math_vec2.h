#ifndef SPMATH_VEC2_H
#define SPMATH_VEC2_H

#include <secondpylon\plat\plat_types.h>
#include <secondpylon\plat\plat_compiler.h>

namespace secondpylon {
namespace math {
    
class vec2
{
public:
	plat::float32 x;
    plat::float32 y;

	// Constructors
	vec2() { }
	vec2(const vec2& p) { x = p.x; y = p.y; }
	vec2(plat::float32 X, plat::float32 Y)   { x = X; y = Y;  }
	explicit vec2(const plat::float32 vf[2])  { x = vf[0]; y = vf[1]; }

	// Access operators
    float& operator[](plat::uint32 i) { return (&x)[i]; }     
	const float& operator[](plat::uint32 i) const { return (&x)[i]; }  
	
	// Unary operators
	vec2 operator-() const { return vec2(-x,-y); } 
	vec2 operator+() const { return *this; }
    
    // Property functions
	plat::float32 Length() const;
	plat::uint32 MaxComponent() const;
	plat::uint32 MinComponent() const;
	vec2 Normal() const;

	// Assignment operators
	SPPLAT_INLINE vec2& operator-=(const vec2&);
	SPPLAT_INLINE vec2& operator+=(const vec2&);
    SPPLAT_INLINE vec2& operator*=(plat::float32);
	SPPLAT_INLINE vec2& operator/=(plat::float32);

	// Relational operators
    plat::bool8 operator==(const vec2& p) const { return ((x == p.x) && (y == p.y)); }
	plat::bool8 operator!=(const vec2& p) const { return ((x != p.x) || (y != p.y)); }
	plat::bool8 Equals(const vec2& p, plat::float32 epsilon = 1E-6f);

	// In-place normalize
	vec2& Unify();

	// Binary operators
	SPPLAT_INLINE vec2 operator-(const vec2&) const;
	SPPLAT_INLINE vec2 operator+(const vec2&) const;
};

SPPLAT_INLINE vec2& vec2::operator-=(const vec2& a)
{
	x -= a.x;
	y -= a.y;
	return *this;
}

SPPLAT_INLINE vec2& vec2::operator+=(const vec2& a)
{
	x += a.x;
	y += a.y;
	return *this;
}

SPPLAT_INLINE vec2& vec2::operator*=(plat::float32 f)
{
	x *= f;
	y *= f;
	return *this;
}

SPPLAT_INLINE vec2& vec2::operator/=(plat::float32 f)
{
	x /= f;
	y /= f;
	return *this; 
}

SPPLAT_INLINE vec2 vec2::operator-(const vec2& b) const
{
	return vec2(x-b.x, y-b.y);
}

SPPLAT_INLINE vec2 vec2::operator+(const vec2& b) const
{
	return vec2(x+b.x, y+b.y);
}

//
// Operators
// 

SPPLAT_INLINE vec2 operator*(plat::float32 f, const vec2& a)
{
	return vec2(a.x*f, a.y*f);
}

SPPLAT_INLINE vec2 operator*(const vec2& a, plat::float32 f)
{
	return vec2(a.x*f, a.y*f);
}

SPPLAT_INLINE vec2 operator/(const vec2& a, plat::float32 f)
{
	return vec2(a.x/f, a.y/f);
}

SPPLAT_INLINE plat::float32 DotProduct(const vec2& a, const vec2& b)
{
	return (a.x*b.x + a.y*b.y);
}

SPPLAT_INLINE vec2 Interpolate(const vec2& p1, const vec2& p2, plat::float32 t)
{
	return p1 + t*(p2-p1);
}

}
}

#endif // SPMATH_VEC2_H
