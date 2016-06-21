#include <BSLib/utility/random.h>
#include <BSLib/utility/thread/thdMsgQueue.h>
#include <BSLib/utility/tracer.h>
#include <BSLib/framework/sysChannelMgr.h>

namespace BSLib
{

namespace Framework
{

//////////////////////////////////////////////////////////////////////////
enum ESysChannelState
{
	ESYSCHNNLST_NULL = 0,
	ESYSCHNNLST_REGISTER,
	ESYSCHNNLST_RUNNING,
	ESYSCHNNLST_CLOSE,
};

#ifdef WIN32
#pragma pack (push, 1)
#else
#pragma pack (1)
#endif

struct SSysChannelItem
{
	ESysChannelState m_state;
	BSLib::Utility::HndThdMsgQueue m_msgQueueHand;
	BSLib::uint32 m_shmKey;
};

struct SSysChannelHead
{
	BSLib::uint8 m_count;
	SSysChannelItem m_sysChannelItem[GFLIB_COMMONSERVER_SYSCHANNEL_MAX];
};

struct SSysChannelMsgBuff
{
	BSLib::uint32 m_maxSize;
	BSLib::uint32 m_currentPos;
	BSLib::uint8 m_msgBuff[1];
};

struct SSysMsgHead
{
	BSLib::uint8 m_localNumberFrom;
	BSLib::uint8 m_localNumberTo;
	BSLib::uint32 m_checkCond;
	BSLib::uint32 m_sysMsgSize;
	BSLib::uint8 m_sysMsg[1];
};

#ifdef WIN32
#pragma pack (pop)
#else
#pragma pack ()
#endif

struct SSysChannelItemLocal
{
	BSLib::Utility::HndThdMsgQueue m_msgQueueHand;
	BSLib::Utility::CShareMemory m_shareMemory;
};

//////////////////////////////////////////////////////////////////////////

CSysChannelMgr::CSysChannelMgr()
: m_isRunning(false)
, m_sysChannelHead(NULL)
, m_channelID(INVALID_CHANNELID)
{
	for (BSLib::uint16 i=0; i<GFLIB_COMMONSERVER_SYSCHANNEL_MAX; ++i) {
		m_sysChannelItems[i] = NULL;
	}
}

CSysChannelMgr::~CSysChannelMgr()
{
	final();
}

bool CSysChannelMgr::init(BSLib::uint32 a_sysKey)
{
	if (a_sysKey == 0){
		return false;
	}
	if (!_initChannelInfor(a_sysKey)) {
		return false;
	}
	m_isRunning = true;
	m_recvMsgThread = BSLib::Utility::CHndThread::createThread(&CSysChannelMgr::_run, this, (void*)a_sysKey);
	if (!m_recvMsgThread.isValid()) {
		m_isRunning = false;
		return false;
	}
	return true;
}

void CSysChannelMgr::final()
{
	if (m_recvMsgThread.isValid()) {
		if (m_isRunning) {
			terminate();
		}
		m_recvMsgThread.join();
	}
	BSLib::uint8 localNumber = m_channelID.getLocalNumber();
	if (m_sysChannelHead != NULL && localNumber < GFLIB_COMMONSERVER_SYSCHANNEL_MAX) {
		m_mutexProcess.lock();
		SSysChannelItem* sysChannelItem = &m_sysChannelHead->m_sysChannelItem[localNumber];
		if (sysChannelItem->m_state == ESYSCHNNLST_RUNNING) {
			sendSysMsgToLocalAll(ESYSMSGTYPE_CLOSE);
			sysChannelItem->m_state = ESYSCHNNLST_NULL;
		}
		if (sysChannelItem->m_msgQueueHand != BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID) {
			BSLib::Utility::CThdMsgQueue::remove(sysChannelItem->m_msgQueueHand);
		}
		sysChannelItem->m_msgQueueHand = BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID;
		m_mutexProcess.unlock();
	}

	m_channelID = INVALID_CHANNELID;
	m_sysChannelHead = NULL;
	
	for (BSLib::uint16 i=0; i<GFLIB_COMMONSERVER_SYSCHANNEL_MAX; ++i) {
		if (m_sysChannelItems[i] != NULL) {
			m_sysChannelItems[i]->m_shareMemory.close();
			BSLIB_SAFE_DELETE(m_sysChannelItems[i]);
		}
	}

	m_shareMemoryOfHead.close();
	m_mutexProcess.close();
}

void CSysChannelMgr::terminate()
{
	sendSysMsg(m_channelID.getLocalNumber(), ESYSMSGTYPE_TERMINATE);
}

bool CSysChannelMgr::sendMsg(CChannelID& a_sysMsgIDTo, SMessage* a_msg, int a_msgSize)
{
	SSysMsgLabel sysMsgLabel;
	sysMsgLabel.m_sysMsgIDFrome = m_channelID;
	sysMsgLabel.m_sysMsgIDTo = a_sysMsgIDTo;
	sysMsgLabel.m_msgSize = a_msgSize;

	return sendMsg(a_sysMsgIDTo, a_msg, &sysMsgLabel, sizeof(sysMsgLabel));
}

bool CSysChannelMgr::sendMsg(CChannelID& a_sysMsgIDTo, SMessage* a_msg, SSysMsgLabel* msgLabel, int msgLabelSize)
{
	BSLib::uint8 localNumberTo = a_sysMsgIDTo.getLocalNumber();
	if (localNumberTo >= GFLIB_COMMONSERVER_SYSCHANNEL_MAX) {
		return false;
	}
	BSLib::uint8 localNumber = m_channelID.getLocalNumber();
	if (localNumber >= GFLIB_COMMONSERVER_SYSCHANNEL_MAX) {
		return false;
	}
	if (m_sysChannelItems[localNumber] == NULL || m_sysChannelItems[localNumberTo] == NULL) {
		return false;
	}
	//获取发送目标消息队列句柄
	BSLib::Utility::HndThdMsgQueue msgQueueHandTo = m_sysChannelItems[localNumberTo]->m_msgQueueHand;
	if (msgQueueHandTo == BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID) {
		return false;
	}
	//获取写消息的Buffer
	SSysChannelMsgBuff* sysChannelMsgBuff = (SSysChannelMsgBuff*)m_sysChannelItems[localNumber]->m_shareMemory.getHeadAddress();
	if (sysChannelMsgBuff == NULL) {
		return false;
	}
	BSLib::uint32 currentPos = sysChannelMsgBuff->m_currentPos;
	BSLib::uint32 writeSize = sizeof(SSysMsgHead) - 1 + msgLabelSize + msgLabel->m_msgSize;
	if (currentPos + writeSize > sysChannelMsgBuff->m_maxSize) {
		sysChannelMsgBuff->m_currentPos = 0;
		currentPos = 0;
		if (currentPos + writeSize > sysChannelMsgBuff->m_maxSize) {
			return false;
		}
	}
	//保存消息
	SSysMsgHead* sysMsgHead = (SSysMsgHead*)&sysChannelMsgBuff->m_msgBuff[currentPos];
	sysMsgHead->m_localNumberFrom = m_channelID.getLocalNumber();
	sysMsgHead->m_localNumberTo = a_sysMsgIDTo.getLocalNumber();
	sysMsgHead->m_checkCond = BSLib::Utility::CRandom::randomBetween(0, 16777215);
	sysMsgHead->m_sysMsgSize = msgLabelSize + msgLabel->m_msgSize;
	memcpy(&sysMsgHead->m_sysMsg[0], msgLabel, msgLabelSize);
	memcpy(&sysMsgHead->m_sysMsg[msgLabelSize], a_msg, msgLabel->m_msgSize);
	
	sysChannelMsgBuff->m_currentPos += writeSize;

	BSLib::uint32 para = (sysMsgHead->m_checkCond << 8) + m_channelID.getLocalNumber();

	return BSLib::Utility::CThdMsgQueue::send(msgQueueHandTo, para, ESYSMSGTYPE_MESSAGE, (void*)currentPos);
}

bool CSysChannelMgr::sendMsgToLocalAll(SMessage* a_msg, int a_msgSize)
{
	SSysMsgLabel sysMsgLabel;
	sysMsgLabel.m_sysMsgIDFrome = m_channelID;
	sysMsgLabel.m_sysMsgIDTo = INVALID_CHANNELID;
	sysMsgLabel.m_msgSize = a_msgSize;

	return sendMsgToLocalAll(a_msg, &sysMsgLabel, sizeof(sysMsgLabel));
}

bool CSysChannelMgr::sendMsgToLocalAll(SMessage* a_msg, SSysMsgLabel* msgLabel, int msgLabelSize)
{
	BSLib::uint8 localNumber = m_channelID.getLocalNumber();
	if (localNumber >= GFLIB_COMMONSERVER_SYSCHANNEL_MAX) {
		return false;
	}
	if (m_sysChannelItems[localNumber] == NULL) {
		return false;
	}
	//获取写消息的Buffer
	SSysChannelMsgBuff* sysChannelMsgBuff = (SSysChannelMsgBuff*)m_sysChannelItems[localNumber]->m_shareMemory.getHeadAddress();
	if (sysChannelMsgBuff == NULL) {
		return false;
	}
	BSLib::uint32 currentPos = sysChannelMsgBuff->m_currentPos;
	BSLib::uint32 writeSize = sizeof(SSysMsgHead) - 1 + msgLabelSize + msgLabel->m_msgSize;
	if (currentPos + writeSize > sysChannelMsgBuff->m_maxSize) {
		sysChannelMsgBuff->m_currentPos = 0;
		currentPos = 0;
		if (currentPos + writeSize > sysChannelMsgBuff->m_maxSize) {
			return false;
		}
	}
	//保存消息
	SSysMsgHead* sysMsgHead = (SSysMsgHead*)&sysChannelMsgBuff->m_msgBuff[currentPos];
	sysMsgHead->m_localNumberFrom = m_channelID.getLocalNumber();
	sysMsgHead->m_localNumberTo = 0XFF;
	sysMsgHead->m_checkCond = BSLib::Utility::CRandom::randomBetween(0, 16777215);
	sysMsgHead->m_sysMsgSize = msgLabelSize + msgLabel->m_msgSize;
	memcpy(&sysMsgHead->m_sysMsg[0], msgLabel, msgLabelSize);
	memcpy(&sysMsgHead->m_sysMsg[msgLabelSize], a_msg, msgLabel->m_msgSize);

	sysChannelMsgBuff->m_currentPos += writeSize;

	BSLib::uint32 para = (sysMsgHead->m_checkCond << 8) + m_channelID.getLocalNumber();

	for (int i=0; i<GFLIB_COMMONSERVER_SYSCHANNEL_MAX; ++i) {
		if (i == localNumber) {
			continue;
		}
		if (m_sysChannelItems[i] == NULL) {
			continue;
		}
		BSLib::Utility::HndThdMsgQueue msgQueueHandTo = m_sysChannelItems[i]->m_msgQueueHand;
		if (msgQueueHandTo == BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID) {
			continue;
		}
		BSLib::Utility::CThdMsgQueue::send(msgQueueHandTo, para, ESYSMSGTYPE_MESSAGE, (void*)currentPos);
	}
	return true;
}

bool CSysChannelMgr::sendSysMsg(BSLib::uint8 a_channelLocalNumberTo, ESysMsgType a_sysMsgType)
{
	if (!m_channelID.isValid() || m_channelID.getLocalNumber() >= GFLIB_COMMONSERVER_SYSCHANNEL_MAX) {
		return false;
	}

	if (a_channelLocalNumberTo >= GFLIB_COMMONSERVER_SYSCHANNEL_MAX) {
		return false;
	}
	if (m_sysChannelItems[a_channelLocalNumberTo] == NULL) {
		return false;
	}
	//获取发送目标消息队列句柄
	BSLib::Utility::HndThdMsgQueue msgQueueHandTo = m_sysChannelItems[a_channelLocalNumberTo]->m_msgQueueHand;
	if (msgQueueHandTo == BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID) {
		return false;
	}
	BSLib::uint32 para = m_channelID.getLocalNumber();

	return BSLib::Utility::CThdMsgQueue::send(msgQueueHandTo, para, a_sysMsgType, (void*)NULL);;
}

bool CSysChannelMgr::sendSysMsgToLocalAll(ESysMsgType a_sysMsgType)
{
	if (!m_channelID.isValid() || m_channelID.getLocalNumber() >= GFLIB_COMMONSERVER_SYSCHANNEL_MAX) {
		return false;
	}
	BSLib::uint32 para = m_channelID.getLocalNumber();

	for (int i=0; i<GFLIB_COMMONSERVER_SYSCHANNEL_MAX; ++i) {
		if (m_sysChannelItems[i] == NULL) {
			continue;
		}
		if (i == m_channelID.getLocalNumber()) {
			continue;
		}
		BSLib::Utility::HndThdMsgQueue msgQueueHandTo = m_sysChannelItems[i]->m_msgQueueHand;
		if (msgQueueHandTo == BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID) {
			continue;
		}
		BSLib::Utility::CThdMsgQueue::send(msgQueueHandTo, para, a_sysMsgType, (void*)NULL);
	}

	return true;
}

void CSysChannelMgr::_onSysMsgRegister(BSLib::uint32 a_para1)
{
	BSLib::int32 key = 0;
	BSLib::Utility::HndThdMsgQueue msgQueueHand = BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID;

	BSLib::uint8 channelLocalNumber = (BSLib::uint8)(a_para1 & 0X000000FF);
	if (channelLocalNumber >= GFLIB_COMMONSERVER_SYSCHANNEL_MAX) {
		return;
	}
	m_mutexProcess.lock();
	if (m_sysChannelHead->m_sysChannelItem[channelLocalNumber].m_state != ESYSCHNNLST_RUNNING) {
		m_mutexProcess.unlock();
		return ;
	}
	msgQueueHand = m_sysChannelHead->m_sysChannelItem[channelLocalNumber].m_msgQueueHand;
	if (msgQueueHand == BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID) {
		m_mutexProcess.unlock();
		return ;
	}
	key = m_sysChannelHead->m_sysChannelItem[channelLocalNumber].m_shmKey;
	m_mutexProcess.unlock();

	if (m_sysChannelItems[channelLocalNumber] != NULL) {
		m_sysChannelItems[channelLocalNumber]->m_shareMemory.close();
	} else {
		m_sysChannelItems[channelLocalNumber] = new SSysChannelItemLocal();
		if (m_sysChannelItems[channelLocalNumber] == NULL) {
			return ;
		}
	}
	m_sysChannelItems[channelLocalNumber]->m_msgQueueHand = msgQueueHand;
	if (!m_sysChannelItems[channelLocalNumber]->m_shareMemory.open(key)) {
		return;
	}
// 	CChannelID sysMsgIDFrom;
// 	sysMsgIDFrom.setChannelID(channelLocalNumber);
// 
// 	_parseSysMsg(sysMsgIDFrom, ESYSMSGTYPE_REGISTER);
}

void CSysChannelMgr::_onSysMsgMessage(BSLib::uint32 a_para1, void* a_para3)
{
	BSLib::uint8 channelLocalNumber = (BSLib::uint8)(a_para1 & 0X000000FF);
	if (channelLocalNumber >= GFLIB_COMMONSERVER_SYSCHANNEL_MAX) {
		return;
	}
	BSLib::uint32 checkCode = ((a_para1 & 0XFFFFFF00) >> 8);
	BSLib::uint32 msgPos = (long int)a_para3;

	if (m_sysChannelItems[channelLocalNumber] == NULL) {
		return;
	}
	SSysChannelMsgBuff* sysChannelMsgBuff = (SSysChannelMsgBuff*)m_sysChannelItems[channelLocalNumber]->m_shareMemory.getHeadAddress();
	if (sysChannelMsgBuff == NULL) {
		return;
	}
	if (msgPos > sysChannelMsgBuff->m_maxSize) {
		return;
	}
	SSysMsgHead* sysMsgHead = (SSysMsgHead*)&sysChannelMsgBuff->m_msgBuff[msgPos];
	if (sysMsgHead->m_checkCond != checkCode) {
		return;
	}
	BSLib::uint32 readSize = sizeof(SSysMsgHead) - 1 + sysMsgHead->m_sysMsgSize;
	if (msgPos + readSize > sysChannelMsgBuff->m_maxSize) {
		return;
	}
	if (sysMsgHead->m_localNumberFrom != channelLocalNumber) {
		return;
	}
	if (!(sysMsgHead->m_localNumberTo == 0XFF || sysMsgHead->m_localNumberTo == m_channelID.getLocalNumber())) {
		return;
	}
	SSysMsgLabel* msgLabel = (SSysMsgLabel*)sysMsgHead->m_sysMsg;
	BSLib::uint32 msgLabelSize = msgLabel->getLabelSize();
	if (msgLabelSize + msgLabel->m_msgSize != sysMsgHead->m_sysMsgSize) {
		return ;
	}
	SMessage* msg = (SMessage*)&sysMsgHead->m_sysMsg[msgLabelSize];
	_parseMsg(msg, msgLabel);
}

void CSysChannelMgr::_onSysMsgClose(BSLib::uint32 a_para1)
{
	BSLib::uint8 channelLocalNumber = (BSLib::uint8)(a_para1 & 0X000000FF);
	if (channelLocalNumber >= GFLIB_COMMONSERVER_SYSCHANNEL_MAX) {
		return;
	}
	CChannelID sysMsgIDFrom;
	sysMsgIDFrom.setChannelID(channelLocalNumber);

	_parseSysMsg(sysMsgIDFrom, ESYSMSGTYPE_CLOSE);

	if (m_sysChannelItems[channelLocalNumber] == NULL) {
		return;
	}
	m_sysChannelItems[channelLocalNumber]->m_shareMemory.close();
	m_sysChannelItems[channelLocalNumber]->m_msgQueueHand = BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID;
}

void CSysChannelMgr::_onSysMsgTerminate()
{
	m_isRunning = false;
}

bool CSysChannelMgr::_initChannelInfor(BSLib::uint32 a_sysKey)
{
	BSLib::uint32 sysKey = a_sysKey* (BSLIB_UINT8_MAX + 1);
	//进程锁
	if (!m_mutexProcess.create(sysKey)) {
		if (!m_mutexProcess.open(sysKey)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "打开进程锁[%d]失败", sysKey);
			return false;
		}
	} 
	int size = sizeof(SSysChannelHead);
	m_mutexProcess.lock();
	if (!m_shareMemoryOfHead.create(sysKey, size)) {
		if (!m_shareMemoryOfHead.open(sysKey)) {
			m_mutexProcess.unlock();
			BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "打开共享内存[%d]失败", sysKey);
			return false;
		} else {
			m_sysChannelHead = (SSysChannelHead*)m_shareMemoryOfHead.getHeadAddress();
			if (m_sysChannelHead == NULL) {
				m_mutexProcess.unlock();
				BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "从共享内存[%d]中获取地址失败", sysKey);
				return false;
			}
		}
	} else {
		m_sysChannelHead = (SSysChannelHead*)m_shareMemoryOfHead.getHeadAddress();
		if (m_sysChannelHead == NULL) {
			m_mutexProcess.unlock();
			BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "从共享内存[%d]中获取地址失败", sysKey);
			return false;
		}
		m_sysChannelHead->m_count = 0;
	}
	//分配系统消息ID
	BSLib::uint8 localNumber = m_sysChannelHead->m_count;
	for (BSLib::uint8 i=0; i<m_sysChannelHead->m_count; ++i){
		ESysChannelState state = m_sysChannelHead->m_sysChannelItem[i].m_state;
		if (state == ESYSCHNNLST_NULL || state == ESYSCHNNLST_CLOSE) {
			localNumber = i;
			break;
		}
	}
	if (localNumber == m_sysChannelHead->m_count) {
		m_sysChannelHead->m_count += 1;
	}
	if (localNumber >= GFLIB_COMMONSERVER_SYSCHANNEL_MAX) {
		m_mutexProcess.unlock();
		BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "分配消息通道失败, 最大数量[%d]", GFLIB_COMMONSERVER_SYSCHANNEL_MAX);
		return false;
	}
	m_sysChannelHead->m_sysChannelItem[localNumber].m_state = ESYSCHNNLST_REGISTER;
	m_sysChannelHead->m_sysChannelItem[localNumber].m_msgQueueHand = BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID;
	m_sysChannelHead->m_sysChannelItem[localNumber].m_shmKey = 0;

	

	m_mutexProcess.unlock();

	BSLIB_LOG_INFOR(ETT_BSLIB_FRAMEWORK, "分配消息通道[%d]", localNumber);
	
	m_channelID.setChannelID(localNumber);

	return true;
}

