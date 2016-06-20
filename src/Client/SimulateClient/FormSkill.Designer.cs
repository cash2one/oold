namespace SimulateClient
{
    partial class FormSkill
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
            this.learnSkillIDInputTextBox = new System.Windows.Forms.TextBox();
            this.labelSkillIDtip = new System.Windows.Forms.Label();
            this.upgradeSkillIDInputTextBox = new System.Windows.Forms.TextBox();
            this.skillLogTextBox = new System.Windows.Forms.TextBox();
            this.timerWait = new System.Windows.Forms.Timer(this.components);
            this.buttonLearnSkill = new System.Windows.Forms.Button();
            this.buttonUpgradeSkill = new System.Windows.Forms.Button();
            this.buttonSetSkillButton = new System.Windows.Forms.Button();
            this.textBoxButtonSkillTPID = new System.Windows.Forms.TextBox();
            this.textBoxButtonIndex = new System.Windows.Forms.TextBox();
            this.buttonExitSkillSystem = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // learnSkillIDInputTextBox
            // 
            this.learnSkillIDInputTextBox.Location = new System.Drawing.Point(86, 38);
            this.learnSkillIDInputTextBox.Name = "learnSkillIDInputTextBox";
            this.learnSkillIDInputTextBox.Size = new System.Drawing.Size(65, 21);
            this.learnSkillIDInputTextBox.TabIndex = 1;
            this.learnSkillIDInputTextBox.TextChanged += new System.EventHandler(this.learnSkillTextBox_TextChanged);
            // 
            // labelSkillIDtip
            // 
            this.labelSkillIDtip.AutoSize = true;
            this.labelSkillIDtip.Location = new System.Drawing.Point(98, 13);
            this.labelSkillIDtip.Name = "labelSkillIDtip";
            this.labelSkillIDtip.Size = new System.Drawing.Size(41, 12);
            this.labelSkillIDtip.TabIndex = 2;
            this.labelSkillIDtip.Text = "技能ID";
            // 
            // upgradeSkillIDInputTextBox
            // 
            this.upgradeSkillIDInputTextBox.Location = new System.Drawing.Point(86, 70);
            this.upgradeSkillIDInputTextBox.Name = "upgradeSkillIDInputTextBox";
            this.upgradeSkillIDInputTextBox.Size = new System.Drawing.Size(65, 21);
            this.upgradeSkillIDInputTextBox.TabIndex = 4;
            this.upgradeSkillIDInputTextBox.TextChanged += new System.EventHandler(this.upgradeSkillTextBox_TextChanged);
            // 
            // skillLogTextBox
            // 
            this.skillLogTextBox.Location = new System.Drawing.Point(157, 4);
            this.skillLogTextBox.Multiline = true;
            this.skillLogTextBox.Name = "skillLogTextBox";
            this.skillLogTextBox.Size = new System.Drawing.Size(264, 252);
            this.skillLogTextBox.TabIndex = 5;
            this.skillLogTextBox.TextChanged += new System.EventHandler(this.skillLogTextBox_TextChanged);
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // buttonLearnSkill
            // 
            this.buttonLearnSkill.Location = new System.Drawing.Point(1, 37);
            this.buttonLearnSkill.Name = "buttonLearnSkill";
            this.buttonLearnSkill.Size = new System.Drawing.Size(75, 23);
            this.buttonLearnSkill.TabIndex = 6;
            this.buttonLearnSkill.Text = "学习技能";
            this.buttonLearnSkill.UseVisualStyleBackColor = true;
            this.buttonLearnSkill.Click += new System.EventHandler(this.buttonLearnSkill_Click);
            // 
            // buttonUpgradeSkill
            // 
            this.buttonUpgradeSkill.Location = new System.Drawing.Point(1, 69);
            this.buttonUpgradeSkill.Name = "buttonUpgradeSkill";
            this.buttonUpgradeSkill.Size = new System.Drawing.Size(75, 23);
            this.buttonUpgradeSkill.TabIndex = 7;
            this.buttonUpgradeSkill.Text = "升级技能";
            this.buttonUpgradeSkill.UseVisualStyleBackColor = true;
            this.buttonUpgradeSkill.Click += new System.EventHandler(this.buttonUpgradeSkill_Click);
            // 
            // buttonSetSkillButton
            // 
            this.buttonSetSkillButton.Location = new System.Drawing.Point(1, 99);
            this.buttonSetSkillButton.Name = "buttonSetSkillButton";
            this.buttonSetSkillButton.Size = new System.Drawing.Size(75, 23);
            this.buttonSetSkillButton.TabIndex = 8;
            this.buttonSetSkillButton.Text = "设置技能";
            this.buttonSetSkillButton.UseVisualStyleBackColor = true;
            this.buttonSetSkillButton.Click += new System.EventHandler(this.buttonSetSkillButton_Click);
            // 
            // textBoxButtonSkillTPID
            // 
            this.textBoxButtonSkillTPID.Location = new System.Drawing.Point(86, 98);
            this.textBoxButtonSkillTPID.Name = "textBoxButtonSkillTPID";
            this.textBoxButtonSkillTPID.Size = new System.Drawing.Size(28, 21);
            this.textBoxButtonSkillTPID.TabIndex = 9;
            this.textBoxButtonSkillTPID.TextChanged += new System.EventHandler(this.textBoxButtonSkillTPID_TextChanged);
            // 
            // textBoxButtonIndex
            // 
            this.textBoxButtonIndex.Location = new System.Drawing.Point(121, 99);
            this.textBoxButtonIndex.Name = "textBoxButtonIndex";
            this.textBoxButtonIndex.Size = new System.Drawing.Size(30, 21);
            this.textBoxButtonIndex.TabIndex = 10;
            this.textBoxButtonIndex.TextChanged += new System.EventHandler(this.textBoxButtonIndex_TextChanged);
            // 
            // buttonExitSkillSystem
            // 
            this.buttonExitSkillSystem.Location = new System.Drawing.Point(1, 138);
            this.buttonExitSkillSystem.Name = "buttonExitSkillSystem";
            this.buttonExitSkillSystem.Size = new System.Drawing.Size(75, 23);
            this.buttonExitSkillSystem.TabIndex = 11;
            this.buttonExitSkillSystem.Text = "退出";
            this.buttonExitSkillSystem.UseVisualStyleBackColor = true;
            this.buttonExitSkillSystem.Click += new System.EventHandler(this.buttonExitSkillSystem_Click);
            // 
            // FormSkill
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(432, 268);
            this.Controls.Add(this.buttonExitSkillSystem);
            this.Controls.Add(this.textBoxButtonIndex);
            this.Controls.Add(this.textBoxButtonSkillTPID);
            this.Controls.Add(this.buttonSetSkillButton);
            this.Controls.Add(this.buttonUpgradeSkill);
            this.Controls.Add(this.buttonLearnSkill);
            this.Controls.Add(this.skillLogTextBox);
            this.Controls.Add(this.upgradeSkillIDInputTextBox);
            this.Controls.Add(this.labelSkillIDtip);
            this.Controls.Add(this.learnSkillIDInputTextBox);
            this.Name = "FormSkill";
            this.Text = "技能";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox learnSkillIDInputTextBox;
        private System.Windows.Forms.Label labelSkillIDtip;
        private System.Windows.Forms.TextBox upgradeSkillIDInputTextBox;
        private System.Windows.Forms.TextBox skillLogTextBox;
        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.Button buttonLearnSkill;
        private System.Windows.Forms.Button buttonUpgradeSkill;
        private System.Windows.Forms.Button buttonSetSkillButton;
        private System.Windows.Forms.TextBox textBoxButtonSkillTPID;
        private System.Windows.Forms.TextBox textBoxButtonIndex;
        private System.Windows.Forms.Button buttonExitSkillSystem;
    }
}