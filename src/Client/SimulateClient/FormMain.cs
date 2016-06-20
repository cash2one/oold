using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace SimulateClient
{
    public partial class FormMain : Form
    {
        public FormMain()
        {
            InitializeComponent();
            string lg = GC.CPlayer.Singleton.getRoleDataToLogString();
            UnityUtility.CTrace.Singleton.debug(lg);
        }

        private void FormMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void Log(string content)
        {
            string lg = "[" + this.Name.ToString() + "]" + content + "";
            GC.CLog.write(lg);
        }

        private void timerWait_Tick(object sender, EventArgs e)
        {
            //m_cotrolScene.render();
            UnityGMClient.CClientCore.Singleton.Update(0);
        }

        public void TimerStart()
        {
            timerWait.Start();
        }
        
         private void CbQuitScene(UnityGMClient.EQuitSceneResult retCode, UInt32 currentSceneID)
         {
             string lg = "[CbQuitScene][retCode=" + retCode.ToString() + "][currentSceneID=" + currentSceneID.ToString() + "]\r\n";
             Log(lg);
             if (retCode != UnityGMClient.EQuitSceneResult.EQUITSCENE_RESUlT_SUCCESS)
             {
                 UnityUtility.CTrace.Singleton.debug("退出场景失败");
                 return;
             }
             UnityUtility.CTrace.Singleton.debug("退出场景成功");
         }


         private void quitScene_Click(object sender, EventArgs e)
         {
             uint sceneTypeID = GC.CPlayer.Singleton.getSceneTypeID();
             string lg = "[SendMsgPlayerSystemGC2GMReqEnterScene][sceneTypeID=" + sceneTypeID + "]\r\n";
             Log(lg);
             UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqQuitScene(sceneTypeID, CbQuitScene);
         }

         private void CbEnterScene(UnityGMClient.EEnterSceneResult retCode, UInt32 currentSceneID, List<UnityGMClient.CSceneRoleInfo> listSceneRoles)
         {
             //string lg = "[CbEnterScene][retCode=" + retCode.ToString() + "][prizeCount=" + prizeCount.ToString() + "]\r\n";
             //Log(lg);
             if (retCode != UnityGMClient.EEnterSceneResult.EENTER_SCENE_RESULT_SUCCESS)
             {
                 UnityUtility.CTrace.Singleton.debug("返回进入场景[{0}]失败", currentSceneID);
                 return;
             }

             UnityUtility.CTrace.Singleton.debug("返回进入场景[{0}]", currentSceneID);
             GC.CPlayer.Singleton.setCurrentSceneID(currentSceneID);
             this.Hide();
             timerWait.Stop();
             //FormInstance.getForm().InitPrizeData(prizeList);
             FormInstance.showForm();
             
         }

         private void CbRoleQuit(UnityGMClient.ERoleQuitResult retCode)
         {
             string lg = "[CbRoleQuit][retCode=" + retCode.ToString() + "]\r\n";
             Log(lg);
             if (retCode != UnityGMClient.ERoleQuitResult.EROLEQUIT_RESUlT_SUCCESS)
             {
                 UnityUtility.CTrace.Singleton.debug("角色退出失败");
                 return;
             }
             UnityUtility.CTrace.Singleton.debug("角色退出成功");
             this.Hide();
             timerWait.Stop();
             FormSelectRole.showForm();
             //FormSelectRole.getForm().InitPlayerData();
         }

         private void btnEnterCarbon_Click(object sender, EventArgs e)
         {
             //uint sceneTypeID = 2;
             //string lg = "[SendMsgPlayerSystemGC2GMReqEnterScene][sceneTypeID=" + sceneTypeID + "]\r\n";
             //Log(lg);
             //UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqEnterScene(sceneTypeID, CbEnterScene);
             this.Hide();
             timerWait.Stop();
             FormInstance.showForm();
         }

         public static void showForm()
         {
             if (g_Form == null)
             {
                 g_Form = new FormMain();
             }
             g_Form.Show();
             g_Form.TimerStart();
         }
         public static FormMain getForm()
         {
             if (g_Form == null)
             {
                 g_Form = new FormMain();
             }
             return g_Form;
         }
         public static FormMain g_Form = null;

         private void skill_Click(object sender, EventArgs e)
         {
             this.Hide();
             timerWait.Stop();
             FormSkill.showForm();
         }

         private void equip_Click(object sender, EventArgs e)
         {
             string lg = "[Click][Strengthen_Click]\r\n";
             Log(lg);
             this.Hide();
             timerWait.Stop();
             FormEquip.showForm();
         }

         private void pet_Click(object sender, EventArgs e)
         {
             string lg = "[Click][pet_Click]\r\n";
             Log(lg);
             this.Hide();
             timerWait.Stop();
             FormPet.showForm();
         }
         private void buttonChatSystem_Click(object sender, EventArgs e)
         {
             this.Hide();
             timerWait.Stop();
             FormChat.showForm();
         }

         private void Bag_Click(object sender, EventArgs e)
         {
             string lg = "[Click][Bag_Click]\r\n";
             Log(lg);
             this.Hide();
             timerWait.Stop();
             FormBag.showForm();
         }

         private void buttonArena_Click(object sender, EventArgs e)
         {
             string lg = "[enter Arena UI]\r\n";
             Log(lg);
             this.Hide();
             timerWait.Stop();
             FormArena.showForm();
         }

         private void buttonRankSystem_Click(object sender, EventArgs e)
         {
             string lg = "[enter Rank UI]\r\n";
             Log(lg);
             this.Hide();
             timerWait.Stop();
             FormRank.showForm();
         }

         public void opMail(UInt32 op_type, List<UInt64> mail_ids)
         {
             mail_ids.ToArray();
         }


         private void get_attach(List<UInt64> mail_ids, List<UInt32> bonus_ids, List<UInt32> bonus_nums)
         {

         }

         private void mail_Click(object sender, EventArgs e)
         {
             List<UInt64> mail_ids = new List<UInt64>();
             mail_ids.Add(12701637381958139905);
             //mail_ids.Add(7);
             //mail_ids.Add(11);
             bool bSuccess = UnityGMClient.CClientCore.Singleton.SendMsgMailSystemGC2GMReqOPMail(1, mail_ids, opMail);

             UnityGMClient.CClientCore.Singleton.SendMsgMailSystemGC2GMReqGetAttach(mail_ids, get_attach);
             //bSuccess = UnityGMClient.CClientCore.Singleton.SendMsgMailSystemGC2GMReqOPMail(2, mail_ids, opMail);
         }

         private void buttonTask_Click(object sender, EventArgs e)
         {
             string lg = "[enter Task UI]\r\n";
             Log(lg);
             this.Hide();
             timerWait.Stop();
             FormTask.showForm();
         }

         private void reLogin_Click(object sender, EventArgs e)
         {
             Int32 currentIndex = GC.CPlayer.Singleton.getCurrentRoleIndex();
             if (currentIndex == -1)
             {
                 return;
             }
             UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqRoleQuit((UInt32)currentIndex, CbRoleQuit);
         }

         private void buttonShop_Click(object sender, EventArgs e)
         {
             string lg = "[enter Shop UI]\r\n";
             Log(lg);
             this.Hide();
             timerWait.Stop();
             FormShop.showForm();
         }

         private void buttonActivity_Click(object sender, EventArgs e)
         {
             string lg = "[enter Activity UI]\r\n";
             Log(lg);
             this.Hide();
             timerWait.Stop();
             FormActivity.showForm();
         }

         private void buttonFriend_Click(object sender, EventArgs e)
         {
             string lg = "[enter Friend UI]\r\n";
             Log(lg);
             this.Hide();
             timerWait.Stop();
             FormFriend.showForm();
         }

         private void getRoleData_Click(object sender, EventArgs e)
         {
             string lg = "[enter RoleData UI]\r\n";
             Log(lg);
             this.Hide();
             timerWait.Stop();
             FormRoleData.showForm();
         }



    }
}
