//////////////////////////////////////////////////////////////////////
//	created:	2014/08/10
//	filename: 	GSLib\sceneSystem\GM\sceneSystemDataMgr.h
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef		__GSLIB_SCENESYSTEM_GM_SCENESYSTEMDATAMGR_H__
#define		__GSLIB_SCENESYSTEM_GM_SCENESYSTEMDATAMGR_H__

#include <BSLib/utility/baseDef.h>
#include <BSLib/utility/hashMap.h>
#include <BSLib/utility/singleton.h>
#include <GSLib/itemSystem/GM/itemAttributeGM.h>
#include <GSLib/sceneSystem/GM/sceneDefine.h>

namespace GSLib
{

namespace SceneSystem
{

namespace GM
{
	class CReviveItem;
	class CDropTableEntry;
	class CDropItem;
	class CArenaPrize;
	class CStageAttr;
	class CInstanceAttr;
	class CInstanceStarPrizeAttr;
	class CSceneAttr;
	class CStageUnitAttr;
	class CDropMonsterAttr;
	class CStageTemplate;

class CSceneSystemDataMgr
{
	BSLIB_SINGLETON_DECLARE(CSceneSystemDataMgr);
public:
	CSceneSystemDataMgr();
	~CSceneSystemDataMgr();
public:
	bool loadConfig(const std::string &a_configPath);
public:
	const CSceneAttr* getSceneAttr(ESceneType a_sceneType, BSLib::uint32 a_sceneTPID) const;

	void addReviveItem(CReviveItem *a_reviveItem);
	const CReviveItem *getReviveItem(BSLib::uint32 a_reviveTimes);

	void addDropItemTableEntry(CDropTableEntry *a_dropItemEntry);
	const CDropTableEntry *getDropItemEntry(BSLib::uint32 a_ID) const;

	const CDropItem* getRandomDropItem(BSLib::uint32 a_ID) const;

	void addDailyRankPrize(BSLib::uint32 a_endRank, CArenaPrize *a_prize);
	const CArenaPrize* getDailyRankPrize(BSLib::uint32 a_rank) const;

	void addHistoryHighestRankPrize(BSLib::uint32 a_endRank, CArenaPrize* a_prize);
	const CArenaPrize* getHistoryHighestRankPrize(BSLib::uint32 a_rank, CArenaPrize* a_prize);

	void setArenaChallengeSucPrize(CArenaPrize *a_prize);
	const CArenaPrize* getArenaChallengeSucPrize() const;

	void setArenaChallengeFailPrize(CArenaPrize *a_prize);
	const CArenaPrize* getArenaChallengeFailPrize() const;

	const CInstanceAttr * getInstanceAttr(BSLib::uint32 a_instanceTPID) const;

	const CStageAttr * getStageAttr(BSLib::uint32 a_stageTPID) const;
	const CStageAttr* getStageAttr(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex) const;

	const CStageAttr *getContinuousStageAttr(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_stageIndex);

	const CInstanceStarPrizeAttr* getInstanceStarPrizeAttr(BSLib::uint32 a_instanceTPID) const;

	const CSceneAttr* getArenaSceneAttr() const;

	const CStageTemplate *getStageTemplate(BSLib::uint32 a_difficulty) const;

private:
	bool _loadCityAttr(const std::string & a_path);
	bool _loadReviveItems(const std::string &a_path);
	bool _loadItemDropTable(const std::string &a_path);
	bool _loadArenaData(const std::string &a_path);
	bool _loadStageUnit(const std::string &a_path);
	bool _loadStageAttr(const std::string &a_path);
	bool _loadInstanceData(const std::string &a_path);
	bool _loadInstanceStarPrizeData(const std::string & a_path);
	bool _loadArenaDailyRankPrize(const std::string &a_path);
	bool _loadArenaHistoryHighestRankPrize(const std::string &a_path);
	bool _loadArenaChallengePrize(const std::string &a_path);
	bool _loadArenaConfig(const std::string &a_path);
	bool _loadStageTemplate(const std::string &a_path);
private:
	void _addStageData(CStageAttr * stageAttr);
	void _addInstanceStarPrize(BSLib::uint32 a_instanceTPID, BSLib::uint16 a_star, std::vector<ItemSystem::GM::CPrizeItem> &a_vecPrizeItem);
	void _addTemplateStage(CStageTemplate * a_stageTemplate);
private:
	BSLib::Utility::CHashMap<BSLib::uint32, CSceneAttr*> m_hashScene;		
	BSLib::Utility::CHashMap<BSLib::uint32, CReviveItem*> m_hashReviveItems;		
	BSLib::Utility::CHashMap<BSLib::uint32, CDropTableEntry*> m_hashDropItemTable;
	BSLib::Utility::CHashMap<BSLib::uint32, CArenaPrize*> m_hashDailyRankPrize;
	BSLib::Utility::CHashMap<BSLib::uint32, CArenaPrize*> m_hashHistoryHighestRankPrize;
	BSLib::Utility::CHashMap<BSLib::uint32, CStageAttr*> m_hashStage;
	BSLib::Utility::CHashMap<BSLib::uint32, CInstanceAttr*> m_hashInstance[EINSTANCE_TYPE_MAX];
	BSLib::Utility::CHashMap<BSLib::uint32, CInstanceStarPrizeAttr*> m_hashInstanceStarPrize;
	BSLib::Utility::CHashMap<BSLib::uint32, CStageUnitAttr*> m_hashStageUnit;
	//BSLib::Utility::CHashMap<BSLib::uint32, CDropMonsterAttr*> m_hashMonster;
	BSLib::Utility::CHashMap<BSLib::uint32, CStageTemplate*> m_hashTemplateStage;
	CSceneAttr * m_arenaAttr;
	CArenaPrize *m_arenaChallengeSucPrize;
	CArenaPrize *m_arenaChallengeFailPrize;
	BSLib::uint32 m_maxRoleHPExtendTimes;
};

}//GM

}//SceneSystem

}//GSLib













#endif
