//////////////////////////////////////////////////////////////////////
//	created:	2014/08/19
//	filename: 	src\GSLib\sceneSystem\GM\fsm\sceneGMFSMMgr.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include "GM/fsm/sceneGMFSMMgr.h"
#include "GM/fsm/sceneGMFSM.h"
#include "GM/fsm/fsmBTCondition.h"
#include "GM/fsm/fsmScripCondition.h"
#include "GM/fsm/fsmBTState.h"
#include "GM/fsm/fsmScripState.h"

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

BSLIB_SINGLETON_DEFINE(CSceneGMFSMMgr);


CSceneGMFSMMgr::CSceneGMFSMMgr()
{
	;
}

CSceneGMFSMMgr::~CSceneGMFSMMgr()
{
	;
}

bool CSceneGMFSMMgr::init()
{
	initFSMState();
	initFSMCondition();
	return true;
}

void CSceneGMFSMMgr::final()
{
	BSLib::FSM::CFSMMgr::clear();
}

BSLib::FSM::CFSM* CSceneGMFSMMgr::_createFSM(BSLib::Utility::CScriptObject* a_object, const std::string& a_fsmName)
{
	return new CSceneGMFSM(a_object);
}

void CSceneGMFSMMgr::initFSMState()
{
	BSLib::FSM::CFSMMgr::registerCreateFSMStateFun("FSMScriptState", BSLib::FSM::createFSMState<CFSMScriptState>);
	BSLib::FSM::CFSMMgr::registerCreateFSMStateFun("FSMBTState", BSLib::FSM::createFSMState<CFSMBTState>);
}

void CSceneGMFSMMgr::initFSMCondition()
{
	BSLib::FSM::CFSMMgr::registerCreateFSMConditionFun("FSMScriptCondition", BSLib::FSM::createFSMCondition<CFSMScriptCondition>);
	BSLib::FSM::CFSMMgr::registerCreateFSMConditionFun("FSMBTCondition", BSLib::FSM::createFSMCondition<CFSMBTCondition>);
}

}//GM

}//SceneSystem

}//GSLib
