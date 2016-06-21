#ifndef ___GSLIB_SCENESYSTEM_GM_FSM_FSMSCRIPCONDITION_H__
#define ___GSLIB_SCENESYSTEM_GM_FSM_FSMSCRIPCONDITION_H__

#include <BSLib/fsm/fsmClass.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
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

}//GM

}//SceneSystem

}//GSLib

#endif//___GSLIB_SCENESYSTEM_GM_FSM_FSMSCRIPCONDITION_H__
