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
    public partial class FormPet : Form
    {
        private static FormPet g_FormPet = null;
        const UInt32 m_strengthenMetarialID = 100200000;
        const UInt32 m_strengthenMetarialCount = 1;

        public static void showForm()
        {
            if (g_FormPet == null)
            {
                g_FormPet = new FormPet();
            }
            FormPet.showBtnGetPetTaskList(false);
            g_FormPet.Show();
            g_FormPet.TimerStart();
        }

        public static FormPet getForm()
        {
            if (g_FormPet == null)
            {
                g_FormPet = new FormPet();
            }
            return g_FormPet;
        }

        public FormPet()
        {
            InitializeComponent();
            showData();

            if(GC.CPlayer.Singleton.m_petData.PetCount>0){
                this.textBoxPetID.Text = GC.CPlayer.Singleton.m_petData.PetList[0].PetID.ToString();
                this.textTaskType.Text = "0";
            }    
        }

        private void showData()
        {
           string lg = GC.CPlayer.Singleton.getPetDataToLogString();
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

        private void Log(string content)
        {
            this.textBoxTestShow.Text = content;
            string lg = "[" + this.Name.ToString() + "]" + content + "";
            GC.CLog.write(lg);
        }
        private void FormPet_FormClosed(object sender, FormClosedEventArgs e)
        {
            this.Hide();
            g_FormPet = null;
            timerWait.Stop();
            FormMain.showForm();
        }

        private void cbPetChangeStatus(UnityGMClient.EHotSpringTaskEndResult retCode, UInt32 petID, UnityGMClient.EPetStatus petStatus)
        {
            string lg = "[cbPetChangeStatus][retCode=" + retCode.ToString()
                + "][petID=" + petID
                + "][positionType=" + petStatus.ToString()
                + "]\r\n";
            Log(lg);

            if (retCode != UnityGMClient.EHotSpringTaskEndResult.EHOTSPRINGTASK_END_RESULT_SUCCESS)
            {
                return;
            }

            GC.CPlayer.Singleton.updatePetStatus(petID,petStatus);
            showData();
        }


        private void FormPet_Load(object sender, EventArgs e)
        {

        }

        private void CBPetTaskFinish(UnityGMClient.EPetTaskFinishResult retCode, UInt32 petID)
        {
            string lg = "[CBPetTaskFinish][retCode=" + retCode.ToString()
                + "][petID=" + petID 
                + "]\r\n";
            Log(lg);
            if (retCode != UnityGMClient.EPetTaskFinishResult.EPETTASKFINISH_RESULT_SUCCESS)
            {
                return;
            }
            //GC.CPlayer.Singleton.updatePetStarLevel(petID, starLevel);
            showData();
        }

        private void UpdateSkillPoint_Click(object sender, EventArgs e)
        {
            string lg = "[UpdateSkillPoint_Click][SendMsgPlayerSystemGC2GMReqUpdateSkillPoint]\r\n";
            Log(lg);
            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqUpdateSkillPoint(CBUpdateSkillPoint);
        }

        private void CBUpdateSkillPoint(UnityGMClient.EUpdateSkillPointResult retCode, UInt32 a_skillPoint, UInt32 a_updateTime)
        {
            string lg = "[CBUpdateSkillPoint][retCode=" + retCode.ToString()
                + "][a_skillPoint=" + a_skillPoint
                + "][a_updateTime=" + a_updateTime 
                + "]\r\n";
            Log(lg);
            if (retCode != UnityGMClient.EUpdateSkillPointResult.EUPDATESKILLPOINT_RESULT_SUCCESS)
            {
                return;
            }
        }

        public static void showBtnGetPetTaskList(bool bShow){
            FormPet form = getForm();
        }


        private void 进入温泉ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            uint petID = 0;
            try
            {
                petID = UInt32.Parse(textBoxPetID.Text);
            }
            catch (Exception exp)
            {
                Log(exp.ToString());
                return;
            }
            UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGM2GCReqPetEnterPool(petID,UnityGMClient.EHotSpringType.EFiveMiniteHotSpring,
                delegate(UnityGMClient.EPetEnterPoolResult retCode)
                {
                    string lg = "EPetEnterPoolResult:" + retCode.ToString();
                    Log(lg);
                });
        }

        private void 离开温泉ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if ((textBoxPetID.Text == ""))
            {
                MessageBox.Show("伙伴信息不能为空！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            uint petID = UInt32.Parse(textBoxPetID.Text);
            UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGM2GCReqPetQuitPool(petID,
                delegate(UnityGMClient.EPetQuitPoolResult retCode,UnityGMClient.CPetItem petItem)
            {
                string lg = "EPetQuitPoolResult:" + retCode.ToString();
                Log(lg);
            });
        }

        private void 坐下喝茶ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            uint petID = UInt32.Parse(textBoxPetID.Text);
            UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGM2GCReqPetSitDown(petID,
                delegate(UnityGMClient.EPetSitDownResult retCode)
            {
                string lg = "EPetSitDownResult:" + retCode.ToString();
                Log(lg);
            });
        }

        private void 伙伴数据ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGM2GCReqInitPetData(
           delegate(UnityGMClient.EGetInitRolePetDataResult retCode, UnityGMClient.CPetData petData)
           {
               string lg = "EGetInitRolePetDataResult:" + retCode.ToString();
               Log(lg);
               GC.CPlayer.Singleton.setPetData(petData);
               lg = GC.CPlayer.Singleton.getPetDataToLogString();
               Log(lg);
           });
        }

        private void 完成伙伴任务ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (textBoxPetID.Text == "")
            {
                MessageBox.Show("伙伴信息不能为空！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            uint petid = UInt32.Parse(textBoxPetID.Text);
            string lg = "[StarLevelUp_Click][SendMsgPetSystemGC2GMReqPetFinishHotSpringTask][petid=" + petid + "]\r\n";
            Log(lg);
            uint answerID = 0;
            UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGC2GMReqPetFinishHotSpringTask(petid,answerID,CBPetTaskFinish);
        }

        private void 取消援护ToolStripMenuItem_Click(object sender, EventArgs e)
        {
             UInt32 petID = 0;
            try
            {
                petID = UInt32.Parse(textBoxPetID.Text);
            }
            catch (Exception exp)
            {
                Log(exp.ToString());
                return;
            }
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGM2GCReqPetStandUp(petID,
                          delegate(UnityGMClient.EPetStandUpResult retCode)
                          {
                              string lg = "retCode:" + retCode.ToString();
                              Log(lg);
                          });
        }

        private void 温泉快速完成ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if ((textBoxPetID.Text == ""))
            {
                MessageBox.Show("伙伴信息不能为空！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            uint petID = UInt32.Parse(textBoxPetID.Text);
            UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGM2GCReqPetFastQuitPool(petID,
                delegate(UnityGMClient.EPetFastQuitPoolResult retCode,UnityGMClient.CPetItem petItem)
                {
                    string lg = "EPetFastQuitPoolResult:" + retCode.ToString();
                    Log(lg);
                });
        }

        private void 获取单个伙伴数据ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 petID = 0;
            try
            {
                petID = UInt32.Parse(textBoxPetID.Text);
            }
            catch (Exception exp)
            {
                Log(exp.ToString());
                return;
            }
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGM2GCReqGetPetData(petID,
                          delegate(UnityGMClient.EGetPetDataResult retCode, UnityGMClient.CPetItem petItem)
                          {
                              string lg = "retCode:" + retCode.ToString();
                              if (retCode == UnityGMClient.EGetPetDataResult.EGETPETDATA_RESULT_SUCCESS)
                              {
                                  lg += " " + petItem.getLogString();
                              }
                              Log(lg);
                          });
        }

        private void 获取解锁进度ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGC2GMReqGetPetUnlockData(
                          delegate(UnityGMClient.EGetPetUnlockDataResult retCode, UnityGMClient.CPetUnlockData petUnlockData)
                          {
                              string lg = "retCode:" + retCode.ToString();
                              if (retCode == UnityGMClient.EGetPetUnlockDataResult.EGETPETUNLOCKDATARESULT_SUCCESS)
                              {
                                  lg += " " + petUnlockData.getLogString();
                              }
                              Log(lg);
                          });
        }

        private void 获取日常对话任务ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 petID = 0;
            UnityGMClient.EHotSpringTaskType petTaskType = UnityGMClient.EHotSpringTaskType.EHotSpringTaskTypeInvalid;
            try
            {
                petID = UInt32.Parse(textBoxPetID.Text);
            }
            catch (Exception exp)
            {
                Log(exp.ToString());
                return;
            }
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGC2GMReqPetGetHotSpringTaskDetail(petID, petTaskType,
                          delegate(UnityGMClient.EPetGetHotSpringTaskDetailResult retCode, UnityGMClient.CHotSpringTaskData taskData)
                          {
                              string lg = "retCode:" + retCode.ToString();
                              if (retCode == UnityGMClient.EPetGetHotSpringTaskDetailResult.EPETGET_HOTSPRING_TASKDETAIL_RESULT_SUCCESS)
                              {
                                  lg += " " + taskData.getLogString();
                              }
                              Log(lg);
                          });
        }

        private void GetSendGiftToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 petID = 0;
            List<UnityGMClient.CPrizeItem> itemList = new List<UnityGMClient.CPrizeItem>();
            UnityGMClient.CPrizeItem item = new UnityGMClient.CPrizeItem();
           
            
            try
            {
                petID = UInt32.Parse(textBoxPetID.Text);
                item.m_ItemCount = UInt32.Parse(this.textBoxCount.Text);
                item.m_ItemTPID = UInt32.Parse(this.textBoxTPID.Text);
                item.m_ItemType = UnityGMClient.EItemType.EITEM_TP_PET_MATERIAL;
                itemList.Add(item);
            }
            catch (Exception exp)
            {
                Log(exp.ToString());
                return;
            }
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGC2GMReqSendPetGift(petID,itemList,
                          delegate(UnityGMClient.ESendPetGiftResult retCode)
                          {
                              string lg = "retCode:" + retCode.ToString();
                              Log(lg);
                          });
        }

        private void 伙伴解锁ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 petTPID = 0;
            try
            {
                petTPID = UInt32.Parse(textBoxPetID.Text);
            }
            catch (Exception exp)
            {
                Log(exp.ToString());
                return;
            }
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGC2GMReqUnlockPet(petTPID,
                          delegate(UnityGMClient.EUnlockPetResult retCode, UnityGMClient.CPetItem petItem)
                          {
                              string lg = "retCode:" + retCode.ToString();
                              if (retCode == UnityGMClient.EUnlockPetResult.EUNLOCKPET_RESULT_SUCCESS)
                              {
                                  lg += " " + petItem.getLogString();
                              }
                              Log(lg);
                          });
        }

        private void 进入4小时温泉ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            uint petID = 0;
            try
            {
                petID = UInt32.Parse(textBoxPetID.Text);
            }
            catch (Exception exp)
            {
                Log(exp.ToString());
                return;
            }
            UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGM2GCReqPetEnterPool(petID, UnityGMClient.EHotSpringType.EFourHoursHotSpring,
                delegate(UnityGMClient.EPetEnterPoolResult retCode)
                {
                    string lg = "EPetEnterPoolResult:" + retCode.ToString();
                    Log(lg);
                });
        }

        private void 进入8小时温泉ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            uint petID = 0;
            try
            {
                petID = UInt32.Parse(textBoxPetID.Text);
            }
            catch (Exception exp)
            {
                Log(exp.ToString());
                return;
            }
            UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGM2GCReqPetEnterPool(petID, UnityGMClient.EHotSpringType.EEightHoursHotSpring,
                delegate(UnityGMClient.EPetEnterPoolResult retCode)
                {
                    string lg = "EPetEnterPoolResult:" + retCode.ToString();
                    Log(lg);
                });
        }

        private void 获取伙伴基础信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGC2GMReqGetPetBaseInforList(
               delegate(UnityGMClient.EGetPetBaseInforListResult retCode, List<UnityGMClient.CPetBaseInfor> petBaseInforList)
               {
                   string lg = "EGetPetBaseInforListResult:" + retCode.ToString();
                   if (retCode == UnityGMClient.EGetPetBaseInforListResult.EGET_PETBASEINFORLIST_RESULT_SUCCESS)
                   {
                       if (petBaseInforList != null)
                       {
                           for (int i = 0; i < petBaseInforList.Count; ++i)
                           {
                               UnityGMClient.CPetBaseInfor pet = petBaseInforList[i];
                               lg += pet.getLogString();
                           }
                       } 
                   }
                   Log(lg);
               });
        }

        private void 完成对战ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            uint petID = 0;
            try
            {
                petID = UInt32.Parse(textBoxPetID.Text);
            }
            catch (Exception exp)
            {
                Log(exp.ToString());
                return;
            }
            UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGC2GMReqHotSpringTaskEnd(petID, UnityGMClient.EPetHotSprintEnd.EPetHotSprintEndWin,
                delegate(UnityGMClient.EHotSpringTaskEndResult retCode, UnityGMClient.CTalkAnswer answer)
                {
                    string lg = "EHotSpringTaskEndResult:" + retCode.ToString() + "answer:"+ answer.getLogString();
                    Log(lg);
                });
        }

        private void 获取任务ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 petID = 0;
            UnityGMClient.EHotSpringTaskType petTaskType = UnityGMClient.EHotSpringTaskType.EHotSpringTaskTypeTalk;
            try
            {
                petID = UInt32.Parse(textBoxPetID.Text);
            }
            catch (Exception exp)
            {
                Log(exp.ToString());
                return;
            }
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGC2GMReqPetGetHotSpringTaskDetail(petID, petTaskType,
                          delegate(UnityGMClient.EPetGetHotSpringTaskDetailResult retCode, UnityGMClient.CHotSpringTaskData taskData)
                          {
                              string lg = "retCode:" + retCode.ToString();
                              if (retCode == UnityGMClient.EPetGetHotSpringTaskDetailResult.EPETGET_HOTSPRING_TASKDETAIL_RESULT_SUCCESS)
                              {
                                  lg += " " + taskData.getLogString();
                              }
                              Log(lg);
                          });
        }

        private void 获取发布任务ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UInt32 petID = 0;
            UnityGMClient.EHotSpringTaskType petTaskType = UnityGMClient.EHotSpringTaskType.EHotSpringTaskTypePublishTask;
            try
            {
                petID = UInt32.Parse(textBoxPetID.Text);
            }
            catch (Exception exp)
            {
                Log(exp.ToString());
                return;
            }
            bool bResult = UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGC2GMReqPetGetHotSpringTaskDetail(petID, petTaskType,
                          delegate(UnityGMClient.EPetGetHotSpringTaskDetailResult retCode, UnityGMClient.CHotSpringTaskData taskData)
                          {
                              string lg = "retCode:" + retCode.ToString();
                              if (retCode == UnityGMClient.EPetGetHotSpringTaskDetailResult.EPETGET_HOTSPRING_TASKDETAIL_RESULT_SUCCESS)
                              {
                                  lg += " " + taskData.getLogString();
                              }
                              Log(lg);
                          });
        }

        private void ExpandHotSpringToolStripMenuItem_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgPetSystemGM2GCReqExpandHotSpring(
                  delegate(UnityGMClient.EExpandHotSpringResult retCode, UnityGMClient.CHotSpring hotSpring)
                          {
                              string lg = "retCode:" + retCode.ToString();
                              if (retCode == UnityGMClient.EExpandHotSpringResult.EEXPANDHOTSPRING_RESULT_SUCCESS)
                              {
                                  lg += " " + hotSpring.getLogString();
                              }
                              Log(lg);
                          });
        }
    }
}
