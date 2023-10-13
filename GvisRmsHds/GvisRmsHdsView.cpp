
// GvisRmsHdsView.cpp : CGvisRmsHdsView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CGvisRmsHdsView ����/�Ҹ�

CGvisRmsHdsView::CGvisRmsHdsView()
	: CFormView(IDD_GVISRMSHDS_FORM)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CGvisRmsHdsView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CGvisRmsHdsView ����

#ifdef _DEBUG
void CGvisRmsHdsView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGvisRmsHdsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CGvisRmsHdsDoc* CGvisRmsHdsView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGvisRmsHdsDoc)));
	return (CGvisRmsHdsDoc*)m_pDocument;
}
#endif //_DEBUG


// CGvisRmsHdsView �޽��� ó����

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
