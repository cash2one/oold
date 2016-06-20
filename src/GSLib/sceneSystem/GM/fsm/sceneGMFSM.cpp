//////////////////////////////////////////////////////////////////////
//	created:	2014/08/19
//	filename: 	src\GSLib\sceneSystem\GM\fsm\sceneGMFSMMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/tracer.h>
#include "GM/fsm/sceneGMFSM.h"
#include <GSLib/sceneSystem/GM/sceneScriptEnv.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

CSceneGMFSM::CSceneGMFSM(BSLib::Utility::CScriptObject* a_object)
: BSLib::FSM::CFSMBase(a_object)
{
	;
}

CSceneGMFSM::~CSceneGMFSM()
{
	;
}

bool CSceneGMFSM::initFSM()
{
	if (m_scriptInitFSM != NULL) {
		BSLib::Utility::CScriptData functionResult;
		if (!m_scriptInitFSM->execute(this->getObject(), &functionResult)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "initFSM[%s]", m_textInitFSM.c_str());
			return false;
		}
	}
	return true;
}

void CSceneGMFSM::finalFSM()
{
	if (m_scriptFinalFSM != NULL) {
		BSLib::Utility::CScriptData functionResult;
		if (!m_scriptFinalFSM->execute(this->getObject(), &functionResult)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "finalFSM[%s]", m_textFianlFSM.c_str());
			return ;
		}
	}
}

bool CSceneGMFSM::parseProperties(BSLib::Utility::CProperties* a_properties)
{
	a_properties->getValueString("init", m_textInitFSM);
	a_properties->getValueString("final", m_textFianlFSM);
	if (!m_textInitFSM.empty()) {
		m_scriptInitFSM = CSceneScriptEnv::singleton().parseFunctionList(m_textInitFSM);
		if (m_scriptInitFSM == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "½âÎöinitFSM[%s]", m_textInitFSM.c_str());
			return false;
		}
	}
	if (!m_textFianlFSM.empty()) {
		m_scriptFinalFSM = CSceneScriptEnv::singleton().parseFunctionList(m_textFianlFSM);
		if (m_scriptFinalFSM == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "½âÎöfinalFSM[%s]", m_textFianlFSM.c_str());
			return false;
		}
	}
	return true;
}

}//GM

}//SceneSystem

}//GSLib
