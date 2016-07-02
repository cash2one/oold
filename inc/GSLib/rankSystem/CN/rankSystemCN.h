#ifndef	__GSLIB_RANKSYSTEM_CN_RANKSYSTEMCN_H__
#define __GSLIB_RANKSYSTEM_CN_RANKSYSTEMCN_H__

#include <BSLib/utility/singleton.h>
#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/dbSystem/dbCommonSystem.h>
#include <GSLib/dbSystem/keyTable.h>
#include <GSLib/rankSystem/CN/rankImpl.h>
#include <GSLib/rankSystem/CN/dateTimer.h>

namespace GSLib
{

namespace RankSystem
{

namespace CN
{

class CRankSystemCN :  public GSLib::DBSystem::CDBCommonSystem
	, BSLib::Utility::CHashMap<std::string, BSLib::Database::CDBTableRow*>::CCallback
	,CDateTimerCallback
{
public:
	CRankSystemCN();
	virtual ~CRankSystemCN();

	virtual BSLib::uint16 getFuncType() { return GSLib::EFUNCTYPE_RANKSYSTEM; }

	BSLIB_SINGLETON_DECLARE(CRankSystemCN);

public:
	virtual bool _init();
	virtual void _final();
	virtual bool ICommonSystem_loadGameConfig(const std::string& a_configPath);
	virtual bool ICommonSystem_initServerMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual bool _startSystem();
	virtual void ICommonSystem_cbServerEnter(const GFLib::SServerID& a_serverID, const std::string& a_key);
	virtual void ICommonSystem_cbServerLeave(const GFLib::SServerID& a_serverID, const std::string& a_key);
	
	// 获取排行榜接口
	Rank*	getRank(BSLib::uint32 a_id);
	
	Rank*   regRank(BSLib::uint32 a_id, ERankType a_type);
private:
	virtual bool	exec(const std::string& a_key, BSLib::Database::CDBTableRow*& a_value);
	virtual bool	_cbSelectKeyTableData(const GSLib::SRoleKey& a_roleKey, DBSystem::CKeyTablePtr& a_keyTable,
											EDBTableID a_tableID, EModuleType a_moduleType, BSLib::uint32 a_sessionID);
	bool			_cbSaveTimer(BSLib::uint64, void* a_para);
	bool			_cbDateTimer(BSLib::uint64, void* a_para);
	Rank*			CreateRank(BSLib::Utility::CStream& a_stream);
	BSLib::uint32   rankCapacity(BSLib::uint64 a_id);
	BSLib::uint32	rankPrizeSize(BSLib::uint64 a_id);
	bool			rankTimeHandle(BSLib::uint64 a_id, STimeHandle& a_handle); // todo
	void			initRankTimer();
	virtual void	cb(BSLib::uint32 a_id);

private:
	DBSystem::CKeyTablePtr m_outputTablePtr;
	std::vector<Rank*>  m_rankContainer;
	bool	m_dataReady;
	CDateTimer m_dateTimer;
};

}//CN

}//RankSystem

}//GSLib

#endif//__GSLIB_RANKSYSTEM_CN_RANKSYSTEMCN_H__

