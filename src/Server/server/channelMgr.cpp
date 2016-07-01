#include <BSLib/framework/sysConfig.h>
#include <BSLib/framework/message/msgDebug.h>
#include "channelMgr.h"
#include "mainCommand.h"

BSLIB_SINGLETON_DEFINE(CChannelMgr);

CChannelMgr::CChannelMgr()
{
	m_localServerInfo.resize(BSLIB_UINT8_MAX, NULL);
}

CChannelMgr::~CChannelMgr()
{
	;
}

bool CChannelMgr::init(BSLib::uint32 a_sysKey)
{
	if (!BSLib::Framework::CSysChannelMgr::init(a_sysKey)) {
		return false;
	}

	BSLib::Framework::CMsgExecPtr msgExecPtr = new BSLib::Framework::CMsgExec(&CChannelMgr::_onSysChannelLC2LCResServerInfo, this);
	m_msgExecMgr.addMsgExecPtr(GFLIB_MSG_TYPE(GFLib::SRVTYPE_LOCAL, GFLib::EFUNCTYPE_SYSTEM_CHANNEL), GFLib::EMSGID_SYSCHANNEL_LC2LC_RES_SERVERINFO, msgExecPtr);

	return true;
}

void CChannelMgr::final()
{
	BSLib::Framework::CSysChannelMgr::final();
	_final();
}

void CChannelMgr::stopAll()
{
	BSLib::Framework::CSysChannelMgr::sendSysMsgToLocalAll(BSLib::Framework::ESYSMSGTYPE_TERMINATE);
}

void CChannelMgr::stop(BSLib::uint8 a_localNumber)
{
	if (a_localNumber >= BSLIB_UINT8_MAX) {
		return ;
	}
	if (m_localServerInfo[a_localNumber] == NULL) {
		return ;
	}
	if (!m_localServerInfo[a_localNumber]->m_channelID.isValid()) {
		return ;
	}
	BSLib::Framework::CSysChannelMgr::sendSysMsg(a_localNumber, BSLib::Framework::ESYSMSGTYPE_TERMINATE);
}

SChannelInfo* CChannelMgr::getChannelInfo(const std::string& a_serverName)
{
	for (int i=0; i < BSLIB_UINT8_MAX; ++i) {
		if (m_localServerInfo[i] == NULL) {
			continue;
		}
		if (!m_localServerInfo[i]->m_channelID.isValid()) {
			continue;
		}
		if (m_localServerInfo[i]->m_serverName == a_serverName) {
			return m_localServerInfo[i];
		}
	}
	return NULL;
}

SChannelInfo* CChannelMgr::getChannelInfo(BSLib::uint8 a_localNumber)
{
	if (a_localNumber >= BSLIB_UINT8_MAX) {
		return NULL;
	}
	if (m_localServerInfo[a_localNumber] == NULL) {
		return NULL;
	}
	if (!m_localServerInfo[a_localNumber]->m_channelID.isValid()) {
		return NULL;
	}
	return m_localServerInfo[a_localNumber];
}

void CChannelMgr::showAllChannelInfo()
{
	for (BSLib::uint32 i=0; i<m_localServerInfo.size(); ++i) {
		if (m_localServerInfo[i] == NULL) {
			continue;
		}
		printf("\n\r通道[%d] Server(%d.%d.%d)[%s]已运行",
			m_localServerInfo[i]->m_channelID.getLocalNumber(),
			m_localServerInfo[i]->m_serverID.getZoneID(),
			m_localServerInfo[i]->m_serverID.ICommonServer_getServerType(),
			m_localServerInfo[i]->m_serverID.getServerNumber(),
			m_localServerInfo[i]->m_serverName.c_str());
	}
	printf("\n");
}

void CChannelMgr::_initChannel()
{
	BSLib::Utility::CStringA command = BSLib::Framework::CSysConfig::singleton().getValueStr("c");
	if (!command.empty()) {
		std::vector<BSLib::Utility::CStringA> subCommand;
		command.split(subCommand, ';');
		for (BSLib::uint32 i=0; i<subCommand.size(); ++i) {
			subCommand[i].trim();
			CMainCommand::singleton().parseCommand(subCommand[i]);
		}
	}
}

