#ifndef __GSLIB_PLAYERSYSTEM_CN_PLAYERSYSTEMCN_H__
#define __GSLIB_PLAYERSYSTEM_CN_PLAYERSYSTEMCN_H__

#include <BSLib/utility/singleton.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/dbSystem/keyIndexTable.h>

namespace GSLib
{

namespace PlayerSystem
{
namespace CN
{

class CPlayerSystemCN : public GSLib::DBSystem::CDBCommonSystem, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
{
public:
	CPlayerSystemCN();
	virtual ~CPlayerSystemCN();

	BSLIB_SINGLETON_DECLARE(CPlayerSystemCN);

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_PLAYERSYSTEM; }

protected:
	virtual bool _init();
	virtual void _final();
	virtual bool _loadGameConfig(const std::string& a_configPath);
	virtual bool _initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void _cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void _cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);

private:
	void _onMsgPlayerSystem(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
protected:
	virtual bool _cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	virtual bool _cbSelectKeyIndexTableData(const GSLib::SRoleKey& a_roleKey, GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
    virtual bool exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);
private:
    GSLib::DBSystem::CKeyIndexTablePtr m_roleTablePtr;
};

}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_PLAYERSYSTEMCN_H__

