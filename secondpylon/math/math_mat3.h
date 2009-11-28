// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_MATH_MATH_MAT3_H_
#define SECONDPYLON_MATH_MATH_MAT3_H_

#include "secondpylon/plat/plat_types.h"
#include "secondpylon/plat/plat_compiler.h"
#include "secondpylon/math/math_vec3.h"

// Example matrix implementation.
// http://msdn2.microsoft.com/en-us/library/microsoft.xna.framework.matrix_methods.aspx
//
// What is the role of the matrix vs quaternion?
// - Quats are smaller, do we need a 3x3 when we could use a quat instead?
// - Quats interpolate nicely
// - 4x4 matrices can represent translation and rotation
// - APIs require matrices
namespace secondpylon {
namespace math {

template <typename TStorage>
class mat3 {
public:
    enum {
        kComponents = 9
    };

    enum EElements {
        k00 = 0, k01 = 1,  k02 = 2
        , k10 = 3, k11 = 4,  k12 = 5
        , k20 = 6, k21 = 7,  k22 = 8
    };

    TStorage m[kComponents];

    // Default construct doesn't do any initialization for performance reasons.
    mat3() {}
    mat3(TStorage m00, TStorage m01, TStorage m02
        , TStorage m10, TStorage m11, TStorage m12
        , TStorage m20, TStorage m21, TStorage m22);

    // Performs an exact equalty test on all components in the matrix. This
    // should only be used in special cases.
    bool operator==(const mat3<TStorage>& rhs) const;
    bool operator!=(const mat3<TStorage>& rhs) const;

    TStorage operator[](EElements element) const { return m[element]; }

    // Static functions
    static void Identity(mat3<TStorage>* dest);

    static void Multiply(
        const mat3<TStorage>& dest
        , const mat3<TStorage>& source0
        , const mat3<TStorage>& source1);

    static void Transform(
        const math::vec3<TStorage>&dest
        , const mat3<TStorage>& source0
        , const math::vec3<TStorage>& source);

    static void Transpose(
        const math::mat3<TStorage>& source
        , math::mat3<TStorage>* dest);
};

}  // namespace math
}  // namespace secondpylon

#include "secondpylon/math/math_mat3-inl.h"

#endif  // SECONDPYLON_MATH_MATH_MAT3_H_
