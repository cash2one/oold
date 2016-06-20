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
    public partial class FormRank : Form
    {
        private static FormRank s_Form = null;

        public FormRank()
        {
            InitializeComponent();
        }

        public void TimerStart()
        {
            timerWait.Start();
        }

        public static void showForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormRank();
            }
            s_Form.Show();
            s_Form.TimerStart();
        }

        public static FormRank getForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormRank();
            }
            return s_Form;
        }

        private void timerWait_Tick(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Update(0);
        }

        private void _cbMsgRankSystemGC2GMReqGetRankData(UnityGMClient.EGetRankDataResult result, UnityGMClient.ERankType type, List<UnityGMClient.CRankData> listRankData)
        {

        }

        private void buttonGetRank_Click(object sender, EventArgs e)
        {
            if (!UnityGMClient.CClientCore.Singleton.SendMsgRankSystemGC2GMReqGetRankData(UnityGMClient.ERankType.ERANK_TYPE_ARENA,  _cbMsgRankSystemGC2GMReqGetRankData))
            {
                MessageBox.Show("发送获取排名消息失败！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            this.Hide();
            timerWait.Stop();
            FormMain.showForm();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void _cbMsgRankSystemGC2GMReqGetRankList(UInt32 id, bool isMySelf, List<UnityGMClient.CRankCell> rankList)
        {

        }


        private void rankButton_Click(object sender, EventArgs e)
        {
            if (!UnityGMClient.CClientCore.Singleton.SendMsgRankSystemGC2GMReqGetRankList( 110001, false, 0, _cbMsgRankSystemGC2GMReqGetRankList))
            {
                MessageBox.Show("发送获取排名消息失败！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void _CBMsgPrizeSystemGM2GCAckState(Dictionary<UInt32, Int32> states)
        {

        }

        private void vipState_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPrizeSystemGC2GMReqState(_CBMsgPrizeSystemGM2GCAckState);
        }

        private void _CBMsgPrizeSystemGM2GCAck(UInt32 vip, UInt32 result)
        {

        }

        private void  _CBMsgPrizeSystemGM2GCNtfCharge(UInt32 id, Int64 time)
        {

        }

        private void getVipPrize_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPrizeSystemGC2GMReq(1, _CBMsgPrizeSystemGM2GCAck);
        }

        private void regNtfCharge_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.RegMsgPrizeSystemGM2GCNtfCharge(_CBMsgPrizeSystemGM2GCNtfCharge);
        }

        private void _CBMsgPrizeSystemGM2GCAckTime(Int64 time)
        {

        }

        private void GetTimeBtn_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPrizeSystemGC2GMReqTime(_CBMsgPrizeSystemGM2GCAckTime);
        }

        void _CBMsgPrizeSystemGM2GCAckChargeInfo(List<UnityGMClient.PrizeSystemChargeInfo> info)
        {

        }

        private void GetChargeInfoBtn_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPrizeSystemGC2GMReqChargeInfo(0, _CBMsgPrizeSystemGM2GCAckChargeInfo);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPrizeSystemGC2GMNtfAction();
        }
    }
}
