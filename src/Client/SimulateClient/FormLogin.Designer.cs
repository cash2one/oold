namespace SimulateClient
{
    partial class FormLogin
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
            this.buttonLogin = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.timerWait = new System.Windows.Forms.Timer(this.components);
            this.labelWait = new System.Windows.Forms.Label();
            this.textBoxAccount = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxPassword = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxIp = new System.Windows.Forms.TextBox();
            this.textZone = new System.Windows.Forms.TextBox();
            this.buttonFastLogin = new System.Windows.Forms.Button();
            this.buttonFastRegister = new System.Windows.Forms.Button();
            this.normalRegister = new System.Windows.Forms.Button();
            this.textPort = new System.Windows.Forms.TextBox();
            this.comboBoxServer = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.buttonToken = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // buttonLogin
            // 
            this.buttonLogin.Location = new System.Drawing.Point(35, 161);
            this.buttonLogin.Name = "buttonLogin";
            this.buttonLogin.Size = new System.Drawing.Size(75, 23);
            this.buttonLogin.TabIndex = 0;
            this.buttonLogin.Text = "登录";
            this.buttonLogin.UseVisualStyleBackColor = true;
            this.buttonLogin.Click += new System.EventHandler(this.buttonLogin_Click);
            // 
            // buttonCancel
            // 
            this.buttonCancel.Location = new System.Drawing.Point(198, 135);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 1;
            this.buttonCancel.Text = "退出";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Visible = false;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // labelWait
            // 
            this.labelWait.AutoSize = true;
            this.labelWait.Location = new System.Drawing.Point(90, 135);
            this.labelWait.Name = "labelWait";
            this.labelWait.Size = new System.Drawing.Size(41, 12);
            this.labelWait.TabIndex = 2;
            this.labelWait.Text = "☀☀☀";
            // 
            // textBoxAccount
            // 
            this.textBoxAccount.Location = new System.Drawing.Point(77, 25);
            this.textBoxAccount.Name = "textBoxAccount";
            this.textBoxAccount.Size = new System.Drawing.Size(174, 21);
            this.textBoxAccount.TabIndex = 3;
            this.textBoxAccount.Text = "test_1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(42, 34);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(29, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "账号";
            // 
            // textBoxPassword
            // 
            this.textBoxPassword.Location = new System.Drawing.Point(77, 52);
            this.textBoxPassword.Name = "textBoxPassword";
            this.textBoxPassword.PasswordChar = '*';
            this.textBoxPassword.Size = new System.Drawing.Size(174, 21);
            this.textBoxPassword.TabIndex = 3;
            this.textBoxPassword.Text = "123456";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(42, 61);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "密码";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(33, 84);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "服务器";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(169, 109);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 12);
            this.label4.TabIndex = 4;
            this.label4.Text = "端口";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(42, 233);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 12);
            this.label5.TabIndex = 4;
            this.label5.Text = "游戏区";
            this.label5.Visible = false;
            // 
            // textBoxIp
            // 
            this.textBoxIp.Location = new System.Drawing.Point(77, 105);
            this.textBoxIp.Name = "textBoxIp";
            this.textBoxIp.Size = new System.Drawing.Size(86, 21);
            this.textBoxIp.TabIndex = 5;
            this.textBoxIp.Text = "192.168.2.37";
            this.textBoxIp.TextChanged += new System.EventHandler(this.textBoxIp_TextChanged);
            // 
            // textZone
            // 
            this.textZone.Location = new System.Drawing.Point(92, 233);
            this.textZone.Name = "textZone";
            this.textZone.Size = new System.Drawing.Size(86, 21);
            this.textZone.TabIndex = 6;
            this.textZone.Text = "9000";
            this.textZone.Visible = false;
            // 
            // buttonFastLogin
            // 
            this.buttonFastLogin.Location = new System.Drawing.Point(117, 161);
            this.buttonFastLogin.Name = "buttonFastLogin";
            this.buttonFastLogin.Size = new System.Drawing.Size(75, 23);
            this.buttonFastLogin.TabIndex = 7;
            this.buttonFastLogin.Text = "快速登录";
            this.buttonFastLogin.UseVisualStyleBackColor = true;
            this.buttonFastLogin.Click += new System.EventHandler(this.buttonFastLogin_Click);
            // 
            // buttonFastRegister
            // 
            this.buttonFastRegister.Location = new System.Drawing.Point(200, 219);
            this.buttonFastRegister.Name = "buttonFastRegister";
            this.buttonFastRegister.Size = new System.Drawing.Size(75, 23);
            this.buttonFastRegister.TabIndex = 8;
            this.buttonFastRegister.Text = "快速注册";
            this.buttonFastRegister.UseVisualStyleBackColor = true;
            this.buttonFastRegister.Visible = false;
            this.buttonFastRegister.Click += new System.EventHandler(this.buttonFastRegister_Click);
            // 
            // normalRegister
            // 
            this.normalRegister.Location = new System.Drawing.Point(198, 159);
            this.normalRegister.Name = "normalRegister";
            this.normalRegister.Size = new System.Drawing.Size(75, 23);
            this.normalRegister.TabIndex = 9;
            this.normalRegister.Text = "注册";
            this.normalRegister.UseVisualStyleBackColor = true;
            this.normalRegister.Click += new System.EventHandler(this.normalRegister_Click);
            // 
            // textPort
            // 
            this.textPort.Location = new System.Drawing.Point(200, 103);
            this.textPort.Name = "textPort";
            this.textPort.Size = new System.Drawing.Size(49, 21);
            this.textPort.TabIndex = 6;
            this.textPort.Text = "9000";
            // 
            // comboBoxServer
            // 
            this.comboBoxServer.FormattingEnabled = true;
            this.comboBoxServer.Items.AddRange(new object[] {
            "外网正式服",
            "公共测试服",
            "公共测试服_zm",
            "dev_mzj",
            "dev_zp",
            "dev_zp_debug",
            "dev_zm",
            "dev_bj",
            "dev_test",
            "dev_bj_linux"});
            this.comboBoxServer.Location = new System.Drawing.Point(78, 79);
            this.comboBoxServer.Name = "comboBoxServer";
            this.comboBoxServer.Size = new System.Drawing.Size(171, 20);
            this.comboBoxServer.TabIndex = 10;
            this.comboBoxServer.Tag = "";
            this.comboBoxServer.SelectedIndexChanged += new System.EventHandler(this.comboBoxServer_SelectedIndexChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(33, 85);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(41, 12);
            this.label6.TabIndex = 4;
            this.label6.Text = "服务器";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(53, 110);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(17, 12);
            this.label7.TabIndex = 4;
            this.label7.Text = "IP";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(198, 190);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 11;
            this.button1.Text = "快速选角";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // buttonToken
            // 
            this.buttonToken.Location = new System.Drawing.Point(117, 190);
            this.buttonToken.Name = "buttonToken";
            this.buttonToken.Size = new System.Drawing.Size(75, 23);
            this.buttonToken.TabIndex = 0;
            this.buttonToken.Text = "Token登陆";
            this.buttonToken.UseVisualStyleBackColor = true;
            this.buttonToken.Click += new System.EventHandler(this.buttonToken_Click);
            // 
            // FormLogin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(333, 266);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.comboBoxServer);
            this.Controls.Add(this.normalRegister);
            this.Controls.Add(this.buttonFastRegister);
            this.Controls.Add(this.buttonFastLogin);
            this.Controls.Add(this.textPort);
            this.Controls.Add(this.textZone);
            this.Controls.Add(this.textBoxIp);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxPassword);
            this.Controls.Add(this.textBoxAccount);
            this.Controls.Add(this.labelWait);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonToken);
            this.Controls.Add(this.buttonLogin);
            this.Name = "FormLogin";
            this.Text = "登录";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonLogin;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.Label labelWait;
        private System.Windows.Forms.TextBox textBoxAccount;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxPassword;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxIp;
        private System.Windows.Forms.TextBox textZone;
        private System.Windows.Forms.Button buttonFastLogin;
        private System.Windows.Forms.Button buttonFastRegister;
        private System.Windows.Forms.Button normalRegister;
        private System.Windows.Forms.TextBox textPort;
        private System.Windows.Forms.ComboBox comboBoxServer;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button buttonToken;
    }
}
