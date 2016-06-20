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
    public partial class FormEquip : Form
    {
        private static FormEquip g_FormEquip = null;

        public static void showForm()
        {
            if (g_FormEquip == null)
            {
                g_FormEquip = new FormEquip();
            }
            g_FormEquip.Show();
            g_FormEquip.TimerStart();
        }

        public static FormEquip getForm()
        {
            if (g_FormEquip == null)
            {
                g_FormEquip = new FormEquip();
            }
            return g_FormEquip;
        }
        public FormEquip()
        {
            InitializeComponent();
            textBoxEquipID.Text = "1";
            textBoxGemID.Text = "0";
            string lg = GC.CPlayer.Singleton.getEquipDataToLogString();
            Log(lg);
        }

        private void Log(string content)
        {
            string lg = "[" + this.Name.ToString() + "]" + content + "";
            GC.CLog.write(lg);
            this.textBoxData.Text = lg;
        }

        private void CbUpgradeLevel(UnityGMClient.EUPGRADELEVELResult retCode, UnityGMClient.CEquipItem equip)
        {
            string lg = "[CbUpgradeLevel][retCode=" + retCode.ToString() + "]";
            Log(lg);
            switch (retCode)
            {
                case UnityGMClient.EUPGRADELEVELResult.EUPGRADELEVEL_RESUlT_SUCCESS:
                    {
                        GC.CHelper.showMsg("强化装备成功！");
                    }
                    break;
                case UnityGMClient.EUPGRADELEVELResult.EUPGRADELEVEL_RESUlT_EQUIP_NOT_EXIST:
                    {
                        GC.CHelper.showMsg("装备不存在！");
                    }
                    break;
                case UnityGMClient.EUPGRADELEVELResult.EUPGRADELEVEL_RESUlT_GOLD_LIMIT:
                    {
                        GC.CHelper.showMsg("金币不足！");
                    }
                    break;
                case UnityGMClient.EUPGRADELEVELResult.EUPGRADELEVEL_RESUlT_LEVEL_LIMIT:
                    {
                        GC.CHelper.showMsg("达到强化等级上限！");
                    }
                    break;
                case UnityGMClient.EUPGRADELEVELResult.EUPGRADELEVEL_RESUlT_METARIAL_LIMIT:
                    {
                        GC.CHelper.showMsg("材料不足！");
                    }
                    break;
                case UnityGMClient.EUPGRADELEVELResult.EUPGRADELEVEL_RESUlT_FAIL:
                    {
                        GC.CHelper.showMsg("强化失败！");
                    }
                    break;
                default: break;
            }
            if (retCode != UnityGMClient.EUPGRADELEVELResult.EUPGRADELEVEL_RESUlT_SUCCESS)
            {
                return;
            }

            lg = equip.getLogString();
            Log(lg);
        }

        private void Evelove_Click(object sender, EventArgs e)
        {
            uint equipID = UInt32.Parse(textBoxEquipID.Text);
            uint itemTPID = GC.CItemTPID.MID_QUALITY_L; // 低级熔炼石
            string lg = "[Evelove_Click][SendMsgEquipSystemGC2GMReqUpgradeQuality][equipID=" + equipID + "]";
            Log(lg);
            UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGC2GMReqUpgradeQuality(equipID,itemTPID, CbUpgradeQuality);
        }

        private void CbUpgradeQuality(UnityGMClient.EUpgradeQualityResult retCode,UnityGMClient.CEquipItem equip)
        {

            string lg = "[CbUpgradeQuality][retCode=" + retCode.ToString() + "]";
            Log(lg);
            switch (retCode)
            {
                case UnityGMClient.EUpgradeQualityResult.EUPGRADEQUALITY_RESUlT_SUCCESS:
                    {
                        GC.CHelper.showMsg("熔炼成功！");
                    }
                    break;
                case UnityGMClient.EUpgradeQualityResult.EUPGRADEQUALITY_RESUlT_FAIL:
                    {
                        GC.CHelper.showMsg("熔炼失败！");
                    }
                    break;
                default: break;
            }
            lg = equip.getLogString();
            Log(lg);
        }


        private void timerWait_Tick(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Update(0);
        }

        public void TimerStart()
        {
            timerWait.Start();
        }

        private void CbGemCombine(UnityGMClient.EGemCombineResult retCode, UInt32 newGemTPID)
        {
            string lg = "[CbUpgradeQuality][retCode=" + retCode.ToString() + "][newGemTPID=" + newGemTPID.ToString() + "]";
            Log(lg);
            switch (retCode)
            {
                case UnityGMClient.EGemCombineResult.EGEM_COMBINE_RESULT_SUCCESS:
                    {
                        GC.CHelper.showMsg("宝石合并成功！");
                    }
                    break;
                case UnityGMClient.EGemCombineResult.EGEM_COMBINE_RESULT_FAIL:
                    {
                        GC.CHelper.showMsg("宝石合并失败！");
                    }
                    break;
                default: break;
            }
            lg = GC.CPlayer.Singleton.getEquipDataToLogString();
            Log(lg);
        }

        private void FormEquip_FormClosed(object sender, FormClosedEventArgs e)
        {
            this.Hide();
            g_FormEquip = null;
            timerWait.Stop();
            FormMain.showForm();
        }

        private void CbEquipData(UnityGMClient.EEquipDataResult retCode, UnityGMClient.CEquipData equipData)
        {
            string lg = "[CbEquipData][retCode=" + retCode.ToString() + "]";
            Log(lg);
            if (retCode != UnityGMClient.EEquipDataResult.EEQUIPEDATA_RESUlT_SUCCESS)
            {
                return;
            }

            string lgs = equipData.getLogString();
            Log(lgs);
        }

        private void CbResetAttr(UnityGMClient.EResetAttrResult retCode, UnityGMClient.CEquipItem equip)
        {
            string lg = "[CbEquipData][retCode=" + retCode.ToString() + "]";
            Log(lg);
            if (retCode != UnityGMClient.EResetAttrResult.ERESETATTR_RESULT_SUCCESS)
            {
                return;
            }

            string equipData = equip.getLogString();
            Log(equipData);
        }

        private void CbCondition(UnityGMClient.EConditionResult retCode, UnityGMClient.CConditionData condition)
        {
            string lg = "[CbEquipData][retCode=" + retCode.ToString() + "]";
            Log(lg);
            if (retCode != UnityGMClient.EConditionResult.ECONDITION_RESUlT_SUCCESS)
            {
                return;
            }

            string logs = condition.getLogString();
            Log(logs);
        }

        private void CbGetEquipItem(UnityGMClient.EGetEquipItemResult retCode, UnityGMClient.CEquipItem equipItem)
        {
            string lg = "[CbGetEquipItem][retCode=" + retCode.ToString() + "]";
            Log(lg);
            if (retCode != UnityGMClient.EGetEquipItemResult.EGETEQUIPITEM_RESUlT_SUCCESS)
            {
                return;
            }

            string logs = equipItem.getLogString();
            Log(logs);
        }

        private void CBGetDisassemblyEquipResult(UnityGMClient.EGetDisassemblyEquipResult retCode,List<UnityGMClient.CPrizeItem> itemList)
        {
            string lg = "[CBGetDisassemblyEquipResult][retCode=" + retCode.ToString() + "]";
            Log(lg);
            if (retCode != UnityGMClient.EGetDisassemblyEquipResult.EGETDISASSEMBLYEQUIP_RESULT_SUCCESS)
            {
                return;
            }
            lg = "";
            for (int i = 0; i < itemList.Count; ++i)
            {
                UnityGMClient.CPrizeItem item = itemList[i];
                lg += item.getLogString() + " ";
            }
            Log(lg);
        }

        private void saveQuality_Click(object sender, EventArgs e)
        {
            uint equipID = UInt32.Parse(textBoxEquipID.Text);
            string lg = "[SendMsgEquipSystemGM2GCReqSaveOperation][equipID=" + equipID + "]";
            Log(lg);
            UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqSaveOperation(equipID, UnityGMClient.EEquipOperation.EQUIP_UPGRADE_QUALITY, UnityGMClient.EOperationResult.OPRESULT_SAVE, CbSaveOperation);
        }

        private void CbSaveOperation(UnityGMClient.ESaveOperationResult retCode, UInt32 equipID)
        {
            string lg = "[CbSaveOperation][retCode=" + retCode.ToString() + "]";
            Log(lg);
        }

        private void CBChangeGemStatus(UnityGMClient.EGemUpdateStatusResult retCode, UnityGMClient.CEquipItem equipItem)
        {
            string lg = "[CbSaveOperation][retCode=" + retCode.ToString() + "]";
            Log(lg);
            if (retCode != UnityGMClient.EGemUpdateStatusResult.EGEM_UPDATESTATUS_RESULT_SUCCESS)
            {
                return;
            }

            string logs = equipItem.getLogString();
            Log(logs);
        }

         private void button2_Click(object sender, EventArgs e)
         {
             
         }
         private void CbChangeEquipStatu(UnityGMClient.EChangeStatusResult retCode, UInt32 equipID, UInt32 itemIndex, UnityGMClient.EEquipStatus status)
         {
             string lg = "[CbChangeEquipStatu][retCode=" + retCode.ToString() + "][equipID=" + equipID + "]";
             Log(lg);

             switch (retCode)
             {
                 case UnityGMClient.EChangeStatusResult.ECHANGESTATUS_RESULT_SUCCESS:
                     {
                         GC.CHelper.showMsg("换装成功！");
                     }
                     break;
                 case UnityGMClient.EChangeStatusResult.ECHANGESTATUS_RESULT_FAIL:
                     {
                         GC.CHelper.showMsg("换装失败！");
                     }
                     break;
                 default: break;
             }

             string equipData = GC.CPlayer.Singleton.getEquipDataToLogString();
             Log(equipData);
         }

         private void CBNextAddLevelEquip(UnityGMClient.EGetNextAddLevelEquipResult retCode, UnityGMClient.CEquipItem equip)
         {
             string lg = "[CBNextAddLevelEquip][retCode=" + retCode.ToString() + "]";
             Log(lg);
             if (retCode != UnityGMClient.EGetNextAddLevelEquipResult.EGETEQUIP_RESULT_SUCCESS)
             {
                 return;
             }

             string logs = equip.getLogString();
             Log(logs);
         }

         private void CBDisassemblyEquip(UnityGMClient.EDisassemblyEquipResult retCode)
         {
             string lg = "[CBDisassemblyEquip][retCode=" + retCode.ToString() + "]";
             Log(lg);
         }

         private void 当前装备ToolStripMenuItem_Click(object sender, EventArgs e)
         {
             uint equipID = UInt32.Parse(textBoxEquipID.Text);
             string lg = "[SendMsgEquipSystemGM2GCReqGetCondition][equipID=" + equipID + "]";
             Log(lg);
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqGetEquipItem(UnityGMClient.EReqGetEquip.REQ_BY_EQUIPID, equipID, CbGetEquipItem);
         }

         private void 下一强化等级装备ToolStripMenuItem_Click(object sender, EventArgs e)
         {
             uint equipID = UInt32.Parse(textBoxEquipID.Text);
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGC2GMReqNextAddLevelEquip(equipID, CBNextAddLevelEquip);
         }

         private void 身上装备ToolStripMenuItem_Click(object sender, EventArgs e)
         {
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqEquipData(UnityGMClient.EReqEquipType.REQ_EQUIP_ON, CbEquipData);
         }

         private void 背包装备ToolStripMenuItem_Click(object sender, EventArgs e)
         {
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqEquipData(UnityGMClient.EReqEquipType.REQ_EQUIP_OFF, CbEquipData);
         }

         private void 全部装备ToolStripMenuItem_Click(object sender, EventArgs e)
         {
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqEquipData(UnityGMClient.EReqEquipType.REQ_EQUIP_ALL, CbEquipData);
         }

         private void 获取强化条件ToolStripMenuItem_Click(object sender, EventArgs e)
         {
             uint equipID = UInt32.Parse(textBoxEquipID.Text);
             string lg = "[SendMsgEquipSystemGM2GCReqGetCondition][equipID=" + equipID + "]";
             Log(lg);
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqGetCondition(equipID, UnityGMClient.EEquipOperation.EQUIP_UPGRADE_NENGLIANGQIU, CbCondition);
         }

         private void 装备强化ToolStripMenuItem_Click(object sender, EventArgs e)
         {
             uint equipID = UInt32.Parse(textBoxEquipID.Text);
             string lg = "[Strengthen_Click][SendMsgEquipSystemGC2GMReqUpgradeLevel][equipID=" + equipID + "][count=" + 1 + "]";
             Log(lg);
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGC2GMReqUpgradeLevel(equipID, CbUpgradeLevel);
         }

         private void 脱下装备ToolStripMenuItem_Click(object sender, EventArgs e)
         {
             uint equipID = UInt32.Parse(textBoxEquipID.Text);
             string lg = "[Strengthen_Click][SendMsgEquipSystemGM2GCReqChangeEquipStatus][equipID=" + equipID + "]";
             Log(lg);
             uint index = 9;
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqChangeEquipStatus(equipID, index, UnityGMClient.EEquipStatus.EQUIP_STATUS_OFF, CbChangeEquipStatu);
         }

         private void 穿上装备ToolStripMenuItem_Click(object sender, EventArgs e)
         {
             uint equipID = UInt32.Parse(textBoxEquipID.Text);
             string lg = "[Strengthen_Click][SendMsgEquipSystemGM2GCReqChangeEquipStatus][equipID=" + equipID + "]";
             Log(lg);
             uint index = 8;
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqChangeEquipStatus(equipID, index, UnityGMClient.EEquipStatus.EQUIP_STATUS_ON, CbChangeEquipStatu);
         }

         private void 装备洗练ToolStripMenuItem1_Click(object sender, EventArgs e)
         {
             uint equipID = UInt32.Parse(textBoxEquipID.Text);
             //uint itemTPID = GC.CItemTPID.MID_ResetAttr_L; // 一级洗练石
             string lg = "[SendMsgEquipSystemGM2GCReqResetAttr][equipID=" + equipID + "]";
             Log(lg);
             List<UInt32> lockAttrIndexList = new List<UInt32>();
             UInt32 AttrIndex = UInt32.Parse(this.textBoxIndex.Text);//1;
             lockAttrIndexList.Add(AttrIndex);
             UInt32 itemEquipID = UInt32.Parse(this.textBox1.Text);
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqResetAttr(UnityGMClient.EResetEquipType.ERESET_EQUIP_TYPE_XILIAN,
                 equipID, lockAttrIndexList, itemEquipID, CbResetAttr);
         }

         private void 镶嵌宝石ToolStripMenuItem_Click(object sender, EventArgs e)
         {
             try
             {
                 uint equipID = UInt32.Parse(textBoxEquipID.Text);
                 uint itemTPID = UInt32.Parse(this.textBoxGemID.Text);
                 UnityGMClient.EGemSlot posIndex = (UnityGMClient.EGemSlot)UInt32.Parse(this.textBoxIndex.Text);
                 UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqChangeGemStatus(equipID, posIndex, UnityGMClient.EGemStatus.GEM_STATUS_ON, itemTPID, CBChangeGemStatus);
             }
             catch (Exception ex)
             {
                 string lg = "[error][" + ex.ToString() + "]";
                 Log(lg);
             }
         }

         private void 取下宝石ToolStripMenuItem_Click(object sender, EventArgs e)
         {
             try
             {
                 uint equipID = UInt32.Parse(textBoxEquipID.Text);
                 uint itemTPID = UInt32.Parse(this.textBoxGemID.Text);
                 UnityGMClient.EGemSlot posIndex = (UnityGMClient.EGemSlot)UInt32.Parse(this.textBoxIndex.Text);
                 UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqChangeGemStatus(equipID, posIndex, UnityGMClient.EGemStatus.GEM_STATUS_OFF, itemTPID, CBChangeGemStatus);
             }
             catch (Exception ex)
             {
                 string lg = "[error][" + ex.ToString() + "]";
                 Log(lg);
             }
         }

         private void 合成宝石ToolStripMenuItem_Click(object sender, EventArgs e)
         {
             uint equipID = UInt32.Parse(textBoxEquipID.Text);
             uint gemTPID = UInt32.Parse(textBoxGemID.Text);
             string lg = "[SendMsgEquipSystemGC2GMReqGemCombine][equipID=" + equipID + "][gemTPID=" + gemTPID + "]";
             Log(lg);
             UnityGMClient.EGemsCombineType type = UnityGMClient.EGemsCombineType.EGEMS_COMBINE_TYPE_SINGLE;
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGC2GMReqGemCombine(type, gemTPID, CbGemCombine);
         }

         private void 拆解结果ToolStripMenuItem_Click(object sender, EventArgs e)
         {
             uint equipID = UInt32.Parse(textBoxEquipID.Text);
             List<uint> equipIDList = new List<uint>();
             equipIDList.Add(equipID);
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGC2GMReqGetDisassemblyEquipResult(equipIDList, CBGetDisassemblyEquipResult);
         }

         private void 装备拆解ToolStripMenuItem1_Click(object sender, EventArgs e)
         {
             uint equipID = UInt32.Parse(textBoxEquipID.Text);
             List<uint> equipIDList = new List<uint>();
             equipIDList.Add(equipID);
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGC2GMReqDisassemblyEquip(equipIDList, CBDisassemblyEquip);
         }

         private void textBoxIndex_TextChanged(object sender, EventArgs e)
         {

         }

         private void textBoxEquipID_TextChanged(object sender, EventArgs e)
         {

         }

         private void textBoxGemID_TextChanged(object sender, EventArgs e)
         {

         }

         private void CBMsgEquipSystemGM2GCAckSaveOperation(UnityGMClient.ESaveOperationResult retCode, UInt32 equipID)
         {

         }

         private void resetRestore_Click(object sender, EventArgs e)
         {
             uint equipID = UInt32.Parse(textBoxEquipID.Text);
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqSaveOperation(equipID, UnityGMClient.EEquipOperation.EQUIP_UPGRADE_INVALID,
                 UnityGMClient.EOperationResult.OPRESULT_NOT_SAVE, CBMsgEquipSystemGM2GCAckSaveOperation);
         }

         private void ExchangeToolStripMenuItem_Click(object sender, EventArgs e)
         {
             uint equipID = UInt32.Parse(textBoxEquipID.Text);
             //uint itemTPID = GC.CItemTPID.MID_ResetAttr_L; // 一级洗练石
             string lg = "[SendMsgEquipSystemGM2GCReqResetAttr][equipID=" + equipID + "]";
             Log(lg);
             List<UInt32> lockAttrIndexList = new List<UInt32>();
             UInt32 AttrIndex = UInt32.Parse(this.textBoxIndex.Text);//1;
             lockAttrIndexList.Add(AttrIndex);
             UInt32 itemEquipID = UInt32.Parse(this.textBox1.Text);
             UnityGMClient.CClientCore.Singleton.SendMsgEquipSystemGM2GCReqResetAttr(UnityGMClient.EResetEquipType.ERESET_EQUIP_TYPE_ZHUANYI,
                 equipID, lockAttrIndexList, itemEquipID, CbResetAttr);
         }
    }
}
