//////////////////////////////////////////////////////////////////////
//	created:	2014/08/17
//	filename:	BSLib\fsm\fsmFile.hpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/tracer.h>
#include "fsmFile.h"

namespace BSLib
{

namespace FSM
{


CFSMFile::CFSMFile()
{
	;
}

CFSMFile::~CFSMFile()
{
	clear();
}

bool CFSMFile::loadFSMFile(const std::string& a_fsmFile)
{
	BSLib::Utility::CXmlFile xmlFile;
	if (!xmlFile.loadFile(a_fsmFile)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "读取文件失败");
		return false;
	}
	BSLib::Utility::HXmlNode rootNode = xmlFile.getRootNode("fsms");
	if (rootNode == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "获取fsms节点失败");
		return false;
	}
	BSLib::Utility::HXmlAttr btAttr = xmlFile.getFirstAttr(rootNode);
	while (btAttr != NULL){
		std::string attrName;
		if (!xmlFile.getAttrName(btAttr, attrName)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "获取fsms节点属性失败");
			return false;
		}
		std::string attrValue;
		if (!xmlFile.getAttrValue(btAttr, attrValue)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "获取fsms节点属性失败");
			return false;
		}
		m_fsmsProperties.setValueString(attrName, attrValue);
		btAttr = xmlFile.getNextAttr(btAttr);
	}

	BSLib::Utility::HXmlNode childreNode = xmlFile.getChildNode(rootNode);
	while (childreNode != NULL) {
		std::string nodeName;
		if (!xmlFile.getNodeName(childreNode, nodeName)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "获取节点失败");
			xmlFile.clear();
			return false;
		}
		if (nodeName == "fsm") {
			if (!loadFSMNode(&xmlFile, childreNode)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "获取fsm节点失败");
				return false;
			}
		} else if (nodeName == "include") {
			std::string includeFSMFile;
			if (!xmlFile.getNodeValue(childreNode, includeFSMFile)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_FSM, "获取include节点失败");
				xmlFile.clear();
				return false;
			}
			if (!includeFSMFile.empty()) {
				std::string filePath = BSLib::Utility::CFileInfo::getFullPath(a_fsmFile);
				if (!filePath.empty()) {
					filePath += "/";
					filePath += includeFSMFile;
				} else {
					filePath = includeFSMFile;
				}
				BSLib::Utility::CFileInfo::standardization(filePath);
				BSLIB_LOG_INFOR(ETT_BSLIB_BTREE, "加载include节点文件[%s]", filePath.c_str());
				if (!loadFSMFile(filePath)) {
					BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "加载include节点文件失败[%s]", filePath.c_str());
					xmlFile.clear();
					return false;
				}
			}
		}
		childreNode = xmlFile.getNextNode(childreNode);
	}
	xmlFile.clear();
	return true;
}

