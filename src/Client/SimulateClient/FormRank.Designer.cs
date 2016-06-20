namespace SimulateClient
{
    partial class FormRank
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
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.buttonGetRank = new System.Windows.Forms.Button();
            this.buttonExit = new System.Windows.Forms.Button();
            this.rankButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.rankList = new System.Windows.Forms.ComboBox();
            this.vipState = new System.Windows.Forms.Button();
            this.getVipPrize = new System.Windows.Forms.Button();
            this.regNtfCharge = new System.Windows.Forms.Button();
            this.GetTimeBtn = new System.Windows.Forms.Button();
            this.GetChargeInfoBtn = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 68);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(298, 171);
            this.textBox1.TabIndex = 0;
            // 
            // buttonGetRank
            // 
            this.buttonGetRank.Location = new System.Drawing.Point(13, 11);
            this.buttonGetRank.Name = "buttonGetRank";
            this.buttonGetRank.Size = new System.Drawing.Size(75, 23);
            this.buttonGetRank.TabIndex = 1;
            this.buttonGetRank.Text = "排名";
            this.buttonGetRank.UseVisualStyleBackColor = true;
            this.buttonGetRank.Click += new System.EventHandler(this.buttonGetRank_Click);
            // 
            // buttonExit
            // 
            this.buttonExit.Location = new System.Drawing.Point(331, 227);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(75, 23);
            this.buttonExit.TabIndex = 2;
            this.buttonExit.Text = "退出";
            this.buttonExit.UseVisualStyleBackColor = true;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // rankButton
            // 
            this.rankButton.Location = new System.Drawing.Point(331, 20);
            this.rankButton.Name = "rankButton";
            this.rankButton.Size = new System.Drawing.Size(75, 23);
            this.rankButton.TabIndex = 3;
            this.rankButton.Text = "获取排名";
            this.rankButton.UseVisualStyleBackColor = true;
            this.rankButton.Click += new System.EventHandler(this.rankButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(117, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 5;
            this.label1.Text = "排名类型:";
            // 
            // rankList
            // 
            this.rankList.FormattingEnabled = true;
            this.rankList.Items.AddRange(new object[] {
            "竞技场",
            "试炼空间",
            "玩家活跃度",
            "战斗力"});
            this.rankList.Location = new System.Drawing.Point(178, 24);
            this.rankList.Name = "rankList";
            this.rankList.Size = new System.Drawing.Size(121, 20);
            this.rankList.TabIndex = 6;
            // 
            // vipState
            // 
            this.vipState.Location = new System.Drawing.Point(331, 49);
            this.vipState.Name = "vipState";
            this.vipState.Size = new System.Drawing.Size(75, 23);
            this.vipState.TabIndex = 7;
            this.vipState.Text = "vip奖励状态";
            this.vipState.UseVisualStyleBackColor = true;
            this.vipState.Click += new System.EventHandler(this.vipState_Click);
            // 
            // getVipPrize
            // 
            this.getVipPrize.Location = new System.Drawing.Point(331, 78);
            this.getVipPrize.Name = "getVipPrize";
            this.getVipPrize.Size = new System.Drawing.Size(75, 23);
            this.getVipPrize.TabIndex = 8;
            this.getVipPrize.Text = "获取奖励";
            this.getVipPrize.UseVisualStyleBackColor = true;
            this.getVipPrize.Click += new System.EventHandler(this.getVipPrize_Click);
            // 
            // regNtfCharge
            // 
            this.regNtfCharge.Location = new System.Drawing.Point(331, 107);
            this.regNtfCharge.Name = "regNtfCharge";
            this.regNtfCharge.Size = new System.Drawing.Size(75, 23);
            this.regNtfCharge.TabIndex = 9;
            this.regNtfCharge.Text = "注册充值通知";
            this.regNtfCharge.UseVisualStyleBackColor = true;
            this.regNtfCharge.Click += new System.EventHandler(this.regNtfCharge_Click);
            // 
            // GetTimeBtn
            // 
            this.GetTimeBtn.Location = new System.Drawing.Point(331, 136);
            this.GetTimeBtn.Name = "GetTimeBtn";
            this.GetTimeBtn.Size = new System.Drawing.Size(75, 23);
            this.GetTimeBtn.TabIndex = 10;
            this.GetTimeBtn.Text = "获取时间";
            this.GetTimeBtn.UseVisualStyleBackColor = true;
            this.GetTimeBtn.Click += new System.EventHandler(this.GetTimeBtn_Click);
            // 
            // GetChargeInfoBtn
            // 
            this.GetChargeInfoBtn.Location = new System.Drawing.Point(331, 166);
            this.GetChargeInfoBtn.Name = "GetChargeInfoBtn";
            this.GetChargeInfoBtn.Size = new System.Drawing.Size(75, 23);
            this.GetChargeInfoBtn.TabIndex = 11;
            this.GetChargeInfoBtn.Text = "获取商品信息";
            this.GetChargeInfoBtn.UseVisualStyleBackColor = true;
            this.GetChargeInfoBtn.Click += new System.EventHandler(this.GetChargeInfoBtn_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(331, 198);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 12;
            this.button1.Text = "事件回复";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // FormRank
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(418, 262);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.GetChargeInfoBtn);
            this.Controls.Add(this.GetTimeBtn);
            this.Controls.Add(this.regNtfCharge);
            this.Controls.Add(this.getVipPrize);
            this.Controls.Add(this.vipState);
            this.Controls.Add(this.rankList);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.rankButton);
            this.Controls.Add(this.buttonExit);
            this.Controls.Add(this.buttonGetRank);
            this.Controls.Add(this.textBox1);
            this.Name = "FormRank";
            this.Text = "FormRank";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button buttonGetRank;
        private System.Windows.Forms.Button buttonExit;
        private System.Windows.Forms.Button rankButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox rankList;
        private System.Windows.Forms.Button vipState;
        private System.Windows.Forms.Button getVipPrize;
        private System.Windows.Forms.Button regNtfCharge;
        private System.Windows.Forms.Button GetTimeBtn;
        private System.Windows.Forms.Button GetChargeInfoBtn;
        private System.Windows.Forms.Button button1;
    }
}