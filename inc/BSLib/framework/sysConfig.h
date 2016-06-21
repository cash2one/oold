#ifndef __BSLIB_FRAMEWORK_SYSCONFIG_H__
#define __BSLIB_FRAMEWORK_SYSCONFIG_H__

#include <BSLib/utility/singleton.h>
#include <BSLib/utility/file/iniFile.h>
#include <BSLib/framework/baseDef.h>

namespace BSLib
{

namespace Framework
{

class BSLIB_FRAMEWORK_API CSysConfig : public Utility::CIniFile
{
public:
	BSLIB_SINGLETON_DECLARE(CSysConfig);

public:
	CSysConfig();
	virtual ~CSysConfig();

	void initMain(char* lpCmdLine);
	void initMain(int argc, char* argv[]);
	const std::vector<char*>& argv() { return m_argv; }

protected:

private:
	void _initCmd(std::vector<std::string>& cmdList);
	std::vector<char*> m_argv;
	char* m_cmdLine;
};

}//Framework

}//BSLib

#endif //__BSLIB_FRAMEWORK_SYSCONFIG_H__

