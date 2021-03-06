#pragma once

#include "ATM.h"
// GuaShi 对话框

class GuaShi : public ATM_Base
{
	DECLARE_DYNAMIC(GuaShi)

public:
	GuaShi(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~GuaShi();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GUASHI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	// 输入的密码
//	CString Passwd_input;
	afx_msg void OnEnChangeEdit1();
	// 输入的密码
	CString PasswdInput;
};
