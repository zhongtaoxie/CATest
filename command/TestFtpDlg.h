
// TestFtpDlg.h : ͷ�ļ�
//

#pragma once
#include <string>


// CTestFtpDlg �Ի���
class CTestFtpDlg : public CDialog
{
// ����
public:
	CTestFtpDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTFTP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	LRESULT OnWcsnlen(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/);
	BOOL GetTransFileName(std::string& szInfo);
	BOOL GetAction(std::string& szInfo);
	BOOL GetUserAndHost(std::string& szInfo);


// ʵ��
protected:
	HICON m_hIcon;

	std::string				m_sCurrentHost;
	std::string				m_sCurrentPort;
	std::string				m_sCurrentUser;
	std::string             m_sAction;
	std::string             m_sFile;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSftp();
};
