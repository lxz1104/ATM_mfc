// Notice.cpp: 实现文件
//

#include "stdafx.h"
#include "atm003.h"
#include "Notice.h"
#include "afxdialogex.h"


// Notice 对话框

IMPLEMENT_DYNAMIC(Notice, CDialogEx)

Notice::Notice(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOTICE, pParent)
{
	
}

Notice::~Notice()
{
}

void Notice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG, NoticeMsg);
	NoticeMsg.SetWindowText("正在重新连接数据库...");
}


BEGIN_MESSAGE_MAP(Notice, CDialogEx)
END_MESSAGE_MAP()






