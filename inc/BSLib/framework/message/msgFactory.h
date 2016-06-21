#ifndef __BSLIB_FRAMEWORK_MESSAGE_MSGFACTORY_H__
#define __BSLIB_FRAMEWORK_MESSAGE_MSGFACTORY_H__

#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/singleton.h>
#include <BSLib/framework/message/msgExec.h>

namespace BSLib
{

namespace Framework
{

typedef CMessage*(*CreateCMessageFun)();

template<typename T>
CMessage* CreateCMessage()
{
	T* msg = new T();
	if (msg == NULL) {
		return NULL;
	}
	BSLib::Framework::CMessage* cmsg = dynamic_cast<BSLib::Framework::CMessage*>(msg);
	if (cmsg == NULL) {
		BSLIB_SAFE_DELETE(msg);
		return NULL;
	}
	return cmsg;
}

// template<typename T>
// bool GetMsgIDByMsgType(uint32& msgID)
// {
// 	T* msg = new T();
// 	if (msg == NULL) {
// 		return false;
// 	}
// 	BSLib::Framework::SMessage* smsg = dynamic_cast<BSLib::Framework::SMessage*>(msg);
// 	if (smsg == NULL) {
// 		BSLIB_SAFE_DELETE(smsg);
// 		return false;
// 	}
// 	msgID = smsg->getUniqueID();
// 	return true;
// }

class CMsgFactory
{
public:
	CMsgFactory();
	~CMsgFactory();

	BSLIB_SINGLETON_DECLARE(CMsgFactory)
		
public:
	void clear();

	void registerCreateCMsgFun(const BSLib::uint32 msgID, CreateCMessageFun fun);
	void registerCreateCMsgFun(const BSLib::uint32 msgID, BSLib::Utility::CFunction<CMessage*>& a_fun);

	template<class NAME>
	void registerCreateCMsgFun(const BSLib::uint32 msgID, CMessage*(NAME::*a_fun)(), NAME* a_object)
	{
		BSLib::Utility::CFunctionObject<CMessage*, NAME> objFun(a_fun, a_object);
		return registerCreateCMsgFun(msgID, objFun);
	}

	CMessage* createCMessage(const BSLib::uint32 msgID);

private:
	BSLib::Utility::CHashMap< uint32, BSLib::Utility::CFunction<CMessage*>* > m_msgCreateCMsgHashMap;
};

}//Framework

}//BSLib

#endif//__BSLIB_FRAMEWORK_MESSAGE_MSGFACTORY_H__
