#include <BSLib/utility/string.h>
#include <BSLib/utility/tracer.h>
#include <BSLib/behaviorTree/behaviorTree.h>
#include "btScriptCondition.h"

namespace BSLib
{

namespace BehaviorTree
{

//////////////////////////////////////////////////////////////////////////

CBTScriptCondition::CBTScriptCondition(CBTNode *parent)
: CBTCondition(parent)
, m_conditionScript(NULL)
{
	;
}

CBTScriptCondition::~CBTScriptCondition()
{
	_clear();
}

bool CBTScriptCondition::_init()
{
	if (m_nodeInfor == NULL) {
		return false;
	}
	CBehaviorTree* tree = CBTLeafNode::getBehaviorTree();
	if (tree == NULL) {
		return false;
	}
	BSLib::Utility::CScriptEnvironment* env = tree->getBTEnvironment();
	if (env == false) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取ScriptEnvironment失败");
		return false;
	}
	BSLib::Utility::CStringA strScript;
	if (!m_nodeInfor->m_btNodeProperties.getValue("Expression", strScript)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取Expression失败[NodeID=%d]", getId());
		return false;
	}
	strScript.trim();
	if (strScript.empty()) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取Expression失败[NodeID=%d]", getId());
		return false;
	}
	m_conditionScript = env->parseExpression(strScript);
	if (m_conditionScript == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "解析Expression失败[NodeID=%d][Expression=%s]", getId(), strScript.c_str());
		return false;
	}
	m_textConditionScript = strScript;
	return true;
}

void CBTScriptCondition::_clear()
{
	m_conditionScript = NULL;
}

ENodeStatus CBTScriptCondition::_step()
{
	if (m_conditionScript == NULL) {
		return FAILURE;
	}
	CBehaviorTree* tree = CBTLeafNode::getBehaviorTree();
	if (tree == NULL) {
		return FAILURE;
	}
	BSLib::Utility::CScriptObject* scriptObject = tree->getScriptObject();
	if (scriptObject == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取ScriptObject失败[NodeID=%d]", getId());
		return FAILURE;
	}
	bool scriptResult = false;
	if (!m_conditionScript->execute(scriptObject, scriptResult)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "执行Expression失败[NodeID=%d]Expression=%s]", getId(), m_textConditionScript.c_str());
		return FAILURE;
	}
	if (scriptResult == true) {
		return SUCCESS;
	}
	return FAILURE;
}

}// BehaviorTree

}//BSLib


