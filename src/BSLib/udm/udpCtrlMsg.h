#ifndef __BSLIB_UDM_UDPCTRLMSG_H__
#define __BSLIB_UDM_UDPCTRLMSG_H__

#include <BSLib/utility/thread/thread.h>
#include <BSLib/network/sockAddr.h>

#define BSLIB_UDM_UDPCTRL_FLAGE 0X81
#define BSLIB_UDM_UDPDATA_FLAGE 0X7E

namespace BSLib
{

namespace UDM
{

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

struct SUdpCtrlMsg
{
public:
	SUdpCtrlMsg(uint8 msgID = 0, uint8 flag = BSLIB_UDM_UDPCTRL_FLAGE) : m_flag(flag), m_msgID(msgID){}

	bool isCtrlMsg() { return (m_flag & BSLIB_UDM_UDPCTRL_FLAGE) == BSLIB_UDM_UDPCTRL_FLAGE; }
	bool isDataMsg() { return m_flag == BSLIB_UDM_UDPDATA_FLAGE; }

	uint8 getMsgID() { return m_msgID; }

private:
	uint8 m_flag;
	uint8 m_msgID;
};

struct SUdpDataMsg : public SUdpCtrlMsg
{
public:
	SUdpDataMsg() : SUdpCtrlMsg(0, BSLIB_UDM_UDPDATA_FLAGE) {}

public:
	int m_msgSize;
	char m_msg[1];

	int getSize() { return sizeof(SUdpDataMsg) + m_msgSize - 1; }
};

enum EUdpCtrlMsgID
{
	EMID_PC2PS_REQ_CONNECT = 1,
	EMID_PS2PC_RES_CONNECT,
	EMID_PC2PS_NTF_CONNECT,

	EMID_PS2PC_REQ_PING,
	EMID_PC2PS_RES_PING,

	EMID_PC2PS_REQ_PING,
	EMID_PS2PC_RES_PING,

	EMID_PS2PC_NTF_CLOSE,
	EMID_PC2PS_REQ_CLOSE,
	EMID_PS2PC_RES_CLOSE,
	EMID_PC2PS_NTF_CLOSE,
};

//连接消息
struct SMsgPc2PsReqConnect : public SUdpCtrlMsg
{
public:
	SMsgPc2PsReqConnect() : SUdpCtrlMsg(EMID_PC2PS_REQ_CONNECT)
	{
		;
	}
};

struct SMsgPs2PcResConnect : public SUdpCtrlMsg
{
public:
	SMsgPs2PcResConnect() : SUdpCtrlMsg(EMID_PS2PC_RES_CONNECT)
	{
		;
	}
};

struct SMsgPc2PsNtfConnect : public SUdpCtrlMsg
{
public:
	SMsgPc2PsNtfConnect() : SUdpCtrlMsg(EMID_PC2PS_NTF_CONNECT)
	{
		;
	}
};

//心跳包消息
struct SMsgPs2PcReqPing : public SUdpCtrlMsg
{
public:
	SMsgPs2PcReqPing() : SUdpCtrlMsg(EMID_PS2PC_REQ_PING)
	{
		;
	}
};

struct SMsgPc2PsResPing : public SUdpCtrlMsg
{
public:
	SMsgPc2PsResPing() : SUdpCtrlMsg(EMID_PC2PS_RES_PING)
	{
		;
	}
};
 
struct SMsgPc2PsReqPing : public SUdpCtrlMsg
{
public:
	SMsgPc2PsReqPing() : SUdpCtrlMsg(EMID_PC2PS_REQ_PING)
	{
		;
	}
};

struct SMsgPs2PcResPing : public SUdpCtrlMsg
{
public:
	SMsgPs2PcResPing() : SUdpCtrlMsg(EMID_PS2PC_RES_PING)
	{
		;
	}
};

//退出消息
struct SMsgPs2PcNtfClose : public SUdpCtrlMsg
{
public:
	SMsgPs2PcNtfClose() : SUdpCtrlMsg(EMID_PS2PC_NTF_CLOSE)
	{
		;
	}
};

struct SMsgPc2PsReqClose : public SUdpCtrlMsg
{
public:
	SMsgPc2PsReqClose() : SUdpCtrlMsg(EMID_PC2PS_REQ_CLOSE)
	{
		;
	}
};

struct SMsgPs2PcResClose : public SUdpCtrlMsg
{
public:
	SMsgPs2PcResClose() : SUdpCtrlMsg(EMID_PS2PC_RES_CLOSE)
	{
		;
	}
};

struct SMsgPc2PsNtfClose : public SUdpCtrlMsg
{
public:
	SMsgPc2PsNtfClose() : SUdpCtrlMsg(EMID_PC2PS_NTF_CLOSE)
	{
		;
	}
};


#ifdef WIN32
#pragma pack (pop)
#else
#pragma pack ()
#endif

}//UDM

}//BSLib

#endif//__BSLIB_UDM_UDPCTRLMSG_H__



