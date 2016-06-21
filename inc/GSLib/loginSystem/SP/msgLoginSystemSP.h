#ifndef __GSLIB_LOGINSYSTEM_SP_MSGLOGINSYSTEMSP_H__
#define __GSLIB_LOGINSYSTEM_SP_MSGLOGINSYSTEMSP_H__

#include <GSLib/loginSystem/msgNumIDLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

const BSLib::uint32 MsgIDLoginSystemLG2SPReqRegisterToken = GFLIB_MSGID_DEBUG(SRVTYPE_SUPERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_LG2SP_REQ_REGISTER_TOKEN);
class CMsgLoginSystemLG2SPReqRegisterToken: public GFLib::CMessage
{
public:
	CMsgLoginSystemLG2SPReqRegisterToken() : GFLib::CMessage(MsgIDLoginSystemLG2SPReqRegisterToken)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_loginSession;
		stream << m_token;
		stream << m_accountKey;
		stream << m_accountName;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_loginSession;
		stream >> m_token;
		stream >> m_accountKey;
		stream >> m_accountName;
		return true;
	}
public:
	BSLib::uint32 m_loginSession;
	GFLib::SAccountKey m_accountKey;
	std::string m_accountName;
	std::string m_token;
};

const BSLib::uint32 MsgIDLoginSystemLG2SPReqCheckToken = GFLIB_MSGID_DEBUG(SRVTYPE_SUPERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_LG2SP_REQ_CHECK_TOKEN);
class CMsgLoginSystemLG2SPReqCheckToken: public GFLib::CMessage
{
public:
	CMsgLoginSystemLG2SPReqCheckToken() : GFLib::CMessage(MsgIDLoginSystemLG2SPReqCheckToken)
	{
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_loginSession;
		stream << m_token;
		stream << m_accountKey;
		stream << m_accountName;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_loginSession;
		stream >> m_token;
		stream >> m_accountKey;
		stream >> m_accountName;
		return true;
	}

public:
	BSLib::uint32 m_loginSession;
	GFLib::SAccountKey m_accountKey;
	std::string m_accountName;
	std::string m_token;
};

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemAC2SPAckCheckToken = GFLIB_MSGID_DEBUG(SRVTYPE_SUPERSERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_AC2SP_ACK_CHECK_TAKEN);
class CMsgLoginSystemAC2SPAckCheckToken : public GFLib::CMessage
{
public:
	CMsgLoginSystemAC2SPAckCheckToken() : GFLib::CMessage(MsgIDLoginSystemAC2SPAckCheckToken)
	{
		m_result = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_accountName;
		stream << m_token;
		stream << m_result;
		stream << m_accountKey;
		stream << m_serverID;
		stream << m_sessionID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_accountName;
		stream >> m_token;
		stream >> m_result;
		stream >> m_accountKey;
		stream >> m_serverID;
		stream >> m_sessionID;
		return true;
	}

public:
	std::string m_accountName;
	std::string m_token;
	BSLib::uint32 m_result;//1 ³É¹¦£¬0Ê§°Ü
	GFLib::SAccountKey m_accountKey;
	GFLib::SServerID m_serverID;
	BSLib::uint32 m_sessionID;
};

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_SP_MSGLOGINSYSTEMSP_H__

