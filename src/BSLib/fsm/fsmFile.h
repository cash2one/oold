//////////////////////////////////////////////////////////////////////
//	created:	2014/08/18
//	filename: 	src\BSLib\fsm\fsmFile.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_FSM_FSMFILE_H__
#define __BSLIB_FSM_FSMFILE_H__

#include <BSLib/utility/file/fileInfo.h>
#include <BSLib/utility/string.h>
#include <BSLib/utility/file/xmlFile.h>
#include <BSLib/utility/command.h>
#include <BSLib/utility/hashMap.h>
#include <BSLib/fsm/fsmClass.h>

namespace BSLib
{

namespace FSM
{

//////////////////////////////////////////////////////////////////////////

struct SFSMConditionInfor
{
	std::string m_fromStateName;
	std::string m_toStateName;
	std::string m_conditionType;
	BSLib::Utility::CProperties m_properties;
};

struct SFSMStateInfor
{

	std::string m_stateType;
	std::string m_stateName;
	bool m_isStart;
	BSLib::Utility::CProperties m_properties;
};

struct SFSMInfor
{
	FSMTPID m_fsmTPID;
	std::string m_fsmName;
	std::vector<SFSMStateInfor*> m_states;
	std::vector<SFSMConditionInfor*> m_conditions; 
	BSLib::Utility::CProperties m_properties;

	~SFSMInfor()
	{
		for (BSLib::uint32 i_state=0; i_state<m_states.size(); ++i_state) {
			SFSMStateInfor* stateInfor = m_states[i_state];
			if (stateInfor == NULL) {
				continue;
			}
			BSLIB_SAFE_DELETE(stateInfor);
		}
		m_states.clear();

		for (BSLib::uint32 i_condition=0; i_condition<m_conditions.size(); ++i_condition) {
			SFSMConditionInfor* conditionInfor = m_conditions[i_condition];
			if (conditionInfor == NULL) {
				continue;
			}
			BSLIB_SAFE_DELETE(conditionInfor);
		}
		m_conditions.clear();
	}
};

//////////////////////////////////////////////////////////////////////////
class CFSMFile
{
public:
	CFSMFile();

	~CFSMFile();

	bool loadFSMFile(const std::string& a_fsmFile);
	bool loadFSMNode(BSLib::Utility::CXmlFile* a_xmlFile, BSLib::Utility::HXmlNode& a_fsmNode);

	void clear();

	SFSMInfor* getFsmInfor(const std::string& a_fsmName);
	SFSMInfor* getFsmInfor(FSMTPID& a_fsmTPID);

	BSLib::Utility::CProperties* getFsmsProperties() { return &m_fsmsProperties; }

private:
	SFSMStateInfor* _readFSMStateNode(BSLib::Utility::CXmlFile* a_xmlFile, BSLib::Utility::HXmlNode& a_stateNode);
	SFSMConditionInfor* _readFSMConditionNode(BSLib::Utility::CXmlFile* a_xmlFile, BSLib::Utility::HXmlNode& a_conditionNode);

private:
	BSLib::Utility::CHashMap<std::string, SFSMInfor*> m_fsmInforsByName;
	BSLib::Utility::CHashMap<FSMTPID, SFSMInfor*> m_fsmInforsByTPID;

	BSLib::Utility::CProperties m_fsmsProperties;
};

}//FSM

}//BSLib

#endif //__BSLIB_FSM_FSMFILE_H__