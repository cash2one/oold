#include <BSLib/utility/string.h>
#include <BSLib/behaviorTree/behaviorTree.h>
#include "timerFilter.h"

namespace BSLib
{

namespace BehaviorTree
{

CTimerFilter::CTimerFilter(CBTNode* a_parent)
: CBTDecoratorNode(a_parent)
, m_timer(10)
, m_realTime(NULL)
, m_intervalTime(10)
{
	;
}

bool CTimerFilter::_init()
{
	if (m_nodeInfor == NULL) {
		return false;
	}
	BSLib::Utility::CStringA strTrueMax;
	if (m_nodeInfor->m_btNodeProperties.getValue("IntervalTime", strTrueMax)) {
		strTrueMax >> m_intervalTime;
	}
	if (m_tree != NULL) {
		if (m_realTime == NULL) {
			return false;
		}
		m_realTime->now();
		m_timer.reset(m_intervalTime, *m_realTime);
	}
	return true;
}

EDecoratorStatus CTimerFilter::_decorator(ENodeStatus& a_result)
{
	return EDCTS_TOPARENT;
}

void  CTimerFilter::_reset()
{
	if (m_tree != NULL) {
		if (m_realTime != NULL) {
			m_realTime->now();
			m_timer.reset(m_intervalTime, *m_realTime);
		}
	}
	CBTDecoratorNode::_reset();
}

void CTimerFilter::_execute()
{
	if (m_tree != NULL) {
		if (m_realTime != NULL) {
			m_realTime->now();
			if (m_timer(*m_realTime, m_intervalTime)) {
				CBTDecoratorNode::_execute();
			}
		}
	}
}

}//BehaviorTree

}//BSLib
