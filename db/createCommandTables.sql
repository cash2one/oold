#创建数据库
CREATE SCHEMA IF NOT EXISTS `gamedb` DEFAULT CHARACTER SET utf8 COLLATE utf8_bin;

USE gamedb;

DROP TABLE IF EXISTS `Command`;

CREATE TABLE `Command` (
  `Id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '递增',
  `Request` varchar(10000) COLLATE utf8_bin DEFAULT '' COMMENT '命令',
  `Reply` varchar(255) COLLATE utf8_bin DEFAULT '' COMMENT '回复',
  `ReadFlag` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '已读标志',
  `ReturnFlag` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '已返回标志',
  `Time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

