#include "encrypt/mydes.h"
#include <BSLib/utility/encrypt/encryDes.h>

extern void DES_random_key(DES_cblock *ret);
extern void DES_set_key(const_DES_cblock *key, DES_key_schedule *schedule);
extern void DES_encrypt1(DES_LONG *data, DES_key_schedule *ks,t_DES_SPtrans * sp, int enc);
extern t_DES_SPtrans MyDES_SPtrans;

namespace BSLib
{

namespace Utility
{

CEncryDes::CEncryDes()
: m_key(NULL)
{
	;
}

CEncryDes::~CEncryDes()
{
	DES_key_schedule* key = (DES_key_schedule*)m_key;
	if (key != NULL) {
		BSLIB_SAFE_DELETE(key);
		m_key = NULL;
	}
}

void CEncryDes::randomKey(DES_cblock* a_key)
{
	::DES_random_key(a_key);
}

void CEncryDes::setKey(const_DES_cblock* a_key)
{
	if (m_key == NULL) {
		m_key = new DES_key_schedule();
		if (m_key == NULL) {
			return ;
		}
	}
	::DES_set_key(a_key, (DES_key_schedule*)m_key);
}

int CEncryDes::encrypt(BSLib::uint8 a_data[], BSLib::int32 a_len)
{
	if (m_key == NULL) {
		return -1;
	}
	if (a_data == NULL) {
		return -1;
	}

	BSLib::int32 offset = 0;
	while (offset <= a_len-8) {
		DES_encrypt1((DES_LONG*)(a_data+offset), (DES_key_schedule*)m_key, &MyDES_SPtrans, true);
		offset += 8;
	}

	return offset;
}

int CEncryDes::decrypt(BSLib::uint8 a_data[], BSLib::int32 a_len)
{
	if (m_key == NULL) {
		return -1;
	}
	if (a_data == NULL) {
		return -1;
	}

	BSLib::int32 offset = 0;
	while (offset <= a_len-8) {
		DES_encrypt1((DES_LONG*)(a_data+offset), (DES_key_schedule*)m_key, &MyDES_SPtrans, false);
		offset += 8;
	}

	return offset;
}

}//Utility

}//BSLib
