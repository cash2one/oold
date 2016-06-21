#include <BSLib/utility/tracer.h>
#include <BSLib/fsm/fsmMgr.h>
#include "fsmFile.h"
#include "fsmScripCondition.h"
#include "fsmScripState.h"

namespace BSLib
{

namespace FSM
{

//////////////////////////////////////////////////////////////////////////
CFSMBase::CFSMBase(BSLib::Utility::CScriptObject* a_object) 
: CFSM(a_object)
{
	;
}

CFSMBase::~CFSMBase()
{
	_clear();
}

bool CFSMBase::addState(const std::string& a_name, SFSMState* a_fsmState, bool isStart)
{
	m_fsmStateList.push_back(a_fsmState);
	return CFSM::addState(a_name, a_fsmState, isStart);
}

bool CFSMBase::addJumpCondition(const std::string& a_fromStateName, const std::string a_toStateName, SFSMCondition* a_condition)
{
	m_fsmConditionList.push_back(a_condition);
	return CFSM::addJumpCondition(a_fromStateName, a_toStateName, a_condition);
}

void CFSMBase::_clear()
{
	std::vector<SFSMState*>::iterator it_state = m_fsmStateList.begin();
	for (; it_state != m_fsmStateList.end(); ++it_state) {
		SFSMState* fsmState = *it_state;
		if (fsmState != NULL) {
			BSLIB_SAFE_DELETE(fsmState);
		}
	}
	m_fsmStateList.clear();

	std::vector<SFSMCondition*>::iterator it_condition = m_fsmConditionList.begin();
	for (; it_condition != m_fsmConditionList.end(); ++it_condition) {
		SFSMCondition* fsmCondition = *it_condition;
		if (fsmCondition != NULL) {
			BSLIB_SAFE_DELETE(fsmCondition);
		}
	}
	m_fsmConditionList.clear();
}

//////////////////////////////////////////////////////////////////////////
CFSMMgr::CFSMMgr()
: m_fsmFile(NULL)
, m_createFsmFun(NULL)
{
	;
}

bool CFSMMgr::loadFSMFile(const std::string& a_fsmFile)
{
	if (m_fsmFile == NULL) {
		m_fsmFile = new CFSMFile();
		if (m_fsmFile == NULL) {
			return false;
		}
	}
	return m_fsmFile->loadFSMFile(a_fsmFile);
}

bool CFSMMgr::loadFSMNode(BSLib::Utility::CXmlFile* a_xmlFile, BSLib::Utility::HXmlNode& a_fsmNode)
{
	if (m_fsmFile == NULL) {
		m_fsmFile = new CFSMFile();
		if (m_fsmFile == NULL) {
			return false;
		}
	}
	return m_fsmFile->loadFSMNode(a_xmlFile, a_fsmNode);
}

CFSMMgr::~CFSMMgr()
{
	clear();
}

void CFSMMgr::init()
{
	registerCreateFSMStateFun("ScriptState", createFSMState<CFSMScriptState>);
	registerCreateFSMConditionFun("ScriptCondition", createFSMCondition<CFSMScriptCondition>);
}

void CFSMMgr::clear()
{
	BSLib::Utility::CHashMap<std::string, FSMStateFunction*>::iterator it_state = m_fsmStateFuns.begin();
	for (; it_state != m_fsmStateFuns.end(); ++it_state) {
		FSMStateFunction* stateFun = it_state->second;
		if (stateFun != NULL) {
			BSLIB_SAFE_DELETE(stateFun);
		}
	}
	m_fsmStateFuns.clear();

	BSLib::Utility::CHashMap<std::string, FSMConditionFunction*>::iterator it_condition = m_fsmConditionFuns.begin();
	for (; it_condition != m_fsmConditionFuns.end(); ++it_condition) {
		FSMConditionFunction* conditionFun = it_condition->second;
		if (conditionFun != NULL) {
			BSLIB_SAFE_DELETE(conditionFun);
		}
	}
	m_fsmConditionFuns.clear();

	BSLib::Utility::CHashMap<FSMID, CFSM*>::iterator it_fsm = m_fsms.begin();
	for (; it_fsm != m_fsms.end(); ++it_fsm) {
		CFSM* fsm = it_fsm->second;
		if (fsm != NULL) {
			BSLIB_SAFE_DELETE(fsm);
		}
	}
	m_fsms.clear();
}

bool CFSMMgr::createFSM(const std::string& a_fsmName, BSLib::Utility::CScriptObject* a_object, CFSM** a_fsm)
{
	if (m_fsmFile == NULL) {
		return false;
	}
	SFSMInfor* fsmInfor = m_fsmFile->getFsmInfor(a_fsmName);
	if (fsmInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "获取FSM失败[name=%s]", a_fsmName.c_str());
		return false;
	}
	if (!_createFSM(fsmInfor, a_object, a_fsm)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "创建FSM失败[name=%s]", a_fsmName.c_str());
		return false;
	}
	if ((*a_fsm) == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "创建FSM失败[name=%s]", a_fsmName.c_str());
		return false;
	}
	if (!(*a_fsm)->initFSM()) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "初始化FSM失败[name=%s]", a_fsmName.c_str());
		return false;
	}
	return true;
}

