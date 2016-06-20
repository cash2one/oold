//////////////////////////////////////////////////////////////////////
//	created:	2012/08/05
//	filename: 	GFLib\commonServer\message\msgServerLink.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GFLIB_COMMONSERVER_MESSAGE_MSGSERVERLINK_H__
#define __GFLIB_COMMONSERVER_MESSAGE_MSGSERVERLINK_H__

#include <GFLib/commonServer/message/funcType.h>
#include <GFLib/commonServer/message/message.h>

#define GFLIB_USER_NAME_MAX 32
#define GFLIB_USER_PWD_MAX 32
#define GFLIB_IP_TEXT_MAX 15
#define GFLIB_KEY_NAME_MAX 16

namespace GFLib
{

enum EFuncServerLinkID
{
	//服务器之间互联，交互服务器信息
	EMSGNUMID_SERVERLINK_XX2XS_REQ_SERVERID = 1,
	EMSGNUMID_SERVERLINK_XS2XX_RES_SERVERID,
	
	//客户端与服务器之间的ping包
	EMSGNUMID_SERVERLINK_XS2XX_REQ_PING,
	EMSGNUMID_SERVERLINK_XX2XS_RES_PING,

	//转发消息
	EMSGNUMID_SERVERLINK_XX2XX_NTF_TRANSFER,
};

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

//服务器之间互换身份消息
const BSLib::uint32 MsgIDServerLinkXX2XSReqServerID = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_SERVER_LINK, EMSGNUMID_SERVERLINK_XX2XS_REQ_SERVERID);
struct SMsgServerLinkXX2XSReqServerID: public SMessage
{
	SServerID m_serverID;
	char m_key[GFLIB_KEY_NAME_MAX + 1];
	SMsgServerLinkXX2XSReqServerID() : SMessage(MsgIDServerLinkXX2XSReqServerID)
	{
		m_serverID = INVALID_SERVERID;
		memset(m_key, 0, sizeof(m_key));
	}

	void setKeyName(const std::string& keyName)
	{
		strncpy(m_key, keyName.c_str(), GFLIB_KEY_NAME_MAX);
	}

};

const BSLib::uint32 MsgIDServerLinkXS2XXResServerID = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANY, EFUNCTYPE_SERVER_LINK, EMSGNUMID_SERVERLINK_XS2XX_RES_SERVERID);
struct SMsgServerLinkXS2XXResServerID: public SMessage
{
	SServerID m_serverID;
	char m_keyName[GFLIB_KEY_NAME_MAX + 1];
	SMsgServerLinkXS2XXResServerID() : SMessage(MsgIDServerLinkXS2XXResServerID)
	{
		m_serverID = INVALID_SERVERID;
		memset(m_keyName, 0, sizeof(m_keyName));
	}

	void setKey(const std::string& keyName)
	{
		strncpy(m_keyName, keyName.c_str(), GFLIB_KEY_NAME_MAX);
	}

};

//客户端与服务器之间的ping包
const BSLib::uint32 MsgIDServerLinkXS2XXReqPing = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANY, EFUNCTYPE_SERVER_LINK, EMSGNUMID_SERVERLINK_XS2XX_REQ_PING);
struct SMsgServerLinkXS2XXReqPing: public SMessage
{
	SMsgServerLinkXS2XXReqPing() : SMessage(MsgIDServerLinkXS2XXReqPing)
	{
		;
	}
};

const BSLib::uint32 MsgIDServerLinkXX2XSResPing = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANYSERVER, EFUNCTYPE_SERVER_LINK, EMSGNUMID_SERVERLINK_XX2XS_RES_PING);
struct SMsgServerLinkXX2XSResPing: public SMessage
{
	SMsgServerLinkXX2XSResPing() : SMessage(MsgIDServerLinkXX2XSResPing)
	{
		;
	}
};

//转发消息
const BSLib::uint32 MsgIDServerLinkXX2XXNtfTransfer = GFLIB_MSGID_DEBUG(GFLib::SRVTYPE_ANY, EFUNCTYPE_SERVER_LINK, EMSGNUMID_SERVERLINK_XX2XX_NTF_TRANSFER);
struct SMsgServerLinkXX2XXNtfTransfer: public SMessage
{
	SServerID m_serverIDFrome;
	SServerID m_serverIDTo;
	SAccountKey m_accountKey;

	BSLib::uint32 m_msgSize;
	char m_msg[1];

	SMsgServerLinkXX2XXNtfTransfer() : SMessage(MsgIDServerLinkXX2XXNtfTransfer)
	{
		m_serverIDFrome = INVALID_SERVERID;
		m_serverIDTo = INVALID_SERVERID;
		m_msgSize = 0;
	}

	BSLib::uint32 getSize() { return sizeof(SMsgServerLinkXX2XXNtfTransfer) + m_msgSize - 1;}
};

#ifdef WIN32
#pragma pack (pop)
#else
#pragma pack ()
#endif

}//GFLib

#endif//__GFLIB_COMMONSERVER_MESSAGE_MSGSERVERLINK_H__


