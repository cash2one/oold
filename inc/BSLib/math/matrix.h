//////////////////////////////////////////////////////////////////////
//	created:	2014/11/20
//	filename: 	BSLib\math\matrix.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_MATH_MATRIX_H__
#define __BSLIB_MATH_MATRIX_H__

#include <BSLib/math/baseDef.h>
#include <BSLib/math/vector3.h>

namespace BSLib
{

namespace Math
{

class CMatrix
{
public:
	CMatrix() { setIdentity(); }
	CMatrix(const CMatrix& a_m) : m_00(a_m.m_00), m_01(a_m.m_01), m_02(a_m.m_02), m_03(a_m.m_03), m_10(a_m.m_10), m_11(a_m.m_11), m_12(a_m.m_12), m_13(a_m.m_13), m_20(a_m.m_20), m_21(a_m.m_21), m_22(a_m.m_22), m_23(a_m.m_23), m_30(a_m.m_30), m_31(a_m.m_31), m_32(a_m.m_32), m_33(a_m.m_33) {}
	CMatrix(Scalar a_m[16]) : m_00(a_m[0]), m_01(a_m[1]), m_02(a_m[2]), m_03(a_m[3]), m_10(a_m[4]), m_11(a_m[5]), m_12(a_m[6]), m_13(a_m[7]), m_20(a_m[8]), m_21(a_m[9]), m_22(a_m[10]), m_23(a_m[11]), m_30(a_m[12]), m_31(a_m[13]), m_32(a_m[14]), m_33(a_m[15]) {}
	CMatrix(Scalar a_00, Scalar a_01, Scalar a_02, Scalar a_03, 
		Scalar a_10, Scalar a_11, Scalar a_12, Scalar a_13, 
		Scalar a_20, Scalar a_21, Scalar a_22, Scalar a_23, 
		Scalar a_30, Scalar a_31, Scalar a_32, Scalar a_33) : m_00(a_00), m_01(a_01), m_02(a_02), m_03(a_03), m_10(a_10), m_11(a_11), m_12(a_12), m_13(a_13), m_20(a_20), m_21(a_21), m_22(a_22), m_23(a_23), m_30(a_30), m_31(a_31), m_32(a_32), m_33(a_33) {}


	void set(const CMatrix& a_m)
	{
		m_00 = a_m.m_00; m_01 = a_m.m_01; m_02 = a_m.m_02; m_03 = a_m.m_03;
		m_10 = a_m.m_10; m_11 = a_m.m_11; m_12 = a_m.m_12; m_13 = a_m.m_13;
		m_20 = a_m.m_20; m_21 = a_m.m_21; m_22 = a_m.m_22; m_23 = a_m.m_23;
		m_30 = a_m.m_30; m_31 = a_m.m_31; m_32 = a_m.m_32; m_33 = a_m.m_33;
	}

	void set(Scalar a_m[16])
	{
		m_00 = a_m[0]; m_01 = a_m[1]; m_02 = a_m[2]; m_03 = a_m[3];
		m_10 = a_m[4]; m_11 = a_m[5]; m_12 = a_m[6]; m_13 = a_m[7];
		m_20 = a_m[8]; m_21 = a_m[9]; m_22 = a_m[10]; m_23 = a_m[11];
		m_30 = a_m[12]; m_31 = a_m[13]; m_32 = a_m[14]; m_33 = a_m[15];
	}

	void set(Scalar a_00, Scalar a_01, Scalar a_02, Scalar a_03, 
		Scalar a_10, Scalar a_11, Scalar a_12, Scalar a_13, 
		Scalar a_20, Scalar a_21, Scalar a_22, Scalar a_23, 
		Scalar a_30, Scalar a_31, Scalar a_32, Scalar a_33)
	{
		m_00 = a_00; m_01 = a_01; m_02 = a_02; m_03 = a_03; 
		m_10 = a_10; m_11 = a_11; m_12 = a_12; m_13 = a_13;
		m_20 = a_20; m_21 = a_21; m_22 = a_22; m_23 = a_23; 
		m_30 = a_30; m_31 = a_31; m_32 = a_32; m_33 = a_33;
	}


