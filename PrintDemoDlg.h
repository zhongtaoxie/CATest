// PrintDemoDlg.h : ͷ�ļ�
//

#pragma once

#include "PrintFrame.h"
#include "../../../3partylib/libjsonparser/include/reader.h"
// CPrintDemoDlg �Ի���

class CPrintDemoDlg : public CDialog
{
// ����
public:
	CPrintDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void	GetWindowGraph();

// �Ի�������
	enum { IDD = IDD_PRINTDEMO_DIALOG };

	CPrintFrame*	m_pPrintFrame;
	CBitmap			m_bitmapPrint;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual BOOL OnInitDialog();

private:
	CFont m_fontDlg;
	Json::Value m_inRoot;
	CString m_strMsgInfo;

public:
	BOOL ReadForsaveFile(const CString& strPath);
	void initData();
	CString GetHMS(CString strTime);
	CString GetYMD(CString strTime);
	void GetExePath();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	afx_msg void	OnPaint();
	afx_msg HCURSOR	OnQueryDragIcon();
	afx_msg void	OnClickButtonPrint();
	afx_msg LRESULT OnPrintWindow(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonPrintview();
	afx_msg void OnBnClickedButton2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
