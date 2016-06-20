//////////////////////////////////////////////////////////////////////
//	created:	2014/08/22
//	filename: 	src\GSLib\sceneSystem\GM\fsm\fsmBTCondition.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef ___GSLIB_SCENESYSTEM_GM_FSM_FSMBTCONDITION_H__
#define ___GSLIB_SCENESYSTEM_GM_FSM_FSMBTCONDITION_H__

#include <BSLib/fsm/fsmClass.h>
#include <BSLib/behaviorTree/behaviorTree.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CFSMBTCondition : public BSLib::FSM::CFSMCondition
{
public:
	CFSMBTCondition();
	virtual ~CFSMBTCondition();

	virtual bool jumpCondition(BSLib::Utility::CScriptObject* a_object);

	virtual bool parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties);

private:
	std::string m_btName;
	BSLib::BehaviorTree::CBehaviorTree* m_btExecuteState;
};

}//GM

}//SceneSystem

}//GSLib

#endif//___GSLIB_SCENESYSTEM_GM_FSM_FSMBTCONDITION_H__