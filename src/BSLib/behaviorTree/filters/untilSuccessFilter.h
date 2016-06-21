#ifndef __BSLIB_BEHAVIORTREE_FILTERS_UNTILSUCCESSFILTER_H__
#define __BSLIB_BEHAVIORTREE_FILTERS_UNTILSUCCESSFILTER_H__

#include <BSLib/behaviorTree/btDecoratorNode.h>

namespace BSLib
{

namespace BehaviorTree
{

/**
 * UntilFailsFilter class.
 * Executes this node's child repeatedly until it receives a FAILULRE.
 */
class CUntilSuccessFilter : public CBTDecoratorNode
{
public:
	/**
	 * Constructor initializes member variables.
	 * @param a_parent The parent of this node.
	 */
	CUntilSuccessFilter(CBTNode* a_parent);

protected:
	//!Function that codifies the behavior of this filter/decorator.
	virtual EDecoratorStatus _decorator(ENodeStatus& a_result);
};


}//BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_FILTERS_UNTILSUCCESSFILTER_H__

