//////////////////////////////////////////////////////////////////////
//	created:	2014/07/22
//	filename: 	GSLib\loginSystem\GM\msgLoginSystemGM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_GM_MSGLOGINSYSTEMGM_H__
#define __GSLIB_LOGINSYSTEM_GM_MSGLOGINSYSTEMGM_H__

#include <GSLib/loginSystem/msgNumIDLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2GMReqCreatePlayer = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2GM_REQ_CREATE_PLAYER);
class CMsgLoginSystemCN2GMReqCreatePlayer: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2GMReqCreatePlayer() : GFLib::CMessage(MsgIDLoginSystemCN2GMReqCreatePlayer)
	{
		m_gateServerID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerSessionID;
		stream << m_gateServerID;
		stream << m_dataServerID;
		stream << m_accountKey;
		stream << m_accountName;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerSessionID;
		stream >> m_gateServerID;
		stream >> m_dataServerID;
		stream >> m_accountKey;
		stream >> m_accountName;
		return true;
	}

public:
	BSLib::uint32 m_centerSessionID;
	GFLib::ServerID m_gateServerID;
	GFLib::ServerID m_dataServerID;
	GFLib::SAccountKey m_accountKey;
	std::string m_accountName;
};

//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemDB2GMReqInitPlayer = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_DB2GM_REQ_INIT_PLAYER);
class CMsgLoginSystemDB2GMReqInitPlayer: public GFLib::CMessage
{
public:
	CMsgLoginSystemDB2GMReqInitPlayer() : GFLib::CMessage(MsgIDLoginSystemDB2GMReqInitPlayer)
	{
		m_centerServerID = 0;
		m_centerSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerServerID;
		stream << m_centerSessionID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerServerID;
		stream >> m_centerSessionID;
		stream >> m_accountKey;
		return true;
	}

public:
	GFLib::ServerID m_centerServerID;
	BSLib::uint32 m_centerSessionID;
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////
// const BSLib::uint32 MsgIDLoginSystemGT2GMNtfPlayerInforToClient = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GT2GM_NTF_PLAYER_INFOR_TO_CLIENT);
// class CMsgLoginSystemGT2GMNtfPlayerInforToClient: public GFLib::CMessage
// {
// public:
// 	CMsgLoginSystemGT2GMNtfPlayerInforToClient() : GFLib::CMessage(MsgIDLoginSystemGT2GMNtfPlayerInforToClient)
// 	{
// 		m_accountID = 0;
// 	}
// 
// protected:
// 	bool _serializeTo(BSLib::Utility::CStream& stream) const
// 	{
// 		stream << m_accountID;
// 		return true;
// 	}
// 
// 	bool _serializeFrom(BSLib::Utility::CStream& stream)
// 	{
// 		stream >> m_accountID;
// 		return true;
// 	}
// 
// public:
// 	BSLib::uint64 m_accountID;
// };

//离线协议
//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2GMReqAccountOffline = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2GM_REQ_ACCOUNT_OFFLINE);
class CMsgLoginSystemCN2GMReqAccountOffline: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2GMReqAccountOffline() : GFLib::CMessage(MsgIDLoginSystemCN2GMReqAccountOffline)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_accountKey;
		stream << m_centerSessionID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountKey;
		stream >> m_centerSessionID;
		return true;
	}

public:
	GFLib::SAccountKey m_accountKey;
	BSLib::uint32 m_centerSessionID;
};

//上线协议
//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2GMReqAccountOnline = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2GM_REQ_ACCOUNT_ONLINE);
class CMsgLoginSystemCN2GMReqAccountOnline: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2GMReqAccountOnline() : GFLib::CMessage(MsgIDLoginSystemCN2GMReqAccountOnline)
	{
		m_centerSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_accountKey;
		stream << m_centerSessionID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountKey;
		stream >> m_centerSessionID;
		return true;
	}

public:
	GFLib::SAccountKey m_accountKey;
	BSLib::uint32 m_centerSessionID;
};

//退出协议
//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2GMReqAccountFinal = GFLIB_MSGID_DEBUG(SRVTYPE_GAMESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2GM_REQ_ACCOUNT_FINAL);
class CMsgLoginSystemCN2GMReqAccountFinal: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2GMReqAccountFinal() : GFLib::CMessage(MsgIDLoginSystemCN2GMReqAccountFinal)
	{
		m_centerSessionID = 0;
		m_dataServerID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_accountKey;
		stream << m_centerSessionID;
		stream << m_dataServerID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountKey;
		stream >> m_centerSessionID;
		stream >> m_dataServerID;
		return true;
	}

public:
	GFLib::SAccountKey m_accountKey;
	BSLib::uint32 m_centerSessionID;
	GFLib::ServerID m_dataServerID;
};

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_GM_MSGLOGINSYSTEMGM_H__
