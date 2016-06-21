#include <stdio.h>
#include <BSLib/utility/string.h>
#include <BSLib/framework/sysConfig.h>

namespace BSLib
{

namespace Framework
{

BSLIB_SINGLETON_DEFINE(CSysConfig)

#ifdef _WIN32 
	char g_moduleFileName[MAX_PATH + 1] = { 0 };
	std::vector<std::string> g_argv;
#endif


CSysConfig::CSysConfig()
: m_cmdLine(NULL)
{
	;
}

CSysConfig::~CSysConfig()
{
	if (m_cmdLine != NULL){
		BSLIB_SAFE_DELETE_ARRAY(m_cmdLine);
	}
}
void CSysConfig::initMain(char* lpCmdLine)
{
#ifdef _WIN32
	::GetModuleFileName(NULL, g_moduleFileName, MAX_PATH);
	
	std::vector<char *> argv;
	argv.push_back(g_moduleFileName);

	g_argv.clear();

	std::string temp;
	bool flag = false;

	for (int i=0; lpCmdLine[i]; ++i){
		if (lpCmdLine[i] == '"'){
			flag = !flag;
			continue;
		}
		if (!flag && lpCmdLine[i] == ' '){
			if (temp.empty() || temp == "")	{
				continue;
			}
			g_argv.push_back(temp);
			temp.clear();
			continue;
		}
		temp.push_back(lpCmdLine[i]);
	}
	if (!(temp.empty() || temp == ""))	{
		g_argv.push_back(temp);
	}

	for (uint32 j=0; j<g_argv.size(); ++j){
		argv.push_back((char*const)g_argv[j].c_str());
	}

	initMain((int)argv.size(), &argv[0]);
#endif
}

void CSysConfig::initMain(int argc, char* argv[])
{
	std::vector<std::string> cmdList;
	for (int i=0; i<argc; ++i){
		std::string strItem = argv[i];
		cmdList.push_back(strItem);
		m_argv.push_back(argv[i]);
	}
	_initCmd(cmdList);
}

void CSysConfig::_initCmd(std::vector<std::string>& cmdList)
{
	std::string key;
	std::string val;
	int paraNum = 0;
	for (uint32 i=0; i<cmdList.size(); ++i){
		key.clear();
		val.clear();

		if (cmdList[i][0] == '-'){
			if (cmdList[i].size() <= 1){
				continue;
			}
			if (cmdList[i][1] == '-'){
				if (cmdList[i].size() <= 2){
					continue;
				}
				key = &(cmdList[i].c_str()[2]);
				Utility::CIniFile::setValue(key, key);
				continue ;
			}
			key = &(cmdList[i].c_str()[1]);
			if (i+1 < cmdList.size()){
				val = cmdList[i+1];
				++i;
			}
			Utility::CIniFile::setValue(key, val);
			continue;
		}
		char tmpParaNum[16];

#ifdef _WIN32

		sprintf_s(tmpParaNum, sizeof(tmpParaNum), "%d", paraNum);

#else

		snprintf(tmpParaNum, sizeof(tmpParaNum), "%d", paraNum);

#endif

		key = tmpParaNum;
		val = cmdList[i];
		Utility::CIniFile::setValue(key, val);
		++paraNum;
	}
}

}//Framework

}//BSLib

