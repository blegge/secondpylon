// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_MATH_MATH_QUAT_INL_H_
#define SECONDPYLON_MATH_MATH_QUAT_INL_H_

namespace secondpylon {
namespace math {

template <typename TStorage>
quat<TStorage>::quat(const quat& rhs) {
    q[kW] = rhs.q[kW];
    q[kX] = rhs.q[kX];
    q[kY] = rhs.q[kY];
    q[kZ] = rhs.q[kZ];
}

template <typename TStorage>
quat<TStorage>::quat(TStorage w, TStorage x, TStorage y, TStorage z) {
    q[kW] = w;
    q[kX] = x;
    q[kY] = y;
    q[kZ] = z;
}


template <typename TStorage>
SPPLAT_INLINE int quat<TStorage>::operator==(const quat &rhs) const {
    return (q[kX] == rhs.q[kX]
        && q[kY] == rhs.q[kY]
        && q[kZ] == rhs.q[kZ]
        && q[kW] == rhs.q[kW]);
}

// ----------

template <typename TStorage>
quat<TStorage> quat<TStorage>::Conjugate() const {
    return quat( q[kW], -q[kX], -q[kY], -q[kZ] );
}

template <typename TStorage>
quat<TStorage>& quat<TStorage>::operator-=(const quat &b) {
    x -= b.x;
    y -= b.y;
    z -= b.z;
    w -= b.w;
    return *this;
}

template <typename TStorage>
quat<TStorage>& quat<TStorage>::operator+=(const quat &b) {
    x += b.x;
    y += b.y;
    z += b.z;
    w += b.w;
    return *this;
}

template <typename TStorage>
quat<TStorage>& quat<TStorage>::operator*=(const quat &b) {
    x = w*b.x + x*b.w + y*b.z - z*b.y;
    y = w*b.y - x*b.z + y*b.w + z*b.x;
    z = w*b.z + x*b.y - y*b.x + z*b.w;
    w = w*b.w - x*b.x - y*b.y - z*b.z;
    return *this;
}

template <typename TStorage>
int quat<TStorage>::Equals(const quat &b, TStorage epsilon) const {
    return (M_Abs(x - b.x) <= epsilon &&
        M_Abs(y - b.y) <= epsilon &&
        M_Abs(z - b.z) <= epsilon &&
        M_Abs(w - b.w) <= epsilon);
}

template <typename TStorage>
int quat<TStorage>::IsIdentity() const {
    return ((x == 0) && (y == 0) && (z == 0) && (w == 1.0f));
}

template <typename TStorage>
void quat<TStorage>::Normalize() {
    TStorage dot;
    dot = M_Sqrt(x*x + y*y + z*z + w*w);
    x /= dot;
    y /= dot;
    z /= dot;
    w /= dot;
}

template <typename TStorage>
quat<TStorage> quat<TStorage>::operator-(const quat<TStorage> &b) const {
    return quat( x-b.x, y-b.y, z-b.z, w-b.w );
}

template <typename TStorage>
quat<TStorage> quat<TStorage>::operator+(const quat<TStorage> &b) const {
    return quat( x+b.x, y+b.y, z+b.z, w+b.w );
}

template <typename TStorage>
quat<TStorage> quat<TStorage>::operator*(const quat<TStorage> &b) const {
    return quat(
        w*b.x + x*b.w + y*b.z - z*b.y,   // x
        w*b.y - x*b.z + y*b.w + z*b.x,   // y
        w*b.z + x*b.y - y*b.x + z*b.w,   // z
        w*b.w - x*b.x - y*b.y - z*b.z);  // w
}

template <typename TStorage>
math::vec3<TStorage> quat<TStorage>::RotatePoint(
    const math::vec3<TStorage>& p) const {
    quat qp(p.x, p.y, p.z, 0);
    quat qr = (*this) * qp * Conjugate();

    return math::vec3<TStorage>(qr.x, qr.y, qr.z);
}

template <typename TStorage>
quat<TStorage> quat<TStorage>::GetIdentity() {
    return quat<TStorage>( TStorage(1), TStorage(0), TStorage(0), TStorage(0) );
}

}  // namespace secondpylon
}  // namespace math

#endif  // SECONDPYLON_MATH_MATH_QUAT_INL_H_
