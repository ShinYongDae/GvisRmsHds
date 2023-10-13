
// GvisRmsHdsView.cpp : CGvisRmsHdsView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GvisRmsHds.h"
#endif

#include "MainFrm.h"

#include "GvisRmsHdsDoc.h"
#include "GvisRmsHdsView.h"

#include "DlgSpec.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGvisRmsHdsView

IMPLEMENT_DYNCREATE(CGvisRmsHdsView, CFormView)

BEGIN_MESSAGE_MAP(CGvisRmsHdsView, CFormView)
END_MESSAGE_MAP()

// CGvisRmsHdsView 생성/소멸

CGvisRmsHdsView::CGvisRmsHdsView()
	: CFormView(IDD_GVISRMSHDS_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CGvisRmsHdsView::~CGvisRmsHdsView()
{
}

void CGvisRmsHdsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CGvisRmsHdsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CGvisRmsHdsView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CGvisRmsHdsView 진단

#ifdef _DEBUG
void CGvisRmsHdsView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGvisRmsHdsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CGvisRmsHdsDoc* CGvisRmsHdsView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGvisRmsHdsDoc)));
	return (CGvisRmsHdsDoc*)m_pDocument;
}
#endif //_DEBUG


// CGvisRmsHdsView 메시지 처리기

void CGvisRmsHdsView::DispSpecInsp()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	pFrame->ShowWindow(SW_MINIMIZE);
	ShowDlgSpecInsp();
	pFrame->ShowWindow(SW_NORMAL);
}

void CGvisRmsHdsView::DispSpecAddon()
{

}

void CGvisRmsHdsView::DispSpecLight()
{

}

void CGvisRmsHdsView::DispSpecPunch()
{

}

void CGvisRmsHdsView::DispSpec2dLaser()
{

}


void CGvisRmsHdsView::ShowDlgSpecInsp()
{
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	CDlgSpec Dlg;
	Dlg.DoModal();
}

void CGvisRmsHdsView::ShowDlgSpecAddon()
{

}

void CGvisRmsHdsView::ShowDlgSpecLight()
{

}

void CGvisRmsHdsView::ShowDlgSpecPunch()
{

}

void CGvisRmsHdsView::ShowDlgSpec2dLaser()
{

}
