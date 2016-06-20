//////////////////////////////////////////////////////////////////////
//	created:	2014/07/22
//	filename: 	GSLib\loginSystem\GT\msgLoginSystemGT.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_GT_MSGLOGINSYSTEMGT_H__
#define __GSLIB_LOGINSYSTEM_GT_MSGLOGINSYSTEMGT_H__

#include <GSLib/loginSystem/msgNumIDLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGC2GTReqAccountLogin = GFLIB_MSGID_DEBUG(SRVTYPE_GATESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GC2GT_REQ_ACCOUNT_LOGIN);
class CMsgLoginSystemGC2GTReqAccountLogin: public GFLib::CMessage
{
public:

	CMsgLoginSystemGC2GTReqAccountLogin() : GFLib::CMessage(MsgIDLoginSystemGC2GTReqAccountLogin)
	{
		m_channelID = 0;
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_gateSession;
		stream >> m_gateKey;
		stream >> m_channelID;
		stream >> m_accountKey;
		return true;
	}

public:
	BSLib::uint32 m_gateSession;
	BSLib::uint32 m_gateKey;
	BSLib::uint32 m_channelID;
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2GTReqAccountLogin = GFLIB_MSGID_DEBUG(SRVTYPE_GATESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2GT_REQ_ACCOUNT_LOGIN);
class CMsgLoginSystemCN2GTReqAccountLogin: public GFLib::CMessage
{
public:

	CMsgLoginSystemCN2GTReqAccountLogin() : GFLib::CMessage(MsgIDLoginSystemCN2GTReqAccountLogin)
	{
		m_centerSession = 0;
		m_channelID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerSession;
		stream << m_channelID;
		stream << m_accountName;
		stream << m_accountLoginIP;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerSession;
		stream >> m_channelID;
		stream >> m_accountName;
		stream >> m_accountLoginIP;
		stream >> m_accountKey;
		return true;
	}

public:
	BSLib::uint32 m_centerSession;
	BSLib::uint32 m_channelID;
	std::string m_accountName;
	std::string m_accountLoginIP;
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2GTAckAccountLogin = GFLIB_MSGID_DEBUG(SRVTYPE_GATESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2GT_ACK_ACCOUNT_LOGIN);
class CMsgLoginSystemCN2GTAckAccountLogin: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2GTAckAccountLogin() : GFLib::CMessage(MsgIDLoginSystemCN2GTAckAccountLogin)
	{
		m_state = 0;
		m_gateSession = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_gateSession;
		stream << m_accountKey;
		stream << m_state;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_gateSession;
		stream >> m_accountKey;
		stream >> m_state;
		return true;
	}
public:
	BSLib::uint32 m_gateSession;
	GFLib::SAccountKey m_accountKey;
	BSLib::uint32 m_state;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2GTReqCreatePlayer = GFLIB_MSGID_DEBUG(SRVTYPE_GATESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2GT_REQ_CREATE_PLAYER);
class CMsgLoginSystemCN2GTReqCreatePlayer: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2GTReqCreatePlayer() : GFLib::CMessage(MsgIDLoginSystemCN2GTReqCreatePlayer)
	{
		m_centerSessionID = 0;
		m_gateSessionID = 0;
		m_gameServerID = 0;
		m_dataServerID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerSessionID;
		stream << m_accountKey;
		stream << m_gateSessionID;
		stream << m_gameServerID;
		stream << m_dataServerID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerSessionID;
		stream >> m_accountKey;
		stream >> m_gateSessionID;
		stream >> m_gameServerID;
		stream >> m_dataServerID;
		return true;
	}
public:
	BSLib::uint32 m_centerSessionID;
	GFLib::SAccountKey m_accountKey;
	GFLib::ServerID m_gameServerID;
	GFLib::ServerID m_dataServerID;
	BSLib::uint32 m_gateSessionID;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2GTReqInitPlayer = GFLIB_MSGID_DEBUG(SRVTYPE_GATESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2GT_REQ_INIT_PLAYER);
class CMsgLoginSystemCN2GTReqInitPlayer: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2GTReqInitPlayer() : GFLib::CMessage(MsgIDLoginSystemCN2GTReqInitPlayer)
	{
		m_centerSessionID = 0;
		m_gateSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerSessionID;
		stream << m_gateSessionID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerSessionID;
		stream >> m_gateSessionID;
		stream >> m_accountKey;
		return true;
	}
public:
	BSLib::uint32 m_centerSessionID;
	BSLib::uint32 m_gateSessionID;
	GFLib::SAccountKey m_accountKey;
};

//离线协议
//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2GTAckAccountBreak = GFLIB_MSGID_DEBUG(SRVTYPE_GATESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2GT_ACK_ACCOUNT_BREAK);
class CMsgLoginSystemCN2GTAckAccountBreak: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2GTAckAccountBreak() : GFLib::CMessage(MsgIDLoginSystemCN2GTAckAccountBreak)
	{
		m_gateSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_gateSessionID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_gateSessionID;
		stream >> m_accountKey;
		return true;
	}
public:
	BSLib::uint32 m_gateSessionID;
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2GTReqAccountOffline = GFLIB_MSGID_DEBUG(SRVTYPE_GATESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2GT_REQ_ACCOUNT_OFFLINE);
class CMsgLoginSystemCN2GTReqAccountOffline: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2GTReqAccountOffline() : GFLib::CMessage(MsgIDLoginSystemCN2GTReqAccountOffline)
	{
		m_gateSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_gateSessionID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_gateSessionID;
		stream >> m_accountKey;
		return true;
	}
public:
	BSLib::uint32 m_gateSessionID;
	GFLib::SAccountKey m_accountKey;
};

