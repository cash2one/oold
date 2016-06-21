#include <BSLib/behaviorTree/behaviorTree.h>
#include <BSLib/behaviorTree/btDecoratorNode.h>

namespace BSLib
{

namespace BehaviorTree
{

CBTDecoratorNode::CBTDecoratorNode(CBTNode *a_parent) 
: CBTNode(a_parent)
{
	;
}

void CBTDecoratorNode::update(ENodeStatus a_result)
{
	if (m_tree != NULL) {
		m_tree->setCurrentNode(this);
	}

	EDecoratorStatus decoratorStatus = _decorator(a_result);

	if (decoratorStatus == EDCTS_TOPARENT) {
		m_nodeStatus = a_result;
		if (m_parent != NULL) {
			m_parent->update(m_nodeStatus);
		}
	} else if (decoratorStatus == EDCTS_EXECUTE) {
		if (m_itChildren == m_Children.end()) {
			return ;
		}
		CBTNode* btNode = *m_itChildren;
		if (btNode == NULL) {
			return ;
		}
		btNode->executeDbg();
	}
}

void CBTDecoratorNode::_reset()
{
	m_itChildren = m_Children.begin();
}

void CBTDecoratorNode::_execute()
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

}// BehaviorTree

}//BSLib

