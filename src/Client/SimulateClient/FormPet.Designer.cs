namespace SimulateClient
{
    partial class FormPet
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
            this.timerWait = new System.Windows.Forms.Timer(this.components);
            this.textBoxTestShow = new System.Windows.Forms.TextBox();
            this.Position = new System.Windows.Forms.Label();
            this.PetID = new System.Windows.Forms.Label();
            this.textTaskType = new System.Windows.Forms.TextBox();
            this.textBoxPetID = new System.Windows.Forms.TextBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.状态变更ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.进入温泉ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.进入4小时温泉ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.进入8小时温泉ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.离开温泉ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.温泉快速完成ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.坐下喝茶ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.取消援护ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取数据ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.伙伴数据ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取伙伴基础信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取单个伙伴数据ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取解锁进度ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.伙伴解锁ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.伙伴任务ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取日常对话任务ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取任务ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.完成伙伴任务ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.完成对战ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取任务列表ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.HotSpringToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ExpandHotSpringToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.textBoxCount = new System.Windows.Forms.TextBox();
            this.textBoxTPID = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // textBoxTestShow
            // 
            this.textBoxTestShow.Location = new System.Drawing.Point(12, 61);
            this.textBoxTestShow.Multiline = true;
            this.textBoxTestShow.Name = "textBoxTestShow";
            this.textBoxTestShow.Size = new System.Drawing.Size(630, 470);
            this.textBoxTestShow.TabIndex = 1;
            // 
            // Position
            // 
            this.Position.AutoSize = true;
            this.Position.Location = new System.Drawing.Point(171, 37);
            this.Position.Name = "Position";
            this.Position.Size = new System.Drawing.Size(53, 12);
            this.Position.TabIndex = 8;
            this.Position.Text = "taskType";
            // 
            // PetID
            // 
            this.PetID.AutoSize = true;
            this.PetID.Location = new System.Drawing.Point(25, 38);
            this.PetID.Name = "PetID";
            this.PetID.Size = new System.Drawing.Size(35, 12);
            this.PetID.TabIndex = 9;
            this.PetID.Text = "PetID";
            // 
            // textTaskType
            // 
            this.textTaskType.Location = new System.Drawing.Point(228, 34);
            this.textTaskType.Name = "textTaskType";
            this.textTaskType.Size = new System.Drawing.Size(75, 21);
            this.textTaskType.TabIndex = 6;
            this.textTaskType.Text = "1";
            // 
            // textBoxPetID
            // 
            this.textBoxPetID.Location = new System.Drawing.Point(82, 34);
            this.textBoxPetID.Name = "textBoxPetID";
            this.textBoxPetID.Size = new System.Drawing.Size(75, 21);
            this.textBoxPetID.TabIndex = 7;
            this.textBoxPetID.Text = "1";
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.状态变更ToolStripMenuItem,
            this.获取数据ToolStripMenuItem,
            this.伙伴任务ToolStripMenuItem,
            this.HotSpringToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(651, 25);
            this.menuStrip1.TabIndex = 23;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 状态变更ToolStripMenuItem
            // 
            this.状态变更ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.进入温泉ToolStripMenuItem,
            this.进入4小时温泉ToolStripMenuItem,
            this.进入8小时温泉ToolStripMenuItem,
            this.离开温泉ToolStripMenuItem,
            this.温泉快速完成ToolStripMenuItem,
            this.坐下喝茶ToolStripMenuItem,
            this.取消援护ToolStripMenuItem});
            this.状态变更ToolStripMenuItem.Name = "状态变更ToolStripMenuItem";
            this.状态变更ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.状态变更ToolStripMenuItem.Text = "状态变更";
            // 
            // 进入温泉ToolStripMenuItem
            // 
            this.进入温泉ToolStripMenuItem.Name = "进入温泉ToolStripMenuItem";
            this.进入温泉ToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
            this.进入温泉ToolStripMenuItem.Text = "进入5分钟温泉";
            this.进入温泉ToolStripMenuItem.Click += new System.EventHandler(this.进入温泉ToolStripMenuItem_Click);
            // 
            // 进入4小时温泉ToolStripMenuItem
            // 
            this.进入4小时温泉ToolStripMenuItem.Name = "进入4小时温泉ToolStripMenuItem";
            this.进入4小时温泉ToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
            this.进入4小时温泉ToolStripMenuItem.Text = "进入4小时温泉";
            this.进入4小时温泉ToolStripMenuItem.Click += new System.EventHandler(this.进入4小时温泉ToolStripMenuItem_Click);
            // 
            // 进入8小时温泉ToolStripMenuItem
            // 
            this.进入8小时温泉ToolStripMenuItem.Name = "进入8小时温泉ToolStripMenuItem";
            this.进入8小时温泉ToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
            this.进入8小时温泉ToolStripMenuItem.Text = "进入8小时温泉";
            this.进入8小时温泉ToolStripMenuItem.Click += new System.EventHandler(this.进入8小时温泉ToolStripMenuItem_Click);
            // 
            // 离开温泉ToolStripMenuItem
            // 
            this.离开温泉ToolStripMenuItem.Name = "离开温泉ToolStripMenuItem";
            this.离开温泉ToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
            this.离开温泉ToolStripMenuItem.Text = "温泉完成";
            this.离开温泉ToolStripMenuItem.Click += new System.EventHandler(this.离开温泉ToolStripMenuItem_Click);
            // 
            // 温泉快速完成ToolStripMenuItem
            // 
            this.温泉快速完成ToolStripMenuItem.Name = "温泉快速完成ToolStripMenuItem";
            this.温泉快速完成ToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
            this.温泉快速完成ToolStripMenuItem.Text = "温泉快速完成";
            this.温泉快速完成ToolStripMenuItem.Click += new System.EventHandler(this.温泉快速完成ToolStripMenuItem_Click);
            // 
            // 坐下喝茶ToolStripMenuItem
            // 
            this.坐下喝茶ToolStripMenuItem.Name = "坐下喝茶ToolStripMenuItem";
            this.坐下喝茶ToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
            this.坐下喝茶ToolStripMenuItem.Text = "开始援护";
            this.坐下喝茶ToolStripMenuItem.Click += new System.EventHandler(this.坐下喝茶ToolStripMenuItem_Click);
            // 
            // 取消援护ToolStripMenuItem
            // 
            this.取消援护ToolStripMenuItem.Name = "取消援护ToolStripMenuItem";
            this.取消援护ToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
            this.取消援护ToolStripMenuItem.Text = "取消援护";
            this.取消援护ToolStripMenuItem.Click += new System.EventHandler(this.取消援护ToolStripMenuItem_Click);
            // 
            // 获取数据ToolStripMenuItem
            // 
            this.获取数据ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.伙伴数据ToolStripMenuItem,
            this.获取伙伴基础信息ToolStripMenuItem,
            this.获取单个伙伴数据ToolStripMenuItem,
            this.获取解锁进度ToolStripMenuItem,
            this.伙伴解锁ToolStripMenuItem});
            this.获取数据ToolStripMenuItem.Name = "获取数据ToolStripMenuItem";
            this.获取数据ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.获取数据ToolStripMenuItem.Text = "获取数据";
            // 
            // 伙伴数据ToolStripMenuItem
            // 
            this.伙伴数据ToolStripMenuItem.Name = "伙伴数据ToolStripMenuItem";
            this.伙伴数据ToolStripMenuItem.Size = new System.Drawing.Size(196, 22);
            this.伙伴数据ToolStripMenuItem.Text = "获取全部数据";
            this.伙伴数据ToolStripMenuItem.Click += new System.EventHandler(this.伙伴数据ToolStripMenuItem_Click);
            // 
            // 获取伙伴基础信息ToolStripMenuItem
            // 
            this.获取伙伴基础信息ToolStripMenuItem.Name = "获取伙伴基础信息ToolStripMenuItem";
            this.获取伙伴基础信息ToolStripMenuItem.Size = new System.Drawing.Size(196, 22);
            this.获取伙伴基础信息ToolStripMenuItem.Text = "获取伙伴基础信息列表";
            this.获取伙伴基础信息ToolStripMenuItem.Click += new System.EventHandler(this.获取伙伴基础信息ToolStripMenuItem_Click);
            // 
            // 获取单个伙伴数据ToolStripMenuItem
            // 
            this.获取单个伙伴数据ToolStripMenuItem.Name = "获取单个伙伴数据ToolStripMenuItem";
            this.获取单个伙伴数据ToolStripMenuItem.Size = new System.Drawing.Size(196, 22);
            this.获取单个伙伴数据ToolStripMenuItem.Text = "获取单个伙伴数据";
            this.获取单个伙伴数据ToolStripMenuItem.Click += new System.EventHandler(this.获取单个伙伴数据ToolStripMenuItem_Click);
            // 
            // 获取解锁进度ToolStripMenuItem
            // 
            this.获取解锁进度ToolStripMenuItem.Name = "获取解锁进度ToolStripMenuItem";
            this.获取解锁进度ToolStripMenuItem.Size = new System.Drawing.Size(196, 22);
            this.获取解锁进度ToolStripMenuItem.Text = "获取解锁进度";
            this.获取解锁进度ToolStripMenuItem.Click += new System.EventHandler(this.获取解锁进度ToolStripMenuItem_Click);
            // 
            // 伙伴解锁ToolStripMenuItem
            // 
            this.伙伴解锁ToolStripMenuItem.Name = "伙伴解锁ToolStripMenuItem";
            this.伙伴解锁ToolStripMenuItem.Size = new System.Drawing.Size(196, 22);
            this.伙伴解锁ToolStripMenuItem.Text = "伙伴解锁";
            this.伙伴解锁ToolStripMenuItem.Click += new System.EventHandler(this.伙伴解锁ToolStripMenuItem_Click);
            // 
            // 伙伴任务ToolStripMenuItem
            // 
            this.伙伴任务ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.获取日常对话任务ToolStripMenuItem,
            this.获取任务ToolStripMenuItem,
            this.完成伙伴任务ToolStripMenuItem,
            this.完成对战ToolStripMenuItem,
            this.获取任务列表ToolStripMenuItem});
            this.伙伴任务ToolStripMenuItem.Name = "伙伴任务ToolStripMenuItem";
            this.伙伴任务ToolStripMenuItem.Size = new System.Drawing.Size(44, 21);
            this.伙伴任务ToolStripMenuItem.Text = "任务";
            // 
            // 获取日常对话任务ToolStripMenuItem
            // 
            this.获取日常对话任务ToolStripMenuItem.Name = "获取日常对话任务ToolStripMenuItem";
            this.获取日常对话任务ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.获取日常对话任务ToolStripMenuItem.Text = "获取日常聊天任务";
            this.获取日常对话任务ToolStripMenuItem.Click += new System.EventHandler(this.获取日常对话任务ToolStripMenuItem_Click);
            // 
            // 获取任务ToolStripMenuItem
            // 
            this.获取任务ToolStripMenuItem.Name = "获取任务ToolStripMenuItem";
            this.获取任务ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.获取任务ToolStripMenuItem.Text = "获取任务";
            this.获取任务ToolStripMenuItem.Click += new System.EventHandler(this.获取任务ToolStripMenuItem_Click);
            // 
            // 完成伙伴任务ToolStripMenuItem
            // 
            this.完成伙伴任务ToolStripMenuItem.Name = "完成伙伴任务ToolStripMenuItem";
            this.完成伙伴任务ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.完成伙伴任务ToolStripMenuItem.Text = "完成伙伴任务";
            this.完成伙伴任务ToolStripMenuItem.Click += new System.EventHandler(this.完成伙伴任务ToolStripMenuItem_Click);
            // 
            // 完成对战ToolStripMenuItem
            // 
            this.完成对战ToolStripMenuItem.Name = "完成对战ToolStripMenuItem";
            this.完成对战ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.完成对战ToolStripMenuItem.Text = "完成对战";
            this.完成对战ToolStripMenuItem.Click += new System.EventHandler(this.完成对战ToolStripMenuItem_Click);
            // 
            // 获取任务列表ToolStripMenuItem
            // 
            this.获取任务列表ToolStripMenuItem.Name = "获取任务列表ToolStripMenuItem";
            this.获取任务列表ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.获取任务列表ToolStripMenuItem.Text = "日常送礼";
            this.获取任务列表ToolStripMenuItem.Click += new System.EventHandler(this.GetSendGiftToolStripMenuItem_Click);
            // 
            // HotSpringToolStripMenuItem
            // 
            this.HotSpringToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ExpandHotSpringToolStripMenuItem});
            this.HotSpringToolStripMenuItem.Name = "HotSpringToolStripMenuItem";
            this.HotSpringToolStripMenuItem.Size = new System.Drawing.Size(44, 21);
            this.HotSpringToolStripMenuItem.Text = "温泉";
            // 
            // ExpandHotSpringToolStripMenuItem
            // 
            this.ExpandHotSpringToolStripMenuItem.Name = "ExpandHotSpringToolStripMenuItem";
            this.ExpandHotSpringToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.ExpandHotSpringToolStripMenuItem.Text = "温泉扩建";
            this.ExpandHotSpringToolStripMenuItem.Click += new System.EventHandler(this.ExpandHotSpringToolStripMenuItem_Click);
            // 
            // textBoxCount
            // 
            this.textBoxCount.Location = new System.Drawing.Point(533, 34);
            this.textBoxCount.Name = "textBoxCount";
            this.textBoxCount.Size = new System.Drawing.Size(100, 21);
            this.textBoxCount.TabIndex = 24;
            this.textBoxCount.Text = "1";
            // 
            // textBoxTPID
            // 
            this.textBoxTPID.Location = new System.Drawing.Point(365, 34);
            this.textBoxTPID.Name = "textBoxTPID";
            this.textBoxTPID.Size = new System.Drawing.Size(100, 21);
            this.textBoxTPID.TabIndex = 24;
            this.textBoxTPID.Text = "2413";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(306, 38);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 8;
            this.label1.Text = "itemTPID";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(471, 37);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(59, 12);
            this.label2.TabIndex = 8;
            this.label2.Text = "itemCount";
            // 
            // FormPet
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(651, 543);
            this.Controls.Add(this.textBoxTPID);
            this.Controls.Add(this.textBoxCount);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Position);
            this.Controls.Add(this.PetID);
            this.Controls.Add(this.textTaskType);
            this.Controls.Add(this.textBoxPetID);
            this.Controls.Add(this.textBoxTestShow);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "FormPet";
            this.Text = "FormPet";
            this.Load += new System.EventHandler(this.FormPet_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormPet_FormClosed);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.TextBox textBoxTestShow;
        private System.Windows.Forms.Label Position;
        private System.Windows.Forms.Label PetID;
        private System.Windows.Forms.TextBox textTaskType;
        private System.Windows.Forms.TextBox textBoxPetID;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 状态变更ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 进入温泉ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 离开温泉ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 坐下喝茶ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取数据ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 伙伴数据ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 伙伴任务ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取任务列表ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 完成伙伴任务ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem HotSpringToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ExpandHotSpringToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 取消援护ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 温泉快速完成ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取单个伙伴数据ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取日常对话任务ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取解锁进度ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 伙伴解锁ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 进入4小时温泉ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 进入8小时温泉ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取伙伴基础信息ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 完成对战ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取任务ToolStripMenuItem;
        private System.Windows.Forms.TextBox textBoxCount;
        private System.Windows.Forms.TextBox textBoxTPID;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}