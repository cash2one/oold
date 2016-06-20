//////////////////////////////////////////////////////////////////////
//	created:	2012/10/25
//	filename:	src\BSLib\behaviorTree\filters\counterFilter.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/string.h>
#include "counterFilter.h"

namespace BSLib
{

namespace BehaviorTree
{

CCounterFilter::CCounterFilter(CBTNode* a_parent)
: CBTDecoratorNode(a_parent)
, m_maxTimes(1)
, m_times(0)
{
	;
}

bool CCounterFilter::_init()
{
	if (m_nodeInfor == NULL) {
		return false;
	}
	BSLib::Utility::CStringA strTrueMax;
	if (m_nodeInfor->m_btNodeProperties.getValue("MaxTimes", strTrueMax)) {
		strTrueMax >> m_maxTimes;
	}
	return true;
}

EDecoratorStatus CCounterFilter::_decorator(ENodeStatus& a_result)
{
	++m_times;
	return EDCTS_TOPARENT;
}

void CCounterFilter::_execute()
{
	if (m_times >= m_maxTimes) {
		if (m_parent != NULL) {
			m_nodeStatus = FAILURE;
			m_parent->update(m_nodeStatus);
		}
		return ;
	}
	CBTDecoratorNode::_execute();
}


void  CCounterFilter::_reset()
{
	m_times = 0;
	CBTDecoratorNode::_reset();
}

}//BehaviorTree

}//BSLib
