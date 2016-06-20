//////////////////////////////////////////////////////////////////////
//	created:	2014/08/22
//	filename: 	src\GSLib\sceneSystem\GM\fsm\fsmScripState.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/tracer.h>
#include "fsmScripState.h"

namespace BSLib
{

namespace FSM
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
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "finalFSM[%s]", m_textEnterState.c_str());
			return ;
		}
	}
}

void CFSMScriptState::executeState(BSLib::Utility::CScriptObject* a_object)
{
	if (m_scriptExecuteState != NULL) {
		BSLib::Utility::CScriptData functionResult;
		if (!m_scriptExecuteState->execute(a_object, &functionResult)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "finalFSM[%s]", m_textExecuteState.c_str());
			return ;
		}
	}
}

void CFSMScriptState::leaveState(BSLib::Utility::CScriptObject* a_object)
{
	if (m_scriptLeaveState != NULL) {
		BSLib::Utility::CScriptData functionResult;
		if (!m_scriptLeaveState->execute(a_object, &functionResult)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "finalFSM[%s]", m_textLeaveState.c_str());
			return ;
		}
	}
}

bool CFSMScriptState::parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties)
{
	BSLib::Utility::CScriptEnvironment* scriptEvironment = a_object->getScriptEnvironment();
	if (scriptEvironment == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "获取CScriptEnvironment失败");
		return false;
	}
	a_properties->getValueString("enter", m_textEnterState);
	a_properties->getValueString("leave", m_textLeaveState);
	a_properties->getValueString("execute", m_textExecuteState);
	if (!m_textEnterState.empty()) {
		m_scriptEnterState = scriptEvironment->parseFunctionList(m_textEnterState);
		if (m_scriptEnterState == NULL) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "解析initFSM[%s]", m_textEnterState.c_str());
			return false;
		}
	}
	if (!m_textLeaveState.empty()) {
		m_scriptLeaveState = scriptEvironment->parseFunctionList(m_textLeaveState);
		if (m_scriptLeaveState == NULL) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "解析finalFSM[%s]", m_textLeaveState.c_str());
			return false;
		}
	}
	if (!m_textExecuteState.empty()) {
		m_scriptExecuteState = scriptEvironment->parseFunctionList(m_textExecuteState);
		if (m_scriptExecuteState == NULL) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "解析finalFSM[%s]", m_textExecuteState.c_str());
			return false;
		}
	}
	return true;
}

}//FSM

}//BSLib

