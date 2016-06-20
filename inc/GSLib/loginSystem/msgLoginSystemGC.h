//////////////////////////////////////////////////////////////////////
//	created:	2014/07/22
//	filename: 	GSLib\loginSystem\msgLoginSystemGC.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_LOGINSYSTEM_MSGLOGINSYSTEMGC_H__
#define __GSLIB_LOGINSYSTEM_MSGLOGINSYSTEMGC_H__

#include <GSLib/loginSystem/msgNumIDLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemLG2GCAckAccountLogin = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_LG2GC_ACK_ACCOUNT_LOGIN);
class CMsgLoginSystemLG2GCAckAccountLogin: public GFLib::CMessage
{
public:
	CMsgLoginSystemLG2GCAckAccountLogin() : GFLib::CMessage(MsgIDLoginSystemLG2GCAckAccountLogin)
	{
		m_gateServerIP = "127.0.0.1";
		m_gateServerPort = 9002;
		m_gateKey = 88888;
		m_gateSession = 11111;
		m_state = ELOGINRESULT_SUCCESS;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_state;

		if (m_state <= 1) {
			stream << m_gateServerIP;
			stream << m_gateServerPort;
			stream << m_gateKey;
			stream << m_gateSession;
			stream << m_accountKey;
		} 
		return true;
	}
public:
	BSLib::uint32 m_state;//LoginResult
	std::string m_gateServerIP;
	BSLib::uint16 m_gateServerPort;
	BSLib::uint32 m_gateKey;
	BSLib::uint32 m_gateSession;
	GFLib::SAccountKey m_accountKey;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemGT2GCAckAccountLogin = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_GT2GC_ACK_ACCOUNT_LOGIN);
class CMsgLoginSystemGT2GCAckAccountLogin: public GFLib::CMessage
{
public:
	CMsgLoginSystemGT2GCAckAccountLogin() : GFLib::CMessage(MsgIDLoginSystemGT2GCAckAccountLogin)
	{
		m_state = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_state;
		return true;
	}
public:
	BSLib::uint32 m_state;
};


const BSLib::uint32 MsgIDLoginSystemLG2GCAckRegisterAccount = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_LG2GC_ACK_REGISTER_ACCOUNT);
class CMsgLoginSystemLG2GCAckRegisterAccount: public GFLib::CMessage
{
public:
	CMsgLoginSystemLG2GCAckRegisterAccount() : GFLib::CMessage(MsgIDLoginSystemLG2GCAckRegisterAccount)
	{
		m_state = EREGISTERRESULT_SUCCESS;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_state;
		return true;
	}
public:
	BSLib::uint32 m_state;//LoginResult
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemLG2GCAckGetAccountToken = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_GAMECLIENT, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_LG2GC_ACK_GET_ACCOUNT_TAKEN);
class CMsgLoginSystemLG2GCAckGetAccountToken: public GFLib::CMessage
{
public:
    CMsgLoginSystemLG2GCAckGetAccountToken() : GFLib::CMessage(MsgIDLoginSystemLG2GCAckGetAccountToken)
    {
        m_state = EGETACCOUNTTAKEN_SUCCESS;
        m_accountToken = "";
        m_accountID = 0;
    }

protected:
    bool _serializeTo(BSLib::Utility::CStream& stream) const
    {
        stream << m_state;
        stream << m_accountToken;
        stream << m_accountID;
        return true;
    }
public:
    BSLib::uint32 m_state;
    std::string m_accountToken;
    BSLib::uint64 m_accountID;
};

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_MSGLOGINSYSTEM_H__
