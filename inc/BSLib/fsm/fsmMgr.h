//////////////////////////////////////////////////////////////////////
//	created:	2014/08/18
//	filename: 	BSLib\fsm\fsmMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_FSM_FSMMGR_H__
#define __BSLIB_FSM_FSMMGR_H__

#include <BSLib/utility/file/xmlFile.h>
#include <BSLib/fsm/fsmClass.h>
#include <BSLib/utility/uniqueID.h>

namespace BSLib
{

namespace FSM
{

class CFSMFile;
struct SFSMInfor;

template<typename T>
SFSMState* createFSMState(BSLib::Utility::CScriptObject* a_object, const std::string& a_stateName, BSLib::Utility::CProperties& a_properties, CFSM* a_fsm)
{
	return new T();
}

template<typename T>
SFSMCondition* createFSMCondition(BSLib::Utility::CScriptObject* a_object, const std::string& a_conditionName, BSLib::Utility::CProperties& a_properties, CFSM* a_fsm)
{
	return new T();
}

typedef BSLib::Utility::CFunction<SFSMState*, BSLib::Utility::CScriptObject*, const std::string&, BSLib::Utility::CProperties&, CFSM*> FSMStateFunction;
typedef BSLib::Utility::CFunction<SFSMCondition*, BSLib::Utility::CScriptObject*, const std::string&, BSLib::Utility::CProperties&, CFSM*> FSMConditionFunction;
typedef BSLib::Utility::CFunction<CFSM*, BSLib::Utility::CScriptObject*, const std::string&> FSMFunction;

class CFSMBase : public CFSM
{
public: 
	CFSMBase(BSLib::Utility::CScriptObject* a_object);

	virtual ~CFSMBase();

	virtual bool addState(const std::string& a_name, SFSMState* a_fsmState, bool isStart = false);

	virtual bool addJumpCondition(const std::string& a_fromStateName, const std::string a_toStateName, SFSMCondition* a_condition);

private:
	void _clear();

private:
	std::vector<SFSMState*> m_fsmStateList;
	std::vector<SFSMCondition*> m_fsmConditionList;
};

class CFSMMgr : public BSLib::Utility::CUniqueIDMgr<FSMID>
{
public:
	CFSMMgr();

	~CFSMMgr();

	bool loadFSMFile(const std::string& a_fsmFile);
	bool loadFSMNode(BSLib::Utility::CXmlFile* a_xmlFile, BSLib::Utility::HXmlNode& a_fsmNode);

	void init();
	void clear();

	bool createFSM(const std::string& a_fsmName, BSLib::Utility::CScriptObject* a_object, CFSM** a_fsm);
	bool createFSM(FSMTPID a_fsmTPID, BSLib::Utility::CScriptObject* a_object, CFSM** a_fsm);

	
	CFSM* getFSM(FSMID a_fsmID);

	void removeFSM(FSMID a_fsmID);

	void removeFSM(CFSM** a_fsm);

	// 设置创建FSM State函数
	void registerCreateFSMStateFun(const std::string& a_name, SFSMState*(*a_fun)(BSLib::Utility::CScriptObject*, const std::string&, BSLib::Utility::CProperties&, CFSM*));

	void registerCreateFSMStateFun(const std::string& a_name, FSMStateFunction& a_fun);

	template<class NAME>
	void registerCreateFSMStateFun(const std::string& a_name, SFSMState*(NAME::*a_fun)(BSLib::Utility::CScriptObject*, const std::string&, BSLib::Utility::CProperties&, CFSM*), NAME* a_object)
	{
		BSLib::Utility::CFunctionObject<SFSMState*, NAME, BSLib::Utility::CScriptObject*, const std::string&, BSLib::Utility::CProperties&, CFSM*> fun(a_fun, a_object);
		registerCreateFSMStateFun(a_name, fun);
	}

	//设置FSM Condition函数
	void registerCreateFSMConditionFun(const std::string& a_name, SFSMCondition*(*a_fun)(BSLib::Utility::CScriptObject*, const std::string&, BSLib::Utility::CProperties&, CFSM*));

	void registerCreateFSMConditionFun(const std::string& a_name, FSMConditionFunction& a_fun);

	template<class NAME>
	void registerCreateFSMConditionFun(const std::string& a_name, SFSMCondition*(NAME::*a_fun)(BSLib::Utility::CScriptObject*, const std::string&, BSLib::Utility::CProperties&, CFSM*), NAME* a_object)
	{
		BSLib::Utility::CFunctionObject<SFSMCondition*, NAME, BSLib::Utility::CScriptObject*, const std::string&, BSLib::Utility::CProperties&, CFSM*> fun(a_fun, a_object);
		registerCreateFSMConditionFun(a_name, fun);
	}

	//设置FSM创建函数
	void registerCreateFSMFun(CFSM*(*a_fun)(BSLib::Utility::CScriptObject*, const std::string&));

	void registerCreateFSMFun(FSMFunction& a_fun);

	template<class NAME>
	void registerCreateFSMFun(CFSM*(NAME::*a_fun)(BSLib::Utility::CScriptObject*, const std::string&), NAME* a_object)
	{
		BSLib::Utility::CFunctionObject<CFSM*, NAME, BSLib::Utility::CScriptObject*, const std::string&> fun(a_fun, a_object);
		registerCreateFSMFun(fun);
	}

	BSLib::Utility::CProperties* getFsmsProperties();

protected:

	virtual CFSM* _createFSM(BSLib::Utility::CScriptObject* a_object, const std::string& a_fsmName);

private:
	bool _createFSM(SFSMInfor* a_fsmInfor, BSLib::Utility::CScriptObject* a_object, CFSM** a_fsm);
	FSMStateFunction* _getFsmStateFun(const std::string& a_fsmStateName);

	FSMConditionFunction* _getFsmConditionFun(const std::string& a_fsmConditionName);

	virtual bool checkUniqueID(FSMID id);

private:
	CFSMFile* m_fsmFile;
	BSLib::Utility::CHashMap<std::string, FSMStateFunction*> m_fsmStateFuns;
	BSLib::Utility::CHashMap<std::string, FSMConditionFunction*> m_fsmConditionFuns;
	BSLib::Utility::CHashMap<FSMID, CFSM*> m_fsms;
	BSLib::Utility::CUniqueID<FSMID> m_uniqueID;
	FSMFunction* m_createFsmFun;

};

}//FSM

}//BSLib

#endif //__BSLIB_FSM_FSMMGR_H__