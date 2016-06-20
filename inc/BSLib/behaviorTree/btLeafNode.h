//////////////////////////////////////////////////////////////////////
//	created:	2012/10/20
//	filename:	BSLib\behaviorTree\btLeafNode.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_BEHAVIORTREE_BTLEAFNODE_H__
#define __BSLIB_BEHAVIORTREE_BTLEAFNODE_H__

#include <BSLib/behaviorTree/btNode.h>

namespace BSLib
{

namespace BehaviorTree
{

enum EBTLeafType
{
	BTLEAF_UNDEF = 0,
	BTLEAF_CONDITION = 1,
	BTLEAF_ACTION = 2
};

/**
 * The core CLeafNode class.
 * This is a virtual class, and must be used as the base class for leaf node classes.
 * Actions and condition classes must inherit from this class, overriding the method step()
 * to perform the actual behavior of the node.
 */
class BSLIB_BEHAVIORTREE_API CBTLeafNode : public CBTNode
{
public:
	/**
	 * Constructor initializes member variables. Receives and sets a pointer to the parent of this new node.
	 * @param a_owner Is the handler that identifies the owner of this node.
	 * @param parent Is the parent of this node.
	 */
	CBTLeafNode(CBTNode *parent);
	
	//!Destructor frees member variables.
	~CBTLeafNode();

	virtual EBTLeafType _getLeafType() = 0;

protected:
	/**
	 * This method must be overridden by the leaf node classes, so the actual behavior of the 
	 * action or condition is triggered.
	 * @return The result of the execution.
	 */
	virtual ENodeStatus _step() { return START; }		

	/**
	 * Executes this leaf node. Takes care of logging and calls step() to trigger the
	 * leaf node behavior.
	 * @return The result of the execution.
	 */
	virtual void _execute(); 
};

class BSLIB_BEHAVIORTREE_API CBTCondition : public CBTLeafNode
{
public:
	CBTCondition(CBTNode *parent) : CBTLeafNode(parent)
	{
		;
	}

	virtual EBTLeafType _getLeafType() { return BTLEAF_CONDITION; }
};

class BSLIB_BEHAVIORTREE_API CBTAction : public CBTLeafNode
{
public:
	CBTAction(CBTNode *parent) : CBTLeafNode(parent)
	{
		;
	}

	virtual EBTLeafType _getLeafType() { return BTLEAF_ACTION; }
};

}// BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_BTLEAFNODE_H__
