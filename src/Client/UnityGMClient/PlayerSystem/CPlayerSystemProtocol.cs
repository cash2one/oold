using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    partial class CPlayerSystem
    {
        public void Init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCNtfInitRoleData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCNtfInitRoleData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckGetBagData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckBagData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCNtfBagData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCNtfInitBagData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCNtfUpdateBagItemData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCNtfUpdateBagItemData));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCNtfUpdateBagSize), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCNtfUpdateBagSize));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckPlayerData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckPlayerData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckCreateRole), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckCreateRole));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckSelectRole), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckSelectRole));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckRoleQuit), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckRoleQuit));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckDeleteRole), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckDeleteRole));
            
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckSoldBagItemData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckSoldBagItemData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckUseBagItemData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckUseBagItemData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckGetRoleData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckGetRoleData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckUpdateSkillPoint), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckUpdateSkillPoint));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckGetVitality), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckGetVitality));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckBuyVitality), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckBuyVitality));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckGetVipLevelGift), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckGetVipLevelGift));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckVipLevelGiftStatus), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckVipLevelGiftStatus));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckPurchaseGold), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckPurchaseGold));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo));


        }

        public void OnMsgPlayerSystemGM2GCAckPlayerData(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckPlayerData ack = (CMsgPlayerSystemGM2GCAckPlayerData)msgData;
            CMsgPlayerSystemGM2GCAckPlayerData.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCAckCreateRole(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckCreateRole ack = (CMsgPlayerSystemGM2GCAckCreateRole)msgData;
            CMsgPlayerSystemGM2GCAckCreateRole.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCAckDeleteRole(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckDeleteRole ack = (CMsgPlayerSystemGM2GCAckDeleteRole)msgData;
            CMsgPlayerSystemGM2GCAckDeleteRole.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCAckSelectRole(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckSelectRole ack = (CMsgPlayerSystemGM2GCAckSelectRole)msgData;
            CMsgPlayerSystemGM2GCAckSelectRole.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCNtfInitRoleData(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCNtfInitRoleData ack = (CMsgPlayerSystemGM2GCNtfInitRoleData)msgData;
            CMsgPlayerSystemGM2GCNtfInitRoleData.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute ack = (CMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute)msgData;
            CMsgPlayerSystemGM2GCNtfUpdateRoleBattleAttribute.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute ack = (CMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute)msgData;
            CMsgPlayerSystemGM2GCNtfUpdateUInt32Attribute.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute ack = (CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute)msgData;
            CMsgPlayerSystemGM2GCNtfUpdateUInt64Attribute.CallBack(ack);
        }
        
        public void OnMsgPlayerSystemGM2GCAckRoleQuit(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckRoleQuit ack = (CMsgPlayerSystemGM2GCAckRoleQuit)msgData;
            CMsgPlayerSystemGM2GCAckRoleQuit.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCAckBagData(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckGetBagData ack = (CMsgPlayerSystemGM2GCAckGetBagData)msgData;
            CMsgPlayerSystemGM2GCAckGetBagData.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCNtfInitBagData(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCNtfBagData ack = (CMsgPlayerSystemGM2GCNtfBagData)msgData;
            CMsgPlayerSystemGM2GCNtfBagData.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCAckSoldBagItemData(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckSoldBagItemData ack = (CMsgPlayerSystemGM2GCAckSoldBagItemData)msgData;
            CMsgPlayerSystemGM2GCAckSoldBagItemData.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCAckUseBagItemData(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckUseBagItemData ack = (CMsgPlayerSystemGM2GCAckUseBagItemData)msgData;
            CMsgPlayerSystemGM2GCAckUseBagItemData.CallBack(ack);
        } 

        public void OnMsgPlayerSystemGM2GCNtfUpdateBagItemData(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCNtfUpdateBagItemData ack = (CMsgPlayerSystemGM2GCNtfUpdateBagItemData)msgData;
            CMsgPlayerSystemGM2GCNtfUpdateBagItemData.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCNtfUpdateBagSize(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCNtfUpdateBagSize ack = (CMsgPlayerSystemGM2GCNtfUpdateBagSize)msgData;
            CMsgPlayerSystemGM2GCNtfUpdateBagSize.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore ack = (CMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore)msgData;
            CMsgPlayerSystemGM2GCNtfUpdatePlayerVipScore.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCAckGetRoleData(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckGetRoleData ack = (CMsgPlayerSystemGM2GCAckGetRoleData)msgData;
            CMsgPlayerSystemGM2GCAckGetRoleData.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCAckUpdateSkillPoint(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckUpdateSkillPoint ack = (CMsgPlayerSystemGM2GCAckUpdateSkillPoint)msgData;
            CMsgPlayerSystemGM2GCAckUpdateSkillPoint.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCAckGetVitality(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckGetVitality ack = (CMsgPlayerSystemGM2GCAckGetVitality)msgData;
            CMsgPlayerSystemGM2GCAckGetVitality.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCAckBuyVitality(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckBuyVitality ack = (CMsgPlayerSystemGM2GCAckBuyVitality)msgData;
            CMsgPlayerSystemGM2GCAckBuyVitality.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond ack = (CMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond)msgData;
            CMsgPlayerSystemGM2GCAckGetBuyVitalityDiamond.CallBack(ack);
        }
        
        public void OnMsgPlayerSystemGM2GCAckGetVipLevelGift(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckGetVipLevelGift ack = (CMsgPlayerSystemGM2GCAckGetVipLevelGift)msgData;
            CMsgPlayerSystemGM2GCAckGetVipLevelGift.CallBack(ack);
        }

        public void OnMsgPlayerSystemGM2GCAckVipLevelGiftStatus(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckVipLevelGiftStatus ack = (CMsgPlayerSystemGM2GCAckVipLevelGiftStatus)msgData;
            CMsgPlayerSystemGM2GCAckVipLevelGiftStatus.CallBack(ack);
        }

        private void OnMsgPlayerSystemGM2GCAckPurchaseGold(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckPurchaseGold ack = (CMsgPlayerSystemGM2GCAckPurchaseGold)msgData;
            CMsgPlayerSystemGM2GCAckPurchaseGold.CallBack(ack);
        }

        private void OnMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo(UnityFrame.CMsg msgData)
        {
            CMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo ack = (CMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo)msgData;
            CMsgPlayerSystemGM2GCAckGetPurchaseGoldInfo.CallBack(ack);
        }









    }
}