	void setZero()
	{
		memset(m_m16, 0, 16 * sizeof(float));
	}

	void setIdentity()
	{
		setZero();
		m_00 = m_11 = m_22 = m_33 = 1.0f;
	}

	void setScale(const CVector3& a_scale)
	{
		setScale(a_scale.getX(), a_scale.getY(), a_scale.getZ());
	}

	void setScale(Scalar a_scaleX, Scalar a_scaleY, Scalar a_scaleZ)
	{
		m_00  = a_scaleX;	m_01  = 0.0f;		m_02  = 0.0f;
		m_10  = 0.0f;		m_11  = a_scaleY;	m_12  = 0.0f;
		m_20  = 0.0f;		m_21  = 0.0f;		m_22 = a_scaleZ;
		m_30 = 0.0f;		m_31 = 0.0f;		m_32 = 0.0f;
	}

	void scale(const CVector3& a_scale)
	{
		scale(a_scale.getX(), a_scale.getY(), a_scale.getZ());
	}

	void scale(Scalar a_scaleX, Scalar a_scaleY, Scalar a_scaleZ)
	{
		m_00 *= a_scaleX; m_01 *= a_scaleY; m_02 *= a_scaleZ;
		m_10 *= a_scaleX; m_11 *= a_scaleY; m_12 *= a_scaleZ;
		m_20 *= a_scaleX; m_21 *= a_scaleY; m_22 *= a_scaleZ;
	}

	CMatrix transpose() const
	{
		return CMatrix(m_00, m_10, m_20, m_30, m_01, m_11, m_21, m_31, m_02, m_12, m_22, m_32, m_03, m_13, m_23, m_33); 
	}

	void transposeSelf()
	{
		set(m_00, m_10, m_20, m_30, m_01, m_11, m_21, m_31, m_02, m_12, m_22, m_32, m_03, m_13, m_23, m_33); 
	}

	CMatrix operator +(const CMatrix &a_m) const
	{
		return CMatrix(m_00 + a_m.m_00, m_01 + a_m.m_01, m_02 + a_m.m_02, m_03 + a_m.m_03, 
					   m_10 + a_m.m_10, m_11 + a_m.m_11, m_12 + a_m.m_12, m_13 + a_m.m_13, 
					   m_20 + a_m.m_20, m_21 + a_m.m_21, m_22 + a_m.m_22, m_23 + a_m.m_23,
					   m_30 + a_m.m_30, m_31 + a_m.m_31, m_32 + a_m.m_22, m_33 + a_m.m_33);
	}

	CMatrix operator -(const CMatrix &a_m) const
	{
		return CMatrix(m_00 - a_m.m_00, m_01 - a_m.m_01, m_02 - a_m.m_02, m_03 - a_m.m_03, 
					   m_10 - a_m.m_10, m_11 - a_m.m_11, m_12 - a_m.m_12, m_13 - a_m.m_13, 
					   m_20 - a_m.m_20, m_21 - a_m.m_21, m_22 - a_m.m_22, m_23 - a_m.m_23,
			           m_30 - a_m.m_30, m_31 - a_m.m_31, m_32 - a_m.m_22, m_33 - a_m.m_33);
	}

