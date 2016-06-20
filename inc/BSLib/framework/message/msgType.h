//////////////////////////////////////////////////////////////////////
//	created:	2012/09/09
//	filename: 	BSLib\framework\message\msgType.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_FRAMEWORK_MESSAGE_MSGTYPE_H__
#define __BSLIB_FRAMEWORK_MESSAGE_MSGTYPE_H__

#include <BSLib/framework/baseDef.h>

namespace BSLib
{

//��Ϣ���Ͷ���
enum EMsgType
{
	//framework��Ϣ���Ͷ���
	EMT_FRAMEWORK = 1,
	EMT_P2P = 2,
	EMT_SAMPLE,
	//////////////////////////////////////////////////////////////////////////
	//��Ϸ�߼���Ϣ����
	//////////////////////////////////////////////////////////////////////////
	EMT_EXTEND,
};

}//BSLib

#define BSLIB_MSG_BUFF_MAX (1024 * 64)

#define BSLIB_DEFINE_OBJECT(type, para) \
	char __tmepBuff##para [BSLIB_MSG_BUFF_MAX+256]={0};\
	para = (type*)__tmepBuff##para;\
	new (static_cast<void*>(para)) type();

#endif//__BSLIB_FRAMEWORK_MESSAGE_MSGTYPE_H__

