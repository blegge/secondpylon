#ifndef SPMATH_MAT3_H
#define SPMATH_MAT3_H

#include <secondpylon/plat/plat_types.h>
#include <secondpylon/plat/plat_compiler.h>
#include <secondpylon/math/math_vec3.h>

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
class mat3
{
public:
    enum 
    {
        kComponents = 9
    };

    enum EElements
    { 
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

    // Performs an exact equalty test on all components in the matrix. This should only be used in special cases.
    bool operator==(const mat3<TStorage> rhs) const;
    bool operator!=(const mat3<TStorage> rhs) const;

    TStorage operator[](EElements element) const { return m[element]; }

    // Static functions
    static void Identity(mat3<TStorage>& dest);
    static void Multiply(const mat3<TStorage>& dest, const mat3<TStorage>& source0, const mat3<TStorage>& source1);
    static void Transform(const math::vec3<TStorage>&dest, const mat3<TStorage>& source0, const math::vec3<TStorage>& source);
    static void Transpose(math::mat3<TStorage>& dest, const math::mat3<TStorage>& source);
};


template <typename TStorage>
mat3<TStorage>::mat3(
    TStorage m00, TStorage m01, TStorage m02
    , TStorage m10, TStorage m11, TStorage m12
    , TStorage m20, TStorage m21, TStorage m22) 
{
    m[k00] = m00; m[k01] = m01; m[k02] = m02;
    m[k10] = m10; m[k11] = m11; m[k12] = m12;
    m[k20] = m20; m[k21] = m21; m[k22] = m22;
}

template <typename TStorage>
void mat3<TStorage>::Identity(mat3<TStorage>& dest)
{
    dest = mat3<TStorage>(
        TStorage(1), TStorage(0), TStorage(0)
        , TStorage(0), TStorage(1), TStorage(0)
        , TStorage(0), TStorage(0), TStorage(1));
}

template <typename TStorage>
bool mat3<TStorage>::operator==(const mat3<TStorage> rhs) const
{
    plat::uint8 equal = 1;
    for (plat::uint32 i = 0; i < kComponents; ++i)
    {
        equal &= (m[i] == rhs.m[i]);
    }
    return (equal == 1);
}

template <typename TStorage>
bool mat3<TStorage>::operator!=(const mat3<TStorage> rhs) const
{
    return !(*this == rhs);
}

template <typename TStorage>
void mat3<TStorage>::Transpose(math::mat3<TStorage>& dest, const math::mat3<TStorage>& source)
{
    dest.m[k01] = source.m[k10];
    dest.m[k02] = source.m[k20];
    dest.m[k10] = source.m[k01];
    dest.m[k12] = source.m[k21];
    dest.m[k20] = source.m[k02];
    dest.m[k21] = source.m[k12];
}


}
}

#endif // SPMATH_MAT3_H
