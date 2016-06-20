using System;
using System.Collections.Generic;
using System.Text;

namespace UnityGMClient
{
    public partial class CClientCore : UnityUtility.CSingletonBase<CClientCore>
    {
        /// <summary>
        /// 学习技能回调
        /// </summary>
        /// <param name="error"></param>
        /// <param name="skillTPID"></param>
        public delegate void CBMsgSkillSystemGM2GCAckLearnSkill(ELearnSkillError error, UInt32 skillTPID);

        /// <summary>
        /// 学习技能
        /// </summary>
        /// <param name="skillTPID"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSkillSystemGC2GMReqLearnSkill(UInt32 skillTPID, CBMsgSkillSystemGM2GCAckLearnSkill cb)
        {
            CMsgSkillSystemGC2GMReqLearnSkill req = new CMsgSkillSystemGC2GMReqLearnSkill(skillTPID);
            CMsgSkillSystemGM2GCAckLearnSkill.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }

        /// <summary>
        /// 升级技能回调
        /// </summary>
        /// <param name="error"></param>
        /// <param name="cb"></param>
        public delegate void CBMsgSkillSystemGM2GCAckUpgradeSkill(EUpgradeSkillError error, UInt32 skillTPID);

        /// <summary>
        /// 升级技能
        /// </summary>
        /// <param name="skillTPID"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSkillSystemGC2GMReqUpgradeSkill(UInt32 skillTPID, CBMsgSkillSystemGM2GCAckUpgradeSkill cb)
        {
            CMsgSkillSystemGC2GMReqUpgradeSkill req = new CMsgSkillSystemGC2GMReqUpgradeSkill(skillTPID);
            CMsgSkillSystemGM2GCAckUpgradeSkill.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }


        /// <summary>
        /// 初始化技能列表回调
        /// </summary>
        /// <param name="listSkill"></param>
        public delegate void CBMsgSkillSystemGM2GCAckInitRoleSkillData(List<CSkill> listSkill, UInt32[] skillButtons);
        public void RegisterInitRoleSkillDataCallBack(CBMsgSkillSystemGM2GCAckInitRoleSkillData cb)
        {
            CMsgSkillSystemGM2GCAckInitRoleSkillData.s_cb = cb;
        }

        /// <summary>
        /// 设置技能按钮回调
        /// </summary>
        /// <param name="error"></param>
        /// <param name="skillButtons"></param>
        public delegate void CBMsgSkillSystemGM2GCAckSetSkillButton(ESetSkillButtonError error, UInt32[] skillButtons);

        /// <summary>
        /// 设置技能按钮
        /// </summary>
        /// <param name="skillTPID"></param>
        /// <param name="skillButtonIndex"></param>
        /// <param name="cb"></param>
        /// <returns></returns>
        public bool SendMsgSkillSystemGC2GMReqSetSkillButton(UInt32 skillTPID, byte skillButtonIndex, CBMsgSkillSystemGM2GCAckSetSkillButton cb)
        {
            CMsgSkillSystemGC2GMReqSetSkillButton req = new CMsgSkillSystemGC2GMReqSetSkillButton(skillTPID, skillButtonIndex);
            CMsgSkillSystemGM2GCAckSetSkillButton.s_cb = cb;
            return CGameClient.Singleton.SendMsg(req);
        }
    }

}
