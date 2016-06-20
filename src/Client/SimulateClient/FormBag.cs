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
    public partial class FormBag : Form
    {
        public FormBag()
        {
            InitializeComponent();
            textBoxID.Text = "1";
        }
        private static FormBag g_FormBag = null;

        public static void showForm()
        {
            if (g_FormBag == null)
            {
                g_FormBag = new FormBag();
            }
            g_FormBag.Show();
            g_FormBag.TimerStart();
            g_FormBag.textBoxShow.Text = GC.CPlayer.Singleton.getBagDataToLogString();
        }

        public static FormBag getForm()
        {
            if (g_FormBag == null)
            {
                g_FormBag = new FormBag();
            }
            return g_FormBag;
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
            string lg = "[" + this.Name.ToString() + "]" + content + "";
            GC.CLog.write(lg);
        }

        private void CbUseBagItemData(UnityGMClient.EUseBagItemDataResult retCode)
        {
            if (retCode != UnityGMClient.EUseBagItemDataResult.EUSEITEMPACKAGEDATA_RESUlT_SUCCESS)
            {
                string msg = string.Format("操作失败！msg:{0}", retCode.ToString());
                MessageBox.Show(msg, "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            textBoxShow.Text = GC.CPlayer.Singleton.getBagDataToLogString();
        }
        
        private void FormBag_FormClosed(object sender, FormClosedEventArgs e)
        {
            this.Hide();
            g_FormBag = null;
            timerWait.Stop();
            FormMain.showForm();
        }

        private void CbSoldBagItemData(UnityGMClient.ESoldBagItemDataResult retCode)
        {
            string lg = "[CbUseBagItemData][retCode=" + retCode.ToString() + "\r\n";
            Log(lg);
        }

        private void ExpandBagSize_Click(object sender, EventArgs e)
        { 
        }

        void cbShopBuyResult(UnityGMClient.EShopType type, Int32 id, Int32 num, UnityGMClient.EShopSystemResult result)
        {
            string lg = "result:" + result.ToString();
            Log(lg);
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
            textBoxShow.Text = GC.CPlayer.Singleton.getBagDataToLogString();
        }

        private void 获取物品ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqGetBagData(CbGetBagData);
        }

        private void 出售物品ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if ((textBoxID.Text == ""))
            {
                MessageBox.Show("物品信息不能为空！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            try
            {
                UnityGMClient.EItemType type = UnityGMClient.EItemType.EITEM_TP_EQUIP_GLOVE;
                uint index = UInt32.Parse(textBoxID.Text);
                uint count = 1;
                UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqSoldBagItemData(type, index, count, CbSoldBagItemData);
            }
            catch (Exception)
            {
                MessageBox.Show("输入数据错误！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
        }

        private void 使用物品ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if ((textBoxID.Text == ""))
            {
                MessageBox.Show("物品信息不能为空！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            UnityGMClient.EItemType type = UnityGMClient.EItemType.EITEM_TP_PROP_VITALITY;
            uint index = UInt32.Parse(textBoxID.Text);
            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqUseBagItemData(type, index, CbUseBagItemData);
        }

        private void 添加物品ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string msg = "\\AddItem " + this.textBoxTPID.Text + " 1";
            GC.CCmdMgr.Singleton.sendCmd(GC.CCmd.CMD_CMD_MSG, msg, "", "");
        }

        private void 批量添加物品测试ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string msg = "\\AddItem " + this.textBoxTPID.Text + " 5";
            GC.CCmdMgr.Singleton.sendCmd(GC.CCmd.CMD_CMD_MSG, msg, "", "");
        }

        private void 获取能量球ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqGetNengLiangQiuBagData(CbGetBagData);
        }
    }
}
