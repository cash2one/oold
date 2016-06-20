//////////////////////////////////////////////////////////////////////
//	created:	2014/12/5
//	filename: 	GSLib\activitySystem\GM\activitySystemDataMgr.cpp
//	author:		zhangming
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#include <BSLib/utility/file/dirInfo.h>
#include <GSLib/activitySystem/GM/activityData.h>
#include <GSLib/activitySystem/GM/activitySystemDataMgr.h>
#include <BSLib/utility/string.h>
#include <BSLib/utility/table.h>
#include <BSLib/utility/tracer.h>
#include <GSLib/tracer.h>
#include <BSLib/utility/convert.h>

namespace GSLib
{

namespace ActivitySystem
{

namespace GM
{

CActivitySystemDataMgr::CActivitySystemDataMgr()
:m_curAttendenceTable(0)
{

}

CActivitySystemDataMgr::~CActivitySystemDataMgr()
{
	for (BSLib::Utility::CHashMap< BSLib::uint32, BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *> >::iterator itr = m_hashAttendenceAttrs.begin(); itr != m_hashAttendenceAttrs.end(); ++itr) {
		BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *> & attendenceMap = itr->second;
		for (BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *>::iterator attrItr = attendenceMap.begin(); attrItr != attendenceMap.end(); ++attrItr) {
			if (attrItr->second != NULL) {
				delete attrItr->second, attrItr->second = NULL;
			}
		}
		attendenceMap.clear();
	}
	m_hashAttendenceAttrs.clear();
}

BSLIB_SINGLETON_DEFINE(CActivitySystemDataMgr);

bool CActivitySystemDataMgr::loadActivityConfig(const std::string & a_path)
{
	std::string activityPath = a_path + "\\activity";
	if (!_loadAttendenceAttrs(activityPath)) {
		return false;
	}
	if (!_loadAttendenceConfig(activityPath)) {
		return false;
	}
	if (!_loadPetCardConfig(activityPath)) {
		return false;
	}
	if (!_loadDrawCardWeightBonusConfig(activityPath)) {
		return false;
	}
	return true;
}

void CActivitySystemDataMgr::addAttendenceAttr(BSLib::uint32 a_tableID, CAttendenceAttr *a_attendenceAttr)
{
	if (a_attendenceAttr != NULL) {
		BSLib::Utility::CHashMap< BSLib::uint32, BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *> >::iterator itr = m_hashAttendenceAttrs.find(a_tableID);
		if (itr != m_hashAttendenceAttrs.end()) {
			BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *> & attendenceMap = itr->second;
			if (attendenceMap.find(a_attendenceAttr->getDays()) == attendenceMap.end()) {
				attendenceMap.setValue(a_attendenceAttr->getDays(), a_attendenceAttr);
			}
		} else {
			BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *> attendenceMap;
			attendenceMap.setValue(a_attendenceAttr->getDays(), a_attendenceAttr);
			m_hashAttendenceAttrs.setValue(a_tableID, attendenceMap);
		}
	}
}

BSLib::uint32 CActivitySystemDataMgr::getCurAttendencePrizeTable() const
{
	return m_curAttendenceTable;
}

const CAttendenceAttr * CActivitySystemDataMgr::getAttendenceAttr(BSLib::uint32 a_tableID, BSLib::uint32 a_day) const
{
	BSLib::Utility::CHashMap< BSLib::uint32, BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *> >::const_iterator itr = m_hashAttendenceAttrs.find(a_tableID);
	if (itr != m_hashAttendenceAttrs.end()) {
		const BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *> & attendenceMap = itr->second;
		BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *>::const_iterator attrItr = attendenceMap.find(a_day);
		if (attrItr != attendenceMap.end()) {
			if (attrItr->second != NULL) {
				return attrItr->second;
			}
		}
	}
	return NULL;
}

const CAttendenceAttr * CActivitySystemDataMgr::getCurAttendenceAttr(BSLib::uint32 a_day) const
{
	return getAttendenceAttr(m_curAttendenceTable, a_day); 
}
const BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *>* CActivitySystemDataMgr::getAttendenceAttrMap(BSLib::uint32 a_tableID) const
{
	BSLib::Utility::CHashMap< BSLib::uint32, BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *> >::const_iterator itr = m_hashAttendenceAttrs.find(a_tableID);
	if (itr != m_hashAttendenceAttrs.end()) {
		return &(itr->second);
	}
	return NULL;
}

const BSLib::Utility::CHashMap<BSLib::uint32, CAttendenceAttr *>* CActivitySystemDataMgr::getCurAttendenceAttrMap() const
{
	return getAttendenceAttrMap(m_curAttendenceTable);
}

bool CActivitySystemDataMgr::_loadAttendenceAttrs(const std::string & a_path)
{
	const BSLib::uint32 C_MAX_PRIZE_SIZE = 5;
	std::string fileName = a_path + "\\attendence\\t_attendence_attr_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);
	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载每日签到奖励数据失败[%s]", fileName.c_str());
		return false;
	}
	try {
		BSLib::Utility::CTable &table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			CAttendenceAttr *attr = new CAttendenceAttr;
			BSLib::uint32 tableID = 0;
			BSLib::Utility::CStringA input(table[i]["f_table_id"]);
			input >> tableID;
			input = table[i]["f_day"];
			input >> attr->m_days;
			input = table[i]["f_emoticon_id"];
			input >> attr->m_emoticonID;
			input = table[i]["f_is_special_prize"];
			BSLib::uint32 special = 0;
			input >> special;
			attr->m_isSpecialPrize = (special != 0);
			for (BSLib::uint32 j = 0; j < C_MAX_PRIZE_SIZE; ++j) {
				GSLib::ItemSystem::GM::CPrizeItem item;
				input = table[i]["f_prize_id_" + BSLib::Utility::CConvert::toStringA(j + 1)];
				if (!input.empty()) {
					input >> item.m_itemTPID;
					input = table[i]["f_prize_count_" + BSLib::Utility::CConvert::toStringA(j + 1)];
					input >> item.m_itemCount;
					if (item.m_itemTPID > 0) {
						attr->m_vecPrizeItems.push_back(item);
					}
				}
			}
			CActivitySystemDataMgr::singleton().addAttendenceAttr(tableID, attr);
		}
	} catch (...) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载每日签到奖励数据失败[%s]", fileName.c_str());
		return false;		
	}

