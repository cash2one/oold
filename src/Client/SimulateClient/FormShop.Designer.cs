namespace SimulateClient
{
    partial class FormShop
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
            this.buttonOpen = new System.Windows.Forms.Button();
            this.buttonBuy = new System.Windows.Forms.Button();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.buttonPaidRefresh = new System.Windows.Forms.Button();
            this.textBoxInput = new System.Windows.Forms.TextBox();
            this.textBoxOutput = new System.Windows.Forms.TextBox();
            this.buttonExit = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.textBoxId = new System.Windows.Forms.TextBox();
            this.textBoxNum = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.OpenCardBtn = new System.Windows.Forms.Button();
            this.clickCardBtn = new System.Windows.Forms.Button();
            this.GetCardBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonOpen
            // 
            this.buttonOpen.Location = new System.Drawing.Point(261, 44);
            this.buttonOpen.Name = "buttonOpen";
            this.buttonOpen.Size = new System.Drawing.Size(75, 23);
            this.buttonOpen.TabIndex = 0;
            this.buttonOpen.Text = "打开";
            this.buttonOpen.UseVisualStyleBackColor = true;
            this.buttonOpen.Click += new System.EventHandler(this.buttonOpen_Click);
            // 
            // buttonBuy
            // 
            this.buttonBuy.Location = new System.Drawing.Point(261, 76);
            this.buttonBuy.Name = "buttonBuy";
            this.buttonBuy.Size = new System.Drawing.Size(75, 23);
            this.buttonBuy.TabIndex = 1;
            this.buttonBuy.Text = "购买";
            this.buttonBuy.UseVisualStyleBackColor = true;
            this.buttonBuy.Click += new System.EventHandler(this.buttonBuy_Click);
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.Location = new System.Drawing.Point(261, 105);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(75, 23);
            this.buttonRefresh.TabIndex = 2;
            this.buttonRefresh.Text = "刷新";
            this.buttonRefresh.UseVisualStyleBackColor = true;
            this.buttonRefresh.Click += new System.EventHandler(this.buttonRefresh_Click);
            // 
            // buttonPaidRefresh
            // 
            this.buttonPaidRefresh.Location = new System.Drawing.Point(261, 134);
            this.buttonPaidRefresh.Name = "buttonPaidRefresh";
            this.buttonPaidRefresh.Size = new System.Drawing.Size(75, 23);
            this.buttonPaidRefresh.TabIndex = 3;
            this.buttonPaidRefresh.Text = "付费刷新";
            this.buttonPaidRefresh.UseVisualStyleBackColor = true;
            this.buttonPaidRefresh.Click += new System.EventHandler(this.buttonPaidRefresh_Click);
            // 
            // textBoxInput
            // 
            this.textBoxInput.Location = new System.Drawing.Point(7, 12);
            this.textBoxInput.Name = "textBoxInput";
            this.textBoxInput.Size = new System.Drawing.Size(105, 21);
            this.textBoxInput.TabIndex = 4;
            // 
            // textBoxOutput
            // 
            this.textBoxOutput.Location = new System.Drawing.Point(-4, 217);
            this.textBoxOutput.Multiline = true;
            this.textBoxOutput.Name = "textBoxOutput";
            this.textBoxOutput.Size = new System.Drawing.Size(220, 157);
            this.textBoxOutput.TabIndex = 5;
            // 
            // buttonExit
            // 
            this.buttonExit.Location = new System.Drawing.Point(148, 188);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(75, 23);
            this.buttonExit.TabIndex = 6;
            this.buttonExit.Text = "退出";
            this.buttonExit.UseVisualStyleBackColor = true;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // textBoxId
            // 
            this.textBoxId.Location = new System.Drawing.Point(7, 72);
            this.textBoxId.Name = "textBoxId";
            this.textBoxId.Size = new System.Drawing.Size(100, 21);
            this.textBoxId.TabIndex = 7;
            // 
            // textBoxNum
            // 
            this.textBoxNum.Location = new System.Drawing.Point(7, 125);
            this.textBoxNum.Name = "textBoxNum";
            this.textBoxNum.Size = new System.Drawing.Size(100, 21);
            this.textBoxNum.TabIndex = 8;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(140, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(185, 12);
            this.label1.TabIndex = 9;
            this.label1.Text = "商店(1道具, 2 pvp, 3 每日限量)";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(140, 81);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 12);
            this.label2.TabIndex = 10;
            this.label2.Text = "id(非item id)";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(140, 134);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 11;
            this.label3.Text = "购买次数";
            // 
            // OpenCardBtn
            // 
            this.OpenCardBtn.Location = new System.Drawing.Point(261, 188);
            this.OpenCardBtn.Name = "OpenCardBtn";
            this.OpenCardBtn.Size = new System.Drawing.Size(75, 23);
            this.OpenCardBtn.TabIndex = 12;
            this.OpenCardBtn.Text = "抽卡界面";
            this.OpenCardBtn.UseVisualStyleBackColor = true;
            this.OpenCardBtn.Click += new System.EventHandler(this.OpenCardBtn_Click);
            // 
            // clickCardBtn
            // 
            this.clickCardBtn.Location = new System.Drawing.Point(261, 288);
            this.clickCardBtn.Name = "clickCardBtn";
            this.clickCardBtn.Size = new System.Drawing.Size(75, 23);
            this.clickCardBtn.TabIndex = 13;
            this.clickCardBtn.Text = "抽卡";
            this.clickCardBtn.UseVisualStyleBackColor = true;
            this.clickCardBtn.Click += new System.EventHandler(this.clickCardBtn_Click);
            // 
            // GetCardBtn
            // 
            this.GetCardBtn.Location = new System.Drawing.Point(261, 241);
            this.GetCardBtn.Name = "GetCardBtn";
            this.GetCardBtn.Size = new System.Drawing.Size(75, 23);
            this.GetCardBtn.TabIndex = 14;
            this.GetCardBtn.Text = "获得状态";
            this.GetCardBtn.UseVisualStyleBackColor = true;
            this.GetCardBtn.Click += new System.EventHandler(this.GetCardBtn_Click);
            // 
            // FormShop
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(336, 386);
            this.Controls.Add(this.GetCardBtn);
            this.Controls.Add(this.clickCardBtn);
            this.Controls.Add(this.OpenCardBtn);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxNum);
            this.Controls.Add(this.textBoxId);
            this.Controls.Add(this.buttonExit);
            this.Controls.Add(this.textBoxOutput);
            this.Controls.Add(this.textBoxInput);
            this.Controls.Add(this.buttonPaidRefresh);
            this.Controls.Add(this.buttonRefresh);
            this.Controls.Add(this.buttonBuy);
            this.Controls.Add(this.buttonOpen);
            this.Name = "FormShop";
            this.Text = "FormShop";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonOpen;
        private System.Windows.Forms.Button buttonBuy;
        private System.Windows.Forms.Button buttonRefresh;
        private System.Windows.Forms.Button buttonPaidRefresh;
        private System.Windows.Forms.TextBox textBoxInput;
        private System.Windows.Forms.TextBox textBoxOutput;
        private System.Windows.Forms.Button buttonExit;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TextBox textBoxId;
        private System.Windows.Forms.TextBox textBoxNum;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button OpenCardBtn;
        private System.Windows.Forms.Button clickCardBtn;
        private System.Windows.Forms.Button GetCardBtn;
    }
}