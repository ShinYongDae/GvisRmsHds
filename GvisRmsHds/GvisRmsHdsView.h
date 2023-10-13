
// GvisRmsHdsView.h : CGvisRmsHdsView 클래스의 인터페이스
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

protected: // serialization에서만 만들어집니다.
	CGvisRmsHdsView();
	DECLARE_DYNCREATE(CGvisRmsHdsView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_GVISRMSHDS_FORM };
#endif

// 특성입니다.
public:
	CGvisRmsHdsDoc* GetDocument() const;

// 작업입니다.
public:
	void DispSpecInsp();
	void DispSpecAddon();
	void DispSpecLight();
	void DispSpecPunch();
	void DispSpec2dLaser();

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CGvisRmsHdsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GvisRmsHdsView.cpp의 디버그 버전
inline CGvisRmsHdsDoc* CGvisRmsHdsView::GetDocument() const
   { return reinterpret_cast<CGvisRmsHdsDoc*>(m_pDocument); }
#endif

