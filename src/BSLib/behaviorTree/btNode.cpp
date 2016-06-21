#include <BSLib/behaviorTree/btNode.h>
#include <BSLib/behaviorTree/behaviorTree.h>

namespace BSLib
{

namespace BehaviorTree
{


int CBTNode::m_NodeCount = 0;

CBTNode::CBTNode()
: m_index(0)
, m_parent(NULL)
, m_tree(NULL)
, m_nodeInfor(NULL)
, m_nodeStatus(START)
{
	;
}

	
CBTNode::CBTNode(CBTNode* a_parent) 
: m_index(0)
, m_parent(a_parent)
, m_tree(NULL)
, m_nodeInfor(NULL)
, m_nodeStatus(START)
{
	m_itChildren = m_Children.end();
}

CBTNode::~CBTNode()
{
	;
}

bool CBTNode::initNode()
{
	for(ChildNodes::const_iterator itChild = m_Children.begin(); itChild != m_Children.end(); ++itChild) {
		CBTNode* child = (*itChild);
		if (child != NULL) {
			if (!child->initNode()) {
				return false;
			}
		}
	}
	return _init();
}

void CBTNode::clearNode()
{
	_clear();
	for (ChildNodes::const_iterator itChild = m_Children.begin(); itChild != m_Children.end(); ++itChild) {
		CBTNode* child = (*itChild);
		if (child != NULL) {
			child->clearNode();
			BSLIB_SAFE_DELETE(child);
		}
	}
	m_Children.clear();
	
}

void CBTNode::resetNode()
{
	for (ChildNodes::const_iterator itChild = m_Children.begin(); itChild != m_Children.end(); ++itChild) {
		CBTNode* child = (*itChild);
		if (child != NULL) {
			child->resetNode();
		}
	}
	_reset();
}

void CBTNode::pushBack(CBTNode* a_Node)
{
	if (a_Node == NULL) {
		return ;
	}
	for(ChildNodes::const_iterator itChild = m_Children.begin(); itChild != m_Children.end(); ++itChild) {
		CBTNode* child = (*itChild);
		if (child == a_Node) {
			return ;
		}
	}
	m_Children.push_back(a_Node);
}

void CBTNode::notifyResult()
{
	if((m_nodeStatus == FAILURE) || (m_nodeStatus == SUCCESS)) {
        ENodeStatus nodeStatusResult = m_nodeStatus;
        m_nodeStatus = START;
		if (m_parent != NULL) {
			m_parent->update(nodeStatusResult);
		}
    } else {
        //This will be executed if an action returns 
        //something different than SUCCESS or FAILURE (action executed again)
        executeDbg();
    }
}

void CBTNode::executeDbg()
{
	if (m_tree != NULL) {
		m_tree->setCurrentNode(this);
	}
	//Execution of this node. Step into this function if you are debugging to see what will be executed.
	_execute();
}

}// BehaviorTree

}//BSLib
