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
    public partial class FormActivity : Form
    {
        public FormActivity()
        {
            InitializeComponent();
        }

        private static FormActivity s_Form = null;

        public void TimerStart()
        {
            timerWait.Start();
        }
        public static void showForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormActivity();
            }
            s_Form.Show();
            s_Form.TimerStart();
        }

        public static FormActivity getForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormActivity();
            }
            return s_Form;
        }

        private void timerWait_Tick(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Update(0);
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            this.Hide();
            timerWait.Stop();
            FormMain.showForm();
        }

        private void _cbGetAttendenceData(UnityGMClient.EGetAttendenceDataResult result, UnityGMClient.CRoleAttendenceData roleAttendenceData)
        {
            GC.CLog.write("_cbGetAttendenceData");
        }

        private void buttonGetAttendenceData_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgActivitySystemGC2GMReqGetAttendenceData(_cbGetAttendenceData);
        }

        private void _cbAttendenceSignIn(UnityGMClient.EAttendenceSignInResult result, Int32 signInTime)
        {
            UnityUtility.CTrace.Singleton.trace("_cbAttendenceSignIn");
        }

        private void buttonSignIn_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgActivitySystemGC2GMReqSignIn(_cbAttendenceSignIn);
        }

        private void textBoxCardType_TextChanged(object sender, EventArgs e)
        {
            textBoxCardType = sender as TextBox;
        }

        private void textBoxDrawTimes_TextChanged(object sender, EventArgs e)
        {
            textBoxDrawTimes = sender as TextBox;
        }

        private void buttonDrawCard_Click(object sender, EventArgs e)
        {
            try
            {
                UnityGMClient.EDrawCardType type = (UnityGMClient.EDrawCardType)byte.Parse(textBoxCardType.Text);
                UInt16 count = UInt16.Parse(textBoxDrawTimes.Text);
                UnityGMClient.CClientCore.Singleton.SendMsgActivitySystemGC2GMReqDrawCard(type, count, delegate(UnityGMClient.EDrawCardResult result, UnityGMClient.CDrawCardInfo drawCardInfo, List<UnityGMClient.CRolledItem> listRolledItems) 
                {
                    string log = string.Format("result[{0}] nextGoldDrewCardRemainTime[{1}] nextDiamondDrawCardRemainTime[{2}]] dailyFreeGoldDrawCardRemaindCount[{3} item count[{4}]",
                                                            result, drawCardInfo.m_nextFreeGoldDrawCardRemaindTime, drawCardInfo.m_nextFreeDiamondDrawCardRemainTime,
                                                            drawCardInfo.m_curFreeGoldDrawCardRemaindCount, listRolledItems.Count);
                    UnityUtility.CTrace.Singleton.trace(log);
                    textBoxLog.Text += log;
                    textBoxLog.Text += "\r\n";
                    foreach(UnityGMClient.CRolledItem item in listRolledItems)
                    {
                        textBoxLog.Text  += string.Format("rolled item is pet[{0}] TPID[{1}] count[{2}]", item.m_isPet, item.m_TPID, item.m_count);
                    }
                }
                );
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString(), "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void buttonGetDrawCardInfo_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgActivitySystemGC2GMReqGetDrawCardInfo(delegate(UnityGMClient.CDrawCardInfo drawCardInfo)
            {
                string log = string.Format("nextGoldDrewCardRemainTime[{0}] nextDiamondDrawCardRemainTime[{1}]] dailyFreeGoldDrawCardRemaindCount[{2}]",
                                                        drawCardInfo.m_nextFreeGoldDrawCardRemaindTime, drawCardInfo.m_nextFreeDiamondDrawCardRemainTime, drawCardInfo.m_curFreeGoldDrawCardRemaindCount);
                UnityUtility.CTrace.Singleton.trace(log);
                textBoxLog.Text += log;
                textBoxLog.Text += "\r\n";
            }
);
        }



    }
}
