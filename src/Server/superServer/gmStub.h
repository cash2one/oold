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
	virtual void INetStub_finalStub();
	virtual void INetStub_initStubMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void INetStub_cbTerminate();

private:
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqLogin);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqOnlineZone);

private:
	BSLib::Utility::TimerHandle m_timeHandleAccountLogin;
	std::string m_accountName;
	BSLib::uint32 m_zoneID;
};


#endif//__SERVER_SUPERSERVER_SUPERSTUB_H__
