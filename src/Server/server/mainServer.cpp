#include <BSLib/utility/fileTracer.h>
#include <BSLib/framework/sysConfig.h>
#include "channelMgr.h"
#include "mainServer.h"
#include "mainCommand.h"

BSLIB_FRAMEWORK_MAIN(CMainServer::main);

BSLIB_SINGLETON_DEFINE(CMainServer);

BSLib::Utility::CFileTracer g_fileTracer;

CMainServer::CMainServer()
{
	;
}

CMainServer::~CMainServer()
{
	;
}

int CMainServer::main()
{	
	return CMainServer::singleton()._main();
}

bool CMainServer::_init()
{
	BSLib::Utility::CStringA command = BSLib::Framework::CSysConfig::singleton().getValueStr("c");
	if (command.empty()) {
		g_fileTracer.setOutConsole(true, "infor");
		
		CMainCommand::singleton().init(true);
		
		printf("################################################\n");
		printf("# 服务器管理器 \n");
		printf("################################################\n");
		
	} else {
		CMainCommand::singleton().init(false);
	}
	if (!BSLib::Framework::CMainThread::_init()) {
		return false;
	}
	BSLib::uint32 key = BSLib::Framework::CSysConfig::singleton().getValueInt("k");
	if (!CChannelMgr::singleton().init(key)) {
		return false;
	}
	return true;
}

int CMainServer::_final()
{
	g_fileTracer.close();
	CMainCommand::singleton().final();
	CChannelMgr::singleton().final();
	return BSLib::Framework::CMainThread::_final();
}



