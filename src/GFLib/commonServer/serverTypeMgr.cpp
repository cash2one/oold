#include <BSLib/utility/string.h>
#include <GFLib/commonServer/serverTypeMgr.h>

namespace GFLib
{

namespace CommonServer
{

#define SERVERTYPE_MAX (BSLIB_UINT8_MAX + 1)

struct SServerTypeInfor 
{
	ServerType m_msgServerType;
	std::string m_msgServerText;
	std::string m_msgServerCode;

	SServerTypeInfor(ServerType type, const std::string& text, const std::string& code) : m_msgServerType(type), m_msgServerText(text), m_msgServerCode(code)
	{
		;
	}

	void setServerTypeInfor(ServerType type, const std::string& text, const std::string& code)
	{
		m_msgServerType = type;
		m_msgServerText = text;
		m_msgServerCode = code;
	}

	void setServerTypeInfor(SServerTypeInfor& serverTypeInfor)
	{
		m_msgServerType = serverTypeInfor.m_msgServerType;
		m_msgServerText = serverTypeInfor.m_msgServerText;
		m_msgServerCode = serverTypeInfor.m_msgServerCode;
	}
};

SServerTypeInfor* g_serverTypeTable[SERVERTYPE_MAX];

BSLIB_SINGLETON_DEFINE(CServerTypeMgr)

CServerTypeMgr::CServerTypeMgr()
{
	for (int i=0; i<SERVERTYPE_MAX; ++i) {
		g_serverTypeTable[i] = NULL;
	}
	setServerType(SRVTYPE_NULL, "Unkown", "");
	setServerType(SRVTYPE_LOCAL, "Local", "LC");
	setServerType(SRVTYPE_ANY, "AnyOne", "XX");
	setServerType(SRVTYPE_ANYSERVER, "AnyServer", "XS");
}

CServerTypeMgr::~CServerTypeMgr()
{
	for (int i=0; i<SERVERTYPE_MAX; ++i) {
		if (g_serverTypeTable[i] != NULL) {
			BSLIB_SAFE_DELETE(g_serverTypeTable[i]);
		}
	}
}

const std::string& CServerTypeMgr::getTextServerType(ServerType type)
{
	static std::string tmp = "Unkown";
	if (g_serverTypeTable[type] == NULL) {
		return tmp;
	}
	return g_serverTypeTable[type]->m_msgServerText;
}

const std::string& CServerTypeMgr::getCodeServerType(ServerType type)
{
	static std::string tmp = "";
	if (g_serverTypeTable[type] == NULL) {
		return tmp;
	}
	return g_serverTypeTable[type]->m_msgServerCode;
}

ServerType CServerTypeMgr::getServerTypeByText(const std::string& text)
{
	BSLib::Utility::CStringA tmpText = text;
	tmpText.toLower();

	for (int i=0; i<SERVERTYPE_MAX; ++i){
		if (g_serverTypeTable[i] == NULL) {
			continue;
		}
		BSLib::Utility::CStringA msgText = g_serverTypeTable[i]->m_msgServerText;
		msgText.toLower();

		if (msgText == tmpText)	{
			return g_serverTypeTable[i]->m_msgServerType;
		}
	}
	return SRVTYPE_NULL;
}

ServerType CServerTypeMgr::getServerTypeByCode(const std::string& code)
{
	BSLib::Utility::CStringA tmpCode = code;
	tmpCode.toLower();

	for (int i=0; i<SERVERTYPE_MAX; ++i){
		if (g_serverTypeTable[i] == NULL) {
			continue;
		}
		BSLib::Utility::CStringA msgCode = g_serverTypeTable[i]->m_msgServerCode;
		msgCode.toLower();

		if (msgCode == tmpCode)	{
			return g_serverTypeTable[i]->m_msgServerType;
		}
	}
	return SRVTYPE_NULL;
}

void CServerTypeMgr::setServerType(ServerType type, const std::string& text, const std::string& code)
{
	if (g_serverTypeTable[type] == NULL) {
		g_serverTypeTable[type] = new SServerTypeInfor(type, text, code);
		return;
	}
	g_serverTypeTable[type]->setServerTypeInfor(type, text, code);
}

}//CommonServer

}//GFLib



