#pragma once
// ATM_main_menu 对话框

#include "ATM.h"
#include "WithdrawMoney.h"

class ATM_main_menu : public ATM_Base
{
	DECLARE_DYNAMIC(ATM_main_menu)

public:
	ATM_main_menu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ATM_main_menu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ATM_MAINMEAN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP();


	

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();

	

	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
};
