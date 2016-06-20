//////////////////////////////////////////////////////////////////////
//	created:	2014/07/25
//	filename: 	GSLib\equipSystem\GM\CEquipGM.h
//	author:	     zhangping	
//	
//	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __GSLIB_PLAYERSYSTEM_GM_ROLESTATICDATAGM_H__
#define __GSLIB_PLAYERSYSTEM_GM_ROLESTATICDATAGM_H__

#include <GFLib/commonServer/commonSystem.h>
#include <GSLib/playerSystem/GM/roleResource.h>
#include <BSLib/utility/table.h>

namespace GSLib
{

namespace PlayerSystem
{

namespace GM
{

struct SBagInitConfig{
	BSLib::uint32 m_tpid;
	BSLib::uint32 m_count;

	SBagInitConfig()
	{
		m_tpid = 0;
		m_count = 0;
	};

	void loadData(BSLib::Utility::CTableRow& a_tableRow)
	{
		a_tableRow["f_id"] >> m_tpid;
		a_tableRow["f_count"] >> m_count;
	}
};

struct SSkillInitConfig{
    BSLib::uint32 m_roleTPID;
    std::map<SkillTPID, SkillLevel> m_skillList;
    SSkillInitConfig()
    {
        m_roleTPID = 0;
    }

    void clear()
    {
        m_skillList.clear();
    }

    bool addSkill(SkillTPID a_skillTPID,SkillLevel a_skillLevel)
    {
        std::map<SkillTPID, SkillLevel>::iterator it = m_skillList.find(a_skillTPID);
        if( it != m_skillList.end()) {
            return false;
        }

        m_skillList.insert( std::make_pair(a_skillTPID, a_skillLevel));
        return true;
    }
};


struct SVipConfig{
    BSLib::uint32 m_level;
    BSLib::uint32 m_score;
    BSLib::uint32 m_buy_vitality_count;
    BSLib::uint32 m_enter_instance_count;
    BSLib::uint32 m_activity_count;

    std::string m_activity_prize;
    std::string m_task_prize;

    std::string m_instance_prize;
    std::string m_charge_prize;
    std::string m_vip_gift;

    BSLib::uint32 m_buy_discount;

    SVipConfig()
    {
        m_level = 0;
        m_score = 0;
        m_buy_vitality_count = 0;
        m_enter_instance_count = 0;
        m_activity_count = 0;
        m_activity_prize = "";
        m_task_prize = "";
        m_instance_prize = "";
        m_charge_prize = "";
        m_buy_discount = 0;
        m_vip_gift = "";
    };

    void loadData(BSLib::Utility::CTableRow& a_tableRow)
    {
        a_tableRow["f_level"] >> m_level;
        a_tableRow["f_vip_score"] >> m_score;
        a_tableRow["f_buy_vitality_count"] >> m_buy_vitality_count;
        a_tableRow["f_enter_instance_count"] >> m_enter_instance_count;
        a_tableRow["f_activity_count"] >> m_activity_count;
        a_tableRow["f_activity_prize"] >> m_activity_prize;
        a_tableRow["f_task_prize"] >> m_task_prize;
        a_tableRow["f_instance_prize"] >> m_instance_prize;
        a_tableRow["f_charge_prize"] >> m_charge_prize;
        a_tableRow["f_buy_discount"] >> m_buy_discount;
        a_tableRow["f_vip_gift"] >> m_vip_gift;
    }
};


}//GM

}//EquipSystem

}//GSLib

#endif//__GSLIB_PLAYERSYSTEM_GM_ROLESTATICDATAGM_H__
