
// atm003Dlg.h: 头文件
//

#pragma once

#include "ATM.h"
#include "ATM_admin.h"
#include "ATM_main_menu.h"
#define ROOT "root"
#define ROOTPASSWD "123"
#define MAXLEN 19





// Catm003Dlg 对话框
class Catm003Dlg : public ATM_Base
{
// 构造
public:
	Catm003Dlg(CWnd* pParent = nullptr);	// 标准构造函数
	~Catm003Dlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ATM_LOGIN };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
private:
	HICON m_hIcon;

	//服务器地址
	DWORD IP;
	//数据库名
	CString DatabaseName;
	//数据库用户名
	CString DatabaseUser;
	//数据库密码
	CString DatabasePasswd;

	//初始化用户账户（构造）
	void InitATM();
	////删除用户账户(析构）
	void DeleteAccount();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
	afx_msg void OnBnClickedButton2();
	// 用户输入的账户
	CString CAccount;
	// 用户输入的密码
	CString CPasswd;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton1();
	// 银行卡类别
	CComboBox CCardType;
	afx_msg void OnCbnSelchangeAtmCard();

	
protected:
	
	//登录
	bool Login();
	//初始化数据成员
	bool InitData(ATM_main_menu& user_menu);
	
public:

	afx_msg void OnBnClickedButton3();
};
