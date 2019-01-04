// ShowMessage.cpp: 实现文件
//

#include "stdafx.h"
#include "atm003.h"
#include "ShowMessage.h"
#include "afxdialogex.h"


// ShowMessage 对话框

IMPLEMENT_DYNAMIC(ShowMessage, CDialogEx)

ShowMessage::ShowMessage(CWnd* pParent /*=nullptr*/)
	: ATM_Base(IDD_SHOW_MONEY, pParent)
{

}

ShowMessage::~ShowMessage()
{
}

void ShowMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOW_NAME, showName);
	DDX_Control(pDX, IDC_SHOW_MONEY, showMoney);
	DDX_Control(pDX, IDC_SHOW_TYPE, showCardType);
	DDX_Control(pDX, IDC_SHOW_CREDITS, showCredits);
	DDX_Control(pDX, IDC_SHOW_ENABLE_CREDITS, show_enable_credits);
	char str_name[20];
	sprintf(str_name, "%s***", FirstName);
	cstr_name = str_name;
	cstr_money.Format(_T("%.2f"), money);
	switch (cardType)
	{
	case DebitCard:
		cstr_cardType = "储蓄卡";
		cstr_credits = CString("此银行卡类型不支持");
		cstr_enable_credits = CString("此银行卡类型不支持");
		break;
	case CreditCard:
		cstr_cardType = "信用卡";
		cstr_credits = CString("***");
		cstr_enable_credits = CString("***");
		break;
	}

	showName.SetWindowText(cstr_name);
	showCardType.SetWindowText(cstr_cardType);
	showMoney.SetWindowText(cstr_money);
	showCredits.SetWindowText(cstr_credits);
	show_enable_credits.SetWindowText(cstr_enable_credits);


	DDX_Control(pDX, IDC_BUTTON1, showHide);
}


BEGIN_MESSAGE_MAP(ShowMessage, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &ShowMessage::OnBnClickedCancel)
	ON_STN_CLICKED(IDC_SHOW_NAME, &ShowMessage::OnStnClickedShowName)
	ON_BN_CLICKED(IDC_BUTTON1, &ShowMessage::OnBnClickedButton1)
END_MESSAGE_MAP()


// ShowMessage 消息处理程序


void ShowMessage::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->EndDialog(0);
}


void ShowMessage::OnStnClickedShowName()
{
	// TODO: 在此添加控件通知处理程序代码
	showName.SetWindowText(TEXT("测试"));
}

void ShowMessage::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	char str_name[40];
	sprintf(str_name, "%s %s", FirstName,LastName);
	cstr_name = str_name;
	if (cardType == CreditCard)
	{
		cstr_credits.Format(_T("%.2f"), Credits);
		cstr_enable_credits.Format(_T("%.2f"), (money >= 0) ? Credits : (Credits + money));
	}
	showName.SetWindowText(cstr_name);
	showCardType.SetWindowText(cstr_cardType);
	showMoney.SetWindowText(cstr_money);
	showCredits.SetWindowText(cstr_credits);
	show_enable_credits.SetWindowText(cstr_enable_credits);
	showHide.EnableWindow(0);
}
