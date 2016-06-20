//////////////////////////////////////////////////////////////////////
//	created:	2011/06/03
//	filename:	src\BSLib\utility\io\iniFile.cpp
//	author:		mazhejiang
//
///	@brief
///
//////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <BSLib/utility/tracer.h>
#include <BSLib/utility/file/iniFile.h>
#include <BSLib/utility/string.h>

#define FILE_CMD_LINE_MAX 4192

namespace BSLib
{

namespace Utility
{

bool CIniFile::open(std::string& strFile)
{
	if (strFile.empty() || strFile == "") {
		return false;
	}

	FILE *fp = NULL;
#ifdef _WIN32
	
	if (fopen_s(&fp, strFile.c_str(), "rb") != 0){
		return false;
	}

#else

	fp = fopen(strFile.c_str(), "rb");
	if (fp == NULL) {
		return false;
	}

#endif
	
	char buff[FILE_CMD_LINE_MAX+1];
	std::string app = "";
	memset(buff, 0, sizeof(buff));
	while (!feof(fp)){
		if (fgets(buff, FILE_CMD_LINE_MAX, fp) == NULL) {
			continue;;
		}
		if (strlen(buff) <= 0){
			continue;
		}
		if (buff[0] == '#'){
			continue;
		}
		if (buff[0] == '['){
			app = "";
			for (int i = 1; buff[i] >= ' ' && buff[i] != ']'; ++i){
				app.push_back(buff[i]);
			}
			continue;
		}
		std::string key = "";
		if (!(app.empty() || app == "")){
			key = app + '/';
		}
		int j = 0;
		for (; buff[j] >= ' ' && buff[j] != '='; ++j){
			if (buff[j] == ' '){
				continue;
			}
			key.push_back(buff[j]);
		}

		if (buff[j] == '='){
			++j;
		}
		std::string val = "";
		bool first = true;
		for (; buff[j] >= ' '; ++j){
			if (buff[j] == ' ' && first){
				continue;
			}
			first = false;
			val.push_back(buff[j]);
		}
		if (val.empty() || val == ""){
			continue;
		}
		setValue(key, val);
	}
	fclose(fp);
	return true;
}


std::string& CIniFile::getValue(const std::string& key)
{
	CStringA strKey(key);
	strKey.toLower();
	return m_paraHashMap.getValue(strKey);
}

void CIniFile::setValue(const std::string& key, const std::string& value)
{
	CStringA strKey(key);
	strKey.toLower();
	m_paraHashMap.setValue(strKey, value);
}

void CIniFile::setValue(const std::string& appName, const std::string& paramName, const std::string& value)
{
	CStringA key = appName;
	key += "/";
	key += paramName;
	key.toLower();
	m_paraHashMap.setValue(key, value);
}

void CIniFile::remove(const std::string& key)
{
	CStringA strKey(key);
	strKey.toLower();
	m_paraHashMap.remove(strKey);
}

bool CIniFile::find(const std::string& key)
{
	CStringA strKey(key);
	strKey.toLower();
	return m_paraHashMap.find(strKey) != m_paraHashMap.end();
}

void CIniFile::clear()
{
	m_paraHashMap.clear();
}

unsigned int CIniFile::size() const
{
	return m_paraHashMap.size();
}

int CIniFile::getValueInt(const std::string& key)
{
	return atoi(getValue(key).c_str());
}

int CIniFile::getValueInt(const std::string& appName, const std::string& paramName)
{
	std::string key = appName;
	key += "/";
	key += paramName;
	return getValueInt(key);
}

std::string CIniFile::getValueStr(const std::string& key)
{
	return getValue(key);
}

std::string CIniFile::getValueStr(const std::string& appName, const std::string& paramName)
{
	std::string key = appName;
	key += "/";
	key += paramName;
	return getValueStr(key);
}

std::string& CIniFile::operator [](const std::string& key)
{
	return getValue(key);
}

void CIniFile::showAll()
{
	CHashMap<std::string, std::string>::iterator it = m_paraHashMap.begin();
	for (; it != m_paraHashMap.end(); ++it){
		BSLIB_LOG_DEBUG(ETT_BSLIB_UTILITY, "%s=%s", it->first.c_str(), it->second.c_str());
	}
}

}//Utility

}//BSLib
