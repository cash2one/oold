#ifndef __GSLIB_LOGINSYSTEM_GM_NETPLAYERGM_H__
#define __GSLIB_LOGINSYSTEM_GM_NETPLAYERGM_H__

#include <GFLib/commonServer/message/message.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

class GNetPlayerGM
{
public:
	GNetPlayerGM(const BSLib::uint64 a_accountID, const std::string& a_accountName);
	virtual ~GNetPlayerGM();

	bool sendMsgToClient(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToClient(GFLib::CMessage& msg);

	bool sendMsgToGateServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToGateServer(GFLib::CMessage& msg);

	bool sendMsgToDataServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToDataServer(GFLib::CMessage& msg);

	bool sendMsgToCenterServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToCenterServer(GFLib::CMessage& msg);

	const std::string& getAccountName() { return m_accountName; }
	BSLib::uint64 getAccountID() { return m_accountID; }

protected:
	virtual void _cbInitPlayer();
	virtual void _cbFinalPlayer();

	virtual void _cbPlayerOnline();
	virtual void _cbPlayerOffline();

	void _quit();
	void _notifyCNPlayerInit(ELoginResult a_loginResult);

private:
	void _setGateServerID(GFLib::SServerID& a_gateServerID) { m_gateServerID = a_gateServerID; }
	void _setCenterServerID(GFLib::SServerID& a_centerServerID) { m_centerServerID = a_centerServerID; }
	void _setDataServerID(GFLib::SServerID& a_dataServerID) { m_dataServerID = a_dataServerID; }

private:
	GFLib::SServerID m_gateServerID;
	GFLib::SServerID m_centerServerID;
	GFLib::SServerID m_dataServerID;
	BSLib::uint64 m_accountID;
	std::string m_accountName;
};

}//GM

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_GM_NETPLAYERGM_H__
