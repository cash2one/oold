#ifndef __GFLIB_COMMONSERVER_STUB_H__
#define __GFLIB_COMMONSERVER_STUB_H__

#include <BSLib/network/netStub.h>
#include <BSLib/framework/message/msgExecMgr.h>
#include <GFLib/commonServer/service.h>

namespace GFLib
{

namespace CommonServer
{

class GFLIB_COMMONSERVER_API CStub : public IService, public BSLib::Network::CNetStub
{
public:
	CStub(BSLib::Network::CNetConnectionPtr& netConnection);
	virtual ~CStub();

	virtual bool IService_sendMsg(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	virtual bool IService_sendMsg(GFLib::CMessage& msg);
	virtual void close();

protected:
	virtual void _initStub();
	virtual void _finalStub();
	virtual void _initStubMsg(BSLib::Framework::CMsgExecMgr* msgExecMgr);
	virtual void _cbNotifyPing();
	virtual bool _cbParseMsg(void* msgBuff, BSLib::uint32 msgSize);
	virtual void _cbTerminate();

	virtual bool _canTransfer();
	virtual GFLib::StubID _getStubID();

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


