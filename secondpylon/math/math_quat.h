#ifndef SPMATH_QUAT_H
#define SPMATH_QUAT_H

#include <secondpylon/math/math_vec3.h>
#include <secondpylon/plat/plat_compiler.h>

namespace secondpylon {
namespace math {

template <typename TStorage>
class quat
{
public:
    enum EComponents
    {
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
	quat operator-() const { return(quat(-x,-y,-z,-w)); }
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

    static quat<TStorage> GetIdentity() { return quat<TStorage>( TStorage(1), TStorage(0), TStorage(0), TStorage(0) ); }
};

template <typename TStorage>
quat<TStorage>::quat(const quat& rhs)
{
    q[kW] = rhs.q[kW];
    q[kX] = rhs.q[kX];
    q[kY] = rhs.q[kY];
    q[kZ] = rhs.q[kZ];
} 

template <typename TStorage>
quat<TStorage>::quat(TStorage w, TStorage x, TStorage y, TStorage z)
{
    q[kW] = w;
    q[kX] = x;
    q[kY] = y;
    q[kZ] = z;
}


template <typename TStorage>
SPPLAT_INLINE int quat<TStorage>::operator==(const quat &rhs) const
{
    return (q[kX] == rhs.q[kX]
        && q[kY] == rhs.q[kY]
        && q[kZ] == rhs.q[kZ]
        && q[kW] == rhs.q[kW]);
}

// ----------

template <typename TStorage>
quat<TStorage> quat<TStorage>::Conjugate() const
{
	return quat( q[kW], -q[kX], -q[kY], -q[kZ] );
}

template <typename TStorage>
quat<TStorage>& quat<TStorage>::operator-=(const quat &b)
{
	x -= b.x;
	y -= b.y;
	z -= b.z;
	w -= b.w;
	return *this;
}

template <typename TStorage>
quat<TStorage>& quat<TStorage>::operator+=(const quat &b)
{
	x += b.x;
	y += b.y;
	z += b.z;
	w += b.w;
	return *this;
}

template <typename TStorage>
quat<TStorage>& quat<TStorage>::operator*=(const quat &b)
{
	x = w*b.x + x*b.w + y*b.z - z*b.y;
	y = w*b.y - x*b.z + y*b.w + z*b.x;
	z = w*b.z + x*b.y - y*b.x + z*b.w; 
	w = w*b.w - x*b.x - y*b.y - z*b.z;
	return *this;
}

template <typename TStorage>
int quat<TStorage>::Equals(const quat &b, TStorage epsilon) const
{
	return (M_Abs(x - b.x) <= epsilon && 
		M_Abs(y - b.y) <= epsilon && 
		M_Abs(z - b.z) <= epsilon && 
		M_Abs(w - b.w) <= epsilon);
}

template <typename TStorage>
int quat<TStorage>::IsIdentity() const
{
	return ((x == 0) && (y == 0) && (z == 0) && (w == 1.0f));
}

template <typename TStorage>
void quat<TStorage>::Normalize()
{
	TStorage dot;
	dot = M_Sqrt(x*x + y*y + z*z + w*w);
	x /= dot;
	y /= dot;
	z /= dot;
	w /= dot;
}

template <typename TStorage>
quat<TStorage> quat<TStorage>::operator-(const quat<TStorage> &b) const
{
	return quat( x-b.x, y-b.y, z-b.z, w-b.w );
}

template <typename TStorage>
quat<TStorage> quat<TStorage>::operator+(const quat<TStorage> &b) const
{
	return quat( x+b.x, y+b.y, z+b.z, w+b.w );
}

template <typename TStorage>
quat<TStorage> quat<TStorage>::operator*(const quat<TStorage> &b) const
{
	return quat(
		w*b.x + x*b.w + y*b.z - z*b.y,  // x
		w*b.y - x*b.z + y*b.w + z*b.x,  // y
		w*b.z + x*b.y - y*b.x + z*b.w,  // z
		w*b.w - x*b.x - y*b.y - z*b.z); // w
}

template <typename TStorage>
math::vec3<TStorage> quat<TStorage>::RotatePoint(const math::vec3<TStorage>& p) const
{
	// r = q * p * q' (where q' = inverse of q)
//	CPoint3 r;
//	r.x =      w*w*p.x + 2.0f*y*w*p.z - 2.0f*z*w*p.y +      x*x*p.x + 2.0f*y*x*p.y + 2.0f*z*x*p.z -      z*z*p.x - y*y*p.x;
//	r.y = 2.0f*x*y*p.x +      y*y*p.y + 2.0f*z*y*p.z + 2.0f*w*z*p.x -      z*z*p.y +      w*w*p.y - 2.0f*x*w*p.z - x*x*p.y;
//	r.z = 2.0f*x*z*p.x + 2.0f*y*z*p.y +      z*z*p.z - 2.0f*w*y*p.x -      y*y*p.z + 2.0f*w*x*p.y -      x*x*p.z + w*w*p.z;

	quat qr;
	quat qp(p.x, p.y, p.z, 0);
	qr = (*this) * qp * Conjugate();

	return math::vec3<TStorage>(qr.x, qr.y, qr.z);
}

}
}

#endif // SPMATH_QUAT_H
