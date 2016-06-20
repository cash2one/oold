//////////////////////////////////////////////////////////////////////
//	created:	2013/10/27
//	filename:	GFLib\commonServer\message\msgLocalServer.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GAMESERVER_MESSAGE_MSGLOCALSERVER_H__
#define __GAMESERVER_MESSAGE_MSGLOCALSERVER_H__

#include <GFLib/commonServer/message/message.h>
#include <GFLib/commonServer/message/funcType.h>
#include <GFLib/commonServer/message/msgServerLink.h>


#define GFLIB_COMMAND_TEXT_MAX 255

namespace GFLib
{

enum EFuncLocalServerID
{
	EMSGID_SERVERLOCAL_LC2LC_NTF_SERVERENTER = 1,
	EMSGID_SERVERLOCAL_LC2LC_NTF_SERVERLEAVE,

	EMSGID_SERVERLOCAL_LC2LC_NTF_COMMAND,
};

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

const BSLib::uint32 MsgIDServerLocalLC2LCNtfServerEnter = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_LOCAL, EFUNCTYPE_SERVER_LOCAL, EMSGID_SERVERLOCAL_LC2LC_NTF_SERVERENTER);
struct SMsgServerLocalLC2LCNtfServerEnter: public GFLib::SMessage
{
	SServerID m_enterServerID;
	char m_enterServerKey[GFLIB_KEY_NAME_MAX + 1];
	SMsgServerLocalLC2LCNtfServerEnter() : GFLib::SMessage(MsgIDServerLocalLC2LCNtfServerEnter)
	{
		m_enterServerID = INVALID_SERVERID;
		memset(m_enterServerKey, 0, sizeof(m_enterServerKey));
	}

	void setServerKey(const std::string& a_serverKey)
	{
		strncpy(m_enterServerKey, a_serverKey.c_str(), GFLIB_KEY_NAME_MAX);
	}
};

const BSLib::uint32 MsgIDServerLocalLC2LCNtfServerLeave = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_LOCAL, EFUNCTYPE_SERVER_LOCAL, EMSGID_SERVERLOCAL_LC2LC_NTF_SERVERLEAVE);
struct SMsgServerLocalLC2LCNtfServerLeave: public GFLib::SMessage
{
	SServerID m_leaveServerID;
	char m_leaveServerKey[GFLIB_KEY_NAME_MAX + 1];
	SMsgServerLocalLC2LCNtfServerLeave() : GFLib::SMessage(MsgIDServerLocalLC2LCNtfServerLeave)
	{
		m_leaveServerID = INVALID_SERVERID;
		memset(m_leaveServerKey, 0, sizeof(m_leaveServerKey));
	}

	void setServerKey(const std::string& a_serverKey)
	{
		strncpy(m_leaveServerKey, a_serverKey.c_str(), GFLIB_KEY_NAME_MAX);
	}
};

#ifdef WIN32
#pragma pack (pop) 
#else
#pragma pack ()
#endif

const BSLib::uint32 MsgIDServerLocalLC2LCNtfCommand = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_LOCAL, EFUNCTYPE_SERVER_LOCAL, EMSGID_SERVERLOCAL_LC2LC_NTF_COMMAND);
struct CMsgServerLocalLC2LCNtfCommand: public GFLib::CMessage
{
public:
	CMsgServerLocalLC2LCNtfCommand() : GFLib::CMessage(MsgIDServerLocalLC2LCNtfCommand)
	{
		;
	}

protected:
	bool _serializeTo(BSLib::Utility::CStream& stream) const
	{
		stream << m_command;
		return true;
	}

	bool _serializeFrom(BSLib::Utility::CStream& stream)
	{
		stream >> m_command;
		return true;
	}

public:
	std::string m_command;
};

}//GFLib

#endif//__GAMESERVER_MESSAGE_MSGLOCALSERVER_H__



