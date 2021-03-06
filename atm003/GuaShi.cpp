// GuaShi.cpp: 实现文件
//

#include "stdafx.h"
#include "atm003.h"
#include "GuaShi.h"
#include "afxdialogex.h"


// GuaShi 对话框

IMPLEMENT_DYNAMIC(GuaShi, CDialogEx)

GuaShi::GuaShi(CWnd* pParent /*=nullptr*/)
	: ATM_Base(IDD_GUASHI, pParent)
	, PasswdInput(_T(""))
{

}

GuaShi::~GuaShi()
{
}

void GuaShi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, Passwd_input);
	DDX_Text(pDX, IDC_EDIT1, PasswdInput);
	DDV_MaxChars(pDX, PasswdInput, 19);
}


BEGIN_MESSAGE_MAP(GuaShi, CDialogEx)
	ON_BN_CLICKED(IDOK, &GuaShi::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &GuaShi::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &GuaShi::OnEnChangeEdit1)
END_MESSAGE_MAP()


// GuaShi 消息处理程序


void GuaShi::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp_passwd(passwd);
	if (PasswdInput.IsEmpty())
	{
		printMessage("请输入密码!");
		return;
	}
	if (PasswdInput == temp_passwd)
	{
		if (QueryMessage("确定要挂失银行卡吗?"))
		{
			if (UpdateData_atm("OnLock", ID, "1"))
			{
				char str[50];
				sprintf(str, "您的银行卡[卡号:%d]冻结成功，即将强制下线", ID);
				printMessage(str);
				//退出
				PostQuitMessage(0);
			}
		}
		else
		{
			this->EndDialog(0);
		}
	}
	else
	{
		if (try_times >= MAXTRY)
		{
			printMessage("超过最大尝试次数！！！");
			this->EndDialog(0);
		}
		else
		{
			char msg[50];
			sprintf(msg, "密码错误！您还有%d次机会。", (MAXTRY - try_times));
			try_times++;
			printMessage(msg);
		}
		
	}
	UpdateData(TRUE);
	PasswdInput = "";
	UpdateData(FALSE);
}


void GuaShi::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->EndDialog(0);
}


void GuaShi::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 ATM_Base::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}