bool CFSMFile::loadFSMNode(BSLib::Utility::CXmlFile* a_xmlFile, BSLib::Utility::HXmlNode& a_fsmNode)
{
	SFSMInfor* fsmInfor = new SFSMInfor();
	if (fsmInfor == NULL) {
		return false;
	}
	BSLib::Utility::HXmlAttr btAttr = a_xmlFile->getFirstAttr(a_fsmNode);
	while (btAttr != NULL){
		std::string attrName;
		if (!a_xmlFile->getAttrName(btAttr, attrName)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取fsm节点属性失败");
			BSLIB_SAFE_DELETE(fsmInfor);
			return false;
		}
		if (attrName == "name") {
			if (!a_xmlFile->getAttrValue(btAttr, fsmInfor->m_fsmName)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取fsm节点name属性失败");
				BSLIB_SAFE_DELETE(fsmInfor);
				return false;
			}
		}else if (attrName == "id") {
			int32 id = 0;
			if (!a_xmlFile->getAttrValue(btAttr, id)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取fsm节点id属性失败");
				BSLIB_SAFE_DELETE(fsmInfor);
				return false;
			}
			fsmInfor->m_fsmTPID = id;
		} else {
			std::string attrValue;
			if (!a_xmlFile->getAttrValue(btAttr, attrValue)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取fsm节点属性失败");
				BSLIB_SAFE_DELETE(fsmInfor);
				return false;
			}
			fsmInfor->m_properties.setValueString(attrName, attrValue);
		}
		btAttr = a_xmlFile->getNextAttr(btAttr);
	}
	if (fsmInfor->m_fsmName.empty()) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取fsm节点name属性为空");
		BSLIB_SAFE_DELETE(fsmInfor);
		return false;
	}
	if (m_fsmInforsByName.find(fsmInfor->m_fsmName) != m_fsmInforsByName.end()) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "fsm已经存在[FSMName=%s][FSMTPID=%d]", fsmInfor->m_fsmName.c_str(), fsmInfor->m_fsmTPID);
		BSLIB_SAFE_DELETE(fsmInfor);
		return false;
	}
	if (m_fsmInforsByTPID.find(fsmInfor->m_fsmTPID) != m_fsmInforsByTPID.end()) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "fsm已经存在[FSMName=%s][FSMTPID=%d]", fsmInfor->m_fsmName.c_str(), fsmInfor->m_fsmTPID);
		BSLIB_SAFE_DELETE(fsmInfor);
		return false;
	}
	BSLib::Utility::HXmlNode childreNode = a_xmlFile->getChildNode(a_fsmNode);
	while (childreNode != NULL) {
		std::string nodeName;
		if (!a_xmlFile->getNodeName(childreNode, nodeName)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取fsm子节点失败");
			BSLIB_SAFE_DELETE(fsmInfor);
			return NULL;
		}
		if (nodeName == "state") {
			SFSMStateInfor* btNodeInfor = _readFSMStateNode(a_xmlFile, childreNode);
			if (btNodeInfor == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取fsm子节点state失败");
				BSLIB_SAFE_DELETE(fsmInfor);
				return NULL;
			}
			fsmInfor->m_states.push_back(btNodeInfor);
		} else if (nodeName == "jump") {
			SFSMConditionInfor* btNodeInfor = _readFSMConditionNode(a_xmlFile, childreNode);
			if (btNodeInfor == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取fsm子节点jump失败");
				BSLIB_SAFE_DELETE(fsmInfor);
				return NULL;
			}
			fsmInfor->m_conditions.push_back(btNodeInfor);
		}
		childreNode = a_xmlFile->getNextNode(childreNode);
	}
	m_fsmInforsByName.setValue(fsmInfor->m_fsmName, fsmInfor);
	m_fsmInforsByTPID.setValue(fsmInfor->m_fsmTPID, fsmInfor);
	return true;
}

void CFSMFile::clear()
{
	BSLib::Utility::CHashMap<std::string, SFSMInfor*>::iterator it_fsmInfor = m_fsmInforsByName.begin();
	for (; it_fsmInfor != m_fsmInforsByName.end(); ++it_fsmInfor) {
		SFSMInfor* fsmInfor = it_fsmInfor->second;
		if (fsmInfor != NULL) {
			BSLIB_SAFE_DELETE(fsmInfor);
		}
	}
	m_fsmInforsByName.clear();
	m_fsmInforsByTPID.clear();
}

SFSMInfor* CFSMFile::getFsmInfor(const std::string& a_fsmName)
{
	BSLib::Utility::CHashMap<std::string, SFSMInfor*>::iterator it = m_fsmInforsByName.find(a_fsmName);
	if (it == m_fsmInforsByName.end()) {
		return NULL;
	}
	return it->second;
}

SFSMInfor* CFSMFile::getFsmInfor(FSMTPID& a_fsmTPID)
{
	BSLib::Utility::CHashMap<FSMTPID, SFSMInfor*>::iterator it = m_fsmInforsByTPID.find(a_fsmTPID);
	if (it == m_fsmInforsByTPID.end()) {
		return NULL;
	}
	return it->second;
}

