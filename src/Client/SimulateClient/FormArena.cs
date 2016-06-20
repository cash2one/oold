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
    public partial class FormArena : Form
    {

        private static FormArena s_Form = null;
        private UnityGMClient.CChallengeInfo m_challengeInfo = new UnityGMClient.CChallengeInfo();

        public FormArena()
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
                s_Form = new FormArena();
            }
            s_Form.Show();
            s_Form.TimerStart();
        }

        public static FormArena getForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormArena();
            }
            return s_Form;
        }

        private void timerWait_Tick(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Update(0);
        }

        private void textChallengeeIndex_TextChanged(object sender, EventArgs e)
        {
            textChallengeeType = sender as TextBox;
            try
            {
                m_challengeInfo.m_type = (UnityGMClient.EChallengeType)UInt64.Parse(textChallengeeType.Text);
            }
            catch (System.Exception)
            {
                MessageBox.Show("输入挑战类型有误！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void textBoxNotification_TextChanged(object sender, EventArgs e)
        {
            textBoxNotification = sender as TextBox;
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            this.Hide();
            timerWait.Stop();
            FormMain.showForm();
        }

        private void textBoxChallengeResult_TextChanged(object sender, EventArgs e)
        {
            textBoxChallengeResult = sender as TextBox;
        }

        //获取竞技场信息回调
        private void _cbMsgSceneSystemGC2GMReqGetArenaData(UnityGMClient.CRoleArenaData data)
        {
            textBoxNotification.Text += string.Format("rank[{0}]\r\n", data.m_rank);
            textBoxNotification.Text += string.Format("challengeTimes[{0}]\r\n", data.m_arenaTicketCount);
            textBoxNotification.Text += string.Format("coolDownCost[{0}]\r\n", data.m_eraseChallengeColdDownDiamondCost);
            textBoxNotification.Text += string.Format("total challenge record[{0}]\r\n", data.m_listChallengeRecords.Count);
            foreach (UnityGMClient.CArenaChallengeRecord record in data.m_listChallengeRecords)
            {
                textBoxNotification.Text += string.Format("记录ID[{0}] IsActive[{1}] IsWin[{2}] ChallengeTime[{3}] NewRank[{4}] IsRevenge[{5}] changedRank[{6}]:\r\n",
                    record.m_recordID, record.m_isActive, record.m_isWin, record.m_challengeTime, record.m_newRank, record.m_isRevenged, record.m_changedRank);
            }
            textBoxNotification.Text += string.Format("total challengee[{0}]\r\n", data.m_listChallengees.Count);
            foreach (UnityGMClient.CArenaChallengeeData challengee in data.m_listChallengees)
            {
                textBoxNotification.Text += string.Format("被挑战者acccount[{0}] zoneID[{1}] RoleIndex[{2}] 排名[{3}] 战斗力[{4}]:\r\n",
                    challengee.m_accountID, challengee.m_zoneID, challengee.m_roleIndex, challengee.m_rank, challengee.m_combatPower);
            }
            
        }

        //获取竞技场信息
        private void buttonGetArenaData_Click(object sender, EventArgs e)
        {
            if (!UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqGetArenaData(_cbMsgSceneSystemGC2GMReqGetArenaData))
            {
                MessageBox.Show("发送获取竞技场信息消息失败！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        //换一批回调
        private void _cbMsgSceneSystemGC2GMReqGetNewArenaChallengees(List<UnityGMClient.CArenaChallengeeData> listChallengees)
        {
            textBoxNotification.Text += string.Format("Get New ArenaChallgees[{0}]:\r\n", listChallengees.Count);
            foreach (UnityGMClient.CArenaChallengeeData challengee in listChallengees)
            {
                textBoxNotification.Text += string.Format("被挑战者acccount[{0}] zoneID[{1}] RoleIndex[{2} 排名[{3} 战斗力[{4}]]:\r\n", 
                    challengee.m_accountID, challengee.m_zoneID, challengee.m_roleIndex, challengee.m_rank, challengee.m_combatPower);
            }
        }
        //换一批按钮
        private void buttonRefreshChallengees_Click(object sender, EventArgs e)
        {
            if (!UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGM2GCAckGetNewArenaChallengees(_cbMsgSceneSystemGC2GMReqGetNewArenaChallengees))
            {
                MessageBox.Show("发送获取新一批竞技场被调整者消息失败！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        //挑战玩家回调
        private void _cbMsgSceneSystemGC2GMReqChallengeArenaRole(UnityGMClient.EEnterSceneResult result, UnityGMClient.CBattleRoleData roleData)
        {
            textBoxNotification.Text += string.Format("挑战玩家返回result[{0}]\r\n", result);
        }
        

        //挑战
        private void buttonChallenge_Click(object sender, EventArgs e)
        {
            if (!UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqChallengeArenaRole(m_challengeInfo, _cbMsgSceneSystemGC2GMReqChallengeArenaRole))
            {
                MessageBox.Show("发送挑战消息失败！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            textBoxNotification.Text += string.Format("发起挑战了第[{0}]个玩家\r\n", m_challengeInfo.m_param);
        }

        //挑战结束回调
        private void _cbMsgSceneSystemGC2GMReqChallengeArenaRoleFinish(UnityGMClient.EChallengeArenaRoleFinishResult result)
        {
            textBoxNotification.Text += string.Format("挑战结构返回\r\n");
            textBoxNotification.Text += string.Format("比赛结果:{0}\r\n", result);
        }

        //挑战结束
        private void buttonChallengeFinish_Click(object sender, EventArgs e)
        {
            UInt32 result = 0;
            try
            {
                result = UInt32.Parse(textBoxChallengeResult.Text);
            }
            catch (System.Exception)
            {
                MessageBox.Show("输入竞技场挑战结果数据有误！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            bool isWin = result == 1;
            if (!UnityGMClient.CClientCore.Singleton.SendMsgCMsgSceneSystemGM2GCAckChallengeArenaRoleFinish(isWin, _cbMsgSceneSystemGC2GMReqChallengeArenaRoleFinish))
            {
                MessageBox.Show("发送挑战结束消息失败！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                textBoxNotification.Text = string.Format("发送挑战结果[{}]\r\n",result);
            }
        }

        private void textBoxRecordID_TextChanged(object sender, EventArgs e)
        {
            textBoxParam = sender as TextBox;
            try
            {
                m_challengeInfo.m_param = UInt64.Parse(textBoxParam.Text);
            }
            catch (System.Exception)
            {
                MessageBox.Show("输入参数有误！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void buttonPurchaseTicket_Click(object sender, EventArgs e)
        {
            if (!UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqPurchaseArenaTickts(delegate(UnityGMClient.EPurchaseArenaTicketsResult result, UInt32 curTicketCount, UInt32 nextTicketPrice)
            {

            }
            ))
            {
                MessageBox.Show("发送挑战消息失败！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            textBoxNotification.Text += string.Format("发起挑战了第[{0}]个玩家\r\n", m_challengeInfo.m_param);
        }




    }
}
