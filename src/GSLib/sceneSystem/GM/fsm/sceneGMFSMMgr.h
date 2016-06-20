//////////////////////////////////////////////////////////////////////
//	created:	2014/08/19
//	filename: 	src\GSLib\sceneSystem\GM\fsm\sceneGMFSMMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_SCENESYSTEM_GM_FSM_SCENEGMFSMMGR_H__
#define __GSLIB_SCENESYSTEM_GM_FSM_SCENEGMFSMMGR_H__ 

#include <BSLib/utility/singleton.h>
#include <BSLib/fsm/fsmMgr.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CSceneGMFSMMgr : public BSLib::FSM::CFSMMgr
{
public:
	CSceneGMFSMMgr();
	~CSceneGMFSMMgr();

	BSLIB_SINGLETON_DECLARE(CSceneGMFSMMgr);

	bool init();
	void final();

private:
	void initFSMState();
	void initFSMCondition();

private:
	virtual BSLib::FSM::CFSM* _createFSM(BSLib::Utility::CScriptObject* a_object, const std::string& a_fsmName);
};

}//GM

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_GM_FSM_SCENEGMFSMMGR_H__