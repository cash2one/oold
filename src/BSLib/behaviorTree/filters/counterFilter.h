#ifndef __BSLIB_BEHAVIORTREE_FILTERS_COUNTERFILTER_H__
#define __BSLIB_BEHAVIORTREE_FILTERS_COUNTERFILTER_H__

#include <BSLib/behaviorTree/btDecoratorNode.h>

namespace BSLib
{

namespace BehaviorTree
{

/**
 * CounterFilter class.
 * Limits the number of executions that this filter's child can afford.
 */
class CCounterFilter : public CBTDecoratorNode
{
public:
	/**
	 * Constructor initializes member variables. Receives this node's parent and the number of times 
	 * that this filter's child can afford.
	 * @param a_parent The parent of this node.
	 * @param a_times Number of times that this filter's child can afford.
	 */
	CCounterFilter(CBTNode* a_parent);

protected:
	/**
	 * This method is used to initialize the node (suggestion: read leaf node parameters here from property table)
	 */
	virtual bool _init();

	//!Function that codifies the behavior of this filter/decorator.
	virtual EDecoratorStatus _decorator(ENodeStatus& a_result);

	/**
	 * This function is called when this node has to be executed.
	 */
	virtual void _execute();

	/**
	 * This method is used to reset the values of the node to its initial state.
	 * Used when the user hits the Stop button in the editor. Every subclass must overwrite this method
	 * to reset its state (filter variables, current child in selectors and conditions, etc...).
	 * This may be used too in class leaf nodes to reset user's leaves.
	 */
	virtual void _reset();

protected:

	//! Number of times that this filter's child can afford.
	int m_maxTimes;

	//! Number of this filter's child executions.
	int m_times;
};

}//BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_FILTERS_COUNTERFILTER_H__

