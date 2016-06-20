
#ifndef __GSLIB_MASTERSYSTEM_MSGMASTERSYSTEM_H__
#define __GSLIB_MASTERSYSTEM_MSGMASTERSYSTEM_H__

#include <GSLib/masterSystem/GM/msgMasterSystemGM.h>
#include <GSLib/masterSystem/msgMasterSystemGC.h>
#include <GSLib/masterSystem/CN/msgMasterSystemCN.h>
#include <GSLib/masterSystem/gm.proto.h>


namespace GSLib
{

namespace MasterSystem
{	

#define GSLIB_MSGFUN_DECLARE(classname) \
	void _on##classname(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)

#define GSLIB_MSGFUN_REG(classname, handlerclass) \
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(msgID##classname, &BSLib::Framework::CreateCMessage<classname>); \
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, msgID##classname, &handlerclass::_on##classname, this);

// 向前转发消息
#define GSLIB_FORWARD_MSGFUN_DEFINE(classname, handlerclass) \
	void  handlerclass::_on##classname(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg) \
	{ \
		classname *req = (classname *)a_msg; \
		using namespace GFLib::CommonServer; \
		GFLib::SNetMsgLabel* netLable = (GFLib::SNetMsgLabel*)a_msgLabel; \
		req->stubId = netLable->m_stubIDsender; \
		CServiceMgr::singleton().sendMsgToServer(req->zone, *req); \
	}	


// 向后返回消息
#define GSLIB_BACKWARD_MSGFUN_DEFINE(classname, handlerclass) \
	void  handlerclass::_on##classname(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg) \
	{ \
		classname *ack = (classname *)a_msg; \
		onReply(ack->stubId, ack->result, ""); \
	}	

// CN向GM转发消息
#define GSLIB_CN2GM_MSGFUN_DEFINE(classname, handlerclass) \
	void  handlerclass::_on##classname(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg) \
	{ \
		classname *req = (classname *)a_msg; \
		using namespace GFLib::CommonServer; \
		CServiceMgr::singleton().sendMsgToServer(m_gmKey, *req); \
	}	

// CN向Super转发消息
#define GSLIB_CN2SP_MSGFUN_DEFINE(classname, handlerclass) \
	void  handlerclass::_on##classname(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg) \
	{ \
		classname *req = (classname *)a_msg; \
		using namespace GFLib::CommonServer; \
		CServiceMgr::singleton().sendMsgToServer(m_superKey, *req); \
	}	

} // MasterSystem

} // GSLib

#endif
