
// atm003Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "atm003.h"
#include "atm003Dlg.h"
#include "afxdialogex.h"
#include "Notice.h"
#include "ATM_main_menu.h"
#include "ATM_admin.h"
#include "Report.h"



using std::string;
using std::stringstream;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Catm003Dlg 对话框



Catm003Dlg::Catm003Dlg(CWnd* pParent /*=nullptr*/)
	:ATM_Base(IDD_ATM003_DIALOG, pParent)
	, CAccount(_T(""))
	, CPasswd(_T(""))

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	InitATM();
}

Catm003Dlg::~Catm003Dlg()
{
	DeleteAccount();
}

void Catm003Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, CAccount);
	DDV_MaxChars(pDX, CAccount, 18);
	DDX_Text(pDX, IDC_EDIT2, CPasswd);
	DDV_MaxChars(pDX, CPasswd, 18);
	DDX_Control(pDX, IDC_ATM_CARD, CCardType);
}

BEGIN_MESSAGE_MAP(Catm003Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &Catm003Dlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &Catm003Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &Catm003Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &Catm003Dlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_ATM_CARD, &Catm003Dlg::OnCbnSelchangeAtmCard)
	ON_BN_CLICKED(IDC_BUTTON3, &Catm003Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Catm003Dlg 消息处理程序

BOOL Catm003Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	//添加下拉框数据
	CCardType.AddString(TEXT("储蓄卡"));
	CCardType.AddString(TEXT("信用卡"));

	//设定默认值
	CCardType.SetCurSel(0);

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if (!connectMysql(ip, database_user, database_passwd, database_name, Port))
	{
		printMessage("数据库连接失败！！！");
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Catm003Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Catm003Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Catm003Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Catm003Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//exit(0);
	SendMessage(WM_CLOSE);
}


void Catm003Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//记录输入的值
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void Catm003Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	//记录输入的值
	UpdateData(TRUE);
	UpdateData(FALSE);
}


void Catm003Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	if (CPasswd.IsEmpty() || CAccount.IsEmpty())
	{
		printMessage("账号或密码为空,请重新输入!");
		UpdateData(TRUE);
		CAccount = "";
		CPasswd = "";
		UpdateData(FALSE);
		return;
	}
	if (CAccount == ROOT && CPasswd == ROOTPASSWD)
	{
		if (QueryMessage("是否进入管理员界面?"))
		{
			//UpdateData(TRUE);
			this->ShowWindow(SW_HIDE);
			ATM_admin admin;
			Notice wait;
			//wait = new Notice();
			wait.Create(IDD_NOTICE);
			if (admin.DoModal() == IDOK)
			{
				wait.ShowWindow(SW_SHOWNORMAL);
				Port = admin.Port;
				IP = admin.IP;
				DatabaseName = admin.DatabaseName;
				DatabasePasswd = admin.DatabasePasswd;
				DatabaseUser = admin.DatabaseUser;
				//转换ip地址
				IN_ADDR ia;
				ia.S_un.S_addr = htonl(IP);
				strcpy(ip, inet_ntoa(ia));
				//转换char*
				if (!(CstringToStr(DatabaseUser, database_user) && CstringToStr(DatabasePasswd, database_passwd) && CstringToStr(DatabaseName, database_name)))
				{
					printMessage("类型转换出错!!!");
					SendMessage(WM_CLOSE);
				}
			}
			freeMysqlConnect();	
			if (!connectMysql(ip, database_user, database_passwd, database_name, Port))
			{
				printMessage("数据库连接失败！！！");
			}
			//delete wait;
			this->ShowWindow(SW_SHOWNORMAL);
			
		}
	}
	else
	{
		if (!Login())
		{
			UpdateData(TRUE);
			CAccount = "";
			CPasswd = "";
			UpdateData(FALSE);
			return;
		}
		else
		{
			ATM_main_menu menu;
			InitData(menu);
			this->OnOK();
			menu.DoModal();
		}
		
	}
	UpdateData(TRUE);
	CAccount = "";
	CPasswd = "";
	UpdateData(FALSE);
	
}


