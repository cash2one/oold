//////////////////////////////////////////////////////////////////////
//	created:	2012/10/21
//	filename:	src\BSLib\behaviorTree\btWeightSequenceNode.cpp
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/string.h>
#include <BSLib/behaviorTree/behaviorTree.h>
#include "btWeightSequenceNode.h"

namespace BSLib
{

namespace BehaviorTree
{

CBTWeightSequenceNode::CBTWeightSequenceNode(CBTNode *a_parent) : CBTNode(a_parent)
{
}

void CBTWeightSequenceNode::update(ENodeStatus a_result)
{
	if (m_tree != NULL) {
		m_tree->setCurrentNode(this);
	}
	if (a_result == EXECUTING) {
		return ;
	}

	if (m_itChildren == m_btweight.end()) {
		return ;
	}
	++m_itChildren;

	//SUCCESS
	if(a_result == SUCCESS) {
		//If I can, go on with the next one...
		if(m_itChildren != m_btweight.end()) {
			CBTNode* btNode = *m_itChildren;
			if (btNode == NULL) {
				return ;
			}
			btNode->executeDbg();
		} else {
			//If not, we succeed! Notify that to my parent.
			m_itChildren = m_btweight.begin();
			m_nodeStatus = SUCCESS;
			if (m_parent != NULL) {
				m_parent->update(m_nodeStatus);
			}
		}
	} else if(a_result == FAILURE){
		//FAIL!! We have failed!
		m_itChildren = m_btweight.begin();
		m_nodeStatus = FAILURE;
		if (m_parent != NULL) {
			m_parent->update(m_nodeStatus);
		}
	}
}

bool CBTWeightSequenceNode::_init()
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

void CBTWeightSequenceNode::_execute()
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

void CBTWeightSequenceNode::_reset()
{
	m_btweight.recalculate();
	m_itChildren = m_btweight.begin();
}

}// CBehaviorTree

}//BSLib