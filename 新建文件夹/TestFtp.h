
// TestFtp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestFtpApp:
// �йش����ʵ�֣������ TestFtp.cpp
//

class CTestFtpApp : public CWinAppEx
{
public:
	CTestFtpApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestFtpApp theApp;