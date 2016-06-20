//////////////////////////////////////////////////////////////////////
//	created:	2012/11/14
//	filename:	src\BSLib\behaviorTree\btFunction.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/string.h>
#include <BSLib/utility/tracer.h>
#include <BSLib/behaviorTree/behaviorTree.h>
#include "btScriptAction.h"

namespace BSLib
{

namespace BehaviorTree
{
//////////////////////////////////////////////////////////////////////////

CBTScriptAction::CBTScriptAction(CBTNode *parent)
: CBTAction(parent)
, m_actionScript(NULL)
{
	;
}

CBTScriptAction::~CBTScriptAction()
{
	_clear();
}

bool CBTScriptAction::_init()
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
	if (!m_nodeInfor->m_btNodeProperties.getValue("Function", strScript)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取Script失败[NodeID=%d]", getId());
		return false;
	}
	strScript.trim();
	if (strScript.empty()) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "获取Script失败[NodeID=%d]", getId());
		return false;
	}
	m_actionScript = env->parseFunctionList(strScript);
	if (m_actionScript == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "解析Script失败[NodeID=%d][Script=%s]", getId(), strScript.c_str());
		return false;
	}
	m_textActionScript = strScript;
	return true;
}

void CBTScriptAction::_clear()
{
	m_actionScript = NULL;
}

ENodeStatus CBTScriptAction::_step()
{
	if (m_actionScript == NULL) {
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
	BSLib::Utility::CScriptData scriptData;
	if (!m_actionScript->execute(scriptObject, &scriptData)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_BTREE, "执行Script失败[NodeID=%d]Script=%s]", getId(), m_textActionScript.c_str());
		return FAILURE;
	}
	BSLib::int32 resultData = 0;
	if (!scriptData.getInt32(resultData)) {
		return FAILURE;
	}
	if (resultData > 0) {
		return SUCCESS;
	} else if (resultData < 0) {
		return EXECUTING;
	}
	return FAILURE;
}

}// BehaviorTree

}//BSLib
