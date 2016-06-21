#include <BSLib/utility/string.h>
#include <BSLib/utility/script.h>
#include <BSLib/utility/convert.h>
#include <BSLib/utility/tracer.h>
#include <BSLib/utility/random.h>

namespace BSLib
{

namespace Utility
{
//////////////////////////////////////////////////////////////////////////
CScriptData::CScriptData()
: m_isText(false)
, m_number(0)
{
	;
}

CScriptData::CScriptData(const CScriptData& a_other) 
: m_isText(false)
, m_number(0)
{
	if (a_other.m_isText){
		setString(*a_other.m_text);
		return ;
	}
	setInt64(a_other.m_number);
}

CScriptData::~CScriptData() 
{
	if (m_isText){
		BSLIB_SAFE_DELETE(m_text);
		m_isText = false;
	}
}

bool CScriptData::isText() const
{
	return m_isText;
}

void CScriptData::setInt32(BSLib::int32 a_data)
{
	if (m_isText){
		BSLIB_SAFE_DELETE(m_text);
		m_isText = false;
	}
	m_number = a_data;
}

void CScriptData::setUInt32(BSLib::uint32 a_data)
{
	if (m_isText){
		BSLIB_SAFE_DELETE(m_text);
		m_isText = false;
	}
	m_number = a_data;
}

void CScriptData::setInt64(BSLib::int64 a_data)
{
	if (m_isText){
		BSLIB_SAFE_DELETE(m_text);
		m_isText = false;
	}
	m_number = a_data;
}

void CScriptData::setUInt64(BSLib::uint64 a_data)
{
	if (m_isText){
		BSLIB_SAFE_DELETE(m_text);
		m_isText = false;
	}
	m_number = a_data;
}

void CScriptData::setString(const std::string& a_data)
{
	if (!m_isText){
		m_text = new std::string();
		if (m_text == NULL) {
			return;
		}
		m_isText = true;
	}
	*m_text = a_data;
}

bool CScriptData::getInt32(BSLib::int32& a_data) const
{
	if (m_isText){
		return false;
	}
	a_data = (BSLib::int32)m_number;
	return true;
}

bool CScriptData::getUInt32(BSLib::uint32& a_data) const
{
	if (m_isText){
		return false;
	}
	a_data = (BSLib::uint32)m_number;
	return true;
}

bool CScriptData::getInt64(BSLib::int64& a_data) const
{
	if (m_isText){
		return false;
	}
	a_data = m_number;
	return true;
}

bool CScriptData::getUInt64(BSLib::uint64& a_data) const
{
	if (m_isText){
		return false;
	}
	a_data = m_number;
	return true;
}

bool CScriptData::getString(std::string& a_data) const
{
	if (!m_isText){
		return false;
	}
	a_data = *m_text;
	return true;
}

bool CScriptData::operator >(const CScriptData& a_other) const
{
	return m_number > a_other.m_number;
}

bool CScriptData::operator >=(const CScriptData& a_other) const
{
	return m_number >= a_other.m_number;
}

bool CScriptData::operator <(const CScriptData& a_other) const
{
	return m_number < a_other.m_number;
}

bool CScriptData::operator <=(const CScriptData& a_other) const
{
	return m_number <= a_other.m_number;
}

bool CScriptData::operator ==(const CScriptData& a_other) const
{
	if (m_isText && a_other.m_isText){
		return *m_text == *a_other.m_text;
	}
	return m_number == a_other.m_number;
}

bool CScriptData::operator !=(const CScriptData& a_other) const
{
	if (m_isText && a_other.m_isText){
		return *m_text != *a_other.m_text;
	}
	return m_number != a_other.m_number;
}

const CScriptData& CScriptData::operator =(const CScriptData& a_other)
{
	if (a_other.m_isText){
		setString(*a_other.m_text);
		return *this;
	}
	setInt64(a_other.m_number);
	return *this;
}

//////////////////////////////////////////////////////////////////////////
class CLogicExpressAND : public IScript
{
public:
	CLogicExpressAND(const std::string& a_scriptText) : m_scriptText(a_scriptText) {}

	virtual bool execute(CScriptObject* a_scriptObject, bool& a_scriptResult)
	{
		if (m_subScriptList.size() <= 0) {
			BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本[%s]失败", m_scriptText.c_str());
			return false;
		}
		
		for (BSLib::uint32 i=0; i<m_subScriptList.size(); ++i) {
			if (m_subScriptList[i] == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本[%s]失败", m_scriptText.c_str());
				return false;
			}
			bool scriptResult = false;
			if (!m_subScriptList[i]->execute(a_scriptObject, scriptResult))	{
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本[%s]失败", m_scriptText.c_str());
				return false;
			}
			if (!scriptResult){
				a_scriptResult = false;
				return true;
			}
		}
		a_scriptResult = true;
		return true;
	}