	return true;
}

bool CActivitySystemDataMgr::_loadAttendenceConfig(const std::string & a_path)
{
	std::string fileName = a_path + "\\attendence\\t_attendence_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);
	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载每日签到配置数据失败[%s]", fileName.c_str());
		return false;
	}
	try {
		BSLib::Utility::CTable &table = tableSheet["item"];
		BSLib::Utility::CStringA input(table[0]["f_current_table_id"]);
		input >> m_curAttendenceTable;
	} catch (...) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载每日签到配置数据失败[%s]", fileName.c_str());
		return false;		
	}

	return true;
}
bool CActivitySystemDataMgr::_loadPetCardConfig(const std::string & a_path)
{
	std::string fileName = a_path + "\\drawCard\\t_draw_card_item_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);
	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载抽卡宠物物品数据失败[%s]", fileName.c_str());
		return false;
	}
	try {
		BSLib::Utility::CTable &table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			CPetCardInfo petCardInfo;
			table[i]["f_pet_id"] >> petCardInfo.m_petTPID;
			table[i]["f_level"] >> petCardInfo.m_level;
			if (petCardInfo.m_level > (BSLib::uint32)MAX_DRAW_CARD_LEVEL) {
				BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载抽卡宠物物品数据失败[%s], 卡牌[%d]类型超过最大上限", fileName.c_str(), petCardInfo.m_petTPID);
				return false;
			}
			table[i]["f_pet_weight"] >> petCardInfo.m_petWeight;
			table[i]["f_pet_piece_id"] >> petCardInfo.m_petPieceTPID;
			table[i]["f_pet_piece_count"] >> petCardInfo.m_petPieceCount;
			table[i]["f_pet_piece_weight"] >> petCardInfo.m_petPieceWeight;
			m_hashPetCardInfo[0].setValue(petCardInfo.m_petTPID, petCardInfo);
			m_hashPetCardInfo[petCardInfo.m_level].setValue(petCardInfo.m_petTPID, petCardInfo);
		}
	} catch (...) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载抽卡宠物物品数据失败[%s]", fileName.c_str());
		return false;		
	}
	return true;
}

bool CActivitySystemDataMgr::_loadDrawCardWeightBonusConfig(const std::string & a_path)
{
	const BSLib::int32 C_LEVEL = 5;
	std::string fileName = a_path + "\\drawCard\\t_draw_card_weight_bonus_config.xml";
	BSLib::Utility::CDirInfo::standardization(fileName);
	BSLib::Utility::CTableSheet tableSheet;
	if (!tableSheet.loadXmlFile(fileName)) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载抽卡权重加成数据失败[%s]", fileName.c_str());
		return false;
	}
	try {
		BSLib::Utility::CTable &table = tableSheet["item"];
		for (BSLib::uint32 i = 0; i < table.getRowCount(); ++i) {
			BSLib::int32 type = 0;
			BSLib::uint32 para = 0;
			table[i]["f_bouns_type"] >> type;
			if (type < EDRAW_CARD_WEIGHT_BONUS_TYPE_CHARGE || type >= EDRAW_CARD_WEIGHT_BONUS_TYPE_MAX) {
				BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "权重加成类型错误,加载抽卡权重加成数据失败[%s]", fileName.c_str());
				return false;		
			}
			table[i]["f_para"] >> para;
			CCardLevelWeightBonus cardLevelWeightBonus;
			cardLevelWeightBonus.m_para = para;
			for (BSLib::int32 j = 0; j < C_LEVEL; ++j) {
				std::string levelWeightBonus = "f_item_weight_bonus_level_" + BSLib::Utility::CConvert::toStringA(j + 1);
				BSLib::uint32 weight = 0;
				table[i][levelWeightBonus] >> weight;
				cardLevelWeightBonus.m_vecBonus.push_back(weight);
			}
			m_drawCardWeightBonusInfo[type].setValue(cardLevelWeightBonus.m_para, cardLevelWeightBonus);
		}
	} catch (...) {
		BSLIB_LOG_INFOR(ETT_GSLIB_TASKSYSTEM, "加载抽卡权重加成数据失败[%s]", fileName.c_str());
		return false;		
	}
	return true;
}

const BSLib::Utility::CHashMap<BSLib::uint32, CPetCardInfo> & CActivitySystemDataMgr::getPetCardInfoMap(BSLib::uint32 a_level) const
{
	return m_hashPetCardInfo[a_level];
}

} //GM

} //ActivitySystem

} //GSLib
