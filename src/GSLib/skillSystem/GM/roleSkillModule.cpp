//////////////////////////////////////////////////////////////////////
//	created:	2014/09/13
//	filename: 	src\GSLib\skillSystem\GM\roleSkillModule.cpp
//	author:		mazhejiang
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <GSLib/skillSystem/GM/roleSkillModule.h>
#include <GSLib/skillSystem/GM/skill.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/skillSystem/GM/skillAttr.h>
#include <GSLib/skillSystem/GM/skillAttrMgr.h>
#include <GSLib/skillSystem/GM/skillLevel.h>
#include <GSLib/playerSystem/GM/roleBagModuleGM.h>
#include <GSLib/skillSystem/msgSkillSystem.h>
#include <GSLib/skillSystem/DB/tableSkillDB.h>
#include <GSLib/playerSystem/GM/roleGM.h>
#include <GSLib/playerSystem/GM/playerGM.h>
#include <GSLib/taskSystem/GM/roleTaskModule.h>

namespace GSLib
{

namespace SkillSystem
{

namespace GM
{

CRoleSkillModule::CRoleSkillModule(GSLib::PlayerSystem::GM::CRoleGM* a_roleGM, EModuleType a_moduleType)
: GSLib::PlayerSystem::GM::CRoleModuleGM(a_roleGM, a_moduleType)
{
	m_skills.clear();
	memset(m_skillPos, 0, sizeof(m_skillPos));
}

CRoleSkillModule::~CRoleSkillModule()
{
	for (BSLib::Utility::CHashMap<SkillTPID, CSkill*>::iterator itr = m_skills.begin(); itr != m_skills.end(); ++itr) {
		if (itr->second != NULL) {
			delete itr->second, itr->second = NULL;
		}
	}

	m_skills.clear();
}

void CRoleSkillModule::preInit(bool isFirst)
{
	;
}

void CRoleSkillModule::postInit(bool isFirst)
{
	;
}

void CRoleSkillModule::initToClient()
{
	CMsgSkillSystemGM2GCAckInitRoleSkillData msgAck;
	msgAck.m_skills = m_skills;
	memcpy(msgAck.m_skillButtons, m_skillPos, sizeof(m_skillPos));
	sendMsgToClient(msgAck);
}

void CRoleSkillModule::final()
{
	m_skills.clear();
}

void CRoleSkillModule::initMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSkillSystemGC2GMReqLearnSkill, &BSLib::Framework::CreateCMessage<CMsgSkillSystemGC2GMReqLearnSkill>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSkillSystemGC2GMReqLearnSkill, &CRoleSkillModule::_OnMsgSkillSystemGC2GMReqLearnSkill, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSkillSystemGC2GMReqUpgradeSkill, &BSLib::Framework::CreateCMessage<CMsgSkillSystemGC2GMReqUpgradeSkill>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSkillSystemGC2GMReqUpgradeSkill, &CRoleSkillModule::_OnMsgSkillSystemGC2GMReqUpgradeSkill, this);

