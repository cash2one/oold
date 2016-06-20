//////////////////////////////////////////////////////////////////////
//	created:	2012/10/21
//	filename: 	BSLib\behaviorTree\btParallelNode.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/string.h>
#include <BSLib/behaviorTree/behaviorTree.h>
#include "btParallelNode.h"

namespace BSLib
{

namespace BehaviorTree
{

CBTParallelNode::CBTParallelNode(CBTNode* a_parent) 
: CBTNode(a_parent)
, m_trueMax(1)
, m_trueCount(0)
{

}

bool CBTParallelNode::_init()
{
	if (m_nodeInfor == NULL) {
		return false;
	}
	BSLib::Utility::CStringA strTrueMax;
	if (m_nodeInfor->m_btNodeProperties.getValue("SuccessCount", strTrueMax)) {
		strTrueMax >> m_trueMax;
	}
	return true;
}

void CBTParallelNode::update(ENodeStatus a_result)
{
	if (m_tree == NULL) {
		return ;
	}
	m_tree->setCurrentNode(this);
	
	if (a_result == EXECUTING) {
		return ;
	}
	if (m_itChildren == m_Children.end()) {
		return ;
	}
	++m_itChildren;

	if (a_result == SUCCESS) {
		++m_trueCount;
	}
	if (m_itChildren != m_Children.end()) {
		CBTNode* btNode = *m_itChildren;
		if (btNode == NULL) {
			return ;
		}
		btNode->executeDbg();
		return ;
	}

	if (m_trueCount >= m_trueMax) {
		m_nodeStatus = SUCCESS;
	} else {
		m_nodeStatus = FAILURE;
	}

	m_trueCount = 0;
	m_itChildren = m_Children.begin();

	if (m_parent != NULL) {
		m_parent->update(m_nodeStatus);
	}
}

void CBTParallelNode::_execute()
{
	m_trueCount = 0;
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

void  CBTParallelNode::_reset()
{
	m_trueCount = 0;
	m_itChildren = m_Children.begin();
}

}// BehaviorTree

}//BSLib