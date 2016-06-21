#ifndef __BSLIB_BEHAVIORTREE_FILTERS_NONFILTER_H__
#define __BSLIB_BEHAVIORTREE_FILTERS_NONFILTER_H__

#include <BSLib/behaviorTree/btDecoratorNode.h>

namespace BSLib
{

namespace BehaviorTree
{

/**
 * NonFilter class.
 * Inverts the result of this node's child result.
 */
class CNonFilter : public CBTDecoratorNode
{
public:
	/**
	 * Constructor initializes member variables.
	 * @param a_parent The parent of this node.
	 */
	CNonFilter(CBTNode* a_parent);
	
protected:
	//!Function that codifies the behavior of this filter/decorator.
	virtual EDecoratorStatus _decorator(ENodeStatus& a_result);

};

}// BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_FILTERS_NONFILTER_H__

