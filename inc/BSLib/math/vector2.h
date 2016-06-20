//////////////////////////////////////////////////////////////////////
//	created:	2014/11/20
//	filename: 	BSLib\math\vector2.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_MATH_VECTOR2_H__
#define __BSLIB_MATH_VECTOR2_H__

#include <BSLib/math/baseDef.h>

namespace BSLib
{

namespace Math
{

class CVector2
{
public:
	CVector2() : m_x(0), m_y(0) {}
	CVector2(Scalar a_x, Scalar a_y) : m_x(a_x), m_y(a_y) {}
	CVector2(const Scalar a_v[2]) : m_x(a_v[0]), m_y(a_v[1]) {}
	CVector2(const CVector2& a_v) : m_x(a_v.m_x), m_y(a_v.m_y) {}

	Scalar getX() const { return m_x; }
	Scalar getY() const { return m_y; }

	void set(Scalar a_x, Scalar a_y) { m_x = a_x; m_y = a_y; }
	void set(const Scalar a_v[2]) { m_x = a_v[0]; m_y = a_v[1]; }
	void set(const CVector2& a_v) { m_x = a_v.m_x; m_y = a_v.m_y;}
	void setX(Scalar a_x) { m_x = a_x; }
	void setY(Scalar a_y) { m_y = a_y; }

	CVector2& operator +=(const CVector2& a_v)
	{
		m_x += a_v.m_x;
		m_y += a_v.m_y;
		return *this;
	}

	CVector2& operator -=(const CVector2& a_v)
	{
		m_x -= a_v.m_x;
		m_y -= a_v.m_y;
		return *this;
	}

	CVector2& operator *=(const CVector2& a_v)
	{
		m_x *= a_v.m_x;
		m_y *= a_v.m_y;
		return *this;
	}

	CVector2& operator /=(const CVector2& a_v)
	{
		m_x /= a_v.m_x;
		m_y /= a_v.m_y;
		return *this;
	}

	CVector2& operator *=(Scalar a_s)
	{
		m_x *= a_s;
		m_y *= a_s;
		return *this;
	}

	CVector2& operator /=(Scalar a_s)
	{
		m_x /= a_s;
		m_y /= a_s;
		return *this;
	}

	CVector2& operator =(const CVector2& a_v)
	{
		m_x = a_v.m_x;
		m_y = a_v.m_y;
		return *this;
	}

	CVector2 operator +(const CVector2& a_v) const
	{
		return CVector2(m_x + a_v.m_x, m_y + a_v.m_y);
	}

	CVector2 operator -=(const CVector2& a_v) const
	{
		return CVector2(m_x - a_v.m_x, m_y - a_v.m_y);
	}

	CVector2 operator *=(const CVector2& a_v) const
	{
		return CVector2(m_x * a_v.m_x, m_y * a_v.m_y);
	}

	CVector2 operator /=(const CVector2& a_v) const
	{
		return CVector2(m_x / a_v.m_x, m_y / a_v.m_y);
	}

	CVector2 operator *=(Scalar a_s) const
	{
		return CVector2(m_x * a_s, m_y * a_s);
	}

	CVector2 operator /=(Scalar a_s) const
	{
		return CVector2(m_x / a_s, m_y / a_s);
	}

	bool operator !=(const CVector2 &a_v) const
	{
		return (m_x != a_v.m_x) || (m_y != a_v.m_y);
	}

	bool operator ==(const CVector2 &a_v) const
	{
		return (m_x == a_v.m_x) && (m_y == a_v.m_y);
	}

	bool isZero() const     
	{ 
		return (m_x == 0) && (m_y == 0);
	}

	bool isNearZero() const     
	{ 
		return (fabs(m_x) <= GMH_EPSILON) && (fabs(m_y) <= GMH_EPSILON); 
	}

	Scalar length() const
	{
		return sqrtf(lengthSquare());
	}

	Scalar lengthSquare() const 
	{
		return m_x * m_x + m_y * m_y;
	}

	Scalar dotProduct(const CVector2 &a_v) const
	{
		return m_x * a_v.m_x + m_y + a_v.m_y;
	}

	Scalar crossProduct(const CVector2 &a_v) const
	{
		return m_x * a_v.m_y - m_y * a_v.m_x;
	}

	void normalize();

	Scalar angle(const CVector2 &a_v) const;

private:
	union
	{
		struct
		{
			Scalar m_x;
			Scalar m_y;
		};
		Scalar m_v[2];
	};
};

}//Math

}//BSLib

#endif//__BSLIB_MATH_VECTOR2_H__