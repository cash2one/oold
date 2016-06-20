namespace SimulateClient
{
    partial class FormRoleData
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
            this.getRoleData = new System.Windows.Forms.Button();
            this.timerWait = new System.Windows.Forms.Timer(this.components);
            this.textRoleData = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxZoneID = new System.Windows.Forms.TextBox();
            this.textBoxAccountID = new System.Windows.Forms.TextBox();
            this.textBoxIndex = new System.Windows.Forms.TextBox();
            this.textBoxCMD = new System.Windows.Forms.TextBox();
            this.menuPlayerSystem = new System.Windows.Forms.ToolStripMenuItem();
            this.getPlayerInfoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getRoleListToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getRoleMsgToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getRoleLocalInfoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PurchaseGoldToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuEquipSystem = new System.Windows.Forms.ToolStripMenuItem();
            this.getEquipInfoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.背包系统ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getBagDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取背包数据ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.物品系统ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取当前体力ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.获取当前体力ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.UseVitalityProToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.伙伴系统ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getPetDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.查看伙伴初始数据ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.登录系统ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.reconnectGameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.disconnectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.gM工具ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addItemToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addDiamondToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addGoldToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.updateLevelToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.vip系统ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getVipStatusToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getvipGiftToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.查看vip积分ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.成就系统ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getAchieveList = new System.Windows.Forms.ToolStripMenuItem();
            this.RoleLevelAchieveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.BattleAchieveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.KillBossAchieveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PassStageAchieveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pvpAchieveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.DiceAchieveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PassStageCountToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.EquipAchieveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.GemAchieveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.SkillAchieveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.PetAchieveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ChargePayAchieveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.getAchievePrizeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAchieveDataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAchieveDataInstanceIDToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.achieveTestToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.装备系统 = new System.Windows.Forms.MenuStrip();
            this.comboBoxSendCmd = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.p1 = new System.Windows.Forms.TextBox();
            this.p2 = new System.Windows.Forms.TextBox();
            this.btnDo = new System.Windows.Forms.Button();
            this.GetPurchaseGoldInfoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.装备系统.SuspendLayout();
            this.SuspendLayout();
            // 
            // getRoleData
            // 
            this.getRoleData.Location = new System.Drawing.Point(424, 30);
            this.getRoleData.Name = "getRoleData";
            this.getRoleData.Size = new System.Drawing.Size(93, 23);
            this.getRoleData.TabIndex = 0;
            this.getRoleData.Text = "获取角色信息";
            this.getRoleData.UseVisualStyleBackColor = true;
            this.getRoleData.Click += new System.EventHandler(this.getRoleData_Click);
            // 
            // timerWait
            // 
            this.timerWait.Tick += new System.EventHandler(this.timerWait_Tick);
            // 
            // textRoleData
            // 
            this.textRoleData.Location = new System.Drawing.Point(0, 85);
            this.textRoleData.Multiline = true;
            this.textRoleData.Name = "textRoleData";
            this.textRoleData.Size = new System.Drawing.Size(703, 430);
            this.textRoleData.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 34);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 2;
            this.label1.Text = "区号ID：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(166, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "账号ID：";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(320, 34);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "索引ID：";
            // 
            // textBoxZoneID
            // 
            this.textBoxZoneID.Location = new System.Drawing.Point(71, 29);
            this.textBoxZoneID.Name = "textBoxZoneID";
            this.textBoxZoneID.Size = new System.Drawing.Size(89, 21);
            this.textBoxZoneID.TabIndex = 3;
            this.textBoxZoneID.Text = "21";
            // 
            // textBoxAccountID
            // 
            this.textBoxAccountID.Location = new System.Drawing.Point(214, 29);
            this.textBoxAccountID.Name = "textBoxAccountID";
            this.textBoxAccountID.Size = new System.Drawing.Size(100, 21);
            this.textBoxAccountID.TabIndex = 3;
            this.textBoxAccountID.Text = "10000000";
            // 
            // textBoxIndex
            // 
            this.textBoxIndex.Location = new System.Drawing.Point(380, 31);
            this.textBoxIndex.Name = "textBoxIndex";
            this.textBoxIndex.Size = new System.Drawing.Size(38, 21);
            this.textBoxIndex.TabIndex = 3;
            this.textBoxIndex.Text = "0";
            // 
            // textBoxCMD
            // 
            this.textBoxCMD.Location = new System.Drawing.Point(71, 58);
            this.textBoxCMD.Name = "textBoxCMD";
            this.textBoxCMD.Size = new System.Drawing.Size(178, 21);
            this.textBoxCMD.TabIndex = 4;
            // 
            // menuPlayerSystem
            // 
            this.menuPlayerSystem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.getPlayerInfoToolStripMenuItem,
            this.getRoleListToolStripMenuItem,
            this.getRoleMsgToolStripMenuItem,
            this.getRoleLocalInfoToolStripMenuItem,
            this.PurchaseGoldToolStripMenuItem,
            this.GetPurchaseGoldInfoToolStripMenuItem});
            this.menuPlayerSystem.Name = "menuPlayerSystem";
            this.menuPlayerSystem.Size = new System.Drawing.Size(68, 21);
            this.menuPlayerSystem.Text = "玩家系统";
            // 
            // getPlayerInfoToolStripMenuItem
            // 
            this.getPlayerInfoToolStripMenuItem.Name = "getPlayerInfoToolStripMenuItem";
            this.getPlayerInfoToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.getPlayerInfoToolStripMenuItem.Text = "获取玩家数据";
            this.getPlayerInfoToolStripMenuItem.Click += new System.EventHandler(this.getPlayerInfoToolStripMenuItem_Click);
            // 
            // getRoleListToolStripMenuItem
            // 
            this.getRoleListToolStripMenuItem.Name = "getRoleListToolStripMenuItem";
            this.getRoleListToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.getRoleListToolStripMenuItem.Text = "获取角色列表";
            this.getRoleListToolStripMenuItem.Click += new System.EventHandler(this.getRoleListToolStripMenuItem_Click);
            // 
            // getRoleMsgToolStripMenuItem
            // 
            this.getRoleMsgToolStripMenuItem.Name = "getRoleMsgToolStripMenuItem";
            this.getRoleMsgToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.getRoleMsgToolStripMenuItem.Text = "获取角色信息";
            this.getRoleMsgToolStripMenuItem.Click += new System.EventHandler(this.getRoleMsgToolStripMenuItem_Click);
            // 
            // getRoleLocalInfoToolStripMenuItem
            // 
            this.getRoleLocalInfoToolStripMenuItem.Name = "getRoleLocalInfoToolStripMenuItem";
            this.getRoleLocalInfoToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.getRoleLocalInfoToolStripMenuItem.Text = "获取角色本地信息";
            this.getRoleLocalInfoToolStripMenuItem.Click += new System.EventHandler(this.getRoleLocalInfoToolStripMenuItem_Click);
            // 
            // PurchaseGoldToolStripMenuItem
            // 
            this.PurchaseGoldToolStripMenuItem.Name = "PurchaseGoldToolStripMenuItem";
            this.PurchaseGoldToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.PurchaseGoldToolStripMenuItem.Text = "购买金币";
            this.PurchaseGoldToolStripMenuItem.Click += new System.EventHandler(this.PurchaseGoldToolStripMenuItem_Click);
            // 
            // menuEquipSystem
            // 
            this.menuEquipSystem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.getEquipInfoToolStripMenuItem});
            this.menuEquipSystem.Name = "menuEquipSystem";
            this.menuEquipSystem.Size = new System.Drawing.Size(68, 21);
            this.menuEquipSystem.Text = "装备系统";
            // 
            // getEquipInfoToolStripMenuItem
            // 
            this.getEquipInfoToolStripMenuItem.Name = "getEquipInfoToolStripMenuItem";
            this.getEquipInfoToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.getEquipInfoToolStripMenuItem.Text = "获取装备信息";
            this.getEquipInfoToolStripMenuItem.Click += new System.EventHandler(this.getEquipInfoToolStripMenuItem_Click);
            // 
            // 背包系统ToolStripMenuItem
            // 
            this.背包系统ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.getBagDataToolStripMenuItem,
            this.获取背包数据ToolStripMenuItem});
            this.背包系统ToolStripMenuItem.Name = "背包系统ToolStripMenuItem";
            this.背包系统ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.背包系统ToolStripMenuItem.Text = "背包系统";
            // 
            // getBagDataToolStripMenuItem
            // 
            this.getBagDataToolStripMenuItem.Name = "getBagDataToolStripMenuItem";
            this.getBagDataToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.getBagDataToolStripMenuItem.Text = "本地背包数据";
            this.getBagDataToolStripMenuItem.Click += new System.EventHandler(this.getBagDataToolStripMenuItem_Click);
            // 
            // 获取背包数据ToolStripMenuItem
            // 
            this.获取背包数据ToolStripMenuItem.Name = "获取背包数据ToolStripMenuItem";
            this.获取背包数据ToolStripMenuItem.Size = new System.Drawing.Size(148, 22);
            this.获取背包数据ToolStripMenuItem.Text = "获取背包数据";
            this.获取背包数据ToolStripMenuItem.Click += new System.EventHandler(this.获取背包数据ToolStripMenuItem_Click);
            // 
            // 物品系统ToolStripMenuItem
            // 
            this.物品系统ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.获取当前体力ToolStripMenuItem,
            this.获取ToolStripMenuItem,
            this.获取当前体力ToolStripMenuItem1,
            this.UseVitalityProToolStripMenuItem});
            this.物品系统ToolStripMenuItem.Name = "物品系统ToolStripMenuItem";
            this.物品系统ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.物品系统ToolStripMenuItem.Text = "体力系统";
            // 
            // 获取当前体力ToolStripMenuItem
            // 
            this.获取当前体力ToolStripMenuItem.Name = "获取当前体力ToolStripMenuItem";
            this.获取当前体力ToolStripMenuItem.Size = new System.Drawing.Size(196, 22);
            this.获取当前体力ToolStripMenuItem.Text = "获取当前体力";
            this.获取当前体力ToolStripMenuItem.Click += new System.EventHandler(this.getVitality);
            // 
            // 获取ToolStripMenuItem
            // 
            this.获取ToolStripMenuItem.Name = "获取ToolStripMenuItem";
            this.获取ToolStripMenuItem.Size = new System.Drawing.Size(196, 22);
            this.获取ToolStripMenuItem.Text = "获取购买体力所需宝石";
            this.获取ToolStripMenuItem.Click += new System.EventHandler(this.getNeedDiamond);
            // 
            // 获取当前体力ToolStripMenuItem1
            // 
            this.获取当前体力ToolStripMenuItem1.Name = "获取当前体力ToolStripMenuItem1";
            this.获取当前体力ToolStripMenuItem1.Size = new System.Drawing.Size(196, 22);
            this.获取当前体力ToolStripMenuItem1.Text = "购买体力";
            this.获取当前体力ToolStripMenuItem1.Click += new System.EventHandler(this.buyVitality);
            // 
            // UseVitalityProToolStripMenuItem
            // 
            this.UseVitalityProToolStripMenuItem.Name = "UseVitalityProToolStripMenuItem";
            this.UseVitalityProToolStripMenuItem.Size = new System.Drawing.Size(196, 22);
            this.UseVitalityProToolStripMenuItem.Text = "使用体力道具";
            this.UseVitalityProToolStripMenuItem.Click += new System.EventHandler(this.UseVitalityProToolStripMenuItem_Click);
            // 
            // 伙伴系统ToolStripMenuItem
            // 
            this.伙伴系统ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.getPetDataToolStripMenuItem,
            this.查看伙伴初始数据ToolStripMenuItem});
            this.伙伴系统ToolStripMenuItem.Name = "伙伴系统ToolStripMenuItem";
            this.伙伴系统ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.伙伴系统ToolStripMenuItem.Text = "伙伴系统";
            // 
            // getPetDataToolStripMenuItem
            // 
            this.getPetDataToolStripMenuItem.Name = "getPetDataToolStripMenuItem";
            this.getPetDataToolStripMenuItem.Size = new System.Drawing.Size(196, 22);
            this.getPetDataToolStripMenuItem.Text = "获取伙伴数据";
            this.getPetDataToolStripMenuItem.Click += new System.EventHandler(this.getPetDataToolStripMenuItem_Click);
            // 
            // 查看伙伴初始数据ToolStripMenuItem
            // 
            this.查看伙伴初始数据ToolStripMenuItem.Name = "查看伙伴初始数据ToolStripMenuItem";
            this.查看伙伴初始数据ToolStripMenuItem.Size = new System.Drawing.Size(196, 22);
            this.查看伙伴初始数据ToolStripMenuItem.Text = "查看伙伴初始本地数据";
            // 
            // 登录系统ToolStripMenuItem
            // 
            this.登录系统ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.reconnectGameToolStripMenuItem,
            this.disconnectToolStripMenuItem});
            this.登录系统ToolStripMenuItem.Name = "登录系统ToolStripMenuItem";
            this.登录系统ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.登录系统ToolStripMenuItem.Text = "登录系统";
            // 
            // reconnectGameToolStripMenuItem
            // 
            this.reconnectGameToolStripMenuItem.Name = "reconnectGameToolStripMenuItem";
            this.reconnectGameToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.reconnectGameToolStripMenuItem.Text = "重连游戏";
            this.reconnectGameToolStripMenuItem.Click += new System.EventHandler(this.reconnectGameToolStripMenuItem_Click);
            // 
            // disconnectToolStripMenuItem
            // 
            this.disconnectToolStripMenuItem.Name = "disconnectToolStripMenuItem";
            this.disconnectToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.disconnectToolStripMenuItem.Text = "断开游戏";
            this.disconnectToolStripMenuItem.Click += new System.EventHandler(this.disconnectToolStripMenuItem_Click);
            // 
            // gM工具ToolStripMenuItem
            // 
            this.gM工具ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addItemToolStripMenuItem,
            this.addDiamondToolStripMenuItem,
            this.addGoldToolStripMenuItem,
            this.addToolStripMenuItem,
            this.updateLevelToolStripMenuItem});
            this.gM工具ToolStripMenuItem.Name = "gM工具ToolStripMenuItem";
            this.gM工具ToolStripMenuItem.Size = new System.Drawing.Size(65, 21);
            this.gM工具ToolStripMenuItem.Text = "GM工具";
            // 
            // addItemToolStripMenuItem
            // 
            this.addItemToolStripMenuItem.Name = "addItemToolStripMenuItem";
            this.addItemToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.addItemToolStripMenuItem.Text = "AddItem";
            this.addItemToolStripMenuItem.Click += new System.EventHandler(this.addItemToolStripMenuItem_Click);
            // 
            // addDiamondToolStripMenuItem
            // 
            this.addDiamondToolStripMenuItem.Name = "addDiamondToolStripMenuItem";
            this.addDiamondToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.addDiamondToolStripMenuItem.Text = "AddDiamond";
            this.addDiamondToolStripMenuItem.Click += new System.EventHandler(this.addDiamondToolStripMenuItem_Click);
            // 
            // addGoldToolStripMenuItem
            // 
            this.addGoldToolStripMenuItem.Name = "addGoldToolStripMenuItem";
            this.addGoldToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.addGoldToolStripMenuItem.Text = "AddGold";
            this.addGoldToolStripMenuItem.Click += new System.EventHandler(this.addGoldToolStripMenuItem_Click);
            // 
            // addToolStripMenuItem
            // 
            this.addToolStripMenuItem.Name = "addToolStripMenuItem";
            this.addToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.addToolStripMenuItem.Text = "AddExp";
            // 
            // updateLevelToolStripMenuItem
            // 
            this.updateLevelToolStripMenuItem.Name = "updateLevelToolStripMenuItem";
            this.updateLevelToolStripMenuItem.Size = new System.Drawing.Size(153, 22);
            this.updateLevelToolStripMenuItem.Text = "UpdateLevel";
            this.updateLevelToolStripMenuItem.Click += new System.EventHandler(this.updateLevelToolStripMenuItem_Click);
            // 
            // vip系统ToolStripMenuItem
            // 
            this.vip系统ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.getVipStatusToolStripMenuItem,
            this.getvipGiftToolStripMenuItem,
            this.查看vip积分ToolStripMenuItem});
            this.vip系统ToolStripMenuItem.Name = "vip系统ToolStripMenuItem";
            this.vip系统ToolStripMenuItem.Size = new System.Drawing.Size(61, 21);
            this.vip系统ToolStripMenuItem.Text = "vip系统";
            // 
            // getVipStatusToolStripMenuItem
            // 
            this.getVipStatusToolStripMenuItem.Name = "getVipStatusToolStripMenuItem";
            this.getVipStatusToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.getVipStatusToolStripMenuItem.Text = "获取vip礼物领取状态";
            this.getVipStatusToolStripMenuItem.Click += new System.EventHandler(this.getVipStatusToolStripMenuItem_Click);
            // 
            // getvipGiftToolStripMenuItem
            // 
            this.getvipGiftToolStripMenuItem.Name = "getvipGiftToolStripMenuItem";
            this.getvipGiftToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.getvipGiftToolStripMenuItem.Text = "领取vip礼物";
            this.getvipGiftToolStripMenuItem.Click += new System.EventHandler(this.getvipGiftToolStripMenuItem_Click);
            // 
            // 查看vip积分ToolStripMenuItem
            // 
            this.查看vip积分ToolStripMenuItem.Name = "查看vip积分ToolStripMenuItem";
            this.查看vip积分ToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.查看vip积分ToolStripMenuItem.Text = "获取vip信息";
            // 
            // 成就系统ToolStripMenuItem
            // 
            this.成就系统ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.getAchieveList,
            this.getAchievePrizeToolStripMenuItem,
            this.saveAchieveDataToolStripMenuItem,
            this.saveAchieveDataInstanceIDToolStripMenuItem,
            this.achieveTestToolStripMenuItem});
            this.成就系统ToolStripMenuItem.Name = "成就系统ToolStripMenuItem";
            this.成就系统ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.成就系统ToolStripMenuItem.Text = "成就系统";
            // 
            // getAchieveList
            // 
            this.getAchieveList.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.RoleLevelAchieveToolStripMenuItem,
            this.BattleAchieveToolStripMenuItem,
            this.KillBossAchieveToolStripMenuItem,
            this.PassStageAchieveToolStripMenuItem,
            this.pvpAchieveToolStripMenuItem,
            this.DiceAchieveToolStripMenuItem,
            this.PassStageCountToolStripMenuItem,
            this.EquipAchieveToolStripMenuItem,
            this.GemAchieveToolStripMenuItem,
            this.SkillAchieveToolStripMenuItem,
            this.PetAchieveToolStripMenuItem,
            this.ChargePayAchieveToolStripMenuItem});
            this.getAchieveList.Name = "getAchieveList";
            this.getAchieveList.Size = new System.Drawing.Size(235, 22);
            this.getAchieveList.Text = "获取成就";
            // 
            // RoleLevelAchieveToolStripMenuItem
            // 
            this.RoleLevelAchieveToolStripMenuItem.Name = "RoleLevelAchieveToolStripMenuItem";
            this.RoleLevelAchieveToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.RoleLevelAchieveToolStripMenuItem.Text = "1角色等级成就";
            this.RoleLevelAchieveToolStripMenuItem.Click += new System.EventHandler(this.RoleLevelAchieveToolStripMenuItem_Click);
            // 
            // BattleAchieveToolStripMenuItem
            // 
            this.BattleAchieveToolStripMenuItem.Name = "BattleAchieveToolStripMenuItem";
            this.BattleAchieveToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.BattleAchieveToolStripMenuItem.Text = "2战斗力成就";
            this.BattleAchieveToolStripMenuItem.Click += new System.EventHandler(this.BattleAchieveToolStripMenuItem_Click);
            // 
            // KillBossAchieveToolStripMenuItem
            // 
            this.KillBossAchieveToolStripMenuItem.Name = "KillBossAchieveToolStripMenuItem";
            this.KillBossAchieveToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.KillBossAchieveToolStripMenuItem.Text = "3击杀boss成就";
            this.KillBossAchieveToolStripMenuItem.Click += new System.EventHandler(this.KillBossAchieveToolStripMenuItem_Click);
            // 
            // PassStageAchieveToolStripMenuItem
            // 
            this.PassStageAchieveToolStripMenuItem.Name = "PassStageAchieveToolStripMenuItem";
            this.PassStageAchieveToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.PassStageAchieveToolStripMenuItem.Text = "4通关副本成就";
            this.PassStageAchieveToolStripMenuItem.Click += new System.EventHandler(this.PassStageAchieveToolStripMenuItem_Click);
            // 
            // pvpAchieveToolStripMenuItem
            // 
            this.pvpAchieveToolStripMenuItem.Name = "pvpAchieveToolStripMenuItem";
            this.pvpAchieveToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.pvpAchieveToolStripMenuItem.Text = "5pvp排行成就";
            this.pvpAchieveToolStripMenuItem.Click += new System.EventHandler(this.pvpAchieveToolStripMenuItem_Click);
            // 
            // DiceAchieveToolStripMenuItem
            // 
            this.DiceAchieveToolStripMenuItem.Name = "DiceAchieveToolStripMenuItem";
            this.DiceAchieveToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.DiceAchieveToolStripMenuItem.Text = "6骰子次数成就";
            this.DiceAchieveToolStripMenuItem.Click += new System.EventHandler(this.DiceAchieveToolStripMenuItem_Click);
            // 
            // PassStageCountToolStripMenuItem
            // 
            this.PassStageCountToolStripMenuItem.Name = "PassStageCountToolStripMenuItem";
            this.PassStageCountToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.PassStageCountToolStripMenuItem.Text = "7连续闯关成就";
            this.PassStageCountToolStripMenuItem.Click += new System.EventHandler(this.PassStageCountToolStripMenuItem_Click);
            // 
            // EquipAchieveToolStripMenuItem
            // 
            this.EquipAchieveToolStripMenuItem.Name = "EquipAchieveToolStripMenuItem";
            this.EquipAchieveToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.EquipAchieveToolStripMenuItem.Text = "8装备成就";
            this.EquipAchieveToolStripMenuItem.Click += new System.EventHandler(this.EquipAchieveToolStripMenuItem_Click);
            // 
            // GemAchieveToolStripMenuItem
            // 
            this.GemAchieveToolStripMenuItem.Name = "GemAchieveToolStripMenuItem";
            this.GemAchieveToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.GemAchieveToolStripMenuItem.Text = "9宝石成就";
            this.GemAchieveToolStripMenuItem.Click += new System.EventHandler(this.GemAchieveToolStripMenuItem_Click);
            // 
            // SkillAchieveToolStripMenuItem
            // 
            this.SkillAchieveToolStripMenuItem.Name = "SkillAchieveToolStripMenuItem";
            this.SkillAchieveToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.SkillAchieveToolStripMenuItem.Text = "10技能成就";
            this.SkillAchieveToolStripMenuItem.Click += new System.EventHandler(this.SkillAchieveToolStripMenuItem_Click);
            // 
            // PetAchieveToolStripMenuItem
            // 
            this.PetAchieveToolStripMenuItem.Name = "PetAchieveToolStripMenuItem";
            this.PetAchieveToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.PetAchieveToolStripMenuItem.Text = "11伙伴成就";
            this.PetAchieveToolStripMenuItem.Click += new System.EventHandler(this.PetAchieveToolStripMenuItem_Click);
            // 
            // ChargePayAchieveToolStripMenuItem
            // 
            this.ChargePayAchieveToolStripMenuItem.Name = "ChargePayAchieveToolStripMenuItem";
            this.ChargePayAchieveToolStripMenuItem.Size = new System.Drawing.Size(162, 22);
            this.ChargePayAchieveToolStripMenuItem.Text = "12充值消费成就";
            this.ChargePayAchieveToolStripMenuItem.Click += new System.EventHandler(this.ChargePayAchieveToolStripMenuItem_Click);
            // 
            // getAchievePrizeToolStripMenuItem
            // 
            this.getAchievePrizeToolStripMenuItem.Name = "getAchievePrizeToolStripMenuItem";
            this.getAchievePrizeToolStripMenuItem.Size = new System.Drawing.Size(235, 22);
            this.getAchievePrizeToolStripMenuItem.Text = "获取成就奖励";
            this.getAchievePrizeToolStripMenuItem.Click += new System.EventHandler(this.getAchievePrizeToolStripMenuItem_Click);
            // 
            // saveAchieveDataToolStripMenuItem
            // 
            this.saveAchieveDataToolStripMenuItem.Name = "saveAchieveDataToolStripMenuItem";
            this.saveAchieveDataToolStripMenuItem.Size = new System.Drawing.Size(235, 22);
            this.saveAchieveDataToolStripMenuItem.Text = "SaveAchieveDataBossID";
            this.saveAchieveDataToolStripMenuItem.Click += new System.EventHandler(this.saveAchieveDataToolStripMenuItem_Click);
            // 
            // saveAchieveDataInstanceIDToolStripMenuItem
            // 
            this.saveAchieveDataInstanceIDToolStripMenuItem.Name = "saveAchieveDataInstanceIDToolStripMenuItem";
            this.saveAchieveDataInstanceIDToolStripMenuItem.Size = new System.Drawing.Size(235, 22);
            this.saveAchieveDataInstanceIDToolStripMenuItem.Text = "SaveAchieveDataInstanceID";
            this.saveAchieveDataInstanceIDToolStripMenuItem.Click += new System.EventHandler(this.saveAchieveDataInstanceIDToolStripMenuItem_Click);
            // 
            // achieveTestToolStripMenuItem
            // 
            this.achieveTestToolStripMenuItem.Name = "achieveTestToolStripMenuItem";
            this.achieveTestToolStripMenuItem.Size = new System.Drawing.Size(235, 22);
            this.achieveTestToolStripMenuItem.Text = "AchieveTest";
            this.achieveTestToolStripMenuItem.Click += new System.EventHandler(this.achieveTestToolStripMenuItem_Click);
            // 
            // 装备系统
            // 
            this.装备系统.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.登录系统ToolStripMenuItem,
            this.menuPlayerSystem,
            this.menuEquipSystem,
            this.背包系统ToolStripMenuItem,
            this.伙伴系统ToolStripMenuItem,
            this.vip系统ToolStripMenuItem,
            this.成就系统ToolStripMenuItem,
            this.gM工具ToolStripMenuItem,
            this.物品系统ToolStripMenuItem});
            this.装备系统.Location = new System.Drawing.Point(0, 0);
            this.装备系统.Name = "装备系统";
            this.装备系统.Size = new System.Drawing.Size(703, 25);
            this.装备系统.TabIndex = 12;
            this.装备系统.Text = "menuStrip1";
            // 
            // comboBoxSendCmd
            // 
            this.comboBoxSendCmd.FormattingEnabled = true;
            this.comboBoxSendCmd.Items.AddRange(new object[] {
            "玩家列表",
            "角色信息",
            "背包数据",
            "装备信息",
            "转换时间",
            "GM命令"});
            this.comboBoxSendCmd.Location = new System.Drawing.Point(389, 59);
            this.comboBoxSendCmd.Name = "comboBoxSendCmd";
            this.comboBoxSendCmd.Size = new System.Drawing.Size(121, 20);
            this.comboBoxSendCmd.TabIndex = 8;
            this.comboBoxSendCmd.SelectedIndexChanged += new System.EventHandler(this.comboBoxSendCmd_SelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(2, 61);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(65, 12);
            this.label5.TabIndex = 2;
            this.label5.Text = "操作数据：";
            // 
            // p1
            // 
            this.p1.Location = new System.Drawing.Point(255, 58);
            this.p1.Name = "p1";
            this.p1.Size = new System.Drawing.Size(61, 21);
            this.p1.TabIndex = 4;
            // 
            // p2
            // 
            this.p2.Location = new System.Drawing.Point(322, 58);
            this.p2.Name = "p2";
            this.p2.Size = new System.Drawing.Size(61, 21);
            this.p2.TabIndex = 4;
            // 
            // btnDo
            // 
            this.btnDo.Location = new System.Drawing.Point(529, 56);
            this.btnDo.Name = "btnDo";
            this.btnDo.Size = new System.Drawing.Size(66, 23);
            this.btnDo.TabIndex = 0;
            this.btnDo.Text = "执行";
            this.btnDo.UseVisualStyleBackColor = true;
            this.btnDo.Click += new System.EventHandler(this.btnDo_Click);
            // 
            // GetPurchaseGoldInfoToolStripMenuItem
            // 
            this.GetPurchaseGoldInfoToolStripMenuItem.Name = "GetPurchaseGoldInfoToolStripMenuItem";
            this.GetPurchaseGoldInfoToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.GetPurchaseGoldInfoToolStripMenuItem.Text = "购买金币信息";
            this.GetPurchaseGoldInfoToolStripMenuItem.Click += new System.EventHandler(this.GetPurchaseGoldInfoToolStripMenuItem_Click);
            // 
            // FormRoleData
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(703, 515);
            this.Controls.Add(this.comboBoxSendCmd);
            this.Controls.Add(this.p2);
            this.Controls.Add(this.p1);
            this.Controls.Add(this.textBoxCMD);
            this.Controls.Add(this.textBoxIndex);
            this.Controls.Add(this.textBoxAccountID);
            this.Controls.Add(this.textBoxZoneID);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textRoleData);
            this.Controls.Add(this.btnDo);
            this.Controls.Add(this.getRoleData);
            this.Controls.Add(this.装备系统);
            this.MainMenuStrip = this.装备系统;
            this.Name = "FormRoleData";
            this.Text = "角色信息";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.FormRoleData_FormClosed);
            this.装备系统.ResumeLayout(false);
            this.装备系统.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button getRoleData;
        private System.Windows.Forms.Timer timerWait;
        private System.Windows.Forms.TextBox textRoleData;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxZoneID;
        private System.Windows.Forms.TextBox textBoxAccountID;
        private System.Windows.Forms.TextBox textBoxIndex;
        private System.Windows.Forms.TextBox textBoxCMD;
        private System.Windows.Forms.ToolStripMenuItem menuPlayerSystem;
        private System.Windows.Forms.ToolStripMenuItem getRoleMsgToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getRoleListToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuEquipSystem;
        private System.Windows.Forms.ToolStripMenuItem 背包系统ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 物品系统ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 伙伴系统ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 登录系统ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem gM工具ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addItemToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addDiamondToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addGoldToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem updateLevelToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem vip系统ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getVipStatusToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getvipGiftToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 查看vip积分ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 成就系统ToolStripMenuItem;
        private System.Windows.Forms.MenuStrip 装备系统;
        private System.Windows.Forms.ToolStripMenuItem getEquipInfoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getBagDataToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getPetDataToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getPlayerInfoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getRoleLocalInfoToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getAchievePrizeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem reconnectGameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem disconnectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAchieveDataToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAchieveDataInstanceIDToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem achieveTestToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem getAchieveList;
        private System.Windows.Forms.ToolStripMenuItem RoleLevelAchieveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem BattleAchieveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem PetAchieveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ChargePayAchieveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem SkillAchieveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem KillBossAchieveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem PassStageAchieveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pvpAchieveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem DiceAchieveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem PassStageCountToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem EquipAchieveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem GemAchieveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 查看伙伴初始数据ToolStripMenuItem;
        private System.Windows.Forms.ComboBox comboBoxSendCmd;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox p1;
        private System.Windows.Forms.TextBox p2;
        private System.Windows.Forms.Button btnDo;
        private System.Windows.Forms.ToolStripMenuItem 获取当前体力ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取当前体力ToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem UseVitalityProToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 获取背包数据ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem PurchaseGoldToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem GetPurchaseGoldInfoToolStripMenuItem;
    }
}