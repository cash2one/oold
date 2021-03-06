#ifndef __SERVER_SUPERSERVER_SUPERSTUB_H__
#define __SERVER_SUPERSERVER_SUPERSTUB_H__

#include <GFLib/commonServer/stub.h>
#include <GSLib/loginSystem/msgLoginSystem.h>

class CSuperStub : public GFLib::CommonServer::IStub
{
public:
	CSuperStub(BSLib::Network::CNetConnectionPtr& netConnection);

protected:
	virtual void INetStub_finalStub();
	virtual void IStub_initStubMsg(BSLib::Framework::CMsgExecMgr* msgExecMgr);
	virtual void INetStub_cbTerminate();

private:
// 	void _onMsgLoginSystemGC2LGReqAccountLogin(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
// 	void _onMsgLoginSystemGC2LGReqRegisterAccount(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
// 	void _afterMsgHandlerLoginStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg);
// 	void _afterMsgHandlerRegisterStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg);
// 
// 	bool _cbTimerAccountLogin(BSLib::uint64, void* a_para);
// 
// 	void _notifyAccountLoginResult(GSLib::LoginSystem::ELoginResult result);

private:
	BSLib::Utility::TimerHandle m_timeHandleAccountLogin;
	std::string m_accountName;
	BSLib::uint32 m_zoneID;
};


#endif//__SERVER_SUPERSERVER_SUPERSTUB_H__
