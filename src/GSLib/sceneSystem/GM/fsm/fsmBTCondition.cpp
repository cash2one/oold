#include <GSLib/tracer.h>
#include "GM/fsm/fsmBTCondition.h"
#include <GSLib/sceneSystem/GM/sceneScriptEnv.h>
#include "GM/btree/sceneGMBTMgr.h"

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

CFSMBTCondition::CFSMBTCondition()
: m_btExecuteState(NULL)
{
	;
}

CFSMBTCondition::~CFSMBTCondition()
{
	CSceneGMBTMgr::singleton().removeBT(&m_btExecuteState);
}

bool CFSMBTCondition::jumpCondition(BSLib::Utility::CScriptObject* a_object)
{
	if (m_btExecuteState != NULL) {
		return m_btExecuteState->execute() == BSLib::BehaviorTree::SUCCESS;
	}
	return false;
}

bool CFSMBTCondition::parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties)
{
	a_properties->getValueString("btname", m_btName);
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

