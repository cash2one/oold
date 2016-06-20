//////////////////////////////////////////////////////////////////////
//	created:	2013/06/09
//	filename:	BSLib\utility\cmdExecMgr.h
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __BSLIB_UTILITY_CMDEXECMGR_H__
#define __BSLIB_UTILITY_CMDEXECMGR_H__

#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/command.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CCmdExecMgr : public CCommand
{
public:
	//返回值说明,-1 解析命令出错，0 命令没有执行，>0自定义
	typedef int(*FCmdExecCb)(CProperties&, void*);
	typedef CFunction<int, CProperties&, void*> TCmdExecFun;

public:
	CCmdExecMgr();
	virtual ~CCmdExecMgr();

	virtual int executeCommand(const std::string& cmdLine, void* tempPara);

	bool addCmdExecPtr(const std::string& name, FCmdExecCb funCmdExec);
	bool addCmdExecPtr(const std::string& name, const TCmdExecFun& funCmdExec);
	
	template<class NAME>
	bool addCmdExecPtr(const std::string& name, int(NAME::*funCmdExec)(CProperties&, void*), NAME* object)
	{
		return addCmdExecPtr(name, CFunctionObject<int, NAME, CProperties&, void*>(funCmdExec, object));
	}
	
	void delCmdExecPtr(const std::string& name);

private:
	virtual int _execCmd(const std::string& command, CProperties& properties, void* tempPara);
	void _remove();

private:
	typedef Utility::CHashMap<std::string, TCmdExecFun*> THashMapCmdExec;
	typedef THashMapCmdExec::iterator THashMapCmdExecIter;

	THashMapCmdExec m_cmdExecHashMap;
};


}//Utility

}//BSLib

#define BSLIB_CMDEXEC_DEFINE_BEGIN(name, funPtr)\
	const std::string cmdName = name;\
	TCmdExecFun*& cmdFunPtr = funPtr;
	
#define BSLIB_CMDEXEC_GLOBAL_FUN(name, fun)\
	if (cmdName == name) {\
		cmdFunPtr = new BSLib::Utility::CFunction<int, BSLib::Utility::CProperties&, void*>(fun);\
		return true;\
	}

#define BSLIB_CMDEXEC_OBJECT_FUN(name, className, fun, object)\
	if (cmdName == name) {\
		cmdFunPtr = new BSLib::Utility::CFunctionObject<int, className, BSLib::Utility::CProperties&, void*>(fun, object);\
		return true;\
	}

#define BSLIB_CMDEXEC_DEFINE_END()


#endif // __BSLIB_UTILITY_CMDEXECMGR_H__
