#include <GFLib/commonServer/commonServer.h>
#include <GFLib/commonServer/serviceMgr.h>
#include <GFLib/commonServer/sysChannelMgr.h>

namespace GFLib
{

namespace CommonServer
{

BSLIB_SINGLETON_DEFINE(CSysChannelMgr);

CSysChannelMgr::CSysChannelMgr()
{
	;
}

CSysChannelMgr::~CSysChannelMgr()
{
	;
}

void CSysChannelMgr::_initChannel()
{
	;
}

void CSysChannelMgr::_finalChannel()
{
	;
}

void CSysChannelMgr::_parseSysMsg(BSLib::Framework::CChannelID& a_channelIDFrom, BSLib::Framework::ESysMsgType a_sysMsgType)
{
	;
}

void CSysChannelMgr::_parseMsg(BSLib::Framework::SMessage* a_msg, BSLib::Framework::SSysMsgLabel* msgLabel)
{
	CCommonServer* commonServer = CCommonServer::getCommonServer();

	if (commonServer == NULL) {
		return ;
	}
	commonServer->sendMsg(a_msg, msgLabel->m_msgSize, msgLabel, msgLabel->getLabelSize());
}

void CSysChannelMgr::_onSysMsgTerminate()
{
	BSLib::Framework::CSysChannelMgr::_onSysMsgTerminate();

	CServiceMgr::singleton().closeAll();

	CCommonServer* commonServer = CCommonServer::getCommonServer();
	if (commonServer != NULL) {
		commonServer->terminate();
	}
}

}//CommonServer

}//GFLib



