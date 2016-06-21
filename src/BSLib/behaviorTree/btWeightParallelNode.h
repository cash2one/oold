#ifndef __BSLIB_BEHAVIORTREE_BTWEIGHTPARALLELNODE_H__
#define __BSLIB_BEHAVIORTREE_BTWEIGHTPARALLELNODE_H__

#include <BSLib/behaviorTree/btNode.h>
#include "btWeight.h"

namespace BSLib
{

namespace BehaviorTree
{

/**
 * BTLinkNode class.
 * This is the Root Node class. It is the top of the tree and it can only have one child.
 */
class CBTWeightParallelNode : public CBTNode
{
public:
	//!Constructor initializes member variables. Receives the parent of this new node, which normally is Null.
	CBTWeightParallelNode(CBTNode *a_parent);

	/** 
	 * Called when my child ends its execution
	 * @param a_result Result of the child execution.
	 */
	virtual void update(ENodeStatus a_result);

protected:
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
	CBTWeight m_btweight;
};

}// BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_BTWEIGHTPARALLELNODE_H__

