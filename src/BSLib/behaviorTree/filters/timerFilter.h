#ifndef __BSLIB_BEHAVIORTREE_FILTERS_TIMERFILTER_H__
#define __BSLIB_BEHAVIORTREE_FILTERS_TIMERFILTER_H__

#include <BSLib/utility/dateTime.h>
#include <BSLib/behaviorTree/btDecoratorNode.h>

namespace BSLib
{

namespace BehaviorTree
{

/**
 * TimerFilter class.
 * Locks the access to this node's child during a X amount of time since the last execution.
 */
class CTimerFilter : public CBTDecoratorNode
{
public:
	/**
	 * Constructor initializes member variables.
	 * @param a_parent The parent of this node.
	 * @param a_time Time to lock the access after execution.
	 */
	CTimerFilter(CBTNode* a_parent);

	void setRealTime(BSLib::Utility::CRealTime* a_realTime) { m_realTime = a_realTime; }

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

	/**
	 * This function is called when this node has to be executed.
	 */
	virtual void _execute();

protected:
	BSLib::Utility::CDelayTimer m_timer;
	BSLib::Utility::CRealTime* m_realTime;
	BSLib::uint32 m_intervalTime;
};

}//BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_FILTERS_TIMERFILTER_H__

