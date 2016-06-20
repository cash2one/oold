//////////////////////////////////////////////////////////////////////
//	created:	2014/12/5
//	filename: 	GSLib\activitySystem\GM\roleActivityModule.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_ACTIVITYSYSTEM_GM_ROLEACTIVITYMODULE_H__
#define __GSLIB_ACTIVITYSYSTEM_GM_ROLEACTIVITYMODULE_H__

#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <BSLib/database/dbTableRow.h>
#include <GSLib/activitySystem/DB/tableActivityDB.h>
#include <GSLib/activitySystem/GM/activityData.h>
#include <GSLib/activitySystem/GM/activitySystemDefine.h>
#include <GSLib/activitySystem/GM/activitySystemError.h>

namespace GSLib
{

namespace ActivitySystem
{

namespace GM
{
	const BSLib::uint32 DAILY_FREE_GOLD_DRAW_CARD_COUNT = 10;

class CRoleActivityModule : public GSLib::PlayerSystem::GM::CRoleModuleGM
{
public:
	CRoleActivityModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleActivityModule();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void onRoleActive();

	virtual void updateDataToDB();
	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);

	void updateRoleAttendenceTable(CRoleAttendenceData &a_roleAttendenceData);
	void updateDrawCardTable(CRoleDrawCardData & a_roleDrawCardData);
private:
	void _onMsgActivitySystemGC2GMReqGetAttendenceData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgActivitySystemGC2GMReqSignIn(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgActivitySystemGC2GMReqDrawCard(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgActivitySystemGC2GMReqGetDrawCardInfo(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
public:
	void onDailyFreeGoldDrawCardCountResetCallback();
private:
	BSLib::int32 _calcAttendenceEndTime(BSLib::int32 a_startTime) const;
	EDrawCardResult _canDrawCard(EDrawCardType type, BSLib::uint16 count);

	bool _genRollMap(BSLib::int32 a_level, CDrawItemPool& a_drawItemPool);
	void _rollCard(const CDrawItemPool& a_drawItemPool, CRolledItem & a_rolledItem);
	void _drawCard(BSLib::int32, CRolledItem & a_rolledItem);
	void _drawTenCard(EDrawCardType a_type, std::vector<CRolledItem> & a_vecRolledItem);
	void _addRolledItem(const CRolledItem & a_rolledItem);

private:
	GSLib::DBSystem::CKeyTablePtr m_roleAttendenceTable;
	GSLib::DBSystem::CKeyTablePtr m_roleDrawCardDataTable;
	CRoleAttendenceData m_roleAttendenceData;
	CRoleDrawCardData m_roleDrawCardData;
};

}//GM

}

}//GSLib

#endif