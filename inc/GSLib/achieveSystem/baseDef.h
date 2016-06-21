#ifndef __GSLIB_ACHIEVESYSTEM_BASEDEF_H__
#define __GSLIB_ACHIEVESYSTEM_BASEDEF_H__

typedef BSLib::uint32 AchieveID;
enum EAchieveType
{
    ACHIEVE_INVALID = 0,
    ACHIEVE_LEVEL = 1,		    //等级成就
    ACHIEVE_COMBAT = 2,         //战斗力成就
    ACHIEVE_KILL_BOSS = 3,		//击杀BOSS成就	
    ACHIEVE_PASS_INSTANCE = 4,  //通关副本成就	
    ACHIEVE_PVP = 5,			//PVP成就	
    ACHIEVE_DICE = 6,			//骰子成就
    ACHIEVE_PASS_STAGE = 7,	    //连续闯关成就
    ACHIEVE_EQUIP = 8,	        //装备成就
    ACHIEVE_GEM = 9,	        //宝石成就
    ACHIEVE_SKILL = 10,	        //技能成就
    ACHIEVE_PET = 11,	        //僚机成就
    ACHIEVE_CHARGEPAY = 12,    	//充值消费成就
};

enum ESubAchieveType
{
    SUB_ACHIEVE_INVALID = 0,
    SUB_ACHIEVE_LEVEL = 100,		    //等级子成就
    SUB_ACHIEVE_COMBAT = 200,           //战斗力子成就
    SUB_ACHIEVE_KILL_BOSS = 300,		//击杀BOSS子成就	
    SUB_ACHIEVE_PASS_INSTANCE = 400,    //通关副本子成就	
    SUB_ACHIEVE_PVP_WINCOUNT = 500,			    //PVP竞技场连胜成就 失败则归0	
    SUB_ACHIEVE_PVP_RANK = 501,			//PVP竞技场排行成就	
    SUB_ACHIEVE_DICE = 600,			    //骰子子成就
    SUB_ACHIEVE_PASS_STAGE = 700,	    //连续闯关子成就
    SUB_ACHIEVE_EQUIP_COLOR = 800,	    //装备子成就  套装
    SUB_ACHIEVE_EQUIP_ONE_LEVEL = 801,	//装备子成就 一件收集 
    SUB_ACHIEVE_EQUIP_FOUR_LEVEL = 802,	//装备子成就 四件收集 
    SUB_ACHIEVE_EQUIP_SIX_LEVEL = 803,	//装备子成就 六件收集 

    SUB_ACHIEVE_GEM = 900,	            //宝石子成就
    SUB_ACHIEVE_SKILL = 1000,	        //技能子成就 个数

    SUB_ACHIEVE_PET_COLOR_PURPLE = 1100,//僚机子成就 紫色僚姬个数
    SUB_ACHIEVE_PET_COLOR_YELLOW = 1101,//僚机子成就 橙色僚姬个数
    SUB_ACHIEVE_PET_COLOR_STARLEVEL = 1102,//僚机子成就 5星级僚姬个数

    SUB_ACHIEVE_VIPLEVEL = 1200,    	//充值消费子成就 vip等级
    SUB_ACHIEVE_CHARGE = 1201,    	    //充值消费子成就 充值宝石数量
    SUB_ACHIEVE_BUY_VIALITY = 1202,    	//充值消费子成就 购买体力次数
};

enum EAchieveStatus
{
    ACHIEVE_STATUS_DOING,     //进行中
    EACHIEVE_STATUS_FINISHED, //已完成
    ACHIEVE_STATUS_PRIZED,    //已领取奖励
};

#endif//__GSLIB_ACHIEVESYSTEM_BASEDEF_H__
