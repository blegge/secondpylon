// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_MATH_MATH_VEC2_H_
#define SECONDPYLON_MATH_MATH_VEC2_H_

#include "secondpylon/plat/plat_types.h"
#include "secondpylon/plat/plat_compiler.h"
#include "secondpylon/math/math_utils.h"

namespace secondpylon {
namespace math {

template <typename TStorage>
class vec2 {
public:
    TStorage x;
    TStorage y;

    // Default construct doesn't do any initialization for performance reasons.
    vec2() { }
    vec2(const vec2<TStorage >& p);
    vec2(TStorage X, TStorage Y);

    // Access operators
    float& operator[](plat::uint32 i) { return (&x)[i]; }
    const float& operator[](plat::uint32 i) const { return (&x)[i]; }

    // Unary operators
    vec2<TStorage> operator-() const { return vec2<TStorage >(-x, -y); }
    vec2<TStorage> operator+() const { return *this; }

    // Property functions
    plat::float32 Length() const;
    vec2 Normal() const;

    // Assignment operators
    vec2& operator=(const vec2& source);
    vec2<TStorage>& operator-=(const vec2<TStorage >&);
    vec2<TStorage>& operator+=(const vec2<TStorage >&);
    vec2<TStorage>& operator*=(TStorage);
    vec2<TStorage>& operator/=(TStorage);

    // Relational operators
    plat::bool8 operator==(const vec2<TStorage>& p) const;
    plat::bool8 operator!=(const vec2<TStorage>& p) const;

    // Returns true if the vector components are within the specified epsilon.
    // Note that this epsilon is applied per-part, the vectors vec2(0, 0) and
    // vec2(1, 1) are equal under an epsilon of 1.
    plat::bool8 Equals(const vec2<TStorage>& p, TStorage epsilon = 1E-6f);

    // Binary operators
    vec2 operator-(const vec2&) const;
    vec2 operator+(const vec2&) const;

    // Static functions
    static TStorage DotProduct(
        const vec2<TStorage>& a
        , const vec2<TStorage>& b);

    static vec2<TStorage> Interpolate(
        const vec2<TStorage>& p1
        , const vec2<TStorage>& p2, TStorage t);
};

}  // namespace math
}  // namespace secondpylon

#include "secondpylon/math/math_vec2-inl.h"

#endif  // SECONDPYLON_MATH_MATH_VEC2_H_