	CMatrix operator *(const CMatrix &a_m) const
	{
		Scalar dest[16];
		dest[0]  = m_00*a_m.m_00 + m_01*a_m.m_10 + m_02 * a_m.m_20  + m_03 *a_m.m_30;
		dest[1]  = m_00*a_m.m_01 + m_01*a_m.m_11 + m_02 * a_m.m_21  + m_03 *a_m.m_31;
		dest[2]  = m_00*a_m.m_02 + m_01*a_m.m_12 + m_02 * a_m.m_22  + m_03 *a_m.m_32;
		dest[3]  = m_00*a_m.m_03 + m_01*a_m.m_13 + m_02 * a_m.m_23  + m_03 *a_m.m_33;
		
		dest[4]  = m_10*a_m.m_00 + m_11*a_m.m_10 + m_12 * a_m.m_20  + m_13 *a_m.m_30;
		dest[5]  = m_10*a_m.m_01 + m_11*a_m.m_11 + m_12 * a_m.m_21  + m_13 *a_m.m_31;
		dest[6]  = m_10*a_m.m_02 + m_11*a_m.m_12 + m_12 * a_m.m_22  + m_13 *a_m.m_32;
		dest[7]  = m_10*a_m.m_03 + m_11*a_m.m_13 + m_12 * a_m.m_23  + m_13 *a_m.m_33;

		dest[8]  = m_20*a_m.m_00 + m_21*a_m.m_10 + m_22 * a_m.m_20  + m_23 *a_m.m_30;
		dest[9]  = m_20*a_m.m_01 + m_21*a_m.m_11 + m_22 * a_m.m_21  + m_23 *a_m.m_31;
		dest[10]  = m_20*a_m.m_02 + m_21*a_m.m_12 + m_22 * a_m.m_22  + m_23 *a_m.m_32;
		dest[11]  = m_20*a_m.m_03 + m_21*a_m.m_13 + m_22 * a_m.m_23  + m_23 *a_m.m_33;

		dest[12]  = m_30*a_m.m_00 + m_31*a_m.m_10 + m_32 * a_m.m_20  + m_33 *a_m.m_30;
		dest[13]  = m_30*a_m.m_01 + m_31*a_m.m_11 + m_32 * a_m.m_21  + m_33 *a_m.m_31;
		dest[14]  = m_30*a_m.m_02 + m_31*a_m.m_12 + m_32 * a_m.m_22  + m_33 *a_m.m_32;
		dest[15]  = m_30*a_m.m_03 + m_31*a_m.m_13 + m_32 * a_m.m_23  + m_33 *a_m.m_33;

		return CMatrix(dest);
	}

	CMatrix operator *(Scalar a_s) const
	{
		return CMatrix(	m_00 * a_s, m_01 * a_s, m_02 * a_s, m_03 * a_s, 
						m_10 * a_s, m_11 * a_s, m_12 * a_s, m_13 * a_s, 
						m_20 * a_s, m_21 * a_s, m_22 * a_s, m_23 * a_s,
						m_30 * a_s, m_31 * a_s, m_32 * a_s, m_33 * a_s);
	}

	CMatrix operator /(Scalar a_s) const
	{
		return CMatrix(	m_00 / a_s, m_01 / a_s, m_02 / a_s, m_03 / a_s, 
						m_10 / a_s, m_11 / a_s, m_12 / a_s, m_13 / a_s, 
						m_20 / a_s, m_21 / a_s, m_22 / a_s, m_23 / a_s,
						m_30 / a_s, m_31 / a_s, m_32 / a_s, m_33 / a_s);
	}

	CMatrix& operator +=(const CMatrix &a_m)
	{
		m_00 += a_m.m_00; m_01 += a_m.m_01; m_02 += a_m.m_02; m_03 += a_m.m_03;
		m_10 += a_m.m_10; m_11 += a_m.m_11; m_12 += a_m.m_12; m_13 += a_m.m_13; 
		m_20 += a_m.m_20; m_21 += a_m.m_21; m_22 += a_m.m_22; m_23 += a_m.m_23;
		m_30 += a_m.m_30; m_31 += a_m.m_31; m_32 += a_m.m_22; m_33 += a_m.m_33;
		return *this;
	}

	CMatrix& operator -=(const CMatrix &a_m)
	{
		m_00 -= a_m.m_00; m_01 -= a_m.m_01; m_02 -= a_m.m_02; m_03 -= a_m.m_03;
		m_10 -= a_m.m_10; m_11 -= a_m.m_11; m_12 -= a_m.m_12; m_13 -= a_m.m_13; 
		m_20 -= a_m.m_20; m_21 -= a_m.m_21; m_22 -= a_m.m_22; m_23 -= a_m.m_23;
		m_30 -= a_m.m_30; m_31 -= a_m.m_31; m_32 -= a_m.m_22; m_33 -= a_m.m_33;
		return *this;
	}

