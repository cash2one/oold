#include <BSLib/utility/string.h>
#include <BSLib/utility/file/xmlFile.h>
#include <BSLib/utility/file/fileInfo.h>
#include <BSLib/utility/tracer.h>
#include <BSLib/behaviorTree/behaviorTreeMgr.h>
#include "btParallelNode.h"
#include "btSelectorNode.h"
#include "btSequenceNode.h"
#include "btWeightParallelNode.h"
#include "btWeightSelectorNode.h"
#include "btWeightSequenceNode.h"
#include "btLinkNode.h"
#include "btScriptAction.h"
#include "btScriptCondition.h"

#include "filters/counterFilter.h"
#include "filters/loopFilter.h"
#include "filters/nonFilter.h"
#include "filters/timerFilter.h"
#include "filters/untilFailsFilter.h"
#include "filters/untilFailsLimitedFilter.h"
#include "filters/untilSuccessFilter.h"
#include "filters/untilSuccessLimitedFilter.h"

namespace BSLib
{

namespace BehaviorTree
{

struct SBTNodeInforInFile
{
	SBTNodeInfor m_btNodeInfor;
	std::vector<SBTNodeInforInFile*> m_subNodes;

	SBTNodeInforInFile() {}
	~SBTNodeInforInFile()
	{
		for (BSLib::uint32 i=0; i<m_subNodes.size(); ++i){
			SBTNodeInforInFile* nodeInfor = m_subNodes[i];
			if (nodeInfor != NULL) {
				BSLIB_SAFE_DELETE(nodeInfor);
			}
		}
		m_subNodes.clear();
	}
};

struct SBTInforInFile
{
	SBTInfor m_btInfor;
	std::vector<SBTNodeInforInFile*> m_subNodes;

	SBTInforInFile() {}
	~SBTInforInFile()
	{
		for (BSLib::uint32 i=0; i<m_subNodes.size(); ++i){
			SBTNodeInforInFile* nodeInfor = m_subNodes[i];
			if (nodeInfor != NULL) {
				BSLIB_SAFE_DELETE(nodeInfor);
			}
		}
		m_subNodes.clear();
	}
};

struct SBTCreatorNodeInfor
{
	BSLib::Utility::CFunction<CBTNode*, const std::string&, CBTNode*, void*>* m_fun;
	void* m_tempData;

