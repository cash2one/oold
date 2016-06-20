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
    public partial class FormShop : Form
    {
        public FormShop()
        {
            InitializeComponent();
            this.timer1.Start();
        }

        static FormShop s_Form = null;

        public static void showForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormShop();
            }
            s_Form.Show();
        }

        public static FormShop getForm()
        {
            if (s_Form == null)
            {
                s_Form = new FormShop();
            }
            return s_Form;
        }

        void resultToString(UnityGMClient.EShopType type, List<Int32> ids, List<Int32> nums, UInt64 refreshTime, UnityGMClient.EShopSystemResult result)
        {
            textBoxOutput.Clear();
            textBoxOutput.Text = type.ToString() + "\r\n";
            for (Int32 i = 0; i < ids.Count(); i++)
            {
                textBoxOutput.Text += ids[i].ToString() + ";";
                textBoxOutput.Text += nums[i].ToString() + "\r\n";
            }

            textBoxOutput.Text += refreshTime.ToString() + "\r\n";
            textBoxOutput.Text += result.ToString();
        }

        UnityGMClient.EShopType getCurType()
        {
            String input = textBoxInput.Text;
            if ("1" == input)
            {
                return UnityGMClient.EShopType.ESHOPTYPE_PROP;
            }
            else if ("2" == input)
            {
                return UnityGMClient.EShopType.ESHOPTYPE_PVP;
            }

            return UnityGMClient.EShopType.ESHOPTYPE_DAILY;
        }

        UInt32 getCurId()
        {
            string id = textBoxId.Text;
            return System.UInt32.Parse(id);
        }

        UInt32 getCurNum()
        {
            string num = textBoxNum.Text;
            return System.UInt32.Parse(num);
        }

        void cbGM2GCAckShopOpen(UnityGMClient.EShopType type, List<UnityGMClient.ShopSystemItemInfo> itemInfo, UInt64 refreshTime)
        {
            //resultToString(type, ids, nums, refreshTime, UnityGMClient.EShopSystemResult.ESHOPSYSTEMRESULT_SUCCESS);
        }

        private void buttonOpen_Click(object sender, EventArgs e)
        {

            bool success = UnityGMClient.CClientCore.Singleton.SendMsgShopSystemGC2GMReqShopOpen(getCurType(), cbGM2GCAckShopOpen);
        }

        private void buttonExit_Click(object sender, EventArgs e)
        {
            this.Hide();
            FormMain.showForm();
        }

        private void timerWait_Tick(object sender, EventArgs e)
        {
             UnityGMClient.CClientCore.Singleton.Update(0);
        }

        void cbShopBuy(UnityGMClient.EShopType type, Int32 id, Int32 num, UnityGMClient.EShopSystemResult result)
        {
            List<Int32> ids = new List<Int32>();
            ids.Add(id);

            List<Int32> nums = new List<Int32>();
            nums.Add(num);

            resultToString(type, ids, nums, 0, result);
        }

        private void buttonBuy_Click(object sender, EventArgs e)
        {
            bool success = UnityGMClient.CClientCore.Singleton.SendMsgShopSystemGC2GMReqShopBuy(getCurType(), getCurId(), getCurNum(), cbShopBuy);
        }

        void cbShopRefresh(UnityGMClient.EShopType type, List<Int32> ids, List<Int32> nums, UnityGMClient.EShopSystemResult result, UInt64 refreshTime)
        {
            resultToString(type, ids, nums, refreshTime, result);
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            bool success = UnityGMClient.CClientCore.Singleton.SendMsgShopSystemGC2GMReqShopRefresh(getCurType(), cbShopRefresh);
        }

        void cbPaidRefresh(UnityGMClient.EShopType type, List<Int32> ids, List<Int32> nums, UnityGMClient.EShopSystemResult result)
        {
            resultToString(type, ids, nums, 0, result);
        }

        private void buttonPaidRefresh_Click(object sender, EventArgs e)
        {
            bool success = UnityGMClient.CClientCore.Singleton.SendMsgShopSystemGC2GMReqShopPaidRefresh(getCurType(), cbPaidRefresh);
        }

        void _CBMsgShopSystemGM2GCAckOpenCard(UInt32 fun_type, UInt32 glod1_free, UInt32 gold1_next_cost, UInt64 gold1_next_secs, UInt32 gold10_next_cost,
            UInt32 diamond1_free, UInt32 diamond1_next_cost, UInt64 diamond1_next_secs, UInt32 diamond10_next_cost)
        {

        }

        private void OpenCardBtn_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgShopSystemGC2GMReqOpenCard( getCurId(), _CBMsgShopSystemGM2GCAckOpenCard);
        }

        public void _CBMsgShopSystemGM2GCAckClick(UInt32 fun_type, UInt32 cost_type, UInt32 result, List<UInt32> item_ids, List<UInt32> item_nums)
        {

        }

        private void clickCardBtn_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgShopSystemGC2GMReqClick( getCurId(), getCurNum(), _CBMsgShopSystemGM2GCAckClick);
        }


        public  void _CBMsgShopSystemGM2GCAckEventState(UInt32 update_typ, UInt32 triggered,
            UInt32 item_id, List<UInt32> event_names)
        {

        }

        private void GetCardBtn_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgShopSystemGC2GMReqEventState(_CBMsgShopSystemGM2GCAckEventState);
        }

    }
}
