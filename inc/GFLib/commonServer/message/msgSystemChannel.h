//////////////////////////////////////////////////////////////////////
//	created:	2013/06/09
//	filename:	GFLib\commonServer\message\msgSysChannel.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
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
	EMSGID_SYSCHANNEL_LC2LC_REQ_SERVERINFOR = 1,
	EMSGID_SYSCHANNEL_LC2LC_RES_SERVERINFOR,
	EMSGID_SYSCHANNEL_LC2LC_NTF_COMMAND,
};

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

const BSLib::uint32 MsgIDSysChannelLC2LCReqServerInfor = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_LOCAL, EFUNCTYPE_SYSTEM_CHANNEL, EMSGID_SYSCHANNEL_LC2LC_REQ_SERVERINFOR);
struct SMsgSysChannelLC2LCReqServerInfor: public GFLib::SMessage
{
	SMsgSysChannelLC2LCReqServerInfor() : GFLib::SMessage(MsgIDSysChannelLC2LCReqServerInfor)
	{
		;
	}
};

const BSLib::uint32 MsgIDSysChannelLC2LCResServerInfor = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_LOCAL, EFUNCTYPE_SYSTEM_CHANNEL, EMSGID_SYSCHANNEL_LC2LC_RES_SERVERINFOR);
struct SMsgSysChannelLC2LCResServerInfor: public GFLib::SMessage
{
	SServerID m_localServerID;
	char m_localKeyName[GFLIB_KEY_NAME_MAX + 1];
	SMsgSysChannelLC2LCResServerInfor() : GFLib::SMessage(MsgIDSysChannelLC2LCResServerInfor)
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