void CChannelMgr::_finalChannel()
{
	;
}

void CChannelMgr::_parseSysMsg(BSLib::Framework::CChannelID& a_channelIDFrom, BSLib::Framework::ESysMsgType a_sysMsgType)
{
	BSLib::uint8 localNumber = a_channelIDFrom.getLocalNumber();
	switch(a_sysMsgType) {
		case BSLib::Framework::ESYSMSGTYPE_REGISTER:
			{			
				if (m_localServerInfo[localNumber] != NULL) {
					printf("\n\r通道[%d]已经存在\n", localNumber);
					break;
				}
				
				GFLib::SMsgSysChannelLC2LCReqServerInfo reqServerInfor;
				BSLib::Framework::CSysChannelMgr::sendMsg(a_channelIDFrom, &reqServerInfor, sizeof(reqServerInfor));

				break;
			}
		case BSLib::Framework::ESYSMSGTYPE_CLOSE:
			{
				if (m_localServerInfo[localNumber] == NULL) {
					printf("\n\r通道[%d]已经不存在\n", localNumber);
					break;
				}
				
				printf("\n\r通道[%d] Server(%d.%d.%d)[%s]退出\n",
					m_localServerInfo[localNumber]->m_channelID.getLocalNumber(),
					m_localServerInfo[localNumber]->m_serverID.getZoneID(),
					m_localServerInfo[localNumber]->m_serverID.ICommonServer_getServerType(),
					m_localServerInfo[localNumber]->m_serverID.getServerNumber(),
					m_localServerInfo[localNumber]->m_serverName.c_str());

				BSLIB_SAFE_DELETE(m_localServerInfo[localNumber]);
				break;
			}
		default:
			{
				printf("\n\r通道[%d]消息类型无法识别\n", localNumber);
			}
	}
}

void CChannelMgr::_parseMsg(BSLib::Framework::SMessage* a_msg, BSLib::Framework::SSysMsgLabel* msgLabel)
{
	if (!m_msgExecMgr.executeMessage(msgLabel, a_msg)) {
		printf("\n\r丢弃消息[%d-%d][%s]\n",
			a_msg->getType(),
			a_msg->getID(),
			BSLib::Framework::CMsgDebug::singleton().getPrompt(a_msg).c_str());
	}
}

void CChannelMgr::_final()
{
	for (BSLib::uint32 i=0; i<m_localServerInfo.size(); ++i) {
		if (m_localServerInfo[i] == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(m_localServerInfo[i]);
	}
	m_localServerInfo.clear();
}

void CChannelMgr::_onSysChannelLC2LCResServerInfo(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg)
{
	BSLib::Framework::SSysMsgLabel* channelMsgLabel = (BSLib::Framework::SSysMsgLabel*)msgLabel;
	GFLib::SMsgSysChannelLC2LCResServerInfo* resServerInfor = (GFLib::SMsgSysChannelLC2LCResServerInfo*)msg;

	BSLib::uint8 localNumber = channelMsgLabel->m_sysMsgIDFrome.getLocalNumber();
	if (m_localServerInfo[localNumber] != NULL) {
		printf("\n\r通道[%d]已经存在\n", localNumber);
		return;
	}
	m_localServerInfo[localNumber] = new SChannelInfo();
	if (m_localServerInfo[localNumber] == NULL) {
		printf("\n\r分配内存失败\n");
		return;
	}
	m_localServerInfo[localNumber]->m_serverID = resServerInfor->m_localServerID;
	m_localServerInfo[localNumber]->m_serverName = resServerInfor->m_localKeyName;
	m_localServerInfo[localNumber]->m_channelID = channelMsgLabel->m_sysMsgIDFrome;

	printf("\n\r通道[%d] Server(%d.%d.%d)[%s]已运行\n",
		m_localServerInfo[localNumber]->m_channelID.getLocalNumber(),
		m_localServerInfo[localNumber]->m_serverID.getZoneID(),
		m_localServerInfo[localNumber]->m_serverID.ICommonServer_getServerType(),
		m_localServerInfo[localNumber]->m_serverID.getServerNumber(),
		m_localServerInfo[localNumber]->m_serverName.c_str());
}
