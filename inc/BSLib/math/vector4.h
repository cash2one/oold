//////////////////////////////////////////////////////////////////////
//	created:	2014/11/20
//	filename: 	BSLib\math\vector4.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_MATH_VECTOR4_H__
#define __BSLIB_MATH_VECTOR4_H__

#include <BSLib/math/baseDef.h>

namespace BSLib
{

namespace Math
{

class CVector4
{
public:
	CVector4() : m_x(0), m_y(0), m_z(0), m_w(0) {}
	CVector4(Scalar a_x, Scalar a_y, Scalar a_z, Scalar a_w) : m_x(a_x), m_y(a_y), m_z(a_z), m_w(a_w) {}
	CVector4(Scalar a_v[4]) : m_x(a_v[0]), m_y(a_v[1]), m_z(a_v[2]), m_w(a_v[3]) {}
	CVector4(const CVector4& a_v) : m_x(a_v.m_x), m_y(a_v.m_y), m_z(a_v.m_z), m_w(a_v.m_w) {}

	Scalar getX() const { return m_x; }
	Scalar getY() const { return m_y; }
	Scalar getZ() const { return m_z; }
	Scalar getW() const { return m_w; }

	void set(Scalar a_x, Scalar a_y, Scalar a_z, Scalar a_w) { m_x = a_x; m_y = a_y; m_z = a_z; m_w = a_w; }
	void set(const Scalar a_v[4]) { m_x = a_v[0]; m_y = a_v[1]; m_z = a_v[2]; m_w = a_v[3]; }
	void set(const CVector4& a_v) { m_x = a_v.m_x; m_y = a_v.m_y; m_z = a_v.m_z; m_w = a_v.m_w; }
	void setX(Scalar a_x) { m_x = a_x; }
	void setY(Scalar a_y) { m_y = a_y; }
	void setZ(Scalar a_z) { m_z = a_z; }
	void setW(Scalar a_w) { m_w = a_w; }

	CVector4& operator +=(const CVector4& a_v)
	{
		m_x += a_v.m_x;
		m_y += a_v.m_y;
		m_z += a_v.m_z;
		m_w += a_v.m_w;
		return *this;
	}

	CVector4& operator -=(const CVector4& a_v)
	{
		m_x -= a_v.m_x;
		m_y -= a_v.m_y;
		m_z -= a_v.m_z;
		m_w -= a_v.m_w;
		return *this;
	}

	CVector4& operator *=(const CVector4& a_v)
	{
		m_x *= a_v.m_x;
		m_y *= a_v.m_y;
		m_z *= a_v.m_z;
		m_w *= a_v.m_w;
		return *this;
	}

	CVector4& operator /=(const CVector4& a_v)
	{
		m_x /= a_v.m_x;
		m_y /= a_v.m_y;
		m_z /= a_v.m_z;
		m_w /= a_v.m_w;
		return *this;
	}

	CVector4& operator *=(Scalar a_s)
	{
		m_x *= a_s;
		m_y *= a_s;
		m_z *= a_s;
		m_w += a_s;
		return *this;
	}

	CVector4& operator /=(Scalar a_s)
	{
		m_x /= a_s;
		m_y /= a_s;
		m_z /= a_s;
		m_w /= a_s;
		return *this;
	}

	CVector4& operator =(const CVector4& a_v)
	{
		m_x = a_v.m_x;
		m_y = a_v.m_y;
		m_z = a_v.m_z;
		m_w = a_v.m_w;
		return *this;
	}

	CVector4 operator +(const CVector4& a_v) const
	{
		return CVector4(m_x + a_v.m_x, m_y + a_v.m_y, m_z + a_v.m_z, m_w + a_v.m_w);
	}

	CVector4 operator -(const CVector4& a_v) const
	{
		return CVector4(m_x - a_v.m_x, m_y - a_v.m_y, m_z - a_v.m_z, m_w - a_v.m_w);
	}

	CVector4 operator *(const CVector4& a_v) const
	{
		return CVector4(m_x * a_v.m_x, m_y * a_v.m_y, m_z * a_v.m_z, m_w * a_v.m_w);
	}

	CVector4 operator /(const CVector4& a_v) const
	{
		return CVector4(m_x / a_v.m_x, m_y / a_v.m_y, m_z / a_v.m_z, m_w / a_v.m_w);
	}

	CVector4 operator *(Scalar a_s) const
	{
		return CVector4(m_x * a_s, m_y * a_s, m_z * a_s, m_w * a_s);
	}

	CVector4 operator /(Scalar a_s) const
	{
		return CVector4(m_x / a_s, m_y / a_s, m_z / a_s, m_w / a_s);
	}

	bool operator !=(const CVector4 &a_v) const
	{
		return (m_x != a_v.m_x) || (m_y != a_v.m_y) || (m_z != a_v.m_z) || (m_w != a_v.m_w);
	}

	bool operator ==(const CVector4 &a_v) const
	{
		return (m_x == a_v.m_x) && (m_y == a_v.m_y) && (m_z == a_v.m_z) && (m_w == a_v.m_w);
	}

	bool isZero() const     
	{ 
		return (m_x == 0) && (m_y == 0) && (m_z == 0)  && (m_w == 0);
	}

	bool isNearZero() const     
	{ 
		return (fabs(m_x) <= GMH_EPSILON) && (fabs(m_y) <= GMH_EPSILON) && (fabs(m_z) <= GMH_EPSILON) && (fabs(m_w) <= GMH_EPSILON); 
	}

	Scalar length() const
	{
		return sqrtf(lengthSquare());
	}

	Scalar lengthSquare() const 
	{
		return m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w;
	}

	Scalar dotProduct(const CVector4 &a_v) const
	{
		return m_x * a_v.m_x + m_y + a_v.m_y + m_z * a_v.m_z + m_w * a_v.m_w;
	}

	void normalize();

	Scalar angle(const CVector4 &a_v) const;

protected:

private:
	union
	{
		struct
		{
			Scalar m_x;
			Scalar m_y;
			Scalar m_z;
			Scalar m_w;
		};
		Scalar m_v[4];
	};
};

}//Math

}//BSLib

#endif//__BSLIB_MATH_VECTOR3_H__