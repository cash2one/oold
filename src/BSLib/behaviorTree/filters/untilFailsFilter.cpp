//////////////////////////////////////////////////////////////////////
//	created:	2012/10/25
//	filename:	src\BSLib\behaviorTree\filters\untilFailsFilter.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include "untilFailsFilter.h"

namespace BSLib
{

namespace BehaviorTree
{

CUntilFailsFilter::CUntilFailsFilter(CBTNode* a_parent) 
: CBTDecoratorNode(a_parent)
{
}

EDecoratorStatus CUntilFailsFilter::_decorator(ENodeStatus& a_result)
{
	if (a_result == FAILURE) {
		return EDCTS_TOPARENT;
	} else if (a_result == SUCCESS) {
		return EDCTS_EXECUTE;
	}
	return EDCTS_NULL;
}

}//BehaviorTree

}//BSLib