//////////////////////////////////////////////////////////////////////
//	created:	2012/10/20
//	filename:	src\BSLib\behaviorTree\btSequenceNode.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/behaviorTree/behaviorTree.h>
#include "btSequenceNode.h"

namespace BSLib
{

namespace BehaviorTree
{

CBTSequenceNode::CBTSequenceNode(CBTNode *a_parent) : CBTNode(a_parent)
{
}

void CBTSequenceNode::update(ENodeStatus a_result)
{
	if (m_tree != NULL) {
		m_tree->setCurrentNode(this);
	}
	if (a_result == EXECUTING) {
		return ;
	}

	if (m_itChildren == m_Children.end()) {
		return ;
	}
	++m_itChildren;

	//SUCCESS
	if(a_result == SUCCESS) {
		//If I can, go on with the next one...
		if(m_itChildren != m_Children.end()) {
			CBTNode* btNode = *m_itChildren;
			if (btNode == NULL) {
				return ;
			}
			btNode->executeDbg();
		} else {
			//If not, we succeed! Notify that to my parent.
			m_itChildren = m_Children.begin();
			m_nodeStatus = SUCCESS;
			if (m_parent != NULL) {
				m_parent->update(m_nodeStatus);
			}
		}
	
	} else if(a_result == FAILURE){
		//FAIL!! We have failed!
		m_itChildren = m_Children.begin();
		m_nodeStatus = FAILURE;
		if (m_parent != NULL) {
			m_parent->update(m_nodeStatus);
		}
	}
}


void CBTSequenceNode::_execute()
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

void  CBTSequenceNode::_reset()
{
	m_itChildren = m_Children.begin();
}

}// CBehaviorTree

}//BSLib