bool CFSMMgr::createFSM(FSMTPID a_fsmTPID, BSLib::Utility::CScriptObject* a_object, CFSM** a_fsm)
{
	if (m_fsmFile == NULL) {
		return false;
	}
	SFSMInfor* fsmInfor = m_fsmFile->getFsmInfor(a_fsmTPID);
	if (fsmInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "获取FSM失败[id=%d]", a_fsmTPID);
		return false;
	}
	if (!_createFSM(fsmInfor, a_object, a_fsm)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "创建FSM失败[id=%d]", a_fsmTPID);
		return false;
	}
	if ((*a_fsm) == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "创建FSM失败[id=%d]", a_fsmTPID);
		return false;
	}
	if (!(*a_fsm)->initFSM()) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "初始化FSM失败[id=%d]", a_fsmTPID);
		return false;
	}
	return true;
}

CFSM* CFSMMgr::getFSM(FSMID a_fsmID)
{
	CFSM* fsm = NULL;
	m_fsms.getValue(a_fsmID, fsm);
	return fsm;
}

void CFSMMgr::removeFSM(FSMID a_fsmID)
{
	CFSM* fsm = NULL;
	m_fsms.getValue(a_fsmID, fsm);
	if (fsm != NULL) {
		fsm->finalFSM();
		BSLIB_SAFE_DELETE(fsm);
	}
	m_fsms.remove(a_fsmID);
}

void CFSMMgr::removeFSM(CFSM** a_fsm)
{
	CFSM* fsmRemove = *a_fsm; 
	if (fsmRemove == NULL) {
		return ;
	}
	CFSM* fsm = NULL;
	m_fsms.getValue(fsmRemove->getFSMID(), fsm);
	if (fsm != fsmRemove) {
		return ;
	}
	if (fsm != NULL) {
		fsm->finalFSM();
		BSLIB_SAFE_DELETE(*a_fsm);
	}
	m_fsms.remove(fsmRemove->getFSMID());
}

// 设置创建FSM State函数
void CFSMMgr::registerCreateFSMStateFun(const std::string& a_name, SFSMState*(*a_fun)(BSLib::Utility::CScriptObject*, const std::string&, BSLib::Utility::CProperties&, CFSM*))
{
	FSMStateFunction fun(a_fun);
	registerCreateFSMStateFun(a_name, fun);
}

void CFSMMgr::registerCreateFSMStateFun(const std::string& a_name, FSMStateFunction& a_fun)
{
	BSLib::Utility::CHashMap<std::string, FSMStateFunction*>::iterator it = m_fsmStateFuns.find(a_name);
	if (it != m_fsmStateFuns.end()) {
		FSMStateFunction* fun = it->second;
		if (fun != NULL) {
			BSLIB_SAFE_DELETE(fun);
			m_fsmStateFuns.remove(a_name);
		}
	}
	FSMStateFunction* funClone = a_fun.clone();
	if (funClone == NULL) {
		return ;
	}
	m_fsmStateFuns.setValue(a_name, funClone);
}

