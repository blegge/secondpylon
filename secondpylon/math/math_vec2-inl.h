// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_MATH_MATH_VEC2_INL_H_
#define SECONDPYLON_MATH_MATH_VEC2_INL_H_

namespace secondpylon {
namespace math {

template <typename TStorage>
vec2<TStorage>::vec2(const vec2<TStorage >& p) : x(p.x), y(p.y) {
}

template <typename TStorage>
vec2<TStorage>::vec2(TStorage X, TStorage Y) : x(X), y(Y) {
}

template <typename TStorage>
vec2<TStorage>& vec2<TStorage>::operator=(const vec2& source) {
  x = source.x;
  y = source.y;
  return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage>& vec2<TStorage>::operator-=(
  const vec2<TStorage>& a) {
  x -= a.x;
  y -= a.y;
  return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage >& vec2<TStorage>::operator+=(
  const vec2<TStorage >& a) {
  x += a.x;
  y += a.y;
  return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage >& vec2<TStorage>::operator*=(TStorage f) {
  x *= f;
  y *= f;
  return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage >& vec2<TStorage>::operator/=(TStorage f) {
  SPDIAG_ASSERT(f != TStorage(0), "Cannot divide a vector by 0");
  x /= f;
  y /= f;
  return *this;
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage > vec2<TStorage>::operator-(const vec2& b) const {
  return vec2(x-b.x, y-b.y);
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage > vec2<TStorage>::operator+(const vec2& b) const {
  return vec2(x+b.x, y+b.y);
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage> operator*(TStorage f, const vec2<TStorage>& a) {
  return vec2<TStorage>(a.x*f, a.y*f);
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage> operator*(const vec2<TStorage>& a, TStorage f) {
  return vec2<TStorage>(a.x*f, a.y*f);
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage> operator/(const vec2<TStorage>& a, TStorage f) {
  return vec2<TStorage>(a.x/f, a.y/f);
}

template <typename TStorage>
SPPLAT_INLINE TStorage vec2<TStorage>::DotProduct(const vec2& a
                          , const vec2& b) {
  return (a.x*b.x + a.y*b.y);
}

template <typename TStorage>
SPPLAT_INLINE vec2<TStorage> vec2<TStorage>::Interpolate(
  const vec2<TStorage>& p1, const vec2<TStorage>& p2, TStorage t) {
  SPDIAG_ASSERT(t >= TStorage(0) && t <= TStorage(1),
    "Interpolation value is out of range");
  return p1 + t*(p2-p1);
}

template <typename TStorage>
plat::float32 vec2<TStorage>::Length() const {
  return Utils::Sqrt(x*x+y*y);
}

template <typename TStorage>
vec2<TStorage> vec2<TStorage>::Normal() const {
  plat::float32 flLength = Length();
  plat::float32 flInvLength = 0;
  if (flLength != 0.0F)
    flInvLength = 1.0F / flLength;

  return vec2(x * flInvLength, y * flInvLength);
}

template <typename TStorage>
plat::bool8 vec2<TStorage>::Equals(const vec2<TStorage>& p, TStorage epsilon) {
  if (p.x > x-epsilon && p.x < x+epsilon &&
    p.y > y-epsilon && p.y < y+epsilon)
    return 1;
  else
    return 0;
}

template <typename TStorage>
plat::bool8 vec2<TStorage>::operator==(const vec2<TStorage>& p) const {
  return ((x == p.x) && (y == p.y));
}

template <typename TStorage>
plat::bool8 vec2<TStorage>::operator!=(const vec2<TStorage>& p) const {
  return ((x != p.x) || (y != p.y));
}

}  // namespace secondpylon
}  // namespace math

#endif  // SECONDPYLON_MATH_MATH_VEC2_INL_H_
