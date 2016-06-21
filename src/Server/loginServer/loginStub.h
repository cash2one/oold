#ifndef __SERVER_LOGINSERVER_LOGINSTUB_H__
#define __SERVER_LOGINSERVER_LOGINSTUB_H__

#include <GFLib/commonServer/stub.h>
#include <GSLib/loginSystem/msgLoginSystem.h>

class CLoginStub : public GFLib::CommonServer::CStub
{
public:
	CLoginStub(BSLib::Network::CNetConnectionPtr& netConnection);

protected:
	virtual void _finalStub();
	virtual void _initStubMsg(BSLib::Framework::CMsgExecMgr* msgExecMgr);
	virtual void _cbTerminate();

private:
	void _onMsgLoginSystemGC2LGReqAccountLogin(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
	void _onMsgLoginSystemGC2LGReqRegisterAccount(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
    void _onMsgLoginSystemGC2LGReqGetAccountToken(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);

	void _afterMsgHandlerLoginStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg);
	void _afterMsgHandlerRegisterStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg);
    void _afterMsgHandlerGetAccountTokenStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg);

	bool _cbTimerAccountLogin(BSLib::uint64, void* a_para);

	void _notifyAccountLoginResult(GSLib::LoginSystem::ELoginResult result);
    void _notifyGetAccountTokenResult(GSLib::LoginSystem::EGetAccountTokenResult result);

private:
	BSLib::Utility::TimerHandle m_timeHandleAccountLogin;
	std::string m_accountName;
	BSLib::uint32 m_zoneID;
};


#endif//__SERVER_LOGINSERVER_LOGINSTUB_H__
