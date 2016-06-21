#ifndef __BSLIB_BEHAVIORTREE_BTSCRIPTACTION_H__
#define __BSLIB_BEHAVIORTREE_BTSCRIPTACTION_H__

#include <BSLib/utility/script.h>
#include <BSLib/behaviorTree/btLeafNode.h>

namespace BSLib
{

namespace BehaviorTree
{

class BSLIB_BEHAVIORTREE_API CBTScriptAction : public CBTAction
{
public:
	CBTScriptAction(CBTNode *parent);
	~CBTScriptAction();

protected:
	virtual bool _init();
	virtual void _clear();
	virtual ENodeStatus _step();

private:
	BSLib::Utility::IScriptFunctionListPtr m_actionScript;
	std::string m_textActionScript;
};


}// BehaviorTree

}//BSLib

#endif//__BSLIB_BEHAVIORTREE_BTSCRIPTACTION_H__


