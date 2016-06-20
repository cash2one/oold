namespace SimulateClient
{
    partial class FormMain
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
            this.quitScene = new System.Windows.Forms.Button();
            this.btnEnterCarbon = new System.Windows.Forms.Button();
            this.skill = new System.Windows.Forms.Button();
            this.equip = new System.Windows.Forms.Button();
            this.pet = new System.Windows.Forms.Button();
            this.buttonChatSystem = new System.Windows.Forms.Button();
            this.Bag = new System.Windows.Forms.Button();
            this.buttonArena = new System.Windows.Forms.Button();
            this.buttonRankSystem = new System.Windows.Forms.Button();
            this.mail = new System.Windows.Forms.Button();
            this.buttonTask = new System.Windows.Forms.Button();
            this.reLogin = new System.Windows.Forms.Button();
            this.buttonShop = new System.Windows.Forms.Button();
            this.buttonActivity = new System.Windows.Forms.Button();
            this.buttonFriend = new System.Windows.Forms.Button();
            this.getRoleData = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // quitScene
            // 
            this.quitScene.Location = new System.Drawing.Point(472, 6);
            this.quitScene.Name = "quitScene";
            this.quitScene.Size = new System.Drawing.Size(75, 23);
            this.quitScene.TabIndex = 7;
            this.quitScene.Text = "退出场景";
            this.quitScene.UseVisualStyleBackColor = true;
            this.quitScene.Click += new System.EventHandler(this.quitScene_Click);
            // 
            // btnEnterCarbon
            // 
            this.btnEnterCarbon.Location = new System.Drawing.Point(472, 36);
            this.btnEnterCarbon.Name = "btnEnterCarbon";
            this.btnEnterCarbon.Size = new System.Drawing.Size(75, 23);
            this.btnEnterCarbon.TabIndex = 8;
            this.btnEnterCarbon.Text = "进入副本";
            this.btnEnterCarbon.UseVisualStyleBackColor = true;
            this.btnEnterCarbon.Click += new System.EventHandler(this.btnEnterCarbon_Click);
            // 
            // skill
            // 
            this.skill.Location = new System.Drawing.Point(472, 65);
            this.skill.Name = "skill";
            this.skill.Size = new System.Drawing.Size(75, 23);
            this.skill.TabIndex = 9;
            this.skill.Text = "技能";
            this.skill.UseVisualStyleBackColor = true;
            this.skill.Click += new System.EventHandler(this.skill_Click);
            // 
            // equip
            // 
            this.equip.Location = new System.Drawing.Point(472, 94);
            this.equip.Name = "equip";
            this.equip.Size = new System.Drawing.Size(75, 23);
            this.equip.TabIndex = 10;
            this.equip.Text = "装备";
            this.equip.UseVisualStyleBackColor = true;
            this.equip.Click += new System.EventHandler(this.equip_Click);
            // 
            // pet
            // 
            this.pet.Location = new System.Drawing.Point(472, 154);
            this.pet.Name = "pet";
            this.pet.Size = new System.Drawing.Size(75, 23);
            this.pet.TabIndex = 11;
            this.pet.Text = "伙伴";
            this.pet.UseVisualStyleBackColor = true;
            this.pet.Click += new System.EventHandler(this.pet_Click);
            // 
            // buttonChatSystem
            // 
            this.buttonChatSystem.Location = new System.Drawing.Point(472, 123);
            this.buttonChatSystem.Name = "buttonChatSystem";
            this.buttonChatSystem.Size = new System.Drawing.Size(75, 23);
            this.buttonChatSystem.TabIndex = 11;
            this.buttonChatSystem.Text = "聊天";
            this.buttonChatSystem.UseVisualStyleBackColor = true;
            this.buttonChatSystem.Click += new System.EventHandler(this.buttonChatSystem_Click);
            // 
            // Bag
            // 
            this.Bag.Location = new System.Drawing.Point(472, 184);
            this.Bag.Name = "Bag";
            this.Bag.Size = new System.Drawing.Size(75, 23);
            this.Bag.TabIndex = 12;
            this.Bag.Text = "背包";
            this.Bag.UseVisualStyleBackColor = true;
            this.Bag.Click += new System.EventHandler(this.Bag_Click);
            // 
            // buttonArena
            // 
            this.buttonArena.Location = new System.Drawing.Point(472, 214);
            this.buttonArena.Name = "buttonArena";
            this.buttonArena.Size = new System.Drawing.Size(75, 23);
            this.buttonArena.TabIndex = 13;
            this.buttonArena.Text = "竞技场";
            this.buttonArena.UseVisualStyleBackColor = true;
            this.buttonArena.Click += new System.EventHandler(this.buttonArena_Click);
            // 
            // buttonRankSystem
            // 
            this.buttonRankSystem.Location = new System.Drawing.Point(472, 244);
            this.buttonRankSystem.Name = "buttonRankSystem";
            this.buttonRankSystem.Size = new System.Drawing.Size(75, 23);
            this.buttonRankSystem.TabIndex = 14;
            this.buttonRankSystem.Text = "排名";
            this.buttonRankSystem.UseVisualStyleBackColor = true;
            this.buttonRankSystem.Click += new System.EventHandler(this.buttonRankSystem_Click);
            // 
            // mail
            // 
            this.mail.Location = new System.Drawing.Point(472, 273);
            this.mail.Name = "mail";
            this.mail.Size = new System.Drawing.Size(75, 23);
            this.mail.TabIndex = 15;
            this.mail.Text = "邮件";
            this.mail.UseVisualStyleBackColor = true;
            this.mail.Click += new System.EventHandler(this.mail_Click);
            // 
            // buttonTask
            // 
            this.buttonTask.Location = new System.Drawing.Point(472, 302);
            this.buttonTask.Name = "buttonTask";
            this.buttonTask.Size = new System.Drawing.Size(75, 23);
            this.buttonTask.TabIndex = 16;
            this.buttonTask.Text = "任务";
            this.buttonTask.UseVisualStyleBackColor = true;
            this.buttonTask.Click += new System.EventHandler(this.buttonTask_Click);
            // 
            // reLogin
            // 
            this.reLogin.Location = new System.Drawing.Point(12, 6);
            this.reLogin.Name = "reLogin";
            this.reLogin.Size = new System.Drawing.Size(75, 23);
            this.reLogin.TabIndex = 17;
            this.reLogin.Text = "重新选角";
            this.reLogin.UseVisualStyleBackColor = true;
            this.reLogin.Click += new System.EventHandler(this.reLogin_Click);
            // 
            // buttonShop
            // 
            this.buttonShop.Location = new System.Drawing.Point(472, 331);
            this.buttonShop.Name = "buttonShop";
            this.buttonShop.Size = new System.Drawing.Size(75, 23);
            this.buttonShop.TabIndex = 18;
            this.buttonShop.Text = "商店";
            this.buttonShop.UseVisualStyleBackColor = true;
            this.buttonShop.Click += new System.EventHandler(this.buttonShop_Click);
            // 
            // buttonActivity
            // 
            this.buttonActivity.Location = new System.Drawing.Point(472, 361);
            this.buttonActivity.Name = "buttonActivity";
            this.buttonActivity.Size = new System.Drawing.Size(75, 23);
            this.buttonActivity.TabIndex = 19;
            this.buttonActivity.Text = "活动";
            this.buttonActivity.UseVisualStyleBackColor = true;
            this.buttonActivity.Click += new System.EventHandler(this.buttonActivity_Click);
            // 
            // buttonFriend
            // 
            this.buttonFriend.Location = new System.Drawing.Point(472, 391);
            this.buttonFriend.Name = "buttonFriend";
            this.buttonFriend.Size = new System.Drawing.Size(75, 23);
            this.buttonFriend.TabIndex = 20;
            this.buttonFriend.Text = "好友";
            this.buttonFriend.UseVisualStyleBackColor = true;
            this.buttonFriend.Click += new System.EventHandler(this.buttonFriend_Click);
            // 
            // getRoleData
            // 
            this.getRoleData.Location = new System.Drawing.Point(385, 6);
            this.getRoleData.Name = "getRoleData";
            this.getRoleData.Size = new System.Drawing.Size(75, 23);
            this.getRoleData.TabIndex = 21;
            this.getRoleData.Text = "角色信息";
            this.getRoleData.UseVisualStyleBackColor = true;
            this.getRoleData.Click += new System.EventHandler(this.getRoleData_Click);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(564, 442);
            this.Controls.Add(this.getRoleData);
            this.Controls.Add(this.buttonFriend);
            this.Controls.Add(this.buttonActivity);
            this.Controls.Add(this.reLogin);
            this.Controls.Add(this.buttonShop);
            this.Controls.Add(this.buttonTask);
            this.Controls.Add(this.mail);
            this.Controls.Add(this.buttonRankSystem);
            this.Controls.Add(this.buttonArena);
            this.Controls.Add(this.Bag);
            this.Controls.Add(this.pet);
            this.Controls.Add(this.buttonChatSystem);
            this.Controls.Add(this.equip);
            this.Controls.Add(this.skill);
            this.Controls.Add(this.btnEnterCarbon);
            this.Controls.Add(this.quitScene);
            this.KeyPreview = true;
            this.Name = "FormMain";
            this.Text = "主场景";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormMain_FormClosed);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.Button quitScene;
        private System.Windows.Forms.Button btnEnterCarbon;
        private System.Windows.Forms.Button skill;
        private System.Windows.Forms.Button equip;

        private System.Windows.Forms.Button pet;

        private System.Windows.Forms.Button buttonChatSystem;
        private System.Windows.Forms.Button Bag;
        private System.Windows.Forms.Button buttonArena;
        private System.Windows.Forms.Button buttonRankSystem;
        private System.Windows.Forms.Button mail;
        private System.Windows.Forms.Button buttonTask;
        private System.Windows.Forms.Button reLogin;
        private System.Windows.Forms.Button buttonShop;
        //private SimulateControl.Control3DScene m_cotrolScene;
        private System.Windows.Forms.Button buttonActivity;
        private System.Windows.Forms.Button buttonFriend;
        private System.Windows.Forms.Button getRoleData;
    }
}

