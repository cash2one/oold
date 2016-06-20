using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    partial class CSkillSystem
    {
        public void Init()
        {
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSkillSystemGM2GCAckLearnSkill), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSkillSystemGM2GCAckLeranSkill));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSkillSystemGM2GCAckUpgradeSkill), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSkillSystemGM2GCAckUpgradeSkill));
            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSkillSystemGM2GCAckInitRoleSkillData), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSkillSystemGM2GCAckInitRoleSkillData));

            CGameClient.Singleton.MsgExecMgr.AddParseMsgCb(typeof(CMsgSkillSystemGM2GCAckSetSkillButton), new UnityFrame.CMsgExecMgr.ParseMessageCallback(OnMsgSkillSystemGM2GCAckSetRoleSkillButton));
        }

        private void OnMsgSkillSystemGM2GCAckLeranSkill(UnityFrame.CMsg msgData)
        {
            CMsgSkillSystemGM2GCAckLearnSkill ack = (CMsgSkillSystemGM2GCAckLearnSkill)msgData;
            CMsgSkillSystemGM2GCAckLearnSkill.CallBack(ack);
        }

        private void OnMsgSkillSystemGM2GCAckUpgradeSkill(UnityFrame.CMsg msgData)
        {
            CMsgSkillSystemGM2GCAckUpgradeSkill ack = (CMsgSkillSystemGM2GCAckUpgradeSkill)msgData;
            CMsgSkillSystemGM2GCAckUpgradeSkill.CallBack(ack);
        }

        private void OnMsgSkillSystemGM2GCAckInitRoleSkillData(UnityFrame.CMsg msgData)
        {
            CMsgSkillSystemGM2GCAckInitRoleSkillData ack = (CMsgSkillSystemGM2GCAckInitRoleSkillData)msgData;
            CMsgSkillSystemGM2GCAckInitRoleSkillData.CallBack(ack);
        }

        private void OnMsgSkillSystemGM2GCAckSetRoleSkillButton(UnityFrame.CMsg msgData)
        {
            CMsgSkillSystemGM2GCAckSetSkillButton ack = (CMsgSkillSystemGM2GCAckSetSkillButton)msgData;
            CMsgSkillSystemGM2GCAckSetSkillButton.CallBack(ack);
        }

    }
}
