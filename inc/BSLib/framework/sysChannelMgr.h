#ifndef __BSLIB_FRAMEWORK_SYSCHANNELMGR_H__
#define __BSLIB_FRAMEWORK_SYSCHANNELMGR_H__

#include <BSLib/utility/thread/mutex.h>
#include <BSLib/utility/memory/shareMemory.h>
#include <BSLib/utility/thread/thread.h>
#include <BSLib/framework/baseDef.h>
#include <BSLib/framework/message/message.h>
#include <BSLib/framework/message/msgLabel.h>

#define GFLIB_COMMONSERVER_SYSCHANNEL_MAX 32
#define GFLIB_COMMONSERVER_SYSMSGBUFF_MAX 1024*1024

namespace BSLib
{

namespace Framework
{

struct SSysChannelHead;
struct SSysChannelItemLocal;

enum ESysMsgType
{
	ESYSMSGTYPE_REGISTER = 1,
	ESYSMSGTYPE_MESSAGE,
	ESYSMSGTYPE_CLOSE,
	ESYSMSGTYPE_TERMINATE,
};

class BSLIB_FRAMEWORK_API CSysChannelMgr
{
public:
	CSysChannelMgr();
	virtual ~CSysChannelMgr();

public:
	virtual bool init(BSLib::uint32 a_sysKey);
	virtual void final();
	void terminate();
	
	bool sendMsg(CChannelID& a_channelIDTo, SMessage* a_msg, int a_msgSize);
	bool sendMsg(CChannelID& a_channelIDTo, SMessage* a_msg, SSysMsgLabel* msgLabel, int msgLabelSize);
	bool sendMsgToLocalAll(SMessage* a_msg, int a_msgSize);
	bool sendMsgToLocalAll(SMessage* a_msg, SSysMsgLabel* msgLabel, int msgLabelSize);

	bool sendSysMsg(BSLib::uint8 a_channelLocalNumberTo, ESysMsgType a_sysMsgType);
	bool sendSysMsgToLocalAll(ESysMsgType a_sysMsgType);

protected:
	virtual void _initChannel() = 0;
	virtual void _finalChannel() = 0;
	virtual void _parseSysMsg(CChannelID& a_channelIDFrom, ESysMsgType a_sysMsgType) = 0;
	virtual void _parseMsg(SMessage* a_msg, SSysMsgLabel* msgLabel) = 0; 

	virtual void _onSysMsgRegister(BSLib::uint32 a_para1);
	virtual void _onSysMsgMessage(BSLib::uint32 a_para1, void* a_para3);
	virtual void _onSysMsgClose(BSLib::uint32 a_para1);
	virtual void _onSysMsgTerminate();

private:
	bool _initChannelInfor(BSLib::uint32 a_sysKey);
	int _run(void* a_para);

private:
	BSLib::Utility::CMutex m_mutex;
	BSLib::Utility::CMutexProcess m_mutexProcess;
	BSLib::Utility::CShareMemory m_shareMemoryOfHead;
	BSLib::Utility::CHndThread m_recvMsgThread;
	bool m_isRunning;
	SSysChannelHead* m_sysChannelHead;
	CChannelID m_channelID;

	SSysChannelItemLocal* m_sysChannelItems[GFLIB_COMMONSERVER_SYSCHANNEL_MAX];
};

}//Framework


}//BSLib

#endif//__BSLIB_FRAMEWORK_SYSCHANNELMGR_H__




