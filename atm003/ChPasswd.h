#pragma once

#include "ATM.h"
// ChPasswd 对话框

class ChPasswd : public ATM_Base
{
	DECLARE_DYNAMIC(ChPasswd)

public:
	ChPasswd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ChPasswd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHPASSWD};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	// 旧密码// 旧密码
	CString OldPasswd;
	// 输入的新密码
	CString InputPasswd;
	// 确认新密码
	CString ReInputPasswd;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit1();
};
