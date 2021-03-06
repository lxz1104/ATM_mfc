// ATM_main_menu.cpp: 实现文件
//

#include "stdafx.h"
#include "atm003.h"
#include "ATM_main_menu.h"
#include "afxdialogex.h"
#include "WithdrawMoney.h"
#include "GuaShi.h"
#include "ChPasswd.h"
#include "SaveMoney.h"
#include "ShowMessage.h"

// ATM_main_menu 对话框

IMPLEMENT_DYNAMIC(ATM_main_menu, CDialogEx)

ATM_main_menu::ATM_main_menu(CWnd* pParent /*=nullptr*/)
	: ATM_Base(IDD_ATM_MAINMEAN, pParent)
{

}

ATM_main_menu::~ATM_main_menu()
{
}

void ATM_main_menu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ATM_main_menu, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ATM_main_menu::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &ATM_main_menu::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON3, &ATM_main_menu::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON9, &ATM_main_menu::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON7, &ATM_main_menu::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &ATM_main_menu::OnBnClickedButton8)
END_MESSAGE_MAP()


// ATM_main_menu 消息处理程序


void ATM_main_menu::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	WithdrawMoney getMoney;
	ShowWindow(SW_HIDE);
	getMoney.money = money;
	getMoney.FirstName = FirstName;
	getMoney.LastName = LastName;

	getMoney.ID = ID;
	getMoney.mysql = mysql;
	getMoney.Credits = Credits;
	if (getMoney.DoModal() == IDOK)
	{
		money = getMoney.money;
	}
	ShowWindow(SW_SHOWNORMAL);
}


void ATM_main_menu::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	GuaShi guaShi;
	ShowWindow(SW_HIDE);
	guaShi.passwd = passwd;
	guaShi.ID = ID;
	guaShi.mysql = mysql;
	guaShi.DoModal();
	ShowWindow(SW_SHOWNORMAL);
}


void ATM_main_menu::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	//exit(0);
	SendMessage(WM_CLOSE);
}


void ATM_main_menu::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	ShowMessage showMessage;
	showMessage.FirstName = FirstName;
	showMessage.LastName = LastName;
	showMessage.cardType = cardType;
	showMessage.Credits = Credits;
	showMessage.money = money;
	ShowWindow(SW_HIDE);
	showMessage.DoModal();
	ShowWindow(SW_SHOWNORMAL);
}


void ATM_main_menu::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	ChPasswd changePasswd;
	ShowWindow(SW_HIDE);
	changePasswd.ID = ID;
	changePasswd.passwd = passwd;
	changePasswd.mysql = mysql;
	changePasswd.DoModal();
	ShowWindow(SW_SHOWNORMAL);
}


void ATM_main_menu::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	SaveMoney saveMoney;
	saveMoney.mysql = mysql;
	saveMoney.ID = ID;
	saveMoney.money = money;
	ShowWindow(SW_HIDE);
	if (saveMoney.DoModal() == IDOK)
	{
		money = saveMoney.money;
	}
	ShowWindow(SW_SHOWNORMAL);
}
