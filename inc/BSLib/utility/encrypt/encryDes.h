//////////////////////////////////////////////////////////////////////
//	created:	2013/01/31
//	filename: 	BSLib\utility\encrypt\encryDes.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_ENCRYPT_ENCRYDES_H__
#define __BSLIB_UTILITY_ENCRYPT_ENCRYDES_H__

#include <BSLib/utility/baseDef.h>

typedef unsigned char DES_cblock[8];
typedef unsigned char const_DES_cblock[8];

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CEncryDes
{
public:
	CEncryDes();
	~CEncryDes();

	void randomKey(DES_cblock* a_key);
	void setKey(const_DES_cblock* a_key);

	int encrypt(BSLib::uint8 a_data[], BSLib::int32 a_len);
	int decrypt(BSLib::uint8 a_data[], BSLib::int32 a_len);

private:
	void* m_key;
};

}//Utility

}//BSLib

#endif // __BSLIB_UTILITY_ENCRYPT_ENCRYDES_H__