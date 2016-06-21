#include <GSLib/tracer.h>
#include "GM/fsm/fsmBTState.h"
#include <GSLib/sceneSystem/GM/sceneScriptEnv.h>
#include "GM/btree/sceneGMBTMgr.h"

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

CFSMBTState::CFSMBTState()
: BSLib::FSM::CFSMState(true, true)
, m_btExecuteState(NULL)
{
	;
}
CFSMBTState::~CFSMBTState()
{
	CSceneGMBTMgr::singleton().removeBT(&m_btExecuteState);
}

void CFSMBTState::enterState(BSLib::Utility::CScriptObject* a_object)
{
	if (m_scriptEnterState != NULL) {
		BSLib::Utility::CScriptData functionResult;
		if (!m_scriptEnterState->execute(a_object, &functionResult)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "finalFSM[%s]", m_textEnterState.c_str());
			return ;
		}
	}
	if (m_btExecuteState != NULL) {
		m_btExecuteState->resetTree();
	}
}

void CFSMBTState::executeState(BSLib::Utility::CScriptObject* a_object)
{
	if (m_btExecuteState != NULL) {
		m_btExecuteState->execute();
	}
}

void CFSMBTState::leaveState(BSLib::Utility::CScriptObject* a_object)
{
	if (m_scriptLeaveState != NULL) {
		BSLib::Utility::CScriptData functionResult;
		if (!m_scriptLeaveState->execute(a_object, &functionResult)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "finalFSM[%s]", m_textLeaveState.c_str());
			return ;
		}
	}
}

bool CFSMBTState::parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties)
{
	a_properties->getValueString("enter", m_textEnterState);
	a_properties->getValueString("leave", m_textLeaveState);
	a_properties->getValueString("btname", m_btName);
	if (!m_textEnterState.empty()) {
		m_scriptEnterState = CSceneScriptEnv::singleton().parseFunctionList(m_textEnterState);
		if (m_scriptEnterState == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "½âÎöenter[%s]", m_textEnterState.c_str());
			return false;
		}
	}
	if (!m_textLeaveState.empty()) {
		m_scriptLeaveState = CSceneScriptEnv::singleton().parseFunctionList(m_textLeaveState);
		if (m_scriptLeaveState == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "½âÎöleave[%s]", m_textLeaveState.c_str());
			return false;
		}
	}
	if (!m_btName.empty()) {
		m_btExecuteState = CSceneGMBTMgr::singleton().createBT(m_btName, &CSceneScriptEnv::singleton(), BSLib::BehaviorTree::BTSTOPPROT_ACTIONS);
		if (m_btExecuteState == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "½âÎöfinalFSM[%s]", m_btName.c_str());
			return false;
		}
	}
	return true;
}

}//GM

}//SceneSystem

}//GSLib



