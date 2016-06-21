#ifndef __GSLIB_LOGINSYSTEM_MSGLOGINSYSTEMAC_H__
#define __GSLIB_LOGINSYSTEM_MSGLOGINSYSTEMAC_H__

#include <GSLib/loginSystem/msgNumIDLoginSystem.h>

namespace GSLib
{

namespace LoginSystem
{

//////////////////////////////////////////////////////////////////////////
const BSLib::uint32 MsgIDLoginSystemSP2ACReqCheckToken = GFLIB_MSGID_DEBUG(SRVTYPE_AUTHCODESERVER, EFUNCTYPE_LOGINSYSTEM, EMSGNUMID_LOGINSYSTEM_SP2AC_REQ_CHECK_TAKEN);
class CMsgLoginSystemSP2ACReqCheckToken : public GFLib::CMessage
{
public:
	CMsgLoginSystemSP2ACReqCheckToken() : GFLib::CMessage(MsgIDLoginSystemSP2ACReqCheckToken)
	{
		m_serverID = GFLib::INVALID_SERVERID;
		m_sessionID = 0;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_token;
		stream << m_accountName;
		stream << m_accountKey;
		stream << m_serverID;
		stream << m_sessionID;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_token;
		stream >> m_accountName;
		stream >> m_accountKey;
		stream >> m_serverID;
		stream >> m_sessionID;
		return true;
	}

public:
	std::string m_token;
	std::string m_accountName;
	GFLib::SAccountKey m_accountKey;
	GFLib::SServerID m_serverID;
	BSLib::uint32 m_sessionID;
};

}//LoginSystem

}//GSLib

#endif//__GSLIB_LOGINSYSTEM_MSGLOGINSYSTEMAC_H__

