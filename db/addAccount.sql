


DROP PROCEDURE IF EXISTS addAccount;

Delimiter //
CREATE PROCEDURE addAccount()
BEGIN
	DECLARE v INT;
	SET v = 1;
	WHILE v <= 10000 DO
		INSERT INTO `AccountData`(`AccountName`, `AccountPassword`,`UniqueID`, `UniqueKey`,`Channel`, `Platform`,`BindFlag`,`RegisterTime`,`ActivationCode`) VALUES (CONCAT('test_',CONVERT(v, CHAR)), '123456',"","","","",0,0,"");
		SET v = v + 1;
	END WHILE;
END;//

Delimiter ;

call addAccount();

DROP PROCEDURE addAccount;
