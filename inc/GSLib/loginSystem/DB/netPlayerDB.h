#ifndef __GSLIB_LOGINSYSTEM_DB_NETPLAYERDB_H__
#define __GSLIB_LOGINSYSTEM_DB_NETPLAYERDB_H__

#include <GFLib/commonServer/message/message.h>
#include <GFLib/commonServer/account.h>
#include <GSLib/loginSystem/msgLoginSystem.h>
#include <GSLib/loginSystem/netPlayer.h>

namespace GSLib
{

namespace LoginSystem
{

namespace DB
{

class CNetPlayerDB : public CNetPlayer, public GFLib::CommonServer::CAccountTransferMsgCallback
{
public:
	CNetPlayerDB(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName);
	virtual ~CNetPlayerDB();

	bool sendMsgToClient(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToClient(GFLib::CMessage& msg);

	bool sendMsgToGateServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToGateServer(GFLib::CMessage& msg);

	bool sendMsgToCenterServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToCenterServer(GFLib::CMessage& msg);

	bool sendMsgToGameServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToGameServer(GFLib::CMessage& msg);
protected:
	virtual void _cbInitPlayer();
	virtual void _cbFinalPlayer();

	virtual void _cbPlayerOnline();
	virtual void _cbPlayerOffline();

	void _quit();
	void _finishInitPlayer(ELoginResult a_result);

private:
	void _setAccountPtr(GFLib::CommonServer::CAccountPtr& a_accountPtr) { m_accountPtr = a_accountPtr; }
	void _setCenterServerID(GFLib::SServerID& a_centerServerID) { m_centerServerID = a_centerServerID; }
	void _setGameServerID(GFLib::SServerID& a_gameServerID) { m_gameServerID = a_gameServerID; }
	void _setGateServerID(GFLib::SServerID& a_gateServerID) { m_gateServerID = a_gateServerID; }

	virtual bool _transferMsg(const GFLib::ServerType& a_serverType, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);

private:
	GFLib::SServerID m_centerServerID;
	GFLib::SServerID m_gameServerID;
	GFLib::SServerID m_gateServerID;

	GFLib::CommonServer::CAccountPtr m_accountPtr;

	friend class CAccountLoginDBInforMgr;
};

}//DB

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_DB_NETPLAYERDB_H__
