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
    public partial class FormFriend : Form
    {
        public FormFriend()
        {
            InitializeComponent();
            this.timer1.Start();

            UnityGMClient.CClientCore.Singleton.RegisterFriendSystemCN2GCFriendsAddConfirm(_CBMsgFriendSystemCN2GCReqFriendAddConfirm);
            UnityGMClient.CClientCore.Singleton.RegisterFriendSystemCN2GCNtfFriendsAddResult(_CBAddResult);
        }

        static FormFriend s_Form = null;

        public static void showForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormFriend();
            }
            s_Form.Show();
        }

        public static FormFriend getForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormFriend();
            }
            return s_Form;
        }

        private void timerWait_Tick(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Update(0);
        }

        string getParam1()
        {
            string id = textBoxParam1.Text;
            return id;
        }

        string getParam2()
        {
            string id = textBoxParam2.Text;
            return id;
        }


        string getParam3()
        {
            string id = textBoxParam3.Text;
            return id;
           // return System.UInt32.Parse(id);
        }

        UInt32 ToUint32(string a)
        {
            return System.UInt32.Parse(a);
        }



        void _CBMsgFriendSystemCN2GCAckFriendsOpen(List<UnityGMClient.SFriendInfo> info, UInt32 capacity)
        {

        }

        private void buttonOpen_Click(object sender, EventArgs e)
        {
            bool success = UnityGMClient.CClientCore.Singleton.SendMsgFriendSystemGC2CNReqFriendsOpen(_CBMsgFriendSystemCN2GCAckFriendsOpen);
        }

        private void FormFriend_FormClosed(object sender, FormClosedEventArgs e)
        {
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            this.Hide();
            FormMain.showForm();
        }

        void _CBMsgFriendSystemCN2GCReqFriendAddConfirm(List<UnityGMClient.SFriendInfo> a_list)
        {

        }

        void _CBAddResult(List<UnityGMClient.SFriendInfo> a_list, List<UnityGMClient.FriendResult> a_result)
        {

        }

        private void buttonAdd_Click(object sender, EventArgs e)
        {   
            List<UnityGMClient.SFriendRoleInfo> roles = new List<UnityGMClient.SFriendRoleInfo>();
            UnityGMClient.SFriendRoleInfo info = new UnityGMClient.SFriendRoleInfo();
            info.m_account =  System.UInt64.Parse(getParam1());
            info.m_zone = System.UInt16.Parse(getParam2());
            info.m_index = System.Int32.Parse(getParam3());
            roles.Add(info);
            bool success = UnityGMClient.CClientCore.Singleton.SendMsgFriendSystemGC2CNReqFriendsAdd(roles);
        }

        private void buttonAddConfirmAgree_Click(object sender, EventArgs e)
        {
            List<UnityGMClient.SFriendRoleInfo> roles = new List<UnityGMClient.SFriendRoleInfo>();
            UnityGMClient.SFriendRoleInfo info = new UnityGMClient.SFriendRoleInfo();
            info.m_account = System.UInt64.Parse(getParam1());
            info.m_zone = System.UInt16.Parse(getParam2());
            info.m_index = System.Int32.Parse(getParam3());
            roles.Add(info);
            bool success = UnityGMClient.CClientCore.Singleton.SendMsgFriendSystemGC2CNAckFriendsAddConfirm(1, roles);
        }

        void _CBMsgFriendSystemCN2GCAckFriendsDel(List<UnityGMClient.SFriendRoleInfo> role_info)
        {

        }

        private void buttonDel_Click(object sender, EventArgs e)
        {
            List<UnityGMClient.SFriendRoleInfo> roles = new List<UnityGMClient.SFriendRoleInfo>();
            UnityGMClient.SFriendRoleInfo info = new UnityGMClient.SFriendRoleInfo();
            info.m_account = System.UInt64.Parse(getParam1());
            info.m_zone = System.UInt16.Parse(getParam2());
            info.m_index = System.Int32.Parse(getParam3());
            roles.Add(info);
            bool success = UnityGMClient.CClientCore.Singleton.SendMsgFriendSystemGC2CNReqFriendsDel(roles, _CBMsgFriendSystemCN2GCAckFriendsDel);
        }

        void _CBMsgFriendSystemCN2GCAckFriendsNewStrangers(List<UnityGMClient.SFriendInfo> info)
        {

        }

        private void buttonNewStrangers_Click(object sender, EventArgs e)
        {
            bool success = UnityGMClient.CClientCore.Singleton.SendMsgFriendSystemGC2CNReqFriendsNewStrangers(_CBMsgFriendSystemCN2GCAckFriendsNewStrangers);
        }

        void _CBMsgFriendSystemCN2GCAckFriendsSearch(List<UnityGMClient.SFriendInfo> info)
        {

        }

        private void buttonSearch_Click(object sender, EventArgs e)
        {
            bool success = UnityGMClient.CClientCore.Singleton.SendMsgFriendSystemGC2CNReqFriendsSearch(ToUint32(getParam1()), getParam2(),
                _CBMsgFriendSystemCN2GCAckFriendsSearch);
        }

        void _CBMsgFriendSystemGM2GCAckFriendsLocal(List<UnityGMClient.SFriendInfo> info)
        {

        }

        private void buttonLocal_Click(object sender, EventArgs e)
        {
            bool success = UnityGMClient.CClientCore.Singleton.SendMsgFriendSystemGC2GMReqFriendsLocal(_CBMsgFriendSystemGM2GCAckFriendsLocal);
        }
    }
}
