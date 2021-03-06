// ChPasswd.cpp: 实现文件
//

#include "stdafx.h"
#include "atm003.h"
#include "ChPasswd.h"
#include "afxdialogex.h"


// ChPasswd 对话框

IMPLEMENT_DYNAMIC(ChPasswd, CDialogEx)

ChPasswd::ChPasswd(CWnd* pParent /*=nullptr*/)
	: ATM_Base(IDD_CHPASSWD, pParent)
	, OldPasswd(_T(""))
	, InputPasswd(_T(""))
	, ReInputPasswd(_T(""))
{

}

ChPasswd::~ChPasswd()
{
}

void ChPasswd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT3, InputPasswd);
	//  DDV_MaxChars(pDX, InputPasswd, 19);
	DDX_Text(pDX, IDC_EDIT3, OldPasswd);
	DDV_MaxChars(pDX, OldPasswd, 19);
	DDX_Text(pDX, IDC_EDIT2, InputPasswd);
	DDV_MaxChars(pDX, InputPasswd, 19);
	DDX_Text(pDX, IDC_EDIT1, ReInputPasswd);
}


BEGIN_MESSAGE_MAP(ChPasswd, CDialogEx)
	ON_BN_CLICKED(IDOK, &ChPasswd::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ChPasswd::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT3, &ChPasswd::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT2, &ChPasswd::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, &ChPasswd::OnEnChangeEdit1)
END_MESSAGE_MAP()


// ChPasswd 消息处理程序


void ChPasswd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (OldPasswd.IsEmpty() || InputPasswd.IsEmpty() || ReInputPasswd.IsEmpty())
	{
		printMessage("请将信息填写完整");
		UpdateData(TRUE);
		OldPasswd = "";
		InputPasswd = "";
		ReInputPasswd = "";
		UpdateData(FALSE);
		return;
	}
	if (try_times <= MAXTRY)
	{
		CString temp_passwd(passwd);
		if (temp_passwd != OldPasswd)
		{
			char msg[50];
			sprintf(msg, "密码错误！您还有%d次机会。", (MAXTRY - try_times));
			try_times++;
			printMessage(msg);
			UpdateData(TRUE);
			OldPasswd = "";
			InputPasswd = "";
			ReInputPasswd = "";
			UpdateData(FALSE);
			return;
		}
	}
	else
	{
		printMessage("密码输入错误次数过多！！！");
		this->EndDialog(0);
	}
	if (InputPasswd != ReInputPasswd)
	{
		printMessage("两次输入的密码不同,请重新输入！");
		UpdateData(TRUE);
		OldPasswd = "";
		InputPasswd = "";
		ReInputPasswd = "";
		UpdateData(FALSE);
		return;
	}
	else
	{
		char str_passwd[MAXLEN];
		CstringToStr(ReInputPasswd, str_passwd);
		if (UpdateData_atm("passwd", ID, str_passwd))
		{
			printMessage("您的密码修改成功，即将返回主菜单");
			this->EndDialog(0);
		}
	}
}


void ChPasswd::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->EndDialog(0);
}


void ChPasswd::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 ATM_Base::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void ChPasswd::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 ATM_Base::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void ChPasswd::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 ATM_Base::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	UpdateData(FALSE);
}
