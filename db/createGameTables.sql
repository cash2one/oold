#创建游戏区玩家表
CREATE SCHEMA IF NOT EXISTS `gamedb` DEFAULT CHARACTER SET utf8 COLLATE utf8_bin;

USE gamedb;

DROP TABLE IF EXISTS `PlayerData`;

CREATE TABLE `PlayerData` (
  `AccountID` BIGINT NOT NULL COMMENT '账号ID',
  `ZoneID` INT NOT NULL COMMENT '游戏区ID',
  `CurrentRoleIndex` INT NOT NULL DEFAULT '0' COMMENT '当前使用角色索引',
  `VIPScore` INT NOT NULL DEFAULT '0' COMMENT 'VIP积分',
  `MaxRoleIndex` INT NOT NULL DEFAULT '-1' COMMENT '当前已分配角色索引最大值，（从0开始分配），下一个从MaxRoleIndex+1开始分配',
  PRIMARY KEY (`AccountID`, `ZoneID`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '游戏区玩家管理表';

##########################################################################################
#创建玩家角色表

DROP TABLE IF EXISTS `RoleData`;

CREATE TABLE `RoleData` (
  `AccountID` BIGINT NOT NULL COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL COMMENT '角色索引',
  `RoleName` VARCHAR(65) NOT NULL COMMENT '角色名称',
  `RoleTPID` INT NOT NULL DEFAULT '0' COMMENT '角色类型',
  `RoleID` BIGINT NOT NULL DEFAULT '0' COMMENT '角色ID',
  `RoleEXP` BIGINT NOT NULL DEFAULT '0' COMMENT '角色经验',
  `Vitality` INT NOT NULL DEFAULT '0' COMMENT '角色体力',
  `Gold` BIGINT  NOT NULL DEFAULT '0' COMMENT '金币',
  `ChargeDiamond` INT NOT NULL DEFAULT '0' COMMENT '充值钻石',
  `BindDiamond` INT NOT NULL DEFAULT '0' COMMENT '绑定钻石',
  `RoleLevel` INT NOT NULL DEFAULT '0' COMMENT '等级',
  `StarLevel` INT NOT NULL DEFAULT '0' COMMENT '星级',
  `Quiality` INT NOT NULL DEFAULT '0' COMMENT '品级',
  `SkillPoint` INT NOT NULL DEFAULT '0' COMMENT '技能点',
  `PVPCoin` INT NOT NULL DEFAULT '0' COMMENT 'PVP币',
  `RolePOP` INT NOT NULL DEFAULT '0' COMMENT '人气值',
  `SceneID` INT NOT NULL DEFAULT '0' COMMENT '退出时场景ID',

  `Atk` INT NOT NULL DEFAULT '0' COMMENT '物理攻击 ',
  `Def` INT NOT NULL DEFAULT '0' COMMENT '物理防御',
  
  `AtkCrift` INT NOT NULL DEFAULT '0' COMMENT '暴击',
  `DefCrift` INT NOT NULL DEFAULT '0' COMMENT '暴击抗性',
  
  `HitRate` INT NOT NULL DEFAULT '0' COMMENT '命中几率(1/10000)',
  `MissRate` INT NOT NULL DEFAULT '0' COMMENT '避闪几率(1/10000)',
  `MaxHP`    INT NOT NULL DEFAULT '0' COMMENT '最大生命值',
  
  `Combat` INT NOT NULL DEFAULT '0' COMMENT '战斗力',
  `BagCount` INT NOT NULL DEFAULT '0' COMMENT '背包上限',
  `CreateTime` BIGINT NOT NULL DEFAULT '0' COMMENT '创建时间',
  `LastLoginTime` BIGINT NOT NULL DEFAULT '0' COMMENT '上次登录时间',
  `LastQuitTime` BIGINT NOT NULL DEFAULT '0' COMMENT '上次退出时间',
  `LastSkillUpdateTime` BIGINT NOT NULL DEFAULT '0' COMMENT '技能更新时间',
  `LastVitalityUpdateTime` BIGINT NOT NULL DEFAULT '0' COMMENT '体力更新时间',
  `VIPLevel` INT NOT NULL DEFAULT '0' COMMENT 'VIP等级',
  `VIPScore` INT NOT NULL DEFAULT '0' COMMENT 'VIP积分',
  `ActiveDegree` INT NOT NULL DEFAULT '0' COMMENT '活跃度',

  `TotalUseChargeDiamond` INT NOT NULL DEFAULT '0' COMMENT '累积消费充值砖石',
  `TotalUseBindDiamond` INT NOT NULL DEFAULT '0' COMMENT '累积消费绑定钻石',
  `TotalChargeDiamond` INT NOT NULL DEFAULT '0' COMMENT '充值累积钻石',

  `InvalidFlag` INT NOT NULL DEFAULT '0' COMMENT '无效标识，0有效，1无效',
   `LightPower` INT UNSIGNED NOT NULL DEFAULT '0' COMMENT '光子力',
   
   `HistoryMaxCombatPower` INT NOT NULL DEFAULT '0' COMMENT '历史最高战斗力',
  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`),
  KEY `RoleName` (`RoleName`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '游戏区玩家管理表';
##########################################################################################
#创建玩家角色表

DROP TABLE IF EXISTS `RoleNameData`;
CREATE TABLE `RoleNameData` (
  `RoleID` BIGINT NOT NULL AUTO_INCREMENT COMMENT  '角色ID,自动生成',
  `RoleName` VARCHAR(65) NOT NULL COMMENT '角色名称',
  PRIMARY KEY (`RoleID`),
  KEY `RoleName` (`RoleName`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '角色名字表';
ALTER TABLE `RoleNameData` AUTO_INCREMENT=10000000; 
##########################################################################################
#创建成就表
DROP TABLE IF EXISTS `RoleAchieveData`;
CREATE TABLE `RoleAchieveData` (
  `AccountID` BIGINT NOT NULL COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL COMMENT '角色索引',
  `AchieveList` BLOB NULL COMMENT '成就数组',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '角色成就表';

##########################################################################################

#创建技能表
DROP TABLE IF EXISTS `RoleSkillData`;
CREATE TABLE `RoleSkillData` (
  `AccountID` BIGINT NOT NULL COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL COMMENT '角色索引',
  `SkillList` BLOB NULL COMMENT '技能ID数组',
  `SkillPos`  TINYBLOB NULL COMMENT '技能位置',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '角色技能表';

##########################################################################################
#创建vip礼包表
DROP TABLE IF EXISTS `RoleVipGiftData`;
CREATE TABLE `RoleVipGiftData` (
  `AccountID` BIGINT NOT NULL COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL COMMENT '角色索引',
  `VipGift` BLOB NULL COMMENT 'vip礼包数组',
  `NextUpdateTime` BIGINT NOT NULL DEFAULT '0' COMMENT '更新时间',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '角色技能表';

##########################################################################################
#创建装备表
DROP TABLE IF EXISTS `RoleEquipData`;
CREATE TABLE `RoleEquipData` (
  `AccountID` BIGINT NOT NULL COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL COMMENT '角色索引',
  `EquipIndex` INT NOT NULL COMMENT  '装备ID',
  `EquipTPID` INT NOT NULL COMMENT  '装备TPID',
  `EquipLevel` INT NOT NULL COMMENT  '装备等级',
  `EquipAddLevel` INT NOT NULL COMMENT  '装备强化等级',
  `EquipQuality` INT NOT NULL COMMENT  '装备品级',
  `EquipStatus` INT NOT NULL COMMENT  '装备状态，0穿上，1脱下',
  `ResetSum` FLOAT  NOT NULL COMMENT  '洗练累计价值',
  `EquipWhiteGemsCount` BIGINT NOT NULL DEFAULT '0' COMMENT  '装备强化消耗白色宝石数目',
  `EquipGreenGemsCount` BIGINT NOT NULL DEFAULT '0' COMMENT  '装备强化消耗绿色宝石数目',
  `EquipBlueGemsCount`  BIGINT NOT NULL DEFAULT '0' COMMENT  '装备强化消耗蓝色宝石数目',
  `EquipPurpleGemsCount` BIGINT NOT NULL DEFAULT '0' COMMENT  '装备强化消耗紫色宝石数目',
  `EquipOrangeGemsCount` BIGINT NOT NULL DEFAULT '0' COMMENT  '装备强化消耗橙色宝石数目',
  `EquipAttr` BLOB  NULL COMMENT  '装备属性',
  `EquipAttachAttr` BLOB  NULL COMMENT  '装备附加属性',
  `EquipAddAttr` BLOB  NULL COMMENT  '装备强化属性',
  `SlotCount` INT NOT NULL COMMENT  '宝石槽个数',
  `EquipGem1TPID` INT NOT NULL  DEFAULT '0' COMMENT  '槽1宝石',
  `EquipGem2TPID` INT NOT NULL  DEFAULT '0' COMMENT  '槽2宝石',
  `EquipGem3TPID` INT NOT NULL  DEFAULT '0' COMMENT  '槽3宝石',
  `EquipGem4TPID` INT NOT NULL  DEFAULT '0' COMMENT  '槽4宝石',
  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`, `EquipIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '角色装备表';

##########################################################################################
#创建道具表
DROP TABLE IF EXISTS `RoleItemData`;
CREATE TABLE `RoleItemData` (
  `AccountID` BIGINT NOT NULL COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL COMMENT '角色索引',
  
  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '角色道具表';

##########################################################################################
#创建背包表
DROP TABLE IF EXISTS `RoleBagData`;
CREATE TABLE `RoleBagData` (
  `AccountID` BIGINT NOT NULL COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL COMMENT '角色索引',
  `ItemIndex` INT NOT NULL COMMENT '物品位置索引',
  `ItemCount` INT NOT NULL COMMENT '物品数目',
  `ItemType` INT NOT NULL COMMENT '物品类型',
  `ItemTPID` INT NOT NULL COMMENT '物品TPID',
  `InstanceID` INT NOT NULL DEFAULT '0' COMMENT '物品实例ID,如：装备的装备ID',
  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`, `ItemIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '角色背包表';
##########################################################################################
#创建伙伴表
DROP TABLE IF EXISTS `RolePetData`;
CREATE TABLE `RolePetData` (
`AccountID` BIGINT NOT NULL COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL COMMENT '角色索引',
  `HotSpringLevel` INT NOT NULL COMMENT '温泉等级',
  `PetList` blob COMMENT '伙伴列表',
  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '伙伴表';
##########################################################################################
#创建竞技场挑战纪录表
DROP TABLE IF EXISTS `ArenaChallengeRecordData`;
CREATE TABLE `ArenaChallengeRecordData` (
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `RecordID` BIGINT UNSIGNED NOT NULL DEFAULT 0 COMMENT '角色索引',
  `IsActive` TINYINT NOT NULL DEFAULT 0 COMMENT '是否是主动挑战',
  `IsWin` TINYINT NOT NULL DEFAULT 0 COMMENT '是否胜利',
  `ChallengeTime` INT NOT NULL DEFAULT 0 COMMENT '挑战时间',
  `NewRank` INT NOT NULL DEFAULT 0 COMMENT '新排名',
  `ChangedRank` INT NOT NULL DEFAULT 0 COMMENT '本次挑战后名次变化',
  `ChallengeeAccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '对方的账号',
  `ChallengeeZoneID` INT NOT NULL DEFAULT 0 COMMENT '对方的区ID',
  `ChallengeeRoleIndex` INT NOT NULL DEFAULT 0 COMMENT '对方的RoleIndex',
  `ChallengeeTPID` INT NOT NULL DEFAULT 0 COMMENT '对方的TPID',
  `ChallengeeName` VARCHAR(65) NOT NULL DEFAULT '' COMMENT '对方名称',
  `IsRevenged` TINYINT NOT NULL DEFAULT 0 COMMENT '是否已经复仇',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`, `RecordID`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '角色竞技场挑战纪录';

##########################################################################################
#创建竞技场个人数据表
DROP TABLE IF EXISTS `RoleArenaData`;
CREATE TABLE `RoleArenaData` (
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `DailyAreanTicketCount` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '当日竞技场入场券',
  `DailyTicketPurchasedCount` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '当日入场券已购买次数',
  `DailyCoolDownCount` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '当日竞技场CD消除次数',
  `LastChallengeTime` INT NOT NULL DEFAULT 0 COMMENT '上次挑战时间',
  `LastResetTime` INT NOT NULL DEFAULT 0 COMMENT '上次重置时间',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '竞技场个人数据表';



-- ----------------------------
-- Table structure for `RoleMailConfigData` 个人邮件配置
-- ----------------------------
DROP TABLE IF EXISTS `RoleMailConfigData`;
CREATE TABLE `RoleMailConfigData` (
  `AccountID` bigint(20) unsigned NOT NULL,
  `ZoneID` smallint(10) unsigned NOT NULL,
  `RoleIndex` int(10) unsigned NOT NULL,
  `LastestSystemMailID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '已收到最新的全体邮件id',
  `LastestSelfMailID` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '已收到最新的 center发过来的个人邮件id',
  PRIMARY KEY (`AccountID`,`ZoneID`,`RoleIndex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records of RoleMailConfigData
-- ----------------------------


-- ----------------------------
-- Table structure for `MailOutputData`  系统发件箱
-- ----------------------------
DROP TABLE IF EXISTS `MailOutputData`;
CREATE TABLE `MailOutputData` (
  `AccountID` bigint(20) unsigned NOT NULL COMMENT '玩家游戏唯一ID',
  `ZoneID` int(10) unsigned NOT NULL COMMENT '游戏区ID',
  `RoleIndex` int(10) unsigned NOT NULL COMMENT '角色索引',
  `MailID` bigint(20) unsigned NOT NULL COMMENT '邮件id',
  `MailType` int(10) unsigned NOT NULL COMMENT '邮件类型1:个人邮件  2:系统邮件',
  `SystemMail` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '不为0代表为全体邮件的id',
  `IsRead` int(10) unsigned DEFAULT '0' COMMENT '邮件是否已读0:未读, 1:已读',
  `IsGet` int(10) unsigned DEFAULT '0' COMMENT '邮件是否已领取 0:未领取, 1:已领取',
  `TimeStamp` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '邮件的时间',
  `Title` varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '邮件标题',
  `Content` varchar(3000) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '邮件内容',
  `Sender` varchar(255) COLLATE utf8_bin NOT NULL DEFAULT '' COMMENT '邮件发送者',
  `Types` blob ,  
  `Ids` blob COMMENT '奖励id列表',
  `Nums` blob COMMENT '奖励数量列表',
  PRIMARY KEY (`AccountID`,`ZoneID`,`RoleIndex`,`MailID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Records of MailOutputData
-- ----------------------------



-- ----------------------------
-- Table structure for `RoleMailInputBoxData`  个人收件箱
-- ----------------------------
DROP TABLE IF EXISTS `RoleMailInputBoxData`;
CREATE TABLE `RoleMailInputBoxData` (
  `AccountID` bigint(20) unsigned NOT NULL COMMENT '玩家游戏唯一ID',
  `ZoneID` int(10) unsigned NOT NULL COMMENT '游戏区ID',
  `RoleIndex` int(10) unsigned NOT NULL COMMENT '角色索引',
  `MailID` bigint(20) unsigned NOT NULL COMMENT '邮件id',
  `MailType` int(10) unsigned NOT NULL COMMENT '邮件类型1:个人邮件  2:系统邮件',
  `SystemMail` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '不为0代表为全体邮件的id',
  `IsRead` int(10) unsigned DEFAULT '0' COMMENT '邮件是否已读0:未读, 1:已读',
  `IsGet` int(10) unsigned DEFAULT '0' COMMENT '邮件是否已领取 0:未领取, 1:已领取',
  `TimeStamp` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT '邮件的时间',
  `Title` varchar(255) COLLATE utf8_bin DEFAULT NULL COMMENT '邮件标题',
  `Content` varchar(3000) COLLATE utf8_bin DEFAULT NULL COMMENT '邮件内容',
  `Sender` varchar(255) COLLATE utf8_bin DEFAULT NULL COMMENT '邮件发送者',
  `Types` blob ,   
  `Ids` blob COMMENT '奖励id列表',
  `Nums` blob COMMENT '奖励数量列表',
  PRIMARY KEY (`AccountID`,`ZoneID`,`RoleIndex`,`MailID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;


-- ----------------------------
-- Table structure for `RolePrizeData` 奖励系统
-- ----------------------------
DROP TABLE IF EXISTS `RolePrizeData`;
CREATE TABLE `RolePrizeData` (
  `AccountID` bigint(20) unsigned NOT NULL,
  `ZoneID` smallint(5) unsigned NOT NULL,
  `RoleIndex` int(10) unsigned NOT NULL,
  `PrizeID` int(10) unsigned NOT NULL COMMENT '奖励id',
  `StartTime` bigint(20) unsigned NOT NULL COMMENT '开始时间',
  `EndTime` bigint(20) unsigned NOT NULL COMMENT '结束时间',
  `Timestamp` bigint(20) unsigned NOT NULL COMMENT '奖励领取时间',
  `Num` int(10) unsigned DEFAULT '0',
  `States` blob COMMENT '',
  `Param` blob COMMENT '',
  PRIMARY KEY (`AccountID`,`ZoneID`,`RoleIndex`,`PrizeID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;


##########################################################################################
#创建日常任务场个人数据表
DROP TABLE IF EXISTS `RoleDailyTaskData`;
CREATE TABLE `RoleDailyTaskData`(
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `TaskTPID` INT NOT NULL DEFAULT 0 COMMENT '日常任务的TPID',
  `AcceptTime` BIGINT NOT NULL DEFAULT 0 COMMENT '日常任务接受时间',
  `Count` SMALLINT NOT NULL DEFAULT 0 COMMENT '当前完成的日常任务数',
  `State` TINYINT NOT NULL DEFAULT 0 COMMENT '日常任务状态',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`, `TaskTPID`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '个人日常任务数据表';

##########################################################################################
#创建伙伴任务场个人数据表
DROP TABLE IF EXISTS `RolePetTaskData`;
CREATE TABLE `RolePetTaskData`(
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `TaskIndex` INT NOT NULL DEFAULT 0 COMMENT '伙伴任务索引',
  `TaskTPID` INT NOT NULL DEFAULT 0 COMMENT '伙伴任务的TPID',
  `Color` INT NOT NULL DEFAULT 0 COMMENT '颜色',
  `AcceptTime` BIGINT NOT NULL DEFAULT 0 COMMENT '伙伴任务接受时间',
  `Count` SMALLINT NOT NULL DEFAULT 0 COMMENT '当前完成的伙伴任务数',
  `State` TINYINT NOT NULL DEFAULT 0 COMMENT '伙伴任务状态',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`, `TaskIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '个人伙伴任务数据表';

##########################################################################################
#创建任务系统更新数据表
DROP TABLE IF EXISTS `RoleTaskSystemData`;
CREATE TABLE `RoleTaskSystemData`(
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `taskCompletedCount` INT NOT NULL DEFAULT 0 COMMENT '当日已完成任务数',
  `DailyRereshNewTaskCount` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '当日刷新任务次数',
  `LastUpdateTime` INT NOT NULL DEFAULT 0 COMMENT '上次更新时间',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '#创建任务系统更新数据表';


##########################################################################################
#创建主线任务个人数据表
DROP TABLE IF EXISTS `RoleMainTaskData`;
CREATE TABLE `RoleMainTaskData`(
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `CurTaskTPID` INT NOT NULL DEFAULT 0 COMMENT '主任务的TPID',
  `CurCount` INT NOT NULL DEFAULT 0 COMMENT '当前的完成数',
  `AcceptTime` BIGINT NOT NULL DEFAULT 0 COMMENT '主任务接受时间',
  `State` TINYINT NOT NULL DEFAULT 0 COMMENT '任务状态',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '主线任务个人数据表';


##########################################################################################
#创建每日签到个人数据表
DROP TABLE IF EXISTS `RoleAttendenceData`;
CREATE TABLE `RoleAttendenceData`(
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `PrizeTableID` INT NOT NULL DEFAULT 0 COMMENT '签到所使用的奖励表',
  `StartTime` BIGINT NOT NULL DEFAULT 0 COMMENT '当前周期开始时间',
  `LastSignInTime` BIGINT NOT NULL DEFAULT 0 COMMENT '上次签到时间',
  `AttendenceCount` TINYINT NOT NULL DEFAULT 0 COMMENT '签到次数',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '每日签到个人数据表';


##########################################################################################
#创建副本系统数据表
DROP TABLE IF EXISTS `RoleStageSystemData`;
CREATE TABLE `RoleStageSystemData`(
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `DailyGetHelpCount` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '当日好友助阵次数',
  `GreedLandEnterCountRemaining` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '当前可进入贪婪之地的次数',
  `LastGreedLandUpdateTime` INT NOT NULL DEFAULT 0 COMMENT '贪婪之地门券上次更新时间',
  `LastUpdateTime` INT NOT NULL DEFAULT 0 COMMENT '上次更新时间',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '#创建副本系统数据表';
##########################################################################################
#创建副本系统数据表
DROP TABLE IF EXISTS `RoleStoryInstanceProgressData`;
CREATE TABLE `RoleStoryInstanceProgressData`(
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `InstanceID` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '副本ID',
  `StageIndex` SMALLINT UNSIGNED NOT NULL DEFAULT 0 COMMENT '关卡序号',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '剧情剧本进度个人数据表';
##########################################################################################
#创建个人副本关卡数据表
DROP TABLE IF EXISTS `RoleInstanceStageData`;
CREATE TABLE `RoleInstanceStageData`(
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `InstanceID` INT NOT NULL DEFAULT 0 COMMENT '副本ID',
  `StageIndex` SMALLINT NOT NULL DEFAULT 0 COMMENT '关卡序号',
  `Star` TINYINT NOT NULL DEFAULT 0 COMMENT '星级',
  `DailyEnteredTimes` SMALLINT UNSIGNED NOT NULL DEFAULT 0 COMMENT '当日已经进入的次数',
  `LastResetTime` INT NOT NULL DEFAULT 0 COMMENT '上次副本关卡',
  `DailyRestoreTicketCount` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '当日购买门票次数',
  

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`, `InstanceID`, `StageIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '个人副本关卡数据表';
##########################################################################################
#创建剧个人副本奖励数据表
DROP TABLE IF EXISTS `RoleInstancePrizeData`;
CREATE TABLE `RoleInstancePrizeData`(
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `InstanceID` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '副本ID',
  `Star` SMALLINT NOT NULL DEFAULT 0 COMMENT '已经领取到某个星级的奖励',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`, `InstanceID`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '个人副本奖励数据表';

##########################################################################################
#创建剧个人闯关数据表
DROP TABLE IF EXISTS `RoleContinuousInstanceData`;
CREATE TABLE `RoleContinuousInstanceData`(
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `DailyActivateInstanceCount` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '当日已激活闯关副本次数',
  `DailyFreeRollFastClearStageCount` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '当日免费掷筛子快速通关的次数',
  `LastResetTime` INT NOT NULL DEFAULT 0 COMMENT '上次个人闯关清零时间',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '创建剧个人闯关数据表';

##########################################################################################
#创建剧个人闯关进度数据表
DROP TABLE IF EXISTS `RoleContinuousInstanceProgressData`;
CREATE TABLE `RoleContinuousInstanceProgressData`(
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `InstanceID` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '副本ID',
  `IsActivated` TINYINT NOT NULL DEFAULT 0 COMMENT '是否已激活',
  `CurDayStageIndex` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '当日已进行到的关卡序号',
  `MaxClearStageIndex` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '已进行到的关卡序号',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`, `InstanceID`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '创建剧个人闯关数进度据表';

#########################################################################################
#创建剧个人闯关成绩数据表
DROP TABLE IF EXISTS `RoleContinuousStageResultData`;
CREATE TABLE `RoleContinuousStageResultData`(
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `InstanceID` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '副本ID',
  `StageIndex` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '关卡序号',
  `Score` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT '本关卡的积分',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`, `InstanceID`, `StageIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '创建个人闯关成绩数据表';

##########################################################################################
#创建角色抽卡数据表
DROP TABLE IF EXISTS `RoleDrawCardData`;
CREATE TABLE `RoleDrawCardData`(
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '玩家游戏唯一ID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '游戏区ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '角色索引',
  `curFreeGoldDrawCardCount` INT NOT NULL DEFAULT 0 COMMENT '当日免费金币抽卡次数',
  `LastFreeGoldDrawCardCountResetTime` INT NOT NULL DEFAULT 0 COMMENT '当日免费金币抽卡次数',
  `LastGoldDrawCardTime` INT NOT NULL DEFAULT 0 COMMENT '上次免费金币抽卡时间',
  `LastDiamondDrawCardTime` INT NOT NULL DEFAULT 0 COMMENT '上次免费宝石抽卡时间',

  PRIMARY KEY (`AccountID`, `ZoneID`, `RoleIndex`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '角色抽卡数据表';



-- ----------------------------
-- Table structure for `RoleShopData`
-- ----------------------------
DROP TABLE IF EXISTS `RoleShopData`;
CREATE TABLE `RoleShopData` (
  `AccountID` bigint(20) unsigned NOT NULL COMMENT '玩家游戏唯一ID',
  `ZoneID` int(10) unsigned NOT NULL COMMENT '游戏区ID',
  `RoleIndex` int(10) unsigned NOT NULL COMMENT '角色索引',
  `ShopType` int(10) NOT NULL COMMENT '商店类型',
  `RefreshTime` bigint(20) unsigned NOT NULL COMMENT '刷新时间点',
  `RefreshIds` blob COMMENT '刷新出来的id',
  `BoughtIds` blob COMMENT '限购的物品,记录已购买id',
  `BoughtNums` blob COMMENT '限购的物品,记录已购买数量',
  `PaidRefreshCount` int(10) unsigned NOT NULL COMMENT '周期内付费刷新次数',
  PRIMARY KEY (`AccountID`,`ZoneID`,`RoleIndex`,`ShopType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;


-- ----------------------------
-- Table structure for `FriendPendingQueueData`
-- ----------------------------
DROP TABLE IF EXISTS `FriendPendingQueueData`;
CREATE TABLE `FriendPendingQueueData` (
  `AccountID` bigint(20) unsigned NOT NULL,
  `ZoneID` int(10) unsigned NOT NULL,
  `RoleIndex` int(10) unsigned NOT NULL,
  `LeftSpace` int(10) unsigned NOT NULL COMMENT '好友剩余容量',
  `LeftAddTime` bigint(20) unsigned NOT NULL COMMENT '最后一次添加好友时间, 用于请求的有效期判断, 方便clean memory',
  `ToBeDecided` blob COMMENT '结交请求列表',
  `ToBeDel` blob COMMENT '待删除列表',
  `QuasiFriends` blob COMMENT '准好友列表',
  PRIMARY KEY (`AccountID`,`ZoneID`,`RoleIndex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;


-- ----------------------------
-- Table structure for `RoleFriendData`
-- ----------------------------
DROP TABLE IF EXISTS `RoleFriendData`;
CREATE TABLE `RoleFriendData` (
  `AccountID` bigint(20) unsigned NOT NULL,
  `ZoneID` int(10) unsigned NOT NULL,
  `RoleIndex` int(10) unsigned NOT NULL,
  `Friends` blob COMMENT '好友列表',
  `PaidCount` int(10) unsigned zerofill NOT NULL COMMENT '购买的好友上限',
  `Requests` blob COMMENT '好友添加请求',
  `RequestTimes` blob COMMENT '好友添加请求时间',
  PRIMARY KEY (`AccountID`,`ZoneID`,`RoleIndex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

-- ----------------------------
-- Table structure for `RankData`
-- ----------------------------
DROP TABLE IF EXISTS `RankData`;
CREATE TABLE `RankData` (
  `AccountID` bigint(20) unsigned NOT NULL,
  `ZoneID` int(11) unsigned NOT NULL,
  `RoleIndex` int(11) unsigned NOT NULL,
  `Exact` mediumblob COMMENT '精确的排名',
  `Approximate` mediumblob COMMENT '近似的排名',
  `RefreshTime` bigint(20) unsigned DEFAULT NULL COMMENT '刷新时间',
  PRIMARY KEY (`AccountID`,`ZoneID`,`RoleIndex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;


-- ----------------------------
-- Table structure for `RoleRankCNData`
-- ----------------------------
DROP TABLE IF EXISTS `RoleRankCNData`;
CREATE TABLE `RoleRankCNData` (
  `AccountID` bigint(20) unsigned NOT NULL,
  `ZoneID` int(10) unsigned NOT NULL,
  `RoleIndex` int(11) NOT NULL,
  `Infinite` int(11) DEFAULT NULL COMMENT '无限挑战总积分',
  `InfiniteRefreshTime` bigint(20) unsigned DEFAULT NULL COMMENT '无限挑战最后一次更新时间',
  PRIMARY KEY (`AccountID`,`ZoneID`,`RoleIndex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;


-- ----------------------------
-- Table structure for `RoleRankData`
-- ----------------------------
DROP TABLE IF EXISTS `RoleRankData`;
CREATE TABLE `RoleRankData` (
  `AccountID` bigint(20) unsigned NOT NULL,
  `ZoneID` int(10) unsigned NOT NULL,
  `RoleIndex` int(11) NOT NULL,
  `Power` int(11) DEFAULT NULL COMMENT '战斗力',
  PRIMARY KEY (`AccountID`,`ZoneID`,`RoleIndex`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
