	std::string m_scriptText;
	std::vector<IScriptPtr> m_subScriptList;
};

class CLogicExpressOR : public IScript
{
public:
	CLogicExpressOR(const std::string& a_scriptText) : m_scriptText(a_scriptText) {}

	virtual bool execute(CScriptObject* a_scriptObject, bool& a_scriptResult)
	{
		if (m_subScriptList.size() <= 0) {
			BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本[%s]失败", m_scriptText.c_str());
			return false;
		}
		
		for (BSLib::uint32 i=0; i<m_subScriptList.size(); ++i) {
			if (m_subScriptList[i] == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本[%s]失败", m_scriptText.c_str());
				return false;
			}
			bool scriptResult = false;
			if (!m_subScriptList[i]->execute(a_scriptObject, scriptResult))	{
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本[%s]失败", m_scriptText.c_str());
				return false;
			}
			if (scriptResult){
				a_scriptResult = true;
				return true;
			}
		}
		a_scriptResult = false;
		return true;
	}
	std::string m_scriptText;
	std::vector<IScriptPtr> m_subScriptList;
};

class CLogicExpressNOTAND : public IScript
{
public:
	CLogicExpressNOTAND(const std::string& a_scriptText) : m_scriptText(a_scriptText) {}

	virtual bool execute(CScriptObject* a_scriptObject, bool& a_scriptResult)
	{
		if (m_subScriptList.size() <= 0) {
			BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本[%s]失败", m_scriptText.c_str());
			return false;
		}
		
		for (BSLib::uint32 i=0; i<m_subScriptList.size(); ++i) {
			if (m_subScriptList[i] == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本[%s]失败", m_scriptText.c_str());
				return false;
			}
			bool scriptResult = false;
			if (!m_subScriptList[i]->execute(a_scriptObject, scriptResult))	{
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本[%s]失败", m_scriptText.c_str());
				return false;
			}
			if (!scriptResult){
				a_scriptResult = true;
				return true;
			}
		}
		a_scriptResult = false;
		return true;
	}

	std::string m_scriptText;
	std::vector<IScriptPtr> m_subScriptList;
};

class CLogicExpressNOTOR : public IScript
{
public:
	CLogicExpressNOTOR(const std::string& a_scriptText) : m_scriptText(a_scriptText) {}

	virtual bool execute(CScriptObject* a_scriptObject, bool& a_scriptResult)
	{
		if (m_subScriptList.size() <= 0) {
			BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本[%s]失败", m_scriptText.c_str());
			return false;
		}
		
		for (BSLib::uint32 i=0; i<m_subScriptList.size(); ++i) {
			if (m_subScriptList[i] == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本[%s]失败", m_scriptText.c_str());
				return false;
			}
			bool scriptResult = false;
			if (!m_subScriptList[i]->execute(a_scriptObject, scriptResult))	{
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本[%s]失败", m_scriptText.c_str());
				return false;
			}
			if (scriptResult){
				a_scriptResult = false;
				return true;
			}
		}
		a_scriptResult = true;
		return true;
	}
	std::string m_scriptText;
	std::vector<IScriptPtr> m_subScriptList;
};

class CRelationExpressG : public IScript
{
public:
	CRelationExpressG(const std::string& a_firstFunctionText, const std::string& a_secondFunctionText) 
		: m_firstFunctionText(a_firstFunctionText)
		, m_secondFunctionText(a_secondFunctionText) {}

	virtual bool execute(CScriptObject* a_scriptObject, bool& a_scriptResult)
	{
		CScriptData firstParameter;
		CScriptData secondParameter;

		if (m_firstFunction != NULL) {
			if (!m_firstFunction->execute(a_scriptObject, &firstParameter)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_firstFunctionText.c_str());
				return false;
			}
		}
		if (m_secondFunction != NULL) {
			if (!m_secondFunction->execute(a_scriptObject, &secondParameter)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_secondFunctionText.c_str());
				return false;
			}
		}
		a_scriptResult = firstParameter > secondParameter;
		return true;
	}

	std::string m_firstFunctionText;
	std::string m_secondFunctionText;
	IScriptFunctionPtr m_firstFunction;
	IScriptFunctionPtr m_secondFunction;
};

class CRelationExpressGE : public IScript
{
public:
	CRelationExpressGE(const std::string& a_firstFunctionText, const std::string& a_secondFunctionText) 
		: m_firstFunctionText(a_firstFunctionText)
		, m_secondFunctionText(a_secondFunctionText) {}

	virtual bool execute(CScriptObject* a_scriptObject, bool& a_scriptResult)
	{
		CScriptData firstParameter;
		CScriptData secondParameter;

		if (m_firstFunction != NULL) {
			if (!m_firstFunction->execute(a_scriptObject, &firstParameter)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_firstFunctionText.c_str());
				return false;
			}
		}
		if (m_secondFunction != NULL) {
			if (!m_secondFunction->execute(a_scriptObject, &secondParameter)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_secondFunctionText.c_str());
				return false;
			}
		}
		a_scriptResult = firstParameter >= secondParameter;
		return true;
	}

	std::string m_firstFunctionText;
	std::string m_secondFunctionText;
	IScriptFunctionPtr m_firstFunction;
	IScriptFunctionPtr m_secondFunction;
};

