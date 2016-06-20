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
    public partial class FormInstance : Form
    {
        public UInt32 m_para1;
        public UInt32 m_para2;
        public UInt32 m_para3;

        public FormInstance()
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
            GC.CLog.write(lg);
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

        private void CbEnterScene(UnityGMClient.EEnterSceneResult retCode, UInt32 currentSceneID, List<UnityGMClient.CSceneRoleInfo> listSceneRoles)
        {
            //string lg = "[CbEnterScene][retCode=" + retCode.ToString() + "][prizeCount=" + prizeCount.ToString() + "]\r\n";
            //Log(lg);

            if (retCode != UnityGMClient.EEnterSceneResult.EENTER_SCENE_RESULT_SUCCESS)
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
                g_Form = new FormInstance();
            }
            g_Form.Show();
             g_Form.TimerStart();
        }

        public static FormInstance getForm()
        {
            if (g_Form == null)
            {
                g_Form = new FormInstance();
            }
            return g_Form;
        }

        private static FormInstance g_Form = null;

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

        private void buttonGetStoryInstanceProgress_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqGetStroyInstanceProgress(delegate(UInt32 instanceID, UInt16 index)
            {
                textBoxShow.Text += "================================================\r\n";
                string strResult = string.Format("Story instance progress: instance[{0}], stageIndex:[{1}]", instanceID, index);
                textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                UnityUtility.CTrace.Singleton.trace(strResult);
            }
            );
        }

        private void buttonEnterStage_Click(object sender, EventArgs e)
        {
            try
            {
                UnityGMClient.SRoleKey helperKey;
                //helperKey.m_accountID = 10000001;
                //helperKey.m_zoneID = 22;
                //helperKey.m_roleIndex = 3;
                helperKey.m_accountID = 0;
                helperKey.m_zoneID = 0;
                helperKey.m_roleIndex = 0;
                UInt32 instanceTPID = UInt32.Parse(textBoxInstanceID.Text);
                UInt32 stageIndex = UInt32.Parse(textBoxStageIndex.Text);
                UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqEnterStage(instanceTPID, (UInt16)stageIndex, helperKey, delegate(UnityGMClient.EEnterSceneResult result,
                                                                                         UnityGMClient.CBattleRoleData helperData, UnityGMClient.CStageMonster stageMonster)
                {
                    textBoxShow.Text += "================================================\r\n";
                    string strResult = string.Format("enter stage ack result[{0}]", result);
                    textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                    UnityUtility.CTrace.Singleton.trace(strResult);
                    foreach (UnityGMClient.CStageUnitMonster unit in stageMonster.m_stageUnitMonster)
                    {
                        foreach (UnityGMClient.CMonsterBatch batch in unit.m_monsterBatches)
                        {
                            foreach (UnityGMClient.CMonster monster in batch.m_randomMonster)
                            {
                                string strMonster = string.Format("随机掉落怪:index[{0}] type[{1}]\r\n", monster.m_index, monster.m_type);
                                textBoxShow.Text += strMonster;
                                foreach (UnityGMClient.CPrizeItem prizeItem in monster.m_listDropItems)
                                {
                                    string strPrizeItem = string.Format("物品ID[{0}] 物品数量[{1}]\r\n", prizeItem.m_ItemTPID, prizeItem.m_ItemCount);
                                }
                            }
                            foreach (UnityGMClient.CMonster monster in batch.m_certainlyMonster)
                            {
                                string strMonster = string.Format("随机掉落怪:index[{0}] type[{1}]\r\n", monster.m_index, monster.m_type);
                                textBoxShow.Text += strMonster;
                                foreach (UnityGMClient.CPrizeItem prizeItem in monster.m_listDropItems)
                                {
                                    string strPrizeItem = string.Format("物品ID[{0}] 物品数量[{1}]\r\n", prizeItem.m_ItemTPID, prizeItem.m_ItemCount);
                                    textBoxShow.Text += strPrizeItem;
                                }
                            }
                            if (batch.m_boss != null)
                            {
                                UnityGMClient.CMonster monster = batch.m_boss;
                                string strMonster = string.Format("随机掉落怪:index[{0}] type[{1}]\r\n", monster.m_index, monster.m_type);
                                textBoxShow.Text += strMonster;
                                foreach (UnityGMClient.CPrizeItem prizeItem in monster.m_listDropItems)
                                {
                                    string strPrizeItem = string.Format("物品ID[{0}] 物品数量[{1}]\r\n", prizeItem.m_ItemTPID, prizeItem.m_ItemCount);
                                    textBoxShow.Text += strPrizeItem;
                                }
                            }
                        }
                    }
                }
                );
            }
            catch (System.Exception)
            {
            	
            }

        }

        private void textBoxInstanceID_TextChanged(object sender, EventArgs e)
        {
            textBoxInstanceID = sender as TextBox;
        }

        private void textBoxStageIndex_TextChanged(object sender, EventArgs e)
        {
            textBoxStageIndex = sender as TextBox;
        }

        private void buttonReqGetInstanceData_Click(object sender, EventArgs e)
        {
            try
            {
                UInt32 instanceTPID = UInt32.Parse(textBoxReqInstanceInfoID.Text);
                UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqGetInstanceData(instanceTPID, delegate(UnityGMClient.EGetInstanceDataResult result, UInt32 instanceID, List<UnityGMClient.CStageData> listInstanceData)
                {
                    
                    textBoxShow.Text += "================================================\r\n";
                    string strResult = string.Format("ReqGetInstanceDataAck  result[{0}] instanceID[{1}] stage list count [{2}]", result, instanceID, listInstanceData.Count);
                    textBoxShow.Text += strResult;
                    textBoxShow.Text += "\r\n";

                    UnityUtility.CTrace.Singleton.trace(strResult);
                    foreach (UnityGMClient.CStageData stage in listInstanceData)
                    {
                        string log = string.Format("stageID[{0}] star[{1}] enterTimes[{2}]", stage.m_stageIndex, stage.m_star, stage.m_dailyEnteredTimes);
                        UnityUtility.CTrace.Singleton.trace(log);
                        textBoxShow.Text += log;
                        textBoxShow.Text += "\r\n";
                    }
                }
                );
            }
            catch (System.Exception)
            {
                MessageBox.Show("输入数据有误！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void buttonReqFinishStage_Click(object sender, EventArgs e)
        {
            try
            {
                List<UInt32> clearRandomMonster = new List<UInt32>();
                clearRandomMonster.Add(1);
                clearRandomMonster.Add(2);
                clearRandomMonster.Add(3);
                UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqStageResultReport(true, 3, 60, clearRandomMonster, delegate(UnityGMClient.ESendStageResultReportResult result)
                {
                    textBoxShow.Text += "================================================\r\n";
                    //string strResult = string.Format("reqFinishStage ack: result:[{0}] exp:[{1}] gold[{2}]\r\n", result, exp, gold);
                    string strResult = string.Format("reqFinishStage ack: result:[{0}] \r\n", result);
                    textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                    UnityUtility.CTrace.Singleton.trace(strResult);
                }
                );
            }
            catch (System.Exception)
            {
                MessageBox.Show("输入数据有误！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void textBoxReqInstanceInfoID_TextChanged(object sender, EventArgs e)
        {
            textBoxReqInstanceInfoID = sender as TextBox;
        }

        private void textBoxClearInstanceID_TextChanged(object sender, EventArgs e)
        {
            textBoxClearInstanceID = sender as TextBox;
        }

        private void textBoxClearStageIndex_TextChanged(object sender, EventArgs e)
        {
            textBoxClearStageIndex = sender as TextBox;
        }
        private void textBoxClearCount_TextChanged(object sender, EventArgs e)
        {
            textBoxBreakDownItem = sender as TextBox;
        }

        private void buttonClearStage_Click(object sender, EventArgs e)
        {
            try
            {
                UInt32 instanceTPID = UInt32.Parse(textBoxClearInstanceID.Text);
                UInt16 stageIndex = UInt16.Parse(textBoxClearStageIndex.Text);
                bool breakDownItem = UInt16.Parse(textBoxBreakDownItem.Text) != 0;
                UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqClearStage(instanceTPID, stageIndex, breakDownItem, delegate(UnityGMClient.EClearStageResult result, 
                                                                                        UnityGMClient.CStagePrize stagePrize)
                {
                    textBoxShow.Text += "================================================\r\n";
                    string strResult = string.Format("clear stage ack result[{0}]", result);
                    textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                    string prize = string.Format("exp = [{0}] gold = [{1}]", stagePrize.m_exp, stagePrize.m_gold);
                    textBoxShow.Text += prize;
                    textBoxShow.Text += "\r\n";
                    string itemCount = string.Format("prize item count[{0}]", stagePrize.m_listPrizeItem.Count);
                    textBoxShow.Text += itemCount;
                    textBoxShow.Text += "\r\n";
                    foreach (UnityGMClient.CPrizeItem item in stagePrize.m_listPrizeItem)
                    {
                        string log = string.Format("itemid[{0}] item count:[{1}]", item.m_ItemTPID, item.m_ItemCount);
                        textBoxShow.Text += log;
                        textBoxShow.Text += "\r\n";
                    }
                }
                );
            }
            catch (System.Exception)
            {

            }
        }

        private void buttonInstanceStarPrize_Click(object sender, EventArgs e)
        {
            try
            {
                UInt32 instanceTPID = UInt32.Parse(textBoxGetStarPrizeInstanceTPID.Text);
                UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqGetInstanceStarPrize(instanceTPID, delegate(UnityGMClient.EGetInstanceStarPrizeResult result, List<UnityGMClient.CPrizeItem> listInstancePrizeItem)
                {
                    textBoxShow.Text += "================================================\r\n";
                    string strResult = string.Format("get instance star prize ack result[{0}, Prize count [{1}]]", result, listInstancePrizeItem.Count);
                    textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                    foreach (UnityGMClient.CPrizeItem item in listInstancePrizeItem)
                    {
                        string log = string.Format("itemid[{0}] item count:[{1}]", item.m_ItemTPID, item.m_ItemCount);
                        textBoxShow.Text += log;
                        textBoxShow.Text += "\r\n";
                    }
                }
                );
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString(), "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void buttonGetInstancePrizePregress_Click(object sender, EventArgs e)
        {
            try
            {
                UInt32 instanceTPID = UInt32.Parse(textBoxInstanceStarPrizeProgress.Text);
                UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqGetIntanceStarPrizeProgress(instanceTPID, delegate(UInt32 instanceID, UInt16 star)
                {
                    textBoxShow.Text += "================================================\r\n";
                    string strResult = string.Format("get instance prize progress: instance[{0}], stageIndex:[{1}]", instanceID, star);
                    textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                }
                );
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString(), "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void textBoxGetStarPrizeInstanceTPID_TextChanged(object sender, EventArgs e)
        {
            textBoxGetStarPrizeInstanceTPID = sender as TextBox;
        }

        private void textBoxInstanceStarPrizeProgress_TextChanged(object sender, EventArgs e)
        {
            textBoxInstanceStarPrizeProgress = sender as TextBox;
        }

        private void textBoxBackToCityID_TextChanged(object sender, EventArgs e)
        {
            textBoxBackToCityID = sender as TextBox;
        }

        private void buttonBackToCity_Click(object sender, EventArgs e)
        {
            try
            {
                UInt32 cityID = UInt32.Parse(textBoxBackToCityID.Text);
                UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqEnterScene(cityID, delegate(UnityGMClient.EEnterSceneResult result, UInt32 currentSceneID, List<UnityGMClient.CSceneRoleInfo> listSceneRoles)
                {
                    textBoxShow.Text += "================================================\r\n";
                    string strResult = string.Format("返回主城结果:{0}] 主城ID[{1}]", result, currentSceneID);
                    textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                }
                );
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString(), "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void textBoxContinuousStageIndex_TextChanged(object sender, EventArgs e)
        {
            textBoxContinuousStageIndex = sender as TextBox;
        }

        private void textBoxGetContinuousInstanceTPID_TextChanged(object sender, EventArgs e)
        {
            textBoxGetContinuousInstanceTPID = sender as TextBox;
        }

        private void buttonGetContinuousInstanceData_Click(object sender, EventArgs e)
        {
            try
            {
                UInt32 instanceTPID = UInt32.Parse(textBoxGetContinuousInstanceTPID.Text);
                UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqGetContinuousInstanceData(instanceTPID, delegate(UnityGMClient.EGetContinuousInstanceDataResult result, UInt32 dailyFreeRollFastClearStageCount, UInt32 retInstanceTPID, UInt32 stageIndex)
                {
                    textBoxShow.Text += "================================================\r\n";
                    string strResult = string.Format("获取连续闯关信息结果:[{0}] 副本ID[{1}] 关卡序号[{2}] 每日免费掷筛子次数[{3}]", result, retInstanceTPID, stageIndex, dailyFreeRollFastClearStageCount);
                    textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                }
                );
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString(), "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void buttonEnterContinuousStage_Click(object sender, EventArgs e)
        {
            try
            {
                UInt32 instanceTPID = UInt32.Parse(textBoxContinuousInstanceTPID.Text);
                UInt32 stageIndex = UInt32.Parse(textBoxContinuousStageIndex.Text);
                UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqEnterContinuousStage(instanceTPID, stageIndex, delegate(UnityGMClient.EEnterSceneResult result)
                {
                    textBoxShow.Text += "================================================\r\n";
                    string strResult = string.Format("进入连续闯关关卡结果:[{0}]", result);
                    textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                }
                );
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString(), "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }
        private void textBoxReportConStageResultIsWin_TextChanged(object sender, EventArgs e)
        {
            textBoxReportConStageResultIsWin = sender as TextBox;
        }

        private void textBoxReportConStageResultScore_TextChanged(object sender, EventArgs e)
        {
            textBoxReportConStageResultScore = sender as TextBox;
        }

        private void buttonReportConStageResult_Click(object sender, EventArgs e)
        {
            try
            {
                bool isWin = UInt32.Parse(textBoxReportConStageResultIsWin.Text) > 0;
                UInt32 score = UInt32.Parse(textBoxReportConStageResultScore.Text);
                UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqReportContinuousStageResult(isWin, score, delegate(UnityGMClient.EReportContinuousStageResultResult result, UInt32 lastScore, UnityGMClient.CStagePrize stagePrize)
                {
                    textBoxShow.Text += "================================================\r\n";
                    string strResult = string.Format("汇报连续闯关关卡结果: result:[{0}] exp:[{1}] gold[{2}], lastScore[{3}]\r\n", result, stagePrize.m_exp, stagePrize.m_gold, lastScore);
                    textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                    foreach (UnityGMClient.CPrizeItem item in stagePrize.m_listPrizeItem)
                    {
                        string log = string.Format("itemid[{0}], item count:[{1}]", item.m_ItemTPID, item.m_ItemCount);
                        textBoxShow.Text += log;
                        textBoxShow.Text += "\r\n";
                    }
                }
                );
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString(), "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void textBoxRollFastClearStageInstanceTPID_TextChanged(object sender, EventArgs e)
        {
            textBoxRollFastClearStageInstanceTPID = sender as TextBox;
        }

        private void buttonRollFastClearContinuousStage_Click(object sender, EventArgs e)
        {
            try
            {
                UInt32 instanceTPID = UInt32.Parse(textBoxRollFastClearStageInstanceTPID.Text);
                UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqRollFastClearContinuousStageCount(instanceTPID, delegate(UnityGMClient.ERollFastClearContinuousStageNum result, UInt32 dailyFreeRollFastClearStageCount, UInt32 rollNum, UInt32 curStageIndex, List<UnityGMClient.CStagePrize> listStagePrize)
                {
                    textBoxShow.Text += "================================================\r\n";
                    string strResult = string.Format("连续闯关掷筛子结果:[{0}] 随机数[{1}] 通关数[{2}], 奖励物品数量[{3}] 每日免费掷筛子次数[{4}]", result, rollNum, curStageIndex, listStagePrize.Count, dailyFreeRollFastClearStageCount);
                    textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                }
                );
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString(), "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }

        }

        private void textBoxContinuousInstanceTPID_TextChanged(object sender, EventArgs e)
        {
            textBoxContinuousInstanceTPID = sender as TextBox;
        }

        private void textBoxResetContinuousInstanceTPID_TextChanged(object sender, EventArgs e)
        {
            textBoxResetContinuousInstanceTPID = sender as TextBox;
        }

        private void buttonResetContinuousInstance_Click(object sender, EventArgs e)
        {
            try
            {
                UInt32 instanceTPID = UInt32.Parse(textBoxResetContinuousInstanceTPID.Text);
                UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqResetContinuousInstance(instanceTPID, delegate(UnityGMClient.EResetContinuousInstanceResult result, UInt32 ackInstanceTPID)
                {
                    textBoxShow.Text += "================================================\r\n";
                    string strResult = string.Format("充值连续闯关掷筛子结果:[{0}] 副本TPID[{1}]", result, ackInstanceTPID);
                    textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                }
                );
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString(), "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void buttonDetermineItem_Click(object sender, EventArgs e)
        {
            List<UInt32> receiveItems = new List<UInt32>();
            UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqDeterminePrizeItem(receiveItems, delegate(UnityGMClient.EDetermineStagePrizeItemResult result)
            {
                textBoxShow.Text += "================================================\r\n";
                string strResult = string.Format("物品鉴定结果:[{0}]", result);
                textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
            }
            );
        }

        private void textBoxPara1_TextChanged(object sender, EventArgs e)
        {
            try
            {
                m_para1 = UInt32.Parse(textBoxPara1.Text);
            }
            catch (System.Exception ex)
            {
                //MessageBox.Show("输入数据有误！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                MessageBox.Show(ex.ToString(), "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void textBoxPara2_TextChanged(object sender, EventArgs e)
        {
            try
            {
                m_para2 = UInt32.Parse(textBoxPara2.Text);
            }
            catch (System.Exception ex)
            {
                //MessageBox.Show("输入数据有误！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                MessageBox.Show(ex.ToString(), "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void textBoxPara3_TextChanged(object sender, EventArgs e)
        {
            try
            {
                m_para3 = UInt32.Parse(textBoxPara3.Text);
            }
            catch (System.Exception ex)
            {
                //MessageBox.Show("输入数据有误！ ", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                MessageBox.Show(ex.ToString(), "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void buttonEnterRandomStage_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqEnterRandomStage(m_para1, delegate(UnityGMClient.EEnterSceneResult result, UnityGMClient.CStageMonster stageMonster) 
            {
                textBoxShow.Text += "================================================\r\n";
                string strResult = string.Format("进入随机关卡:[{0}]", result);
                textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                foreach (UnityGMClient.CStageUnitMonster unit in stageMonster.m_stageUnitMonster) {
                    foreach (UnityGMClient.CMonsterBatch batch in unit.m_monsterBatches) {
                        foreach (UnityGMClient.CMonster monster in batch.m_randomMonster) {
                            string strMonster = string.Format("随机掉落怪:index[{0}] type[{1}]\r\n", monster.m_index, monster.m_type);
                            textBoxShow.Text += strMonster;
                            foreach (UnityGMClient.CPrizeItem prizeItem in monster.m_listDropItems) {
                                string strPrizeItem = string.Format("物品ID[{0}] 物品数量[{1}]\r\n", prizeItem.m_ItemTPID, prizeItem.m_ItemCount);
                            }
                        }
                        foreach (UnityGMClient.CMonster monster in batch.m_certainlyMonster) {
                            string strMonster = string.Format("随机掉落怪:index[{0}] type[{1}]\r\n", monster.m_index, monster.m_type);
                            textBoxShow.Text += strMonster;
                            foreach (UnityGMClient.CPrizeItem prizeItem in monster.m_listDropItems) {
                                string strPrizeItem = string.Format("物品ID[{0}] 物品数量[{1}]\r\n", prizeItem.m_ItemTPID, prizeItem.m_ItemCount);
                                textBoxShow.Text += strPrizeItem;
                            }
                        }
                        if (batch.m_boss != null) {
                            UnityGMClient.CMonster monster = batch.m_boss;
                            string strMonster = string.Format("随机掉落怪:index[{0}] type[{1}]\r\n", monster.m_index, monster.m_type);
                            textBoxShow.Text += strMonster;
                            foreach (UnityGMClient.CPrizeItem prizeItem in monster.m_listDropItems) {
                                string strPrizeItem = string.Format("物品ID[{0}] 物品数量[{1}]\r\n", prizeItem.m_ItemTPID, prizeItem.m_ItemCount);
                                textBoxShow.Text += strPrizeItem;
                            }
                        }
                    }
                }
            });
        }

        private void buttonReportRandomStageResult_Click(object sender, EventArgs e)
        {
            bool isWin = m_para1 > 0;
            UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqReportRandomStageResult(isWin, delegate(UnityGMClient.ESendRandomStageReportResult result)
            {
                textBoxShow.Text += "================================================\r\n";
                string strResult = string.Format("汇报随机关卡结果:[{0}]", result);
                textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
            }
            );
        }

        private void buttonRevive_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqRoleRevive(delegate(UnityGMClient.ESceneRoleReviveResult result)
            {
                textBoxShow.Text += "================================================\r\n";
                string strResult = string.Format("关卡复活结果:[{0}]", result);
                textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
            });
        }

        private void buttonGetGreedLandInfo_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqGetGreedLandInfo(delegate(UnityGMClient.EGetGreedLandInfoResult result, UnityGMClient.CGreedLandInfo greedLandInfo)
            {
                textBoxShow.Text += "================================================\r\n";
                string strResult = string.Format("获取贪婪之地结果:[{0}]", result);
                textBoxShow.Text = textBoxShow.Text + strResult + "\r\n";
                string strInfo = string.Format("当前门票[{0}/{1}], 距离下次更新所需时间[{2}]", greedLandInfo.m_ticketsCount, greedLandInfo.m_maxTicketCount, 
                    greedLandInfo.m_nextUpdateTimeRemaining);
                textBoxShow.Text = textBoxShow.Text + strInfo + "\r\n";
            });
        }

        private void buttonRestoreStageTickets_Click(object sender, EventArgs e)
        {
            UnityGMClient.CClientCore.Singleton.SendMsgSceneSystemGC2GMReqRestoreStageTickets(m_para1, m_para2, delegate(UnityGMClient.ERestoreStageTicketsResult result, UInt32 instanceTPID, 
                UInt32 stageIndex, UInt32 ticketCount, UInt32 nextRestoreRequireDiamond) {
                string strText = string.Format("恢复副本关卡次数结果instance[{0}] stage[{1} result[{2}] ticketsCount[{3}]]", 
                    instanceTPID, stageIndex, result, ticketCount);
                textBoxShow.Text = textBoxShow.Text + strText + "\r\n";
            });
        }











    }
}
