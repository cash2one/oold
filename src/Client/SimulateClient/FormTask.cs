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
    public partial class FormTask : Form
    {
        public FormTask()
        {
            InitializeComponent();
        }

        static FormTask s_Form = null;

        public void TimerStart()
        {
            timerWait.Start();
        }

        public static void showForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormTask();
            }
            s_Form.Show();
            s_Form.TimerStart();
        }

        public static FormTask getForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormTask();
            }
            return s_Form;
        }

        private void buttonChatExit_Click(object sender, EventArgs e)
        {
            this.Hide();
            timerWait.Stop();
            FormMain.showForm();
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

        void _cbGetDailyTaskList(UnityGMClient.EGetDailyTaskListResult result, List<UnityGMClient.CRoleDailyTaskData> listDailyTaskData)
        {
            GC.CLog.write("_cbGetDailyTaskList");
        }

        private void buttonDailyTaskList_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgTaskSystemGC2GMReqGetDailyTaskList(_cbGetDailyTaskList);
        }

        private void textBoxPrizeTaskTPID_TextChanged(object sender, EventArgs e)
        {
            textBoxPrizeTaskTPID = sender as TextBox;
        }

        void _cbGetDailyTaskPrize(UnityGMClient.EGetDailyTaskPrizeResult result)
        {
            GC.CLog.write("_cbGetDailyTaskPrize");
        }

        private void buttonGetPrize_Click(object sender, EventArgs e)
        {
            try
            {
                UInt32 taskTPID = UInt32.Parse(textBoxPrizeTaskTPID.Text);
                UnityGMClient.CClientCore.Singleton.SendMsgTaskSystemGC2GMReqGetDailyTaskPrize(taskTPID, _cbGetDailyTaskPrize);
            }
            catch (System.Exception)
            {
                MessageBox.Show("任务ID输入错误！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
        }

        private void _cbTaskSystemGM2GCAckGetMainTaskList(UnityGMClient.EGetMainTaskListResult result, UnityGMClient.CRoleMainTaskData mainTask)
        {
            string strResult = string.Format("主线任务返回:[{0}] TPID[{1}]\r\n", result, mainTask.m_taskTPID);
            textBoxTips.Text += strResult;
        }

        private void buttonGetMainTask_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgTaskSystemGC2GMReqGetMainTaskList(_cbTaskSystemGM2GCAckGetMainTaskList);
        }

        private void _cbMsgTaskSystemGM2GCAckGetMainTaskPrize(UnityGMClient.EGetDailyTaskPrizeResult result)
        {
            string strResult = string.Format("主线任务奖励返回:[{0}]\r\n", result);
            textBoxTips.Text += strResult;
            GC.CLog.write("_cbMsgTaskSystemGM2GCAckGetMainTaskPrize");
        }

        private void buttonGetMainTaskPrize_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgTaskSystemGC2GMReqGetMainTaskPrize(_cbMsgTaskSystemGM2GCAckGetMainTaskPrize);
        }
        private void textBoxMainTaskType_TextChanged(object sender, EventArgs e)
        {
            textBoxPara1 = sender as TextBox;
        }

        private void textBoxMainTaskEventParam1_TextChanged(object sender, EventArgs e)
        {
            textBoxPara2 = sender as TextBox;
        }

        private void textBoxMainTaskEventParam2_TextChanged(object sender, EventArgs e)
        {
            textBoxPara3 = sender as TextBox;
        }

        private void buttonFinishMainTaskEvent_Click(object sender, EventArgs e)
        {
            try
            {
                UnityGMClient.EMainTaskType type = (UnityGMClient.EMainTaskType)UInt32.Parse(textBoxPara1.Text);
                UInt32 taskID = UInt32.Parse(textBoxPara1.Text);
                UInt32 curCount = UInt32.Parse(textBoxPara2.Text);

                UnityGMClient.CClientCore.Singleton.SendMsgTaskSystemGC2GMReqNotifyMainTaskStateUpdate(taskID, curCount, delegate(UnityGMClient.EUpdateMainTaskStateResult result){
                    GC.CLog.write("_cbTaskSystemGM2GCAckGetMainTaskList");
                    string strResult = string.Format("汇报主线任务更新返回:[{0}]\r\n", result);
                    textBoxTips.Text += strResult;
                }
                );
            }
            catch (System.Exception)
            {
                MessageBox.Show("数据输入错误！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
        }

        void cbMsgGM2GCNtfMainTaskState(UInt32 mainTaskTPID, UnityGMClient.ETaskState state)
        {
            GC.CLog.write("cbMsgGM2GCNtfMainTaskState");
        }

        private void buttonGetPetTask_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgTaskSystemGC2GMReqGetPetTask(delegate(UnityGMClient.EGetPetTaskResult result, UnityGMClient.CPetTaskInfo petTaskInfo)
            {
                textBoxTips.Text += "================================================\r\n";
                string strResult = string.Format("result[{0}], 共有{1}个任务 已刷新次数[{2}], 下次刷新需要钻石[{3}], 当日已完成次数[{4}/{5}]", result, petTaskInfo.m_rolePetTaskList.Count, petTaskInfo.m_dailyRefreshCount, petTaskInfo.m_nextRefreshDiamondCost, petTaskInfo.m_taskCompletedCount, petTaskInfo.m_totalCount);
                textBoxTips.Text = textBoxTips.Text + strResult + "\r\n";

                foreach (UnityGMClient.CRolePetTask task in petTaskInfo.m_rolePetTaskList) {
                    string taskInfo = string.Format("taskIndex[{0}] taskTPID[{1}] count[{2}] state[{3}]", task.m_taskIndex, task.m_id, task.m_curCount, task.m_state);
                    textBoxTips.Text = textBoxTips.Text + taskInfo + "\r\n";
                }
            }
            );
        }

        private void buttonRefreshPetTask_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgTaskSystemGC2GMReqRefreshPetTask(delegate(UnityGMClient.ERefreshPetTaskResult result, 
                                    UnityGMClient.CRefreshPetTaskInfo refreshPetTaskInfo) 
            {
                string resultStr = string.Format("result [{0}] daily refresh count[{1}] diamond cost[{2}], new task cout[{3}]",
                    result, refreshPetTaskInfo.m_dailyRefreshCount, refreshPetTaskInfo.m_nextRefreshDiamondCost, refreshPetTaskInfo.m_rolePetTaskList.Count);
                textBoxTips.Text = textBoxTips.Text + resultStr + "\r\n";
                foreach (UnityGMClient.CRolePetTask task in refreshPetTaskInfo.m_rolePetTaskList)
                {
                    string taskInfo = string.Format("taskIndex[{0}] taskTPID[{1}] count[{2}] state[{3}]", task.m_taskIndex, task.m_id, task.m_curCount, task.m_state);
                    textBoxTips.Text = textBoxTips.Text + taskInfo + "\r\n";
                }

            }
            );
        }

        private void buttonUpdatePetTaskState_Click(object sender, EventArgs e)
        {
            UInt32 petTaskIndex = 0;
            UnityGMClient.ETaskState state = UnityGMClient.ETaskState.ETASKSTATE_ACCEPT;
            UInt16 curCount = 0;
            try
            {
                petTaskIndex = UInt32.Parse(textBoxPara1.Text);
                state = (UnityGMClient.ETaskState)UInt32.Parse(textBoxPara2.Text);
                curCount = (UInt16)UInt32.Parse(textBoxPara3.Text);
            }
            catch (System.Exception)
            {
                MessageBox.Show("数据输入错误！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            UnityGMClient.CClientCore.Singleton.SendMsgTaskSystemGC2GMReqUpdatePetTaskState(petTaskIndex, state, curCount,
                delegate(UnityGMClient.EUpdatePetTaskStateResult result, UInt32 taskIndex, UnityGMClient.ETaskState newState, UInt16 count)
            {
                string resultStr = string.Format("更新状态返回[{0}], taskIndex[{1}], state[{2} curCount[{3}]]", result, taskIndex, newState, count);
                textBoxTips.Text = textBoxTips.Text + resultStr + "\r\n";
            });
        }

        private void buttonGetPetTaskPrize_Click(object sender, EventArgs e)
        {
            UInt32 petTaskIndex = 0;
            try
            {
                petTaskIndex = UInt32.Parse(textBoxPara1.Text);
            }
            catch (System.Exception)
            {
                MessageBox.Show("数据输入错误！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            UnityGMClient.CClientCore.Singleton.SendMsgTaskSystemGC2GMReqGetPetTaskPrize(petTaskIndex, delegate(UnityGMClient.EGetPetTaskPrizeResult result, UInt32 taskIndex)
            {
                string resultStr = string.Format("领取奖励结果[{0}], taskIndex[{1}]", result, taskIndex);
                textBoxTips.Text = textBoxTips.Text + resultStr + "\r\n";
            });

        }


    }
}