class CRelationExpressL : public IScript
{
public:
	CRelationExpressL(const std::string& a_firstFunctionText, const std::string& a_secondFunctionText) 
		: m_firstFunctionText(a_firstFunctionText)
		, m_secondFunctionText(a_secondFunctionText) {}

	virtual bool execute(CScriptObject* a_scriptObject, bool& a_scriptResult)
	{
		CScriptData firstParameter;
		CScriptData secondParameter;

		if (m_firstFunction != NULL) {
			if (!m_firstFunction->execute(a_scriptObject, &firstParameter)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_firstFunctionText.c_str());
				return false;
			}
		}
		if (m_secondFunction != NULL) {
			if (!m_secondFunction->execute(a_scriptObject, &secondParameter)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_secondFunctionText.c_str());
				return false;
			}
		}
		a_scriptResult = firstParameter < secondParameter;
		return true;
	}

	std::string m_firstFunctionText;
	std::string m_secondFunctionText;
	IScriptFunctionPtr m_firstFunction;
	IScriptFunctionPtr m_secondFunction;
};

class CRelationExpressLE : public IScript
{
public:
	CRelationExpressLE(const std::string& a_firstFunctionText, const std::string& a_secondFunctionText) 
		: m_firstFunctionText(a_firstFunctionText)
		, m_secondFunctionText(a_secondFunctionText) {}

	virtual bool execute(CScriptObject* a_scriptObject, bool& a_scriptResult)
	{
		CScriptData firstParameter;
		CScriptData secondParameter;

		if (m_firstFunction != NULL) {
			if (!m_firstFunction->execute(a_scriptObject, &firstParameter)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_firstFunctionText.c_str());
				return false;
			}
		}
		if (m_secondFunction != NULL) {
			if (!m_secondFunction->execute(a_scriptObject, &secondParameter)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_secondFunctionText.c_str());
				return false;
			}
		}
		a_scriptResult = firstParameter > secondParameter;
		return true;
	}

	std::string m_firstFunctionText;
	std::string m_secondFunctionText;
	IScriptFunctionPtr m_firstFunction;
	IScriptFunctionPtr m_secondFunction;
};

class CRelationExpressE : public IScript
{
public:
	CRelationExpressE(const std::string& a_firstFunctionText, const std::string& a_secondFunctionText) 
		: m_firstFunctionText(a_firstFunctionText)
		, m_secondFunctionText(a_secondFunctionText) {}

	virtual bool execute(CScriptObject* a_scriptObject, bool& a_scriptResult)
	{
		CScriptData firstParameter;
		CScriptData secondParameter;

		if (m_firstFunction != NULL) {
			if (!m_firstFunction->execute(a_scriptObject, &firstParameter)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_firstFunctionText.c_str());
				return false;
			}
		}
		if (m_secondFunction != NULL) {
			if (!m_secondFunction->execute(a_scriptObject, &secondParameter)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_secondFunctionText.c_str());
				return false;
			}
		}
		a_scriptResult = firstParameter == secondParameter;
		return true;
	}

	std::string m_firstFunctionText;
	std::string m_secondFunctionText;
	IScriptFunctionPtr m_firstFunction;
	IScriptFunctionPtr m_secondFunction;
};

class CRelationExpressNE : public IScript
{
public:
	CRelationExpressNE(const std::string& a_firstFunctionText, const std::string& a_secondFunctionText) 
		: m_firstFunctionText(a_firstFunctionText)
		, m_secondFunctionText(a_secondFunctionText) {}

	virtual bool execute(CScriptObject* a_scriptObject, bool& a_scriptResult)
	{
		CScriptData firstParameter;
		CScriptData secondParameter;

		if (m_firstFunction != NULL) {
			if (!m_firstFunction->execute(a_scriptObject, &firstParameter)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_firstFunctionText.c_str());
				return false;
			}
		}
		if (m_secondFunction != NULL) {
			if (!m_secondFunction->execute(a_scriptObject, &secondParameter)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_secondFunctionText.c_str());
				return false;
			}
		}
		a_scriptResult = firstParameter != secondParameter;
		return true;
	}

	std::string m_firstFunctionText;
	std::string m_secondFunctionText;
	IScriptFunctionPtr m_firstFunction;
	IScriptFunctionPtr m_secondFunction;
};

//////////////////////////////////////////////////////////////////////////

class CScriptFunction : public IScriptFunction
{
public:
	CScriptFunction(const std::string& a_scriptText) : m_scriptText(a_scriptText) {}

