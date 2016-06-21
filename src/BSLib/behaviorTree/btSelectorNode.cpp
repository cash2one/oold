#include <BSLib/behaviorTree/behaviorTree.h>
#include "btSelectorNode.h"

namespace BSLib
{

namespace BehaviorTree
{

CBTSelectorNode::CBTSelectorNode(CBTNode *a_parent) : CBTNode(a_parent)
{
}

void CBTSelectorNode::update(ENodeStatus a_result)
{
	if (m_tree == NULL) {
		return ;
	}
	m_tree->setCurrentNode(this);
	if (a_result == NULL) {
		return ;
	}
	
	if (m_itChildren == m_Children.end()) {
		return ;
	}
	++m_itChildren;

	//FAILURE!
	if (a_result == FAILURE) {
		//Try the next one, if I can.
		if (m_itChildren != m_Children.end()) {
			CBTNode* btNode = *m_itChildren;
			if (btNode == NULL) {
				return ;
			}
			btNode->executeDbg();
		} else {
			//If not, Selector returns a FAILURE
			m_itChildren = m_Children.begin();
			m_nodeStatus = FAILURE;
			if (m_parent!= NULL) {
				m_parent->update(m_nodeStatus);
			}
		}
	
	} else if (a_result == SUCCESS) {
		//With SUCCESS, everything is done, just notify SUCCESS to the parent.
		m_itChildren = m_Children.begin();
		m_nodeStatus = SUCCESS;
		if (m_parent!= NULL) {
			m_parent->update(m_nodeStatus);
		}
	}
}

void CBTSelectorNode::_execute()
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

void  CBTSelectorNode::_reset()
{
	m_itChildren = m_Children.begin();
}

}// BehaviorTree

}//BSLib
