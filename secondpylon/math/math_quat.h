// Copyright 2009 Brian Legge

#ifndef SECONDPYLON_MATH_MATH_QUAT_H_
#define SECONDPYLON_MATH_MATH_QUAT_H_

#include "secondpylon/math/math_vec3.h"
#include "secondpylon/plat/plat_compiler.h"

namespace secondpylon {
namespace math {

template <typename TStorage>
class quat {
public:
  enum EComponents {
    kW = 0
    , kX = 1
    , kY = 2
    , kZ = 3
  };

  TStorage q[4];

  // Default construct doesn't do any initialization for performance reasons.
  quat() { }
  quat(const quat& rhs);
  quat(TStorage w, TStorage x, TStorage y, TStorage z);

  // Access operators
  TStorage& operator[](int i) { return q[i]; }
  const TStorage& operator[](int i) const { return q[i]; }

  // Unary operators
  quat operator-() const { return(quat(-x, -y, -z, -w)); }
  quat operator+() const { return *this; }

  // Math functions
  quat Conjugate() const;

  // Assignment operators
  quat<TStorage>& operator-=(const quat&);
  quat<TStorage>& operator+=(const quat&);
  quat<TStorage>& operator*=(const quat&);

  // Comparison
  SPPLAT_INLINE int operator==(const quat&) const;
  int Equals(const quat&, TStorage epsilon = 1E-6f) const;

  SPPLAT_INLINE int IsIdentity() const;
  void Normalize();

  // Binary Operators
  quat operator-(const quat&) const;
  quat operator+(const quat&) const;
  quat operator*(const quat&) const;

  // Transform Operators
  math::vec3<TStorage> RotatePoint(const math::vec3<TStorage>& source) const;

  static quat<TStorage> GetIdentity();
};

}  // namespace math
}  // namespace secondpylon

#include "secondpylon/math/math_quat-inl.h"

#endif  // SECONDPYLON_MATH_MATH_QUAT_H_
