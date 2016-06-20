//////////////////////////////////////////////////////////////////////
//	created:	2014/08/24
//	filename:	BSLib\math\vector3.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_MATH_VECTOR3_H__
#define __BSLIB_MATH_VECTOR3_H__

#include <BSLib/math/baseDef.h>

namespace BSLib
{

namespace Math
{

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

struct SVector3
{
	Scalar m_x;
	Scalar m_y;
	Scalar m_z;;
};

#ifdef WIN32
#pragma pack (pop) 
#else
#pragma pack ()
#endif

class CVector3
{
public:
	CVector3() : m_x(0), m_y(0), m_z(0) {}
	CVector3(Scalar a_x, Scalar a_y, Scalar a_z) : m_x(a_x), m_y(a_y), m_z(a_z) {}
	CVector3(Scalar a_v[3]) : m_x(a_v[0]), m_y(a_v[1]), m_z(a_v[2]) {}
	CVector3(const CVector3& a_v) : m_x(a_v.m_x), m_y(a_v.m_y), m_z(a_v.m_z) {}
	CVector3(const SVector3& a_v) : m_x(a_v.m_x), m_y(a_v.m_y), m_z(a_v.m_z) {}
	
	Scalar getX() const { return m_x; }
	Scalar getY() const { return m_y; }
	Scalar getZ() const { return m_z; }

	void set(Scalar a_x, Scalar a_y, Scalar a_z) { m_x = a_x; m_y = a_y; m_z = a_z; }
	void set(const Scalar a_v[3]) { m_x = a_v[0]; m_y = a_v[1]; m_z = a_v[2]; }
	void set(const CVector3& a_v) { m_x = a_v.m_x; m_y = a_v.m_y; m_z = a_v.m_z; }
	void set(const SVector3& a_v) { m_x = a_v.m_x; m_y = a_v.m_y; m_z = a_v.m_z; }
	void setX(Scalar a_x) { m_x = a_x; }
	void setY(Scalar a_y) { m_y = a_y; }
	void setZ(Scalar a_z) { m_z = a_z; }

	CVector3& operator +=(const CVector3& a_v)
	{
		m_x += a_v.m_x;
		m_y += a_v.m_y;
		m_z += a_v.m_z;
		return *this;
	}

	CVector3& operator -=(const CVector3& a_v)
	{
		m_x -= a_v.m_x;
		m_y -= a_v.m_y;
		m_z -= a_v.m_z;
		return *this;
	}

	CVector3& operator *=(const CVector3& a_v)
	{
		m_x *= a_v.m_x;
		m_y *= a_v.m_y;
		m_z *= a_v.m_z;
		return *this;
	}

	CVector3& operator /=(const CVector3& a_v)
	{
		m_x /= a_v.m_x;
		m_y /= a_v.m_y;
		m_z /= a_v.m_z;
		return *this;
	}

	CVector3& operator +=(const SVector3& a_v)
	{
		m_x += a_v.m_x;
		m_y += a_v.m_y;
		m_z += a_v.m_z;
		return *this;
	}

	CVector3& operator -=(const SVector3& a_v)
	{
		m_x -= a_v.m_x;
		m_y -= a_v.m_y;
		m_z -= a_v.m_z;
		return *this;
	}

	CVector3& operator *=(const SVector3& a_v)
	{
		m_x *= a_v.m_x;
		m_y *= a_v.m_y;
		m_z *= a_v.m_z;
		return *this;
	}

	CVector3& operator /=(const SVector3& a_v)
	{
		m_x /= a_v.m_x;
		m_y /= a_v.m_y;
		m_z /= a_v.m_z;
		return *this;
	}

	CVector3& operator *=(Scalar a_s)
	{
		m_x *= a_s;
		m_y *= a_s;
		m_z *= a_s;
		return *this;
	}

	CVector3& operator /=(Scalar a_s)
	{
		m_x /= a_s;
		m_y /= a_s;
		m_z /= a_s;
		return *this;
	}

	CVector3& operator =(const CVector3& a_v)
	{
		m_x = a_v.m_x;
		m_y = a_v.m_y;
		m_z = a_v.m_z;
		return *this;
	}

	CVector3& operator =(const SVector3& a_v)
	{
		m_x = a_v.m_x;
		m_y = a_v.m_y;
		m_z = a_v.m_z;
		return *this;
	}

