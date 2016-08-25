#ifndef __BSLIB_NETWORK_NETINIT_H__
#define __BSLIB_NETWORK_NETINIT_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/network/baseDef.h>

#define RECV_BUFF 64*1024

//���ݰ� flag
#define GNET_PACKET_FLAG		0X80000000
//���ݰ�ѹ�� flag
#define GNET_PACKET_COMPRESS	0X40000000
//���ݰ�����flag
#define GNET_PACKET_ENCRYPT		0X20000000
//���ݰ�����
#define GNET_PACKET_NEXT		0X10000000

//���ݿ��Ʊ�־, &��, ��FF clear ����
#define GNET_PACKET_SIGN		0XFF000000

//���ݰ�max����
#define GNET_PACKET_LEN			0X00FFFFFF

#ifdef WIN32

namespace BSLib
{

namespace  Network
{

class CNetInit
{
public:
	BSLIB_SINGLETON_DECLARE(CNetInit);

public:
	CNetInit();
	~CNetInit();
};

}//Network

}//BSLib

#endif//WIN32

#endif//__BSLIB_NETWORK_NETINIT_H__

