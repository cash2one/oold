#include <BSLib/utility/fileTracer.h>
#include <BSLib/framework/sysConfig.h>
#include "channelMgr.h"
#include "mainServer.h"
#include "mainCommand.h"
#include <GSLib/sceneSystem/GM/sceneScriptEnv.h>

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

using namespace  BSLib::Utility;
class SceneScript
:public BSLib::Utility::CScriptObject
{
    virtual bool getVariation(BSLib::uint32 a_variableIndex, CScriptData* scriptData)
    { 
        return false;
    };

    virtual bool executeFunction(BSLib::uint32 a_functionIndex, std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult)
    { 

        return true;
    }

    virtual CScriptEnvironment* getScriptEnvironment() 
    { return NULL; }
};

int CMainServer::main()
{	auto env = GSLib::SceneSystem::GM::CSceneScriptEnv::singleton();
    env.init();
    auto it = env.parseFunctionList("Scene.GetVariation(\"1\", \"2\", \"3\"); Scene.SetVariation(\"1\", \"2\", \"3\");");
    SceneScript srpt;
    CScriptData data;
    it->execute(&srpt, &data);
	return CMainServer::singleton()._IThread_main();
}

bool CMainServer::_IThread_init()
{
	BSLib::Utility::CStringA command = BSLib::Framework::CSysConfig::singleton().getValueStr("c");
	if (command.empty()) {
		g_fileTracer.setOutConsole(true, "info");
		
		CMainCommand::singleton().init(true);
		
		printf("################################################\n");
		printf("# 服务器管理器 \n");
		printf("################################################\n");
		
	} else {
		CMainCommand::singleton().init(false);
	}
	if (!BSLib::Framework::CMainThread::_IThread_init()) {
		return false;
	}
	BSLib::uint32 key = BSLib::Framework::CSysConfig::singleton().getValueInt("k");
	if (!CChannelMgr::singleton().init(key)) {
		return false;
	}
	return true;
}

int CMainServer::_IThread__final()
{
	g_fileTracer.close();
	CMainCommand::singleton().final();
	CChannelMgr::singleton().final();
	return BSLib::Framework::CMainThread::_IThread_final();
}



