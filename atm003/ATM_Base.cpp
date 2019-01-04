#include "stdafx.h"
#include "ATM.h"

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <string>
#include <conio.h>
#include <cstring>
#include<iomanip>
#include <ctime>
#include <Windows.h>
#include <iostream>
#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"libmysql.lib")
#pragma comment(lib, "ws2_32.lib")

using namespace std;


//核对银行卡类型
bool ATM_Base::CheckCardType(CardType type,uint userId)
{
	string str1;
	digToString<uint>(userId, str1);
	uint result = 0;
	char *str,*type_str;
	string QueryCommand = "select CardType from Account where ID = " + str1;
	const char* sqlCode = (char*)QueryCommand.data();

	mysql_query(&mysql, "set names gbk");
	//返回0 查询成功，返回1查询失败
	if (mysql_query(&mysql, sqlCode))        //执行SQL语句
	{
		printMessage_mysql("数据库查询失败，错误代码:");
		return false;
	}
	res = mysql_store_result(&mysql);
	column = mysql_fetch_row(res);
	if (column == NULL)
	{
		return false;
	}
	str = (char*)column[0];
	type_str = new char[strlen(DITBITCARD) + 5];
	switch (type)
	{
	case DebitCard:
		type_str = DITBITCARD;
		break;
	case CreditCard:
		type_str = CRIDECARD;
		break;
	}
	if (strcmp(str, type_str))
	{
		return false;
	}
	return true;
}
//获取信用额度
float ATM_Base::GetCreditsFromDatabase(uint id)
{
	float credits;
	string str_id;
	//合成后的sql语句
	const char* sqlCode;
	digToString<uint>(id, str_id);

	string QueryCommand = " select Credits from CreditLevel where CreditsLevel = (select CreditsLevel from Account where ID = " + str_id + ");" ;
	sqlCode = (char*)QueryCommand.data();

	mysql_query(&mysql, "set names gbk");
	if (mysql_query(&mysql, sqlCode))        //执行SQL语句
	{
		printMessage_mysql("查询数据出错:");
		return -1;
	}
	res = mysql_store_result(&mysql);
	column = mysql_fetch_row(res);
	if (column != NULL)
	{
		credits = float(atof(column[0]));
	}
	else
	{
		return -1;
	}
	return credits;
}

//Cstring转换为char*
bool ATM_Base::CstringToStr(CString& cstr,char* str)
{
	int strLength = cstr.GetLength() + 1;
	strncpy(str, cstr, strLength);
	return true;
}

//Cstring转换为char*(+1重载)
char* ATM_Base::CstringToStr(CString& cstr)
{
	return (char*)cstr.GetBuffer(cstr.GetLength());
}

//连接MySQL数据库
bool ATM_Base::connectMysql(const char* _IP, const char* user, const char* passwd, const char* databaseName, uint Port)
{
	//初始化mysql
	mysql_init(&mysql);  //连接mysql，数据库
	//返回false则连接失败，返回true则连接成功
	//中间分别是主机，用户名，密码，数据库名，端口号（可以写默认0或者3306等）
	if (!(mysql_real_connect(&mysql, _IP, user, passwd, databaseName, Port, NULL, 0)))
	{
		ATM_Base::printMessage_mysql("数据库连接失败，错误代码:");
		return false;
	}
	else
	{
		return true;
	}
}


/*/
bool ATM_Base::InsertDatabase(const char* FirstName, const char* LastName, uint ID, const char* paswd, double moeny, bool Lock)
{
	string str_FirstName(FirstName, FirstName + strlen(FirstName));
	string str_LastName(LastName, LastName + strlen(LastName));
	string str_paswd(paswd, paswd + strlen(paswd));
	string str_id;
	string str_money;
	string str_lock;
	string quot = "\'";
	//合成后的sql语句
	const char* sqlCode;

	//数字转换为string对象
	digToString<uint>(ID, str_id);
	digToString<double>(money, str_money);

	//布尔类型转string
	if (Lock)
	{
		str_lock = "1";
	}
	else
	{
		str_lock = "0";
	}

	string QueryCommand = "insert into Account values (" + quot + str_FirstName + quot + "," + quot + str_LastName + quot + "," + str_id + "," + quot + str_paswd + quot + "," + str_money + "," + str_lock + ");";
	sqlCode = (char*)QueryCommand.data();


	if (mysql_query(&mysql, sqlCode))        //执行SQL语句
	{
		ATM_Base::printMessage_mysql("插入数据出错:");
		return false;
	}
	else
	{
		ATM_Base::printMessage("添加账户成功!");
		return true;
	}
}
*/
//打印mysql错误信息
inline void ATM_Base::printMessage_mysql(char* str)
{
	if (str == NULL)
	{
		return;
	}
	char temp[256];
	sprintf_s(temp, "%s %s", str, mysql_error(&mysql));
	ATM_Base::printMessage(temp);
}

