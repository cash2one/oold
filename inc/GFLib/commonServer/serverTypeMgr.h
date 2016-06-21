#ifndef __GFLIB_COMMONSERVER_SERVERTYPEMGR_H__
#define __GFLIB_COMMONSERVER_SERVERTYPEMGR_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/baseDef.h>

namespace GFLib
{

namespace CommonServer
{

class GFLIB_COMMONSERVER_API CServerTypeMgr
{
public:
	BSLIB_SINGLETON_DECLARE(CServerTypeMgr)

public:
	CServerTypeMgr();
	~CServerTypeMgr();

	const std::string& getTextServerType(ServerType type);
	const std::string& getCodeServerType(ServerType type);

	ServerType getServerTypeByText(const std::string& text);
	ServerType getServerTypeByCode(const std::string& code);

	void setServerType(ServerType type, const std::string& text, const std::string& code);
};


}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_SERVERTYPEMGR_H__



