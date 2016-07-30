#ifndef __BSLIB_UTILITY_SCRIPT_H__
#define __BSLIB_UTILITY_SCRIPT_H__

#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/baseDef.h>
#include <BSLib/utility/pointer.h>

namespace BSLib
{

namespace Utility
{

enum EVariableIndex
{
	ESCRIPT_VARIABLE_EXTEND = 1024,
};

enum EFunctionIndex
{
	ESCRIPT_FUNCINDEX_TRACE = 1,	//Trace(...);
	ESCRIPT_FUNCINDEX_ADDNUMBER,	//AddNumber(...);
	ESCRIPT_FUNCINDEX_ADDSTRING,	//AddString(...);
	ESCRIPT_FUNCINDEX_RANDOMNUMBER,	//RandomNumber(num1, num2);
	ESCRIPT_FUNCINDEX_SETGLOBALDATA,//SetGlobalData(name, data);
	ESCRIPT_FUNCINDEX_GETGLOBALDATA,//GetGlobalData(name);

	ESCRIPT_FUNCINDEX_EXTEND = 1024,
};

class CScriptObject;
class CScriptEnvironment;

//�ű�ʹ�õ�����
class CScriptData
{
public:
	CScriptData();
	CScriptData(const CScriptData& a_other);

	~CScriptData();

	bool isText() const;

	void setInt32(BSLib::int32 a_data);
	void setUInt32(BSLib::uint32 a_data);
	void setInt64(BSLib::int64 a_data);
	void setUInt64(BSLib::uint64 a_data);
	void setString(const std::string& a_data);

	bool getInt32(BSLib::int32& a_data) const;
	bool getUInt32(BSLib::uint32& a_data) const;
	bool getInt64(BSLib::int64& a_data) const;
	bool getUInt64(BSLib::uint64& a_data) const;
	bool getString(std::string& a_data) const;

	bool operator >(const CScriptData& a_other) const;
	bool operator >=(const CScriptData& a_other) const;
	bool operator <(const CScriptData& a_other) const;
	bool operator <=(const CScriptData& a_other) const;
	bool operator ==(const CScriptData& a_other) const;
	bool operator !=(const CScriptData& a_other) const;
	const CScriptData& operator =(const CScriptData& a_other);

private:
	bool m_isText;
	union
	{
		BSLib::int64 m_number;
		std::string* m_text;
	};
};

//�ű�ʹ�õĶ��󣬴Ӷ����л�ȡ�ű���Ҫ������
class CScriptObject
{
public:
	virtual ~CScriptObject(){}

	virtual bool getVariation(BSLib::uint32 a_variableIndex, CScriptData* scriptData) = 0;
	virtual bool executeFunction(BSLib::uint32 a_functionIndex, std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult) = 0;

	virtual CScriptEnvironment* getScriptEnvironment() { return NULL; }
};

//��IScript�еĺ�������
class IScriptFunction
{
public:
	virtual ~IScriptFunction() {}

	virtual bool execute(CScriptObject* a_scriptObject, CScriptData* a_functionResult) = 0;
};
typedef CPointer<IScriptFunction> IScriptFunctionPtr;

class IScriptFunctionList
{
public:
	virtual ~IScriptFunctionList() {}

	virtual bool execute(CScriptObject* a_scriptObject, CScriptData* a_functionResult) = 0;
};
typedef CPointer<IScriptFunctionList> IScriptFunctionListPtr;

// IScript = ���ʽ
// ���ʽ = ��ϵ���ʽ | �߼����ʽ

// �߼����ʽ = [�߼����� ���ʽ, ���ʽ, ����, ���ʽ]
// �߼����� = AND | OR | NOTAND | NOTOR

// ��ϵ���ʽ = ���� ��ϵ���� ����  , ����Ϊ�߼�ֵ true or false
// ��ϵ���� = G | L | E | GE | LE | NE

// ���� = ���� | ���� | ����
// ���� = ���� | "�ַ���"
// ���� = $������
// ���� = ������(����, ����,����, ����)
class IScript
{
public:
	virtual ~IScript(){}
	virtual bool execute(CScriptObject* a_scriptObject, bool& a_scriptResult) = 0;
};
typedef CPointer<IScript> IScriptPtr;

class CScriptEnvironment
{
public:
	CScriptEnvironment();
	virtual ~CScriptEnvironment();

	IScriptPtr parseExpression(const std::string& a_textExpression);
	IScriptFunctionPtr parseFunction(const std::string& a_textFunction);
	IScriptFunctionListPtr parseFunctionList(const std::string& a_textFunction);

	bool getVariation(BSLib::uint32 a_variableIndex, CScriptData* scriptData);
	bool executeFunction(BSLib::uint32 a_functionIndex, std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult);

protected:
	virtual bool _getVariableIndex(const std::string& a_nameVariable, BSLib::uint32* a_index);
	virtual bool _getFunctionIndex(const std::string& a_nameFunction, BSLib::uint32* a_index);

	void _init();
	bool _addVariableIndex(const std::string& a_nameVariable, BSLib::uint32 a_variableIndex);
	bool _addFunctionIndex(const std::string& a_nameFunction, BSLib::uint32 a_functionIndex);

private:
	IScriptPtr _parseLogicText(const std::string& a_textExpression);
	IScriptPtr _parseRelationText(const std::string& a_textExpression);

private:
	bool _executeFunctionTrace(std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult);
	bool _executeFunctionAddNumber(std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult);
	bool _executeFunctionAddString(std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult);
	bool _executeFunctionRandomNumber(std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult);
	bool _executeFunctionGetGlobalData(std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult);
	bool _executeFunctionSetGlobalData(std::vector<CScriptData>& a_functionParamenterList, CScriptData* a_functionResult);

private:
	BSLib::Utility::CHashMap<std::string, BSLib::uint32> m_variableIndexHashMap;
	BSLib::Utility::CHashMap<std::string, BSLib::uint32> m_functionIndexHashMap;

	BSLib::Utility::CHashMap<std::string, BSLib::Utility::CScriptData*> m_globalDataHashMap;
};

}//Utility

}//BSLib

#endif//__BSLIB_UTILITY_SCRIPT_H__

