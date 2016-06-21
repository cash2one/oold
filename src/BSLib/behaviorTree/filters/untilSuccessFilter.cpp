#include "untilSuccessFilter.h"

namespace BSLib
{

namespace BehaviorTree
{

CUntilSuccessFilter::CUntilSuccessFilter(CBTNode* a_parent) 
: CBTDecoratorNode(a_parent)
{
}

EDecoratorStatus CUntilSuccessFilter::_decorator(ENodeStatus& a_result)
{
	if (a_result == SUCCESS) {
		return EDCTS_TOPARENT;
	} else if (a_result == FAILURE) {
		return EDCTS_EXECUTE;
	}
	return EDCTS_NULL;
}

}//BehaviorTree

}//BSLib
