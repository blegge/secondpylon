// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_MATH_MATH_VEC3_INL_H_
#define SECONDPYLON_MATH_MATH_VEC3_INL_H_

namespace secondpylon {
namespace math {

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage>::vec3(const vec3& p) {
  x = p.x;
  y = p.y;
  z = p.z;
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage>::vec3(plat::float32 X,  plat::float32 Y, plat::float32 Z)
  : x(X), y(Y), z(Z) {
}

template <typename TStorage>
SPPLAT_INLINE plat::bool8 vec3<TStorage>::operator==(const vec3<TStorage>& p) const {
  return ((p.x == x) && (p.y == y) && (p.z == z));
}

template <typename TStorage>
SPPLAT_INLINE plat::bool8 vec3<TStorage>::operator!=(const vec3& p) const {
  return ((p.x != x)||(p.y != y)||(p.z != z));
}

template <typename TStorage>
SPPLAT_INLINE plat::bool8 vec3<TStorage>::Equals(const vec3<TStorage>& p
                   , plat::float32 epsilon) const {
  return (M_Abs(p.x - x) <= epsilon &&
    M_Abs(p.y - y) <= epsilon &&
    M_Abs(p.z - z) <= epsilon);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage>& vec3<TStorage>::operator-=(
  const vec3<TStorage>& a) {
  x -= a.x;
  y -= a.y;
  z -= a.z;
  return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage>& vec3<TStorage>::operator+=(
  const vec3<TStorage>& a) {
  x += a.x;
  y += a.y;
  z += a.z;
  return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage>& vec3<TStorage>::operator*=(plat::float32 f) {
  x *= f;
  y *= f;
  z *= f;
  return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage>& vec3<TStorage>::operator/=(plat::float32 f) {
  x /= f;
  y /= f;
  z /= f;
  return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> vec3<TStorage>::operator-(const vec3& b) const {
  return (vec3<TStorage>(x-b.x, y-b.y, z-b.z));
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> vec3<TStorage>::operator+(
  const vec3<TStorage>& b) const {
  return (vec3<TStorage>(x+b.x, y+b.y, z+b.z));
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> vec3<TStorage>::operator-(plat::float32 f) const {
  return vec3<TStorage>(x-f, y-f, z-f);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> vec3<TStorage>::operator+(plat::float32 f) const {
  return vec3<TStorage>(x+f, y+f, z+f);
}

template <typename TStorage>
SPPLAT_INLINE plat::float32 vec3<TStorage>::Length() const {
  return M_Sqrt(x*x+y*y+z*z);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> vec3<TStorage>::Normal() const {
  plat::float32 flLength = Length();
  plat::float32 flInvLength = 0;
  if (flLength != 0.0f)
  flInvLength = 1.0f / flLength;

  return vec3<TStorage>(x * flInvLength, y * flInvLength, z * flInvLength);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> operator*(plat::float32 f
                     , const vec3<TStorage>& a) {
  return vec3<TStorage>(a.x*f, a.y*f, a.z*f);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> operator*(const vec3<TStorage>& a
                     , plat::float32 f) {
  return vec3<TStorage>(a.x*f, a.y*f, a.z*f);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> operator/(const vec3<TStorage>& a
                     , plat::float32 f) {
  return vec3<TStorage>(a.x/f, a.y/f, a.z/f);
}
template <typename TStorage>
SPPLAT_INLINE plat::float32 vec3<TStorage>::DotProduct(
  const vec3<TStorage>& a, const vec3<TStorage>& b) {
  return (a.x*b.x + a.y*b.y + a.z*b.z);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> vec3<TStorage>::CrossProduct(
  const vec3<TStorage>& a, const vec3<TStorage>& b) {
  return vec3<TStorage>(
    a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

template <typename TStorage>
SPPLAT_INLINE vec3<TStorage> vec3<TStorage>::Interpolate(
  const vec3<TStorage> &p1, const vec3<TStorage> &p2, plat::float32 t ) {
  SPDIAG_ASSERT(t >= TStorage(0) && t <= TStorage(1)
    , "Interpolation value is out of range");

  return p1 + t*(p2-p1);
}

}  // namespace secondpylon
}  // namespace math

#endif  // SECONDPYLON_MATH_MATH_VEC3_INL_H_
