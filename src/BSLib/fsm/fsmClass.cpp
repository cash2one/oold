//////////////////////////////////////////////////////////////////////
//	created:	2014/08/18
//	filename: 	BSLib\fsm\fsmClass.hpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/hashMap.h>
#include <BSLib/fsm/fsmClass.h>

namespace BSLib
{

namespace FSM
{
//////////////////////////////////////////////////////////////////////////

CFSMCondition::CFSMCondition() 
{
	this->setJumpCondition(&CFSMCondition::jumpCondition, this);
	this->setProperties(&CFSMCondition::parseProperties, this);
}

bool CFSMCondition::parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
CFSMState::CFSMState(bool a_canEnter, bool a_canLeave)
{
	if (a_canEnter) {
		this->setEnterState(&CFSMState::enterState, this);
	}
	if (a_canLeave) {
		this->setLeaveState(&CFSMState::leaveState, this);
	}
	this->setExecuteState(&CFSMState::executeState, this);
	this->setProperties(&CFSMState::parseProperties, this);
}

void CFSMState::enterState(BSLib::Utility::CScriptObject* a_object)
{
	;
}

void CFSMState::leaveState(BSLib::Utility::CScriptObject* a_object) 
{
	;
}

bool CFSMState::parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties)
{ 
	return true;
}

void CFSMState::addJumpCondition(CFSMState* a_toState, CFSMCondition* a_condition)
{
	a_condition->setToState(a_toState);
	SFSMState::addJumpCondition(a_condition);
}

//////////////////////////////////////////////////////////////////////////
CFSM::CFSM(BSLib::Utility::CScriptObject* a_object)
: m_fsmTPID(0)
, m_fsmID(INVALID_FSMID)
, m_object(a_object)
{
	;
}

CFSM::~CFSM()
{
	;
}

bool CFSM::initFSM()
{
	return m_fsm.init(m_object);
}

bool CFSM::updateFSM()
{
	return m_fsm.update(m_object);
}

void CFSM::finalFSM()
{
	m_fsm.final(m_object);
}

bool CFSM::addState(const std::string& a_name, SFSMState* a_fsmState, bool isStart)
{
	return m_fsm.addState(a_name, a_fsmState, isStart);
}

bool CFSM::addJumpCondition(const std::string& a_fromStateName, const std::string a_toStateName, SFSMCondition* a_condition)
{
	return m_fsm.addJumpCondition(a_fromStateName, a_toStateName, a_condition);
}

bool CFSM::parseProperties(BSLib::Utility::CProperties* a_properties)
{
	return true;
}

}//FSM

}//BSLib