//设置FSM Condition函数
void CFSMMgr::registerCreateFSMConditionFun(const std::string& a_name, SFSMCondition*(*a_fun)(BSLib::Utility::CScriptObject*, const std::string&, BSLib::Utility::CProperties&, CFSM*))
{
	FSMConditionFunction fun(a_fun);
	registerCreateFSMConditionFun(a_name, fun);
}

void CFSMMgr::registerCreateFSMConditionFun(const std::string& a_name, FSMConditionFunction& a_fun)
{
	BSLib::Utility::CHashMap<std::string, FSMConditionFunction*>::iterator it = m_fsmConditionFuns.find(a_name);
	if (it != m_fsmConditionFuns.end()) {
		FSMConditionFunction* fun = it->second;
		if (fun != NULL) {
			BSLIB_SAFE_DELETE(fun);
			m_fsmConditionFuns.remove(a_name);
		}
	}
	FSMConditionFunction* funClone = a_fun.clone();
	if (funClone == NULL) {
		return ;
	}
	m_fsmConditionFuns.setValue(a_name, funClone);
}

void CFSMMgr::registerCreateFSMFun(CFSM*(*a_fun)(BSLib::Utility::CScriptObject*, const std::string&))
{
	FSMFunction fun(a_fun);
	registerCreateFSMFun(fun);
}

void CFSMMgr::registerCreateFSMFun(FSMFunction& a_fun)
{
	if (m_createFsmFun != NULL) {
		BSLIB_SAFE_DELETE(m_createFsmFun);
	}
	m_createFsmFun = a_fun.clone();
}

BSLib::Utility::CProperties* CFSMMgr::getFsmsProperties() 
{ 
	return m_fsmFile->getFsmsProperties(); 
}

CFSM* CFSMMgr::_createFSM(BSLib::Utility::CScriptObject* a_object, const std::string& a_fsmName)
{
	CFSM* fsm = new CFSMBase(a_object);
	return fsm;
}

