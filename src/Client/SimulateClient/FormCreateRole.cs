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
    public partial class FormCreateRole : Form
    {
        private static FormCreateRole g_Form = null;
        private UInt32 m_roleType = 3;

        private string getNewName()
        {
            return "role" + GC.CHelper.randString(6);
        }

        public void allocName()
        {
             this.textBoxName.Text = getNewName();
        }

        public FormCreateRole()
        {
            InitializeComponent();
            this.textBoxName.Text = "role" + GC.CHelper.randString(6);
        }

        private void FormCreateRole_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void Log(string content)
        {
            string lg = "[" + this.Name.ToString() + "]" + content + "";
            GC.CLog.write(lg);
        }



        private void btnCreateRole_Click(object sender, EventArgs e)
        {
            if (textBoxName.Text == "")
           {
               MessageBox.Show("角色名为空", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
               return;
           }
           string name = textBoxName.Text;
           UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqCreateRole(name, m_roleType, CbCreateRole);
        }

        private void CbCreateRole(UnityGMClient.ECreateRoleResult retCode, UInt32 CurrentRoleIndex,UnityGMClient.CRole role)
        {
            switch (retCode)
            {
                case UnityGMClient.ECreateRoleResult.ECREATEROLE_RESUlT_SUCCESS:
                    {
                        GC.CPlayer.Singleton.FinishCreateRole(CurrentRoleIndex, role);
                        UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqSelectRole(CurrentRoleIndex, CbSelectRole);
                        break;
                    }
                case UnityGMClient.ECreateRoleResult.ECREATEROLE_RESUlT_INVALID_PROTYPE:
                    {
                        MessageBox.Show("创建角色失败，无效的角色类型", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        break;
                    }
                case UnityGMClient.ECreateRoleResult.ECREATEROLE_RESUlT_INVALID_ROLENAME:
                    {
                        MessageBox.Show("创建角色失败，无效的角色名", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        break;
                    }
                case UnityGMClient.ECreateRoleResult.ECREATEROLE_RESUlT_ROLECOUNT_LIMIT:
                    {
                        MessageBox.Show("创建角色失败，已达到角色个数限制", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        break;
                    }
                case UnityGMClient.ECreateRoleResult.ECREATEROLE_RESUlT_FAIL:
                    {
                        MessageBox.Show("创建角色失败!", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        break;
                    }
                default:
                    {
                        MessageBox.Show("创建角色失败!", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        break;
                    }
            } 
        }

        private void CbSelectRole(UnityGMClient.ESelectRoleResult retCode)
        {
            string lg = "[CbSelectRole][retCode=" + retCode + "]";
            Log(lg);

            if (retCode != UnityGMClient.ESelectRoleResult.ESELECTROLE_RESUlT_SUCCESS)
            {
                return;
            }
            UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqEnterScene(GC.CPlayer.Singleton.getSceneTypeID(), CbEnterScene);
        }

        private void CbEnterScene(UnityGMClient.EEnterSceneResult retCode, UInt32 currentSceneID, List<UnityGMClient.CSceneRoleInfo> listSceneRoles)
        {
            if (retCode != UnityGMClient.EEnterSceneResult.EENTER_SCENE_RESULT_SUCCESS)
            {
                MessageBox.Show("返回进入场景失败!", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
            timerWait.Stop();
            this.Hide();
            FormMain.showForm();
           
        }


        private void zJiang_CheckedChanged(object sender, EventArgs e)
        {
            if (this.zJiang.Checked)
            {
                m_roleType = 2;
            }
        }

        private void keleijiang_CheckedChanged(object sender, EventArgs e)
        {
            if (this.keleijiang.Checked)
            {
                m_roleType = 3;
            }
        }

        private void gulandaishang_CheckedChanged(object sender, EventArgs e)
        {
            if (this.gulandaishang.Checked)
            {
               m_roleType =  1;
            }
        }

        private void cancel_Click(object sender, EventArgs e)
        {
            this.Hide();
            timerWait.Stop();
            FormSelectRole.showForm();
        }

        public static void showForm()
        {
            if (g_Form == null)
            {
                g_Form = new FormCreateRole();
            }
            g_Form.allocName();
            g_Form.Show();
            
            g_Form.TimerStart();
        }
        public void TimerStart()
        {
            timerWait.Start();
        }

        private void timerWait_Tick(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Update(0);
        }

        private void btnGetName_Click(object sender, EventArgs e)
        {
            allocName();
        }
    }
}