	virtual bool execute(CScriptObject* a_scriptObject, CScriptData* a_functionResult)
	{
		if (m_subScriptFunctionList.size() != m_scriptFunctionParamentList.size()){
			BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_scriptText.c_str());
			return false;
		}
		for (BSLib::uint32 i=0; i<m_subScriptFunctionList.size(); ++i) {
			if (m_subScriptFunctionList[i] == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_scriptText.c_str());
				return false;
			}
			if (!m_subScriptFunctionList[i]->execute(a_scriptObject, &m_scriptFunctionParamentList[i])) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_scriptText.c_str());
				return false;
			}
		}
		return a_scriptObject->executeFunction(m_scriptFunctionIndex, m_scriptFunctionParamentList, a_functionResult);
	}

	std::string m_scriptText;
	BSLib::uint32 m_scriptFunctionIndex;
	std::vector<IScriptFunctionPtr> m_subScriptFunctionList;
	std::vector<CScriptData> m_scriptFunctionParamentList;
};

class CScriptVariation : public IScriptFunction
{
public:
	virtual bool execute(CScriptObject* a_scriptObject, CScriptData* a_functionResult)
	{
		return a_scriptObject->getVariation(m_scriptVariableIndex, a_functionResult);
	}

	BSLib::uint32 m_scriptVariableIndex;
};

class CScriptConstant : public IScriptFunction
{
public:
	virtual bool execute(CScriptObject* a_scriptObject, CScriptData* a_functionResult)
	{
		*a_functionResult = m_scriptData;
		return true;
	}

	CScriptData m_scriptData;
};

//////////////////////////////////////////////////////////////////////////
class CScripFunctionList : public IScriptFunctionList
{
public:
	CScripFunctionList(const std::string& a_scriptText) : m_scriptText(a_scriptText) {}
	virtual ~CScripFunctionList() {}

	virtual bool execute(CScriptObject* a_scriptObject, CScriptData* a_functionResult)
	{
		std::vector<IScriptFunctionPtr>::iterator it = m_scriptFunctionList.begin();
		for (; it != m_scriptFunctionList.end(); ++it) {
			IScriptFunctionPtr& scriptFuncPtr = *it;
			if (scriptFuncPtr == NULL) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_scriptText.c_str());
				return false;
			}
			if (!scriptFuncPtr->execute(a_scriptObject, a_functionResult)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行函数[%s]失败", m_scriptText.c_str());
				return false;
			}
		}
		return true;
	}

	std::string m_scriptText;
	std::vector<IScriptFunctionPtr> m_scriptFunctionList;
};
typedef CPointer<IScriptFunctionList> IScriptFunctionListPtr;

//////////////////////////////////////////////////////////////////////////
CScriptEnvironment::CScriptEnvironment()
{
}

CScriptEnvironment::~CScriptEnvironment()
{
}

IScriptPtr CScriptEnvironment::parseExpression(const std::string& a_textExpression)
{
	BSLib::Utility::CStringA scriptText = a_textExpression;
	scriptText.trim();

	IScriptPtr scriptPtr = NULL;
	if (scriptText.size() <= 0) {
		return scriptPtr;
	}

	if (scriptText[0] == '[') {
		return _parseLogicText(scriptText);
	}
	return _parseRelationText(scriptText);
}