int CSysChannelMgr::_run(void* a_para)
{
	BSLib::uint8 localNumber = m_channelID.getLocalNumber();
	if (localNumber >= GFLIB_COMMONSERVER_SYSCHANNEL_MAX) {
		return 0;
	}

	BSLib::int32 sysKey = (long int)a_para;
	BSLib::int32 key = sysKey * (BSLIB_UINT8_MAX + 1) + localNumber + 1;

	if (m_sysChannelItems[localNumber] == NULL) {
		m_sysChannelItems[localNumber] = new SSysChannelItemLocal();
		if (m_sysChannelItems[localNumber] == NULL) {
			return 0;
		}
	} else {
		m_sysChannelItems[localNumber]->m_shareMemory.close();
	}
	m_sysChannelItems[localNumber]->m_msgQueueHand = BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID;
	if (!m_sysChannelItems[localNumber]->m_shareMemory.create(key, GFLIB_COMMONSERVER_SYSMSGBUFF_MAX)) {
		if (!m_sysChannelItems[localNumber]->m_shareMemory.open(key)) {
			return 0;
		}
	}
	SSysChannelMsgBuff* sysChannelMsgBuff = (SSysChannelMsgBuff*)m_sysChannelItems[localNumber]->m_shareMemory.getHeadAddress();
	if (sysChannelMsgBuff == NULL) {
		m_sysChannelItems[localNumber]->m_shareMemory.close();
		return 0;
	}
	sysChannelMsgBuff->m_maxSize = GFLIB_COMMONSERVER_SYSMSGBUFF_MAX - sizeof(SSysChannelMsgBuff) + 1;
	sysChannelMsgBuff->m_currentPos = 0;
	
	//创建消息队列
	BSLib::Utility::HndThdMsgQueue thdMsgQueue = BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID;
	if (!BSLib::Utility::CThdMsgQueue::create(thdMsgQueue)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FRAMEWORK, "创建消息队列失败");
		return 0;
	}
	m_sysChannelItems[localNumber]->m_msgQueueHand = thdMsgQueue;

	std::vector<BSLib::uint8> localNumberRunning;

	m_mutexProcess.lock();

	for (BSLib::uint8 i=0; i<m_sysChannelHead->m_count; ++i) {
		if (m_sysChannelHead->m_sysChannelItem[i].m_state != ESYSCHNNLST_RUNNING) {
			continue;
		}
		localNumberRunning.push_back(i);
	}
	m_sysChannelHead->m_sysChannelItem[localNumber].m_state = ESYSCHNNLST_RUNNING;
	m_sysChannelHead->m_sysChannelItem[localNumber].m_msgQueueHand = thdMsgQueue;
	m_sysChannelHead->m_sysChannelItem[localNumber].m_shmKey = key;

	m_mutexProcess.unlock();

	for (BSLib::uint32 j=0; j<localNumberRunning.size(); ++j){
		_onSysMsgRegister(localNumberRunning[j]);
		sendSysMsg(localNumberRunning[j], ESYSMSGTYPE_REGISTER);

		CChannelID sysMsgIDFrom;
		sysMsgIDFrom.setChannelID(localNumberRunning[j]);

		_parseSysMsg(sysMsgIDFrom, ESYSMSGTYPE_REGISTER);
		
	}
	
	_initChannel();

	BSLib::uint32 para1 = 0;
	BSLib::uint16 para2 = 0;
	void* para3 = NULL;
	while (m_isRunning) {
		if (BSLib::Utility::CThdMsgQueue::recv(thdMsgQueue, &para1, &para2, &para3)  <= 0) {
			break;
		}
		ESysMsgType sysMsgType = (ESysMsgType)para2;
		switch (sysMsgType) {
			case ESYSMSGTYPE_REGISTER:
				{
					_onSysMsgRegister(para1);

					BSLib::uint8 channelLocalNumber = (BSLib::uint8)(para1 & 0X000000FF);

					CChannelID sysMsgIDFrom;
					sysMsgIDFrom.setChannelID(channelLocalNumber);

					_parseSysMsg(sysMsgIDFrom, ESYSMSGTYPE_REGISTER);
					break;
				}
			case ESYSMSGTYPE_MESSAGE:
				{
					_onSysMsgMessage(para1, para3);
					break;
				}
			case ESYSMSGTYPE_CLOSE:
				{
					_onSysMsgClose(para1);
					break;
				}
			case ESYSMSGTYPE_TERMINATE:
				{
					_onSysMsgTerminate();
				}
			default:
				{
					BSLib::uint8 localNumber = (BSLib::uint8)(para1 & 0XFF);
					
					if (localNumber >= GFLIB_COMMONSERVER_SYSCHANNEL_MAX) {
						break;
					}
					CChannelID sysMsgIDFrom;
					sysMsgIDFrom.setChannelID(localNumber);
					_parseSysMsg(sysMsgIDFrom, sysMsgType);
				}
		}
	}

	_finalChannel();

	m_mutexProcess.lock();

	m_sysChannelHead->m_sysChannelItem[localNumber].m_state = ESYSCHNNLST_CLOSE;
	m_sysChannelHead->m_sysChannelItem[localNumber].m_msgQueueHand = BSLIB_UTILITY_HNDTHDMSGQUEUE_INVALID;
	m_sysChannelHead->m_sysChannelItem[localNumber].m_shmKey = key;

	m_mutexProcess.unlock();
	
	sendSysMsgToLocalAll(ESYSMSGTYPE_CLOSE);

	BSLib::Utility::CThdMsgQueue::remove(thdMsgQueue);
	return 0;
}

}//Framework


}//BSLib



