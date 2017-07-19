#ifndef _UEBAMONITORFEIQ_H_
#define _UEBAMONITORFEIQ_H_
#pragma once


class CUEBAMonitorFeiq
{
protected:
	CUEBAMonitorFeiq(void);
	~CUEBAMonitorFeiq(void);
	static	CUEBAMonitorFeiq*	m_sInst;
public:
	static  CUEBAMonitorFeiq*	GetInstance();
	static	void				Destroy();

private:
	BOOL		Initialize();
	void		Shutdown();


	typedef LRESULT (WINAPI* PSendMessageW)(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	typedef LRESULT (WINAPI* PSendMessageA)(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);

	static	LRESULT CALLBACK HookSendMessageW(__in HWND hWnd,__in UINT Msg,__in WPARAM wParam,__in LPARAM lParam);
	static	LRESULT CALLBACK HookSendMessageA(__in HWND hWnd,__in UINT Msg,__in WPARAM wParam,__in LPARAM lParam);

	static	PSendMessageW	m_spSendMessageW;
	static	PSendMessageA	m_spSendMessageA;

	static	BOOL		RegexMatch(std::string sSrc,std::string sRegex);
	static	std::string RegexSearch(std::string sSrc,std::string sRegex,unsigned int uDefIndex = 0);

	BOOL			SendJson(std::string& sSendJson);
	CUEBAUdpLog		m_UdpLog;

};



#endif