	SBTCreatorNodeInfor() : m_fun(NULL), m_tempData(NULL) {}
	~SBTCreatorNodeInfor()
	{
		if (m_fun != NULL) {
			BSLIB_SAFE_DELETE(m_fun);
		}
	}
};

//////////////////////////////////////////////////////////////////////////
SBTNodeInforInFile* readBehaviorNode(BSLib::Utility::CXmlFile* xmlFile, BSLib::Utility::HXmlNode btNode)
{
	SBTNodeInforInFile* btNodeInforInFile = new SBTNodeInforInFile();
	if (btNodeInforInFile == NULL) {
		return NULL;
	}
	BSLib::Utility::HXmlAttr btAttr = xmlFile->getFirstAttr(btNode);
	while (btAttr != NULL){
		std::string attrName;
		if (!xmlFile->getAttrName(btAttr, attrName)) {
			BSLIB_SAFE_DELETE(btNodeInforInFile);
			return NULL;
		}
		if (attrName == "id") {
			int nodeID = 0;
			if (!xmlFile->getAttrValue(btAttr, nodeID)) {
				BSLIB_SAFE_DELETE(btNodeInforInFile);
				return NULL;
			}
			btNodeInforInFile->m_btNodeInfor.m_btNodeID = nodeID;
		} else if (attrName == "type") {
			if (!xmlFile->getAttrValue(btAttr, btNodeInforInFile->m_btNodeInfor.m_btNodeName)) {
				BSLIB_SAFE_DELETE(btNodeInforInFile);
				return NULL;
			}
		} else {
			std::string attrValue;
			if (!xmlFile->getAttrValue(btAttr, attrValue)) {
				BSLIB_SAFE_DELETE(btNodeInforInFile);
				return NULL;;
			}
			btNodeInforInFile->m_btNodeInfor.m_btNodeProperties.setValue(attrName, attrValue);
		}
		btAttr = xmlFile->getNextAttr(btAttr);
	}
	if (btNodeInforInFile->m_btNodeInfor.m_btNodeID == 0 || btNodeInforInFile->m_btNodeInfor.m_btNodeName.empty()) {
		BSLIB_SAFE_DELETE(btNodeInforInFile);
		return NULL;
	}
	BSLib::Utility::HXmlNode childreNode = xmlFile->getChildNode(btNode);
	while (childreNode != NULL) {
		std::string nodeName;
		if (!xmlFile->getNodeName(childreNode, nodeName)) {
			BSLIB_SAFE_DELETE(btNodeInforInFile);
			return NULL;
		}
		if (nodeName == "node") {
			SBTNodeInforInFile* subNode = readBehaviorNode(xmlFile, childreNode);
			if (subNode == NULL) {
				BSLIB_SAFE_DELETE(btNodeInforInFile);
				return NULL;
			}
			btNodeInforInFile->m_subNodes.push_back(subNode);
		}
		childreNode = xmlFile->getNextNode(childreNode);
	}
	return btNodeInforInFile;
}

SBTInforInFile* readBehaviorTree(BSLib::Utility::CXmlFile* xmlFile, BSLib::Utility::HXmlNode btNode)
{
	SBTInforInFile* btInfor = new SBTInforInFile();
	if (btInfor == NULL) {
		return NULL;
	}
	BSLib::Utility::HXmlAttr btAttr = xmlFile->getFirstAttr(btNode);
	while (btAttr != NULL){
		std::string attrName;
		if (!xmlFile->getAttrName(btAttr, attrName)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取behavior节点属性失败");
			BSLIB_SAFE_DELETE(btInfor);
			return NULL;
		}
		if (attrName == "name") {
			if (!xmlFile->getAttrValue(btAttr, btInfor->m_btInfor.m_btName)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取behavior节点name属性失败");
				BSLIB_SAFE_DELETE(btInfor);
				return NULL;
			}
		} else if (attrName == "id") {
			BSLib::int32 id = 0;
			if (!xmlFile->getAttrValue(btAttr, id)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取behavior节点id属性失败");
				BSLIB_SAFE_DELETE(btInfor);
				return NULL;
			}
			btInfor->m_btInfor.m_btTPID = id;
		} else {
			std::string attrValue;
			if (!xmlFile->getAttrValue(btAttr, attrValue)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取behavior节点属性失败");
				BSLIB_SAFE_DELETE(btInfor);
				return NULL;
			}
			btInfor->m_btInfor.m_btProperties.setValue(attrName, attrValue);
		}
		btAttr = xmlFile->getNextAttr(btAttr);
	}
	if (btInfor->m_btInfor.m_btName.empty()) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取behavior节点空名字");
		BSLIB_SAFE_DELETE(btInfor);
		return NULL;
	}
	BSLib::Utility::HXmlNode childreNode = xmlFile->getChildNode(btNode);
	while (childreNode != NULL) {
		std::string nodeName;
		if (!xmlFile->getNodeName(childreNode, nodeName)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取behavior子节点失败");
			BSLIB_SAFE_DELETE(btInfor);
			return NULL;
		}
		if (nodeName == "node") {
			SBTNodeInforInFile* btNodeInfor = readBehaviorNode(xmlFile, childreNode);
			if (btNodeInfor == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取behavior子节点失败");
				BSLIB_SAFE_DELETE(btInfor);
				return NULL;
			}
			btInfor->m_subNodes.push_back(btNodeInfor);
		}
		childreNode = xmlFile->getNextNode(childreNode);
	}
	return btInfor;
}

//////////////////////////////////////////////////////////////////////////

BSLib::uint32 CBehaviorTreeMgr::m_currentBTID = 0;

CBehaviorTreeMgr::CBehaviorTreeMgr()
{
	;
}

CBehaviorTreeMgr::~CBehaviorTreeMgr()
{
	;
}

void CBehaviorTreeMgr::init()
{
	registerLeafNodeFun("Selector", &createLeafNode<CBTSelectorNode>);
	registerLeafNodeFun("Sequence", &createLeafNode<CBTSequenceNode>);
	registerLeafNodeFun("Parallel", &createLeafNode<CBTParallelNode>);
	registerLeafNodeFun("RWSelector", &createLeafNode<CBTWeightSelectorNode>);
	registerLeafNodeFun("RWSequence", &createLeafNode<CBTWeightSequenceNode>);
	registerLeafNodeFun("RWParallel", &createLeafNode<CBTWeightParallelNode>);
	registerLeafNodeFun("Counter", &createLeafNode<CCounterFilter>);
	registerLeafNodeFun("Loop", &createLeafNode<CLoopFilter>);
	registerLeafNodeFun("Non", &createLeafNode<CNonFilter>);
	registerLeafNodeFun("Timer", &CBehaviorTreeMgr::_createTimerNode, this, NULL);
	registerLeafNodeFun("Failure", &createLeafNode<CUntilFailsFilter>);
	registerLeafNodeFun("LmtFailure", &createLeafNode<CUntilFailsLimitedFilter>);
	registerLeafNodeFun("Success", &createLeafNode<CUntilSuccessFilter>);
	registerLeafNodeFun("LmtSuccess", &createLeafNode<CUntilSuccessLimitedFilter>);
	registerLeafNodeFun("Link", &CBehaviorTreeMgr::_createLinkNode, this, NULL);
	
	registerLeafNodeFun("ScriptCondition", &createLeafNode<CBTScriptCondition>);
	registerLeafNodeFun("ScripAction", &createLeafNode<CBTScriptAction>);
}

void CBehaviorTreeMgr::final()
{
	BSLib::Utility::CHashMap<BTID, CBehaviorTree*>::iterator it_bt = m_behaviorTrees.begin();
	for (; it_bt != m_behaviorTrees.end(); ++it_bt){
		CBehaviorTree* bt = it_bt->second;
		if (bt != NULL) {
			bt->clearTree();
			BSLIB_SAFE_DELETE(bt);
		}
	}
	m_behaviorTrees.clear();

	BSLib::Utility::CHashMap<std::string, SBTInforInFile*>::iterator it_btInfor = m_behaviorTreeInforsByName.begin();
	for (; it_btInfor != m_behaviorTreeInforsByName.end(); ++it_btInfor){
		SBTInforInFile* btInfor = it_btInfor->second;
		if (btInfor != NULL) {
			BSLIB_SAFE_DELETE(btInfor);
		}
	}
	m_behaviorTreeInforsByName.clear();
	m_behaviorTreeInforsByTPID.clear();

	BSLib::Utility::CHashMap<std::string, SBTCreatorNodeInfor*> ::iterator it_btNodeInfor = m_creatorLeafNodes.begin();
	for (; it_btNodeInfor != m_creatorLeafNodes.end(); ++it_btNodeInfor){
		SBTCreatorNodeInfor* btNodeInfor = it_btNodeInfor->second;
		if (btNodeInfor != NULL) {
			BSLIB_SAFE_DELETE(btNodeInfor);
		}
	}
	m_creatorLeafNodes.clear();
}

bool CBehaviorTreeMgr::loadBTFromFile(const std::string& a_behaviorTreeFile)
{
	BSLib::Utility::CXmlFile xmlFile;

	if (!xmlFile.loadFile(a_behaviorTreeFile)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "读取文件失败");
		return false;
	}
	BSLib::Utility::HXmlNode root = xmlFile.getRootNode("behaviors");
	if (root == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取behaviors节点失败");
		return false;
	}
	
