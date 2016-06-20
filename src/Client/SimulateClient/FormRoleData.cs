using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SimulateClient
{
    public partial class FormRoleData : Form
    {
     
        private static FormRoleData g_FormRoleData = null;
        UnityGMClient.SRoleKey m_currentRoleKey = new UnityGMClient.SRoleKey();
        UnityGMClient.SRoleKey m_roleKey = new UnityGMClient.SRoleKey();

        string m_cmd = "";
        string m_strP0 = "";
        string m_strP1 = "";
        string m_strP2 = "";

        public static void showForm()
        {
            if (g_FormRoleData == null)
            {
                g_FormRoleData = new FormRoleData();
            }
            
            g_FormRoleData.Show();
            g_FormRoleData.TimerStart();
            g_FormRoleData.initFormData();
        }

         public static void showLog(string msg)
         {
             FormRoleData form = FormRoleData.getForm();
             form.Log(msg);
        }

        public static FormRoleData getForm()
        {
            if (g_FormRoleData == null)
            {
                g_FormRoleData = new FormRoleData();
            }
            return g_FormRoleData;
        }

        private void timerWait_Tick(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Update(0);
        }

        public void TimerStart()
        {
            timerWait.Start();
        }

        private void Log(string content)
        {
            string lg = "[" + this.Name.ToString() + "  " + content + "";
            GC.CLog.write(lg);
            textRoleData.Text = lg;
        }

        private void FormRoleData_FormClosed(object sender, FormClosedEventArgs e)
        {
            this.Hide();
            g_FormRoleData = null;
            timerWait.Stop();
            FormMain.showForm();
        }

        public FormRoleData()
        {
            InitializeComponent();
        }

        private void getRoleData_Click(object sender, EventArgs e)
        {
            try
            {
                m_roleKey.m_accountID = ulong.Parse(textBoxAccountID.Text);
                m_roleKey.m_zoneID = UInt16.Parse(textBoxZoneID.Text);
                m_roleKey.m_roleIndex = UInt32.Parse(textBoxIndex.Text);
            }
            catch (Exception except)
            {
                UnityUtility.CTrace.Singleton.debug(except.ToString());
                this.textRoleData.Text = except.ToString();
                return;
            }

            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqGetRoleData(m_roleKey, cbGetRoleData);
        }

        public void initFormData()
        {
            UnityGMClient.CRole a_roleData = GC.CPlayer.Singleton.getCurRole();
            if (a_roleData != null)
            {
                m_currentRoleKey.m_zoneID = a_roleData.RoleKey.m_zoneID;
                m_currentRoleKey.m_accountID = a_roleData.RoleKey.m_accountID;
                m_currentRoleKey.m_roleIndex = a_roleData.RoleKey.m_roleIndex;

                textBoxAccountID.Text = m_currentRoleKey.m_accountID.ToString();
                textBoxZoneID.Text = m_currentRoleKey.m_zoneID.ToString();
                textBoxIndex.Text = m_currentRoleKey.m_roleIndex.ToString();

                textBoxCMD.Text = "\\AddExp 100";
                string lg = ""
                    + "区号:" + a_roleData.RoleKey.m_zoneID + "  "
                    + "账号:" + a_roleData.RoleKey.m_accountID + "  "
                    + "角色索引:" + a_roleData.RoleKey.m_roleIndex + " "
                    + "角色ID:" + a_roleData.getRoleID() + "  "
                    + "昵称:" + a_roleData.getRoleName() + "  "
                    + "职业:" + a_roleData.getRoleTPID() + "  "
                    + "等级:" + a_roleData.getLevel() + "\r\n"
                    + "技能点:" + a_roleData.getSkillPoint() + "  "
                    + "PVP币:" + a_roleData.getPVPCoin() + "  "
                    + "体力:" + a_roleData.getVitality() + "  "
                    + "金币:" + a_roleData.getGold() + "  "
                    + "经验:" + a_roleData.getExp() + "  "
                    + "钻石:" + a_roleData.getDiamond() + "  "
                    + "vip积分:" + a_roleData.getVipScore() + "  "
                    + "vip等级:" + a_roleData.getVipLevel() + "  "
                    + "活跃度:" + a_roleData.getActiveDegree() + "\r\n\r\n";

                UnityUtility.CTrace.Singleton.debug(lg);
                g_FormRoleData.textRoleData.Text = lg;
            }
        }

        private void cbGetRoleData(UnityGMClient.EGetRoleDataResult a_retCode, UnityGMClient.CRole a_roleData)
        {
            if (a_retCode != UnityGMClient.EGetRoleDataResult.EGETROLEDATA_RESUlT_SUCCESS)
            {
                UnityUtility.CTrace.Singleton.debug("获取角色信息失败！");
                this.textRoleData.Text = "获取角色信息失败！";
                return;
            }
            if (a_roleData != null)
            {
                string lg = ""
                    + "区号:" + m_roleKey.m_zoneID + "  "
                    + "账号:" + m_roleKey.m_accountID + "  "
                    + "角色索引:" + m_roleKey.m_roleIndex + " "
                    + "角色ID:" + a_roleData.getRoleID() + "  "
                    + "昵称:" + a_roleData.getRoleName() + "  "
                    + "职业:" + a_roleData.getRoleTPID() + "  "
                    + "等级:" + a_roleData.getLevel() + "\r\n"
                    + "技能点:" + a_roleData.getSkillPoint() + "  "
                    + "PVP币:" + a_roleData.getPVPCoin() + "  "
                    + "体力:" + a_roleData.getVitality() + "  "
                    + "金币:" + a_roleData.getGold() + "  "
                    + "经验:" + a_roleData.getExp() + "  "
                    + "钻石:" + a_roleData.getDiamond() + "  "
                    + "vip积分:" + a_roleData.getVipScore() + "  "
                    + "vip等级:" + a_roleData.getVipLevel() + "  "
                    + "活跃度:" + a_roleData.getActiveDegree() + "\r\n\r\n";

                lg += "战斗力(Combat):" + a_roleData.getCombat()+ "   ";
                lg +=  a_roleData.getBattleAttr().getLogString();
                UnityUtility.CTrace.Singleton.debug(lg);
                this.textRoleData.Text = lg;
            }
        }

        private void getRoleMsgToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                m_roleKey.m_accountID = ulong.Parse(textBoxAccountID.Text);
                m_roleKey.m_zoneID = UInt16.Parse(textBoxZoneID.Text);
                m_roleKey.m_roleIndex = UInt32.Parse(textBoxIndex.Text);
            }
            catch (Exception except)
            {
                UnityUtility.CTrace.Singleton.debug(except.ToString());
                this.textRoleData.Text = except.ToString();
                return;
            }

            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqGetRoleData(m_roleKey, cbGetRoleData);
        }

        private void getVipStatusToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 vipLevel = 1;
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqVipLevelGiftStatus(vipLevel,
                delegate(UnityGMClient.EVipLevelGiftStatusResult a_result, UInt32 a_vipLevel, UnityGMClient.EGetVipGiftStatus a_status)
                { ;});
        }

        private void getvipGiftToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 vipLevel = 1;
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqGetVipLevelGift(vipLevel,
                delegate(UnityGMClient.EGetVipLevelGiftResult a_result, UInt32 a_vipLevel, Int32 a_nextVipLevel)
                {

                });

            if (!bResult)
            {
                MessageBox.Show("发送获取vip礼包失败！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void addItemToolStripMenuItem_Click(object sender, EventArgs e)
        {
            textBoxCMD.Text = "\\AddItem " + GC.CItemTPID.LV1_EQUIP_WEAPONS + " 2";
            comboBoxSendCmd.SelectedIndex = comboBoxSendCmd.Items.IndexOf(GC.CCmd.CMD_CMD_MSG);
        }

        private void addDiamondToolStripMenuItem_Click(object sender, EventArgs e)
        {
            textBoxCMD.Text = "\\AddDiamond 100";
        }

        private void addGoldToolStripMenuItem_Click(object sender, EventArgs e)
        {
            textBoxCMD.Text = "\\AddGold 100";
        }

        private void updateLevelToolStripMenuItem_Click(object sender, EventArgs e)
        {
            textBoxCMD.Text = "\\UpdateLevel 2";
        }

        private void getRoleListToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.textRoleData.Text = GC.CPlayer.Singleton.getPlayerDataToLogString();
        }

        private void getEquipInfoToolStripMenuItem_Click(object sender, EventArgs e)
        {
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqEquipData(UnityGMClient.EReqEquipType.REQ_EQUIP_ALL, delegate(UnityGMClient.EEquipDataResult retCode, UnityGMClient.CEquipData equipData)
              {
                   string lg = "[CbEquipData][retCode=" + retCode.ToString() + "]";
                   Log(lg);
                   if (retCode != UnityGMClient.EEquipDataResult.EEQUIPEDATA_RESUlT_SUCCESS) {
                       return;
                   }
                   string lgs = equipData.getLogString();
                   Log(lgs);
              });
        }

        private void getBagDataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.textRoleData.Text = GC.CPlayer.Singleton.getBagDataToLogString();
        }

        private void getPetDataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGM2GCReqInitPetData(
              delegate(UnityGMClient.EGetInitRolePetDataResult retCode, UnityGMClient.CPetData petData)
              {
                  string lg = "EGetInitRolePetDataResult:" + retCode.ToString();
                  Log(lg);
                  GC.CPlayer.Singleton.setPetData(petData);
                  this.textRoleData.Text = GC.CPlayer.Singleton.getPetDataToLogString();
              });
        }

        private void getPlayerInfoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.textRoleData.Text = GC.CPlayer.Singleton.getPlayerDataToLogString();
        }

        private void getRoleLocalInfoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.textRoleData.Text = GC.CPlayer.Singleton.getRoleDataToLogString();
        }

        private void getAchievePrizeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqGetAchievePrize(1,
              delegate(UnityGMClient.EGetAchievePrizeResult retCode, UInt32 a_achieveID)
              {
                  textBoxCMD.Text = "[ack][getAchievePrize]";
              });
        }

        private void reconnectGameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgReConnectServer();

        }

        private void disconnectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgDisconnectGame();
        }

        private void saveAchieveDataToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 subTypeID = 300;
            UInt32 bossID = 1;
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqSaveAchieveData(subTypeID,bossID,
               delegate(UnityGMClient.ESaveAchieveDataResult retCode)
               {
                   string msg = "[ack][saveAchieveData][retCode=" + retCode.ToString() + "]";
                   Log(msg);
               });
        }

        private void saveAchieveDataInstanceIDToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 subTypeID = 401;
            UInt32 instanceID = 1;
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqSaveAchieveData(subTypeID, instanceID,
               delegate(UnityGMClient.ESaveAchieveDataResult retCode)
               {
                   string msg = "[ack][saveAchieveDataInstance][retCode=" + retCode.ToString() + "]";
                   Log(msg);
               });
        }

        private void achieveTestToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        private void RoleLevelAchieveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqGetAchieveList(UnityGMClient.EAchieveType.ACHIEVE_LEVEL,cbGetAchieveList);
        }

        private void BattleAchieveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqGetAchieveList(UnityGMClient.EAchieveType.ACHIEVE_COMBAT,cbGetAchieveList);
        }

        private void cbGetAchieveList(UnityGMClient.EGetAchieveListResult a_retCode, UnityGMClient.CAchieveData a_achieveData)
        {
            string msg = "[ack][getAchieveList][AchieveCount=" + a_achieveData.AchieveCount + "]";
            if (a_achieveData != null)
            {
                msg += a_achieveData.getAllAchieveToLogString();
            }
            Log(msg);
       }

        private void ChargePayAchieveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqGetAchieveList(UnityGMClient.EAchieveType.ACHIEVE_CHARGE, cbGetAchieveList);
        }

        private void PetAchieveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqGetAchieveList(UnityGMClient.EAchieveType.ACHIEVE_PET, cbGetAchieveList);
        }

        private void SkillAchieveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqGetAchieveList(UnityGMClient.EAchieveType.ACHIEVE_SKILL, cbGetAchieveList);
        }

        private void GemAchieveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqGetAchieveList(UnityGMClient.EAchieveType.ACHIEVE_GEM, cbGetAchieveList);
        }

        private void EquipAchieveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqGetAchieveList(UnityGMClient.EAchieveType.ACHIEVE_EQUIP, cbGetAchieveList);
        }

        private void PassStageCountToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqGetAchieveList(UnityGMClient.EAchieveType.ACHIEVE_PASS_STAGE, cbGetAchieveList);
        }

        private void DiceAchieveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqGetAchieveList(UnityGMClient.EAchieveType.ACHIEVE_DICE, cbGetAchieveList);
        }

        private void pvpAchieveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqGetAchieveList(UnityGMClient.EAchieveType.ACHIEVE_PVP, cbGetAchieveList);
        }

        private void PassStageAchieveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqGetAchieveList(UnityGMClient.EAchieveType.ACHIEVE_PASS_INSTANCE, cbGetAchieveList);
        }

        private void KillBossAchieveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgAchieveSystemGC2GMReqGetAchieveList(UnityGMClient.EAchieveType.ACHIEVE_KILL_BOSS, cbGetAchieveList);
        }

        public void CBMsgPetSystemGM2GCAckHotSpringTaskEnd(UnityGMClient.EHotSpringTaskEndResult retCode, UInt32 PetID, UnityGMClient.EPetStatus petStatus)
        {
            string msg = "[CBMsgPetSystemGM2GCAckHotSpringTaskEnd][retCode=" + retCode.ToString() + "]";
            Log(msg);
        }

        private void comboBoxSendCmd_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.comboBoxSendCmd.Items != null && comboBoxSendCmd.Items.Count > 0 && comboBoxSendCmd.SelectedItem != null)
            {
                m_cmd = this.comboBoxSendCmd.SelectedItem.ToString();
            }
        }

        private void btnDo_Click(object sender, EventArgs e)
        {
            m_strP0 = textBoxCMD.Text.ToString();
            m_strP1 = this.p1.Text.ToString();
            m_strP2 = this.p2.Text.ToString();

            this.textRoleData.Text = GC.CCmdMgr.Singleton.sendCmd(m_cmd, m_strP0, m_strP1, m_strP2);
        }

        private void buyVitality(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqBuyVitality(CBBuyVitality);
        }


        private void getVitality(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqGetVitality(CBGetVitality);
        }

        private void getNeedDiamond(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqGetBuyVitalityNeedDiamond(CBGetBuyVitalityDiamond);
        }


        public void CBGetVitality(UnityGMClient.EGetVitalityResult retCode, UInt32 a_vitality, UInt32 a_updateTime)
        {
            string msg = "[CBGetVitality][retCode=" + retCode.ToString() + "][a_vitality=" + a_vitality.ToString() + "]";
            Log(msg);
        }

        public void CBBuyVitality(UnityGMClient.EBuyVitalityResult retCode, UInt32 a_vitality)
        {
            string msg = "[CBBuyVitality][retCode=" + retCode.ToString() + "][a_vitality=" + a_vitality.ToString() + "]";
            Log(msg);
        }


        public void CBGetBuyVitalityDiamond(UnityGMClient.EGetNeedDiamondResult retCode, UnityGMClient.CVitalityData a_vitalityData)
        {
            string msg = "[CBBuyVitality][retCode=" + retCode.ToString() + "]";
            Log(msg);
        }

        private void UseVitalityProToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if ((textBoxCMD.Text == ""))
            {
                MessageBox.Show("物品信息不能为空！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            try
            {
                UnityGMClient.EItemType type = UnityGMClient.EItemType.EITEM_TP_PROP_VITALITY;
                uint index = UInt32.Parse(textBoxCMD.Text);
                UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqUseBagItemData(type, index, CbUseBagItemData);
            }
            catch (Exception exc)
            {
                Log(exc.ToString());
            }
        }

        private void CbUseBagItemData(UnityGMClient.EUseBagItemDataResult retCode)
        {
            if (retCode != UnityGMClient.EUseBagItemDataResult.EUSEITEMPACKAGEDATA_RESUlT_SUCCESS)
            {
                string msg = string.Format("操作失败！msg:{0}", retCode.ToString());
                MessageBox.Show(msg, "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            string lg = GC.CPlayer.Singleton.getBagDataToLogString();
            Log(lg);
        }

        private void 获取背包数据ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqGetBagData(CbGetBagData);
        }

        private void CbGetBagData(UnityGMClient.EGetBagDataResult retCode, UnityGMClient.CBagData bagData)
        {
            string lg = "[CbInitBagData][retCode=" + retCode.ToString() + "][bagData.BagSize=" + bagData.BagSize + "]\r\n";
            Log(lg);
            if (retCode != UnityGMClient.EGetBagDataResult.EINITPACKAGEDATA_RESUlT_SUCCESS)
            {
                lg = "[CbInitBagData][retCode=" + retCode.ToString() + "]\r\n";
                Log(lg);
                return;
            }

            GC.CPlayer.Singleton.CbGetBagData(retCode, bagData);
            this.textRoleData.Text = GC.CPlayer.Singleton.getBagDataToLogString();
        }

        private void PurchaseGoldToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqPurchaseGold(delegate(UnityGMClient.EPurchaseGoldResult result, UInt32 remainTimes, UInt32 maxTimes)
            {
                string resultStr = string.Format("PurchaseGold result[{0}] remainTime[{1}] maxTimes[{2}]", result, remainTimes, maxTimes);
                textRoleData.Text = textRoleData.Text + resultStr + "\r\n";
            });
        }

        private void GetPurchaseGoldInfoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqGetPurchaseGoldInfo(delegate(UnityGMClient.EGetPurchaseGoldInfoResult result, UInt32 remainTimes, UInt32 maxTimes)
            {
                string resultStr = string.Format("GetPurchaseGoldInfo result[{0}] remainTime[{1}] maxTimes[{2}]", result, remainTimes, maxTimes);
                textRoleData.Text = textRoleData.Text + resultStr + "\r\n";
            });
        }




    }
}
