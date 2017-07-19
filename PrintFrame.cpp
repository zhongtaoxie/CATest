// PrintFrame.cpp : 实现文件
//

#include "stdafx.h"
#include "PrintDemo.h"
#include "PrintFrame.h"


// CPrintFrame

IMPLEMENT_DYNCREATE(CPrintFrame, CFrameWnd)

CPrintFrame::CPrintFrame()
{
	m_pMainDlg		= NULL;
	m_pPrintView	= NULL;
}

CPrintFrame::CPrintFrame(CDialog* pMainDlg)
{
	m_pPrintView	= NULL;
	m_pMainDlg		= pMainDlg;
	if(!Create(NULL, _T("打印预览"), WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE, CRect(0, 0, 800, 600)))
		AfxMessageBox(_T("Failed to create view window\n"));
	CenterWindow();
}

CPrintFrame::~CPrintFrame()
{
//	m_pMainDlg->ShowWindow(SW_SHOW);
}

void CPrintFrame::DoPrintView()
{
	if(m_pPrintView!=NULL)
	{
		m_pPrintView->ShowWindow(SW_SHOW);
		SetActiveView(m_pPrintView);
	}
	SetIcon(m_pMainDlg->GetIcon(FALSE), FALSE);
	SetIcon(m_pMainDlg->GetIcon(TRUE), TRUE);
	ShowWindow(SW_MAXIMIZE);
	//ShowWindow(SW_SHOW);
	::SetWindowPos(this->GetSafeHwnd(), HWND_TOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	m_pMainDlg->ShowWindow(SW_HIDE);


void CPrintFrame::DoPrint()
{
	if(m_pPrintView==NULL)
	{
		AfxMessageBox(_T("打印设备初始化失败！"));
		return;
	}

	m_pPrintView->SendMessage(WM_COMMAND, ID_FILE_PRINT);
}

BEGIN_MESSAGE_MAP(CPrintFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPrintFrame 消息处理程序

int CPrintFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CCreateContext	context;

	context.m_pNewViewClass	= RUNTIME_CLASS(CPrintView);
	context.m_pCurrentFrame	= this;
	context.m_pCurrentDoc	= NULL;
	context.m_pLastView		= NULL;

	m_pPrintView	= STATIC_DOWNCAST(CPrintView, CreateView(&context));

	return 0;
}

void CPrintFrame::OnDestroy()
{
	if(m_pPrintView!=NULL)
		m_pPrintView->DestroyWindow();

	CFrameWnd::OnDestroy();

	m_pMainDlg->PostMessage(WM_CLOSE,0,0);
}

void CPrintFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFrameWnd::OnClose();
}
