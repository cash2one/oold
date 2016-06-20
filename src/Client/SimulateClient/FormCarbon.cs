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
    public partial class FormCarbon : Form
    {
        public FormCarbon()
        {
            InitializeComponent();
            textBoxShow.Text = "";
        }

        private void FormCarbon_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void Log(string content)
        {
            string lg = "[" + this.Name.ToString() + "]" + content + "";
            log.write(lg);
        }

        public void InitPrizeData(List<UnityGMClient.CPrize> prizeList)
        {
            string lg = "";
            for (int i = 0; i < prizeList.Count; ++i)
            {
                textBoxShow.Text += "ItemID:" + prizeList[i].getItemID().ToString() + "\r\n";
                lg += "ItemID:" + prizeList[i].getItemID().ToString() + "\r\n";
            }
            Log(lg);
        }

        private void CbEnterScene(UnityGMClient.EEnterSceneResult retCode, UInt32 currentSceneID, UInt32 prizeCount, List<UnityGMClient.CPrize> prizeList)
        {
            string lg = "[CbEnterScene][retCode=" + retCode.ToString() + "][prizeCount=" + prizeCount.ToString() + "]\r\n";
            Log(lg);

            if (retCode != UnityGMClient.EEnterSceneResult.EENTERSCENE_RESUlT_SUCCESS)
            {
                return;
            }

            GC.CPlayer.Singleton.setCurrentSceneID(currentSceneID);
            this.Hide();
            FormMain.showForm();
        }

        public static void showForm()
        {
            if (g_Form == null)
            {
                g_Form = new FormCarbon();
            }
            g_Form.Show();
             g_Form.TimerStart();
        }

        public static FormCarbon getForm()
        {
            if (g_Form == null)
            {
                g_Form = new FormCarbon();
            }
            return g_Form;
        }

        private static FormCarbon g_Form = null;

        private void timerWait_Tick(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.Update(0);
        }

        public void TimerStart()
        {
            timerWait.Start();
        }

        private void ExitInstanceToolStripMenuItem_Click(object sender, EventArgs e)
        {
            uint sceneTypeID = 1;
            string lg = "[SendMsgPlayerSystemGC2GMReqEnterScene][sceneTypeID=" + sceneTypeID + "]\r\n";
            Log(lg);
            UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqEnterScene(sceneTypeID, CbEnterScene);
        }

        private void ReviveToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
        
    }
}
