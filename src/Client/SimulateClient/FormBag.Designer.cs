namespace SimulateClient
{
    partial class FormBag
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
            this.textBoxShow = new System.Windows.Forms.TextBox();
            this.textBoxID = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxTPID = new System.Windows.Forms.TextBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.查询ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取物品ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.添加ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.添加物品ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.批量添加物品测试ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.出售ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.出售物品ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.使用ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.使用物品ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取能量球ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // textBoxShow
            // 
            this.textBoxShow.Location = new System.Drawing.Point(12, 57);
            this.textBoxShow.Multiline = true;
            this.textBoxShow.Name = "textBoxShow";
            this.textBoxShow.Size = new System.Drawing.Size(805, 397);
            this.textBoxShow.TabIndex = 1;
            // 
            // textBoxID
            // 
            this.textBoxID.Location = new System.Drawing.Point(85, 30);
            this.textBoxID.Name = "textBoxID";
            this.textBoxID.Size = new System.Drawing.Size(69, 21);
            this.textBoxID.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(16, 35);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 3;
            this.label1.Text = "格子索引";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(168, 35);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "物品TPID";
            // 
            // textBoxTPID
            // 
            this.textBoxTPID.Location = new System.Drawing.Point(220, 30);
            this.textBoxTPID.Name = "textBoxTPID";
            this.textBoxTPID.Size = new System.Drawing.Size(69, 21);
            this.textBoxTPID.TabIndex = 2;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.查询ToolStripMenuItem,
            this.添加ToolStripMenuItem,
            this.出售ToolStripMenuItem,
            this.使用ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(829, 25);
            this.menuStrip1.TabIndex = 10;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 查询ToolStripMenuItem
            // 
            this.查询ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.获取物品ToolStripMenuItem,
            this.获取能量球ToolStripMenuItem});
            this.查询ToolStripMenuItem.Name = "查询ToolStripMenuItem";
            this.查询ToolStripMenuItem.Size = new System.Drawing.Size(44, 21);
            this.查询ToolStripMenuItem.Text = "查询";
            // 
            // 获取物品ToolStripMenuItem
            // 
            this.获取物品ToolStripMenuItem.Name = "获取物品ToolStripMenuItem";
            this.获取物品ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.获取物品ToolStripMenuItem.Text = "获取物品";
            this.获取物品ToolStripMenuItem.Click += new System.EventHandler(this.获取物品ToolStripMenuItem_Click);
            // 
            // 添加ToolStripMenuItem
            // 
            this.添加ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.添加物品ToolStripMenuItem,
            this.批量添加物品测试ToolStripMenuItem});
            this.添加ToolStripMenuItem.Name = "添加ToolStripMenuItem";
            this.添加ToolStripMenuItem.Size = new System.Drawing.Size(44, 21);
            this.添加ToolStripMenuItem.Text = "添加";
            // 
            // 添加物品ToolStripMenuItem
            // 
            this.添加物品ToolStripMenuItem.Name = "添加物品ToolStripMenuItem";
            this.添加物品ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.添加物品ToolStripMenuItem.Text = "添加物品测试";
            this.添加物品ToolStripMenuItem.Click += new System.EventHandler(this.添加物品ToolStripMenuItem_Click);
            // 
            // 批量添加物品测试ToolStripMenuItem
            // 
            this.批量添加物品测试ToolStripMenuItem.Name = "批量添加物品测试ToolStripMenuItem";
            this.批量添加物品测试ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.批量添加物品测试ToolStripMenuItem.Text = "批量添加物品测试";
            this.批量添加物品测试ToolStripMenuItem.Click += new System.EventHandler(this.批量添加物品测试ToolStripMenuItem_Click);
            // 
            // 出售ToolStripMenuItem
            // 
            this.出售ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.出售物品ToolStripMenuItem});
            this.出售ToolStripMenuItem.Name = "出售ToolStripMenuItem";
            this.出售ToolStripMenuItem.Size = new System.Drawing.Size(44, 21);
            this.出售ToolStripMenuItem.Text = "出售";
            // 
            // 出售物品ToolStripMenuItem
            // 
            this.出售物品ToolStripMenuItem.Name = "出售物品ToolStripMenuItem";
            this.出售物品ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.出售物品ToolStripMenuItem.Text = "出售物品";
            this.出售物品ToolStripMenuItem.Click += new System.EventHandler(this.出售物品ToolStripMenuItem_Click);
            // 
            // 使用ToolStripMenuItem
            // 
            this.使用ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.使用物品ToolStripMenuItem});
            this.使用ToolStripMenuItem.Name = "使用ToolStripMenuItem";
            this.使用ToolStripMenuItem.Size = new System.Drawing.Size(44, 21);
            this.使用ToolStripMenuItem.Text = "使用";
            // 
            // 使用物品ToolStripMenuItem
            // 
            this.使用物品ToolStripMenuItem.Name = "使用物品ToolStripMenuItem";
            this.使用物品ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.使用物品ToolStripMenuItem.Text = "使用物品";
            this.使用物品ToolStripMenuItem.Click += new System.EventHandler(this.使用物品ToolStripMenuItem_Click);
            // 
            // 获取能量球ToolStripMenuItem
            // 
            this.获取能量球ToolStripMenuItem.Name = "获取能量球ToolStripMenuItem";
            this.获取能量球ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.获取能量球ToolStripMenuItem.Text = "获取能量球";
            this.获取能量球ToolStripMenuItem.Click += new System.EventHandler(this.获取能量球ToolStripMenuItem_Click);
            // 
            // FormBag
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(829, 466);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxTPID);
            this.Controls.Add(this.textBoxID);
            this.Controls.Add(this.textBoxShow);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "FormBag";
            this.Text = "背包";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormBag_FormClosed);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.TextBox textBoxShow;
        private System.Windows.Forms.TextBox textBoxID;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxTPID;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 查询ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 添加ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 出售ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 使用ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取物品ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 添加物品ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 出售物品ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 使用物品ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 批量添加物品测试ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取能量球ToolStripMenuItem;
    }
}