IScriptFunctionPtr CScriptEnvironment::parseFunction(const std::string& a_textFunction)
{
	if (a_textFunction.size() <= 0) {
		return IScriptFunctionPtr(NULL);
	}
	IScriptFunctionPtr scriptFunctionPtr = NULL;
	if (a_textFunction[0] == '$'){
		BSLib::uint32 index = 0;
		std::string name = a_textFunction.substr(1, a_textFunction.size()-1);
		if (!_getVariableIndex(name, &index)) {
			return IScriptFunctionPtr(NULL);
		}
		CScriptVariation* scriptVariable = new CScriptVariation();
		if (scriptVariable == NULL)	{
			return IScriptFunctionPtr(NULL);
		}
		scriptVariable->m_scriptVariableIndex = index;
		scriptFunctionPtr = scriptVariable;
		return scriptFunctionPtr;
		//变量
	} else if (a_textFunction[0] == '"' || a_textFunction[0] == '\''){
		size_t end = a_textFunction.size();
		if (end <= 1 || a_textFunction[end-1] != a_textFunction[0]){
			return IScriptFunctionPtr(NULL);
		}
		std::string strValue = a_textFunction.substr(1, a_textFunction.size()-2);
		CScriptConstant* scriptConstant = new CScriptConstant();
		if (scriptConstant == NULL)	{
			return IScriptFunctionPtr(NULL);
		}
		scriptConstant->m_scriptData.setString(strValue);
		scriptFunctionPtr = scriptConstant;
		return scriptFunctionPtr;
		//字符常量
	} else if (a_textFunction[0] >= '0' && a_textFunction[0] <= '9'){
		//数字常量
		BSLib::int64 dataValue = BSLib::Utility::CConvert::toInt64(a_textFunction);
		CScriptConstant* scriptConstant = new CScriptConstant();
		if (scriptConstant == NULL)	{
			return IScriptFunctionPtr(NULL);
		}
		scriptConstant->m_scriptData.setInt64(dataValue);
		scriptFunctionPtr = scriptConstant;
		return scriptFunctionPtr;
	} 
	//函数
	BSLib::Utility::CStringA functionName;
	BSLib::uint32 pos = 0;
	for (; pos < a_textFunction.size(); ++pos){
		char ch = a_textFunction[pos];
		if (ch == '('){
			++pos;
			break;
		}
		functionName.push_back(ch);
	}
	functionName.trim();
	BSLib::uint32 functionIndex = 0;
	if (!_getFunctionIndex(functionName, &functionIndex)) {
		return IScriptFunctionPtr(NULL);
	}
	CScriptFunction* scriptFunction = new CScriptFunction(a_textFunction);
	if (scriptFunction == NULL)	{
		return IScriptFunctionPtr(NULL);
	}
	scriptFunction->m_scriptFunctionIndex = functionIndex;
	scriptFunctionPtr = scriptFunction;

	std::vector<BSLib::Utility::CStringA> parameterList;
	BSLib::Utility::CStringA temp;
	int count = 1;
	bool flag = false;
	for (; pos < a_textFunction.size(); ++pos) {
		char ch = a_textFunction[pos];
		if (ch == ',' && !flag && count == 1 ){
			temp.trim();
			if (!temp.empty()) {
				parameterList.push_back(temp);
				temp.clear();
			}
			continue;
		} else if (ch == '(' && !flag) {
			++count;
		} else if (ch == ')' && !flag){
			--count;
			if (count <= 0) {
				break;
			}
		} else if (ch == '"') {
			flag = !flag;
		}
		temp.push_back(ch);
	}
	temp.trim();
	if (!temp.empty()) {
		parameterList.push_back(temp);
		temp.clear();
	}
	if (parameterList.size() <= 0){
		return scriptFunctionPtr;
	}
	for (BSLib::uint32 i=0; i<parameterList.size(); ++i) {
		IScriptFunctionPtr paramenterPtr = parseFunction(parameterList[i]);
		if (paramenterPtr == NULL)	{
			return IScriptFunctionPtr(NULL);
		}
		scriptFunction->m_subScriptFunctionList.push_back(paramenterPtr);
		
	}
	scriptFunction->m_scriptFunctionParamentList.resize(scriptFunction->m_subScriptFunctionList.size());
	return scriptFunctionPtr;
}

IScriptFunctionListPtr CScriptEnvironment::parseFunctionList(const std::string& a_textFunction)
{
	BSLib::Utility::CStringA textFunction = a_textFunction;
	std::vector<BSLib::Utility::CStringA> subTextFunctionList;
	if (textFunction.split(subTextFunctionList, ';') <= 0) {
		return IScriptFunctionListPtr(NULL);
	}
	CScripFunctionList* scriptFunctionList = new CScripFunctionList(a_textFunction);
	if (scriptFunctionList == NULL) {
		return IScriptFunctionListPtr(NULL);
	}
	for (BSLib::uint32 i=0; i<subTextFunctionList.size(); ++i) {
		IScriptFunctionPtr scriptFunctionPtr = parseFunction(subTextFunctionList[i]);
		if (scriptFunctionPtr == NULL) {
			BSLIB_SAFE_DELETE(scriptFunctionList);
			return IScriptFunctionListPtr(NULL);
		}
		scriptFunctionList->m_scriptFunctionList.push_back(scriptFunctionPtr);
	}
	return IScriptFunctionListPtr(scriptFunctionList);
}

bool CScriptEnvironment::getVariation(BSLib::uint32 a_variableIndex, CScriptData* scriptData)
{
	BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "脚本变量不存在[FunctionIndex=%d]", a_variableIndex);
	return false;
}

bool CScriptEnvironment::executeFunction(BSLib::uint32 a_functionIndex, std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult)
{
	switch (a_functionIndex) {
	case ESCRIPT_FUNCINDEX_TRACE:
		return _executeFunctionTrace(a_functionParamenterList, a_functionResult);
	case ESCRIPT_FUNCINDEX_ADDNUMBER:
		return _executeFunctionAddNumber(a_functionParamenterList, a_functionResult);
	case ESCRIPT_FUNCINDEX_ADDSTRING:
		return _executeFunctionAddString(a_functionParamenterList, a_functionResult);
	case ESCRIPT_FUNCINDEX_RANDOMNUMBER:
		return _executeFunctionAddString(a_functionParamenterList, a_functionResult);
	case ESCRIPT_FUNCINDEX_GETGLOBALDATA:
		return _executeFunctionGetGlobalData(a_functionParamenterList, a_functionResult);
	case ESCRIPT_FUNCINDEX_SETGLOBALDATA:
		return _executeFunctionSetGlobalData(a_functionParamenterList, a_functionResult);
	default:
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "脚本函数不存在[FunctionIndex=%d]", a_functionIndex);
	}
	return false;
}

