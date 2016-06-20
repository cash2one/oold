//////////////////////////////////////////////////////////////////////
//	created:	2014/07/18
//	filename: 	src\BSLib\framework\message\msgFactory.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/framework/message/msgFactory.h>

namespace BSLib
{

namespace Framework
{

BSLIB_SINGLETON_DEFINE(CMsgFactory)

CMsgFactory::CMsgFactory()
{
	;
}

CMsgFactory::~CMsgFactory()
{
	;
}

void CMsgFactory::clear()
{
	BSLib::Utility::CHashMap< uint32, BSLib::Utility::CFunction<CMessage*>* >::iterator it_cmsg = m_msgCreateCMsgHashMap.begin();
	for (; it_cmsg != m_msgCreateCMsgHashMap.end(); ++it_cmsg){
		BSLib::Utility::CFunction<CMessage*>* fun = it_cmsg->second;
		if (fun != NULL) {
			BSLIB_SAFE_DELETE(fun);
		}
	}
	m_msgCreateCMsgHashMap.clear();
}

void CMsgFactory::registerCreateCMsgFun(const BSLib::uint32 msgID, CreateCMessageFun fun)
{
	BSLib::Utility::CFunction<CMessage*> funTemp(fun);
	registerCreateCMsgFun(msgID, funTemp);
}

void CMsgFactory::registerCreateCMsgFun(const BSLib::uint32 msgID, BSLib::Utility::CFunction<CMessage*>& a_fun)
{
	BSLib::Utility::CFunction<CMessage*>* fun = a_fun.clone();
	if (fun == NULL) {
		return;
	}
	m_msgCreateCMsgHashMap.setValue(msgID, fun);
}

CMessage* CMsgFactory::createCMessage(const BSLib::uint32 msgID)
{
	BSLib::Utility::CFunction<CMessage*>* fun = NULL;
	m_msgCreateCMsgHashMap.getValue(msgID, fun);
	if (fun == NULL) {
		return NULL;
	}
	return (*fun)();
}

}//Framework

}//BSLib