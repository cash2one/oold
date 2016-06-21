#ifndef __BSLIB_BEHAVIORTREE_BTWEIGHTSEQUENCENODE_H__
#define __BSLIB_BEHAVIORTREE_BTWEIGHTSEQUENCENODE_H__

#include <BSLib/behaviorTree/btNode.h>
#include "btWeight.h"

namespace BSLib
{

namespace BehaviorTree
{

/**
 * CBTSequenceNode class.
 * This is the Sequence Node class. Executes its children from left to right, 
 * bailing out if one of them fails.
 */
class CBTWeightSequenceNode : public CBTNode
{
public:
	//!Constructor initializes member variables. Receives the parent of this new node.
	CBTWeightSequenceNode(CBTNode* a_parent);

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
	CBTWeight m_btweight;
};

}// BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_BTWEIGHTSEQUENCENODE_H__

