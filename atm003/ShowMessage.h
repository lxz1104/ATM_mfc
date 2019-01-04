#pragma once

#include"ATM.h"

// ShowMessage 对话框

class ShowMessage : public ATM_Base
{
	DECLARE_DYNAMIC(ShowMessage)

public:
	ShowMessage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ShowMessage();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOW_MONEY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	// 显示用户姓名
	CStatic showName;
	afx_msg void OnStnClickedShowName();
	// 显示余额
	CButton showMoney;
	// 显示银行卡类型
	CStatic showCardType;
	// 显示信用总额度
	CStatic showCredits;
	//银行卡类型
	CString cstr_cardType;
	// 显示可用信用额度
	CStatic show_enable_credits;
	//姓名
	CString cstr_name;
	//余额
	CString cstr_money;
	//总信用额度
	CString cstr_credits;
	//可用信用额度
	CString cstr_enable_credits;
	afx_msg void OnBnClickedButton1();
	// 显示隐藏内容
	CButton showHide;
};
