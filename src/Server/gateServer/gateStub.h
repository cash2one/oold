#ifndef __SERVER_GATESERVER_GATESTUB_H__
#define __SERVER_GATESERVER_GATESTUB_H__

#include <GFLib/commonServer/stub.h>
#include <GSLib/loginSystem/GT/loginSystemGT.h>

class CGateStub : public GFLib::CommonServer::CStub, public GSLib::LoginSystem::GT::CVerifyAccountLoginCallBack
{
public:
	CGateStub(BSLib::Network::CNetConnectionPtr& netConnection);

protected:
	virtual void _finalStub();
	virtual void _initStubMsg(BSLib::Framework::CMsgExecMgr* msgExecMgr);
	virtual void _cbTerminate();

	virtual bool _transferMsg(GFLib::SMessage* msg, BSLib::uint32 a_msgSize);

	virtual void _cbVerifyAccountLogin(GFLib::SServerID& a_gameServerID, GFLib::SServerID& a_dbServerID, GFLib::SServerID& a_centerServerID);

protected:
	void _onMsgLoginSystemGC2GTReqAccountLogin(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework::SMessage* msg);
	void _afterMsgHandlerGameStub(BSLib::Framework::CMsgExecMgr* msgExecMgr, BSLib::Framework::SMsgLabel* msgLabel, BSLib::Framework::SMessage* msg);

private:
	GFLib::SAccountKey m_accountKey;
	BSLib::uint32 m_gateKey;
	BSLib::uint32 m_gateSession;

	bool m_isValidAccountID;
	GFLib::SServerID m_gameServerID;
	GFLib::SServerID m_dbServerID;
	GFLib::SServerID m_centerServerID;
};


#endif//__SERVER_GATESERVER_GAMESTUB_H__
