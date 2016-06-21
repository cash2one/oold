#ifndef __BSLIB_UTILITY_COMMAND_H__
#define __BSLIB_UTILITY_COMMAND_H__

#include <BSLib/utility/hashMap.h>

namespace BSLib
{

namespace Utility
{

class BSLIB_UTILITY_API CProperties
{
public:
	CProperties();
	virtual ~CProperties();

	const std::string& getValueString(const std::string& key);
	bool getValueString(const std::string& key, std::string& value);
	int32 getValueInt32(const std::string& key);
	bool getValueInt32(const std::string& key, int32& value);
	void setValueString(const std::string& key, const std::string& value);
	void clear();
	const std::string& operator[] (const std::string& key);

	CHashMap<std::string, std::string>* getPropertiesHashMap() { return &m_properties; }

protected:
private:
	CHashMap<std::string, std::string> m_properties;
};

class BSLIB_UTILITY_API CCommand
{

public:
	CCommand();
	virtual ~CCommand();
	int parseCommand(const std::string& cmdLine, void* tempPara);
	bool getCommand(const std::string& cmdLine, std::string& command);
	bool getCommand(const std::string& cmdLine, std::string& command, CProperties& properties);

private:
	int _split(const std::string& cmdLine, std::vector<std::string>& subCmdList, char separator);
	virtual int _execCmd(const std::string& command, CProperties& properties, void* tempPara) = 0;

};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_COMMAND_H__


