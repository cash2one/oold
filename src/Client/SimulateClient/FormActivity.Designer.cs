namespace SimulateClient
{
    partial class FormActivity
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
            this.buttonExit = new System.Windows.Forms.Button();
            this.textBoxLog = new System.Windows.Forms.TextBox();
            this.buttonGetAttendenceData = new System.Windows.Forms.Button();
            this.buttonSignIn = new System.Windows.Forms.Button();
            this.buttonDrawCard = new System.Windows.Forms.Button();
            this.textBoxCardType = new System.Windows.Forms.TextBox();
            this.textBoxDrawTimes = new System.Windows.Forms.TextBox();
            this.buttonGetDrawCardInfo = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // buttonExit
            // 
            this.buttonExit.Location = new System.Drawing.Point(432, 269);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(75, 23);
            this.buttonExit.TabIndex = 0;
            this.buttonExit.Text = "退出";
            this.buttonExit.UseVisualStyleBackColor = true;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // textBoxLog
            // 
            this.textBoxLog.Location = new System.Drawing.Point(12, 12);
            this.textBoxLog.Multiline = true;
            this.textBoxLog.Name = "textBoxLog";
            this.textBoxLog.Size = new System.Drawing.Size(197, 280);
            this.textBoxLog.TabIndex = 1;
            // 
            // buttonGetAttendenceData
            // 
            this.buttonGetAttendenceData.Location = new System.Drawing.Point(216, 13);
            this.buttonGetAttendenceData.Name = "buttonGetAttendenceData";
            this.buttonGetAttendenceData.Size = new System.Drawing.Size(86, 23);
            this.buttonGetAttendenceData.TabIndex = 2;
            this.buttonGetAttendenceData.Text = "签到信息";
            this.buttonGetAttendenceData.UseVisualStyleBackColor = true;
            this.buttonGetAttendenceData.Click += new System.EventHandler(this.buttonGetAttendenceData_Click);
            // 
            // buttonSignIn
            // 
            this.buttonSignIn.Location = new System.Drawing.Point(216, 43);
            this.buttonSignIn.Name = "buttonSignIn";
            this.buttonSignIn.Size = new System.Drawing.Size(86, 23);
            this.buttonSignIn.TabIndex = 3;
            this.buttonSignIn.Text = "签到";
            this.buttonSignIn.UseVisualStyleBackColor = true;
            this.buttonSignIn.Click += new System.EventHandler(this.buttonSignIn_Click);
            // 
            // buttonDrawCard
            // 
            this.buttonDrawCard.Location = new System.Drawing.Point(216, 73);
            this.buttonDrawCard.Name = "buttonDrawCard";
            this.buttonDrawCard.Size = new System.Drawing.Size(86, 23);
            this.buttonDrawCard.TabIndex = 4;
            this.buttonDrawCard.Text = "抽卡";
            this.buttonDrawCard.UseVisualStyleBackColor = true;
            this.buttonDrawCard.Click += new System.EventHandler(this.buttonDrawCard_Click);
            // 
            // textBoxCardType
            // 
            this.textBoxCardType.Location = new System.Drawing.Point(309, 73);
            this.textBoxCardType.Name = "textBoxCardType";
            this.textBoxCardType.Size = new System.Drawing.Size(71, 21);
            this.textBoxCardType.TabIndex = 5;
            this.textBoxCardType.TextChanged += new System.EventHandler(this.textBoxCardType_TextChanged);
            // 
            // textBoxDrawTimes
            // 
            this.textBoxDrawTimes.Location = new System.Drawing.Point(386, 73);
            this.textBoxDrawTimes.Name = "textBoxDrawTimes";
            this.textBoxDrawTimes.Size = new System.Drawing.Size(71, 21);
            this.textBoxDrawTimes.TabIndex = 6;
            this.textBoxDrawTimes.TextChanged += new System.EventHandler(this.textBoxDrawTimes_TextChanged);
            // 
            // buttonGetDrawCardInfo
            // 
            this.buttonGetDrawCardInfo.Location = new System.Drawing.Point(216, 103);
            this.buttonGetDrawCardInfo.Name = "buttonGetDrawCardInfo";
            this.buttonGetDrawCardInfo.Size = new System.Drawing.Size(75, 23);
            this.buttonGetDrawCardInfo.TabIndex = 7;
            this.buttonGetDrawCardInfo.Text = "抽卡信息";
            this.buttonGetDrawCardInfo.UseVisualStyleBackColor = true;
            this.buttonGetDrawCardInfo.Click += new System.EventHandler(this.buttonGetDrawCardInfo_Click);
            // 
            // FormActivity
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(510, 304);
            this.Controls.Add(this.buttonGetDrawCardInfo);
            this.Controls.Add(this.textBoxDrawTimes);
            this.Controls.Add(this.textBoxCardType);
            this.Controls.Add(this.buttonDrawCard);
            this.Controls.Add(this.buttonSignIn);
            this.Controls.Add(this.buttonGetAttendenceData);
            this.Controls.Add(this.textBoxLog);
            this.Controls.Add(this.buttonExit);
            this.Name = "FormActivity";
            this.Text = "FormActivity";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.Button buttonExit;
        private System.Windows.Forms.TextBox textBoxLog;
        private System.Windows.Forms.Button buttonGetAttendenceData;
        private System.Windows.Forms.Button buttonSignIn;
        private System.Windows.Forms.Button buttonDrawCard;
        private System.Windows.Forms.TextBox textBoxCardType;
        private System.Windows.Forms.TextBox textBoxDrawTimes;
        private System.Windows.Forms.Button buttonGetDrawCardInfo;
    }
}