//数字转换为string
template<typename T>
inline void ATM_Base::digToString(const T digit, std::string & str)
{
	stringstream stream;
	stream << digit;
	str = stream.str();
}
/*
bool ATM_Base::DeleteDatabase(const uint ID)
{
	string str1;
	digToString<uint>(ID, str1);
	string QueryCommand = "delete from user where ID = " + str1;
	const char* sqlCode = (char*)QueryCommand.data();

	mysql_query(&mysql, "set names gbk");
	//返回0 查询成功，返回1查询失败
	if (mysql_query(&mysql, sqlCode))        //执行SQL语句
	{
		printMessage_mysql("数据库操作失败，错误代码:");
		return false;
	}
	ATM_Base::printMessage("账号注销成功！");
	return true;
}
*/
bool ATM_Base::UpdateData_atm(const char* _feild,const uint id, const char* feild_value)
{
	string str_feild(_feild, _feild + strlen(_feild));
	string str_feild_value(feild_value, feild_value + strlen(feild_value));
	string str_id;
	string quot = "\'";
	//合成后的sql语句
	const char* sqlCode;

	digToString<uint>(id, str_id);

	string QueryCommand = "UPDATE Account SET " + str_feild + "=" + quot + str_feild_value + quot + " WHERE ID = " + str_id;

	sqlCode = (char*)QueryCommand.data();

	if (mysql_query(&mysql, sqlCode))        //执行SQL语句
	{
		printMessage_mysql("更新数据出错:");
		return false;
	}
	else
	{
		return true;
	}
}

//mysql查询函数
char* ATM_Base::QueryDatabase(const char* query_feild, const  uint id)
{
	string str1(query_feild, query_feild + strlen(query_feild));
	string str_id;
	char* str;
	digToString<uint>(id, str_id);
	//string str2(feild_value, feild_value + strlen(feild_value));
	string QueryCommand = "select " + str1 + " from Account where ID = " + str_id;
	const char* sqlCode = (char*)QueryCommand.data();

	mysql_query(&mysql, "set names gbk");
	//返回0 查询成功，返回1查询失败
	if (mysql_query(&mysql, sqlCode))        //执行SQL语句
	{
		printMessage_mysql("数据库查询失败，错误代码:");
		return NULL;
	}
	res = mysql_store_result(&mysql);
	column = mysql_fetch_row(res);
	str = new char[MAXLEN];
	if (column != NULL)
	{
		str = (char*)column[0];
	}

	return str;
}

//查看用户是否存在
_accountStatus ATM_Base::QueryDatabase(const uint userId)
{
	string str1;
	digToString<uint>(userId, str1);
	string QueryCommand = "select * from Account where ID = " + str1;
	const char* sqlCode = (char*)QueryCommand.data();

	mysql_query(&mysql, "set names gbk");
	//返回0 查询成功，返回1查询失败
	if (mysql_query(&mysql, sqlCode))        //执行SQL语句
	{
		printMessage_mysql("数据库查询失败，错误代码:");
		return UNEXIST;
	}
	res = mysql_store_result(&mysql);
	char* str;
	column = mysql_fetch_row(res);
	if (column == NULL)
	{
		return UNEXIST;
	}
	str = (char*)column[5];
	if (!strcmp(str, "1"))
	{
		return LOCKED;
	}
	return EXIST;
}

bool ATM_Base::InitAccount(uint & userId)
{
	string str1;
	digToString<uint>(ID, str1);
	const char* sqlCode = "select count(*) from Account;";
	int num;
	mysql_query(&mysql, "set names gbk");
	//返回0 查询成功，返回1查询失败
	if (mysql_query(&mysql, sqlCode))        //执行SQL语句
	{
		printMessage_mysql("数据库操作失败，错误代码:");
		return false;
	}
	res = mysql_store_result(&mysql);
	column = mysql_fetch_row(res);
	//char*类型转浮点型
	num = int(atof(column[0]));
	userId += (num + 1);
	return true;
}

//打印凭条
bool ATM_Base::PrintList(float Get_money, uint ID)
{
	char fileName[64];
	char time_str[64];
	time_t time_seconds = time(0);
	struct tm now_time;
	ofstream file;

	localtime_s(&now_time, &time_seconds);
	sprintf_s(fileName, "%d-%d-%d[%d].txt", now_time.tm_year + 1900, now_time.tm_mon + 1,now_time.tm_mday, ID);
	sprintf_s(time_str, "%d-%d-%d %d:%d:%d", now_time.tm_year + 1900, now_time.tm_mon + 1,now_time.tm_mday, now_time.tm_hour, now_time.tm_min, now_time.tm_sec);
	try
	{
		file.open(fileName);
	}
	catch (exception)
	{
		printMessage("fail to open file!");
		return false;
	}
	file << "+--------------------------------------------------------------------------------------------------------------------------+" << endl;
	file << " |      账号       |      用户名        |     操作类型         |          操作时间             |      账户余额             |" << endl;
	file << setiosflags(ios::fixed) << setprecision(6) << setiosflags(ios::left) << setprecision(2);
	file << " |" << setw(17) 
		<< ID << "|"
		<< FirstName << setw(15) << "**" << "|"
		<< "[取款]:" << Get_money << setw(9) << "元" << "|" << setw(31)
		<< time_str << "|" << setw(26)
		<< money << " |" << endl;
	file << "+--------------------------------------------------------------------------------------------------------------------------+" << endl;
	file.close();
	CString str("打印凭条成功:");
	str += fileName;
	MessageBox(str);
	return true;
}
