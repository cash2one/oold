#ifndef __GAMESERVER_MESSAGE_MSGSYSCHANNEL_H__
#define __GAMESERVER_MESSAGE_MSGSYSCHANNEL_H__

#include <GFLib/commonServer/message/message.h>
#include <GFLib/commonServer/message/funcType.h>
#include <GFLib/commonServer/message/msgServerLink.h>


#define GFLIB_COMMAND_TEXT_MAX 255

namespace GFLib
{

enum EFuncSysChannelID
{
	EMSGID_SYSCHANNEL_LC2LC_REQ_SERVERINFO = 1,
	EMSGID_SYSCHANNEL_LC2LC_RES_SERVERINFO,
	EMSGID_SYSCHANNEL_LC2LC_NTF_COMMAND,
};

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

const BSLib::uint32 MsgIDSysChannelLC2LCReqServerInfo = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_LOCAL, EFUNCTYPE_SYSTEM_CHANNEL, EMSGID_SYSCHANNEL_LC2LC_REQ_SERVERINFO);
struct SMsgSysChannelLC2LCReqServerInfo: public GFLib::SMessage
{
	SMsgSysChannelLC2LCReqServerInfo() : GFLib::SMessage(MsgIDSysChannelLC2LCReqServerInfo)
	{
		;
	}
};

const BSLib::uint32 MsgIDSysChannelLC2LCResServerInfo = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_LOCAL, EFUNCTYPE_SYSTEM_CHANNEL, EMSGID_SYSCHANNEL_LC2LC_RES_SERVERINFO);
struct SMsgSysChannelLC2LCResServerInfo: public GFLib::SMessage
{
	SServerID m_localServerID;
	char m_localKeyName[GFLIB_KEY_NAME_MAX + 1];
	SMsgSysChannelLC2LCResServerInfo() : GFLib::SMessage(MsgIDSysChannelLC2LCResServerInfo)
	{
		m_localServerID = INVALID_SERVERID;
		memset(m_localKeyName, 0, sizeof(m_localKeyName));
	}

	void setLocalKeyName(const std::string& keyName)
	{
		strncpy(m_localKeyName, keyName.c_str(), GFLIB_KEY_NAME_MAX);
	}
};

const BSLib::uint32 MsgIDSysChannelLC2LCNtfCommand = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_LOCAL, EFUNCTYPE_SYSTEM_CHANNEL, EMSGID_SYSCHANNEL_LC2LC_NTF_COMMAND);
struct SMsgSysChannelLC2LCNtfCommand: public GFLib::SMessage
{
	char m_command[GFLIB_COMMAND_TEXT_MAX + 1];
	SMsgSysChannelLC2LCNtfCommand() : GFLib::SMessage(MsgIDSysChannelLC2LCNtfCommand)
	{
		memset(m_command, 0, sizeof(m_command));
	}

	void setCommand(const std::string& command)
	{
		strncpy(m_command, command.c_str(), GFLIB_COMMAND_TEXT_MAX);
	}
};

#ifdef WIN32
#pragma pack (pop) 
#else
#pragma pack ()
#endif

}//GFLib

#endif//__GAMESERVER_MESSAGE_MSGSYSCHANNEL_H__




