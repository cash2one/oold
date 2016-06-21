#ifndef __BSLIB_BEHAVIORTREE_BTPARALLELNODE_H__
#define __BSLIB_BEHAVIORTREE_BTPARALLELNODE_H__

#include <BSLib/behaviorTree/btNode.h>

namespace BSLib
{

namespace BehaviorTree
{

/**
 * CBTParallelNode class.
 * This is the Selector Node class.
 * bailing out if one of them suceeds.
 */
class CBTParallelNode : public CBTNode
{
public:
	//!Constructor initializes member variables. Receives the parent of this new node, which normally is Null.
	CBTParallelNode(CBTNode *a_parent);

	/** 
	 * Called when my child ends its execution
	 * @param a_result Result of the child execution.
	 */
	virtual void update(ENodeStatus a_result);

protected:
	/**
	 * This method is used to initialize the node (suggestion: read leaf node parameters here from property table)
	 */
	virtual bool _init();
	/**
	 * This function is called when this node has to be executed.
	 * Executes its children from left to right, bailing out if one of them fails.
	 */
	virtual void _execute();

	/**
	 * This method is used to reset the values of the node to its initial state.
	 * to reset its state (filter variables, current child in selectors and conditions, etc...).
	 * This may be used too in class leaf nodes to reset user's leaves.
	 */
	virtual void _reset();

private:
	int m_trueMax;
	int m_trueCount;
};

}// BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_BTPARALLELNODE_H__

