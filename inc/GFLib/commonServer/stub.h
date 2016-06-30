#ifndef __GFLIB_COMMONSERVER_STUB_H__
#define __GFLIB_COMMONSERVER_STUB_H__

#include <BSLib/network/netStub.h>
#include <BSLib/framework/message/msgExecMgr.h>
#include <GFLib/commonServer/service.h>

namespace GFLib
{

namespace CommonServer
{

class GFLIB_COMMONSERVER_API CStub : public IService, public BSLib::Network::INetStub
{
public:
	CStub(BSLib::Network::CNetConnectionPtr& netConnection);
	virtual ~CStub();

	virtual bool IService_sendMsg(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	virtual bool IService_sendMsg(GFLib::CMessage& msg);
	virtual void IService_close();

protected:
	virtual void INetStub_initStub();
	virtual void INetStub_finalStub();
	virtual void INetStub_initStubMsg(BSLib::Framework::CMsgExecMgr* msgExecMgr);
	virtual void INetStub_cbNotifyPing();
	virtual bool INetStub_cbParseMsg(void* msgBuff, BSLib::uint32 msgSize);
	virtual void INetStub_cbTerminate();

	virtual bool _IService_canTransfer();
	virtual GFLib::StubID _IService_getStubID();

protected:
	void _onMsgServerLinkXX2XSReqServerType(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
	void _onMsgServerLinkXS2XXReqPing(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
	void _onMsgServerLinkXX2XSResPing(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
	void _afterMsgHandlerStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg);

};

typedef BSLib::Utility::CPointer<CStub> CStubPtr;

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_STUB_H__


