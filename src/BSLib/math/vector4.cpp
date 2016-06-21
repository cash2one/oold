#include <BSLib/math/vector4.h>

namespace BSLib
{

namespace Math
{

void CVector4::normalize()
{
	Scalar len = length();
	if (len == 0) {
		return;
	}
	Scalar invLen = 1.0f / len;
	m_x *= invLen;
	m_y *= invLen;
	m_z *= invLen;
	m_w *= invLen;
}

Scalar CVector4::angle(const CVector4 &a_v) const
{
	Scalar l = length() * a_v.length();
	if (l == 0){
		return 0;
	}
	Scalar d = dotProduct(a_v) / l;
	if (d > 1.0f){
		d = 1.0f;
	} else if (d < -1.0f) {
		d = -1.0f;
	}
	return acosf(d);
}

}//Math

}//BSLib
