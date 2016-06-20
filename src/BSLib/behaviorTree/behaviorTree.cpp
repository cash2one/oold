//////////////////////////////////////////////////////////////////////
//	created:	2012/10/20
//	filename:	src\BSLib\behaviorTree\behaviorTree.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/behaviorTree/behaviorTree.h>

namespace BSLib
{

namespace BehaviorTree
{

CBehaviorTree::CBehaviorTree(BTID a_id, BTTPID a_tpid, BSLib::Utility::CScriptEnvironment* a_btEnvironment)
: m_root(NULL)
, m_stopProtocol(BTSTOPPROT_ACTIONS)
, m_currentNode(NULL)
, m_id(a_id)
, m_tpid(a_tpid)
, m_btEnvironment(a_btEnvironment)
, m_scriptObject(NULL)
, m_btInfor(NULL)
{
	;
}

CBehaviorTree::~CBehaviorTree()
{
	clearTree();
}


void CBehaviorTree::setRootNode(CBTNode* a_Node)
{
	m_root = a_Node;
	m_currentNode = m_root;
}

bool CBehaviorTree::initTree()
{
	if(m_root != NULL){
		return m_root->initNode();
	}
	return false;
}

ENodeStatus CBehaviorTree::execute()
{
	ENodeStatus result = FAILURE;

	if (m_root == NULL || m_currentNode == NULL) {
		return result;
	}

	//Check what do we have to execute!
	if(m_currentNode == m_root) {
		//We are at the root, execute the root:
		m_root->executeDbg();
	} else {
		//We are inside the tree... continue from there.
		m_currentNode->notifyResult();
	}

	return m_currentNode->getNodeStatus();
}

void CBehaviorTree::resetTree()
{
	m_currentNode = m_root;
	if (m_root != NULL) {
		m_root->resetNode();
	}
}

void CBehaviorTree::clearTree()
{
	if (m_root != NULL) {
		m_root->clearNode();
		BSLIB_SAFE_DELETE(m_root);
	}
	m_root = NULL;
	m_currentNode = NULL;
	m_id = 0;
}
void CBehaviorTree::setCurrentNode(CBTNode* a_curNode) {
	
	//Set the current node.
	m_currentNode = a_curNode;
}

}// CBehaviorTree

}//BSLib