#pragma once

#define PORT 5000
#define IPADDR "127.0.0.1"
#define MAXBUFLEN 1024

// Report 对话框

class Report : public CDialogEx
{
	DECLARE_DYNAMIC(Report)

public:
	Report(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Report();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REPORT};
#endif

protected:

	//套接字
	CSocket aSocket;
	//IP地址
	CString strIP;
	//端口
	CString strPort;
	//发送文本
	CString strText;
	//判断是否连接
	BOOL IsConnect;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	//初始化socket
	BOOL InitSocket();
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	// 报告内容
	CString report_content;
	afx_msg void OnEnChangeEdit1();
};
