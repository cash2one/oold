//////////////////////////////////////////////////////////////////////
//	created:	2014/08/19
//	filename: 	GSLib\sceneSystem\GM\sceneScriptEnv.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_GM_SCENESCRIPTENV_H__
#define __GSLIB_SCENESYSTEM_GM_SCENESCRIPTENV_H__ 

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/script.h>
#include <GSLib/sceneSystem/GM/sceneGM.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CSceneScriptEnv : public BSLib::Utility::CScriptEnvironment
{
public:
	CSceneScriptEnv();
	~CSceneScriptEnv();

	BSLIB_SINGLETON_DECLARE(CSceneScriptEnv);

public:
	bool init();
	void final();

protected:
	virtual bool _getVariableIndex(const std::string& a_nameVariable, BSLib::uint32* a_index);
	virtual bool _getFunctionIndex(const std::string& a_nameFunction, BSLib::uint32* a_index);

private:
	void _intiVariableIndex();
	void _intiFunctionIndex();

private:
	BSLib::Utility::CHashMap<std::string, BSLib::uint32> m_variableIndexHashMap;
	BSLib::Utility::CHashMap<std::string, BSLib::uint32> m_functionIndexHashMap;
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_SCENESCRIPTENV_H__