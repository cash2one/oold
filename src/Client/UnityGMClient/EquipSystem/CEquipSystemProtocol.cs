using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    partial class CEquipSystem
    {
        public void Init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCAckGetEquipItem), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCReqAckEquipItem));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCNtfUpdateRoleEquipData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCNtfUpdateRoleEquipData));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCAckEquipData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCAckEquipData));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCAckNextAddLevelEquip), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCAckNextAddLevelEquip));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCAckCondition), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCAckCondition));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCAckSaveOperation), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCAckSaveOperation));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCAckResetAttr), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCAckResetAttr));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCAckChangeEquipStatus), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCAckChangeEquipStatus));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCAckUpgradeLevel), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCAckUpgradeLevel));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCAckUpgradeQuality), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCAckUpgradeQuality));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCAckGemCombine), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCAckGemCombine));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCAckChangeGemStatus), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCAckChangeGemStatus));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCAckDisassemblyEquip), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCAckDisassemblyEquip));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgEquipSystemGM2GCAckGetDisassemblyEquipResult), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgEquipSystemGM2GCAckGetDisassemblyEquipResult));
        }

        private void OnMsgEquipSystemGM2GCReqAckEquipItem(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCAckGetEquipItem ack = (CMsgEquipSystemGM2GCAckGetEquipItem)msgData;
            CMsgEquipSystemGM2GCAckGetEquipItem.CallBack(ack);
        }

        private void OnMsgEquipSystemGM2GCNtfUpdateRoleEquipData(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCNtfUpdateRoleEquipData ack = (CMsgEquipSystemGM2GCNtfUpdateRoleEquipData)msgData;
            CMsgEquipSystemGM2GCNtfUpdateRoleEquipData.CallBack(ack);
        }

        private void OnMsgEquipSystemGM2GCAckUpgradeLevel(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCAckUpgradeLevel ack = (CMsgEquipSystemGM2GCAckUpgradeLevel)msgData;
            CMsgEquipSystemGM2GCAckUpgradeLevel.CallBack(ack);
        }

        private void OnMsgEquipSystemGM2GCAckNextAddLevelEquip(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCAckNextAddLevelEquip ack = (CMsgEquipSystemGM2GCAckNextAddLevelEquip)msgData;
            CMsgEquipSystemGM2GCAckNextAddLevelEquip.CallBack(ack);
        }

        private void OnMsgEquipSystemGM2GCAckUpgradeQuality(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCAckUpgradeQuality ack = (CMsgEquipSystemGM2GCAckUpgradeQuality)msgData;
            CMsgEquipSystemGM2GCAckUpgradeQuality.CallBack(ack);
        }

        private void OnMsgEquipSystemGM2GCAckGemCombine(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCAckGemCombine ack = (CMsgEquipSystemGM2GCAckGemCombine)msgData;
            CMsgEquipSystemGM2GCAckGemCombine.CallBack(ack);
        }

        private void OnMsgEquipSystemGM2GCAckChangeGemStatus(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCAckChangeGemStatus ack = (CMsgEquipSystemGM2GCAckChangeGemStatus)msgData;
            CMsgEquipSystemGM2GCAckChangeGemStatus.CallBack(ack);
        }

        private void OnMsgEquipSystemGM2GCAckDisassemblyEquip(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCAckDisassemblyEquip ack = (CMsgEquipSystemGM2GCAckDisassemblyEquip)msgData;
            CMsgEquipSystemGM2GCAckDisassemblyEquip.CallBack(ack);
        }

        private void OnMsgEquipSystemGM2GCAckGetDisassemblyEquipResult(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCAckGetDisassemblyEquipResult ack = (CMsgEquipSystemGM2GCAckGetDisassemblyEquipResult)msgData;
            CMsgEquipSystemGM2GCAckGetDisassemblyEquipResult.CallBack(ack);
        }

        private void OnMsgEquipSystemGM2GCAckResetAttr(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCAckResetAttr ack = (CMsgEquipSystemGM2GCAckResetAttr)msgData;
            CMsgEquipSystemGM2GCAckResetAttr.CallBack(ack);
        }

        private void OnMsgEquipSystemGM2GCAckEquipData(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCAckEquipData ack = (CMsgEquipSystemGM2GCAckEquipData)msgData;
            CMsgEquipSystemGM2GCAckEquipData.CallBack(ack);
        }

        private void OnMsgEquipSystemGM2GCAckCondition(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCAckCondition ack = (CMsgEquipSystemGM2GCAckCondition)msgData;
            CMsgEquipSystemGM2GCAckCondition.CallBack(ack);
        }

        private void OnMsgEquipSystemGM2GCAckSaveOperation(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCAckSaveOperation ack = (CMsgEquipSystemGM2GCAckSaveOperation)msgData;
            CMsgEquipSystemGM2GCAckSaveOperation.CallBack(ack);
        }

        private void OnMsgEquipSystemGM2GCAckChangeEquipStatus(UnityFrame.CMsg msgData)
        {
            CMsgEquipSystemGM2GCAckChangeEquipStatus ack = (CMsgEquipSystemGM2GCAckChangeEquipStatus)msgData;
            CMsgEquipSystemGM2GCAckChangeEquipStatus.CallBack(ack);
        }
    }
}
