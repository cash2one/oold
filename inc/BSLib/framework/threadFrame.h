//////////////////////////////////////////////////////////////////////
//	created:	2012/07/22
//	filename: 	BSLib\framework\threadFrame.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_FRAMEWORK_THREADFRAME_H__
#define __BSLIB_FRAMEWORK_THREADFRAME_H__

#include <BSLib/utility/thread/mutex.h>
#include <BSLib/utility/thread/threadData.h>
#include <BSLib/utility/timerServer.h>
#include <BSLib/framework/message/msgExecMgr.h>
#include <BSLib/framework/message/msgQueue.h>

namespace BSLib
{

namespace Framework
{

#define BSLIB_FRAMEWORK_MSGQUEUE_MAX 64

class BSLIB_FRAMEWORK_API CThreadFrame
{
public:
	CThreadFrame();
	virtual ~CThreadFrame();

	bool isValid() { return m_isValid; }
	virtual bool isTerminate() { return m_isTerminate; }

	void terminate();

	bool sendMsg(CMessage& msg);
	bool sendMsg(CMessage& msg, SMsgLabel* msgLabel, int msgLabelSize);
	bool sendMsg(SMessage* msg, int msgSize);
	bool sendMsg(SMessage* msg, int msgSize, SMsgLabel* msgLabel, int msgLabelSize);

	BSLib::Utility::CRealTime* getRealTime() { return m_timerServer.getRealTime(); }
	BSLib::int64 getDelayTimer() { return m_delayTimer; }

protected:
	virtual bool _init();
	virtual int _main();
	virtual int _final();
	virtual bool _callback();

	//virtual void _update_1000();
	
	CMsgExecMgr* _getMsgExecMgr() { return &m_msgExecMgr; }
	BSLib::Utility::CTimerServer* _getTimerServer() { return &m_timerServer; }

	
	void _parseMsg();
	void _waitMsg(uint32 a_timeout);

private:
	void _onMsgNtfTerminate(SMsgLabel* lable, SMessage* msg);

private:
	CMsgExecMgr m_msgExecMgr;
	bool m_isTerminate;
	bool m_isValid;
	BSLib::Utility::CEvent m_event;
	BSLib::Utility::CMutex m_mutex; 
	CMsgQueue m_msgQueue;
	BSLib::Utility::CTimerServer m_timerServer;

	BSLib::int64 m_lastMilliseconds;
	BSLib::int64 m_delayTimer;
	//BSLib::Utility::CDelayTimer m_updateTimer_1;
};

}//Framework

}//BSLib

#endif //__BSLIB_FRAMEWORK_THREADFRAME_H__

