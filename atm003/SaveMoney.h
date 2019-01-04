#pragma once

#include"ATM.h"

// SaveMoney 对话框

class SaveMoney : public ATM_Base
{
	DECLARE_DYNAMIC(SaveMoney)

public:
	SaveMoney(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SaveMoney();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAVE_MONEY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 存款金额
	unsigned int SaveMoneyInput = 0;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
