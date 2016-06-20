namespace SimulateClient
{
    partial class FormInstance
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.textBoxShow = new System.Windows.Forms.TextBox();
            this.timerWait = new System.Windows.Forms.Timer(this.components);
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.ExitInstanceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ReviveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.buttonEnterStage = new System.Windows.Forms.Button();
            this.textBoxInstanceID = new System.Windows.Forms.TextBox();
            this.textBoxStageIndex = new System.Windows.Forms.TextBox();
            this.buttonGetStoryInstanceProgress = new System.Windows.Forms.Button();
            this.buttonReqGetInstanceData = new System.Windows.Forms.Button();
            this.textBoxReqInstanceInfoID = new System.Windows.Forms.TextBox();
            this.buttonReqFinishStage = new System.Windows.Forms.Button();
            this.buttonClearStage = new System.Windows.Forms.Button();
            this.textBoxClearInstanceID = new System.Windows.Forms.TextBox();
            this.textBoxClearStageIndex = new System.Windows.Forms.TextBox();
            this.textBoxBreakDownItem = new System.Windows.Forms.TextBox();
            this.buttonInstanceStarPrize = new System.Windows.Forms.Button();
            this.textBoxGetStarPrizeInstanceTPID = new System.Windows.Forms.TextBox();
            this.buttonGetInstancePrizePregress = new System.Windows.Forms.Button();
            this.textBoxInstanceStarPrizeProgress = new System.Windows.Forms.TextBox();
            this.buttonBackToCity = new System.Windows.Forms.Button();
            this.textBoxBackToCityID = new System.Windows.Forms.TextBox();
            this.buttonEnterContinuousStage = new System.Windows.Forms.Button();
            this.textBoxContinuousStageIndex = new System.Windows.Forms.TextBox();
            this.buttonRollFastClearContinuousStage = new System.Windows.Forms.Button();
            this.textBoxContinuousInstanceTPID = new System.Windows.Forms.TextBox();
            this.buttonGetContinuousInstanceData = new System.Windows.Forms.Button();
            this.textBoxGetContinuousInstanceTPID = new System.Windows.Forms.TextBox();
            this.buttonReportConStageResult = new System.Windows.Forms.Button();
            this.textBoxReportConStageResultIsWin = new System.Windows.Forms.TextBox();
            this.textBoxReportConStageResultScore = new System.Windows.Forms.TextBox();
            this.textBoxRollFastClearStageInstanceTPID = new System.Windows.Forms.TextBox();
            this.buttonResetContinuousInstance = new System.Windows.Forms.Button();
            this.textBoxResetContinuousInstanceTPID = new System.Windows.Forms.TextBox();
            this.buttonDetermineItem = new System.Windows.Forms.Button();
            this.buttonEnterRandomStage = new System.Windows.Forms.Button();
            this.textBoxPara1 = new System.Windows.Forms.TextBox();
            this.textBoxPara2 = new System.Windows.Forms.TextBox();
            this.textBoxPara3 = new System.Windows.Forms.TextBox();
            this.buttonReportRandomStageResult = new System.Windows.Forms.Button();
            this.buttonRevive = new System.Windows.Forms.Button();
            this.buttonGetGreedLandInfo = new System.Windows.Forms.Button();
            this.buttonRestoreStageTickets = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // textBoxShow
            // 
            this.textBoxShow.Location = new System.Drawing.Point(12, 40);
            this.textBoxShow.Multiline = true;
            this.textBoxShow.Name = "textBoxShow";
            this.textBoxShow.Size = new System.Drawing.Size(319, 267);
            this.textBoxShow.TabIndex = 1;
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(708, 25);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ExitInstanceToolStripMenuItem,
            this.ReviveToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(44, 21);
            this.toolStripMenuItem1.Text = "操作";
            // 
            // ExitInstanceToolStripMenuItem
            // 
            this.ExitInstanceToolStripMenuItem.Name = "ExitInstanceToolStripMenuItem";
            this.ExitInstanceToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.ExitInstanceToolStripMenuItem.Text = "退出";
            this.ExitInstanceToolStripMenuItem.Click += new System.EventHandler(this.ExitInstanceToolStripMenuItem_Click);
            // 
            // ReviveToolStripMenuItem
            // 
            this.ReviveToolStripMenuItem.Name = "ReviveToolStripMenuItem";
            this.ReviveToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.ReviveToolStripMenuItem.Text = "复活";
            this.ReviveToolStripMenuItem.Click += new System.EventHandler(this.ReviveToolStripMenuItem_Click);
            // 
            // buttonEnterStage
            // 
            this.buttonEnterStage.Location = new System.Drawing.Point(337, 125);
            this.buttonEnterStage.Name = "buttonEnterStage";
            this.buttonEnterStage.Size = new System.Drawing.Size(89, 23);
            this.buttonEnterStage.TabIndex = 3;
            this.buttonEnterStage.Text = "进入关卡";
            this.buttonEnterStage.UseVisualStyleBackColor = true;
            this.buttonEnterStage.Click += new System.EventHandler(this.buttonEnterStage_Click);
            // 
            // textBoxInstanceID
            // 
            this.textBoxInstanceID.Location = new System.Drawing.Point(438, 127);
            this.textBoxInstanceID.Name = "textBoxInstanceID";
            this.textBoxInstanceID.Size = new System.Drawing.Size(54, 21);
            this.textBoxInstanceID.TabIndex = 4;
            this.textBoxInstanceID.TextChanged += new System.EventHandler(this.textBoxInstanceID_TextChanged);
            // 
            // textBoxStageIndex
            // 
            this.textBoxStageIndex.Location = new System.Drawing.Point(496, 127);
            this.textBoxStageIndex.Name = "textBoxStageIndex";
            this.textBoxStageIndex.Size = new System.Drawing.Size(55, 21);
            this.textBoxStageIndex.TabIndex = 5;
            this.textBoxStageIndex.TextChanged += new System.EventHandler(this.textBoxStageIndex_TextChanged);
            // 
            // buttonGetStoryInstanceProgress
            // 
            this.buttonGetStoryInstanceProgress.Location = new System.Drawing.Point(338, 94);
            this.buttonGetStoryInstanceProgress.Name = "buttonGetStoryInstanceProgress";
            this.buttonGetStoryInstanceProgress.Size = new System.Drawing.Size(88, 23);
            this.buttonGetStoryInstanceProgress.TabIndex = 6;
            this.buttonGetStoryInstanceProgress.Text = "主副本进度";
            this.buttonGetStoryInstanceProgress.UseVisualStyleBackColor = true;
            this.buttonGetStoryInstanceProgress.Click += new System.EventHandler(this.buttonGetStoryInstanceProgress_Click);
            // 
            // buttonReqGetInstanceData
            // 
            this.buttonReqGetInstanceData.Location = new System.Drawing.Point(338, 224);
            this.buttonReqGetInstanceData.Name = "buttonReqGetInstanceData";
            this.buttonReqGetInstanceData.Size = new System.Drawing.Size(88, 23);
            this.buttonReqGetInstanceData.TabIndex = 7;
            this.buttonReqGetInstanceData.Text = "副本详情";
            this.buttonReqGetInstanceData.UseVisualStyleBackColor = true;
            this.buttonReqGetInstanceData.Click += new System.EventHandler(this.buttonReqGetInstanceData_Click);
            // 
            // textBoxReqInstanceInfoID
            // 
            this.textBoxReqInstanceInfoID.Location = new System.Drawing.Point(438, 224);
            this.textBoxReqInstanceInfoID.Name = "textBoxReqInstanceInfoID";
            this.textBoxReqInstanceInfoID.Size = new System.Drawing.Size(52, 21);
            this.textBoxReqInstanceInfoID.TabIndex = 8;
            this.textBoxReqInstanceInfoID.TextChanged += new System.EventHandler(this.textBoxReqInstanceInfoID_TextChanged);
            // 
            // buttonReqFinishStage
            // 
            this.buttonReqFinishStage.Location = new System.Drawing.Point(338, 157);
            this.buttonReqFinishStage.Name = "buttonReqFinishStage";
            this.buttonReqFinishStage.Size = new System.Drawing.Size(88, 23);
            this.buttonReqFinishStage.TabIndex = 9;
            this.buttonReqFinishStage.Text = "关卡结束";
            this.buttonReqFinishStage.UseVisualStyleBackColor = true;
            this.buttonReqFinishStage.Click += new System.EventHandler(this.buttonReqFinishStage_Click);
            // 
            // buttonClearStage
            // 
            this.buttonClearStage.Location = new System.Drawing.Point(338, 254);
            this.buttonClearStage.Name = "buttonClearStage";
            this.buttonClearStage.Size = new System.Drawing.Size(88, 23);
            this.buttonClearStage.TabIndex = 10;
            this.buttonClearStage.Text = "扫荡";
            this.buttonClearStage.UseVisualStyleBackColor = true;
            this.buttonClearStage.Click += new System.EventHandler(this.buttonClearStage_Click);
            // 
            // textBoxClearInstanceID
            // 
            this.textBoxClearInstanceID.Location = new System.Drawing.Point(438, 254);
            this.textBoxClearInstanceID.Name = "textBoxClearInstanceID";
            this.textBoxClearInstanceID.Size = new System.Drawing.Size(52, 21);
            this.textBoxClearInstanceID.TabIndex = 11;
            this.textBoxClearInstanceID.TextChanged += new System.EventHandler(this.textBoxClearInstanceID_TextChanged);
            // 
            // textBoxClearStageIndex
            // 
            this.textBoxClearStageIndex.Location = new System.Drawing.Point(496, 254);
            this.textBoxClearStageIndex.Name = "textBoxClearStageIndex";
            this.textBoxClearStageIndex.Size = new System.Drawing.Size(56, 21);
            this.textBoxClearStageIndex.TabIndex = 12;
            this.textBoxClearStageIndex.TextChanged += new System.EventHandler(this.textBoxClearStageIndex_TextChanged);
            // 
            // textBoxBreakDownItem
            // 
            this.textBoxBreakDownItem.Location = new System.Drawing.Point(566, 254);
            this.textBoxBreakDownItem.Name = "textBoxBreakDownItem";
            this.textBoxBreakDownItem.Size = new System.Drawing.Size(58, 21);
            this.textBoxBreakDownItem.TabIndex = 13;
            this.textBoxBreakDownItem.TextChanged += new System.EventHandler(this.textBoxClearCount_TextChanged);
            // 
            // buttonInstanceStarPrize
            // 
            this.buttonInstanceStarPrize.Location = new System.Drawing.Point(337, 313);
            this.buttonInstanceStarPrize.Name = "buttonInstanceStarPrize";
            this.buttonInstanceStarPrize.Size = new System.Drawing.Size(89, 23);
            this.buttonInstanceStarPrize.TabIndex = 14;
            this.buttonInstanceStarPrize.Text = "副本奖励";
            this.buttonInstanceStarPrize.UseVisualStyleBackColor = true;
            this.buttonInstanceStarPrize.Click += new System.EventHandler(this.buttonInstanceStarPrize_Click);
            // 
            // textBoxGetStarPrizeInstanceTPID
            // 
            this.textBoxGetStarPrizeInstanceTPID.Location = new System.Drawing.Point(438, 315);
            this.textBoxGetStarPrizeInstanceTPID.Name = "textBoxGetStarPrizeInstanceTPID";
            this.textBoxGetStarPrizeInstanceTPID.Size = new System.Drawing.Size(54, 21);
            this.textBoxGetStarPrizeInstanceTPID.TabIndex = 15;
            this.textBoxGetStarPrizeInstanceTPID.TextChanged += new System.EventHandler(this.textBoxGetStarPrizeInstanceTPID_TextChanged);
            // 
            // buttonGetInstancePrizePregress
            // 
            this.buttonGetInstancePrizePregress.Location = new System.Drawing.Point(338, 284);
            this.buttonGetInstancePrizePregress.Name = "buttonGetInstancePrizePregress";
            this.buttonGetInstancePrizePregress.Size = new System.Drawing.Size(88, 23);
            this.buttonGetInstancePrizePregress.TabIndex = 16;
            this.buttonGetInstancePrizePregress.Text = "副本奖励进度";
            this.buttonGetInstancePrizePregress.UseVisualStyleBackColor = true;
            this.buttonGetInstancePrizePregress.Click += new System.EventHandler(this.buttonGetInstancePrizePregress_Click);
            // 
            // textBoxInstanceStarPrizeProgress
            // 
            this.textBoxInstanceStarPrizeProgress.Location = new System.Drawing.Point(438, 284);
            this.textBoxInstanceStarPrizeProgress.Name = "textBoxInstanceStarPrizeProgress";
            this.textBoxInstanceStarPrizeProgress.Size = new System.Drawing.Size(54, 21);
            this.textBoxInstanceStarPrizeProgress.TabIndex = 17;
            this.textBoxInstanceStarPrizeProgress.TextChanged += new System.EventHandler(this.textBoxInstanceStarPrizeProgress_TextChanged);
            // 
            // buttonBackToCity
            // 
            this.buttonBackToCity.Location = new System.Drawing.Point(338, 67);
            this.buttonBackToCity.Name = "buttonBackToCity";
            this.buttonBackToCity.Size = new System.Drawing.Size(88, 23);
            this.buttonBackToCity.TabIndex = 18;
            this.buttonBackToCity.Text = "返回主城";
            this.buttonBackToCity.UseVisualStyleBackColor = true;
            this.buttonBackToCity.Click += new System.EventHandler(this.buttonBackToCity_Click);
            // 
            // textBoxBackToCityID
            // 
            this.textBoxBackToCityID.Location = new System.Drawing.Point(433, 67);
            this.textBoxBackToCityID.Name = "textBoxBackToCityID";
            this.textBoxBackToCityID.Size = new System.Drawing.Size(100, 21);
            this.textBoxBackToCityID.TabIndex = 19;
            this.textBoxBackToCityID.TextChanged += new System.EventHandler(this.textBoxBackToCityID_TextChanged);
            // 
            // buttonEnterContinuousStage
            // 
            this.buttonEnterContinuousStage.Location = new System.Drawing.Point(337, 370);
            this.buttonEnterContinuousStage.Name = "buttonEnterContinuousStage";
            this.buttonEnterContinuousStage.Size = new System.Drawing.Size(89, 23);
            this.buttonEnterContinuousStage.TabIndex = 20;
            this.buttonEnterContinuousStage.Text = "连续闯关";
            this.buttonEnterContinuousStage.UseVisualStyleBackColor = true;
            this.buttonEnterContinuousStage.Click += new System.EventHandler(this.buttonEnterContinuousStage_Click);
            // 
            // textBoxContinuousStageIndex
            // 
            this.textBoxContinuousStageIndex.Location = new System.Drawing.Point(496, 372);
            this.textBoxContinuousStageIndex.Name = "textBoxContinuousStageIndex";
            this.textBoxContinuousStageIndex.Size = new System.Drawing.Size(56, 21);
            this.textBoxContinuousStageIndex.TabIndex = 21;
            this.textBoxContinuousStageIndex.TextChanged += new System.EventHandler(this.textBoxContinuousStageIndex_TextChanged);
            // 
            // buttonRollFastClearContinuousStage
            // 
            this.buttonRollFastClearContinuousStage.Location = new System.Drawing.Point(338, 429);
            this.buttonRollFastClearContinuousStage.Name = "buttonRollFastClearContinuousStage";
            this.buttonRollFastClearContinuousStage.Size = new System.Drawing.Size(88, 23);
            this.buttonRollFastClearContinuousStage.TabIndex = 22;
            this.buttonRollFastClearContinuousStage.Text = "摇色子";
            this.buttonRollFastClearContinuousStage.UseVisualStyleBackColor = true;
            this.buttonRollFastClearContinuousStage.Click += new System.EventHandler(this.buttonRollFastClearContinuousStage_Click);
            // 
            // textBoxContinuousInstanceTPID
            // 
            this.textBoxContinuousInstanceTPID.Location = new System.Drawing.Point(438, 371);
            this.textBoxContinuousInstanceTPID.Name = "textBoxContinuousInstanceTPID";
            this.textBoxContinuousInstanceTPID.Size = new System.Drawing.Size(54, 21);
            this.textBoxContinuousInstanceTPID.TabIndex = 23;
            this.textBoxContinuousInstanceTPID.TextChanged += new System.EventHandler(this.textBoxContinuousInstanceTPID_TextChanged);
            // 
            // buttonGetContinuousInstanceData
            // 
            this.buttonGetContinuousInstanceData.Location = new System.Drawing.Point(338, 341);
            this.buttonGetContinuousInstanceData.Name = "buttonGetContinuousInstanceData";
            this.buttonGetContinuousInstanceData.Size = new System.Drawing.Size(88, 23);
            this.buttonGetContinuousInstanceData.TabIndex = 24;
            this.buttonGetContinuousInstanceData.Text = "连续闯关信息";
            this.buttonGetContinuousInstanceData.UseVisualStyleBackColor = true;
            this.buttonGetContinuousInstanceData.Click += new System.EventHandler(this.buttonGetContinuousInstanceData_Click);
            // 
            // textBoxGetContinuousInstanceTPID
            // 
            this.textBoxGetContinuousInstanceTPID.Location = new System.Drawing.Point(438, 341);
            this.textBoxGetContinuousInstanceTPID.Name = "textBoxGetContinuousInstanceTPID";
            this.textBoxGetContinuousInstanceTPID.Size = new System.Drawing.Size(52, 21);
            this.textBoxGetContinuousInstanceTPID.TabIndex = 25;
            this.textBoxGetContinuousInstanceTPID.TextChanged += new System.EventHandler(this.textBoxGetContinuousInstanceTPID_TextChanged);
            // 
            // buttonReportConStageResult
            // 
            this.buttonReportConStageResult.Location = new System.Drawing.Point(337, 400);
            this.buttonReportConStageResult.Name = "buttonReportConStageResult";
            this.buttonReportConStageResult.Size = new System.Drawing.Size(89, 23);
            this.buttonReportConStageResult.TabIndex = 26;
            this.buttonReportConStageResult.Text = "连续闯关战绩";
            this.buttonReportConStageResult.UseVisualStyleBackColor = true;
            this.buttonReportConStageResult.Click += new System.EventHandler(this.buttonReportConStageResult_Click);
            // 
            // textBoxReportConStageResultIsWin
            // 
            this.textBoxReportConStageResultIsWin.Location = new System.Drawing.Point(438, 401);
            this.textBoxReportConStageResultIsWin.Name = "textBoxReportConStageResultIsWin";
            this.textBoxReportConStageResultIsWin.Size = new System.Drawing.Size(54, 21);
            this.textBoxReportConStageResultIsWin.TabIndex = 27;
            this.textBoxReportConStageResultIsWin.TextChanged += new System.EventHandler(this.textBoxReportConStageResultIsWin_TextChanged);
            // 
            // textBoxReportConStageResultScore
            // 
            this.textBoxReportConStageResultScore.Location = new System.Drawing.Point(496, 400);
            this.textBoxReportConStageResultScore.Name = "textBoxReportConStageResultScore";
            this.textBoxReportConStageResultScore.Size = new System.Drawing.Size(56, 21);
            this.textBoxReportConStageResultScore.TabIndex = 28;
            this.textBoxReportConStageResultScore.TextChanged += new System.EventHandler(this.textBoxReportConStageResultScore_TextChanged);
            // 
            // textBoxRollFastClearStageInstanceTPID
            // 
            this.textBoxRollFastClearStageInstanceTPID.Location = new System.Drawing.Point(438, 429);
            this.textBoxRollFastClearStageInstanceTPID.Name = "textBoxRollFastClearStageInstanceTPID";
            this.textBoxRollFastClearStageInstanceTPID.Size = new System.Drawing.Size(52, 21);
            this.textBoxRollFastClearStageInstanceTPID.TabIndex = 29;
            this.textBoxRollFastClearStageInstanceTPID.TextChanged += new System.EventHandler(this.textBoxRollFastClearStageInstanceTPID_TextChanged);
            // 
            // buttonResetContinuousInstance
            // 
            this.buttonResetContinuousInstance.Location = new System.Drawing.Point(337, 459);
            this.buttonResetContinuousInstance.Name = "buttonResetContinuousInstance";
            this.buttonResetContinuousInstance.Size = new System.Drawing.Size(89, 23);
            this.buttonResetContinuousInstance.TabIndex = 30;
            this.buttonResetContinuousInstance.Text = "重置连续关卡";
            this.buttonResetContinuousInstance.UseVisualStyleBackColor = true;
            this.buttonResetContinuousInstance.Click += new System.EventHandler(this.buttonResetContinuousInstance_Click);
            // 
            // textBoxResetContinuousInstanceTPID
            // 
            this.textBoxResetContinuousInstanceTPID.Location = new System.Drawing.Point(438, 461);
            this.textBoxResetContinuousInstanceTPID.Name = "textBoxResetContinuousInstanceTPID";
            this.textBoxResetContinuousInstanceTPID.Size = new System.Drawing.Size(52, 21);
            this.textBoxResetContinuousInstanceTPID.TabIndex = 31;
            this.textBoxResetContinuousInstanceTPID.TextChanged += new System.EventHandler(this.textBoxResetContinuousInstanceTPID_TextChanged);
            // 
            // buttonDetermineItem
            // 
            this.buttonDetermineItem.Location = new System.Drawing.Point(338, 187);
            this.buttonDetermineItem.Name = "buttonDetermineItem";
            this.buttonDetermineItem.Size = new System.Drawing.Size(88, 23);
            this.buttonDetermineItem.TabIndex = 32;
            this.buttonDetermineItem.Text = "物品鉴定";
            this.buttonDetermineItem.UseVisualStyleBackColor = true;
            this.buttonDetermineItem.Click += new System.EventHandler(this.buttonDetermineItem_Click);
            // 
            // buttonEnterRandomStage
            // 
            this.buttonEnterRandomStage.Location = new System.Drawing.Point(338, 489);
            this.buttonEnterRandomStage.Name = "buttonEnterRandomStage";
            this.buttonEnterRandomStage.Size = new System.Drawing.Size(88, 23);
            this.buttonEnterRandomStage.TabIndex = 33;
            this.buttonEnterRandomStage.Text = "进入随机关卡";
            this.buttonEnterRandomStage.UseVisualStyleBackColor = true;
            this.buttonEnterRandomStage.Click += new System.EventHandler(this.buttonEnterRandomStage_Click);
            // 
            // textBoxPara1
            // 
            this.textBoxPara1.Location = new System.Drawing.Point(338, 29);
            this.textBoxPara1.Name = "textBoxPara1";
            this.textBoxPara1.Size = new System.Drawing.Size(100, 21);
            this.textBoxPara1.TabIndex = 34;
            this.textBoxPara1.TextChanged += new System.EventHandler(this.textBoxPara1_TextChanged);
            // 
            // textBoxPara2
            // 
            this.textBoxPara2.Location = new System.Drawing.Point(445, 29);
            this.textBoxPara2.Name = "textBoxPara2";
            this.textBoxPara2.Size = new System.Drawing.Size(100, 21);
            this.textBoxPara2.TabIndex = 35;
            this.textBoxPara2.TextChanged += new System.EventHandler(this.textBoxPara2_TextChanged);
            // 
            // textBoxPara3
            // 
            this.textBoxPara3.Location = new System.Drawing.Point(552, 29);
            this.textBoxPara3.Name = "textBoxPara3";
            this.textBoxPara3.Size = new System.Drawing.Size(100, 21);
            this.textBoxPara3.TabIndex = 36;
            this.textBoxPara3.TextChanged += new System.EventHandler(this.textBoxPara3_TextChanged);
            // 
            // buttonReportRandomStageResult
            // 
            this.buttonReportRandomStageResult.Location = new System.Drawing.Point(337, 519);
            this.buttonReportRandomStageResult.Name = "buttonReportRandomStageResult";
            this.buttonReportRandomStageResult.Size = new System.Drawing.Size(89, 23);
            this.buttonReportRandomStageResult.TabIndex = 37;
            this.buttonReportRandomStageResult.Text = "随机关卡结束";
            this.buttonReportRandomStageResult.UseVisualStyleBackColor = true;
            this.buttonReportRandomStageResult.Click += new System.EventHandler(this.buttonReportRandomStageResult_Click);
            // 
            // buttonRevive
            // 
            this.buttonRevive.Location = new System.Drawing.Point(337, 550);
            this.buttonRevive.Name = "buttonRevive";
            this.buttonRevive.Size = new System.Drawing.Size(88, 23);
            this.buttonRevive.TabIndex = 38;
            this.buttonRevive.Text = "复活";
            this.buttonRevive.UseVisualStyleBackColor = true;
            this.buttonRevive.Click += new System.EventHandler(this.buttonRevive_Click);
            // 
            // buttonGetGreedLandInfo
            // 
            this.buttonGetGreedLandInfo.Location = new System.Drawing.Point(337, 579);
            this.buttonGetGreedLandInfo.Name = "buttonGetGreedLandInfo";
            this.buttonGetGreedLandInfo.Size = new System.Drawing.Size(88, 23);
            this.buttonGetGreedLandInfo.TabIndex = 39;
            this.buttonGetGreedLandInfo.Text = "贪婪之地";
            this.buttonGetGreedLandInfo.UseVisualStyleBackColor = true;
            this.buttonGetGreedLandInfo.Click += new System.EventHandler(this.buttonGetGreedLandInfo_Click);
            // 
            // buttonRestoreStageTickets
            // 
            this.buttonRestoreStageTickets.Location = new System.Drawing.Point(338, 609);
            this.buttonRestoreStageTickets.Name = "buttonRestoreStageTickets";
            this.buttonRestoreStageTickets.Size = new System.Drawing.Size(87, 23);
            this.buttonRestoreStageTickets.TabIndex = 40;
            this.buttonRestoreStageTickets.Text = "恢复关卡次数";
            this.buttonRestoreStageTickets.UseVisualStyleBackColor = true;
            this.buttonRestoreStageTickets.Click += new System.EventHandler(this.buttonRestoreStageTickets_Click);
            // 
            // FormInstance
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(708, 672);
            this.Controls.Add(this.buttonRestoreStageTickets);
            this.Controls.Add(this.buttonGetGreedLandInfo);
            this.Controls.Add(this.buttonRevive);
            this.Controls.Add(this.buttonReportRandomStageResult);
            this.Controls.Add(this.textBoxPara3);
            this.Controls.Add(this.textBoxPara2);
            this.Controls.Add(this.textBoxPara1);
            this.Controls.Add(this.buttonEnterRandomStage);
            this.Controls.Add(this.buttonDetermineItem);
            this.Controls.Add(this.textBoxResetContinuousInstanceTPID);
            this.Controls.Add(this.buttonResetContinuousInstance);
            this.Controls.Add(this.textBoxRollFastClearStageInstanceTPID);
            this.Controls.Add(this.textBoxReportConStageResultScore);
            this.Controls.Add(this.textBoxReportConStageResultIsWin);
            this.Controls.Add(this.buttonReportConStageResult);
            this.Controls.Add(this.textBoxGetContinuousInstanceTPID);
            this.Controls.Add(this.buttonGetContinuousInstanceData);
            this.Controls.Add(this.textBoxContinuousInstanceTPID);
            this.Controls.Add(this.buttonRollFastClearContinuousStage);
            this.Controls.Add(this.textBoxContinuousStageIndex);
            this.Controls.Add(this.buttonEnterContinuousStage);
            this.Controls.Add(this.textBoxBackToCityID);
            this.Controls.Add(this.buttonBackToCity);
            this.Controls.Add(this.textBoxInstanceStarPrizeProgress);
            this.Controls.Add(this.buttonGetInstancePrizePregress);
            this.Controls.Add(this.textBoxGetStarPrizeInstanceTPID);
            this.Controls.Add(this.buttonInstanceStarPrize);
            this.Controls.Add(this.textBoxBreakDownItem);
            this.Controls.Add(this.textBoxClearStageIndex);
            this.Controls.Add(this.textBoxClearInstanceID);
            this.Controls.Add(this.buttonClearStage);
            this.Controls.Add(this.buttonReqFinishStage);
            this.Controls.Add(this.textBoxReqInstanceInfoID);
            this.Controls.Add(this.buttonReqGetInstanceData);
            this.Controls.Add(this.buttonGetStoryInstanceProgress);
            this.Controls.Add(this.textBoxStageIndex);
            this.Controls.Add(this.textBoxInstanceID);
            this.Controls.Add(this.buttonEnterStage);
            this.Controls.Add(this.textBoxShow);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "FormInstance";
            this.Text = "  ";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormCarbon_FormClosed);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxShow;
        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem ExitInstanceToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ReviveToolStripMenuItem;
        private System.Windows.Forms.Button buttonEnterStage;
        private System.Windows.Forms.TextBox textBoxInstanceID;
        private System.Windows.Forms.TextBox textBoxStageIndex;
        private System.Windows.Forms.Button buttonGetStoryInstanceProgress;
        private System.Windows.Forms.Button buttonReqGetInstanceData;
        private System.Windows.Forms.TextBox textBoxReqInstanceInfoID;
        private System.Windows.Forms.Button buttonReqFinishStage;
        private System.Windows.Forms.Button buttonClearStage;
        private System.Windows.Forms.TextBox textBoxClearInstanceID;
        private System.Windows.Forms.TextBox textBoxClearStageIndex;
        private System.Windows.Forms.TextBox textBoxBreakDownItem;
        private System.Windows.Forms.Button buttonInstanceStarPrize;
        private System.Windows.Forms.TextBox textBoxGetStarPrizeInstanceTPID;
        private System.Windows.Forms.Button buttonGetInstancePrizePregress;
        private System.Windows.Forms.TextBox textBoxInstanceStarPrizeProgress;
        private System.Windows.Forms.Button buttonBackToCity;
        private System.Windows.Forms.TextBox textBoxBackToCityID;
        private System.Windows.Forms.Button buttonEnterContinuousStage;
        private System.Windows.Forms.TextBox textBoxContinuousStageIndex;
        private System.Windows.Forms.Button buttonRollFastClearContinuousStage;
        private System.Windows.Forms.TextBox textBoxContinuousInstanceTPID;
        private System.Windows.Forms.Button buttonGetContinuousInstanceData;
        private System.Windows.Forms.TextBox textBoxGetContinuousInstanceTPID;
        private System.Windows.Forms.Button buttonReportConStageResult;
        private System.Windows.Forms.TextBox textBoxReportConStageResultIsWin;
        private System.Windows.Forms.TextBox textBoxReportConStageResultScore;
        private System.Windows.Forms.TextBox textBoxRollFastClearStageInstanceTPID;
        private System.Windows.Forms.Button buttonResetContinuousInstance;
        private System.Windows.Forms.TextBox textBoxResetContinuousInstanceTPID;
        private System.Windows.Forms.Button buttonDetermineItem;
        private System.Windows.Forms.Button buttonEnterRandomStage;
        private System.Windows.Forms.TextBox textBoxPara1;
        private System.Windows.Forms.TextBox textBoxPara2;
        private System.Windows.Forms.TextBox textBoxPara3;
        private System.Windows.Forms.Button buttonReportRandomStageResult;
        private System.Windows.Forms.Button buttonRevive;
        private System.Windows.Forms.Button buttonGetGreedLandInfo;
        private System.Windows.Forms.Button buttonRestoreStageTickets;
    }
}