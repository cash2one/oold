//////////////////////////////////////////////////////////////////////
//	created:	2012/10/20
//	filename:	BSLib\behaviorTree\btNode.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_BEHAVIORTREE_BTNODE_H__
#define __BSLIB_BEHAVIORTREE_BTNODE_H__

#include <BSLib/utility/hashMap.h>
#include <BSLib/behaviorTree/baseDef.h>

namespace BSLib
{

namespace BehaviorTree
{

/*! Status for this node. */
enum ENodeStatus
{
	START = 0,		/*!< The node is ready to start. */
	FAILURE = 1,	/*!< The node returned failure. */
	SUCCESS = 2,	/*!< The node returned success.  */
	EXECUTING = 3	/*!< The node is currently executing. */
};

class CBTNode;
class CBehaviorTree;

/*! Vector of nodes. Used to represent the data structure that holds the children of this node. */
typedef std::vector<CBTNode*> ChildNodes; 

/*! Hashtable of properties. All the node preperties defined in the XML file are stored here, 
    as pairs <Key,Value>: <String,String>. */
typedef BSLib::Utility::CHashMap<std::string, std::string> PropertyTable;

struct BSLIB_BEHAVIORTREE_API SBTNodeInfor
{
	//! ID of this node, given and used by the BT editor in a debug session.
	int		m_btNodeID;

	//! Name of this node. It is only used for debug purposes.
	std::string m_btNodeName;

	/**
	* List of properties defined for this node.
	*/
	PropertyTable m_btNodeProperties;
};

/**
 * The core CBTNode class.
 * This is the basic node for a Behavior Tree. All the nodes in this library 
 * have this as the top class of their hierarchy.
 */
class CBTNode
{
public:
	//!Constructor initializes member variables.
	CBTNode();	

	/**
	 * Constructor initializes member variables. Receives and sets a pointer to the parent of this new node.
	 * @param a_parent Is the parent of this node.
	 */
	CBTNode(CBTNode* a_parent);

	//!Destructor frees member variables.
	virtual ~CBTNode();

	/**
	 * Initializes the node. Calls initNode() method on children nodes.
	 */
	bool initNode();

	void clearNode();

	/**
	 * Resets the node and calls resetNode() method on children nodes.
	 */
	void resetNode();

	/**
	 * Adds a new node as a child of this.
	 * @param a_Node The new child.
	 */
	void pushBack(CBTNode* a_Node);

	/**
	 * Manages breakpoint flags and logging, before
	 * calling the virtual function _execute() to _execute this node.
	 * @see _execute()
	 */
	void executeDbg();

	/**
	 * Function called from the behavior tree so this node contines with the
	 * execution from last step position, both executing the same node again
	 * or notifying the result to the parent (if applicable).
	 */
	void notifyResult();

	// GETTERS //

	/**
	 * Returns the behavior tree this node belongs to.
	 * @return m_tree, a pointer to the behavior tree this node belongs to.
	 */
	CBehaviorTree* getBehaviorTree()	{return m_tree;}
	
	/**
	 * Returns the id given by the BT editor.
	 * @return m_id, the id given by the BT editor.
	 */
	int	getId()
	{
		if (m_nodeInfor != NULL) {
			return m_nodeInfor->m_btNodeID;
		}
		return 0;
	}

	/**
	 * Returns the name of this node. This is used only to help debugging.
	 * @return m_name, the name of this node. 
	 */
	std::string	getName()
	{
		if (m_nodeInfor != NULL) {
			return m_nodeInfor->m_btNodeName;
		}
		return "";
	}
	
	/**
	 * Returns the status of this node. 
	 * @return m_nodeStatus, the status of this node. 
	 */
	ENodeStatus getNodeStatus(){ return m_nodeStatus; }

	// SETTERS //
	
	/**
	 * Assigns the behavior tree this node belongs to.
	 * @param a_bt The behavior tree this node belongs to.
	 */
	void setBehaviorTree(CBehaviorTree* a_bt) {m_tree = a_bt;}

	void setNodeInfor(SBTNodeInfor* a_nodeInfor) { m_nodeInfor = a_nodeInfor; }

	/** 
	 * Called when my child ends its execution
	 * @param a_result Result of the child execution.
	 */
	virtual void update(ENodeStatus a_result) {}

protected:
	/**
	 * This method is used to initialize the node (suggestion: read leaf node parameters here from property table)
	 */
	virtual bool _init() { return true; }

	virtual void _clear() {}

	/**
	 * This method is used to reset the values of the node to its initial state.
	 * to reset its state (filter variables, current child in selectors and conditions, etc...).
	 * This may be used too in class leaf nodes to reset user's leaves.
	 */
	virtual void _reset() {}

	/**
	 * This function is called when this node has to be executed.
	 */
	virtual void _execute() {}

protected:

	//! Index of this node in its parent vector of nodes.
	int m_index;

	//! Pointer to the parent of this node.
	CBTNode* m_parent;

	//! Vector of nodes, children of this node.
	ChildNodes m_Children;
	
	//! Iterator for the children vector of this node.
	ChildNodes::const_iterator m_itChildren; 

	//! Reference to the Behavior tree this node belongs.
	CBehaviorTree* m_tree;

	SBTNodeInfor* m_nodeInfor;

	/**
	 * Status of this node
	 */
	ENodeStatus m_nodeStatus;

private:
	//! Number of children this node has.
	static int m_NodeCount;
};

}// BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_BTNODE_H__