bool CScriptEnvironment::_getVariableIndex(const std::string& a_nameVariable, BSLib::uint32* a_index)
{
	if (m_variableIndexHashMap.getValue(a_nameVariable, *a_index)) {
		return true;
	}
	BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "脚本变量不存在[VariableName=%s]", a_nameVariable.c_str());
	return false;
}

bool CScriptEnvironment::_getFunctionIndex(const std::string& a_nameFunction, BSLib::uint32* a_index)
{
	if (m_functionIndexHashMap.getValue(a_nameFunction, *a_index)) {
		return true;
	}
	BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "脚本函数不存在[VariableName=%s]", a_nameFunction.c_str());
	return false;
}

void CScriptEnvironment::_init()
{
	m_functionIndexHashMap.setValue("Trace", ESCRIPT_FUNCINDEX_TRACE);
	m_functionIndexHashMap.setValue("AddNumber", ESCRIPT_FUNCINDEX_ADDNUMBER);
	m_functionIndexHashMap.setValue("AddString", ESCRIPT_FUNCINDEX_ADDSTRING);
	m_functionIndexHashMap.setValue("RandomNumber", ESCRIPT_FUNCINDEX_RANDOMNUMBER);
	m_functionIndexHashMap.setValue("GetGlobalData", ESCRIPT_FUNCINDEX_GETGLOBALDATA);
	m_functionIndexHashMap.setValue("SetGlobalData", ESCRIPT_FUNCINDEX_SETGLOBALDATA);
}

bool CScriptEnvironment::_addVariableIndex(const std::string& a_nameVariable, BSLib::uint32 a_variableIndex)
{
	if (m_variableIndexHashMap.find(a_nameVariable) != m_variableIndexHashMap.end()) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "脚本变量重复定义[FunctionIndex=%d]", a_nameVariable.c_str());
		return false;
	}
	m_variableIndexHashMap.setValue(a_nameVariable, a_variableIndex);
	return true;
}

bool CScriptEnvironment::_addFunctionIndex(const std::string& a_nameFunction, BSLib::uint32 a_functionIndex)
{
	if (m_functionIndexHashMap.find(a_nameFunction) != m_functionIndexHashMap.end()) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "脚本函数重复定义[FunctionIndex=%d]", a_nameFunction.c_str());
		return false;
	}
	m_functionIndexHashMap.setValue(a_nameFunction, a_functionIndex);
	return true;
}

IScriptPtr CScriptEnvironment::_parseLogicText(const std::string& a_textExpression)
{
	BSLib::Utility::CStringA logicType;
	BSLib::uint32 pos = 1;
	while (pos < a_textExpression.size()){
		char ch = a_textExpression[pos];
		if (ch == ' '  && !logicType.empty()){
			++pos;
			break;
		}
		logicType.push_back(ch);
		++pos;
	}
	logicType.trim();
	logicType.toUpper();

	IScriptPtr scriptPtr = NULL;
	std::vector<IScriptPtr>* subScriptList = NULL;
	if (logicType == "AND"){
		CLogicExpressAND* expression = new CLogicExpressAND(a_textExpression);
		if (expression == NULL) {
			return false;
		}
		scriptPtr = expression;
		subScriptList = &expression->m_subScriptList;
	} else if (logicType == "OR"){
		CLogicExpressOR* expression = new CLogicExpressOR(a_textExpression);
		if (expression == NULL) {
			return false;
		}
		scriptPtr = expression;
		subScriptList = &expression->m_subScriptList;
	} else if (logicType == "NOTAND") {
		CLogicExpressNOTAND* expression = new CLogicExpressNOTAND(a_textExpression);
		if (scriptPtr == NULL) {
			return false;
		}
		scriptPtr = expression;
		subScriptList = &expression->m_subScriptList;
	} else if (logicType == "NOTOR") {
		CLogicExpressNOTOR* expression = new CLogicExpressNOTOR(a_textExpression);
		if (scriptPtr == NULL) {
			return false;
		}
		scriptPtr = expression;
		subScriptList = &expression->m_subScriptList;
	} else {
		return IScriptPtr(NULL);
	}

	std::vector<BSLib::Utility::CStringA> subExpressionList;
	BSLib::Utility::CStringA temp;
	int count = 1;
	bool flag = false;
	for (; pos < a_textExpression.size(); ++pos) {
		char ch = a_textExpression[pos];
		if (ch == ',' && !flag && count == 1){
			temp.trim();
			if (!temp.empty()) {
				subExpressionList.push_back(temp);
				temp.clear();
			}
			continue;
		} else if ((ch == '[' || ch =='(') && !flag) {
			++count;
		} else if ((ch == ']' || ch == ')') && !flag){
			--count;
			if (count <= 0){
				break;
			}
		} else if (ch == '"') {
			flag = !flag;
		}
		temp.push_back(ch);
	}
	temp.trim();
	if (!temp.empty()) {
		subExpressionList.push_back(temp);
		temp.clear();
	}
	if (subExpressionList.size() <= 0){
		return IScriptPtr(NULL);
	}
	for (BSLib::uint32 i=0; i<subExpressionList.size(); ++i){
		IScriptPtr subScriptPtr = NULL;
		subScriptPtr = parseExpression(subExpressionList[i]);
		if (subScriptPtr == NULL){
			return IScriptPtr(NULL);
		}
		subScriptList->push_back(subScriptPtr);
	}
	if (subScriptList->size() <= 0){
		return IScriptPtr(NULL);
	}
	return scriptPtr;
}

