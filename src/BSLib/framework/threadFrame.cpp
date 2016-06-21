#include <BSLib/utility/tracer.h>
#include <BSLib/framework/threadFrame.h>
#include <BSLib/framework/message/msgFramework.h>
#include <BSLib/framework/message/msgFactory.h>

#define BSLIB_FRAMEWORK_MSGQUEUE_WAIT_TIMEOUT 10

namespace BSLib
{

namespace Framework
{

CThreadFrame::CThreadFrame()
: m_isTerminate(false)
, m_isValid(false)
, m_msgQueue(&m_event)
, m_lastMilliseconds(0)
, m_delayTimer(0)
//, m_updateTimer_1(0)
{
	;
}

CThreadFrame::~CThreadFrame()
{
	;
}

void CThreadFrame::terminate()
{
	if (isTerminate()) {
		return ;
	}
	SMsgFrameworkNtfTerminate ntfTerminate;
	sendMsg(&ntfTerminate, sizeof(ntfTerminate));
}

bool CThreadFrame::sendMsg(CMessage& msg)
{
	BSLib::Utility::CStream stream;
	if (!msg.serializeTo(stream)){
		return false;
	}
	return sendMsg((SMessage*)stream.readPtr(), (int)stream.readSize());
}

bool CThreadFrame::sendMsg(CMessage& msg, SMsgLabel* msgLabel, int msgLabelSize)
{
	BSLib::Utility::CStream stream;
	if (!msg.serializeTo(stream)){
		return false;
	}
	return sendMsg((SMessage*)stream.readPtr(), (int)stream.readSize(), msgLabel, msgLabelSize);
}

bool CThreadFrame::sendMsg(SMessage* msg, int msgSize)
{
	if (isTerminate()) {
		return false;
	}
	SMsgLabel msgLabel;
	msgLabel.m_msgSize = msgSize;
	return sendMsg(msg, msgSize, &msgLabel, sizeof(msgLabel));
}

bool CThreadFrame::sendMsg(SMessage* msg, int msgSize, SMsgLabel* msgLabel, int msgLabelSize)
{
	if (isTerminate()) {
		return false;
	}
	m_mutex.lock();
	msgLabel->m_msgSize = msgSize;
	if (m_msgQueue.push(msg, msgSize, msgLabel, msgLabelSize)) {
		m_mutex.unlock();
		return true;
	}
	m_mutex.unlock();
	return false;
}

bool CThreadFrame::_init()
{
	BSLib::Utility::CRealTime* realTime = getRealTime();
	if (realTime == NULL) {
		return false;
	}
	realTime->now();
	m_lastMilliseconds = realTime->milliseconds();
	//m_updateTimer_1.reset(1000, *realTime);

	CMsgExecPtr msgExecPtr = new CMsgExec(&CThreadFrame::_onMsgNtfTerminate, this);
	if (msgExecPtr == NULL){
		return false;
	}
	if (!m_msgExecMgr.addMsgExecPtr(EMT_FRAMEWORK, EMID_FRAMEWORK_NTF_TERMINATE, msgExecPtr)) {
		return false;
	}
	return true;
}

int CThreadFrame::_main()
{
	m_isValid = true;
	m_isTerminate = false;

	BSLib::Utility::CRealTime* realTime = m_timerServer.getRealTime();
	if (realTime == NULL) {
		return -1;
	}

	if (_init()){
		while(!isTerminate()){

			realTime->now();
			BSLib::int64 currentMilliseconds = realTime->milliseconds();
			
			m_delayTimer = currentMilliseconds - m_lastMilliseconds;
			m_lastMilliseconds = currentMilliseconds;

			m_timerServer.update();

			if (!_callback()){
				break;
			}
// 			if (m_updateTimer_1(*realTime)) {
// 				_update_1000();
// 			}

			realTime->now();
			currentMilliseconds = realTime->milliseconds();

			BSLib::int64 useTimer = currentMilliseconds - m_lastMilliseconds;
			if (useTimer < BSLIB_FRAMEWORK_MSGQUEUE_WAIT_TIMEOUT) {
				_waitMsg((BSLib::uint32)(BSLIB_FRAMEWORK_MSGQUEUE_WAIT_TIMEOUT - useTimer));
			} else {
				_waitMsg(1);
			}
		}
	}

	m_isTerminate = true;

	int res = _final();

	m_isValid = false;
	m_msgQueue.clear();

	return res;
}

int CThreadFrame::_final()
{
	CMsgDebug::singleton().clear();
	m_msgExecMgr.clear();
	return 0;
}

bool CThreadFrame::_callback()
{
	_parseMsg();
	return true;
}

// void CThreadFrame::_update_1000()
// {
// 	;
// }

void CThreadFrame::_parseMsg()
{
	SMessage* msg = NULL;
	SMsgLabel* msgLable = NULL;
	uint32 msgLableSize = 0;

	BSLib::uint32 count = 0;

	while (!m_msgQueue.empty()){
		count++;
		if (count >= 500000) {
			break;
		}
		BSLib::uint32 msgSize = m_msgQueue.get(&msg, &msgLable, &msgLableSize);
		if (msgSize <= 0) {
			break;
		}
		if (msgLable->m_msgSize != msgSize) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "��Ϣ��С����, ������Ϣ[%s][%s]",
				msg->toString().c_str(),
				CMsgDebug::singleton().getPrompt(msg).c_str());
			m_msgQueue.pop();
			continue;
		}
		CMessage* cmsg = CMsgFactory::singleton().createCMessage(msg->getUniqueID());
		if (cmsg != NULL) {
			cmsg->serializeFrom(msg, msgLable->m_msgSize);
			if (m_msgExecMgr.executeMessage(msgLable, cmsg)) {
				m_msgQueue.pop();
				BSLIB_SAFE_DELETE(cmsg);
				continue;
			}
			BSLIB_SAFE_DELETE(cmsg);
		} else {
			if (m_msgExecMgr.executeMessage(msgLable, msg)) {
				m_msgQueue.pop();
				continue;
			}
		}
		
		BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "û�д���������Ϣ[%s][%s]",
			msg->toString().c_str(),
			CMsgDebug::singleton().getPrompt(msg).c_str());

		m_msgQueue.pop();
	}

}

void CThreadFrame::_waitMsg(uint32 a_timeout)
{
	m_event.wait(a_timeout);
}

void CThreadFrame::_onMsgNtfTerminate(SMsgLabel* lable, SMessage* msg)
{
	m_isTerminate = true;
}


}//Framework

}//BSLib


