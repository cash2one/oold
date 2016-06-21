#include <BSLib/utility/string.h>
#include <BSLib/behaviorTree/behaviorTree.h>
#include "btWeightParallelNode.h"

namespace BSLib
{

namespace BehaviorTree
{
CBTWeightParallelNode::CBTWeightParallelNode(CBTNode* a_parent) 
: CBTNode(a_parent)
, m_trueMax(1)
, m_trueCount(0)
{

}

void CBTWeightParallelNode::update(ENodeStatus a_result)
{
	if (m_tree == NULL) {
		return ;
	}
	m_tree->setCurrentNode(this);
	
	if (a_result == EXECUTING) {
		return ;
	}
	if (m_itChildren == m_btweight.end()) {
		return ;
	}
	++m_itChildren;

	if (a_result == SUCCESS) {
		++m_trueCount;
	}
	if (m_itChildren != m_btweight.end()) {
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
	m_btweight.recalculate();
	m_itChildren = m_btweight.begin();

	if (m_parent != NULL) {
		m_parent->update(m_nodeStatus);
	}
}

bool CBTWeightParallelNode::_init()
{
	if (m_nodeInfor == NULL) {
		return false;
	}
	BSLib::Utility::CStringA strTrueMax;
	if (m_nodeInfor->m_btNodeProperties.getValue("SuccessCount", strTrueMax)) {
		strTrueMax >> m_trueMax;
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

void CBTWeightParallelNode::_execute()
{
	m_trueCount = 0;
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

void  CBTWeightParallelNode::_reset()
{
	m_trueCount = 0;
	m_btweight.recalculate();
	m_itChildren = m_btweight.begin();
}

}// BehaviorTree

}//BSLib
