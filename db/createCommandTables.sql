#�������ݿ�
CREATE SCHEMA IF NOT EXISTS `gamedb` DEFAULT CHARACTER SET utf8 COLLATE utf8_bin;

USE gamedb;

DROP TABLE IF EXISTS `Command`;

CREATE TABLE `Command` (
  `Id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '����',
  `Request` varchar(10000) COLLATE utf8_bin DEFAULT '' COMMENT '����',
  `Reply` varchar(255) COLLATE utf8_bin DEFAULT '' COMMENT '�ظ�',
  `ReadFlag` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '�Ѷ���־',
  `ReturnFlag` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '�ѷ��ر�־',
  `Time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

