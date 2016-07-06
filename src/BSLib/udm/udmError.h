#ifndef __BSLIB_UDM_UDMERROR_H__
#define __BSLIB_UDM_UDMERROR_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/thread/mutex.h>
#include "udmSocketInfo.h"

#define BSLIB_UDM_SOCKET_MAX BSLIB_UINT16_MAX

namespace BSLib
{

namespace UDM
{

enum EUdmErrorID
{
	UDM_ERROR_OUT_OF_MEMORY = 1001, //�ڴ�����
	UDM_ERROR_OUT_OF_UDMSOCKID,		//UdmSocketID ʹ����
	UDM_ERROR_INVALID_UDMSOCKID,	//UdmSocketID ��Ч
	UDM_ERROR_INVALID_UDMSOCK,		//UdmSocket ��Ч
	UDM_ERROR_INVALID_STATE,		//udmSocket ״̬��Ч
	UDM_ERROR_BIND_UDPADDR,			//�󶨱���UDP IP�Ͷ˿ڳ���
	UDM_ERROR_INVALID_UDMSOCKOBJ,	//UdmSocket ��Ч����
};

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDMERROR_H__



