//////////////////////////////////////////////////////////////////////
//	created:	2012/10/25
//	filename:	src\BSLib\behaviorTree\filters\untilFailsFilter.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_BEHAVIORTREE_FILTERS_UNTILFAILSFILTER_H__
#define __BSLIB_BEHAVIORTREE_FILTERS_UNTILFAILSFILTER_H__

#include <BSLib/behaviorTree/btDecoratorNode.h>

namespace BSLib
{

namespace BehaviorTree
{

/**
 * UntilFailsFilter class.
 * Executes this node's child repeatedly until it receives a FAILULRE.
 */
class CUntilFailsFilter : public CBTDecoratorNode
{
public:
	/**
	 * Constructor initializes member variables.
	 * @param a_parent The parent of this node.
	 */
	CUntilFailsFilter(CBTNode* a_parent);

protected:
	//!Function that codifies the behavior of this filter/decorator.
	virtual EDecoratorStatus _decorator(ENodeStatus& a_result);
};


}//BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_FILTERS_UNTILFAILSFILTER_H__
