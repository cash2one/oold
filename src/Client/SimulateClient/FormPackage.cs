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
            textBoxType.Text = "0";
            textBoxCount.Text = "1";
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

        private void useItem_Click(object sender, EventArgs e)
        {
            if ((textBoxType.Text == "") || (textBoxID.Text == "") || (textBoxCount.Text == ""))
            {
                MessageBox.Show("物品信息不能为空！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            uint type = UInt32.Parse(textBoxType.Text);
            uint index = UInt32.Parse(textBoxID.Text);
            uint count = UInt32.Parse(textBoxCount.Text);

            if ((type !=0)&&(type !=1)){
                MessageBox.Show("物品类型错误！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqUseBagItemData((UnityGMClient.EItemType)type, index, count, CbUseBagItemData);
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

        private void sellItem_Click(object sender, EventArgs e)
        {
            if ((textBoxType.Text == "") || (textBoxID.Text == "") || (textBoxCount.Text == ""))
            {
                MessageBox.Show("物品信息不能为空！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            try
            {
                uint type = UInt32.Parse(textBoxType.Text);
                uint index = UInt32.Parse(textBoxID.Text);
                uint count = UInt32.Parse(textBoxCount.Text);

                if ((type != 0) && (type != 1))
                {
                    MessageBox.Show("物品类型错误！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return;
                }

                UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqSoldBagItemData((UnityGMClient.EItemType)type, index, count, CbSoldBagItemData);
            }
            catch (Exception)
            {
                MessageBox.Show("输入数据错误！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
        }

        private void CbSoldBagItemData(UnityGMClient.ESoldBagItemDataResult retCode)
        {
            string lg = "[CbUseBagItemData][retCode=" + retCode.ToString() + "\r\n";
            Log(lg);
        }

        private void ExpandBagSize_Click(object sender, EventArgs e)
        {
            try
            {
                uint shopItemID = 5;

                UnityGMClient.CClientCore.Singleton.SendMsgShopSystemGC2GMReqShopBuy(UnityGMClient.EShopType.ESHOPTYPE_PROP,
                                shopItemID, 1, cbShopBuyResult);
            }
            catch (Exception)
            {
                MessageBox.Show("输入数据错误！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }   
        }

        void cbShopBuyResult(UnityGMClient.EShopType type, Int32 id, Int32 num, UnityGMClient.EShopSystemResult result)
        {
            string lg = "result:" + result.ToString();
            Log(lg);
        }

        private void btnGetBagData_Click(object sender, EventArgs e)
        {
            textBoxShow.Text = GC.CPlayer.Singleton.getBagDataToLogString();
        }
    }
}
