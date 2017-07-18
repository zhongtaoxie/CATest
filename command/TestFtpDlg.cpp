
// TestFtpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestFtp.h"
#include "TestFtpDlg.h"
//#include "shlwapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTestFtpDlg �Ի���




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


// CTestFtpDlg ��Ϣ�������

BOOL CTestFtpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestFtpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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

	////�õ����䷽��
	//GetAction(szInfo);



	return 0;
}


void CTestFtpDlg::OnBnClickedBtnSftp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
