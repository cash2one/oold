namespace SimulateClient
{
    partial class FormEquip
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
            this.textBoxEquipID = new System.Windows.Forms.TextBox();
            this.textBoxGemID = new System.Windows.Forms.TextBox();
            this.EquipID = new System.Windows.Forms.Label();
            this.gemID = new System.Windows.Forms.Label();
            this.textBoxData = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxIndex = new System.Windows.Forms.TextBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.装备养成ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.当前装备ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.下一强化等级装备ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.身上装备ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.背包装备ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.全部装备ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.装备强化ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.获取强化条件ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.装备强化ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.装备脱穿ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.脱下装备ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.穿上装备ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.装备宝石ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.镶嵌宝石ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.取下宝石ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.合成宝石ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.装备洗练ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.装备洗练ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.装备拆解ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.拆解结果ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.装备拆解ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.resetRestore = new System.Windows.Forms.ToolStripMenuItem();
            this.ExchangeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // textBoxEquipID
            // 
            this.textBoxEquipID.Location = new System.Drawing.Point(79, 35);
            this.textBoxEquipID.Name = "textBoxEquipID";
            this.textBoxEquipID.Size = new System.Drawing.Size(86, 21);
            this.textBoxEquipID.TabIndex = 4;
            this.textBoxEquipID.TextChanged += new System.EventHandler(this.textBoxEquipID_TextChanged);
            // 
            // textBoxGemID
            // 
            this.textBoxGemID.Location = new System.Drawing.Point(217, 34);
            this.textBoxGemID.Name = "textBoxGemID";
            this.textBoxGemID.Size = new System.Drawing.Size(86, 21);
            this.textBoxGemID.TabIndex = 4;
            this.textBoxGemID.TextChanged += new System.EventHandler(this.textBoxGemID_TextChanged);
            // 
            // EquipID
            // 
            this.EquipID.AutoSize = true;
            this.EquipID.Location = new System.Drawing.Point(17, 43);
            this.EquipID.Name = "EquipID";
            this.EquipID.Size = new System.Drawing.Size(53, 12);
            this.EquipID.TabIndex = 5;
            this.EquipID.Text = "EquipID:";
            // 
            // gemID
            // 
            this.gemID.AutoSize = true;
            this.gemID.Location = new System.Drawing.Point(171, 40);
            this.gemID.Name = "gemID";
            this.gemID.Size = new System.Drawing.Size(41, 12);
            this.gemID.TabIndex = 5;
            this.gemID.Text = "GemID:";
            // 
            // textBoxData
            // 
            this.textBoxData.Location = new System.Drawing.Point(12, 62);
            this.textBoxData.Multiline = true;
            this.textBoxData.Name = "textBoxData";
            this.textBoxData.Size = new System.Drawing.Size(884, 539);
            this.textBoxData.TabIndex = 8;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(313, 41);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(71, 12);
            this.label1.TabIndex = 19;
            this.label1.Text = "宝石孔索引:";
            // 
            // textBoxIndex
            // 
            this.textBoxIndex.Location = new System.Drawing.Point(389, 34);
            this.textBoxIndex.Name = "textBoxIndex";
            this.textBoxIndex.Size = new System.Drawing.Size(86, 21);
            this.textBoxIndex.TabIndex = 20;
            this.textBoxIndex.TextChanged += new System.EventHandler(this.textBoxIndex_TextChanged);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.装备养成ToolStripMenuItem,
            this.装备强化ToolStripMenuItem1,
            this.装备脱穿ToolStripMenuItem,
            this.装备宝石ToolStripMenuItem,
            this.装备洗练ToolStripMenuItem,
            this.装备拆解ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(908, 25);
            this.menuStrip1.TabIndex = 23;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 装备养成ToolStripMenuItem
            // 
            this.装备养成ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.当前装备ToolStripMenuItem,
            this.下一强化等级装备ToolStripMenuItem,
            this.身上装备ToolStripMenuItem,
            this.背包装备ToolStripMenuItem,
            this.全部装备ToolStripMenuItem});
            this.装备养成ToolStripMenuItem.Name = "装备养成ToolStripMenuItem";
            this.装备养成ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.装备养成ToolStripMenuItem.Text = "装备获取";
            // 
            // 当前装备ToolStripMenuItem
            // 
            this.当前装备ToolStripMenuItem.Name = "当前装备ToolStripMenuItem";
            this.当前装备ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.当前装备ToolStripMenuItem.Text = "当前装备";
            this.当前装备ToolStripMenuItem.Click += new System.EventHandler(this.当前装备ToolStripMenuItem_Click);
            // 
            // 下一强化等级装备ToolStripMenuItem
            // 
            this.下一强化等级装备ToolStripMenuItem.Name = "下一强化等级装备ToolStripMenuItem";
            this.下一强化等级装备ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.下一强化等级装备ToolStripMenuItem.Text = "下一强化等级装备";
            this.下一强化等级装备ToolStripMenuItem.Click += new System.EventHandler(this.下一强化等级装备ToolStripMenuItem_Click);
            // 
            // 身上装备ToolStripMenuItem
            // 
            this.身上装备ToolStripMenuItem.Name = "身上装备ToolStripMenuItem";
            this.身上装备ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.身上装备ToolStripMenuItem.Text = "身上装备";
            this.身上装备ToolStripMenuItem.Click += new System.EventHandler(this.身上装备ToolStripMenuItem_Click);
            // 
            // 背包装备ToolStripMenuItem
            // 
            this.背包装备ToolStripMenuItem.Name = "背包装备ToolStripMenuItem";
            this.背包装备ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.背包装备ToolStripMenuItem.Text = "背包装备";
            this.背包装备ToolStripMenuItem.Click += new System.EventHandler(this.背包装备ToolStripMenuItem_Click);
            // 
            // 全部装备ToolStripMenuItem
            // 
            this.全部装备ToolStripMenuItem.Name = "全部装备ToolStripMenuItem";
            this.全部装备ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.全部装备ToolStripMenuItem.Text = "全部装备";
            this.全部装备ToolStripMenuItem.Click += new System.EventHandler(this.全部装备ToolStripMenuItem_Click);
            // 
            // 装备强化ToolStripMenuItem1
            // 
            this.装备强化ToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.获取强化条件ToolStripMenuItem,
            this.装备强化ToolStripMenuItem});
            this.装备强化ToolStripMenuItem1.Name = "装备强化ToolStripMenuItem1";
            this.装备强化ToolStripMenuItem1.Size = new System.Drawing.Size(68, 21);
            this.装备强化ToolStripMenuItem1.Text = "装备强化";
            // 
            // 获取强化条件ToolStripMenuItem
            // 
            this.获取强化条件ToolStripMenuItem.Name = "获取强化条件ToolStripMenuItem";
            this.获取强化条件ToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.获取强化条件ToolStripMenuItem.Text = "获取强化条件";
            this.获取强化条件ToolStripMenuItem.Click += new System.EventHandler(this.获取强化条件ToolStripMenuItem_Click);
            // 
            // 装备强化ToolStripMenuItem
            // 
            this.装备强化ToolStripMenuItem.Name = "装备强化ToolStripMenuItem";
            this.装备强化ToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.装备强化ToolStripMenuItem.Text = "装备强化";
            this.装备强化ToolStripMenuItem.Click += new System.EventHandler(this.装备强化ToolStripMenuItem_Click);
            // 
            // 装备脱穿ToolStripMenuItem
            // 
            this.装备脱穿ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.脱下装备ToolStripMenuItem,
            this.穿上装备ToolStripMenuItem});
            this.装备脱穿ToolStripMenuItem.Name = "装备脱穿ToolStripMenuItem";
            this.装备脱穿ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.装备脱穿ToolStripMenuItem.Text = "装备脱穿";
            // 
            // 脱下装备ToolStripMenuItem
            // 
            this.脱下装备ToolStripMenuItem.Name = "脱下装备ToolStripMenuItem";
            this.脱下装备ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.脱下装备ToolStripMenuItem.Text = "脱下装备";
            this.脱下装备ToolStripMenuItem.Click += new System.EventHandler(this.脱下装备ToolStripMenuItem_Click);
            // 
            // 穿上装备ToolStripMenuItem
            // 
            this.穿上装备ToolStripMenuItem.Name = "穿上装备ToolStripMenuItem";
            this.穿上装备ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.穿上装备ToolStripMenuItem.Text = "穿上装备";
            this.穿上装备ToolStripMenuItem.Click += new System.EventHandler(this.穿上装备ToolStripMenuItem_Click);
            // 
            // 装备宝石ToolStripMenuItem
            // 
            this.装备宝石ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.镶嵌宝石ToolStripMenuItem,
            this.取下宝石ToolStripMenuItem,
            this.合成宝石ToolStripMenuItem});
            this.装备宝石ToolStripMenuItem.Name = "装备宝石ToolStripMenuItem";
            this.装备宝石ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.装备宝石ToolStripMenuItem.Text = "装备宝石";
            // 
            // 镶嵌宝石ToolStripMenuItem
            // 
            this.镶嵌宝石ToolStripMenuItem.Name = "镶嵌宝石ToolStripMenuItem";
            this.镶嵌宝石ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.镶嵌宝石ToolStripMenuItem.Text = "镶嵌宝石";
            this.镶嵌宝石ToolStripMenuItem.Click += new System.EventHandler(this.镶嵌宝石ToolStripMenuItem_Click);
            // 
            // 取下宝石ToolStripMenuItem
            // 
            this.取下宝石ToolStripMenuItem.Name = "取下宝石ToolStripMenuItem";
            this.取下宝石ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.取下宝石ToolStripMenuItem.Text = "取下宝石";
            this.取下宝石ToolStripMenuItem.Click += new System.EventHandler(this.取下宝石ToolStripMenuItem_Click);
            // 
            // 合成宝石ToolStripMenuItem
            // 
            this.合成宝石ToolStripMenuItem.Name = "合成宝石ToolStripMenuItem";
            this.合成宝石ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.合成宝石ToolStripMenuItem.Text = "合成宝石";
            this.合成宝石ToolStripMenuItem.Click += new System.EventHandler(this.合成宝石ToolStripMenuItem_Click);
            // 
            // 装备洗练ToolStripMenuItem
            // 
            this.装备洗练ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.装备洗练ToolStripMenuItem1,
            this.resetRestore,
            this.ExchangeToolStripMenuItem});
            this.装备洗练ToolStripMenuItem.Name = "装备洗练ToolStripMenuItem";
            this.装备洗练ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.装备洗练ToolStripMenuItem.Text = "装备洗练";
            // 
            // 装备洗练ToolStripMenuItem1
            // 
            this.装备洗练ToolStripMenuItem1.Name = "装备洗练ToolStripMenuItem1";
            this.装备洗练ToolStripMenuItem1.Size = new System.Drawing.Size(152, 22);
            this.装备洗练ToolStripMenuItem1.Text = "装备洗练";
            this.装备洗练ToolStripMenuItem1.Click += new System.EventHandler(this.装备洗练ToolStripMenuItem1_Click);
            // 
            // 装备拆解ToolStripMenuItem
            // 
            this.装备拆解ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.拆解结果ToolStripMenuItem,
            this.装备拆解ToolStripMenuItem1});
            this.装备拆解ToolStripMenuItem.Name = "装备拆解ToolStripMenuItem";
            this.装备拆解ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.装备拆解ToolStripMenuItem.Text = "装备拆解";
            // 
            // 拆解结果ToolStripMenuItem
            // 
            this.拆解结果ToolStripMenuItem.Name = "拆解结果ToolStripMenuItem";
            this.拆解结果ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.拆解结果ToolStripMenuItem.Text = "拆解结果";
            this.拆解结果ToolStripMenuItem.Click += new System.EventHandler(this.拆解结果ToolStripMenuItem_Click);
            // 
            // 装备拆解ToolStripMenuItem1
            // 
            this.装备拆解ToolStripMenuItem1.Name = "装备拆解ToolStripMenuItem1";
            this.装备拆解ToolStripMenuItem1.Size = new System.Drawing.Size(152, 22);
            this.装备拆解ToolStripMenuItem1.Text = "装备拆解";
            this.装备拆解ToolStripMenuItem1.Click += new System.EventHandler(this.装备拆解ToolStripMenuItem1_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(563, 33);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(100, 21);
            this.textBox1.TabIndex = 24;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(502, 37);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 25;
            this.label2.Text = "材料装备";
            // 
            // resetRestore
            // 
            this.resetRestore.Name = "resetRestore";
            this.resetRestore.Size = new System.Drawing.Size(152, 22);
            this.resetRestore.Text = "洗练恢复";
            this.resetRestore.Click += new System.EventHandler(this.resetRestore_Click);
            // 
            // ExchangeToolStripMenuItem
            // 
            this.ExchangeToolStripMenuItem.Name = "ExchangeToolStripMenuItem";
            this.ExchangeToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.ExchangeToolStripMenuItem.Text = "装备转移";
            this.ExchangeToolStripMenuItem.Click += new System.EventHandler(this.ExchangeToolStripMenuItem_Click);
            // 
            // FormEquip
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(908, 613);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.textBoxIndex);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxData);
            this.Controls.Add(this.gemID);
            this.Controls.Add(this.EquipID);
            this.Controls.Add(this.textBoxGemID);
            this.Controls.Add(this.textBoxEquipID);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "FormEquip";
            this.Text = "装备";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormEquip_FormClosed);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.TextBox textBoxEquipID;
        private System.Windows.Forms.TextBox textBoxGemID;
        private System.Windows.Forms.Label EquipID;
        private System.Windows.Forms.Label gemID;
        private System.Windows.Forms.TextBox textBoxData;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxIndex;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 装备养成ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 当前装备ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 下一强化等级装备ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 身上装备ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 背包装备ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 全部装备ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 装备强化ToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 获取强化条件ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 装备强化ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 装备脱穿ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 脱下装备ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 穿上装备ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 装备宝石ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 装备洗练ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 装备洗练ToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 装备拆解ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 镶嵌宝石ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 取下宝石ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 合成宝石ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 拆解结果ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 装备拆解ToolStripMenuItem1;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ToolStripMenuItem resetRestore;
        private System.Windows.Forms.ToolStripMenuItem ExchangeToolStripMenuItem;
    }
}