//上线协议
//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2GTReqAccountOnline = GFLIB_MSGID_DEBUG(SRVTYPE_GATESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2GT_REQ_ACCOUNT_ONLINE);
class CMsgLoginSystemCN2GTReqAccountOnline: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2GTReqAccountOnline() : GFLib::CMessage(MsgIDLoginSystemCN2GTReqAccountOnline)
	{
		m_gateSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_gateSessionID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_gateSessionID;
		stream >> m_accountKey;
		return true;
	}
public:
	BSLib::uint32 m_gateSessionID;
	GFLib::SAccountKey m_accountKey;
};

//退出协议
//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2GTReqAccountFinal = GFLIB_MSGID_DEBUG(SRVTYPE_GATESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2GT_REQ_ACCOUNT_FINAL);
class CMsgLoginSystemCN2GTReqAccountFinal: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2GTReqAccountFinal() : GFLib::CMessage(MsgIDLoginSystemCN2GTReqAccountFinal)
	{
		m_centerSessionID = 0;
		m_gateSessionID = 0;
		m_dataServerID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerSessionID;
		stream << m_gateSessionID;
		stream << m_dataServerID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerSessionID;
		stream >> m_gateSessionID;
		stream >> m_dataServerID;
		stream >> m_accountKey;
		return true;
	}
public:
	BSLib::uint32 m_centerSessionID;
	BSLib::uint32 m_gateSessionID;
	GFLib::ServerID m_dataServerID;
	GFLib::SAccountKey m_accountKey;
};

const BSLib::uint32 MsgIDLoginSystemXS2GTNtfBroadcastMsg = GFLIB_MSGID_DEBUG(SRVTYPE_GATESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_XS2GT_NTF_BROADCAST_MSG);
class CMsgLoginSystemXS2GTNtfBroadcastMsg: public GFLib::CMessage
{
public:
	CMsgLoginSystemXS2GTNtfBroadcastMsg() : GFLib::CMessage(MsgIDLoginSystemXS2GTNtfBroadcastMsg)
	{
		;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_subMsg;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_subMsg;
		return true;
	}
public:
	BSLib::Utility::CStream m_subMsg;
};

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_GT_MSGLOGINSYSTEMGT_H__
