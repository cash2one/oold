namespace SimulateClient
{
    partial class FormTask
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
            this.buttonExit = new System.Windows.Forms.Button();
            this.timerWait = new System.Windows.Forms.Timer(this.components);
            this.textBoxTips = new System.Windows.Forms.TextBox();
            this.buttonDailyTaskList = new System.Windows.Forms.Button();
            this.buttonGetPrize = new System.Windows.Forms.Button();
            this.textBoxPrizeTaskTPID = new System.Windows.Forms.TextBox();
            this.buttonGetMainTask = new System.Windows.Forms.Button();
            this.buttonGetMainTaskPrize = new System.Windows.Forms.Button();
            this.buttonUpdateMainTaskStage = new System.Windows.Forms.Button();
            this.textBoxPara2 = new System.Windows.Forms.TextBox();
            this.textBoxPara3 = new System.Windows.Forms.TextBox();
            this.textBoxPara1 = new System.Windows.Forms.TextBox();
            this.buttonGetPetTask = new System.Windows.Forms.Button();
            this.buttonRefreshPetTask = new System.Windows.Forms.Button();
            this.buttonUpdatePetTaskState = new System.Windows.Forms.Button();
            this.buttonGetPetTaskPrize = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonExit
            // 
            this.buttonExit.Location = new System.Drawing.Point(422, 506);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(75, 23);
            this.buttonExit.TabIndex = 0;
            this.buttonExit.Text = "退出";
            this.buttonExit.UseVisualStyleBackColor = true;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // textBoxTips
            // 
            this.textBoxTips.Location = new System.Drawing.Point(11, 368);
            this.textBoxTips.Multiline = true;
            this.textBoxTips.Name = "textBoxTips";
            this.textBoxTips.Size = new System.Drawing.Size(405, 161);
            this.textBoxTips.TabIndex = 1;
            // 
            // buttonDailyTaskList
            // 
            this.buttonDailyTaskList.Location = new System.Drawing.Point(12, 44);
            this.buttonDailyTaskList.Name = "buttonDailyTaskList";
            this.buttonDailyTaskList.Size = new System.Drawing.Size(87, 23);
            this.buttonDailyTaskList.TabIndex = 2;
            this.buttonDailyTaskList.Text = "日常任务列表";
            this.buttonDailyTaskList.UseVisualStyleBackColor = true;
            this.buttonDailyTaskList.Click += new System.EventHandler(this.buttonDailyTaskList_Click);
            // 
            // buttonGetPrize
            // 
            this.buttonGetPrize.Location = new System.Drawing.Point(12, 160);
            this.buttonGetPrize.Name = "buttonGetPrize";
            this.buttonGetPrize.Size = new System.Drawing.Size(87, 23);
            this.buttonGetPrize.TabIndex = 3;
            this.buttonGetPrize.Text = "获取日常奖励";
            this.buttonGetPrize.UseVisualStyleBackColor = true;
            this.buttonGetPrize.Click += new System.EventHandler(this.buttonGetPrize_Click);
            // 
            // textBoxPrizeTaskTPID
            // 
            this.textBoxPrizeTaskTPID.Location = new System.Drawing.Point(107, 160);
            this.textBoxPrizeTaskTPID.Name = "textBoxPrizeTaskTPID";
            this.textBoxPrizeTaskTPID.Size = new System.Drawing.Size(101, 21);
            this.textBoxPrizeTaskTPID.TabIndex = 4;
            this.textBoxPrizeTaskTPID.TextChanged += new System.EventHandler(this.textBoxPrizeTaskTPID_TextChanged);
            // 
            // buttonGetMainTask
            // 
            this.buttonGetMainTask.Location = new System.Drawing.Point(12, 73);
            this.buttonGetMainTask.Name = "buttonGetMainTask";
            this.buttonGetMainTask.Size = new System.Drawing.Size(87, 23);
            this.buttonGetMainTask.TabIndex = 5;
            this.buttonGetMainTask.Text = "主线任务";
            this.buttonGetMainTask.UseVisualStyleBackColor = true;
            this.buttonGetMainTask.Click += new System.EventHandler(this.buttonGetMainTask_Click);
            // 
            // buttonGetMainTaskPrize
            // 
            this.buttonGetMainTaskPrize.Location = new System.Drawing.Point(12, 102);
            this.buttonGetMainTaskPrize.Name = "buttonGetMainTaskPrize";
            this.buttonGetMainTaskPrize.Size = new System.Drawing.Size(87, 23);
            this.buttonGetMainTaskPrize.TabIndex = 6;
            this.buttonGetMainTaskPrize.Text = "获取主线奖励";
            this.buttonGetMainTaskPrize.UseVisualStyleBackColor = true;
            this.buttonGetMainTaskPrize.Click += new System.EventHandler(this.buttonGetMainTaskPrize_Click);
            // 
            // buttonUpdateMainTaskStage
            // 
            this.buttonUpdateMainTaskStage.Location = new System.Drawing.Point(12, 131);
            this.buttonUpdateMainTaskStage.Name = "buttonUpdateMainTaskStage";
            this.buttonUpdateMainTaskStage.Size = new System.Drawing.Size(87, 23);
            this.buttonUpdateMainTaskStage.TabIndex = 7;
            this.buttonUpdateMainTaskStage.Text = "更新任务状态";
            this.buttonUpdateMainTaskStage.UseVisualStyleBackColor = true;
            this.buttonUpdateMainTaskStage.Click += new System.EventHandler(this.buttonFinishMainTaskEvent_Click);
            // 
            // textBoxPara2
            // 
            this.textBoxPara2.Location = new System.Drawing.Point(87, 11);
            this.textBoxPara2.Name = "textBoxPara2";
            this.textBoxPara2.Size = new System.Drawing.Size(64, 21);
            this.textBoxPara2.TabIndex = 8;
            this.textBoxPara2.TextChanged += new System.EventHandler(this.textBoxMainTaskEventParam1_TextChanged);
            // 
            // textBoxPara3
            // 
            this.textBoxPara3.Location = new System.Drawing.Point(157, 11);
            this.textBoxPara3.Name = "textBoxPara3";
            this.textBoxPara3.Size = new System.Drawing.Size(64, 21);
            this.textBoxPara3.TabIndex = 9;
            this.textBoxPara3.TextChanged += new System.EventHandler(this.textBoxMainTaskEventParam2_TextChanged);
            // 
            // textBoxPara1
            // 
            this.textBoxPara1.Location = new System.Drawing.Point(16, 12);
            this.textBoxPara1.Name = "textBoxPara1";
            this.textBoxPara1.Size = new System.Drawing.Size(63, 21);
            this.textBoxPara1.TabIndex = 10;
            this.textBoxPara1.TextChanged += new System.EventHandler(this.textBoxMainTaskType_TextChanged);
            // 
            // buttonGetPetTask
            // 
            this.buttonGetPetTask.Location = new System.Drawing.Point(11, 190);
            this.buttonGetPetTask.Name = "buttonGetPetTask";
            this.buttonGetPetTask.Size = new System.Drawing.Size(87, 23);
            this.buttonGetPetTask.TabIndex = 11;
            this.buttonGetPetTask.Text = "获取伙伴任务";
            this.buttonGetPetTask.UseVisualStyleBackColor = true;
            this.buttonGetPetTask.Click += new System.EventHandler(this.buttonGetPetTask_Click);
            // 
            // buttonRefreshPetTask
            // 
            this.buttonRefreshPetTask.Location = new System.Drawing.Point(11, 219);
            this.buttonRefreshPetTask.Name = "buttonRefreshPetTask";
            this.buttonRefreshPetTask.Size = new System.Drawing.Size(87, 23);
            this.buttonRefreshPetTask.TabIndex = 12;
            this.buttonRefreshPetTask.Text = "刷新伙伴任务";
            this.buttonRefreshPetTask.UseVisualStyleBackColor = true;
            this.buttonRefreshPetTask.Click += new System.EventHandler(this.buttonRefreshPetTask_Click);
            // 
            // buttonUpdatePetTaskState
            // 
            this.buttonUpdatePetTaskState.Location = new System.Drawing.Point(11, 248);
            this.buttonUpdatePetTaskState.Name = "buttonUpdatePetTaskState";
            this.buttonUpdatePetTaskState.Size = new System.Drawing.Size(87, 23);
            this.buttonUpdatePetTaskState.TabIndex = 13;
            this.buttonUpdatePetTaskState.Text = "更新伙伴任务";
            this.buttonUpdatePetTaskState.UseVisualStyleBackColor = true;
            this.buttonUpdatePetTaskState.Click += new System.EventHandler(this.buttonUpdatePetTaskState_Click);
            // 
            // buttonGetPetTaskPrize
            // 
            this.buttonGetPetTaskPrize.Location = new System.Drawing.Point(11, 277);
            this.buttonGetPetTaskPrize.Name = "buttonGetPetTaskPrize";
            this.buttonGetPetTaskPrize.Size = new System.Drawing.Size(87, 23);
            this.buttonGetPetTaskPrize.TabIndex = 14;
            this.buttonGetPetTaskPrize.Text = "伙伴任务奖励";
            this.buttonGetPetTaskPrize.UseVisualStyleBackColor = true;
            this.buttonGetPetTaskPrize.Click += new System.EventHandler(this.buttonGetPetTaskPrize_Click);
            // 
            // FormTask
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(509, 541);
            this.Controls.Add(this.buttonGetPetTaskPrize);
            this.Controls.Add(this.buttonUpdatePetTaskState);
            this.Controls.Add(this.buttonRefreshPetTask);
            this.Controls.Add(this.buttonGetPetTask);
            this.Controls.Add(this.textBoxPara1);
            this.Controls.Add(this.textBoxPara3);
            this.Controls.Add(this.textBoxPara2);
            this.Controls.Add(this.buttonUpdateMainTaskStage);
            this.Controls.Add(this.buttonGetMainTaskPrize);
            this.Controls.Add(this.buttonGetMainTask);
            this.Controls.Add(this.textBoxPrizeTaskTPID);
            this.Controls.Add(this.buttonGetPrize);
            this.Controls.Add(this.buttonDailyTaskList);
            this.Controls.Add(this.textBoxTips);
            this.Controls.Add(this.buttonExit);
            this.Name = "FormTask";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonExit;
        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.TextBox textBoxTips;
        private System.Windows.Forms.Button buttonDailyTaskList;
        private System.Windows.Forms.Button buttonGetPrize;
        private System.Windows.Forms.TextBox textBoxPrizeTaskTPID;
        private System.Windows.Forms.Button buttonGetMainTask;
        private System.Windows.Forms.Button buttonGetMainTaskPrize;
        private System.Windows.Forms.Button buttonUpdateMainTaskStage;
        private System.Windows.Forms.TextBox textBoxPara1;
        private System.Windows.Forms.TextBox textBoxPara2;
        private System.Windows.Forms.TextBox textBoxPara3;
        private System.Windows.Forms.Button buttonGetPetTask;
        private System.Windows.Forms.Button buttonRefreshPetTask;
        private System.Windows.Forms.Button buttonUpdatePetTaskState;
        private System.Windows.Forms.Button buttonGetPetTaskPrize;
    }
}