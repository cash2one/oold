#ifndef __BSLIB_FSM_FSMSTRUCT_H__
#define __BSLIB_FSM_FSMSTRUCT_H__

#include <BSLib/utility/script.h>
#include <BSLib/utility/function.h>
#include <BSLib/utility/command.h>

namespace BSLib
{

namespace FSM
{

struct SFSMState;

//////////////////////////////////////////////////////////////////////////

struct SFSMCondition
{
public:
	typedef BSLib::Utility::CFunction<bool, BSLib::Utility::CScriptObject*, BSLib::Utility::CProperties*> SFSMPropertiesFunction;

public:
	SFSMCondition();
	virtual ~SFSMCondition();

	void setToState(SFSMState* a_toState);

	// 设置条件解析函数
	void setJumpCondition(bool(*a_fun)(BSLib::Utility::CScriptObject*));
	void setJumpCondition(BSLib::Utility::CFunction<bool, BSLib::Utility::CScriptObject*>& a_fun);

	template<class NAME>
	void setJumpCondition(bool(NAME::*a_fun)(BSLib::Utility::CScriptObject*), NAME* a_object)
	{
		BSLib::Utility::CFunctionObject<bool, NAME, BSLib::Utility::CScriptObject*> objFun(a_fun, a_object);
		return setJumpCondition(objFun);
	}

	// 设置条件参数解析函数
	void setProperties(bool(*a_fun)(BSLib::Utility::CScriptObject*, BSLib::Utility::CProperties*));
	void setProperties(SFSMPropertiesFunction& a_fun);

	template<class NAME>
	void setProperties(bool(NAME::*a_fun)(BSLib::Utility::CScriptObject*, BSLib::Utility::CProperties*), NAME* a_object)
	{
		BSLib::Utility::CFunctionObject<bool, NAME, BSLib::Utility::CScriptObject*, BSLib::Utility::CProperties*> objFun(a_fun, a_object);
		return setProperties(objFun);
	}

	bool initCondition(BSLib::Utility::CScriptObject* a_fsmObject, BSLib::Utility::CProperties* a_properties);

private:
	SFSMState* m_toState;
	BSLib::Utility::CFunction<bool, BSLib::Utility::CScriptObject*>* m_jumpCondition;
	SFSMPropertiesFunction* m_properties;

	friend struct SFSM;
};

//////////////////////////////////////////////////////////////////////////

struct SFSMState
{
public:
	typedef BSLib::Utility::CFunction<bool, BSLib::Utility::CScriptObject*, BSLib::Utility::CProperties*> SFSMPropertiesFunction;

public:
	SFSMState();
	virtual ~SFSMState();

	// 设置进入状态处理函数 
	void setEnterState(void(*a_fun)(BSLib::Utility::CScriptObject*));
	void setEnterState(BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>& a_fun);

	template<class NAME>
	void setEnterState(void(NAME::*a_fun)(BSLib::Utility::CScriptObject*), NAME* a_object)
	{
		BSLib::Utility::CFunctionObject<void, NAME, BSLib::Utility::CScriptObject*> objFun(a_fun, a_object);
		return setEnterState(objFun);
	}

	// 设置离开状态处理函数 
	void setLeaveState(void(*a_fun)(BSLib::Utility::CScriptObject*));
	void setLeaveState(BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>& a_fun);

	template<class NAME>
	void setLeaveState(void(NAME::*a_fun)(BSLib::Utility::CScriptObject*), NAME* a_object)
	{
		BSLib::Utility::CFunctionObject<void, NAME, BSLib::Utility::CScriptObject*> objFun(a_fun, a_object);
		return setLeaveState(objFun);
	}

	// 设置状态执行处理函数 
	void setExecuteState(void(*a_fun)(BSLib::Utility::CScriptObject*));
	void setExecuteState(BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>& a_fun);

	template<class NAME>
	void setExecuteState(void(NAME::*a_fun)(BSLib::Utility::CScriptObject*), NAME* a_object)
	{
		BSLib::Utility::CFunctionObject<void, NAME, BSLib::Utility::CScriptObject*> objFun(a_fun, a_object);
		return setExecuteState(objFun);
	}

	// 设置状态参数解析函数
	void setProperties(bool(*a_fun)(BSLib::Utility::CScriptObject*, BSLib::Utility::CProperties*));
	void setProperties(SFSMPropertiesFunction& a_fun);

	template<class NAME>
	void setProperties(bool(NAME::*a_fun)(BSLib::Utility::CScriptObject*, BSLib::Utility::CProperties*), NAME* a_object)
	{
		BSLib::Utility::CFunctionObject<bool, NAME, BSLib::Utility::CScriptObject*, BSLib::Utility::CProperties*> objFun(a_fun, a_object);
		return setProperties(objFun);
	}

	void addJumpCondition(SFSMCondition* a_jumpCondition);

	bool initState(BSLib::Utility::CScriptObject* a_fsmObject, BSLib::Utility::CProperties* a_properties);

private:
	BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>* m_enterState;
	BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>* m_executeState;
	BSLib::Utility::CFunction<void, BSLib::Utility::CScriptObject*>* m_leaveState;
	SFSMPropertiesFunction* m_properties;

	std::vector<SFSMCondition*> m_jumpList;

	friend struct SFSM;
};

//////////////////////////////////////////////////////////////////////////

struct SFSM
{
public:
	SFSM();
	virtual ~SFSM();

	bool init(BSLib::Utility::CScriptObject* a_fsmObject);

	bool update(BSLib::Utility::CScriptObject* a_fsmObject);

	void final(BSLib::Utility::CScriptObject* a_fsmObject);

	bool addState(const std::string& a_name, SFSMState* a_fsmState, bool isStart = false);

	void setStartState(SFSMState* a_currentState);

	bool addJumpCondition(const std::string& a_fromStateName, const std::string a_toStateName, SFSMCondition* a_condition);

private:
	SFSMState* m_currentState;
	BSLib::Utility::CHashMap<std::string, SFSMState*> m_fsmStates;
};

}//FSM

}//BSLib

#endif //__BSLIB_FSM_FSMSTRUCT_H__

