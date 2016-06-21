#ifndef __GSLIB_LOGINSYSTEM_LG_MSGLOGINSYSTEMLG_H__
#define __GSLIB_LOGINSYSTEM_LG_MSGLOGINSYSTEMLG_H__

#include <GSLib/loginSystem/msgNumIDLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGC2LGReqAccountLogin = GFLIB_MSGID_DEBUG(SRVTYPE_LOGINSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GC2LG_REQ_ACCOUNT_LOGIN);
class CMsgLoginSystemGC2LGReqAccountLogin: public GFLib::CMessage
{
public:
	CMsgLoginSystemGC2LGReqAccountLogin() : GFLib::CMessage(MsgIDLoginSystemGC2LGReqAccountLogin)
	{
		m_zoneID = 0;
		m_accountName = "";
		m_accountPwd ="";
		m_channelID = 0;
		m_uniqueID = "";
		m_uniqueKey = "";
		m_platform = "";
		m_loginType = 0;
        m_token = "";
        m_accountID = 0;
	}

protected:
	bool serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_accountName;
		stream << m_accountPwd;
		stream << m_zoneID;
		stream << m_channelID;

		stream << m_uniqueID;
		stream << m_uniqueKey;
		stream << m_platform;
		stream << m_loginType;
		stream << m_token;
		stream << m_accountID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountName;
		stream >> m_accountPwd;
		stream >> m_zoneID;
		stream >> m_channelID;

		stream >> m_uniqueID;
		stream >> m_uniqueKey;
		stream >> m_platform;
		stream >> m_loginType;
        stream >> m_token;
        stream >> m_accountID;
		return true;
	}

public:
	std::string m_accountName;
	std::string m_accountPwd;
	BSLib::uint16 m_zoneID;
	BSLib::uint32 m_channelID;
	std::string m_uniqueID;
	std::string m_uniqueKey;
	std::string m_platform;
	BSLib::uint32 m_loginType;
    std::string m_token;
    BSLib::uint64 m_accountID;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemCN2LGAckAccountLogin = GFLIB_MSGID_DEBUG(SRVTYPE_LOGINSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_CN2LG_ACK_ACCOUNT_LOGIN);
class CMsgLoginSystemCN2LGAckAccountLogin: public GFLib::CMessage
{
public:
	CMsgLoginSystemCN2LGAckAccountLogin() : GFLib::CMessage(MsgIDLoginSystemCN2LGAckAccountLogin)
	{
		m_loginSession = 0;
		m_state = 0;
		m_gateServerPort = 0;
		m_gateKey = 0;
		m_gateSession = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_loginSession;
		stream << m_state;
		if (m_state <= 1 ) {
			stream << m_gateServerIP;
			stream << m_gateServerPort;
			stream << m_gateKey;
			stream << m_gateSession;
			stream << m_accountKey;
		}
		
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_loginSession;
		stream >> m_state;
		if (m_state <= 1 ) {
			stream >> m_gateServerIP;
			stream >> m_gateServerPort;
			stream >> m_gateKey;
			stream >> m_gateSession;
			stream >> m_accountKey;
		}
		return true;
	}

public:
	BSLib::uint32 m_loginSession;
	BSLib::uint32 m_state;//LoginResult
	std::string m_gateServerIP;
	BSLib::uint16 m_gateServerPort;
	BSLib::uint32 m_gateKey;
	BSLib::uint32 m_gateSession;
	GFLib::SAccountKey m_accountKey;
};

const BSLib::uint32 MsgIDLoginSystemGC2LGReqRegisterAccount = GFLIB_MSGID_DEBUG(SRVTYPE_LOGINSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GC2LG_REQ_REGISTER_ACCOUNT);
class CMsgLoginSystemGC2LGReqRegisterAccount: public GFLib::CMessage
{
public:
	CMsgLoginSystemGC2LGReqRegisterAccount() : GFLib::CMessage(MsgIDLoginSystemGC2LGReqRegisterAccount)
	{
		//m_zoneID = 0;
		m_accountName = "";
		m_accountPwd ="";
		m_channelID = 0;
		m_uniqueID = "";
		m_uniqueKey = "";
		m_platform = "";
		m_registerType = 0;
	}

protected:
	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountName;
		stream >> m_accountPwd;
		//stream >> m_zoneID;
		stream >> m_channelID;

