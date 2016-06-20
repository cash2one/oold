using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {
        /// <summary>
        /// 初始化玩家信息回调
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="roleCount"></param>
        /// <param name="roleList"></param>
        public delegate void CBMsgPlayerSystemGM2GCAckPlayerData(EInitRoleListResult retCode, CPlayerData playerData);

        /// <summary>
        /// 初始化玩家信息
        /// </summary>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgPlayerSystemGC2GMReqPlayerData(CBMsgPlayerSystemGM2GCAckPlayerData cb)
        {
            CMsgPlayerSystemGM2GCAckPlayerData.cb = cb;
            CMsgPlayerSystemGC2GMReqPlayerData req = new CMsgPlayerSystemGC2GMReqPlayerData();
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 创建角色回调
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="currentRoleIndex"></param>
        /// <param name="SceneTypeID"></param>
        /// <param name="role"></param>
        public delegate void CBMsgPlayerSystemGM2GCAckCreateRole(ECreateRoleResult retCode, UInt32 currentRoleIndex, CRole role);

        /// <summary>
        /// 创建角
        /// </summary>
        /// <param name="roleName"></param>
        /// <param name="roleType"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgPlayerSystemGC2GMReqCreateRole(string roleName, UInt32 roleType, CBMsgPlayerSystemGM2GCAckCreateRole cb)
        {
            CMsgPlayerSystemGC2GMReqCreateRole req = new CMsgPlayerSystemGC2GMReqCreateRole(roleName, roleType);
            CMsgPlayerSystemGM2GCAckCreateRole.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 选择角色
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="currentRoleIndex"></param>
        /// <param name="SceneTypeID"></param>
        public delegate void CBMsgPlayerSystemGM2GCAckSelectRole(ESelectRoleResult retCode);
        /// <summary>
        ///  选择角色
        /// </summary>
        /// <param name="roleIndex">角色索引</param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgPlayerSystemGC2GMReqSelectRole(UInt32 roleIndex, CBMsgPlayerSystemGM2GCAckSelectRole cb)
        {
            CMsgPlayerSystemGC2GMReqSelectRole req = new CMsgPlayerSystemGC2GMReqSelectRole(roleIndex);
            CMsgPlayerSystemGM2GCAckSelectRole.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 初始角色信息
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="currentRoleIndex"></param>
        /// <param name="SceneTypeID"></param>
        public delegate void CBMsgPlayerSystemGM2GCNtfInitRoleData(EInitRoleDataResult retCode, UInt32 currentRoleIndex, UInt32 SceneTypeID, UnityGMClient.CRole role);
        public void RegisterInitRoleDataCallBack(CBMsgPlayerSystemGM2GCNtfInitRoleData callBackFunction)
        {
            CMsgPlayerSystemGM2GCNtfInitRoleData.cb = callBackFunction;
        }

        public delegate void CBMsgPlayerSystemGM2GCNtfBagData(UnityGMClient.CBagData bagData);
        public void RegisterNtfInitBagDataCallBack(CBMsgPlayerSystemGM2GCNtfBagData cb)
        {
            CMsgPlayerSystemGM2GCNtfBagData.cb = cb;
        }

        /// <summary>
        /// 背包数据回调
        /// </summary>
        public delegate void CBMsgPlayerSystemGM2GCAckGetBagData(EGetBagDataResult retCode, CBagData bagData);
        /// <summary>
        /// 背包数据回调
        /// </summary>
        public bool SendMsgPlayerSystemGC2GMReqGetBagData(CBMsgPlayerSystemGM2GCAckGetBagData cb)
        {
            CMsgPlayerSystemGC2GMReqGetBagData req = new CMsgPlayerSystemGC2GMReqGetBagData();
            CMsgPlayerSystemGM2GCAckGetBagData.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public bool SendMsgPlayerSystemGC2GMReqGetNengLiangQiuBagData(CBMsgPlayerSystemGM2GCAckGetBagData cb)
        {
            CMsgPlayerSystemGC2GMReqGetBagData req = new CMsgPlayerSystemGC2GMReqGetBagData();
            req.m_type = 1;
            CMsgPlayerSystemGM2GCAckGetBagData.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgPlayerSystemGM2GCNtfUpdateBagSize(UInt32 a_bagSize);
        /// <summary>
        /// 注册更新背包项
        /// </summary>
        /// <param name="callBackFunction"></param>
        public void RegisterUpdateBagSizeCallBack(CBMsgPlayerSystemGM2GCNtfUpdateBagSize callBackFunction)
        {
            CMsgPlayerSystemGM2GCNtfUpdateBagSize.cb = callBackFunction;
        }

        public delegate void CBMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore(UInt32 a_vipScore);
        /// <summary>
        /// 注册更新vip积分
        /// </summary>
        /// <param name="callBackFunction"></param>
        public void RegisterUpdatePlayerVipScoreCallBack(CBMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore callBackFunction)
        {
            CMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore.cb = callBackFunction;
        }

        public delegate void CBMsgPlayerSystemGM2GCNtfUpdateBagItemData(EUpdateBagItemDataResult retCode, CItem a_Item);
        /// <summary>
        /// 注册更新背包项
        /// </summary>
        /// <param name="callBackFunction"></param>
        public void RegisterUpdateBagItemDataCallBack(CBMsgPlayerSystemGM2GCNtfUpdateBagItemData callBackFunction)
        {
            CMsgPlayerSystemGM2GCNtfUpdateBagItemData.cb = callBackFunction;
        }

        public delegate void CBMsgPlayerSystemGM2GCAckSoldBagItemData(ESoldBagItemDataResult retCode);
        public bool SendMsgPlayerSystemGC2GMReqSoldBagItemData(EItemType a_type, UInt32 a_itemIndex, UInt32 a_itemCount, CBMsgPlayerSystemGM2GCAckSoldBagItemData cb)
        {
            CMsgPlayerSystemGC2GMReqSoldBagItemData req = new CMsgPlayerSystemGC2GMReqSoldBagItemData(a_type, a_itemIndex, a_itemCount);
            CMsgPlayerSystemGM2GCAckSoldBagItemData.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgPlayerSystemGM2GCAckUseBagItemData(EUseBagItemDataResult retCode);
        public bool SendMsgPlayerSystemGC2GMReqUseBagItemData(EItemType a_type, UInt32 a_itemIndex,CBMsgPlayerSystemGM2GCAckUseBagItemData cb)
        {
            CMsgPlayerSystemGC2GMReqUseBagItemData req = new CMsgPlayerSystemGC2GMReqUseBagItemData(a_type, a_itemIndex);
            CMsgPlayerSystemGM2GCAckUseBagItemData.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 更新角色战斗属性回调
        /// </summary>
        /// <param name="a_battleAttr"></param>
        public delegate void CBMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute(CBattleAttribute a_battleAttr,UInt32 a_combat, UInt32 historyMaxCombatPower);
        /// <summary>
        /// 注册更新角色战斗属性
        /// </summary>
        /// <param name="callBackFunction"></param>
        public void RegisterUpdateRoleBattleAttributeCallBack(CBMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute callBackFunction)
        {
            CMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute.cb = callBackFunction;
        }

        public delegate void CBMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute(EUpdateAttributeResult a_retCode, UInt32 a_attributeIndex, UInt32 a_value);
        /// <summary>
        /// 注册回调
        /// </summary>
        /// <param name="callBackFunction"></param>
        public void RegisterUpdateUInt32AttributeCallBack(CBMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute callBackFunction)
        {
            CMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute.cb = callBackFunction;
        }

        public delegate void CBMsgPlayerSystemGM2GCAckUpdateUInt64Attribute(EUpdateAttributeResult a_retCode, UInt32 a_attributeIndex, UInt64 a_value);
        /// <summary>
        /// 注册回调
        /// </summary>
        /// <param name="callBackFunction"></param>
        public void RegisterUpdateUInt64AttributeCallBack(CBMsgPlayerSystemGM2GCAckUpdateUInt64Attribute callBackFunction)
        {
            CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute.cb = callBackFunction;
        }

        /// <summary>
        /// 技能点更新
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="a_skillPoint"></param>
        /// <param name="a_updateTime"></param>
        public delegate void CBMsgPlayerSystemGM2GCAckUpdateSkillPoint(EUpdateSkillPointResult retCode, UInt32 a_skillPoint,UInt32 a_updateTime);
        public bool SendMsgPlayerSystemGC2GMReqUpdateSkillPoint(CBMsgPlayerSystemGM2GCAckUpdateSkillPoint cb)
        {
            CMsgPlayerSystemGC2GMReqUpdateSkillPoint req = new CMsgPlayerSystemGC2GMReqUpdateSkillPoint();
            CMsgPlayerSystemGM2GCAckUpdateSkillPoint.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 获取体力
        /// </summary>
        public delegate void CBMsgPlayerSystemGM2GCAckGetVitality(EGetVitalityResult retCode, UInt32 a_vitality, UInt32 a_updateTime);
        public bool SendMsgPlayerSystemGC2GMReqGetVitality(CBMsgPlayerSystemGM2GCAckGetVitality cb)
        {
            CMsgPlayerSystemGC2GMReqGetVitality req = new CMsgPlayerSystemGC2GMReqGetVitality();
            CMsgPlayerSystemGM2GCAckGetVitality.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }
        
        /// <summary>
        /// 购买体力
        /// </summary>
        public delegate void CBMsgPlayerSystemGM2GCAckBuyVitality(EBuyVitalityResult retCode, UInt32 a_vitality);
        public bool SendMsgPlayerSystemGC2GMReqBuyVitality(CBMsgPlayerSystemGM2GCAckBuyVitality cb)
        {
            CMsgPlayerSystemGC2GMReqBuyVitality req = new CMsgPlayerSystemGC2GMReqBuyVitality();
            CMsgPlayerSystemGM2GCAckBuyVitality.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 购买体力所需钻石
        /// </summary>
        /// <param name="retCode">返回码</param>
        /// <param name="vitalityData">购买条件</param>
        public delegate void CBMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond(EGetNeedDiamondResult retCode, CVitalityData vitalityData);
        public bool SendMsgPlayerSystemGC2GMReqGetBuyVitalityNeedDiamond(CBMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond cb)
        {
            CMsgPlayerSystemGC2GMReqGetBuyVitalityDiamond req = new CMsgPlayerSystemGC2GMReqGetBuyVitalityDiamond();
            CMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }
        
        /// <summary>
        /// 角色退出
        /// </summary>
        /// <param name="retCode"></param>
        public delegate void CBMsgPlayerSystemGM2GCAckRoleQuit(ERoleQuitResult retCode);
        /// <summary>
        /// 角色退出
        /// </summary>
        /// <param name="a_roleIndex"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgPlayerSystemGC2GMReqRoleQuit(UInt32 a_roleIndex,CBMsgPlayerSystemGM2GCAckRoleQuit cb)
        {
            CMsgPlayerSystemGC2GMReqRoleQuit req = new CMsgPlayerSystemGC2GMReqRoleQuit(a_roleIndex);
            CMsgPlayerSystemGM2GCAckRoleQuit.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 删除角色
        /// </summary>
        /// <param name="retCode"></param>
        /// <param name="a_roleIndex"></param>
        public delegate void CBMsgPlayerSystemGM2GCAckDeleteRole(EDeleteRoleResult retCode,UInt32 a_roleIndex);
        public bool SendMsgPlayerSystemGC2GMReqDeleteRole(UInt32 a_roleIndex, CBMsgPlayerSystemGM2GCAckDeleteRole cb)
        {
            CMsgPlayerSystemGC2GMReqDeleteRole req = new CMsgPlayerSystemGC2GMReqDeleteRole(a_roleIndex);
            CMsgPlayerSystemGM2GCAckDeleteRole.cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 获取角色详细信息
        /// </summary>
        /// <param name="a_roleData"></param>
        public delegate void CBMsgPlayerSystemGM2GCAckGetRoleData(EGetRoleDataResult a_retCode, CRole a_roleData);
        public bool SendMsgPlayerSystemGC2GMReqGetRoleData(SRoleKey a_roleKey, CBMsgPlayerSystemGM2GCAckGetRoleData a_cb)
        {
            CMsgPlayerSystemGC2GMReqGetRoleData req = new CMsgPlayerSystemGC2GMReqGetRoleData(a_roleKey);
            CMsgPlayerSystemGM2GCAckGetRoleData.cb = a_cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgPlayerSystemGM2GCAckGetVipLevelGift(EGetVipLevelGiftResult a_retCode, UInt32 a_vipLevel, Int32 nextVipLevel);
        public bool SendMsgPlayerSystemGC2GMReqGetVipLevelGift(UInt32 a_vipLevel, CBMsgPlayerSystemGM2GCAckGetVipLevelGift a_cb)
        {
            CMsgPlayerSystemGC2GMReqGetVipLevelGift req = new CMsgPlayerSystemGC2GMReqGetVipLevelGift(a_vipLevel);
            CMsgPlayerSystemGM2GCAckGetVipLevelGift.cb = a_cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgPlayerSystemGM2GCAckVipLevelGiftStatus(EVipLevelGiftStatusResult a_retCode, UInt32 a_vipLevel,EGetVipGiftStatus a_status);
        public bool SendMsgPlayerSystemGC2GMReqVipLevelGiftStatus(UInt32 a_vipLevel, CBMsgPlayerSystemGM2GCAckVipLevelGiftStatus a_cb)
        {
            CMsgPlayerSystemGC2GMReqVipLevelGiftStatus req = new CMsgPlayerSystemGC2GMReqVipLevelGiftStatus(a_vipLevel);
            CMsgPlayerSystemGM2GCAckVipLevelGiftStatus.cb = a_cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        public delegate void CBMsgPlayerSystemGM2GCAckPurchaseGold(EPurchaseGoldResult result, UInt32 remainTimes, UInt32 maxTimes);
        public bool SendMsgPlayerSystemGC2GMReqPurchaseGold(CBMsgPlayerSystemGM2GCAckPurchaseGold cb)
        {
            CMsgPlayerSystemGC2GMReqPurchaseGold req = new CMsgPlayerSystemGC2GMReqPurchaseGold();
            CMsgPlayerSystemGM2GCAckPurchaseGold.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }


        public delegate void CBMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo(EGetPurchaseGoldInfoResult result, UInt32 remainTimes, UInt32 maxTimes);
        public bool SendMsgPlayerSystemGC2GMReqGetPurchaseGoldInfo(CBMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo cb)
        {
            CMsgPlayerSystemGC2GMReqGetPurchaseGoldInfo req = new CMsgPlayerSystemGC2GMReqGetPurchaseGoldInfo();
            CMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }















    }
}
