#include <BSLib/behaviorTree/behaviorTree.h>
#include <BSLib/behaviorTree/btLeafNode.h>

namespace BSLib
{

namespace BehaviorTree
{

CBTLeafNode::CBTLeafNode(CBTNode *parent)
: CBTNode(parent)
{
	;
}

//Destructor
CBTLeafNode::~CBTLeafNode()
{
	;
}

void CBTLeafNode::_execute()
{
	//Step into this function if you are debugging to see the execution of the leaf node.
	m_nodeStatus = _step();

	//We'll report to the parent only if the leaf node ended (m_nodeStatus != EXECUTING) the execution.
	if(m_nodeStatus == SUCCESS || m_nodeStatus == FAILURE) {
		if (m_tree == NULL) {
			return ;
		}
		//Remember: No matter the protocol, it ALWAYS will stop at the root
		switch(m_tree->getStopProtocol()) 
		{
		case BTSTOPPROT_NON: //ALWAYS UPDATES: Goes up to the root	
			if (m_parent != NULL) {
				m_parent->update(m_nodeStatus);
			}
			break;
		case BTSTOPPROT_LEAFNODES: //NEVER UPDATE: Stops in every leaf node.
			break;
		case BTSTOPPROT_CONDITIONS: //ONLY UPDATE IN ACTIONS: So stop after conditions.
			if(_getLeafType() == BTLEAF_ACTION) {
				if (m_parent != NULL) {
					m_parent->update(m_nodeStatus);
				}
			}
			break;
		case BTSTOPPROT_ACTIONS: //ONLY UPDATE IN CONDITIONS: So stop after actions.
			if(_getLeafType() == BTLEAF_CONDITION) {
				if (m_parent != NULL) {
					m_parent->update(m_nodeStatus);
				}
			}
			break;
		}
	}
}

}// BehaviorTree

}//BSLib