	CVector3 operator +(const CVector3& a_v) const
	{
		return CVector3(m_x + a_v.m_x, m_y + a_v.m_y, m_z + a_v.m_z);
	}

	CVector3 operator -(const CVector3& a_v) const
	{
		return CVector3(m_x - a_v.m_x, m_y - a_v.m_y, m_z - a_v.m_z);
	}

	CVector3 operator *(const CVector3& a_v) const
	{
		return CVector3(m_x * a_v.m_x, m_y * a_v.m_y, m_z * a_v.m_z);
	}

	CVector3 operator /(const CVector3& a_v) const
	{
		return CVector3(m_x / a_v.m_x, m_y / a_v.m_y, m_z / a_v.m_z);
	}

	CVector3 operator *(Scalar a_s) const
	{
		return CVector3(m_x * a_s, m_y * a_s, m_z * a_s);
	}

	CVector3 operator /(Scalar a_s) const
	{
		return CVector3(m_x / a_s, m_y / a_s, m_z / a_s);
	}

	bool operator !=(const CVector3 &a_v) const
	{
		return (m_x != a_v.m_x) || (m_y != a_v.m_y) || (m_z != a_v.m_z);
	}

	bool operator ==(const CVector3 &a_v) const
	{
		return (m_x == a_v.m_x) && (m_y == a_v.m_y) && (m_z == a_v.m_z);
	}

	CVector3 operator +(const SVector3& a_v) const
	{
		return CVector3(m_x + a_v.m_x, m_y + a_v.m_y, m_z + a_v.m_z);
	}

	CVector3 operator -(const SVector3& a_v) const
	{
		return CVector3(m_x - a_v.m_x, m_y - a_v.m_y, m_z - a_v.m_z);
	}

	CVector3 operator *(const SVector3& a_v) const
	{
		return CVector3(m_x * a_v.m_x, m_y * a_v.m_y, m_z * a_v.m_z);
	}

	CVector3 operator /(const SVector3& a_v) const
	{
		return CVector3(m_x / a_v.m_x, m_y / a_v.m_y, m_z / a_v.m_z);
	}

	bool operator !=(const SVector3 &a_v) const
	{
		return (m_x != a_v.m_x) || (m_y != a_v.m_y) || (m_z != a_v.m_z);
	}

	bool operator ==(const SVector3 &a_v) const
	{
		return (m_x == a_v.m_x) && (m_y == a_v.m_y) && (m_z == a_v.m_z);
	}

	bool isZero() const     
	{ 
		return (m_x == 0) && (m_y == 0) && (m_z == 0);
	}

	bool isNearZero() const     
	{ 
		return (fabs(m_x) <= GMH_EPSILON) && (fabs(m_y) <= GMH_EPSILON) && (fabs(m_z) <= GMH_EPSILON); 
	}

	Scalar length() const
	{
		return sqrtf(lengthSquare());
	}

	Scalar lengthSquare() const 
	{
		return m_x * m_x + m_y * m_y + m_z * m_z;
	}

	Scalar dotProduct(const CVector3 &a_v) const
	{
		return m_x * a_v.m_x + m_y + a_v.m_y + m_z * a_v.m_z;
	}

	CVector3 crossProduct(const CVector3 &a_v) const
	{
		return CVector3(m_y * a_v.m_z - m_z * a_v.m_y, m_z * a_v.m_x - m_x * a_v.m_z, m_x * a_v.m_y - m_y * a_v.m_x);
	}

	Scalar dotProduct(const SVector3 &a_v) const
	{
		return m_x * a_v.m_x + m_y + a_v.m_y + m_z * a_v.m_z;
	}

	CVector3 crossProduct(const SVector3 &a_v) const
	{
		return CVector3(m_y * a_v.m_z - m_z * a_v.m_y, m_z * a_v.m_x - m_x * a_v.m_z, m_x * a_v.m_y - m_y * a_v.m_x);
	}

	void normalize();

	Scalar angle(const CVector3 &a_v) const;

	Scalar angle(const SVector3 &a_v) const
	{
		CVector3 v(a_v);
		return angle(v);
	}

protected:

private:
	union
	{
		struct
		{
			Scalar m_x;
			Scalar m_y;
			Scalar m_z;
		};
		Scalar m_v[3];
	};
};

}//Math

}//BSLib

#endif//__BSLIB_MATH_VECTOR3_H__