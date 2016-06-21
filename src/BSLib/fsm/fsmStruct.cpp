#include <BSLib/fsm/fsmStruct.h>

namespace BSLib
{

namespace FSM
{

SFSMCondition::SFSMCondition()
: m_toState(NULL)
, m_jumpCondition(NULL)
, m_properties(NULL) 
{
	;
}

SFSMCondition::~SFSMCondition()
{
	if (m_jumpCondition) {
		BSLIB_SAFE_DELETE(m_jumpCondition);
	}
	if (m_properties) {
		BSLIB_SAFE_DELETE(m_properties);
	}
}

void SFSMCondition::setToState(SFSMState* a_toState)
{
	m_toState = a_toState;
}


// 设置条件解析函数
void SFSMCondition::setJumpCondition(bool(*a_fun)(BSLib::Utility::CScriptObject*))
{
	if (m_jumpCondition != NULL) {
		BSLIB_SAFE_DELETE(m_jumpCondition);
	}
	m_jumpCondition = new BSLib::Utility::CFunction<bool, BSLib::Utility::CScriptObject*>(a_fun);
}

void SFSMCondition::setJumpCondition(BSLib::Utility::CFunction<bool, BSLib::Utility::CScriptObject*>& a_fun)
{
	if (m_jumpCondition != NULL) {
		BSLIB_SAFE_DELETE(m_jumpCondition);
	}
	m_jumpCondition = a_fun.clone();
}

// 设置条件参数解析函数
void SFSMCondition::setProperties(bool(*a_fun)(BSLib::Utility::CScriptObject*, BSLib::Utility::CProperties*))
{
	if (m_properties != NULL) {
		BSLIB_SAFE_DELETE(m_properties);
	}
	m_properties = new SFSMPropertiesFunction(a_fun);
}

void SFSMCondition::setProperties(SFSMPropertiesFunction& a_fun)
{
	if (m_properties != NULL) {
		BSLIB_SAFE_DELETE(m_properties);
	}
	m_properties = a_fun.clone();
}

bool SFSMCondition::initCondition(BSLib::Utility::CScriptObject* a_fsmObject, BSLib::Utility::CProperties* a_properties)
{
	if (m_properties == NULL) {
		return false;
	}
	return (*m_properties)(a_fsmObject, a_properties);
}

//////////////////////////////////////////////////////////////////////////

SFSMState::SFSMState()
: m_enterState(NULL)
, m_executeState(NULL)
, m_leaveState(NULL)
, m_properties(NULL)
{
	;
}

SFSMState::~SFSMState()
{
	if (m_enterState != NULL) {
		BSLIB_SAFE_DELETE(m_enterState);
	}

	if (m_executeState != NULL) {
		BSLIB_SAFE_DELETE(m_executeState);
	}

	if (m_leaveState != NULL) {
		BSLIB_SAFE_DELETE(m_leaveState);
	}
	if (m_properties) {
		BSLIB_SAFE_DELETE(m_properties);
	}
	m_jumpList.clear();
}

// 设置进入状态处理函数 
void SFSMState::setEnterState(void(*a_fun)(BSLib::Utility::CScriptObject*))
{
	if (m_enterState != NULL) {
		BSLIB_SAFE_DELETE(m_enterState);
	}
	m_enterState = new BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>(a_fun);
}

void SFSMState::setEnterState(BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>& a_fun)
{
	if (m_enterState != NULL) {
		BSLIB_SAFE_DELETE(m_enterState);
	}
	m_enterState = a_fun.clone();
}

// 设置离开状态处理函数 
void SFSMState::setLeaveState(void(*a_fun)(BSLib::Utility::CScriptObject*))
{
	if (m_leaveState != NULL) {
		BSLIB_SAFE_DELETE(m_leaveState);
	}
	m_leaveState = new BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>(a_fun);
}

void SFSMState::setLeaveState(BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>& a_fun)
{
	if (m_leaveState != NULL) {
		BSLIB_SAFE_DELETE(m_leaveState);
	}
	m_leaveState = a_fun.clone();
}

// 设置状态执行处理函数 
void SFSMState::setExecuteState(void(*a_fun)(BSLib::Utility::CScriptObject*))
{
	if (m_executeState != NULL) {
		BSLIB_SAFE_DELETE(m_executeState);
	}
	m_executeState = new BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>(a_fun);
}

void SFSMState::setExecuteState(BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>& a_fun)
{
	if (m_executeState != NULL) {
		BSLIB_SAFE_DELETE(m_executeState);
	}
	m_executeState = a_fun.clone();
}

// 设置状态参数解析函数
void SFSMState::setProperties(bool(*a_fun)(BSLib::Utility::CScriptObject*, BSLib::Utility::CProperties*))
{
	if (m_properties != NULL) {
		BSLIB_SAFE_DELETE(m_properties);
	}
	m_properties = new SFSMPropertiesFunction(a_fun);
}

void SFSMState::setProperties(SFSMPropertiesFunction& a_fun)
{
	if (m_properties != NULL) {
		BSLIB_SAFE_DELETE(m_properties);
	}
	m_properties = a_fun.clone();
}

void SFSMState::addJumpCondition(SFSMCondition* a_jumpCondition)
{
	m_jumpList.push_back(a_jumpCondition);
}

bool SFSMState::initState(BSLib::Utility::CScriptObject* a_fsmObject, BSLib::Utility::CProperties* a_properties)
{
	if (m_properties == NULL) {
		return false;
	}
	return (*m_properties)(a_fsmObject, a_properties);
}

//////////////////////////////////////////////////////////////////////////

SFSM::SFSM()
: m_currentState(NULL) 
{
	;
}

SFSM::~SFSM() 
{
	;
}

bool SFSM::init(BSLib::Utility::CScriptObject* a_fsmObject)
{
	if (m_currentState == NULL) {
		return false;
	}
	BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>* fun = m_currentState->m_enterState;
	if (fun != NULL) {
		(*fun)(a_fsmObject);
		return true;
	}
	return false;
}

bool SFSM::update(BSLib::Utility::CScriptObject* a_fsmObject)
{
	if (m_currentState == NULL) {
		return false;
	}
	std::vector<SFSMCondition*>::iterator it = m_currentState->m_jumpList.begin();
	for (; it != m_currentState->m_jumpList.end(); ++it) {
		SFSMCondition* fsmCondition = *it;
		if (fsmCondition == NULL) {
			return false;
		}
		if (fsmCondition->m_jumpCondition == NULL){
			continue;
		}
		BSLib::Utility::CFunction<bool, BSLib::Utility::CScriptObject*>* fun = fsmCondition->m_jumpCondition;
		if ((*fun)(a_fsmObject)) {
			BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>* funLeave = m_currentState->m_leaveState;
			if (funLeave != NULL) {
				(*funLeave)(a_fsmObject);
			}
			m_currentState = fsmCondition->m_toState;
			if (m_currentState == NULL) {
				return false;
			}
			BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>* funEnter = m_currentState->m_enterState;
			if (funEnter != NULL) {
				(*funEnter)(a_fsmObject);
			}
			BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>* funExecute = m_currentState->m_executeState;
			if (funExecute != NULL) {
				(*funExecute)(a_fsmObject);
				return true;
			}
			return true;
		}
	}
	BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>* funExecute = m_currentState->m_executeState;
	if (funExecute != NULL) {
		(*funExecute)(a_fsmObject);
		return true;
	}
	return false;
}

void SFSM::final(BSLib::Utility::CScriptObject* a_fsmObject)
{
	if (m_currentState == NULL) {
		return ;
	}
	BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>* fun = m_currentState->m_leaveState;
	if (fun != NULL) {
		(*fun)(a_fsmObject);
	}
}

bool SFSM::addState(const std::string& a_name, SFSMState* a_fsmState, bool isStart)
{
	if (m_fsmStates.find(a_name) != m_fsmStates.end()) {
		return false;
	}
	if (isStart) {
		m_currentState = a_fsmState;
	}
	m_fsmStates.setValue(a_name, a_fsmState);
	return true;
}

void SFSM::setStartState(SFSMState* a_currentState)
{
	m_currentState = a_currentState;
}

bool SFSM::addJumpCondition(const std::string& a_fromStateName, const std::string a_toStateName, SFSMCondition* a_condition)
{
	BSLib::Utility::CHashMap<std::string, SFSMState*>::iterator it_from = m_fsmStates.find(a_fromStateName);
	if (it_from == m_fsmStates.end()) {
		return false;
	}
	SFSMState* fromState = it_from->second;
	if (fromState == NULL) {
		return false;
	}

	BSLib::Utility::CHashMap<std::string, SFSMState*>::iterator it_to = m_fsmStates.find(a_toStateName);
	if (it_to == m_fsmStates.end()) {
		return false;
	}
	SFSMState* toState = it_to->second;
	if (toState == NULL) {
		return false;
	}
	a_condition->setToState(toState);
	fromState->addJumpCondition(a_condition);
	return true;
}


}//FSM

}//BSLib