	BSLib::Framework::CMsgFactory::singleton().registerCreateCMsgFun(MsgIDSkillSystemGC2GMReqSetSkillButton, &BSLib::Framework::CreateCMessage<CMsgSkillSystemGC2GMReqSetSkillButton>);
	GFLIB_ADDMSG_OBJEXEC(a_msgExecMgr, MsgIDSkillSystemGC2GMReqSetSkillButton, &CRoleSkillModule::_OnMsgSkillSystemGC2GMReqSetSkillButton, this);
}

void CRoleSkillModule::freeMsg(BSLib::Framework::CMsgExecMgr* a_msgExecMgr)
{
	a_msgExecMgr->delMsgExecPtr(MsgIDSkillSystemGC2GMReqLearnSkill);
	a_msgExecMgr->delMsgExecPtr(MsgIDSkillSystemGC2GMReqUpgradeSkill);
	a_msgExecMgr->delMsgExecPtr(MsgIDSkillSystemGC2GMReqSetSkillButton);
}

bool CRoleSkillModule::cbSelectGetTableData(const GSLib::SRoleKey& a_roleKey,GSLib::DBSystem::ETableKeyType a_TableKeyType,GSLib::DBSystem::CKeyIndexTablePtr& a_keyIndexTable, 
								  GSLib::DBSystem::CKeyTablePtr& a_keyTable,EDBTableID a_tableID, BSLib::uint32 a_sessionID,BSLib::Utility::CStream& a_stream)
{
	if (a_TableKeyType != GSLib::DBSystem::ETABLEKEYTYPE_KEY) {
		return false;
	}
	if (a_keyTable == NULL) {
		return false;
	}
	if (a_tableID == EDBTABLEID_ROLE_SKILL_DATA) {
		BSLib::Database::CDBTableRow*  row = a_keyTable->getRow(a_roleKey.getDBKey());
		if (row != NULL) {
			row->serializeTo(a_stream);
		}
	}

	return true;
}

void CRoleSkillModule::updateDataToDB()
{

}

bool CRoleSkillModule::cbSelectKeyTableData(GSLib::DBSystem::CKeyTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	if (getRoleGM() == NULL || getRoleGM()->getAccountID() == 0) {
		return false;
	}

	if (a_tableID == EDBTABLEID_ROLE_SKILL_DATA) {
		m_skillTable = a_keyTable;
	}

	if (a_sessionID == 0) {
		if (a_tableID == EDBTABLEID_ROLE_SKILL_DATA) {
			DB::CRoleSkillData roleSkill;
			roleSkill.m_accountID = getRoleGM()->getAccountID();
			roleSkill.m_zoneID = getRoleGM()->getZoneID();
			roleSkill.m_roleIndex = getRoleGM()->getRoleIndex();
			BSLib::Database::CDBTableRow*  row = a_keyTable->getRow(roleSkill.getDBKey());
			if (row != NULL) {
				BSLib::Utility::CStream stream;
				row->serializeTo(stream);
				roleSkill.serializeFrom(stream);
				for (std::vector<GM::CSkill>::iterator itr = roleSkill.m_vecSkill.begin(); itr != roleSkill.m_vecSkill.end(); ++itr) {
					CSkill *skill = new CSkill(*itr);
					m_skills.setValue(itr->getSkillTPID(), skill);
				}

				for (BSLib::uint32 i = 0; i < roleSkill.m_vecSkillPos.size() && (int)i < SKILL_BOTTON_COUNT; ++i) {
					m_skillPos[i] = roleSkill.m_vecSkillPos[i];
				}
			}
		}
	}

	return true;
}

bool CRoleSkillModule::cbSelectKeyIndexTableData(GSLib::DBSystem::CKeyIndexTablePtr& a_keyTable, EDBTableID a_tableID, BSLib::uint32 a_sessionID)
{
	return true;
}

void CRoleSkillModule::_OnMsgSkillSystemGC2GMReqLearnSkill(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return ;
	}

	CMsgSkillSystemGC2GMReqLearnSkill *msgReq = (CMsgSkillSystemGC2GMReqLearnSkill *)a_msg;
	SkillTPID skillTPID = msgReq->m_skillTPID;
	ELearnSkillError result =  _learnSkill(skillTPID);
	_updateSkillTable();

	CMsgSkillSystemGM2GCAckLearnSkill msgAck;
	msgAck.m_skillTPID = skillTPID;
	msgAck.m_result = result;
	sendMsgToClient(msgAck);
}

