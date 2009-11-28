// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_MATH_MATH_VEC3_H_
#define SECONDPYLON_MATH_MATH_VEC3_H_

#include "secondpylon/plat/plat_types.h"
#include "secondpylon/plat/plat_compiler.h"
#include "secondpylon/diag/diag_assert.h"

namespace secondpylon {
namespace math {

template <typename TStorage>
class vec3 {
 public:
    TStorage x;
    TStorage y;
    TStorage z;

    // Default construct doesn't do any initialization for performance reasons.
    vec3() {}
    vec3(const vec3& p);
    vec3(plat::float32 X,  plat::float32 Y, plat::float32 Z);

    // Access operators
    float& operator[](plat::uint32 i) { return (&x)[i]; }
    const float& operator[](plat::uint32 i) const { return (&x)[i]; }

    // Unary operators
    vec3 operator-() const { return(vec3(-x, -y, -z)); }
    vec3 operator+() const { return *this; }

    // Property functions
    plat::float32 Length() const;
    vec3 Normal() const;

    // Assignment operators
    vec3& operator-=(const vec3&);
    vec3& operator+=(const vec3&);
    vec3& operator*=(plat::float32);
    vec3& operator/=(plat::float32);

    // Relational operators
    plat::bool8 operator==(const vec3& p) const;
    plat::bool8 operator!=(const vec3& p) const;
    plat::bool8 Equals(const vec3& p, plat::float32 epsilon = 1E-6f) const;

    // Binary operators
    vec3 operator-(const vec3&) const;
    vec3 operator+(const vec3&) const;
    vec3 operator-(plat::float32) const;
    vec3 operator+(plat::float32) const;

    static vec3<TStorage> CrossProduct(
        const vec3<TStorage>& a, const vec3<TStorage>& b);

    static plat::float32 DotProduct(
        const vec3<TStorage>& a, const vec3<TStorage>& b);

    static vec3<TStorage> Interpolate(
        const vec3<TStorage>& p1, const vec3<TStorage>& p2, plat::float32 t);
};

}  // namespace math
}  // namespace secondpylon

#include "secondpylon/math/math_vec3-inl.h"

#endif  // SECONDPYLON_MATH_MATH_VEC3_H_