bool CFSMMgr::_createFSM(SFSMInfor* a_fsmInfor, BSLib::Utility::CScriptObject* a_object, CFSM** a_fsm)
{
	FSMID fsmID = m_uniqueID.allocateID();
	if (fsmID == INVALID_FSMID) {
		return false;
	}
	CFSM* fsm = NULL;
	if (m_createFsmFun == NULL) {
		fsm = _createFSM(a_object, a_fsmInfor->m_fsmName);
	} else {
		fsm = (*m_createFsmFun)(a_object, a_fsmInfor->m_fsmName);
	}
	if (fsm == NULL) {
		return false;
	}
	
	fsm->_setFSMID(fsmID);
	fsm->_setFSMTPID(a_fsmInfor->m_fsmTPID);

	//创建FSMState
	for (BSLib::uint32 i_state=0; i_state < a_fsmInfor->m_states.size(); ++i_state) {
		SFSMStateInfor* stateInfor = a_fsmInfor->m_states[i_state];
		if (stateInfor == NULL) {
			continue;
		}
		FSMStateFunction* stateFun = _getFsmStateFun(stateInfor->m_stateType);
		if (stateFun == NULL) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "获取state失败[type=%s][name=%s]", stateInfor->m_stateType.c_str(), stateInfor->m_stateName.c_str());
			BSLIB_SAFE_DELETE(fsm);
			return false;
		}
		SFSMState* fsmState = (*stateFun)(a_object, stateInfor->m_stateType, stateInfor->m_properties, fsm);
		if (fsmState == NULL) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "创建state失败[type=%s][name=%s]", stateInfor->m_stateType.c_str(), stateInfor->m_stateName.c_str());
			BSLIB_SAFE_DELETE(fsm);
			return false;
		}
		if (stateInfor->m_stateName.empty()) {
			if (!fsm->addState(stateInfor->m_stateType, fsmState, stateInfor->m_isStart)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "增加state失败[type=%s][name=%s]", stateInfor->m_stateType.c_str(), stateInfor->m_stateName.c_str());
				BSLIB_SAFE_DELETE(fsm);
				return false;
			}
		} else {
			if (!fsm->addState(stateInfor->m_stateName, fsmState, stateInfor->m_isStart)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "增加state失败[type=%s][name=%s]", stateInfor->m_stateType.c_str(), stateInfor->m_stateName.c_str());
				BSLIB_SAFE_DELETE(fsm);
				return false;
			}
		}
		if (!fsmState->initState(a_object, &stateInfor->m_properties)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "初始化state失败[type=%s][name=%s]", stateInfor->m_stateType.c_str(), stateInfor->m_stateName.c_str());
			BSLIB_SAFE_DELETE(fsm);
			return false;
		}
	}
	//创建FSMCondition
	for (BSLib::uint32 i_condition=0; i_condition<a_fsmInfor->m_conditions.size(); ++i_condition) {
		SFSMConditionInfor* conditionInfor = a_fsmInfor->m_conditions[i_condition];
		if (conditionInfor == NULL) {
			continue;
		}
		FSMConditionFunction* conditionFun = _getFsmConditionFun(conditionInfor->m_conditionType);
		if (conditionFun == NULL) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "获取jump失败[type=%s][from=%s][to=%s]", conditionInfor->m_conditionType.c_str(),conditionInfor->m_fromStateName.c_str(), conditionInfor->m_toStateName.c_str());
			BSLIB_SAFE_DELETE(fsm);
			return false;
		}
		SFSMCondition* fsmCondition = (*conditionFun)(a_object, conditionInfor->m_conditionType, conditionInfor->m_properties, fsm);
		if (fsmCondition == NULL) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "创建jump失败[type=%s][from=%s][to=%s]", conditionInfor->m_conditionType.c_str(),conditionInfor->m_fromStateName.c_str(), conditionInfor->m_toStateName.c_str());
			BSLIB_SAFE_DELETE(fsm);
			return false;
		}
		if (!fsm->addJumpCondition(conditionInfor->m_fromStateName, conditionInfor->m_toStateName, fsmCondition)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "设置jump失败[type=%s][from=%s][to=%s]", conditionInfor->m_conditionType.c_str(),conditionInfor->m_fromStateName.c_str(), conditionInfor->m_toStateName.c_str());
			BSLIB_SAFE_DELETE(fsm);
			return false;
		}
		if (!fsmCondition->initCondition(a_object, &conditionInfor->m_properties)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "初始化jump失败[type=%s][from=%s][to=%s]", conditionInfor->m_conditionType.c_str(),conditionInfor->m_fromStateName.c_str(), conditionInfor->m_toStateName.c_str());
			BSLIB_SAFE_DELETE(fsm);
			return false;
		}
	}
	fsm->parseProperties(&a_fsmInfor->m_properties);
	m_fsms.setValue(fsmID, fsm);

	*a_fsm = fsm;

	return true;
}

FSMStateFunction* CFSMMgr::_getFsmStateFun(const std::string& a_fsmStateType)
{
	BSLib::Utility::CHashMap<std::string, FSMStateFunction*>::iterator it = m_fsmStateFuns.find(a_fsmStateType);
	if (it == m_fsmStateFuns.end()) {
		return NULL;
	}
	return it->second;
}

FSMConditionFunction* CFSMMgr::_getFsmConditionFun(const std::string& a_fsmConditionType)
{
	BSLib::Utility::CHashMap<std::string, FSMConditionFunction*>::iterator it = m_fsmConditionFuns.find(a_fsmConditionType);
	if (it == m_fsmConditionFuns.end()) {
		return NULL;
	}
	return it->second;
}

bool CFSMMgr::checkUniqueID(FSMID id)
{
	return m_fsms.find(id) != m_fsms.end();
}

}//FSM

}//BSLib