void CRoleSkillModule::_OnMsgSkillSystemGC2GMReqUpgradeSkill(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}

	CMsgSkillSystemGC2GMReqUpgradeSkill *msgReq = (CMsgSkillSystemGC2GMReqUpgradeSkill *)a_msg;
	SkillTPID skillTPID = msgReq->m_skillTPID;

	EUpgradeSkillError result = _upgradeSkill(skillTPID);
	if (result == UPGRADE_SKILL_ERROR_SUCCESS) {
		_updateSkillTable();
		GSLib::TaskSystem::GM::CRoleTaskModule *taskModule = (GSLib::TaskSystem::GM::CRoleTaskModule *)getRoleGM()->getPlayerModuleGM(EMODULECTYPE_TASK);
		if (taskModule != NULL) {
			taskModule->updateDailyTask(GSLib::TaskSystem::GM::EDAILY_TASK_TYPE_UPGRADE_SKILL);
		}
	}
	
	CMsgSkillSystemGM2GCAckUpgradeSkill msgAck;
	msgAck.m_skillTPID = skillTPID;
	msgAck.m_result = result;
	sendMsgToClient(msgAck);
}

void CRoleSkillModule::_OnMsgSkillSystemGC2GMReqSetSkillButton(BSLib::Framework::SMsgLabel* a_msgLabel,BSLib::Framework::SMessage* a_msg)
{
	if (a_msg == NULL) {
		return;
	}

	CMsgSkillSystemGC2GMReqSetSkillButton *msgReq = (CMsgSkillSystemGC2GMReqSetSkillButton *)a_msg;

	ESetSkillButtonError result = _canSetSkillButton(msgReq->m_skillTPID, msgReq->m_skillButtonIndex);
	if (result == SET_SKILL_BUTTON_SUCCESS) {
		setSkillButton(msgReq->m_skillTPID, msgReq->m_skillButtonIndex);
		_updateSkillTable();
	}

	CMsgSkillSystemGM2GCAckSetSkillButton msgAck;
	msgAck.m_result = result;
	memcpy(msgAck.m_skillButtons, m_skillPos, sizeof(m_skillPos));
	sendMsgToClient(msgAck);
}

bool CRoleSkillModule::initSkill(SkillTPID a_skillTPID, SkillLevel a_skillLevel)
{
	BSLib::Utility::CHashMap<SkillTPID, CSkill*>::const_iterator itr = m_skills.find(a_skillTPID);
	if (itr != m_skills.end()) {
		return false;
	}

	const CSkillAttr *skillAttr = CSkillDataMgr::singleton().getSkillAttr(a_skillTPID);
	if (skillAttr == NULL) {
		return false;
	}

	GSLib::PlayerSystem::GM::CRoleGM *role = getRoleGM();
	if (role == NULL) {
		return false;	
	}

	if (role->getTPID() != skillAttr->getRoleTPID()) {
		return false;
	}

	getSkill(a_skillTPID, a_skillLevel);
	_updateSkillTable();
	return true;
}

void CRoleSkillModule::getSkill(SkillTPID a_skillID, SkillLevel skillLevel)
{
	CSkill *skill = new CSkill(a_skillID, skillLevel); 
	m_skills.setValue(a_skillID, skill);
}

void CRoleSkillModule::setSkillButton(SkillTPID a_skillTPID, BSLib::uint8 a_skillButtonIndex)
{
	if (a_skillButtonIndex < SKILL_BOTTON_COUNT) {
		if (m_skills.find(a_skillTPID) != m_skills.end()) {
			BSLib::int32 switchIndex = 0;
			while (switchIndex < SKILL_BOTTON_COUNT) {
				if (m_skillPos[switchIndex] == a_skillTPID) {
					break;
				}
				++switchIndex;
			}
			if (switchIndex < SKILL_BOTTON_COUNT) {
				SkillTPID skillTPID = m_skillPos[a_skillButtonIndex];
				m_skillPos[switchIndex] = skillTPID;
				m_skillPos[a_skillButtonIndex] = a_skillTPID;
			} else {
				m_skillPos[a_skillButtonIndex] = a_skillTPID;
			}
		}
	}
}

BSLib::uint32 CRoleSkillModule::getTotalSkillLevelSum() const
{
	BSLib::uint32 count = 0;
	for (BSLib::Utility::CHashMap<SkillTPID, CSkill*>::const_iterator itr =	m_skills.begin(); itr != m_skills.end(); ++itr) {
		if (itr->second != NULL) {
			count += itr->second->getSkillLevel();
		}
	}

	return count;
}

