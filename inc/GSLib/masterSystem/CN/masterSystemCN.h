
#ifndef __GSLIB_MASTERSYSTEM_GM_MASTERSYSTEMGM_H__
#define __GSLIB_MASTERSYSTEM_GM_MASTERSYSTEMGM_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/dbSystem/keyIndexTable.h>
#include <GSLib/masterSystem/msgMasterSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/dbSystem/keyIndexTable.h>

namespace GSLib
{

namespace MasterSystem
{

namespace CN
{

class CMasterSystemCN : public GSLib::DBSystem::CDBCommonSystem
	, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
{
public:
	CMasterSystemCN();
	virtual ~CMasterSystemCN();

	BSLIB_SINGLETON_DECLARE(CMasterSystemCN);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_MASTERSYSTEM; }

	void update(BSLib::uint64 a_delayMilliseconds);

public:
	virtual bool _init();	// test
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

private:
	virtual bool _cbSelectGlobalKeyTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyTablePtr& a_keyTable,
											EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	virtual bool _cbSelectGlobalKeyIndexTableData(const GSLib::SRoleKey& a_srcRoleKey, const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyIndexTablePtr& a_keyTable,
											EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	virtual bool	exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);

private:
	std::string m_superKey;
	std::string m_gmKey;
	std::vector<std::string> m_gmkeys; // 广播专用
private:
	// CN 上处理的消息
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqRoleInfo);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqMail);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqRoleItemDeduct);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqBroadcast);

	// GM上处理的消息,及返回消息
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqAccountSearch);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXS2XXAckAccountSearch);

	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqAccountPwd);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXS2XXAckAccountPwd);

	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXX2XSReqAccountForbid);
	GSLIB_MSGFUN_DECLARE(CMsgMasterSystemXS2XXAckAccountForbid);

};

}

}

}//GSLib

#endif
