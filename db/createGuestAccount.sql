CREATE USER 'guest'@'%' IDENTIFIED BY 'guest';

GRANT SELECT ON *.* TO 'guest'@'%';

GRANT SELECT, INSERT, UPDATE ON `gamedb`.`Command` TO 'guest'@'%';