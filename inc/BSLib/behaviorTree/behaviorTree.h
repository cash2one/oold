#ifndef __BSLIB_BEHAVIORTREE_BEHAVIORTREE_H__
#define __BSLIB_BEHAVIORTREE_BEHAVIORTREE_H__

#include <BSLib/utility/dateTime.h>
#include <BSLib/utility/script.h>
#include <BSLib/behaviorTree/btNode.h>

namespace BSLib
{

namespace BehaviorTree
{

typedef BSLib::uint32 BTTPID;
typedef BSLib::uint32 BTID;
const BTID INVALID_BT = 0;

/*! Stop protocols for the behavior tree. Specifies whether the bt must stop its cycle execution
	in the leaf nodes or not.*/
enum SBTStopProtocol
{
	BTSTOPPROT_NON,			/*!< BT will not stop until reaching back the root.  */
	BTSTOPPROT_LEAFNODES,	/*!< BT will stop in all the leaf nodes. */
	BTSTOPPROT_ACTIONS,		/*!< BT will stop in all the actions.  */
	BTSTOPPROT_CONDITIONS,	/*!< BT will stop in all the conditions.  */
};
struct SBTInfor
{
	BTTPID m_btTPID;
	std::string m_btName;
	PropertyTable m_btProperties;
};

/**
 * The core CBehaviorTree class.
 * It is responsible for holding the collection of nodes that comprises the BT (Behavior Tree)
 * and the functionality for executing an individual BT.
 */
class BSLIB_BEHAVIORTREE_API CBehaviorTree
{
public:

	//!Constructor initializes member variables.
	CBehaviorTree(BTID a_id, BTTPID a_tpid, BSLib::Utility::CScriptEnvironment* a_btEnvironment);
	
	//!Destructor frees member variables.
	~CBehaviorTree(); 

	/**
	 * Sets a new node as a root node.
	 * @param a_Node The new child.
	 */
	void setRootNode(CBTNode* a_Node);

	void setScriptObject(BSLib::Utility::CScriptObject* a_scriptObject) { m_scriptObject = a_scriptObject; }

	//!Initializes the nodes of the tree. Calls init() method on those nodes that implement that function.
	bool initTree(); 

	/**
	 * Executes the behavior tree.
	 * @return The result of the execution.
	 */
	ENodeStatus execute();

	/**
	 * Resets the behavior tree.
	 */
	void resetTree();

	/**
	 * This function cleans the behavior tree.
	 */
	void clearTree();

	// GETTERS //
	/**
	 * Returns the ID of this behavior tree.
	 * @return The ID of the behavior tree.
	 */
	BTID getID() { return m_id; }
	BTTPID getTPID() { return m_tpid; }

	/**
	 * Returns the stop protocol of this tree.
	 * @return The stop protocol.
	 */
	SBTStopProtocol getStopProtocol() {return m_stopProtocol;}

	BSLib::Utility::CScriptEnvironment* getBTEnvironment() { return m_btEnvironment; }


	SBTInfor* getBTInfor() { return  m_btInfor; }

	// SETTERS //
	/**
	 * Sets the node that is being executed right now.
	 * @param a_curNode The current node.
	 */	
	void setCurrentNode(CBTNode* a_curNode);

	/**
	 * Sets the stop protocol for the node
	 * @param a_stopProtocol The new stop protocol.
	 */	
	void setStopProtocol(SBTStopProtocol a_stopProtocol) { m_stopProtocol = a_stopProtocol;}

	void setBTInfor(SBTInfor* btInfor) { m_btInfor = btInfor; }

	BSLib::Utility::CScriptObject* getScriptObject() { return m_scriptObject; }

private:
	//! The root BTLinkNode from which the rest of the tree branches.
	CBTNode* m_root;
	//! Indicates the stop protocol of the behavior tree.
	SBTStopProtocol m_stopProtocol;
	//! The current node being executed.
	CBTNode* m_currentNode;
	//! A unique identifier for the BT.
	BTID m_id; 
	BTTPID m_tpid;
	
	BSLib::Utility::CScriptEnvironment* m_btEnvironment;
	BSLib::Utility::CScriptObject* m_scriptObject;

	SBTInfor* m_btInfor;
};

}// CBehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_BEHAVIORTREE_H__

