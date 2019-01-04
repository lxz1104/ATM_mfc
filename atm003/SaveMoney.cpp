// SaveMoney.cpp: 实现文件
//

#include "stdafx.h"
#include "atm003.h"
#include "SaveMoney.h"
#include "afxdialogex.h"


// SaveMoney 对话框

IMPLEMENT_DYNAMIC(SaveMoney, CDialogEx)

SaveMoney::SaveMoney(CWnd* pParent /*=nullptr*/)
	: ATM_Base(IDD_SAVE_MONEY, pParent)
	, SaveMoneyInput(0)
{

}

SaveMoney::~SaveMoney()
{
}

void SaveMoney::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, SaveMoneyInput);
	DDV_MinMaxUInt(pDX, SaveMoneyInput, 1, UINT_MAX);
}


BEGIN_MESSAGE_MAP(SaveMoney, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &SaveMoney::OnEnChangeEdit1)
	ON_BN_CLICKED(IDCANCEL, &SaveMoney::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &SaveMoney::OnBnClickedOk)
END_MESSAGE_MAP()


// SaveMoney 消息处理程序


void SaveMoney::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 ATM_Base::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void SaveMoney::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->EndDialog(0);
}


void SaveMoney::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (SaveMoneyInput > 0)
	{
		char str[20];
		
		sprintf(str, "%f", (money + SaveMoneyInput));
		if (UpdateData_atm("money", ID, str))
		{
			char msg[50];
			money += SaveMoneyInput;
			sprintf(msg, "存款成功!您一共存款%d元。", SaveMoneyInput);
			printMessage(msg);
			CDialogEx::OnOK();
		}
		else
		{
			UpdateData(TRUE);
			SaveMoneyInput = 0;
			UpdateData(FALSE);
			return;
		}
	}
	else
	{
		printMessage("请输入有效的金额！！！");
		UpdateData(TRUE);
		SaveMoneyInput = 0;
		UpdateData(FALSE);
		return;
	}
}
