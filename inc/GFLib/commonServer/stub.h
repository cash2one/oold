#ifndef __GFLIB_COMMONSERVER_STUB_H__
#define __GFLIB_COMMONSERVER_STUB_H__

#include <BSLib/network/netStub.h>
#include <BSLib/framework/message/msgExecMgr.h>
#include <GFLib/commonServer/service.h>

namespace GFLib
{

namespace CommonServer
{

class GFLIB_COMMONSERVER_API IStub 
    : public IService
    , public BSLib::Network::INetStub
{
public:
	IStub(BSLib::Network::CNetConnectionPtr& netConnection);
	virtual ~IStub();

	virtual bool IService_sendMsg(GFLib::SMessage* msg, BSLib::uint32 msgSize) override;
	virtual bool IService_sendMsg(GFLib::CMessage& msg) override;
	virtual void IService_close() override;

protected:
	virtual void INetStub_initStub() override;
	virtual void INetStub_finalStub() override;
	virtual void INetStub_cbNotifyPing() override;
	virtual bool INetStub_cbParseMsg(void* msgBuff, BSLib::uint32 msgSize) override;
	virtual void INetStub_cbTerminate() override;

	virtual bool _IService_canTransfer() override;
	virtual GFLib::StubID _IService_getStubID() override;

    virtual void IStub_initStubMsg(BSLib::Framework::CMsgExecMgr* msgExecMgr);

protected:
	void _onMsgServerLinkXX2XSReqServerType(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
	void _onMsgServerLinkXS2XXReqPing(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
	void _onMsgServerLinkXX2XSResPing(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
	void _afterMsgHandlerStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg);

};

typedef BSLib::Utility::CPointer<IStub> CStubPtr;

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_STUB_H__


