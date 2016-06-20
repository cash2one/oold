//////////////////////////////////////////////////////////////////////
//	created:	2012/10/25
//	filename:	src\BSLib\behaviorTree\filters\untilSuccessLimitedFilter.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_BEHAVIORTREE_FILTERS_UNTILSUCCESSLIMITEDFILTER_H__
#define __BSLIB_BEHAVIORTREE_FILTERS_UNTILSUCCESSLIMITEDFILTER_H__

#include <BSLib/behaviorTree/btDecoratorNode.h>

namespace BSLib
{

namespace BehaviorTree
{

/**
 * UntilFailsLimitedFilter class.
 * Executes this node's child repeatedly until it receives a FAILULRE, or
 * an execution counter reaches a limit.
 */
class CUntilSuccessLimitedFilter : public CBTDecoratorNode
{
public:
	/**
	 * Constructor initializes member variables.
	 * @param a_parent The parent of this node.
	 */
	CUntilSuccessLimitedFilter(CBTNode* a_parent);
	
	/**
	 * This method is used to initialize the node (suggestion: read leaf node parameters here from property table)
	 */
	virtual bool _init();

	/**
	 * This method is used to reset the values of the node to its initial state.
	 * Used when the user hits the Stop button in the editor. Every subclass must overwrite this method
	 * to reset its state (filter variables, current child in selectors and conditions, etc...).
	 * This may be used too in class leaf nodes to reset user's leaves.
	 */
	virtual void _reset();

	virtual EDecoratorStatus _decorator(ENodeStatus& a_result);

private:
	//! Limit of executions that this filter will 'bounce' (min value: 1)
	int m_maxTimes;

	// Number of consecutve executions 
	int m_currTime;
};

}//BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_FILTERS_UNTILSUCCESSLIMITEDFILTER_H__