SFSMStateInfor* CFSMFile::_readFSMStateNode(BSLib::Utility::CXmlFile* a_xmlFile, BSLib::Utility::HXmlNode& a_stateNode)
{
	SFSMStateInfor* stateInfor = new SFSMStateInfor();
	if (stateInfor == NULL) {
		return NULL;
	}
	stateInfor->m_isStart = false;

	BSLib::Utility::HXmlAttr btAttr = a_xmlFile->getFirstAttr(a_stateNode);
	while (btAttr != NULL){
		std::string attrName;
		if (!a_xmlFile->getAttrName(btAttr, attrName)) {
			BSLIB_SAFE_DELETE(stateInfor);
			return NULL;
		}
		if (attrName == "type") {
			if (!a_xmlFile->getAttrValue(btAttr, stateInfor->m_stateType)) {
				BSLIB_SAFE_DELETE(stateInfor);
				return false;
			}
		} else if (attrName == "name") {
			a_xmlFile->getAttrValue(btAttr, stateInfor->m_stateName);
		} else if (attrName == "start") {
			std::string isStart;
			if (!a_xmlFile->getAttrValue(btAttr, isStart)) {
				BSLIB_SAFE_DELETE(stateInfor);
				return NULL;
			}
			if (isStart == "true") {
				stateInfor->m_isStart = true;
			}
		} else {
			std::string attrValue;
			if (!a_xmlFile->getAttrValue(btAttr, attrValue)) {
				BSLIB_SAFE_DELETE(stateInfor);
				return NULL;;
			}
			stateInfor->m_properties.setValueString(attrName, attrValue);
		}
		btAttr = a_xmlFile->getNextAttr(btAttr);
	}
	if (stateInfor->m_stateType.empty()) {
		BSLIB_SAFE_DELETE(stateInfor);
		return NULL;
	}
	return stateInfor;
}

SFSMConditionInfor* CFSMFile::_readFSMConditionNode(BSLib::Utility::CXmlFile* a_xmlFile, BSLib::Utility::HXmlNode& a_conditionNode)
{
	SFSMConditionInfor* conditionInfor = new SFSMConditionInfor();
	if (conditionInfor == NULL) {
		return NULL;
	}

	BSLib::Utility::HXmlAttr btAttr = a_xmlFile->getFirstAttr(a_conditionNode);
	while (btAttr != NULL){
		std::string attrName;
		if (!a_xmlFile->getAttrName(btAttr, attrName)) {
			BSLIB_SAFE_DELETE(conditionInfor);
			return NULL;
		}
		if (attrName == "type") {
			if (!a_xmlFile->getAttrValue(btAttr, conditionInfor->m_conditionType)) {
				BSLIB_SAFE_DELETE(conditionInfor);
				return false;
			}
		} else if (attrName == "from") {
			if (!a_xmlFile->getAttrValue(btAttr, conditionInfor->m_fromStateName)) {
				BSLIB_SAFE_DELETE(conditionInfor);
				return false;
			}
		} else if (attrName == "to") {
			if (!a_xmlFile->getAttrValue(btAttr, conditionInfor->m_toStateName)) {
				BSLIB_SAFE_DELETE(conditionInfor);
				return false;
			}
		} else {
			std::string attrValue;
			if (!a_xmlFile->getAttrValue(btAttr, attrValue)) {
				BSLIB_SAFE_DELETE(conditionInfor);
				return NULL;;
			}
			conditionInfor->m_properties.setValueString(attrName, attrValue);
		}
		btAttr = a_xmlFile->getNextAttr(btAttr);
	}
	if (conditionInfor->m_conditionType.empty() || conditionInfor->m_fromStateName.empty() || conditionInfor->m_toStateName.empty()) {
		BSLIB_SAFE_DELETE(conditionInfor);
		return NULL;
	}
	return conditionInfor;
}

}//FSM

}//BSLib
