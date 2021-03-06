// Report.cpp: 实现文件
//

#include "stdafx.h"
#include "atm003.h"
#include "Report.h"
#include "afxdialogex.h"



// Report 对话框

IMPLEMENT_DYNAMIC(Report, CDialogEx)

Report::Report(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REPORT, pParent)
	, report_content(_T(""))
{
	if (!InitSocket())
	{
		CString title("提示");
		CString str("无法连接到服务器！");
		MessageBox( str,title);
		IsConnect = FALSE;
	}
	else
	{
		IsConnect = TRUE;
	}
}

Report::~Report()
{
}

void Report::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, report_content);
	DDV_MaxChars(pDX, report_content, 1024);
	//检查是否连接
	if (IsConnect == FALSE)
	{
		this->EndDialog(0);
	}
}


BEGIN_MESSAGE_MAP(Report, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &Report::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &Report::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &Report::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Report 消息处理程序


void Report::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->EndDialog(0);
	
}


void Report::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (report_content.IsEmpty())
	{
		CString title("提示");
		CString str("请输入内容后再提交！");
		MessageBox(str, title);
		return;
	}
	if (aSocket.Send(report_content, report_content.GetLength()) == report_content.GetLength())
	{
		CString title("提示");
		CString str("报告提交成功");
		CString str_exit("close");
		MessageBox(str, title);
		aSocket.Send(str_exit, str_exit.GetLength());
		aSocket.Close();
		this->EndDialog(0);
	}
	else
	{
		CString title("提示");
		CString str("报告提交失败");
		MessageBox(str, title);
		UpdateData(TRUE);
		report_content = "";
		UpdateData(FALSE);
		return;
	}
}


void Report::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
}

//初始化socket
BOOL Report::InitSocket()
{
	//初始化套接字
	if (!AfxSocketInit())
	{
		CString title("提示");
		CString str("IDP_SOCKETS_INIT_FAILED");
		MessageBox(str,title);
		return FALSE;
	}
	//初始化IP地址
	strIP = IPADDR;
	strText = CString("ATM Requests a connection");
	//初始化 CSocket 对象, 因为客户端不需要绑定任何端口和地址, 所以用默认参数即可
	if (!aSocket.Create())
	{
		char szMsg[MAXBUFLEN] = { 0 };

		sprintf(szMsg, "create faild: %d", aSocket.GetLastError());
		CString title("提示");
		CString str(szMsg);
		MessageBox(str, title);
		return FALSE;
	}
	//连接指定的地址和端口
	if (aSocket.Connect(strIP, PORT))
	{
		char szRecValue[1024] = { 0 };
		if (aSocket.Send(strText, strText.GetLength()) != strText.GetLength()) //发送内容给服务器
		{
			aSocket.Close();
			return FALSE;
		}
		aSocket.Receive((void *)szRecValue, MAXBUFLEN); //接收服务器发送回来的内容(该方法会阻塞, 在此等待有内容接收到才继续向下执行)
		if (strcmp(szRecValue, "200") != 0)
		{
			return FALSE;
		}
		return TRUE;
	}
	else
	{
		char szMsg[1024] = { 0 };
		sprintf(szMsg, "Connect faild: %d", aSocket.GetLastError());
		CString title("提示");
		CString str(szMsg);
		MessageBox(str, title);
		return FALSE;
	}
}