void Catm003Dlg::OnCbnSelchangeAtmCard()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	UpdateData(FALSE);
	//设置银行卡类型
	cardType = CardType(CCardType.GetCurSel());
}

//登录
bool Catm003Dlg::Login()
{
	char *tempPasswd;
	uint temp_id;
	temp_id = (uint)_ttoi(CAccount);
	if (!CstringToStr(CPasswd, passwd))
	{
		return false;
	}
	_accountStatus AccountStatus = QueryDatabase(temp_id);
	if (AccountStatus == UNEXIST)
	{
		printMessage("无效卡！！！");
		return false;
	}
	else if (AccountStatus == LOCKED)
	{
		printMessage("该银行卡已被冻结，请前往营业厅解冻！！！");
		return false;
	}
	if (!CheckCardType(cardType, temp_id))
	{
		printMessage("请选择正确的银行卡类型!!!");
		return false;
	}
	tempPasswd = new char[MAXLEN];
	strcpy(tempPasswd, QueryDatabase("passwd", temp_id));
	CString CTempPasswd(tempPasswd);
	CString CInputPasswd(passwd);
	if (CTempPasswd != CInputPasswd)
	{
		printMessage("密码错误！！！");
		delete[] tempPasswd;
		return false;
	}
	ID =  temp_id;
	delete[] tempPasswd;
	return true;
}


//初始化数据成员
bool Catm003Dlg::InitData(ATM_main_menu& user_menu)
{
	int line; //字段个数
	string str2;
	digToString<uint>(ID, str2);
	string QueryCommand = "select * from Account where ID = " + str2;
	const char* sqlCode = (char*)QueryCommand.data();

	mysql_query(&mysql, "SET NAMES gbk");
	//返回0 查询成功，返回1查询失败
	if (mysql_query(&mysql, sqlCode))        //执行SQL语句
	{
		printMessage_mysql("数据库查询失败，返回错误代码:");
		return false;
	}
	if (!(res = mysql_store_result(&mysql)))
	{
		printMessage_mysql("无法获取数据库:");
		return false;
	}
	line = mysql_num_fields(res);   // 获取列数
	column = mysql_fetch_row(res);
	if (column == NULL)
	{
		printMessage("读取数据失败！！！");
		return false;
	}
	//cout << line << endl;
	if (line >= 6)
	{
		user_menu.FirstName = (char*)column[0];
		user_menu.LastName = (char*)column[1];
		user_menu.ID = (unsigned int)atof(column[2]);
		//char*类型转浮点型
		user_menu.money = float(atof(column[4]));
		user_menu.passwd = passwd;
		user_menu.OnLock = false;
		user_menu.mysql = mysql;
		user_menu.cardType = cardType;
		user_menu.Credits = GetCreditsFromDatabase(ID);

	}
	else
	{
		return false;
	}
	user_menu.passwd = passwd;
	return true;

}

void Catm003Dlg::InitATM()
{
	ID = 10000;
	passwd = new char[20];
	OnLock = false;
	/**用户姓*/
	FirstName = new char[20];
	/**用户名*/
	LastName = new char[20];
	//服务器地址
	ip = new char[20];
	//数据库名
	database_name = new char[100];
	//数据库用户名
	database_user = new char[100];
	//数据库密码
	database_passwd = new char[100];
	try_times = 0;
	//设置数据库初始参数
	strcpy(ip, "127.0.1.1");
	strcpy(database_name, "Bank_mfc");
	strcpy(database_user, "root");
	strcpy(database_passwd, "*******");
	Port = 4371;
}

//删除用户账户(析构）
void Catm003Dlg::DeleteAccount()
{
	delete[] passwd;
	passwd = NULL;
	delete[] FirstName;
	FirstName = NULL;
	delete[] LastName;
	LastName = NULL;
	delete[] ip;
	ip = NULL;
	delete[] database_name;
	database_name = NULL;
	delete[] database_user;
	database_user = NULL;
	delete[] database_passwd;
	database_passwd = NULL;
	freeMysqlConnect();
}

void Catm003Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	Report report;
	this->ShowWindow(SW_HIDE);
	report.DoModal();
	this->ShowWindow(SW_SHOWNORMAL);
}
