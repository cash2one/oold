using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
namespace SimulateClient
{
    public partial class FormLogin : Form
    {
        private string m_space = "";
        private string m_flag = "☀☀☀";
        public static string g_serverName = GC.CServerName.SERVER_ZP;
        public static bool g_FastEnter = false;
        public static GC.CServerdata m_server = new GC.CServerdata();

        public FormLogin()
        {
            InitializeComponent();

            timerWait.Start();
            labelWait.Text = "";
            UnityGMClient.CClientCore.Singleton.RegisterNetStatusUpdate(cbNetStatusUpdate);
            GC.CPlayer.Singleton.Init();
            initServer();
            this.comboBoxServer.SelectedIndex = 6;
            int index = comboBoxServer.Items.IndexOf(FormLogin.g_serverName);
            this.comboBoxServer.SelectedIndex = index;
        }

        private void buttonLogin_Click(object sender, EventArgs e)
        {
            sendNormalLogin();
            setButtonState(false);
        }

        private void buttonFastLogin_Click(object sender, EventArgs e)
        {
            sendFastLogin();
            setButtonState(false);
        }

        private void buttonFastRegister_Click(object sender, EventArgs e)
        {
            sendFastRegister();
            setButtonState(false);
        }
        private void normalRegister_Click(object sender, EventArgs e)
        {
            sendNormalRegister();
            setButtonState(false);
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        void cbLoginResult(UnityGMClient.EGetAccountTokenResult result,UInt64 a_accountID,string a_taken)
        {
            GC.CPlayer.Singleton.m_taken = a_taken;
            GC.CPlayer.Singleton.m_accountID = a_accountID;
            
            string lg = "[cbNormalLoginResult][result=" + result.ToString() + "]\r\n";
            Log(lg);
            setButtonState(true);
            if (result == UnityGMClient.EGetAccountTokenResult.EGETACCOUNTTAKEN_SUCCESS)
            {
                buttonCancel.Visible = false;
                this.Hide();
                timerWait.Stop();
                FormSelectZone.showForm(false);

            }
            else
            {
                MessageBox.Show("获取Token登录失败[" + result.ToString() + "]", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        void cbFastLoginResult(UnityGMClient.EErrorPlayerLoginServer result)
        {
            string lg = "[cbFastLoginResult][result=" + result.ToString() + "]\r\n";
            Log(lg);
            setButtonState(true);
            if (result == UnityGMClient.EErrorPlayerLoginServer.ELOGINRESULT_SUCCESS)
            {
                buttonCancel.Visible = false;
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

        void cbFastRegiterResult(UnityGMClient.ERegisterResult result)
        {
            string lg = "[cbFastRegiterResult][result=" + result.ToString() + "]\r\n";
            Log(lg);
            setButtonState(true);

            if (result == UnityGMClient.ERegisterResult.EREGISTERRESULT_SUCCESS)
            {
                if (MessageBox.Show("注册成功！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information).ToString() !="")
                {
                    //sendFastLogin();
                }
            }
            else
            {
                MessageBox.Show("注册失败[" + result.ToString() + "]", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }



        void cbNormalRegiterResult(UnityGMClient.ERegisterResult result)
        {
            string lg = "[cbNormalRegiterResult][result=" + result.ToString() + "]\r\n";
            Log(lg);
            setButtonState(true);

            if (result == UnityGMClient.ERegisterResult.EREGISTERRESULT_SUCCESS)
            {
                if (MessageBox.Show("注册成功,是否现在登录？", "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Information) == DialogResult.Yes)
                {
                    sendNormalLogin();
                    setButtonState(false);
                }
            }
            else
            {
                MessageBox.Show("注册失败[" + result.ToString() + "]", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }


        private void sendFastLogin()
        {
            string serverIP = textBoxIp.Text;
            string account = textBoxAccount.Text;
            string password = textBoxPassword.Text;
            ushort zoneID = UInt16.Parse(textZone.Text);
            ushort serverPort = UInt16.Parse(textPort.Text);
            string uniqueID = GC.CHelper.getUniqueID();
            string uniqueKey = GC.CHelper.getUniqueID();
            GC.CPlayer.Singleton.m_account = account;

            string lg = "[SendMsgLoginSystemGC2LGReqFastLogin]\n\r"
                + "[uniqueID=" + uniqueID + "]\r\n"
                + "[uniqueKey=" + uniqueKey + "]\r\n"
                + "[serverIP=" + serverIP + "]\r\n"
                + "[serverPort=" + serverPort + "]\r\n"
                + "[zoneID=" + zoneID + "]\r\n";
            Log(lg);

            if (!UnityGMClient.CClientCore.Singleton.SendMsgLoginSystemGC2LGReqFastLogin(
                serverIP, 
                serverPort, 
                uniqueID, 
                uniqueKey, 
                "windows", 
                0,
                cbLoginResult))
            {
                MessageBox.Show("连接服务器失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
        }

        private void sendNormalLogin()
        {
            string serverIP = textBoxIp.Text;
            string account = textBoxAccount.Text;
            string password = textBoxPassword.Text;
            ushort zoneID = UInt16.Parse(textZone.Text);
            ushort serverPort = UInt16.Parse(textPort.Text);
            GC.CPlayer.Singleton.m_account = account;

            string lg = "[SendMsgLoginSystemGC2LGReqGetAccountTaken]\n\r"
               + "[account=" + account + "]\r\n"
               + "[password=" + password + "]\r\n"
               + "[serverIP=" + serverIP + "]\r\n"
               + "[serverPort=" + serverPort + "]\r\n";
            Log(lg);

            if (!UnityGMClient.CClientCore.Singleton.SendMsgLoginSystemGC2LGReqNormalLogin(
                serverIP,
                serverPort,
                account,
                password,
                "windows",
                0,
                cbLoginResult))
            {
                MessageBox.Show("连接服务器失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
        }

        private void sendFastRegister()
        {
            string serverIP = textBoxIp.Text;
            string account = textBoxAccount.Text;
            string password = textBoxPassword.Text;
            ushort zoneID = UInt16.Parse(textZone.Text);
            ushort serverPort = UInt16.Parse(textPort.Text);
            string uniqueID = GC.CHelper.getUniqueID();
            string uniqueKey = GC.CHelper.getUniqueID();
            string lg = "[SendMsgLoginSystemGC2LGReqFastRegister]:uniqueID:" + uniqueID + "\r\n";
            Log(lg);

            if (!UnityGMClient.CClientCore.Singleton.SendMsgLoginSystemGC2LGReqFastRegister(
                serverIP, 
                serverPort, 
                uniqueID, 
                uniqueKey, 
                "windows", 
                0, 
                cbFastRegiterResult))
            {
                MessageBox.Show("连接服务器失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
        }

        private string GB2312ToUTF8(string str)
        {
            try
            {
                Encoding utf8 = Encoding.UTF32;
                Encoding gb2312 = Encoding.GetEncoding("GB2312");
                byte[] unicodeBytes = gb2312.GetBytes(str);
                byte[] asciiBytes = Encoding.Convert(gb2312, utf8, unicodeBytes);
                char[] asciiChars = new char[utf8.GetCharCount(asciiBytes, 0, asciiBytes.Length)];
                utf8.GetChars(asciiBytes, 0, asciiBytes.Length, asciiChars, 0);
                string result = new string(asciiChars);
                return result;
            }
            catch
            {
                return "";
            }
        }

        private void sendNormalRegister()
        {
            string serverIP = textBoxIp.Text;
            string account = textBoxAccount.Text;
            string password = textBoxPassword.Text;
            ushort zoneID = UInt16.Parse(textZone.Text);
            ushort serverPort = UInt16.Parse(textPort.Text);
            string lg = "[SendMsgLoginSystemGC2LGReqNormalRegister][account=" + account + "]\r\n";
            Log(lg);

            if (!UnityGMClient.CClientCore.Singleton.SendMsgLoginSystemGC2LGReqNormalRegister(
                serverIP, 
                serverPort, 
                account, 
                password,  
                "windows", 
                0,
                "AAAR27ZuW4GYnqMMirvmZXxBQ",
                cbNormalRegiterResult))
            {
                MessageBox.Show("连接服务器失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }
        }

        private void timerWait_Tick(object sender, EventArgs e)
        {
            if (!buttonLogin.Enabled)
            {
                UnityGMClient.CClientCore.Singleton.Update(0);
                m_space += " ";
                if (m_space.Length >= 10)
                {
                    m_space = "";
                }
                labelWait.Text = m_space + m_flag;
            }
        }

        private void textBoxIp_TextChanged(object sender, EventArgs e)
        {

        }

        public void cbNetStatusUpdate(UnityGMClient.ENetStatus netStatus)
        {
            string lg = "[cbNetStatusUpdate][netStatus=" + netStatus.ToString() + "]\r\n";
            Log(lg);
            setButtonState(true);
            DialogResult result = DialogResult.None;
            switch (netStatus)
            {
                case UnityGMClient.ENetStatus.ENETSTATUS_OFFLINE:
//                     result = MessageBox.Show("服务器连接已断开，是否重连?", "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
// 
//                     if (DialogResult.Yes == result)
//                     {
//                         UnityGMClient.CClientCore.Singleton.SendMsgReConnectServer();
//                     }
                    
                    break;
                case UnityGMClient.ENetStatus.ENETSTATUS_RECONNECT_FAIL:
                    result = MessageBox.Show("与服务器断开，是否重连?", "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

                    if (DialogResult.Yes == result)
                    {
                        UnityGMClient.CClientCore.Singleton.SendMsgReConnectServer();
                    }

                    break;
                case UnityGMClient.ENetStatus.ENETSTATUS_RECONNECT_INVALID:
                    result = MessageBox.Show("与服务器断开，是否重新登录?", "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                    if (DialogResult.Yes == result)
                    {
                        UnityGMClient.CClientCore.Singleton.SendMsgReLogin();
                    }
                    else
                    {
                        Application.Exit();
                    }
                    break;
//                 case UnityGMClient.ENetStatus.ENETSTATUS_GAME_RECONNECTFAIL:
//                     result = MessageBox.Show("重连失败，是否继续重连？", "提示", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
// 
//                     if (DialogResult.Yes == result)
//                     {
//                         UnityGMClient.CClientCore.Singleton.SendMsgReLogin();
//                     }
//                     break;
                case UnityGMClient.ENetStatus.ENETSTATUS_NULL:
                    ;
                    break;
                default:
                    break;
            }
        }

        private void initServer()
        {
            CIniFile ini = new CIniFile("./server.ini");
            string lg = "load config:"+ini.path;
            Log(lg);
            if ((ini.IniReadValue("server", "ip") != "") 
                && (ini.IniReadValue("server", "port") != "") 
                && (ini.IniReadValue("server", "zoneid") != ""))
            {
                textBoxIp.Text = ini.IniReadValue("server", "ip");
                textPort.Text = ini.IniReadValue("server", "port");
                textZone.Text = ini.IniReadValue("server", "zoneid");
            }
        }

        private void Log(string content)
        {
            string lg = "[" + this.Name.ToString() + "]" + content + "";
            GC.CLog.write(lg);
        }

        private void setButtonState(bool enabled)
        {
            buttonLogin.Enabled = enabled;
            buttonFastLogin.Enabled = enabled;
            normalRegister.Enabled = enabled;
        }

        public static void showForm()
        {
            if (g_loginForm == null)
            {
                g_loginForm = new FormLogin();
            }
            g_loginForm.Show();
            g_loginForm.timerWait.Start();
            g_FastEnter = false;
        }

        public static FormLogin getForm()
        {
            if (g_loginForm == null)
            {
                g_loginForm = new FormLogin();
            }
            return g_loginForm;
        }

        private static FormLogin g_loginForm = null;

        private void comboBoxServer_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this.comboBoxServer.Items != null && comboBoxServer.Items.Count > 0 && comboBoxServer.SelectedItem != null)
            {
                FormLogin.g_serverName = this.comboBoxServer.SelectedItem.ToString();
                m_server = GC.CServerMgr.Singleton.getServer(FormLogin.g_serverName);
                textBoxIp.Text = m_server.m_serverIP;
                textPort.Text = m_server.m_serverPort.ToString();
                textZone.Text = m_server.m_zoneID.ToString();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            g_FastEnter = true;
            sendNormalLogin();
            setButtonState(false);
        }

        private void buttonToken_Click(object sender, EventArgs e)
        {
            GC.CPlayer.Singleton.m_taken = textBoxPassword.Text;
            GC.CPlayer.Singleton.m_accountID = 0;
            GC.CPlayer.Singleton.m_account = textBoxAccount.Text;

            buttonCancel.Visible = false;
            this.Hide();
            timerWait.Stop();
            FormSelectZone.showForm(true);

        }
    }
}
