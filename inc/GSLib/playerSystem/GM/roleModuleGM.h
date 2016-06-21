#ifndef __GSLIB_PLAYERSYSTEM_GM_ROLEMODULEGM_H__
#define __GSLIB_PLAYERSYSTEM_GM_ROLEMODULEGM_H__

#include <BSLib/framework/message/msgExecMgr.h>
#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/moduleType.h>
#include <GSLib/dbTableID.h>
#include <GSLib/dbSystem/keyIndexTable.h>
#include <GSLib/dbSystem/keyTable.h>
namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

class CRoleGM;
class CRoleAllData;
class CRoleModuleGM
{
public:
	CRoleModuleGM(CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleModuleGM();

	virtual void preInit(bool isFirst) = 0;
	virtual void postInit(bool isFirst) = 0;
	virtual void initToClient() = 0;
	virtual void final() = 0;

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr) = 0;
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr) = 0;

	virtual void onRoleActive();
	virtual void onRoleInactive();

    virtual void onRoleDelete();

	virtual void updateDataToDB() = 0;

	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID) { return false ;}
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID) { return false; }
    virtual bool cbSelectGetTableData(const GSLib::SRoleKey& a_roleKey,GSLib::DBSystem::ETableKeyType a_TableKeyType,GSLib::DBSystem::CKeyIndexTablePtr& a_keyIndexTable, GSLib::DBSystem::CKeyTablePtr& a_keyTable,EDBTableID a_tableID, BSLib::uint32 a_sessionID,BSLib::Utility::CStream& a_stream);
    virtual bool cbSelectMultiTableData(bool a_success,BSLib::uint32 a_sessionID,void* a_ptr,CRoleAllData& a_roleAllData);

public:
	bool sendMsgToClient(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToClient(GFLib::CMessage& msg);

	bool sendMsgToGateServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToGateServer(GFLib::CMessage& msg);

	bool sendMsgToDataServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToDataServer(GFLib::CMessage& msg);

	bool sendMsgToCenterServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToCenterServer(GFLib::CMessage& msg);
	
	CRoleGM* getRoleGM() const { return m_roleGM; }
	EModuleType getModuleType()const { return m_moduleType; }

private:
	CRoleGM* m_roleGM;
	EModuleType m_moduleType;
};


}//GM

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_ROLEMODULEGM_H__

