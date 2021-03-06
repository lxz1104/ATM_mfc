#pragma once


// Notice 对话框

class Notice : public CDialogEx
{
	DECLARE_DYNAMIC(Notice)

public:
	Notice(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Notice();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOTICE};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	// 提示信息// 提示信息
	CStatic NoticeMsg;
};
