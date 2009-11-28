// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_MATH_MATH_MAT3_INL_H_
#define SECONDPYLON_MATH_MATH_MAT3_INL_H_

namespace secondpylon {
namespace math {

template <typename TStorage>
mat3<TStorage>::mat3(
    TStorage m00, TStorage m01, TStorage m02
    , TStorage m10, TStorage m11, TStorage m12
    , TStorage m20, TStorage m21, TStorage m22) {
    m[k00] = m00;
    m[k01] = m01;
    m[k02] = m02;

    m[k10] = m10;
    m[k11] = m11;
    m[k12] = m12;

    m[k20] = m20;
    m[k21] = m21;
    m[k22] = m22;
}

template <typename TStorage>
void mat3<TStorage>::Identity(mat3<TStorage>* dest) {
    *dest = mat3<TStorage>(
        TStorage(1), TStorage(0), TStorage(0)
        , TStorage(0), TStorage(1), TStorage(0)
        , TStorage(0), TStorage(0), TStorage(1));
}

template <typename TStorage>
bool mat3<TStorage>::operator==(const mat3<TStorage> rhs) const {
    plat::uint8 equal = 1;
    for (plat::uint32 i = 0; i < kComponents; ++i) {
        equal &= (m[i] == rhs.m[i]);
    }
    return (equal == 1);
}

template <typename TStorage>
bool mat3<TStorage>::operator!=(const mat3<TStorage> rhs) const {
    return !(*this == rhs);
}

template <typename TStorage>
void mat3<TStorage>::Transpose(const math::mat3<TStorage>& source
                               , math::mat3<TStorage>* dest) {
    dest->m[k00] = source.m[k00];
    dest->m[k01] = source.m[k10];
    dest->m[k02] = source.m[k20];

    dest->m[k10] = source.m[k01];
    dest->m[k11] = source.m[k11];
    dest->m[k12] = source.m[k21];

    dest->m[k20] = source.m[k02];
    dest->m[k21] = source.m[k12];
    dest->m[k22] = source.m[k22];
}

}  // namespace math
}  // namespace secondpylon

#endif  // SECONDPYLON_MATH_MATH_MAT3_INL_H_
