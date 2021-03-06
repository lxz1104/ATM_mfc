#pragma once


// ATM_admin 对话框

class ATM_admin : public CDialogEx
{
	DECLARE_DYNAMIC(ATM_admin)

public:
	ATM_admin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ATM_admin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ATM_ADMIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton6();
	// IP地址
//	CIPAddressCtrl IP_addr;
	// 服务器端口
	unsigned int Port;
	afx_msg void OnEnChangeAtmPort();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);


	// IP地址
	DWORD IP;
	// 数据库账户
	CString DatabaseUser;
	// 数据库名
	CString DatabaseName;
	// 数据库密码
	CString DatabasePasswd;


	afx_msg void OnEnChangeAtmDatebaseUser();
	afx_msg void OnEnChangeAtmDatabaseName();
	afx_msg void OnEnChangeAtmDatabasePasswd();
	
	
	afx_msg void OnBnClickedOk();
};
