namespace SimulateClient
{
    partial class FormCreateRole
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
            this.btnCreateRole = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.gulandaishang = new System.Windows.Forms.RadioButton();
            this.keleijiang = new System.Windows.Forms.RadioButton();
            this.zJiang = new System.Windows.Forms.RadioButton();
            this.textBoxName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.cancel = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.timerWait = new System.Windows.Forms.Timer(this.components);
            this.textBoxTestShow = new System.Windows.Forms.TextBox();
            this.btnGetName = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnCreateRole
            // 
            this.btnCreateRole.Location = new System.Drawing.Point(246, 191);
            this.btnCreateRole.Name = "btnCreateRole";
            this.btnCreateRole.Size = new System.Drawing.Size(75, 23);
            this.btnCreateRole.TabIndex = 0;
            this.btnCreateRole.Text = "创建角色";
            this.btnCreateRole.UseVisualStyleBackColor = true;
            this.btnCreateRole.Click += new System.EventHandler(this.btnCreateRole_Click);
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.gulandaishang);
            this.panel1.Controls.Add(this.keleijiang);
            this.panel1.Controls.Add(this.zJiang);
            this.panel1.Location = new System.Drawing.Point(99, 64);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(129, 100);
            this.panel1.TabIndex = 1;
            // 
            // gulandaishang
            // 
            this.gulandaishang.AutoSize = true;
            this.gulandaishang.Location = new System.Drawing.Point(6, 62);
            this.gulandaishang.Name = "gulandaishang";
            this.gulandaishang.Size = new System.Drawing.Size(71, 16);
            this.gulandaishang.TabIndex = 2;
            this.gulandaishang.Text = "古兰戴萨";
            this.gulandaishang.UseVisualStyleBackColor = true;
            this.gulandaishang.CheckedChanged += new System.EventHandler(this.gulandaishang_CheckedChanged);
            // 
            // keleijiang
            // 
            this.keleijiang.AutoSize = true;
            this.keleijiang.Location = new System.Drawing.Point(6, 40);
            this.keleijiang.Name = "keleijiang";
            this.keleijiang.Size = new System.Drawing.Size(59, 16);
            this.keleijiang.TabIndex = 1;
            this.keleijiang.Text = "克蕾酱";
            this.keleijiang.UseVisualStyleBackColor = true;
            this.keleijiang.CheckedChanged += new System.EventHandler(this.keleijiang_CheckedChanged);
            // 
            // zJiang
            // 
            this.zJiang.AutoSize = true;
            this.zJiang.Checked = true;
            this.zJiang.Location = new System.Drawing.Point(6, 18);
            this.zJiang.Name = "zJiang";
            this.zJiang.Size = new System.Drawing.Size(41, 16);
            this.zJiang.TabIndex = 0;
            this.zJiang.TabStop = true;
            this.zJiang.Text = "z酱";
            this.zJiang.UseVisualStyleBackColor = true;
            this.zJiang.CheckedChanged += new System.EventHandler(this.zJiang_CheckedChanged);
            // 
            // textBoxName
            // 
            this.textBoxName.Location = new System.Drawing.Point(99, 24);
            this.textBoxName.Name = "textBoxName";
            this.textBoxName.Size = new System.Drawing.Size(129, 21);
            this.textBoxName.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(38, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 3;
            this.label1.Text = "昵称：";
            // 
            // cancel
            // 
            this.cancel.Location = new System.Drawing.Point(476, 220);
            this.cancel.Name = "cancel";
            this.cancel.Size = new System.Drawing.Size(75, 23);
            this.cancel.TabIndex = 4;
            this.cancel.Text = "返回";
            this.cancel.UseVisualStyleBackColor = true;
            this.cancel.Click += new System.EventHandler(this.cancel_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(40, 64);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 5;
            this.label2.Text = "职业：";
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // textBoxTestShow
            // 
            this.textBoxTestShow.Location = new System.Drawing.Point(335, 24);
            this.textBoxTestShow.Multiline = true;
            this.textBoxTestShow.Name = "textBoxTestShow";
            this.textBoxTestShow.Size = new System.Drawing.Size(216, 190);
            this.textBoxTestShow.TabIndex = 6;
            // 
            // btnGetName
            // 
            this.btnGetName.Location = new System.Drawing.Point(246, 22);
            this.btnGetName.Name = "btnGetName";
            this.btnGetName.Size = new System.Drawing.Size(75, 23);
            this.btnGetName.TabIndex = 7;
            this.btnGetName.Text = "换个昵称";
            this.btnGetName.UseVisualStyleBackColor = true;
            this.btnGetName.Click += new System.EventHandler(this.btnGetName_Click);
            // 
            // FormCreateRole
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(576, 252);
            this.Controls.Add(this.btnGetName);
            this.Controls.Add(this.textBoxTestShow);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.cancel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxName);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.btnCreateRole);
            this.Name = "FormCreateRole";
            this.Text = "创建角色";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormCreateRole_FormClosed);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnCreateRole;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.RadioButton zJiang;
        private System.Windows.Forms.RadioButton gulandaishang;
        private System.Windows.Forms.RadioButton keleijiang;
        private System.Windows.Forms.TextBox textBoxName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button cancel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.TextBox textBoxTestShow;
        private System.Windows.Forms.Button btnGetName;
    }
}