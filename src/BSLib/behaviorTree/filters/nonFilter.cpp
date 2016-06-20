//////////////////////////////////////////////////////////////////////
//	created:	2012/10/25
//	filename:	src\BSLib\behaviorTree\filters\nonFilter.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include "nonFilter.h"

namespace BSLib
{

namespace BehaviorTree
{

CNonFilter::CNonFilter(CBTNode* a_parent)
: CBTDecoratorNode(a_parent)
{
}

EDecoratorStatus CNonFilter::_decorator(ENodeStatus& a_result)
{
	if(a_result == SUCCESS){
		a_result = FAILURE;
	} else if(a_result == FAILURE){
		a_result = SUCCESS;
	}
	return EDCTS_TOPARENT;
}

}// BehaviorTree

}//BSLib
