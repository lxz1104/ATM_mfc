#pragma once

#include "ATM.h"
// WithdrawMoney 对话框

class WithdrawMoney : public ATM_Base
{
	DECLARE_DYNAMIC(WithdrawMoney)

public:
	WithdrawMoney(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~WithdrawMoney();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WITHDRAW};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	// //取款额
	unsigned int withdrawMoney = 0;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();

	//取款函数
	bool WithDrawMooney();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton9();
};
