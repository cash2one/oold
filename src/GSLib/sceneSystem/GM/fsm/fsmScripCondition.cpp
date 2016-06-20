//////////////////////////////////////////////////////////////////////
//	created:	2014/08/22
//	filename: 	src\GSLib\sceneSystem\GM\fsm\fsmScripCondition.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/tracer.h>
#include "GM/fsm/fsmScripCondition.h"
#include <GSLib/sceneSystem/GM/sceneScriptEnv.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{

CFSMScriptCondition::CFSMScriptCondition()
{
	;
}

CFSMScriptCondition::~CFSMScriptCondition()
{
	;
}

bool CFSMScriptCondition::jumpCondition(BSLib::Utility::CScriptObject* a_object)
{
	bool result = false;
	if (m_scriptJumpCondition != NULL) {
		if (!m_scriptJumpCondition->execute(a_object, result)) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "Ö´ÐÐ[%s]Ê§°Ü", m_textJumpCondition.c_str());
			return false;
		}
	}
	return result;
}

bool CFSMScriptCondition::parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties)
{
	a_properties->getValueString("expression", m_textJumpCondition);
	if (!m_textJumpCondition.empty()) {
		m_scriptJumpCondition = CSceneScriptEnv::singleton().parseExpression(m_textJumpCondition);
		if (m_scriptJumpCondition == NULL) {
			BSLIB_LOG_ERROR(ETT_GSLIB_SCENESYSTEM, "½âÎö[%s]Ê§°Ü", m_textJumpCondition.c_str());
			return false;
		}
	}
	return true;
}

}//GM

}//SceneSystem

}//GSLib