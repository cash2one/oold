namespace SimulateClient
{
    partial class FormBag
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
            this.useItem = new System.Windows.Forms.Button();
            this.timerWait = new System.Windows.Forms.Timer(this.components);
            this.textBoxShow = new System.Windows.Forms.TextBox();
            this.textBoxID = new System.Windows.Forms.TextBox();
            this.textBoxType = new System.Windows.Forms.TextBox();
            this.textBoxCount = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.buttonSell = new System.Windows.Forms.Button();
            this.ExpandBagSize = new System.Windows.Forms.Button();
            this.btnGetBagData = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // useItem
            // 
            this.useItem.Location = new System.Drawing.Point(674, 13);
            this.useItem.Name = "useItem";
            this.useItem.Size = new System.Drawing.Size(75, 23);
            this.useItem.TabIndex = 0;
            this.useItem.Text = "使用";
            this.useItem.UseVisualStyleBackColor = true;
            this.useItem.Click += new System.EventHandler(this.useItem_Click);
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // textBoxShow
            // 
            this.textBoxShow.Location = new System.Drawing.Point(36, 12);
            this.textBoxShow.Multiline = true;
            this.textBoxShow.Name = "textBoxShow";
            this.textBoxShow.Size = new System.Drawing.Size(450, 405);
            this.textBoxShow.TabIndex = 1;
            // 
            // textBoxID
            // 
            this.textBoxID.Location = new System.Drawing.Point(552, 13);
            this.textBoxID.Name = "textBoxID";
            this.textBoxID.Size = new System.Drawing.Size(100, 21);
            this.textBoxID.TabIndex = 2;
            // 
            // textBoxType
            // 
            this.textBoxType.Location = new System.Drawing.Point(553, 40);
            this.textBoxType.Name = "textBoxType";
            this.textBoxType.Size = new System.Drawing.Size(100, 21);
            this.textBoxType.TabIndex = 2;
            // 
            // textBoxCount
            // 
            this.textBoxCount.Location = new System.Drawing.Point(552, 67);
            this.textBoxCount.Name = "textBoxCount";
            this.textBoxCount.Size = new System.Drawing.Size(100, 21);
            this.textBoxCount.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(493, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 12);
            this.label1.TabIndex = 3;
            this.label1.Text = "Index";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(492, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "type";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(492, 76);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(35, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "count";
            // 
            // buttonSell
            // 
            this.buttonSell.Location = new System.Drawing.Point(674, 42);
            this.buttonSell.Name = "buttonSell";
            this.buttonSell.Size = new System.Drawing.Size(75, 23);
            this.buttonSell.TabIndex = 0;
            this.buttonSell.Text = "出售";
            this.buttonSell.UseVisualStyleBackColor = true;
            this.buttonSell.Click += new System.EventHandler(this.sellItem_Click);
            // 
            // ExpandBagSize
            // 
            this.ExpandBagSize.Location = new System.Drawing.Point(674, 71);
            this.ExpandBagSize.Name = "ExpandBagSize";
            this.ExpandBagSize.Size = new System.Drawing.Size(75, 23);
            this.ExpandBagSize.TabIndex = 4;
            this.ExpandBagSize.Text = "购买格子";
            this.ExpandBagSize.UseVisualStyleBackColor = true;
            this.ExpandBagSize.Click += new System.EventHandler(this.ExpandBagSize_Click);
            // 
            // btnGetBagData
            // 
            this.btnGetBagData.Location = new System.Drawing.Point(674, 100);
            this.btnGetBagData.Name = "btnGetBagData";
            this.btnGetBagData.Size = new System.Drawing.Size(75, 23);
            this.btnGetBagData.TabIndex = 5;
            this.btnGetBagData.Text = "背包数据";
            this.btnGetBagData.UseVisualStyleBackColor = true;
            this.btnGetBagData.Click += new System.EventHandler(this.btnGetBagData_Click);
            // 
            // FormBag
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(772, 459);
            this.Controls.Add(this.btnGetBagData);
            this.Controls.Add(this.ExpandBagSize);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxCount);
            this.Controls.Add(this.textBoxType);
            this.Controls.Add(this.textBoxID);
            this.Controls.Add(this.textBoxShow);
            this.Controls.Add(this.buttonSell);
            this.Controls.Add(this.useItem);
            this.Name = "FormBag";
            this.Text = "背包";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormBag_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button useItem;
        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.TextBox textBoxShow;
        private System.Windows.Forms.TextBox textBoxID;
        private System.Windows.Forms.TextBox textBoxType;
        private System.Windows.Forms.TextBox textBoxCount;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button buttonSell;
        private System.Windows.Forms.Button ExpandBagSize;
        private System.Windows.Forms.Button btnGetBagData;
    }
}