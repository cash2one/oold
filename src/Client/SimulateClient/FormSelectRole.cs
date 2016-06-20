using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;

namespace SimulateClient
{
    public partial class FormSelectRole : Form
    {
        private UInt32 m_roleIndex = 0;

        public FormSelectRole()
        {
            InitializeComponent();
        }

        
        private void Log(string content)
        {
            string lg = "[" + this.Name.ToString() + "]" + content + "";
            GC.CLog.write(lg);
        }

        private void SelectRoleForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void createRole_Click(object sender, EventArgs e)
        {
            string lg = "[Click][createRole_Click]\r\n";
            Log(lg);
            this.Hide();
            timerWait.Stop();
            FormCreateRole.showForm();
        }
       
        private void timerWait_Tick(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Update(0);
        }

        public void TimerStart()
        {
            timerWait.Start();
        }

        public void InitPlayerData()
        {
            string lg = "[InitRoleList][SendMsgPlayerSystemGC2GMReqPlayerData]\r\n";
            Log(lg);
            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqPlayerData(cbShowPlayerData);
        }

        public void cbShowPlayerData(UnityGMClient.EInitRoleListResult retCode, UnityGMClient.CPlayerData playerData)
        {
            string lg = "[cbShowRoleList][SendMsgPlayerSystemGC2GMReqPlayerData][retCode=" + retCode + "][roleCount=" + playerData.RoleCount + "]\r\n";
            Log(lg);
            
            if (retCode != UnityGMClient.EInitRoleListResult.EINITROLELIST_RESUlT_SUCCESS)
            {
                textBoxTestShow.Text += "初始化玩家信息失败!\r\n";
                return;
            }

            if (playerData.RoleCount != playerData.RoleList.Count)
            {
                textBoxTestShow.Text += "数据不完成!\r\n";
                return;
            }

            GC.CPlayer.Singleton.InitPlayerData(playerData);

            textBoxTestShow.Text += GC.CPlayer.Singleton.getPlayerDataToLogString();

            showRadioButton(GC.CPlayer.Singleton.getRoleBaseInfoList());
        }

        
        //动态显示radioButton  
        public void showRadioButton(Hashtable list)
        {
            this.panelRole.Controls.Clear();
            //控件上边缘与容器上边缘的距离  
            int top = 6;
            //记录循环，控件左上角相对于容器左上角的坐标  
            int i = 0;
            int n = 0;
            RadioButton[] radioButton = new RadioButton[list.Count];
            foreach (DictionaryEntry roleData in list)
            {
                UnityGMClient.CRoleBaseInfo role = (UnityGMClient.CRoleBaseInfo)roleData.Value;
                if (n % 15 == 0 && n != 0)
                {
                    i++;
                    if (i % 5 == 0)
                    {
                        top = 6 * n;
                        i = 0;
                    }
                    else
                    {
                        top = 6;
                    }
                }
                radioButton[n] = new RadioButton();
                radioButton[n].AutoSize = true;
                radioButton[n].Top = top;
                //控件左上角相对于容器左上角的坐标，以及每个控件之间的距离  
                radioButton[n].Location = new Point(i * 150 + 2, top);
                // MessageBox.Show(name[n].ToString());  
                radioButton[n].Text = role.getRoleName();
                radioButton[n].Visible = true;
                radioButton[n].Name = role.getRoleIndex().ToString();
                radioButton[n].CheckedChanged  += new EventHandler(ckb_CheckedChanged);
                this.panelRole.Controls.Add(radioButton[n]);
                top = top + 21;
                n++;
            }

            if (radioButton.Length > 0)
            {
                radioButton[0].Checked = true;
            }
        }

        void ckb_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rbt = (RadioButton)sender;
            if (rbt.Checked)
            {
                m_roleIndex = UInt32.Parse(rbt.Name.ToString());
                string st = "[selected][roleIndex=" + m_roleIndex + "][roleName=" + rbt.Text + "]\r\n";
                Log(st);
                textBoxTestShow.Text = st + "\r\n";
            }  
        }

        private void push_mail(UInt32 type, List<UnityGMClient.CMail> mail_box)
        {
            mail_box.ToArray();
        }

        private void selectRole_Click(object sender, EventArgs e)
        {
            string lg = "[selectRole_Click][SendMsgPlayerSystemGC2GMReqSelectRole][m_roleIndex=" + m_roleIndex + "]\r\n";
            Log(lg);
            //UnityGMClient.CClientCore.Singleton.RegisterMailSystemGM2GCPushMail(push_mail);
            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqSelectRole(m_roleIndex, CbSelectRole);
        }

        private void CbSelectRole(UnityGMClient.ESelectRoleResult retCode)
        {
            string lg = "[CbSelectRole][retCode=" + retCode 
                + "]\r\n";
            Log(lg);

            if (retCode != UnityGMClient.ESelectRoleResult.ESELECTROLE_RESUlT_SUCCESS)
            {
                return;
            }
            UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqEnterScene(GC.CPlayer.Singleton.getSceneTypeID(), CbEnterScene);
         }


        private void CbEnterScene(UnityGMClient.EEnterSceneResult retCode, UInt32 currentSceneID, List<UnityGMClient.CSceneRoleInfo> listSceneRoles)
        {
            string lg = "[CbEnterScene][retCode=" + retCode.ToString() 
                + "][currentSceneID=" + currentSceneID
                + "]\r\n";
            Log(lg);
            //if (retCode != UnityGMClient.EEnterSceneResult.EENTER_SCENE_RESULT_SUCCESS)
            //{
            //    return;
            //}

            GC.CPlayer.Singleton.setCurrentSceneID(currentSceneID);
            this.Hide();
            timerWait.Stop();
            FormMain.showForm();
             
        }
        public static void showForm()
        {
            if (g_Form == null)
            {
                g_Form = new FormSelectRole();
            }

            g_Form.showRadioButton(GC.CPlayer.Singleton.getRoleBaseInfoList());
            g_Form.Show();
            g_Form.TimerStart();
        }

        public static FormSelectRole getForm()
        {
            if (g_Form == null)
            {
                g_Form = new FormSelectRole();
            }
            return g_Form;
        }

        private static FormSelectRole g_Form = null;

        private void btnDeleteRole_Click(object sender, EventArgs e)
        {
            string lg = "[selectRole_Click][SendMsgPlayerSystemGC2GMReqDeleteRole][m_roleIndex=" + m_roleIndex + "]\r\n";
            Log(lg);
            UnityGMClient.CClientCore.Singleton.SendMsgPlayerSystemGC2GMReqDeleteRole(m_roleIndex, CbDeleteRole);
        }

        private void CbDeleteRole(UnityGMClient.EDeleteRoleResult retCode, UInt32 roleIndex)
        {
            string lg = "[CbDeleteRole][SendMsgPlayerSystemGC2GMReqDeleteRole][retCode=" + retCode + "]\r\n";
            Log(lg);

            if (retCode == UnityGMClient.EDeleteRoleResult.EDELETEROLE_RESUlT_SUCCESS)
            {
                GC.CPlayer.Singleton.RemoveRole(roleIndex);
                showRadioButton(GC.CPlayer.Singleton.getRoleBaseInfoList());
            }
        }

        private void btnLogout_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Final();
            this.Hide();
            timerWait.Stop();
            FormLogin.showForm();
        }

        private void btnChangeServer_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Final();
            this.Hide();
            timerWait.Stop();
            FormSelectZone.showForm();
        }
    }
}
