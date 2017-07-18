
// TestFtpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestFtp.h"
#include "TestFtpDlg.h"
//#include "shlwapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestFtpDlg 对话框




CTestFtpDlg::CTestFtpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestFtpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestFtpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestFtpDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_SFTP, &CTestFtpDlg::OnBnClickedBtnSftp)
END_MESSAGE_MAP()


// CTestFtpDlg 消息处理程序

BOOL CTestFtpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestFtpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestFtpDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestFtpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CTestFtpDlg::GetAction(std::string& szInfo)
{
	std::string szTag = "New transfer created for \\\"";
	size_t nFind = szInfo.find(szTag);
	if (std::string::npos != nFind)
	{
		size_t nEnd = szInfo.rfind("\\");
		if (std::string::npos != nEnd)
		{
			std::string szFile = szInfo.substr(nFind+szTag.length(),nEnd-(nFind+szTag.length()));
			if (PathFileExists(szFile.c_str()))
			{
				m_sAction = "upload";
			}
			else
			{
				m_sAction = "download";
			}

			return TRUE;
		}
	}

	return FALSE;
}

BOOL CTestFtpDlg::GetTransFileName(std::string& szInfo)
{
	std::string szTag = "Transferring file \"";
	size_t nFind = szInfo.find(szTag);
	if (std::string::npos != nFind)
	{
		size_t nEnd = szInfo.rfind("\"");
		if (std::string::npos != nEnd)
		{
			m_sFile = szInfo.substr(nFind+szTag.length(),nEnd-(nFind+szTag.length()));
			return TRUE;
		}
	}

	return FALSE;
}
//root@192.168.0.213:22:0:0
BOOL CTestFtpDlg::GetUserAndHost(std::string& szInfo)
{
	size_t nFind = szInfo.find("@");
	if (std::string::npos == nFind)
	{
		return FALSE;
	}

	m_sCurrentUser = szInfo.substr(0,nFind);
	size_t nEnd = szInfo.find(":");
	if (std::string::npos == nEnd)
	{
		return FALSE;
	}

	m_sCurrentHost = szInfo.substr(nFind+1,nEnd-(nFind+1));
	nFind = nEnd+1;
	nEnd = szInfo.find(":",nFind);
	if (std::string::npos == nEnd)
	{
		return FALSE;
	}

	m_sCurrentPort = szInfo.substr(nFind,nEnd-nFind);

	return TRUE;

}

LRESULT CTestFtpDlg::OnWcsnlen(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	//wchar_t*	pData	= (wchar_t*)wParam;
	//int nLen = (int)lParam;
	//std::string szInfo = WChar2s(_Src,nRet);
	//delete pData;

	////得到传输方向
	//GetAction(szInfo);



	return 0;
}


void CTestFtpDlg::OnBnClickedBtnSftp()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strInfo;
	CStdioFile file;
	if(!file.Open("d:\\2.mime",CFile::modeRead))
	{
		return ;
	}

	while(file.ReadString(strInfo))
	{
		std::string szInfo = strInfo;
		if (GetAction(szInfo))
		{
			continue;
		}
		if (GetUserAndHost(szInfo))
		{
			continue;
		}

		GetTransFileName(szInfo);
		

	}

}
