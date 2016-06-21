#ifndef __BSLIB_BEHAVIORTREE_BTDECORATORNODE_H__
#define __BSLIB_BEHAVIORTREE_BTDECORATORNODE_H__

#include <BSLib/behaviorTree/btNode.h>

namespace BSLib
{

namespace BehaviorTree
{
enum EDecoratorStatus
{
	EDCTS_NULL = 0,
	EDCTS_TOPARENT = 1,
	EDCTS_EXECUTE = 2,
};

/**
 * The CBTDecoratorNode class.
 * Node for Filter nodes. This is a virtual class, must be overridden to create new filters.
 */
class BSLIB_BEHAVIORTREE_API CBTDecoratorNode : public CBTNode
{
public:
	//!Constructor initializes member variables.  Receives the pointer to the parent of this node.
	CBTDecoratorNode(CBTNode* a_parent);

	/** 
	 * Called when my child ends its execution
	 * @param a_result Result of the child execution.
	 */
	virtual void update(ENodeStatus a_result);

protected:
	//!Function that codifies the behavior of this filter/decorator.
	virtual EDecoratorStatus _decorator(ENodeStatus& a_result) { return EDCTS_TOPARENT; }

	/**
	 * This method is used to reset the values of the node to its initial state.
	 * to reset its state (filter variables, current child in selectors and conditions, etc...).
	 * This may be used too in class leaf nodes to reset user's leaves.
	 */
	virtual void _reset();

	/**
	 * This function is called when this node has to be executed.
	 * @return The result of the execution
	 */
	virtual void _execute();
};

}// BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_BTDECORATORNODE_H__

