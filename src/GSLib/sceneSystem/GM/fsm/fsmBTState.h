#ifndef ___GSLIB_SCENESYSTEM_GM_FSM_FSMBTSTATE_H__
#define ___GSLIB_SCENESYSTEM_GM_FSM_FSMBTSTATE_H__

#include <BSLib/fsm/fsmClass.h>
#include <BSLib/behaviorTree/behaviorTree.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CFSMBTState : public BSLib::FSM::CFSMState
{
public:
	CFSMBTState();
	virtual ~CFSMBTState();

	virtual void enterState(BSLib::Utility::CScriptObject* a_object);

	virtual void executeState(BSLib::Utility::CScriptObject* a_object);

	virtual void leaveState(BSLib::Utility::CScriptObject* a_object);

	virtual bool parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties);

private:
	std::string m_textEnterState;
	std::string m_textLeaveState;
	std::string m_btName;

	BSLib::Utility::IScriptFunctionListPtr m_scriptEnterState;
	BSLib::Utility::IScriptFunctionListPtr m_scriptLeaveState;
	BSLib::BehaviorTree::CBehaviorTree* m_btExecuteState;
};

}//GM

}//SceneSystem

}//GSLib

#endif//___GSLIB_SCENESYSTEM_GM_FSM_FSMBTSTATE_H__
