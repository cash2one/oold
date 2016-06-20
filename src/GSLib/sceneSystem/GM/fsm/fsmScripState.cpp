//////////////////////////////////////////////////////////////////////
//	created:	2014/08/22
//	filename: 	src\GSLib\sceneSystem\GM\fsm\fsmScripState.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/tracer.h>
#include "GM/fsm/fsmScripState.h"
#include <GSLib/sceneSystem/GM/sceneScriptEnv.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

CFSMScriptState::CFSMScriptState()
: BSLib::FSM::CFSMState(true, true)
{
	;
}
CFSMScriptState::~CFSMScriptState()
{
	;
}

void CFSMScriptState::enterState(BSLib::Utility::CScriptObject* a_object)
{
	if (m_scriptEnterState != NULL) {
		BSLib::Utility::CScriptData functionResult;
		if (!m_scriptEnterState->execute(a_object, &functionResult)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "finalFSM[%s]", m_textEnterState.c_str());
			return ;
		}
	}
}

void CFSMScriptState::executeState(BSLib::Utility::CScriptObject* a_object)
{
	if (m_scriptExecuteState != NULL) {
		BSLib::Utility::CScriptData functionResult;
		if (!m_scriptExecuteState->execute(a_object, &functionResult)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "finalFSM[%s]", m_textExecuteState.c_str());
			return ;
		}
	}
}

void CFSMScriptState::leaveState(BSLib::Utility::CScriptObject* a_object)
{
	if (m_scriptLeaveState != NULL) {
		BSLib::Utility::CScriptData functionResult;
		if (!m_scriptLeaveState->execute(a_object, &functionResult)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "finalFSM[%s]", m_textLeaveState.c_str());
			return ;
		}
	}
}

bool CFSMScriptState::parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties)
{
	a_properties->getValueString("enter", m_textEnterState);
	a_properties->getValueString("leave", m_textLeaveState);
	a_properties->getValueString("execute", m_textExecuteState);
	if (!m_textEnterState.empty()) {
		m_scriptEnterState = CSceneScriptEnv::singleton().parseFunctionList(m_textEnterState);
		if (m_scriptEnterState == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "½âÎöinitFSM[%s]", m_textEnterState.c_str());
			return false;
		}
	}
	if (!m_textLeaveState.empty()) {
		m_scriptLeaveState = CSceneScriptEnv::singleton().parseFunctionList(m_textLeaveState);
		if (m_scriptLeaveState == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "½âÎöfinalFSM[%s]", m_textLeaveState.c_str());
			return false;
		}
	}
	if (!m_textExecuteState.empty()) {
		m_scriptExecuteState = CSceneScriptEnv::singleton().parseFunctionList(m_textExecuteState);
		if (m_scriptExecuteState == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "½âÎöfinalFSM[%s]", m_textExecuteState.c_str());
			return false;
		}
	}
	return true;
}

}//GM

}//SceneSystem

}//GSLib

