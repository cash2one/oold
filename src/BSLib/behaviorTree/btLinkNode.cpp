#include <BSLib/utility/string.h>
#include "btLinkNode.h"

namespace BSLib
{

namespace BehaviorTree
{

CBTLinkNode::CBTLinkNode(CBTNode *a_parent)
: CBTNode(a_parent)
, m_btMgr(NULL)
{
	;
}

void CBTLinkNode::update(ENodeStatus a_result)
{
	if (m_tree != NULL) {
		m_tree->setCurrentNode(this);
	}
	
	m_nodeStatus = a_result;
	
	if (m_parent == NULL) {
		m_parent->update(m_nodeStatus);
	}
}

bool CBTLinkNode::_init()
{
	if (m_nodeInfor == NULL) {
		return false;
	}
	if (m_btMgr == NULL) {
		return false;
	}
	if (m_tree == NULL) {
		return false;
	}
	BSLib::Utility::CStringA childBtName;
	if (m_nodeInfor->m_btNodeProperties.getValue("ChildBTName", childBtName)) {
		if (!childBtName.empty()){
			return false;
		}
		return m_btMgr->_createChildBT(childBtName, m_tree, this);
	}
	return false;
}

void CBTLinkNode::_execute()
{
	m_itChildren = m_Children.begin();
	if (m_itChildren == m_Children.end()) {
		return ;
	}
	CBTNode* btNode = *m_itChildren;
	if (btNode == NULL) {
		return ;
	}
	btNode->executeDbg();
}

void CBTLinkNode::_reset()
{
	m_itChildren = m_Children.begin();
}

}// BehaviorTree

}//BSLib


