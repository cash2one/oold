//////////////////////////////////////////////////////////////////////
//	created:	2013/06/09
//	filename:	src\Server\server\channelMgr.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/framework/sysConfig.h>
#include <BSLib/framework/message/msgDebug.h>
#include "channelMgr.h"
#include "mainCommand.h"

BSLIB_SINGLETON_DEFINE(CChannelMgr);

CChannelMgr::CChannelMgr()
{
	m_localServerInfor.resize(BSLIB_UINT8_MAX, NULL);
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

	BSLib::Framework::CMsgExecPtr msgExecPtr = new BSLib::Framework::CMsgExec(&CChannelMgr::_onSysChannelLC2LCResServerInfor, this);
	m_msgExecMgr.addMsgExecPtr(GFLIB_MSG_TYPE(GFLib::SRVTYPE_LOCAL, GFLib::EFUNCTYPE_SYSTEM_CHANNEL), GFLib::EMSGID_SYSCHANNEL_LC2LC_RES_SERVERINFOR, msgExecPtr);

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
	if (m_localServerInfor[a_localNumber] == NULL) {
		return ;
	}
	if (!m_localServerInfor[a_localNumber]->m_channelID.isValid()) {
		return ;
	}
	BSLib::Framework::CSysChannelMgr::sendSysMsg(a_localNumber, BSLib::Framework::ESYSMSGTYPE_TERMINATE);
}

SChannelInfor* CChannelMgr::getChannelInfor(const std::string& a_serverName)
{
	for (int i=0; i < BSLIB_UINT8_MAX; ++i) {
		if (m_localServerInfor[i] == NULL) {
			continue;
		}
		if (!m_localServerInfor[i]->m_channelID.isValid()) {
			continue;
		}
		if (m_localServerInfor[i]->m_serverName == a_serverName) {
			return m_localServerInfor[i];
		}
	}
	return NULL;
}

SChannelInfor* CChannelMgr::getChannelInfor(BSLib::uint8 a_localNumber)
{
	if (a_localNumber >= BSLIB_UINT8_MAX) {
		return NULL;
	}
	if (m_localServerInfor[a_localNumber] == NULL) {
		return NULL;
	}
	if (!m_localServerInfor[a_localNumber]->m_channelID.isValid()) {
		return NULL;
	}
	return m_localServerInfor[a_localNumber];
}

void CChannelMgr::showAllChannelInfor()
{
	for (BSLib::uint32 i=0; i<m_localServerInfor.size(); ++i) {
		if (m_localServerInfor[i] == NULL) {
			continue;
		}
		printf("\n\r通道[%d] Server(%d.%d.%d)[%s]已运行",
			m_localServerInfor[i]->m_channelID.getLocalNumber(),
			m_localServerInfor[i]->m_serverID.getZoneID(),
			m_localServerInfor[i]->m_serverID.getServerType(),
			m_localServerInfor[i]->m_serverID.getServerNumber(),
			m_localServerInfor[i]->m_serverName.c_str());
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
				if (m_localServerInfor[localNumber] != NULL) {
					printf("\n\r通道[%d]已经存在\n", localNumber);
					break;
				}
				
				GFLib::SMsgSysChannelLC2LCReqServerInfor reqServerInfor;
				BSLib::Framework::CSysChannelMgr::sendMsg(a_channelIDFrom, &reqServerInfor, sizeof(reqServerInfor));

				break;
			}
		case BSLib::Framework::ESYSMSGTYPE_CLOSE:
			{
				if (m_localServerInfor[localNumber] == NULL) {
					printf("\n\r通道[%d]已经不存在\n", localNumber);
					break;
				}
				
				printf("\n\r通道[%d] Server(%d.%d.%d)[%s]退出\n",
					m_localServerInfor[localNumber]->m_channelID.getLocalNumber(),
					m_localServerInfor[localNumber]->m_serverID.getZoneID(),
					m_localServerInfor[localNumber]->m_serverID.getServerType(),
					m_localServerInfor[localNumber]->m_serverID.getServerNumber(),
					m_localServerInfor[localNumber]->m_serverName.c_str());

				BSLIB_SAFE_DELETE(m_localServerInfor[localNumber]);
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
	for (BSLib::uint32 i=0; i<m_localServerInfor.size(); ++i) {
		if (m_localServerInfor[i] == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(m_localServerInfor[i]);
	}
	m_localServerInfor.clear();
}

void CChannelMgr::_onSysChannelLC2LCResServerInfor(BSLib::Framework::SMsgLabel* msgLabel,BSLib::Framework:: SMessage* msg)
{
	BSLib::Framework::SSysMsgLabel* channelMsgLabel = (BSLib::Framework::SSysMsgLabel*)msgLabel;
	GFLib::SMsgSysChannelLC2LCResServerInfor* resServerInfor = (GFLib::SMsgSysChannelLC2LCResServerInfor*)msg;

	BSLib::uint8 localNumber = channelMsgLabel->m_sysMsgIDFrome.getLocalNumber();
	if (m_localServerInfor[localNumber] != NULL) {
		printf("\n\r通道[%d]已经存在\n", localNumber);
		return;
	}
	m_localServerInfor[localNumber] = new SChannelInfor();
	if (m_localServerInfor[localNumber] == NULL) {
		printf("\n\r分配内存失败\n");
		return;
	}
	m_localServerInfor[localNumber]->m_serverID = resServerInfor->m_localServerID;
	m_localServerInfor[localNumber]->m_serverName = resServerInfor->m_localKeyName;
	m_localServerInfor[localNumber]->m_channelID = channelMsgLabel->m_sysMsgIDFrome;

	printf("\n\r通道[%d] Server(%d.%d.%d)[%s]已运行\n",
		m_localServerInfor[localNumber]->m_channelID.getLocalNumber(),
		m_localServerInfor[localNumber]->m_serverID.getZoneID(),
		m_localServerInfor[localNumber]->m_serverID.getServerType(),
		m_localServerInfor[localNumber]->m_serverID.getServerNumber(),
		m_localServerInfor[localNumber]->m_serverName.c_str());
}