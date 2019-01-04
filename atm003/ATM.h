#ifndef _ATM_H_
#define _ATM_H_

#include <sstream>
#include <WinSock2.h>
#include "include/mysql.h"

#define MAXLEN 19
#define MAXTRY 3
//�������п�����
#define DITBITCARD "DebitCard"
#define CRIDECARD "CreditCard"

typedef unsigned int uint;


enum _accountStatus {
	//�˺Ŵ���
	EXIST,
	//�˺Ų�����
	UNEXIST,
	//�˺Ŷ���
	LOCKED
};
enum CardType {
	//���
	DebitCard,
	//���ÿ�
	CreditCard
};


class ATM_Base :public  CDialogEx
{
public:
	/**�û���*/
	char *FirstName = NULL;
	/**�û���*/
	char *LastName = NULL;
	/**�û�����*/
	char *passwd = NULL;
	/**�û��˺�*/
	uint ID = 0;
	/**�û����*/
	float money = 0;
	/**�˻��Ƿ�����*/
	bool OnLock = false;
	//mysql����
	MYSQL mysql;
	//��¼���볢�Դ���
	uint try_times = 0;
	
	//���п�����
	CardType cardType;
	//���ö��
	float Credits = 0;

	ATM_Base(int CId, CWnd* pParent /*=nullptr*/) :CDialogEx(CId, pParent) {}
	ATM_Base() = delete;
	~ATM_Base() {}
	//��ӡ��Ϣ
	void printMessage(const char* str)
	{
		CString str_out(str), title;
		title = "��ʾ";
		MessageBox(str_out, title);
	}
	//ѯ�ʶԻ���
	bool QueryMessage(const char* str)
	{
		CString str_out(str), title;
		title = "��ʾ";
		if (MessageBox(str_out, title, MB_OKCANCEL) == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	} 
	//��ӡƾ��
	bool PrintList(float Get_money, uint ID);
	//�������ݿ�
	bool connectMysql(const char* IP = "127.0.0.1",
		const char* user = "root",
		const char* passwd = "root",
		const char* databaseName = "Bank",
		uint Port = 3306);
	
	//��ʼ���û��˺�
	bool InitAccount(uint& userId);
	
	//�ͷ�mysql������Դ
	void freeMysqlConnect()
	{
		//�ͷ���Դ
		mysql_free_result(this->res);
		if (&(this->mysql))
		{
			mysql_close(&(this->mysql));
		}
	}
	//��mysql�������û���Ϣ
	//bool InsertDatabase(const char* FirstName, const char* LastName, uint ID, const char* paswd, double moxeny, bool Lock);
	//ɾ��mysql���ݱ����
	//bool DeleteDatabase(const uint ID);
	//Cstringת��Ϊchar*
	bool CstringToStr(CString& cstr,char* str);
	//Cstringת��Ϊchar*(+1����)
	char* CstringToStr(CString& cstr);
	//����ת��Ϊstring(ģ�庯��)
	template<typename T>
	inline void digToString(const T digit, std::string &str);

	//��ӡmysql������Ϣ
	inline void printMessage_mysql(char*);

	//�޸�����
	bool UpdateData_atm(const char* _feild, const uint id, const char* feild_value);
	//mysql��ѯ����(����+1),��ѯĳһ�ֶε�ֵ,��idΪ��ѯ����
	char* QueryDatabase(const char* query_feild, uint id);
	//mysql��ѯ����(����+2������ѯĳ�ֶ�ID�Ƿ���ֵ
	_accountStatus QueryDatabase(const uint userId);	
	
	//��ȡ���ö��
	float GetCreditsFromDatabase(uint id);
	//�˶����п�����
	bool CheckCardType(CardType type, uint userId);
	
protected:

	//��������ַ
	char *ip;
	//�������˿�
	unsigned short Port = 3306;
	//���ݿ���
	char *database_name;
	//���ݿ��û���
	char *database_user;
	//���ݿ�����
	char *database_passwd;

	//�в�ѯ�����
	MYSQL_RES *res;
	MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ����ʾ�����е���

};

#endif // !_ATM_H_

