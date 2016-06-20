//////////////////////////////////////////////////////////////////////
//	created:	2012/07/20
//	filename:	src\BSLib\framework\message\msgExec.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/framework/message/msgExec.h>

namespace BSLib
{

namespace Framework
{

CMsgExec::CMsgExec(MessageExecFun execFun)
: m_execFun(NULL)
{
	m_execFun = new BSLib::Utility::CFunction<void, SMsgLabel*, SMessage*>(execFun);
}

CMsgExec::CMsgExec(const BSLib::Utility::CFunction<void, SMsgLabel*, SMessage*>& execFun)
{
	if (m_execFun != NULL) {
		BSLIB_SAFE_DELETE(m_execFun);
	}
	m_execFun = execFun.clone();
}

CMsgExec::~CMsgExec()
{
	if (m_execFun != NULL) {
		BSLIB_SAFE_DELETE(m_execFun);
	}
}

void CMsgExec::executeMessage(SMsgLabel* msgLabel, SMessage* msg)
{
	if (m_execFun == NULL) {
		return ;
	}
	(*m_execFun)(msgLabel, msg);
}

}//Framework

}//BSLib

