#include <BSLib/utility/tracer.h>
#include "fsmScripCondition.h"

namespace BSLib
{

namespace FSM
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
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "Ö´ÐÐ[%s]Ê§°Ü", m_textJumpCondition.c_str());
			return false;
		}
	}
	return result;
}

bool CFSMScriptCondition::parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties)
{
	BSLib::Utility::CScriptEnvironment* scriptEvironment = a_object->getScriptEnvironment();
	if (scriptEvironment == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "»ñÈ¡CScriptEnvironmentÊ§°Ü");
		return false;
	}

	a_properties->getValueString("expression", m_textJumpCondition);
	if (!m_textJumpCondition.empty()) {
		m_scriptJumpCondition = scriptEvironment->parseExpression(m_textJumpCondition);
		if (m_scriptJumpCondition == NULL) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "½âÎö[%s]Ê§°Ü", m_textJumpCondition.c_str());
			return false;
		}
	}
	return true;
}

}//FSM

}//BSLib

