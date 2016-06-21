#ifndef __BSLIB_BEHAVIORTREE_BTSCRIPTCONDITION_H__
#define __BSLIB_BEHAVIORTREE_BTSCRIPTCONDITION_H__

#include <BSLib/utility/script.h>
#include <BSLib/behaviorTree/btLeafNode.h>

namespace BSLib
{

namespace BehaviorTree
{

class CBTScriptConditionItem;

class BSLIB_BEHAVIORTREE_API CBTScriptCondition : public CBTCondition
{
public:
	CBTScriptCondition(CBTNode *parent);
	~CBTScriptCondition();

protected:
	virtual bool _init();
	virtual void _clear();
	virtual ENodeStatus _step();

private:
	BSLib::Utility::IScriptPtr m_conditionScript;
	std::string m_textConditionScript;
};

}// BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_BTSCRIPTCONDITION_H__