IScriptPtr CScriptEnvironment::_parseRelationText(const std::string& a_textExpression)
{
	std::vector<BSLib::Utility::CStringA> subExpressionList;
	BSLib::Utility::CStringA temp;
	int count = 0;
	bool flag = false;
	for (BSLib::uint32 pos = 0; pos < a_textExpression.size(); ++pos) {
		char ch = a_textExpression[pos];
		if (ch == ' ' && !flag && count == 0 ){
			temp.trim();
			if (!temp.empty()) {
				subExpressionList.push_back(temp);
				temp.clear();
			}
			continue;
		} else if (ch == '(' && !flag) {
			++count;
		} else if (ch == ')' && !flag){
			--count;
			if (count < 0) {
				return IScriptPtr(NULL);
			}
		} else if (ch == '"') {
			flag = !flag;
		}
		temp.push_back(ch);
	}
	temp.trim();
	if (!temp.empty()) {
		subExpressionList.push_back(temp);
		temp.clear();
	}
	if (subExpressionList.size() != 3){
		return IScriptPtr(NULL);
	}
	
	IScriptFunctionPtr firstFunction = parseFunction(subExpressionList[0]);
	IScriptFunctionPtr secondFunction = parseFunction(subExpressionList[2]);
	if (firstFunction == NULL){
		return IScriptPtr(NULL);
	}
	if (secondFunction == NULL){
		return IScriptPtr(NULL);
	}
	IScriptPtr scriptPtr = NULL;
	subExpressionList[1].toUpper();
	if (subExpressionList[1] == "G") {
		CRelationExpressG* express = new CRelationExpressG(subExpressionList[0], subExpressionList[2]);
		if (express == NULL) {
			return IScriptPtr(NULL);
		}
		express->m_firstFunction = firstFunction;
		express->m_secondFunction = secondFunction;
		scriptPtr = express;
	} else if (subExpressionList[1] == "GE") {
		CRelationExpressGE* express = new CRelationExpressGE(subExpressionList[0], subExpressionList[2]);
		if (express == NULL) {
			return IScriptPtr(NULL);
		}
		express->m_firstFunction = firstFunction;
		express->m_secondFunction = secondFunction;
		scriptPtr = express;
	} else if (subExpressionList[1] == "L") {
		CRelationExpressL* express = new CRelationExpressL(subExpressionList[0], subExpressionList[2]);
		if (express == NULL) {
			return IScriptPtr(NULL);
		}
		express->m_firstFunction = firstFunction;
		express->m_secondFunction = secondFunction;
		scriptPtr = express;
	} else if (subExpressionList[1] == "LE") {
		CRelationExpressLE* express = new CRelationExpressLE(subExpressionList[0], subExpressionList[2]);
		if (express == NULL) {
			return IScriptPtr(NULL);
		}
		express->m_firstFunction = firstFunction;
		express->m_secondFunction = secondFunction;
		scriptPtr = express;
	} else if (subExpressionList[1] == "E") {
		CRelationExpressE* express = new CRelationExpressE(subExpressionList[0], subExpressionList[2]);
		if (express == NULL) {
			return IScriptPtr(NULL);
		}
		express->m_firstFunction = firstFunction;
		express->m_secondFunction = secondFunction;
		scriptPtr = express;
	} else if (subExpressionList[1] == "NE") {
		CRelationExpressNE* express = new CRelationExpressNE(subExpressionList[0], subExpressionList[2]);
		if (express == NULL) {
			return IScriptPtr(NULL);
		}
		express->m_firstFunction = firstFunction;
		express->m_secondFunction = secondFunction;
		scriptPtr = express;
	} else {
		return IScriptPtr(NULL);
	}
	return scriptPtr;
}

