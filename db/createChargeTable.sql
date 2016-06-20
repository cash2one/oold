#��ɫ��ֵ��
DROP TABLE IF EXISTS `RoleCharge`;
CREATE TABLE `RoleCharge`(
  `ChargeID` BIGINT NOT NULL AUTO_INCREMENT COMMENT '��ֵID,�Զ�����',
  `AccountID` BIGINT NOT NULL DEFAULT 0 COMMENT '�����ϷΨһID',
  `ZoneID` INT NOT NULL DEFAULT 0 COMMENT '��Ϸ��ID',
  `RoleIndex` INT NOT NULL DEFAULT 0 COMMENT '��ɫ����',
  `PlatformAccount` VARCHAR(65) NOT NULL DEFAULT 0 COMMENT '��Ϸƽ̨�˺�',
  `GameOrderID` VARCHAR(65) NOT NULL DEFAULT 0 COMMENT '��Ϸ��ֵ����ID',
  `PlatformOrderID` VARCHAR(65) NOT NULL DEFAULT 0 COMMENT 'ƽ̨��ֵ����ID',
  `Type` INT NOT NULL DEFAULT 0 COMMENT '��Ʒ����',
  `Money` INT NOT NULL DEFAULT 0 COMMENT '��ֵ���',
  `SetTime` BIGINT NOT NULL DEFAULT '0' COMMENT '��ֵ������д��ʱ��',
  `GetTime` BIGINT NOT NULL DEFAULT '0' COMMENT '��Ϸ��������ȡʱ��',
  `Platform` VARCHAR(16) NOT NULL DEFAULT 0 COMMENT 'ƽ̨��ֵ����',
  PRIMARY KEY (`ChargeID`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin
COMMENT = '��ɫ��ֵ��';