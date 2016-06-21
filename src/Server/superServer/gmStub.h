#ifndef __SERVER_SUPERSERVER_SUPERSTUB_H__
#define __SERVER_SUPERSERVER_SUPERSTUB_H__

#include <GFLib/commonServer/stub.h>
#include <GSLib/loginSystem/msgLoginSystem.h>
#include <GSLib/masterSystem/msgMasterSystem.h>

class CGMStub : public GFLib::CommonServer::CStub
{
public:
	CGMStub(BSLib::Network::CNetConnectionPtr& netConnection);

protected:
	virtual void _finalStub();
	virtual void _initStubMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void _cbTerminate();

private:
// 	void _onMsgLoginSystemGC2LGReqAccountLogin(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
// 	void _onMsgLoginSystemGC2LGReqRegisterAccount(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
// 	void _afterMsgHandlerLoginStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg);
// 	void _afterMsgHandlerRegisterStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg);
// 
// 	bool _cbTimerAccountLogin(BSLib::uint64, void* a_para);
// 
// 	void _notifyAccountLoginResult(GSLib::LoginSystem::ELoginResult result);


	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqLogin);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqOnlineZone);

private:
	BSLib::Utility::TimerHandle m_timeHandleAccountLogin;
	std::string m_accountName;
	BSLib::uint32 m_zoneID;
};


#endif//__SERVER_SUPERSERVER_SUPERSTUB_H__
