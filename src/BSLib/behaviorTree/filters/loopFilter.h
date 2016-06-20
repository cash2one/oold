//////////////////////////////////////////////////////////////////////
//	created:	2012/10/25
//	filename:	src\BSLib\behaviorTree\filters\loopFilter.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_BEHAVIORTREE_FILTERS_LOOPFILTER_H__
#define __BSLIB_BEHAVIORTREE_FILTERS_LOOPFILTER_H__

#include <BSLib/behaviorTree/btDecoratorNode.h>

namespace BSLib
{

namespace BehaviorTree
{

/**
 * LoopFilter class.
 * Executes this filter's child a determinated number of times.
 */
class CLoopFilter : public CBTDecoratorNode
{
public:
	/**
	 * Constructor initializes member variables. Receives this node's parent and the number of times this 
	 * filter's child must be executed.
	 * @param a_parent The parent of this node.
	 * @param a_times Number of times that this filter's child must be executed.
	 */
	CLoopFilter(CBTNode* a_parent);

protected:
	/**
	 * This method is used to initialize the node (suggestion: read leaf node parameters here from property table)
	 */
	virtual bool _init();

	//!Function that codifies the behavior of this filter/decorator.
	virtual EDecoratorStatus _decorator(ENodeStatus& a_result);

	/**
	 * This method is used to reset the values of the node to its initial state.
	 * to reset its state (filter variables, current child in selectors and conditions, etc...).
	 * This may be used too in class leaf nodes to reset user's leaves.
	 */
	virtual void _reset();

protected:
	//! Number of times that this filter's child must be executed.
	int m_maxTimes;

	//! Number of this filter's child consecutive executions.
	int m_curExe;
};

}//BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_FILTERS_LOOPFILTER_H__
