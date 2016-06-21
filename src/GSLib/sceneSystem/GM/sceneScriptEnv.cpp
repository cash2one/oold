#include <GSLib/tracer.h>
#include <GSLib/sceneSystem/GM/sceneScriptEnv.h>
#include <GSLib/sceneSystem/GM/sceneScriptGM.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CSceneScriptEnv);

CSceneScriptEnv::CSceneScriptEnv()
{
	;
}

CSceneScriptEnv::~CSceneScriptEnv()
{
	;
}

bool CSceneScriptEnv::init()
{
	BSLib::Utility::CScriptEnvironment::_init();
	
	_intiFunctionIndex();
	_intiVariableIndex();

	return true;
}

void CSceneScriptEnv::final()
{

}

bool CSceneScriptEnv::_getVariableIndex(const std::string& a_nameVariable, BSLib::uint32* a_index)
{
	return BSLib::Utility::CScriptEnvironment::_getFunctionIndex(a_nameVariable, a_index);
}

bool CSceneScriptEnv::_getFunctionIndex(const std::string& a_nameFunction, BSLib::uint32* a_index)
{
	return BSLib::Utility::CScriptEnvironment::_getFunctionIndex(a_nameFunction, a_index);
}

void CSceneScriptEnv::_intiVariableIndex()
{
	//BSLib::Utility::CScriptEnvironment::_addVariableIndex("", 0);
}

void CSceneScriptEnv::_intiFunctionIndex()
{
	BSLib::Utility::CScriptEnvironment::_addFunctionIndex("Scene.GetVariation", ESCRIPT_FUNCINDEX_SCENE_GETVARIATION);
	BSLib::Utility::CScriptEnvironment::_addFunctionIndex("Scene.SetVariation", ESCRIPT_FUNCINDEX_SCENE_SETVARIATION);
}

}//GM

}//SceneSystem

}//GSLib

