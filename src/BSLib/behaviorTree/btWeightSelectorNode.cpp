#include <BSLib/utility/string.h>
#include <BSLib/behaviorTree/behaviorTree.h>
#include "btWeightSelectorNode.h"

namespace BSLib
{

namespace BehaviorTree
{

CBTWeightSelectorNode::CBTWeightSelectorNode(CBTNode *a_parent) : CBTNode(a_parent)
{
}

void CBTWeightSelectorNode::update(ENodeStatus a_result)
{
	if (m_tree == NULL) {
		return ;
	}
	m_tree->setCurrentNode(this);
	if (a_result == NULL) {
		return ;
	}
	
	if (m_itChildren == m_btweight.end()) {
		return ;
	}
	++m_itChildren;

	//FAILURE!
	if (a_result == FAILURE) {
		//Try the next one, if I can.
		if (m_itChildren != m_btweight.end()) {
			CBTNode* btNode = *m_itChildren;
			if (btNode == NULL) {
				return ;
			}
			btNode->executeDbg();
		} else {
			//If not, Selector returns a FAILURE
			m_btweight.recalculate();
			m_itChildren = m_btweight.begin();
			m_nodeStatus = FAILURE;
			if (m_parent!= NULL) {
				m_parent->update(m_nodeStatus);
			}
		}
	
	} else if (a_result == SUCCESS) {
		//With SUCCESS, everything is done, just notify SUCCESS to the parent.
		m_btweight.recalculate();
		m_itChildren = m_btweight.begin();
		m_nodeStatus = SUCCESS;
		if (m_parent!= NULL) {
			m_parent->update(m_nodeStatus);
		}
	}
}

bool CBTWeightSelectorNode::_init()
{
	if (m_nodeInfor == NULL) {
		return false;
	}

	BSLib::Utility::CStringA strWeights;
	if (m_nodeInfor->m_btNodeProperties.getValue("Weights", strWeights)) {
		std::vector<BSLib::Utility::CStringA> strWeightList;
		NodeWeights nodeWeights;
		int w = 0;
		if (strWeights.split(strWeightList, ',')) {
			for (BSLib::uint32 i=0; i<strWeightList.size(); ++i) {
				strWeightList[i] >> w;
				nodeWeights.push_back(w);
			}
			m_btweight.setWeights(nodeWeights);
		}
	}

	m_btweight.setChildrenNodes(m_Children);
	m_btweight.recalculate();
	return true;
}

void CBTWeightSelectorNode::_execute()
{
	m_itChildren = m_btweight.begin();
	if (m_itChildren == m_btweight.end()) {
		return ;
	}
	CBTNode* btNode = *m_itChildren;
	if (btNode == NULL) {
		return ;
	}
	btNode->executeDbg();	
}

void  CBTWeightSelectorNode::_reset()
{
	m_btweight.recalculate();
	m_itChildren = m_btweight.begin();
}

}// BehaviorTree

}//BSLib
