
// TestFtpDlg.h : 头文件
//

#pragma once
#include <string>


// CTestFtpDlg 对话框
class CTestFtpDlg : public CDialog
{
// 构造
public:
	CTestFtpDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTFTP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	LRESULT OnWcsnlen(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	BOOL GetTransFileName(std::string& szInfo);
	BOOL GetAction(std::string& szInfo);
	BOOL GetUserAndHost(std::string& szInfo);


// 实现
protected:
	HICON m_hIcon;

	std::string				m_sCurrentHost;
	std::string				m_sCurrentPort;
	std::string				m_sCurrentUser;
	std::string             m_sAction;
	std::string             m_sFile;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSftp();
};