BSLib::uint32 CRoleSkillModule::getLearnedSkillCount() const
{
	return (BSLib::uint32)m_skills.size();
}

ELearnSkillError CRoleSkillModule::_learnSkill(SkillTPID a_TPID)
{
	ELearnSkillError  result = _canLearnSkill(a_TPID);		
	if (result != LEARN_SKILL_ERROR_SUCCESS) {
		return result;
	}

	const CSkillAttr *skillAttr = CSkillDataMgr::singleton().getSkillAttr(a_TPID);
	if (skillAttr == NULL) {
		return LEARN_SKILL_ERROR_INVALID_SKILLTPID;
	}
	PlayerSystem::GM::CRoleGM *role = getRoleGM();
	if (role == NULL) {
		return LEARN_SKILL_ERROR_FAIL;
	}

	SkillLevel defaultLevel = 1;
	role->modifyGold(static_cast<BSLib::int64>(skillAttr->getRequiredGold(skillAttr->m_skillLearnRequiredLevel, defaultLevel)) * (-1), "EREASON_GOLD_DEC_SKILL_LEARN_SKILL", true);

	getSkill(a_TPID, defaultLevel);
	if (getRoleGM() != NULL) {
		getRoleGM()->updateCombat();   	
		getRoleGM()->updateTotalBattleAttr();
	}

	return LEARN_SKILL_ERROR_SUCCESS;
}

EUpgradeSkillError CRoleSkillModule::_upgradeSkill(SkillTPID a_TPID)
{
	EUpgradeSkillError result = _canUpgradeSkill(a_TPID);
	if (result != UPGRADE_SKILL_ERROR_SUCCESS) {
		return result;
	}

	BSLib::Utility::CHashMap<SkillTPID, CSkill*>::iterator itr = m_skills.find(a_TPID);	
	if (itr == m_skills.end() || itr->second == NULL) {
		return UPGRADE_SKILL_ERROR_NOT_LEARN;
	}
	PlayerSystem::GM::CRoleGM *role = getRoleGM();
	if (role == NULL) {
		return UPGRADE_SKILL_ERROR_FAIL;
	}
	const CSkillAttr *skillAttr = CSkillDataMgr::singleton().getSkillAttr(a_TPID);
	if (skillAttr == NULL) {
		return UPGRADE_SKILL_ERROR_INVALID_SKILLTPID;
	}

	CSkill *skill = itr->second;
	SkillLevel curSkillLevel = skill->getSkillLevel();
	role->modifyGold(static_cast<BSLib::int64>(skillAttr->getRequiredGold(skillAttr->m_skillLearnRequiredLevel, curSkillLevel + 1)) * (-1), "EREASON_GOLD_DEC_SKILL_UPGRADE_SKILL", true);

	skill->setSkillLevel(curSkillLevel + 1);
	if (getRoleGM() != NULL) {
		getRoleGM()->updateCombat();   	
		getRoleGM()->updateTotalBattleAttr();
	}
	return UPGRADE_SKILL_ERROR_SUCCESS;
}

void CRoleSkillModule::_updateSkillTable()
{
	if (getRoleGM() == NULL || getRoleGM()->getPlayerGM() == NULL) {
		return;
	}

	DB::CRoleSkillData skillData;
	skillData.m_accountID = getRoleGM()->getAccountID();
	skillData.m_zoneID = getRoleGM()->getZoneID();
	skillData.m_roleIndex = getRoleGM()->getRoleIndex();
	for (BSLib::Utility::CHashMap<SkillTPID, CSkill*>::iterator itr = m_skills.begin(); itr != m_skills.end(); ++itr) {
		CSkill & skill = *(itr->second);
		skillData.m_vecSkill.push_back(skill);	
	}

	for (BSLib::int32 i = 0; i < SKILL_BOTTON_COUNT; ++i) {
		skillData.m_vecSkillPos.push_back(m_skillPos[i]);
	}

	BSLib::Utility::CStream stream;
	skillData.serializeTo(stream);
	m_skillTable->update(skillData.getDBKey(), stream);
	m_skillTable->saveDataToDBServer(skillData.getDBKey(), true);	
}

