#ifndef ___BSLIB_FSM_FSMSCRIPCONDITION_H__
#define ___BSLIB_FSM_FSMSCRIPCONDITION_H__

#include <BSLib/fsm/fsmClass.h>

namespace BSLib
{

namespace FSM
{

class CFSMScriptCondition : public BSLib::FSM::CFSMCondition
{
public:
	CFSMScriptCondition();
	virtual ~CFSMScriptCondition();

	virtual bool jumpCondition(BSLib::Utility::CScriptObject* a_object);

	virtual bool parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties);

private:
	std::string m_textJumpCondition;
	BSLib::Utility::IScriptPtr m_scriptJumpCondition;
};

}//FSM

}//BSLib

#endif//___BSLIB_FSM_FSMSCRIPCONDITION_H__
