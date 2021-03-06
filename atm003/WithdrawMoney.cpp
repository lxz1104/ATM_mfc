// WithdrawMoney.cpp: 实现文件
//


#include "stdafx.h"
#include "atm003.h"
#include "WithdrawMoney.h"
#include "afxdialogex.h"

// WithdrawMoney 对话框

IMPLEMENT_DYNAMIC(WithdrawMoney, CDialogEx)

WithdrawMoney::WithdrawMoney(CWnd* pParent /*=nullptr*/)
	: ATM_Base(IDD_WITHDRAW, pParent)
	, withdrawMoney(0)
{

}

WithdrawMoney::~WithdrawMoney()
{
}

void WithdrawMoney::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, withdrawMoney);
}


BEGIN_MESSAGE_MAP(WithdrawMoney, CDialogEx)
	ON_BN_CLICKED(IDOK, &WithdrawMoney::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &WithdrawMoney::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &WithdrawMoney::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &WithdrawMoney::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON8, &WithdrawMoney::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON4, &WithdrawMoney::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON9, &WithdrawMoney::OnBnClickedButton9)
END_MESSAGE_MAP()


// WithdrawMoney 消息处理程序


void WithdrawMoney::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (WithDrawMooney())
	{
		this->OnOK();
	}
	UpdateData(TRUE);
	withdrawMoney = 0;
	UpdateData(FALSE);
}


void WithdrawMoney::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->EndDialog(0);
}


void WithdrawMoney::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void WithdrawMoney::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	withdrawMoney = 100;
	UpdateData(FALSE);
}


bool WithdrawMoney::WithDrawMooney()
{
	if (Credits == -1)
	{
		if (withdrawMoney > money)
		{
			printMessage("余额不足！");
			return false;
		}
	}
	else
	{
		if (withdrawMoney > money + Credits)
		{
			printMessage("余额不足！");
			return false;
		}
	}
	
	if(withdrawMoney == 0)
	{
		printMessage("请输入有效的取款金额！");
		return false;
	}
	else
	{
		money -= withdrawMoney;
	}
	//类型转换
	char* str = new char[30];
	sprintf(str, "%f", money);
	if (UpdateData_atm("money", ID, str))
	{
		printMessage("取款成功!!!");
		if (QueryMessage("是否要打印凭条？"))
		{
			if (!PrintList(withdrawMoney, float(ID)))
			{
				printMessage("打印凭条失败!");
				delete[] str;
				return false;
			}
			return true;
		}
		else
		{
			delete[] str;
			return true;
		}
	}
	else {
		money += withdrawMoney;
		printMessage("取款失败，请检查网络连接.");
		delete[] str;
		return false;
	}
}



void WithdrawMoney::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	withdrawMoney = 500;
	UpdateData(FALSE);
}


void WithdrawMoney::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	withdrawMoney = 200;
	UpdateData(FALSE);
}


void WithdrawMoney::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	withdrawMoney = 1000;
	UpdateData(FALSE);
}