bool CScriptEnvironment::_executeFunctionTrace(std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult)
{
	BSLib::Utility::CStringA strTrace = "";
	std::vector<CScriptData>::iterator it = a_functionParamenterList.begin();
	for (; it != a_functionParamenterList.end(); ++it) {
		CScriptData& scriptData = *it;
		if (scriptData.isText()) {
			std::string strValue = "";
			if (!scriptData.getString(strValue)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本指令[Trace]失败");
				a_functionResult->setInt32(0);
				return false;
			}
			strTrace << strValue;
		} else {
			BSLib::int64 data = 0;
			if (!scriptData.getInt64(data)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本指令[Trace]失败");
				a_functionResult->setInt32(0);
				return false;
			}
			strTrace << data;
		}
	}
	BSLIB_LOG_TRACE(ETT_BSLIB_UTILITY, "%s", strTrace.c_str());
	a_functionResult->setInt32(1);
	return true;
}

bool CScriptEnvironment::_executeFunctionAddNumber(std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult)
{
	BSLib::int64 count = 0;
	std::vector<CScriptData>::iterator it = a_functionParamenterList.begin();
	for (; it != a_functionParamenterList.end(); ++it) {
		CScriptData& scriptData = *it;
		if (scriptData.isText()) {
			BSLib::int64 data = 0;
			BSLib::Utility::CStringA strValue = "";
			if (!scriptData.getString(strValue)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本指令[AddNumber]失败");
				return false;
			}
			strValue >> data;
			count += data;
		} else {
			BSLib::int64 data = 0;
			if (!scriptData.getInt64(data)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本指令[AddNumber]失败");
				return false;
			}
			count += data;
		}
	}
	a_functionResult->setInt64(count);
	return true;
}

bool CScriptEnvironment::_executeFunctionAddString(std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult)
{
	BSLib::Utility::CStringA strTrace = "";
	std::vector<CScriptData>::iterator it = a_functionParamenterList.begin();
	for (; it != a_functionParamenterList.end(); ++it) {
		CScriptData& scriptData = *it;
		if (scriptData.isText()) {
			std::string strValue = "";
			if (!scriptData.getString(strValue)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本指令[AddString]失败");
				a_functionResult->setString("");
				return false;
			}
			strTrace << strValue;
		} else {
			BSLib::int64 data = 0;
			if (!scriptData.getInt64(data)) {
				BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本指令[AddString]失败");
				a_functionResult->setString("");
				return false;
			}
			strTrace << data;
		}
	}
	a_functionResult->setString(strTrace);
	return true;
}

bool CScriptEnvironment::_executeFunctionRandomNumber(std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult)
{
	if (a_functionParamenterList.size() != 2) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本指令[RandomNumber]失败, 参数不正确");
		return false;
	}
	BSLib::int32 num1 = 0;
	if (a_functionParamenterList[0].getInt32(num1)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本指令[RandomNumber]失败, 获取参数1无效");
		return false;
	}
	BSLib::int32 num2 = 0;
	if (a_functionParamenterList[1].getInt32(num2)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "执行脚本指令[RandomNumber]失败, 获取参数1无效");
		return false;
	}
	BSLib::int32 randomValue = BSLib::Utility::CRandom::randomBetween(num1, num2);
	a_functionResult->setInt32(randomValue);
	return true;
}

bool CScriptEnvironment::_executeFunctionGetGlobalData(std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult)
{
	if (a_functionParamenterList.size() != 1) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "脚本执行GetGlobalData函数失败,参数无效");
		a_functionResult->setInt32(0);
		return false;
	}
	std::string dataName;
	if (!a_functionParamenterList[0].getString(dataName)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "脚本执行GetGlobalData函数失败,参数1无效");
		a_functionResult->setInt32(0);
		return false;
	}
	BSLib::Utility::CScriptData* scriptData = NULL;
	m_globalDataHashMap.getValue(dataName, scriptData);
	if (scriptData == NULL) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "脚本执行GetGlobalData函数失败,参数[%s]不存在", dataName.c_str());
		a_functionResult->setInt32(0);
		return false;
	}
	*a_functionResult = *scriptData;
	return true;
}

bool CScriptEnvironment::_executeFunctionSetGlobalData(std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult)
{
	if (a_functionParamenterList.size() != 2) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "脚本执行SetGlobalData函数失败,参数无效");
		a_functionResult->setInt32(0);
		return false;
	}
	std::string dataName;
	if (!a_functionParamenterList[0].getString(dataName)) {
		BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "脚本执行SetGlobalData函数失败,参数1无效");
		a_functionResult->setInt32(0);
		return false;
	}
	BSLib::Utility::CScriptData* scriptData = NULL;
	m_globalDataHashMap.getValue(dataName, scriptData);
	if (scriptData == NULL) {
		scriptData = new BSLib::Utility::CScriptData();
		if (scriptData == NULL) {
			BSLIB_LOG_ERROR(ETT_BSLIB_UTILITY, "脚本执行SetGlobalData函数失败,参数[%s]无效", dataName.c_str());
			a_functionResult->setInt32(0);
			return false;
		}
		m_globalDataHashMap.setValue(dataName, scriptData);
	}
	*scriptData = a_functionParamenterList[1];
	a_functionResult->setInt32(1);
	return true;
}

}//Utility

}//BSLib


