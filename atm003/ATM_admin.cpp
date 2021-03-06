// ATM_admin.cpp: 实现文件
//

#include "stdafx.h"
#include "atm003.h"
#include "ATM_admin.h"
#include "afxdialogex.h"


// ATM_admin 对话框

IMPLEMENT_DYNAMIC(ATM_admin, CDialog)

ATM_admin::ATM_admin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ATM_ADMIN, pParent)
	, DatabaseUser(_T(""))
	, DatabaseName(_T(""))
	, DatabasePasswd(_T(""))
	, IP(0)
{

	Port = 0;
	IP = 0;
}

ATM_admin::~ATM_admin()
{
	
}

void ATM_admin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_IPAddress(pDX, IDC_IPADDRESS1, IP);
	DDX_Text(pDX, IDC_ATM_PORT, Port);
	DDX_Text(pDX, IDC_ATM_DATEBASE_USER, DatabaseUser);
	DDX_Text(pDX, IDC_ATM_DATABASE_NAME, DatabaseName);
	DDX_Text(pDX, IDC_ATM_DATABASE_PASSWD, DatabasePasswd);
	//  DDX_IPAddress(pDX, IDC_IPADDRESS1, IP);
	//  DDX_Control(pDX, IDC_IPADDRESS1, IP_addr);
	DDX_IPAddress(pDX, IDC_IPADDRESS1, IP);
}


BEGIN_MESSAGE_MAP(ATM_admin, CDialog)
	ON_BN_CLICKED(IDC_BUTTON6, &ATM_admin::OnBnClickedButton6)
	ON_EN_CHANGE(IDC_ATM_PORT, &ATM_admin::OnEnChangeAtmPort)
	ON_BN_CLICKED(IDC_BUTTON1, &ATM_admin::OnBnClickedButton1)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &ATM_admin::OnIpnFieldchangedIpaddress1)
	ON_EN_CHANGE(IDC_ATM_DATEBASE_USER, &ATM_admin::OnEnChangeAtmDatebaseUser)
	ON_EN_CHANGE(IDC_ATM_DATABASE_NAME, &ATM_admin::OnEnChangeAtmDatabaseName)
	ON_EN_CHANGE(IDC_ATM_DATABASE_PASSWD, &ATM_admin::OnEnChangeAtmDatabasePasswd)
	ON_BN_CLICKED(IDOK, &ATM_admin::OnBnClickedOk)
END_MESSAGE_MAP()


// ATM_admin 消息处理程序


void ATM_admin::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	this->EndDialog(0);
}


void ATM_admin::OnEnChangeAtmPort()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void ATM_admin::OnBnClickedButton1()
{
	
}


void ATM_admin::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void ATM_admin::OnEnChangeAtmDatebaseUser()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void ATM_admin::OnEnChangeAtmDatabaseName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void ATM_admin::OnEnChangeAtmDatabasePasswd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	UpdateData(FALSE);

}




void ATM_admin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码

	if (DatabaseName.IsEmpty() || DatabasePasswd.IsEmpty() || DatabaseUser.IsEmpty() || Port == 0 || IP == 0)
	{
		CString str("请填完所有信息再提交");
		CString title("提示");
		MessageBox(str, title);
		return;
	}
	CString str("保存成功");
	CString title("提示");
	MessageBox(str, title);
	this->OnOK();
}
