// PrintDemoDlg.h : 头文件
//

#pragma once

#include "PrintFrame.h"
#include "../../../3partylib/libjsonparser/include/reader.h"
// CPrintDemoDlg 对话框

class CPrintDemoDlg : public CDialog
{
// 构造
public:
	CPrintDemoDlg(CWnd* pParent = NULL);	// 标准构造函数
	void	GetWindowGraph();

// 对话框数据
	enum { IDD = IDD_PRINTDEMO_DIALOG };

	CPrintFrame*	m_pPrintFrame;
	CBitmap			m_bitmapPrint;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
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

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
