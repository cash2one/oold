#创建数据库
CREATE SCHEMA IF NOT EXISTS `gamedb` DEFAULT CHARACTER SET utf8 COLLATE utf8_bin;

USE gamedb;

DROP TABLE IF EXISTS `AccountData`;

CREATE TABLE `AccountData` (

  `AccountID` BIGINT NOT NULL AUTO_INCREMENT COMMENT '账号ID,自动生成',

  `AccountName` VARCHAR(65) NOT NULL COMMENT '账号名称',

  `AccountPassword` VARCHAR(65) NULL COMMENT '账号密码',
  `UniqueID` VARCHAR(65) NULL COMMENT '唯一ID',
  `UniqueKey` VARCHAR(65) NULL COMMENT 'key',
  `Channel` VARCHAR(65) NULL COMMENT '渠道名',
  `Platform` VARCHAR(65) NULL COMMENT '平台',
  `BindFlag` INT NOT NULL   DEFAULT '0'  COMMENT '绑定标识，1已绑定，0未绑定',
  `RegisterTime` INT NOT NULL   DEFAULT '0'  COMMENT '注册时间',
  `Forbidden` INT NOT NULL   DEFAULT '0'  COMMENT '禁用标示，1已禁，0未禁',
  `ActivationCode` varchar(256) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`AccountID`),
  KEY `AccountName` (`AccountName`),
  KEY `ActivationCode` (`ActivationCode`) USING HASH
  )
	
ENGINE = MyISAM

DEFAULT CHARACTER SET = utf8

COLLATE = utf8_bin

COMMENT = '游戏玩家账号管理表';

ALTER TABLE `AccountData` AUTO_INCREMENT=10000000; 

DROP TABLE IF EXISTS `ActivationCode`;
CREATE TABLE `ActivationCode` (
  `ID` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `Code` varchar(30) COLLATE utf8_bin NOT NULL,
  `Used` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`ID`),
  UNIQUE KEY `Code` (`Code`) USING HASH
) ENGINE=InnoDB AUTO_INCREMENT=208 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

