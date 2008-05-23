#ifndef SPMATH_VEC3_H
#define SPMATH_VEC3_H

#include <secondpylon/plat/plat_types.h>
#include <secondpylon/plat/plat_compiler.h>

namespace secondpylon {
namespace math {

template <typename TStorage>
class vec3
{
public:
    TStorage x;
    TStorage y;
    TStorage z;

    // Default construct doesn't do any initialization for performance reasons.
	vec3() {}
	vec3(const vec3 &p) { x = p.x; y = p.y; z = p.z; }
    explicit vec3(plat::float32 X,  plat::float32 Y, plat::float32 Z) { x = X; y = Y; z = Z; }

	// Access operators
    float& operator[](plat::uint32 i) { return (&x)[i]; }     
	const float& operator[](plat::uint32 i) const { return (&x)[i]; }  

	// Unary operators
	vec3 operator-() const { return(vec3(-x,-y,-z)); } 
	vec3 operator+() const { return *this; }

	// Property functions
    plat::float32 Length() const;
	vec3 Normal() const;

	// Assignment operators
	SPPLAT_INLINE vec3& operator-=(const vec3&);
	SPPLAT_INLINE vec3& operator+=(const vec3&);
	SPPLAT_INLINE vec3& operator*=(plat::float32); 
	SPPLAT_INLINE vec3& operator/=(plat::float32);

	// Relational operators
	SPPLAT_INLINE int operator==(const vec3& p) const { return ((p.x==x)&&(p.y==y)&&(p.z==z)); }
	SPPLAT_INLINE int operator!=(const vec3& p) const { return ((p.x!=x)||(p.y!=y)||(p.z!=z)); }
	plat::bool8 Equals(const vec3& p, plat::float32 epsilon = 1E-6f) const;

	// Binary operators
	SPPLAT_INLINE vec3 operator-(const vec3&) const;
	SPPLAT_INLINE vec3 operator+(const vec3&) const;
	SPPLAT_INLINE vec3 operator-(plat::float32) const;
	SPPLAT_INLINE vec3 operator+(plat::float32) const;

    static SPPLAT_INLINE vec3<TStorage> CrossProduct(const vec3<TStorage>& a, const vec3<TStorage>& b);
    static SPPLAT_INLINE plat::float32 DotProduct(const vec3<TStorage>& a, const vec3<TStorage>& b);
    static SPPLAT_INLINE vec3<TStorage> Interpolate(const vec3<TStorage>& p1, const vec3<TStorage>& p2, plat::float32 t);
};

//
// vec3 template function implementations
// 

template <typename TStorage>
plat::bool8 vec3<TStorage>::Equals(const vec3<TStorage>& p, plat::float32 epsilon) const
{
	return (M_Abs(p.x - x) <= epsilon && 
		M_Abs(p.y - y) <= epsilon && 
		M_Abs(p.z - z) <= epsilon);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage>& vec3<TStorage>::operator-=(const vec3<TStorage>& a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage>& vec3<TStorage>::operator+=(const vec3<TStorage>& a)
{
	x += a.x;
	y += a.y;
	z += a.z;
	return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage>& vec3<TStorage>::operator*=(plat::float32 f) 
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage>& vec3<TStorage>::operator/=(plat::float32 f)
{
	x /= f;
	y /= f;
	z /= f;	
	return *this; 
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> vec3<TStorage>::operator-(const vec3& b) const
{
	return (vec3<TStorage>(x-b.x,y-b.y,z-b.z));
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> vec3<TStorage>::operator+(const vec3<TStorage>& b) const
{
	return (vec3<TStorage>(x+b.x,y+b.y,z+b.z));
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> vec3<TStorage>::operator-(plat::float32 f) const
{
	return vec3<TStorage>(x-f, y-f, z-f);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> vec3<TStorage>::operator+(plat::float32 f) const
{
	return vec3<TStorage>(x+f, y+f, z+f);
}

template <typename TStorage>
plat::float32 vec3<TStorage>::Length() const
{
    return M_Sqrt(x*x+y*y+z*z);
}

template <typename TStorage>
vec3<TStorage> vec3<TStorage>::Normal() const
{
    plat::float32 flLength = Length();
    plat::float32 flInvLength = 0;
    if (flLength != 0.0f)
    flInvLength = 1.0f / flLength;

    return vec3<TStorage>(x * flInvLength, y * flInvLength, z * flInvLength);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> operator*(plat::float32 f, const vec3<TStorage>& a)
{
	return vec3<TStorage>(a.x*f, a.y*f, a.z*f);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> operator*(const vec3<TStorage>& a, plat::float32 f)
{
	return vec3<TStorage>(a.x*f, a.y*f, a.z*f);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> operator/(const vec3<TStorage>& a, plat::float32 f)
{
	return vec3<TStorage>(a.x/f, a.y/f, a.z/f);
}
template <typename TStorage>
SPPLAT_INLINE plat::float32 vec3<TStorage>::DotProduct(const vec3<TStorage>& a, const vec3<TStorage>& b)
{
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> vec3<TStorage>::CrossProduct(const vec3<TStorage>& a, const vec3<TStorage>& b)
{
	return vec3<TStorage>( a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x );
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> vec3<TStorage>::Interpolate( const vec3<TStorage> &p1, const vec3<TStorage> &p2, plat::float32 t )
{
	return p1 + t*(p2-p1);
}

}
}

#endif // SPMATH_VEC3_H
