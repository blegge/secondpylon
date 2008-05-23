#ifndef SPMATH_QUAT3_H
#define SPMATH_QUAT3_H

namespace secondpylon {
namespace math {

class CMatrix3;
class CAxisAngle;

class CQuaternion
{
public:
	float x,y,z,w;

	// Constructors
	CQuaternion() : x(0.0f),y(0.0f),z(0.0f),w(1.0f) { }
	CQuaternion(const CQuaternion &a) { x = a.x; y = a.y; z = a.z; w = a.w; } 
	CQuaternion(float X, float Y, float Z, float W) { x = X; y = Y; z = Z; w = W; }
	CQuaternion(double X, double Y, double Z, double W) { x=(float)X; y=(float)Y; z=(float)Z; w=(float)W; }
	explicit CQuaternion(float vf[4]) { x = vf[0]; y = vf[1]; z = vf[2]; w = vf[3]; }
	CQuaternion(const CMatrix3 &mat);
	CQuaternion(const CPoint3 &V, float W);

    // Data members
    static const CQuaternion Identity;

	// Access operators
	float& operator[](int i) { return (&x)[i]; }
	const float& operator[](int i) const { return (&x)[i]; }

	float Scalar() { return w; }
	CPoint3 Vector() { return CPoint3(x, y, z); }

	// Conversion function
	operator float*() { return(&x); }

	// Unary operators
	CQuaternion operator-() const { return(CQuaternion(-x,-y,-z,-w)); }
	CQuaternion operator+() const { return *this; }

    // Math functions
	CQuaternion Inverse() const;   // assumes unit quaternion
	CQuaternion Conjugate() const;
//	CQuaternion LogN() const;
//	CQuaternion Exp() const;

	// Assignment operators
	CQuaternion& operator-=(const CQuaternion&);
	CQuaternion& operator+=(const CQuaternion&);
	CQuaternion& operator*=(const CQuaternion&);
	CQuaternion& operator*=(float);
	CQuaternion& operator/=(float);

	CQuaternion& Set(float X, float Y, float Z, float W)
		{ x = X; y = Y; z = Z; w = W; return *this; }
	CQuaternion& Set(double X, double Y, double Z, double W)
		{ x = (float)X; y = (float)Y; z = (float)Z; w = (float)W; return *this; }

	CQuaternion& Set(const CMatrix3 &in_Matrix );
	CQuaternion& Set(const CAxisAngle &aa);
	CQuaternion& Set(const CPoint3 &V, float W);
	CQuaternion& SetEuler(float X, float Y, float Z, int iEulerOrder=kEulerOrderXYZ);
	inline void SetIdentity() { x = y = z = 0; w = 1.0f; }
	CQuaternion& Invert(); // assumes unit quaternion

//	CQuaternion& MakeClosest(const CQuaternion &qto);

	// Comparison
	inline int operator==(const CQuaternion&) const;
	int Equals(const CQuaternion&, float epsilon = 1E-6f) const;

	inline int IsIdentity() const;
	void Normalize();
//	void GetEuler(float *X, float *Y, float *Z) const;

	// Binary Operators
	CQuaternion operator-(const CQuaternion&) const;
	CQuaternion operator+(const CQuaternion&) const;
	CQuaternion operator*(const CQuaternion&) const;

	// Transform Operators
	CPoint3 RotatePoint(const CPoint3&) const;
};

// Inlines:
inline int CQuaternion::operator==(const CQuaternion &b) const
{
	return ((x == b.x) &&
		(y == b.y) && 
		(z == b.z) && 
		(w == b.w));
}

inline CQuaternion operator*(float f, const CQuaternion &q)
{
	return CQuaternion( q.x*f, q.y*f, q.z*f, q.w*f );
}

inline CQuaternion operator*(const CQuaternion &q, float f)
{
	return CQuaternion( q.x*f, q.y*f, q.z*f, q.w*f );
}

inline CQuaternion operator/(const CQuaternion &q, float f)
{
	return CQuaternion( q.x/f, q.y/f, q.z/f, q.w/f );
}

// dot product of two quaternions
inline float QuaternionDot( const CQuaternion &q1, const CQuaternion &q2 )
{
	return q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
}

// linear interpolation between two unit quaternions
CQuaternion QuaternionLerp( const CQuaternion &q1, const CQuaternion &q2, float t );
// linear interpolation between two unit quaternions, no check for theta > 90
CQuaternion QuaternionLerpNoInvert( const CQuaternion &q1, const CQuaternion &q2, float t );
// spherical linear interpolation between two unit quaternions
CQuaternion QuaternionSlerp( const CQuaternion &q1, const CQuaternion &q2, float t );
// this version of slerp, used by squad, does not check for theta > 90
CQuaternion QuaternionSlerpNoInvert( const CQuaternion &q1, const CQuaternion &q2, float t );
CQuaternion QuaternionSquad( const CQuaternion &p, const CQuaternion &a, const CQuaternion &b, const CQuaternion &q, float t );
CQuaternion QuaternionRotationArc( const CPoint3 &v0, const CPoint3 &v1 );

}
}

#endif // SPMATH_QUAT3_H