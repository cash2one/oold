#ifndef __BSLIB_UTILITY_INIFILE_H__
#define __BSLIB_UTILITY_INIFILE_H__

#include <BSLib/utility/hashMap.h>

namespace BSLib
{

namespace Utility
{
//////////////////////////////////////////////////////////////////////////
/// @brief 对ini文件操作
//////////////////////////////////////////////////////////////////////////	
class BSLIB_UTILITY_API CIniFile
{
public:
	bool open(std::string& strFile);

	std::string& getValue(const std::string& key);
	void setValue(const std::string& key, const std::string& value);
	void setValue(const std::string& appName, const std::string& paramName, const std::string& value);
	void remove(const std::string& key);
	bool find(const std::string& key);
	void clear();
	unsigned int size() const;

	int getValueInt(const std::string& key);
	int getValueInt(const std::string& appName, const std::string& paramName);
	std::string getValueStr(const std::string& key);
	std::string getValueStr(const std::string& appName, const std::string& paramName);

	std::string& operator [](const std::string& key);

	void showAll();

private:
	CHashMap<std::string, std::string> m_paraHashMap;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_INIFILE_H__

