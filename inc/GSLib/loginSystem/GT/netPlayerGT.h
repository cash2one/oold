//////////////////////////////////////////////////////////////////////
//	created:	2014/07/28
//	filename: 	GSLib\loginSystem\GT\netPlayerGT.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_GT_NETPLAYERGT_H__
#define __GSLIB_LOGINSYSTEM_GT_NETPLAYERGT_H__

#include <GFLib/commonServer/message/message.h>
#include <GFLib/commonServer/account.h>
#include <GSLib/loginSystem/msgLoginSystem.h>
#include <GSLib/loginSystem/netPlayer.h>

namespace GSLib
{

namespace LoginSystem
{

namespace GT
{

class CNetPlayerGT : public CNetPlayer, public GFLib::CommonServer::CAccountTransferMsgCallback
{
public:
	CNetPlayerGT(const GFLib::SAccountKey& a_accountKey, const std::string& a_accountName);
	virtual ~CNetPlayerGT();

	bool sendMsgToClient(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);
	bool sendMsgToClient(GFLib::CMessage& a_msg);

	bool sendMsgToCenterServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);
	bool sendMsgToCenterServer(GFLib::CMessage& a_msg);

	bool sendMsgToDataServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);
	bool sendMsgToDataServer(GFLib::CMessage& a_msg);

	bool sendMsgToGameServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);
	bool sendMsgToGameServer(GFLib::CMessage& a_msg);

// 	bool sendMsgToSuperServer(GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);
// 	bool sendMsgToSuperServer(GFLib::CMessage& a_msg);

	virtual bool broadcastMsgToClient(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	virtual bool broadcastMsgToClient(GFLib::CMessage& msg);

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
	void _setDataServerID(GFLib::SServerID& a_dataServerID) { m_dataServerID = a_dataServerID; }
	void _setClientStubID(GFLib::StubID a_stubID) { m_stubID = a_stubID; }

	virtual bool _transferMsg(const GFLib::ServerType& a_serverType, GFLib::SMessage* a_msg, BSLib::uint32 a_msgSize);

private:
	GFLib::SServerID m_centerServerID;
	GFLib::SServerID m_gameServerID;
	GFLib::SServerID m_dataServerID;
	GFLib::StubID m_stubID;

	GFLib::CommonServer::CAccountPtr m_accountPtr;

	friend class CAccountLoginGTInforMgr;
};

}//GT

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_GT_NETPLAYERGT_H__