#ifndef __BSLIB_FSM_FSMCLASS_H__
#define __BSLIB_FSM_FSMCLASS_H__

#include <BSLib/utility/hashMap.h>
#include <BSLib/fsm/fsmStruct.h>

namespace BSLib
{

typedef BSLib::uint32 FSMTPID;

typedef BSLib::uint32 FSMID;
const FSMID INVALID_FSMID = 0;

namespace FSM
{
	
//////////////////////////////////////////////////////////////////////////

class CFSMCondition : public SFSMCondition
{
public:
	CFSMCondition();

	virtual bool jumpCondition(BSLib::Utility::CScriptObject* a_object) = 0;

	virtual bool parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties);
};

//////////////////////////////////////////////////////////////////////////

class CFSMState : public SFSMState
{
public:
	CFSMState(bool a_canEnter = false, bool a_canLeave = false);

	virtual void enterState(BSLib::Utility::CScriptObject* a_object);

	virtual void executeState(BSLib::Utility::CScriptObject* a_object) = 0;
	
	virtual void leaveState(BSLib::Utility::CScriptObject* a_object);

	virtual bool parseProperties(BSLib::Utility::CScriptObject* a_object, BSLib::Utility::CProperties* a_properties);

	void addJumpCondition(CFSMState* a_toState, CFSMCondition* a_condition);
};

//////////////////////////////////////////////////////////////////////////

class CFSM
{
public:
	CFSM(BSLib::Utility::CScriptObject* a_object);
	virtual ~CFSM();

	virtual bool initFSM();

	virtual bool updateFSM();

	virtual void finalFSM();

	virtual bool addState(const std::string& a_name, SFSMState* a_fsmState, bool isStart = false);

	virtual bool addJumpCondition(const std::string& a_fromStateName, const std::string a_toStateName, SFSMCondition* a_condition);

	virtual bool parseProperties(BSLib::Utility::CProperties* a_properties);

	FSMID getFSMID()
	{
		return m_fsmID;
	}

	FSMTPID getFSMTPID()
	{
		return m_fsmTPID;
	}

	BSLib::Utility::CScriptObject* getObject()
	{
		return m_object;
	}

private:
	void _setFSMID(FSMID a_fsmID)
	{
		m_fsmID = a_fsmID; 
	}

	void _setFSMTPID(FSMTPID a_fsmTPID)
	{
		m_fsmTPID = a_fsmTPID; 
	}

private:
	FSMTPID m_fsmTPID;
	FSMID m_fsmID;
	BSLib::Utility::CScriptObject* m_object;
	SFSM m_fsm;

	friend class CFSMMgr;
};

}//FSM

}//BSLib

#endif //__BSLIB_FSM_FSMCLASS_H__

