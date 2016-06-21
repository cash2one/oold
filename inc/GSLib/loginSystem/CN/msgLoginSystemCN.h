#ifndef __GSLIB_LOGINSYSTEM_CN_MSGLOGINSYSTEMCN_H__
#define __GSLIB_LOGINSYSTEM_CN_MSGLOGINSYSTEMCN_H__

#include <GSLib/loginSystem/msgNumIDLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

//////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemLG2CNReqAccountLogin = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_LG2CN_REQ_ACCOUNT_LOGIN);
class CMsgLoginSystemLG2CNReqAccountLogin: public GFLib::CMessage
{
public:
	CMsgLoginSystemLG2CNReqAccountLogin() : GFLib::CMessage(MsgIDLoginSystemLG2CNReqAccountLogin)
	{
		m_loginSession = 0;
		m_channelID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_loginSession;
		stream << m_channelID;
		stream << m_accountName;
		stream << m_accountLoginIP;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_loginSession;
		stream >> m_channelID;
		stream >> m_accountName;
		stream >> m_accountLoginIP;
		stream >> m_accountKey;
		return true;
	}

public:
	BSLib::uint32 m_loginSession;
	BSLib::uint32 m_channelID;
	std::string m_accountName;
	std::string m_accountLoginIP;
	GFLib::SAccountKey m_accountKey;
};


//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGT2CNAckAccountLogin = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GT2CN_ACK_ACCOUNT_LOGIN);
class CMsgLoginSystemGT2CNAckAccountLogin: public GFLib::CMessage
{
public:
	CMsgLoginSystemGT2CNAckAccountLogin() : GFLib::CMessage(MsgIDLoginSystemGT2CNAckAccountLogin)
	{
		m_state = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_centerSession;
		stream << m_state;
		stream << m_gateKey;
		stream << m_gateSession;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_centerSession;
		stream >> m_state;
		stream >> m_gateKey;
		stream >> m_gateSession;
		stream >> m_accountKey;
		return true;
	}

public:
	BSLib::uint32 m_centerSession;
	BSLib::uint32 m_state;//LoginResult?
	BSLib::uint32 m_gateKey;
	BSLib::uint32 m_gateSession;
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGT2CNReqAccountLogin = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GT2CN_REQ_ACCOUNT_LOGIN);
class CMsgLoginSystemGT2CNReqAccountLogin: public GFLib::CMessage
{
public:
	CMsgLoginSystemGT2CNReqAccountLogin() : GFLib::CMessage(MsgIDLoginSystemGT2CNReqAccountLogin)
	{
		m_centerSessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_gateSessionID;
		stream << m_centerSessionID;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_gateSessionID;
		stream >> m_centerSessionID;
		stream >> m_accountKey;
		return true;
	}

public:
	BSLib::uint32 m_gateSessionID;
	BSLib::uint32 m_centerSessionID;
	GFLib::SAccountKey m_accountKey;
};


