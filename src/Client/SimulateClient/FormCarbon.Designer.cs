namespace SimulateClient
{
    partial class FormCarbon
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
            this.textBoxShow = new System.Windows.Forms.TextBox();
            this.timerWait = new System.Windows.Forms.Timer(this.components);
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.ExitInstanceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ReviveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // textBoxShow
            // 
            this.textBoxShow.Location = new System.Drawing.Point(12, 40);
            this.textBoxShow.Multiline = true;
            this.textBoxShow.Name = "textBoxShow";
            this.textBoxShow.Size = new System.Drawing.Size(338, 185);
            this.textBoxShow.TabIndex = 1;
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(448, 25);
            this.menuStrip1.TabIndex = 2;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ExitInstanceToolStripMenuItem,
            this.ReviveToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(44, 21);
            this.toolStripMenuItem1.Text = "操作";
            // 
            // ExitInstanceToolStripMenuItem
            // 
            this.ExitInstanceToolStripMenuItem.Name = "ExitInstanceToolStripMenuItem";
            this.ExitInstanceToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.ExitInstanceToolStripMenuItem.Text = "退出";
            this.ExitInstanceToolStripMenuItem.Click += new System.EventHandler(this.ExitInstanceToolStripMenuItem_Click);
            // 
            // ReviveToolStripMenuItem
            // 
            this.ReviveToolStripMenuItem.Name = "ReviveToolStripMenuItem";
            this.ReviveToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.ReviveToolStripMenuItem.Text = "复活";
            this.ReviveToolStripMenuItem.Click += new System.EventHandler(this.ReviveToolStripMenuItem_Click);
            // 
            // FormCarbon
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(448, 251);
            this.Controls.Add(this.textBoxShow);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "FormCarbon";
            this.Text = "副本";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormCarbon_FormClosed);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxShow;
        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem ExitInstanceToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ReviveToolStripMenuItem;
    }
}