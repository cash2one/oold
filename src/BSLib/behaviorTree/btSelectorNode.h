//////////////////////////////////////////////////////////////////////
//	created:	2012/10/20
//	filename:	src\BSLib\behaviorTree\btSelectorNode.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_BEHAVIORTREE_BTSELECTORNODE_H__
#define __BSLIB_BEHAVIORTREE_BTSELECTORNODE_H__

#include <BSLib/behaviorTree/btNode.h>

namespace BSLib
{

namespace BehaviorTree
{

/**
 * CBTSelectorNode class.
 * This is the Selector Node class. Executes its children from left to right, 
 * bailing out if one of them suceeds.
 */
class CBTSelectorNode : public CBTNode
{

public:
	//!Constructor initializes member variables. Receives the parent of this new node.
	CBTSelectorNode(CBTNode *a_parent);

	/** 
	 * Called when my child ends its execution
	 * @param a_result Result of the child execution.
	 */
	virtual void update(ENodeStatus a_result);

protected:
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
};

}// BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_BTSELECTORNODE_H__