	BSLib::Utility::HXmlNode childreNode = xmlFile.getChildNode(root);
	while (childreNode != NULL) {
		std::string nodeName;
		if (!xmlFile.getNodeName(childreNode, nodeName)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取节点失败");
			xmlFile.clear();
			return false;
		}
		if (nodeName == "behavior") {
			SBTInforInFile* btInfor = readBehaviorTree(&xmlFile, childreNode);
			if (btInfor == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取behavior节点失败");
				xmlFile.clear();
				return false;
			}
			if (m_behaviorTreeInforsByName.find(btInfor->m_btInfor.m_btName) != m_behaviorTreeInforsByName.end()) {
				BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取behavior已经存在失败[%s][%d]", btInfor->m_btInfor.m_btName.c_str(), btInfor->m_btInfor.m_btTPID);
				BSLIB_SAFE_DELETE(btInfor);
				xmlFile.clear();
				return false;
			}
			if (m_behaviorTreeInforsByTPID.find(btInfor->m_btInfor.m_btTPID) != m_behaviorTreeInforsByTPID.end()) {
				BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取behavior已经存在失败[%s][%d]", btInfor->m_btInfor.m_btName.c_str(), btInfor->m_btInfor.m_btTPID);
				BSLIB_SAFE_DELETE(btInfor);
				xmlFile.clear();
				return false;
			}
			m_behaviorTreeInforsByName.setValue(btInfor->m_btInfor.m_btName, btInfor);
			m_behaviorTreeInforsByTPID.setValue(btInfor->m_btInfor.m_btTPID, btInfor);
		} else if (nodeName == "include") {
			std::string includeBTFile;
			if (!xmlFile.getNodeValue(childreNode, includeBTFile)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取include节点失败");
				xmlFile.clear();
				return false;
			}
			if (!includeBTFile.empty()) {
				std::string filePath = BSLib::Utility::CFileInfo::getFullPath(a_behaviorTreeFile);
				if (!filePath.empty()) {
					filePath += "/";
					filePath += includeBTFile;
				} else {
					filePath = includeBTFile;
				}
				BSLib::Utility::CFileInfo::standardization(filePath);
				BSLIB_LOG_INFO(ETT_BSLIB_BTREE, "加载include节点文件[%s]", filePath.c_str());
				if (!loadBTFromFile(filePath)) {
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

CBehaviorTree* CBehaviorTreeMgr::createBT(const std::string& a_behaviorTreeName, BSLib::Utility::CScriptEnvironment* a_btEnvironment, SBTStopProtocol a_btStopProtocol)
{
	SBTInforInFile* btInfor = NULL;
	m_behaviorTreeInforsByName.getValue(a_behaviorTreeName, btInfor);
	if (btInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取BT失败[name=%s]", a_behaviorTreeName.c_str());
		return NULL;
	}
	return _createBT(btInfor, a_btEnvironment, a_btStopProtocol);
}

CBehaviorTree* CBehaviorTreeMgr::createBT(BTTPID a_btTPID, BSLib::Utility::CScriptEnvironment* a_btEnvironment, SBTStopProtocol a_btStopProtocol)
{
	SBTInforInFile* btInfor = NULL;
	m_behaviorTreeInforsByTPID.getValue(a_btTPID, btInfor);
	if (btInfor == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取BT失败[id=%d]", a_btTPID);
		return NULL;
	}
	return _createBT(btInfor, a_btEnvironment, a_btStopProtocol);
}

void CBehaviorTreeMgr::removeBT(BTID a_btID)
{
	BSLib::Utility::CHashMap<BTID, CBehaviorTree*>::iterator it = m_behaviorTrees.find(a_btID);
	if (it == m_behaviorTrees.end()) {
		return ;
	}
	
	CBehaviorTree* tree = it->second;
	if (tree != NULL) {
		BSLIB_SAFE_DELETE(tree);
	}
	m_behaviorTrees.remove(a_btID);
}

void CBehaviorTreeMgr::removeBT(CBehaviorTree** a_tree)
{
	CBehaviorTree* treeRemove = *a_tree;
	if (treeRemove == NULL) {
		return ;
	}
	CBehaviorTree* tree = NULL;
	m_behaviorTrees.getValue(treeRemove->getID(), tree);
	if (tree != treeRemove) {
		return ;
	}
	m_behaviorTrees.remove(treeRemove->getID());
	BSLIB_SAFE_DELETE(*a_tree);
}

CBehaviorTree* CBehaviorTreeMgr::getBT(BTID a_btID)
{
	BSLib::Utility::CHashMap<BTID, CBehaviorTree*>::iterator it = m_behaviorTrees.find(a_btID);
	if (it == m_behaviorTrees.end()) {
		return NULL;
	}
	return it->second;
}

void CBehaviorTreeMgr::registerLeafNodeFun(const std::string& a_name, CreateLeafNodeFun fun, void* a_temp)
{
	BSLib::Utility::CFunction<CBTNode*, const std::string&, CBTNode*, void*> funTemp(fun);
	
	registerLeafNodeFun(a_name, funTemp, a_temp);
}

void CBehaviorTreeMgr::registerLeafNodeFun(const std::string& a_name, BSLib::Utility::CFunction<CBTNode*, const std::string&, CBTNode*, void*>& fun, void* a_temp)
{
	BSLib::Utility::CStringA strName = a_name;
	strName.toLower();

	BSLib::Utility::CHashMap<std::string, SBTCreatorNodeInfor*>::iterator it = m_creatorLeafNodes.find(strName);
	if (it != m_creatorLeafNodes.end()) {
		SBTCreatorNodeInfor* nodeInfor = it->second;
		if (nodeInfor != NULL) {
			if (nodeInfor->m_fun != NULL) {
				BSLIB_SAFE_DELETE(it->second->m_fun);
			}
			nodeInfor->m_fun = fun.clone();
			nodeInfor->m_tempData = a_temp;
			return ;
		}
	}
	SBTCreatorNodeInfor* creatorInfor = new SBTCreatorNodeInfor();
	creatorInfor->m_fun = fun.clone();
	creatorInfor->m_tempData = a_temp;
	m_creatorLeafNodes.setValue(strName, creatorInfor);
}

CBehaviorTree* CBehaviorTreeMgr::_createBT(SBTInforInFile* a_btInfor, BSLib::Utility::CScriptEnvironment* a_btEnvironment, SBTStopProtocol a_btStopProtocol)
{
	BTID btID = _allocateBTID();
	if (btID == INVALID_BT) {
		return NULL;
	}
	CBehaviorTree* tree = new CBehaviorTree(btID, a_btInfor->m_btInfor.m_btTPID, a_btEnvironment);
	if (tree == NULL) {
		return NULL;
	}

	tree->setBTInfor(&a_btInfor->m_btInfor);
	tree->setStopProtocol(a_btStopProtocol);

	CBTNode* rootNode = _assembleBTRootNode(tree, a_btInfor);
	if (rootNode == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "创建BT失败[id=%d]", a_btInfor->m_btInfor.m_btTPID);
		BSLIB_SAFE_DELETE(tree);
		return NULL;
	}
	tree->setRootNode(rootNode);
	if (!tree->initTree()) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "初始化BT失败[id=%d]", a_btInfor->m_btInfor.m_btTPID);
		BSLIB_SAFE_DELETE(tree);
		return NULL;
	}

	m_behaviorTrees.setValue(btID, tree);
	return tree;
}

bool CBehaviorTreeMgr::_createChildBT(const std::string& a_childBTName, CBehaviorTree* a_tree, CBTNode* a_parentNode)
{
	SBTInforInFile* btInfor = NULL;
	m_behaviorTreeInforsByName.getValue(a_childBTName, btInfor);
	if (btInfor == NULL) {
		return false;
	}
	CBTNode* btNode = _assembleBTLinkNode(a_tree, a_parentNode, btInfor->m_subNodes);
	if (btNode == NULL) {
		return false;
	}
	if (!btNode->initNode()) {
		return false;
	}
	a_parentNode->pushBack(btNode);
	return true;
}

CBTNode* CBehaviorTreeMgr::_createBTNode(const std::string& a_name, CBTNode* a_parent)
{
	BSLib::Utility::CStringA strName = a_name;
	strName.toLower();

	BSLib::Utility::CHashMap<std::string, SBTCreatorNodeInfor*>::iterator it = m_creatorLeafNodes.find(strName);
	if (it == m_creatorLeafNodes.end()) {
		return NULL;
	}
	SBTCreatorNodeInfor* creatorInfor = it->second;
	if (creatorInfor == NULL) {
		return NULL;
	}
	BSLib::Utility::CFunction<CBTNode*, const std::string&, CBTNode*, void*>* fun = creatorInfor->m_fun;
	if (fun == NULL) {
		return NULL;
	}
	CBTNode* leafNode = (*fun)(a_name, a_parent, creatorInfor->m_tempData);
	if (leafNode == NULL) {
		return NULL;
	}
	return leafNode;
}

bool CBehaviorTreeMgr::_assembleBTNode(CBehaviorTree* a_tree, CBTNode* a_btNode, std::vector<SBTNodeInforInFile*>& a_subNodes)
{
	for (BSLib::uint32 i=0; i<a_subNodes.size(); ++i){
		SBTNodeInforInFile* btNodeInfor = a_subNodes[i];
		if (btNodeInfor == NULL) {
			return false;
		}
		CBTNode* btSubNode = _createBTNode(btNodeInfor->m_btNodeInfor.m_btNodeName, a_btNode);
		if (btSubNode == NULL) {
			BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "创建BT节点失败[name=%s]", btNodeInfor->m_btNodeInfor.m_btNodeName.c_str());
			return false;
		}

		btSubNode->setBehaviorTree(a_tree);
		btSubNode->setNodeInfor(&btNodeInfor->m_btNodeInfor);

		if (!_assembleBTNode(a_tree, btSubNode, btNodeInfor->m_subNodes)) {
			BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "创建BT子节点失败[name=%s]", btNodeInfor->m_btNodeInfor.m_btNodeName.c_str());
			BSLIB_SAFE_DELETE(btSubNode);
			return false;
		}
		a_btNode->pushBack(btSubNode);
	}
	return true;
}

