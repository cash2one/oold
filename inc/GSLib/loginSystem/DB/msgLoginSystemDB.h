//////////////////////////////////////////////////////////////////////
//	created:	2014/07/22
//	filename: 	GSLib\loginSystem\DB\msgLoginSystemDB.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_DB_MSGLOGINSYSTEMDB_H__
#define __GSLIB_LOGINSYSTEM_DB_MSGLOGINSYSTEMDB_H__

#include <GSLib/loginSystem/msgNumIDLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2DBReqCreatePlayer = GFLIB_MSGID_DEBUG(SRVTYPE_DATASERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2DB_REQ_CREATE_PLAYER);
class CMsgLoginSystemCN2DBReqCreatePlayer: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2DBReqCreatePlayer() : GFLib::CMessage(MsgIDLoginSystemCN2DBReqCreatePlayer)
	{
		m_gateServerID = 0;
		m_gameServerID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerSessionID;
		stream << m_gateServerID;
		stream << m_gameServerID;
		stream << m_accountKey;
		stream << m_accountName;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerSessionID;
		stream >> m_gateServerID;
		stream >> m_gameServerID;
		stream >> m_accountKey;
		stream >> m_accountName;
		return true;
	}

public:
	BSLib::uint32 m_centerSessionID;
	GFLib::ServerID m_gateServerID;
	GFLib::ServerID m_gameServerID;
	GFLib::SAccountKey m_accountKey;
	std::string m_accountName;
};

//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2DBReqInitPlayer = GFLIB_MSGID_DEBUG(SRVTYPE_DATASERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2DB_REQ_INIT_PLAYER);
class CMsgLoginSystemCN2DBReqInitPlayer: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2DBReqInitPlayer() : GFLib::CMessage(MsgIDLoginSystemCN2DBReqInitPlayer)
	{
		m_centerSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerSessionID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerSessionID;
		stream >> m_accountKey;
		return true;
	}

public:
	BSLib::uint32 m_centerSessionID;
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGM2DBAckInitPlayer = GFLIB_MSGID_DEBUG(SRVTYPE_DATASERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GM2DB_ACK_INIT_PLAYER);
class CMsgLoginSystemGM2DBAckInitPlayer: public GFLib::CMessage
{
public:
	CMsgLoginSystemGM2DBAckInitPlayer() : GFLib::CMessage(MsgIDLoginSystemGM2DBAckInitPlayer)
	{
		m_centerSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_state;
		stream << m_centerSessionID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_state;
		stream >> m_centerSessionID;
		stream >> m_accountKey;
		return true;
	}

public:
	BSLib::uint32 m_state;
	BSLib::uint32 m_centerSessionID;
	GFLib::SAccountKey m_accountKey;
};

//离线协议
//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2DBReqAccountOffline = GFLIB_MSGID_DEBUG(SRVTYPE_DATASERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2DB_REQ_ACCOUNT_OFFLINE);
class CMsgLoginSystemCN2DBReqAccountOffline: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2DBReqAccountOffline() : GFLib::CMessage(MsgIDLoginSystemCN2DBReqAccountOffline)
	{
		m_centerSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerSessionID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerSessionID;
		stream >> m_accountKey;
		return true;
	}

public:
	BSLib::uint32 m_centerSessionID;
	GFLib::SAccountKey m_accountKey;
};

//上线协议
//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2DBReqAccountOnline = GFLIB_MSGID_DEBUG(SRVTYPE_DATASERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2DB_REQ_ACCOUNT_ONLINE);
class CMsgLoginSystemCN2DBReqAccountOnline: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2DBReqAccountOnline() : GFLib::CMessage(MsgIDLoginSystemCN2DBReqAccountOnline)
	{
		m_centerSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerSessionID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerSessionID;
		stream >> m_accountKey;
		return true;
	}

public:
	BSLib::uint32 m_centerSessionID;
	GFLib::SAccountKey m_accountKey;
};

//退出协议
//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGT2DBNtfAccountFinal = GFLIB_MSGID_DEBUG(SRVTYPE_DATASERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GT2DB_NTF_ACCOUNT_FINAL);
class CMsgLoginSystemGT2DBNtfAccountFinal: public GFLib::CMessage
{
public:
	CMsgLoginSystemGT2DBNtfAccountFinal() : GFLib::CMessage(MsgIDLoginSystemGT2DBNtfAccountFinal)
	{
		m_centerSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerSessionID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerSessionID;
		stream >> m_accountKey;
		return true;
	}

public:
	BSLib::uint32 m_centerSessionID;
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGM2DBNtfAccountFinal = GFLIB_MSGID_DEBUG(SRVTYPE_DATASERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GM2DB_NTF_ACCOUNT_FINAL);
class CMsgLoginSystemGM2DBNtfAccountFinal: public GFLib::CMessage
{
public:
	CMsgLoginSystemGM2DBNtfAccountFinal() : GFLib::CMessage(MsgIDLoginSystemGM2DBNtfAccountFinal)
	{
		m_centerSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerSessionID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerSessionID;
		stream >> m_accountKey;
		return true;
	}

public:
	BSLib::uint32 m_centerSessionID;
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2DBReqAccountFinal = GFLIB_MSGID_DEBUG(SRVTYPE_DATASERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2DB_REQ_ACCOUNT_FINAL);
class CMsgLoginSystemCN2DBReqAccountFinal: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2DBReqAccountFinal() : GFLib::CMessage(MsgIDLoginSystemCN2DBReqAccountFinal)
	{
		m_centerSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerSessionID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerSessionID;
		stream >> m_accountKey;
		return true;
	}

public:
	BSLib::uint32 m_centerSessionID;
	GFLib::SAccountKey m_accountKey;
};

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_DB_MSGLOGINSYSTEMDB_H__
