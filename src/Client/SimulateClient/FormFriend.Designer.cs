namespace SimulateClient
{
    partial class FormFriend
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
            this.buttonAdd = new System.Windows.Forms.Button();
            this.buttonAddConfirmAgree = new System.Windows.Forms.Button();
            this.buttonDel = new System.Windows.Forms.Button();
            this.buttonNewStrangers = new System.Windows.Forms.Button();
            this.buttonSearch = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxParam1 = new System.Windows.Forms.TextBox();
            this.textBoxParam2 = new System.Windows.Forms.TextBox();
            this.textBoxOutput = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxParam3 = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.buttonExit = new System.Windows.Forms.Button();
            this.buttonLocal = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonOpen
            // 
            this.buttonOpen.Location = new System.Drawing.Point(314, 13);
            this.buttonOpen.Name = "buttonOpen";
            this.buttonOpen.Size = new System.Drawing.Size(75, 23);
            this.buttonOpen.TabIndex = 0;
            this.buttonOpen.Text = "打开";
            this.buttonOpen.UseVisualStyleBackColor = true;
            this.buttonOpen.Click += new System.EventHandler(this.buttonOpen_Click);
            // 
            // buttonAdd
            // 
            this.buttonAdd.Location = new System.Drawing.Point(314, 61);
            this.buttonAdd.Name = "buttonAdd";
            this.buttonAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonAdd.TabIndex = 1;
            this.buttonAdd.Text = "添加好友";
            this.buttonAdd.UseVisualStyleBackColor = true;
            this.buttonAdd.Click += new System.EventHandler(this.buttonAdd_Click);
            // 
            // buttonAddConfirmAgree
            // 
            this.buttonAddConfirmAgree.Location = new System.Drawing.Point(314, 107);
            this.buttonAddConfirmAgree.Name = "buttonAddConfirmAgree";
            this.buttonAddConfirmAgree.Size = new System.Drawing.Size(94, 23);
            this.buttonAddConfirmAgree.TabIndex = 2;
            this.buttonAddConfirmAgree.Text = "同意好友申请";
            this.buttonAddConfirmAgree.UseVisualStyleBackColor = true;
            this.buttonAddConfirmAgree.Click += new System.EventHandler(this.buttonAddConfirmAgree_Click);
            // 
            // buttonDel
            // 
            this.buttonDel.Location = new System.Drawing.Point(314, 156);
            this.buttonDel.Name = "buttonDel";
            this.buttonDel.Size = new System.Drawing.Size(75, 23);
            this.buttonDel.TabIndex = 4;
            this.buttonDel.Text = "删除好友";
            this.buttonDel.UseVisualStyleBackColor = true;
            this.buttonDel.Click += new System.EventHandler(this.buttonDel_Click);
            // 
            // buttonNewStrangers
            // 
            this.buttonNewStrangers.Location = new System.Drawing.Point(314, 206);
            this.buttonNewStrangers.Name = "buttonNewStrangers";
            this.buttonNewStrangers.Size = new System.Drawing.Size(75, 23);
            this.buttonNewStrangers.TabIndex = 5;
            this.buttonNewStrangers.Text = "推送新好友";
            this.buttonNewStrangers.UseVisualStyleBackColor = true;
            this.buttonNewStrangers.Click += new System.EventHandler(this.buttonNewStrangers_Click);
            // 
            // buttonSearch
            // 
            this.buttonSearch.Location = new System.Drawing.Point(314, 252);
            this.buttonSearch.Name = "buttonSearch";
            this.buttonSearch.Size = new System.Drawing.Size(75, 23);
            this.buttonSearch.TabIndex = 6;
            this.buttonSearch.Text = "搜索好友";
            this.buttonSearch.UseVisualStyleBackColor = true;
            this.buttonSearch.Click += new System.EventHandler(this.buttonSearch_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(31, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 7;
            this.label1.Text = "参数1";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(31, 81);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 12);
            this.label2.TabIndex = 8;
            this.label2.Text = "参数2";
            // 
            // textBoxParam1
            // 
            this.textBoxParam1.Location = new System.Drawing.Point(12, 44);
            this.textBoxParam1.Name = "textBoxParam1";
            this.textBoxParam1.Size = new System.Drawing.Size(100, 21);
            this.textBoxParam1.TabIndex = 9;
            // 
            // textBoxParam2
            // 
            this.textBoxParam2.Location = new System.Drawing.Point(12, 109);
            this.textBoxParam2.Name = "textBoxParam2";
            this.textBoxParam2.Size = new System.Drawing.Size(100, 21);
            this.textBoxParam2.TabIndex = 10;
            // 
            // textBoxOutput
            // 
            this.textBoxOutput.Location = new System.Drawing.Point(12, 220);
            this.textBoxOutput.Multiline = true;
            this.textBoxOutput.Name = "textBoxOutput";
            this.textBoxOutput.Size = new System.Drawing.Size(183, 136);
            this.textBoxOutput.TabIndex = 11;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(31, 142);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 12);
            this.label3.TabIndex = 12;
            this.label3.Text = "参数3";
            // 
            // textBoxParam3
            // 
            this.textBoxParam3.Location = new System.Drawing.Point(12, 176);
            this.textBoxParam3.Name = "textBoxParam3";
            this.textBoxParam3.Size = new System.Drawing.Size(100, 21);
            this.textBoxParam3.TabIndex = 13;
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // buttonExit
            // 
            this.buttonExit.Location = new System.Drawing.Point(314, 333);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(75, 23);
            this.buttonExit.TabIndex = 14;
            this.buttonExit.Text = "退出";
            this.buttonExit.UseVisualStyleBackColor = true;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // buttonLocal
            // 
            this.buttonLocal.Location = new System.Drawing.Point(314, 294);
            this.buttonLocal.Name = "buttonLocal";
            this.buttonLocal.Size = new System.Drawing.Size(75, 23);
            this.buttonLocal.TabIndex = 15;
            this.buttonLocal.Text = "附近的人";
            this.buttonLocal.UseVisualStyleBackColor = true;
            this.buttonLocal.Click += new System.EventHandler(this.buttonLocal_Click);
            // 
            // FormFriend
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(454, 382);
            this.Controls.Add(this.buttonLocal);
            this.Controls.Add(this.buttonExit);
            this.Controls.Add(this.textBoxParam3);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBoxOutput);
            this.Controls.Add(this.textBoxParam2);
            this.Controls.Add(this.textBoxParam1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.buttonSearch);
            this.Controls.Add(this.buttonNewStrangers);
            this.Controls.Add(this.buttonDel);
            this.Controls.Add(this.buttonAddConfirmAgree);
            this.Controls.Add(this.buttonAdd);
            this.Controls.Add(this.buttonOpen);
            this.Name = "FormFriend";
            this.Text = "FormFriend";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormFriend_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonOpen;
        private System.Windows.Forms.Button buttonAdd;
        private System.Windows.Forms.Button buttonAddConfirmAgree;
        private System.Windows.Forms.Button buttonDel;
        private System.Windows.Forms.Button buttonNewStrangers;
        private System.Windows.Forms.Button buttonSearch;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxParam1;
        private System.Windows.Forms.TextBox textBoxParam2;
        private System.Windows.Forms.TextBox textBoxOutput;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxParam3;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button buttonExit;
        private System.Windows.Forms.Button buttonLocal;
    }
}