CBTNode* CBehaviorTreeMgr::_assembleBTRootNode(CBehaviorTree* a_tree, SBTInforInFile* a_btInfor)
{
	if (a_btInfor->m_subNodes.size() <= 0) {
		return NULL;
	}
	SBTNodeInforInFile* btRootNodeInfor = a_btInfor->m_subNodes[0];
	if (btRootNodeInfor == NULL) {
		return NULL;
	}
	CBTNode* btRootNode = _createBTNode(btRootNodeInfor->m_btNodeInfor.m_btNodeName, NULL);
	if (btRootNode == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "创建BT节点失败[name=%s]", btRootNodeInfor->m_btNodeInfor.m_btNodeName.c_str());
		return NULL;
	}
	btRootNode->setBehaviorTree(a_tree);
	btRootNode->setNodeInfor(&btRootNodeInfor->m_btNodeInfor);

	if (!_assembleBTNode(a_tree, btRootNode, btRootNodeInfor->m_subNodes)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "创建BT子节点失败[name=%s]", btRootNodeInfor->m_btNodeInfor.m_btNodeName.c_str());
		BSLIB_SAFE_DELETE(btRootNode);
		return NULL;
	}
	return btRootNode;
}

CBTNode* CBehaviorTreeMgr::_assembleBTLinkNode(CBehaviorTree* a_tree, CBTNode* a_btNode, std::vector<SBTNodeInforInFile*>& a_subNodes)
{
	if (a_subNodes.size() <= 0) {
		return NULL;
	}
	SBTNodeInforInFile* btRootNodeInfor = a_subNodes[0];
	if (btRootNodeInfor == NULL) {
		return NULL;
	}
	CBTNode* btSubNode = _createBTNode(btRootNodeInfor->m_btNodeInfor.m_btNodeName, a_btNode);
	if (btSubNode == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "创建BT节点失败[name=%s]", btRootNodeInfor->m_btNodeInfor.m_btNodeName.c_str());
		return NULL;
	}
	btSubNode->setBehaviorTree(a_tree);
	btSubNode->setNodeInfor(&btRootNodeInfor->m_btNodeInfor);

	if (!_assembleBTNode(a_tree, btSubNode, btRootNodeInfor->m_subNodes)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "创建BT子节点失败[name=%s]", btRootNodeInfor->m_btNodeInfor.m_btNodeName.c_str());
		BSLIB_SAFE_DELETE(btSubNode);
		return NULL;
	}
	return btSubNode;
}

CBTNode* CBehaviorTreeMgr::_createLinkNode(const std::string& a_name, CBTNode* a_parent, void* a_temp)
{
	CBTLinkNode* linkNode = new CBTLinkNode(a_parent);
	if (linkNode == NULL) {
		return NULL;
	}
	linkNode->setBTMgr(this);
	return linkNode;
}

CBTNode* CBehaviorTreeMgr::_createTimerNode(const std::string& a_name, CBTNode* a_parent, void* a_temp)
{
	CTimerFilter* timerNode = new CTimerFilter(a_parent);
	if (timerNode == NULL) {
		return NULL;
	}
	timerNode->setRealTime(&m_realTime);
	return timerNode;
}

BTID CBehaviorTreeMgr::_allocateBTID()
{
	for (BSLib::uint32 i=0; i<=BSLIB_UINT32_MAX; ++i){
		m_currentBTID = (m_currentBTID + 1) % BSLIB_UINT32_MAX;
		if (m_currentBTID == 0) {
			continue;
		}
		if (m_behaviorTrees.find(m_currentBTID) == m_behaviorTrees.end()) {
			return m_currentBTID;
		}
	}
	return INVALID_BT;
}

}// CBehaviorTree

}//BSLib


