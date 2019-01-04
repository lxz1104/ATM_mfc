#ifndef _ATM_H_
#define _ATM_H_

#include <sstream>
#include <WinSock2.h>
#include "include/mysql.h"

#define MAXLEN 19
#define MAXTRY 3
//定义银行卡类型
#define DITBITCARD "DebitCard"
#define CRIDECARD "CreditCard"

typedef unsigned int uint;


enum _accountStatus {
	//账号存在
	EXIST,
	//账号不存在
	UNEXIST,
	//账号冻结
	LOCKED
};
enum CardType {
	//储蓄卡
	DebitCard,
	//信用卡
	CreditCard
};


class ATM_Base :public  CDialogEx
{
public:
	/**用户姓*/
	char *FirstName = NULL;
	/**用户名*/
	char *LastName = NULL;
	/**用户密码*/
	char *passwd = NULL;
	/**用户账号*/
	uint ID = 0;
	/**用户余额*/
	float money = 0;
	/**账户是否上锁*/
	bool OnLock = false;
	//mysql连接
	MYSQL mysql;
	//记录密码尝试次数
	uint try_times = 0;
	
	//银行卡类型
	CardType cardType;
	//信用额度
	float Credits = 0;

	ATM_Base(int CId, CWnd* pParent /*=nullptr*/) :CDialogEx(CId, pParent) {}
	ATM_Base() = delete;
	~ATM_Base() {}
	//打印信息
	void printMessage(const char* str)
	{
		CString str_out(str), title;
		title = "提示";
		MessageBox(str_out, title);
	}
	//询问对话框
	bool QueryMessage(const char* str)
	{
		CString str_out(str), title;
		title = "提示";
		if (MessageBox(str_out, title, MB_OKCANCEL) == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	} 
	//打印凭条
	bool PrintList(float Get_money, uint ID);
	//连接数据库
	bool connectMysql(const char* IP = "127.0.0.1",
		const char* user = "root",
		const char* passwd = "root",
		const char* databaseName = "Bank",
		uint Port = 3306);
	
	//初始化用户账号
	bool InitAccount(uint& userId);
	
	//释放mysql连接资源
	void freeMysqlConnect()
	{
		//释放资源
		mysql_free_result(this->res);
		if (&(this->mysql))
		{
			mysql_close(&(this->mysql));
		}
	}
	//在mysql中新增用户信息
	//bool InsertDatabase(const char* FirstName, const char* LastName, uint ID, const char* paswd, double moxeny, bool Lock);
	//删除mysql数据表的行
	//bool DeleteDatabase(const uint ID);
	//Cstring转换为char*
	bool CstringToStr(CString& cstr,char* str);
	//Cstring转换为char*(+1重载)
	char* CstringToStr(CString& cstr);
	//数字转换为string(模板函数)
	template<typename T>
	inline void digToString(const T digit, std::string &str);

	//打印mysql错误信息
	inline void printMessage_mysql(char*);

	//修改数据
	bool UpdateData_atm(const char* _feild, const uint id, const char* feild_value);
	//mysql查询函数(重载+1),查询某一字段的值,以id为查询条件
	char* QueryDatabase(const char* query_feild, uint id);
	//mysql查询函数(重载+2），查询某字段ID是否有值
	_accountStatus QueryDatabase(const uint userId);	
	
	//获取信用额度
	float GetCreditsFromDatabase(uint id);
	//核对银行卡类型
	bool CheckCardType(CardType type, uint userId);
	
protected:

	//服务器地址
	char *ip;
	//服务器端口
	unsigned short Port = 3306;
	//数据库名
	char *database_name;
	//数据库用户名
	char *database_user;
	//数据库密码
	char *database_passwd;

	//行查询结果集
	MYSQL_RES *res;
	MYSQL_ROW column; //一个行数据的类型安全(type-safe)的表示，表示数据行的列

};

#endif // !_ATM_H_

