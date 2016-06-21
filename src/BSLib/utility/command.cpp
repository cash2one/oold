#include <BSLib/utility/command.h>

namespace BSLib
{

namespace Utility
{


CProperties::CProperties()
{
	;
}

CProperties::~CProperties()
{
	;
}

const std::string& CProperties::getValueString(const std::string& key)
{
	return m_properties.getValue(key);
}

bool CProperties::getValueString(const std::string& key, std::string& value)
{
	return m_properties.getValue(key, value);
}

int32 CProperties::getValueInt32(const std::string& key)
{
	return atoi(m_properties.getValue(key).c_str());
}

bool CProperties::getValueInt32(const std::string& key, int32& value)
{
	std::string strValue;
	if (!m_properties.getValue(key, strValue)) {
		return false;
	}
	value = atoi(strValue.c_str());
	return true;
}

void CProperties::setValueString(const std::string& key, const std::string& value)
{
	m_properties.setValue(key, value);
}

void CProperties::clear()
{
	m_properties.clear();
}

const std::string& CProperties::operator[] (const std::string& key)
{
	return m_properties.getValue(key);
}

//////////////////////////////////////////////////////////////////////////
CCommand::CCommand()
{
	;
}

CCommand::~CCommand()
{
	;
}

int CCommand::parseCommand(const std::string& cmdLine, void* tempPara)
{
	std::string command;
	CProperties properties;
	if (!getCommand(cmdLine, command, properties)) {
		return -1;
	}

	return _execCmd(command, properties, tempPara);
}

bool CCommand::getCommand(const std::string& cmdLine, std::string& command)
{
	CProperties properties;
	if (!getCommand(cmdLine, command, properties)) {
		return false;
	}
	return true;
}

bool CCommand::getCommand(const std::string& cmdLine, std::string& command, CProperties& properties)
{
	std::vector<std::string> subCmdList;
	properties.clear();

	if(_split(cmdLine, subCmdList, ' ') <= 0){
		return false;
	}
	char tmpParaNum[16];
	int paraNum = 0;

	BSLibSprintf(tmpParaNum, sizeof(tmpParaNum), "%d", paraNum);
	properties.setValueString(tmpParaNum, subCmdList[0]);
	++paraNum;

	std::vector<std::string> keyValueList;
	for (uint32 i=1; i<subCmdList.size(); ++i){
		int res = _split(subCmdList[i].c_str(), keyValueList, '=');
		if (res <= 0){
			continue;
		} else if (res == 1){
			BSLibSprintf(tmpParaNum, sizeof(tmpParaNum), "%d", paraNum);
			properties.setValueString(tmpParaNum, keyValueList[0]);
			++paraNum;
			continue;
		}
		properties.setValueString(keyValueList[0], keyValueList[1]);
	}
	command = subCmdList[0];
	return true;
}

int CCommand::_split(const std::string& cmdLine, std::vector<std::string>& subCmdList, char separator)
{
	std::string temp;
	subCmdList.clear();
	bool flag = false;
	for (uint32 i=0; i<cmdLine.size(); ++i){
		if (cmdLine[i] == '"'){
			flag = !flag;
			continue;
		}
		if (!flag && cmdLine[i] == separator){
			if (temp.empty() || temp == "")	{
				continue;
			}
			subCmdList.push_back(temp);
			temp.clear();
			continue;
		}
		temp.push_back(cmdLine[i]);
	}
	if (!(temp.empty() || temp == ""))	{
		subCmdList.push_back(temp);
	}
	return (int)subCmdList.size();
}

}//Utility

}//BSLib


