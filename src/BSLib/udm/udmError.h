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
	UDM_ERROR_OUT_OF_MEMORY = 1001, //内存用完
	UDM_ERROR_OUT_OF_UDMSOCKID,		//UdmSocketID 使用完
	UDM_ERROR_INVALID_UDMSOCKID,	//UdmSocketID 无效
	UDM_ERROR_INVALID_UDMSOCK,		//UdmSocket 无效
	UDM_ERROR_INVALID_STATE,		//udmSocket 状态无效
	UDM_ERROR_BIND_UDPADDR,			//绑定本地UDP IP和端口出错
	UDM_ERROR_INVALID_UDMSOCKOBJ,	//UdmSocket 无效对象
};

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDMERROR_H__



