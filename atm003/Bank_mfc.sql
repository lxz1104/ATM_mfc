#数据库创建脚本
DROP DATABASE Bank_mfc;
CREATE DATABASE Bank_mfc;

USE Bank_mfc;
#创建银行卡表
CREATE TABLE Account (
        FirstName VARCHAR(20),LastName VARCHAR(20),
        ID INT(20) UNSIGNED,passwd VARCHAR(20),
        money FLOAT(20),OnLock BOOLEAN,
        CardType ENUM('DebitCard','CreditCard'),CreditsLevel INT(20) UNSIGNED);
#创建信用等级表
CREATE TABLE CreditLevel(
        CreditsLevel INT(4) not null primary key auto_increment,
        Credits FLOAT(20)
);
#添加信用等级表数据
INSERT into CreditLevel(Credits) values(0),(1000.0),(2000.0),(5000.0),(10000.0);

#创建测试账户
INSERT INTO Account (FirstName,LastName,ID,passwd, money,OnLock,CardType,CreditsLevel) VALUES ("Kivii","Navo",9527,"123",3000,FALSE,1,0);
INSERT INTO Account (FirstName,LastName,ID,passwd, money,OnLock,CardType,CreditsLevel) VALUES ("MaxWell","Nano",9521,"123",5000,FALSE,2,3);
