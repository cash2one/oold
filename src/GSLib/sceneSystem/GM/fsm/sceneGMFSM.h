//////////////////////////////////////////////////////////////////////
//	created:	2014/08/19
//	filename: 	src\GSLib\sceneSystem\GM\fsm\sceneGMFSM.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_GM_FSM_SCENEGMFSM_H__
#define __GSLIB_SCENESYSTEM_GM_FSM_SCENEGMFSM_H__ 

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/script.h>
#include <BSLib/fsm/fsmMgr.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CSceneGMFSM : public BSLib::FSM::CFSMBase
{
public:
	CSceneGMFSM(BSLib::Utility::CScriptObject* a_object);
	virtual ~CSceneGMFSM();

public:
	virtual bool initFSM();

	virtual void finalFSM();

	virtual bool parseProperties(BSLib::Utility::CProperties* a_properties);

private:
	std::string m_textInitFSM;
	std::string m_textFianlFSM;
	BSLib::Utility::IScriptFunctionListPtr m_scriptInitFSM;
	BSLib::Utility::IScriptFunctionListPtr m_scriptFinalFSM;
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_FSM_SCENEGMFSM_H__