//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGT2CNAckCreatePlayer = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GT2CN_ACK_CREATE_PLAYER);
class CMsgLoginSystemGT2CNAckCreatePlayer: public GFLib::CMessage
{
public:
	CMsgLoginSystemGT2CNAckCreatePlayer() : GFLib::CMessage(MsgIDLoginSystemGT2CNAckCreatePlayer)
	{
		m_state = 0;
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

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGM2CNAckCreatePlayer = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GM2CN_ACK_CREATE_PLAYER);
class CMsgLoginSystemGM2CNAckCreatePlayer: public GFLib::CMessage
{
public:
	CMsgLoginSystemGM2CNAckCreatePlayer() : GFLib::CMessage(MsgIDLoginSystemGM2CNAckCreatePlayer)
	{
		m_state = 0;
		m_centerSession = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_state;
		stream << m_centerSession;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_state;
		stream >> m_centerSession;
		stream >> m_accountKey;
		return true;
	}

public:	
	BSLib::uint32 m_state;
	BSLib::uint32 m_centerSession;
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemDB2CNAckCreatePlayer = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_DB2CN_ACK_CREATE_PLAYER);
class CMsgLoginSystemDB2CNAckCreatePlayer: public GFLib::CMessage
{
public:
	CMsgLoginSystemDB2CNAckCreatePlayer() : GFLib::CMessage(MsgIDLoginSystemDB2CNAckCreatePlayer)
	{
		m_state = 0;
		m_centerSession = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_state;
		stream << m_centerSession;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_state;
		stream >> m_centerSession;
		stream >> m_accountKey;
		return true;
	}

public:	
	BSLib::uint32 m_state;
	BSLib::uint32 m_centerSession;
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGT2CNAckInitPlayer = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GT2CN_ACK_INIT_PLAYER);
class CMsgLoginSystemGT2CNAckInitPlayer: public GFLib::CMessage
{
public:
	CMsgLoginSystemGT2CNAckInitPlayer() : GFLib::CMessage(MsgIDLoginSystemGT2CNAckInitPlayer)
	{
		m_state = 0;
		m_centerSession = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_state;
		stream << m_centerSession;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_state;
		stream >> m_centerSession;
		stream >> m_accountKey;
		return true;
	}

public:	
	BSLib::uint32 m_state;
	BSLib::uint32 m_centerSession;
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGM2CNNtfInitPlayer = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GM2CN_NTF_INIT_PLAYER);
class CMsgLoginSystemGM2CNNtfInitPlayer: public GFLib::CMessage
{
public:
	CMsgLoginSystemGM2CNNtfInitPlayer() : GFLib::CMessage(MsgIDLoginSystemGM2CNNtfInitPlayer)
	{
		m_state = 0;
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

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemDB2CNAckInitPlayer = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_DB2CN_ACK_INIT_PLAYER);
class CMsgLoginSystemDB2CNAckInitPlayer: public GFLib::CMessage
{
public:
	CMsgLoginSystemDB2CNAckInitPlayer() : GFLib::CMessage(MsgIDLoginSystemDB2CNAckInitPlayer)
	{
		m_state = 0;
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
//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGT2CNReqAccountBreak = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GT2CN_REQ_ACCOUNT_BREAK);
class CMsgLoginSystemGT2CNReqAccountBreak: public GFLib::CMessage
{
public:
	CMsgLoginSystemGT2CNReqAccountBreak() : GFLib::CMessage(MsgIDLoginSystemGT2CNReqAccountBreak)
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

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGT2CNAckAccountOffline = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GT2CN_ACK_ACCOUNT_OFFLINE);
class CMsgLoginSystemGT2CNAckAccountOffline: public GFLib::CMessage
{
public:
	CMsgLoginSystemGT2CNAckAccountOffline() : GFLib::CMessage(MsgIDLoginSystemGT2CNAckAccountOffline)
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

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGM2CNAckAccountOffline = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GM2CN_ACK_ACCOUNT_OFFLINE);
class CMsgLoginSystemGM2CNAckAccountOffline: public GFLib::CMessage
{
public:
	CMsgLoginSystemGM2CNAckAccountOffline() : GFLib::CMessage(MsgIDLoginSystemGM2CNAckAccountOffline)
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

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemDB2CNAckAccountOffline = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_DB2CN_ACK_ACCOUNT_OFFLINE);
class CMsgLoginSystemDB2CNAckAccountOffline: public GFLib::CMessage
{
public:
	CMsgLoginSystemDB2CNAckAccountOffline() : GFLib::CMessage(MsgIDLoginSystemDB2CNAckAccountOffline)
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
//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGT2CNAckAccountOnline = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GT2CN_ACK_ACCOUNT_ONLINE);
class CMsgLoginSystemGT2CNAckAccountOnline: public GFLib::CMessage
{
public:
	CMsgLoginSystemGT2CNAckAccountOnline() : GFLib::CMessage(MsgIDLoginSystemGT2CNAckAccountOnline)
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

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGM2CNAckAccountOnline = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GM2CN_ACK_ACCOUNT_ONLINE);
class CMsgLoginSystemGM2CNAckAccountOnline: public GFLib::CMessage
{
public:
	CMsgLoginSystemGM2CNAckAccountOnline() : GFLib::CMessage(MsgIDLoginSystemGM2CNAckAccountOnline)
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

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemDB2CNAckAccountOnline = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_DB2CN_ACK_ACCOUNT_ONLINE);
class CMsgLoginSystemDB2CNAckAccountOnline: public GFLib::CMessage
{
public:
	CMsgLoginSystemDB2CNAckAccountOnline() : GFLib::CMessage(MsgIDLoginSystemDB2CNAckAccountOnline)
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
//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGT2CNNtfAccountQuit = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GT2CN_NTF_ACCOUNT_QUIT);
class CMsgLoginSystemGT2CNNtfAccountQuit: public GFLib::CMessage
{
public:
	CMsgLoginSystemGT2CNNtfAccountQuit() : GFLib::CMessage(MsgIDLoginSystemGT2CNNtfAccountQuit)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountKey;
		return true;
	}

public:	
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGM2CNNtfAccountQuit = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GM2CN_NTF_ACCOUNT_QUIT);
class CMsgLoginSystemGM2CNNtfAccountQuit: public GFLib::CMessage
{
public:
	CMsgLoginSystemGM2CNNtfAccountQuit() : GFLib::CMessage(MsgIDLoginSystemGM2CNNtfAccountQuit)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountKey;
		return true;
	}

public:	
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemDB2CNNtfAccountQuit = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_DB2CN_NTF_ACCOUNT_QUIT);
class CMsgLoginSystemDB2CNNtfAccountQuit: public GFLib::CMessage
{
public:
	CMsgLoginSystemDB2CNNtfAccountQuit() : GFLib::CMessage(MsgIDLoginSystemDB2CNNtfAccountQuit)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountKey;
		return true;
	}

public:	
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGT2CNAckAccountFinal = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GT2CN_ACK_ACCOUNT_FINAL);
class CMsgLoginSystemGT2CNAckAccountFinal: public GFLib::CMessage
{
public:
	CMsgLoginSystemGT2CNAckAccountFinal() : GFLib::CMessage(MsgIDLoginSystemGT2CNAckAccountFinal)
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

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGM2CNAckAccountFinal = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GM2CN_ACK_ACCOUNT_FINAL);
class CMsgLoginSystemGM2CNAckAccountFinal: public GFLib::CMessage
{
public:
	CMsgLoginSystemGM2CNAckAccountFinal() : GFLib::CMessage(MsgIDLoginSystemGM2CNAckAccountFinal)
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

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemDB2CNAckAccountFinal = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_DB2CN_ACK_ACCOUNT_FINAL);
class CMsgLoginSystemDB2CNAckAccountFinal: public GFLib::CMessage
{
public:
	CMsgLoginSystemDB2CNAckAccountFinal() : GFLib::CMessage(MsgIDLoginSystemDB2CNAckAccountFinal)
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

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGT2CNNtfAccountTimeout = GFLIB_MSGID_DEBUG(SRVTYPE_CENTERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GT2CN_NTF_ACCOUNT_TIMEOUT);
class CMsgLoginSystemGT2CNNtfAccountTimeout: public GFLib::CMessage
{
public:
	CMsgLoginSystemGT2CNNtfAccountTimeout() : GFLib::CMessage(MsgIDLoginSystemGT2CNNtfAccountTimeout)
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

#endif//__GSLIB_LOGINSYSTEM_CN_MSGLOGINSYSTEMCN_H__

