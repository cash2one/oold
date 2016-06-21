#ifndef __GFLIB_COMMONSERVER_COMMONSYSTEMMGR_H__
#define __GFLIB_COMMONSERVER_COMMONSYSTEMMGR_H__

#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>

namespace GFLib
{

namespace CommonServer
{

class GFLIB_COMMONSERVER_API CCommonSystemMgr
{
public:
	CCommonSystemMgr();
	~CCommonSystemMgr();

	BSLIB_SINGLETON_DECLARE(CCommonSystemMgr)

public:
	bool addSystem(CCommonSystem* a_commonSystem);

	CCommonSystem* getSystem(BSLib::uint16 a_funType);


	bool init(BSLib::Utility::CTimerServer* a_timerServer);
	void final();

	bool loadGameConfig(const std::string& a_configPath);
	void initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	void initCommand(BSLib::Utility::CCmdExecMgr* a_cmdExecMgr);

	bool startSystem();

	void cbServerEnter(const SServerID& a_serverID, const std::string& a_key);
	void cbServerLeave(const SServerID& a_serverID, const std::string& a_key);

private:
	bool _prepStartSystem();
	bool _startSystem();
	bool _postStartSystem();

	BSLib::Utility::CHashMap<BSLib::uint16, CCommonSystem*> m_funSystemHashMap;
};

}//CommonServer

}//GFLib

#endif//__GFLIB_COMMONSERVER_COMMONSYSTEMMGR_H__