		stream >> m_uniqueID;
		stream >> m_uniqueKey;
		stream >> m_platform;
		stream >> m_registerType;
        stream >> m_activationCode;
		return true;
	}

public:
	std::string m_accountName;
	std::string m_accountPwd;
	//BSLib::uint16 m_zoneID;
	BSLib::uint32 m_channelID;
	std::string m_uniqueID;
	std::string m_uniqueKey;
	std::string m_platform;
	BSLib::uint32 m_registerType;
    std::string m_activationCode;
};


const BSLib::uint32 MsgIDLoginSystemSP2LGAckRegisterToken = GFLIB_MSGID_DEBUG(SRVTYPE_LOGINSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_SP2LG_ACK_REGISTER_TOKEN);
class CMsgLoginSystemSP2LGAckRegisterToken: public GFLib::CMessage
{
public:
	CMsgLoginSystemSP2LGAckRegisterToken() : GFLib::CMessage(MsgIDLoginSystemSP2LGAckRegisterToken)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_loginSession;
		stream << m_state;
		stream << m_accountKey;
        stream << m_token;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_loginSession;
		stream >> m_state;
		stream >> m_accountKey;
        stream >> m_token;
		return true;
	}

public:
	BSLib::uint32 m_loginSession;
	BSLib::uint32 m_state;//LoginResult
	GFLib::SAccountKey m_accountKey;
    std::string m_token;

};

const BSLib::uint32 MsgIDLoginSystemSP2LGAckCheckToken = GFLIB_MSGID_DEBUG(SRVTYPE_LOGINSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_SP2LG_ACK_CHECK_TOKEN);
class CMsgLoginSystemSP2LGAckCheckToken: public GFLib::CMessage
{
public:
	CMsgLoginSystemSP2LGAckCheckToken() : GFLib::CMessage(MsgIDLoginSystemSP2LGAckCheckToken)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_loginSession;
		stream << m_state;
		stream << m_accountKey;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_loginSession;
		stream >> m_state;
		stream >> m_accountKey;
		return true;
	}

public:
	BSLib::uint32 m_loginSession;
	BSLib::uint32 m_state;//LoginResult
	GFLib::SAccountKey m_accountKey;

};


//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGC2LGReqGetAccountToken = GFLIB_MSGID_DEBUG(SRVTYPE_LOGINSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GC2LG_REQ_GET_ACCOUNT_TAKEN);
class CMsgLoginSystemGC2LGReqGetAccountToken: public GFLib::CMessage
{
public:
    CMsgLoginSystemGC2LGReqGetAccountToken() : GFLib::CMessage(MsgIDLoginSystemGC2LGReqGetAccountToken)
    {
        m_accountName = "";
        m_accountPwd ="";
        m_channelID = 0;
        m_uniqueID = "";
        m_uniqueKey = "";
        m_platform = "";
        m_loginType = 0;
    }

protected:
    bool _serializeFrom(BSLib::Utility::CStream& stream)
    {
        stream >> m_accountName;
        stream >> m_accountPwd;
        stream >> m_channelID;

        stream >> m_uniqueID;
        stream >> m_uniqueKey;
        stream >> m_platform;
        stream >> m_loginType;
        return true;
    }

public:
    std::string m_accountName;	//’À∫≈
    std::string m_accountPwd;	//’À∫≈Token
    BSLib::uint32 m_channelID;	//«˛µ¿ID
    std::string m_uniqueID;
    std::string m_uniqueKey;
    std::string m_platform;		//÷’∂À∆ΩÃ®
    BSLib::uint32 m_loginType;	//µ«¬Ω¿‡–Õ
};

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_LG_MSGLOGINSYSTEMLG_H__

