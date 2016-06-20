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
    public partial class FormSkill : Form
    {
        private static FormSkill s_Form = null;
        private string m_learnSkillTPID;
        private string m_upgradeSkillTPID;
        private string m_buttonSkillTPID;
        private string m_buttonIndex;

        public FormSkill()
        {
            InitializeComponent();
        }

        private void learnSkillTextBox_TextChanged(object sender, EventArgs e)
        {
            learnSkillIDInputTextBox = sender as TextBox;
            m_learnSkillTPID = learnSkillIDInputTextBox.Text;
        }

        private void upgradeSkillTextBox_TextChanged(object sender, EventArgs e)
        {
            upgradeSkillIDInputTextBox = sender as TextBox;
            m_upgradeSkillTPID = upgradeSkillIDInputTextBox.Text;
        }

        private void skillLogTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void timerWait_Tick(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Update(0);
        }

        public void TimerStart()
        {
            timerWait.Start();
        }
        public static void showForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormSkill();
            }
            s_Form.Show();
            s_Form.TimerStart();
        }

        public static FormSkill getForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormSkill();
            }
            return s_Form;
        }

        private void _cbMsgSkillSystemGM2GCAckLearnSkill(UnityGMClient.ELearnSkillError error, UInt32 skillTPID)
        {
            if (error == UnityGMClient.ELearnSkillError.LEARN_SKILL_ERROR_SUCCESS)
            {
                skillLogTextBox.Text += string.Format("学习技能[{0}]成功\r\n", skillTPID);
            }
            else
            {
                skillLogTextBox.Text += string.Format("学习技能[{0}]失败:{1}\r\n", skillTPID, error.ToString());
            }
        }

        private void buttonLearnSkill_Click(object sender, EventArgs e)
        {
            try {
                UInt32 skillTPID = UInt32.Parse(m_learnSkillTPID);
                if (!UnityGMClient.CClientCore.Singleton.SendMsgSkillSystemGC2GMReqLearnSkill(skillTPID, _cbMsgSkillSystemGM2GCAckLearnSkill))
                {
                    MessageBox.Show("发送学习技能消息失败！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return;
                }
            }
            catch (System.Exception ) {
               skillLogTextBox.Text += "学习技能的ID输入有误!\r\n"; 	
            }
        }

        private void _cbMsgSkillSystemGM2GCAckUpgradeSkill(UnityGMClient.EUpgradeSkillError error, UInt32 skillTPID)
        {
            if (error == UnityGMClient.EUpgradeSkillError.UPGRADE_SKILL_ERROR_SUCCESS)
            {
                skillLogTextBox.Text += string.Format("强化技能[{0}]成功\r\n", skillTPID);
            }
            else
            {
                skillLogTextBox.Text += string.Format("强化技能[{0}]失败:{1}\r\n", skillTPID, error.ToString());
            }
        }
        private void buttonUpgradeSkill_Click(object sender, EventArgs e)
        {
           try {
                UInt32 skillTPID = UInt32.Parse(m_upgradeSkillTPID);
                if (!UnityGMClient.CClientCore.Singleton.SendMsgSkillSystemGC2GMReqUpgradeSkill(skillTPID, _cbMsgSkillSystemGM2GCAckUpgradeSkill))
                {
                    MessageBox.Show("发送升级技能消息失败！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return;
                }
            }
            catch (System.Exception ) {
               skillLogTextBox.Text += "升级技能的ID输入有误!\r\n"; 	
            }
        }

        private void _cbMsgSkillSystemGM2GCAckSetSkillButton(UnityGMClient.ESetSkillButtonError error, UInt32[] skillButtons)
        {
            if (error == UnityGMClient.ESetSkillButtonError.SET_SKILL_BUTTON_SUCCESS)
            {
                UInt32 skillTPID = UInt32.Parse(m_buttonSkillTPID);
                byte skillButtonIndex = byte.Parse(m_buttonIndex);
                skillLogTextBox.Text += string.Format("设置技能[技能][技能按钮][{0}][{1}]成功\r\n", skillTPID, skillButtonIndex);
                skillLogTextBox.Text += string.Format("============\r\n");
                for (int i = 0; i < UnityGMClient.CSkillDefine.SKILL_BUTTON_COUNT; ++i)
                {
                    skillLogTextBox.Text += string.Format("[{0}][{1}]\r\n", skillButtons[i], i);
                }
            }
            else
            {
                for (int i = 0; i < UnityGMClient.CSkillDefine.SKILL_BUTTON_COUNT; ++i )
                {
                    skillLogTextBox.Text += string.Format("设置技能[技能][技能按钮][{0}][{1}]:{2}\r\n", skillButtons[i], i, error.ToString());
                }
            }
        }

        private void buttonSetSkillButton_Click(object sender, EventArgs e)
        {
            try
            {
                UInt32 skillTPID = UInt32.Parse(m_buttonSkillTPID);
                byte skillButtonIndex = byte.Parse(m_buttonIndex);
                if (!UnityGMClient.CClientCore.Singleton.SendMsgSkillSystemGC2GMReqSetSkillButton(skillTPID, skillButtonIndex, _cbMsgSkillSystemGM2GCAckSetSkillButton))
                {
                    MessageBox.Show("发送设置技能按钮消息失败！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    return;
                }
            }
            catch (System.Exception )
            {
                skillLogTextBox.Text += "设置技能按钮的数据输入有误!\r\n";
            }
        }

        private void textBoxButtonSkillTPID_TextChanged(object sender, EventArgs e)
        {
            textBoxButtonSkillTPID = sender as TextBox;
            m_buttonSkillTPID = textBoxButtonSkillTPID.Text;
        }

        private void textBoxButtonIndex_TextChanged(object sender, EventArgs e)
        {
            textBoxButtonIndex = sender as TextBox;
            m_buttonIndex = textBoxButtonIndex.Text;
        }

        private void buttonExitSkillSystem_Click(object sender, EventArgs e)
        {
            this.Hide();
            timerWait.Stop();
            FormMain.showForm();
        }
    }
}
