//////////////////////////////////////////////////////////////////////
//	created:	2012/10/25
//	filename:	src\BSLib\behaviorTree\filters\loopFilter.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/string.h>
#include "loopFilter.h"

namespace BSLib
{

namespace BehaviorTree
{

CLoopFilter::CLoopFilter(CBTNode* a_parent)
: CBTDecoratorNode(a_parent)
, m_maxTimes(1)
, m_curExe(0)
{
	;
}

bool CLoopFilter::_init()
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

EDecoratorStatus CLoopFilter::_decorator(ENodeStatus& a_result)
{
	++m_curExe;
	if (m_curExe >= m_maxTimes) {
		a_result = SUCCESS;
		m_curExe = 0;
		return EDCTS_TOPARENT;
	} 
	return EDCTS_EXECUTE;
}

void CLoopFilter::_reset()
{
	m_curExe = 0;
	CBTDecoratorNode::_reset();
}

}//BehaviorTree

}//BSLib