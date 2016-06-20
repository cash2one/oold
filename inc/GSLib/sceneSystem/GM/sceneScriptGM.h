//////////////////////////////////////////////////////////////////////
//	created:	2014/08/19
//	filename: 	GSLib\sceneSystem\GM\sceneScriptGM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_GM_SCENESCRIPTGM_H__
#define __GSLIB_SCENESYSTEM_GM_SCENESCRIPTGM_H__ 

#include <BSLib/fsm/fsmClass.h>
#include <GSLib/sceneSystem/GM/sceneGM.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

enum EScriptVariableIndex
{
	
};

enum EScriptFunctionIndex
{
	ESCRIPT_FUNCINDEX_SCENE_GETVARIATION = BSLib::Utility::ESCRIPT_FUNCINDEX_EXTEND,//Scene.GetVariation(name);
	ESCRIPT_FUNCINDEX_SCENE_SETVARIATION,//Scene.GetVariation(name, value);
};

class CSceneScriptGM : public BSLib::Utility::CScriptObject
{
public:
	CSceneScriptGM(CSceneGM* a_sceneGM);
	~CSceneScriptGM();

	bool init();
	void final();

	void update(BSLib::uint64 a_delayMilliseconds);

	virtual bool getVariation(BSLib::uint32 a_variableIndex, BSLib::Utility::CScriptData* a_scriptData);
	virtual bool executeFunction(BSLib::uint32 a_functionIndex, std::vector<BSLib::Utility::CScriptData>& a_functionParamenterList, BSLib::Utility::CScriptData* a_functionResult);

private:
	bool _executeFunctionSceneGetVariation(std::vector<BSLib::Utility::CScriptData>& a_functionParamenterList, BSLib::Utility::CScriptData* a_functionResult);
	bool _executeFunctionSceneSetVariation(std::vector<BSLib::Utility::CScriptData>& a_functionParamenterList, BSLib::Utility::CScriptData* a_functionResult);

private:
	CSceneGM* m_sceneGM;
	BSLib::FSM::CFSM* m_fsm;

	BSLib::Utility::CHashMap<std::string, BSLib::Utility::CScriptData> m_defineVariation;
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_SCENESCRIPTGM_H__
