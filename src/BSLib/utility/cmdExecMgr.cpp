//////////////////////////////////////////////////////////////////////
//	created:	2013/06/09
//	filename:	src\BSLib\utility\cmdExecMgr.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/string.h>
#include <BSLib/utility/cmdExecMgr.h>

namespace BSLib
{

namespace Utility
{

CCmdExecMgr::CCmdExecMgr()
{
	;
}

CCmdExecMgr::~CCmdExecMgr()
{
	_remove();
}

int CCmdExecMgr::executeCommand(const std::string& cmdLine, void* tempPara)
{ 
	return CCommand::parseCommand(cmdLine, tempPara); 
}

bool CCmdExecMgr::addCmdExecPtr(const std::string& name, FCmdExecCb funCmdExec)
{
	BSLib::Utility::CStringA commandName = name;
	commandName.toLower();

	if (funCmdExec == NULL) {
		return false;
	}

	TCmdExecFun* cmdExeFun = new TCmdExecFun(funCmdExec);
	if (cmdExeFun == NULL) {
		return false;
	}

	THashMapCmdExecIter it = m_cmdExecHashMap.find(commandName);
	if (it != m_cmdExecHashMap.end()) {
		TCmdExecFun* cmdExecFunOld = it->second;
		
		m_cmdExecHashMap.remove(commandName);
		
		if (cmdExecFunOld != NULL) {
			delete cmdExecFunOld;
		}
	}
	m_cmdExecHashMap.setValue(commandName, cmdExeFun);
	return true;
}

bool CCmdExecMgr::addCmdExecPtr(const std::string& name, const TCmdExecFun& funCmdExec)
{
	BSLib::Utility::CStringA commandName = name;
	commandName.toLower();

	if (!funCmdExec.isValid()) {
		return false;
	}

	TCmdExecFun* cmdExeFun = funCmdExec.clone();
	if (cmdExeFun == NULL) {
		return false;
	}

	THashMapCmdExecIter it = m_cmdExecHashMap.find(commandName);
	if (it != m_cmdExecHashMap.end()) {
		TCmdExecFun* cmdExecFunOld = it->second;

		m_cmdExecHashMap.remove(commandName);

		if (cmdExecFunOld != NULL) {
			delete cmdExecFunOld;
		}
	}
	m_cmdExecHashMap.setValue(commandName, cmdExeFun);
	return true;
}

void CCmdExecMgr::delCmdExecPtr(const std::string& name)
{
	BSLib::Utility::CStringA commandName = name;
	commandName.toLower();

	THashMapCmdExecIter it = m_cmdExecHashMap.find(commandName);
	if (it != m_cmdExecHashMap.end()) {
		TCmdExecFun* cmdExecFunOld = it->second;

		m_cmdExecHashMap.remove(commandName);

		if (cmdExecFunOld != NULL) {
			delete cmdExecFunOld;
		}
	}
}

int CCmdExecMgr::_execCmd(const std::string& command, CProperties& properties, void* tempPara)
{
	BSLib::Utility::CStringA commandName = command;
	commandName.toLower();

	THashMapCmdExecIter it = m_cmdExecHashMap.find(commandName);
	TCmdExecFun* cmdExecFun= NULL;
	if (it == m_cmdExecHashMap.end()){
		return 0;
	}
	cmdExecFun = it->second;
	if (cmdExecFun == NULL)	{
		return 0;
	}
	return (*cmdExecFun)(properties, tempPara);
}

void CCmdExecMgr::_remove()
{
	THashMapCmdExecIter it = m_cmdExecHashMap.begin();
	for (; it != m_cmdExecHashMap.end(); ++it) {
		TCmdExecFun* cmdExecFun = it->second;
		if (cmdExecFun == NULL) {
			continue;
		}
		BSLIB_SAFE_DELETE(cmdExecFun);
	}
	m_cmdExecHashMap.clear();
}


}//Utility

}//BSLib

