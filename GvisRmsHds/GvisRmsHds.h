
// GvisRmsHds.h : GvisRmsHds ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.

#define SYSTEM_VERSION	_T("GvisRmsHds - Version 1.0.0")

// CGvisRmsHdsApp:
// �� Ŭ������ ������ ���ؼ��� GvisRmsHds.cpp�� �����Ͻʽÿ�.
//

class CGvisRmsHdsApp : public CWinApp
{
public:
	CGvisRmsHdsApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGvisRmsHdsApp theApp;
