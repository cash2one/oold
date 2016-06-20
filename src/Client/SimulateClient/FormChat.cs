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
    public partial class FormChat : Form
    {
        const string WORLD_CHANNEL = "世界频道";
        const string PRIVATE_CHANNEL = "私聊频道";
        const string ANNOUNCE_CHAT = "公告频道";
        const string CITY_CHAT = "主城频道";

        private static FormChat s_Form = null;
        UnityGMClient.EChatChanel m_channel = UnityGMClient.EChatChanel.CHAT_CHANNEL_PRIVATE;
        UnityGMClient.SRoleKey m_roleKey;
        UnityGMClient.CChatEquipID m_equipID = new UnityGMClient.CChatEquipID(0, 0);

        public FormChat()
        {
            InitializeComponent();
            UnityGMClient.CClientCore.Singleton.RegisterInitRoleChatToAllCallBack(_cbMsgChatSystemGM2GCAckChat2All);
        }

        public void TimerStart()
        {
            timerWait.Start();
        }
        public static void showForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormChat();
            }
            s_Form.Show();
            s_Form.TimerStart();
        }

        private void _cbMsgChatSystemGM2GCAckPrivateChat(UnityGMClient.EChatResult result)
        {
            if (result == UnityGMClient.EChatResult.CHAT_RESULT_SUCCESS)
            {

            }
            else
            {

            }
        }

        private void _cbMsgChatSystemGM2GCAckChat(UnityGMClient.EChatResult result)
        {
            if (result == UnityGMClient.EChatResult.CHAT_RESULT_SUCCESS)
            {

            }
            else
            {

            }
        }

        private void _cbMsgChatSystemGM2GCAckChat2All(UnityGMClient.CChatContent content)
        {
            textBoxChatContent.Text += string.Format("[{0}]{1} VIP[{2}]说：{3}\r\n", content.m_channel.ToString(), content.m_senderName, content.m_VIPLevel, content.m_content);
        }

        public static FormChat getForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormChat();
            }
            return s_Form;
        }

        private void buttonChatExit_Click(object sender, EventArgs e)
        {
            this.Hide();
            timerWait.Stop();
            FormMain.showForm();
        }

        private void textBoxPrivateChatRoleID_TextChanged(object sender, EventArgs e)
        {
            textBoxPrivateChatReceiverAccountID = sender as TextBox;
            try
            {
                m_roleKey.m_accountID = UInt32.Parse(textBoxPrivateChatReceiverAccountID.Text);
            }
            catch (System.Exception)
            {
                textBoxChatContent.Text += "私聊接收的角色ID填写有误!\r\n";
            }
        }

        private void textBoxChatContent_TextChanged(object sender, EventArgs e)
        {
            textBoxChatContent = sender as TextBox;
        }

        private void textBoxChatInput_TextChanged(object sender, EventArgs e)
        {
            textBoxChatInput = sender as TextBox;
        }

        private void timerWait_Tick(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Update(0);
        }

        private void comboBoxChannel_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBoxChannel.Items != null && comboBoxChannel.Items.Count > 0 && comboBoxChannel.SelectedItem != null)
            {
                string name = comboBoxChannel.SelectedItem.ToString();
                switch(name)
                {
                    case PRIVATE_CHANNEL:
                        {
                            m_channel = UnityGMClient.EChatChanel.CHAT_CHANNEL_PRIVATE;
                            m_roleKey.m_roleIndex = 0;
                            m_roleKey.m_zoneID = 22;
                        }
                        break;
                    case WORLD_CHANNEL:
                        {
                            m_channel = UnityGMClient.EChatChanel.CHAT_CHANNEL_WORLD;
                        }
                        break;
                    case CITY_CHAT:
                        {
                            m_channel = UnityGMClient.EChatChanel.CHAT_CHANNEL_CITY;
                        }
                        break;
                    case ANNOUNCE_CHAT:
                        {
                            m_channel = UnityGMClient.EChatChanel.CHAT_CHANNEL_ANNOUNCE;
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        private void buttonSend_Click(object sender, EventArgs e)
        {
            if (!UnityGMClient.CClientCore.Singleton.SendMsgChatSystemGC2GMReqChat(m_roleKey, m_channel, textBoxChatInput.Text, m_equipID, _cbMsgChatSystemGM2GCAckChat))
            {
                MessageBox.Show("发送聊天信息失败！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void textBoxZoneID_TextChanged(object sender, EventArgs e)
        {
            textBoxZoneID = sender as TextBox;
            try
            {
                m_roleKey.m_zoneID = UInt16.Parse(textBoxZoneID.Text);
            }
            catch (System.Exception)
            {
                textBoxChatContent.Text += "私聊接收的角色区填写有误!\r\n";
            }
        }

        private void textBoxRoleIndex_TextChanged(object sender, EventArgs e)
        {
            textBoxRoleIndex = sender as TextBox;
            try
            {
                m_roleKey.m_roleIndex = UInt32.Parse(textBoxRoleIndex.Text);
            }
            catch (System.Exception)
            {
                textBoxChatContent.Text += "私聊接收的角色Index填写有误!\r\n";
            }
        }

        private void textBoxBagIndex_TextChanged(object sender, EventArgs e)
        {
            textBoxBagIndex = sender as TextBox;
            try
            {
                m_equipID.m_bagIndex = UInt32.Parse(textBoxBagIndex.Text);
            }
            catch (System.Exception)
            {
                textBoxChatContent.Text += "背包Index填写有误!\r\n";
            }
        }

        private void textBoxEquipID_TextChanged(object sender, EventArgs e)
        {
            textBoxEquipID = sender as TextBox;
            try
            {
                m_equipID.m_equipID = UInt32.Parse(textBoxEquipID.Text);
            }
            catch (System.Exception)
            {
                textBoxChatContent.Text += "装备ID填写有误!\r\n";
            }
        }



    }
}
