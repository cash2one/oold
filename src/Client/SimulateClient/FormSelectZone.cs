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
    public partial class FormSelectZone : Form
    {
        public static FormSelectZone g_formSelectZone = null;
        GC.CServerdata m_server = new GC.CServerdata();

        public static void showForm(bool a_needTokenLogin)
        {
            if (g_formSelectZone == null)
            {
                g_formSelectZone = new FormSelectZone();
            }
            g_formSelectZone.showWnd(a_needTokenLogin);
            g_formSelectZone.TimerStart();
            if (FormLogin.g_FastEnter == true)
            {
                g_formSelectZone.sendTokenLoginByAccountID();
            }

        }

        public static void showForm()
        {
            if (g_formSelectZone == null)
            {
                g_formSelectZone = new FormSelectZone();
            }
            g_formSelectZone.showWnd();
            g_formSelectZone.TimerStart();
            if (FormLogin.g_FastEnter == true)
            {
                g_formSelectZone.sendTokenLoginByAccountID();
            }

        }

        public static FormSelectZone getForm()
        {
            if (g_formSelectZone == null)
            {
                g_formSelectZone = new FormSelectZone();
            }
            return g_formSelectZone;
        }

        public void showWnd(bool a_needTokenLogin)
        {
            int index = comboBoxZone.Items.IndexOf(FormLogin.g_serverName);
            g_formSelectZone.comboBoxZone.SelectedIndex = index;

            if (a_needTokenLogin)
            {
                buttonToken.Enabled = true;
                btnLogin.Enabled = false;
            }
            else
            {
                buttonToken.Enabled = false;
                btnLogin.Enabled = true;
            }

            g_formSelectZone.Show();
        }

        public void showWnd()
        {
            int index = comboBoxZone.Items.IndexOf(FormLogin.g_serverName);
            g_formSelectZone.comboBoxZone.SelectedIndex = index;
            g_formSelectZone.Show();
        }
        

        private void Log(string content)
        {
            string lg = "[" + this.Name.ToString() + "]" + content + "";
            GC.CLog.write(lg);
        }

        private void timerWait_Tick(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Update(0);
        }

        public void TimerStart()
        {
            timerWait.Start();
        }

        public FormSelectZone()
        {
            InitializeComponent();
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            sendTokenLoginByAccountID();
        }

        private void sendTokenLoginByAccountID()
        {
            m_server.m_serverIP = this.textBoxIp.Text;
            m_server.m_zoneID = UInt16.Parse(textZone.Text);
            m_server.m_serverPort = UInt16.Parse(textPort.Text);

            string token = GC.CPlayer.Singleton.m_taken;
            UInt64 accouontID = GC.CPlayer.Singleton.m_accountID;
            //string account = GC.CPlayer.Singleton.m_account;
            string lg = "[SendMsgLoginSystemGC2LGReqAccountLogin]\n\r"
               + "[serverIP=" + m_server.m_serverIP + "]\r\n"
               + "[serverPort=" + m_server.m_serverPort + "]\r\n"
               + "[zoneID=" + m_server.m_zoneID + "]\r\n"
               + "[token=" + token + "]\r\n";
            Log(lg);
            
            if (!UnityGMClient.CClientCore.Singleton.SendMsgLoginSystemGC2LGReqSelectServer(
                m_server.m_serverIP,
                m_server.m_serverPort,
                m_server.m_zoneID,
                accouontID,
                token,
                cbSelectServerResult))
            {
                MessageBox.Show("连接服务器失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
        }

        private void sendTokenLoginByAccountName()
        {
            m_server.m_serverIP = this.textBoxIp.Text;
            m_server.m_zoneID = UInt16.Parse(textZone.Text);
            m_server.m_serverPort = UInt16.Parse(textPort.Text);

            string token = GC.CPlayer.Singleton.m_taken;
            UInt64 accouontID = GC.CPlayer.Singleton.m_accountID;
            string account = GC.CPlayer.Singleton.m_account;
            string lg = "[SendMsgLoginSystemGC2LGReqAccountLogin]\n\r"
               + "[serverIP=" + m_server.m_serverIP + "]\r\n"
               + "[serverPort=" + m_server.m_serverPort + "]\r\n"
               + "[zoneID=" + m_server.m_zoneID + "]\r\n"
               + "[token=" + token + "]\r\n";
            Log(lg);

            if (!UnityGMClient.CClientCore.Singleton.SendMsgLoginSystemGC2LGReqSelectServer(
                m_server.m_serverIP,
                m_server.m_serverPort,
                m_server.m_zoneID,
                account,
                token,
                cbSelectServerResult))
            {
                MessageBox.Show("连接服务器失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
        }

        void cbSelectServerResult(UnityGMClient.EErrorPlayerLoginServer result)
        {
            string lg = "[cbNormalLoginResult][result=" + result.ToString() + "]\r\n";
            Log(lg);
            if (result == UnityGMClient.EErrorPlayerLoginServer.ELOGINRESULT_SUCCESS)
            {
                this.Hide();
                timerWait.Stop();
                FormSelectRole.showForm();
                FormSelectRole.getForm().InitPlayerData();
            }
            else
            {
                MessageBox.Show("登录失败[" + result.ToString() + "]", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void comboBoxZone_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.comboBoxZone.Items != null && comboBoxZone.Items.Count > 0 && comboBoxZone.SelectedItem != null)
            {
                string name = this.comboBoxZone.SelectedItem.ToString();
                m_server = GC.CServerMgr.Singleton.getServer(name);
                this.textBoxIp.Text = m_server.m_serverIP.ToString();
                this.textPort.Text = m_server.m_serverPort.ToString();
                this.textZone.Text = m_server.m_zoneID.ToString();
            }
        }

        private void btnLogout_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Final();
            this.Hide();
            timerWait.Stop();
            FormLogin.showForm();
        }

        private void buttonToken_Click(object sender, EventArgs e)
        {
            sendTokenLoginByAccountName();
        }
    }
}