	CMatrix& operator *=(const CMatrix &a_m)
	{
		Scalar dest[16];
		dest[0]  = m_00*a_m.m_00 + m_01*a_m.m_10 + m_02 * a_m.m_20  + m_03 *a_m.m_30;
		dest[1]  = m_00*a_m.m_01 + m_01*a_m.m_11 + m_02 * a_m.m_21  + m_03 *a_m.m_31;
		dest[2]  = m_00*a_m.m_02 + m_01*a_m.m_12 + m_02 * a_m.m_22  + m_03 *a_m.m_32;
		dest[3]  = m_00*a_m.m_03 + m_01*a_m.m_13 + m_02 * a_m.m_23  + m_03 *a_m.m_33;

		dest[4]  = m_10*a_m.m_00 + m_11*a_m.m_10 + m_12 * a_m.m_20  + m_13 *a_m.m_30;
		dest[5]  = m_10*a_m.m_01 + m_11*a_m.m_11 + m_12 * a_m.m_21  + m_13 *a_m.m_31;
		dest[6]  = m_10*a_m.m_02 + m_11*a_m.m_12 + m_12 * a_m.m_22  + m_13 *a_m.m_32;
		dest[7]  = m_10*a_m.m_03 + m_11*a_m.m_13 + m_12 * a_m.m_23  + m_13 *a_m.m_33;

		dest[8]  = m_20*a_m.m_00 + m_21*a_m.m_10 + m_22 * a_m.m_20  + m_23 *a_m.m_30;
		dest[9]  = m_20*a_m.m_01 + m_21*a_m.m_11 + m_22 * a_m.m_21  + m_23 *a_m.m_31;
		dest[10]  = m_20*a_m.m_02 + m_21*a_m.m_12 + m_22 * a_m.m_22  + m_23 *a_m.m_32;
		dest[11]  = m_20*a_m.m_03 + m_21*a_m.m_13 + m_22 * a_m.m_23  + m_23 *a_m.m_33;

		dest[12]  = m_30*a_m.m_00 + m_31*a_m.m_10 + m_32 * a_m.m_20  + m_33 *a_m.m_30;
		dest[13]  = m_30*a_m.m_01 + m_31*a_m.m_11 + m_32 * a_m.m_21  + m_33 *a_m.m_31;
		dest[14]  = m_30*a_m.m_02 + m_31*a_m.m_12 + m_32 * a_m.m_22  + m_33 *a_m.m_32;
		dest[15]  = m_30*a_m.m_03 + m_31*a_m.m_13 + m_32 * a_m.m_23  + m_33 *a_m.m_33;
		set(dest);
		return *this;
	}
	
	CMatrix& operator *=(Scalar a_s)
	{
		m_00 *= a_s; m_01 *= a_s; m_02 *= a_s; m_03 *= a_s;
		m_10 *= a_s; m_11 *= a_s; m_12 *= a_s; m_13 *= a_s; 
		m_20 *= a_s; m_21 *= a_s; m_22 *= a_s; m_23 *= a_s;
		m_30 *= a_s; m_31 *= a_s; m_32 *= a_s; m_33 *= a_s;
		return *this;
	}

	CMatrix& operator /=(Scalar a_s)
	{
		m_00 /= a_s; m_01 /= a_s; m_02 /= a_s; m_03 /= a_s;
		m_10 /= a_s; m_11 /= a_s; m_12 /= a_s; m_13 /= a_s; 
		m_20 /= a_s; m_21 /= a_s; m_22 /= a_s; m_23 /= a_s;
		m_30 /= a_s; m_31 /= a_s; m_32 /= a_s; m_33 /= a_s;
		return *this;
	}

	bool operator ==(const CMatrix &a_m) const
	{
		for (int i=0; i<16; ++i) {
			if (m_m16[i] != a_m.m_m16[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator !=(const CMatrix &a_m) const
	{
		return !(operator ==(a_m));
	}


private:
	union
	{
		struct
		{
			Scalar m_00, m_01, m_02, m_03;
			Scalar m_10, m_11, m_12, m_13;
			Scalar m_20, m_21, m_22, m_23;
			Scalar m_30, m_31, m_32, m_33;
		};
		struct
		{
			Scalar m_row0[4];
			Scalar m_row1[4];
			Scalar m_row2[4];
			Scalar m_row3[4];
		};
		Scalar m_m[4][4];
		Scalar m_m16[16];
	};
};

}//Math

}//BSLib

#endif//__BSLIB_MATH_MATRIX_H__