//////////////////////////////////////////////////////////////////////
//	created:	2012/07/20
//	filename: 	BSLib\framework\message\msgExecMgr.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_FRAMEWORK_MESSAGE_MSGEXECMGR_H__
#define __BSLIB_FRAMEWORK_MESSAGE_MSGEXECMGR_H__

#include <BSLib/utility/hashMap.h>
#include <BSLib/framework/message/msgExec.h>
#include <BSLib/framework/message/msgFactory.h>

namespace BSLib
{

namespace Framework
{

class BSLIB_FRAMEWORK_API CMsgExecMgr
{
private:
	struct SMsgExecItem
	{
	public:
		SMsgExecItem() : m_msgExecPtr(NULL), m_afterMsgExecFun(NULL) {}

	public:
		CMsgExecPtr m_msgExecPtr;
		BSLib::Utility::CFunction<void, CMsgExecMgr*, SMsgLabel*, SMessage*>* m_afterMsgExecFun;
	};

public:
	CMsgExecMgr();
	virtual ~CMsgExecMgr();

	bool executeMessage(SMsgLabel* msgLabel, SMessage* msg);

	bool addMsgExecPtr(uint32 msgID, CMsgExecPtr& msgExecPtr);
	bool addMsgExecPtr(uint32 msgID, CMsgExecPtr& msgExecPtr, void(*afterMsgExecFun)(CMsgExecMgr*, SMsgLabel*, SMessage*));
	bool addMsgExecPtr(uint32 msgID, CMsgExecPtr& msgExecPtr, const BSLib::Utility::CFunction<void, CMsgExecMgr*, SMsgLabel*, SMessage*>& afterMsgExecFun);

	bool addMsgExecPtr(uint16 type, uint16 id, CMsgExecPtr& msgExecPtr);
	bool addMsgExecPtr(uint16 type, uint16 id, CMsgExecPtr& msgExecPtr, void(*afterMsgExecFun)(CMsgExecMgr*, SMsgLabel*, SMessage*));
	bool addMsgExecPtr(uint16 type, uint16 id, CMsgExecPtr& msgExecPtr, const BSLib::Utility::CFunction<void, CMsgExecMgr*, SMsgLabel*, SMessage*>& afterMsgExecFun);

	bool addMsgTypeExecPtr(uint16 type, CMsgExecPtr& msgExecPtr);
	bool addMsgTypeExecPtr(uint16 type, CMsgExecPtr& msgExecPtr, void(*afterMsgExecFun)(CMsgExecMgr*, SMsgLabel*, SMessage*));
	bool addMsgTypeExecPtr(uint16 type, CMsgExecPtr& msgExecPtr, const BSLib::Utility::CFunction<void, CMsgExecMgr*, SMsgLabel*, SMessage*>& afterMsgExecFun);
	
	template<class NAME>
	bool addMsgExecPtr(uint32 msgID, CMsgExecPtr& msgExecPtr, void(NAME::*afterMsgExecFun)(CMsgExecMgr*, SMsgLabel*, SMessage*), NAME* object)
	{
		BSLib::Utility::CFunctionObject<void, NAME, CMsgExecMgr*, SMsgLabel*, SMessage*> fun(afterMsgExecFun, object);
		return addMsgExecPtr(msgID, msgExecPtr, fun);
	}

	template<class NAME>
	bool addMsgExecPtr(uint16 type, uint16 id, CMsgExecPtr& msgExecPtr, void(NAME::*afterMsgExecFun)(CMsgExecMgr*, SMsgLabel*, SMessage*), NAME* object)
	{
		BSLib::Utility::CFunctionObject<void, NAME, CMsgExecMgr*, SMsgLabel*, SMessage*> fun(afterMsgExecFun, object);
		return addMsgExecPtr(type, id, msgExecPtr, fun);
	}

	template<class NAME>
	bool addMsgTypeExecPtr(uint16 type, CMsgExecPtr& msgExecPtr, void(NAME::*afterMsgExecFun)(CMsgExecMgr*, SMsgLabel*, SMessage*), NAME* object)
	{
		BSLib::Utility::CFunctionObject<void, NAME, CMsgExecMgr*, SMsgLabel*, SMessage*> fun(afterMsgExecFun, object);
		return addMsgTypeExecPtr(type, msgExecPtr, fun);
	}

	void delMsgExecPtr(uint32 msgID);
	void delMsgExecPtr(uint16 type, uint16 id);
	void delMsgExecPtr(uint16 type);
	void clear();

private:
	BSLib::Utility::CHashMap<uint32, SMsgExecItem*> m_msgExecHashMap;
	BSLib::Utility::CHashMap<uint16, SMsgExecItem*> m_typeMsgExecHashMap;
};


#define GFLIB_ADDMSG_EOBJEXEC_AOBJAFTER(mgr, id, ex, eobj, af, aobj)\
{\
	BSLib::Framework::CMsgExecPtr msgExecPtr = new BSLib::Framework::CMsgExec(ex, eobj);\
	mgr->addMsgExecPtr(id, msgExecPtr, af, aobj);\
}

#define GFLIB_ADDMSG_OBJEXEC_OBJAFTER(mgr, id, ex, af, obj)\
{\
	BSLib::Framework::CMsgExecPtr msgExecPtr = new BSLib::Framework::CMsgExec(ex, obj);\
	mgr->addMsgExecPtr(id, msgExecPtr, af, obj);\
}

#define GFLIB_ADDMSG_OBJEXEC_AFTER(mgr, id, ex, af, obj)\
{\
	BSLib::Framework::CMsgExecPtr msgExecPtr = new BSLib::Framework::CMsgExec(ex, obj);\
	mgr->addMsgExecPtr(id, msgExecPtr, af);\
}

#define GFLIB_ADDMSG_EXEC_OBJAFTER(mgr, id, ex, af, obj)\
{\
	BSLib::Framework::CMsgExecPtr msgExecPtr = new BSLib::Framework::CMsgExec(ex);\
	mgr->addMsgExecPtr(id, msgExecPtr, af, obj);\
}

#define GFLIB_ADDMSG_EXEC_AFTER(mgr, id, ex, af)\
{\
	BSLib::Framework::CMsgExecPtr msgExecPtr = new BSLib::Framework::CMsgExec(ex);\
	mgr->addMsgExecPtr(id, msgExecPtr, af);\
}

#define GFLIB_ADDMSG_OBJEXEC(mgr, id, ex, obj)\
{\
	BSLib::Framework::CMsgExecPtr msgExecPtr = new BSLib::Framework::CMsgExec(ex, obj);\
	mgr->addMsgExecPtr(id, msgExecPtr);\
}

#define GFLIB_ADDMSG_EXEC(mgr, id, ex)\
{\
	BSLib::Framework::CMsgExecPtr msgExecPtr = new BSLib::Framework::CMsgExec(ex);\
	mgr->addMsgExecPtr(id, msgExecPtr);\
}

#define GFLIB_ADDMSGTYPE_OBJEXEC(mgr, type, ex, obj)\
{\
	BSLib::Framework::CMsgExecPtr msgExecPtr = new BSLib::Framework::CMsgExec(ex, obj);\
	mgr->addMsgTypeExecPtr(type, msgExecPtr);\
}

#define GFLIB_ADDMSGTYPE_EXEC(mgr, type, ex)\
{\
	BSLib::Framework::CMsgExecPtr msgExecPtr = new BSLib::Framework::CMsgExec(ex);\
	mgr->addMsgTypeExecPtr(type, msgExecPtr);\
}

}//Framework

}//BSLib

#endif // __BSLIB_FRAMEWORK_MESSAGE_MSGEXECMGR_H__
