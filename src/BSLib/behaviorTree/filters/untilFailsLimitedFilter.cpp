#include <BSLib/utility/string.h>
#include "untilFailsLimitedFilter.h"

namespace BSLib
{

namespace BehaviorTree
{

CUntilFailsLimitedFilter::CUntilFailsLimitedFilter(CBTNode* a_parent)
: CBTDecoratorNode(a_parent)
, m_maxTimes(1)
, m_currTime(0)
{
	;
}

bool CUntilFailsLimitedFilter::_init()
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

void  CUntilFailsLimitedFilter::_reset()
{
	m_currTime = 0;
	CBTDecoratorNode::_reset();
}

EDecoratorStatus CUntilFailsLimitedFilter::_decorator(ENodeStatus& a_result)
{
	++m_currTime;
	if (a_result == FAILURE) {
		m_currTime = 0;
		return EDCTS_TOPARENT;
	} else if (a_result == SUCCESS) {
		if (m_currTime >= m_maxTimes) {
			m_currTime = 0;
			return EDCTS_TOPARENT;
		}
		return EDCTS_EXECUTE;
	}
	return EDCTS_NULL;
}

}//BehaviorTree

}//BSLib

