//////////////////////////////////////////////////////////////////////
//	created:	2014/10/09
//	filename: 	GSLib\rankSystem\GM\roleRankModule.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_RANKSYSTEM_GM_ROLERANKMODULE_H__
#define __GSLIB_RANKSYSTEM_GM_ROLERANKMODULE_H__

#include <GFLib/commonServer/baseDef.h>
#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/rankSystem/cmmhdr.h>

namespace GSLib
{

namespace RankSystem
{

namespace GM
{

class CRoleRankModule : public GSLib::PlayerSystem::GM::CRoleModuleGM
	, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
{
public:
	CRoleRankModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleRankModule();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();
	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);

	// 接口, a_aparam 秒数
	void	update(BSLib::uint32 a_id, BSLib::int32 a_param);

	void	updateArena(const SRoleKey& a_opponent); // 更新竞技场
	BSLib::uint32  getPlace(BSLib::uint32 a_id);  // 获取排名位置

private:
	void _onMsgRankSystemGC2GMReqGetRankData(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _onMsgRankSystemCN2GMNtfPlace(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	bool _dbUpdate();

private:
	GSLib::DBSystem::CKeyTablePtr				m_keyTablePtr;
	SRoleRank m_roleRank;
	BSLib::uint32 m_place;
};


}//GM

}//RankSystem

}//GSLib

#endif//__GSLIB_RANKSYSTEM_GM_ROLERANKMODULE_H__