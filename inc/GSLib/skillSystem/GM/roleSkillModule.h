#ifndef __GSLIB_SKILLSYSTEM_GM_ROLESKILLMODULE_H__
#define __GSLIB_SKILLSYSTEM_GM_ROLESKILLMODULE_H__

#include <GSLib/playerSystem/GM/roleModuleGM.h>
#include <GSLib/skillSystem/GM/skillError.h>
#include <GSLib/skillSystem/GM/skillDefine.h>

namespace GSLib
{

namespace SkillSystem
{

namespace GM
{
class CSkill;

class CRoleSkillModule : public GSLib::PlayerSystem::GM::CRoleModuleGM
{
public:
	CRoleSkillModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType);
	virtual ~CRoleSkillModule();

	virtual void preInit(bool isFirst);
	virtual void postInit(bool isFirst);
	virtual void initToClient();
	virtual void final();

	virtual void initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);
	virtual void freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr);

	virtual bool cbSelectGetTableData(const GSLib::SRoleKey& a_roleKey,GSLib::DBSystem::ETableKeyType a_TableKeyType,GSLib::DBSystem::CKeyIndexTablePtr& a_keyIndexTable, 
		GSLib::DBSystem::CKeyTablePtr& a_keyTable,EDBTableID a_tableID, BSLib::uint32 a_sessionID,BSLib::Utility::CStream& a_stream);

	virtual void updateDataToDB();
	virtual bool cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
	virtual bool cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID);
private:
	void _OnMsgSkillSystemGC2GMReqLearnSkill(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _OnMsgSkillSystemGC2GMReqUpgradeSkill(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
	void _OnMsgSkillSystemGC2GMReqSetSkillButton(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg);
public:
	bool initSkill(SkillTPID a_skillTPID, SkillLevel a_skillLevel);
	void getSkill(SkillTPID a_skillID, SkillLevel skillLevel = 1);
	void setSkillButton(SkillTPID a_skillTPID, BSLib::uint8 a_skillButtonIndex);
	BSLib::uint32 getTotalSkillLevelSum() const;
	BSLib::uint32 getLearnedSkillCount() const;
private:
	ELearnSkillError _learnSkill(SkillTPID a_skillID);
	EUpgradeSkillError _upgradeSkill(SkillTPID a_skillID);
	void _updateSkillTable();
private:
	ELearnSkillError _canLearnSkill(SkillTPID a_skillTPID) /*const*/;
	EUpgradeSkillError _canUpgradeSkill(SkillTPID a_skillTPID) /*const*/;
	ESetSkillButtonError _canSetSkillButton(SkillTPID a_skillTPID, BSLib::uint8 a_skillButtonIndex) const;
public:
	BSLib::Utility::CHashMap<SkillTPID, CSkill*>	m_skills;
	SkillTPID m_skillPos[SKILL_BOTTON_COUNT];
	GSLib::DBSystem::CKeyTablePtr	m_skillTable;
};

}//GM

}//SkillSystem

}//GSLib

#endif//__GSLIB_SKILLSYSTEM_GM_ROLESKILLMODULE_H__
