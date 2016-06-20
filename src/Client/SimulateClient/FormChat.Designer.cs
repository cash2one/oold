namespace SimulateClient
{
    partial class FormChat
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
            this.buttonChatExit = new System.Windows.Forms.Button();
            this.textBoxChatContent = new System.Windows.Forms.TextBox();
            this.textBoxPrivateChatReceiverAccountID = new System.Windows.Forms.TextBox();
            this.textBoxChatInput = new System.Windows.Forms.TextBox();
            this.comboBoxChannel = new System.Windows.Forms.ComboBox();
            this.buttonSend = new System.Windows.Forms.Button();
            this.textBoxZoneID = new System.Windows.Forms.TextBox();
            this.textBoxRoleIndex = new System.Windows.Forms.TextBox();
            this.textBoxEquipID = new System.Windows.Forms.TextBox();
            this.textBoxBagIndex = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // buttonChatExit
            // 
            this.buttonChatExit.Location = new System.Drawing.Point(401, 227);
            this.buttonChatExit.Name = "buttonChatExit";
            this.buttonChatExit.Size = new System.Drawing.Size(75, 23);
            this.buttonChatExit.TabIndex = 0;
            this.buttonChatExit.Text = "退出";
            this.buttonChatExit.UseVisualStyleBackColor = true;
            this.buttonChatExit.Click += new System.EventHandler(this.buttonChatExit_Click);
            // 
            // textBoxChatContent
            // 
            this.textBoxChatContent.Location = new System.Drawing.Point(11, 107);
            this.textBoxChatContent.Multiline = true;
            this.textBoxChatContent.Name = "textBoxChatContent";
            this.textBoxChatContent.Size = new System.Drawing.Size(290, 143);
            this.textBoxChatContent.TabIndex = 2;
            this.textBoxChatContent.TextChanged += new System.EventHandler(this.textBoxChatContent_TextChanged);
            // 
            // textBoxPrivateChatReceiverAccountID
            // 
            this.textBoxPrivateChatReceiverAccountID.Location = new System.Drawing.Point(113, 12);
            this.textBoxPrivateChatReceiverAccountID.Name = "textBoxPrivateChatReceiverAccountID";
            this.textBoxPrivateChatReceiverAccountID.Size = new System.Drawing.Size(74, 21);
            this.textBoxPrivateChatReceiverAccountID.TabIndex = 3;
            this.textBoxPrivateChatReceiverAccountID.Text = "0";
            this.textBoxPrivateChatReceiverAccountID.TextChanged += new System.EventHandler(this.textBoxPrivateChatRoleID_TextChanged);
            // 
            // textBoxChatInput
            // 
            this.textBoxChatInput.Location = new System.Drawing.Point(11, 46);
            this.textBoxChatInput.Multiline = true;
            this.textBoxChatInput.Name = "textBoxChatInput";
            this.textBoxChatInput.Size = new System.Drawing.Size(288, 20);
            this.textBoxChatInput.TabIndex = 5;
            this.textBoxChatInput.TextChanged += new System.EventHandler(this.textBoxChatInput_TextChanged);
            // 
            // comboBoxChannel
            // 
            this.comboBoxChannel.FormattingEnabled = true;
            this.comboBoxChannel.Items.AddRange(new object[] {
            "私聊频道",
            "世界频道",
            "公告频道",
            "主城频道"});
            this.comboBoxChannel.Location = new System.Drawing.Point(15, 14);
            this.comboBoxChannel.Name = "comboBoxChannel";
            this.comboBoxChannel.Size = new System.Drawing.Size(92, 20);
            this.comboBoxChannel.TabIndex = 8;
            this.comboBoxChannel.SelectedIndexChanged += new System.EventHandler(this.comboBoxChannel_SelectedIndexChanged);
            // 
            // buttonSend
            // 
            this.buttonSend.Location = new System.Drawing.Point(315, 43);
            this.buttonSend.Name = "buttonSend";
            this.buttonSend.Size = new System.Drawing.Size(75, 23);
            this.buttonSend.TabIndex = 10;
            this.buttonSend.Text = "发送";
            this.buttonSend.UseVisualStyleBackColor = true;
            this.buttonSend.Click += new System.EventHandler(this.buttonSend_Click);
            // 
            // textBoxZoneID
            // 
            this.textBoxZoneID.Location = new System.Drawing.Point(193, 13);
            this.textBoxZoneID.Name = "textBoxZoneID";
            this.textBoxZoneID.Size = new System.Drawing.Size(60, 21);
            this.textBoxZoneID.TabIndex = 11;
            this.textBoxZoneID.TextChanged += new System.EventHandler(this.textBoxZoneID_TextChanged);
            // 
            // textBoxRoleIndex
            // 
            this.textBoxRoleIndex.Location = new System.Drawing.Point(259, 13);
            this.textBoxRoleIndex.Name = "textBoxRoleIndex";
            this.textBoxRoleIndex.Size = new System.Drawing.Size(54, 21);
            this.textBoxRoleIndex.TabIndex = 12;
            this.textBoxRoleIndex.TextChanged += new System.EventHandler(this.textBoxRoleIndex_TextChanged);
            // 
            // textBoxEquipID
            // 
            this.textBoxEquipID.Location = new System.Drawing.Point(382, 12);
            this.textBoxEquipID.Name = "textBoxEquipID";
            this.textBoxEquipID.Size = new System.Drawing.Size(59, 21);
            this.textBoxEquipID.TabIndex = 13;
            this.textBoxEquipID.TextChanged += new System.EventHandler(this.textBoxEquipID_TextChanged);
            // 
            // textBoxBagIndex
            // 
            this.textBoxBagIndex.Location = new System.Drawing.Point(319, 12);
            this.textBoxBagIndex.Name = "textBoxBagIndex";
            this.textBoxBagIndex.Size = new System.Drawing.Size(57, 21);
            this.textBoxBagIndex.TabIndex = 14;
            this.textBoxBagIndex.TextChanged += new System.EventHandler(this.textBoxBagIndex_TextChanged);
            // 
            // FormChat
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(496, 262);
            this.Controls.Add(this.textBoxBagIndex);
            this.Controls.Add(this.textBoxEquipID);
            this.Controls.Add(this.textBoxRoleIndex);
            this.Controls.Add(this.textBoxZoneID);
            this.Controls.Add(this.buttonSend);
            this.Controls.Add(this.comboBoxChannel);
            this.Controls.Add(this.textBoxChatInput);
            this.Controls.Add(this.textBoxPrivateChatReceiverAccountID);
            this.Controls.Add(this.textBoxChatContent);
            this.Controls.Add(this.buttonChatExit);
            this.Name = "FormChat";
            this.Text = "FormChat";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.Button buttonChatExit;
        private System.Windows.Forms.TextBox textBoxChatContent;
        private System.Windows.Forms.TextBox textBoxPrivateChatReceiverAccountID;
        private System.Windows.Forms.TextBox textBoxChatInput;
        private System.Windows.Forms.ComboBox comboBoxChannel;
        private System.Windows.Forms.Button buttonSend;
        private System.Windows.Forms.TextBox textBoxZoneID;
        private System.Windows.Forms.TextBox textBoxRoleIndex;
        private System.Windows.Forms.TextBox textBoxBagIndex;
        private System.Windows.Forms.TextBox textBoxEquipID;

    }
}