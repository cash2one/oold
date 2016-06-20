//////////////////////////////////////////////////////////////////////
//	created:	2014/07/28
//	filename: 	GSLib\loginSystem\CN\netPlayerCN.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_CN_NETPLAYERCN_H__
#define __GSLIB_LOGINSYSTEM_CN_NETPLAYERCN_H__

#include <GFLib/commonServer/message/message.h>
#include <GFLib/commonServer/account.h>
#include <GSLib/loginSystem/msgLoginSystem.h>
#include <GSLib/loginSystem/netPlayer.h>

namespace GSLib
{

namespace LoginSystem
{

namespace CN
{

class CNetPlayerCN : public CNetPlayer, public GFLib::CommonServer::CAccountTransferMsgCallback
{
public:
	CNetPlayerCN(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName);
	virtual ~CNetPlayerCN();

	bool sendMsgToClient(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToClient(GFLib::CMessage& msg);

	bool sendMsgToGateServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToGateServer(GFLib::CMessage& msg);

	bool sendMsgToDataServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToDataServer(GFLib::CMessage& msg);

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
	void _setGateServerID(GFLib::SServerID& a_gateServerID) { m_gateServerID = a_gateServerID; }
	void _setGameServerID(GFLib::SServerID& a_gameServerID) { m_gameServerID = a_gameServerID; }
	void _setDataServerID(GFLib::SServerID& a_dataServerID) { m_dataServerID = a_dataServerID; }

	virtual bool _transferMsg(const GFLib::ServerType& a_serverType, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);

private:
	GFLib::SServerID m_gateServerID;
	GFLib::SServerID m_gameServerID;
	GFLib::SServerID m_dataServerID;

	GFLib::CommonServer::CAccountPtr m_accountPtr;

	friend class CAccountLoginCNInforMgr;
};

}//CN

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_CN_NETPLAYERCN_H__
