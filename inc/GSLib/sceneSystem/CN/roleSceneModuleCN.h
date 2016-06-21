#ifndef __GSLIB_SCENESYSTEM_CN_ROLESCENEMODULECN_H__
#define __GSLIB_SCENESYSTEM_CN_ROLESCENEMODULECN_H__

#include <GSLib/playerSystem/CN/roleModuleCN.h>
#include <GSLib/dbSystem/keyIndexTable.h>
#include <GSLib/dbSystem/keyTable.h>

namespace GSLib
{

namespace SceneSystem
{
	class CArenaChallengeeData;
	class CArenaChallengeRecord;
	class CMsgSceneSystemGM2CNReqArenaAction;
namespace CN
{
class CRoleSceneModuleCN : public GSLib::PlayerSystem::CN::CRoleModuleCN
{
public:
	CRoleSceneModuleCN(GSLib::PlayerSystem::CN::CRoleCN* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleSceneModuleCN();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual void updateDataToDB();

	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);

	virtual void onRoleActive();
	virtual void onRoleInactive();

private:
	void _onMsgSceneSystemGM2CNReqArenaAction(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
private:
	void _onGetRoleArenaData();
	void _onGetChallengableRoles();
	void _onUpdateChallengeeArenaRecord(const SceneSystem::CArenaChallengeRecord &a_record);
	void _onArenaChallengeFinished(const CMsgSceneSystemGM2CNReqArenaAction & a_msg);

	void _getChallengableRoles(std::vector<SceneSystem::CArenaChallengeeData> & a_vecChallengees);
	void _getRandomArea(BSLib::uint32 a_rank, BSLib::uint32 a_count, BSLib::uint32 &a_start, BSLib::uint32 &a_end) const;
	bool _getChallengeeData(const SRoleKey &roleKey, SceneSystem::CArenaChallengeeData & challengeeData);
	BSLib::uint32 _getArenaBaseRank(BSLib::uint32 a_rank) const;
	void _updateChallengeRecord(const CArenaChallengeRecord & a_challengeRecord, const SRoleKey & a_roleKey);

private:
	std::map<BSLib::uint64, SceneSystem::CArenaChallengeRecord> m_mapChallengeRecords;
	GSLib::DBSystem::CKeyIndexTablePtr m_arenaChallengeRecordTable;
};

}//CN

}//SceneSystem

}//GSLib

#endif//__GSLIB_SCENESYSTEM_CN_ROLESCENEMODULECN_H__
