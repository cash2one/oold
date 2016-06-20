namespace SimulateClient
{
    partial class FormSelectZone
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
            this.comboBoxZone = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btnLogin = new System.Windows.Forms.Button();
            this.timerWait = new System.Windows.Forms.Timer(this.components);
            this.btnLogout = new System.Windows.Forms.Button();
            this.textPort = new System.Windows.Forms.TextBox();
            this.textBoxIp = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textZone = new System.Windows.Forms.TextBox();
            this.buttonToken = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // comboBoxZone
            // 
            this.comboBoxZone.FormattingEnabled = true;
            this.comboBoxZone.Items.AddRange(new object[] {
            "外网正式服",
            "公共测试服",
            "公共测试服_zm",
            "dev_mzj",
            "dev_zp",
            "dev_zp_debug",
            "dev_zm",
            "dev_bj",
            "dev_test"});
            this.comboBoxZone.Location = new System.Drawing.Point(90, 64);
            this.comboBoxZone.Name = "comboBoxZone";
            this.comboBoxZone.Size = new System.Drawing.Size(121, 20);
            this.comboBoxZone.TabIndex = 0;
            this.comboBoxZone.Text = "dev_zm";
            this.comboBoxZone.SelectedIndexChanged += new System.EventHandler(this.comboBoxZone_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(37, 67);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "服务器：";
            // 
            // btnLogin
            // 
            this.btnLogin.Location = new System.Drawing.Point(246, 64);
            this.btnLogin.Name = "btnLogin";
            this.btnLogin.Size = new System.Drawing.Size(75, 23);
            this.btnLogin.TabIndex = 2;
            this.btnLogin.Text = "登录";
            this.btnLogin.UseVisualStyleBackColor = true;
            this.btnLogin.Click += new System.EventHandler(this.btnLogin_Click);
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // btnLogout
            // 
            this.btnLogout.Location = new System.Drawing.Point(350, 12);
            this.btnLogout.Name = "btnLogout";
            this.btnLogout.Size = new System.Drawing.Size(75, 23);
            this.btnLogout.TabIndex = 3;
            this.btnLogout.Text = "注销";
            this.btnLogout.UseVisualStyleBackColor = true;
            this.btnLogout.Click += new System.EventHandler(this.btnLogout_Click);
            // 
            // textPort
            // 
            this.textPort.Location = new System.Drawing.Point(89, 113);
            this.textPort.Name = "textPort";
            this.textPort.Size = new System.Drawing.Size(49, 21);
            this.textPort.TabIndex = 10;
            this.textPort.Text = "9000";
            // 
            // textBoxIp
            // 
            this.textBoxIp.Location = new System.Drawing.Point(89, 90);
            this.textBoxIp.Name = "textBoxIp";
            this.textBoxIp.Size = new System.Drawing.Size(86, 21);
            this.textBoxIp.TabIndex = 9;
            this.textBoxIp.Text = "10.0.1.102";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(60, 95);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(29, 12);
            this.label7.TabIndex = 7;
            this.label7.Text = "IP：";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(48, 119);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 8;
            this.label4.Text = "端口：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(48, 140);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 8;
            this.label2.Text = "区号：";
            // 
            // textZone
            // 
            this.textZone.Location = new System.Drawing.Point(89, 134);
            this.textZone.Name = "textZone";
            this.textZone.Size = new System.Drawing.Size(49, 21);
            this.textZone.TabIndex = 10;
            this.textZone.Text = "22";
            // 
            // buttonToken
            // 
            this.buttonToken.Location = new System.Drawing.Point(246, 95);
            this.buttonToken.Name = "buttonToken";
            this.buttonToken.Size = new System.Drawing.Size(75, 23);
            this.buttonToken.TabIndex = 2;
            this.buttonToken.Text = "Token登录";
            this.buttonToken.UseVisualStyleBackColor = true;
            this.buttonToken.Click += new System.EventHandler(this.buttonToken_Click);
            // 
            // FormSelectZone
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(437, 178);
            this.Controls.Add(this.textZone);
            this.Controls.Add(this.textPort);
            this.Controls.Add(this.textBoxIp);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.btnLogout);
            this.Controls.Add(this.buttonToken);
            this.Controls.Add(this.btnLogin);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.comboBoxZone);
            this.Name = "FormSelectZone";
            this.Text = "FormSelectZone";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comboBoxZone;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnLogin;
        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.Button btnLogout;
        private System.Windows.Forms.TextBox textPort;
        private System.Windows.Forms.TextBox textBoxIp;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textZone;
        private System.Windows.Forms.Button buttonToken;
    }
}