#ifndef __GSLIB_PLAYERSYSTEM_CN_ROLEMODULECN_H__
#define __GSLIB_PLAYERSYSTEM_CN_ROLEMODULECN_H__

#include <BSLib/framework/message/msgExecMgr.h>
#include <GFLib/commonServer/message/message.h>
#include <GSLib/funType.h>
#include <GSLib/moduleType.h>
#include <GSLib/dbTableID.h>
#include <GSLib/dbSystem/CN/dbSystemCN.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace CN
{

class CRoleCN;

class CRoleModuleCN
{
public:
	CRoleModuleCN(CRoleCN* a_roleCN, EModuleType a_moduleType);
	virtual ~CRoleModuleCN();

	virtual void preInit(bool isFirst) = 0;
	virtual void postInit(bool isFirst) = 0;

	virtual void initToClient() = 0;
	virtual void final() = 0;

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr) = 0;
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr) = 0;
	virtual void onRoleActive();
	virtual void onRoleInactive();

	virtual void cbPlayerOnline();
	virtual void cbPlayerOffline();

	virtual void updateDataToDB() = 0;
	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID) { return false ;}
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID) { return false; }

public:
	bool sendMsgToClient(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToClient(GFLib::CMessage& msg);

	bool sendMsgToGateServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToGateServer(GFLib::CMessage& msg);

	bool sendMsgToDataServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToDataServer(GFLib::CMessage& msg);

	bool sendMsgToGameServer(GFLib::SMessage* msg, BSLib::uint32 msgSize);
	bool sendMsgToGameServer(GFLib::CMessage& msg);
	
	CRoleCN* getRoleCN() { return m_roleCN; }
	EModuleType getModuleType() { return m_moduleType; }

private:
	CRoleCN* m_roleCN;
	EModuleType m_moduleType;
};


}//CN

}//PlayerSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_CN_ROLEMODULECN_H__

