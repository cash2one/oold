namespace SimulateClient
{
    partial class FormSelectRole
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
            this.createRole = new System.Windows.Forms.Button();
            this.textBoxTestShow = new System.Windows.Forms.TextBox();
            this.timerWait = new System.Windows.Forms.Timer(this.components);
            this.panelRole = new System.Windows.Forms.Panel();
            this.selectRole = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.btnDeleteRole = new System.Windows.Forms.Button();
            this.btnLogout = new System.Windows.Forms.Button();
            this.btnChangeServer = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // createRole
            // 
            this.createRole.Location = new System.Drawing.Point(323, 171);
            this.createRole.Name = "createRole";
            this.createRole.Size = new System.Drawing.Size(75, 23);
            this.createRole.TabIndex = 0;
            this.createRole.Text = "创建角色";
            this.createRole.UseVisualStyleBackColor = true;
            this.createRole.Click += new System.EventHandler(this.createRole_Click);
            // 
            // textBoxTestShow
            // 
            this.textBoxTestShow.Location = new System.Drawing.Point(235, 12);
            this.textBoxTestShow.Multiline = true;
            this.textBoxTestShow.Name = "textBoxTestShow";
            this.textBoxTestShow.Size = new System.Drawing.Size(252, 153);
            this.textBoxTestShow.TabIndex = 1;
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // panelRole
            // 
            this.panelRole.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelRole.Location = new System.Drawing.Point(55, 12);
            this.panelRole.Name = "panelRole";
            this.panelRole.Size = new System.Drawing.Size(149, 225);
            this.panelRole.TabIndex = 5;
            // 
            // selectRole
            // 
            this.selectRole.Location = new System.Drawing.Point(331, 213);
            this.selectRole.Name = "selectRole";
            this.selectRole.Size = new System.Drawing.Size(75, 23);
            this.selectRole.TabIndex = 6;
            this.selectRole.Text = "开始游戏";
            this.selectRole.UseVisualStyleBackColor = true;
            this.selectRole.Click += new System.EventHandler(this.selectRole_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 7;
            this.label1.Text = "角色：";
            // 
            // btnDeleteRole
            // 
            this.btnDeleteRole.Location = new System.Drawing.Point(235, 171);
            this.btnDeleteRole.Name = "btnDeleteRole";
            this.btnDeleteRole.Size = new System.Drawing.Size(75, 23);
            this.btnDeleteRole.TabIndex = 8;
            this.btnDeleteRole.Text = "删除角色";
            this.btnDeleteRole.UseVisualStyleBackColor = true;
            this.btnDeleteRole.Click += new System.EventHandler(this.btnDeleteRole_Click);
            // 
            // btnLogout
            // 
            this.btnLogout.Location = new System.Drawing.Point(235, 214);
            this.btnLogout.Name = "btnLogout";
            this.btnLogout.Size = new System.Drawing.Size(75, 23);
            this.btnLogout.TabIndex = 9;
            this.btnLogout.Text = "注销";
            this.btnLogout.UseVisualStyleBackColor = true;
            this.btnLogout.Click += new System.EventHandler(this.btnLogout_Click);
            // 
            // btnChangeServer
            // 
            this.btnChangeServer.Location = new System.Drawing.Point(412, 171);
            this.btnChangeServer.Name = "btnChangeServer";
            this.btnChangeServer.Size = new System.Drawing.Size(75, 23);
            this.btnChangeServer.TabIndex = 10;
            this.btnChangeServer.Text = "返回选服";
            this.btnChangeServer.UseVisualStyleBackColor = true;
            this.btnChangeServer.Click += new System.EventHandler(this.btnChangeServer_Click);
            // 
            // FormSelectRole
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(525, 260);
            this.Controls.Add(this.btnChangeServer);
            this.Controls.Add(this.btnLogout);
            this.Controls.Add(this.btnDeleteRole);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.selectRole);
            this.Controls.Add(this.panelRole);
            this.Controls.Add(this.textBoxTestShow);
            this.Controls.Add(this.createRole);
            this.Name = "FormSelectRole";
            this.Text = "选择角色";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.SelectRoleForm_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button createRole;
        private System.Windows.Forms.TextBox textBoxTestShow;
        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.Panel panelRole;
        private System.Windows.Forms.Button selectRole;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnDeleteRole;
        private System.Windows.Forms.Button btnLogout;
        private System.Windows.Forms.Button btnChangeServer;
    }
}