ELearnSkillError CRoleSkillModule::_canLearnSkill(SkillTPID a_skillTPID) /*const */
{
	BSLib::Utility::CHashMap<SkillTPID, CSkill*>::const_iterator itr = m_skills.find(a_skillTPID);
	if (itr != m_skills.end()) {
		return LEARN_SKILL_ERROR_ALREADY_LEARN;
	}

	const CSkillAttr *skillAttr = CSkillDataMgr::singleton().getSkillAttr(a_skillTPID);
	if (skillAttr == NULL) {
		return LEARN_SKILL_ERROR_INVALID_SKILLTPID;
	}

	GSLib::PlayerSystem::GM::CRoleGM *role = getRoleGM();
	if (role == NULL) {
		return LEARN_SKILL_ERROR_FAIL;	
	}

	if (role->getTPID() != skillAttr->getRoleTPID()) {
		return LEARN_SKILL_ERROR_INCORRECT_ROLETPID;
	}

	//BSLib::uint32 level = role->getLevel();
	if (role->getLevel() < skillAttr->m_skillLearnRequiredLevel) {
		return LEARN_SKILL_ERROR_NOT_ENOUGH_LEVEL;
	}

	if (role->getGold() < skillAttr->getRequiredGold(skillAttr->m_skillLearnRequiredLevel, 1)) {
		return LEARN_SKILL_ERROR_NOT_ENOUGH_GOLD;
	}

	return LEARN_SKILL_ERROR_SUCCESS;
}

EUpgradeSkillError CRoleSkillModule::_canUpgradeSkill(SkillTPID a_skillTPID) /*const*/
{
	BSLib::Utility::CHashMap<SkillTPID, CSkill*>::const_iterator itr = m_skills.find(a_skillTPID);
	if (itr == m_skills.end()) {
		return UPGRADE_SKILL_ERROR_NOT_LEARN;
	}
	CSkill *skill = itr->second;
	if (skill == NULL) {
		return UPGRADE_SKILL_ERROR_FAIL;
	}

	const CSkillAttr *skillAttr = CSkillDataMgr::singleton().getSkillAttr(a_skillTPID);
	if (skillAttr == NULL) {
		return UPGRADE_SKILL_ERROR_INVALID_SKILLTPID;
	}

	GSLib::PlayerSystem::GM::CRoleGM *role = getRoleGM();
	if (role == NULL) {
		return UPGRADE_SKILL_ERROR_FAIL;	
	}

	if (role->getLevel() < (skill->getSkillLevel() * 3 + skillAttr->m_skillLearnRequiredLevel)) {
		return UPGRADE_SKILL_ERROR_NOT_ENOUGH_ROLE_LEVEL;
	}

	if (skill->getSkillLevel() >= skillAttr->m_maxSkillLevel) {
		return UPGRADE_SKILL_ERROR_MAX_SKILL_LEVEL;
	}

	if (role->getGold() < skillAttr->getRequiredGold(skillAttr->m_skillLearnRequiredLevel, skill->getSkillLevel() + 1)) {
		return UPGRADE_SKILL_ERROR_NOT_ENOUGH_GOLD;
	}

	return UPGRADE_SKILL_ERROR_SUCCESS;
}


ESetSkillButtonError CRoleSkillModule::_canSetSkillButton(SkillTPID a_skillTPID, BSLib::uint8 a_skillButtonIndex) const
{
	if (a_skillButtonIndex >= SKILL_BOTTON_COUNT) {
		return SET_SKILL_BUTTON_FAIL;
	}

	if (m_skills.find(a_skillTPID) == m_skills.end()) {
		return SET_SKILL_BUTTON_NOT_SUCH_SKILL;
	}

	return SET_SKILL_BUTTON_SUCCESS;
}



}//GM

}//SkillSystem

}//GSLib


