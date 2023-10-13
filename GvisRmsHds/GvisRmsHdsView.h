
// GvisRmsHdsView.h : CGvisRmsHdsView Ŭ������ �������̽�
//

#pragma once
#include "GvisRmsHdsDoc.h"


class CGvisRmsHdsView : public CFormView
{
	void ShowDlgSpecInsp();
	void ShowDlgSpecAddon();
	void ShowDlgSpecLight();
	void ShowDlgSpecPunch();
	void ShowDlgSpec2dLaser();

protected: // serialization������ ��������ϴ�.
	CGvisRmsHdsView();
	DECLARE_DYNCREATE(CGvisRmsHdsView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_GVISRMSHDS_FORM };
#endif

// Ư���Դϴ�.
public:
	CGvisRmsHdsDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	void DispSpecInsp();
	void DispSpecAddon();
	void DispSpecLight();
	void DispSpecPunch();
	void DispSpec2dLaser();

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CGvisRmsHdsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GvisRmsHdsView.cpp�� ����� ����
inline CGvisRmsHdsDoc* CGvisRmsHdsView::GetDocument() const
   { return reinterpret_cast<CGvisRmsHdsDoc*>(m_pDocument); }
#endif

