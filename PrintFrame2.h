#pragma once

#include "PrintView.h"

// CPrintFrame ���

class CPrintFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CPrintFrame)
public:
	CPrintFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	CPrintFrame(CDialog* pMainDlg);
	virtual ~CPrintFrame();

	void	DoPrintView();
	void	DoPrint();

public:
	CDialog*	m_pMainDlg;
	CPrintView* m_pPrintView;

public:
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnDestroy();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};