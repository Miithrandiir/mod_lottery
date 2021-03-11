-- Put only sql structure in this file (create table if exists, delete table, alter table etc...).
-- If you don't use this database, then delete this file.
DROP TABLE IF EXISTS lottery_gain;
DROP TABLE IF EXISTS lottery_member;
DROP TABLE IF EXISTS lottery;
CREATE TABLE lottery
(

    id          int(10) unsigned not null AUTO_INCREMENT,
    lotteryName varchar(255)     not null,
    beginDate   datetime         not null,
    endDate     datetime         not null,
    isDone      tinyint          not null,

    CONSTRAINT PK_lottery PRIMARY KEY (id)

);
CREATE TABLE lottery_member
(
    id          int(10) unsigned not null,
    characterId int(10) unsigned not null,
    lotteryId   int(10) unsigned not null,

    CONSTRAINT PK_lottery_member PRIMARY KEY (characterId, lotteryId),
    CONSTRAINT FK_lottery_member_character FOREIGN KEY (characterId) REFERENCES characters (guid),
    CONSTRAINT FK_lottery_member_lottery FOREIGN KEY (lotteryId) REFERENCES lottery (id)
);

CREATE TABLE lottery_gain
(
    id        int(10) unsigned not null AUTO_INCREMENT,
    lotteryId int(10) unsigned not null,
    type      int              not null,
    typeId    int              not null,

    CONSTRAINT PK_lottery_gain PRIMARY KEY (id),
    CONSTRAINT FK_lottery_gain_lottery FOREIGN KEY (lotteryId) REFERENCES lottery (id)
)