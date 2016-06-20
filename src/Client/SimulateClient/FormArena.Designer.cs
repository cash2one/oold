namespace SimulateClient
{
    partial class FormArena
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
            this.textBoxNotification = new System.Windows.Forms.TextBox();
            this.textChallengeeType = new System.Windows.Forms.TextBox();
            this.buttonChallenge = new System.Windows.Forms.Button();
            this.buttonExit = new System.Windows.Forms.Button();
            this.timerWait = new System.Windows.Forms.Timer(this.components);
            this.buttonGetArenaData = new System.Windows.Forms.Button();
            this.buttonRefreshChallengees = new System.Windows.Forms.Button();
            this.buttonChallengeFinish = new System.Windows.Forms.Button();
            this.textBoxChallengeResult = new System.Windows.Forms.TextBox();
            this.textBoxParam = new System.Windows.Forms.TextBox();
            this.buttonPurchaseTicket = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBoxNotification
            // 
            this.textBoxNotification.Location = new System.Drawing.Point(12, 101);
            this.textBoxNotification.Multiline = true;
            this.textBoxNotification.Name = "textBoxNotification";
            this.textBoxNotification.Size = new System.Drawing.Size(514, 189);
            this.textBoxNotification.TabIndex = 1;
            this.textBoxNotification.TextChanged += new System.EventHandler(this.textBoxNotification_TextChanged);
            // 
            // textChallengeeType
            // 
            this.textChallengeeType.Location = new System.Drawing.Point(100, 34);
            this.textChallengeeType.Name = "textChallengeeType";
            this.textChallengeeType.Size = new System.Drawing.Size(75, 21);
            this.textChallengeeType.TabIndex = 0;
            this.textChallengeeType.TextChanged += new System.EventHandler(this.textChallengeeIndex_TextChanged);
            // 
            // buttonChallenge
            // 
            this.buttonChallenge.Location = new System.Drawing.Point(13, 33);
            this.buttonChallenge.Name = "buttonChallenge";
            this.buttonChallenge.Size = new System.Drawing.Size(75, 23);
            this.buttonChallenge.TabIndex = 5;
            this.buttonChallenge.Text = "挑战";
            this.buttonChallenge.UseVisualStyleBackColor = true;
            this.buttonChallenge.Click += new System.EventHandler(this.buttonChallenge_Click);
            // 
            // buttonExit
            // 
            this.buttonExit.Location = new System.Drawing.Point(550, 267);
            this.buttonExit.Name = "buttonExit";
            this.buttonExit.Size = new System.Drawing.Size(75, 23);
            this.buttonExit.TabIndex = 6;
            this.buttonExit.Text = "退出";
            this.buttonExit.UseVisualStyleBackColor = true;
            this.buttonExit.Click += new System.EventHandler(this.buttonExit_Click);
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // buttonGetArenaData
            // 
            this.buttonGetArenaData.Location = new System.Drawing.Point(13, 3);
            this.buttonGetArenaData.Name = "buttonGetArenaData";
            this.buttonGetArenaData.Size = new System.Drawing.Size(75, 23);
            this.buttonGetArenaData.TabIndex = 7;
            this.buttonGetArenaData.Text = "竞技场";
            this.buttonGetArenaData.UseVisualStyleBackColor = true;
            this.buttonGetArenaData.Click += new System.EventHandler(this.buttonGetArenaData_Click);
            // 
            // buttonRefreshChallengees
            // 
            this.buttonRefreshChallengees.Location = new System.Drawing.Point(100, 3);
            this.buttonRefreshChallengees.Name = "buttonRefreshChallengees";
            this.buttonRefreshChallengees.Size = new System.Drawing.Size(75, 23);
            this.buttonRefreshChallengees.TabIndex = 8;
            this.buttonRefreshChallengees.Text = "换一批";
            this.buttonRefreshChallengees.UseVisualStyleBackColor = true;
            this.buttonRefreshChallengees.Click += new System.EventHandler(this.buttonRefreshChallengees_Click);
            // 
            // buttonChallengeFinish
            // 
            this.buttonChallengeFinish.Location = new System.Drawing.Point(186, 3);
            this.buttonChallengeFinish.Name = "buttonChallengeFinish";
            this.buttonChallengeFinish.Size = new System.Drawing.Size(75, 23);
            this.buttonChallengeFinish.TabIndex = 9;
            this.buttonChallengeFinish.Text = "挑战结束";
            this.buttonChallengeFinish.UseVisualStyleBackColor = true;
            this.buttonChallengeFinish.Click += new System.EventHandler(this.buttonChallengeFinish_Click);
            // 
            // textBoxChallengeResult
            // 
            this.textBoxChallengeResult.Location = new System.Drawing.Point(268, 3);
            this.textBoxChallengeResult.Name = "textBoxChallengeResult";
            this.textBoxChallengeResult.Size = new System.Drawing.Size(43, 21);
            this.textBoxChallengeResult.TabIndex = 10;
            this.textBoxChallengeResult.TextChanged += new System.EventHandler(this.textBoxChallengeResult_TextChanged);
            // 
            // textBoxParam
            // 
            this.textBoxParam.Location = new System.Drawing.Point(182, 33);
            this.textBoxParam.Name = "textBoxParam";
            this.textBoxParam.Size = new System.Drawing.Size(79, 21);
            this.textBoxParam.TabIndex = 11;
            this.textBoxParam.TextChanged += new System.EventHandler(this.textBoxRecordID_TextChanged);
            // 
            // buttonPurchaseTicket
            // 
            this.buttonPurchaseTicket.Location = new System.Drawing.Point(13, 63);
            this.buttonPurchaseTicket.Name = "buttonPurchaseTicket";
            this.buttonPurchaseTicket.Size = new System.Drawing.Size(75, 23);
            this.buttonPurchaseTicket.TabIndex = 12;
            this.buttonPurchaseTicket.Text = "购买入场券";
            this.buttonPurchaseTicket.UseVisualStyleBackColor = true;
            this.buttonPurchaseTicket.Click += new System.EventHandler(this.buttonPurchaseTicket_Click);
            // 
            // FormArena
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(661, 302);
            this.Controls.Add(this.buttonPurchaseTicket);
            this.Controls.Add(this.textBoxParam);
            this.Controls.Add(this.textBoxChallengeResult);
            this.Controls.Add(this.buttonChallengeFinish);
            this.Controls.Add(this.buttonRefreshChallengees);
            this.Controls.Add(this.buttonGetArenaData);
            this.Controls.Add(this.buttonExit);
            this.Controls.Add(this.buttonChallenge);
            this.Controls.Add(this.textBoxNotification);
            this.Controls.Add(this.textChallengeeType);
            this.Name = "FormArena";
            this.Text = "FormArena";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxNotification;
        private System.Windows.Forms.TextBox textChallengeeType;
        private System.Windows.Forms.Button buttonChallenge;
        private System.Windows.Forms.Button buttonExit;
        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.Button buttonGetArenaData;
        private System.Windows.Forms.Button buttonRefreshChallengees;
        private System.Windows.Forms.Button buttonChallengeFinish;
        private System.Windows.Forms.TextBox textBoxChallengeResult;
        private System.Windows.Forms.TextBox textBoxParam;
        private System.Windows.Forms.Button buttonPurchaseTicket;
    }
}