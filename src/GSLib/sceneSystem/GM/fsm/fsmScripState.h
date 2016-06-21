#ifndef ___GSLIB_SCENESYSTEM_GM_FSM_FSMSCRIPSTATE_H__
#define ___GSLIB_SCENESYSTEM_GM_FSM_FSMSCRIPSTATE_H__

#include <BSLib/fsm/fsmClass.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

class CFSMScriptState : public BSLib::FSM::CFSMState
{
public:
	CFSMScriptState();
	virtual ~CFSMScriptState();

	virtual void enterState(BSLib::Utility::CScriptObject* a_object);

	virtual void executeState(BSLib::Utility::CScriptObject* a_object);

	virtual void leaveState(BSLib::Utility::CScriptObject* a_object);

	virtual bool parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties);

private:
	std::string m_textEnterState;
	std::string m_textExecuteState;
	std::string m_textLeaveState;
	BSLib::Utility::IScriptFunctionListPtr m_scriptEnterState;
	BSLib::Utility::IScriptFunctionListPtr m_scriptExecuteState;
	BSLib::Utility::IScriptFunctionListPtr m_scriptLeaveState;
};

}//GM

}//SceneSystem

}//GSLib

#endif//___GSLIB_SCENESYSTEM_GM_FSM_FSMSCRIPSTATE_H__
