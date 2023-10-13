// DlgSpec.cpp : ±∏«ˆ ∆ƒ¿œ¿‘¥œ¥Ÿ.
//

#include "stdafx.h"
#include "GvisRmsHds.h"
#include "DlgSpec.h"
#include "afxdialogex.h"


// CDlgSpec ¥Î»≠ ªÛ¿⁄¿‘¥œ¥Ÿ.

IMPLEMENT_DYNAMIC(CDlgSpec, CDialog)

CDlgSpec::CDlgSpec(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DLG_SPEC, pParent)
{
	m_hDlgSpecBkBrush = NULL;
}

CDlgSpec::~CDlgSpec()
{
	Close();
}

void CDlgSpec::Close()
{
	if (m_hDlgSpecBkBrush != NULL)
	{
		DeleteObject(m_hDlgSpecBkBrush);
		m_hDlgSpecBkBrush = NULL;
	}
}

void CDlgSpec::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DEFAULT_SPEC_COMBO, m_DefaultSpecCombo);
	DDX_Control(pDX, IDC_TAB1, m_tabDlgInspection);
}


BEGIN_MESSAGE_MAP(CDlgSpec, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgSpec::OnBnClickedOk)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	//ON_NOTIFY(NM_CLICK, IDC_TAB1, OnClickTab1)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_DEFAULT_LOCAL_SPEC, OnButtonSaveDefaultLocalSpec)
	ON_CBN_SELCHANGE(IDC_COMBO_DEFAULT_SPEC_COMBO, OnSelchangeComboDefaultSpecCombo)
	ON_CBN_DROPDOWN(IDC_COMBO_DEFAULT_SPEC_COMBO, OnDropdownComboDefaultSpecCombo)
	//ON_BN_CLICKED(IDC_BUTTON_SET_SPEC_LOCK, OnButtonSetSpecLock)
	//ON_BN_CLICKED(IDC_BUTTON_SET_LIGHT_LOCK, OnButtonSetLightLock)
	//ON_MESSAGE(WM_CONTROL_USER_MESSAGE, OnControlTabMessage)
	ON_MESSAGE(SSM_CLICK, OnClickFpspread1)
	ON_MESSAGE(SSM_DBLCLK, OnDblClickFpspread1)
	ON_MESSAGE(SSM_COMBOSELCHANGE, OnComboCloseUpFpspread1)
	ON_MESSAGE(SSM_LEAVECELL, OnLeaveCellFpspread1)
	ON_MESSAGE(SSM_KEYDOWN, OnKeyDownFpspread1)
END_MESSAGE_MAP()


// CDlgSpec ∏ﬁΩ√¡ˆ √≥∏Æ±‚¿‘¥œ¥Ÿ.

void CDlgSpec::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: ø©±‚ø° ∏ﬁΩ√¡ˆ √≥∏Æ±‚ ƒ⁄µÂ∏¶ √ﬂ∞°«’¥œ¥Ÿ.
}

BOOL CDlgSpec::PreTranslateMessage(MSG* pMsg)
{
	//	if (pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4)
	//		return TRUE;
	//
	//	if (pMsg->message == WM_KEYDOWN)
	//	{
	//		if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_TAB)
	//		{
	//			if (pMsg->hwnd == ((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Lot_Edit.m_hWnd)
	//			{
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Serial_Edit.SetFocus();
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Serial_Edit.SetSel(0, -1);
	//			}
	//			else if (pMsg->hwnd == ((CGvisAOIView*)FromHandle(m_hParentWnd))->m_LayerCombo.m_hWnd)
	//			{
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Lot_Edit.SetFocus();
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Lot_Edit.SetSel(0, -1);
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->DisplayParameter();
	//			}
	//
	//			SS_LEAVECELL ss;
	//			ss.ColCurrent = 1;
	//			ss.ColNew = 1;
	//			ss.RowCurrent = m_nSpreadCellFocusPos[m_nTabNum];
	//			ss.RowNew = m_nSpreadCellFocusPos[m_nTabNum];
	//
	//			LPSS_LEAVECELL lpleave = &ss;
	//			OnLeaveCellFpspread1(0, (LPARAM)lpleave);
	//
	//			if (pMsg->wParam != VK_TAB)
	//			{
	//				if (m_nTabNum == 0)
	//				{
	//					//DisplayChangedData();
	//					if (m_nSpreadCellFocusPos[0] < 16) // Total Rows
	//					{
	//						if (pGlobalDoc->m_bUseCombo && m_nSpreadCellFocusPos[0] == 8)	//150611 hjc add
	//							m_nSpreadCellFocusPos[0] = m_nSpreadCellFocusPos[0] + 3; //Complete Editing Without Error.
	//						else
	//							m_nSpreadCellFocusPos[0] = m_nSpreadCellFocusPos[0] + 1; //Complete Editing Without Error.
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[0] = 1; //Complete Editing Without Error. -> First Pos.
	//					}
	//					//DisplaySelectRow();
	//				}
	//				else if (m_nTabNum == 1)
	//				{
	//					//DisplayChangedData();
	//					if (m_nSpreadCellFocusPos[1] < 16) // Total Rows
	//					{
	//						if (pGlobalDoc->m_bUseCombo && m_nSpreadCellFocusPos[1] == 8)	//150611 hjc add
	//							m_nSpreadCellFocusPos[1] = m_nSpreadCellFocusPos[1] + 3; //Complete Editing Without Error.
	//						else
	//							m_nSpreadCellFocusPos[1] = m_nSpreadCellFocusPos[1] + 1; //Complete Editing Without Error.
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[1] = 1; //Complete Editing Without Error. -> First Pos.
	//					}
	//					//DisplaySelectRow();
	//				}
	//				else if (m_nTabNum == 2)
	//				{
	//					//DisplayChangedData();
	//					if (m_nSpreadCellFocusPos[2] < 9)
	//					{
	//						if (pGlobalDoc->m_bUseCombo && m_nSpreadCellFocusPos[2] == 4)	//150611 hjc add
	//							m_nSpreadCellFocusPos[2] = m_nSpreadCellFocusPos[2] + 2; //Complete Editing Without Error.
	//						else
	//							m_nSpreadCellFocusPos[2] = m_nSpreadCellFocusPos[2] + 1; //Complete Editing Without Error.
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[2] = 1; //Complete Editing Without Error. -> First Pos.
	//					}
	//					//DisplaySelectRow();
	//				}
	//				else if (m_nTabNum == 3)		//20100322 hjc add
	//				{
	//					//DisplayChangedData();
	//					int nMax = 12;
	//
	//					if (SpecData.bEnableCharInspection)
	//						nMax = 15;
	//
	//					if (m_nSpreadCellFocusPos[3] < nMax) // Total Rows		//jun 20120903 for LG_CCL-Inspector
	//					{
	//						if (m_nSpreadCellFocusPos[3] == 1 || m_nSpreadCellFocusPos[3] == 4 || m_nSpreadCellFocusPos[3] == 7)
	//						{
	//							m_nSpreadCellFocusPos[3] = m_nSpreadCellFocusPos[3] + 2; //Complete Editing Without Error.
	//						}
	//						else
	//						{
	//							m_nSpreadCellFocusPos[3] = m_nSpreadCellFocusPos[3] + 1; //Complete Editing Without Error.
	//						}
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[3] = 1; //Complete Editing Without Error. -> First Pos.
	//					}
	//					//DisplaySelectRow();
	//				}
	//				else if (m_nTabNum == 4)
	//				{
	//					//DisplayChangedData();
	//					if (m_nSpreadCellFocusPos[4] < 22) // Total Rows
	//					{
	//						if (m_nSpreadCellFocusPos[4] == 6 || m_nSpreadCellFocusPos[4] == 8 || m_nSpreadCellFocusPos[4] == 11
	//							|| m_nSpreadCellFocusPos[4] == 15 || m_nSpreadCellFocusPos[4] == 17 || m_nSpreadCellFocusPos[4] == 20)
	//						{
	//							m_nSpreadCellFocusPos[4] = m_nSpreadCellFocusPos[4] + 2; //Complete Editing Without Error.
	//						}
	//						else
	//						{
	//							m_nSpreadCellFocusPos[4] = m_nSpreadCellFocusPos[4] + 1; //Complete Editing Without Error.
	//						}
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[4] = 1; //Complete Editing Without Error. -> First Pos.
	//					}
	//					//DisplaySelectRow();
	//				}
	//				else if (m_nTabNum == 5)
	//				{
	//					//DisplayChangedData();
	//					if (m_nSpreadCellFocusPos[5] < 18)
	//					{
	//
	//						//20090311 hjc
	//						if (m_nSpreadCellFocusPos[5] == 6 || m_nSpreadCellFocusPos[5] == 8)
	//							m_nSpreadCellFocusPos[5] = m_nSpreadCellFocusPos[5] + 2; //Complete Editing Without Error.
	//						else
	//							m_nSpreadCellFocusPos[5] = m_nSpreadCellFocusPos[5] + 1; //Complete Editing Without Error.
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[5] = 1; //Complete Editing Without Error. -> First Pos.
	//					}
	//					//DisplaySelectRow();
	//				}
	//				else if (m_nTabNum == 6)
	//				{
	//					//DisplayChangedData();
	//					if (m_nSpreadCellFocusPos[6] < 15)
	//					{
	//						m_nSpreadCellFocusPos[6] = m_nSpreadCellFocusPos[6] + 1; //Complete Editing Without Error.
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[6] = 1; //Complete Editing Without Error. -> First Pos.
	//					}
	//					//DisplaySelectRow();
	//				}
	//				else if (m_nTabNum == 7)
	//				{
	//					//DisplayChangedData();
	//					if (m_nSpreadCellFocusPos[7] < 7)
	//					{
	//						if (m_nSpreadCellFocusPos[7] == 3 || m_nSpreadCellFocusPos[7] == 6)	//20100210 hjc mod
	//							m_nSpreadCellFocusPos[7] = m_nSpreadCellFocusPos[7] + 2; //Complete Editing Without Error.
	//						else
	//							m_nSpreadCellFocusPos[7] = m_nSpreadCellFocusPos[7] + 1; //Complete Editing Without Error.
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[7] = 1; //Complete Editing Without Error. -> First Pos.
	//					}
	//					//DisplaySelectRow();
	//				}
	//
	//				RefreshSheetOnChanging();
	//				if (pMsg->wParam == VK_RETURN && m_Spread.GetEditMode() == FALSE)
	//					m_Spread.SetEditMode(TRUE);
	//				//DisplaySelectRow();
	//			}
	//			/*
	//			if(m_nTabNum == 0)
	//			{
	//			m_tabDlgInspection.SetCurSel(0);
	//			DisplaySpread(0);
	//			//RefreshSheetOnChanging();
	//			}
	//			if(m_nTabNum == 1)
	//			{
	//			m_tabDlgInspection.SetCurSel(1);
	//			DisplaySpread(1);
	//			//RefreshSheetOnChanging();
	//			}
	//			else if(m_nTabNum == 2)
	//			{
	//			m_tabDlgInspection.SetCurSel(2);
	//			DisplaySpread(2);
	//			//RefreshSheetOnChanging();
	//			}
	//			else if(m_nTabNum == 3)
	//			{
	//			m_tabDlgInspection.SetCurSel(3);
	//			DisplaySpread(3);
	//			//RefreshSheetOnChanging();
	//			}
	//			else if(m_nTabNum == 4)
	//			{
	//			m_tabDlgInspection.SetCurSel(4);
	//			DisplaySpread(4);
	//			//RefreshSheetOnChanging();
	//			}
	//			else if(m_nTabNum == 5)
	//			{
	//			m_tabDlgInspection.SetCurSel(5);
	//			DisplaySpread(5);
	//			//RefreshSheetOnChanging();
	//			}
	//			else if(m_nTabNum == 6)
	//			{
	//			m_tabDlgInspection.SetCurSel(6);
	//			DisplaySpread(6);
	//			//RefreshSheetOnChanging();
	//			}
	//			else if(m_nTabNum == 7)		//20100322 hjc add
	//			{
	//			m_tabDlgInspection.SetCurSel(7);
	//			DisplaySpread(7);
	//			//RefreshSheetOnChanging();
	//			}
	//			*/
	//			return TRUE;
	//		}
	//	}
	//
	//	if (0 && m_Spread.m_pSpread != NULL && pMsg->hwnd == GetDlgItem(IDC_FPSPREAD_SPEC1)->GetSafeHwnd())
	//	{
	//		if (pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_RBUTTONDOWN || pMsg->message == WM_MBUTTONDOWN || pMsg->message == WM_LBUTTONDBLCLK || pMsg->message == WM_RBUTTONDBLCLK)
	//		{
	//			m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	//			RECT rt;
	//			m_Spread.m_pSpread->GetWindowRect(&rt);
	//			long x = pMsg->pt.x - rt.left;
	//			long y = pMsg->pt.y - rt.top;
	//			OnMouseDownFpspread1(0, 0, x, y);
	//		}
	//		int jjj = 0;
	//	}
	//
	//
	//	if (pMsg->message != WM_KEYDOWN)
	//	{
	//		if (pMsg->message == WM_LBUTTONDOWN)
	//		{
	//			pGlobalDoc->m_bRestedMotion = FALSE;
	//			pGlobalDoc->m_dCurrSystemTime = pGlobalDoc->m_dRestedSystemTime = GetTickCount64(); //pGlobalView->GetSystemTimeVal();
	//		}
	//		return CDialog::PreTranslateMessage(pMsg);
	//	}
	//
	//	if ((pMsg->lParam & 0x40000000) == 0 && pMsg->message == WM_KEYDOWN)
	//	{
	//		pGlobalDoc->m_bRestedMotion = FALSE;
	//		pGlobalDoc->m_dCurrSystemTime = pGlobalDoc->m_dRestedSystemTime = GetTickCount64(); //pGlobalView->GetSystemTimeVal();
	//
	//		switch (pMsg->wParam)
	//		{
	//		case 229:
	//			return TRUE;
	//		case 0xBD: // '-'
	//				   //case 0x6D:
	//			if (g_nCustomerCompany == IBIDEN_GAMA)
	//			{
	//				if (pMsg->hwnd == pGlobalView->GetDlgItem(IDC_LOT_EDIT)->m_hWnd ||
	//					pMsg->hwnd == pGlobalView->GetDlgItem(IDC_PANNEL1_EDIT)->m_hWnd ||
	//					pMsg->hwnd == pGlobalView->GetDlgItem(IDC_PANNEL2_EDIT)->m_hWnd)
	//					return CDialog::PreTranslateMessage(pMsg);
	//			}
	//			else
	//			{
	//				if (pMsg->hwnd == pGlobalView->GetDlgItem(IDC_LOT_EDIT)->m_hWnd ||
	//					pMsg->hwnd == pGlobalView->GetDlgItem(IDC_PANNEL_EDIT)->m_hWnd)
	//					return CDialog::PreTranslateMessage(pMsg);
	//			}
	//
	//			if (GetKeyState(VK_CONTROL) < 0) // Ctrl ≈∞∞° ¥≠∑¡¡ÅEªÛ≈¬
	//			{
	//				pGlobalView->m_pDlgLiveImage->ChangeZoomRatio(MINUS);
	//				return TRUE;
	//			}
	//			break;
	//
	//		case 0xBB: // '+'
	//				   //case 0x6B:
	//			if (g_nCustomerCompany == IBIDEN_GAMA)
	//			{
	//				if (pMsg->hwnd == pGlobalView->GetDlgItem(IDC_LOT_EDIT)->m_hWnd ||
	//					pMsg->hwnd == pGlobalView->GetDlgItem(IDC_PANNEL1_EDIT)->m_hWnd ||
	//					pMsg->hwnd == pGlobalView->GetDlgItem(IDC_PANNEL2_EDIT)->m_hWnd)
	//					return CDialog::PreTranslateMessage(pMsg);
	//			}
	//			else
	//			{
	//				if (pMsg->hwnd == pGlobalView->GetDlgItem(IDC_LOT_EDIT)->m_hWnd ||
	//					pMsg->hwnd == pGlobalView->GetDlgItem(IDC_PANNEL_EDIT)->m_hWnd)
	//					return CDialog::PreTranslateMessage(pMsg);
	//			}
	//
	//			if (GetKeyState(VK_CONTROL) < 0) // Ctrl ≈∞∞° ¥≠∑¡¡ÅEªÛ≈¬
	//			{
	//				pGlobalView->m_pDlgLiveImage->ChangeZoomRatio(PLUS);
	//				return TRUE;
	//			}
	//			break;
	//		case VK_TAB: // Spec Tab or Print
	//			if (GetKeyState(VK_CONTROL) < 0) // Ctrl ≈∞∞° ¥≠∑¡¡ÅEªÛ≈¬
	//			{
	//				//if(!pGlobalView->WndToBmp.PrintWindowFit("CaptureWnd.bmp",this))	
	//				if (!pGlobalView->WndToBmp.WriteWindowToDIB(_T("CaptureWnd.bmp"), this))
	//				{
	//					// 2009-04-02 jsy
	//					/*
	//					AfxMessageBox("Screen Capture Fail",MB_ICONWARNING|MB_OK);
	//					*/
	//					pGlobalView->m_strAfxMsg = _T("[MSG235] ") + pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "AFX_MSG", "PreTranslateMessage_P1_M1");
	//					AfxMessageBox(pGlobalView->m_strAfxMsg, MB_ICONWARNING | MB_OK);
	//				}
	//				return TRUE;
	//			}
	//			else
	//			{
	//
	//			}
	//			break;
	//		case 73:	// Alphabet 'I' or 'i'
	//			pGlobalView->PostMessage(WM_THB_ZOOMIN, (WPARAM)0, (LPARAM)0);
	//			break;
	//		case 79:	// Alphabet 'O' or 'o'
	//			pGlobalView->PostMessage(WM_THB_ZOOMOUT, (WPARAM)0, (LPARAM)0);
	//			break;
	//#if MACHINE_MODEL == INSMART_GM4000
	//		case VK_F1:
	//			pGlobalView->GetButtonItem(IDC_BTN_WORK_PREPARE)->SetValue(TRUE);
	//			return TRUE;
	//
	//		case VK_F2:
	//			pGlobalView->GetButtonItem(IDC_BTN_INSPECTVIEW)->SetValue(TRUE);
	//			return TRUE;
	//
	//		case VK_F3:
	//			if (((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_VERIFYVIEW))->IsWindowEnabled())
	//				((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_VERIFYVIEW))->SetValue(TRUE);
	//			return TRUE;
	//
	//		case VK_F4:
	//			((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_SPECVIEW))->SetValue(TRUE);
	//			return TRUE;
	//
	//		case VK_F5:
	//			((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_CALIBVIEW))->SetValue(TRUE);
	//			return TRUE;
	//
	//		case VK_F6:
	//			((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_VERIFYMASKVIEW))->SetValue(TRUE);
	//			return TRUE;
	//
	//		case VK_F7:
	//			((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_ROIGRABVIEW))->SetValue(TRUE);
	//			return TRUE;
	//#else
	//		case VK_F1:
	//			pGlobalView->GetButtonItem(IDC_BTN_INSPECTVIEW)->SetValue(TRUE);
	//			return TRUE;
	//
	//		case VK_F2:
	//			if (((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_VERIFYVIEW))->IsWindowEnabled())
	//				((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_VERIFYVIEW))->SetValue(TRUE);
	//			return TRUE;
	//
	//		case VK_F3:
	//			((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_SPECVIEW))->SetValue(TRUE);
	//			return TRUE;
	//
	//		case VK_F4:
	//			((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_CALIBVIEW))->SetValue(TRUE);
	//			return TRUE;
	//
	//		case VK_F5:
	//			((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_VERIFYMASKVIEW))->SetValue(TRUE);
	//			return TRUE;
	//
	//		case VK_F6:
	//			((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_ROIGRABVIEW))->SetValue(TRUE);
	//			return TRUE;
	//#endif
	//
	//		case VK_F11:
	//			if (!((CGvisAOIView*)FromHandle(m_hParentWnd))->m_bVK_F11)
	//			{
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_bVK_F11 = TRUE;
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Lot_Edit.SetFocus();
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Lot_Edit.SetSel(0, -1);
	//			}
	//			else
	//			{
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_bVK_F11 = FALSE;
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Serial_Edit.SetFocus();
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Serial_Edit.SetSel(0, -1);
	//			}
	//			break;
	//
	//		case VK_F12: // ªÁøÅE“∞?
	//			break;
	//
	//		case VK_RETURN:
	//			if (pMsg->hwnd == ((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Lot_Edit.m_hWnd)
	//			{
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Serial_Edit.SetFocus();
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Serial_Edit.SetSel(0, -1);
	//			}
	//			else if (pMsg->hwnd == ((CGvisAOIView*)FromHandle(m_hParentWnd))->m_LayerCombo.m_hWnd)
	//			{
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Lot_Edit.SetFocus();
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->m_Lot_Edit.SetSel(0, -1);
	//				((CGvisAOIView*)FromHandle(m_hParentWnd))->DisplayParameter();
	//			}
	//
	//			if (m_nTabNum == 0)
	//			{
	//				if (m_nSpreadCellFocusPos[0] < 16) // Total Rows
	//				{
	//					if (pGlobalDoc->m_bUseCombo && m_nSpreadCellFocusPos[0] == 8)	//150611 hjc add
	//						m_nSpreadCellFocusPos[0] = m_nSpreadCellFocusPos[0] + 3; //Complete Editing Without Error.
	//					else
	//						m_nSpreadCellFocusPos[0] = m_nSpreadCellFocusPos[0] + 1; //Complete Editing Without Error.
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[0] = 1; //Complete Editing Without Error. -> First Pos.
	//				}
	//
	//			}
	//			else if (m_nTabNum == 1)
	//			{
	//				if (m_nSpreadCellFocusPos[1] < 16) // Total Rows
	//				{
	//					if (pGlobalDoc->m_bUseCombo && m_nSpreadCellFocusPos[1] == 8)	//150611 hjc add
	//						m_nSpreadCellFocusPos[1] = m_nSpreadCellFocusPos[1] + 3; //Complete Editing Without Error.
	//					else
	//						m_nSpreadCellFocusPos[1] = m_nSpreadCellFocusPos[1] + 1; //Complete Editing Without Error.
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[1] = 1; //Complete Editing Without Error. -> First Pos.
	//				}
	//			}
	//			else if (m_nTabNum == 2)
	//			{
	//				if (m_nSpreadCellFocusPos[2] < 9)
	//				{
	//					if (pGlobalDoc->m_bUseCombo && m_nSpreadCellFocusPos[2] == 4)	//150611 hjc add
	//						m_nSpreadCellFocusPos[2] = m_nSpreadCellFocusPos[2] + 2; //Complete Editing Without Error.
	//					else
	//						m_nSpreadCellFocusPos[2] = m_nSpreadCellFocusPos[2] + 1; //Complete Editing Without Error.
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[2] = 1; //Complete Editing Without Error. -> First Pos.
	//				}
	//
	//			}
	//			else if (m_nTabNum == 3)		//20100322 hjc add
	//			{
	//				if (m_nSpreadCellFocusPos[3] < 12) // Total Rows		//jun 20120903 for LG_CCL-Inspector
	//				{
	//					if (m_nSpreadCellFocusPos[3] == 1 || m_nSpreadCellFocusPos[3] == 4 || m_nSpreadCellFocusPos[3] == 7)
	//					{
	//						m_nSpreadCellFocusPos[3] = m_nSpreadCellFocusPos[3] + 2; //Complete Editing Without Error.
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[3] = m_nSpreadCellFocusPos[3] + 1; //Complete Editing Without Error.
	//					}
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[3] = 1; //Complete Editing Without Error. -> First Pos.
	//				}
	//
	//			}
	//			else if (m_nTabNum == 4)
	//			{
	//				if (m_nSpreadCellFocusPos[4] < 22) // Total Rows
	//				{
	//					if (m_nSpreadCellFocusPos[4] == 6 || m_nSpreadCellFocusPos[4] == 8 || m_nSpreadCellFocusPos[4] == 11
	//						|| m_nSpreadCellFocusPos[4] == 15 || m_nSpreadCellFocusPos[4] == 17 || m_nSpreadCellFocusPos[4] == 20)
	//					{
	//						m_nSpreadCellFocusPos[4] = m_nSpreadCellFocusPos[4] + 2; //Complete Editing Without Error.
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[4] = m_nSpreadCellFocusPos[4] + 1; //Complete Editing Without Error.
	//					}
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[4] = 1; //Complete Editing Without Error. -> First Pos.
	//				}
	//			}
	//			else if (m_nTabNum == 5)
	//			{
	//				if (m_nSpreadCellFocusPos[5] < 18)
	//				{
	//
	//					//20090311 hjc
	//					if (m_nSpreadCellFocusPos[5] == 6 || m_nSpreadCellFocusPos[5] == 8)
	//						m_nSpreadCellFocusPos[5] = m_nSpreadCellFocusPos[5] + 2; //Complete Editing Without Error.
	//					else
	//						m_nSpreadCellFocusPos[5] = m_nSpreadCellFocusPos[5] + 1; //Complete Editing Without Error.
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[5] = 1; //Complete Editing Without Error. -> First Pos.
	//				}
	//			}
	//			else if (m_nTabNum == 6)
	//			{
	//				if (m_nSpreadCellFocusPos[6] < 15)
	//				{
	//					m_nSpreadCellFocusPos[6] = m_nSpreadCellFocusPos[6] + 1; //Complete Editing Without Error.
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[6] = 1; //Complete Editing Without Error. -> First Pos.
	//				}
	//			}
	//			else if (m_nTabNum == 7)
	//			{
	//				if (m_nSpreadCellFocusPos[7] < 7)
	//				{
	//					if (m_nSpreadCellFocusPos[7] == 3 || m_nSpreadCellFocusPos[7] == 6)	//20100210 hjc mod
	//						m_nSpreadCellFocusPos[7] = m_nSpreadCellFocusPos[7] + 2; //Complete Editing Without Error.
	//					else
	//						m_nSpreadCellFocusPos[7] = m_nSpreadCellFocusPos[7] + 1; //Complete Editing Without Error.
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[7] = 1; //Complete Editing Without Error. -> First Pos.
	//				}
	//			}
	//			break;
	//
	//		case VK_DOWN:
	//			if (m_nTabNum == 0)
	//			{
	//				if (m_nSpreadCellFocusPos[0] < 16) // Total Rows
	//				{
	//					if (pGlobalDoc->m_bUseCombo && m_nSpreadCellFocusPos[0] == 8)	//150611 hjc add
	//						m_nSpreadCellFocusPos[0] = m_nSpreadCellFocusPos[0] + 3; //Complete Editing Without Error.
	//					else
	//						m_nSpreadCellFocusPos[0] = m_nSpreadCellFocusPos[0] + 1; //Complete Editing Without Error.
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[0] = 1; //Complete Editing Without Error. -> First Pos.
	//					RefreshSheetOnChanging();
	//				}
	//
	//			}
	//			else if (m_nTabNum == 1)
	//			{
	//				if (m_nSpreadCellFocusPos[1] < 16) // Total Rows
	//				{
	//					if (pGlobalDoc->m_bUseCombo && m_nSpreadCellFocusPos[1] == 8)	//150611 hjc add
	//						m_nSpreadCellFocusPos[1] = m_nSpreadCellFocusPos[1] + 3; //Complete Editing Without Error.
	//					else
	//						m_nSpreadCellFocusPos[1] = m_nSpreadCellFocusPos[1] + 1; //Complete Editing Without Error.
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[1] = 1; //Complete Editing Without Error. -> First Pos.
	//					RefreshSheetOnChanging();
	//				}
	//			}
	//			else if (m_nTabNum == 2)
	//			{
	//				if (m_nSpreadCellFocusPos[2] < 9)
	//				{
	//					if (pGlobalDoc->m_bUseCombo && m_nSpreadCellFocusPos[2] == 4)	//150611 hjc add
	//						m_nSpreadCellFocusPos[2] = m_nSpreadCellFocusPos[2] + 2; //Complete Editing Without Error.
	//					else
	//						m_nSpreadCellFocusPos[2] = m_nSpreadCellFocusPos[2] + 1; //Complete Editing Without Error.
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[2] = 1; //Complete Editing Without Error. -> First Pos.
	//					RefreshSheetOnChanging();
	//				}
	//
	//			}
	//			else if (m_nTabNum == 3)		//20100322 hjc add
	//			{
	//				if (m_nSpreadCellFocusPos[3] < 12) // Total Rows		//jun 20120903 for LG_CCL-Inspector
	//				{
	//					if (m_nSpreadCellFocusPos[3] == 1 || m_nSpreadCellFocusPos[3] == 4 || m_nSpreadCellFocusPos[3] == 7)
	//					{
	//						m_nSpreadCellFocusPos[3] = m_nSpreadCellFocusPos[3] + 2; //Complete Editing Without Error.
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[3] = m_nSpreadCellFocusPos[3] + 1; //Complete Editing Without Error.
	//					}
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[3] = 1; //Complete Editing Without Error. -> First Pos.
	//					RefreshSheetOnChanging();
	//				}
	//
	//			}
	//			else if (m_nTabNum == 4)
	//			{
	//				if (m_nSpreadCellFocusPos[4] < 22) // Total Rows
	//				{
	//					if (m_nSpreadCellFocusPos[4] == 6 || m_nSpreadCellFocusPos[4] == 8 || m_nSpreadCellFocusPos[4] == 11
	//						|| m_nSpreadCellFocusPos[4] == 15 || m_nSpreadCellFocusPos[4] == 17 || m_nSpreadCellFocusPos[4] == 20)
	//					{
	//						m_nSpreadCellFocusPos[4] = m_nSpreadCellFocusPos[4] + 2; //Complete Editing Without Error.
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[4] = m_nSpreadCellFocusPos[4] + 1; //Complete Editing Without Error.
	//					}
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[4] = 1; //Complete Editing Without Error. -> First Pos.
	//					RefreshSheetOnChanging();
	//				}
	//
	//			}
	//			else if (m_nTabNum == 5)
	//			{
	//				if (m_nSpreadCellFocusPos[5] < 18)
	//				{
	//					//20090311 hjc
	//					if (m_nSpreadCellFocusPos[5] == 6 || m_nSpreadCellFocusPos[5] == 8)
	//						m_nSpreadCellFocusPos[5] = m_nSpreadCellFocusPos[5] + 2; //Complete Editing Without Error.
	//					else
	//						m_nSpreadCellFocusPos[5] = m_nSpreadCellFocusPos[5] + 1; //Complete Editing Without Error.
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[5] = 1; //Complete Editing Without Error. -> First Pos.
	//					RefreshSheetOnChanging();
	//				}
	//			}
	//			else if (m_nTabNum == 6)
	//			{
	//				if (m_nSpreadCellFocusPos[6] < 15)
	//				{
	//					m_nSpreadCellFocusPos[6] = m_nSpreadCellFocusPos[6] + 1; //Complete Editing Without Error.
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[6] = 1; //Complete Editing Without Error. -> First Pos.
	//					RefreshSheetOnChanging();
	//				}
	//			}
	//			else if (m_nTabNum == 7)
	//			{
	//				if (m_nSpreadCellFocusPos[7] < 7)
	//				{
	//					if (m_nSpreadCellFocusPos[7] == 3 || m_nSpreadCellFocusPos[7] == 6)	//20100210 hjc mod
	//						m_nSpreadCellFocusPos[7] = m_nSpreadCellFocusPos[7] + 2; //Complete Editing Without Error.
	//					else
	//						m_nSpreadCellFocusPos[7] = m_nSpreadCellFocusPos[7] + 1; //Complete Editing Without Error.
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[7] = 1; //Complete Editing Without Error. -> First Pos.
	//												  //20090216 chg
	//					RefreshSheetOnChanging();
	//				}
	//			}
	//
	//			break;
	//
	//		case VK_PRIOR: //pgup lgh add 130515
	//			if (!pGlobalDoc->m_bTesting)
	//			{
	//				if (pGlobalDoc->m_DefectListItem[pGlobalView->m_nSelectDefectListID].GetCount()>0)
	//				{
	//					((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_THUMBNAIL_PACK_PAGEUP))->SetValue(TRUE);
	//					pGlobalView->MoveThumbPos(0);
	//					return TRUE;
	//				}
	//			}
	//			break;
	//
	//		case VK_NEXT: //pgdown lgh add 130515
	//			if (!pGlobalDoc->m_bTesting)
	//			{
	//				if (pGlobalDoc->m_DefectListItem[pGlobalView->m_nSelectDefectListID].GetCount()>0)
	//				{
	//					((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_THUMBNAIL_PACK_PAGEDOWN))->SetValue(TRUE);
	//					pGlobalView->MoveThumbPos(0);
	//					return TRUE;
	//				}
	//			}
	//			break;
	//
	//
	//		case VK_UP:
	//			if (m_nTabNum == 0)
	//			{
	//				if (m_nSpreadCellFocusPos[0] == 1)
	//				{
	//					m_nSpreadCellFocusPos[0] = 16; //Complete Editing Without Error. -> Last Pos.
	//					RefreshSheetOnChanging();
	//				}
	//				else
	//				{
	//					if (pGlobalDoc->m_bUseCombo && m_nSpreadCellFocusPos[0] == 11)	//150611 hjc add
	//						m_nSpreadCellFocusPos[0] = m_nSpreadCellFocusPos[0] - 3;
	//					else
	//						m_nSpreadCellFocusPos[0] = m_nSpreadCellFocusPos[0] - 1; //Complete Editing Without Error.
	//				}
	//			}
	//			else if (m_nTabNum == 1)
	//			{
	//				if (m_nSpreadCellFocusPos[1] == 1)
	//				{
	//					m_nSpreadCellFocusPos[1] = 16; //Complete Editing Without Error. -> Last Pos.
	//					RefreshSheetOnChanging();
	//				}
	//				else
	//				{
	//					if (pGlobalDoc->m_bUseCombo && m_nSpreadCellFocusPos[1] == 11)	//150611 hjc add
	//						m_nSpreadCellFocusPos[1] = m_nSpreadCellFocusPos[1] - 3;
	//					else
	//						m_nSpreadCellFocusPos[1] = m_nSpreadCellFocusPos[1] - 1; //Complete Editing Without Error.
	//				}
	//			}
	//			else if (m_nTabNum == 2)
	//			{
	//				if (m_nSpreadCellFocusPos[2] == 1)
	//				{
	//					m_nSpreadCellFocusPos[2] = 9; //Complete Editing Without Error. -> Last Pos.
	//					RefreshSheetOnChanging();
	//				}
	//				else
	//				{
	//					if (pGlobalDoc->m_bUseCombo && m_nSpreadCellFocusPos[2] == 6)	//150611 hjc add
	//						m_nSpreadCellFocusPos[2] = m_nSpreadCellFocusPos[2] - 2;
	//					else
	//						m_nSpreadCellFocusPos[2] = m_nSpreadCellFocusPos[2] - 1; //Complete Editing Without Error.
	//				}
	//			}
	//			else if (m_nTabNum == 3)		//20100322 hjc add
	//			{
	//				if (m_nSpreadCellFocusPos[3] == 1)
	//				{
	//					m_nSpreadCellFocusPos[3] = 12; //Complete Editing Without Error. -> Last Pos.	//jun 20120903 for LG_CCL-Inspector
	//					RefreshSheetOnChanging();
	//				}
	//				else
	//				{
	//					if (m_nSpreadCellFocusPos[3] == 3 || m_nSpreadCellFocusPos[3] == 6 || m_nSpreadCellFocusPos[3] == 9)
	//					{
	//						m_nSpreadCellFocusPos[3] = m_nSpreadCellFocusPos[3] - 2; //Complete Editing Without Error.
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[3] = m_nSpreadCellFocusPos[3] - 1; //Complete Editing Without Error.
	//					}
	//				}
	//			}
	//			else if (m_nTabNum == 4)
	//			{
	//				if (m_nSpreadCellFocusPos[4] == 1)
	//				{
	//					m_nSpreadCellFocusPos[4] = 22; //Complete Editing Without Error. -> Last Pos.
	//					RefreshSheetOnChanging();
	//				}
	//				else
	//				{
	//					if (m_nSpreadCellFocusPos[4] == 8 || m_nSpreadCellFocusPos[4] == 10 || m_nSpreadCellFocusPos[4] == 13
	//						|| m_nSpreadCellFocusPos[4] == 17 || m_nSpreadCellFocusPos[4] == 19 || m_nSpreadCellFocusPos[4] == 22)
	//					{
	//						m_nSpreadCellFocusPos[4] = m_nSpreadCellFocusPos[4] - 2; //Complete Editing Without Error.
	//					}
	//					else
	//					{
	//						m_nSpreadCellFocusPos[4] = m_nSpreadCellFocusPos[4] - 1; //Complete Editing Without Error.
	//					}
	//				}
	//			}
	//			else if (m_nTabNum == 5)
	//			{
	//				if (m_nSpreadCellFocusPos[5] == 1)
	//				{
	//					m_nSpreadCellFocusPos[5] = 18; //Complete Editing Without Error. -> Last Pos.
	//					RefreshSheetOnChanging();
	//				}
	//				else
	//				{
	//					//20090311 hjc
	//					if (m_nSpreadCellFocusPos[5] == 8 || m_nSpreadCellFocusPos[5] == 10)
	//					{
	//						m_nSpreadCellFocusPos[5] = m_nSpreadCellFocusPos[5] - 2; //Complete Editing Without Error.
	//
	//					}
	//					else
	//						m_nSpreadCellFocusPos[5] = m_nSpreadCellFocusPos[5] - 1; //Complete Editing Without Error.
	//				}
	//			}
	//			else if (m_nTabNum == 6)
	//			{
	//				if (m_nSpreadCellFocusPos[6] == 1)
	//				{
	//					m_nSpreadCellFocusPos[6] = 15; //Complete Editing Without Error. -> Last Pos.
	//					RefreshSheetOnChanging();
	//				}
	//				else
	//				{
	//					m_nSpreadCellFocusPos[6] = m_nSpreadCellFocusPos[6] - 1; //Complete Editing Without Error.
	//				}
	//			}
	//			else if (m_nTabNum == 7)
	//			{
	//				//20090216 chg
	//				if (m_nSpreadCellFocusPos[7] == 1) //Complete Editing Without Error. -> First Pos.)
	//				{
	//					m_nSpreadCellFocusPos[7] = 8; //Complete Editing Without Error. -> Last Pos.
	//					RefreshSheetOnChanging();
	//				}
	//				else
	//				{
	//					if (m_nSpreadCellFocusPos[7] == 7)
	//						m_nSpreadCellFocusPos[7] = m_nSpreadCellFocusPos[7] - 2; //Complete Editing Without Error.
	//					else
	//						m_nSpreadCellFocusPos[7] = m_nSpreadCellFocusPos[7] - 1; //Complete Editing Without Error.
	//				}
	//				//-------------
	//			}
	//
	//			break;
	//
	//			/////////
	//		case VK_ESCAPE:
	//			((CGvisAOIView*)FromHandle(pGlobalView->m_hWnd))->GetButtonItem(IDC_BTN_INSPECTVIEW)->SetValue(TRUE);
	//			return TRUE;
	//
	//		case 'S':
	//			//		case 's':
	//			//OnClickSpecSave();
	//			break;
	//
	//		case VK_HOME:
	//			pMotion->GotoLoadingPosition(WAIT);
	//#if CUSTOMER_COMPANY == SUMITOMO	//121031 hjc add
	//			pGlobalDoc->m_bTowerLampFlag = FALSE;
	//			pGlobalView->TowerLampControl(TOWER_LAMP_GREEN);
	//#endif
	//			pGlobalView->Air_Restore();
	//			break;
	//
	//		case 'G':
	//			//	case 'g':
	//			if (GetKeyState(VK_CONTROL) < 0) // Ctrl ≈∞∞° ¥≠∑¡¡ÅEªÛ≈¬
	//			{
	//				if (g_nCustomerCompany == IBIDEN_GAMA)
	//				{
	//					if (pMsg->hwnd == pGlobalView->GetDlgItem(IDC_LOT_EDIT)->m_hWnd ||
	//						pMsg->hwnd == pGlobalView->GetDlgItem(IDC_PANNEL1_EDIT)->m_hWnd ||
	//						pMsg->hwnd == pGlobalView->GetDlgItem(IDC_PANNEL2_EDIT)->m_hWnd)
	//						return CDialog::PreTranslateMessage(pMsg);
	//				}
	//				else
	//				{
	//					if (pMsg->hwnd == pGlobalView->GetDlgItem(IDC_LOT_EDIT)->m_hWnd ||
	//						pMsg->hwnd == pGlobalView->GetDlgItem(IDC_PANNEL_EDIT)->m_hWnd)
	//						return CDialog::PreTranslateMessage(pMsg);
	//				}
	//
	//				pGlobalView->m_bChangedLiveImageBtnFlag = !pGlobalView->m_bChangedLiveImageBtnFlag;
	//				((CCustomCmdButton*)pGlobalView->GetButtonItem(IDC_BTN_MAP_COLOR_CAM))->SetValue(pGlobalView->m_bChangedLiveImageBtnFlag);
	//				return TRUE;
	//			}
	//			break;
	//
	//		case 'D':
	//			//	case 'd':
	//			if (GetKeyState(VK_CONTROL) < 0)
	//			{
	//				//161012 lgh
	//				pMainFrame->PostMessage(WM_USER_CONTROL_ACT, WM_IMAGE_SAVE, 0);
	//			}
	//			break;
	//
	//		case 'P': //130809 LGH ADD
	//			if (GetKeyState(VK_CONTROL) < 0)
	//			{
	//				pMainFrame->PostMessage(WM_USER_CONTROL_ACT, WM_CREATE, 'P');
	//			}
	//			else
	//			{
	//				pGlobalView->m_pDlgVerify->PostMessage(WM_USER_CONTROL_ACT, WM_KEYDOWN, 'P');
	//			}
	//			break;
	//
	//			//	Ctrl+Z	-> Standard Zoom (Zoom Axis)	//	20100609 ljh	//	20102225 ljh mod
	//		case 'Z':
	//			//	case 'z':
	//#ifdef ZOOM_AXIS
	//			if (GetKeyState(VK_CONTROL) < 0) {
	//				if (pMotion->GetPosSWLimitValue(ZOOM_AXIS) <= pGlobalView->m_pDlgZoomCtrl->m_dStandardZoom)	//20101130 hjc 
	//					pGlobalView->m_pDlgZoomCtrl->m_dStandardZoom = pMotion->GetPosSWLimitValue(ZOOM_AXIS) - 0.1f;
	//				//	double dTargetDegree = pGlobalView->m_pDlgLiveImage->MagToDegree(dTargetMag);
	//				pMotion->MoveZoomMotor(pGlobalView->m_pDlgZoomCtrl->m_dStandardZoom, ABS, NO_WAIT);
	//				return TRUE;
	//			}
	//#endif
	//			break;
	//			//	Ctrl+X	-> Magnify Zoom	(Zoom Axis)		//	20100609 ljh	//	20102225 ljh mod
	//		case 'X':
	//			//		case 'x':
	//#ifdef ZOOM_AXIS
	//			if (GetKeyState(VK_CONTROL) < 0) {
	//				if (pMotion->GetNegSWLimitValue(ZOOM_AXIS) >= pGlobalView->m_pDlgZoomCtrl->m_dMagnifyZoom)	//20101130 hjc 
	//					pGlobalView->m_pDlgZoomCtrl->m_dMagnifyZoom = pMotion->GetNegSWLimitValue(ZOOM_AXIS) + 0.1f;
	//				//	double dTargetDegree = pGlobalView->m_pDlgLiveImage->MagToDegree(dTargetMag);
	//				pMotion->MoveZoomMotor(pGlobalView->m_pDlgZoomCtrl->m_dMagnifyZoom, ABS, NO_WAIT);
	//				return TRUE;
	//			}
	//#endif
	//			break;
	//			//	Ctrl+W	-> Zoom Step Sub (Zoom Axis)	//	20100609 ljh
	//		case 'W':
	//			//		case 'w':
	//#ifdef ZOOM_AXIS
	//			if (GetKeyState(VK_CONTROL) < 0) {
	//				double dCurDegree = pMotion->GetActualPosition(ZOOM_AXIS) + 37.529;
	//				double dTargetDegree = pGlobalView->m_pDlgZoomCtrl->StepZoomDegree(dCurDegree, 0);
	//				pMotion->MoveZoomMotor(dTargetDegree - 37.529, ABS, NO_WAIT);
	//				return TRUE;
	//			}
	//#endif
	//			break;
	//			//	Ctrl+T	-> Zoom Step Add	(Zoom Axis)		//	20100609 ljh
	//		case 'T':
	//			//		case 't':
	//#ifdef ZOOM_AXIS
	//			if (GetKeyState(VK_CONTROL) < 0) {
	//				double dCurDegree = pMotion->GetActualPosition(ZOOM_AXIS) + 37.529;
	//				double dTargetDegree = pGlobalView->m_pDlgZoomCtrl->StepZoomDegree(dCurDegree, 1);
	//				pMotion->MoveZoomMotor(dTargetDegree - 37.529, ABS, NO_WAIT);
	//				return TRUE;
	//			}
	//#endif
	//			break;
	//
	//		case 'H':	// 20110726 ljh
	//					//		case 'h':
	//#ifdef AUTO_FOCUS_OPTION
	//#if SEPERATE_AXIS_AF != AF_ONLY_HEIGHT_AXIS
	//			if (pGlobalView->m_bViewDlgLiveImage)
	//				if (GetKeyState(VK_CONTROL) < 0) // Ctrl 
	//					pGlobalView->NewFullScanFocusAdjust(TRUE);
	//#endif
	//#endif
	//			break;
	//
	//		case 'F':	// 20110726 ljh	check;
	//					//	case 'f':
	//#ifdef AUTO_FOCUS_OPTION
	//#if SEPERATE_AXIS_AF != AF_ONLY_HEIGHT_AXIS
	//			if (pGlobalView->m_bViewDlgLiveImage)
	//				if (GetKeyState(VK_CONTROL) < 0) // Ctrl 
	//					pGlobalView->NewSmartFocusAdjust();
	//#endif
	//#endif
	//			break;
	//
	//		}
	//	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgSpec::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	//m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	//m_Spread.SetActiveCell(0, 0);
	//m_Spread.SetRetainSelBlock(FALSE);
	//m_Spread.ClearSelection();
	//this->SendMessage(WM_CONTROL_USER_MESSAGE, 0, 0);
	//*pResult = 0;
}

//LRESULT CDlgSpec::OnControlTabMessage(WPARAM wParam, LPARAM lParam)
//{
	/*
	if (wParam == 0)
	{
	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	TabRestore();
	}
	else if (wParam == 1)
	{
	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	m_Spread.SetFocus();
	}
	else if (wParam == 2)
	{
	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	RefreshSheetOnChanging();
	}
	else if (wParam == 3)
	{
	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	AtDlgShow();
	}
	else if (wParam == 4)
	{
	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	AtDlgHide();
	}
	else if (wParam == 5)
	{
	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	DisplaySpread(lParam);
	}
	*/
//	return 0;
//}


BOOL CDlgSpec::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: ø©±‚ø° ∆Øºˆ»≠µ» ƒ⁄µÂ∏¶ √ﬂ∞° π◊/∂«¥¬ ±‚∫ª ≈¨∑°Ω∫∏¶ »£√‚«’¥œ¥Ÿ.
	//Ω∫«¡∑πµÂ∑Œ∫Œ≈Õ ø¿¥¬ ¿Ã∫•∆Æ∏¶ πﬁ¥¬¥Ÿ
	if (LOWORD(wParam) == IDC_FPSPREAD_SPEC1)
	{
		long a = LOWORD(wParam);
		long b = HIWORD(wParam);
		TRACE("%d , %d\n", a, b);

		/*
		ON_MESSAGE( SSN_BUTTONDOWN, OnButtonClickedFpspreadDown)
		ON_MESSAGE( SSN_BUTTONUP, OnButtonClickedFpspreadUp)
		ON_MESSAGE( IDC_FPSPREAD1, -605 , OnMouseDownFpspread1)
		ON_MESSAGE( IDC_FPSPREAD1, -606 , OnMouseMoveFpspread1)
		*/

		switch (HIWORD(wParam))
		{
		case SSN_SETFOCUS://51
			break;
		case SSN_KILLFOCUS://52
			break;
		case SSN_INVALIDDATA://53
			break;
		case SSN_BLOCKSELECTED://54
			break;
		case SSN_BLOCKCHANGED://55
			break;
		case SSN_USERFORMULA://56
			break;
		case SSN_EXITNEXT://57
			break;
		case SSN_EXITPREV://58
			break;
		case SSN_BUTTONDOWN://59

			break;
		case SSN_BUTTONUP://60
						  //m_Spread.m_pSpread->GetActiveCell()
			OnButtonClickedFpspreadDown(0, 0);
			break;
		case SSN_TOPROWCHANGE://61
			break;
		case SSN_LEFTCOLCHANGE://62
			break;
		case SSN_TOPLEFTCHANGE://63
			break;
		case SSN_BLOCKDESELECTED://64
			break;
		}
	}

	return CDialog::OnCommand(wParam, lParam);
}

HBRUSH CDlgSpec::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr;
	// TODO: Change any attributes of the DC here
	switch (nCtlColor)
	{

	case CTLCOLOR_STATIC:
	case CTLCOLOR_DLG:
		pDC->SetBkMode(TRANSPARENT);
		return m_hDlgSpecBkBrush;

	case CTLCOLOR_EDIT:
	case CTLCOLOR_BTN:
	case CTLCOLOR_LISTBOX:
	case CTLCOLOR_MSGBOX:
	case CTLCOLOR_SCROLLBAR:
	default:
		hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

LRESULT CDlgSpec::OnKeyDownFpspread1(WPARAM wParam, LPARAM lParam)
{
	/*
	//	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	//wparam is control id
	WORD nVKey = LOWORD(lParam);
	WORD nShfit = HIWORD(lParam);
	// TODO: Add your control notification handler code here
	m_bKeyDown = TRUE;
	*/
	return 0;
}

LRESULT CDlgSpec::OnLeaveCellFpspread1(WPARAM wParam, LPARAM lParam)
{
	/*	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	LPSS_LEAVECELL info = (LPSS_LEAVECELL)lParam;

	SS_COORD NewCol = info->ColNew;
	SS_COORD NewRow = info->RowNew;
	SS_COORD Col = info->ColCurrent;
	SS_COORD Row = info->RowCurrent;

	// TODO: Add your control notification handler code here

	if (NewCol < 0 || NewRow < 0) return 0; // To Prevent Message Leaving MsgBox.

	switch (m_nTabNum)
	{
	case 7:
	switch (NewRow)
	{
	case 4:
	case 7:
	return 0;
	}
	break;
	}

	// Verify Normal Cell Value.

	CString strMsg, strTemp;

	if (NewCol)
	m_nSpreadCellFocusPos[m_nTabNum] = NewRow;

	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE); //160302 LGH ADD

	TRACE("OnLeaveCellFpspread1 %d %d , %d %d \n", NewCol, NewRow, Col, Row);
	switch (m_nTabNum)
	{
	case 0:
	if (Col == 1 && Row == 1)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(1);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[0][1] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (1 - 1)); // Bit Flag.
	}
	m_fNominalLine = (float)_ttof(strTemp);
	}
	if (Col == 1 && Row == 2)
	{

	m_Spread.SetCol(1);
	m_Spread.SetRow(2);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[0][2] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (Row - 1)); // Bit Flag.
	}
	m_fRealNormLine = (float)_ttof(strTemp);
	}
	if (Col == 1 && Row == 3)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(3);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}

	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[0][3] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (3 - 1)); // Bit Flag.
	}
	//20090216 chg
	m_nNickGray = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 4)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(4);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}

	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[0][4] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (4 - 1)); // Bit Flag.
	}
	m_nOpenGray = _ttoi(strTemp);
	}
	//150413 hjc add
	if (Col == 1 && Row == 5)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(5);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}

	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}


	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[0][5] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (5 - 1)); // Bit Flag.
	}
	m_nHalfSideNickDiffBrightGray = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 6)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(6);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[0][6] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (6 - 1)); // Bit Flag.
	}
	m_nHalfSideNickDiffDarkGray = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 7)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(7);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[0][7] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (7 - 1)); // Bit Flag.
	}
	m_nLeadOpenGray = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 8)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(8);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[0][8] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (8 - 1)); // Bit Flag.
	}
	m_fMinCheckWidth = _ttof(strTemp);

	}

	if (SpecData.nLineWidthGroupNum == 0 || AoiParam()->m_bUseMultilineSpecEx)
	{
	if (!pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	if (Col == 1 && Row == 9)	//150413 hjc add
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[0][9] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (9 - 1)); // Bit Flag.
	}
	m_nNickPercent[0] = _ttoi(strTemp);

	}
	if (Col == 1 && Row == 10)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(10);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[0][10] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (10 - 1)); // Bit Flag.
	}
	m_nProtrusionPercent[0] = _ttoi(strTemp);

	}
	}
	if (Col == 1 && Row == 11)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(11);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}
	if (_ttoi(strTemp) < 30 || _ttoi(strTemp) > 90)
	{
	strMsg.Format(_T("%s (30~90)%%%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}
	else
	{
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[0][11] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (11 - 1)); // Bit Flag.
	}
	}
	m_nNickNGFilterPercent[0] = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 12)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(12);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}

	if (_ttoi(strTemp) < 110 || _ttoi(strTemp) > 200)
	{
	strMsg.Format(_T("%s (110~200)%%%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}
	else
	{
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[0][12] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (12 - 1)); // Bit Flag.
	}
	}
	m_nExcsNGFilterPercent[0] = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 13)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(13);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[0][13] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (13 - 1)); // Bit Flag.
	}
	m_fLineWdDeltaGradViolation[0] = _ttof(strTemp);
	}
	if (Col == 1 && Row == 14)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(14);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[0][14] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (14 - 1)); // Bit Flag.
	}
	m_fExcsWdDeltaGradViolation[0] = _ttof(strTemp);
	}

	if (Col == 1 && Row == 15)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(15);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[0][15] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (15 - 1)); // Bit Flag.
	}
	m_fNarrowTraceViolation[0] = (float)_ttof(strTemp);
	}
	if (Col == 1 && Row == 16)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(16);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(0);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[0][16] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (16 - 1)); // Bit Flag.
	}
	m_fWideTraceViolation[0] = (float)_ttof(strTemp);
	}
	}

	if (m_bKeyDown)
	{
	m_bKeyDown = FALSE;
	RefreshSheetOnChanging();
	}

	break;

	case 1:
	if (Col == 1 && Row == 1)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(1);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][1] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (1 - 1)); // Bit Flag.
	}
	m_fNominalLine = (float)_ttof(strTemp);
	}
	if (Col == 1 && Row == 2)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(2);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][2] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (2 - 1)); // Bit Flag.
	}
	m_fRealNormLine = (float)_ttof(strTemp);
	}
	if (Col == 1 && Row == 3)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(3);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][3] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (3 - 1)); // Bit Flag.
	}
	m_nFineNickGray = _ttoi(strTemp);	//170403 hjc mod
	}
	if (Col == 1 && Row == 4)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(4);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}

	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][4] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (4 - 1)); // Bit Flag.
	}
	m_nFineOpenGray = _ttoi(strTemp);
	}
	//150413 hjc add
	if (Col == 1 && Row == 5)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(5);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}

	if (m_strOriginData[1][5] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (5 - 1)); // Bit Flag.
	}
	m_nFineHalfSideNickDiffBrightGray = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 6)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(6);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][6] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (6 - 1)); // Bit Flag.
	}
	m_nFineHalfSideNickDiffDarkGray = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 7)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(7);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][7] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (7 - 1)); // Bit Flag.
	}
	m_nLeadOpenGray = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 8)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(8);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][8] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (8 - 1)); // Bit Flag.
	}
	m_fFineMinCheckWidth = _ttof(strTemp);	//170404 hjc mod ttoi -> ttof

	}

	if (SpecData.nLineWidthGroupNum == 0 || AoiParam()->m_bUseMultilineSpecEx)
	{
	if (!pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	if (Col == 1 && Row == 9)	//150413 hjc add
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][9] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (9 - 1)); // Bit Flag.
	}
	m_nFineNickPercent[0] = _ttoi(strTemp);

	}
	if (Col == 1 && Row == 10)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(10);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[1][10] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (10 - 1)); // Bit Flag.
	}
	m_nFineProtrusionPercent[0] = _ttoi(strTemp);

	}
	}
	if (Col == 1 && Row == 11)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(11);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (_ttoi(strTemp) < 30 || _ttoi(strTemp) > 90)
	{
	strMsg.Format(_T("%s (30~90)%%%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	else
	{
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][11] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (11 - 1)); // Bit Flag.
	}
	}
	m_nFineNickNGFilterPercent[0] = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 12)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(12);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}

	if (_ttoi(strTemp) < 110 || _ttoi(strTemp) > 200)
	{
	strMsg.Format(_T("%s (110~200)%%%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	else
	{
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][12] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (12 - 1)); // Bit Flag.
	}
	}
	m_nFineExcsNGFilterPercent[0] = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 13)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(13);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][13] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (13 - 1)); // Bit Flag.
	}
	m_fFineLineWdDeltaGradViolation[0] = _ttof(strTemp);
	}
	if (Col == 1 && Row == 14)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(14);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][14] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (14 - 1)); // Bit Flag.
	}
	m_fFineExcsWdDeltaGradViolation[0] = _ttof(strTemp);
	}
	if (Col == 1 && Row == 15)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(15);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][15] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (15 - 1)); // Bit Flag.
	}
	m_fFineNarrowTraceViolation[0] = (float)_ttof(strTemp);
	}
	if (Col == 1 && Row == 16)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(16);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][16] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (16 - 1)); // Bit Flag.
	}
	m_fFineWideTraceViolation[0] = (float)_ttof(strTemp);
	}
	}

	if (m_bKeyDown)
	{
	m_bKeyDown = FALSE;
	RefreshSheetOnChanging();
	}

	break;
	case 2:
	if (Col == 1 && Row == 1)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(1);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[2][1] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (1 - 1)); // Bit Flag.
	}
	m_MinSpGray = _ttoi(strTemp);
	}
	//20090412 hjc
	if (Col == 1 && Row == 2)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(2);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[2][2] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (2 - 1)); // Bit Flag.
	}
	m_nNeibSpGrayDiff = _ttoi(strTemp);
	}

	//150413 hjc add
	if (Col == 1 && Row == 3)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(3);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[2][3] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (3 - 1)); // Bit Flag.
	}
	m_nUSDarkGrayMinus = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 4)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(4);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[2][4] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (4 - 1)); // Bit Flag.
	}
	m_fMinSpWidth = _ttof(strTemp);
	}
	if (!pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	if (Col == 1 && Row == 5)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(5);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}
	//if(_ttof(strTemp) < 1 || _ttof(strTemp) > 1.5)
	if (_ttoi(strTemp) < 10 || _ttoi(strTemp) > 90)
	{
	strMsg.Format(_T("%s (10~90)%%%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}
	else
	{
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[2][5] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (5 - 1)); // Bit Flag.
	}
	}
	m_nMinSPPercent = _ttoi(strTemp);
	}
	}
	if (Col == 1 && Row == 6)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(6);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}
	//if(_ttof(strTemp) < 1 || _ttof(strTemp) > 1.5)
	if (_ttoi(strTemp) < 10 || _ttoi(strTemp) > 90)
	{
	strMsg.Format(_T("%s (30~90)%%%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}
	else
	{
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[2][6] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (6 - 1)); // Bit Flag.
	}
	}
	m_nSpaceNGFilterPercent = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 7)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(7);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[2][7] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (7 - 1)); // Bit Flag.
	}
	//20090228 hjc
	m_fSpWdDeltaGradViolation = _ttof(strTemp);
	}
	//20090405 hjc
	if (Col == 1 && Row == 8)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(8);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[2][8] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (8 - 1)); // Bit Flag.
	}
	//20090228 hjc
	m_fSpWdDeltaOuterGradViolation = _ttof(strTemp);
	}

	if (Col == 1 && Row == 9)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(2);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[2][9] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (9 - 1)); // Bit Flag.
	}
	m_fFineMinSpWidth = _ttof(strTemp);
	}

	if (m_bKeyDown)
	{
	m_bKeyDown = FALSE;
	RefreshSheetOnChanging();
	}

	break;

	//20100322 hjc add
	case 3:
	if (Col == 1 && Row == 1)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(1);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[3][1] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (1 - 1)); // Bit Flag.
	}
	m_nPinHoleGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 3)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(3);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[3][3] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (3 - 1)); // Bit Flag.
	}

	if (pGlobalDoc->m_bInspCCL[AoiParam()->m_nCurrentInspectionMode])
	{
	m_fPinHoleMin = _ttof(strTemp);

	int nTempSize, nCellSize = 100000;
	for (int nBlockID = 0; nBlockID < RgnBlock.nBlockNum; nBlockID++)
	{
	nTempSize = min(SizeData[nBlockID].ProcSizeX, SizeData[nBlockID].ProcSizeY);
	nCellSize = (nCellSize > nTempSize) ? nTempSize : nCellSize;
	}
	nCellSize /= 10;

	if (m_fPinHoleMin > nCellSize)
	{
	m_fPinHoleMin = nCellSize;
	strTemp.Format(_T("%.1f"), m_fPinHoleMin);
	m_Spread.SetText(strTemp);
	}
	}
	else
	m_fPinHoleMin = _ttof(strTemp);
	}

	if (Col == 1 && Row == 4)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(4);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[3][4] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (4 - 1)); // Bit Flag.
	}
	m_nIsLandGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 6)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(6);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[3][6] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (6 - 1)); // Bit Flag.
	}
	m_fIsLandMin = _ttof(strTemp);
	}
	//20090412 hjc
	if (Col == 1 && Row == 7)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(7);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[3][7] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (7 - 1)); // Bit Flag.
	}
	m_nIsLandExtGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 9)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[3][9] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (9 - 1)); // Bit Flag.
	}
	m_fIsLandExtMin = _ttof(strTemp);
	}
	if (Col == 1 && Row == 10)	//jun 20120903 for LG_CCL-Inspector
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(10);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[3][10] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (10 - 1)); // Bit Flag.
	}
	m_nCCLGray = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 11)	//jun 20120903 for LG_CCL-Inspector
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(11);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[3][11] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (11 - 1)); // Bit Flag.
	}
	m_fCCLCircularity = _ttof(strTemp);
	}
	if (Col == 1 && Row == 12)	//jun 20120903 for LG_CCL-Inspector
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(12);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[3][12] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (12 - 1)); // Bit Flag.
	}
	m_fCCLDefSize = _ttof(strTemp);
	}

	//2022 01 10 lgh add
	if (Col == 1 && Row == 13)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(13);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[3][13] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (13 - 1)); // Bit Flag.
	}
	m_nCharInspectionGray = _ttoi(strTemp);
	}

	//2022 01 10 lgh add
	if (Col == 1 && Row == 14)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(14);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (fabs(_ttof(m_strOriginData[3][14]) - _ttof(strTemp)) > 0.01)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (14 - 1)); // Bit Flag.
	}
	m_dCharRegionUpperPercent = _ttof(strTemp);
	}

	//2022 01 10 lgh add
	if (Col == 1 && Row == 15)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(15);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (fabs(_ttof(m_strOriginData[3][15]) - _ttof(strTemp)) > 0.01)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (15 - 1)); // Bit Flag.
	}
	m_dCharRegionLowerPercent = _ttof(strTemp);
	}
	//---------------



	if (m_bKeyDown)
	{
	m_bKeyDown = FALSE;
	RefreshSheetOnChanging();
	}

	break;
	case 4:
	//150823 hjc add
	if (Col == 1 && Row == 1)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(1);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][1] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (1 - 1)); // Bit Flag.
	}
	SpecData.nVDrillDiffBrightGray = _ttoi(strTemp);		//150606 hjc mod
	}

	if (Col == 1 && Row == 2)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(2);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][2] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (2 - 1)); // Bit Flag.
	}
	SpecData.nVDrillDiffDarkGray = _ttoi(strTemp);		//150606 hjc mod
	}

	if (Col == 1 && Row == 3)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(3);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][3] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (3 - 1)); // Bit Flag.
	}
	SpecData.fVDPadPrecName = _ttof(strTemp);
	}
	//20090419 hjc
	if (Col == 1 && Row == 4)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(4);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][4] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (4 - 1)); // Bit Flag.
	}
	m_fVDLocationTolerance = _ttof(strTemp);
	}
	//-----------
	if (Col == 1 && Row == 5)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(5);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][5] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (5 - 1)); // Bit Flag.
	}
	m_fVDPadMin = _ttof(strTemp);
	}

	if (Col == 1 && Row == 6)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(6);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}

	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][6] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (6 - 1)); // Bit Flag.
	}
	m_nPADVoidGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 8)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(8);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	//111214 hjc add
	if (m_strOriginData[4][8] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (8 - 1)); // Bit Flag.
	}
	m_fPADVoidMin = _ttof(strTemp);
	}

	if (Col == 1 && Row == 10)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(10);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][10] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (10 - 1)); // Bit Flag.
	}
	m_fPADTipMin = _ttof(strTemp);
	}

	if (Col == 1 && Row == 11)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(11);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][11] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (11 - 1)); // Bit Flag.
	}
	m_nHoleLandVoidGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 13)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(13);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][13] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (13 - 1)); // Bit Flag.
	}
	m_fARLandMin = _ttof(strTemp);
	}

	if (Col == 1 && Row == 14)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(14);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][14] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (14 - 1)); // Bit Flag.
	}
	SpecData.fHoleFillExt = _ttof(strTemp);
	}

	if (Col == 1 && Row == 15)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(15);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][15] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (15 - 1)); // Bit Flag.
	}
	m_nCO2LandVoidGraySpec = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 17)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(17);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][17] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (17 - 1)); // Bit Flag.
	}
	m_fCO2LandMin = _ttof(strTemp);
	}

	//20100323 hjc add
	if (Col == 1 && Row == 19)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(19);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][19] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (19 - 1)); // Bit Flag.
	}
	SpecData.fCO2HoleFillExt = _ttof(strTemp);
	}

	if (Col == 1 && Row == 20)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(20);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][20] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (20 - 1)); // Bit Flag.
	}
	m_nFinePADVoidGraySpec = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 22)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(22);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][22] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (22 - 1)); // Bit Flag.
	}
	m_fFineVDPadMin = _ttof(strTemp);	//090324-ndy
	}

	//---------------

	//----------------------------------------------------------------------------------

	if (m_bKeyDown)
	{
	m_bKeyDown = FALSE;
	RefreshSheetOnChanging();
	}

	break;
	case 5:
	if (Col == 1 && Row == 1)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(1);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][1] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (1 - 1)); // Bit Flag.
	}
	m_fHoleTolerance = (float)_ttof(strTemp);
	}

	//20090311 hjc modify
	if (Col == 1 && Row == 2)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(2);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}

	if (_ttof(strTemp) < 1.05 || _ttof(strTemp) > 3.0)
	{
	strMsg.Format(_T("%s (1.05~3.0)%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (_ttof(m_strOriginData[5][2]) != _ttof(strTemp))
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (2 - 1)); // Bit Flag.
	}
	m_fHoleDiaUpper = _ttof(strTemp);
	}

	if (Col == 1 && Row == 3)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(3);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (_ttof(strTemp) < 0.2 || _ttof(strTemp) > 0.95)
	{
	strMsg.Format(_T("%s (0.2~0.95)%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (_ttof(m_strOriginData[5][3]) != _ttof(strTemp))
	//if(m_strOriginData[5][3] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (3 - 1)); // Bit Flag.
	}
	m_fHoleDiaLower = _ttof(strTemp);
	}

	if (Col == 1 && Row == 4)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(4);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][4] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (4 - 1)); // Bit Flag.
	}
	m_nHoleOpenGray = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 5)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(5);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][5] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (5 - 1)); // Bit Flag.
	}
	m_nHoleMissingGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 6)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(6);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}

	if (_ttof(strTemp) < 35 || _ttof(strTemp) > 220)
	{
	strMsg.Format(_T("%s (35~220)%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][6] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (6 - 1)); // Bit Flag.
	}
	m_nHoleInnerGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 8)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(8);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][8] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (8 - 1)); // Bit Flag.
	}
	m_nHoleDefSize = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 10)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(10);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][10] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (10 - 1)); // Bit Flag.
	}
	m_nCO2MissingGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 11)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(11);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][11] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (11 - 1)); // Bit Flag.
	}
	m_nCO2HoleNum = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 12)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(12);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][12] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (12 - 1)); // Bit Flag.
	}
	m_nCO2OpenGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 13)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(13);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][13] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (13 - 1)); // Bit Flag.
	}
	m_nCO2MisAgnGray = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 14)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(14);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][14] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (14 - 1)); // Bit Flag.
	}
	m_nCO2MisAgnDefPercent = _ttoi(strTemp);
	}


	if (Col == 1 && Row == 15)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(15);
	strTemp = m_Spread.GetText();
	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (_ttof(strTemp) < 20 || _ttof(strTemp) > 80)
	{
	strMsg.Format(_T("%s (20~80)%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	else
	{
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][15] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (15 - 1)); // Bit Flag.
	}
	}

	SpecData.nVHEdgeThrDiffGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 16)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(16);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (_ttof(strTemp) < 80 || _ttof(strTemp) > 170)
	{
	strMsg.Format(_T("%s (80~170)%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	else
	{
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][16] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (16 - 1)); // Bit Flag.
	}
	}

	SpecData.nVHBreakOutGray = _ttoi(strTemp);

	}

	if (Col == 1 && Row == 17)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(17);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (_ttof(strTemp) < 20 || _ttof(strTemp) > 80)
	{
	strMsg.Format(_T("%s (20~80)%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	else
	{
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][17] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (17 - 1)); // Bit Flag.
	}
	}

	SpecData.nVHDissmearGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 18)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(18);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	if (_ttof(strTemp) < 1 || _ttof(strTemp) > 15)
	{
	strMsg.Format(_T("%s (1~15)%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(5);
	return 0;
	}
	else
	{
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[5][18] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (18 - 1)); // Bit Flag.
	}
	}

	SpecData.nVHContiBreakOutNum = _ttoi(strTemp);
	}

	if (m_bKeyDown)
	{
	m_bKeyDown = FALSE;
	RefreshSheetOnChanging();
	}

	break;
	case 6:
	//20090228 modify hjc 1~6
	if (Col == 1 && Row == 1)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(1);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][1] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (1 - 1)); // Bit Flag.
	}
	m_nPadEdgeNickGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 2)	//120105 hjc add
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(2);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][2] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (2 - 1)); // Bit Flag.
	}
	m_nPadEdgeNeibGrayDiff = _ttoi(strTemp);
	}
	if (Col == 1 && Row == 3)	//120105 hjc add
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(3);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	//20090326 hjc
	if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
	{
	strMsg.Format(_T("Input Range : 0 ~ 255"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][3] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (3 - 1)); // Bit Flag.
	}
	m_nPadEdgeBADiffDarkGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 4)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(4);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][4] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (4 - 1)); // Bit Flag.
	}
	m_fPadEdgeNickWdDeltaGradViolation = _ttof(strTemp);
	}

	if (Col == 1 && Row == 5)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(5);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][5] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (5 - 1)); // Bit Flag.
	}
	m_fPadEdgeExcsWdDeltaGradViolation = _ttof(strTemp);
	}

	//------------------------
	//20090412 hjc
	if (Col == 1 && Row == 6)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(6);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][6] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (6 - 1)); // Bit Flag.
	}
	m_nPadVDEdgeGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 7)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(7);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][7] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (7 - 1)); // Bit Flag.
	}
	m_fPadVDEdgeWdDeltaGradViolation = _ttof(strTemp);
	}
	//-------------------

	if (Col == 1 && Row == 8)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(8);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][8] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (8 - 1)); // Bit Flag.
	}
	m_nHoleEdgeNickGray = _ttoi(strTemp);	//111214 hjc mod
	}

	if (Col == 1 && Row == 9)	//120109 hjc add
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][9] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (9 - 1)); // Bit Flag.
	}
	m_nHoleEdgeNeibGrayDiff = _ttoi(strTemp);	//111214 hjc mod
	}

	if (Col == 1 && Row == 10)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(10);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][10] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (10 - 1)); // Bit Flag.
	}
	m_fHoleEdgeNickWdDeltaGradViolation = _ttof(strTemp);
	}

	if (Col == 1 && Row == 11)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(11);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][11] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (11 - 1)); // Bit Flag.
	}
	m_fHoleEdgeExcsWdDeltaGradViolation = _ttof(strTemp);
	}

	if (Col == 1 && Row == 12)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(12);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][12] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (12 - 1)); // Bit Flag.
	}
	m_nViaEdgeNickGray = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 13)	//120109 hjc add
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(13);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][13] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (13 - 1)); // Bit Flag.
	}
	m_nViaEdgeNeibGrayDiff = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 14)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(14);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][14] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (14 - 1)); // Bit Flag.
	}
	m_fViaEdgeNickWdDeltaGradViolation = _ttof(strTemp);
	}

	if (Col == 1 && Row == 15)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(15);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(6);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[6][15] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (15 - 1)); // Bit Flag.
	}
	m_fViaEdgeExcsWdDeltaGradViolation = _ttof(strTemp);
	}

	//-------------------
	//20090216 chg
	if (m_bKeyDown)
	{
	m_bKeyDown = FALSE;
	RefreshSheetOnChanging();
	}

	break;
	case 7:
	if (Col == 1 && Row == 1)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(1);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(7);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[7][1] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001); // Bit Flag.
	}
	pGlobalDoc->m_nPtSrchRngExt = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 3)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(3);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(7);
	return 0;
	}
	if (_ttoi(strTemp) < 5 || _ttoi(strTemp) > 700)	//20210625 mod
	{
	strMsg.Format(_T("%s (5~140)%s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
	pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
	MessageBox(strMsg);
	DisplaySpread(7);
	return 0;
	}
	else
	{
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[7][3] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (3 - 1)); // Bit Flag.
	}
	}
	m_nAlignTolerance = _ttoi(strTemp);
	}

	if (Col == 1 && Row == 4)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(4);
	strTemp = m_Spread.GetText();
	if (!(strTemp == _T("Highest") || strTemp == _T("VeryHigh") || strTemp == _T("Maximum") || strTemp == _T("High") || strTemp == _T("Normal") || strTemp == _T("Low")))
	{
	DisplaySpread(7);
	return 0;
	}
	if (m_strOriginData[7][4] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (4 - 1)); // Bit Flag.
	}
	m_strThetaAlign = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	if (Col == 1 && Row == 5)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(5);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(7);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (_ttof(strTemp) < SizeData[COMMON_PARAMETER].fPixelSizeX)
	{
	strMsg.Format(_T("%s %.1f %s"),
	pGlobalView->GetLanguageString("MENU", "INPUT_VALUE"),
	SizeData[COMMON_PARAMETER].fPixelSizeX,
	pGlobalView->GetLanguageString("MENU", "MUST_OVER"));
	MessageBox(strMsg);
	m_fDefMaskSize = max(SizeData[COMMON_PARAMETER].fPixelSizeX, SpecData.fDefMaskSize);
	DisplaySpread(7);
	return 0;
	}
	else if (m_strOriginData[7][5] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (5 - 1)); // Bit Flag.
	}
	m_fDefMaskSize = _ttof(strTemp);
	}
	if (Col == 1 && Row == 6)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(6);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(7);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[7][6] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (6 - 1)); // Bit Flag.
	}
	m_fNearDefLen = _ttof(strTemp);
	}

	if (AoiParam()->m_bUseAutoPinPosAdjust || g_bUsePinPosEstimate)
	{
	if (Col == 1 && Row == 8)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(8);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(7);
	return 0;
	}
	if (m_strOriginData[7][8] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (8 - 1)); // Bit Flag.
	}
	m_dPanelSizeX = _ttof(strTemp);
	}

	if (Col == 1 && Row == 9)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();

	if (IsCharInString(strTemp))
	{
	strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
	MessageBox(strMsg);
	DisplaySpread(7);
	return 0;
	}
	if (m_strOriginData[7][9] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (9 - 1)); // Bit Flag.
	}
	m_dPanelSizeY = _ttof(strTemp);
	}

	#ifdef IRIS_AXIS
	if (Col == 1 && Row == 10)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(10);
	strTemp = m_Spread.GetText();

	for (int i = 0; i < 12; i++)
	{
	double dPosName = fabs(pGlobalDoc->m_IRISAxisControl.m_dIRISPosName[i] - _ttof(strTemp));

	if (dPosName < 0.01)
	{
	m_nIRISPosID = i;
	break;
	}
	}

	if (fabs(_ttof(m_strOriginData[7][10]) - _ttof(strTemp)) > 0.01)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (10 - 1)); // Bit Flag.
	}

	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	#endif

	}
	else
	{
	#ifdef IRIS_AXIS
	if (Col == 1 && Row == 8)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(8);
	strTemp = m_Spread.GetText();

	for (int i = 0; i < 12; i++)
	{
	double dPosName = fabs(pGlobalDoc->m_IRISAxisControl.m_dIRISPosName[i] - _ttof(strTemp));

	if (dPosName < 0.01)
	{
	m_nIRISPosID = i;
	break;
	}
	}

	if (fabs(_ttof(m_strOriginData[7][8]) - _ttof(strTemp)) > 0.01)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (8 - 1)); // Bit Flag.
	}

	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	#endif
	}

	//20090216 chg
	if (m_bKeyDown)
	{
	m_bKeyDown = FALSE;
	RefreshSheetOnChanging();
	}
	break;

	default:
	;
	break;
	}

	CString  strInfo;
	int NextNum, currNum, ModifiedNum;

	switch (m_nTabNum)
	{
	case 0:
	if (SpecData.nLineWidthGroupNum == 0 || AoiParam()->m_bUseMultilineSpecEx)
	{
	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	//m_nSpreadCellFocusPos[0] = Row;

	if (Col == 1 && Row == 9)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
	{
	DisplaySpread(0);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[0][9] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (9 - 1)); // Bit Flag.
	}
	m_strNick[0] = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	if (Col == 1 && Row == 10)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(10);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
	{
	DisplaySpread(0);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[0][10] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (10 - 1)); // Bit Flag.
	}
	m_strProtrusion[0] = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	}
	}
	break;
	case 1:
	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	//m_nSpreadCellFocusPos[1] = Row;
	if (SpecData.nLineWidthGroupNum == 0 || AoiParam()->m_bUseMultilineSpecEx)
	{
	if (Col == 1 && Row == 9)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][9] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (9 - 1)); // Bit Flag.
	}
	m_strFineNick[0] = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	if (Col == 1 && Row == 10)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(10);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[1][10] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (10 - 1)); // Bit Flag.
	}
	m_strFineProtrusion[0] = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	}
	}
	break;
	case 2:
	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	//m_nSpreadCellFocusPos[2] = Row;

	if (Col == 1 && Row == 5)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(5);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(2);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[2][5] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (5 - 1)); // Bit Flag.
	}
	m_strMinSP = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	}
	break;
	case 3:
	//m_nSpreadCellFocusPos[3] = Row;

	if (Col == 1 && Row == 2)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(2);
	strTemp = m_Spread.GetText();
	//strcpy(SpecData.szVDPadPrecName, strTemp);
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[3][2] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P3_M4");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (2 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[3][2]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_LARGE, ModifiedNum, strTemp) == SUCCESS)
	//	m_strOriginData[3][17] = m_strLP_Prec;
	m_strOriginData[3][2] = SpecData.szLPADRLName;	//20100305 hjc mod
	}
	}
	else
	{
	//	m_strLP_Prec = m_strOriginData[3][17];
	strTemp = m_strLP_Prec = m_strOriginData[3][2];	//20100305 hjc mod
	DisplaySpread(3);
	}
	}
	else
	{
	//	m_strLP_Prec = m_strOriginData[3][17];
	strTemp = m_strLP_Prec = m_strOriginData[3][2];	//20100305 hjc mod
	DisplaySpread(3);
	}
	}
	m_strLP_Prec = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	if (Col == 1 && Row == 5)  // Extra RLE
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(5);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[3][5] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P0_M5");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (5 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[3][5]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_SPACE, ModifiedNum, strTemp) == SUCCESS)
	m_strOriginData[3][5] = SpecData.szSPRLName;
	}
	}
	else
	{
	strTemp = m_strSP_Prec = m_strOriginData[3][5];		//170112 hjc mod
	DisplaySpread(3);
	}
	}
	else
	{
	strTemp = m_strSP_Prec = m_strOriginData[3][5];		//170112 hjc mod
	DisplaySpread(3);
	}
	}
	m_strSP_Prec = strTemp;

	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	//170112 hjc add
	if (Col == 1 && Row == 8)  // Space Pad Ext RLE
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(8);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(3);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[3][8] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P0_M5");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (8 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[3][8]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_SPACEEXT, ModifiedNum, strTemp) == SUCCESS)
	m_strOriginData[3][8] = SpecData.szSPACEEXTRLName;
	}
	}
	else
	{
	strTemp = m_strSPExt_Prec = m_strOriginData[3][8];		//170112 hjc mod
	DisplaySpread(3);
	}
	}
	else
	{
	strTemp = m_strSPExt_Prec = m_strOriginData[3][8];		//170112 hjc mod
	DisplaySpread(3);
	}
	}
	m_strSPExt_Prec = strTemp;

	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	break;
	case 4:		//20100322 hjc add
	//m_nSpreadCellFocusPos[4] = Row;

	if (Col == 1 && Row == 7)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(7);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][7] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P3_M1");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red
	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (7 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[4][7]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_SMALL, ModifiedNum, strTemp) == SUCCESS)
	//	m_strOriginData[3][6] = m_strPadBallPrec;
	m_strOriginData[4][7] = SpecData.szPADRLPrecName;	//20100305 hjc mod
	}
	}
	else
	{
	//	m_strPadBallPrec = m_strOriginData[3][6];
	strTemp = m_strPadBallPrec = m_strOriginData[4][7];	//20100305 hjc mod
	DisplaySpread(4);
	}
	}
	else
	{
	//	m_strPadBallPrec = m_strOriginData[3][6];
	strTemp = m_strPadBallPrec = m_strOriginData[4][7];	//20100305 hjc mod
	DisplaySpread(4);
	}
	}
	m_strPadBallPrec = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	if (Col == 1 && Row == 9)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][9] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P3_M3");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (9 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[4][9]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_PADTIP, ModifiedNum, strTemp) == SUCCESS)
	m_strOriginData[4][9] = SpecData.szPADTipPrecName;
	}
	}
	else
	{
	strTemp = m_strPadTip_Prec = m_strOriginData[4][9];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	else
	{
	strTemp = m_strPadTip_Prec = m_strOriginData[4][9];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	m_strPadTip_Prec = strTemp;

	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	if (Col == 1 && Row == 12)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(12);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}
	if (m_strOriginData[4][12] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P3_M2");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (12 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[4][12]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_AR, ModifiedNum, strTemp) == SUCCESS)
	m_strOriginData[4][12] = SpecData.szARLandPrecName;
	}
	}
	else
	{
	strTemp = m_strARLand_Prec = m_strOriginData[4][12];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	else
	{
	strTemp = m_strARLand_Prec = m_strOriginData[4][12];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	m_strARLand_Prec = strTemp;

	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	//20100322 hjc add
	if (Col == 1 && Row == 16)  // Fine PAD Size
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(16);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(4);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[4][16] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P3_M15");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (16 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[4][16]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_CO2, ModifiedNum, strTemp) == SUCCESS)	//20100322 hjc mod
	m_strOriginData[4][16] = SpecData.szCO2LandPrecName;
	}
	}
	else
	{
	strTemp = m_strCO2Land_Prec = m_strOriginData[4][16];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	else
	{
	strTemp = m_strCO2Land_Prec = m_strOriginData[4][16];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	m_strCO2Land_Prec = strTemp;

	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	if (Col == 1 && Row == 18)  // Fine PAD Size
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(18);
	strTemp = m_Spread.GetText();
	//			int nPos = strTemp.Find(_T(" ",0);
	//			strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Yes" || strTemp == "No"))
	{
	DisplaySpread(4);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[4][18] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (18 - 1)); // Bit Flag.

	StringToChar(strTemp, SpecData.szCO2LandAlignMode);
	//					strcpy(SpecData.szCO2LandAlignMode, strTemp);
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	else
	{
	StringToChar(m_strOriginData[4][18], SpecData.szCO2LandAlignMode);
	//					strcpy(SpecData.szCO2LandAlignMode, m_strOriginData[4][18]);
	strTemp = m_strOriginData[4][18];	//20100305 hjc mod
	DisplaySpread(4);
	}
	}
	if (strTemp == "Yes")
	SpecData.nCO2LandAlignMode = 1;
	else
	SpecData.nCO2LandAlignMode = 0;

	StringToChar(strTemp, SpecData.szCO2LandAlignMode);
	//			strcpy(SpecData.szCO2LandAlignMode, strTemp);
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	if (Col == 1 && Row == 21)  // Fine PAD Size
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(21);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(4);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[4][21] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P3_M6");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (21 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[4][21]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_FINE, ModifiedNum, strTemp) == SUCCESS)  // 20101208 bug fix PAD_SPACE->PAD_FINE by ljg
	m_strOriginData[4][21] = SpecData.szPADFine_PrecName;
	}
	}
	else
	{
	strTemp = m_strFPad_Prec = m_strOriginData[4][21];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	else
	{
	strTemp = m_strFPad_Prec = m_strOriginData[4][21];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	m_strFPad_Prec = strTemp;

	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	break;
	case 5:
	//m_nSpreadCellFocusPos[5] = Row;

	//20090311 hjc modify
	if (Col == 1 && Row == 7)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(7);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(5);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[5][7] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (7 - 1)); // Bit Flag.
	}
	m_strHolePrec = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	if (Col == 1 && Row == 9)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();

	if (!(strTemp == "AreaMode" || strTemp == "EdgeMode"))
	{
	DisplaySpread(5);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[5][9] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (9 - 1)); // Bit Flag.
	}
	StringToChar(strTemp, SpecData.szVHMode);
	//			strcpy(SpecData.szVHMode, strTemp);
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	//20090311 hjc add
	if (strTemp == "AreaMode")
	{
	//Disable Cells
	m_Spread.SetCol(1);

	m_Spread.SetRow(15);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(TRUE);
	m_Spread.SetForeColor(RGB(152, 152, 152));

	m_Spread.SetRow(16);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(TRUE);
	m_Spread.SetForeColor(RGB(152, 152, 152));

	//Temperary 2006.10.13 -----------------------------------
	m_Spread.SetRow(17);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(TRUE);
	m_Spread.SetForeColor(RGB(152, 152, 152));

	m_Spread.SetRow(18);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(TRUE);
	m_Spread.SetForeColor(RGB(152, 152, 152));
	}
	else
	{
	//Disable Cells
	m_Spread.SetCol(1);

	m_Spread.SetRow(15);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(FALSE);
	m_Spread.SetForeColor(RGB(60, 145, 103));

	m_Spread.SetRow(16);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(FALSE);
	m_Spread.SetForeColor(RGB(60, 145, 103));

	//Temperary 2006.10.13 -----------------------------------
	m_Spread.SetRow(17);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(FALSE);
	m_Spread.SetForeColor(RGB(60, 145, 103));

	m_Spread.SetRow(18);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(FALSE);
	m_Spread.SetForeColor(RGB(60, 145, 103));
	}
	}
	break;

	case 6:
	//m_nSpreadCellFocusPos[6] = Row;
	break;
	case 7:
	//m_nSpreadCellFocusPos[7] = Row;
	if (Col == 1 && Row == 4)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(4);
	TCHAR str[1024];
	m_Spread.GetData(1, 4, str);
	strTemp = CString(str);
	strTemp = m_Spread.GetText();
	//160924 LGH
	if (!(strTemp == _T("Highest") || strTemp == _T("VeryHigh") || strTemp == _T("Maximum") || strTemp == _T("High") || strTemp == _T("Normal") || strTemp == _T("Low")))
	//if(!(strTemp == "High" || strTemp == "Normal" || strTemp == "Low"))
	{
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	DisplaySpread(7);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[7][4] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (4 - 1)); // Bit Flag.
	}
	m_strThetaAlign = strTemp;
	//m_Spread.SetEditMode(FALSE);
	}
	if (Col == 1 && Row == 7)	//20100210 hjc add
	{
	int nPos;
	m_Spread.SetCol(1);
	m_Spread.SetRow(7);
	if (pGlobalDoc->m_bUseMultiVaccumControl)	//130311 hjc add
	{
	strTemp = m_Spread.GetText();
	nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Both" || strTemp == "FirstOnly"))
	{
	DisplaySpread(7);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	{
	strTemp = CheckLock(m_nTabNum, Row, strTemp);
	}

	if (m_strOriginData[7][7] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (7 - 1)); // Bit Flag.
	}
	m_strSelectVaccum = strTemp;
	if (strTemp == "Both")
	SpecData.nSelectVaccum = 1;
	else
	SpecData.nSelectVaccum = 2;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	else
	{
	strTemp = m_Spread.GetText();
	nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	m_strSelectVaccum = strTemp;
	SpecData.nSelectVaccum = 1;
	}
	}
	break;
	default:
	;
	}*/
	return 0;
}

LRESULT CDlgSpec::OnButtonClickedFpspreadDown(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your control notification handler code here
	/*	SS_COORD col, row;
	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	m_Spread.GetActiveCell(&col, &row);

	SS_COORD Col = col;
	SS_COORD Row = row;

	// About Check Box
	CString strTemp;
	int idx; // syd-091008

	switch (m_nTabNum)
	{
	// syd-091008
	case 0:
	case 1:
	if (AoiParam()->m_bUseMultilineSpecEx == 0)
	{
	if (Col == 1 && Row >= 9 && Row <= 16)
	{
	if (SpecData.nLineWidthGroupNum > 0)
	{
	BOOL bLineWidthChanged = FALSE;
	CDlgMultiLineSpec dlg;
	dlg.LoadFractionData(pGlobalDoc->m_strLocSpecDir, pGlobalDoc->m_strModel, pGlobalDoc->m_strLayer);

	dlg.m_nNum = m_nLineWidthGroupNum;
	for (idx = 0; idx < max(1, m_nLineWidthGroupNum + 1); idx++)
	{
	dlg.m_dGroupLower[idx] = m_fLineWidthGroupLower[idx];
	dlg.m_dGroup[idx] = m_fLineWidthGroup[idx];
	dlg.m_dAdjusted[idx] = SpecData.fLineWidthGroupAdjusted[idx];
	dlg.m_strNick[idx] = m_strNick[idx];
	dlg.m_strProtrusion[idx] = m_strProtrusion[idx];
	dlg.m_nNickPercent[idx] = m_nNickPercent[idx];
	dlg.m_nProtrusionPercent[idx] = m_nProtrusionPercent[idx];
	dlg.m_nNickNGFilterPercent[idx] = m_nNickNGFilterPercent[idx];
	dlg.m_nExcsNGFilterPercent[idx] = m_nExcsNGFilterPercent[idx];
	dlg.m_fLineWdDeltaGradViolation[idx] = m_fLineWdDeltaGradViolation[idx];
	dlg.m_fExcsWdDeltaGradViolation[idx] = m_fExcsWdDeltaGradViolation[idx];
	dlg.m_fNarrowTraceViolation[idx] = m_fNarrowTraceViolation[idx];
	dlg.m_fWideTraceViolation[idx] = m_fWideTraceViolation[idx];

	dlg.m_strFineNick[idx] = m_strFineNick[idx];
	dlg.m_strFineProtrusion[idx] = m_strFineProtrusion[idx];
	dlg.m_nFineNickPercent[idx] = m_nFineNickPercent[idx];
	dlg.m_nFineProtrusionPercent[idx] = m_nFineProtrusionPercent[idx];
	dlg.m_nFineNickNGFilterPercent[idx] = m_nFineNickNGFilterPercent[idx];
	dlg.m_nFineExcsNGFilterPercent[idx] = m_nFineExcsNGFilterPercent[idx];
	dlg.m_fFineLineWdDeltaGradViolation[idx] = m_fFineLineWdDeltaGradViolation[idx];
	dlg.m_fFineExcsWdDeltaGradViolation[idx] = m_fFineExcsWdDeltaGradViolation[idx];
	dlg.m_fFineNarrowTraceViolation[idx] = m_fFineNarrowTraceViolation[idx];
	dlg.m_fFineWideTraceViolation[idx] = m_fFineWideTraceViolation[idx];
	}
	dlg.m_strDlgCaption = _T("Multi Line Spec");
	dlg.DoModal();

	if (m_nLineWidthGroupNum != dlg.m_nNum)
	{
	pGlobalView->m_bInitVisionAdjust = 0;
	pGlobalDoc->m_fEntireMeanLineWidthDiff = 0.0;
	pGlobalDoc->m_fEntireMeanFineLineWidthDiff = 0.0;
	g_nProcessStepState[PSTEP_ADJUST] = 0;
	m_bReloadReference = 1;
	m_bMultilineSaved = 1;
	bLineWidthChanged = 1;
	m_nLineWidthGroupNum = dlg.m_nNum;
	}

	SpecData.nLineWidthGroupNum = SpecData.nLineWidthGroupNum = dlg.m_nNum;
	m_nLineWidthGroupNum = SpecData.nLineWidthGroupNum;
	//		m_nFineLineWidthGroupNum = SpecData.nLineWidthGroupNum;
	SpecData.nLineWidthGroupNum = SpecData.nLineWidthGroupNum = dlg.m_nNum;

	for (idx = 0; idx < m_nLineWidthGroupNum + 1; idx++)
	{
	if (idx < m_nLineWidthGroupNum)
	{
	if (SpecData.fLineWidthGroup[idx] != dlg.m_dGroup[idx])
	{
	m_bMultilineSaved = 1;
	bLineWidthChanged = TRUE;
	SpecData.fLineWidthGroup[idx] = dlg.m_dGroup[idx];
	}

	m_fLineWidthGroup[idx] = SpecData.fLineWidthGroup[idx];
	SpecData.fFineLineWidthGroup[idx] = SpecData.fLineWidthGroup[idx];
	m_fFineLineWidthGroup[idx] = SpecData.fLineWidthGroup[idx];
	}
	else
	{
	SpecData.fLineWidthGroup[idx] = 999999;
	SpecData.fFineLineWidthGroup[idx] = 999999;
	m_fLineWidthGroup[idx] = 999999;
	m_fFineLineWidthGroup[idx] = 999999;
	}

	if (SpecData.fLineWidthGroupAdjusted[idx] != dlg.m_dAdjusted[idx])
	{
	bLineWidthChanged = TRUE;
	SpecData.fLineWidthGroupAdjusted[idx] = dlg.m_dAdjusted[idx];
	}

	if (m_strNick[idx] != dlg.m_strNick[idx])
	{
	bLineWidthChanged = TRUE;
	m_strNick[idx] = dlg.m_strNick[idx];
	}

	if (m_strProtrusion[idx] != dlg.m_strProtrusion[idx])
	{
	bLineWidthChanged = TRUE;
	m_strProtrusion[idx] = dlg.m_strProtrusion[idx];
	}

	if (m_nNickPercent[idx] != dlg.m_nNickPercent[idx])
	{
	bLineWidthChanged = TRUE;
	m_nNickPercent[idx] = dlg.m_nNickPercent[idx];
	}

	if (m_nProtrusionPercent[idx] != dlg.m_nProtrusionPercent[idx])
	{
	bLineWidthChanged = TRUE;
	m_nProtrusionPercent[idx] = dlg.m_nProtrusionPercent[idx];
	}

	if (m_nNickNGFilterPercent[idx] != dlg.m_nNickNGFilterPercent[idx])
	{
	bLineWidthChanged = TRUE;
	m_nNickNGFilterPercent[idx] = dlg.m_nNickNGFilterPercent[idx];
	}

	if (m_nExcsNGFilterPercent[idx] != dlg.m_nExcsNGFilterPercent[idx])
	{
	bLineWidthChanged = TRUE;
	m_nExcsNGFilterPercent[idx] = dlg.m_nExcsNGFilterPercent[idx];
	}

	if (fabs(m_fLineWdDeltaGradViolation[idx] - dlg.m_fLineWdDeltaGradViolation[idx]))
	{
	bLineWidthChanged = TRUE;
	m_fLineWdDeltaGradViolation[idx] = dlg.m_fLineWdDeltaGradViolation[idx];
	}

	if (fabs(m_fExcsWdDeltaGradViolation[idx] - dlg.m_fExcsWdDeltaGradViolation[idx]) > 0.001)
	{
	bLineWidthChanged = TRUE;
	m_fExcsWdDeltaGradViolation[idx] = dlg.m_fExcsWdDeltaGradViolation[idx];
	}

	if (fabs(m_fNarrowTraceViolation[idx] - dlg.m_fNarrowTraceViolation[idx]) > 0.001)
	{
	bLineWidthChanged = TRUE;
	m_fNarrowTraceViolation[idx] = dlg.m_fNarrowTraceViolation[idx];
	}

	if (fabs(m_fWideTraceViolation[idx] - dlg.m_fWideTraceViolation[idx]) > 0.001)
	{
	bLineWidthChanged = TRUE;
	m_fWideTraceViolation[idx] = dlg.m_fWideTraceViolation[idx];
	}

	if (m_strFineNick[idx] != dlg.m_strFineNick[idx])
	{
	bLineWidthChanged = TRUE;
	m_strFineNick[idx] = dlg.m_strFineNick[idx];
	}

	if (m_strFineProtrusion[idx] != dlg.m_strFineProtrusion[idx])
	{
	bLineWidthChanged = TRUE;
	m_strFineProtrusion[idx] = dlg.m_strFineProtrusion[idx];
	}

	if (m_nFineNickPercent[idx] != dlg.m_nFineNickPercent[idx])
	{
	bLineWidthChanged = TRUE;
	m_nFineNickPercent[idx] = dlg.m_nFineNickPercent[idx];
	}

	if (m_nFineProtrusionPercent[idx] != dlg.m_nFineProtrusionPercent[idx])
	{
	bLineWidthChanged = TRUE;
	m_nFineProtrusionPercent[idx] = dlg.m_nFineProtrusionPercent[idx];
	}

	if (m_nFineNickNGFilterPercent[idx] != dlg.m_nFineNickNGFilterPercent[idx])
	{
	bLineWidthChanged = TRUE;
	m_nFineNickNGFilterPercent[idx] = dlg.m_nFineNickNGFilterPercent[idx];
	}

	if (m_nFineExcsNGFilterPercent[idx] != dlg.m_nFineExcsNGFilterPercent[idx])
	{
	bLineWidthChanged = TRUE;
	m_nFineExcsNGFilterPercent[idx] = dlg.m_nFineExcsNGFilterPercent[idx];
	}

	if (fabs(m_fFineLineWdDeltaGradViolation[idx] != dlg.m_fFineLineWdDeltaGradViolation[idx]) > 0.001)
	{
	bLineWidthChanged = TRUE;
	m_fFineLineWdDeltaGradViolation[idx] = dlg.m_fFineLineWdDeltaGradViolation[idx];
	}

	if (fabs(m_fFineExcsWdDeltaGradViolation[idx] != dlg.m_fFineExcsWdDeltaGradViolation[idx]) > 0.001)
	{
	bLineWidthChanged = TRUE;
	m_fFineExcsWdDeltaGradViolation[idx] = dlg.m_fFineExcsWdDeltaGradViolation[idx];
	}

	if (fabs(m_fFineNarrowTraceViolation[idx] != dlg.m_fFineNarrowTraceViolation[idx]) > 0.001)
	{
	bLineWidthChanged = TRUE;
	m_fFineNarrowTraceViolation[idx] = dlg.m_fFineNarrowTraceViolation[idx];
	}

	if (fabs(m_fFineWideTraceViolation[idx] - dlg.m_fFineWideTraceViolation[idx]) > 0.001)
	{
	bLineWidthChanged = TRUE;
	m_fFineWideTraceViolation[idx] = dlg.m_fFineWideTraceViolation[idx];
	}

	m_strNick[idx] = dlg.m_strNick[idx];
	m_strProtrusion[idx] = dlg.m_strProtrusion[idx];
	m_nNickPercent[idx] = dlg.m_nNickPercent[idx];
	m_nProtrusionPercent[idx] = dlg.m_nProtrusionPercent[idx];
	m_nNickNGFilterPercent[idx] = dlg.m_nNickNGFilterPercent[idx];
	m_nExcsNGFilterPercent[idx] = dlg.m_nExcsNGFilterPercent[idx];
	m_fLineWdDeltaGradViolation[idx] = dlg.m_fLineWdDeltaGradViolation[idx];
	m_fExcsWdDeltaGradViolation[idx] = dlg.m_fExcsWdDeltaGradViolation[idx];
	m_fNarrowTraceViolation[idx] = dlg.m_fNarrowTraceViolation[idx];
	m_fWideTraceViolation[idx] = dlg.m_fWideTraceViolation[idx];

	m_strFineNick[idx] = dlg.m_strFineNick[idx];
	m_strFineProtrusion[idx] = dlg.m_strFineProtrusion[idx];
	m_nFineNickPercent[idx] = dlg.m_nFineNickPercent[idx];
	m_nFineProtrusionPercent[idx] = dlg.m_nFineProtrusionPercent[idx];
	m_nFineNickNGFilterPercent[idx] = dlg.m_nFineNickNGFilterPercent[idx];
	m_nFineExcsNGFilterPercent[idx] = dlg.m_nFineExcsNGFilterPercent[idx];
	m_fFineLineWdDeltaGradViolation[idx] = dlg.m_fFineLineWdDeltaGradViolation[idx];
	m_fFineExcsWdDeltaGradViolation[idx] = dlg.m_fFineExcsWdDeltaGradViolation[idx];
	m_fFineNarrowTraceViolation[idx] = dlg.m_fFineNarrowTraceViolation[idx];
	m_fFineWideTraceViolation[idx] = dlg.m_fFineWideTraceViolation[idx];
	}

	int nLastNo = m_nLineWidthGroupNum;
	for (idx = m_nLineWidthGroupNum + 1; idx < 15; idx++)
	{
	SpecData.fLineWidthGroup[idx] = 999999;
	SpecData.fFineLineWidthGroup[idx] = 999999;
	m_fLineWidthGroup[idx] = 999999;
	m_fFineLineWidthGroup[idx] = 999999;

	m_strNick[idx] = dlg.m_strNick[m_nLineWidthGroupNum];
	m_strProtrusion[idx] = dlg.m_strProtrusion[m_nLineWidthGroupNum];
	m_nNickPercent[idx] = dlg.m_nNickPercent[m_nLineWidthGroupNum];
	m_nProtrusionPercent[idx] = dlg.m_nProtrusionPercent[m_nLineWidthGroupNum];
	m_nNickNGFilterPercent[idx] = dlg.m_nNickNGFilterPercent[m_nLineWidthGroupNum];
	m_nExcsNGFilterPercent[idx] = dlg.m_nExcsNGFilterPercent[m_nLineWidthGroupNum];
	m_fLineWdDeltaGradViolation[idx] = dlg.m_fLineWdDeltaGradViolation[m_nLineWidthGroupNum];
	m_fExcsWdDeltaGradViolation[idx] = dlg.m_fExcsWdDeltaGradViolation[m_nLineWidthGroupNum];
	m_fNarrowTraceViolation[idx] = dlg.m_fNarrowTraceViolation[m_nLineWidthGroupNum];
	m_fWideTraceViolation[idx] = dlg.m_fWideTraceViolation[m_nLineWidthGroupNum];

	m_strFineNick[idx] = dlg.m_strFineNick[m_nLineWidthGroupNum];
	m_strFineProtrusion[idx] = dlg.m_strFineProtrusion[m_nLineWidthGroupNum];
	m_nFineNickPercent[idx] = dlg.m_nFineNickPercent[m_nLineWidthGroupNum];
	m_nFineProtrusionPercent[idx] = dlg.m_nFineProtrusionPercent[m_nLineWidthGroupNum];
	m_nFineNickNGFilterPercent[idx] = dlg.m_nFineNickNGFilterPercent[m_nLineWidthGroupNum];
	m_nFineExcsNGFilterPercent[idx] = dlg.m_nFineExcsNGFilterPercent[m_nLineWidthGroupNum];
	m_fFineLineWdDeltaGradViolation[idx] = dlg.m_fFineLineWdDeltaGradViolation[m_nLineWidthGroupNum];
	m_fFineExcsWdDeltaGradViolation[idx] = dlg.m_fFineExcsWdDeltaGradViolation[m_nLineWidthGroupNum];
	m_fFineNarrowTraceViolation[idx] = dlg.m_fFineNarrowTraceViolation[m_nLineWidthGroupNum];
	m_fFineWideTraceViolation[idx] = dlg.m_fFineWideTraceViolation[m_nLineWidthGroupNum];
	}

	if (bLineWidthChanged)
	{
	LoadSpreadDataTab0();

	m_bSpecDataChanged = TRUE;
	}
	}
	}
	}
	else if (AoiParam()->m_bUseMultilineSpecEx && Col == 1 && Row >= 9 && Row <= 16)
	{
	if (m_nTabNum == 0)
	{
	if (SpecData.nLineWidthGroupNum > 0)
	{
	BOOL bLineWidthChanged = FALSE;
	CDlgMultiLineSpec_Old dlg;
	dlg.m_nNum = m_nLineWidthGroupNum;
	for (idx = 0; idx < m_nLineWidthGroupNum; idx++)
	{
	dlg.m_dGroupLower[idx] = m_fLineWidthGroupLower[idx];
	dlg.m_dGroup[idx] = m_fLineWidthGroup[idx];
	dlg.m_dSpec[idx] = m_fNarrowTraceViolation[idx];
	dlg.m_dSpecUpper[idx] = m_fWideTraceViolation[idx];
	}
	dlg.m_strDlgCaption = _T("Multi Line Spec");
	dlg.DoModal();

	for (idx = 0; idx < m_nLineWidthGroupNum; idx++)
	{
	if (m_fLineWidthGroup[idx] != dlg.m_dGroup[idx])
	{
	bLineWidthChanged = TRUE;
	m_fLineWidthGroup[idx] = dlg.m_dGroup[idx];
	}

	if (m_fNarrowTraceViolation[idx] != dlg.m_dSpec[idx])
	{
	bLineWidthChanged = TRUE;
	m_fNarrowTraceViolation[idx] = dlg.m_dSpec[idx];
	}

	if (m_fWideTraceViolation[idx] != dlg.m_dSpecUpper[idx])
	{
	bLineWidthChanged = TRUE;
	m_fWideTraceViolation[idx] = dlg.m_dSpecUpper[idx];
	}
	}

	if (bLineWidthChanged)
	{
	m_bSpecDataChanged = TRUE;
	CString strVal;
	strTemp = "";


	idx = 0;
	for (idx; idx < SpecData.nLineWidthGroupNum; idx++)
	{
	if (idx < 4)
	{
	if (idx)
	strTemp += _T("/");
	strVal.Format(_T("[%.1f,%.1f]"), m_fNarrowTraceViolation[idx], m_fWideTraceViolation[idx]);
	strTemp += strVal;
	}
	else if (idx == 4)
	{
	strTemp += _T("/..");
	}

	}
	m_Spread.SetCol(1);
	m_Spread.SetRow(15);
	m_Spread.SetTypeButtonText(strTemp);

	strTemp = _T("(MT) ");
	idx = 0;
	for (idx; idx < SpecData.nLineWidthGroupNum; idx++)
	{
	if (idx < 2)
	{
	if (idx)
	strTemp += _T("/");

	strVal.Format(_T("%.1f"), m_fLineWidthGroup[idx]);
	strTemp += strVal;
	}
	else if (idx == 2)
	{
	strTemp += _T("/..");
	}

	}
	m_Spread.SetCol(0);
	m_Spread.SetRow(15);
	m_Spread.SetText(strTemp);

	}
	}
	}
	else if (m_nTabNum == 1)
	{
	if (SpecData.nLineWidthGroupNum > 0)
	{
	BOOL bLineWidthChanged = FALSE;
	CDlgMultiLineSpec_Old dlg;
	dlg.m_nNum = SpecData.nLineWidthGroupNum;
	for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
	{
	dlg.m_dGroupLower[idx] = m_fLineWidthGroupLower[idx];
	dlg.m_dGroup[idx] = m_fFineLineWidthGroup[idx];
	dlg.m_dSpec[idx] = m_fFineNarrowTraceViolation[idx];
	dlg.m_dSpecUpper[idx] = m_fFineWideTraceViolation[idx];
	}

	dlg.m_strDlgCaption = _T("Fine Mulit Line Spec");
	dlg.DoModal();

	for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
	{
	if (m_fFineLineWidthGroup[idx] != dlg.m_dGroup[idx])
	{
	bLineWidthChanged = TRUE;
	m_fFineLineWidthGroup[idx] = dlg.m_dGroup[idx];
	}

	if (m_fFineNarrowTraceViolation[idx] != dlg.m_dSpec[idx])
	{
	bLineWidthChanged = TRUE;
	m_fFineNarrowTraceViolation[idx] = dlg.m_dSpec[idx];
	}

	if (m_fFineWideTraceViolation[idx] != dlg.m_dSpecUpper[idx])
	{
	bLineWidthChanged = TRUE;
	m_fFineWideTraceViolation[idx] = dlg.m_dSpecUpper[idx];
	}
	}

	if (bLineWidthChanged)
	{
	m_bSpecDataChanged = TRUE;
	CString strVal;
	strTemp = "";
	for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
	{
	if (idx < 4)
	{
	if (idx)
	strTemp += _T("/");
	strVal.Format(_T("[%.1f,%.1f]"), m_fFineNarrowTraceViolation[idx], m_fWideTraceViolation[idx]);
	strTemp += strVal;
	}
	else if (idx == 4)
	{
	strTemp += _T("/..");
	}

	}
	m_Spread.SetCol(1);
	m_Spread.SetRow(15);
	m_Spread.SetTypeButtonText(strTemp);

	strTemp = _T("");
	for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
	{
	if (idx < 2)
	{
	if (idx)
	strTemp += _T("/");
	else
	strTemp += _T("(MT) ");
	strVal.Format(_T("%.1f"), m_fFineLineWidthGroup[idx]);
	strTemp += strVal;
	}
	else if (idx == 2)
	{
	strTemp += _T("/..");
	}

	}
	m_Spread.SetCol(0);
	m_Spread.SetRow(15);
	m_Spread.SetText(strTemp);
	}
	}
	}
	}

	break;


	case 2:
	break;
	case 3:
	break;
	case 4:
	break;
	case 5:
	break;
	case 6:
	break;
	case 7:		//20100322 hjc add
	break;
	}
	*/
	return 0;
}

LRESULT CDlgSpec::OnClickFpspread1(WPARAM wParam, LPARAM lParam)
{
	/*	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	// TODO: Add your control notification handler code here
	CString strTemp;
	SS_CELLCOORD* info = (SS_CELLCOORD*)lParam;

	SS_COORD Col = info->Col;
	SS_COORD Row = info->Row;

	m_Spread.m_nClickedCol = Col;
	m_Spread.m_nClickedRow = Row;

	if (Col == 0) // To Prevent Selecting Line.
	{
	m_Spread.SetActiveCell(0, 0);
	m_Spread.SetRetainSelBlock(FALSE);
	m_Spread.ClearSelection();
	}

	BOOL bNoEdit = FALSE;
	switch (m_nTabNum)
	{
	case 0:
	if (Col == 1)
	m_nSpreadCellFocusPos[0] = Row;

	//150611 hjc add
	if (pGlobalDoc->m_bUseCombo)
	{
	//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	if (Col == 1 && (Row == 9 || Row == 10))
	{
	bNoEdit = TRUE;
	}
	}
	break;
	case 1:
	if (Col == 1)
	m_nSpreadCellFocusPos[1] = Row;

	//150611 hjc add
	if (pGlobalDoc->m_bUseCombo)
	{
	//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	if (Col == 1 && (Row == 9 || Row == 10))
	{
	bNoEdit = TRUE;
	}
	}
	break;
	case 2:
	if (Col == 1)
	m_nSpreadCellFocusPos[2] = Row;

	//150611 hjc add
	if (pGlobalDoc->m_bUseCombo)
	{
	//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	if (Col == 1 && Row == 5)
	{
	bNoEdit = TRUE;
	}
	}
	break;
	case 3:
	//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	if (Col == 1 && (Row == 2 || Row == 5 || Row == 8))	//20100322 hjc add	//170112 hjc mod
	{
	bNoEdit = TRUE;
	}

	if (Col == 1)
	m_nSpreadCellFocusPos[3] = Row;

	break;
	case 4:	//20100322 hjc add
	//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	if (Col == 1 && (Row == 7 || Row == 9 || Row == 12 || Row == 16 || Row == 18 || Row == 21))
	{
	bNoEdit = TRUE;
	}

	if (Col == 1)
	m_nSpreadCellFocusPos[4] = Row;

	break;
	case 5:
	if (Col == 1)
	m_nSpreadCellFocusPos[5] = Row;

	//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	//20090311 hjc modify
	if (Col == 1 && Row == 7)
	{
	bNoEdit = TRUE;
	}

	break;
	case 6:
	if (Col == 1)
	m_nSpreadCellFocusPos[6] = Row;
	break;
	case 7:
	if (Col == 1)
	m_nSpreadCellFocusPos[7] = Row;

	//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	if (Col == 1 && (Row == 4 || Row == 7))	//20100210 hjc add
	{
	bNoEdit = TRUE;
	}

	break;

	default:
	;
	break;
	}

	if (Col == 1)
	{
	RefreshSheetOnChanging();
	//EDIT∏µÂ∏¶ ƒ“¥Ÿ.
	if (bNoEdit == FALSE)
	{
	if (!m_Spread.GetEditMode())
	m_Spread.SetEditMode(TRUE); //160302 LGH ADD
	}
	else
	{
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	}
	*/
	return 0;
}

LRESULT CDlgSpec::OnDblClickFpspread1(WPARAM wParam, LPARAM lParam)
{
	/*	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	SS_CELLCOORD* info = (SS_CELLCOORD*)lParam;

	SS_COORD Col = info->Col;
	SS_COORD Row = info->Row;

	m_Spread.m_nClickedCol = Col;
	m_Spread.m_nClickedRow = Row;

	if (Col == 0) // To Prevent Selecting Line.
	{
	m_Spread.SetActiveCell(0, 0);
	m_Spread.SetRetainSelBlock(FALSE);
	m_Spread.ClearSelection();
	}
	else // About Combo Box To Prevent Editting.
	{
	switch (m_nTabNum)
	{
	case 0:
	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	if (Col == 1 && (Row == 9 || Row == 10))
	{
	m_Spread.SetActiveCell(0, 0);
	m_Spread.SetRetainSelBlock(FALSE);
	m_Spread.ClearSelection();
	}
	}
	break;
	case 1:
	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	if (Col == 1 && (Row == 9 || Row == 10))
	{
	m_Spread.SetActiveCell(0, 0);
	m_Spread.SetRetainSelBlock(FALSE);
	m_Spread.ClearSelection();
	}
	}
	break;
	case 2:
	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	if (Col == 1 && Row == 5)
	{
	m_Spread.SetActiveCell(0, 0);
	m_Spread.SetRetainSelBlock(FALSE);
	m_Spread.ClearSelection();
	}
	}
	break;
	case 3:
	if (Col == 1 && (Row == 2 || Row == 5))
	{
	m_Spread.SetActiveCell(0, 0);
	m_Spread.SetRetainSelBlock(FALSE);
	m_Spread.ClearSelection();
	}
	break;
	case 4:		//20100322 hjc add
	if (Col == 1 && (Row == 7 || Row == 9 || Row == 12 || Row == 16 || Row == 18 || Row == 21))
	{
	m_Spread.SetActiveCell(0, 0);
	m_Spread.SetRetainSelBlock(FALSE);
	m_Spread.ClearSelection();
	}
	break;
	case 5:
	//20090311 hjc modify
	if (Col == 1 && (Row == 7 || Row == 9))
	{
	m_Spread.SetActiveCell(0, 0);
	m_Spread.SetRetainSelBlock(FALSE);
	m_Spread.ClearSelection();
	}
	break;
	case 6:
	break;
	case 7:
	if (Col == 1 && (Row == 4 || Row == 7))	//20100210 hjc mod
	{
	m_Spread.SetActiveCell(0, 0);
	m_Spread.SetRetainSelBlock(FALSE);
	m_Spread.ClearSelection();
	}
	break;
	default:
	;
	break;
	}
	}*/
	return 0;
}

LRESULT CDlgSpec::OnComboCloseUpFpspread1(WPARAM wParam, LPARAM lParam)
{
	/*	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	SS_CELLCOORD* pCombo = (SS_CELLCOORD*)lParam;

	SS_COORD Col = pCombo->Col;
	SS_COORD Row = pCombo->Row;

	// TODO: Add your control notification handler code here

	// Verify Combo Box Text.

	CString strTemp, strInfo;
	int NextNum, currNum, ModifiedNum;


	switch (m_nTabNum)
	{

	case 0:
	if (SpecData.nLineWidthGroupNum == 0 || AoiParam()->m_bUseMultilineSpecEx)
	{
	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	m_nSpreadCellFocusPos[0] = Row;

	if (Col == 1 && Row == 9)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
	{
	DisplaySpread(0);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)
	{
	CString strNewVal = CheckLock(0, 9, strTemp);

	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	if (strNewVal == "Highest")
	strTemp = strNewVal + " (90%)";
	if (strNewVal == "VeryHigh")
	strTemp = strNewVal + " (80%)";
	if (strNewVal == "High")
	strTemp = strNewVal + " (70%)";
	if (strNewVal == "Normal")
	strTemp = strNewVal + " (60%)";
	if (strNewVal == "Low")
	strTemp = strNewVal + " (50%)";
	if (strNewVal == "VeryLow")
	strTemp = strNewVal + " (40%)";
	if (strNewVal == "Lowest")
	strTemp = strNewVal + " (30%)";
	if (strNewVal == "MaxLimit")		//140126 hjc add
	strTemp = strNewVal + " (10%)";
	m_Spread.SetText(strTemp);

	strTemp = strNewVal;
	}
	}

	if (m_strOriginData[0][9] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (9 - 1)); // Bit Flag.
	}
	m_strNick[0] = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	if (Col == 1 && Row == 10)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(10);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
	{
	DisplaySpread(0);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)
	{
	CString strNewVal = CheckLock(0, 10, strTemp);

	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	if (strNewVal == "Highest")
	strTemp = strNewVal + " (110%)";
	if (strNewVal == "VeryHigh")
	strTemp = strNewVal + " (120%)";
	if (strNewVal == "High")
	strTemp = strNewVal + " (130%)";
	if (strNewVal == "Normal")
	strTemp = strNewVal + " (140%)";
	if (strNewVal == "Low")
	strTemp = strNewVal + " (150%)";
	if (strNewVal == "VeryLow")
	strTemp = strNewVal + " (160%)";
	if (strNewVal == "Lowest")
	strTemp = strNewVal + " (170%)";
	if (strNewVal == "MaxLimit")		//140126 hjc add
	strTemp = strNewVal + " (190%)";

	m_Spread.SetText(strTemp);

	strTemp = strNewVal;
	}

	}
	if (m_strOriginData[0][10] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (10 - 1)); // Bit Flag.
	}
	m_strProtrusion[0] = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	}
	}
	break;
	case 1:
	if (SpecData.nLineWidthGroupNum == 0 || AoiParam()->m_bUseMultilineSpecEx)
	{
	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	m_nSpreadCellFocusPos[1] = Row;

	if (Col == 1 && Row == 9)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest" || strTemp == "MaxLimit"))
	{
	DisplaySpread(1);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)
	{

	CString strNewVal = CheckLock(1, 9, strTemp);

	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	if (strNewVal == "Highest")
	strTemp = strNewVal + " (90%)";
	if (strNewVal == "VeryHigh")
	strTemp = strNewVal + " (80%)";
	if (strNewVal == "High")
	strTemp = strNewVal + " (70%)";
	if (strNewVal == "Normal")
	strTemp = strNewVal + " (60%)";
	if (strNewVal == "Low")
	strTemp = strNewVal + " (50%)";
	if (strNewVal == "VeryLow")
	strTemp = strNewVal + " (40%)";
	if (strNewVal == "Lowest")
	strTemp = strNewVal + " (30%)";
	if (strNewVal == "MaxLimit")		//140126 hjc add
	strTemp = strNewVal + " (10%)";
	m_Spread.SetText(strTemp);

	strTemp = strNewVal;
	}

	}
	if (m_strOriginData[1][9] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (9 - 1)); // Bit Flag.
	}
	m_strFineNick[0] = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	if (Col == 1 && Row == 10)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(10);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest" || strTemp == "MaxLimit"))
	{
	DisplaySpread(1);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)
	{
	CString strNewVal = CheckLock(1, 10, strTemp);

	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	if (strNewVal == "Highest")
	strTemp = strNewVal + " (110%)";
	if (strNewVal == "VeryHigh")
	strTemp = strNewVal + " (120%)";
	if (strNewVal == "High")
	strTemp = strNewVal + " (130%)";
	if (strNewVal == "Normal")
	strTemp = strNewVal + " (140%)";
	if (strNewVal == "Low")
	strTemp = strNewVal + " (150%)";
	if (strNewVal == "VeryLow")
	strTemp = strNewVal + " (160%)";
	if (strNewVal == "Lowest")
	strTemp = strNewVal + " (170%)";
	if (strNewVal == "MaxLimit")		//140126 hjc add
	strTemp = strNewVal + " (190%)";

	m_Spread.SetText(strTemp);

	strTemp = strNewVal;
	}

	}
	if (m_strOriginData[1][10] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (10 - 1)); // Bit Flag.
	}
	m_strFineProtrusion[0] = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	}
	}
	break;

	case 2:
	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	m_nSpreadCellFocusPos[2] = Row;

	if (Col == 1 && Row == 5)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(5);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	if (nPos >= 0)
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(2);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)
	{
	CString strNewVal = CheckLock(2, 5, strTemp);

	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	if (strNewVal == "Highest")
	strTemp = strNewVal + " (90%)";
	if (strNewVal == "VeryHigh")
	strTemp = strNewVal + " (80%)";
	if (strNewVal == "High")
	strTemp = strNewVal + " (70%)";
	if (strNewVal == "Normal")
	strTemp = strNewVal + " (60%)";
	if (strNewVal == "Low")
	strTemp = strNewVal + " (50%)";
	if (strNewVal == "VeryLow")
	strTemp = strNewVal + " (40%)";
	if (strNewVal == "Lowest")
	strTemp = strNewVal + " (30%)";

	m_Spread.SetText(strTemp);

	strTemp = strNewVal;
	}

	}
	if (m_strOriginData[2][5] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (5 - 1)); // Bit Flag.
	}
	m_strMinSP = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	}
	break;
	case 3:
	m_nSpreadCellFocusPos[3] = Row;

	if (Col == 1 && Row == 2)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(2);
	strTemp = m_Spread.GetText();
	//strcpy(SpecData.szVDPadPrecName, strTemp);
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(3);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)
	{
	CString strNewVal = CheckLock(3, 2, strTemp);
	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	DisplaySpread(3);
	return 0;
	}
	}

	if (m_strOriginData[3][2] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P3_M4");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (2 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[3][2]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_LARGE, ModifiedNum, strTemp) == SUCCESS)
	//	m_strOriginData[3][17] = m_strLP_Prec;
	m_strOriginData[3][2] = SpecData.szLPADRLName;	//20100305 hjc mod
	}
	}
	else
	{
	//	m_strLP_Prec = m_strOriginData[3][17];
	strTemp = m_strLP_Prec = m_strOriginData[3][2];	//20100305 hjc mod
	DisplaySpread(3);
	}
	}
	else
	{
	//	m_strLP_Prec = m_strOriginData[3][17];
	strTemp = m_strLP_Prec = m_strOriginData[3][2];	//20100305 hjc mod
	DisplaySpread(3);
	}
	}
	m_strLP_Prec = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	if (Col == 1 && Row == 5)  // Extra RLE
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(5);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(3);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)
	{
	CString strNewVal = CheckLock(3, 5, strTemp);
	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	DisplaySpread(3);
	return 0;
	}
	}

	if (m_strOriginData[3][5] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P0_M5");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (5 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[3][5]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_SPACE, ModifiedNum, strTemp) == SUCCESS)
	m_strOriginData[3][5] = SpecData.szSPRLName;
	}
	}
	else
	{
	strTemp = m_strSP_Prec = m_strOriginData[3][5];	//170112 hjc mod
	DisplaySpread(3);
	}
	}
	else
	{
	strTemp = m_strSP_Prec = m_strOriginData[3][5];	//170112 hjc mod
	DisplaySpread(3);
	}
	}
	m_strSP_Prec = strTemp;

	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	//170112 hjc add
	if (Col == 1 && Row == 8)  // Space Pad Ext RLE
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(8);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(3);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)
	{
	CString strNewVal = CheckLock(3, 8, strTemp);
	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	DisplaySpread(3);
	return 0;
	}
	}

	if (m_strOriginData[3][8] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P0_M5");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (8 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[3][8]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_SPACEEXT, ModifiedNum, strTemp) == SUCCESS)
	m_strOriginData[3][8] = SpecData.szSPACEEXTRLName;
	}
	}
	else
	{
	strTemp = m_strSPExt_Prec = m_strOriginData[3][8];	//170112 hjc mod
	DisplaySpread(3);
	}
	}
	else
	{
	strTemp = m_strSPExt_Prec = m_strOriginData[3][8];	//170112 hjc mod
	DisplaySpread(3);
	}
	}
	m_strSPExt_Prec = strTemp;

	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	break;
	case 4:		//20100322 hjc add
	m_nSpreadCellFocusPos[4] = Row;

	if (Col == 1 && Row == 7)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(7);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(4);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)
	{
	CString strNewVal = CheckLock(4, 7, strTemp);
	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	DisplaySpread(4);
	return 0;
	}
	}

	if (m_strOriginData[4][7] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P3_M1");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red
	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (7 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[4][7]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_SMALL, ModifiedNum, strTemp) == SUCCESS)
	//	m_strOriginData[3][6] = m_strPadBallPrec;
	m_strOriginData[4][7] = SpecData.szPADRLPrecName;	//20100305 hjc mod
	}
	}
	else
	{
	//	m_strPadBallPrec = m_strOriginData[3][6];
	strTemp = m_strPadBallPrec = m_strOriginData[4][7];	//20100305 hjc mod
	DisplaySpread(4);
	}
	}
	else
	{
	//	m_strPadBallPrec = m_strOriginData[3][6];
	strTemp = m_strPadBallPrec = m_strOriginData[4][7];	//20100305 hjc mod
	DisplaySpread(4);
	}
	}
	m_strPadBallPrec = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	if (Col == 1 && Row == 9)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(4);
	return 0;
	}
	if (AoiParam()->m_bSetSpecLocking)
	{
	CString strNewVal = CheckLock(4, 9, strTemp);
	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	DisplaySpread(4);
	return 0;
	}
	}

	if (m_strOriginData[4][9] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P3_M3");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (9 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[4][9]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_PADTIP, ModifiedNum, strTemp) == SUCCESS)
	m_strOriginData[4][9] = SpecData.szPADTipPrecName;
	}
	}
	else
	{
	strTemp = m_strPadTip_Prec = m_strOriginData[4][9];	//170112 hjc mod
	//	StringToChar(m_strOriginData[4][9],SpecData.szPADTipPrecName);
	//	strTemp = m_strOriginData[4][9];	//20100305 hjc mod
	DisplaySpread(4);
	}
	}
	else
	{
	strTemp = m_strPadTip_Prec = m_strOriginData[4][9];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	m_strPadTip_Prec = strTemp;	//170112 hjc mod
	//	StringToChar(strTemp,SpecData.szPADTipPrecName);
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	if (Col == 1 && Row == 12)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(12);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(4);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)
	{
	CString strNewVal = CheckLock(4, 12, strTemp);
	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	DisplaySpread(4);
	return 0;
	}
	}

	if (m_strOriginData[4][12] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P3_M2");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (12 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[4][12]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_AR, ModifiedNum, strTemp) == SUCCESS)
	m_strOriginData[4][12] = SpecData.szARLandPrecName;
	}
	}
	else
	{
	strTemp = m_strARLand_Prec = m_strOriginData[4][12];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	else
	{
	strTemp = m_strARLand_Prec = m_strOriginData[4][12];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	m_strARLand_Prec = strTemp;
	StringToChar(strTemp, SpecData.szARLandPrecName);
	//			strcpy(SpecData.szARLandPrecName, strTemp);
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	//20100322 hjc add
	if (Col == 1 && Row == 16)  // Fine PAD Size
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(16);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(4);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)
	{
	CString strNewVal = CheckLock(4, 16, strTemp);
	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	DisplaySpread(4);
	return 0;
	}
	}

	if (m_strOriginData[4][16] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P3_M15");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (16 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[4][16]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_CO2, ModifiedNum, strTemp) == SUCCESS)	//20100322 hjc mod
	m_strOriginData[4][16] = SpecData.szCO2LandPrecName;
	}
	}
	else
	{
	strTemp = m_strCO2Land_Prec = m_strOriginData[4][16];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	else
	{
	strTemp = m_strCO2Land_Prec = m_strOriginData[4][16];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	m_strCO2Land_Prec = strTemp;

	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	if (Col == 1 && Row == 18)  // Fine PAD Size
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(18);
	strTemp = m_Spread.GetText();
	//			int nPos = strTemp.Find(_T(" ",0);
	//			strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Yes" || strTemp == "No"))
	{
	DisplaySpread(4);
	return 0;
	}
	if (m_strOriginData[4][18] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (18 - 1)); // Bit Flag.

	StringToChar(strTemp, SpecData.szCO2LandAlignMode);
	//					strcpy(SpecData.szCO2LandAlignMode, strTemp);
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	else
	{
	StringToChar(m_strOriginData[4][18], SpecData.szCO2LandAlignMode);
	//					strcpy(SpecData.szCO2LandAlignMode, m_strOriginData[4][18]);
	strTemp = m_strOriginData[4][18];	//20100305 hjc mod
	DisplaySpread(4);
	}
	}
	if (strTemp == "Yes")
	SpecData.nCO2LandAlignMode = 1;
	else
	SpecData.nCO2LandAlignMode = 0;

	StringToChar(strTemp, SpecData.szCO2LandAlignMode);
	//			strcpy(SpecData.szCO2LandAlignMode, strTemp);
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	if (Col == 1 && Row == 21)  // Fine PAD Size
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(21);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(4);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)
	{
	CString strNewVal = CheckLock(4, 21, strTemp);
	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	DisplaySpread(4);
	return 0;
	}
	}

	if (m_strOriginData[4][21] != strTemp)
	{
	if (pGlobalDoc->CheckAllMasterLoc(TRUE))
	{
	pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "OnComboCloseUpFpspread1_P3_M6");
	if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (21 - 1)); // Bit Flag.

	currNum = Level2Number(m_strOriginData[4][21]);
	NextNum = Level2Number(strTemp);
	ModifiedNum = NextNum - currNum;
	if (ModifiedNum != 0)
	{
	if (ChangePADModifiyDataAllClient(PAD_FINE, ModifiedNum, strTemp) == SUCCESS)  // 20101208 bug fix PAD_SPACE->PAD_FINE by ljg
	m_strOriginData[4][21] = SpecData.szPADFine_PrecName;
	}
	}
	else
	{
	strTemp = m_strFPad_Prec = m_strOriginData[4][21];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	else
	{
	strTemp = m_strFPad_Prec = m_strOriginData[4][21];	//170112 hjc mod
	DisplaySpread(4);
	}
	}
	m_strFPad_Prec = strTemp;

	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	break;
	case 5:
	m_nSpreadCellFocusPos[5] = Row;

	//20090311 hjc modify
	if (Col == 1 && Row == 7)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(7);
	strTemp = m_Spread.GetText();
	int nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
	|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
	|| strTemp == "Lowest"))
	{
	DisplaySpread(5);
	return 0;
	}

	if (AoiParam()->m_bSetSpecLocking)
	{
	CString strNewVal = CheckLock(5, 7, strTemp);

	if (strNewVal.CompareNoCase(strTemp) != 0)
	{
	if (strNewVal == "Highest")
	strTemp = strNewVal + " (-1)";
	if (strNewVal == "VeryHigh")
	strTemp = strNewVal + " (-2)";
	if (strNewVal == "High")
	strTemp = strNewVal + " (-3)";
	if (strNewVal == "Normal")
	strTemp = strNewVal + " (-4)";
	if (strNewVal == "Low")
	strTemp = strNewVal + " (-5)";
	if (strNewVal == "VeryLow")
	strTemp = strNewVal + " (-6)";
	if (strNewVal == "Lowest")
	strTemp = strNewVal + " (-7)";

	m_Spread.SetText(strTemp);

	strTemp = strNewVal;
	}

	}

	if (m_strOriginData[5][7] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (7 - 1)); // Bit Flag.
	}
	m_strHolePrec = strTemp;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}

	if (Col == 1 && Row == 9)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(9);
	strTemp = m_Spread.GetText();

	if (!(strTemp == "AreaMode" || strTemp == "EdgeMode"))
	{
	DisplaySpread(5);
	return 0;
	}
	if (m_strOriginData[5][9] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (9 - 1)); // Bit Flag.
	}
	StringToChar(strTemp, SpecData.szVHMode);
	//			strcpy(SpecData.szVHMode, strTemp);
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	//20090311 hjc add
	if (strTemp == "AreaMode")
	{
	//Disable Cells
	m_Spread.SetCol(1);

	m_Spread.SetRow(15);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(TRUE);
	m_Spread.SetForeColor(RGB(152, 152, 152));

	m_Spread.SetRow(16);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(TRUE);
	m_Spread.SetForeColor(RGB(152, 152, 152));

	//Temperary 2006.10.13 -----------------------------------
	m_Spread.SetRow(17);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(TRUE);
	m_Spread.SetForeColor(RGB(152, 152, 152));

	m_Spread.SetRow(18);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(TRUE);
	m_Spread.SetForeColor(RGB(152, 152, 152));
	}
	else
	{
	//Disable Cells
	m_Spread.SetCol(1);

	m_Spread.SetRow(15);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(FALSE);
	m_Spread.SetForeColor(RGB(60, 145, 103));

	m_Spread.SetRow(16);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(FALSE);
	m_Spread.SetForeColor(RGB(60, 145, 103));

	//Temperary 2006.10.13 -----------------------------------
	m_Spread.SetRow(17);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(FALSE);
	m_Spread.SetForeColor(RGB(60, 145, 103));

	m_Spread.SetRow(18);
	//m_Spread.SetCellType(TYPE_STATIC);
	m_Spread.SetLock(FALSE);
	m_Spread.SetForeColor(RGB(60, 145, 103));
	}
	}
	break;

	case 6:
	m_nSpreadCellFocusPos[6] = Row;
	break;
	case 7:
	m_nSpreadCellFocusPos[7] = Row;
	if (Col == 1 && Row == 4)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(4);
	TCHAR str[1024];
	m_Spread.GetData(1, 4, str);
	strTemp = CString(str);
	strTemp = m_Spread.GetText();
	//160924 LGH
	if (!(strTemp == _T("Highest") || strTemp == _T("VeryHigh") || strTemp == _T("Maximum") || strTemp == _T("High") || strTemp == _T("Normal") || strTemp == _T("Low")))
	//if(!(strTemp == "High" || strTemp == "Normal" || strTemp == "Low"))
	{
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	DisplaySpread(7);
	return 0;
	}
	if (m_strOriginData[7][4] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (4 - 1)); // Bit Flag.
	}
	m_strThetaAlign = strTemp;
	//m_Spread.SetEditMode(FALSE);
	}
	if (Col == 1 && Row == 7)	//20100210 hjc add
	{
	int nPos;
	m_Spread.SetCol(1);
	m_Spread.SetRow(7);
	if (pGlobalDoc->m_bUseMultiVaccumControl)	//130311 hjc add
	{
	strTemp = m_Spread.GetText();
	nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	if (!(strTemp == "Both" || strTemp == "FirstOnly"))
	{
	DisplaySpread(7);
	return 0;
	}
	if (m_strOriginData[7][7] != strTemp)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (7 - 1)); // Bit Flag.
	}
	m_strSelectVaccum = strTemp;
	if (strTemp == "Both")
	SpecData.nSelectVaccum = 1;
	else
	SpecData.nSelectVaccum = 2;
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);
	}
	else
	{
	strTemp = m_Spread.GetText();
	nPos = strTemp.Find(_T(" "), 0);
	strTemp = strTemp.Left(nPos);
	m_strSelectVaccum = strTemp;
	SpecData.nSelectVaccum = 1;
	}
	}

	#ifdef IRIS_AXIS
	if (1)
	{
	int nCheckRow = 8;
	if (AoiParam()->m_bUseAutoPinPosAdjust || g_bUsePinPosEstimate)
	nCheckRow = 10;

	if (Col == 1 && Row == nCheckRow)
	{
	m_Spread.SetCol(1);
	m_Spread.SetRow(nCheckRow);
	TCHAR str[1024];
	m_Spread.GetData(1, nCheckRow, str);
	strTemp = CString(str);
	strTemp = m_Spread.GetText();

	for (int i = 0; i < 12; i++)
	{
	double dPosName = fabs(pGlobalDoc->m_IRISAxisControl.m_dIRISPosName[i] - _ttof(strTemp));

	if (dPosName < 0.01)
	{
	m_nIRISPosID = i;
	break;
	}
	}

	if (fabs(_ttof(m_strOriginData[7][nCheckRow]) - _ttof(strTemp)) > 0.01)
	{
	m_bSpecDataChanged = TRUE;
	m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

	m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (nCheckRow - 1)); // Bit Flag.
	}
	}
	}
	#endif
	break;

	default:
	;
	}
	if (m_Spread.GetEditMode())
	m_Spread.SetEditMode(FALSE);*/
	return 0;
}

void CDlgSpec::OnMouseDownFpspread1(short Button, short Shift, long x, long y)
{
	// TODO: Add your control notification handler code here
	/*
	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));

	long lx, ly, lw, lh;

	// ?EΩ√Ω∫≈€¿« «»ºø¥ÅETwips∞™¿ª ∆ƒæ««—¥Ÿ.
	CDC* pDC = GetDC();
	int nLogY = pDC->GetDeviceCaps(LOGPIXELSY);
	ReleaseDC(pDC);
	int nTwipPerPixel = 1440 / nLogY;

	long lCol = x; // «ˆ¿ÅE∏∂øÅE∫∞?≈¨∏Øµ» ∆Æ¿¨	x¡¬«•.
	long lRow = y; // «ˆ¿ÅE∏∂øÅE∫∞?≈¨∏Øµ» ∆Æ¿¨	y¡¬«•.

	switch (m_nTabNum)
	{
	case 0:
	// Edit Box øµø™
	m_Spread.GetCellPos(1, 1, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 1;
	}
	m_Spread.GetCellPos(1, 2, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 2;
	}
	m_Spread.GetCellPos(1, 3, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 3;
	}
	m_Spread.GetCellPos(1, 4, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 4;
	}

	m_Spread.GetCellPos(1, 5, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 5;
	}

	m_Spread.GetCellPos(1, 6, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 6;
	}
	m_Spread.GetCellPos(1, 7, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 7;
	}
	m_Spread.GetCellPos(1, 8, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 8;
	}
	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	// Combo Box øµø™
	m_Spread.GetCellPos(1, 9, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[0] = 9;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	m_Spread.GetCellPos(1, 10, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[0] = 10;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}
	}
	else
	{
	m_Spread.GetCellPos(1, 9, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 9;
	}
	m_Spread.GetCellPos(1, 10, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 10;
	}
	}

	m_Spread.GetCellPos(1, 11, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 11;
	}

	m_Spread.GetCellPos(1, 12, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 12;
	}
	m_Spread.GetCellPos(1, 13, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 13;
	}
	m_Spread.GetCellPos(1, 14, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 14;
	}
	m_Spread.GetCellPos(1, 15, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 15;
	}
	m_Spread.GetCellPos(1, 16, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[0] = 16;
	}
	break;
	case 1:
	// Edit Box øµø™
	m_Spread.GetCellPos(1, 1, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 1;
	}
	m_Spread.GetCellPos(1, 2, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 2;
	}
	m_Spread.GetCellPos(1, 3, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 3;
	}
	m_Spread.GetCellPos(1, 4, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 4;
	}

	m_Spread.GetCellPos(1, 5, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 5;
	}

	m_Spread.GetCellPos(1, 6, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 6;
	}
	m_Spread.GetCellPos(1, 7, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 7;
	}
	m_Spread.GetCellPos(1, 8, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 8;
	}

	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	// Combo Box øµø™
	m_Spread.GetCellPos(1, 9, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[1] = 9;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	m_Spread.GetCellPos(1, 10, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[1] = 10;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}
	}
	else
	{
	m_Spread.GetCellPos(1, 9, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 9;
	}
	m_Spread.GetCellPos(1, 10, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 10;
	}
	}

	m_Spread.GetCellPos(1, 11, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 11;
	}

	m_Spread.GetCellPos(1, 12, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 12;
	}
	m_Spread.GetCellPos(1, 13, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 13;
	}
	m_Spread.GetCellPos(1, 14, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 14;
	}
	m_Spread.GetCellPos(1, 15, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 15;
	}
	m_Spread.GetCellPos(1, 16, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[1] = 16;
	}
	break;
	case 2:
	// Edit Box øµø™
	m_Spread.GetCellPos(1, 1, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[2] = 1;
	}
	m_Spread.GetCellPos(1, 2, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[2] = 2;
	}
	m_Spread.GetCellPos(1, 3, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[2] = 3;
	}
	m_Spread.GetCellPos(1, 4, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[2] = 4;
	}
	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
	// Combo Box øµø™
	m_Spread.GetCellPos(1, 5, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[2] = 5;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}
	}
	else
	{
	m_Spread.GetCellPos(1, 5, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[2] = 5;
	}
	}

	m_Spread.GetCellPos(1, 6, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[2] = 6;
	}
	m_Spread.GetCellPos(1, 7, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[2] = 7;
	}
	m_Spread.GetCellPos(1, 8, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[2] = 8;
	}
	m_Spread.GetCellPos(1, 9, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[2] = 9;
	}
	break;
	//20100322 hjc add
	case 3:
	// Edit Box øµø™
	m_Spread.GetCellPos(1, 1, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[3] = 1;
	}

	// Combo Box øµø™
	m_Spread.GetCellPos(1, 2, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[3] = 2;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	m_Spread.GetCellPos(1, 3, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[3] = 3;
	}
	m_Spread.GetCellPos(1, 4, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[3] = 4;
	}
	// Combo Box øµø™
	m_Spread.GetCellPos(1, 5, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[3] = 5;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	m_Spread.GetCellPos(1, 6, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[3] = 6;
	}

	m_Spread.GetCellPos(1, 7, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[3] = 7;
	}

	// Combo Box øµø™	//170112 hjc add
	m_Spread.GetCellPos(1, 8, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[3] = 8;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	m_Spread.GetCellPos(1, 9, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[3] = 9;
	}
	m_Spread.GetCellPos(1, 10, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».		//jun 20120903 for LG_CCL-Inspector
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[3] = 10;
	}
	m_Spread.GetCellPos(1, 11, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[3] = 11;
	}
	m_Spread.GetCellPos(1, 12, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[3] = 12;
	}

	if (SpecData.bEnableCharInspection)
	{
	m_Spread.GetCellPos(1, 13, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[3] = 13;
	}

	m_Spread.GetCellPos(1, 14, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[3] = 14;
	}

	m_Spread.GetCellPos(1, 15, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[3] = 15;
	}
	}

	//---------

	break;
	case 4:
	// Edit Box øµø™
	m_Spread.GetCellPos(1, 1, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 1;
	}
	m_Spread.GetCellPos(1, 2, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 2;
	}
	m_Spread.GetCellPos(1, 3, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 3;
	}
	m_Spread.GetCellPos(1, 4, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 4;
	}
	m_Spread.GetCellPos(1, 5, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 5;
	}
	m_Spread.GetCellPos(1, 5, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 6;
	}

	// Combo Box øµø™
	m_Spread.GetCellPos(1, 7, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[4] = 7;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	m_Spread.GetCellPos(1, 8, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 8;
	}

	m_Spread.GetCellPos(1, 9, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[4] = 9;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	m_Spread.GetCellPos(1, 10, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 10;
	}
	m_Spread.GetCellPos(1, 11, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 11;
	}

	// Combo Box øµø™
	m_Spread.GetCellPos(1, 12, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[4] = 12;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	m_Spread.GetCellPos(1, 13, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 13;
	}
	m_Spread.GetCellPos(1, 14, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 14;
	}
	m_Spread.GetCellPos(1, 15, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 15;
	}

	// Combo Box øµø™
	m_Spread.GetCellPos(1, 16, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[4] = 16;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	m_Spread.GetCellPos(1, 17, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 17;
	}

	// Combo Box øµø™
	m_Spread.GetCellPos(1, 18, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[4] = 18;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	m_Spread.GetCellPos(1, 19, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 19;
	}

	m_Spread.GetCellPos(1, 20, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 20;
	}

	m_Spread.GetCellPos(1, 21, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[4] = 21;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	m_Spread.GetCellPos(1, 22, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[4] = 22;
	}
	//---------
	break;
	case 5:
	m_Spread.GetCellPos(1, 1, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 1;
	}
	m_Spread.GetCellPos(1, 2, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 2;
	}
	m_Spread.GetCellPos(1, 3, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 3;
	}
	m_Spread.GetCellPos(1, 4, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 4;
	}
	m_Spread.GetCellPos(1, 5, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 5;
	}
	m_Spread.GetCellPos(1, 6, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 6;
	}
	// Combo Box øµø™
	//20090311 hjc modify
	m_Spread.GetCellPos(1, 7, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[5] = 7;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	m_Spread.GetCellPos(1, 6, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 8;
	}

	m_Spread.GetCellPos(1, 9, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[5] = 9;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	m_Spread.GetCellPos(1, 6, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 10;
	}

	m_Spread.GetCellPos(1, 11, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 11;

	}
	m_Spread.GetCellPos(1, 12, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 12;
	}
	m_Spread.GetCellPos(1, 13, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 13;
	}
	m_Spread.GetCellPos(1, 14, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 14;
	}
	m_Spread.GetCellPos(1, 15, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 15;
	}
	m_Spread.GetCellPos(1, 16, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 16;
	}
	m_Spread.GetCellPos(1, 17, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 17;
	}
	m_Spread.GetCellPos(1, 18, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[5] = 18;
	}
	break;
	case 6:
	//20090216 chg
	m_Spread.GetCellPos(1, 1, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 1;
	}
	m_Spread.GetCellPos(1, 2, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 2;
	}
	m_Spread.GetCellPos(1, 3, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 3;
	}
	m_Spread.GetCellPos(1, 4, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 4;
	}
	m_Spread.GetCellPos(1, 5, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 5;
	}
	m_Spread.GetCellPos(1, 6, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 6;
	}
	//20090412 hjc
	m_Spread.GetCellPos(1, 7, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 7;
	}
	m_Spread.GetCellPos(1, 8, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 8;
	}
	//--------------------
	m_Spread.GetCellPos(1, 9, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 9;
	}
	m_Spread.GetCellPos(1, 10, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 10;
	}
	m_Spread.GetCellPos(1, 11, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 11;
	}	//111214 hjc mod
	m_Spread.GetCellPos(1, 12, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 12;
	}	//120105 hjc mod
	m_Spread.GetCellPos(1, 13, &lx, &ly, &lw, &lh);
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 13;
	}	//120109 hjc mod
	m_Spread.GetCellPos(1, 14, &lx, &ly, &lw, &lh);
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 14;
	}	//120105 hjc mod
	m_Spread.GetCellPos(1, 15, &lx, &ly, &lw, &lh);
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_nSpreadCellFocusPos[6] = 15;
	}
	break;
	case 7:
	// Combo Box øµø™
	m_Spread.GetCellPos(1, 4, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[7] = 4;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}

	//20100210 hjc add
	m_Spread.GetCellPos(1, 7, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[7] = 7;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}


	#ifdef IRIS_AXIS
	if (1)
	{
	int nCheckPos = 8;

	if (AoiParam()->m_bUseAutoPinPosAdjust || g_bUsePinPosEstimate)
	nCheckPos = 10;

	m_Spread.GetCellPos(1, nCheckPos, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_bComboReFocus = TRUE;
	m_nSpreadCellFocusPos[7] = nCheckPos;
	m_Spread.SetLock(FALSE);//Combo Box∏¶ ≈¨∏Ø «“∂ß Edit Mode∏¶ ∏∑¥¬¥Ÿ.
	}
	}
	#endif

	//Disable Cell øµø™
	m_Spread.GetCellPos(1, 2, &lx, &ly, &lw, &lh); // ∆Æ¿¨¡¬«•∏¶ πﬁæ∆ø».
	if (lx < lCol && lCol < lx + lw && ly < lRow && lRow < ly + lh) // CellπÅEßæ»ø?µÈæ˚€¿∏ÅE
	{
	m_Spread.SetActiveCell(0, 0);
	m_Spread.SetRetainSelBlock(FALSE);
	m_Spread.ClearSelection();
	}

	default:
	;
	}
	*/
}



void CDlgSpec::AutoChangeSpecControl(int nDefType, int nRecordK)
{
	//POSITION p = NULL;

	//int nSelID = pGlobalView->m_nSelectDefectListID;

	//POSITION pHead = pGlobalDoc->m_DefectListItem[nSelID].GetHeadPosition();

	//CDefectRawData* pDefect = NULL;
	//BOOL bFind = FALSE;

	//int nCurrentID = 0;
	//for (p = pHead; p != NULL; pGlobalDoc->m_DefectListItem[nSelID].GetNext(p))
	//{
	//	pDefect = (CDefectRawData*)pGlobalDoc->m_DefectListItem[nSelID].GetAt(p);

	//	if (pDefect == NULL)
	//	{
	//		break;
	//	}


	//	if (pDefect->da_Type == nDefType && pDefect->m_nRecordOrg == nRecordK)
	//	{

	//		if (pGlobalView->m_nPrevKDefectID < nCurrentID)
	//		{
	//			pGlobalView->m_nPrevKDefectID = nCurrentID;

	//			pGlobalDoc->m_nGridIndex = nCurrentID + 1;
	//			pGlobalView->m_nCurrentDefect = nCurrentID;

	//			int nCurGridIndex = nCurrentID;// 130701 TEST DISALBE

	//			if (pGlobalView->m_nCurDispDlgId == IDC_BTN_VERIFYVIEW)
	//			{
	//				int nRow = nCurrentID + 1;
	//				if (!AoiParam()->m_bUseNewUI)
	//				{
	//					pGlobalView->m_pDlgVerify->m_Grid.SetRow(nRow);
	//				}

	//				if (nRow < 1)
	//					return;

	//				pGlobalDoc->m_bContinuousDefViewStart = FALSE;
	//				pGlobalDoc->m_bContinuousAOMViewStart = FALSE;
	//				pGlobalDoc->m_nGridIndex = nRow - 1;

	//				if (AoiParam()->m_bUseNewUI)
	//					pGlobalView->m_pDlgVerifyView->m_nGlobalDefectIdx = pGlobalDoc->m_nGridIndex + 1;

	//				pGlobalView->m_pDlgVerifySub->PostMessage(WM_VERIFY_NEXT, 0, 0); // OnVerifyNext() Call
	//			}
	//			else if (pGlobalView->m_nCurDispDlgId == IDC_BTN_SPECVIEW)
	//			{
	//				m_Spread.AutoAttach();

	//				if (m_Spread.GetEditMode())
	//				{
	//					m_Spread.SetEditMode(FALSE);
	//					m_Spread.SetFocus();
	//					return;
	//				}

	//				if (pGlobalDoc->m_nSaveThumbImg != -1)
	//				{
	//					pGlobalView->m_GLopen = 2;
	//					if (pGlobalDoc->m_nGridIndex <= 0)
	//					{
	//						pGlobalView->SetThumbnailImgPack(0);
	//						//pGlobalView->GotoThumbnailPosition(0);//131001 lgh remove
	//					}
	//					else
	//					{
	//						if (nCurGridIndex <= 0) //130520 lgh add For thumbnailpos Bugfix
	//						{
	//							preindex = pGlobalDoc->m_nGridIndex - 1;
	//							pGlobalView->SetThumbnailImgPack(0);//1301516 lgh add if Preindex > Gridindex, Set Thumbnail St Index Set 0
	//																//pGlobalView->GotoThumbnailPosition(0); //131001 lgh remove
	//						}
	//						else
	//						{
	//							pGlobalView->SetThumbnailImgPack(nCurGridIndex); //130701
	//																			 //pGlobalView->GotoThumbnailPosition(nCurGridIndex);//131001 lgh remove
	//						}
	//					}
	//				}
	//				pGlobalView->m_EasySpec.SetDefectVal(pDefect);

	//				int nTabNo = -1;

	//				switch (pDefect->da_Type)
	//				{
	//				case DEF_OPEN:
	//				case DEF_NICK:
	//				case DEF_PROTRUSION:
	//				case DEF_NARROW:
	//				case DEF_WIDE:
	//					nTabNo = 0;
	//					break;

	//				case DEF_SHORT:
	//				case DEF_SPACE:
	//				case DEF_USHORT:
	//					nTabNo = 2;
	//					break;


	//				case DEF_PINHOLE:
	//				case DEF_EXTRA:
	//					nTabNo = 3;
	//					break;

	//				case DEF_PAD:
	//					if (pDefect->m_nRecordOrg >= 51 && pDefect->m_nRecordOrg <= 55)
	//						nTabNo = 8;
	//					else
	//						nTabNo = 4;

	//					break;

	//				case DEF_HOLE_DEFECT:
	//				case DEF_HOLE_MISS:
	//				case DEF_HOLE_OPEN:
	//				case DEF_HOLE_POSITION:
	//				case DEF_VH_DEF:
	//				case DEF_VH_MISS:
	//				case DEF_VH_OPEN:
	//				case DEF_VH_POSITION:
	//					nTabNo = 5;
	//					break;


	//				case DEF_EDGE_NICK:
	//				case DEF_EDGE_PROT:
	//				case DEF_EDGE_SPACE:
	//					nTabNo = 6;
	//					break;
	//				}

	//				if (nTabNo > -1)
	//				{
	//					TabChange(nTabNo);
	//				}

	//			}
	//			bFind = TRUE;
	//			break;
	//		}
	//		else
	//		{
	//			nCurrentID++;
	//			continue;
	//		}
	//	}

	//	nCurrentID++;
	//}

	//if (!bFind)
	//{
	//	pGlobalView->m_nPrevKDefectID = 0;
	//}

}

void CDlgSpec::AtDlgShow()
{
//	if (!pGlobalDoc->m_bSpecLoaded)
//		return;
//	for (int i = 0; i < MAX_HOLE_TYPE; i++)
//		memcpy(&m_DlgSroSpec.m_SRSpec[i], &SpecData.SRSpec[i], sizeof(SROSpec));
//#if CUSTOMER_COMPANY == SHINKO_DENKKI
//	pGlobalView->ViewDlgShinkoRecipe(1);
//#else
//	if (g_bNewRecipeUI && g_bUseZDTNewGEM == 0)
//		pGlobalView->ViewDlgShinkoRecipe(1);
//#endif
//
//	ViewViaExtensionSpec();
//
//	if (g_bShowHeightFixUI)
//		GetDlgItem(IDC_BTN_HEIGHT_FIXED)->ShowWindow(SW_SHOW);
//	else
//		GetDlgItem(IDC_BTN_HEIGHT_FIXED)->ShowWindow(SW_HIDE);
//
//	TCHAR strString[200];
//	CString strPath;
//
//	TCHAR lpszFileName[MAX_PATH];
//	DWORD dwLength = GetCurrentDirectory(MAX_PATH, lpszFileName);
//
//
//	//161206 lgh
//	TC_ITEM item;
//	int nTapNum = 8;
//
//	m_tabDlgInspection.DeleteAllItems();
//
//	CStringArray arr;
//
//	arr.Add(_T("Line"));
//	arr.Add(_T("F.Line"));
//	arr.Add(_T("Space"));
//	arr.Add(_T("Ext/Ph"));
//	arr.Add(_T("PAD"));
//	arr.Add(_T("Hole/VH"));
//	arr.Add(_T("Edge"));
//	arr.Add(_T("Info."));
//
//	if (g_bSRMode)
//		arr.Add(_T("SRO"));
//	if (AoiParam()->m_bUseMultilineSpecEx)
//		arr.Add(_T("Multi Line"));
//
//	if (g_bSRMode)
//		nTapNum++;
//
//	if (AoiParam()->m_bUseMultilineSpecEx)
//		nTapNum++;
//
//	for (int i = 0; i < 8; i++)
//	{
//		CString buffer = arr.GetAt(i);
//		item.mask = TCIF_TEXT;
//		item.pszText = buffer.GetBuffer();
//		m_tabDlgInspection.InsertItem(i, &item);
//		buffer.ReleaseBuffer();
//	}
//
//	m_nTabNum = 8;
//
//	if (g_bSRMode)
//	{
//		item.mask = TCIF_TEXT;
//		CString buffer = arr.GetAt(m_nTabNum);
//		item.pszText = buffer.GetBuffer();
//		buffer.ReleaseBuffer();
//		m_tabDlgInspection.InsertItem(m_nTabNum, &item);
//		m_nTabNum++;
//	}
//
//	if (AoiParam()->m_bUseMultilineSpecEx)
//	{
//		item.mask = TCIF_TEXT;
//		CString buffer = arr.GetAt(m_nTabNum);
//		item.pszText = buffer.GetBuffer();
//		buffer.ReleaseBuffer();
//		m_tabDlgInspection.InsertItem(m_nTabNum, &item);
//		m_nTabNum++;
//	}
//
//	// 2009-04-13 jsy
//	// Lang.ini file path change
//	switch (pGlobalDoc->m_nSelectedLanguage)
//	{
//	case KOREAN:
//		strPath.Format(_T("%sLanguage\\InSmart_Lang-kor.ini"), pGlobalDoc->m_strAoiSetDir);
//		break;
//	case ENGLISH:
//		strPath.Format(_T("%sLanguage\\InSmart_Lang-eng.ini"), pGlobalDoc->m_strAoiSetDir);
//		break;
//	case JAPAN:
//		strPath.Format(_T("%sLanguage\\InSmart_Lang-jpn.ini"), pGlobalDoc->m_strAoiSetDir);
//		break;
//	case CHINESE:
//		strPath.Format(_T("%sLanguage\\InSmart_Lang-chi.ini"), pGlobalDoc->m_strAoiSetDir);
//		break;
//	case VIETNAMESE:
//		strPath.Format(_T("%sLanguage\\InSmart_Lang-viet.ini"), pGlobalDoc->m_strAoiSetDir);
//		break;
//	case CHINESE_SIMPLE:
//		strPath.Format(_T("%sLanguage\\InSmart_Lang-chi_simple.ini"), pGlobalDoc->m_strAoiSetDir);
//		break;
//	}
//
//	if (0 < GetPrivateProfileString(_T("COMMON_MESSAGE"), _T("FONT_SIZE"), NULL, strString, sizeof(strString), strPath))
//		m_fDataFontSize = _ttof(strString);
//	else
//		m_fDataFontSize = 10;
//
//
//#if WIN_OS == WIN_10
//	if (pGlobalDoc->m_nSelectedLanguage == CHINESE || pGlobalDoc->m_nSelectedLanguage == CHINESE_SIMPLE)
//	{
//		m_fDataFontSize = 12;
//	}
//#endif
//
//	if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
//	{
//		CString strPath;
//
//		CFileFind finder;
//
//		CString strSpecNew;
//		strSpecNew.Format(_T("%s%s\\%s_speclock.bin"),
//			pGlobalDoc->m_strSpecDir,
//			pGlobalDoc->m_strModel,
//			pGlobalDoc->m_strLayer);
//
//		if (finder.FindFile(strSpecNew))
//		{
//			LoadLockedSpecData(strSpecNew);
//		}
//		else if (finder.FindFile(SPEC_LOCK_1_PATH))
//		{
//			LoadLockedSpecData(SPEC_LOCK_1_PATH);
//		}
//		else if (finder.FindFile(SPEC_LOCK_2_PATH))
//		{
//			LoadLockedSpecData(SPEC_LOCK_2_PATH);
//		}
//		else
//		{
//			//call lock alarm
//		}
//
//		GetDlgItem(IDC_BUTTON_SET_SPEC_LOCK)->ShowWindow(SW_SHOW);
//	}
//	else
//		GetDlgItem(IDC_BUTTON_SET_SPEC_LOCK)->ShowWindow(SW_HIDE);
//
//	if (AoiParam()->m_bSetLightLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
//		GetDlgItem(IDC_BUTTON_SET_LIGHT_LOCK)->ShowWindow(SW_SHOW);
//	else
//		GetDlgItem(IDC_BUTTON_SET_LIGHT_LOCK)->ShowWindow(SW_HIDE);
//
//	if (AoiParam()->m_bSetDefectLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
//		GetDlgItem(IDC_BUTTON_SET_SPEC_DEFECT)->ShowWindow(SW_SHOW);
//	else
//		GetDlgItem(IDC_BUTTON_SET_SPEC_DEFECT)->ShowWindow(SW_HIDE);
//
//
//
//	if (!pGlobalDoc->m_bInspCCL[AoiParam()->m_nCurrentInspectionMode])	//jun 20120903 for LG_CCL-Inspector
//		LoadOriginDataTab(0);
//	else
//		LoadOriginDataTab(3);
//
//	LoadOriginDataTab(0);
//	LoadOriginDataTab(1);
//	LoadOriginDataTab(2);
//	LoadOriginDataTab(3);
//	LoadOriginDataTab(4);
//	LoadOriginDataTab(5);
//	LoadOriginDataTab(6);
//	LoadOriginDataTab(7);
//
//	//151111 lgh 
//	int nIdx = 0;
//
//	// Init Spec Display...	
//	m_tabDlgInspection.SetCurSel(0);
//	InitSpread();
//
//	INSPECTION_MODE nInspMode = AoiParam()->m_nCurrentInspectionMode;
//
//	if (pGlobalDoc->m_bInspCCL[nInspMode])	//jun 20120903 for LG_CCL-Inspector
//	{
//		InitSpreadTab3();
//		LoadSpreadDataTab3();
//		m_tabDlgInspection.SetCurSel(3);
//		DisplaySpread(3);
//	}
//	else
//	{
//		InitSpreadTab0();
//		LoadSpreadDataTab0();
//	}
//	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
//	m_Spread.SetReDraw(TRUE);
//	SetSpecAccess(pGlobalView->m_nUserID); // syd-20100115
//	if (!pGlobalDoc->m_bInspCCL[nInspMode])		//jun 20120903 for LG_CCL-Inspector
//		m_nTabNum = 0;
//	else
//		m_nTabNum = 3;
//
//	m_PADLgFlag = FALSE;
//	m_PADSmFlag = FALSE;
//	m_PADARFlag = FALSE;
//	m_PADCO2Flag = FALSE;
//	m_PADTipFlag = FALSE;
//	m_PADSpaceFlag = FALSE;
//
//	if (pGlobalDoc->m_DefectListItem[pGlobalDoc->m_cboSelDefID].GetCount()>0)
//	{
//
//		if (pGlobalView->m_pDlgInspection != NULL)
//		{
//			if (IsWindow(pGlobalView->m_pDlgInspection->GetSafeHwnd()))
//				(pGlobalView->m_pDlgInspection->GetDlgItem(IDC_SORT_ALL))->EnableWindow(TRUE);
//		}
//
//		pGlobalView->EnableDefectCounter(1);
//	}
//	else
//	{
//
//		if (pGlobalView->m_pDlgInspection != NULL)
//		{
//			if (IsWindow(pGlobalView->m_pDlgInspection->GetSafeHwnd()))
//			{
//				pGlobalView->m_pDlgInspection->GetButtonItem(IDC_SORT_ALL)->EnableWindow(0);
//				pGlobalView->m_pDlgInspection->GetButtonItem(IDC_SORT_ALL)->SetOffTextColor(RGB(180, 180, 180));
//			}
//		}
//		pGlobalView->EnableDefectCounter(0);
//
//	}
//
//	int nCurGridIndex = pGlobalDoc->m_nGridIndex - 1;// 130701 TEST DISALBE
//
//	if (pGlobalDoc->m_nSaveThumbImg != -1)
//	{
//		pGlobalView->m_GLopen = 2;
//		if (pGlobalDoc->m_nGridIndex <= 0)
//		{
//			pGlobalView->SetThumbnailImgPack(0);
//		}
//		else
//		{
//			if (nCurGridIndex <= 0) //130520 lgh add For thumbnailpos Bugfix
//			{
//				preindex = pGlobalDoc->m_nGridIndex - 1;
//				pGlobalView->SetThumbnailImgPack(0);//1301516 lgh add if Preindex > Gridindex, Set Thumbnail St Index Set 0
//			}
//			else
//			{
//				pGlobalView->SetThumbnailImgPack(nCurGridIndex); //130701
//			}
//		}
//		AoiParam()->m_bEasySpecDoNotResetRequire = TRUE; //130702 LGH ADD FOR EASYSPEC FIRST VIEW
//	}
//
//
//	//2023 02 14 LGH ADD
//	if (AoiParam()->m_bShowCadThumbList)
//	{
//		if (pGlobalView->m_DlgThumbCadList.GetSafeHwnd())
//		{
//			pGlobalView->m_DlgThumbCadList.ShowWindow(SW_SHOW);
//		}
//	}
//
//
//	GetDlgItem(IDC_BUTTON_MULTILINE)->ShowWindow(g_bShowMultilineMenu);

}

void CDlgSpec::AtDlgHide()
{
//
//	if (g_bDestroy)
//		return;
//
//
//#if CUSTOMER_COMPANY == SHINKO_DENKKI
//	pGlobalView->ViewDlgShinkoRecipe(0);
//#else
//	if (g_bNewRecipeUI)
//		pGlobalView->ViewDlgShinkoRecipe(0);
//#endif
//	CString strTitleMsg, strMsg;
//	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
//
//	m_Spread.SetActiveCell(0, 0);
//	m_Spread.SetRetainSelBlock(FALSE);
//	m_Spread.ClearSelection();
//
//	//170317 lgh
//	if (m_dlgViaSpec.GetSafeHwnd() && m_dlgViaSpec.IsWindowVisible())
//		m_dlgViaSpec.ShowWindow(SW_HIDE);
//
//	AoiParam()->m_bEasySpecDoNotResetRequire = FALSE;
//
//	if (m_DlgSroSpec.GetSafeHwnd())
//	{
//		CSROInspectionData* pSROData = CSROInspectionData::GetInstance(g_nCurrentLayerSide);
//
//		for (int i = 0; i < pSROData->m_nNumOfType; i++)
//		{
//			if (fabs(SpecData.SRSpec[i].dAreaPercent - m_DlgSroSpec.m_SRSpec[i].dAreaPercent) > 0.01)
//			{
//				m_bSpecDataChanged = 1;
//				break;
//			}
//
//			if (fabs(SpecData.SRSpec[i].dCircleShiftSpecUm - m_DlgSroSpec.m_SRSpec[i].dCircleShiftSpecUm) > 0.01)
//			{
//				m_bSpecDataChanged = 1;
//				break;
//			}
//
//			if (fabs(SpecData.SRSpec[i].dDiameterSpecLower - m_DlgSroSpec.m_SRSpec[i].dDiameterSpecLower) > 0.01)
//			{
//				m_bSpecDataChanged = 1;
//				break;
//			}
//
//			if (fabs(SpecData.SRSpec[i].dDiameterSpecUpper - m_DlgSroSpec.m_SRSpec[i].dDiameterSpecUpper) > 0.01)
//			{
//				m_bSpecDataChanged = 1;
//				break;
//			}
//
//			if (fabs(SpecData.SRSpec[i].nSROGray - m_DlgSroSpec.m_SRSpec[i].nSROGray) > 0)
//			{
//				m_bSpecDataChanged = 1;
//				break;
//			}
//
//			if (fabs(SpecData.SRSpec[i].nPrecision - m_DlgSroSpec.m_SRSpec[i].nPrecision) > 0)
//			{
//				m_bSpecDataChanged = 1;
//				break;
//			}
//
//		}
//	}
//
//	if (m_DlgSroSpec.GetSafeHwnd())
//	{
//		m_DlgSroSpec.ShowWindow(SW_HIDE);
//	}
//
//	if (m_bMultilineSaved == 0)
//	{
//
//
//		if (m_bSpecDataChanged || m_dlgViaSpec.m_bSpecDataChanged || m_dlgViaSpec.m_bClientSpecDataUpdate)
//		{
//			//
//
//			pGlobalView->m_strMsgBox = pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "MSG_BOX", "AtDlgHide_P0_M1");
//			if (MessageBox(pGlobalView->m_strMsgBox, NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
//			{
//				m_dlgViaSpec.m_bClientSpecDataUpdate = 1;
//				pGlobalView->m_pDlgSpecSub->SaveSpec();
//				m_dlgViaSpec.m_bClientSpecDataUpdate = 0;
//				m_bClientSpecDataUpdate = TRUE;
//			}
//			else
//			{
//				//170608 lgh fix
//				if (m_dlgViaSpec.GetSafeHwnd())
//				{
//					m_dlgViaSpec.InitVariablesWithLoadSpecFromFile();
//					m_dlgViaSpec.LoadOriginDataTab(0);
//					m_dlgViaSpec.LoadOriginDataTab(1);
//					m_dlgViaSpec.LoadOriginDataTab(2);
//					m_dlgViaSpec.RecoverOriginData();
//				}
//				InitVariablesWithLoadSpecFromFile();
//
//				//20100323 hjc
//				LoadOriginDataTab(0);
//				LoadOriginDataTab(1);
//				LoadOriginDataTab(2);
//				LoadOriginDataTab(3);
//				LoadOriginDataTab(4);
//				LoadOriginDataTab(5);
//				LoadOriginDataTab(6);
//				LoadOriginDataTab(7);
//				//--------------
//				// Remark by syd
//				// Function Order: RecoverOriginData() - LoadOriginDataTab(0) - ......
//				RecoverOriginData();
//			}
//			InitSpreadInfoVariables();
//			if (m_dlgViaSpec.GetSafeHwnd())
//				m_dlgViaSpec.InitSpreadInfoVariables();
//		}
//	}
//
//	if (m_bMultilineSaved)
//	{		// Send Spec to Client
//		strTitleMsg.Format(_T("%s"), pGlobalView->GetLanguageString("SYSTEM", "NOTIFY"));
//
//		strMsg = _T("Saving..");
//
//		if (pGlobalDoc->m_nSelectedLanguage == CHINESE_SIMPLE)
//			strMsg = _T("Ô·Ó§‹¡Ì€’ˆ«...ı™‘ıÏÈ˘ª°£[Spec]");
//
//		pGlobalView->DispMessage(strTitleMsg, _T("Saving.."), RGB_LTGREEN);
//
//		m_bMultilineSaved = 0;
//		if (m_dlgViaSpec.GetSafeHwnd())
//			m_dlgViaSpec.m_bClientSpecDataUpdate = 1;
//		pGlobalView->m_pDlgSpecSub->SaveSpec();
//		if (m_dlgViaSpec.GetSafeHwnd())
//			m_dlgViaSpec.m_bClientSpecDataUpdate = 0;
//		m_bClientSpecDataUpdate = TRUE;
//		InitSpreadInfoVariables();
//		if (m_dlgViaSpec.GetSafeHwnd())
//			m_dlgViaSpec.InitSpreadInfoVariables();
//
//
//		if (pGlobalView->PrepareIPU() == 0)
//			pGlobalView->m_bAutoSpecDownload = 1;
//
//
//		pGlobalView->ClearDispMessage();
//
//	}
//	else if (m_bClientSpecDataUpdate && pGlobalView->CheckAllClientsReady())
//	{
//		// Send Spec to Client
//		strTitleMsg.Format(_T("%s"), pGlobalView->GetLanguageString("SYSTEM", "NOTIFY"));
//		strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("NETWORK", "SEND_SPEC_DATA"));
//		pGlobalView->DispMessage(strTitleMsg, strMsg, RGB_LTGREEN);
//
//		if (pGlobalView->SendSpecDataToAllClient() != SUCCESS || pGlobalView->SendSystemParamToAllClient() != SUCCESS)
//		{
//#if CUSTOMER_COMPANY == UMTC || CUSTOMER_COMPANY == ZDT || CUSTOMER_COMPANY == SAMSUNG_VIETNAM  //NTH Add for GEM
//			if (pGlobalDoc->m_bUseGemComm)
//			{
//				if (!pGlobalDoc->m_bCheckAlarm)
//				{
//					pGlobalDoc->m_bCheckAlarm = TRUE;
//					pMainFrame->SetEESAlarm(60, EES_ACTIVATE_ALARM);
//				}
//			}
//			else
//				pMainFrame->SetEESAlarm(60, EES_ACTIVATE_ALARM);
//#else
//			pMainFrame->SetEESAlarm(60, EES_ACTIVATE_ALARM);
//#endif
//			strTitleMsg.Format(_T("%s"), pGlobalView->GetLanguageString("SYSTEM", "WARNING"));
//			strMsg.Format(_T("[MSG1] %s"), pGlobalView->GetLanguageString("NETWORK", "DOWNLOAD_ERROR_SPEC_DATA"));
//			pGlobalView->ResultDisplayStaticEX(strMsg, RGB_BLACK, RGB_YELLOW);
//			CString strErrorMsg = pGlobalView->GetLanguageString("ERROR_GUIDE", "SPEC_DOWNLOAD_ERROR");
//
//#if CUSTOMER_COMPANY == SHINKO_DENKKI
//			pIO->BuzzerOnOff(TRUE);
//			pGlobalView->TowerLampControl(TOWER_LAMP_RED, 1);
//#endif
//			pMainFrame->DispMessageModal(strTitleMsg, strMsg, RGB_YELLOW, 300000, TRUE, strErrorMsg);
//#if CUSTOMER_COMPANY == SHINKO_DENKKI
//			pIO->BuzzerOnOff(0);
//			pGlobalView->TowerLampControl(TOWER_LAMP_GREEN, 1);
//#endif
//
//#if CUSTOMER_COMPANY == UMTC || CUSTOMER_COMPANY == ZDT || CUSTOMER_COMPANY == SAMSUNG_VIETNAM  //NTH Add for GEM
//			if (pGlobalDoc->m_bUseGemComm)
//			{
//				if (pGlobalDoc->m_bCheckAlarm)
//				{
//					pGlobalDoc->m_bCheckAlarm = FALSE;
//					pMainFrame->SetEESAlarm(60, EES_DEACTIVATE_ALARM);
//				}
//			}
//			else
//				pMainFrame->SetEESAlarm(60, EES_DEACTIVATE_ALARM);
//#else
//			pMainFrame->SetEESAlarm(60, EES_DEACTIVATE_ALARM);
//#endif
//		}
//		pGlobalView->ClearDispMessage();
//	}
//
//
//
//	//	GetDlgItem(IDC_BUTTON_SAVEMASK)->SetFocus();
//	m_bClientSpecDataUpdate = FALSE;
}

void CDlgSpec::InitSpread()
{
	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	//Row Caption
	//m_Spread.Reset();

	m_Spread.SetScrollBarStyle(SS_SCROLLBARSTYLE_CLASSIC);
	m_Spread.SetBool(SSB_HORZSCROLLBAR, 0);
	m_Spread.SetBool(SSB_VERTSCROLLBAR, 0);
	m_Spread.SetAppearanceStyle(0);// FOR CLASSIC

	m_Spread.Clear(-1, -1);
	m_Spread.SetCol(0);
	m_Spread.SetRow(-1);
	m_Spread.SetBackColor(RGB(226, 233, 251));
	//m_Spread.SetAppearanceStyle(1);
	m_Spread.SetShadowColor(RGB(226, 233, 251), SPREAD_COLOR_NONE, COLOR_3DSHADOW, COLOR_3DHILIGHT);
	//m_Spread.shadow
	//m_Spread.SetGridColor(0xDCDCDC);
	m_Spread.SetActiveCellHighlightStyle(0);
	m_Spread.SetBool(SSB_EDITMODEREPLACE, TRUE);

	HFONT hfont = CreateFont(10 + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, _T(""));
	m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
	//if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
	//{
	//	HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
	//	m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
	//}
	//else
	//{
	//	HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
	//	m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
	//}
}

void CDlgSpec::RefreshDataColor(int nTabNum)
{
	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	for (int iRow = 1; iRow <= m_Spread.GetMaxRows(); iRow++)
	{
		m_Spread.SetColor(1, iRow, RGB(255, 255, 255), RGB(60, 145, 103));
		m_Spread.SetLock(1, iRow, FALSE);
	}
	DisplaySpread(nTabNum);
}

void CDlgSpec::DisplaySpread(int nTabNum)
{
	//m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	//m_Spread.SetReDraw(FALSE);
	//switch (nTabNum)
	//{
	//case 0:
	//	InitSpreadTab0();
	//	LoadSpreadDataTab0();
	//	break;
	//case 1:
	//	InitSpreadTab1();
	//	LoadSpreadDataTab1();
	//	break;
	//case 2:
	//	InitSpreadTab2();
	//	LoadSpreadDataTab2();
	//	break;
	//case 3:
	//	InitSpreadTab3();
	//	LoadSpreadDataTab3();
	//	break;
	//	//20090213
	//case 4:
	//	InitSpreadTab4();
	//	LoadSpreadDataTab4();
	//	break;
	//case 5:
	//	InitSpreadTab5();
	//	LoadSpreadDataTab5();
	//	break;
	//case 6:
	//	InitSpreadTab6();
	//	LoadSpreadDataTab6();
	//	break;
	//case 7:		//20100322 hjc add
	//	InitSpreadTab7();
	//	LoadSpreadDataTab7();
	//	break;
	//	//20092013 end
	//default:
	//	;
	//}
	//SetSpecAccess(pGlobalView->m_nUserID); // syd-20100115
	//m_Spread.SetReDraw(TRUE);
}


void CDlgSpec::ChangeSpecSpreadCaption(int nTab)
{
//	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
//	//syd-091008
//	CString strTemp, strVal;
//	int idx;
//
//	m_Spread.SetCol(0);
//	if (AoiParam()->m_bSetSpecLocking)
//	{
//		switch (nTab)
//		{
//		case 0:
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_1") + GetRangeString(nTab, 1, _T("")));
//			m_Spread.SetRow(2);
//			if (g_bSuccessMeasureEtch)
//			{
//				strTemp.Format(_T("%s[e:%.1fum]"),
//					pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_2") + GetRangeString(nTab, 2, _T("")), g_dCurrentEtchValue);
//
//				m_Spread.SetText(strTemp);
//			}
//			else
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_2") + GetRangeString(nTab, 2, _T("")));
//
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_3") + GetRangeString(nTab, 3, _T("")));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_4") + GetRangeString(nTab, 4, _T("")));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_5") + GetRangeString(nTab, 5, _T("")));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_6") + GetRangeString(nTab, 6, _T("")));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_7") + GetRangeString(nTab, 7, _T("")));
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_8") + GetRangeString(nTab, 8, _T("")));
//			m_Spread.SetRow(9);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_9") + GetRangeString(nTab, 9, _T("")));
//			m_Spread.SetRow(10);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_10") + GetRangeString(nTab, 10, _T("")));
//			m_Spread.SetRow(11);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_11") + GetRangeString(nTab, 11, _T("")));
//			m_Spread.SetRow(12);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_12") + GetRangeString(nTab, 12, _T("")));
//			m_Spread.SetRow(13);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_13") + GetRangeString(nTab, 13, _T("")));
//			m_Spread.SetRow(14);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_14") + GetRangeString(nTab, 14, _T("")));
//
//			m_Spread.SetRow(15);
//			if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx)
//			{
//				strTemp = "";
//				for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
//				{
//					if (idx < 2)
//					{
//						if (idx)
//							strTemp += "/";
//						else
//							strTemp += "(MT) ";
//						strVal.Format(_T("(%.1f)"), m_fLineWidthGroup[idx]);
//						strTemp += strVal;
//					}
//					else if (idx == 2)
//					{
//						strTemp += "/..";
//					}
//				}
//				m_Spread.SetText(strTemp);
//			}
//			else
//			{
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_15") + GetRangeString(nTab, 15, _T("")));
//
//				m_Spread.SetRow(16);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_16") + GetRangeString(nTab, 16, _T("")));
//			}
//
//			break;
//		case 1:
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_1") + GetRangeString(nTab, 1, _T("")));
//			m_Spread.SetRow(2);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_2") + GetRangeString(nTab, 2, _T("")));
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_3") + GetRangeString(nTab, 3, _T("")));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_4") + GetRangeString(nTab, 4, _T("")));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_5") + GetRangeString(nTab, 5, _T("")));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_6") + GetRangeString(nTab, 6, _T("")));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_7") + GetRangeString(nTab, 7, _T("")));
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_8") + GetRangeString(nTab, 8, _T("")));
//			m_Spread.SetRow(9);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_9") + GetRangeString(nTab, 9, _T("")));
//			m_Spread.SetRow(10);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_10") + GetRangeString(nTab, 10, _T("")));
//			m_Spread.SetRow(11);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_11") + GetRangeString(nTab, 11, _T("")));
//			m_Spread.SetRow(12);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_12") + GetRangeString(nTab, 12, _T("")));
//			m_Spread.SetRow(13);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_13") + GetRangeString(nTab, 13, _T("")));
//			m_Spread.SetRow(14);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_14") + GetRangeString(nTab, 14, _T("")));
//
//			if (AoiParam()->m_bUseMultilineSpecEx && m_nLineWidthGroupNum > 0)
//			{
//				if (1)
//				{
//					CString strVal;
//					strTemp = "";
//					for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
//					{
//						if (idx < 4)
//						{
//							if (idx)
//								strTemp += _T("/");
//							strVal.Format(_T("[%.1f,%.1f]"), m_fFineNarrowTraceViolation[idx], m_fWideTraceViolation[idx]);
//							strTemp += strVal;
//						}
//						else if (idx == 4)
//						{
//							strTemp += _T("/..");
//						}
//
//					}
//					m_Spread.SetCol(1);
//					m_Spread.SetRow(15);
//					m_Spread.SetTypeButtonText(strTemp);
//
//					strTemp = _T("");
//					for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
//					{
//						if (idx < 2)
//						{
//							if (idx)
//								strTemp += _T("/");
//							else
//								strTemp += _T("(MT) ");
//							strVal.Format(_T("%.1f"), m_fFineLineWidthGroup[idx]);
//							strTemp += strVal;
//						}
//						else if (idx == 2)
//						{
//							strTemp += _T("/..");
//						}
//
//					}
//					m_Spread.SetCol(0);
//					m_Spread.SetRow(15);
//					m_Spread.SetText(strTemp);
//				}
//			}
//			else
//			{
//				m_Spread.SetRow(15);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_15") + GetRangeString(nTab, 15, _T("")));
//
//				m_Spread.SetRow(16);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_16") + GetRangeString(nTab, 16, _T("")));
//			}
//
//			break;
//		case 2:
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_1") + GetRangeString(nTab, 1, _T("")));
//			m_Spread.SetRow(2);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_2") + GetRangeString(nTab, 2, _T("")));
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_3") + GetRangeString(nTab, 3, _T("")));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_4") + GetRangeString(nTab, 4, _T("")));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_5") + GetRangeString(nTab, 5, _T("")));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_6") + GetRangeString(nTab, 6, _T("")));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_7") + GetRangeString(nTab, 7, _T("")));
//			//20090412 hjc
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_8") + GetRangeString(nTab, 8, _T("")));
//			m_Spread.SetRow(9);	//121226 hjc add
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_9") + GetRangeString(nTab, 9, _T("")));
//			//------------
//			break;
//		case 3:		//20100322 hjc add
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_1") + GetRangeString(nTab, 1, _T("")));
//			m_Spread.SetRow(2);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_2") + GetRangeString(nTab, 2, _T("")));
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_3") + GetRangeString(nTab, 3, _T("")));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_4") + GetRangeString(nTab, 4, _T("")));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_5") + GetRangeString(nTab, 5, _T("")));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_6") + GetRangeString(nTab, 6, _T("")));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_7") + GetRangeString(nTab, 7, _T("")));
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_8") + GetRangeString(nTab, 8, _T("")));
//			//jun 20120903 for LG_CCL-Inspector
//			m_Spread.SetRow(9);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_9") + GetRangeString(nTab, 9, _T("")));
//			m_Spread.SetRow(10);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_10") + GetRangeString(nTab, 10, _T("")));
//			m_Spread.SetRow(11);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_11") + GetRangeString(nTab, 11, _T("")));
//			m_Spread.SetRow(12);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_12") + GetRangeString(nTab, 12, _T("")));
//			//------------
//
//			//2022 01 10 §”»£ §±§∑§∑
//			if (SpecData.bEnableCharInspection)
//			{
//				m_Spread.SetRow(13);
//				m_Spread.SetText(_T("πÆ¿⁄ø≠±‚¡ÿπ‡±‚") + GetRangeString(nTab, 13, _T("")));
//
//				m_Spread.SetRow(14);
//				m_Spread.SetText(_T("πÆ¿⁄øµø™ªÛ«—ƒ°") + GetRangeString(nTab, 14, _T("")));
//
//				m_Spread.SetRow(15);
//				m_Spread.SetText(_T("πÆ¿⁄øµø™«œ«—ƒ°") + GetRangeString(nTab, 15, _T("")));
//			}
//
//
//			break;
//		case 4:
//			if (pGlobalDoc->m_bUseTeachingLineWidth)
//			{
//				if (pGlobalDoc->m_bUseOnlyViaInsp[AoiParam()->m_nCurrentInspectionMode])	//151210 hjc add
//				{
//					strTemp.Format(_T("[T:%d][Max:%d]  %s"), pGlobalDoc->m_nViaHoleMeanDiff, 255 - pGlobalDoc->m_nViaHoleMeanDiff, pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_1"));
//					m_Spread.SetRow(1);
//					m_Spread.SetText(strTemp + GetRangeString(nTab, 1, _T("")));
//					m_Spread.SetRow(2);
//					strTemp.Format(_T("[T:%d][Max:%d]  %s"), pGlobalDoc->m_nViaHoleMeanDiff, pGlobalDoc->m_nViaHoleMeanDiff, pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_2"));
//					m_Spread.SetText(strTemp + GetRangeString(nTab, 2, _T("")));
//				}
//				else if (pGlobalDoc->m_nVDMeanDiff > 0)
//				{
//					strTemp.Format(_T("[T:%d][Max:%d]  %s"), pGlobalDoc->m_nVDMeanDiff, 255 - pGlobalDoc->m_nVDMeanDiff, pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_1"));
//					m_Spread.SetRow(1);
//					m_Spread.SetText(strTemp + GetRangeString(nTab, 1, _T("")));
//					m_Spread.SetRow(2);
//					strTemp.Format(_T("[T:%d][Max:%d]  %s"), pGlobalDoc->m_nVDMeanDiff, pGlobalDoc->m_nVDMeanDiff, pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_2"));
//					m_Spread.SetText(strTemp + GetRangeString(nTab, 2, _T("")));
//				}
//				else
//				{
//					strTemp.Format(_T("[(X)VD Data]  %s"), pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_1"));
//					m_Spread.SetRow(1);
//					m_Spread.SetText(strTemp + GetRangeString(nTab, 1, _T("")));
//					m_Spread.SetRow(2);
//					strTemp.Format(_T("[(X)VD Data]  %s"), pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_2"));
//					m_Spread.SetText(strTemp + GetRangeString(nTab, 2, _T("")));
//				}
//			}
//			else
//			{
//				m_Spread.SetRow(1);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_1") + GetRangeString(nTab, 1, _T("")));
//				m_Spread.SetRow(2);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_2") + GetRangeString(nTab, 2, _T("")));
//			}
//
//
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_3") + GetRangeString(nTab, 3, _T("")));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_4") + GetRangeString(nTab, 4, _T("")));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_5") + GetRangeString(nTab, 5, _T("")));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_6") + GetRangeString(nTab, 6, _T("")));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_7") + GetRangeString(nTab, 7, _T("")));
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_8") + GetRangeString(nTab, 8, _T("")));
//			m_Spread.SetRow(9);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_9") + GetRangeString(nTab, 9, _T("")));
//			m_Spread.SetRow(10);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_10") + GetRangeString(nTab, 10, _T("")));
//			m_Spread.SetRow(11);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_11") + GetRangeString(nTab, 11, _T("")));
//			m_Spread.SetRow(12);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_12") + GetRangeString(nTab, 12, _T("")));
//			m_Spread.SetRow(13);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_13") + GetRangeString(nTab, 13, _T("")));
//			m_Spread.SetRow(14);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_14") + GetRangeString(nTab, 14, _T("")));
//			m_Spread.SetRow(15);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_15") + GetRangeString(nTab, 15, _T("")));
//			m_Spread.SetRow(16);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_16") + GetRangeString(nTab, 16, _T("")));
//			m_Spread.SetRow(17);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_17") + GetRangeString(nTab, 17, _T("")));
//			m_Spread.SetRow(18);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_18") + GetRangeString(nTab, 18, _T("")));
//			m_Spread.SetRow(19);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_19") + GetRangeString(nTab, 19, _T("")));
//			m_Spread.SetRow(20);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_20") + GetRangeString(nTab, 20, _T("")));
//			m_Spread.SetRow(21);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_21") + GetRangeString(nTab, 21, _T("")));
//			m_Spread.SetRow(22);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_22") + GetRangeString(nTab, 22, _T("")));		//150606 hjc add
//			break;
//		case 5:
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_1") + GetRangeString(nTab, 1, _T("")));
//			m_Spread.SetRow(2);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_2") + GetRangeString(nTab, 2, _T("")));
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_3") + GetRangeString(nTab, 3, _T("")));
//
//			if (pGlobalDoc->m_bUseTeachingLineWidth)
//			{
//				if (pGlobalDoc->m_nHoleMeanDiff > 0)
//				{
//					strTemp.Format(_T("[T:%d]   %s"), pGlobalDoc->m_nHoleMeanDiff, pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_4"));
//					m_Spread.SetRow(4);
//					m_Spread.SetText(strTemp + GetRangeString(nTab, 4, _T("")));
//
//					strTemp.Format(_T("[T:%d]   %s"), pGlobalDoc->m_nHoleMeanDiff, pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_5"));
//					m_Spread.SetRow(5);
//					m_Spread.SetText(strTemp + GetRangeString(nTab, 5, _T("")));
//				}
//				else
//				{
//					//160125 lgh 
//					strTemp.Format(_T("[(X) HoleData]   %s"), pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_4"));
//					m_Spread.SetRow(4);
//					m_Spread.SetText(strTemp + GetRangeString(nTab, 4, _T("")));
//
//					strTemp.Format(_T("[(X) HoleData]   %s"), pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_5"));
//					m_Spread.SetRow(5);
//					m_Spread.SetText(strTemp + GetRangeString(nTab, 5, _T("")));
//				}
//			}
//			else
//			{
//				m_Spread.SetRow(4);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_4") + GetRangeString(nTab, 4, _T("")));
//				m_Spread.SetRow(5);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_5") + GetRangeString(nTab, 5, _T("")));
//
//			}
//
//
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_6") + GetRangeString(nTab, 6, _T("")));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_7") + GetRangeString(nTab, 7, _T("")));
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_8") + GetRangeString(nTab, 8, _T("")));
//			m_Spread.SetRow(9);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_9") + GetRangeString(nTab, 9, _T("")));
//			m_Spread.SetRow(10);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_10") + GetRangeString(nTab, 10, _T("")));
//			m_Spread.SetRow(11);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_11") + GetRangeString(nTab, 11, _T("")));
//			m_Spread.SetRow(12);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_12") + GetRangeString(nTab, 12, _T("")));
//			m_Spread.SetRow(13);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_13") + GetRangeString(nTab, 13, _T("")));
//			m_Spread.SetRow(14);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_14") + GetRangeString(nTab, 14, _T("")));
//			m_Spread.SetRow(15);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_15") + GetRangeString(nTab, 15, _T("")));
//			m_Spread.SetRow(16);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_16") + GetRangeString(nTab, 16, _T("")));
//			m_Spread.SetRow(17);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_17") + GetRangeString(nTab, 17, _T("")));
//			m_Spread.SetRow(18);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_18") + GetRangeString(nTab, 18, _T("")));
//			break;
//		case 6:
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_1") + GetRangeString(nTab, 1, _T("")));
//			m_Spread.SetRow(2);	//111214 hjc mod
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_2") + GetRangeString(nTab, 2, _T("")));
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_3") + GetRangeString(nTab, 3, _T("")));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_4") + GetRangeString(nTab, 4, _T("")));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_5") + GetRangeString(nTab, 5, _T("")));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_6") + GetRangeString(nTab, 6, _T("")));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_7") + GetRangeString(nTab, 7, _T("")));
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_8") + GetRangeString(nTab, 8, _T("")));
//			m_Spread.SetRow(9);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_9") + GetRangeString(nTab, 9, _T("")));
//			m_Spread.SetRow(10);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_10") + GetRangeString(nTab, 10, _T("")));
//			m_Spread.SetRow(11);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_11") + GetRangeString(nTab, 11, _T("")));
//			m_Spread.SetRow(12);	//120105 hjc add
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_12") + GetRangeString(nTab, 12, _T("")));
//			m_Spread.SetRow(13);	//120109 hjc add
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_13") + GetRangeString(nTab, 13, _T("")));
//			m_Spread.SetRow(14);	//120105 hjc add
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_14") + GetRangeString(nTab, 14, _T("")));
//			m_Spread.SetRow(15);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_15") + GetRangeString(nTab, 15, _T("")));
//			//----------------
//			break;
//		case 7:
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_3") + GetRangeString(nTab, 1, _T("")));
//			m_Spread.SetRow(2);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_4") + GetRangeString(nTab, 2, _T("")));
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_5") + GetRangeString(nTab, 3, _T("")));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_6") + GetRangeString(nTab, 4, _T("")));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_7") + GetRangeString(nTab, 5, _T("")));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_8") + GetRangeString(nTab, 6, _T("")));
//			m_Spread.SetRow(7);	//20100210 hjc add
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_9") + GetRangeString(nTab, 7, _T("")));
//			if (AoiParam()->m_bUseAutoPinPosAdjust || g_bUsePinPosEstimate)
//			{
//				m_Spread.SetRow(8);	//20100210 hjc add
//				m_Spread.SetText(LoadLanguageString(ID_PANEL_SIZE_X, pGlobalDoc->m_nSelectedLanguage));
//
//				m_Spread.SetRow(9);	//20100210 hjc add
//				m_Spread.SetText(LoadLanguageString(ID_PANEL_SIZE_Y, pGlobalDoc->m_nSelectedLanguage));
//#ifdef IRIS_AXIS
//				m_Spread.SetRow(10);	//20100210 hjc add
//				if (pGlobalDoc->m_nSelectedLanguage == KOREA)
//					m_Spread.SetText(_T("¡∂∏Æ∞≥ ¿ßƒ°"));
//				else if (pGlobalDoc->m_nSelectedLanguage == JAPANESE)
//					m_Spread.SetText(_T("´´´·´ÈŒÌ™ÍÍ»ˆ«"));
//				else
//					m_Spread.SetText(_T("IrisPos"));
//#endif
//			}
//			else
//			{
//#ifdef IRIS_AXIS
//				m_Spread.SetRow(8);	//20100210 hjc add
//				if (pGlobalDoc->m_nSelectedLanguage == KOREA)
//					m_Spread.SetText(_T("¡∂∏Æ∞≥ ¿ßƒ°"));
//				else if (pGlobalDoc->m_nSelectedLanguage == JAPANESE)
//					m_Spread.SetText(_T("´´´·´ÈŒÌ™ÍÍ»ˆ«"));
//				else
//					m_Spread.SetText(_T("IrisPos"));
//#endif
//			}
//
//
//			break;
//		}
//	}
//	else
//	{
//		switch (nTab)
//		{
//		case 0:
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_1"));
//			m_Spread.SetRow(2);
//			if (g_bSuccessMeasureEtch)
//			{
//				strTemp.Format(_T("%s[e:%.1fum, %.1fum]"),
//					pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_2"), g_dCurrentEtchValue, SpecData.fNominalLineWidth - g_dCurrentEtchValue);
//
//				m_Spread.SetText(strTemp);
//			}
//			else
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_2"));
//
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_3"));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_4"));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_5"));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_6"));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_7"));
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_8"));
//			m_Spread.SetRow(9);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_9"));
//			m_Spread.SetRow(10);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_10"));
//			m_Spread.SetRow(11);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_11"));
//			m_Spread.SetRow(12);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_12"));
//			m_Spread.SetRow(13);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_13"));
//			m_Spread.SetRow(14);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_14"));
//
//			m_Spread.SetRow(15);
//
//			if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx)
//			{
//				strTemp = "";
//				for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
//				{
//					if (idx < 2)
//					{
//						if (idx)
//							strTemp += "/";
//						else
//							strTemp += "(MT) ";
//						strVal.Format(_T("(%.1f~%.1f)"), m_fLineWidthGroupLower[idx], m_fLineWidthGroup[idx]);
//						strTemp += strVal;
//					}
//					else if (idx == 2)
//					{
//						strTemp += "/..";
//					}
//				}
//				m_Spread.SetText(strTemp);
//			}
//			else
//			{
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_15"));
//				m_Spread.SetRow(16);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_0", "ROW_16"));
//			}
//
//			break;
//		case 1:
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_1"));
//			m_Spread.SetRow(2);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_2"));
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_3"));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_4"));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_5"));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_6"));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_7"));
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_8"));
//			m_Spread.SetRow(9);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_9"));
//			m_Spread.SetRow(10);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_10"));
//			m_Spread.SetRow(11);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_11"));
//			m_Spread.SetRow(12);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_12"));
//			m_Spread.SetRow(13);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_13"));
//			m_Spread.SetRow(14);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_14"));
//
//
//			if (AoiParam()->m_bUseMultilineSpecEx && m_nLineWidthGroupNum > 0)
//			{
//				if (1)
//				{
//					CString strVal;
//					strTemp = "";
//					for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
//					{
//						if (idx < 4)
//						{
//							if (idx)
//								strTemp += _T("/");
//							strVal.Format(_T("[%.1f,%.1f]"), m_fFineNarrowTraceViolation[idx], m_fWideTraceViolation[idx]);
//							strTemp += strVal;
//						}
//						else if (idx == 4)
//						{
//							strTemp += _T("/..");
//						}
//
//					}
//					m_Spread.SetCol(1);
//					m_Spread.SetRow(15);
//					m_Spread.SetTypeButtonText(strTemp);
//
//					strTemp = _T("");
//					for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
//					{
//						if (idx < 2)
//						{
//							if (idx)
//								strTemp += _T("/");
//							else
//								strTemp += _T("(MT) ");
//							strVal.Format(_T("%.1f"), m_fFineLineWidthGroup[idx]);
//							strTemp += strVal;
//						}
//						else if (idx == 2)
//						{
//							strTemp += _T("/..");
//						}
//
//					}
//					m_Spread.SetCol(0);
//					m_Spread.SetRow(15);
//					m_Spread.SetText(strTemp);
//				}
//			}
//			else
//			{
//				m_Spread.SetRow(15);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_15"));
//
//				m_Spread.SetRow(16);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_1", "ROW_16"));
//			}
//			break;
//		case 2:
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_1"));
//			m_Spread.SetRow(2);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_2"));
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_3"));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_4"));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_5"));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_6"));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_7"));
//			//20090412 hjc
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_8"));
//			m_Spread.SetRow(9);	//121226 hjc add
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_2", "ROW_9"));
//			//------------
//			break;
//		case 3:		//20100322 hjc add
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_1"));
//			m_Spread.SetRow(2);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_2"));
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_3"));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_4"));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_5"));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_6"));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_7"));
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_8"));
//			//jun 20120903 for LG_CCL-Inspector
//			m_Spread.SetRow(9);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_9"));
//			m_Spread.SetRow(10);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_10"));
//			m_Spread.SetRow(11);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_11"));
//			m_Spread.SetRow(12);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_3", "ROW_12"));
//			//------------
//			break;
//		case 4:
//			if (pGlobalDoc->m_bUseTeachingLineWidth)
//			{
//				if (pGlobalDoc->m_bUseOnlyViaInsp[AoiParam()->m_nCurrentInspectionMode])	//151210 hjc add
//				{
//					strTemp.Format(_T("[T:%d][Max:%d]  %s"), pGlobalDoc->m_nViaHoleMeanDiff, 255 - pGlobalDoc->m_nViaHoleMeanDiff, pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_1"));
//					m_Spread.SetRow(1);
//					m_Spread.SetText(strTemp);
//					m_Spread.SetRow(2);
//					strTemp.Format(_T("[T:%d][Max:%d]  %s"), pGlobalDoc->m_nViaHoleMeanDiff, pGlobalDoc->m_nViaHoleMeanDiff, pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_2"));
//					m_Spread.SetText(strTemp);
//				}
//				else if (pGlobalDoc->m_nVDMeanDiff > 0)
//				{
//					strTemp.Format(_T("[T:%d][Max:%d]  %s"), pGlobalDoc->m_nVDMeanDiff, 255 - pGlobalDoc->m_nVDMeanDiff, pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_1"));
//					m_Spread.SetRow(1);
//					m_Spread.SetText(strTemp);
//					m_Spread.SetRow(2);
//					strTemp.Format(_T("[T:%d][Max:%d]  %s"), pGlobalDoc->m_nVDMeanDiff, pGlobalDoc->m_nVDMeanDiff, pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_2"));
//					m_Spread.SetText(strTemp);
//				}
//				else
//				{
//					strTemp.Format(_T("[(X)VD Data]  %s"), pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_1"));
//					m_Spread.SetRow(1);
//					m_Spread.SetText(strTemp);
//					m_Spread.SetRow(2);
//					strTemp.Format(_T("[(X)VD Data]  %s"), pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_2"));
//					m_Spread.SetText(strTemp);
//				}
//			}
//			else
//			{
//				m_Spread.SetRow(1);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_1"));
//				m_Spread.SetRow(2);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_2"));
//			}
//
//
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_3"));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_4"));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_5"));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_6"));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_7"));
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_8"));
//			m_Spread.SetRow(9);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_9"));
//			m_Spread.SetRow(10);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_10"));
//			m_Spread.SetRow(11);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_11"));
//			m_Spread.SetRow(12);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_12"));
//			m_Spread.SetRow(13);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_13"));
//			m_Spread.SetRow(14);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_14"));
//			m_Spread.SetRow(15);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_15"));
//			m_Spread.SetRow(16);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_16"));
//			m_Spread.SetRow(17);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_17"));
//			m_Spread.SetRow(18);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_18"));
//			m_Spread.SetRow(19);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_19"));
//			m_Spread.SetRow(20);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_20"));
//			m_Spread.SetRow(21);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_21"));
//			m_Spread.SetRow(22);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_4", "ROW_22"));		//150606 hjc add
//			break;
//		case 5:
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_1"));
//			m_Spread.SetRow(2);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_2"));
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_3"));
//
//			if (pGlobalDoc->m_bUseTeachingLineWidth)
//			{
//				if (pGlobalDoc->m_nHoleMeanDiff > 0)
//				{
//					strTemp.Format(_T("[T:%d]   %s"), pGlobalDoc->m_nHoleMeanDiff, pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_4"));
//					m_Spread.SetRow(4);
//					m_Spread.SetText(strTemp);
//
//					strTemp.Format(_T("[T:%d]   %s"), pGlobalDoc->m_nHoleMeanDiff, pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_5"));
//					m_Spread.SetRow(5);
//					m_Spread.SetText(strTemp);
//				}
//				else
//				{
//					//160125 lgh 
//					strTemp.Format(_T("[(X) HoleData]   %s"), pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_4"));
//					m_Spread.SetRow(4);
//					m_Spread.SetText(strTemp);
//
//					strTemp.Format(_T("[(X) HoleData]   %s"), pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_5"));
//					m_Spread.SetRow(5);
//					m_Spread.SetText(strTemp);
//				}
//			}
//			else
//			{
//				m_Spread.SetRow(4);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_4"));
//				m_Spread.SetRow(5);
//				m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_5"));
//
//			}
//
//
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_6"));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_7"));
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_8"));
//			m_Spread.SetRow(9);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_9"));
//			m_Spread.SetRow(10);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_10"));
//			m_Spread.SetRow(11);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_11"));
//			m_Spread.SetRow(12);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_12"));
//			m_Spread.SetRow(13);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_13"));
//			m_Spread.SetRow(14);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_14"));
//			m_Spread.SetRow(15);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_15"));
//			m_Spread.SetRow(16);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_16"));
//			m_Spread.SetRow(17);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_17"));
//			m_Spread.SetRow(18);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_5", "ROW_18"));
//			break;
//		case 6:
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_1"));
//			m_Spread.SetRow(2);	//111214 hjc mod
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_2"));
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_3"));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_4"));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_5"));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_6"));
//			m_Spread.SetRow(7);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_7"));
//			m_Spread.SetRow(8);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_8"));
//			m_Spread.SetRow(9);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_9"));
//			m_Spread.SetRow(10);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_10"));
//			m_Spread.SetRow(11);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_11"));
//			m_Spread.SetRow(12);	//120105 hjc add
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_12"));
//			m_Spread.SetRow(13);	//120109 hjc add
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_13"));
//			m_Spread.SetRow(14);	//120105 hjc add
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_14"));
//			m_Spread.SetRow(15);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_6", "ROW_15"));
//			//----------------
//			break;
//		case 7:
//			m_Spread.SetRow(1);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_3"));
//			m_Spread.SetRow(2);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_4"));
//			m_Spread.SetRow(3);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_5"));
//			m_Spread.SetRow(4);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_6"));
//			m_Spread.SetRow(5);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_7"));
//			m_Spread.SetRow(6);
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_8"));
//			m_Spread.SetRow(7);	//20100210 hjc add
//			m_Spread.SetText(pGlobalView->GetMultiLangString(pGlobalDoc->m_nSelectedLanguage, "SPEC_TAB_7", "ROW_9"));
//
//			if (AoiParam()->m_bUseAutoPinPosAdjust || g_bUsePinPosEstimate)
//			{
//				m_Spread.SetRow(8);	//20100210 hjc add
//				m_Spread.SetText(LoadLanguageString(ID_PANEL_SIZE_X, pGlobalDoc->m_nSelectedLanguage));
//
//				m_Spread.SetRow(9);	//20100210 hjc add
//				m_Spread.SetText(LoadLanguageString(ID_PANEL_SIZE_Y, pGlobalDoc->m_nSelectedLanguage));
//#ifdef IRIS_AXIS
//				m_Spread.SetRow(10);	//20100210 hjc add
//				if (pGlobalDoc->m_nSelectedLanguage == KOREA)
//					m_Spread.SetText(_T("¡∂∏Æ∞≥ ¿ßƒ°"));
//				else if (pGlobalDoc->m_nSelectedLanguage == JAPANESE)
//					m_Spread.SetText(_T("´´´·´ÈŒÌ™ÍÍ»ˆ«"));
//				else
//					m_Spread.SetText(_T("IrisPos"));
//#endif
//			}
//			else
//			{
//#ifdef IRIS_AXIS
//				m_Spread.SetRow(8);	//20100210 hjc add
//				if (pGlobalDoc->m_nSelectedLanguage == KOREA)
//					m_Spread.SetText(_T("¡∂∏Æ∞≥ ¿ßƒ°"));
//				else if (pGlobalDoc->m_nSelectedLanguage == JAPANESE)
//					m_Spread.SetText(_T("´´´·´ÈŒÌ™ÍÍ»ˆ«"));
//				else
//					m_Spread.SetText(_T("IrisPos"));
//#endif
//			}
//
//			break;
//		}
//	}
}

void CDlgSpec::InitSpreadTab0()
{
//	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
//	//	m_Spread.SetBool()
//	//	m_Spread.SetAppearanceStyle(0);// FOR CLASSIC
//	// Initialize Tab ctrl for information viewer
//	m_tabDlgInspection.HighlightItem(m_nTabNum, FALSE);
//
//	//Tab Index
//	m_nTabNum = 0;
//	m_tabDlgInspection.HighlightItem(m_nTabNum, TRUE);
//
//	m_Spread.SetReDraw(FALSE);
//	InitSpread();
//	//Column Width twip
//	m_Spread.SetMaxCols(2);
//
//	//161123 lgh
//	if (SpecData.nLineWidthGroupNum >0 && AoiParam()->m_bUseMultilineSpecEx)	//170526 hjc mod
//		m_Spread.SetMaxRows(15);
//	else
//		m_Spread.SetMaxRows(16);
//
//	//m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//	SS_CELLTYPE stype;
//
//	m_Spread.SetTypeEdit(&stype, 0, 128, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(SS_ALLCOLS, SS_ALLROWS, &stype);
//
//#if WIN_OS == WIN_10
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//
//		m_Spread.SetFont(1, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize + 2, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(2, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//
//		m_Spread.SetFont(3, SS_ALLROWS, hfont, TRUE);
//
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//
//#else
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//#endif
//
//
//	//m_Spread.SetCol(SS_HEADER);	
//	//m_Spread.SetRow(SS_ALLROWS);
//
//	//«Ï¥ı ƒ¡∆Æ∑—
//	m_Spread.SetTypeStaticText(&stype, SS_TEXT_SHADOW | SS_TEXT_VCENTER | SS_TEXT_RIGHT);
//	m_Spread.SetCellType(SS_HEADER, SS_ALLROWS, &stype);
//
//	//Column Caption
//	//m_Spread.SetBackColor(RGB(226,233,251));
//
//	// ?EΩ√Ω∫≈€¿« «»ºø¥ÅETwips∞™¿ª ∆ƒæ««—¥Ÿ.
//	CDC* pDC = GetDC();
//	int nLogX = pDC->GetDeviceCaps(LOGPIXELSX);
//	ReleaseDC(pDC);
//	int nTwipPerPixel = 1440 / nLogX;
//
//	// ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	CRect rect;
//	m_Spread.GetClientRect(rect);
//	long twpWidth = (rect.right - rect.left);
//
//	// Ω∫«¡∑πµÂ¿« ∆¯¿ª  Column Width¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadWidth, EachColWidth;
//	m_Spread.LogUnitsToColWidth(twpWidth, &fSpreadWidth);
//
//	if (AoiParam()->m_bSetSpecLocking)
//	{
//		m_Spread.SetColWidth(0, 37);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 20);	//140314 hjc mod
//	}
//	else
//	{
//		m_Spread.SetColWidth(0, 32);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 28);	//140314 hjc mod
//	}
//
//	double dColGetWidth = 0;
//	double dColGetWidth2 = 0;
//	m_Spread.GetColWidth(0, &dColGetWidth);
//
//	EachColWidth = (float)(fSpreadWidth - (dColGetWidth + m_Spread.GetColWidth(2)) - 0.5);
//	m_Spread.SetColWidth(1, EachColWidth);
//
//	m_Spread.SetRowHeight(0, 5); // COL(0)'S HEIGHT
//
//								 // ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	long twpHeight = (rect.bottom - rect.top);
//
//	// Ω∫«¡∑πµÂ¿« ≥Ù¿Ã∏¶ Row Height¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadHeight;//, EachRowHeight
//
//
//
//	long nRow;
//	m_Spread.LogUnitsToRowHeight(0, twpHeight, &fSpreadHeight);
//	double dSepHeight = (fSpreadHeight - 10) / max(1, m_Spread.GetMaxRows() + 1);
//	for (nRow = 1; nRow <= m_Spread.GetMaxRows(); nRow++)
//	{
//
//		m_Spread.SetRowHeight(nRow, dSepHeight);
//	}
//
//	//Column Caption
//	m_Spread.SetRow(0);
//
//	m_Spread.SetCol(1);
//	m_Spread.SetText(_T(" "));
//	m_Spread.SetCol(2);
//	m_Spread.SetText(_T(" "));
//
//
//
//	ChangeSpecSpreadCaption(0);
//	m_Spread.SetCellBorder(-1, -1, -1, -1, SS_BORDERTYPE_BOTTOM | SS_BORDERTYPE_RIGHT, RGB(180, 180, 180), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//	for (int iRow = 1; iRow <= m_Spread.GetMaxRows(); iRow++)
//	{
//		m_Spread.SetRow(iRow);
//		m_Spread.SetCol(1);
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_VCENTER | SSS_ALIGN_CENTER, 128, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(SS_ALLCOLS, iRow, &stype);
//		//m_Spread.SetCellType(TYPE_DEFAULT,SSS_ALIGN_VCENTER |SSS_ALIGN_CENTER);
//		//m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		//m_Spread.SetTypeAlign(SSS_ALIGN_RIGHT);
//
//		if (m_bMasterLocalFlag[0][iRow - 1] && pGlobalDoc->m_bDefaultSpecFlag)
//		{
//			//m_Spread.SetForeColor(RGB(58,53,151));
//			m_Spread.SetColor(1, iRow, RGB(255, 255, 255), RGB(58, 53, 151));
//		}
//		else
//		{
//			m_Spread.SetColor(1, iRow, RGB(255, 255, 255), RGB(60, 145, 103));
//			//m_Spread.SetForeColor(RGB(60,145,103));
//		}
//		//m_Spread.SetEditMode(TRUE);
//		//m_Spread.SetBackColor(RGB(255,255,255));
//		m_Spread.SetLock(FALSE);
//
//		m_Spread.SetCol(2);
//		m_Spread.SetCellType(TYPE_STATIC, SSS_ALIGN_VCENTER | SSS_ALIGN_LEFT);
//
//		m_Spread.SetColor(1, iRow, RGB(255, 255, 255), RGB(0, 0, 0));
//
//		// Clear Cell Boarder
//		//m_Spread.SetCellBorder(0,iRow,2,iRow,8,0,-1); // Bottom Line - Default Style.
//	}
//
//	m_bEnableCheckBox = FALSE;
//
//	// Clear Spread Sheet
//	m_Spread.ClearRange(1, 1, m_Spread.GetMaxCols(), m_Spread.GetMaxRows());
//
//	// syd-091008
//	// Button in Cell
//	m_Spread.SetCol(1);
//	if (SpecData.nLineWidthGroupNum > 0)	//170526 hjc mod
//	{
//		if (AoiParam()->m_bUseMultilineSpecEx)
//		{
//
//			//150611 hjc add
//			if (pGlobalDoc->m_bUseCombo)
//			{
//				// ComboBox in Cell
//				m_Spread.SetCol(1);
//				m_Spread.SetRow(9);
//				//m_Spread.SetCellType(TYPE_COMBO);
//
//				//m_Spread.SetTypeComboBox(&stype,SSS_ALIGN_CENTER  | SS_CB_DROPDOWN,"Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)\tMaxLimit     (10%)");
//				//m_Spread.SetCellType(1, 9, &stype);
//
//#if LANGUAGE == ENGLISH
//				m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)\tMaxLimit     (10%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"	//\tMaxLimit     (10%)
//#elif LANGUAGE == KOREAN
//				m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)\tMaxLimit     (10%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//#elif LANGUAGE == JAPANESE
//				m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)\tMaxLimit     (10%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//#endif	
//				m_Spread.SetTypeComboBoxEditable(FALSE);
//				m_Spread.SetTypeComboBoxMaxDrop(10);
//				//m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER );
//				//m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//
//				m_Spread.SetRow(10);
//				//	m_Spread.SetCellType(TYPE_COMBO);
//#if LANGUAGE == ENGLISH
//				m_Spread.SetTypeComboBoxList(_T("Highest    (110%)\tVeryHigh   (120%)\tHigh        (130%)\tNormal     (140%)\tLow         (150%)\tVeryLow   (160%)\tLowest     (170%)\tMaxLimit     (190%)"));		//140126 hjc add \tMaxLimit     (190%)
//#elif LANGUAGE == KOREAN
//				m_Spread.SetTypeComboBoxList(_T("Highest    (110%)\tVeryHigh   (120%)\tHigh        (130%)\tNormal     (140%)\tLow         (150%)\tVeryLow   (160%)\tLowest     (170%)\tMaxLimit     (190%)"));
//#elif LANGUAGE == JAPANESE
//				m_Spread.SetTypeComboBoxList(_T("Highest    (110%)\tVeryHigh   (120%)\tHigh        (130%)\tNormal     (140%)\tLow         (150%)\tVeryLow   (160%)\tLowest     (170%)\tMaxLimit     (190%)"));
//#endif
//				m_Spread.SetTypeComboBoxEditable(FALSE);
//				m_Spread.SetTypeComboBoxMaxDrop(10);
//				//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER );
//				//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//			}
//
//			m_Spread.SetRow(15);
//
//			//subbtn_co
//			m_Spread.SetTypeButton(&stype, SBS_NOPOINTERFOCUS, _T(""), NULL, SUPERBTN_PICT_NONE, NULL, SUPERBTN_PICT_NONE, SUPERBTN_TYPE_NORMAL, 1, nullptr);
//			m_Spread.SetCellType(1, 15, &stype);
//		}
//		else
//		{
//			for (int i = 9; i <= 16; i++)
//			{
//				m_Spread.SetRow(i);
//				//subbtn_co
//				m_Spread.SetTypeButton(&stype, SBS_NOPOINTERFOCUS, _T(""), NULL, SUPERBTN_PICT_NONE, NULL, SUPERBTN_PICT_NONE, SUPERBTN_TYPE_NORMAL, 1, nullptr);
//				m_Spread.SetCellType(1, i, &stype);
//			}
//		}
//	}
//	else
//	{
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_CENTER | SSS_ALIGN_VCENTER, 128, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(1, 15, &stype);
//
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_CENTER | SSS_ALIGN_VCENTER, 128, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(1, 16, &stype);
//
//		//150611 hjc add
//		if (pGlobalDoc->m_bUseCombo)
//		{
//			// ComboBox in Cell
//			m_Spread.SetCol(1);
//			m_Spread.SetRow(9);
//			//m_Spread.SetCellType(TYPE_COMBO);
//
//			//m_Spread.SetTypeComboBox(&stype,SSS_ALIGN_CENTER  | SS_CB_DROPDOWN,"Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)\tMaxLimit     (10%)");
//			//m_Spread.SetCellType(1, 9, &stype);
//
//#if LANGUAGE == ENGLISH
//			m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)\tMaxLimit     (10%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"	//\tMaxLimit     (10%)
//#elif LANGUAGE == KOREAN
//			m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)\tMaxLimit     (10%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//#elif LANGUAGE == JAPANESE
//			m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)\tMaxLimit     (10%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//#endif	
//			m_Spread.SetTypeComboBoxEditable(FALSE);
//			m_Spread.SetTypeComboBoxMaxDrop(10);
//			//m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER );
//			//m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//
//			m_Spread.SetRow(10);
//			//	m_Spread.SetCellType(TYPE_COMBO);
//#if LANGUAGE == ENGLISH
//			m_Spread.SetTypeComboBoxList(_T("Highest    (110%)\tVeryHigh   (120%)\tHigh        (130%)\tNormal     (140%)\tLow         (150%)\tVeryLow   (160%)\tLowest     (170%)\tMaxLimit     (190%)"));		//140126 hjc add \tMaxLimit     (190%)
//#elif LANGUAGE == KOREAN
//			m_Spread.SetTypeComboBoxList(_T("Highest    (110%)\tVeryHigh   (120%)\tHigh        (130%)\tNormal     (140%)\tLow         (150%)\tVeryLow   (160%)\tLowest     (170%)\tMaxLimit     (190%)"));
//#elif LANGUAGE == JAPANESE
//			m_Spread.SetTypeComboBoxList(_T("Highest    (110%)\tVeryHigh   (120%)\tHigh        (130%)\tNormal     (140%)\tLow         (150%)\tVeryLow   (160%)\tLowest     (170%)\tMaxLimit     (190%)"));
//#endif
//			m_Spread.SetTypeComboBoxEditable(FALSE);
//			m_Spread.SetTypeComboBoxMaxDrop(10);
//			//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER );
//			//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//		}
//	}
//
//	// Static in Cell
//	m_Spread.SetCol(2);
//
//	m_Spread.SetRow(1);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T("um"));
//
//	m_Spread.SetRow(2);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//
//	CString strData;
//
//	m_Spread.SetRow(3);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//	{   //20191224 add 251
//		strData.Format(_T("DN[N72,75,251](%d~%d)"), pGlobalDoc->m_nSpecNickGrayLowerLimit, pGlobalDoc->m_nSpecNickGrayUpperLimit);	//170217 hjc mod
//		m_Spread.SetText(strData);
//	}
//	else
//	{
//		strData.Format(_T("DN[N72,75,251](%d~%d)"), pGlobalDoc->m_nSpecNickGrayLowerLimit, pGlobalDoc->m_nSpecNickGrayUpperLimit);	//170217 hjc mod
//		m_Spread.SetText(strData);
//	}
//
//	//150413 hjc add
//	m_Spread.SetRow(4);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//	{
//		strData.Format(_T("DN[OP0,OP41,N44](%d~%d)"), pGlobalDoc->m_nSpecOpenGrayLowerLimit, pGlobalDoc->m_nSpecOpenGrayUpperLimit); //20200102 add N41,44
//		m_Spread.SetText(strData);
//	}
//	else
//	{
//		strData.Format(_T("DN(%d~%d)"), pGlobalDoc->m_nSpecOpenGrayLowerLimit, pGlobalDoc->m_nSpecOpenGrayUpperLimit);
//		m_Spread.SetText(strData);
//	}
//
//	m_Spread.SetRow(5);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//	{
//		strData.Format(_T("DN[P13,15,72,80,83~85,N26,S42,83]"));	//170217 hjc mod	//20200102 mod
//		m_Spread.SetText(strData);
//	}
//	else
//	{
//		strData.Format(_T("DN"));
//		m_Spread.SetText(strData);
//	}
//
//	m_Spread.SetRow(6);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//	{
//		strData.Format(_T("DN[N11,13,24~26,32,72,83~85,87,251,ES303]"));	//20200102 mod
//		m_Spread.SetText(strData);
//	}
//	else
//	{
//		strData.Format(_T("DN"));
//		m_Spread.SetText(strData);
//	}
//
//
//	m_Spread.SetRow(7);
//	m_Spread.SetCellType(TYPE_STATIC);
//#if MACHINE_MODEL == INSPRO2HR2R || MACHINE_MODEL == INSPRO2HR2R_GANTRY //20101026 add
//	m_Spread.SetText(_T("DN[90,70~100]"));
//#else
//	m_Spread.SetText(_T("DN[OP]"));
//#endif
//
//	m_Spread.SetRow(8);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[N4]"));
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("um[N4]"));
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("pxl"));
//
//
//	m_Spread.SetRow(9);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[N1,2,43,70,78]"));	//170217 hjc mod  //20191224 add 43
//	else
//		m_Spread.SetText(_T("%"));
//
//	m_Spread.SetRow(10);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[P1]"));
//	else
//		m_Spread.SetText(_T("%"));
//
//
//	m_Spread.SetRow(11);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[N3,8,31,43,71,77]"));	//20191224 add 43
//	else
//		m_Spread.SetText(_T("%"));
//
//	m_Spread.SetRow(12);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[P3,8,31,71,77]"));	//170217 hjc mod
//	else
//		m_Spread.SetText(_T("%"));
//
//	m_Spread.SetRow(13);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[N6,7,10,14,18,22,30,31,33,45,62,63,69,70,72,74,76,218,P70,75]"));	//20200102 mod
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("pxl[N6,7,10,14,18,22,30,31,33,45,62,63,69,70,72,74,76,218,P70,75]"));   //20190724 add 72,
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("pxl"));
//
//	m_Spread.SetRow(14);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[P6,7,10,14,18,28,30,62,70,72]"));	//20120522-ndy mod	//170217 hjc mod
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("pxl[P6,7,10,14,18,28,30,62,70,72]"));	//20120522-ndy mod  //170217 hjc mod
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("pxl"));
//
//	m_Spread.SetRow(15);
//	m_Spread.SetCellType(TYPE_STATIC);
//	//if (SpecData.nLineWidthGroupNum >0 && AoiParam()->m_bUseMultilineSpecEx)
//	//170607 lgh fix
//	if (AoiParam()->m_bUseMultilineSpecEx == FALSE || SpecData.nLineWidthGroupNum == 0)
//	{
//		if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//			m_Spread.SetText(_T("um[N5]"));
//		else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//			m_Spread.SetText(_T("pxl[N5]"));
//		else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//			m_Spread.SetText(_T("um"));
//		else
//			m_Spread.SetText(_T("pxl"));
//	}
//	else
//	{
//		if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//			m_Spread.SetText(_T("um[N5,7,P5,7]"));	//170217 hjc mod
//		else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//			m_Spread.SetText(_T("pxl[N5,7,P5,7]"));	//170217 hjc mod
//		else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//			m_Spread.SetText(_T("um"));
//		else
//			m_Spread.SetText(_T("pxl"));
//	}
//
//	//161123 lgh
//	m_Spread.SetRow(16);
//	m_Spread.SetCellType(TYPE_STATIC);
//
//	//	if(SpecData.nLineWidthGroupNum <=0)
//	//170607 lgh fix
//	if (AoiParam()->m_bUseMultilineSpecEx == FALSE || SpecData.nLineWidthGroupNum == 0)
//	{
//		if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//			m_Spread.SetText(_T("um[P5]"));	//170217 hjc mod
//		else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//			m_Spread.SetText(_T("pxl[P5]"));	//170217 hjc mod
//		else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//			m_Spread.SetText(_T("um"));
//		else
//			m_Spread.SetText(_T("pxl"));
//	}
//	else  //170217 hjc add
//	{
//		/*
//		if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[P5,7]"));	//170217 hjc mod
//		else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("pxl[P5,7]"));	//170217 hjc mod
//		else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//		else
//		m_Spread.SetText(_T("pxl"));
//		*/
//	}
//
//	//m_Spread.SetCellBorder(-1,-1,-1,-1,SS_BORDERTYPE_NONE ,RGB(0,0,0),SS_BORDERSTYLE_SOLID ); // Bottom Line - Solid Style.
//
//	// Draw Cell Boarder
//	m_Spread.SetCellBorder(0, 2, 2, 2, SS_BORDERTYPE_OUTLINE | SS_BORDERTYPE_BOTTOM, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 7, 2, 7, SS_BORDERTYPE_OUTLINE | SS_BORDERTYPE_BOTTOM, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 12, 2, 12, SS_BORDERTYPE_OUTLINE | SS_BORDERTYPE_BOTTOM, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 14, 2, 14, SS_BORDERTYPE_OUTLINE | SS_BORDERTYPE_BOTTOM, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 16, 2, 16, SS_BORDERTYPE_OUTLINE | SS_BORDERTYPE_BOTTOM, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_OUTLINE, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//																									 //Set Color Group
//	for (int iCol = 1; iCol <= 2; iCol++)
//	{
//		m_Spread.SetCol(iCol);
//
//		m_Spread.SetRow(1);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(2);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//
//		m_Spread.SetRow(3);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(4);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(5);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(6);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(7);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//
//		m_Spread.SetRow(8);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(9);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(10);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(11);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(12);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//
//		m_Spread.SetRow(13);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(14);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//
//		m_Spread.SetRow(15);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
//
//		m_Spread.SetRow(16);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
//	}
}

void CDlgSpec::InitSpreadTab1()
{
//	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
//	// Initialize Tab ctrl for information viewer
//	m_tabDlgInspection.HighlightItem(m_nTabNum, FALSE);
//
//	//Tab Index
//	m_nTabNum = 1;
//	m_tabDlgInspection.HighlightItem(m_nTabNum, TRUE);
//
//	m_Spread.SetReDraw(FALSE);
//	InitSpread();
//	//Column Width twip
//	m_Spread.SetMaxCols(2);
//	if (SpecData.nLineWidthGroupNum >0 && AoiParam()->m_bUseMultilineSpecEx)
//		m_Spread.SetMaxRows(15);
//	else
//		m_Spread.SetMaxRows(16);
//
//#if WIN_OS == WIN_10
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		//HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(1, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize + 2, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(2, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//
//		m_Spread.SetFont(3, SS_ALLROWS, hfont, TRUE);
//
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//
//#else
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//#endif
//
//
//	// ?EΩ√Ω∫≈€¿« «»ºø¥ÅETwips∞™¿ª ∆ƒæ««—¥Ÿ.
//	CDC* pDC = GetDC();
//	int nLogX = pDC->GetDeviceCaps(LOGPIXELSX);
//	ReleaseDC(pDC);
//	int nTwipPerPixel = 1440 / nLogX;
//
//	// ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	CRect rect;
//	m_Spread.GetClientRect(rect);
//	long twpWidth = (rect.right - rect.left);
//
//	// Ω∫«¡∑πµÂ¿« ∆¯¿ª  Column Width¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadWidth, EachColWidth;
//	m_Spread.LogUnitsToColWidth(twpWidth, &fSpreadWidth);
//
//	if (AoiParam()->m_bSetSpecLocking)
//	{
//		m_Spread.SetColWidth(0, 37);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 20);	//140314 hjc mod
//	}
//	else
//	{
//		m_Spread.SetColWidth(0, 32);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 28);	//140314 hjc mod
//	}
//	EachColWidth = (float)(fSpreadWidth - (m_Spread.GetColWidth(0)
//		+ m_Spread.GetColWidth(2)) - 0.5);
//	m_Spread.SetColWidth(1, EachColWidth);
//
//	m_Spread.SetRowHeight(0, 5); // COL(0)'S HEIGHT
//
//								 // ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	long twpHeight = (rect.bottom - rect.top);
//
//	// Ω∫«¡∑πµÂ¿« ≥Ù¿Ã∏¶ Row Height¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadHeight;//, EachRowHeight
//
//	long nRow;
//	m_Spread.LogUnitsToRowHeight(0, twpHeight, &fSpreadHeight);
//	double dSepHeight = (fSpreadHeight - 10) / max(1, m_Spread.GetMaxRows() + 1);
//	for (nRow = 1; nRow <= m_Spread.GetMaxRows(); nRow++)
//	{
//
//		m_Spread.SetRowHeight(nRow, dSepHeight);
//	}
//	if (AoiParam()->m_bSetSpecLocking)
//	{
//		m_Spread.SetRowHeight(14, 16);
//		m_Spread.SetRowHeight(15, 16);
//	}
//	//Column Caption
//	m_Spread.SetRow(0);
//
//	m_Spread.SetCol(1);
//	m_Spread.SetText(_T(" "));
//	m_Spread.SetCol(2);
//	m_Spread.SetText(_T(" "));
//
//	//«Ï¥ı ƒ¡∆Æ∑—
//	SS_CELLTYPE stype;
//	m_Spread.SetTypeStaticText(&stype, SS_TEXT_SHADOW | SS_TEXT_VCENTER | SS_TEXT_RIGHT);
//	m_Spread.SetCellType(SS_HEADER, SS_ALLROWS, &stype);
//	ChangeSpecSpreadCaption(1);
//
//	//m_Spread.SetCellBorder(-1,-1,-1,-1,SS_BORDERTYPE_OUTLINE ,RGB(0,0,0),SS_BORDERSTYLE_NONE ); // Bottom Line - Solid Style.
//	//m_Spread.SetCellBorder(-1,-1,-1,-1,SS_BORDERTYPE_BOTTOM | SS_BORDERTYPE_RIGHT ,RGB(180,180,180),SS_BORDERSTYLE_SOLID ); // Bottom Line - Solid Style.
//
//	for (int iRow = 1; iRow <= m_Spread.GetMaxRows(); iRow++)
//	{
//		m_Spread.SetRow(iRow);
//
//		m_Spread.SetCol(1);
//		m_Spread.SetCellType(TYPE_DEFAULT);
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_CENTER | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(SS_ALLCOLS, iRow, &stype);
//
//		if (m_bMasterLocalFlag[1][iRow - 1] && pGlobalDoc->m_bDefaultSpecFlag)
//			m_Spread.SetForeColor(RGB(58, 53, 151));
//		else
//			m_Spread.SetForeColor(RGB(60, 145, 103));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//		m_Spread.SetLock(FALSE);
//
//		m_Spread.SetCol(2);
//		m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_CENTER | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(2, iRow, &stype);
//		m_Spread.SetForeColor(RGB(0, 0, 0));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//
//		// Clear Cell Boarder
//		m_Spread.SetCellBorder(0, iRow, 2, iRow, 8, -1, 0); // Bottom Line - Default Style.
//	}
//	//m_Spread.SetCellBorder(-1,-1,-1,-1,SS_BORDERTYPE_OUTLINE ,RGB(180,180,180),SS_BORDERSTYLE_SOLID ); // Bottom Line - Solid Style.
//
//	m_bEnableCheckBox = FALSE;
//
//	// Clear Spread Sheet
//	m_Spread.ClearRange(1, 1, m_Spread.GetMaxCols(), m_Spread.GetMaxRows(), TRUE);
//
//	// Button in Cell
//	m_Spread.SetCol(1);
//
//	m_Spread.SetCol(1);
//	if (SpecData.nLineWidthGroupNum > 0)
//	{
//		if (AoiParam()->m_bUseMultilineSpecEx)
//		{
//			//150611 hjc add
//			if (pGlobalDoc->m_bUseCombo)
//			{
//				// ComboBox in Cell
//				m_Spread.SetCol(1);
//
//				m_Spread.SetRow(9);
//				m_Spread.SetCellType(TYPE_COMBO);
//#if LANGUAGE == ENGLISH
//				m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//#elif LANGUAGE == KOREAN
//				m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//#elif LANGUAGE == JAPANESE
//				m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//#endif	
//				m_Spread.SetTypeComboBoxEditable(FALSE);
//				m_Spread.SetTypeComboBoxMaxDrop(10);
//				//m_Spread.SetTypeEdit(&stype,SSS_ALIGN_CENTER | SSS_ALIGN_VCENTER,256,SS_CHRSET_CHR,SS_CASE_NOCASE);
//				//m_Spread.SetCellType(1, 9, &stype);
//
//				m_Spread.SetRow(10);
//				m_Spread.SetCellType(TYPE_COMBO);
//#if LANGUAGE == ENGLISH
//				m_Spread.SetTypeComboBoxList(_T("Highest    (110%)\tVeryHigh   (120%)\tHigh        (130%)\tNormal     (140%)\tLow         (150%)\tVeryLow   (160%)\tLowest     (170%)"));
//#elif LANGUAGE == KOREAN
//				m_Spread.SetTypeComboBoxList(_T("Highest    (110%)\tVeryHigh   (120%)\tHigh        (130%)\tNormal     (140%)\tLow         (150%)\tVeryLow   (160%)\tLowest     (170%)"));
//#elif LANGUAGE == JAPANESE
//				m_Spread.SetTypeComboBoxList(_T("Highest    (110%)\tVeryHigh   (120%)\tHigh        (130%)\tNormal     (140%)\tLow         (150%)\tVeryLow   (160%)\tLowest     (170%)"));
//#endif
//				m_Spread.SetTypeComboBoxEditable(FALSE);
//				m_Spread.SetTypeComboBoxMaxDrop(10);
//				//m_Spread.SetTypeEdit(&stype,SSS_ALIGN_CENTER | SSS_ALIGN_VCENTER,256,SS_CHRSET_CHR,SS_CASE_NOCASE);
//				//m_Spread.SetCellType(1, 10, &stype);
//			}
//
//			m_Spread.SetRow(15);
//
//			//subbtn_co
//			m_Spread.SetTypeButton(&stype, SBS_NOPOINTERFOCUS, _T(""), NULL, SUPERBTN_PICT_NONE, NULL, SUPERBTN_PICT_NONE, SUPERBTN_TYPE_NORMAL, 1, nullptr);
//			m_Spread.SetCellType(1, 15, &stype);
//
//			//		m_Spread.SetTypeEdit(&stype,SSS_ALIGN_CENTER | SSS_ALIGN_VCENTER,128,SS_CHRSET_CHR,SS_CASE_NOCASE);
//			//		m_Spread.SetCellType(1, 15, &stype);
//
//			m_Spread.SetRow(16);
//			m_Spread.SetTypeButton(&stype, SBS_NOPOINTERFOCUS, _T(""), NULL, SUPERBTN_PICT_NONE, NULL, SUPERBTN_PICT_NONE, SUPERBTN_TYPE_NORMAL, 1, nullptr);
//			m_Spread.SetCellType(1, 16, &stype);
//		}
//		else
//		{
//			for (int i = 9; i <= 16; i++)
//			{
//				m_Spread.SetRow(i);
//
//				m_Spread.SetTypeButton(&stype, SBS_NOPOINTERFOCUS, _T(""), NULL, SUPERBTN_PICT_NONE, NULL, SUPERBTN_PICT_NONE, SUPERBTN_TYPE_NORMAL, 1, nullptr);
//				m_Spread.SetCellType(1, i, &stype);
//			}
//		}
//	}
//	else
//	{
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_CENTER | SSS_ALIGN_VCENTER, 128, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(1, 15, &stype);
//
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_CENTER | SSS_ALIGN_VCENTER, 128, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(1, 16, &stype);
//
//
//		//150611 hjc add
//		if (pGlobalDoc->m_bUseCombo)
//		{
//			// ComboBox in Cell
//			m_Spread.SetCol(1);
//
//			m_Spread.SetRow(9);
//			m_Spread.SetCellType(TYPE_COMBO);
//#if LANGUAGE == ENGLISH
//			m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//#elif LANGUAGE == KOREAN
//			m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//#elif LANGUAGE == JAPANESE
//			m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//#endif	
//			m_Spread.SetTypeComboBoxEditable(FALSE);
//			m_Spread.SetTypeComboBoxMaxDrop(10);
//			//m_Spread.SetTypeEdit(&stype,SSS_ALIGN_CENTER | SSS_ALIGN_VCENTER,256,SS_CHRSET_CHR,SS_CASE_NOCASE);
//			//m_Spread.SetCellType(1, 9, &stype);
//
//			m_Spread.SetRow(10);
//			m_Spread.SetCellType(TYPE_COMBO);
//#if LANGUAGE == ENGLISH
//			m_Spread.SetTypeComboBoxList(_T("Highest    (110%)\tVeryHigh   (120%)\tHigh        (130%)\tNormal     (140%)\tLow         (150%)\tVeryLow   (160%)\tLowest     (170%)"));
//#elif LANGUAGE == KOREAN
//			m_Spread.SetTypeComboBoxList(_T("Highest    (110%)\tVeryHigh   (120%)\tHigh        (130%)\tNormal     (140%)\tLow         (150%)\tVeryLow   (160%)\tLowest     (170%)"));
//#elif LANGUAGE == JAPANESE
//			m_Spread.SetTypeComboBoxList(_T("Highest    (110%)\tVeryHigh   (120%)\tHigh        (130%)\tNormal     (140%)\tLow         (150%)\tVeryLow   (160%)\tLowest     (170%)"));
//#endif
//			m_Spread.SetTypeComboBoxEditable(FALSE);
//			m_Spread.SetTypeComboBoxMaxDrop(10);
//			//m_Spread.SetTypeEdit(&stype,SSS_ALIGN_CENTER | SSS_ALIGN_VCENTER,256,SS_CHRSET_CHR,SS_CASE_NOCASE);
//			//m_Spread.SetCellType(1, 10, &stype);
//		}
//	}
//
//	// Static in Cell
//	m_Spread.SetCol(2);
//
//	m_Spread.SetRow(1);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 1, &stype);
//
//	m_Spread.SetRow(2);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T("um"));
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 2, &stype);
//
//	m_Spread.SetRow(3);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[N72,75]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 3, &stype);
//
//	//150413 hjc add
//	m_Spread.SetRow(4);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[OP0,41,N44]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 4, &stype);
//
//	m_Spread.SetRow(5);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[P13,15,83]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 5, &stype);
//
//	m_Spread.SetRow(6);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[N16,25]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 6, &stype);
//
//	m_Spread.SetRow(7);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T("DN"));
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 7, &stype);
//
//	m_Spread.SetRow(8);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[N104]"));
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("um[N104]"));
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("pxl"));
//
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 8, &stype);
//
//	m_Spread.SetRow(9);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[N101,102]"));
//	else
//		m_Spread.SetText(_T("%"));
//
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 9, &stype);
//
//	m_Spread.SetRow(10);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[P101]"));
//	else
//		m_Spread.SetText(_T("%"));
//
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 10, &stype);
//
//	m_Spread.SetRow(11);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[N103,108]"));
//	else
//		m_Spread.SetText(_T("%"));
//
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 11, &stype);
//
//	m_Spread.SetRow(12);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[P103,108]"));
//	else
//		m_Spread.SetText(_T("%"));
//
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 12, &stype);
//
//	m_Spread.SetRow(13);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[N102,106,107,110,114,122,161~163]"));
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("pxl[N102,106,107,110,114,122,161~163]"));
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("pxl"));
//
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 13, &stype);
//
//	m_Spread.SetRow(14);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[P106,107,110,114,162]"));	//20120522-ndy mod
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("pxl[P106,107,110,114,162]"));	//20120522-ndy mod
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("pxl"));
//
//	m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(2, 14, &stype);
//
//
//	if (SpecData.nLineWidthGroupNum>0 && AoiParam()->m_bUseMultilineSpecEx)
//	{
//		m_Spread.SetRow(15);
//		m_Spread.SetCellType(TYPE_STATIC);
//		if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//			m_Spread.SetText(_T("um[N105,P105]"));
//		else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//			m_Spread.SetText(_T("pxl[N105,P105]"));
//		else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//			m_Spread.SetText(_T("um"));
//		else
//			m_Spread.SetText(_T("pxl"));
//
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(2, 15, &stype);
//	}
//	else
//	{
//		m_Spread.SetRow(15);
//		m_Spread.SetCellType(TYPE_STATIC);
//		if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//			m_Spread.SetText(_T("um[N105]"));
//		else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//			m_Spread.SetText(_T("pxl[N105]"));
//		else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//			m_Spread.SetText(_T("um"));
//		else
//			m_Spread.SetText(_T("pxl"));
//
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(2, 15, &stype);
//
//		m_Spread.SetRow(16);
//		m_Spread.SetCellType(TYPE_STATIC);
//		if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//			m_Spread.SetText(_T("um[P105]"));
//		else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//			m_Spread.SetText(_T("pxl[P105]"));
//		else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//			m_Spread.SetText(_T("um"));
//		else
//			m_Spread.SetText(_T("pxl"));
//
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_LEFT | SSS_ALIGN_VCENTER, 256, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(2, 16, &stype);
//	}
//
//
//	//-------------------------------------------------------
//	m_Spread.SetCellBorder(-1, -1, -1, -1, SS_BORDERTYPE_BOTTOM | SS_BORDERTYPE_RIGHT, RGB(180, 180, 180), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_LEFT | SS_BORDERTYPE_TOP | SS_BORDERTYPE_BOTTOM, RGB(180, 180, 180), SS_BORDERSTYLE_NONE); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_RIGHT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//																								   // Draw Cell Boarder
//	m_Spread.SetCellBorder(0, 2, 2, 2, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 7, 2, 7, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 12, 2, 12, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 14, 2, 14, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 16, 2, 16, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(2, -1, 2, -1, SS_BORDERTYPE_LEFT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//																								  //Set Color Group
//	for (int iCol = 1; iCol <= 2; iCol++)
//	{
//		m_Spread.SetCol(iCol);
//
//		m_Spread.SetRow(1);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(2);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//
//		m_Spread.SetRow(3);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(4);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(5);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(6);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(7);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//
//		m_Spread.SetRow(8);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(9);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(10);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(11);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(12);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//
//		m_Spread.SetRow(13);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(14);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//
//		m_Spread.SetRow(15);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
//
//		m_Spread.SetRow(16);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
//	}
}

void CDlgSpec::InitSpreadTab2()
{
//	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
//	// Initialize Tab ctrl for information viewer
//	m_tabDlgInspection.HighlightItem(m_nTabNum, FALSE);
//
//	//Tab Index
//	m_nTabNum = 2;
//	m_tabDlgInspection.HighlightItem(m_nTabNum, TRUE);
//
//	//m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//	SS_CELLTYPE stype;
//
//	m_Spread.SetReDraw(FALSE);
//	InitSpread();
//
//	m_Spread.SetTypeEdit(&stype, 0, 128, SS_CHRSET_CHR, SS_CASE_NOCASE);
//	m_Spread.SetCellType(SS_ALLCOLS, SS_ALLROWS, &stype);
//
//
//	//Column Width twip
//	m_Spread.SetMaxCols(2);
//	m_Spread.SetMaxRows(9);	//121226 hjc add
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//#if WIN_OS == WIN_10
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		//HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(1, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize + 2, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(2, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//
//		m_Spread.SetFont(3, SS_ALLROWS, hfont, TRUE);
//
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//
//#else
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//#endif
//	// ?EΩ√Ω∫≈€¿« «»ºø¥ÅETwips∞™¿ª ∆ƒæ««—¥Ÿ.
//	CDC* pDC = GetDC();
//	int nLogX = pDC->GetDeviceCaps(LOGPIXELSX);
//	ReleaseDC(pDC);
//	int nTwipPerPixel = 1440 / nLogX;
//
//	// ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	CRect rect;
//	m_Spread.GetClientRect(rect);
//	long twpWidth = (rect.right - rect.left);
//
//	// Ω∫«¡∑πµÂ¿« ∆¯¿ª  Column Width¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadWidth, EachColWidth;
//	m_Spread.LogUnitsToColWidth(twpWidth, &fSpreadWidth);
//
//	if (AoiParam()->m_bSetSpecLocking)
//	{
//		m_Spread.SetColWidth(0, 34);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 28);	//140314 hjc mod
//	}
//	else
//	{
//		m_Spread.SetColWidth(0, 32);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 26);	//140314 hjc mod
//	}
//	EachColWidth = (float)(fSpreadWidth - (m_Spread.GetColWidth(0)
//		+ m_Spread.GetColWidth(2)) - 0.5);
//	m_Spread.SetColWidth(1, EachColWidth);
//
//	m_Spread.SetRowHeight(0, 5); // COL(0)'S HEIGHT
//
//								 // ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	long twpHeight = (rect.bottom - rect.top);
//
//	// Ω∫«¡∑πµÂ¿« ≥Ù¿Ã∏¶ Row Height¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadHeight;//, EachRowHeight
//
//	long nRow;
//	m_Spread.LogUnitsToRowHeight(0, twpHeight, &fSpreadHeight);
//	double dSepHeight = (fSpreadHeight - 10) / max(1, m_Spread.GetMaxRows() + 1);
//	for (nRow = 1; nRow <= m_Spread.GetMaxRows(); nRow++)
//	{
//
//		m_Spread.SetRowHeight(nRow, dSepHeight);
//	}
//
//	//Column Caption
//	m_Spread.SetRow(0);
//
//	m_Spread.SetCol(1);
//	m_Spread.SetText(_T(" "));
//	m_Spread.SetCol(2);
//	m_Spread.SetText(_T(" "));
//
//	//«Ï¥ı ƒ¡∆Æ∑—
//	//	SS_CELLTYPE stype;
//	m_Spread.SetTypeStaticText(&stype, SS_TEXT_SHADOW | SS_TEXT_VCENTER | SS_TEXT_RIGHT);
//	m_Spread.SetCellType(SS_HEADER, SS_ALLROWS, &stype);
//
//
//	ChangeSpecSpreadCaption(2);
//	m_Spread.SetCellBorder(-1, -1, -1, -1, SS_BORDERTYPE_BOTTOM | SS_BORDERTYPE_RIGHT, RGB(180, 180, 180), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//																																  //Arrange All Cells with Vertical Center.
//	for (int iRow = 1; iRow <= m_Spread.GetMaxRows(); iRow++)
//	{
//		m_Spread.SetRow(iRow);
//
//		m_Spread.SetCol(1);
//		m_Spread.SetCellType(TYPE_DEFAULT);
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_VCENTER | SSS_ALIGN_CENTER, 128, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(SS_ALLCOLS, iRow, &stype);
//		m_Spread.SetFontBold(TRUE);
//		m_Spread.SetFontSize(m_fDataFontSize);
//		if (m_bMasterLocalFlag[2][iRow - 1] && pGlobalDoc->m_bDefaultSpecFlag)
//			m_Spread.SetForeColor(RGB(58, 53, 151));
//		else
//			m_Spread.SetForeColor(RGB(60, 145, 103));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//		m_Spread.SetLock(FALSE);
//
//		m_Spread.SetCol(2);
//		m_Spread.SetCellType(TYPE_STATIC);
//		//m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER );
//		//m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//		m_Spread.SetFontBold(TRUE);
//		m_Spread.SetFontSize(m_fDataFontSize);
//		m_Spread.SetForeColor(RGB(0, 0, 0));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//
//		// Clear Cell Boarder
//		m_Spread.SetCellBorder(0, iRow, 2, iRow, 8, -1, 0); // Bottom Line - Default Style.
//	}
//
//	m_bEnableCheckBox = FALSE;
//
//	// Clear Spread Sheet
//	m_Spread.ClearRange(1, 1, m_Spread.GetMaxCols(), m_Spread.GetMaxRows(), TRUE);
//
//	//150611 hjc add
//	if (pGlobalDoc->m_bUseCombo)
//	{
//		// ComboBox in Cell
//		m_Spread.SetCol(1);
//
//		m_Spread.SetRow(5);
//		m_Spread.SetCellType(TYPE_COMBO);
//#if LANGUAGE == ENGLISH
//		m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//#elif LANGUAGE == KOREAN
//		m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//#elif LANGUAGE == JAPANESE
//		m_Spread.SetTypeComboBoxList(_T("Highest    (90%)\tVeryHigh   (80%)\tHigh        (70%)\tNormal     (60%)\tLow         (50%)\tVeryLow   (40%)\tLowest     (30%)"));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//#endif
//		m_Spread.SetTypeComboBoxEditable(TRUE);
//		m_Spread.SetTypeComboBoxMaxDrop(10);
//		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//	}
//
//	// Static in Cell
//	m_Spread.SetCol(2);
//
//	CString strData;
//
//	m_Spread.SetRow(1);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)	//140314 hjc add
//	{
//		strData.Format(_T("DN[ST,S44](%d~%d)"), pGlobalDoc->m_nSpecSpaceGrayLowerLimit, pGlobalDoc->m_nSpecSpaceGrayUpperLimit);  //20200102 mod
//		m_Spread.SetText(strData);
//	}
//	else
//	{
//		strData.Format(_T("DN(%d~%d)"), pGlobalDoc->m_nSpecSpaceGrayLowerLimit, pGlobalDoc->m_nSpecSpaceGrayUpperLimit);
//		m_Spread.SetText(strData);
//	}
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(2);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)	//20100210 hjc mod
//		m_Spread.SetText(_T("DN[S20~22,24,27,30,31,40,41]"));	//20200102 mod
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	//150413 hjc add
//	m_Spread.SetRow(3);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)	//20100210 hjc mod
//		m_Spread.SetText(_T("DN[S15,17,23,25,26]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(4);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[S4,EP275,Hd25]"));		//20101013 hjc mod		//20230629 add ,EP275,Hd25
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("um[S4,EP275,Hd25]"));	//20101013 hjc mod
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(5);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[S1,5,6,7]"));
//	else
//		m_Spread.SetText(_T("%"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(6);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[S3,8,58,71,570]"));	//20200102 mod
//	else
//		m_Spread.SetText(_T("%"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(7);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[S18,19,45,50,54,57,70,83,570]"));	//20200102 mod
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("pxl[S18,19,45,50,54,57,70,83,570]"));	// 20110715 ? check
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(8);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[S52]"));
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("pxl[S52]"));
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(9);		//121226 hjc add
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[S104]"));		//20101013 hjc mod
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("um[S104]"));	//20101013 hjc mod
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("um"));
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	// Draw Cell Boarder
//	//	m_Spread.SetCellBorder(2,-1,2,-1, SS_BORDERTYPE_LEFT | SS_BORDERTYPE_RIGHT | SS_BORDERTYPE_TOP | SS_BORDERTYPE_BOTTOM ,RGB(0,0,0),SS_BORDERSTYLE_SOLID ); // Bottom Line - Solid Style.
//	//m_Spread.SetCellBorder(2,-1,2,-1, SS_BORDERTYPE_TOP | SS_BORDERTYPE_BOTTOM ,RGB(180,180,180),SS_BORDERSTYLE_SOLID ); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_LEFT | SS_BORDERTYPE_TOP | SS_BORDERTYPE_BOTTOM, RGB(180, 180, 180), SS_BORDERSTYLE_NONE); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_RIGHT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//
//	m_Spread.SetCellBorder(0, 3, 2, 3, 8, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 6, 2, 6, 8, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 8, 2, 8, 8, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 9, 2, 9, 8, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID);
//	m_Spread.SetCellBorder(2, -1, 2, -1, SS_BORDERTYPE_LEFT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//																								  //	m_Spread.SetCellBorder(2,-1,2,-1, SS_BORDERTYPE_LEFT | SS_BORDERTYPE_RIGHT | SS_BORDERTYPE_TOP | SS_BORDERTYPE_BOTTOM ,RGB(0,0,0),SS_BORDERSTYLE_SOLID ); // Bottom Line - Solid Style.
//
//																								  //Set Color Group
//	for (int iCol = 1; iCol <= 2; iCol++)
//	{
//		m_Spread.SetCol(iCol);
//
//		m_Spread.SetRow(1);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(2);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(3);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//
//		m_Spread.SetRow(4);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(5);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(6);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//
//		m_Spread.SetRow(7);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(8);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//
//		m_Spread.SetRow(9);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//	}
}

void CDlgSpec::InitSpreadTab3()
{
//	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
//	// Initialize Tab ctrl for information viewer
//	m_tabDlgInspection.HighlightItem(m_nTabNum, FALSE);
//
//	//Tab Index
//	m_nTabNum = 3;
//	m_tabDlgInspection.HighlightItem(m_nTabNum, TRUE);
//
//	m_Spread.SetReDraw(FALSE);
//	InitSpread();
//	//Column Width twip
//	m_Spread.SetMaxCols(2);
//
//	//2022 01 10 lgh ad
//	if (SpecData.bEnableCharInspection)
//		m_Spread.SetMaxRows(15);	//jun 20120903 for LG_CCL-Inspector
//	else
//		m_Spread.SetMaxRows(12);	//jun 20120903 for LG_CCL-Inspector
//
//
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//#if WIN_OS == WIN_10
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		//HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(1, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize + 2, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(2, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//
//		m_Spread.SetFont(3, SS_ALLROWS, hfont, TRUE);
//
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//
//#else
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//#endif
//
//	// ?EΩ√Ω∫≈€¿« «»ºø¥ÅETwips∞™¿ª ∆ƒæ««—¥Ÿ.
//	CDC* pDC = GetDC();
//	int nLogX = pDC->GetDeviceCaps(LOGPIXELSX);
//	ReleaseDC(pDC);
//	int nTwipPerPixel = 1440 / nLogX;
//
//	// ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	CRect rect;
//	m_Spread.GetClientRect(rect);
//	long twpWidth = (rect.right - rect.left);
//
//	// Ω∫«¡∑πµÂ¿« ∆¯¿ª  Column Width¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadWidth, EachColWidth;
//	m_Spread.LogUnitsToColWidth(twpWidth, &fSpreadWidth);
//
//	if (AoiParam()->m_bSetSpecLocking)
//	{
//
//		m_Spread.SetColWidth(0, 35);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 22);	//140314 hjc mod
//	}
//	else
//	{
//		m_Spread.SetColWidth(0, 32);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 26);	//140314 hjc mod
//	}
//	EachColWidth = (float)(fSpreadWidth - (m_Spread.GetColWidth(0)
//		+ m_Spread.GetColWidth(2)) - 0.5);
//	m_Spread.SetColWidth(1, EachColWidth);
//
//	m_Spread.SetRowHeight(0, 5); // COL(0)'S HEIGHT
//
//								 // ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	long twpHeight = (rect.bottom - rect.top);
//
//	// Ω∫«¡∑πµÂ¿« ≥Ù¿Ã∏¶ Row Height¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadHeight;//, EachRowHeight
//	long nRow;
//	m_Spread.LogUnitsToRowHeight(0, twpHeight, &fSpreadHeight);
//	double dSepHeight = (fSpreadHeight - 10) / max(1, m_Spread.GetMaxRows() + 1);
//	for (nRow = 1; nRow <= m_Spread.GetMaxRows(); nRow++)
//	{
//		m_Spread.SetRowHeight(nRow, dSepHeight);
//	}
//
//	//Column Caption
//	m_Spread.SetRow(0);
//
//	m_Spread.SetCol(1);
//	m_Spread.SetText(_T(" "));
//	m_Spread.SetCol(2);
//	m_Spread.SetText(_T(" "));
//
//	//«Ï¥ı ƒ¡∆Æ∑—
//	SS_CELLTYPE stype;
//	m_Spread.SetTypeStaticText(&stype, SS_TEXT_SHADOW | SS_TEXT_VCENTER | SS_TEXT_RIGHT);
//	m_Spread.SetCellType(SS_HEADER, SS_ALLROWS, &stype);
//
//	ChangeSpecSpreadCaption(3);
//
//	//Arrange All Cells with Vertical Center.
//	for (int iRow = 1; iRow <= m_Spread.GetMaxRows(); iRow++)
//	{
//		m_Spread.SetRow(iRow);
//
//		m_Spread.SetCol(1);
//		m_Spread.SetCellType(TYPE_DEFAULT);
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_VCENTER | SSS_ALIGN_CENTER, 128, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(SS_ALLCOLS, iRow, &stype);
//
//		m_Spread.SetFontBold(TRUE);
//		m_Spread.SetFontSize(m_fDataFontSize);
//		if (m_bMasterLocalFlag[3][iRow - 1] && pGlobalDoc->m_bDefaultSpecFlag)
//			m_Spread.SetForeColor(RGB(58, 53, 151));
//		else
//			m_Spread.SetForeColor(RGB(60, 145, 103));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//		m_Spread.SetLock(FALSE);
//
//		m_Spread.SetCol(2);
//		m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//		m_Spread.SetFontBold(TRUE);
//		m_Spread.SetFontSize(m_fDataFontSize);	//20090309 hjc
//		m_Spread.SetForeColor(RGB(0, 0, 0));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//
//		// Clear Cell Boarder
//		m_Spread.SetCellBorder(0, iRow, 2, iRow, 8, -1, 0); // Bottom Line - Default Style.
//	}
//
//	m_bEnableCheckBox = FALSE;
//
//	// Clear Spread Sheet
//	m_Spread.ClearRange(1, 1, m_Spread.GetMaxCols(), m_Spread.GetMaxRows(), TRUE);
//
//	//jun 20120903 for LG_CCL-Inspector
//	if (!pGlobalDoc->m_bInspCCL[AoiParam()->m_nCurrentInspectionMode])
//	{
//		//Disable Cells
//		m_Spread.SetCol(1);
//
//		m_Spread.SetRow(10);
//		m_Spread.SetLock(TRUE);
//		m_Spread.SetForeColor(RGB(152, 152, 152));
//
//		m_Spread.SetRow(11);
//		m_Spread.SetLock(TRUE);
//		m_Spread.SetForeColor(RGB(152, 152, 152));
//
//		m_Spread.SetRow(12);
//		m_Spread.SetLock(TRUE);
//		m_Spread.SetForeColor(RGB(152, 152, 152));
//	}
//
//	// ComboBox in Cell
//	CString strComboDisp;
//	int nHighest, nVeryHigh, nHigh, nNormal, nLow, nVeryLow, nLowest;
//	m_Spread.SetCol(1);
//
//	m_Spread.SetRow(2);
//	m_Spread.SetCellType(TYPE_COMBO);
//
//	DecisionPixelAdjust(m_strLP_Prec, SpecData.LPADRL_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);
//	//160314 hjc relive
//	strComboDisp.Format(_T("Highest    (%d)\tVeryHigh   (%d)\tHigh        (%d)\tNormal     (%d)\tLow         (%d)\tVeryLow   (%d)\tLowest     (%d)"), nHighest, nVeryHigh, nHigh, nNormal, nLow, nVeryLow, nLowest);
//	//150624 hjc mod	//160314 hjc del
//	//	strComboDisp.Format("Highest    \tVeryHigh   \tHigh        \tNormal     \tLow         \tVeryLow   \tLowest     ");
//	m_Spread.SetTypeComboBoxList(strComboDisp);
//
//	m_Spread.SetTypeComboBoxEditable(TRUE);
//	m_Spread.SetTypeComboBoxMaxDrop(10);
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(5);
//	m_Spread.SetCellType(TYPE_COMBO);
//
//	//170112 hjc mod m_strSP_Prec -> SpecData.szSPRLName
//	DecisionPixelAdjust(m_strSP_Prec, SpecData.LSpaceRL_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);
//	//160314 hjc relive
//	strComboDisp.Format(_T("Highest    (%d)\tVeryHigh   (%d)\tHigh        (%d)\tNormal     (%d)\tLow         (%d)\tVeryLow   (%d)\tLowest     (%d)"), nHighest, nVeryHigh, nHigh, nNormal, nLow, nVeryLow, nLowest);
//	//150624 hjc mod
//	//strComboDisp.Format("Highest    \tVeryHigh   \tHigh        \tNormal     \tLow         \tVeryLow   \tLowest     ");
//	m_Spread.SetTypeComboBoxList(strComboDisp);
//
//	m_Spread.SetTypeComboBoxEditable(TRUE);
//	m_Spread.SetTypeComboBoxMaxDrop(10);
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	//170112 hjc add
//	m_Spread.SetRow(8);
//	m_Spread.SetCellType(TYPE_COMBO);
//
//	DecisionPixelAdjust(m_strSPExt_Prec, SpecData.SpaceExtRL_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);
//	strComboDisp.Format(_T("Highest    (%d)\tVeryHigh   (%d)\tHigh        (%d)\tNormal     (%d)\tLow         (%d)\tVeryLow   (%d)\tLowest     (%d)"), nHighest, nVeryHigh, nHigh, nNormal, nLow, nVeryLow, nLowest);
//	m_Spread.SetTypeComboBoxList(strComboDisp);
//
//	m_Spread.SetTypeComboBoxEditable(TRUE);
//	m_Spread.SetTypeComboBoxMaxDrop(10);
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//	//170112 hjc mod end
//
//	// Static in Cell
//	m_Spread.SetCol(2);
//	m_Spread.SetFontBold(TRUE);
//	m_Spread.SetFontSize(m_fDataFontSize);
//
//	m_Spread.SetRow(1);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[PH1]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(2);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("pxl[PH1]"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(3);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[PH1]"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(4);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[IS1]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(5);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("pxl[IS1]"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(6);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[IS1]"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	//20090412 hjc
//	m_Spread.SetRow(7);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[IS2]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	//170112 hjc add
//	m_Spread.SetRow(8);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("pxl[IS2]"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(9);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[IS2]"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(10);		//CCL gray
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[PH10]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(11);		//size, pixel
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("PH10"));
//	else
//		m_Spread.SetText(_T(""));
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(12);		//Circularity
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("pxl[PH10]"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//	//--------------
//
//	//2022 01 10 LGH ADD
//	if (SpecData.bEnableCharInspection)
//	{
//		m_Spread.SetRow(13);		//Circularity
//		m_Spread.SetCellType(TYPE_STATIC);
//		if (pGlobalDoc->m_bDisplayKValue)
//			m_Spread.SetText(_T("DN[PD61,62]"));
//		else
//			m_Spread.SetText(_T("DN"));
//		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//		m_Spread.SetRow(14);		//Circularity
//		m_Spread.SetCellType(TYPE_STATIC);
//		if (pGlobalDoc->m_bDisplayKValue)
//			m_Spread.SetText(_T("%[PD61]"));
//		else
//			m_Spread.SetText(_T("%"));
//		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//		m_Spread.SetRow(15);		//Circularity
//		m_Spread.SetCellType(TYPE_STATIC);
//		if (pGlobalDoc->m_bDisplayKValue)
//			m_Spread.SetText(_T("%[PD62]"));
//		else
//			m_Spread.SetText(_T("%"));
//		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	}
//
//
//	m_Spread.SetCellBorder(-1, -1, -1, -1, SS_BORDERTYPE_BOTTOM | SS_BORDERTYPE_RIGHT, RGB(180, 180, 180), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_LEFT | SS_BORDERTYPE_TOP | SS_BORDERTYPE_BOTTOM, RGB(180, 180, 180), SS_BORDERSTYLE_NONE); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_RIGHT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//																								   // Draw Cell Boarder
//	m_Spread.SetCellBorder(0, 3, 2, 3, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 9, 2, 9, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.	
//	m_Spread.SetCellBorder(0, 12, 2, 12, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.	//jun 20120903 for LG_CCL-Inspector
//	m_Spread.SetCellBorder(2, -1, 2, -1, SS_BORDERTYPE_LEFT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//
//																								  //Set Color Group
//	for (int iCol = 1; iCol <= 2; iCol++)
//	{
//		m_Spread.SetCol(iCol);
//
//		m_Spread.SetRow(1);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(2);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(3);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//
//		m_Spread.SetRow(4);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(5);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(6);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(7);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(8);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(9);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//
//		m_Spread.SetRow(10);	//jun 20120903 for LG_CCL-Inspector
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(11);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(12);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//
//		//2022 01 10 lgh 
//		if (SpecData.bEnableCharInspection)
//		{
//			m_Spread.SetRow(13);	//jun 20120903 for LG_CCL-Inspector
//			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//			m_Spread.SetRow(14);
//			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//			m_Spread.SetRow(15);
//			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//
//		}
//
//	}
}

void CDlgSpec::InitSpreadTab4()
{
//	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
//	// Initialize Tab ctrl for information viewer
//	m_tabDlgInspection.HighlightItem(m_nTabNum, FALSE);
//
//	//Tab Index
//	m_nTabNum = 4;
//	m_tabDlgInspection.HighlightItem(m_nTabNum, TRUE);
//
//	m_Spread.SetReDraw(FALSE);
//	InitSpread();
//	//Column Width twip
//	m_Spread.SetMaxCols(2);
//	m_Spread.SetMaxRows(22);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//#if WIN_OS == WIN_10
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		//HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(1, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize + 2, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(2, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//
//		m_Spread.SetFont(3, SS_ALLROWS, hfont, TRUE);
//
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//
//#else
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//#endif
//	// ?EΩ√Ω∫≈€¿« «»ºø¥ÅETwips∞™¿ª ∆ƒæ««—¥Ÿ.
//	CDC* pDC = GetDC();
//	int nLogX = pDC->GetDeviceCaps(LOGPIXELSX);
//	ReleaseDC(pDC);
//	int nTwipPerPixel = 1440 / nLogX;
//
//	// ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	CRect rect;
//	m_Spread.GetClientRect(rect);
//	long twpWidth = (rect.right - rect.left);
//
//	// Ω∫«¡∑πµÂ¿« ∆¯¿ª  Column Width¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadWidth, EachColWidth;
//	m_Spread.LogUnitsToColWidth(twpWidth, &fSpreadWidth);
//
//	if (AoiParam()->m_bSetSpecLocking)
//	{
//		m_Spread.SetColWidth(0, 40);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 19);	//140314 hjc mod
//	}
//	else
//	{
//		m_Spread.SetColWidth(0, 32);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 25);	//140314 hjc mod
//	}
//
//	EachColWidth = (float)(fSpreadWidth - (m_Spread.GetColWidth(0)
//		+ m_Spread.GetColWidth(2)) - 0.5);
//	m_Spread.SetColWidth(1, EachColWidth);
//
//	m_Spread.SetRowHeight(0, 5); // COL(0)'S HEIGHT
//
//								 // ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	long twpHeight = (rect.bottom - rect.top);
//
//	// Ω∫«¡∑πµÂ¿« ≥Ù¿Ã∏¶ Row Height¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadHeight;//, EachRowHeight
//	long nRow;
//	m_Spread.LogUnitsToRowHeight(0, twpHeight, &fSpreadHeight);
//	double dSepHeight = (fSpreadHeight - 10) / max(1, m_Spread.GetMaxRows() + 1);
//	for (nRow = 1; nRow <= m_Spread.GetMaxRows(); nRow++)
//	{
//
//		m_Spread.SetRowHeight(nRow, dSepHeight);
//	}
//
//	//Column Caption
//	m_Spread.SetRow(0);
//
//	m_Spread.SetCol(1);
//	m_Spread.SetText(_T(" "));
//	m_Spread.SetCol(2);
//	m_Spread.SetText(_T(" "));
//
//	//«Ï¥ı ƒ¡∆Æ∑—
//	SS_CELLTYPE stype;
//	m_Spread.SetTypeStaticText(&stype, SS_TEXT_SHADOW | SS_TEXT_VCENTER | SS_TEXT_RIGHT);
//	m_Spread.SetCellType(SS_HEADER, SS_ALLROWS, &stype);
//
//
//	ChangeSpecSpreadCaption(4);
//
//	//Arrange All Cells with Vertical Center.
//	for (int iRow = 1; iRow <= m_Spread.GetMaxRows(); iRow++)
//	{
//		m_Spread.SetRow(iRow);
//
//		m_Spread.SetCol(1);
//		m_Spread.SetCellType(TYPE_DEFAULT);
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_VCENTER | SSS_ALIGN_CENTER, 128, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(SS_ALLCOLS, iRow, &stype);
//
//		m_Spread.SetFontBold(TRUE);
//		m_Spread.SetFontSize(m_fDataFontSize);
//		if (m_bMasterLocalFlag[4][iRow - 1] && pGlobalDoc->m_bDefaultSpecFlag)
//			m_Spread.SetForeColor(RGB(58, 53, 151));
//		else
//			m_Spread.SetForeColor(RGB(60, 145, 103));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//		m_Spread.SetLock(FALSE);
//
//		m_Spread.SetCol(2);
//		m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//		m_Spread.SetFontBold(TRUE);
//		m_Spread.SetFontSize(m_fDataFontSize);	//20090309 hjc
//		m_Spread.SetForeColor(RGB(0, 0, 0));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//
//		// Clear Cell Boarder
//		m_Spread.SetCellBorder(0, iRow, 2, iRow, 8, -1, 0); // Bottom Line - Default Style.
//	}
//
//	m_bEnableCheckBox = FALSE;
//
//	// Clear Spread Sheet
//	m_Spread.ClearRange(1, 1, m_Spread.GetMaxCols(), m_Spread.GetMaxRows(), TRUE);
//
//	// ComboBox in Cell
//	CString strComboDisp;
//	int nHighest, nVeryHigh, nHigh, nNormal, nLow, nVeryLow, nLowest;
//	m_Spread.SetCol(1);
//
//	m_Spread.SetRow(7);
//	m_Spread.SetCellType(TYPE_COMBO);
//
//	DecisionPixelAdjust(m_strPadBallPrec, SpecData.PADRL_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);
//	//160314 hjc relive
//	strComboDisp.Format(_T("Highest    (%d)\tVeryHigh   (%d)\tHigh        (%d)\tNormal     (%d)\tLow         (%d)\tVeryLow   (%d)\tLowest     (%d)"), nHighest, nVeryHigh, nHigh, nNormal, nLow, nVeryLow, nLowest);
//	//150624 hjc mod
//	//strComboDisp.Format("Highest    \tVeryHigh   \tHigh        \tNormal     \tLow         \tVeryLow   \tLowest     ");
//	m_Spread.SetTypeComboBoxList(strComboDisp);
//
//	m_Spread.SetTypeComboBoxEditable(TRUE);
//	m_Spread.SetTypeComboBoxMaxDrop(10);
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(9);
//	m_Spread.SetCellType(TYPE_COMBO);
//
//	//170112 hjc mod SpecData.szPADTipPrecName -> m_strPadTip_Prec
//	DecisionPixelAdjust(m_strPadTip_Prec, SpecData.PADTip_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);
//	//160314 hjc relive
//	strComboDisp.Format(_T("Highest    (%d)\tVeryHigh   (%d)\tHigh        (%d)\tNormal     (%d)\tLow         (%d)\tVeryLow   (%d)\tLowest     (%d)"), nHighest, nVeryHigh, nHigh, nNormal, nLow, nVeryLow, nLowest);
//	//150624 hjc mod
//	//strComboDisp.Format("Highest    \tVeryHigh   \tHigh        \tNormal     \tLow         \tVeryLow   \tLowest     ");
//	m_Spread.SetTypeComboBoxList(strComboDisp);
//
//	m_Spread.SetTypeComboBoxEditable(TRUE);
//	m_Spread.SetTypeComboBoxMaxDrop(10);
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(12);
//	m_Spread.SetCellType(TYPE_COMBO);
//	//170112 hjc mod m_strARLand_Prec -> SpecData.szARLandPrecName
//	DecisionPixelAdjust(m_strARLand_Prec, SpecData.ARLand_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);
//	//160314 hjc relive
//	strComboDisp.Format(_T("Highest    (%d)\tVeryHigh   (%d)\tHigh        (%d)\tNormal     (%d)\tLow         (%d)\tVeryLow   (%d)\tLowest     (%d)"), nHighest, nVeryHigh, nHigh, nNormal, nLow, nVeryLow, nLowest);
//	//150624 hjc mod
//	//strComboDisp.Format("Highest    \tVeryHigh   \tHigh        \tNormal     \tLow         \tVeryLow   \tLowest     ");
//	m_Spread.SetTypeComboBoxList(strComboDisp);
//
//	m_Spread.SetTypeComboBoxEditable(TRUE);
//	m_Spread.SetTypeComboBoxMaxDrop(10);
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(16);
//	m_Spread.SetCellType(TYPE_COMBO);
//	//170112 hjc mod m_strCO2Land_Prec -> SpecData.szCO2LandPrecName
//	DecisionPixelAdjust(m_strCO2Land_Prec, SpecData.CO2Land_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);
//	//160314 hjc relive
//	strComboDisp.Format(_T("Highest    (%d)\tVeryHigh   (%d)\tHigh        (%d)\tNormal     (%d)\tLow         (%d)\tVeryLow   (%d)\tLowest     (%d)"), nHighest, nVeryHigh, nHigh, nNormal, nLow, nVeryLow, nLowest);
//	//150624 hjc mod
//	//strComboDisp.Format("Highest    \tVeryHigh   \tHigh        \tNormal     \tLow         \tVeryLow   \tLowest     ");
//	m_Spread.SetTypeComboBoxList(strComboDisp);
//
//	m_Spread.SetTypeComboBoxEditable(TRUE);
//	m_Spread.SetTypeComboBoxMaxDrop(10);
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(18);
//	m_Spread.SetCellType(TYPE_COMBO);
//#if LANGUAGE == ENGLISH
//	strComboDisp.Format(_T("Yes\tNo"));
//	m_Spread.SetTypeComboBoxList(strComboDisp);
//#elif LANGUAGE == KOREAN
//	//	DecisionPixelAdjust(SpecData.szCO2LandAlignMode, SpecData.nCO2LandAlignMode, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);
//	strComboDisp.Format(_T("Yes\tNo"));
//	m_Spread.SetTypeComboBoxList(strComboDisp);
//#elif LANGUAGE == JAPANESE
//	//	DecisionPixelAdjust(SpecData.szCO2LandAlignMode, SpecData.nCO2LandAlignMode, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);	
//	strComboDisp.Format(_T("Yes\tNo"));
//	m_Spread.SetTypeComboBoxList(strComboDisp);
//#endif	
//	m_Spread.SetTypeComboBoxEditable(TRUE);
//	m_Spread.SetTypeComboBoxMaxDrop(10);
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(21);
//	m_Spread.SetCellType(TYPE_COMBO);
//
//	//170112 hjc mod m_strFPad_Prec -> SpecData.szPADFine_PrecName
//	DecisionPixelAdjust(m_strFPad_Prec, SpecData.PADFine_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);
//	//160314 hjc relive
//	strComboDisp.Format(_T("Highest    (%d)\tVeryHigh   (%d)\tHigh        (%d)\tNormal     (%d)\tLow         (%d)\tVeryLow   (%d)\tLowest     (%d)"), nHighest, nVeryHigh, nHigh, nNormal, nLow, nVeryLow, nLowest);
//	//150624 hjc mod
//	//strComboDisp.Format("Highest    \tVeryHigh   \tHigh        \tNormal     \tLow         \tVeryLow   \tLowest     ");
//	m_Spread.SetTypeComboBoxList(strComboDisp);
//
//	m_Spread.SetTypeComboBoxEditable(TRUE);
//	m_Spread.SetTypeComboBoxMaxDrop(10);
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	// Static in Cell
//	m_Spread.SetCol(2);
//	m_Spread.SetFontBold(TRUE);
//	m_Spread.SetFontSize(m_fDataFontSize);
//
//	m_Spread.SetRow(1);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[CD20,Vd31]"));	//20200903 add Vd31
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(2);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[CD10,Vd30]"));	//20200903 add Vd30
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	//20090419 hjc
//	m_Spread.SetRow(3);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[CD10]"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(4);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[CD10]"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(5);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[CD10,20,Vd30,31]"));	//20200903 add Vd30,31
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(6);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[PD1,200,201]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(7);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("pxl[PD1]"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(8);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[PD1]"));	//110706 hjc mod
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(9);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("pxl[10,11,200,201]"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(10);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[10,11,200,201]"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	//20100322 hjc add
//	m_Spread.SetRow(11);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[PD100]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(12);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("pxl[PD100]"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(13);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[PD100]"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(14);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[PD100]"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(15);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[PD20]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(16);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("pxl[PD20]"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(17);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[PD20]"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(19);	//20100323 hjc add
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[PD20]"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(20);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[PD10,11,40]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(21);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("pxl[PD40]"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(22);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[PD40]"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//	//--------------
//
//	m_Spread.SetCellBorder(-1, -1, -1, -1, SS_BORDERTYPE_BOTTOM | SS_BORDERTYPE_RIGHT, RGB(180, 180, 180), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_LEFT | SS_BORDERTYPE_TOP | SS_BORDERTYPE_BOTTOM, RGB(180, 180, 180), SS_BORDERSTYLE_NONE); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_RIGHT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//																								   // Draw Cell Boarder
//	m_Spread.SetCellBorder(0, 5, 2, 5, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 10, 2, 10, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 14, 2, 14, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.	
//	m_Spread.SetCellBorder(0, 19, 2, 19, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 22, 2, 22, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//
//	m_Spread.SetCellBorder(2, -1, 2, -1, SS_BORDERTYPE_LEFT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//
//																								  //Set Color Group
//	for (int iCol = 1; iCol <= 2; iCol++)
//	{
//		m_Spread.SetCol(iCol);
//
//		//20090311 hjc modify
//		m_Spread.SetRow(1);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(2);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(3);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(4);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(5);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//
//		m_Spread.SetRow(6);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(7);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(8);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(9);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(10);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//
//		m_Spread.SetRow(11);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(12);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(13);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(14);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//
//		m_Spread.SetRow(15);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(16);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(17);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(18);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(19);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//
//		m_Spread.SetRow(20);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
//		m_Spread.SetRow(21);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
//		m_Spread.SetRow(22);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
//	}
}

void CDlgSpec::InitSpreadTab5()
{
//	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
//	// Initialize Tab ctrl for information viewer
//	m_tabDlgInspection.HighlightItem(m_nTabNum, FALSE);
//
//	//Tab Index
//	m_nTabNum = 5;
//	m_tabDlgInspection.HighlightItem(m_nTabNum, TRUE);
//
//	m_Spread.SetReDraw(FALSE);
//	InitSpread();
//	//Column Width twip
//	m_Spread.SetMaxCols(2);
//	m_Spread.SetMaxRows(18);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//#if WIN_OS == WIN_10
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		//HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(1, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize + 2, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(2, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//
//		m_Spread.SetFont(3, SS_ALLROWS, hfont, TRUE);
//
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//
//#else
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//#endif
//
//	// ?EΩ√Ω∫≈€¿« «»ºø¥ÅETwips∞™¿ª ∆ƒæ««—¥Ÿ.
//	CDC* pDC = GetDC();
//	int nLogX = pDC->GetDeviceCaps(LOGPIXELSX);
//	ReleaseDC(pDC);
//	int nTwipPerPixel = 1440 / nLogX;
//
//	// ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	CRect rect;
//	m_Spread.GetClientRect(rect);
//	long twpWidth = (rect.right - rect.left);
//
//	// Ω∫«¡∑πµÂ¿« ∆¯¿ª  Column Width¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadWidth, EachColWidth;
//	m_Spread.LogUnitsToColWidth(twpWidth, &fSpreadWidth);
//
//	if (AoiParam()->m_bSetSpecLocking)
//	{
//		m_Spread.SetColWidth(0, 39);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 20);	//140314 hjc mod
//	}
//	else
//	{
//		m_Spread.SetColWidth(0, 32);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 25);	//140314 hjc mod
//	}
//	EachColWidth = (float)(fSpreadWidth - (m_Spread.GetColWidth(0)
//		+ m_Spread.GetColWidth(2)) - 0.5);
//	m_Spread.SetColWidth(1, EachColWidth);
//
//	m_Spread.SetRowHeight(0, 5); // COL(0)'S HEIGHT
//	m_Spread.SetBool(SSB_SHOWCOLHEADERS, 1);
//	// ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	long twpHeight = (rect.bottom - rect.top);
//
//	// Ω∫«¡∑πµÂ¿« ≥Ù¿Ã∏¶ Row Height¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadHeight;//, EachRowHeight
//	long nRow;
//	m_Spread.LogUnitsToRowHeight(0, twpHeight, &fSpreadHeight);
//	double dSepHeight = (fSpreadHeight - 10) / max(1, m_Spread.GetMaxRows() + 1);
//	for (nRow = 1; nRow <= m_Spread.GetMaxRows(); nRow++)
//	{
//
//		m_Spread.SetRowHeight(nRow, dSepHeight);
//	}
//
//	//Column Caption
//	m_Spread.SetRow(0);
//
//	m_Spread.SetCol(1);
//	m_Spread.SetText(_T(" "));
//	m_Spread.SetCol(2);
//	m_Spread.SetText(_T(" "));
//
//	//«Ï¥ı ƒ¡∆Æ∑—
//	SS_CELLTYPE stype;
//	m_Spread.SetTypeStaticText(&stype, SS_TEXT_SHADOW | SS_TEXT_VCENTER | SS_TEXT_RIGHT);
//	m_Spread.SetCellType(SS_HEADER, SS_ALLROWS, &stype);
//
//	ChangeSpecSpreadCaption(5);
//
//	//Arrange All Cells with Vertical Center.
//	for (int iRow = 1; iRow <= m_Spread.GetMaxRows(); iRow++)
//	{
//		m_Spread.SetRow(iRow);
//
//		m_Spread.SetCol(1);
//		m_Spread.SetCellType(TYPE_DEFAULT);
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_VCENTER | SSS_ALIGN_CENTER, 128, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(SS_ALLCOLS, iRow, &stype);
//
//		m_Spread.SetFontBold(TRUE);
//		m_Spread.SetFontSize(m_fDataFontSize);
//		if (m_bMasterLocalFlag[0][iRow - 1] && pGlobalDoc->m_bDefaultSpecFlag)
//			m_Spread.SetForeColor(RGB(58, 53, 151));
//		else
//			m_Spread.SetForeColor(RGB(60, 145, 103));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//		m_Spread.SetLock(FALSE);
//
//		m_Spread.SetCol(2);
//		m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//		m_Spread.SetFontBold(TRUE);
//		m_Spread.SetFontSize(m_fDataFontSize);
//		m_Spread.SetForeColor(RGB(0, 0, 0));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//
//		// Clear Cell Boarder
//		m_Spread.SetCellBorder(0, iRow, 2, iRow, 8, -1, 0); // Bottom Line - Default Style.
//	}
//
//	m_bEnableCheckBox = FALSE;
//
//	// Clear Spread Sheet
//	m_Spread.ClearRange(1, 1, m_Spread.GetMaxCols(), m_Spread.GetMaxRows(), TRUE);
//
//	// ComboBox in Cell
//	m_Spread.SetCol(1);
//
//	m_Spread.SetRow(7);
//	m_Spread.SetCellType(TYPE_COMBO);
//
//	//	m_Spread.SetTypeComboBoxList (_T("Highest    (-1)\tVeryHigh   (-2)\tHigh        (-3)\tNormal     (-4)\tLow         (-5)\tVeryLow   (-6)\tLowest     (-7)");//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//	//150624 hjc mod
//	m_Spread.SetTypeComboBoxList(_T("Highest    \tVeryHigh   \tHigh        \tNormal     \tLow         \tVeryLow   \tLowest     "));//"90%\t80%\t70%\t60%\t50%\t40%\t30%"
//
//	m_Spread.SetTypeComboBoxEditable(TRUE);
//	m_Spread.SetTypeComboBoxMaxDrop(10);
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(9);
//	m_Spread.SetCellType(TYPE_COMBO);
//#if LANGUAGE == ENGLISH
//	m_Spread.SetTypeComboBoxList(_T("AreaMode\tEdgeMode"));
//#elif LANGUAGE == KOREAN
//	m_Spread.SetTypeComboBoxList(_T("AreaMode\tEdgeMode"));
//#elif LANGUAGE == JAPANESE
//	m_Spread.SetTypeComboBoxList(_T("AreaMode\tEdgeMode"));
//#endif
//	m_Spread.SetTypeComboBoxEditable(TRUE);
//	m_Spread.SetTypeComboBoxMaxDrop(10);
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	CString temp;
//	temp.Format(_T("%s"), CharToString(SpecData.szVHMode));
//
//	//20090311 hjc add
//	if (temp == "AreaMode")
//	{
//		//Disable Cells
//		m_Spread.SetCol(1);
//
//		m_Spread.SetRow(15);
//		//m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetLock(TRUE);
//		m_Spread.SetForeColor(RGB(152, 152, 152));
//
//		m_Spread.SetRow(16);
//		//m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetLock(TRUE);
//		m_Spread.SetForeColor(RGB(152, 152, 152));
//
//		//Temperary 2006.10.13 -----------------------------------
//		m_Spread.SetRow(17);
//		//m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetLock(TRUE);
//		m_Spread.SetForeColor(RGB(152, 152, 152));
//
//		m_Spread.SetRow(18);
//		//m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetLock(TRUE);
//		m_Spread.SetForeColor(RGB(152, 152, 152));
//	}
//	//------------
//
//	// Static in Cell
//	m_Spread.SetCol(2);
//
//	m_Spread.SetRow(1);
//	m_Spread.SetCellType(TYPE_STATIC);
//	//20090228 hjc modify
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[HL4,HM42,VL4]"));	//20230630 add VL4
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(2);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[HD2,CD2]")); //[HM32,HL3]	//20230629 add ,CD2
//	else
//		m_Spread.SetText(_T("%"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(3);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[HD3,CD3]"));		//20230629 add ,CD3
//	else
//		m_Spread.SetText(_T("%"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(4);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[HM2,VO0,HD4]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(5);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[L3,5,M1,2,32,42,52]"));	//HM32,42,52
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(6);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[HD0]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(7);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("pxl[HD0]"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(8);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[HD0]"));
//	else
//		m_Spread.SetText(_T("%"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//	//--------------------	
//
//	m_Spread.SetRow(9);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T("  "));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(10);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[VM0,10,VL1,2]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(11);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("pxl[VM0]"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(12);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[OP4]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(13);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[VM0,10,VL0,1]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(14);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("%[VL1, VL12]"));	//20230630 add
//	else
//		m_Spread.SetText(_T("%"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(15);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[VM0,VL1,2]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(16);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[VL1,2]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(17);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[VL1,2]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(18);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("EA[VL4]"));
//	else
//		m_Spread.SetText(_T("EA"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//
//	m_Spread.SetCellBorder(-1, -1, -1, -1, SS_BORDERTYPE_BOTTOM | SS_BORDERTYPE_RIGHT, RGB(180, 180, 180), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_LEFT | SS_BORDERTYPE_TOP | SS_BORDERTYPE_BOTTOM, RGB(180, 180, 180), SS_BORDERSTYLE_NONE); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_RIGHT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//																								   // Draw Cell Boarder
//	m_Spread.SetCellBorder(0, 3, 2, 3, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 5, 2, 5, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 8, 2, 8, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 18, 2, 18, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(2, -1, 2, -1, SS_BORDERTYPE_LEFT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//																								  //Set Color Group
//	for (int iCol = 1; iCol <= 2; iCol++)
//	{
//		m_Spread.SetCol(iCol);
//
//		m_Spread.SetRow(1);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(2);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(3);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//
//		m_Spread.SetRow(4);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(5);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//
//		m_Spread.SetRow(6);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(7);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(8);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//
//		m_Spread.SetRow(9);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(10);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(11);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(12);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(13);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(14);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(15);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(16);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(17);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(18);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//	}
}

void CDlgSpec::InitSpreadTab6()
{
//	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
//	// Initialize Tab ctrl for information viewer
//	m_tabDlgInspection.HighlightItem(m_nTabNum, FALSE);
//
//	//Tab Index
//	m_nTabNum = 6;
//	m_tabDlgInspection.HighlightItem(m_nTabNum, TRUE);
//
//	m_Spread.SetReDraw(FALSE);
//	InitSpread();
//	//Column Width twip
//	m_Spread.SetMaxCols(2);
//	m_Spread.SetMaxRows(15);	//111214 hjc mod
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//#if WIN_OS == WIN_10
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		//HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(1, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize + 2, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(2, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//
//		m_Spread.SetFont(3, SS_ALLROWS, hfont, TRUE);
//
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//
//#else
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//#endif
//	// ?EΩ√Ω∫≈€¿« «»ºø¥ÅETwips∞™¿ª ∆ƒæ««—¥Ÿ.
//	CDC* pDC = GetDC();
//	int nLogX = pDC->GetDeviceCaps(LOGPIXELSX);
//	ReleaseDC(pDC);
//	int nTwipPerPixel = 1440 / nLogX;
//
//	// ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	CRect rect;
//	m_Spread.GetClientRect(rect);
//	long twpWidth = (rect.right - rect.left);
//
//	// Ω∫«¡∑πµÂ¿« ∆¯¿ª  Column Width¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadWidth, EachColWidth;
//	m_Spread.LogUnitsToColWidth(twpWidth, &fSpreadWidth);
//
//	if (AoiParam()->m_bSetSpecLocking)
//	{
//		m_Spread.SetColWidth(0, 35);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 22);	//140314 hjc mod
//	}
//	else
//	{
//		m_Spread.SetColWidth(0, 32);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 26);	//140314 hjc mod
//	}
//	EachColWidth = (float)(fSpreadWidth - (m_Spread.GetColWidth(0)
//		+ m_Spread.GetColWidth(2)) - 0.5);
//	m_Spread.SetColWidth(1, EachColWidth);
//
//	m_Spread.SetRowHeight(0, 5); // COL(0)'S HEIGHT
//
//								 // ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	long twpHeight = (rect.bottom - rect.top);
//
//	// Ω∫«¡∑πµÂ¿« ≥Ù¿Ã∏¶ Row Height¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadHeight;//, EachRowHeight
//	long nRow;
//	m_Spread.LogUnitsToRowHeight(0, twpHeight, &fSpreadHeight);
//	double dSepHeight = (fSpreadHeight - 10) / max(1, m_Spread.GetMaxRows() + 1);
//	for (nRow = 1; nRow <= m_Spread.GetMaxRows(); nRow++)
//	{
//
//		m_Spread.SetRowHeight(nRow, dSepHeight);
//	}
//
//	//Column Caption
//	m_Spread.SetRow(0);
//
//	m_Spread.SetCol(1);
//	m_Spread.SetText(_T(" "));
//	m_Spread.SetCol(2);
//	m_Spread.SetText(_T(" "));
//
//	//«Ï¥ı ƒ¡∆Æ∑—
//	SS_CELLTYPE stype;
//	m_Spread.SetTypeStaticText(&stype, SS_TEXT_SHADOW | SS_TEXT_VCENTER | SS_TEXT_RIGHT);
//	m_Spread.SetCellType(SS_HEADER, SS_ALLROWS, &stype);
//
//
//	ChangeSpecSpreadCaption(6);
//
//
//	// #elif LANGUAGE == KOREAN
//	// 	m_Spread.SetRow(1);
//	// 	m_Spread.SetText(_T("PAD          Edge∞·º’π‡±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(2);
//	// 	m_Spread.SetText(_T("Edgeµß∆Æπ‡±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(3);
//	// 	m_Spread.SetText(_T("Edgeµπ±‚π‡±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(4);
//	// 	m_Spread.SetText(_T("Edge∫Ø»≠(∞·º’)≈©±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(5);
//	// 	m_Spread.SetText(_T("Edge∫Ø»≠(µπ±ÅE≈©±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(6);
//	// 	//m_Spread.SetText(_T("∞·º’HLG(∞·º’-µß∆Æ)"));    // 20090301 ljg
//	// 	m_Spread.SetText(_T("(µß∆Æ/∞·º’)ø°¡ˆº±∆¯∫ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(7);
//	// 	m_Spread.SetText(_T("HOLE          Edge∞·º’π‡±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(8);
//	// 	m_Spread.SetText(_T("Edgeµß∆Æπ‡±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(9);
//	// 	m_Spread.SetText(_T("Edgeµπ±‚π‡±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(10);
//	// 	m_Spread.SetText(_T("Edge∫Ø»≠(∞·º’)≈©±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(11);
//	// 	m_Spread.SetText(_T("Edge∫Ø»≠(µπ±ÅE≈©±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(12);
//	// 	//m_Spread.SetText(_T("∞·º’HLG(∞·º’-µß∆Æ)"));    // 20090301 ljg
//	// 	m_Spread.SetText(_T("(µß∆Æ/∞·º’)ø°¡ˆº±∆¯∫ÅE));
//	// 	m_Spread.SetRow(13);
//	// 	m_Spread.SetText(_T("VIA          Edge∞·º’π‡±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(14);
//	// 	m_Spread.SetText(_T("Edgeµß∆Æπ‡±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(15);
//	// 	m_Spread.SetText(_T("Edgeµπ±‚π‡±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(16);
//	// 	m_Spread.SetText(_T("Edge∫Ø»≠(∞·º’)≈©±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(17);
//	// 	m_Spread.SetText(_T("Edge∫Ø»≠(µπ±ÅE≈©±ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//	// 	m_Spread.SetRow(18);
//	// 	//m_Spread.SetText(_T("∞·º’HLG(∞·º’-µß∆Æ)"));	// 20090301 ljg
//	// 	m_Spread.SetText(_T("(µß∆Æ/∞·º’)ø°¡ˆº±∆¯∫ÅE));
//	// 	m_Spread.SetTypeVAlign(SS_ALIGN_RIGHT);
//	// 	//m_Spread.SetTypeAlign(SS_ALIGN_RIGHT);
//
//	//Arrange All Cells with Vertical Center.
//	for (int iRow = 1; iRow <= m_Spread.GetMaxRows(); iRow++)
//	{
//		m_Spread.SetRow(iRow);
//
//		m_Spread.SetCol(1);
//		m_Spread.SetCellType(TYPE_DEFAULT);
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_VCENTER | SSS_ALIGN_CENTER, 128, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(SS_ALLCOLS, iRow, &stype);
//		m_Spread.SetFontBold(TRUE);
//		m_Spread.SetFontSize(m_fDataFontSize);
//		if (m_bMasterLocalFlag[0][iRow - 1] && pGlobalDoc->m_bDefaultSpecFlag)
//			m_Spread.SetForeColor(RGB(58, 53, 151));
//		else
//			m_Spread.SetForeColor(RGB(60, 145, 103));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//		m_Spread.SetLock(FALSE);
//
//		m_Spread.SetCol(2);
//		m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//		m_Spread.SetFontBold(TRUE);
//		m_Spread.SetFontSize(m_fDataFontSize);
//		m_Spread.SetForeColor(RGB(0, 0, 0));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//
//		// Clear Cell Boarder
//		m_Spread.SetCellBorder(0, iRow, 2, iRow, 8, -1, 0); // Bottom Line - Default Style.
//	}
//
//	m_bEnableCheckBox = FALSE;
//
//	// Clear Spread Sheet
//	m_Spread.ClearRange(1, 1, m_Spread.GetMaxCols(), m_Spread.GetMaxRows(), TRUE);
//
//	// Static in Cell
//	m_Spread.SetCol(2);
//
//	m_Spread.SetRow(1);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)	//170217 hjc mod
//		m_Spread.SetText(_T("DN[N205,231,255,256]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(2);	//120105 hjc add
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[N211,213,225,226,236,255,256,261]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(3);	//120105 hjc add
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[N212]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(4);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[N201,202,205,206,208,225,226,232]"));	//170217 hjc mod  //20191223 add 225,226
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("pxl[N201,202,205,206,208,225,226,232]"));
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(5);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[P235,252~255,257,258]"));	//170217 hjc mod  //20191223 add 253,254,
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("pxl[P235,252~255,257,258]"));
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	//20090412 hjc
//	m_Spread.SetRow(6);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[256]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(7);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[203, 253]"));
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("pxl[203, 253]"));
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(8);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T("DN"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(9);	//120109 hjc add
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[HD8,9]"));
//	else
//		m_Spread.SetText(_T("DN"));
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(10);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[HD5]"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(11);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("um[HD6]"));
//	else
//		m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(12);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T("DN[HD15,16]"));	//20191224 add hd15,
//											//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(13);	//120105 hjc add
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue)
//		m_Spread.SetText(_T("DN[HD8,9,10,15,CD8,9]"));	//20200102 add 15
//	else
//		m_Spread.SetText(_T("DN"));
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//
//	m_Spread.SetRow(14);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[HD5,7,CD5]"));
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("pxl[HD5,7,CD5]"));
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(15);
//	m_Spread.SetCellType(TYPE_STATIC);
//	if (pGlobalDoc->m_bDisplayKValue && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um[HD6,11,15,16,17,CD6]"));	//20191219 mod
//	else if (pGlobalDoc->m_bDisplayKValue && (!pGlobalDoc->m_bUseMicron2Spec))
//		m_Spread.SetText(_T("pxl[HD6,11,15,16,17,CD6]"));
//	else if ((!pGlobalDoc->m_bDisplayKValue) && pGlobalDoc->m_bUseMicron2Spec)
//		m_Spread.SetText(_T("um"));
//	else
//		m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	//Disable Cells
//	m_Spread.SetCol(1);
//
//
//	m_Spread.SetCellBorder(-1, -1, -1, -1, SS_BORDERTYPE_BOTTOM | SS_BORDERTYPE_RIGHT, RGB(180, 180, 180), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_LEFT | SS_BORDERTYPE_TOP | SS_BORDERTYPE_BOTTOM, RGB(180, 180, 180), SS_BORDERSTYLE_NONE); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_RIGHT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//																								   // Draw Cell Boarder
//	m_Spread.SetCellBorder(0, 5, 2, 5, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 7, 2, 7, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 11, 2, 11, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 15, 2, 15, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(2, -1, 2, -1, SS_BORDERTYPE_LEFT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//																								  //Set Color Group
//	for (int iCol = 1; iCol <= 2; iCol++)
//	{
//		m_Spread.SetCol(iCol);
//
//		m_Spread.SetRow(1);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(2);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(3);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(4);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(5);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//
//		m_Spread.SetRow(6);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(7);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//
//		m_Spread.SetRow(8);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(9);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(10);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//		m_Spread.SetRow(11);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//
//		m_Spread.SetRow(12);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(13);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(14);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//		m_Spread.SetRow(15);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//	}
}

void CDlgSpec::InitSpreadTab7()
{
//	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
//	// Initialize Tab ctrl for information viewer
//	m_tabDlgInspection.HighlightItem(m_nTabNum, FALSE);
//
//	//Tab Index
//	m_nTabNum = 7;
//	m_tabDlgInspection.HighlightItem(m_nTabNum, TRUE);
//
//	m_Spread.SetReDraw(FALSE);
//	InitSpread();
//	//Column Width twip
//	m_Spread.SetMaxCols(2);
//
//	int nAddRow = 0;
//
//#ifdef IRIS_AXIS
//	nAddRow++;
//#endif
//
//	if (AoiParam()->m_bUseAutoPinPosAdjust || g_bUsePinPosEstimate)
//		m_Spread.SetMaxRows(9 + nAddRow);
//	else
//		m_Spread.SetMaxRows(7 + nAddRow);
//
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//#if WIN_OS == WIN_10
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		//HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		//m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(1, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize + 2, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//
//		m_Spread.SetFont(2, SS_ALLROWS, hfont, TRUE);
//
//		hfont = CreateFont(m_fDataFontSize, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//
//		m_Spread.SetFont(3, SS_ALLROWS, hfont, TRUE);
//
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//
//#else
//	if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 4, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//	else
//	{
//		HFONT hfont = CreateFont(m_fDataFontSize + 3, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, pGlobalView->m_strMainFont);
//		m_Spread.SetFont(SS_ALLCOLS, SS_ALLROWS, hfont, TRUE);
//	}
//#endif
//	// ?EΩ√Ω∫≈€¿« «»ºø¥ÅETwips∞™¿ª ∆ƒæ««—¥Ÿ.
//	CDC* pDC = GetDC();
//	int nLogX = pDC->GetDeviceCaps(LOGPIXELSX);
//	ReleaseDC(pDC);
//	int nTwipPerPixel = 1440 / nLogX;
//
//	// ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	CRect rect;
//	m_Spread.GetClientRect(rect);
//	long twpWidth = (rect.right - rect.left);
//
//	// Ω∫«¡∑πµÂ¿« ∆¯¿ª  Column Width¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadWidth, EachColWidth;
//	m_Spread.LogUnitsToColWidth(twpWidth, &fSpreadWidth);
//
//	if (AoiParam()->m_bSetSpecLocking)
//	{
//		m_Spread.SetColWidth(0, 35);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 22);	//140314 hjc mod
//	}
//	else
//	{
//		m_Spread.SetColWidth(0, 32);	//20090311 hjc modify
//		m_Spread.SetColWidth(2, 26);	//140314 hjc mod
//	}
//	EachColWidth = (float)(fSpreadWidth - (m_Spread.GetColWidth(0)
//		+ m_Spread.GetColWidth(2)) - 0.5);
//	m_Spread.SetColWidth(1, EachColWidth);
//
//	m_Spread.SetRowHeight(0, 5); // COL(0)'S HEIGHT
//
//								 // ∏Æº“Ω∫ ø°µ≈Õ∑Œ ±◊∑¡¡ÅEΩ∫«¡∑πµÂ¿« ≈©±‚∏¶ Twips¥‹¿ß∑Œ ∆ƒæ««—¥Ÿ.
//	long twpHeight = (rect.bottom - rect.top);
//
//	// Ω∫«¡∑πµÂ¿« ≥Ù¿Ã∏¶ Row Height¥‹¿ß∑Œ ∫Ø»Ø«—¥Ÿ.
//	double fSpreadHeight;//, EachRowHeight
//	long nRow;
//	m_Spread.LogUnitsToRowHeight(0, twpHeight, &fSpreadHeight);
//	double dSepHeight = (fSpreadHeight - 10) / max(1, m_Spread.GetMaxRows() + 1);
//	for (nRow = 1; nRow <= m_Spread.GetMaxRows(); nRow++)
//	{
//
//		m_Spread.SetRowHeight(nRow, dSepHeight);
//	}
//
//	//Column Caption
//	m_Spread.SetRow(0);
//
//	m_Spread.SetCol(1);
//	m_Spread.SetText(_T(" "));
//	m_Spread.SetCol(2);
//	m_Spread.SetText(_T(" "));
//
//	//«Ï¥ı ƒ¡∆Æ∑—
//	SS_CELLTYPE stype;
//	m_Spread.SetTypeStaticText(&stype, SS_TEXT_SHADOW | SS_TEXT_VCENTER | SS_TEXT_RIGHT);
//	m_Spread.SetCellType(SS_HEADER, SS_ALLROWS, &stype);
//
//
//
//	ChangeSpecSpreadCaption(7);
//
//	for (int iRow = 1; iRow <= m_Spread.GetMaxRows(); iRow++)
//	{
//		m_Spread.SetRow(iRow);
//
//		m_Spread.SetCol(1);
//		m_Spread.SetCellType(TYPE_DEFAULT);
//		m_Spread.SetTypeEdit(&stype, SSS_ALIGN_VCENTER | SSS_ALIGN_CENTER, 128, SS_CHRSET_CHR, SS_CASE_NOCASE);
//		m_Spread.SetCellType(SS_ALLCOLS, iRow, &stype);
//
//		m_Spread.SetFontBold(TRUE);
//		m_Spread.SetFontSize(m_fDataFontSize);
//		if (m_bMasterLocalFlag[3][iRow - 1] && pGlobalDoc->m_bDefaultSpecFlag)
//			m_Spread.SetForeColor(RGB(58, 53, 151));
//		else
//			m_Spread.SetForeColor(RGB(60, 145, 103));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//		m_Spread.SetLock(FALSE);
//
//		m_Spread.SetCol(2);
//		m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//		m_Spread.SetFontBold(TRUE);
//		m_Spread.SetFontSize(m_fDataFontSize);	//20090309 hjc
//		m_Spread.SetForeColor(RGB(0, 0, 0));
//		m_Spread.SetBackColor(RGB(255, 255, 255));
//
//		// Clear Cell Boarder
//		m_Spread.SetCellBorder(0, iRow, 2, iRow, 8, -1, 0); // Bottom Line - Default Style.
//	}
//
//	m_bEnableCheckBox = FALSE;
//
//	// Clear Spread Sheet
//	m_Spread.ClearRange(1, 1, m_Spread.GetMaxCols(), m_Spread.GetMaxRows(), TRUE);
//
//	// Static in Cell
//	m_Spread.SetCol(2);
//
//	m_Spread.SetRow(1);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(2);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T("pxl"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(3);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T("(5~200)"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(4);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T(" "));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(5);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	m_Spread.SetRow(6);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T("um"));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	//20100210 hjc add
//	m_Spread.SetRow(7);
//	m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetText(_T(""));
//	//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	if (AoiParam()->m_bUseAutoPinPosAdjust || g_bUsePinPosEstimate)
//	{
//		//20100210 hjc add
//		m_Spread.SetRow(8);
//		m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetText(_T("mm"));
//		//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//		//20100210 hjc add
//		m_Spread.SetRow(9);
//		m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetText(_T("mm"));
//		//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//
//#ifdef IRIS_AXIS
//		//20100210 hjc add
//		m_Spread.SetRow(10);
//		m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetText(_T("PosID"));
//		//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//#endif
//
//	}
//	else
//	{
//#ifdef IRIS_AXIS
//		//20100210 hjc add
//		m_Spread.SetRow(8);
//		m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetText(_T("PosID"));
//		//m_Spread.SetTypeTextWordWrap(TRUE);// Set the text to wrap to multiple lines
//		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//#endif
//	}
//
//
//	//comboBox
//	m_Spread.SetCol(1);
//
//	m_Spread.SetRow(4);
//	m_Spread.SetCellType(TYPE_COMBO);
//
//	//160924 lgh fix
//	m_Spread.SetTypeComboBoxList(_T("Maximum\tHighest\tVeryHigh\tHigh\tNormal\tLow"));//"1/4\t1/3\t1/2"
//
//	m_Spread.SetTypeComboBoxEditable(TRUE);
//	m_Spread.SetTypeComboBoxMaxDrop(10);
//	//m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER );
//	//m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//	//20100210 hjc add
//	m_Spread.SetCol(1);
//
//	m_Spread.SetRow(7);
//	m_Spread.SetCellType(TYPE_COMBO);
//	if (!pGlobalDoc->m_bUseMultiVaccumControl)	//20100210 hjc add		//130311 hjc mod
//	{
//#if LANGUAGE == ENGLISH
//		m_Spread.SetTypeComboBoxList(_T("Both    (1)"));
//#elif LANGUAGE == KOREAN
//		m_Spread.SetTypeComboBoxList(_T("Both    (1)"));
//#elif LANGUAGE == JAPANESE
//		m_Spread.SetTypeComboBoxList(_T("Both    (1)"));
//#endif
//	}
//	else
//	{
//#if LANGUAGE == ENGLISH
//		m_Spread.SetTypeComboBoxList(_T("Both    (1)\tFirstOnly   (2)"));
//#elif LANGUAGE == KOREAN
//		m_Spread.SetTypeComboBoxList(_T("Both    (1)\tFirstOnly   (2)"));
//#elif LANGUAGE == JAPANESE
//		m_Spread.SetTypeComboBoxList(_T("Both    (1)\tFirstOnly   (2)"));
//#endif
//	}
//	m_Spread.SetTypeComboBoxEditable(TRUE);
//	m_Spread.SetTypeComboBoxMaxDrop(10);
//	m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
//	m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
//
//#ifdef IRIS_AXIS
//
//	CString strDropPos;
//
//	int nAllID = 0;
//	for (int i = 0; i < 12; i++)
//	{
//		CString strData;
//
//		if (pGlobalDoc->m_IRISAxisControl.m_dIRISPosName[i] > 0.0)
//		{
//			strData.Format(_T("%.3f"), pGlobalDoc->m_IRISAxisControl.m_dIRISPosName[i]);
//
//			strDropPos += strData;
//			if (i != 11)
//				strDropPos += _T("\t");
//			nAllID++;
//		}
//	}
//
//	m_Spread.SetCol(1);
//
//	m_Spread.SetRow(m_Spread.GetMaxRows());
//	m_Spread.SetCellType(TYPE_COMBO);
//
//	//160924 lgh fix
//	m_Spread.SetTypeComboBoxList(strDropPos);//"1/4\t1/3\t1/2"
//
//	m_Spread.SetTypeComboBoxEditable(FALSE);
//	m_Spread.SetTypeComboBoxMaxDrop(nAllID);
//#endif
//
//	//Disable Cells
//	m_Spread.SetCol(1);
//
//	m_Spread.SetRow(2);
//	//m_Spread.SetCellType(TYPE_STATIC);
//	m_Spread.SetLock(TRUE);
//	m_Spread.SetForeColor(RGB(152, 152, 152));
//
//	if (pGlobalDoc->m_bUseMultiVaccumControl)	//20100210 hjc add		//130311 hjc mod
//	{
//		m_Spread.SetRow(7);
//		//m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetLock(FALSE);
//		m_Spread.SetForeColor(RGB(152, 152, 152));
//	}
//	else	//130311 hjc mod
//	{
//		m_Spread.SetRow(7);
//		//m_Spread.SetCellType(TYPE_STATIC);
//		m_Spread.SetLock(TRUE);
//		m_Spread.SetForeColor(RGB(152, 152, 152));
//	}
//	m_Spread.SetCellBorder(-1, -1, -1, -1, SS_BORDERTYPE_BOTTOM | SS_BORDERTYPE_RIGHT, RGB(180, 180, 180), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_LEFT | SS_BORDERTYPE_TOP | SS_BORDERTYPE_BOTTOM, RGB(180, 180, 180), SS_BORDERSTYLE_NONE); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, -1, 0, -1, SS_BORDERTYPE_RIGHT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//																								   // Draw Cell Boarder
//	m_Spread.SetCellBorder(0, 4, 2, 4, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(0, 6, 2, 6, 8, RGB(0, 0, 0), 1); // Bottom Line - Solid Style.
//	m_Spread.SetCellBorder(2, -1, 2, -1, SS_BORDERTYPE_LEFT, RGB(0, 0, 0), SS_BORDERSTYLE_SOLID); // Bottom Line - Solid Style.
//
//																								  //Set Color Group
//	for (int iCol = 1; iCol <= 2; iCol++)
//	{
//		m_Spread.SetCol(iCol);
//
//		//20090311 hjc modify
//		m_Spread.SetRow(1);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(2);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(3);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//		m_Spread.SetRow(4);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
//
//		m_Spread.SetRow(5);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//		m_Spread.SetRow(6);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
//
//		m_Spread.SetRow(7);
//		m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
//
//		if (AoiParam()->m_bUseAutoPinPosAdjust || g_bUsePinPosEstimate)
//		{
//			m_Spread.SetRow(8);
//			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//			m_Spread.SetRow(9);
//			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//#ifdef IRIS_AXIS
//			m_Spread.SetRow(10);
//			m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
//#endif
//		}
//		else
//		{
//#ifdef IRIS_AXIS
//			m_Spread.SetRow(8);
//			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
//#endif
//		}
//	}
}

void CDlgSpec::SetSpecAccessItem(int nTab, int nRow)
{
	//if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
	//{
	//	m_Spread.SetRow(nRow);

	//	if (pGlobalDoc->m_LockTable.m_pLockTable[nTab][nRow].bAccessUser)
	//	{
	//		m_Spread.SetLock(0);
	//	}
	//	else
	//	{
	//		if (pGlobalView->m_nUserID == OPERATOR)
	//			m_Spread.SetLock(1);
	//		else
	//			m_Spread.SetLock(0);
	//	}
	//}
}

void CDlgSpec::LoadSpreadDataTab0()
{
	//m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	//CString strTemp;

	//m_Spread.SetCol(1);

	//m_Spread.SetRow(1);
	//strTemp.Format(_T("%.1f"), m_fNominalLine);
	//m_Spread.SetText(strTemp);
	//m_Spread.SetCellNote(_T("GigaVis _ Note 1 !!!"));
	//SetSpecAccessItem(0, 1);

	//m_Spread.SetRow(2);
	//strTemp.Format(_T("%.1f"), m_fRealNormLine);
	//m_Spread.SetText(strTemp);
	//m_Spread.SetCellNote(_T("GigaVis _ Note 2 !!!"));
	//SetSpecAccessItem(0, 2);

	//m_Spread.SetRow(3);
	//strTemp.Format(_T("%d"), m_nNickGray);
	//m_Spread.SetText(strTemp);
	//m_Spread.SetCellNote(_T("GigaVis _ Note 3 !!!"));
	//SetSpecAccessItem(0, 3);

	////20090216 chg
	//m_Spread.SetRow(4);
	//strTemp.Format(_T("%d"), m_nOpenGray);	//150410 hjc add
	//m_Spread.SetText(strTemp);
	//m_Spread.SetCellNote(_T("GigaVis _ Note 4 !!!"));
	//SetSpecAccessItem(0, 4);

	////150413 hjc add
	//m_Spread.SetRow(5);
	//strTemp.Format(_T("%d"), m_nHalfSideNickDiffBrightGray);
	//m_Spread.SetText(strTemp);
	//m_Spread.SetCellNote(_T("GigaVis _ Note 5 !!!"));
	//SetSpecAccessItem(0, 5);

	//m_Spread.SetRow(6);
	//strTemp.Format(_T("%d"), m_nHalfSideNickDiffDarkGray);
	//m_Spread.SetText(strTemp);
	//m_Spread.SetCellNote(_T("GigaVis _ Note 6 !!!"));
	//SetSpecAccessItem(0, 6);

	//m_Spread.SetRow(7);
	//strTemp.Format(_T("%d"), m_nLeadOpenGray);
	//m_Spread.SetText(strTemp);
	//m_Spread.SetCellNote(_T("GigaVis _ Note 7 !!!"));
	//SetSpecAccessItem(0, 7);

	//m_Spread.SetRow(8);
	//strTemp.Format(_T("%.1f"), m_fMinCheckWidth);
	//m_Spread.SetText(strTemp);
	//m_Spread.SetCellNote(_T("GigaVis _ Note 8 !!!"));
	//SetSpecAccessItem(0, 8);

	//CString strVal;


	//if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx)	//170526 hjc mod
	//{
	//	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	//	{
	//		//170217 lgh
	//		int nPos = m_strNick[0].Find(_T(" "), 0);
	//		if (nPos >= 0)
	//			m_strNick[0] = m_strNick[0].Left(nPos);

	//		m_Spread.SetRow(9);
	//		if (m_strNick[0] == "Highest")
	//			strTemp = m_strNick[0] + "   (90%)";
	//		else if (m_strNick[0] == "VeryHigh")
	//			strTemp = m_strNick[0] + "   (80%)";
	//		else if (m_strNick[0] == "High")
	//			strTemp = m_strNick[0] + "   (70%)";
	//		else if (m_strNick[0] == "Normal")
	//			strTemp = m_strNick[0] + "   (60%)";
	//		else if (m_strNick[0] == "Low")
	//			strTemp = m_strNick[0] + "   (50%)";
	//		else if (m_strNick[0] == "VeryLow")
	//			strTemp = m_strNick[0] + "   (40%)";
	//		else if (m_strNick[0] == "Lowest")
	//			strTemp = m_strNick[0] + "   (30%)";
	//		else if (m_strNick[0] == "MaxLimit")		//140126 hjc add
	//			strTemp = m_strNick[0] + "   (10%)";
	//		else
	//		{
	//			strTemp = CString("Normal") + "   (60%)";
	//			m_strNick[0] = "Normal";
	//		}

	//		m_Spread.SetText(strTemp);
	//		m_Spread.SetCellNote(_T("GigaVis _ Note 9 !!!"));
	//		SetSpecAccessItem(0, 9);


	//		//170217 lgh
	//		nPos = m_strProtrusion[0].Find(_T(" "), 0);
	//		if (nPos >= 0)
	//			m_strProtrusion[0] = m_strProtrusion[0].Left(nPos);

	//		m_Spread.SetRow(10);
	//		if (m_strProtrusion[0] == "Highest")
	//			strTemp = m_strProtrusion[0] + "   (110%)";
	//		else if (m_strProtrusion[0] == "VeryHigh")
	//			strTemp = m_strProtrusion[0] + "   (120%)";
	//		else if (m_strProtrusion[0] == "High")
	//			strTemp = m_strProtrusion[0] + "   (130%)";
	//		else if (m_strProtrusion[0] == "Normal")
	//			strTemp = m_strProtrusion[0] + "   (140%)";
	//		else if (m_strProtrusion[0] == "Low")
	//			strTemp = m_strProtrusion[0] + "   (150%)";
	//		else if (m_strProtrusion[0] == "VeryLow")
	//			strTemp = m_strProtrusion[0] + "   (160%)";
	//		else if (m_strProtrusion[0] == "Lowest")
	//			strTemp = m_strProtrusion[0] + "   (170%)";
	//		else if (m_strProtrusion[0] == "MaxLimit")		//140126 hjc add
	//			strTemp = m_strProtrusion[0] + "   (190%)";
	//		else
	//		{
	//			strTemp = CString("Normal") + "   (140%)";
	//			m_strProtrusion[0] = "Normal";
	//		}

	//		m_Spread.SetText(strTemp);
	//		m_Spread.SetCellNote(_T("GigaVis _ Note 10 !!!"));
	//		SetSpecAccessItem(0, 10);
	//	}
	//	else
	//	{
	//		m_Spread.SetRow(9);
	//		strTemp.Format(_T("%d"), m_nNickPercent[0]);
	//		m_Spread.SetText(strTemp);
	//		m_Spread.SetCellNote(_T("GigaVis _ Note 9 !!!"));

	//		SetSpecAccessItem(0, 9);

	//		m_Spread.SetRow(10);
	//		strTemp.Format(_T("%d"), m_nProtrusionPercent[0]);
	//		m_Spread.SetText(strTemp);
	//		m_Spread.SetCellNote(_T("GigaVis _ Note 10 !!!"));

	//		SetSpecAccessItem(0, 10);
	//	}

	//	m_Spread.SetRow(11);
	//	strTemp.Format(_T("%d"), m_nNickNGFilterPercent[0]);
	//	m_Spread.SetText(strTemp);
	//	m_Spread.SetCellNote(_T("GigaVis _ Note 11 !!!"));

	//	SetSpecAccessItem(0, 11);

	//	m_Spread.SetRow(12);
	//	strTemp.Format(_T("%d"), m_nExcsNGFilterPercent[0]);
	//	m_Spread.SetText(strTemp);
	//	m_Spread.SetCellNote(_T("GigaVis _ Note 12 !!!"));

	//	SetSpecAccessItem(0, 12);

	//	m_Spread.SetRow(13);
	//	strTemp.Format(_T("%.2f"), m_fLineWdDeltaGradViolation[0]);
	//	m_Spread.SetText(strTemp);
	//	m_Spread.SetCellNote(_T("GigaVis _ Note 13 !!!"));

	//	SetSpecAccessItem(0, 13);

	//	m_Spread.SetRow(14);
	//	strTemp.Format(_T("%.2f"), m_fExcsWdDeltaGradViolation[0]);
	//	m_Spread.SetText(strTemp);
	//	m_Spread.SetCellNote(_T("GigaVis _ Note 14 !!!"));

	//	SetSpecAccessItem(0, 14);

	//	m_Spread.SetRow(15);
	//	strTemp = "";
	//	for (int idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
	//	{
	//		if (idx < 4)
	//		{
	//			if (idx)
	//				strTemp += _T("/");
	//			strVal.Format(_T("%.1f"), m_fNarrowTraceViolation[idx]);
	//			strTemp += strVal;
	//		}
	//		else if (idx == 4)
	//		{
	//			strTemp += "/..";
	//		}

	//	}
	//	m_Spread.SetTypeButtonText(strTemp);

	//}
	//else
	//{
	//	if (SpecData.nLineWidthGroupNum == 0)
	//	{
	//		if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	//		{
	//			//170217 lgh
	//			int nPos = m_strNick[0].Find(_T(" "), 0);
	//			if (nPos >= 0)
	//				m_strNick[0] = m_strNick[0].Left(nPos);

	//			m_Spread.SetRow(9);
	//			if (m_strNick[0] == "Highest")
	//				strTemp = m_strNick[0] + "   (90%)";
	//			else if (m_strNick[0] == "VeryHigh")
	//				strTemp = m_strNick[0] + "   (80%)";
	//			else if (m_strNick[0] == "High")
	//				strTemp = m_strNick[0] + "   (70%)";
	//			else if (m_strNick[0] == "Normal")
	//				strTemp = m_strNick[0] + "   (60%)";
	//			else if (m_strNick[0] == "Low")
	//				strTemp = m_strNick[0] + "   (50%)";
	//			else if (m_strNick[0] == "VeryLow")
	//				strTemp = m_strNick[0] + "   (40%)";
	//			else if (m_strNick[0] == "Lowest")
	//				strTemp = m_strNick[0] + "   (30%)";
	//			else if (m_strNick[0] == "MaxLimit")		//140126 hjc add
	//				strTemp = m_strNick[0] + "   (10%)";
	//			else
	//			{
	//				strTemp = CString("Normal") + "   (60%)";
	//				m_strNick[0] = "Normal";
	//			}

	//			m_Spread.SetText(strTemp);
	//			m_Spread.SetCellNote(_T("GigaVis _ Note 9 !!!"));
	//			SetSpecAccessItem(0, 9);


	//			//170217 lgh
	//			nPos = m_strProtrusion[0].Find(_T(" "), 0);
	//			if (nPos >= 0)
	//				m_strProtrusion[0] = m_strProtrusion[0].Left(nPos);

	//			m_Spread.SetRow(10);
	//			if (m_strProtrusion[0] == "Highest")
	//				strTemp = m_strProtrusion[0] + "   (110%)";
	//			else if (m_strProtrusion[0] == "VeryHigh")
	//				strTemp = m_strProtrusion[0] + "   (120%)";
	//			else if (m_strProtrusion[0] == "High")
	//				strTemp = m_strProtrusion[0] + "   (130%)";
	//			else if (m_strProtrusion[0] == "Normal")
	//				strTemp = m_strProtrusion[0] + "   (140%)";
	//			else if (m_strProtrusion[0] == "Low")
	//				strTemp = m_strProtrusion[0] + "   (150%)";
	//			else if (m_strProtrusion[0] == "VeryLow")
	//				strTemp = m_strProtrusion[0] + "   (160%)";
	//			else if (m_strProtrusion[0] == "Lowest")
	//				strTemp = m_strProtrusion[0] + "   (170%)";
	//			else if (m_strProtrusion[0] == "MaxLimit")		//140126 hjc add
	//				strTemp = m_strProtrusion[0] + "   (190%)";
	//			else
	//			{
	//				strTemp = CString("Normal") + "   (140%)";
	//				m_strProtrusion[0] = "Normal";
	//			}

	//			m_Spread.SetText(strTemp);
	//			m_Spread.SetCellNote(_T("GigaVis _ Note 10 !!!"));
	//			SetSpecAccessItem(0, 10);
	//		}
	//		else
	//		{
	//			m_Spread.SetRow(9);
	//			strTemp.Format(_T("%d"), m_nNickPercent[0]);
	//			m_Spread.SetText(strTemp);
	//			m_Spread.SetCellNote(_T("GigaVis _ Note 9 !!!"));

	//			SetSpecAccessItem(0, 9);

	//			m_Spread.SetRow(10);
	//			strTemp.Format(_T("%d"), m_nProtrusionPercent[0]);
	//			m_Spread.SetText(strTemp);
	//			m_Spread.SetCellNote(_T("GigaVis _ Note 10 !!!"));

	//			SetSpecAccessItem(0, 10);
	//		}

	//		m_Spread.SetRow(11);
	//		strTemp.Format(_T("%d"), m_nNickNGFilterPercent[0]);
	//		m_Spread.SetText(strTemp);
	//		m_Spread.SetCellNote(_T("GigaVis _ Note 11 !!!"));

	//		SetSpecAccessItem(0, 11);

	//		m_Spread.SetRow(12);
	//		strTemp.Format(_T("%d"), m_nExcsNGFilterPercent[0]);
	//		m_Spread.SetText(strTemp);
	//		m_Spread.SetCellNote(_T("GigaVis _ Note 12 !!!"));

	//		SetSpecAccessItem(0, 12);

	//		m_Spread.SetRow(13);
	//		strTemp.Format(_T("%.2f"), m_fLineWdDeltaGradViolation[0]);
	//		m_Spread.SetText(strTemp);
	//		m_Spread.SetCellNote(_T("GigaVis _ Note 13 !!!"));

	//		SetSpecAccessItem(0, 13);

	//		m_Spread.SetRow(14);
	//		strTemp.Format(_T("%.2f"), m_fExcsWdDeltaGradViolation[0]);
	//		m_Spread.SetText(strTemp);
	//		m_Spread.SetCellNote(_T("GigaVis _ Note 14 !!!"));

	//		SetSpecAccessItem(0, 14);

	//		m_Spread.SetRow(15);
	//		strTemp.Format(_T("%.1f"), m_fNarrowTraceViolation[0]);
	//		m_Spread.SetText(strTemp);
	//		m_Spread.SetCellNote(_T("GigaVis _ Note 15 !!!"));

	//		SetSpecAccessItem(0, 15);

	//		m_Spread.SetRow(16);
	//		strTemp.Format(_T("%.1f"), m_fWideTraceViolation[0]);
	//		m_Spread.SetText(strTemp);

	//		SetSpecAccessItem(0, 16);
	//	}
	//	else
	//	{
	//		if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	//		{
	//			m_Spread.SetRow(9);
	//			if (SpecData.nLineWidthGroupNum > 0)	//170526 hjc mod
	//			{
	//				strTemp = "";
	//				for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
	//				{
	//					if (idx < 4)
	//					{
	//						if (idx)
	//							strTemp += _T("/");
	//						strVal.Format(_T("%s"), GetNickRange(m_strNick[idx]));
	//						strTemp += strVal;
	//					}
	//					else if (idx == 4)
	//					{
	//						strTemp += "/..";
	//					}

	//				}
	//				m_Spread.SetTypeButtonText(strTemp);
	//			}

	//			SetSpecAccessItem(0, 9);

	//			m_Spread.SetRow(10);
	//			if (SpecData.nLineWidthGroupNum > 0)	//170526 hjc mod
	//			{
	//				strTemp = "";
	//				for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
	//				{
	//					if (idx < 4)
	//					{
	//						if (idx)
	//							strTemp += _T("/");
	//						strVal.Format(_T("%s"), GetProtRange(m_strProtrusion[idx]));
	//						strTemp += strVal;
	//					}
	//					else if (idx == 4)
	//					{
	//						strTemp += "/..";
	//					}

	//				}
	//				m_Spread.SetTypeButtonText(strTemp);
	//			}

	//			SetSpecAccessItem(0, 10);
	//		}
	//		else
	//		{
	//			m_Spread.SetRow(9);

	//			if (SpecData.nLineWidthGroupNum > 0)	//170526 hjc mod
	//			{
	//				strTemp = "";
	//				for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
	//				{
	//					if (idx < 4)
	//					{
	//						if (idx)
	//							strTemp += _T("/");
	//						strVal.Format(_T("%d"), m_nNickPercent[idx]);
	//						strTemp += strVal;
	//					}
	//					else if (idx == 4)
	//					{
	//						strTemp += "/..";
	//					}

	//				}
	//				m_Spread.SetTypeButtonText(strTemp);
	//			}

	//			SetSpecAccessItem(0, 9);

	//			m_Spread.SetRow(10);

	//			if (SpecData.nLineWidthGroupNum > 0)	//170526 hjc mod
	//			{
	//				strTemp = "";
	//				for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
	//				{
	//					if (idx < 4)
	//					{
	//						if (idx)
	//							strTemp += _T("/");
	//						strVal.Format(_T("%d"), m_nProtrusionPercent[idx]);
	//						strTemp += strVal;
	//					}
	//					else if (idx == 4)
	//					{
	//						strTemp += "/..";
	//					}

	//				}
	//				m_Spread.SetTypeButtonText(strTemp);
	//			}

	//			SetSpecAccessItem(0, 10);
	//		}

	//		m_Spread.SetRow(11);

	//		if (SpecData.nLineWidthGroupNum > 0)	//170526 hjc mod
	//		{
	//			strTemp = "";
	//			for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
	//			{
	//				if (idx < 4)
	//				{
	//					if (idx)
	//						strTemp += _T("/");
	//					strVal.Format(_T("%d"), m_nNickNGFilterPercent[idx]);
	//					strTemp += strVal;
	//				}
	//				else if (idx == 4)
	//				{
	//					strTemp += "/..";
	//				}

	//			}
	//			m_Spread.SetTypeButtonText(strTemp);
	//		}

	//		m_Spread.SetCellNote(_T("GigaVis _ Note 11 !!!"));
	//		SetSpecAccessItem(0, 11);


	//		m_Spread.SetRow(12);

	//		if (SpecData.nLineWidthGroupNum > 0)	//170526 hjc mod
	//		{
	//			strTemp = "";
	//			for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
	//			{
	//				if (idx < 4)
	//				{
	//					if (idx)
	//						strTemp += _T("/");
	//					strVal.Format(_T("%d"), m_nExcsNGFilterPercent[idx]);
	//					strTemp += strVal;
	//				}
	//				else if (idx == 4)
	//				{
	//					strTemp += "/..";
	//				}
	//			}
	//			m_Spread.SetTypeButtonText(strTemp);
	//		}

	//		m_Spread.SetCellNote(_T("GigaVis _ Note 12 !!!"));
	//		SetSpecAccessItem(0, 12);

	//		m_Spread.SetRow(13);

	//		if (SpecData.nLineWidthGroupNum > 0)	//170526 hjc mod
	//		{
	//			strTemp = "";
	//			for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
	//			{
	//				if (idx < 4)
	//				{
	//					if (idx)
	//						strTemp += _T("/");
	//					strVal.Format(_T("%.1f"), m_fLineWdDeltaGradViolation[idx]);
	//					strTemp += strVal;
	//				}
	//				else if (idx == 4)
	//				{
	//					strTemp += "/..";
	//				}
	//			}
	//			m_Spread.SetTypeButtonText(strTemp);
	//		}

	//		m_Spread.SetCellNote(_T("GigaVis _ Note 13 !!!"));
	//		SetSpecAccessItem(0, 13);


	//		m_Spread.SetRow(14);

	//		if (SpecData.nLineWidthGroupNum > 0)	//170526 hjc mod
	//		{
	//			strTemp = "";
	//			for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
	//			{
	//				if (idx < 4)
	//				{
	//					if (idx)
	//						strTemp += _T("/");
	//					strVal.Format(_T("%.1f"), m_fExcsWdDeltaGradViolation[idx]);
	//					strTemp += strVal;
	//				}
	//				else if (idx == 4)
	//				{
	//					strTemp += "/..";
	//				}
	//			}
	//			m_Spread.SetTypeButtonText(strTemp);
	//		}

	//		m_Spread.SetText(strTemp);
	//		m_Spread.SetCellNote(_T("GigaVis _ Note 14 !!!"));

	//		SetSpecAccessItem(0, 14);



	//		m_Spread.SetRow(15);

	//		if (SpecData.nLineWidthGroupNum > 0)	//170526 hjc mod
	//		{
	//			strTemp = "";
	//			for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
	//			{
	//				if (idx < 4)
	//				{
	//					if (idx)
	//						strTemp += _T("/");
	//					strVal.Format(_T("%.1f"), m_fNarrowTraceViolation[idx]);
	//					strTemp += strVal;
	//				}
	//				else if (idx == 4)
	//				{
	//					strTemp += "/..";
	//				}
	//			}
	//			m_Spread.SetTypeButtonText(strTemp);
	//		}

	//		m_Spread.SetCellNote(_T("GigaVis _ Note 15 !!!"));
	//		SetSpecAccessItem(0, 15);

	//		m_Spread.SetRow(16);
	//		if (SpecData.nLineWidthGroupNum > 0)	//170526 hjc mod
	//		{
	//			strTemp = "";
	//			for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
	//			{
	//				if (idx < 4)
	//				{
	//					if (idx)
	//						strTemp += _T("/");
	//					strVal.Format(_T("%.1f"), m_fWideTraceViolation[idx]);
	//					strTemp += strVal;
	//				}
	//				else if (idx == 4)
	//				{
	//					strTemp += "/..";
	//				}
	//			}
	//			m_Spread.SetTypeButtonText(strTemp);
	//		}

	//		m_Spread.SetCellNote(_T("GigaVis _ Note 16 !!!"));
	//		SetSpecAccessItem(0, 16);
	//	}
	//}

	//m_bEnableCheckBox = TRUE;
	//DisplayChangedData();
}

void CDlgSpec::LoadSpreadDataTab1()
{
/*	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	CString strTemp;
	CString strVal;

	m_Spread.SetCol(1);

	m_Spread.SetRow(1);
	strTemp.Format(_T("%.1f"), m_fNominalLine);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 17 !!!"));

	SetSpecAccessItem(1, 1);

	m_Spread.SetRow(2);
	strTemp.Format(_T("%.1f"), m_fRealNormLine);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 18 !!!"));
	SetSpecAccessItem(1, 2);

	m_Spread.SetRow(3);
	strTemp.Format(_T("%d"), m_nFineNickGray);	//170403 hjc mod
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 19 !!!"));
	SetSpecAccessItem(1, 3);

	m_Spread.SetRow(4);
	//20090228
	strTemp.Format(_T("%d"), m_nFineOpenGray);	//150410 hjc mod
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 20 !!!"));
	SetSpecAccessItem(1, 4);

	//150413 hjc add
	m_Spread.SetRow(5);
	strTemp.Format(_T("%d"), m_nFineHalfSideNickDiffBrightGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 21 !!!"));
	SetSpecAccessItem(1, 5);

	m_Spread.SetRow(6);
	strTemp.Format(_T("%d"), m_nFineHalfSideNickDiffDarkGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 22 !!!"));
	SetSpecAccessItem(1, 6);

	m_Spread.SetRow(7);
	strTemp.Format(_T("%d"), m_nLeadOpenGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 23 !!!"));
	SetSpecAccessItem(1, 7);

	m_Spread.SetRow(8);
	strTemp.Format(_T("%.1f"), m_fFineMinCheckWidth);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 24 !!!"));
	SetSpecAccessItem(1, 8);

	if (SpecData.nLineWidthGroupNum == 0)
	{

		if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
		{
			//170217 lgh
			int nPos = m_strFineNick[0].Find(_T(" "), 0);
			if (nPos >= 0)
				m_strFineNick[0] = m_strFineNick[0].Left(nPos);

			m_Spread.SetRow(9);
			if (m_strFineNick[0] == "Highest")
				strTemp = m_strFineNick[0] + "   (90%)";
			else if (m_strFineNick[0] == "VeryHigh")
				strTemp = m_strFineNick[0] + "   (80%)";
			else if (m_strFineNick[0] == "High")
				strTemp = m_strFineNick[0] + "   (70%)";
			else if (m_strFineNick[0] == "Normal")
				strTemp = m_strFineNick[0] + "   (60%)";
			else if (m_strFineNick[0] == "Low")
				strTemp = m_strFineNick[0] + "   (50%)";
			else if (m_strFineNick[0] == "VeryLow")
				strTemp = m_strFineNick[0] + "   (40%)";
			else if (m_strFineNick[0] == "Lowest")
				strTemp = m_strFineNick[0] + "   (30%)";
			else
			{
				m_strFineNick[0] = "Normal";
				strTemp = m_strFineNick[0] + "   (60%)";
			}

			m_Spread.SetText(strTemp);
			m_Spread.SetCellNote(_T("GigaVis _ Note 25 !!!"));
			SetSpecAccessItem(1, 9);

			//170217 lgh
			nPos = m_strFineProtrusion[0].Find(_T(" "), 0);
			if (nPos >= 0)
				m_strFineProtrusion[0] = m_strFineProtrusion[0].Left(nPos);


			m_Spread.SetRow(10);
			if (m_strFineProtrusion[0] == "Highest")
				strTemp = m_strFineProtrusion[0] + "   (110%)";
			else if (m_strFineProtrusion[0] == "VeryHigh")
				strTemp = m_strFineProtrusion[0] + "   (120%)";
			else if (m_strFineProtrusion[0] == "High")
				strTemp = m_strFineProtrusion[0] + "   (130%)";
			else if (m_strFineProtrusion[0] == "Normal")
				strTemp = m_strFineProtrusion[0] + "   (140%)";
			else if (m_strFineProtrusion[0] == "Low")
				strTemp = m_strFineProtrusion[0] + "   (150%)";
			else if (m_strFineProtrusion[0] == "VeryLow")
				strTemp = m_strFineProtrusion[0] + "   (160%)";
			else if (m_strFineProtrusion[0] == "Lowest")
				strTemp = m_strFineProtrusion[0] + "   (170%)";
			else
			{
				m_strFineProtrusion[0] = "Normal";
				strTemp = m_strFineProtrusion[0] + "   (140%)";
			}
			m_Spread.SetText(strTemp);
			m_Spread.SetCellNote(_T("GigaVis _ Note 26 !!!"));

			SetSpecAccessItem(1, 10);
		}
		else
		{
			m_Spread.SetRow(9);
			strTemp.Format(_T("%d"), m_nFineNickPercent[0]);
			m_Spread.SetText(strTemp);
			m_Spread.SetCellNote(_T("GigaVis _ Note 25 !!!"));

			SetSpecAccessItem(1, 9);

			m_Spread.SetRow(10);
			strTemp.Format(_T("%d"), m_nFineProtrusionPercent[0]);
			m_Spread.SetText(strTemp);
			m_Spread.SetCellNote(_T("GigaVis _ Note 26 !!!"));
			SetSpecAccessItem(1, 10);
		}

		m_Spread.SetRow(11);
		strTemp.Format(_T("%d"), m_nFineNickNGFilterPercent[0]);
		m_Spread.SetValueEx(strTemp);
		m_Spread.SetCellNote(_T("GigaVis _ Note 27 !!!"));
		SetSpecAccessItem(1, 11);

		m_Spread.SetRow(12);
		strTemp.Format(_T("%d"), m_nFineExcsNGFilterPercent[0]);
		m_Spread.SetText(strTemp);
		m_Spread.SetCellNote(_T("GigaVis _ Note 28 !!!"));
		SetSpecAccessItem(1, 12);

		m_Spread.SetRow(13);
		strTemp.Format(_T("%.2f"), m_fFineLineWdDeltaGradViolation[0]);
		m_Spread.SetText(strTemp);
		m_Spread.SetCellNote(_T("GigaVis _ Note 29 !!!"));
		SetSpecAccessItem(1, 13);

		m_Spread.SetRow(14);
		strTemp.Format(_T("%.2f"), m_fFineExcsWdDeltaGradViolation[0]);
		m_Spread.SetText(strTemp);
		m_Spread.SetCellNote(_T("GigaVis _ Note 30 !!!"));
		SetSpecAccessItem(1, 14);

		m_Spread.SetRow(15);
		strTemp.Format(_T("%.1f"), m_fFineNarrowTraceViolation[0]);
		m_Spread.SetText(strTemp);
		m_Spread.SetCellNote(_T("GigaVis _ Note 31 !!!"));
		SetSpecAccessItem(1, 15);

		m_Spread.SetRow(16);
		strTemp.Format(_T("%.1f"), m_fFineWideTraceViolation[0]);
		m_Spread.SetText(strTemp);

		m_Spread.SetCellNote(_T("GigaVis _ Note 32 !!!"));
		SetSpecAccessItem(1, 16);
	}
	else
	{
		if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
		{
			m_Spread.SetRow(9);
			if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx == 0)
			{
				strTemp = "";
				for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
				{
					if (idx < 4)
					{
						if (idx)
							strTemp += "/";
						strVal.Format(_T("%s"), GetNickRange(m_strFineNick[idx]));
						strTemp += strVal;
					}
					else if (idx == 4)
					{
						strTemp += "/..";
					}

				}
				m_Spread.SetTypeButtonText(strTemp);
			}
			else
			{
				int nPos = m_strFineNick[0].Find(_T(" "), 0);
				if (nPos >= 0)
					m_strFineNick[0] = m_strFineNick[0].Left(nPos);

				m_Spread.SetRow(9);
				if (m_strFineNick[0] == "Highest")
					strTemp = m_strFineNick[0] + "   (90%)";
				else if (m_strFineNick[0] == "VeryHigh")
					strTemp = m_strFineNick[0] + "   (80%)";
				else if (m_strFineNick[0] == "High")
					strTemp = m_strFineNick[0] + "   (70%)";
				else if (m_strFineNick[0] == "Normal")
					strTemp = m_strFineNick[0] + "   (60%)";
				else if (m_strFineNick[0] == "Low")
					strTemp = m_strFineNick[0] + "   (50%)";
				else if (m_strFineNick[0] == "VeryLow")
					strTemp = m_strFineNick[0] + "   (40%)";
				else if (m_strFineNick[0] == "Lowest")
					strTemp = m_strFineNick[0] + "   (30%)";
				else
				{
					m_strFineNick[0] = "Normal";
					strTemp = m_strFineNick[0] + "   (60%)";
				}

				m_Spread.SetText(strTemp);
				m_Spread.SetCellNote(_T("GigaVis _ Note 25 !!!"));
				SetSpecAccessItem(1, 9);
			}
			m_Spread.SetCellNote(_T("GigaVis _ Note 25 !!!"));
			SetSpecAccessItem(1, 9);

			m_Spread.SetRow(10);
			if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx == 0)
			{
				strTemp = "";
				for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
				{
					if (idx < 4)
					{
						if (idx)
							strTemp += "/";
						strVal.Format(_T("%s"), GetProtRange(m_strFineProtrusion[idx]));
						strTemp += strVal;
					}
					else if (idx == 4)
					{
						strTemp += "/..";
					}

				}
				m_Spread.SetTypeButtonText(strTemp);
			}
			else
			{
				int nPos = m_strFineProtrusion[0].Find(_T(" "), 0);
				if (nPos >= 0)
					m_strFineProtrusion[0] = m_strFineProtrusion[0].Left(nPos);


				m_Spread.SetRow(10);
				if (m_strFineProtrusion[0] == "Highest")
					strTemp = m_strFineProtrusion[0] + "   (110%)";
				else if (m_strFineProtrusion[0] == "VeryHigh")
					strTemp = m_strFineProtrusion[0] + "   (120%)";
				else if (m_strFineProtrusion[0] == "High")
					strTemp = m_strFineProtrusion[0] + "   (130%)";
				else if (m_strFineProtrusion[0] == "Normal")
					strTemp = m_strFineProtrusion[0] + "   (140%)";
				else if (m_strFineProtrusion[0] == "Low")
					strTemp = m_strFineProtrusion[0] + "   (150%)";
				else if (m_strFineProtrusion[0] == "VeryLow")
					strTemp = m_strFineProtrusion[0] + "   (160%)";
				else if (m_strFineProtrusion[0] == "Lowest")
					strTemp = m_strFineProtrusion[0] + "   (170%)";
				else
				{
					m_strFineProtrusion[0] = "Normal";
					strTemp = m_strFineProtrusion[0] + "   (140%)";
				}
				m_Spread.SetText(strTemp);
				m_Spread.SetCellNote(_T("GigaVis _ Note 26 !!!"));

				SetSpecAccessItem(1, 10);
			}
			m_Spread.SetCellNote(_T("GigaVis _ Note 26 !!!"));
			SetSpecAccessItem(1, 10);
		}
		else
		{
			m_Spread.SetRow(9);

			if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx == 0)
			{
				strTemp = "";
				for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
				{
					if (idx < 4)
					{
						if (idx)
							strTemp += "/";
						strVal.Format(_T("%d"), m_nFineNickPercent[idx]);
						strTemp += strVal;
					}
					else if (idx == 4)
					{
						strTemp += "/..";
					}

				}
				m_Spread.SetTypeButtonText(strTemp);
			}
			else
			{
				m_Spread.SetRow(9);
				strTemp.Format(_T("%d"), m_nFineNickPercent[0]);
				m_Spread.SetText(strTemp);
				m_Spread.SetCellNote(_T("GigaVis _ Note 25 !!!"));

				SetSpecAccessItem(1, 9);
			}
			m_Spread.SetCellNote(_T("GigaVis _ Note 25 !!!"));
			SetSpecAccessItem(1, 9);

			m_Spread.SetRow(10);
			if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx == 0)
			{
				strTemp = "";
				for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
				{
					if (idx < 4)
					{
						if (idx)
							strTemp += "/";
						strVal.Format(_T("%d"), m_nFineProtrusionPercent[idx]);
						strTemp += strVal;
					}
					else if (idx == 4)
					{
						strTemp += "/..";
					}

				}
				m_Spread.SetTypeButtonText(strTemp);
			}
			else
			{
				m_Spread.SetRow(10);
				strTemp.Format(_T("%d"), m_nFineProtrusionPercent[0]);
				m_Spread.SetText(strTemp);
				m_Spread.SetCellNote(_T("GigaVis _ Note 26 !!!"));
				SetSpecAccessItem(1, 10);
			}
			m_Spread.SetCellNote(_T("GigaVis _ Note 26 !!!"));
			SetSpecAccessItem(1, 10);
		}

		m_Spread.SetRow(11);

		if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx == 0)
		{
			strTemp = "";
			for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
			{
				if (idx < 4)
				{
					if (idx)
						strTemp += "/";
					strVal.Format(_T("%d"), m_nFineNickNGFilterPercent[idx]);
					strTemp += strVal;
				}
				else if (idx == 4)
				{
					strTemp += "/..";
				}

			}
			m_Spread.SetTypeButtonText(strTemp);
		}
		else
		{
			m_Spread.SetRow(11);
			strTemp.Format(_T("%d"), m_nFineNickNGFilterPercent[0]);
			m_Spread.SetValueEx(strTemp);
			m_Spread.SetCellNote(_T("GigaVis _ Note 27 !!!"));
			SetSpecAccessItem(1, 11);

		}


		m_Spread.SetCellNote(_T("GigaVis _ Note 27 !!!"));
		SetSpecAccessItem(1, 11);

		m_Spread.SetRow(12);

		if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx == 0)
		{
			strTemp = "";
			for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
			{
				if (idx < 4)
				{
					if (idx)
						strTemp += "/";
					strVal.Format(_T("%d"), m_nFineExcsNGFilterPercent[idx]);
					strTemp += strVal;
				}
				else if (idx == 4)
				{
					strTemp += "/..";
				}

			}
			m_Spread.SetTypeButtonText(strTemp);
		}
		else
		{
			m_Spread.SetRow(12);
			strTemp.Format(_T("%d"), m_nFineExcsNGFilterPercent[0]);
			m_Spread.SetText(strTemp);
			m_Spread.SetCellNote(_T("GigaVis _ Note 28 !!!"));
			SetSpecAccessItem(1, 12);
		}

		m_Spread.SetCellNote(_T("GigaVis _ Note 28 !!!"));
		SetSpecAccessItem(1, 12);

		m_Spread.SetRow(13);

		if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx == 0)
		{
			strTemp = "";
			for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
			{
				if (idx < 4)
				{
					if (idx)
						strTemp += "/";
					strVal.Format(_T("%.1f"), m_fFineLineWdDeltaGradViolation[idx]);
					strTemp += strVal;
				}
				else if (idx == 4)
				{
					strTemp += "/..";
				}

			}
			m_Spread.SetTypeButtonText(strTemp);
		}
		else
		{
			m_Spread.SetRow(13);
			strTemp.Format(_T("%.2f"), m_fFineLineWdDeltaGradViolation[0]);
			m_Spread.SetText(strTemp);
			m_Spread.SetCellNote(_T("GigaVis _ Note 29 !!!"));
			SetSpecAccessItem(1, 13);
		}

		m_Spread.SetCellNote(_T("GigaVis _ Note 29 !!!"));
		SetSpecAccessItem(1, 13);

		m_Spread.SetRow(14);

		if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx == 0)
		{
			strTemp = "";
			for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
			{
				if (idx < 4)
				{
					if (idx)
						strTemp += "/";
					strVal.Format(_T("%.1f"), m_fFineExcsWdDeltaGradViolation[idx]);
					strTemp += strVal;
				}
				else if (idx == 4)
				{
					strTemp += "/..";
				}

			}
			m_Spread.SetTypeButtonText(strTemp);
		}
		else
		{
			m_Spread.SetRow(14);
			strTemp.Format(_T("%.2f"), m_fFineExcsWdDeltaGradViolation[0]);
			m_Spread.SetText(strTemp);
			m_Spread.SetCellNote(_T("GigaVis _ Note 30 !!!"));
			SetSpecAccessItem(1, 14);

		}

		m_Spread.SetCellNote(_T("GigaVis _ Note 30 !!!"));
		SetSpecAccessItem(1, 14);

		m_Spread.SetRow(15);

		if (SpecData.nLineWidthGroupNum > 0)
		{
			strTemp = "";
			for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
			{
				if (idx < 4)
				{
					if (idx)
						strTemp += "/";
					strVal.Format(_T("%.1f"), m_fFineNarrowTraceViolation[idx]);
					strTemp += strVal;
				}
				else if (idx == 4)
				{
					strTemp += "/..";
				}

			}
			m_Spread.SetTypeButtonText(strTemp);
		}

		m_Spread.SetCellNote(_T("GigaVis _ Note 31 !!!"));
		SetSpecAccessItem(1, 15);

		m_Spread.SetRow(16);
		if (SpecData.nLineWidthGroupNum > 0)
		{
			strTemp = "";
			for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
			{
				if (idx < 4)
				{
					if (idx)
						strTemp += "/";
					strVal.Format(_T("%.1f"), m_fFineWideTraceViolation[idx]);
					strTemp += strVal;
				}
				else if (idx == 4)
				{
					strTemp += "/..";
				}
			}
			m_Spread.SetTypeButtonText(strTemp);
		}

		m_Spread.SetCellNote(_T("GigaVis _ Note 32 !!!"));
		SetSpecAccessItem(1, 16);
	}

	m_bEnableCheckBox = TRUE;
	DisplayChangedData();*/
}

void CDlgSpec::LoadSpreadDataTab2()
{
/*	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	CString strTemp;

	m_Spread.SetCol(1);

	m_Spread.SetRow(1);
	strTemp.Format(_T("%d"), m_MinSpGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 45 !!!"));
	SetSpecAccessItem(2, 1);

	//20090412 hjc	
	m_Spread.SetRow(2);
	strTemp.Format(_T("%d"), m_nNeibSpGrayDiff);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 46 !!!"));
	SetSpecAccessItem(2, 2);

	//150413 hjc add
	m_Spread.SetRow(3);
	strTemp.Format(_T("%d"), m_nUSDarkGrayMinus);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 47 !!!"));
	SetSpecAccessItem(2, 3);

	m_Spread.SetRow(4);
	strTemp.Format(_T("%.1f"), m_fMinSpWidth);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 48 !!!"));
	SetSpecAccessItem(2, 4);

	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
		//170217 lgh
		int nPos = m_strMinSP.Find(_T(" "), 0);
		if (nPos >= 0)
			m_strMinSP = m_strMinSP.Left(nPos);

		m_Spread.SetRow(5);
		if (m_strMinSP == "Highest")
			strTemp = m_strMinSP + "   (90%)";
		else if (m_strMinSP == "VeryHigh")
			strTemp = m_strMinSP + "   (80%)";
		else if (m_strMinSP == "High")
			strTemp = m_strMinSP + "   (70%)";
		else if (m_strMinSP == "Normal")
			strTemp = m_strMinSP + "   (60%)";
		else if (m_strMinSP == "Low")
			strTemp = m_strMinSP + "   (50%)";
		else if (m_strMinSP == "VeryLow")
			strTemp = m_strMinSP + "   (40%)";
		else if (m_strMinSP == "Lowest")
			strTemp = m_strMinSP + "   (30%)";
		else
		{
			m_strMinSP = "Normal";
			strTemp = m_strMinSP + "   (60%)";
		}

		m_Spread.SetText(strTemp);
		m_Spread.SetCellNote(_T("GigaVis _ Note 48 !!!"));
		SetSpecAccessItem(2, 5);

	}
	else
	{
		m_Spread.SetRow(5);
		strTemp.Format(_T("%d"), m_nMinSPPercent);
		m_Spread.SetText(strTemp);
		m_Spread.SetCellNote(_T("GigaVis _ Note 48 !!!"));
		SetSpecAccessItem(2, 5);

	}

	m_Spread.SetRow(6);
	strTemp.Format(_T("%d"), m_nSpaceNGFilterPercent);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 49 !!!"));
	SetSpecAccessItem(2, 6);

	//20090228 hjc
	m_Spread.SetRow(7);
	strTemp.Format(_T("%.2f"), m_fSpWdDeltaGradViolation);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 50 !!!"));
	SetSpecAccessItem(2, 7);

	//20090405 hjc
	m_Spread.SetRow(8);
	strTemp.Format(_T("%.2f"), m_fSpWdDeltaOuterGradViolation);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 51 !!!"));
	SetSpecAccessItem(2, 8);

	m_Spread.SetRow(9);	//121226 hjc add	
	strTemp.Format(_T("%.1f"), m_fFineMinSpWidth);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 53 !!!"));
	//-------------------
	SetSpecAccessItem(2, 9);

	m_bEnableCheckBox = TRUE;
	DisplayChangedData();*/
}

void CDlgSpec::LoadSpreadDataTab3()
{
/*	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	CString strTemp;
	int nHighest, nVeryHigh, nHigh, nNormal, nLow, nVeryLow, nLowest;

	m_Spread.SetCol(1);

	m_Spread.SetRow(1);
	strTemp.Format(_T("%d"), m_nPinHoleGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 72 !!!"));
	SetSpecAccessItem(3, 1);


	m_Spread.SetRow(2);
	//strTemp.Format(_T("%.1f"), m_fRealNormLine);

	DecisionPixelAdjust(m_strLP_Prec, SpecData.LPADRL_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);

	//170217 lgh
	int nPos = m_strLP_Prec.Find(_T(" "), 0);
	if (nPos >= 0)
		m_strLP_Prec = m_strLP_Prec.Left(nPos);

	//160314 hjc relive
	if (m_strLP_Prec == _T("Highest"))
		strTemp.Format(_T("%s   (%d)"), (m_strLP_Prec), nHighest);
	if (m_strLP_Prec == "VeryHigh")
		strTemp.Format(_T("%s   (%d)"), (m_strLP_Prec), nVeryHigh);
	if (m_strLP_Prec == "High")
		strTemp.Format(_T("%s   (%d)"), (m_strLP_Prec), nHigh);
	if (m_strLP_Prec == "Normal")
		strTemp.Format(_T("%s   (%d)"), (m_strLP_Prec), nNormal);
	if (m_strLP_Prec == "Low")
		strTemp.Format(_T("%s   (%d)"), (m_strLP_Prec), nLow);
	if (m_strLP_Prec == "VeryLow")
		strTemp.Format(_T("%s   (%d)"), (m_strLP_Prec), nVeryLow);
	if (m_strLP_Prec == "Lowest")
		strTemp.Format(_T("%s   (%d)"), (m_strLP_Prec), nLowest);

	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 73 !!!"));
	SetSpecAccessItem(3, 2);

	m_Spread.SetRow(3);
	strTemp.Format(_T("%.1f"), m_fPinHoleMin);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 74 !!!"));
	SetSpecAccessItem(3, 3);

	m_Spread.SetRow(4);
	strTemp.Format(_T("%d"), m_nIsLandGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 75 !!!"));
	SetSpecAccessItem(3, 4);

	m_Spread.SetRow(5);

	//170112 hjc mod
	DecisionPixelAdjust(m_strSP_Prec, SpecData.LSpaceRL_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);

	if (m_strSP_Prec == _T("Highest"))
		strTemp.Format(_T("%s   (%d)"), (m_strSP_Prec), nHighest);
	if (m_strSP_Prec == "VeryHigh")
		strTemp.Format(_T("%s   (%d)"), (m_strSP_Prec), nVeryHigh);
	if (m_strSP_Prec == "High")
		strTemp.Format(_T("%s   (%d)"), (m_strSP_Prec), nHigh);
	if (m_strSP_Prec == "Normal")
		strTemp.Format(_T("%s   (%d)"), (m_strSP_Prec), nNormal);
	if (m_strSP_Prec == "Low")
		strTemp.Format(_T("%s   (%d)"), (m_strSP_Prec), nLow);
	if (m_strSP_Prec == "VeryLow")
		strTemp.Format(_T("%s   (%d)"), (m_strSP_Prec), nVeryLow);
	if (m_strSP_Prec == "Lowest")
		strTemp.Format(_T("%s   (%d)"), (m_strSP_Prec), nLowest);

	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 76 !!!"));
	SetSpecAccessItem(3, 5);

	m_Spread.SetRow(6);
	strTemp.Format(_T("%.1f"), m_fIsLandMin);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 77 !!!"));
	SetSpecAccessItem(3, 6);

	//20090412 hjc
	m_Spread.SetRow(7);
	strTemp.Format(_T("%d"), m_nIsLandExtGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 78 !!!"));
	SetSpecAccessItem(3, 7);

	//170112 hjc add
	m_Spread.SetRow(8);
	DecisionPixelAdjust(m_strSPExt_Prec, SpecData.SpaceExtRL_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);

	if (m_strSPExt_Prec == _T("Highest"))
		strTemp.Format(_T("%s   (%d)"), (m_strSPExt_Prec), nHighest);
	if (m_strSPExt_Prec == "VeryHigh")
		strTemp.Format(_T("%s   (%d)"), (m_strSPExt_Prec), nVeryHigh);
	if (m_strSPExt_Prec == "High")
		strTemp.Format(_T("%s   (%d)"), (m_strSPExt_Prec), nHigh);
	if (m_strSPExt_Prec == "Normal")
		strTemp.Format(_T("%s   (%d)"), (m_strSPExt_Prec), nNormal);
	if (m_strSPExt_Prec == "Low")
		strTemp.Format(_T("%s   (%d)"), (m_strSPExt_Prec), nLow);
	if (m_strSPExt_Prec == "VeryLow")
		strTemp.Format(_T("%s   (%d)"), (m_strSPExt_Prec), nVeryLow);
	if (m_strSPExt_Prec == "Lowest")
		strTemp.Format(_T("%s   (%d)"), (m_strSPExt_Prec), nLowest);

	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 79 !!!"));
	SetSpecAccessItem(3, 8);

	m_Spread.SetRow(9);
	strTemp.Format(_T("%.1f"), m_fIsLandExtMin);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 80 !!!"));
	SetSpecAccessItem(3, 9);

	//jun 20120903 for LG_CCL-Inspector
	m_Spread.SetRow(10);
	strTemp.Format(_T("%d"), m_nCCLGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 81 !!!"));
	SetSpecAccessItem(3, 10);

	m_Spread.SetRow(11);
	strTemp.Format(_T("%.1f"), m_fCCLCircularity);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 82 !!!"));
	SetSpecAccessItem(3, 11);

	m_Spread.SetRow(12);
	strTemp.Format(_T("%.1f"), m_fCCLDefSize);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 83 !!!"));
	//------------
	SetSpecAccessItem(3, 12);


	if (SpecData.bEnableCharInspection)
	{
		m_Spread.SetRow(13);
		strTemp.Format(_T("%d"), m_nCharInspectionGray);
		m_Spread.SetText(strTemp);
		m_Spread.SetCellNote(_T("GigaVis _ Note 84 !!!"));
		//------------
		SetSpecAccessItem(3, 13);

		m_Spread.SetRow(14);
		strTemp.Format(_T("%.1f"), m_dCharRegionUpperPercent);
		m_Spread.SetText(strTemp);
		m_Spread.SetCellNote(_T("GigaVis _ Note 85 !!!"));
		//------------
		SetSpecAccessItem(3, 14);

		m_Spread.SetRow(15);
		strTemp.Format(_T("%.1f"), m_dCharRegionLowerPercent);
		m_Spread.SetText(strTemp);
		m_Spread.SetCellNote(_T("GigaVis _ Note 86 !!!"));
		//------------
		SetSpecAccessItem(3, 15);
	}

	m_bEnableCheckBox = TRUE;
	DisplayChangedData();*/
}

void CDlgSpec::LoadSpreadDataTab4()
{
/*	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	CString strTemp;
	int nHighest, nVeryHigh, nHigh, nNormal, nLow, nVeryLow, nLowest;

	m_Spread.SetCol(1);

	m_Spread.SetRow(1);
	strTemp.Format(_T("%d"), SpecData.nVDrillDiffBrightGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 57 !!!"));
	SetSpecAccessItem(4, 1);

	m_Spread.SetRow(2);
	strTemp.Format(_T("%d"), SpecData.nVDrillDiffDarkGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 57 !!!"));
	SetSpecAccessItem(4, 2);

	m_Spread.SetRow(3);
	strTemp.Format(_T("%.1f"), SpecData.fVDPadPrecName);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 58 !!!"));
	SetSpecAccessItem(4, 3);

	//20090419 hjc
	m_Spread.SetRow(4);
	strTemp.Format(_T("%.1f"), m_fVDLocationTolerance);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 59 !!!"));
	//-----------
	SetSpecAccessItem(4, 4);

	m_Spread.SetRow(5);
	strTemp.Format(_T("%.1f"), m_fVDPadMin);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 60 !!!"));
	SetSpecAccessItem(4, 5);

	m_Spread.SetRow(6);
	strTemp.Format(_T("%d"), m_nPADVoidGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 61 !!!"));
	SetSpecAccessItem(4, 6);

	m_Spread.SetRow(7);

	DecisionPixelAdjust(m_strPadBallPrec, SpecData.PADRL_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);
	//160314 hjc relive
	if (m_strPadBallPrec == "Highest")
		strTemp.Format(_T("%s   (%d)"), (m_strPadBallPrec), nHighest);
	if (m_strPadBallPrec == "VeryHigh")
		strTemp.Format(_T("%s   (%d)"), (m_strPadBallPrec), nVeryHigh);
	if (m_strPadBallPrec == "High")
		strTemp.Format(_T("%s   (%d)"), (m_strPadBallPrec), nHigh);
	if (m_strPadBallPrec == "Normal")
		strTemp.Format(_T("%s   (%d)"), (m_strPadBallPrec), nNormal);
	if (m_strPadBallPrec == "Low")
		strTemp.Format(_T("%s   (%d)"), (m_strPadBallPrec), nLow);
	if (m_strPadBallPrec == "VeryLow")
		strTemp.Format(_T("%s   (%d)"), (m_strPadBallPrec), nVeryLow);
	if (m_strPadBallPrec == "Lowest")
		strTemp.Format(_T("%s   (%d)"), (m_strPadBallPrec), nLowest);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 62 !!!"));
	SetSpecAccessItem(4, 7);

	m_Spread.SetRow(8);
	strTemp.Format(_T("%.1f"), m_fPADVoidMin);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 63 !!!"));
	SetSpecAccessItem(4, 8);

	m_Spread.SetRow(9);
	//strTemp.Format(_T("%.1f"), m_fRealNormLine);

	//170112 hjc mod
	DecisionPixelAdjust(m_strPadTip_Prec, SpecData.PADTip_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);

	if (m_strPadTip_Prec == "Highest")
		strTemp.Format(_T("%s   (%d)"), (m_strPadTip_Prec), nHighest);
	if (m_strPadTip_Prec == "VeryHigh")
		strTemp.Format(_T("%s   (%d)"), (m_strPadTip_Prec), nVeryHigh);
	if (m_strPadTip_Prec == "High")
		strTemp.Format(_T("%s   (%d)"), (m_strPadTip_Prec), nHigh);
	if (m_strPadTip_Prec == "Normal")
		strTemp.Format(_T("%s   (%d)"), (m_strPadTip_Prec), nNormal);
	if (m_strPadTip_Prec == "Low")
		strTemp.Format(_T("%s   (%d)"), (m_strPadTip_Prec), nLow);
	if (m_strPadTip_Prec == "VeryLow")
		strTemp.Format(_T("%s   (%d)"), (m_strPadTip_Prec), nVeryLow);
	if (m_strPadTip_Prec == "Lowest")
		strTemp.Format(_T("%s   (%d)"), (m_strPadTip_Prec), nLowest);

	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 64 !!!"));
	SetSpecAccessItem(4, 9);

	m_Spread.SetRow(10);
	strTemp.Format(_T("%.1f"), m_fPADTipMin);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 65 !!!"));
	SetSpecAccessItem(4, 10);

	m_Spread.SetRow(11);
	strTemp.Format(_T("%d"), m_nHoleLandVoidGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 65 !!!"));
	SetSpecAccessItem(4, 11);

	m_Spread.SetRow(12);
	//strTemp.Format(_T("%.1f", m_fRealNormLine);

	//170111 hjc mod
	DecisionPixelAdjust(m_strARLand_Prec, SpecData.ARLand_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);

	if (m_strARLand_Prec == "Highest")
		strTemp.Format(_T("%s   (%d)"), (m_strARLand_Prec), nHighest);
	if (m_strARLand_Prec == "VeryHigh")
		strTemp.Format(_T("%s   (%d)"), (m_strARLand_Prec), nVeryHigh);
	if (m_strARLand_Prec == "High")
		strTemp.Format(_T("%s   (%d)"), (m_strARLand_Prec), nHigh);
	if (m_strARLand_Prec == "Normal")
		strTemp.Format(_T("%s   (%d)"), (m_strARLand_Prec), nNormal);
	if (m_strARLand_Prec == "Low")
		strTemp.Format(_T("%s   (%d)"), (m_strARLand_Prec), nLow);
	if (m_strARLand_Prec == "VeryLow")
		strTemp.Format(_T("%s   (%d)"), (m_strARLand_Prec), nVeryLow);
	if (m_strARLand_Prec == "Lowest")
		strTemp.Format(_T("%s   (%d)"), (m_strARLand_Prec), nLowest);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 66 !!!"));
	SetSpecAccessItem(4, 12);

	m_Spread.SetRow(13);
	strTemp.Format(_T("%.1f"), m_fARLandMin);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 67 !!!"));
	SetSpecAccessItem(4, 13);

	m_Spread.SetRow(14);
	strTemp.Format(_T("%.1f"), SpecData.fHoleFillExt);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 68 !!!"));
	SetSpecAccessItem(4, 14);

	//20100322 hjc add
	m_Spread.SetRow(15);
	strTemp.Format(_T("%d"), m_nCO2LandVoidGraySpec);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 74 !!!"));
	SetSpecAccessItem(4, 15);

	m_Spread.SetRow(16);
	//170111 hjc mod
	DecisionPixelAdjust(m_strCO2Land_Prec, SpecData.CO2Land_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);

	if (m_strCO2Land_Prec == "Highest")
		strTemp.Format(_T("%s   (%d)"), (m_strCO2Land_Prec), nHighest);
	if (m_strCO2Land_Prec == "VeryHigh")
		strTemp.Format(_T("%s   (%d)"), (m_strCO2Land_Prec), nVeryHigh);
	if (m_strCO2Land_Prec == "High")
		strTemp.Format(_T("%s   (%d)"), (m_strCO2Land_Prec), nHigh);
	if (m_strCO2Land_Prec == "Normal")
		strTemp.Format(_T("%s   (%d)"), (m_strCO2Land_Prec), nNormal);
	if (m_strCO2Land_Prec == "Low")
		strTemp.Format(_T("%s   (%d)"), (m_strCO2Land_Prec), nLow);
	if (m_strCO2Land_Prec == "VeryLow")
		strTemp.Format(_T("%s   (%d)"), (m_strCO2Land_Prec), nVeryLow);
	if (m_strCO2Land_Prec == "Lowest")
		strTemp.Format(_T("%s   (%d)"), (m_strCO2Land_Prec), nLowest);

	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 73 !!!"));
	SetSpecAccessItem(4, 16);



	m_Spread.SetRow(17);
	strTemp.Format(_T("%.1f"), m_fCO2LandMin);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 74 !!!"));
	SetSpecAccessItem(4, 17);

	m_Spread.SetRow(18);
	if (strcmp(SpecData.szCO2LandAlignMode, "Yes") == 0)
	{
		SpecData.nCO2LandAlignMode = 1;
		strTemp.Format(_T("%s"), CharToString(SpecData.szCO2LandAlignMode));
	}
	else
	{
		SpecData.nCO2LandAlignMode = 0;
		strTemp.Format(_T("%s"), CharToString(SpecData.szCO2LandAlignMode));
	}
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 73 !!!"));
	SetSpecAccessItem(4, 18);

	//20100323 hjc add
	m_Spread.SetRow(19);
	strTemp.Format(_T("%.1f"), SpecData.fCO2HoleFillExt);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 68 !!!"));
	SetSpecAccessItem(4, 19);

	m_Spread.SetRow(20);
	strTemp.Format(_T("%d"), m_nFinePADVoidGraySpec);	//20090419 hjc
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 69 !!!"));
	SetSpecAccessItem(4, 20);

	m_Spread.SetRow(21);
	//strTemp.Format(_T("%.1f"), m_fRealNormLine);
	//170111 hjc mod
	DecisionPixelAdjust(m_strFPad_Prec, SpecData.PADFine_Prec, SpecData.nRLEPrecisionStepSize, &nHighest, &nVeryHigh, &nHigh, &nNormal, &nLow, &nVeryLow, &nLowest);

	if (m_strFPad_Prec == "Highest")
		strTemp.Format(_T("%s   (%d)"), (m_strFPad_Prec), nHighest);
	if (m_strFPad_Prec == "VeryHigh")
		strTemp.Format(_T("%s   (%d)"), (m_strFPad_Prec), nVeryHigh);
	if (m_strFPad_Prec == "High")
		strTemp.Format(_T("%s   (%d)"), (m_strFPad_Prec), nHigh);
	if (m_strFPad_Prec == "Normal")
		strTemp.Format(_T("%s   (%d)"), (m_strFPad_Prec), nNormal);
	if (m_strFPad_Prec == "Low")
		strTemp.Format(_T("%s   (%d)"), (m_strFPad_Prec), nLow);
	if (m_strFPad_Prec == "VeryLow")
		strTemp.Format(_T("%s   (%d)"), (m_strFPad_Prec), nVeryLow);
	if (m_strFPad_Prec == "Lowest")
		strTemp.Format(_T("%s   (%d)"), (m_strFPad_Prec), nLowest);

	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 70 !!!"));
	SetSpecAccessItem(4, 21);

	m_Spread.SetRow(22);
	strTemp.Format(_T("%.1f"), m_fFineVDPadMin);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 71 !!!"));
	//------------
	SetSpecAccessItem(4, 22);

	m_bEnableCheckBox = TRUE;
	DisplayChangedData();*/
}

void CDlgSpec::LoadSpreadDataTab5()
{
/*	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	CString strTemp;

	m_Spread.SetCol(1);

	//20090311 hjc modify
	m_Spread.SetRow(1);
	strTemp.Format(_T("%.1f"), m_fHoleTolerance);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 79 !!!"));
	SetSpecAccessItem(5, 1);

	m_Spread.SetRow(2);
	strTemp.Format(_T("%.1f"), m_fHoleDiaUpper);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 85 !!!"));
	SetSpecAccessItem(5, 2);

	m_Spread.SetRow(3);
	strTemp.Format(_T("%.1f"), m_fHoleDiaLower);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 86 !!!"));
	SetSpecAccessItem(5, 3);

	m_Spread.SetRow(4);
	strTemp.Format(_T("%d"), m_nHoleOpenGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 81 !!!"));
	SetSpecAccessItem(5, 4);

	m_Spread.SetRow(5);
	strTemp.Format(_T("%d"), m_nHoleMissingGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 82 !!!"));
	SetSpecAccessItem(5, 5);

	m_Spread.SetRow(6);
	strTemp.Format(_T("%d"), m_nHoleInnerGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 83 !!!"));
	SetSpecAccessItem(5, 6);

	m_Spread.SetRow(7);
	strTemp = m_strHolePrec;
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 80 !!!"));
	SetSpecAccessItem(5, 7);

	m_Spread.SetRow(8);
	strTemp.Format(_T("%d"), m_nHoleDefSize);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 84 !!!"));
	SetSpecAccessItem(5, 8);

	m_Spread.SetRow(9);
	strTemp.Format(_T("%s"), CharToString(SpecData.szVHMode));
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 87 !!!"));
	SetSpecAccessItem(5, 9);

	m_Spread.SetRow(10);
	strTemp.Format(_T("%d"), m_nCO2MissingGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 88 !!!"));
	SetSpecAccessItem(5, 10);

	m_Spread.SetRow(11);
	strTemp.Format(_T("%d"), m_nCO2HoleNum);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 89 !!!"));
	SetSpecAccessItem(5, 11);

	m_Spread.SetRow(12);
	strTemp.Format(_T("%d"), m_nCO2OpenGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 90 !!!"));
	SetSpecAccessItem(5, 12);

	m_Spread.SetRow(13);
	strTemp.Format(_T("%d"), m_nCO2MisAgnGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 91 !!!"));
	SetSpecAccessItem(5, 13);

	m_Spread.SetRow(14);
	strTemp.Format(_T("%d"), m_nCO2MisAgnDefPercent);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 92 !!!"));
	SetSpecAccessItem(5, 14);

	m_Spread.SetRow(15);
	strTemp.Format(_T("%d"), SpecData.nVHEdgeThrDiffGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 93 !!!"));
	SetSpecAccessItem(5, 15);

	m_Spread.SetRow(16);
	strTemp.Format(_T("%d"), SpecData.nVHBreakOutGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 94 !!!"));
	SetSpecAccessItem(5, 16);

	m_Spread.SetRow(17);
	strTemp.Format(_T("%d"), SpecData.nVHDissmearGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 95 !!!"));
	SetSpecAccessItem(5, 17);

	m_Spread.SetRow(18);
	strTemp.Format(_T("%d"), SpecData.nVHContiBreakOutNum);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 96 !!!"));
	SetSpecAccessItem(5, 18);

	m_bEnableCheckBox = TRUE;
	DisplayChangedData();*/
}

void CDlgSpec::LoadSpreadDataTab6()
{
/*	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	CString strTemp;

	m_Spread.SetCol(1);

	//20090228 modify hjc 1~6
	m_Spread.SetRow(1);
	strTemp.Format(_T("%d"), m_nPadEdgeNickGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 97 !!!"));
	SetSpecAccessItem(6, 1);

	//120105 hjc add
	m_Spread.SetRow(2);
	strTemp.Format(_T("%d"), m_nPadEdgeNeibGrayDiff);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 98 !!!"));
	SetSpecAccessItem(6, 2);

	//150413 hjc add
	m_Spread.SetRow(3);
	strTemp.Format(_T("%d"), m_nPadEdgeBADiffDarkGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 98 !!!"));
	SetSpecAccessItem(6, 3);

	m_Spread.SetRow(4);
	strTemp.Format(_T("%.1f"), m_fPadEdgeNickWdDeltaGradViolation);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 99 !!!"));
	SetSpecAccessItem(6, 4);

	m_Spread.SetRow(5);
	strTemp.Format(_T("%.1f"), m_fPadEdgeExcsWdDeltaGradViolation);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 100 !!!"));
	SetSpecAccessItem(6, 5);

	//------------------------
	//20090412 hjc
	m_Spread.SetRow(6);
	strTemp.Format(_T("%d"), m_nPadVDEdgeGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 101 !!!"));
	SetSpecAccessItem(6, 6);

	m_Spread.SetRow(7);
	strTemp.Format(_T("%.2f"), m_fPadVDEdgeWdDeltaGradViolation);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 102 !!!"));
	//------------------------------------
	SetSpecAccessItem(6, 7);

	m_Spread.SetRow(8);
	strTemp.Format(_T("%d"), m_nHoleEdgeNickGray);	//111214 hjc add
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 103 !!!"));
	SetSpecAccessItem(6, 8);

	//120109 hjc add
	m_Spread.SetRow(9);
	strTemp.Format(_T("%d"), m_nHoleEdgeNeibGrayDiff);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 104 !!!"));
	SetSpecAccessItem(6, 9);

	m_Spread.SetRow(10);
	strTemp.Format(_T("%.1f"), m_fHoleEdgeNickWdDeltaGradViolation);
	m_Spread.SetValueEx(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 105 !!!"));
	SetSpecAccessItem(6, 10);

	m_Spread.SetRow(11);
	strTemp.Format(_T("%.1f"), m_fHoleEdgeExcsWdDeltaGradViolation);
	m_Spread.SetValueEx(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 106 !!!"));
	SetSpecAccessItem(6, 11);

	m_Spread.SetRow(12);
	strTemp.Format(_T("%d"), m_nViaEdgeNickGray);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 107 !!!"));
	SetSpecAccessItem(6, 12);

	//120109 hjc add
	m_Spread.SetRow(13);
	strTemp.Format(_T("%d"), m_nViaEdgeNeibGrayDiff);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 108 !!!"));
	SetSpecAccessItem(6, 13);

	m_Spread.SetRow(14);
	strTemp.Format(_T("%.1f"), m_fViaEdgeNickWdDeltaGradViolation);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 109 !!!"));
	SetSpecAccessItem(6, 14);

	m_Spread.SetRow(15);
	strTemp.Format(_T("%.1f"), m_fViaEdgeExcsWdDeltaGradViolation);
	m_Spread.SetText(strTemp);
	m_Spread.SetCellNote(_T("GigaVis _ Note 110 !!!"));
	SetSpecAccessItem(6, 15);

	m_bEnableCheckBox = TRUE;
	DisplayChangedData();*/
}

void CDlgSpec::LoadSpreadDataTab7()
{
//	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
//	CString strTemp;
//
//	m_Spread.SetCol(1);
//
//	m_Spread.SetRow(1);
//	strTemp.Format(_T("%d"), pGlobalDoc->m_nPtSrchRngExt);
//	m_Spread.SetText(strTemp);
//	m_Spread.SetCellNote(_T("GigaVis _ Note 110!!"));
//	SetSpecAccessItem(7, 1);
//
//	m_Spread.SetRow(2);
//	m_Spread.SetText(m_cboPTMOD_SIZE);
//	m_Spread.SetCellNote(_T("GigaVis _ Note 111!!"));
//	SetSpecAccessItem(7, 2);
//
//	m_Spread.SetRow(3);
//	strTemp.Format(_T("%d"), m_nAlignTolerance);
//	m_Spread.SetText(strTemp);
//	m_Spread.SetCellNote(_T("GigaVis _ Note 112!!"));
//	SetSpecAccessItem(7, 3);
//
//	m_Spread.SetRow(4);
//	m_Spread.SetText(m_strThetaAlign);
//	m_Spread.SetCellNote(_T("GigaVis _ Note 113!!"));
//	SetSpecAccessItem(7, 4);
//
//	m_Spread.SetRow(5);
//	strTemp.Format(_T("%.1f"), m_fDefMaskSize);
//	m_Spread.SetText(strTemp);
//	m_Spread.SetCellNote(_T("GigaVis _ Note 114!!"));
//	SetSpecAccessItem(7, 5);
//
//	m_Spread.SetRow(6);
//	strTemp.Format(_T("%.1f"), m_fNearDefLen);
//	m_Spread.SetText(strTemp);
//	m_Spread.SetCellNote(_T("GigaVis _ Note 115!!"));
//	SetSpecAccessItem(7, 6);
//
//	//20100210 hjc add
//	m_Spread.SetRow(7);
//	if (pGlobalDoc->m_bUseMultiVaccumControl)	//130311 hjc add
//	{
//		if (m_strSelectVaccum == "Both")
//			strTemp = m_strSelectVaccum + "   (1)";
//		if (m_strSelectVaccum == "FirstOnly")
//			strTemp = m_strSelectVaccum + "   (2)";
//	}
//	else
//		strTemp = m_strSelectVaccum = "Both";
//
//	m_Spread.SetText(strTemp);
//	m_Spread.SetCellNote(_T("GigaVis _ Note 116!!"));
//	SetSpecAccessItem(7, 7);
//
//	if (AoiParam()->m_bUseAutoPinPosAdjust || g_bUsePinPosEstimate)
//	{
//		m_Spread.SetRow(8);
//		strTemp.Format(_T("%.1f"), m_dPanelSizeX);
//		m_Spread.SetText(strTemp);
//		m_Spread.SetCellNote(_T("Panel Size X"));
//		m_Spread.SetRow(9);
//		strTemp.Format(_T("%.1f"), m_dPanelSizeY);
//		m_Spread.SetText(strTemp);
//		m_Spread.SetCellNote(_T("Panel Size Y"));
//
//#ifdef IRIS_AXIS
//		strTemp.Format(_T("%.3f"), pGlobalDoc->m_IRISAxisControl.m_dIRISPosName[m_nIRISPosID]);
//		m_Spread.SetRow(10);
//		m_Spread.SetText(strTemp);
//		m_Spread.SetCellNote(_T("GigaVis _ Note 113!!"));
//		SetSpecAccessItem(7, 10);
//#endif
//
//	}
//	else
//	{
//#ifdef IRIS_AXIS
//		strTemp.Format(_T("%.3f"), pGlobalDoc->m_IRISAxisControl.m_dIRISPosName[m_nIRISPosID]);
//		m_Spread.SetRow(8);
//		m_Spread.SetText(strTemp);
//		m_Spread.SetCellNote(_T("GigaVis _ Note 113!!"));
//		SetSpecAccessItem(7, 8);
//#endif
//	}
//
//	m_bEnableCheckBox = TRUE;
//	DisplayChangedData();
}

void CDlgSpec::CheckOriginDataTab0()
{
/*	CString strTemp;
	CString strLog;
	//	strTemp.Format("%.1f", m_fNominalLine);
	//	m_strOriginData[0][1]=strTemp;

	if (fabs(_ttof(m_strOriginData[0][1]) - m_fNominalLine) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(0, 1),
			m_strOriginData[0][1],
			m_fNominalLine);
		SaveSpecLog(strLog);
	}


	//	strTemp.Format("%.1f", m_fRealNormLine);
	//	m_strOriginData[0][2]=strTemp;

	if (fabs(_ttof(m_strOriginData[0][2]) - m_fRealNormLine) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(0, 2),
			m_strOriginData[0][2],
			m_fRealNormLine);
		SaveSpecLog(strLog);
	}

	//	strTemp.Format("%d", m_nNickGray);
	//	m_strOriginData[0][3]=strTemp;	

	if (_ttoi(m_strOriginData[0][3]) != m_nNickGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(0, 3),
			m_strOriginData[0][3],
			m_nNickGray);
		SaveSpecLog(strLog);
	}

	//20090216 chg
	//	strTemp.Format("%d", m_nOpenGray);
	//	m_strOriginData[0][4]=strTemp;	

	if (_ttoi(m_strOriginData[0][4]) != m_nOpenGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(0, 4),
			m_strOriginData[0][4],
			m_nOpenGray);
		SaveSpecLog(strLog);
	}

	//	strTemp.Format("%d", m_nHalfSideNickDiffBrightGray);
	//	m_strOriginData[0][5]=strTemp;	

	if (_ttoi(m_strOriginData[0][5]) != m_nHalfSideNickDiffBrightGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(0, 5),
			m_strOriginData[0][5],
			m_nHalfSideNickDiffBrightGray);
		SaveSpecLog(strLog);
	}

	//20090228 hjc
	//	strTemp.Format("%d", m_nHalfSideNickDiffDarkGray);
	//	m_strOriginData[0][6]=strTemp;	

	if (_ttoi(m_strOriginData[0][6]) != m_nHalfSideNickDiffDarkGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(0, 6),
			m_strOriginData[0][6],
			m_nHalfSideNickDiffDarkGray);
		SaveSpecLog(strLog);
	}

	//	strTemp.Format("%d", m_nLeadOpenGray);
	//	m_strOriginData[0][7]=strTemp;	

	if (_ttoi(m_strOriginData[0][7]) != m_nLeadOpenGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(0, 7),
			m_strOriginData[0][7],
			m_nLeadOpenGray);
		SaveSpecLog(strLog);
	}

	//	strTemp.Format("%.1f", m_fMinCheckWidth);
	//	m_strOriginData[0][8]=strTemp;	

	if (fabs(_ttof(m_strOriginData[0][8]) - m_fMinCheckWidth) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(0, 8),
			m_strOriginData[0][8],
			m_fMinCheckWidth);
		SaveSpecLog(strLog);
	}



	//	m_strOriginData[0][9]=m_strNick;

	//	m_strOriginData[0][10]=m_strProtrusion;	

	if (pGlobalDoc->m_bUseCombo)
	{
		if (m_strOriginData[0][9] != m_strNick[0])
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(0, 9),
				m_strOriginData[0][9],
				m_strNick);
			SaveSpecLog(strLog);
		}

		if (m_strOriginData[0][10] != m_strProtrusion[0])
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(0, 10),
				m_strOriginData[0][10],
				m_strProtrusion[0]);
			SaveSpecLog(strLog);
		}
	}
	else
	{
		if (_ttoi(m_strOriginData[0][9]) != (m_nNickPercent[0]))
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(0, 9),
				m_strOriginData[0][9],
				m_nNickPercent[0]);
			SaveSpecLog(strLog);
		}

		if (_ttoi(m_strOriginData[0][10]) != m_nProtrusionPercent[0])
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(0, 10),
				m_strOriginData[0][10],
				m_nProtrusionPercent[0]);
			SaveSpecLog(strLog);
		}
	}




	if (_ttoi(m_strOriginData[0][11]) != m_nNickNGFilterPercent[0])
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(0, 11),
			m_strOriginData[0][11],
			m_nNickNGFilterPercent[0]);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[0][12]) != m_nExcsNGFilterPercent[0])
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(0, 12),
			m_strOriginData[0][12],
			m_nExcsNGFilterPercent[0]);
		SaveSpecLog(strLog);
	}


	if (fabs(_ttof(m_strOriginData[0][13]) - m_fLineWdDeltaGradViolation[0]) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(0, 13),
			m_strOriginData[0][13],
			m_fLineWdDeltaGradViolation[0]);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[0][14]) - m_fExcsWdDeltaGradViolation[0]) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(0, 15),
			m_strOriginData[0][14],
			m_fExcsWdDeltaGradViolation[0]);
		SaveSpecLog(strLog);
	}

	int idx;
	if (SpecData.nLineWidthGroupNum == 0)
	{
		if (fabs(_ttof(m_strOriginData[0][15]) - m_fNarrowTraceViolation[0]) > 0.01)
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(0, 15),
				m_strOriginData[0][15],
				m_fNarrowTraceViolation[0]);
			SaveSpecLog(strLog);
		}
	}

	if (SpecData.nLineWidthGroupNum == 0)
	{
		if (fabs(_ttof(m_strOriginData[0][16]) - m_fWideTraceViolation[0]) > 0.01)
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(0, 16),
				m_strOriginData[0][16],
				m_fWideTraceViolation[0]);
			SaveSpecLog(strLog);
		}
	}
	*/
}

void CDlgSpec::CheckOriginDataTab1()
{
/*	CString strTemp;
	CString strLog;


	//strTemp.Format(_T("%d"), m_nFineHalfSideNickDiffDarkGray);
	//m_strOriginData[1][6] = strTemp;

	//strTemp.Format(_T("%d"), m_nLeadOpenGray);
	//m_strOriginData[1][7] = strTemp;

	//strTemp.Format(_T("%.1f"), m_fFineMinCheckWidth);
	//m_strOriginData[1][8] = strTemp;


	if (_ttoi(m_strOriginData[1][3]) != m_nFineNickGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(1, 3),
			m_strOriginData[1][3],
			m_nFineNickGray);
		SaveSpecLog(strLog);
	}

	//20090216 chg
	//	strTemp.Format("%d", m_nOpenGray);
	//	m_strOriginData[0][4]=strTemp;	

	if (_ttoi(m_strOriginData[1][4]) != m_nFineOpenGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(1, 4),
			m_strOriginData[1][4],
			m_nFineOpenGray);
		SaveSpecLog(strLog);
	}

	//	strTemp.Format("%d", m_nHalfSideNickDiffBrightGray);
	//	m_strOriginData[0][5]=strTemp;	

	if (_ttoi(m_strOriginData[1][5]) != m_nFineHalfSideNickDiffBrightGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(1, 5),
			m_strOriginData[1][5],
			m_nFineHalfSideNickDiffBrightGray);
		SaveSpecLog(strLog);
	}

	//20090228 hjc
	//	strTemp.Format("%d", m_nHalfSideNickDiffDarkGray);
	//	m_strOriginData[0][6]=strTemp;	

	if (_ttoi(m_strOriginData[1][6]) != m_nFineHalfSideNickDiffDarkGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(1, 6),
			m_strOriginData[1][6],
			m_nFineHalfSideNickDiffDarkGray);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[1][8]) - m_fFineMinCheckWidth) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(1, 8),
			m_strOriginData[1][8],
			m_fFineMinCheckWidth);
		SaveSpecLog(strLog);
	}



	if (pGlobalDoc->m_bUseCombo)
	{
		if (m_strOriginData[1][9] != m_strFineNick[0])
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(1, 9),
				m_strOriginData[1][9],
				m_strFineNick[0]);
			SaveSpecLog(strLog);
		}

		if (m_strOriginData[1][10] != m_strFineProtrusion[0])
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(1, 10),
				m_strOriginData[1][10],
				m_strFineProtrusion[0]);
			SaveSpecLog(strLog);
		}
	}
	else
	{
		if (_ttoi(m_strOriginData[1][9]) != m_nFineNickPercent[0])
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(1, 9),
				m_strOriginData[1][9],
				m_nFineNickPercent[0]);
			SaveSpecLog(strLog);
		}

		if (_ttoi(m_strOriginData[1][10]) != m_nFineProtrusionPercent[0])
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(1, 10),
				m_strOriginData[1][10],
				m_nFineProtrusionPercent[0]);
			SaveSpecLog(strLog);
		}
	}


	if (_ttoi(m_strOriginData[1][11]) != m_nFineNickNGFilterPercent[0])
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(1, 11),
			m_strOriginData[1][11],
			m_nFineNickNGFilterPercent[0]);
		SaveSpecLog(strLog);
	}


	if (_ttoi(m_strOriginData[1][12]) != m_nFineExcsNGFilterPercent[0])
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(1, 12),
			m_strOriginData[1][12],
			m_nFineExcsNGFilterPercent[0]);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[1][13]) - m_fFineLineWdDeltaGradViolation[0]) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(1, 13),
			m_strOriginData[1][13],
			m_fFineLineWdDeltaGradViolation[0]);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[1][14]) - m_fFineExcsWdDeltaGradViolation[0]) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(1, 14),
			m_strOriginData[1][14],
			m_fFineExcsWdDeltaGradViolation[0]);
		SaveSpecLog(strLog);
	}

	CString strVal;
	int idx;
	if (SpecData.nLineWidthGroupNum == 0)
	{

		if (fabs(_ttof(m_strOriginData[1][15]) - m_fFineNarrowTraceViolation[0]) > 0.01)
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(1, 15),
				m_strOriginData[1][15],
				m_fFineNarrowTraceViolation[0]);
			SaveSpecLog(strLog);
		}
	}

	if (SpecData.nLineWidthGroupNum == 0)
	{

		if (fabs(_ttof(m_strOriginData[1][16]) - m_fFineWideTraceViolation[0]) > 0.01)
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(1, 16),
				m_strOriginData[1][16],
				m_fFineWideTraceViolation[0]);
			SaveSpecLog(strLog);
		}

	}
	*/
}

void CDlgSpec::CheckOriginDataTab2()
{
/*	CString strTemp;
	CString strLog;

	if (_ttoi(m_strOriginData[2][1]) != m_MinSpGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(2, 1),
			m_strOriginData[2][1],
			m_MinSpGray);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[2][2]) != m_nNeibSpGrayDiff)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(2, 2),
			m_strOriginData[2][2],
			m_nNeibSpGrayDiff);
		SaveSpecLog(strLog);
	}


	if (_ttoi(m_strOriginData[2][3]) != m_nUSDarkGrayMinus)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(2, 3),
			m_strOriginData[2][3],
			m_nUSDarkGrayMinus);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[2][4]) - m_fMinSpWidth) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(2, 4),
			m_strOriginData[2][4],
			m_fMinSpWidth);
		SaveSpecLog(strLog);
	}

	if (pGlobalDoc->m_bUseCombo)
	{
		if (m_strOriginData[2][5] != m_strMinSP)
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(2, 6),
				m_strOriginData[2][6],
				m_strMinSP);
			SaveSpecLog(strLog);
		}
	}
	else
	{
		if (_ttoi(m_strOriginData[2][5]) != m_nMinSPPercent)
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(2, 6),
				m_strOriginData[2][6],
				m_nMinSPPercent);
			SaveSpecLog(strLog);
		}
	}

	if (_ttoi(m_strOriginData[2][6]) != m_nSpaceNGFilterPercent)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(2, 6),
			m_strOriginData[2][6],
			m_nSpaceNGFilterPercent);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[2][7]) != m_fSpWdDeltaGradViolation)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(2, 7),
			m_strOriginData[2][7],
			m_fSpWdDeltaGradViolation);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[2][8]) - m_fSpWdDeltaOuterGradViolation) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(2, 8),
			m_strOriginData[2][8],
			m_fSpWdDeltaOuterGradViolation);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[2][9]) - m_fFineMinSpWidth) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(2, 9),
			m_strOriginData[2][9],
			m_fFineMinSpWidth);
		SaveSpecLog(strLog);
	}
	*/
}

void CDlgSpec::CheckOriginDataTab3()
{
/*	CString strTemp;
	CString strLog;

	if (_ttoi(m_strOriginData[3][1]) != m_nPinHoleGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(3, 1),
			m_strOriginData[3][1],
			m_nPinHoleGray);
		SaveSpecLog(strLog);
	}


	if (m_strOriginData[3][2] != m_strLP_Prec)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(3, 2),
			m_strOriginData[3][2],
			m_strLP_Prec);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[3][3]) - m_fPinHoleMin) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(3, 3),
			m_strOriginData[3][3],
			m_fPinHoleMin);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[3][4]) != m_nIsLandGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(3, 4),
			m_strOriginData[3][4],
			m_nIsLandGray);
		SaveSpecLog(strLog);
	}

	strTemp = m_strSP_Prec;

	if (m_strOriginData[3][5] != strTemp)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(3, 5),
			m_strOriginData[3][5],
			m_strSP_Prec);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[3][6]) - m_fIsLandMin) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(3, 6),
			m_strOriginData[3][6],
			m_fIsLandMin);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[3][7]) != m_nIsLandExtGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(3, 7),
			m_strOriginData[3][7],
			m_nIsLandExtGray);
		SaveSpecLog(strLog);
	}


	strTemp = m_strSPExt_Prec;

	if (m_strOriginData[3][8] != strTemp)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(3, 8),
			m_strOriginData[3][8],
			m_strSPExt_Prec);
		SaveSpecLog(strLog);
	}


	if (fabs(_ttof(m_strOriginData[3][9]) - m_fIsLandExtMin) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(3, 9),
			m_strOriginData[3][9],
			m_fIsLandExtMin);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[3][10]) != m_nCCLGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(3, 10),
			m_strOriginData[3][10],
			m_nCCLGray);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[3][11]) - m_fCCLCircularity) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(3, 11),
			m_strOriginData[3][11],
			m_fCCLCircularity);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[3][12]) - m_fCCLDefSize) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(3, 12),
			m_strOriginData[3][12],
			m_fCCLDefSize);
		SaveSpecLog(strLog);
	}

	//2022 01 10 lgh add
	if (SpecData.bEnableCharInspection)
	{

		if (fabs(_ttoi(m_strOriginData[3][13]) - m_nCharInspectionGray) > 0)
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(3, 13),
				m_strOriginData[3][13],
				m_nCharInspectionGray);
			SaveSpecLog(strLog);
		}

		if (fabs(_ttoi(m_strOriginData[3][14]) - m_dCharRegionUpperPercent) > 0.01)
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(3, 14),
				m_strOriginData[3][14],
				m_dCharRegionUpperPercent);
			SaveSpecLog(strLog);
		}

		if (fabs(_ttoi(m_strOriginData[3][15]) - m_dCharRegionLowerPercent) > 0.01)
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(3, 15),
				m_strOriginData[3][15],
				m_dCharRegionLowerPercent);
			SaveSpecLog(strLog);
		}
	}
	*/
}

void CDlgSpec::CheckOriginDataTab4()
{
/*	CString strTemp;
	CString strLog;

	if (_ttoi(m_strOriginData[4][1]) != SpecData.nVDrillDiffBrightGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 1),
			m_strOriginData[4][1],
			SpecData.nVDrillDiffBrightGray);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[4][2]) != SpecData.nVDrillDiffDarkGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 2),
			m_strOriginData[4][2],
			SpecData.nVDrillDiffDarkGray);
		SaveSpecLog(strLog);
	}


	if (fabs(_ttof(m_strOriginData[4][3]) - SpecData.fVDPadPrecName) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 3),
			m_strOriginData[4][3],
			SpecData.fVDPadPrecName);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[4][4]) - m_fVDLocationTolerance) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 4),
			m_strOriginData[4][4],
			m_fVDLocationTolerance);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[4][5]) - m_fVDPadMin) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 5),
			m_strOriginData[4][5],
			m_fVDPadMin);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[4][6]) != m_nPADVoidGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 6),
			m_strOriginData[4][6],
			m_nPADVoidGray);
		SaveSpecLog(strLog);
	}

	if (m_strOriginData[4][7] != m_strPadBallPrec)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 7),
			m_strOriginData[4][7],
			m_strPadBallPrec);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[4][8]) - m_fPADVoidMin) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 8),
			m_strOriginData[4][8],
			m_fPADVoidMin);
		SaveSpecLog(strLog);
	}

	strTemp = m_strPadTip_Prec;

	if (m_strOriginData[4][9] != strTemp)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 9),
			m_strOriginData[4][9],
			m_strPadTip_Prec);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[4][10]) - m_fPADTipMin) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 10),
			m_strOriginData[4][10],
			m_fPADTipMin);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[4][11]) != m_nHoleLandVoidGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 11),
			m_strOriginData[4][11],
			m_nHoleLandVoidGray);
		SaveSpecLog(strLog);
	}

	strTemp = m_strARLand_Prec;

	if (m_strOriginData[4][12] != strTemp)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 12),
			m_strOriginData[4][12],
			SpecData.szARLandPrecName);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[4][13]) - m_fARLandMin) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 13),
			m_strOriginData[4][13],
			m_fARLandMin);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[4][14]) - SpecData.fHoleFillExt) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 14),
			m_strOriginData[4][14],
			SpecData.fHoleFillExt);
		SaveSpecLog(strLog);
	}


	if (_ttoi(m_strOriginData[4][15]) != m_nCO2LandVoidGraySpec)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 15),
			m_strOriginData[4][15],
			m_nCO2LandVoidGraySpec);
		SaveSpecLog(strLog);
	}


	strTemp = m_strCO2Land_Prec;

	if (m_strOriginData[4][16] != strTemp)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 16),
			m_strOriginData[4][16],
			m_strCO2Land_Prec);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[4][17]) - m_fCO2LandMin) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 17),
			m_strOriginData[4][17],
			m_fCO2LandMin);
		SaveSpecLog(strLog);
	}


	strTemp = SpecData.szCO2LandAlignMode;

	if (m_strOriginData[4][18] != strTemp)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 18),
			m_strOriginData[4][18],
			SpecData.szCO2LandAlignMode);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[4][19]) - SpecData.fCO2HoleFillExt) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 19),
			m_strOriginData[4][19],
			SpecData.fCO2HoleFillExt);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[4][20]) != m_nFinePADVoidGraySpec)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 20),
			m_strOriginData[4][20],
			m_nFinePADVoidGraySpec);
		SaveSpecLog(strLog);
	}


	strTemp = m_strFPad_Prec;

	if (m_strOriginData[4][21] != strTemp)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 21),
			m_strOriginData[4][21],
			SpecData.szPADFine_PrecName);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[4][22]) - m_fFineVDPadMin) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(4, 22),
			m_strOriginData[4][22],
			m_fFineVDPadMin);
		SaveSpecLog(strLog);
	}
	*/
}

void CDlgSpec::CheckOriginDataTab5()
{
/*	CString strTemp;
	CString strLog;

	if (fabs(_ttof(m_strOriginData[5][1]) - m_fHoleTolerance) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 1),
			m_strOriginData[5][1],
			m_fHoleTolerance);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[5][2]) - m_fHoleDiaUpper) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 2),
			m_strOriginData[5][2],
			m_fHoleDiaUpper);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[5][3]) - m_fHoleDiaLower) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 3),
			m_strOriginData[5][3],
			m_fHoleDiaLower);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[5][4]) != m_nHoleOpenGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 4),
			m_strOriginData[5][4],
			m_nHoleOpenGray);
		SaveSpecLog(strLog);
	}


	if (_ttoi(m_strOriginData[5][5]) != m_nHoleMissingGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 5),
			m_strOriginData[5][5],
			m_nHoleMissingGray);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[5][6]) != m_nHoleInnerGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 6),
			m_strOriginData[5][6],
			m_nHoleInnerGray);
		SaveSpecLog(strLog);
	}



	if (m_strOriginData[5][7] != m_strHolePrec)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 7),
			m_strOriginData[5][7],
			m_strHolePrec);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[5][8]) != m_nHoleDefSize)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 8),
			m_strOriginData[5][8],
			m_nHoleDefSize);
		SaveSpecLog(strLog);
	}


	strTemp = CharToString(SpecData.szVHMode);

	if (m_strOriginData[5][9] != strTemp)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 9),
			m_strOriginData[5][9],
			CharToString(SpecData.szVHMode));
		SaveSpecLog(strLog);
	}


	if (_ttoi(m_strOriginData[5][10]) != m_nCO2MissingGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 10),
			m_strOriginData[5][10],
			m_nCO2MissingGray);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[5][11]) != m_nCO2HoleNum)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 11),
			m_strOriginData[5][11],
			m_nCO2HoleNum);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[5][12]) != m_nCO2OpenGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 12),
			m_strOriginData[5][12],
			m_nCO2OpenGray);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[5][13]) != m_nCO2MisAgnGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 13),
			m_strOriginData[5][13],
			m_nCO2MisAgnGray);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[5][14]) != m_nCO2MisAgnDefPercent)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 14),
			m_strOriginData[5][14],
			m_nCO2MisAgnDefPercent);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[5][15]) != SpecData.nVHEdgeThrDiffGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 15),
			m_strOriginData[5][15],
			SpecData.nVHEdgeThrDiffGray);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[5][16]) != SpecData.nVHBreakOutGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 16),
			m_strOriginData[5][16],
			SpecData.nVHBreakOutGray);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[5][17]) != SpecData.nVHDissmearGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 17),
			m_strOriginData[5][17],
			SpecData.nVHDissmearGray);
		SaveSpecLog(strLog);
	}


	if (_ttoi(m_strOriginData[5][18]) != SpecData.nVHContiBreakOutNum)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(5, 18),
			m_strOriginData[5][18],
			SpecData.nVHContiBreakOutNum);
		SaveSpecLog(strLog);
	}
	*/
}

void CDlgSpec::CheckOriginDataTab6()
{
/*	CString strTemp;
	CString strLog;

	if (_ttoi(m_strOriginData[6][1]) != m_nPadEdgeNickGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 1),
			m_strOriginData[6][1],
			m_nPadEdgeNickGray);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[6][2]) != m_nPadEdgeNeibGrayDiff)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 2),
			m_strOriginData[6][2],
			m_nPadEdgeNeibGrayDiff);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[6][3]) - m_nPadEdgeBADiffDarkGray) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 3),
			m_strOriginData[6][3],
			m_nPadEdgeBADiffDarkGray);
		SaveSpecLog(strLog);
	}


	if (fabs(_ttof(m_strOriginData[6][4]) - m_fPadEdgeNickWdDeltaGradViolation) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 4),
			m_strOriginData[6][4],
			m_fPadEdgeNickWdDeltaGradViolation);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[6][5]) - m_fPadEdgeExcsWdDeltaGradViolation) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 5),
			m_strOriginData[6][5],
			m_fPadEdgeExcsWdDeltaGradViolation);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[6][6]) != m_nPadVDEdgeGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 6),
			m_strOriginData[6][6],
			m_nPadVDEdgeGray);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[6][7]) - m_fPadVDEdgeWdDeltaGradViolation) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 7),
			m_strOriginData[6][7],
			m_fPadVDEdgeWdDeltaGradViolation);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[6][8]) != m_nHoleEdgeNickGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 8),
			m_strOriginData[6][8],
			m_nHoleEdgeNickGray);
		SaveSpecLog(strLog);
	}


	if (_ttoi(m_strOriginData[6][9]) != m_nHoleEdgeNeibGrayDiff)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 9),
			m_strOriginData[6][9],
			m_nHoleEdgeNeibGrayDiff);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[6][10]) - m_fHoleEdgeNickWdDeltaGradViolation) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 10),
			m_strOriginData[6][10],
			m_fHoleEdgeNickWdDeltaGradViolation);
		SaveSpecLog(strLog);
	}


	if (fabs(_ttof(m_strOriginData[6][11]) - m_fHoleEdgeExcsWdDeltaGradViolation) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 11),
			m_strOriginData[6][11],
			m_fHoleEdgeExcsWdDeltaGradViolation);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[6][12]) != m_nViaEdgeNickGray)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 12),
			m_strOriginData[6][12],
			m_nViaEdgeNickGray);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[6][13]) != m_nViaEdgeNeibGrayDiff)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 13),
			m_strOriginData[6][13],
			m_nViaEdgeNeibGrayDiff);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[6][14]) - m_fViaEdgeNickWdDeltaGradViolation) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 14),
			m_strOriginData[6][14],
			m_fViaEdgeNickWdDeltaGradViolation);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[6][15]) - m_fViaEdgeExcsWdDeltaGradViolation) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(6, 15),
			m_strOriginData[6][15],
			m_fViaEdgeExcsWdDeltaGradViolation);
		SaveSpecLog(strLog);
	}*/
}

void CDlgSpec::CheckOriginDataTab7()
{
/*	CString strTemp;
	CString strLog;

	if (_ttoi(m_strOriginData[7][1]) != pGlobalDoc->m_nPtSrchRngExt)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(7, 1),
			m_strOriginData[7][1],
			pGlobalDoc->m_nPtSrchRngExt);
		SaveSpecLog(strLog);
	}

	if (m_strOriginData[7][2] != m_cboPTMOD_SIZE)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(7, 2),
			m_strOriginData[7][2],
			m_cboPTMOD_SIZE);
		SaveSpecLog(strLog);
	}

	if (_ttoi(m_strOriginData[7][3]) != m_nAlignTolerance)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%d]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(7, 3),
			m_strOriginData[7][3],
			m_nAlignTolerance);
		SaveSpecLog(strLog);
	}

	if (m_strOriginData[7][4] != m_strThetaAlign)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(7, 4),
			m_strOriginData[7][4],
			m_strThetaAlign);
		SaveSpecLog(strLog);
	}

	if (fabs(_ttof(m_strOriginData[7][5]) - m_fDefMaskSize) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(7, 5),
			m_strOriginData[7][5],
			m_fDefMaskSize);
		SaveSpecLog(strLog);
	}


	if (fabs(_ttof(m_strOriginData[7][6]) - m_fNearDefLen) > 0.01)
	{
		strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%.1f]"),
			pGlobalDoc->m_strUserID,
			pGlobalDoc->m_strModel,
			pGlobalDoc->m_strLayer,
			pGlobalDoc->m_strLotNum,
			pGlobalDoc->m_nSerialNum,
			GetSpecName(7, 6),
			m_strOriginData[7][6],
			m_fNearDefLen);
		SaveSpecLog(strLog);
	}

	if (pGlobalDoc->m_bUseMultiVaccumControl)	//130311 hjc add
	{
		if (m_strOriginData[7][7] != m_strSelectVaccum)
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(7, 7),
				m_strOriginData[7][7],
				m_strSelectVaccum);
			SaveSpecLog(strLog);
		}
	}
	else
	{
		if (m_strOriginData[7][7] != "Both")
		{
			strLog.Format(_T("[Spec] [User:%s] Model:%s Layer:%s Lot:%s Sn:%d Change [%s] Spec [%s]->[%s]"),
				pGlobalDoc->m_strUserID,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer,
				pGlobalDoc->m_strLotNum,
				pGlobalDoc->m_nSerialNum,
				GetSpecName(7, 7),
				m_strOriginData[7][7],
				"Both");
			SaveSpecLog(strLog);
		}
	}
*/

}




void CDlgSpec::TabChange(int nTap)
{
/*	ULONGLONG nTick = GetTickCount64();

	if (g_bSRMode)
		m_tabDlgInspection.HighlightItem(8, 0);

	if (nTap >= 8)
	{
		m_tabDlgInspection.HighlightItem(m_nTabNum, 0);
		m_nTabNum = nTap;
		m_tabDlgInspection.SetCurSel(nTap);

		m_tabDlgInspection.HighlightItem(nTap, TRUE);


		m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));

		if (m_Spread.GetEditMode())
			m_Spread.SetEditMode(FALSE);

		GetDlgItem(IDC_FPSPREAD_SPEC1)->ShowWindow(SW_HIDE);
		if (g_bSRMode && nTap == 8)
		{

			if (m_DlgSroSpec.GetSafeHwnd())
			{
				m_DlgSroSpec.DestroyWindow();
			}

			CRect RT;
			GetDlgItem(IDC_TAB1)->GetWindowRect(RT);

			m_DlgSroSpec.m_nStartPosX = RT.left;
			m_DlgSroSpec.m_nStartPosY = RT.bottom;

			for (int i = 0; i < MAX_HOLE_TYPE; i++)
				memcpy(&m_DlgSroSpec.m_SRSpec[i], &SpecData.SRSpec[i], sizeof(SROSpec));

			CSROInspectionData* pSROData = CSROInspectionData::GetInstance(g_nCurrentLayerSide);
			if (!m_DlgSroSpec.GetSafeHwnd())
				m_DlgSroSpec.Create(IDD_DLG_SRSPEC, this);
			m_DlgSroSpec.ShowWindow(SW_SHOW);
			return;
		}
		else if (AoiParam()->m_bUseMultilineSpecEx)
		{
			m_tabDlgInspection.SetCurSel(nTap);
			m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
			GetDlgItem(IDC_FPSPREAD_SPEC1)->ShowWindow(SW_HIDE);

			CRect RT;

			GetDlgItem(IDC_TAB1)->GetWindowRect(RT);

			DlgMultiLineNew dlg;
			dlg.LoadFractionData(pGlobalDoc->m_strLocSpecDir, pGlobalDoc->m_strModel, pGlobalDoc->m_strLayer);
			dlg.m_nStartPosX = RT.left;
			dlg.m_nStartPosY = RT.bottom;

			dlg.SetTeachingDataPtr((CLineWidthFraction*)pGlobalDoc);

			if (m_nLineWidthGroupNum)
			{
				dlg.m_nNum = m_nLineWidthGroupNum;
				int i = 0;
				for (i = 0; i<dlg.m_nNum; i++)
				{

					if (i == 0)
					{
						dlg.m_SpecGroup[i].dGroupLowerWidthUm = 0;
						dlg.m_SpecGroup[i].dGroupUpperWidthUm = m_fLineWidthGroup[i];
						dlg.m_SpecGroup[i].dSpecLower = m_fNarrowTraceViolation[i];
						dlg.m_SpecGroup[i].dSpecUpper = m_fWideTraceViolation[i];
						dlg.m_SpecGroup[i].dAdjustWidthDiffPercent = SpecData.fLineWidthGroupAdjusted[i];
					}
					else
					{
						dlg.m_SpecGroup[i].dGroupLowerWidthUm = m_fLineWidthGroup[i - 1];
						dlg.m_SpecGroup[i].dGroupUpperWidthUm = m_fLineWidthGroup[i];
						dlg.m_SpecGroup[i].dSpecLower = m_fNarrowTraceViolation[i];
						dlg.m_SpecGroup[i].dSpecUpper = m_fWideTraceViolation[i];
						dlg.m_SpecGroup[i].dAdjustWidthDiffPercent = SpecData.fLineWidthGroupAdjusted[i];
					}

					dlg.m_SpecGroup[i].dSpecLowerFine = m_fFineNarrowTraceViolation[i];
					dlg.m_SpecGroup[i].dSpecUpperFine = m_fFineWideTraceViolation[i];
				}

				for (i = dlg.m_nNum; i < 15; i++)
				{
					dlg.m_SpecGroup[i].dGroupLowerWidthUm = m_fLineWidthGroup[i - 1];
					dlg.m_SpecGroup[i].dGroupUpperWidthUm = 999999;
					dlg.m_SpecGroup[i].dSpecLower = m_fNarrowTraceViolation[dlg.m_nNum - 1];
					dlg.m_SpecGroup[i].dSpecUpper = m_fWideTraceViolation[dlg.m_nNum - 1];
					dlg.m_SpecGroup[i].dAdjustWidthDiffPercent = SpecData.fLineWidthGroupAdjusted[dlg.m_nNum - 1];
					dlg.m_SpecGroup[i].dSpecLowerFine = m_fFineNarrowTraceViolation[dlg.m_nNum - 1];
					dlg.m_SpecGroup[i].dSpecUpperFine = m_fFineWideTraceViolation[dlg.m_nNum - 1];
				}



			}

			dlg.DoModal();

			//save part
			if (dlg.m_bSave)
			{
				m_bMultilineSaved = TRUE;
				m_bSpecDataChanged = TRUE;

				if (dlg.m_nNum > 0)
					SpecData.nLineWidthGroupNum = dlg.m_nNum;
				else
					SpecData.nLineWidthGroupNum = 0;

				m_nLineWidthGroupNum = SpecData.nLineWidthGroupNum;
				int i = 0;
				for (i = 0; i < dlg.m_nNum; i++)
				{
					if (i != 0)
					{
						SpecData.fLineWidthGroupLower[i] = dlg.m_SpecGroup[i].dGroupLowerWidthUm;
						SpecData.fLineWidthGroup[i] = dlg.m_SpecGroup[i].dGroupUpperWidthUm;
						SpecData.fNarrowTraceViolation[i] = dlg.m_SpecGroup[i].dSpecLower;
						SpecData.fWideTraceViolation[i] = dlg.m_SpecGroup[i].dSpecUpper;
						SpecData.fLineWidthGroupAdjusted[i] = dlg.m_SpecGroup[i].dAdjustWidthDiffPercent;
					}
					else
					{
						SpecData.fLineWidthGroupLower[i] = 0;
						SpecData.fLineWidthGroup[i] = dlg.m_SpecGroup[i].dGroupUpperWidthUm;
						SpecData.fNarrowTraceViolation[i] = dlg.m_SpecGroup[i].dSpecLower;
						SpecData.fWideTraceViolation[i] = dlg.m_SpecGroup[i].dSpecUpper;
						SpecData.fLineWidthGroupAdjusted[i] = dlg.m_SpecGroup[i].dAdjustWidthDiffPercent;
					}

					m_fNarrowTraceViolation[i] = SpecData.fNarrowTraceViolation[i];
					m_fWideTraceViolation[i] = SpecData.fWideTraceViolation[i];

					SpecData.fFineLineWidthGroup[i] = SpecData.fLineWidthGroup[i];
					m_fFineNarrowTraceViolation[i] = SpecData.fFineNarrowTraceViolation[i] = dlg.m_SpecGroup[i].dSpecLowerFine;
					m_fFineWideTraceViolation[i] = SpecData.fFineWideTraceViolation[i] = dlg.m_SpecGroup[i].dSpecUpperFine;
				}

				for (i = dlg.m_nNum; i < 15; i++)
				{
					SpecData.fLineWidthGroupLower[i] = SpecData.fLineWidthGroupLower[dlg.m_nNum - 1];
					m_fNarrowTraceViolation[i] = SpecData.fNarrowTraceViolation[i] = SpecData.fNarrowTraceViolation[dlg.m_nNum - 1];
					m_fWideTraceViolation[i] = SpecData.fWideTraceViolation[i] = SpecData.fWideTraceViolation[dlg.m_nNum - 1];

					m_fFineNarrowTraceViolation[i] = SpecData.fFineNarrowTraceViolation[i] = SpecData.fFineNarrowTraceViolation[dlg.m_nNum - 1];
					m_fFineWideTraceViolation[i] = SpecData.fFineWideTraceViolation[i] = SpecData.fFineWideTraceViolation[dlg.m_nNum - 1];

					//	SpecData.fLineWidthGroupAdjusted[i] = 0;
					SpecData.fLineWidthGroup[i] = 9999999;
				}

				for (i = 0; i < 15; i++)
				{
					m_fLineWidthGroupLower[i] = SpecData.fLineWidthGroupLower[i];
					m_fLineWidthGroup[i] = SpecData.fLineWidthGroup[i];
					m_fFineLineWidthGroup[i] = SpecData.fLineWidthGroup[i];
					m_fNarrowTraceViolation[i] = SpecData.fNarrowTraceViolation[i];
					m_fWideTraceViolation[i] = SpecData.fWideTraceViolation[i];
					m_fFineNarrowTraceViolation[i] = SpecData.fFineNarrowTraceViolation[i];
					m_fFineWideTraceViolation[i] = SpecData.fFineWideTraceViolation[i];

				}
			}

			TabChange(0);

			return;
		}

		return;
	}
	else
		GetDlgItem(IDC_FPSPREAD_SPEC1)->ShowWindow(SW_SHOW);

	if (m_DlgSroSpec.GetSafeHwnd())
	{
		m_DlgSroSpec.ShowWindow(SW_HIDE);
	}

	m_tabDlgInspection.SetCurSel(nTap);

	if (nTap >= 0 && nTap<8)
		m_nSpreadCellFocusPos[nTap] = 0;

	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	if (m_Spread.GetEditMode())
		m_Spread.SetEditMode(FALSE);
	m_Spread.SetFocus();
	LoadOriginDataTab(nTap);
	DisplaySpread(nTap);

	ULONGLONG nTick2 = GetTickCount64() - nTick;*/
}

void CDlgSpec::TabRestore()
{
	//int nTabNum = m_tabDlgInspection.GetCurSel();
	//TabChange(nTabNum);
}

CString CDlgSpec::CheckLock(int tab, int Row, CString strVal)
{
/*	CString strTemp;
	if (pGlobalDoc->m_LockTable.m_pLockTable[tab][Row].bUse)
	{
		if (pGlobalDoc->m_LockTable.m_pLockTable[tab][Row].type == LOCK_INT)
		{

			int nTemp;
			int nLow = _ttoi(pGlobalDoc->m_LockTable.m_pLockTable[tab][Row].szLSL);
			int nHigh = _ttoi(pGlobalDoc->m_LockTable.m_pLockTable[tab][Row].szUSL);

			if (nLow == 0 && nHigh == 0)
				return strVal;

			nTemp = _ttoi(strVal);
			nTemp = min(nHigh, max(nLow, nTemp));
			strTemp.Format(_T("%d"), nTemp);

			m_Spread.SetText(strTemp);
			return strTemp;
		}
		else if (pGlobalDoc->m_LockTable.m_pLockTable[tab][Row].type == LOCK_FLOAT)
		{
			float nTemp;
			float nLow = _ttof(pGlobalDoc->m_LockTable.m_pLockTable[tab][Row].szLSL);
			float nHigh = _ttof(pGlobalDoc->m_LockTable.m_pLockTable[tab][Row].szUSL);

			if (nLow == 0.0 && nHigh == 0.0)
				return strVal;

			int nLen = strVal.GetLength();
			int nPivot = strVal.ReverseFind('.');

			nTemp = _ttof(strVal);
			nTemp = min(nHigh, max(nLow, nTemp));
			if (nPivot != -1)
			{
				nPivot = nLen - nPivot - 1;
				if (nPivot == 1)
					strTemp.Format(_T("%.1f"), nTemp);
				else if (nPivot == 2)
					strTemp.Format(_T("%.2f"), nTemp);
				else if (nPivot == 3)
					strTemp.Format(_T("%.3f"), nTemp);
				else
					strTemp.Format(_T("%.1f"), nTemp);
			}
			else
				strTemp.Format(_T("%.1f"), nTemp);
			m_Spread.SetText(strTemp);
			return strTemp;
		}
		else if (pGlobalDoc->m_LockTable.m_pLockTable[tab][Row].type == LOCK_LEVEL)
		{
			int nHigh = abs(Level2NumberForLock(pGlobalDoc->m_LockTable.m_pLockTable[tab][Row].szUSL));
			int nLow = abs(Level2NumberForLock(pGlobalDoc->m_LockTable.m_pLockTable[tab][Row].szLSL));
			int nLevel = abs(Level2NumberForLock(strVal));



			nLevel = max(nLow, min(nHigh, nLevel));

			switch (nLevel)
			{
			case 7:
				return _T("Highest");

			case 6:
				return _T("VeryHigh");

			case 5:
				return _T("High");

			case 4:
				return _T("Normal");

			case 3:
				return _T("Low");

			case 2:
				return _T("VeryLow");

			case 1:
				return _T("Lowest");

			case 0:
				return _T("MaxLimit");
			}

			//	strTemp = number2

			return strVal;
		}
	}
	*/
	return strVal;
}

void CDlgSpec::ChangeSpecFromEasy(int Col, int Row)
{
	// Verify Normal Cell Value.

/*	CString strMsg, strTemp;
	int nPos;

	switch (m_nTabNum)
	{
	case 0:
		if (Col == 1 && Row == 1)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(1);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(0);
				return;
			}

			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[0][1] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (1 - 1)); // Bit Flag.
			}
			m_fNominalLine = (float)_ttof(strTemp);
		}
		if (Col == 1 && Row == 2)
		{
			if (!pGlobalDoc->m_bUseExternalRLWInputParam)	//20120416-ndy add
			{
				DisplaySpread(0);
				return;
			}

			m_Spread.SetCol(1);
			m_Spread.SetRow(2);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(0);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[0][2] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (Row - 1)); // Bit Flag.
			}
			m_fRealNormLine = (float)_ttof(strTemp);
		}
		if (Col == 1 && Row == 3)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(3);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(0);
				return;
			}

			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(0);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[0][3] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (3 - 1)); // Bit Flag.
			}
			//20090216 chg
			m_nNickGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 4)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(4);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(0);
				return;
			}

			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(0);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[0][4] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (4 - 1)); // Bit Flag.
			}
			m_nOpenGray = _ttoi(strTemp);
		}
		//150413 hjc add
		if (Col == 1 && Row == 5)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(5);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(0);
				return;
			}

			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(0);
				return;
			}

			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[0][5] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (5 - 1)); // Bit Flag.
			}
			m_nHalfSideNickDiffBrightGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 6)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(6);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(0);
				return;
			}
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(0);
				return;
			}

			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[0][6] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (6 - 1)); // Bit Flag.
			}
			m_nHalfSideNickDiffDarkGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 7)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(7);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(0);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(0);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[0][7] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (7 - 1)); // Bit Flag.
			}
			m_nLeadOpenGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 8)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(8);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(0);
				return;
			}

			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[0][8] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (8 - 1)); // Bit Flag.
			}
			m_fMinCheckWidth = _ttof(strTemp);

		}


		if (SpecData.nLineWidthGroupNum == 0 || AoiParam()->m_bUseMultilineSpecEx)
		{
			if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
			{
				if (Col == 1 && Row == 9)
				{
					m_Spread.SetCol(Col);
					m_Spread.SetRow(Row);
					strTemp = m_Spread.GetText();
					nPos = strTemp.Find(_T(" "), 0);
					strTemp = strTemp.Left(nPos);
					if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
						|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
						|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
					{
						DisplaySpread(0);
						return;
					}

					if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
					{
						strTemp = CheckLock(m_nTabNum, Row, strTemp);
					}

					if (m_strOriginData[0][9] != strTemp)
					{
						m_bSpecDataChanged = TRUE;
						m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

						m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (9 - 1)); // Bit Flag.
					}
					m_strNick[0] = strTemp;
				}

				if (Col == 1 && Row == 10)
				{
					m_Spread.SetCol(Col);
					m_Spread.SetRow(Row);
					strTemp = m_Spread.GetText();
					nPos = strTemp.Find(_T(" "), 0);
					strTemp = strTemp.Left(nPos);
					if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
						|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
						|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
					{
						DisplaySpread(0);
						return;
					}

					if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
					{
						strTemp = CheckLock(m_nTabNum, Row, strTemp);
					}

					if (m_strOriginData[0][10] != strTemp)
					{
						m_bSpecDataChanged = TRUE;
						m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

						m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (10 - 1)); // Bit Flag.
					}
					m_strProtrusion[0] = strTemp;
				}
			}
			else
			{
				if (Col == 1 && Row == 9)	//150413 hjc add
				{
					m_Spread.SetCol(1);
					m_Spread.SetRow(9);
					strTemp = m_Spread.GetText();

					if (IsCharInString(strTemp))
					{
						strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
						MessageBox(strMsg);
						DisplaySpread(0);
						return;
					}

					if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
					{
						strTemp = CheckLock(m_nTabNum, Row, strTemp);
					}

					if (m_strOriginData[0][9] != strTemp)
					{
						m_bSpecDataChanged = TRUE;
						m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

						m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (9 - 1)); // Bit Flag.
					}
					m_nNickPercent[0] = _ttoi(strTemp);

				}
				if (Col == 1 && Row == 10)
				{
					m_Spread.SetCol(1);
					m_Spread.SetRow(10);
					strTemp = m_Spread.GetText();

					if (IsCharInString(strTemp))
					{
						strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
						MessageBox(strMsg);
						DisplaySpread(0);
						return;
					}

					if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
					{
						strTemp = CheckLock(m_nTabNum, Row, strTemp);
					}

					if (m_strOriginData[0][10] != strTemp)
					{
						m_bSpecDataChanged = TRUE;
						m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

						m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (10 - 1)); // Bit Flag.
					}
					m_nProtrusionPercent[0] = _ttoi(strTemp);
				}

			}

			if (Col == 1 && Row == 11)
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(11);
				strTemp = m_Spread.GetText();

				if (IsCharInString(strTemp))
				{
					strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
					MessageBox(strMsg);
					DisplaySpread(0);
					return;
				}
				if (_ttoi(strTemp) < 30 || _ttoi(strTemp) > 90)
				{
					strMsg.Format(_T("%s (30~90)%%%s"),
						pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
						pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
					MessageBox(strMsg);
					DisplaySpread(0);
					return;
				}
				else
				{

					if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
					{
						strTemp = CheckLock(m_nTabNum, Row, strTemp);
					}

					if (m_strOriginData[0][11] != strTemp)
					{
						m_bSpecDataChanged = TRUE;
						m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

						m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (11 - 1)); // Bit Flag.
					}
				}
				m_nNickNGFilterPercent[0] = _ttoi(strTemp);
			}
			if (Col == 1 && Row == 12)
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(12);
				strTemp = m_Spread.GetText();

				if (IsCharInString(strTemp))
				{
					strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
					MessageBox(strMsg);
					DisplaySpread(0);
					return;
				}

				if (_ttoi(strTemp) < 110 || _ttoi(strTemp) > 200)
				{
					strMsg.Format(_T("%s (110~200)%%%s"),
						pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
						pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
					MessageBox(strMsg);
					DisplaySpread(0);
					return;
				}
				else
				{

					if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
					{
						strTemp = CheckLock(m_nTabNum, Row, strTemp);
					}



					if (m_strOriginData[0][12] != strTemp)
					{
						m_bSpecDataChanged = TRUE;
						m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

						m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (12 - 1)); // Bit Flag.
					}
				}
				m_nExcsNGFilterPercent[0] = _ttoi(strTemp);
			}
			if (Col == 1 && Row == 13)
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(13);
				strTemp = m_Spread.GetText();

				if (IsCharInString(strTemp))
				{
					strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
					MessageBox(strMsg);
					DisplaySpread(0);
					return;
				}

				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}

				if (m_strOriginData[0][13] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (13 - 1)); // Bit Flag.
				}
				m_fLineWdDeltaGradViolation[0] = _ttof(strTemp);
			}
			if (Col == 1 && Row == 14)
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(14);
				strTemp = m_Spread.GetText();

				if (IsCharInString(strTemp))
				{
					strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
					MessageBox(strMsg);
					DisplaySpread(0);
					return;
				}

				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}

				if (m_strOriginData[0][14] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (14 - 1)); // Bit Flag.
				}
				m_fExcsWdDeltaGradViolation[0] = _ttof(strTemp);
			}

			if (Col == 1 && Row == 15)
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(15);
				strTemp = m_Spread.GetText();

				if (IsCharInString(strTemp))
				{
					strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
					MessageBox(strMsg);
					DisplaySpread(0);
					return;
				}

				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}

				if (m_strOriginData[0][15] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (15 - 1)); // Bit Flag.
				}
				m_fNarrowTraceViolation[0] = (float)_ttof(strTemp);
			}
			if (Col == 1 && Row == 16)
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(16);
				strTemp = m_Spread.GetText();

				if (IsCharInString(strTemp))
				{
					strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
					MessageBox(strMsg);
					DisplaySpread(0);
					return;
				}

				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}

				if (m_strOriginData[0][16] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[0] |= (0x00000001 << (16 - 1)); // Bit Flag.
				}
				m_fWideTraceViolation[0] = (float)_ttof(strTemp);
			}
		}


		if (m_bKeyDown)
		{
			m_bKeyDown = FALSE;
			RefreshSheetOnChanging();
		}

		break;

	case 1:
		if (Col == 1 && Row == 1)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(1);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(1);
				return;
			}

			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[1][1] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (1 - 1)); // Bit Flag.
			}
			m_fNominalLine = (float)_ttof(strTemp);
		}
		if (Col == 1 && Row == 2)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(2);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(1);
				return;
			}

			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[1][2] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (2 - 1)); // Bit Flag.
			}
			m_fRealNormLine = (float)_ttof(strTemp);
		}
		if (Col == 1 && Row == 3)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(3);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(1);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[1][3] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (3 - 1)); // Bit Flag.
			}
			m_nFineNickGray = _ttoi(strTemp);	//170403 hjc mod
		}
		if (Col == 1 && Row == 4)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(4);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(1);
				return;
			}

			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(1);
				return;
			}

			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[1][4] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (4 - 1)); // Bit Flag.
			}
			m_nFineOpenGray = _ttoi(strTemp);
		}
		//150413 hjc add
		if (Col == 1 && Row == 5)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(5);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(1);
				return;
			}

			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(1);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[1][5] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (5 - 1)); // Bit Flag.
			}
			m_nFineHalfSideNickDiffBrightGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 6)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(6);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(1);
				return;
			}
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(1);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[1][6] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (6 - 1)); // Bit Flag.
			}
			m_nFineHalfSideNickDiffDarkGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 7)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(7);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(1);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[1][7] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (7 - 1)); // Bit Flag.
			}
			m_nLeadOpenGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 8)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(8);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(1);
				return;
			}

			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[1][8] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (8 - 1)); // Bit Flag.
			}
			m_fFineMinCheckWidth = _ttoi(strTemp);

		}

		if (SpecData.nLineWidthGroupNum == 0 || AoiParam()->m_bUseMultilineSpecEx)
		{
			if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
			{
				if (Col == 1 && Row == 9)
				{
					m_Spread.SetCol(Col);
					m_Spread.SetRow(Row);
					strTemp = m_Spread.GetText();
					nPos = strTemp.Find(_T(" "), 0);
					strTemp = strTemp.Left(nPos);
					if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
						|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
						|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
					{
						DisplaySpread(1);
						return;
					}

					if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
					{
						strTemp = CheckLock(m_nTabNum, Row, strTemp);
					}

					if (m_strOriginData[1][9] != strTemp)
					{
						m_bSpecDataChanged = TRUE;
						m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

						m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (9 - 1)); // Bit Flag.
					}
					m_strFineNick[0] = strTemp;
				}

				if (Col == 1 && Row == 10)	//140625 lsg add
				{
					m_Spread.SetCol(Col);
					m_Spread.SetRow(Row);
					strTemp = m_Spread.GetText();
					nPos = strTemp.Find(_T(" "), 0);
					strTemp = strTemp.Left(nPos);
					if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
						|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
						|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
					{
						DisplaySpread(1);
						return;
					}

					if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
					{
						strTemp = CheckLock(m_nTabNum, Row, strTemp);
					}

					if (m_strOriginData[1][10] != strTemp)
					{
						m_bSpecDataChanged = TRUE;
						m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

						m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (10 - 1)); // Bit Flag.
					}
					m_strFineProtrusion[0] = strTemp;
				}
			}
			else
			{
				if (Col == 1 && Row == 9)	//150413 hjc add
				{
					m_Spread.SetCol(1);
					m_Spread.SetRow(9);
					strTemp = m_Spread.GetText();

					if (IsCharInString(strTemp))
					{
						strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
						MessageBox(strMsg);
						DisplaySpread(1);
						return;
					}

					if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
					{
						strTemp = CheckLock(m_nTabNum, Row, strTemp);
					}

					if (m_strOriginData[1][9] != strTemp)
					{
						m_bSpecDataChanged = TRUE;
						m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

						m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (9 - 1)); // Bit Flag.
					}
					m_nFineNickPercent[0] = _ttoi(strTemp);

				}
				if (Col == 1 && Row == 10)
				{
					m_Spread.SetCol(1);
					m_Spread.SetRow(10);
					strTemp = m_Spread.GetText();

					if (IsCharInString(strTemp))
					{
						strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
						MessageBox(strMsg);
						DisplaySpread(1);
						return;
					}

					if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
					{
						strTemp = CheckLock(m_nTabNum, Row, strTemp);
					}

					if (m_strOriginData[1][10] != strTemp)
					{
						m_bSpecDataChanged = TRUE;
						m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

						m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (10 - 1)); // Bit Flag.
					}
					m_nFineProtrusionPercent[0] = _ttoi(strTemp);
				}
			}

			if (Col == 1 && Row == 11)
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(11);
				strTemp = m_Spread.GetText();

				if (IsCharInString(strTemp))
				{
					strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
					MessageBox(strMsg);
					DisplaySpread(1);
					return;
				}
				if (_ttoi(strTemp) < 30 || _ttoi(strTemp) > 90)
				{
					strMsg.Format(_T("%s (30~90)%%%s"),
						pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
						pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
					MessageBox(strMsg);
					DisplaySpread(1);
					return;
				}
				else
				{

					if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
					{
						strTemp = CheckLock(m_nTabNum, Row, strTemp);
					}

					if (m_strOriginData[1][11] != strTemp)
					{
						m_bSpecDataChanged = TRUE;
						m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

						m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (11 - 1)); // Bit Flag.
					}
				}
				m_nFineNickNGFilterPercent[0] = _ttoi(strTemp);
			}

			if (Col == 1 && Row == 12)
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(12);
				strTemp = m_Spread.GetText();

				if (IsCharInString(strTemp))
				{
					strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
					MessageBox(strMsg);
					DisplaySpread(1);
					return;
				}

				if (_ttoi(strTemp) < 110 || _ttoi(strTemp) > 200)
				{
					strMsg.Format(_T("%s (110~200)%%%s"),
						pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
						pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
					MessageBox(strMsg);
					DisplaySpread(1);
					return;
				}
				else
				{

					if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
					{
						strTemp = CheckLock(m_nTabNum, Row, strTemp);
					}

					if (m_strOriginData[1][12] != strTemp)
					{
						m_bSpecDataChanged = TRUE;
						m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

						m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (12 - 1)); // Bit Flag.
					}
				}
				m_nFineExcsNGFilterPercent[0] = _ttoi(strTemp);
			}
			if (Col == 1 && Row == 13)
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(13);
				strTemp = m_Spread.GetText();

				if (IsCharInString(strTemp))
				{
					strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
					MessageBox(strMsg);
					DisplaySpread(1);
					return;
				}

				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}

				if (m_strOriginData[1][13] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (13 - 1)); // Bit Flag.
				}
				m_fFineLineWdDeltaGradViolation[0] = _ttof(strTemp);
			}

			if (Col == 1 && Row == 14)
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(14);
				strTemp = m_Spread.GetText();

				if (IsCharInString(strTemp))
				{
					strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
					MessageBox(strMsg);
					DisplaySpread(1);
					return;
				}

				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}

				if (m_strOriginData[1][14] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (14 - 1)); // Bit Flag.
				}
				m_fFineExcsWdDeltaGradViolation[0] = _ttof(strTemp);
			}

			if (Col == 1 && Row == 15)
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(15);
				strTemp = m_Spread.GetText();

				if (IsCharInString(strTemp))
				{
					strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
					MessageBox(strMsg);
					DisplaySpread(1);
					return;
				}
				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}
				if (m_strOriginData[1][15] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (15 - 1)); // Bit Flag.
				}
				m_fFineNarrowTraceViolation[0] = (float)_ttof(strTemp);
			}
			if (Col == 1 && Row == 16)
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(16);
				strTemp = m_Spread.GetText();

				if (IsCharInString(strTemp))
				{
					strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
					MessageBox(strMsg);
					DisplaySpread(1);
					return;
				}
				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}
				if (m_strOriginData[1][16] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[1] |= (0x00000001 << (16 - 1)); // Bit Flag.
				}
				m_fFineWideTraceViolation[0] = (float)_ttof(strTemp);
			}

		}

		if (m_bKeyDown)
		{
			m_bKeyDown = FALSE;
			RefreshSheetOnChanging();
		}

		break;
	case 2:
		if (Col == 1 && Row == 1)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(1);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}

			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[2][1] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (1 - 1)); // Bit Flag.
			}
			m_MinSpGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 2)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(2);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}

			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[2][2] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (2 - 1)); // Bit Flag.
			}
			m_nNeibSpGrayDiff = _ttoi(strTemp);
		}

		//150413 hjc add		
		if (Col == 1 && Row == 3)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(3);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[2][3] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (3 - 1)); // Bit Flag.
			}
			m_nUSDarkGrayMinus = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 4)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(4);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}

			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (m_strOriginData[2][4] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (4 - 1)); // Bit Flag.
			}
			m_fMinSpWidth = _ttof(strTemp);
		}

		//150413 hjc add		
		if (Col == 1 && Row == 5)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(5);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[2][5] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (5 - 1)); // Bit Flag.
			}
			m_nMinSPPercent = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 6)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(6);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}
			//if(_ttof(strTemp) < 1 || _ttof(strTemp) > 1.5)
			if (_ttof(strTemp) < 30 || _ttof(strTemp) > 90)
			{
				strMsg.Format(_T("%s (30~90)%%%s"),
					pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
					pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}
			else
			{
				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}

				if (m_strOriginData[2][6] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (6 - 1)); // Bit Flag.
				}
			}
			m_nSpaceNGFilterPercent = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 7)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(7);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[2][7] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (7 - 1)); // Bit Flag.
			}
			//20090228 hjc
			m_fSpWdDeltaGradViolation = _ttof(strTemp);
		}
		//20090405 hjc
		if (Col == 1 && Row == 8)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(8);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[2][8] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (8 - 1)); // Bit Flag.
			}
			//20090228 hjc
			m_fSpWdDeltaOuterGradViolation = _ttof(strTemp);
		}

		//141021 hjc add
		if (Col == 1 && Row == 9)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(9);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(2);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[2][9] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[2] |= (0x00000001 << (9 - 1)); // Bit Flag.
			}
			m_fFineMinSpWidth = _ttof(strTemp);
		}

		if (m_bKeyDown)
		{
			m_bKeyDown = FALSE;
			RefreshSheetOnChanging();
		}
		break;

		//20100322 hjc add
	case 3:
		if (Col == 1 && Row == 1)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(1);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(3);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[3][1] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (1 - 1)); // Bit Flag.
			}
			m_nPinHoleGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 2)	//140625 lsg add
		{
			m_Spread.SetCol(Col);
			m_Spread.SetRow(Row);
			strTemp = m_Spread.GetText();
			nPos = strTemp.Find(_T(" "), 0);
			strTemp = strTemp.Left(nPos);
			if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
				|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
				|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
			{
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[3][2] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (2 - 1)); // Bit Flag.
			}
			m_strLP_Prec = strTemp;
		}

		if (Col == 1 && Row == 3)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(3);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[3][3] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (3 - 1)); // Bit Flag.
			}

			if (pGlobalDoc->m_bInspCCL[AoiParam()->m_nCurrentInspectionMode])
			{
				m_fPinHoleMin = _ttof(strTemp);

				int nTempSize, nCellSize = 100000;
				for (int nBlockID = 0; nBlockID < RgnBlock.nBlockNum; nBlockID++)
				{
					nTempSize = min(SizeData[nBlockID].ProcSizeX, SizeData[nBlockID].ProcSizeY);
					nCellSize = (nCellSize > nTempSize) ? nTempSize : nCellSize;
				}
				nCellSize /= 10;

				if (m_fPinHoleMin > nCellSize)
				{
					m_fPinHoleMin = nCellSize;
					strTemp.Format(_T("%.1f"), m_fPinHoleMin);
					m_Spread.SetText(strTemp);
				}
			}
			else
				m_fPinHoleMin = _ttof(strTemp);
		}

		if (Col == 1 && Row == 4)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(4);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(3);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[3][4] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (4 - 1)); // Bit Flag.
			}
			m_nIsLandGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 5)	//140625 lsg add
		{
			m_Spread.SetCol(Col);
			m_Spread.SetRow(Row);
			strTemp = m_Spread.GetText();
			nPos = strTemp.Find(_T(" "), 0);
			strTemp = strTemp.Left(nPos);
			if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
				|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
				|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
			{
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[3][5] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (5 - 1)); // Bit Flag.
			}
			m_strLP_Prec = strTemp;	//170112 hjc mod
									//	StringToChar(strTemp,SpecData.szSPRLName);
		}
		if (Col == 1 && Row == 6)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(6);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[3][6] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (6 - 1)); // Bit Flag.
			}
			m_fIsLandMin = _ttof(strTemp);
		}
		//20090412 hjc
		if (Col == 1 && Row == 7)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(7);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[3][7] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (7 - 1)); // Bit Flag.
			}
			m_nIsLandExtGray = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 8)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(8);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[3][8] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[3] |= (0x00000001 << (8 - 1)); // Bit Flag.
			}
			m_fIsLandExtMin = _ttof(strTemp);
		}
		//---------------

		if (m_bKeyDown)
		{
			m_bKeyDown = FALSE;
			RefreshSheetOnChanging();
		}

		break;
	case 4:
		//150823 hjc add
		if (Col == 1 && Row == 1)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(1);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][1] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (1 - 1)); // Bit Flag.
			}
			SpecData.nVDrillDiffBrightGray = _ttoi(strTemp);		//150606 hjc mod
		}


		if (Col == 1 && Row == 2)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(2);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][2] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (2 - 1)); // Bit Flag.
			}
			SpecData.nVDrillDiffDarkGray = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 3)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(3);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][3] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (3 - 1)); // Bit Flag.
			}
			SpecData.fVDPadPrecName = _ttof(strTemp);
		}
		//20090419 hjc
		if (Col == 1 && Row == 4)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(4);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][4] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (4 - 1)); // Bit Flag.
			}
			m_fVDLocationTolerance = _ttof(strTemp);
		}
		//-----------
		if (Col == 1 && Row == 5)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(5);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][5] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (5 - 1)); // Bit Flag.
			}
			m_fVDPadMin = _ttof(strTemp);
		}

		if (Col == 1 && Row == 6)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(6);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][6] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (6 - 1)); // Bit Flag.
			}
			m_nPADVoidGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 7)	//140625 lsg add
		{
			m_Spread.SetCol(Col);
			m_Spread.SetRow(Row);
			strTemp = m_Spread.GetText();
			nPos = strTemp.Find(_T(" "), 0);
			strTemp = strTemp.Left(nPos);
			if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
				|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
				|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
			{
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][7] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (7 - 1)); // Bit Flag.
			}
			m_strPadBallPrec = strTemp;
		}
		if (Col == 1 && Row == 8)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(8);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			//111214 hjc add
			if (m_strOriginData[4][8] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (8 - 1)); // Bit Flag.
			}
			m_fPADVoidMin = _ttof(strTemp);
		}
		if (Col == 1 && Row == 9)	//140625 lsg add
		{
			m_Spread.SetCol(Col);
			m_Spread.SetRow(Row);
			strTemp = m_Spread.GetText();
			nPos = strTemp.Find(_T(" "), 0);
			strTemp = strTemp.Left(nPos);
			if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
				|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
				|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
			{
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][9] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (9 - 1)); // Bit Flag.
			}
			m_strPadTip_Prec = strTemp;	//170112 hjc mod
										//	StringToChar(strTemp,SpecData.szPADTipPrecName);
		}
		if (Col == 1 && Row == 10)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(10);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][10] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (10 - 1)); // Bit Flag.
			}
			m_fPADTipMin = _ttof(strTemp);
		}

		if (Col == 1 && Row == 11)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(11);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][11] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (11 - 1)); // Bit Flag.
			}
			m_nHoleLandVoidGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 12)	//140625 lsg add
		{
			m_Spread.SetCol(Col);
			m_Spread.SetRow(Row);
			strTemp = m_Spread.GetText();
			nPos = strTemp.Find(_T(" "), 0);
			strTemp = strTemp.Left(nPos);
			if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
				|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
				|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
			{
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][12] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (12 - 1)); // Bit Flag.
			}
			m_strARLand_Prec = strTemp;	//170112 hjc mod
										//	StringToChar(strTemp,SpecData.szARLandPrecName);
		}
		if (Col == 1 && Row == 13)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(13);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][13] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (13 - 1)); // Bit Flag.
			}
			m_fARLandMin = _ttof(strTemp);
		}

		if (Col == 1 && Row == 14)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(14);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][14] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (14 - 1)); // Bit Flag.
			}
			SpecData.fHoleFillExt = _ttof(strTemp);
		}

		if (Col == 1 && Row == 15)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(15);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][15] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (15 - 1)); // Bit Flag.
			}
			m_nCO2LandVoidGraySpec = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 16)	//140625 lsg add
		{
			m_Spread.SetCol(Col);
			m_Spread.SetRow(Row);
			strTemp = m_Spread.GetText();
			nPos = strTemp.Find(_T(" "), 0);
			strTemp = strTemp.Left(nPos);
			if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
				|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
				|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
			{
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][16] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (16 - 1)); // Bit Flag.
			}
			m_strCO2Land_Prec = strTemp;	//170112 hjc mod
											//	StringToChar(strTemp,SpecData.szCO2LandPrecName);

		}
		if (Col == 1 && Row == 17)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(17);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][17] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (17 - 1)); // Bit Flag.
			}
			m_fCO2LandMin = _ttof(strTemp);
		}
		//20100323 hjc add
		if (Col == 1 && Row == 19)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(19);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][19] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (19 - 1)); // Bit Flag.
			}
			SpecData.fCO2HoleFillExt = _ttof(strTemp);
		}

		if (Col == 1 && Row == 20)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(20);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][20] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (20 - 1)); // Bit Flag.
			}
			m_nFinePADVoidGraySpec = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 21)	//140625 lsg add
		{
			m_Spread.SetCol(Col);
			m_Spread.SetRow(Row);
			strTemp = m_Spread.GetText();
			nPos = strTemp.Find(_T(" "), 0);
			strTemp = strTemp.Left(nPos);
			if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
				|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
				|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
			{
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][21] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (21 - 1)); // Bit Flag.
			}
			m_strFPad_Prec = strTemp;	//170112 hjc mod
										//	StringToChar(strTemp,SpecData.szPADFine_PrecName);
		}
		if (Col == 1 && Row == 22)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(22);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(4);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[4][22] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[4] |= (0x00000001 << (22 - 1)); // Bit Flag.
			}
			m_fFineVDPadMin = _ttof(strTemp);	//090324-ndy
		}

		//---------------

		//----------------------------------------------------------------------------------

		if (m_bKeyDown)
		{
			m_bKeyDown = FALSE;
			RefreshSheetOnChanging();
		}

		break;
	case 5:
		if (Col == 1 && Row == 1)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(1);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[5][1] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (1 - 1)); // Bit Flag.
			}
			m_fHoleTolerance = (float)_ttof(strTemp);
		}

		//20090311 hjc modify
		if (Col == 1 && Row == 2)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(2);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}

			if (_ttof(strTemp) < 1.05 || _ttof(strTemp) > 3.0)
			{
				strMsg.Format(_T("%s (1.05~3.0)%s"),
					pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
					pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[5][2] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (2 - 1)); // Bit Flag.
			}
			m_fHoleDiaUpper = _ttof(strTemp);
		}

		if (Col == 1 && Row == 3)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(3);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (_ttof(strTemp) < 0.2 || _ttof(strTemp) > 0.95)
			{
				strMsg.Format(_T("%s (0.2~0.95)%s"),
					pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
					pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[5][3] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (3 - 1)); // Bit Flag.
			}
			m_fHoleDiaLower = _ttof(strTemp);
		}

		if (Col == 1 && Row == 4)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(4);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[5][4] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (4 - 1)); // Bit Flag.
			}
			m_nHoleOpenGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 5)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(5);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[5][5] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (5 - 1)); // Bit Flag.
			}
			m_nHoleMissingGray = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 6)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(6);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}

			if (_ttof(strTemp) < 35 || _ttof(strTemp) > 220)
			{
				strMsg.Format(_T("%s (35~220)%s"),
					pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
					pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[5][6] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (6 - 1)); // Bit Flag.
			}
			m_nHoleInnerGray = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 7)	//140625 lsg add
		{
			m_Spread.SetCol(Col);
			m_Spread.SetRow(Row);
			strTemp = m_Spread.GetText();
			nPos = strTemp.Find(_T(" "), 0);
			strTemp = strTemp.Left(nPos);
			if (!(strTemp == "Highest" || strTemp == "VeryHigh" || strTemp == "High"
				|| strTemp == "Normal" || strTemp == "Low" || strTemp == "VeryLow"
				|| strTemp == "Lowest" || strTemp == "MaxLimit"))	//140126 hjc add || strTemp == "MaxLimit"
			{
				DisplaySpread(3);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[5][7] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (7 - 1)); // Bit Flag.
			}
			m_strHolePrec = strTemp;
		}

		if (Col == 1 && Row == 8)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(8);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[5][8] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (8 - 1)); // Bit Flag.
			}
			m_nHoleDefSize = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 10)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(10);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[5][10] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (10 - 1)); // Bit Flag.
			}
			m_nCO2MissingGray = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 11)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(11);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[5][11] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (11 - 1)); // Bit Flag.
			}
			m_nCO2HoleNum = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 12)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(12);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[5][12] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (12 - 1)); // Bit Flag.
			}
			m_nCO2OpenGray = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 13)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(13);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[5][13] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (13 - 1)); // Bit Flag.
			}
			m_nCO2MisAgnGray = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 14)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(14);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[5][14] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (14 - 1)); // Bit Flag.
			}
			m_nCO2MisAgnDefPercent = _ttoi(strTemp);
		}


		if (Col == 1 && Row == 15)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(15);
			strTemp = m_Spread.GetText();
			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (_ttof(strTemp) < 20 || _ttof(strTemp) > 80)
			{
				strMsg.Format(_T("%s (20~80)%s"),
					pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
					pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			else
			{
				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}
				if (m_strOriginData[5][15] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (15 - 1)); // Bit Flag.
				}
			}

			SpecData.nVHEdgeThrDiffGray = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 16)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(16);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (_ttof(strTemp) < 80 || _ttof(strTemp) > 170)
			{
				strMsg.Format(_T("%s (80~170)%s"),
					pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
					pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			else
			{
				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}
				if (m_strOriginData[5][16] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (16 - 1)); // Bit Flag.
				}
			}

			SpecData.nVHBreakOutGray = _ttoi(strTemp);

		}

		if (Col == 1 && Row == 17)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(17);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (_ttof(strTemp) < 20 || _ttof(strTemp) > 80)
			{
				strMsg.Format(_T("%s (20~80)%s"),
					pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
					pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			else
			{
				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}
				if (m_strOriginData[5][17] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (17 - 1)); // Bit Flag.
				}
			}

			SpecData.nVHDissmearGray = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 18)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(18);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			if (_ttof(strTemp) < 1 || _ttof(strTemp) > 15)
			{
				strMsg.Format(_T("%s (1~15)%s"),
					pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
					pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
				MessageBox(strMsg);
				DisplaySpread(5);
				return;
			}
			else
			{
				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}
				if (m_strOriginData[5][18] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[5] |= (0x00000001 << (18 - 1)); // Bit Flag.
				}
			}

			SpecData.nVHContiBreakOutNum = _ttoi(strTemp);
		}

		if (m_bKeyDown)
		{
			m_bKeyDown = FALSE;
			RefreshSheetOnChanging();
		}

		break;
	case 6:
		//20090228 modify hjc 1~6
		if (Col == 1 && Row == 1)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(1);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][1] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (1 - 1)); // Bit Flag.
			}
			m_nPadEdgeNickGray = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 2)	//120105 hjc add
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(2);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][2] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (2 - 1)); // Bit Flag.
			}
			m_nPadEdgeNeibGrayDiff = _ttoi(strTemp);
		}
		if (Col == 1 && Row == 3)	//120105 hjc add
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(3);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			//20090326 hjc
			if (_ttoi(strTemp) < 0 || _ttoi(strTemp) > 255)
			{
				strMsg.Format(_T("Input Range : 0 ~ 255"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][3] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (3 - 1)); // Bit Flag.
			}
			m_nPadEdgeBADiffDarkGray = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 4)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(4);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][4] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (4 - 1)); // Bit Flag.
			}
			m_fPadEdgeNickWdDeltaGradViolation = _ttof(strTemp);
		}

		if (Col == 1 && Row == 5)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(5);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][5] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (5 - 1)); // Bit Flag.
			}
			m_fPadEdgeExcsWdDeltaGradViolation = _ttof(strTemp);
		}

		//------------------------
		//20090412 hjc
		if (Col == 1 && Row == 6)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(6);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][6] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (6 - 1)); // Bit Flag.
			}
			m_nPadVDEdgeGray = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 7)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(7);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][7] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (7 - 1)); // Bit Flag.
			}
			m_fPadVDEdgeWdDeltaGradViolation = _ttof(strTemp);
		}
		//-------------------

		if (Col == 1 && Row == 8)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(8);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][8] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (8 - 1)); // Bit Flag.
			}
			m_nHoleEdgeNickGray = _ttoi(strTemp);	//111214 hjc mod
		}

		if (Col == 1 && Row == 9)	//120109 hjc add
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(9);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][9] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (9 - 1)); // Bit Flag.
			}
			m_nHoleEdgeNeibGrayDiff = _ttoi(strTemp);	//111214 hjc mod
		}

		if (Col == 1 && Row == 10)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(10);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][10] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (10 - 1)); // Bit Flag.
			}
			m_fHoleEdgeNickWdDeltaGradViolation = _ttof(strTemp);
		}

		if (Col == 1 && Row == 11)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(11);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][11] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (11 - 1)); // Bit Flag.
			}
			m_fHoleEdgeExcsWdDeltaGradViolation = _ttof(strTemp);
		}

		if (Col == 1 && Row == 12)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(12);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][12] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (12 - 1)); // Bit Flag.
			}
			m_nViaEdgeNickGray = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 13)	//120109 hjc add
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(13);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][13] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (13 - 1)); // Bit Flag.
			}
			m_nViaEdgeNeibGrayDiff = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 14)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(14);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][14] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (14 - 1)); // Bit Flag.
			}
			m_fViaEdgeNickWdDeltaGradViolation = _ttof(strTemp);
		}

		if (Col == 1 && Row == 15)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(15);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(6);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[6][15] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[6] |= (0x00000001 << (15 - 1)); // Bit Flag.
			}
			m_fViaEdgeExcsWdDeltaGradViolation = _ttof(strTemp);
		}

		//-------------------
		//20090216 chg
		if (m_bKeyDown)
		{
			m_bKeyDown = FALSE;
			RefreshSheetOnChanging();
		}

		break;
	case 7:
		if (Col == 1 && Row == 1)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(3);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(7);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[7][1] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[7] |= (0x00000001); // Bit Flag.
			}
			pGlobalDoc->m_nPtSrchRngExt = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 3)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(3);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(7);
				return;
			}
			if (_ttoi(strTemp) < 5 || _ttoi(strTemp) > 700)	//20210625 mod
			{
				strMsg.Format(_T("%s (5~140)%s"),
					pGlobalView->GetLanguageString("MENU", "INPUT_VALUE_RANGE"),
					pGlobalView->GetLanguageString("MENU", "OVER_RANGE"));
				MessageBox(strMsg);
				DisplaySpread(7);
				return;
			}
			else
			{
				if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
				{
					strTemp = CheckLock(m_nTabNum, Row, strTemp);
				}
				if (m_strOriginData[7][3] != strTemp)
				{
					m_bSpecDataChanged = TRUE;
					m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

					m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (3 - 1)); // Bit Flag.
				}
			}
			m_nAlignTolerance = _ttoi(strTemp);
		}

		if (Col == 1 && Row == 4)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(4);
			strTemp = m_Spread.GetText();
			if (!(strTemp == _T("Highest") || strTemp == _T("VeryHigh") || strTemp == _T("Maximum") || strTemp == _T("High") || strTemp == _T("Normal") || strTemp == _T("Low")))
				//if(!(strTemp == "High" || strTemp == "Normal" || strTemp == "Low"))
			{
				DisplaySpread(7);
				return;
			}
			if (m_strOriginData[7][4] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (4 - 1)); // Bit Flag.
			}
			m_strThetaAlign = strTemp;
			if (m_Spread.GetEditMode())
				m_Spread.SetEditMode(FALSE);
		}

		if (Col == 1 && Row == 5)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(5);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(7);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}

			if (_ttof(strTemp) < SizeData[COMMON_PARAMETER].fPixelSizeX)
			{
				strMsg.Format(_T("%s %.1f %s"),
					pGlobalView->GetLanguageString("MENU", "INPUT_VALUE"),
					SizeData[COMMON_PARAMETER].fPixelSizeX,
					pGlobalView->GetLanguageString("MENU", "MUST_OVER"));
				MessageBox(strMsg);
				m_fDefMaskSize = max(SizeData[COMMON_PARAMETER].fPixelSizeX, SpecData.fDefMaskSize);
				DisplaySpread(7);
				return;
			}
			else if (m_strOriginData[7][5] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (5 - 1)); // Bit Flag.
			}
			m_fDefMaskSize = _ttof(strTemp);
		}
		if (Col == 1 && Row == 6)
		{
			m_Spread.SetCol(1);
			m_Spread.SetRow(6);
			strTemp = m_Spread.GetText();

			if (IsCharInString(strTemp))
			{
				strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("MENU", "ERROR_CHAR_NUMBER"));
				MessageBox(strMsg);
				DisplaySpread(7);
				return;
			}
			if (AoiParam()->m_bSetSpecLocking)	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
			{
				strTemp = CheckLock(m_nTabNum, Row, strTemp);
			}
			if (m_strOriginData[7][6] != strTemp)
			{
				m_bSpecDataChanged = TRUE;
				m_Spread.SetForeColor(RGB(255, 0, 0)); //Red

				m_lChangedDataSpreadCellPos[7] |= (0x00000001 << (6 - 1)); // Bit Flag.
			}
			m_fNearDefLen = _ttof(strTemp);
		}

		//20090216 chg
		if (m_bKeyDown)
		{
			m_bKeyDown = FALSE;
			RefreshSheetOnChanging();
		}
		break;

	default:
		;
	}*/
}

void CDlgSpec::DisplaySpec(void)
{
/*	int i = 0;

	//20090216 Spec Fines
	m_fNominalLine = SpecData.fNominalLineWidth;
	m_fRealNormLine = SpecData.fRealNominalLineWidth;

	m_nNickGray = SpecData.nNickGraySpec;
	m_nOpenGray = SpecData.nOpenGraySpec;	//150410 hjc add
	m_nHalfSideNickDiffBrightGray = SpecData.nHalfSideNickDiffBrightGray;
	m_nHalfSideNickDiffDarkGray = SpecData.nHalfSideNickDiffDarkGray;

	m_nIRISPosID = pGlobalDoc->m_nIRISPosID;

	//170403 hjc add
	m_nFineNickGray = SpecData.nFineNickGraySpec;
	m_nFineOpenGray = SpecData.nFineOpenGraySpec;
	m_nFineHalfSideNickDiffBrightGray = SpecData.nFineHalfSideNickDiffBrightGray;
	m_nFineHalfSideNickDiffDarkGray = SpecData.nFineHalfSideNickDiffDarkGray;
	//170403 hjc add end


	//------------------------------------------------

	m_nHoleMissingGray = SpecData.nHoleMissingGray;

	m_nHoleDefSize = max(min(SpecData.nHoleDefNum, 90), 1);


	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
		m_strMinSP = CString(SpecData.szMinSPSize);
	}
	else
	{
		m_nMinSPPercent = SpecData.nMinSPPercent;
	}

	for (i = 0; i < 15; i++)
	{
		if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
		{
			m_strNick[i] = CString(SpecData.szNickSize[i]);
			m_strProtrusion[i] = CString(SpecData.szProtrusionSize[i]);
			m_strFineNick[i] = CString(SpecData.szFineNickSize[i]);
			m_strFineProtrusion[i] = CString(SpecData.szFineProtrusionSize[i]);
			m_nNickPercent[i] = SpecData.nNickPercent[i];
			m_nProtrusionPercent[i] = SpecData.nProtrusionPercent[i];
			m_nFineNickPercent[i] = SpecData.nFineNickPercent[i];
			m_nFineProtrusionPercent[i] = SpecData.nFineProtrusionPercent[i];
		}
		else
		{
			m_nNickPercent[i] = SpecData.nNickPercent[i];
			m_nProtrusionPercent[i] = SpecData.nProtrusionPercent[i];
			m_nFineNickPercent[i] = SpecData.nFineNickPercent[i];
			m_nFineProtrusionPercent[i] = SpecData.nFineProtrusionPercent[i];
		}

		m_fLineWdDeltaGradViolation[i] = SpecData.fLineWdDeltaGradViolation[i];
		m_fExcsWdDeltaGradViolation[i] = SpecData.fExcsWdDeltaGradViolation[i];
		m_nNickNGFilterPercent[i] = SpecData.nNickNGFilterPercent[i];
		m_nExcsNGFilterPercent[i] = SpecData.nExcsNGFilterPercent[i];
		m_nFineNickNGFilterPercent[i] = SpecData.nFineNickNGFilterPercent[i];
		m_nFineExcsNGFilterPercent[i] = SpecData.nFineExcsNGFilterPercent[i];
		m_fFineLineWdDeltaGradViolation[i] = SpecData.fFineLineWdDeltaGradViolation[i];
		m_fFineExcsWdDeltaGradViolation[i] = SpecData.fFineExcsWdDeltaGradViolation[i];
	}


	m_strThetaAlign = pGlobalDoc->m_strThetaAlign;

	m_MinSpGray = SpecData.nMinSpaceGraySpec;

	m_nSpaceNGFilterPercent = SpecData.nSpaceNGFilterPercent;
	//20090228 hjc
	m_fMinSpWidth = SpecData.fMinSpWidth;
	m_fSpWdDeltaGradViolation = SpecData.fSpWdDeltaGradViolation;
	m_fSpWdDeltaOuterGradViolation = SpecData.fSpWdDeltaOuterGradViolation;   //20090405 hjc
	m_fFineMinSpWidth = SpecData.fFineMinSpWidth;		//121226 hjc add
														//-----------------

	m_fDefMaskSize = max(SizeData[COMMON_PARAMETER].fPixelSizeX, SpecData.fDefMaskSize);
	m_fNearDefLen = SpecData.fNearDefLen;

	m_nLeadOpenGray = SpecData.nLeadOpenGray;

	if (SpecData.nAlignTolerance == 0)
	{
		m_nAlignTolerance = 25;
	}

	m_nAlignTolerance = SpecData.nAlignTolerance;

	//170112 hjc mod RLE
	m_strPadBallPrec = CString(SpecData.szPADRLPrecName);
	m_strLP_Prec = CString(SpecData.szLPADRLName);
	m_strSP_Prec = CString(SpecData.szSPRLName);
	m_strSPExt_Prec = CString(SpecData.szSPACEEXTRLName);
	m_strFPad_Prec = CString(SpecData.szPADFine_PrecName);
	m_strARLand_Prec = CString(SpecData.szARLandPrecName);
	m_strCO2Land_Prec = CString(SpecData.szCO2LandPrecName);
	m_strPadTip_Prec = CString(SpecData.szPADTipPrecName);
	//170112 hjc mod end

	m_fHoleTolerance = SpecData.fHoleTolerance;

	//20090311 hjc add
	m_fHoleDiaLower = SpecData.fHoleDiaLower;
	m_fHoleDiaUpper = SpecData.fHoleDiaUpper;
	m_nHoleInnerGray = SpecData.nHoleInnerGray;
	//-----------

	m_strHolePrec = CString(SpecData.szHoleRLPrecName);
	m_nHoleOpenGray = min(max(m_nHoleOpenGray, 1), 130);

	m_fARLandMin = SpecData.fARLandMin;
	m_fPADTipMin = SpecData.fPADTipMin;
	m_fIsLandMin = SpecData.fIsLandMin;
	//20090412 hjc
	m_nIsLandExtGray = SpecData.nIsLandExtGray;
	m_fIsLandExtMin = SpecData.fIsLandExtMin;
	//jun 20120903 for LG_CCL-Inspector
	m_nCCLGray = SpecData.nCCLGray;
	m_fCCLCircularity = SpecData.fCCLCircularity;
	m_fCCLDefSize = SpecData.fCCLDefSize;

	//2022 01 10 lgh add
	m_nCharInspectionGray = SpecData.nCharInspectionGray;
	m_dCharRegionUpperPercent = SpecData.dCharRegionUpperPercent;
	m_dCharRegionLowerPercent = SpecData.dCharRegionLowerPercent;



	//------------
	m_fVDPadMin = SpecData.fVDPadMin;
	//20090419 hjc
	m_fVDLocationTolerance = SpecData.fVDLocationTolerance;
	m_fFineVDPadMin = SpecData.fFinePADVoidMin;
	m_nFinePADVoidGraySpec = SpecData.nFinePADVoidGraySpec;
	//-------

	m_fPinHoleMin = SpecData.fPinHoleMin;
	m_fPADVoidMin = SpecData.fPADVoidMin;

	m_nIsLandGray = SpecData.nIsLandGraySpec;
	m_nPinHoleGray = SpecData.nPinHoleGraySpec;
	m_nPADVoidGray = SpecData.nPADVoidGraySpec;


	m_nCO2MissingGray = SpecData.nCO2MissingGray;
	m_nCO2HoleNum = SpecData.nCO2HoleNum;
	m_nCO2MisAgnGray = SpecData.nCO2MisAgnGray;
	m_nCO2MisAgnDefPercent = SpecData.nCO2MisAgnDefPercent;
	m_nCO2OpenGray = SpecData.nCO2OpenGray;

	//20090412 hjc
	m_nNeibSpGrayDiff = SpecData.nNeibSpGrayDiff;
	m_nUSDarkGrayMinus = SpecData.nUSDarkGrayMinus;	//150413 hjc add
													//20100210 hjc add
	if (pGlobalDoc->m_bUseMultiVaccumControl)	//130311 hjc add
		m_strSelectVaccum = CString(SpecData.strSelectVaccum);
	else
		m_strSelectVaccum = "Both";

	//20100322 hjc add
	m_nHoleLandVoidGray = SpecData.nHoleLandVoidGray;
	m_nCO2LandVoidGraySpec = SpecData.nCO2LandVoidGraySpec;
	m_strCO2Land_Prec = CString(SpecData.szCO2LandPrecName);
	m_fCO2LandMin = SpecData.fCO2LandMin;
	m_strCO2LandAlignMode = CString(SpecData.szCO2LandAlignMode);
	//----------------------
	*/
}





void CDlgSpec::RefreshSheetOnChanging()
{
/*	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	if (m_Spread.GetEditMode())
		m_Spread.SetEditMode(FALSE); //160302 LGH ADD
	int nTabNum = m_tabDlgInspection.GetCurSel();
	m_nSpreadCellFocusPos[nTabNum] = max(1, m_nSpreadCellFocusPos[nTabNum]);
	m_Spread.SetActiveCell(1, m_nSpreadCellFocusPos[nTabNum]);

	//m_Spread.SetEditEnterAction(2);
	m_lNewSelectRow[m_nTabNum] = m_nSpreadCellFocusPos[nTabNum];

	TRACE("RefreshSheetOnChanging %d - %d\n", 1, m_nSpreadCellFocusPos[nTabNum]);

	DisplaySelectRow();
	DisplayChangedData();*/
}

void CDlgSpec::DisplayChangedData()
{
/*	int i;
	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	switch (m_nTabNum)
	{
	case 0:
		for (i = 1; i <= 16; i++)
		{
			if (m_lChangedDataSpreadCellPos[0] & (0x00000001 << (i - 1)))
			{
				TRACE("m_lChangedDataSpreadCellPos %d - %d\n", 1, i);
				m_Spread.SetCol(1);
				m_Spread.SetRow(i);
				m_Spread.SetForeColor(RGB(255, 0, 0)); // Red
			}
		}
		break;

	case 1:
		for (i = 1; i <= 16; i++)
		{
			if (m_lChangedDataSpreadCellPos[1] & (0x00000001 << (i - 1)))
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(i);
				m_Spread.SetForeColor(RGB(255, 0, 0)); // Red
			}
		}
		break;

	case 2:
		for (i = 1; i <= 9; i++)	//121226 hjc mod
		{
			if (m_lChangedDataSpreadCellPos[2] & (0x00000001 << (i - 1)))
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(i);
				m_Spread.SetForeColor(RGB(255, 0, 0)); // Red
			}
		}
		break;

	case 3:
		if (SpecData.bEnableCharInspection)
		{
			for (i = 1; i <= 15; i++)	//jun 20120903 for LG_CCL-Inspector
			{
				if (m_lChangedDataSpreadCellPos[3] & (0x00000001 << (i - 1)))
				{
					m_Spread.SetCol(1);
					m_Spread.SetRow(i);
					m_Spread.SetForeColor(RGB(255, 0, 0)); // Red
				}
			}
		}
		else
		{
			for (i = 1; i <= 12; i++)	//jun 20120903 for LG_CCL-Inspector
			{
				if (m_lChangedDataSpreadCellPos[3] & (0x00000001 << (i - 1)))
				{
					m_Spread.SetCol(1);
					m_Spread.SetRow(i);
					m_Spread.SetForeColor(RGB(255, 0, 0)); // Red
				}
			}
		}
		break;

		//20100322 hjc add
	case 4:
		for (i = 1; i <= 22; i++)
		{
			if (m_lChangedDataSpreadCellPos[4] & (0x00000001 << (i - 1)))
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(i);
				m_Spread.SetForeColor(RGB(255, 0, 0)); // Red
			}
		}
		break;

	case 5:
		for (i = 1; i <= 18; i++)
		{
			if (m_lChangedDataSpreadCellPos[5] & (0x00000001 << (i - 1)))
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(i);
				m_Spread.SetForeColor(RGB(255, 0, 0)); // Red
			}
		}
		break;

	case 6:
		for (i = 1; i <= 15; i++)	//120105 hjc mod
		{
			if (m_lChangedDataSpreadCellPos[6] & (0x00000001 << (i - 1)))
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(i);
				m_Spread.SetForeColor(RGB(255, 0, 0)); // Red
			}
		}
		break;

	case 7:
		for (i = 1; i <= 10; i++)		//20100210 hjc mod
		{
			if (m_lChangedDataSpreadCellPos[7] & (0x00000001 << (i - 1)))
			{
				m_Spread.SetCol(1);
				m_Spread.SetRow(i);
				m_Spread.SetForeColor(RGB(255, 0, 0)); // Red
			}
		}
		break;

	default:
		;
	}*/
}

void CDlgSpec::SetGroupBackColor()
{
/*	int i, j, iCol;
	m_Spread.SetReDraw(FALSE);

	switch (m_nTabNum)
	{
	case 0:
		//Set Color Group
		for (i = 1; i <= 16; i++)
			for (j = 1; j <= 2; j++)
			{
				m_Spread.SetRow(i);
				m_Spread.SetCol(j);
				m_Spread.SetBackColor(RGB(255, 255, 255));
			}

		for (iCol = 1; iCol <= 2; iCol++)
		{
			m_Spread.SetCol(iCol);

			m_Spread.SetRow(1);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(2);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);

			m_Spread.SetRow(3);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(4);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(5);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(6);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(7);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);

			m_Spread.SetRow(8);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(9);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(10);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(11);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(12);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);

			m_Spread.SetRow(13);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(14);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);

			m_Spread.SetRow(15);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
			m_Spread.SetRow(16);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
		}
		break;
	case 1:
		//Set Color Group
		for (i = 1; i <= 16; i++)
			for (j = 1; j <= 2; j++)
			{
				m_Spread.SetRow(i);
				m_Spread.SetCol(j);
				m_Spread.SetBackColor(RGB(255, 255, 255));
			}
		for (iCol = 1; iCol <= 2; iCol++)
		{
			m_Spread.SetCol(iCol);

			m_Spread.SetRow(1);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(2);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);

			m_Spread.SetRow(3);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(4);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(5);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(6);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(7);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);

			m_Spread.SetRow(8);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(9);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(10);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(11);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(12);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);

			m_Spread.SetRow(13);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(14);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);

			m_Spread.SetRow(15);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
			m_Spread.SetRow(16);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
		}

		break;
	case 2:
		//Set Color Group
		for (i = 1; i <= 9; i++)
			for (j = 1; j <= 2; j++)
			{
				m_Spread.SetRow(i);
				m_Spread.SetCol(j);
				m_Spread.SetBackColor(RGB(255, 255, 255));
			}
		for (iCol = 1; iCol <= 2; iCol++)
		{
			m_Spread.SetCol(iCol);

			m_Spread.SetRow(1);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(2);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(3);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);

			m_Spread.SetRow(4);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(5);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(6);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);

			m_Spread.SetRow(7);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(8);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);

			m_Spread.SetRow(9);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
		}
		break;
	case 3:		//20100322 hjc add
				//Set Color Group
		if (SpecData.bEnableCharInspection)
		{
			for (i = 1; i <= 15; i++)
				for (j = 1; j <= 2; j++)
				{
					m_Spread.SetRow(i);
					m_Spread.SetCol(j);
					m_Spread.SetBackColor(RGB(255, 255, 255));
				}
		}
		else
		{
			for (i = 1; i <= 12; i++)
				for (j = 1; j <= 2; j++)
				{
					m_Spread.SetRow(i);
					m_Spread.SetCol(j);
					m_Spread.SetBackColor(RGB(255, 255, 255));
				}
		}

		for (iCol = 1; iCol <= 2; iCol++)
		{
			m_Spread.SetCol(iCol);

			m_Spread.SetRow(1);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(2);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(3);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);

			m_Spread.SetRow(4);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(5);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(6);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(7);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(8);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(9);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);

			m_Spread.SetRow(10);		//jun 20120903 for LG_CCL-Inspector
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(11);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(12);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			//--------------------------------------------------------

			if (SpecData.bEnableCharInspection)
			{
				m_Spread.SetRow(13);		//jun 20120903 for LG_CCL-Inspector
				m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
				m_Spread.SetRow(14);
				m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
				m_Spread.SetRow(15);
				m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			}
		}
		break;
	case 4:
		//Set Color Group
		for (i = 1; i <= 22; i++)
			for (j = 1; j <= 2; j++)
			{
				m_Spread.SetRow(i);
				m_Spread.SetCol(j);
				m_Spread.SetBackColor(RGB(255, 255, 255));
			}
		for (iCol = 1; iCol <= 2; iCol++)
		{
			m_Spread.SetCol(iCol);

			m_Spread.SetRow(1);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(2);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(3);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(4);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(5);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);

			m_Spread.SetRow(6);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(7);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(8);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(9);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(10);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);

			m_Spread.SetRow(11);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(12);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(13);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(14);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);

			m_Spread.SetRow(15);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(16);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(17);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(18);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(19);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);

			m_Spread.SetRow(20);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
			m_Spread.SetRow(21);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
			m_Spread.SetRow(22);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
			//--------------------------------------------------------
		}
		break;

	case 5:
		//Set Color Group
		for (i = 1; i <= 18; i++)
			for (j = 1; j <= 2; j++)
			{
				m_Spread.SetRow(i);
				m_Spread.SetCol(j);
				m_Spread.SetBackColor(RGB(255, 255, 255));
			}
		for (iCol = 1; iCol <= 2; iCol++)
		{
			m_Spread.SetCol(iCol);

			m_Spread.SetRow(1);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(2);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(3);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);

			m_Spread.SetRow(4);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(5);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);

			m_Spread.SetRow(6);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(7);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(8);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);

			m_Spread.SetRow(9);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(10);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(11);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(12);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(13);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(14);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(15);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(16);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(17);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(18);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			//--------------------------------------------------------
		}
		break;

	case 6:
		//Set Color Group
		for (i = 1; i <= 15; i++)
			for (j = 1; j <= 2; j++)
			{
				m_Spread.SetRow(i);
				m_Spread.SetCol(j);
				m_Spread.SetBackColor(RGB(255, 255, 255));
			}
		for (iCol = 1; iCol <= 2; iCol++)
		{
			m_Spread.SetCol(iCol);

			m_Spread.SetRow(1);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(2);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(3);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(4);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(5);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);

			m_Spread.SetRow(6);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(7);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);

			m_Spread.SetRow(8);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(9);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(10);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);
			m_Spread.SetRow(11);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);

			m_Spread.SetRow(12);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(13);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(14);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			m_Spread.SetRow(15);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
		}
		break;

	case 7:
		//Set Color Group
		for (i = 1; i <= 7; i++)
			for (j = 1; j <= 2; j++)
			{
				m_Spread.SetRow(i);
				m_Spread.SetCol(j);
				m_Spread.SetBackColor(RGB(255, 255, 255));
			}
		for (iCol = 1; iCol <= 2; iCol++)
		{
			m_Spread.SetCol(iCol);

			m_Spread.SetRow(1);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(2);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(3);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);
			m_Spread.SetRow(4);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR);

			m_Spread.SetRow(5);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);
			m_Spread.SetRow(6);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR1);

			m_Spread.SetRow(7);
			m_Spread.SetBackColor(SPREAD_GROUP_COLOR2);

			if (AoiParam()->m_bUseAutoPinPosAdjust || g_bUsePinPosEstimate)
			{
				m_Spread.SetRow(8);
				m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);

				m_Spread.SetRow(9);
				m_Spread.SetBackColor(SPREAD_GROUP_COLOR3);
			}

#ifdef IRIS_AXIS
			if (AoiParam()->m_bUseAutoPinPosAdjust || g_bUsePinPosEstimate)
			{
				m_Spread.SetRow(10);
				m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
			}
			else
			{
				m_Spread.SetRow(8);
				m_Spread.SetBackColor(SPREAD_GROUP_COLOR4);
			}
#endif

		}
		break;
	default:
		;
	}

	m_Spread.SetReDraw(TRUE);*/
}

void CDlgSpec::DisplaySelectRow()
{
/*	m_Spread.Attach((TSpread*)GetDlgItem(IDC_FPSPREAD_SPEC1));
	//	TSpread* pSpread=(TSpread*)GetDlgItem(IDC_FPSPREAD_SPEC1);

	//pSpread->SetEditMode(FALSE);

	//m_Spread.SetEditMode(FALSE);
	if (m_lOldSelectRow[m_nTabNum] != 0) // Clear Color Line.
	{
		m_Spread.SetCol(1);
		m_Spread.SetRow(m_lOldSelectRow[m_nTabNum]);
		SetGroupBackColor();
	}
	TRACE("DisplaySelectRow %d - %d\n", 1, m_lNewSelectRow[m_nTabNum]);
	m_Spread.SetCol(1);
	m_Spread.SetRow(m_lNewSelectRow[m_nTabNum]);
	m_Spread.SetBackColor(0x00C0E0FF); //Bright Orange

	m_lOldSelectRow[m_nTabNum] = m_lNewSelectRow[m_nTabNum];*/
}

void CDlgSpec::LoadOriginDataTab(int nTabNum)
{
/*	switch (nTabNum)
	{
	case 0:
		LoadOriginDataTab0();
		break;
	case 1:
		LoadOriginDataTab1();
		break;
	case 2:
		LoadOriginDataTab2();
		break;
	case 3:
		LoadOriginDataTab3();
		break;
	case 4:
		LoadOriginDataTab4();
		break;
	case 5:
		LoadOriginDataTab5();
		break;
	case 6:
		LoadOriginDataTab6();
		break;
	case 7:	//20100322 hjc add
		LoadOriginDataTab7();
		break;
	}*/
}

void CDlgSpec::LoadOriginDataTab0()
{
/*
	CString strTemp;

	strTemp.Format(_T("%.1f"), m_fNominalLine);
	m_strOriginData[0][1] = strTemp;

	strTemp.Format(_T("%.1f"), m_fRealNormLine);
	m_strOriginData[0][2] = strTemp;

	strTemp.Format(_T("%d"), m_nNickGray);
	m_strOriginData[0][3] = strTemp;

	//150410 hjc add
	strTemp.Format(_T("%d"), m_nOpenGray);
	m_strOriginData[0][4] = strTemp;

	strTemp.Format(_T("%d"), m_nHalfSideNickDiffBrightGray);
	m_strOriginData[0][5] = strTemp;

	strTemp.Format(_T("%d"), m_nHalfSideNickDiffDarkGray);
	m_strOriginData[0][6] = strTemp;

	strTemp.Format(_T("%d"), m_nLeadOpenGray);
	m_strOriginData[0][7] = strTemp;

	strTemp.Format(_T("%.1f"), m_fMinCheckWidth);
	m_strOriginData[0][8] = strTemp;

	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
		m_strOriginData[0][9] = m_strNick[0];
		m_strOriginData[0][10] = m_strProtrusion[0];
	}
	else
	{
		strTemp.Format(_T("%d"), m_nNickPercent[0]);	//150413 hjc add
		m_strOriginData[0][9] = strTemp;

		strTemp.Format(_T("%d"), m_nProtrusionPercent[0]);
		m_strOriginData[0][10] = strTemp;
	}

	strTemp.Format(_T("%d"), m_nNickNGFilterPercent[0]);
	m_strOriginData[0][11] = strTemp;

	strTemp.Format(_T("%d"), m_nExcsNGFilterPercent[0]);
	m_strOriginData[0][12] = strTemp;

	strTemp.Format(_T("%.2f"), m_fLineWdDeltaGradViolation[0]);
	m_strOriginData[0][13] = strTemp;

	strTemp.Format(_T("%.2f"), m_fExcsWdDeltaGradViolation[0]);
	m_strOriginData[0][14] = strTemp;

	CString strVal;
	int idx;
	if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx)	//170526 hjc mod
	{
		strTemp = _T("");
		for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
		{
			if (idx)
				strTemp += _T("/");
			strVal.Format(_T("%.1f"), m_fNarrowTraceViolation[idx]);
			strTemp += strVal;
		}
	}
	else
	{
		strTemp.Format(_T("%.1f"), m_fNarrowTraceViolation[0]);
	}
	m_strOriginData[0][15] = strTemp;

	if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx)	//170526 hjc mod
	{
		strTemp = "";
		for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
		{
			if (idx)
				strTemp += _T("/");
			strVal.Format(_T("%.1f"), m_fWideTraceViolation[idx]);
			strTemp += strVal;
		}
	}
	else
	{
		strTemp.Format(_T("%.1f"), m_fWideTraceViolation[0]);
	}
	m_strOriginData[0][16] = strTemp;*/
}

void CDlgSpec::LoadOriginDataTab1()
{
/*	CString strTemp;

	strTemp.Format(_T("%.1f"), m_fNominalLine);
	m_strOriginData[1][1] = strTemp;

	strTemp.Format(_T("%.1f"), m_fRealNormLine);
	m_strOriginData[1][2] = strTemp;

	strTemp.Format(_T("%d"), m_nFineNickGray);	//170403 hjc mod
	m_strOriginData[1][3] = strTemp;

	//150410 hjc add
	strTemp.Format(_T("%d"), m_nFineOpenGray);
	m_strOriginData[1][4] = strTemp;

	strTemp.Format(_T("%d"), m_nFineHalfSideNickDiffBrightGray);
	m_strOriginData[1][5] = strTemp;

	strTemp.Format(_T("%d"), m_nFineHalfSideNickDiffDarkGray);
	m_strOriginData[1][6] = strTemp;

	strTemp.Format(_T("%d"), m_nLeadOpenGray);
	m_strOriginData[1][7] = strTemp;

	strTemp.Format(_T("%.1f"), m_fFineMinCheckWidth);
	m_strOriginData[1][8] = strTemp;

	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
		m_strOriginData[1][9] = m_strFineNick[0];
		m_strOriginData[1][10] = m_strFineProtrusion[0];
	}
	else
	{
		strTemp.Format(_T("%d"), m_nFineNickPercent[0]);
		m_strOriginData[1][9] = strTemp;

		strTemp.Format(_T("%d"), m_nFineProtrusionPercent[0]);
		m_strOriginData[1][10] = strTemp;
	}

	strTemp.Format(_T("%d"), m_nFineNickNGFilterPercent[0]);
	m_strOriginData[1][11] = strTemp;

	strTemp.Format(_T("%d"), m_nFineExcsNGFilterPercent[0]);
	m_strOriginData[1][12] = strTemp;

	strTemp.Format(_T("%.2f"), m_fFineLineWdDeltaGradViolation[0]);
	m_strOriginData[1][13] = strTemp;

	strTemp.Format(_T("%.2f"), m_fFineExcsWdDeltaGradViolation[0]);
	m_strOriginData[1][14] = strTemp;

	CString strVal;
	int idx;
	if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx)
	{
		strTemp = "";
		for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
		{
			if (idx)
				strTemp += _T("/");
			strVal.Format(_T("%.1f"), m_fFineNarrowTraceViolation[idx]);
			strTemp += strVal;
		}
	}
	else
		strTemp.Format(_T("%.1f"), m_fFineNarrowTraceViolation[0]);
	m_strOriginData[1][15] = strTemp;

	if (SpecData.nLineWidthGroupNum > 0 && AoiParam()->m_bUseMultilineSpecEx)
	{
		strTemp = "";
		for (idx = 0; idx < SpecData.nLineWidthGroupNum; idx++)
		{
			if (idx)
				strTemp += _T("/");
			strVal.Format(_T("%.1f"), m_fFineWideTraceViolation[idx]);
			strTemp += strVal;
		}
	}
	else
		strTemp.Format(_T("%.1f"), m_fFineWideTraceViolation[0]);
	m_strOriginData[1][16] = strTemp;*/
}

void CDlgSpec::LoadOriginDataTab2()
{
/*	CString strTemp;

	strTemp.Format(_T("%d"), m_MinSpGray);
	m_strOriginData[2][1] = strTemp;

	strTemp.Format(_T("%d"), m_nNeibSpGrayDiff);
	m_strOriginData[2][2] = strTemp;

	//150413 hjc add
	strTemp.Format(_T("%d"), m_nUSDarkGrayMinus);
	m_strOriginData[2][3] = strTemp;

	strTemp.Format(_T("%.1f"), m_fMinSpWidth);
	m_strOriginData[2][4] = strTemp;

	//if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	//{
	//m_Spread.SetRow(5);
	//if(m_strMinSP == "Highest")
	//strTemp = m_strMinSP + "   (90%)";
	//if(m_strMinSP == "VeryHigh")
	//strTemp = m_strMinSP + "   (80%)";
	//if(m_strMinSP == "High")
	//strTemp = m_strMinSP + "   (70%)";
	//if(m_strMinSP == "Normal")
	//strTemp = m_strMinSP + "   (60%)";
	//if(m_strMinSP == "Low")
	//strTemp = m_strMinSP + "   (50%)";
	//if(m_strMinSP == "VeryLow")
	//strTemp = m_strMinSP + "   (40%)";
	//if(m_strMinSP == "Lowest")
	//strTemp = m_strMinSP + "   (30%)";
	//m_Spread.SetText(strTemp);
	//m_Spread.SetCellNote(_T("GigaVis _ Note 48 !!!"));
	//}
	//else
	//{
	//m_Spread.SetRow(5);
	//strTemp.Format(_T("%d"), m_nMinSPPercent);
	//m_Spread.SetText(strTemp);
	//m_Spread.SetCellNote(_T("GigaVis _ Note 48 !!!"));
	//}

	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
		int nPos = m_strMinSP.Find(_T(" "), 0);
		if (nPos >= 0)
			m_strMinSP = m_strMinSP.Left(nPos);

		m_strOriginData[2][5] = m_strMinSP;
	}
	else
	{
		strTemp.Format(_T("%d"), m_nMinSPPercent);
		m_strOriginData[2][5] = strTemp;
	}

	strTemp.Format(_T("%d"), m_nSpaceNGFilterPercent);
	m_strOriginData[2][6] = strTemp;

	//20090228 hjc
	strTemp.Format(_T("%.2f"), m_fSpWdDeltaGradViolation);
	m_strOriginData[2][7] = strTemp;

	//20090405 hjc
	strTemp.Format(_T("%.2f"), m_fSpWdDeltaOuterGradViolation);
	m_strOriginData[2][8] = strTemp;

	strTemp.Format(_T("%.1f"), m_fFineMinSpWidth);	//121226 hjc add
	m_strOriginData[2][9] = strTemp;
	//-----------
*/
}

void CDlgSpec::LoadOriginDataTab3()
{
/*	CString strTemp;

	strTemp.Format(_T("%d"), m_nPinHoleGray);
	m_strOriginData[3][1] = strTemp;

	m_strOriginData[3][2] = m_strLP_Prec;

	strTemp.Format(_T("%.1f"), m_fPinHoleMin);
	m_strOriginData[3][3] = strTemp;

	strTemp.Format(_T("%d"), m_nIsLandGray);
	m_strOriginData[3][4] = strTemp;

	m_strOriginData[3][5] = m_strSP_Prec;		//170112 hjc mod SpecData.szSPRLName

	strTemp.Format(_T("%.1f"), m_fIsLandMin);
	m_strOriginData[3][6] = strTemp;

	//20090412 hjc
	strTemp.Format(_T("%d"), m_nIsLandExtGray);
	m_strOriginData[3][7] = strTemp;

	m_strOriginData[3][8] = m_strSPExt_Prec;		//170112 hjc add

	strTemp.Format(_T("%.1f"), m_fIsLandExtMin);
	m_strOriginData[3][9] = strTemp;

	//jun 20120903 for LG_CCL-Inspector
	strTemp.Format(_T("%d"), m_nCCLGray);
	m_strOriginData[3][10] = strTemp;

	strTemp.Format(_T("%.1f"), m_fCCLCircularity);
	m_strOriginData[3][11] = strTemp;

	strTemp.Format(_T("%.1f"), m_fCCLDefSize);
	m_strOriginData[3][12] = strTemp;
	//---------------

	//2022 01 10 lgh add
	if (SpecData.bEnableCharInspection)
	{
		strTemp.Format(_T("%d"), m_nCharInspectionGray);
		m_strOriginData[3][13] = strTemp;

		strTemp.Format(_T("%.1f"), m_dCharRegionUpperPercent);
		m_strOriginData[3][14] = strTemp;

		strTemp.Format(_T("%.1f"), m_dCharRegionLowerPercent);
		m_strOriginData[3][15] = strTemp;
	}
*/
}

//20100322 hjc add
void CDlgSpec::LoadOriginDataTab4()
{
/*	CString strTemp;

	strTemp.Format(_T("%d"), SpecData.nVDrillDiffBrightGray);
	m_strOriginData[4][1] = strTemp;

	strTemp.Format(_T("%d"), SpecData.nVDrillDiffDarkGray);
	m_strOriginData[4][2] = strTemp;

	strTemp.Format(_T("%.1f"), SpecData.fVDPadPrecName);
	m_strOriginData[4][3] = strTemp;

	//20090419 hjc
	strTemp.Format(_T("%.1f"), m_fVDLocationTolerance);
	m_strOriginData[4][4] = strTemp;
	//

	strTemp.Format(_T("%.1f"), m_fVDPadMin);
	m_strOriginData[4][5] = strTemp;

	strTemp.Format(_T("%d"), m_nPADVoidGray);
	m_strOriginData[4][6] = strTemp;

	m_strOriginData[4][7] = m_strPadBallPrec;

	strTemp.Format(_T("%.1f"), m_fPADVoidMin);
	m_strOriginData[4][8] = strTemp;

	m_strOriginData[4][9] = m_strPadTip_Prec;		//170112 hjc mod SpecData.szPADTipPrecName	

	strTemp.Format(_T("%.1f"), m_fPADTipMin);
	m_strOriginData[4][10] = strTemp;

	//20100322 hjc add
	strTemp.Format(_T("%d"), m_nHoleLandVoidGray);
	m_strOriginData[4][11] = strTemp;

	m_strOriginData[4][12] = m_strARLand_Prec;	//170112 hjc mod SpecData.szARLandPrecName

	strTemp.Format(_T("%.1f"), m_fARLandMin);
	m_strOriginData[4][13] = strTemp;

	strTemp.Format(_T("%.1f"), SpecData.fHoleFillExt);
	m_strOriginData[4][14] = strTemp;

	//20100322 hjc add
	strTemp.Format(_T("%d"), m_nCO2LandVoidGraySpec);
	m_strOriginData[4][15] = strTemp;

	m_strOriginData[4][16] = m_strCO2Land_Prec;	//170112 hjc mod SpecData.szCO2LandPrecName

	strTemp.Format(_T("%.1f"), m_fCO2LandMin);
	m_strOriginData[4][17] = strTemp;

	m_strOriginData[4][18] = SpecData.szCO2LandAlignMode;

	//20100323 hjc add
	strTemp.Format(_T("%.1f"), SpecData.fCO2HoleFillExt);
	m_strOriginData[4][19] = strTemp;

	strTemp.Format(_T("%d"), m_nFinePADVoidGraySpec);	//090324-ndy
	m_strOriginData[4][20] = strTemp;

	m_strOriginData[4][21] = m_strFPad_Prec;		//170112 hjc mod SpecData.szPADFine_PrecName

	strTemp.Format(_T("%.1f"), m_fFineVDPadMin);	//090324-ndy
	m_strOriginData[4][22] = strTemp;

	//---------------
	*/
}

void CDlgSpec::LoadOriginDataTab5()
{
/*	CString strTemp;

	//20090311 hjc modify
	strTemp.Format(_T("%.1f"), m_fHoleTolerance);
	m_strOriginData[5][1] = strTemp;

	strTemp.Format(_T("%.2f"), m_fHoleDiaUpper);
	m_strOriginData[5][2] = strTemp;

	strTemp.Format(_T("%.2f"), m_fHoleDiaLower);
	m_strOriginData[5][3] = strTemp;

	strTemp.Format(_T("%d"), m_nHoleOpenGray);
	m_strOriginData[5][4] = strTemp;

	strTemp.Format(_T("%d"), m_nHoleMissingGray);
	m_strOriginData[5][5] = strTemp;

	strTemp.Format(_T("%d"), m_nHoleInnerGray);
	m_strOriginData[5][6] = strTemp;

	m_strOriginData[5][7] = m_strHolePrec;

	strTemp.Format(_T("%d"), m_nHoleDefSize);
	m_strOriginData[5][8] = strTemp;

	strTemp.Format(_T("%s"), CharToString(SpecData.szVHMode));
	m_strOriginData[5][9] = strTemp;

	strTemp.Format(_T("%d"), m_nCO2MissingGray);
	m_strOriginData[5][10] = strTemp;

	strTemp.Format(_T("%d"), m_nCO2HoleNum);
	m_strOriginData[5][11] = strTemp;

	strTemp.Format(_T("%d"), m_nCO2OpenGray);
	m_strOriginData[5][12] = strTemp;

	strTemp.Format(_T("%d"), m_nCO2MisAgnGray);
	m_strOriginData[5][13] = strTemp;

	strTemp.Format(_T("%d"), m_nCO2MisAgnDefPercent);
	m_strOriginData[5][14] = strTemp;

	strTemp.Format(_T("%d"), SpecData.nVHEdgeThrDiffGray);
	m_strOriginData[5][15] = strTemp;

	strTemp.Format(_T("%d"), SpecData.nVHBreakOutGray);
	m_strOriginData[5][16] = strTemp;

	strTemp.Format(_T("%d"), SpecData.nVHDissmearGray);
	m_strOriginData[5][17] = strTemp;

	strTemp.Format(_T("%d"), SpecData.nVHContiBreakOutNum);
	m_strOriginData[5][18] = strTemp;*/
}

void CDlgSpec::LoadOriginDataTab6()
{
/*	CString strTemp;

	//20090228 modify hjc
	strTemp.Format(_T("%d"), m_nPadEdgeNickGray);
	m_strOriginData[6][1] = strTemp;

	strTemp.Format(_T("%d"), m_nPadEdgeNeibGrayDiff);	//120105 hjc add
	m_strOriginData[6][2] = strTemp;

	strTemp.Format(_T("%d"), m_nPadEdgeBADiffDarkGray);	//150413 hjc add
	m_strOriginData[6][3] = strTemp;

	strTemp.Format(_T("%.1f"), m_fPadEdgeNickWdDeltaGradViolation);
	m_strOriginData[6][4] = strTemp;

	strTemp.Format(_T("%.1f"), m_fPadEdgeExcsWdDeltaGradViolation);
	m_strOriginData[6][5] = strTemp;

	//---------------
	//20090412 hjc
	strTemp.Format(_T("%d"), m_nPadVDEdgeGray);
	m_strOriginData[6][6] = strTemp;

	strTemp.Format(_T("%.2f"), m_fPadVDEdgeWdDeltaGradViolation);
	m_strOriginData[6][7] = strTemp;
	//--------------

	strTemp.Format(_T("%d"), m_nHoleEdgeNickGray);	//111214 hjc mod
	m_strOriginData[6][8] = strTemp;

	strTemp.Format(_T("%d"), m_nHoleEdgeNeibGrayDiff);	//120109 hjc mod
	m_strOriginData[6][9] = strTemp;

	strTemp.Format(_T("%.1f"), m_fHoleEdgeNickWdDeltaGradViolation);
	m_strOriginData[6][10] = strTemp;

	strTemp.Format(_T("%.1f"), m_fHoleEdgeExcsWdDeltaGradViolation);
	m_strOriginData[6][11] = strTemp;

	strTemp.Format(_T("%d"), m_nViaEdgeNickGray);
	m_strOriginData[6][12] = strTemp;

	strTemp.Format(_T("%d"), m_nViaEdgeNeibGrayDiff);	//120109 hjc add
	m_strOriginData[6][13] = strTemp;

	strTemp.Format(_T("%.1f"), m_fViaEdgeNickWdDeltaGradViolation);
	m_strOriginData[6][14] = strTemp;

	strTemp.Format(_T("%.1f"), m_fViaEdgeExcsWdDeltaGradViolation);
	m_strOriginData[6][15] = strTemp;
	*/
}

void CDlgSpec::LoadOriginDataTab7()
{
/*	CString strTemp;

	strTemp.Format(_T("%d"), pGlobalDoc->m_nPtSrchRngExt);
	m_strOriginData[7][1] = strTemp;

	m_strOriginData[7][2] = m_cboPTMOD_SIZE;

	strTemp.Format(_T("%d"), m_nAlignTolerance);
	m_strOriginData[7][3] = strTemp;

	m_strOriginData[7][4] = m_strThetaAlign;

	strTemp.Format(_T("%.1f"), m_fDefMaskSize);
	m_strOriginData[7][5] = strTemp;

	strTemp.Format(_T("%.1f"), m_fNearDefLen);
	m_strOriginData[7][6] = strTemp;

	if (pGlobalDoc->m_bUseMultiVaccumControl)	//130311 hjc add
		m_strOriginData[7][7] = m_strSelectVaccum;	//20100210 hjc add
	else
		m_strOriginData[7][7] = "Both";

	if (AoiParam()->m_bUseAutoPinPosAdjust || g_bUsePinPosEstimate)
	{
		strTemp.Format(_T("%.1f"), m_dPanelSizeX);
		m_strOriginData[7][8] = strTemp;

		strTemp.Format(_T("%.1f"), m_dPanelSizeY);
		m_strOriginData[7][9] = strTemp;

#ifdef IRIS_AXIS
		m_strOriginData[7][10].Format(_T("%.3f"), pGlobalDoc->m_IRISAxisControl.m_dIRISPosName[m_nIRISPosID]);
#endif

	}
	else
	{
#ifdef IRIS_AXIS
		m_strOriginData[7][8].Format(_T("%.3f"), pGlobalDoc->m_IRISAxisControl.m_dIRISPosName[m_nIRISPosID]);
#endif
	}*/
}

CString CDlgSpec::GetSpecName(int tab, int row)
{

/*
	CString strTemp, strVal;
	int idx;

	m_Spread.SetCol(0);

	switch (tab)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		strTemp.Format(_T("SPEC_TAB_%d"), tab);
		strVal.Format(_T("ROW_%d"), row);

		return (pGlobalView->GetMultiLangStringW(pGlobalDoc->m_nSelectedLanguage, strTemp, strVal));
		break;
	case 7:

		strTemp.Format(_T("SPEC_TAB_%d"), tab);
		strVal.Format(_T("ROW_%d"), row + 2);

		return (pGlobalView->GetMultiLangStringW(pGlobalDoc->m_nSelectedLanguage, strTemp, strVal));
		break;
	}
	*/
	return _T("Unknown");
}


void CDlgSpec::RecoverOriginData()
{
/*	m_fNominalLine = (float)_ttof(m_strOriginData[0][1]);
	m_fRealNormLine = (float)_ttof(m_strOriginData[0][2]);
	m_nNickGray = _ttoi(m_strOriginData[0][3]);
	//150410 hjc add
	m_nOpenGray = _ttoi(m_strOriginData[0][4]);
	m_nHalfSideNickDiffBrightGray = _ttoi(m_strOriginData[0][5]);	//150529 hjc mod
	m_nHalfSideNickDiffDarkGray = _ttoi(m_strOriginData[0][6]);
	//----------
	m_nLeadOpenGray = _ttoi(m_strOriginData[0][7]);
	m_fMinCheckWidth = (float)_ttof(m_strOriginData[0][8]);
	int idx;

	m_nLineWidthGroupNum = SpecData.nLineWidthGroupNum;


	//20091019 hjc mod
	if (SpecData.nLineWidthGroupNum > 0)
	{
		for (idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
		{

			if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
			{
				m_strNick[idx] = CString(SpecData.szNickSize[idx]);
				m_strProtrusion[idx] = CString(SpecData.szProtrusionSize[idx]);
			}
			else
			{
				m_nNickPercent[idx] = SpecData.nNickPercent[idx];
				m_nProtrusionPercent[idx] = SpecData.nProtrusionPercent[idx];
			}

			m_nNickNGFilterPercent[idx] = SpecData.nNickNGFilterPercent[idx];
			m_nExcsNGFilterPercent[idx] = SpecData.nExcsNGFilterPercent[idx];

			//20090228 hjc
			m_fLineWdDeltaGradViolation[idx] = SpecData.fLineWdDeltaGradViolation[idx];
			m_fExcsWdDeltaGradViolation[idx] = SpecData.fExcsWdDeltaGradViolation[idx];

			m_fLineWidthGroupLower[idx] = SpecData.fLineWidthGroupLower[idx]; //170524 lgh
			m_fLineWidthGroup[idx] = SpecData.fLineWidthGroup[idx];
			m_fNarrowTraceViolation[idx] = SpecData.fNarrowTraceViolation[idx];
			m_fWideTraceViolation[idx] = SpecData.fWideTraceViolation[idx];
		}

		int nLastID = SpecData.nLineWidthGroupNum;

		for (idx = SpecData.nLineWidthGroupNum + 1; idx < 15; idx++)
		{
			if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
			{
				m_strNick[idx] = CString(SpecData.szNickSize[nLastID]);
				m_strProtrusion[idx] = CString(SpecData.szProtrusionSize[nLastID]);
			}
			else
			{
				m_nNickPercent[idx] = SpecData.nNickPercent[nLastID];
				m_nProtrusionPercent[idx] = SpecData.nProtrusionPercent[nLastID];
			}

			m_nNickNGFilterPercent[idx] = SpecData.nNickNGFilterPercent[nLastID];
			m_nExcsNGFilterPercent[idx] = SpecData.nExcsNGFilterPercent[nLastID];

			m_fLineWdDeltaGradViolation[idx] = SpecData.fLineWdDeltaGradViolation[nLastID];
			m_fExcsWdDeltaGradViolation[idx] = SpecData.fExcsWdDeltaGradViolation[nLastID];

			m_fNarrowTraceViolation[idx] = SpecData.fNarrowTraceViolation[nLastID];
			m_fWideTraceViolation[idx] = SpecData.fWideTraceViolation[nLastID];
		}


	}
	else
	{
		m_fLineWidthGroupLower[0] = SpecData.fLineWidthGroupLower[0]; //170524 lgh
		m_fLineWidthGroup[0] = SpecData.fLineWidthGroup[0];
		m_fNarrowTraceViolation[0] = (float)_ttof(m_strOriginData[0][15]);
		m_fWideTraceViolation[0] = (float)_ttof(m_strOriginData[0][16]);

		int nLastID = 0;

		for (idx = 1; idx < 15; idx++)
		{
			if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
			{
				m_strNick[idx] = CString(SpecData.szNickSize[nLastID]);
				m_strProtrusion[idx] = CString(SpecData.szProtrusionSize[nLastID]);
			}
			else
			{
				m_nNickPercent[idx] = SpecData.nNickPercent[nLastID];
				m_nProtrusionPercent[idx] = SpecData.nProtrusionPercent[nLastID];
			}

			m_nNickNGFilterPercent[idx] = SpecData.nNickNGFilterPercent[nLastID];
			m_nExcsNGFilterPercent[idx] = SpecData.nExcsNGFilterPercent[nLastID];

			//20090228 hjc
			m_fLineWdDeltaGradViolation[idx] = SpecData.fLineWdDeltaGradViolation[nLastID];
			m_fExcsWdDeltaGradViolation[idx] = SpecData.fExcsWdDeltaGradViolation[nLastID];
		}
	}

	m_nFineLineWidthGroupNum = SpecData.nLineWidthGroupNum;

	m_fNominalLine = (float)_ttof(m_strOriginData[1][1]);
	m_fRealNormLine = (float)_ttof(m_strOriginData[1][2]);
	m_nFineNickGray = _ttoi(m_strOriginData[1][3]);	//170403 hjc mod
													//150410 hjc add
	m_nFineOpenGray = _ttoi(m_strOriginData[1][4]);
	m_nFineHalfSideNickDiffBrightGray = _ttoi(m_strOriginData[1][5]);	//150529 hjc mod
	m_nFineHalfSideNickDiffDarkGray = _ttoi(m_strOriginData[1][6]);
	m_nLeadOpenGray = _ttoi(m_strOriginData[1][7]);
	m_fFineMinCheckWidth = (float)_ttof(m_strOriginData[1][8]);

	if (SpecData.nLineWidthGroupNum > 0)
	{
		for (idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
		{
			if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
			{
				m_strFineNick[idx] = m_strOriginData[1][9];
				m_strFineProtrusion[idx] = m_strOriginData[1][10];
			}
			else
			{
				m_nFineNickPercent[idx] = SpecData.nFineNickPercent[idx];
				m_nFineProtrusionPercent[idx] = SpecData.nFineProtrusionPercent[idx];
			}

			m_nFineNickNGFilterPercent[idx] = SpecData.nFineExcsNGFilterPercent[idx];
			m_nFineExcsNGFilterPercent[idx] = SpecData.nFineExcsNGFilterPercent[idx];
			m_fFineLineWdDeltaGradViolation[idx] = SpecData.fFineLineWdDeltaGradViolation[idx];
			m_fFineExcsWdDeltaGradViolation[idx] = SpecData.fFineExcsWdDeltaGradViolation[idx];
		}
	}
	else
	{
		if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
		{
			m_strFineNick[0] = m_strOriginData[1][9];
			m_strFineProtrusion[0] = m_strOriginData[1][10];
		}
		else
		{
			m_nFineNickPercent[0] = _ttoi(m_strOriginData[1][9]);
			m_nFineProtrusionPercent[0] = _ttoi(m_strOriginData[1][10]);
		}

		m_nFineNickNGFilterPercent[0] = _ttoi(m_strOriginData[1][11]);
		m_nFineExcsNGFilterPercent[0] = _ttoi(m_strOriginData[1][12]);
		m_fFineLineWdDeltaGradViolation[0] = (float)_ttof(m_strOriginData[1][13]);	//150529 hjc mod
		m_fFineExcsWdDeltaGradViolation[0] = (float)_ttof(m_strOriginData[1][14]);
	}

	//20091019 hjc mod
	if (SpecData.nLineWidthGroupNum > 0)
	{
		for (idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
		{
			m_fFineLineWidthGroup[idx] = SpecData.fFineLineWidthGroup[idx];
			m_fFineNarrowTraceViolation[idx] = SpecData.fFineNarrowTraceViolation[idx];
			m_fFineWideTraceViolation[idx] = SpecData.fFineWideTraceViolation[idx];
		}
	}
	else
	{
		m_fFineLineWidthGroup[0] = SpecData.fFineLineWidthGroup[0];
		m_fFineNarrowTraceViolation[0] = (float)_ttof(m_strOriginData[1][15]);
		m_fFineWideTraceViolation[0] = (float)_ttof(m_strOriginData[1][16]);
	}

	m_MinSpGray = _ttoi(m_strOriginData[2][1]);
	//20090412 hjc
	m_nNeibSpGrayDiff = _ttoi(m_strOriginData[2][2]);
	m_nUSDarkGrayMinus = _ttoi(m_strOriginData[2][3]);
	//-----------------
	m_fMinSpWidth = (float)_ttof(m_strOriginData[2][4]);

	if (pGlobalDoc->m_bUseCombo)	//150611 hjc add
	{
		//170217 lgh
		int nPos = m_strMinSP.Find(_T(" "), 0);
		if (nPos >= 0)
			m_strMinSP = m_strMinSP.Left(nPos);

		m_strMinSP = m_strOriginData[2][5];
	}
	else
		m_nMinSPPercent = _ttoi(m_strOriginData[2][5]);

	m_nSpaceNGFilterPercent = _ttoi(m_strOriginData[2][6]);
	//20090228 modify hjc
	m_fSpWdDeltaGradViolation = (float)_ttof(m_strOriginData[2][7]);   //20090405 hjc
	m_fSpWdDeltaOuterGradViolation = (float)_ttof(m_strOriginData[2][8]);
	m_fFineMinSpWidth = (float)_ttof(m_strOriginData[2][9]);		//121226 hjc add
																	//--------------

																	//20100322 hjc add
	m_nPinHoleGray = _ttoi(m_strOriginData[3][1]);
	m_strLP_Prec = m_strOriginData[3][2];	//
	m_fPinHoleMin = (float)_ttof(m_strOriginData[3][3]);
	m_nIsLandGray = _ttoi(m_strOriginData[3][4]);
	m_strSP_Prec = m_strOriginData[3][5];	//170112 hjc mod	
	m_fIsLandMin = (float)_ttof(m_strOriginData[3][6]);
	m_nIsLandExtGray = _ttoi(m_strOriginData[3][7]);
	m_strSPExt_Prec = m_strOriginData[3][8];	//170112 hjc mod
	m_fIsLandExtMin = (float)_ttof(m_strOriginData[3][9]);
	//jun 20120903 for LG_CCL-Inspector
	m_nCCLGray = _ttoi(m_strOriginData[3][10]);
	m_fCCLCircularity = (float)_ttof(m_strOriginData[3][11]);
	m_fCCLDefSize = (float)_ttof(m_strOriginData[3][12]);

	//2022 01 10 lgh add
	m_nCharInspectionGray = _ttoi(m_strOriginData[3][13]);
	m_dCharRegionUpperPercent = (float)_ttof(m_strOriginData[3][14]);
	m_dCharRegionLowerPercent = (float)_ttof(m_strOriginData[3][15]);

	SpecData.nVDrillDiffBrightGray = _ttoi(m_strOriginData[4][1]);
	SpecData.nVDrillDiffDarkGray = _ttoi(m_strOriginData[4][2]);		//150823 hjc add
	SpecData.fVDPadPrecName = (float)_ttof(m_strOriginData[4][3]);
	m_fVDLocationTolerance = (float)_ttof(m_strOriginData[4][4]);
	m_fVDPadMin = (float)_ttof(m_strOriginData[4][5]);
	m_nPADVoidGray = _ttoi(m_strOriginData[4][6]);
	m_strPadBallPrec = m_strOriginData[4][7];
	m_fPADVoidMin = (float)_ttof(m_strOriginData[4][8]);
	m_strPadTip_Prec = m_strOriginData[4][9];	//170112 hjc mod	
	m_fPADTipMin = (float)_ttof(m_strOriginData[4][10]);
	m_nHoleLandVoidGray = _ttoi(m_strOriginData[4][11]);	//20100322 hjc add
	m_strARLand_Prec = m_strOriginData[4][12];		//170112 hjc mod
	m_fARLandMin = (float)_ttof(m_strOriginData[4][13]);
	SpecData.fHoleFillExt = (float)_ttof(m_strOriginData[4][14]);
	m_nCO2LandVoidGraySpec = _ttoi(m_strOriginData[4][15]);	//20100322 hjc add
	m_strCO2Land_Prec = m_strOriginData[4][16];		//170112 hjc mod
	SpecData.fCO2LandMin = (float)_ttof(m_strOriginData[4][17]);
	StringToChar(m_strOriginData[4][18], SpecData.szCO2LandAlignMode);
	//	strcpy(SpecData.szCO2LandAlignMode, m_strOriginData[4][18]);
	SpecData.fCO2HoleFillExt = (float)_ttof(m_strOriginData[4][19]);	//20100323 hjc add
	m_nFinePADVoidGraySpec = _ttoi(m_strOriginData[4][20]);
	m_strFPad_Prec = m_strOriginData[4][21];	//170112 hjc mod	
	m_fFineVDPadMin = (float)_ttof(m_strOriginData[4][22]);	//090324-ndy

	m_fHoleTolerance = (float)_ttof(m_strOriginData[5][1]);
	m_fHoleDiaUpper = _ttof(m_strOriginData[5][2]);
	m_fHoleDiaLower = _ttof(m_strOriginData[5][3]);
	m_nHoleOpenGray = _ttoi(m_strOriginData[5][4]);
	m_nHoleMissingGray = _ttoi(m_strOriginData[5][5]);
	m_nHoleInnerGray = _ttoi(m_strOriginData[5][6]);
	m_strHolePrec = m_strOriginData[5][7];
	m_nHoleDefSize = _ttoi(m_strOriginData[5][8]);
	StringToChar(m_strOriginData[5][9], SpecData.szVHMode);
	//	strcpy(SpecData.szVHMode, m_strOriginData[5][9]);
	m_nCO2MissingGray = _ttoi(m_strOriginData[5][10]);
	m_nCO2HoleNum = _ttoi(m_strOriginData[5][11]);
	m_nCO2OpenGray = _ttoi(m_strOriginData[5][12]);
	m_nCO2MisAgnGray = _ttoi(m_strOriginData[5][13]);
	m_nCO2MisAgnDefPercent = _ttoi(m_strOriginData[5][14]);
	SpecData.nVHEdgeThrDiffGray = _ttoi(m_strOriginData[5][15]);
	SpecData.nVHBreakOutGray = _ttoi(m_strOriginData[5][16]);
	SpecData.nVHDissmearGray = _ttoi(m_strOriginData[5][17]);
	SpecData.nVHContiBreakOutNum = _ttoi(m_strOriginData[5][18]);

	m_nPadEdgeNickGray = _ttoi(m_strOriginData[6][1]);
	m_nPadEdgeNeibGrayDiff = _ttoi(m_strOriginData[6][2]);	//120105 hjc add
	m_nPadEdgeBADiffDarkGray = _ttoi(m_strOriginData[6][3]);
	m_fPadEdgeNickWdDeltaGradViolation = (float)_ttof(m_strOriginData[6][4]);
	m_fPadEdgeExcsWdDeltaGradViolation = (float)_ttof(m_strOriginData[6][5]);
	m_nPadVDEdgeGray = _ttoi(m_strOriginData[6][6]);
	m_fPadVDEdgeWdDeltaGradViolation = (float)_ttof(m_strOriginData[6][7]);
	m_nHoleEdgeNickGray = _ttoi(m_strOriginData[6][8]);
	m_nHoleEdgeNeibGrayDiff = _ttoi(m_strOriginData[6][9]);	//120109 hjc add
	m_fHoleEdgeNickWdDeltaGradViolation = (float)_ttof(m_strOriginData[6][10]);
	m_fHoleEdgeExcsWdDeltaGradViolation = (float)_ttof(m_strOriginData[6][11]);
	m_nViaEdgeNickGray = _ttoi(m_strOriginData[6][12]);
	m_nViaEdgeNeibGrayDiff = _ttoi(m_strOriginData[6][13]);	//120109 hjc add
	m_fViaEdgeNickWdDeltaGradViolation = (float)_ttof(m_strOriginData[6][14]);
	m_fViaEdgeExcsWdDeltaGradViolation = (float)_ttof(m_strOriginData[6][15]);

	if (pGlobalDoc->m_bUseMultiVaccumControl)	//130311 hjc add
		m_strSelectVaccum = m_strOriginData[7][7];	//20100210 hjc add
	else
		m_strSelectVaccum = "Both";


#ifdef IRIS_AXIS
	int nCheckPosID = 8;

	if (AoiParam()->m_bUseAutoPinPosAdjust || g_bUsePinPosEstimate)
		nCheckPosID = 10;

	for (int i = 0; i < 12; i++)
	{
		double dDiff = fabs(_ttof(m_strOriginData[7][8]) - pGlobalDoc->m_IRISAxisControl.m_dIRISPosName[i]);

		if (dDiff < 0.01)
		{
			m_nIRISPosID = i;
			break;
		}
	}
#endif
*/
}

int CDlgSpec::Level2Number(CString strLvl)
{
/*	if (strLvl == "Highest")
		return -1;

	if (strLvl == "VeryHigh")
		return -2;

	if (strLvl == "High")
		return -3;

	if (strLvl == "Normal")
		return -4;

	if (strLvl == "Low")
		return -5;

	if (strLvl == "VeryLow")
		return -6;

	if (strLvl == "Lowest")
		return -7;
*/
	return 0;
}


void CDlgSpec::DecisionPixelAdjust(CString strName, int nLevelVal, int PrecisionStepSize, int* nHighest, int* nVeryHigh, int* nHigh, int* nNormal, int* nLow, int* nVeryLow, int* nLowest)
{
/*	if (strName == "Highest")
	{
		*nHighest = nLevelVal * PrecisionStepSize;
		*nVeryHigh = nLevelVal - 1 * PrecisionStepSize;
		*nHigh = nLevelVal - 2 * PrecisionStepSize;
		*nNormal = nLevelVal - 3 * PrecisionStepSize;
		*nLow = nLevelVal - 4 * PrecisionStepSize;
		*nVeryLow = nLevelVal - 5 * PrecisionStepSize;
		*nLowest = nLevelVal - 6 * PrecisionStepSize;
	}
	if (strName == "VeryHigh")
	{
		*nHighest = nLevelVal + 1 * PrecisionStepSize;
		*nVeryHigh = nLevelVal * PrecisionStepSize;
		*nHigh = nLevelVal - 1 * PrecisionStepSize;
		*nNormal = nLevelVal - 2 * PrecisionStepSize;
		*nLow = nLevelVal - 3 * PrecisionStepSize;
		*nVeryLow = nLevelVal - 4 * PrecisionStepSize;
		*nLowest = nLevelVal - 5 * PrecisionStepSize;
	}
	if (strName == "High")
	{
		*nHighest = nLevelVal + 2 * PrecisionStepSize;
		*nVeryHigh = nLevelVal + 1 * PrecisionStepSize;
		*nHigh = nLevelVal * PrecisionStepSize;
		*nNormal = nLevelVal - 1 * PrecisionStepSize;
		*nLow = nLevelVal - 2 * PrecisionStepSize;
		*nVeryLow = nLevelVal - 3 * PrecisionStepSize;
		*nLowest = nLevelVal - 4 * PrecisionStepSize;
	}
	if (strName == "Normal")
	{
		*nHighest = nLevelVal + 3 * PrecisionStepSize;
		*nVeryHigh = nLevelVal + 2 * PrecisionStepSize;
		*nHigh = nLevelVal + 1 * PrecisionStepSize;
		*nNormal = nLevelVal * PrecisionStepSize;
		*nLow = nLevelVal - 1 * PrecisionStepSize;
		*nVeryLow = nLevelVal - 2 * PrecisionStepSize;
		*nLowest = nLevelVal - 3 * PrecisionStepSize;
	}
	if (strName == "Low")
	{
		*nHighest = nLevelVal + 4 * PrecisionStepSize;
		*nVeryHigh = nLevelVal + 3 * PrecisionStepSize;
		*nHigh = nLevelVal + 2 * PrecisionStepSize;
		*nNormal = nLevelVal + 1 * PrecisionStepSize;
		*nLow = nLevelVal * PrecisionStepSize;
		*nVeryLow = nLevelVal - 1 * PrecisionStepSize;
		*nLowest = nLevelVal - 2 * PrecisionStepSize;
	}
	if (strName == "VeryLow")
	{
		*nHighest = nLevelVal + 5 * PrecisionStepSize;
		*nVeryHigh = nLevelVal + 4 * PrecisionStepSize;
		*nHigh = nLevelVal + 3 * PrecisionStepSize;
		*nNormal = nLevelVal + 2 * PrecisionStepSize;
		*nLow = nLevelVal + 1 * PrecisionStepSize;
		*nVeryLow = nLevelVal * PrecisionStepSize;
		*nLowest = nLevelVal - 1 * PrecisionStepSize;
	}
	if (strName == "Lowest")
	{
		*nHighest = nLevelVal + 6 * PrecisionStepSize;
		*nVeryHigh = nLevelVal + 5 * PrecisionStepSize;
		*nHigh = nLevelVal + 4 * PrecisionStepSize;
		*nNormal = nLevelVal + 3 * PrecisionStepSize;
		*nLow = nLevelVal + 2 * PrecisionStepSize;
		*nVeryLow = nLevelVal + 1 * PrecisionStepSize;
		*nLowest = nLevelVal * PrecisionStepSize;
	}*/
}

BOOL CDlgSpec::GetDefaultSpecData()
{
/*	int i, t, nCount;

	CString strPath, strFileName;

	//20120629-ndy
	if (pGlobalDoc->m_bUseLocalSpecPreset)
		strPath.Format(_T("%sSpecPreset\\%d\\*.MSP"), pGlobalDoc->m_strLocSpecDir, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)));
	else
	{
		if (!pGlobalDoc->m_bUseMultiPreset)	//130128 hjc add
			strPath.Format(_T("%sSpecPreset\\%d\\*.MSP"), pGlobalDoc->m_strIniSpecDir, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)));
		else
			strPath.Format(_T("%sSpecPreset%02d\\%d\\*.MSP"), pGlobalDoc->m_strIniSpecDir, pGlobalDoc->m_nMultiPresetNumber, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)));
	}

	// 100707 jsy
	m_DefaultSpecCombo.ResetContent();

	CFileFind filefind;
	BOOL bContinue;
	if (!(bContinue = filefind.FindFile(strPath)))
		return FALSE;

	while (bContinue)
	{
		bContinue = filefind.FindNextFile();
		strFileName = filefind.GetFileName();
		if (strFileName != "." && strFileName != "..")
			m_DefaultSpecCombo.AddString(strFileName);
	}
	filefind.Close();

	 //ini ¡¶∞≈ 
	CString strBuf, strBuf2;
	nCount = m_DefaultSpecCombo.GetCount();
	for (i = t = 0; i < nCount; i++)
	{
		m_DefaultSpecCombo.GetLBText(i, strBuf);
		//		Layer¿Ã∏ßø°º≠ ".ini"∏¶ ¡¶∞≈ 
		strBuf2 = strBuf.Left(strBuf.GetLength() - 4);
		m_DefaultSpecCombo.InsertString(t, strBuf2);
		m_DefaultSpecCombo.DeleteString(t + 1);
		t++;
	}

	nCount = m_DefaultSpecCombo.FindStringExact(-1, _T("Default"));
	if (nCount != LB_ERR)
	{
		m_DefaultSpecCombo.SetCurSel(nCount);
		return TRUE;
	}
	else*/
		return FALSE;
}

void CDlgSpec::OnButtonSaveDefaultLocalSpec()
{
/*	m_Spread.AutoAttach();
	m_Spread.SetEditMode(FALSE);
	m_Spread.SetFocus();
	m_Spread.SetActiveCell(0, 0);
	m_Spread.SetRetainSelBlock(FALSE);
	m_Spread.ClearSelection();
	CFileOperation fileOp(GetWindowVersion());
	// TODO: Add your control notification handler code here
	CString strPresetName;
	CString strPath, strTitle, strIndex, strData;
	CString strTitleMsg, strMsg;

#if CUSTOMER_COMPANY == LG

	if (g_bLGPresetLogin == 0)
	{
		CDlgPassWord dlgPassword;
		dlgPassword.m_bChkMagUseShow = FALSE;
		dlgPassword.DoModal();

		if (!dlgPassword.m_bPass)
			return;
	}
	else
	{
		if (!pMainFrame->CheckLogin())
		{
			if (pGlobalDoc->m_nSelectedLanguage == KOREA)
				strMsg.Format(_T("∑Œ±◊¿Œø° Ω«∆–«œø¥Ω¿¥œ¥Ÿ. ªÁøÎ¿⁄ ∑Œ±◊¿Œ »ƒ ¥ŸΩ√ Ω√µµ«œΩ Ω√ø¿."));
			else
				strMsg.Format(_T("Access denied. before delete the lot, you must loggined."));

			SaveLog(strMsg);
			return;
		}

		if (pGlobalView->m_nUserID == OPERATOR)
		{
			if (pGlobalDoc->m_nSelectedLanguage == KOREA)
			{
				AfxMessageBox(_T("±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄∏∏ / ø£¡ˆ¥œæÓ∏∏ ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."), MB_ICONSTOP);
				SaveLog(strMsg);
				SaveLog(_T("±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄/ø£¡ˆ¥œæÓ∏∏ Ω∫∆Â ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."));
			}
			else
			{
				AfxMessageBox(_T("Access denied. can't save preset spec"), MB_ICONSTOP);
				SaveLog(strMsg);
				SaveLog(_T("Access denied. can't save preset spec"));
			}
			return;
		}
		else if (pGlobalView->m_nUserID == ENGINEER)
		{
			if (pGlobalDoc->m_nOperatorID == 11)
			{
				if (pGlobalDoc->m_nSelectedLanguage == KOREA)
				{
					AfxMessageBox(_T("±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄∏∏ / ø£¡ˆ¥œæÓ2~3∏∏ ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."), MB_ICONSTOP);
					SaveLog(strMsg);
					SaveLog(_T("±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄/ø£¡ˆ¥œæÓ2~3∏∏ Ω∫∆Â ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."));
				}
				else
				{
					AfxMessageBox(_T("Access denied. can't save preset spec"), MB_ICONSTOP);
					SaveLog(strMsg);
					SaveLog(_T("Access denied. can't save preset spec"));
				}
				return;
			}
		}
	}

#else
	if (AoiParam()->m_bSecurityEnhanceMode)
	{
		if (pGlobalView->m_nUserID != ADMINISTRATOR && pGlobalView->m_nUserID != ENGINEER)
		{
			if (pGlobalDoc->m_nSelectedLanguage == KOREA)
			{
				AfxMessageBox(_T("±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄∏∏ / ø£¡ˆ¥œæÓ∏∏ ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."), MB_ICONSTOP);
				SaveLog(strMsg);
				SaveLog(_T("±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄/ø£¡ˆ¥œæÓ∏∏ Ω∫∆Â ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."));
			}
			else
			{
				AfxMessageBox(_T("Access denied. can't save preset spec"), MB_ICONSTOP);
				SaveLog(strMsg);
				SaveLog(_T("Access denied. can't save preset spec"));
			}
			return;
		}
	}
	else
	{
#if CUSTOMER_COMPANY == LG
		if (!pMainFrame->CheckLogin())
		{
			if (pGlobalDoc->m_nSelectedLanguage == KOREA)
				strMsg.Format(_T("∑Œ±◊¿Œø° Ω«∆–«œø¥Ω¿¥œ¥Ÿ. ªÁøÎ¿⁄ ∑Œ±◊¿Œ »ƒ ¥ŸΩ√ Ω√µµ«œΩ Ω√ø¿."));
			else
				strMsg.Format(_T("Access denied. before delete the lot, you must loggined."));

			SaveLog(strMsg);
			return;
		}

		if (pGlobalView->m_nUserID == OPERATOR)
		{
			if (pGlobalDoc->m_nSelectedLanguage == KOREA)
			{
				AfxMessageBox(_T("±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄∏∏ / ø£¡ˆ¥œæÓ∏∏ ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."), MB_ICONSTOP);
				SaveLog(strMsg);
				SaveLog(_T("±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄/ø£¡ˆ¥œæÓ∏∏ Ω∫∆Â ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."));
			}
			else
			{
				AfxMessageBox(_T("Access denied. can't save preset spec"), MB_ICONSTOP);
				SaveLog(strMsg);
				SaveLog(_T("Access denied. can't save preset spec"));
			}
			return;
		}
		else if (pGlobalView->m_nUserID == ENGINEER)
		{
			if (pGlobalDoc->m_nOperatorID == 11)
			{
				if (pGlobalDoc->m_nSelectedLanguage == KOREA)
				{
					AfxMessageBox(_T("±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄∏∏ / ø£¡ˆ¥œæÓ2~3∏∏ ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."), MB_ICONSTOP);
					SaveLog(strMsg);
					SaveLog(_T("±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄/ø£¡ˆ¥œæÓ2~3∏∏ Ω∫∆Â ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."));
				}
				else
				{
					AfxMessageBox(_T("Access denied. can't save preset spec"), MB_ICONSTOP);
					SaveLog(strMsg);
					SaveLog(_T("Access denied. can't save preset spec"));
				}
				return;
			}
		}

#elif CUSTOMER_COMPANY == SIMMTECH || CUSTOMER_COMPANY ==DAEDUCK_APERIO
		if (pGlobalView->m_nUserID != ADMINISTRATOR)
		{

			if (!pMainFrame->CheckLogin())
			{
				if (pGlobalDoc->m_nSelectedLanguage == KOREA)
					strMsg.Format(_T("∑Œ±◊¿Œø° Ω«∆–«œø¥Ω¿¥œ¥Ÿ. ªÁøÎ¿⁄ ∑Œ±◊¿Œ »ƒ ¥ŸΩ√ Ω√µµ«œΩ Ω√ø¿."));
				else
					strMsg.Format(_T("Access denied. before delete the lot, you must loggined."));

				SaveLog(strMsg);
				return;
			}

			if (pGlobalView->m_nUserID == OPERATOR)
			{
				if (pGlobalDoc->m_nSelectedLanguage == KOREA)
				{
					AfxMessageBox(_T("±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄∏∏ / ø£¡ˆ¥œæÓ∏∏ ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."), MB_ICONSTOP);
					SaveLog(strMsg);
					SaveLog(_T("±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄/ø£¡ˆ¥œæÓ∏∏ Ω∫∆Â ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."));
				}
				else
				{
					AfxMessageBox(_T("Access denied. can't save preset spec"), MB_ICONSTOP);
					SaveLog(strMsg);
					SaveLog(_T("Access denied. can't save preset spec"));
				}
			}

			return;
		}
#else
		CDlgPassWord dlgPassword;
		dlgPassword.m_bChkMagUseShow = FALSE;
		dlgPassword.DoModal();

		if (!dlgPassword.m_bPass)
			return;
#endif
	}
#endif

	pGlobalDoc->SaveAccessLog(_T("Spec Preset Save"));

	CDlgPresetName pDlg;
	pGlobalDoc->m_nPresetNameType = 2;
	if (pDlg.DoModal() == IDOK)
	{
		strPresetName = pDlg.m_strPresetName;
	}
	else
		return;

	if (m_bSpecDataChanged)
	{
		if (MessageBox(_T("Data was changed.\nDo you want to save ?"), NULL, MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			pGlobalView->m_pDlgSpecSub->SaveSpec();
			m_bClientSpecDataUpdate = TRUE;
		}
		else
		{
			InitVariablesWithLoadSpecFromFile();

			// Remark by syd
			// Function Order: RecoverOriginData() - LoadOriginDataTab(0) - ......
			RecoverOriginData();
			//20090228 hjc
			LoadOriginDataTab(0);
			LoadOriginDataTab(1);
			LoadOriginDataTab(2);
			LoadOriginDataTab(3);
			LoadOriginDataTab(4);
			LoadOriginDataTab(5);
			LoadOriginDataTab(6);
			LoadOriginDataTab(7);	//20100322 hjc add
									//--------------
		}

		InitSpreadInfoVariables();
	}

	if (m_bClientSpecDataUpdate && pGlobalView->CheckAllClientsReady())
	{
		// Send Spec to Client
		strTitleMsg.Format(_T("%s"), pGlobalView->GetLanguageString("SYSTEM", "NOTIFY"));
		strMsg.Format(_T("%s"), pGlobalView->GetLanguageString("NETWORK", "SEND_SPEC_DATA"));
		//		pGlobalView->ResultDisplayStaticEX(strMsg,RGB_BLACK,RGB_LTGREEN);
		pGlobalView->DispMessage(strTitleMsg, strMsg, RGB_LTGREEN);

		if (pGlobalView->SendSpecDataToAllClient() != SUCCESS || pGlobalView->SendSystemParamToAllClient() != SUCCESS)
		{
#if CUSTOMER_COMPANY == UMTC || CUSTOMER_COMPANY == ZDT || CUSTOMER_COMPANY == SAMSUNG_VIETNAM  //NTH Add for GEM
			if (pGlobalDoc->m_bUseGemComm)
			{
				if (!pGlobalDoc->m_bCheckAlarm)
				{
					pGlobalDoc->m_bCheckAlarm = TRUE;
					pMainFrame->SetEESAlarm(ALARM_NETWORK_SEND_SPEC, EES_ACTIVATE_ALARM);
				}
			}
			else
				pMainFrame->SetEESAlarm(ALARM_NETWORK_SEND_SPEC, EES_ACTIVATE_ALARM);
#else
			pMainFrame->SetEESAlarm(ALARM_NETWORK_SEND_SPEC, EES_ACTIVATE_ALARM);
#endif
			strTitleMsg.Format(_T("%s"), pGlobalView->GetLanguageString("SYSTEM", "WARNING"));
			strMsg.Format(_T("[MSG1] %s"), pGlobalView->GetLanguageString("NETWORK", "DOWNLOAD_ERROR_SPEC_DATA"));
			pGlobalView->ResultDisplayStaticEX(strMsg, RGB_BLACK, RGB_YELLOW);
			CString strErrorMsg = pGlobalView->GetLanguageString("ERROR_GUIDE", "SPEC_DOWNLOAD_ERROR");
#if CUSTOMER_COMPANY == SHINKO_DENKKI
			pIO->BuzzerOnOff(TRUE);
			pGlobalView->TowerLampControl(TOWER_LAMP_RED, 1);
#endif
			pMainFrame->DispMessageModal(strTitleMsg, strMsg, RGB_YELLOW, 300000, TRUE, strErrorMsg);
#if CUSTOMER_COMPANY == SHINKO_DENKKI
			pIO->BuzzerOnOff(0);
			pGlobalView->TowerLampControl(TOWER_LAMP_GREEN, 1);
#endif
			pGlobalDoc->DispRunStopCondition();
#if CUSTOMER_COMPANY == UMTC || CUSTOMER_COMPANY == ZDT || CUSTOMER_COMPANY == SAMSUNG_VIETNAM  //NTH Add for GEM
			if (pGlobalDoc->m_bUseGemComm)
			{
				if (pGlobalDoc->m_bCheckAlarm)
				{
					pGlobalDoc->m_bCheckAlarm = FALSE;
					pMainFrame->SetEESAlarm(ALARM_NETWORK_SEND_SPEC, EES_DEACTIVATE_ALARM);
				}
			}
			else
				pMainFrame->SetEESAlarm(ALARM_NETWORK_SEND_SPEC, EES_DEACTIVATE_ALARM);
#else
			pMainFrame->SetEESAlarm(ALARM_NETWORK_SEND_SPEC, EES_DEACTIVATE_ALARM);
#endif
		}
		pGlobalView->ClearDispMessage();
	}

	m_bClientSpecDataUpdate = FALSE;

	//20120629-ndy
	if (pGlobalDoc->m_bUseLocalSpecPreset)
	{
		strPath.Format(_T("%sSpecPreset"), pGlobalDoc->m_strLocSpecDir);
		fileOp.DoCreateFolder(strPath, NULL);
		strPath.Format(_T("%sSpecPreset\\%d"), pGlobalDoc->m_strLocSpecDir, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)));
		fileOp.DoCreateFolder(strPath, NULL);

		strPath.Format(_T("%sSpecPreset\\%d\\%s.MSP"), pGlobalDoc->m_strLocSpecDir, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), strPresetName);
	}
	else
	{
		if (!pGlobalDoc->m_bUseMultiPreset)	//130128 hjc add
		{
			strPath.Format(_T("%sSpecPreset"), pGlobalDoc->m_strIniSpecDir);
			fileOp.DoCreateFolder(strPath, NULL);
			strPath.Format(_T("%sSpecPreset\\%d"), pGlobalDoc->m_strIniSpecDir, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)));
			fileOp.DoCreateFolder(strPath, NULL);

			strPath.Format(_T("%sSpecPreset\\%d\\%s.MSP"), pGlobalDoc->m_strIniSpecDir, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), strPresetName);
		}
		else
		{
			strPath.Format(_T("%sSpecPreset%02d"), pGlobalDoc->m_strIniSpecDir, pGlobalDoc->m_nMultiPresetNumber);
			fileOp.DoCreateFolder(strPath, NULL);
			strPath.Format(_T("%sSpecPreset%02d\\%d"), pGlobalDoc->m_strIniSpecDir, pGlobalDoc->m_nMultiPresetNumber, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)));
			fileOp.DoCreateFolder(strPath, NULL);

			strPath.Format(_T("%sSpecPreset%02d\\%d\\%s.MSP"), pGlobalDoc->m_strIniSpecDir, pGlobalDoc->m_nMultiPresetNumber, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), strPresetName);
		}
	}



	//20230621 lgh add for sem fc
	CString strSpecPresetBackup;

	char chHost[HOSTNAME_SIZE] = { 0 };	//2018.04.24 hyk for Daeduck ADC
	gethostname(chHost, sizeof(chHost));
	CString strHostName = CharToString(chHost);

	COleDateTime dt = COleDateTime::GetCurrentTime();
	//20120629-ndy
	if (pGlobalDoc->m_bUseLocalSpecPreset)
	{
		strSpecPresetBackup.Format(_T("%sSpecPreset\\%d\\SpecLog"),
			pGlobalDoc->m_strLocSpecDir,
			(int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)),
			strPresetName);
		::CreateDirectory(strSpecPresetBackup, 0);

		strSpecPresetBackup.Format(_T("%sSpecPreset\\%d\\SpecLog\\%s"),
			pGlobalDoc->m_strLocSpecDir,
			(int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)),
			strPresetName);
		::CreateDirectory(strSpecPresetBackup, 0);

		strSpecPresetBackup.Format(_T("%sSpecPreset\\%d\\SpecLog\\%s\\%04d%02d%02d_%02d%02d%02d_%s_%s.msp"),
			pGlobalDoc->m_strLocSpecDir,
			(int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)),
			strPresetName,
			dt.GetYear(),
			dt.GetMonth(),
			dt.GetDay(),
			dt.GetHour(),
			dt.GetMinute(),
			dt.GetSecond(),
			pGlobalDoc->m_strUserID,
			strHostName);
	}
	else
	{
		if (!pGlobalDoc->m_bUseMultiPreset)	//130128 hjc add
		{
			strSpecPresetBackup.Format(_T("%sSpecPreset\\%d\\SpecLog"),
				pGlobalDoc->m_strIniSpecDir,
				(int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)),
				strPresetName);
			::CreateDirectory(strSpecPresetBackup, 0);

			strSpecPresetBackup.Format(_T("%sSpecPreset\\%d\\SpecLog\\%s"),
				pGlobalDoc->m_strIniSpecDir,
				(int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)),
				strPresetName);
			::CreateDirectory(strSpecPresetBackup, 0);

			strSpecPresetBackup.Format(_T("%sSpecPreset\\%d\\SpecLog\\%s\\%04d%02d%02d_%02d%02d%02d_%s_%s.msp"),
				pGlobalDoc->m_strIniSpecDir,
				(int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)),
				strPresetName,
				dt.GetYear(),
				dt.GetMonth(),
				dt.GetDay(),
				dt.GetHour(),
				dt.GetMinute(),
				dt.GetSecond(),
				pGlobalDoc->m_strUserID,
				strHostName);
		}
		else
		{
			strSpecPresetBackup.Format(_T("%sSpecPreset%02d\\%d\\SpecLog"),
				pGlobalDoc->m_strIniSpecDir,
				pGlobalDoc->m_nMultiPresetNumber,
				(int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), strPresetName);
			::CreateDirectory(strSpecPresetBackup, 0);

			strSpecPresetBackup.Format(_T("%sSpecPreset%02d\\%d\\SpecLog\\%s"),
				pGlobalDoc->m_strIniSpecDir,
				pGlobalDoc->m_nMultiPresetNumber,
				(int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), strPresetName);
			::CreateDirectory(strSpecPresetBackup, 0);

			strSpecPresetBackup.Format(_T("%sSpecPreset%02d\\%d\\SpecLog\\%s\\%04d%02d%02d_%02d%02d%02d_%s_%s.msp"),
				pGlobalDoc->m_strIniSpecDir,
				pGlobalDoc->m_nMultiPresetNumber,
				(int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)),
				strPresetName,
				dt.GetYear(),
				dt.GetMonth(),
				dt.GetDay(),
				dt.GetHour(),
				dt.GetMinute(),
				dt.GetSecond(),
				pGlobalDoc->m_strUserID, strHostName
			);
		}
	}

	CFileFind finder;

	if (finder.FindFile(strPath))
	{
		CString strLog;

		strLog.Format(_T("User:%s pc:%s try save SpecPreset %s[Res%.3f], Since the preset already exists, it will be overwritten"),
			pGlobalDoc->m_strUserID, strHostName,
			strPresetName,
			SizeData[COMMON_PARAMETER].fPixelSize);
		SaveLog(strLog); // totoal log

		strLog.Format(_T("User:%s pc:%s  Spec Preset[%s] Backup from %s to %s"),
			pGlobalDoc->m_strUserID,
			strHostName, strPresetName,
			strPath, strSpecPresetBackup);
		// totoal log
		CopyFileRepeat(strPath, strSpecPresetBackup);
		SaveLog(strLog);
	}



	strTitle.Format(_T("Preset Spec InsVia"));
	//170320 lgh
	strData.Format(_T("%.5f"), SpecData.ViaSpec.fViaHoleTolerance);
	::WritePrivateProfileString(strTitle, _T("VH Shift Tolerance"), strData, strPath);

	strData.Format(_T("%.5f"), SpecData.ViaSpec.fViaHoleDiaUpperPercent);
	::WritePrivateProfileString(strTitle, _T("VH Size Upper Size Limit"), strData, strPath);

	strData.Format(_T("%.5f"), SpecData.ViaSpec.fViaHoleDiaLowerPercent);
	::WritePrivateProfileString(strTitle, _T("VH Size Lower Size Limit"), strData, strPath);

	strData.Format(_T("%d"), SpecData.ViaSpec.nViaInnerEdgeGray);
	::WritePrivateProfileString(strTitle, _T("VH Inner Edge Gray"), strData, strPath);

	strData.Format(_T("%.1f"), SpecData.ViaSpec.fViaInnerEdgeSizePxl);
	::WritePrivateProfileString(strTitle, _T("VH Inner Edge Size Pixel"), strData, strPath);

	strData.Format(_T("%d"), SpecData.ViaSpec.nViaOuterEdgeGray);
	::WritePrivateProfileString(strTitle, _T("VH Outer Edge Gray"), strData, strPath);

	strData.Format(_T("%.1f"), SpecData.ViaSpec.fViaOuterEdgeSizePxl);
	::WritePrivateProfileString(strTitle, _T("VH Outer Edge Size Pixel"), strData, strPath);

	strData.Format(_T("%.1f"), SpecData.ViaSpec.m_fTaperWidth);
	::WritePrivateProfileString(strTitle, _T("VH Taper Width"), strData, strPath);

	strData.Format(_T("%.1f"), SpecData.ViaSpec.m_fInnerDiamterWidthDiff);
	::WritePrivateProfileString(strTitle, _T("VH Inner Diameter"), strData, strPath);

	strData.Format(_T("%.1f"), SpecData.ViaSpec.m_fInnerCompactness);
	::WritePrivateProfileString(strTitle, _T("VH Inner Compactness"), strData, strPath);




	//170320 end


	//Line Spec
	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Meas Gray"));
	strData.Format(_T("%d"), SpecData.nNickGraySpec);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Nick Gray"));
	strData.Format(_T("%d"), SpecData.nOpenGraySpec);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//150410 hjc add
	//	strTitle.Format(_T("Preset Spec Line"));
	//	strIndex.Format(_T("Preset Open Gray"));
	//	strData.Format(_T("%d"), SpecData.nOpenGraySpec);
	//	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//110601 hjc add	//150413 hjc moved
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset HalfSide Nick Diff Bright Gray"));
	strData.Format(_T("%d"), SpecData.nHalfSideNickDiffBrightGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset HalfSide Nick Diff Dark Gray"));
	strData.Format(_T("%d"), SpecData.nHalfSideNickDiffDarkGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//end

	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Lead Open Gray"));
	strData.Format(_T("%d"), SpecData.nLeadOpenGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);


#if CUSTOMER_COMPANY == UMTC || CUSTOMER_COMPANY == SHINKO_DENKKI
	//Delete 20090426-ndy	//20091019 hjc mod
	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Min Line Width"));
	strData.Format(_T("%.1f"), SpecData.fMinLineWidth);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
#endif

	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Nick Size"));
	strData.Format(_T("%s"), CharToString(SpecData.szNickSize[0]));
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//150413 hjc add
	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Nick Size Percent"));
	strData.Format(_T("%d"), SpecData.nNickPercent[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Protrusion Size"));
	strData.Format(_T("%s"), CharToString(SpecData.szProtrusionSize[0]));
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//150413 hjc add
	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Protrusion Size Percent"));
	strData.Format(_T("%d"), SpecData.nProtrusionPercent[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Nick NG Filter Percent"));
	strData.Format(_T("%d"), SpecData.nNickNGFilterPercent[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Excs NG Filter Percent"));
	strData.Format(_T("%d"), SpecData.nExcsNGFilterPercent[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Line WD Delta Grad Violation"));
	strData.Format(_T("%.2f"), SpecData.fLineWdDeltaGradViolation[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Excs WD Delta Grad Violation"));
	strData.Format(_T("%.2f"), SpecData.fExcsWdDeltaGradViolation[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Line Width Group Num"));
	strData.Format(_T("%d"), SpecData.nLineWidthGroupNum);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("New MultiLineSpec"));
	strData.Format(_T("%d"), 1);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	if (SpecData.nLineWidthGroupNum > 0)		//20091009 hjc mod
	{
		int idx = 0;
		for (idx = 0; idx<SpecData.nLineWidthGroupNum + 1; idx++)
		{
			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Line Width Group%d"), idx);
			strData.Format(_T("%.2f"), SpecData.fLineWidthGroup[idx]);
			::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Line Width Group Lower%d"), idx);
			strData.Format(_T("%.2f"), SpecData.fLineWidthGroupLower[idx]);
			::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Narrow Trace Violation%d"), idx);
			strData.Format(_T("%.2f"), SpecData.fNarrowTraceViolation[idx]);
			::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Wide Trace Violation%d"), idx);
			strData.Format(_T("%.2f"), SpecData.fWideTraceViolation[idx]);
			::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset TraceWidthAdjustVal%d"), idx);
			strData.Format(_T("%.2f"), 0.0);
			::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Nick Size%d"), idx);
			strData.Format(_T("%s"), CharToString(SpecData.szNickSize[idx]));
			::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

			//150413 hjc add
			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Nick Size Percent%d"), idx);
			strData.Format(_T("%d"), SpecData.nNickPercent[idx]);
			::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Protrusion Size%d"), idx);
			strData.Format(_T("%s"), CharToString(SpecData.szProtrusionSize[idx]));
			::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

			//150413 hjc add
			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Protrusion Size Percent%d"), idx);
			strData.Format(_T("%d"), SpecData.nProtrusionPercent[idx]);
			::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Nick NG Filter Percent%d"), idx);
			strData.Format(_T("%d"), SpecData.nNickNGFilterPercent[idx]);
			::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Excs NG Filter Percent%d"), idx);
			strData.Format(_T("%d"), SpecData.nExcsNGFilterPercent[idx]);
			::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Line WD Delta Grad Violation%d"), idx);
			strData.Format(_T("%.2f"), SpecData.fLineWdDeltaGradViolation[idx]);
			::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Excs WD Delta Grad Violation%d"), idx);
			strData.Format(_T("%.2f"), SpecData.fExcsWdDeltaGradViolation[idx]);
			::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
		}

	}
	else
	{
		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("Preset Line Width Group0"));
		strData.Format(_T("%.2f"), SpecData.fLineWidthGroup[0]);
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("Preset Line Width Group Lower0"));
		strData.Format(_T("%.2f"), SpecData.fLineWidthGroupLower[0]);
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("Preset Narrow Trace Violation0"));
		strData.Format(_T("%.2f"), SpecData.fNarrowTraceViolation[0]);
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("Preset Wide Trace Violation0"));
		strData.Format(_T("%.2f"), SpecData.fWideTraceViolation[0]);
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("Preset TraceWidthAdjustVal%d"), 0);
		strData.Format(_T("%.2f"), 0.0);
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	}

	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Narrow Trace Violation"));
	strData.Format(_T("%.2f"), SpecData.fNarrowTraceViolation[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Line"));
	strIndex.Format(_T("Preset Wide Trace Violation"));
	strData.Format(_T("%.2f"), SpecData.fWideTraceViolation[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//Fine Line Spec
	//Delete 20090426-ndy	//20091019 hjc mod

	//170403 hjc add
	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Meas Gray"));
	strData.Format(_T("%d"), SpecData.nFineNickGraySpec);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Nick Gray"));
	strData.Format(_T("%d"), SpecData.nFineOpenGraySpec);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine HalfSide Nick Diff Bright Gray"));
	strData.Format(_T("%d"), SpecData.nFineHalfSideNickDiffBrightGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine HalfSide Nick Diff Dark Gray"));
	strData.Format(_T("%d"), SpecData.nFineHalfSideNickDiffDarkGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//170403 hjc add end

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Min Line Width"));
	strData.Format(_T("%.1f"), SpecData.fFineMinLineWidth);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Nick Size"));
	strData.Format(_T("%s"), CharToString(SpecData.szFineNickSize[0]));
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Protrusion Size"));
	strData.Format(_T("%s"), CharToString(SpecData.szFineProtrusionSize[0]));
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//150413 hjc add
	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Nick Size Percent"));
	strData.Format(_T("%d"), SpecData.nFineNickPercent[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Protrusion Size Percent"));
	strData.Format(_T("%d"), SpecData.nFineProtrusionPercent[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Nick NG Filter Percent"));
	strData.Format(_T("%d"), SpecData.nFineNickNGFilterPercent[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Excs NG Filter Percent"));
	strData.Format(_T("%d"), SpecData.nFineExcsNGFilterPercent[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Line WD Delta Grad Violation"));
	strData.Format(_T("%.2f"), SpecData.fFineLineWdDeltaGradViolation[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Excs WD Delta Grad Violation"));
	strData.Format(_T("%.2f"), SpecData.fFineExcsWdDeltaGradViolation[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Line Width Group Num"));
	strData.Format(_T("%d"), SpecData.nLineWidthGroupNum);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	for (int idx = 0; idx < SpecData.nLineWidthGroupNum + 1; idx++)
	{
		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Nick Size%d"), idx);
		strData.Format(_T("%s"), CharToString(SpecData.szFineNickSize[idx]));
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Protrusion Size%d"), idx);
		strData.Format(_T("%s"), CharToString(SpecData.szFineProtrusionSize[idx]));
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		//150413 hjc add
		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Nick Size Percent%d"), idx);
		strData.Format(_T("%d"), SpecData.nFineNickPercent[idx]);
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Protrusion Size Percent%d"), idx);
		strData.Format(_T("%d"), SpecData.nFineProtrusionPercent[idx]);
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Nick NG Filter Percent%d"), idx);
		strData.Format(_T("%d"), SpecData.nFineNickNGFilterPercent[idx]);
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Excs NG Filter Percent%d"), idx);
		strData.Format(_T("%d"), SpecData.nFineExcsNGFilterPercent[idx]);
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Line WD Delta Grad Violation%d"), idx);
		strData.Format(_T("%.2f"), SpecData.fFineLineWdDeltaGradViolation[idx]);
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Excs WD Delta Grad Violation%d"), idx);
		strData.Format(_T("%.2f"), SpecData.fFineExcsWdDeltaGradViolation[idx]);
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Narrow Trace Violation%d"), idx);
		strData.Format(_T("%.2f"), SpecData.fFineNarrowTraceViolation[idx]);
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Wide Trace Violation%d"), idx);
		strData.Format(_T("%.2f"), SpecData.fFineWideTraceViolation[idx]);
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	}

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Line Width Group0"));
	strData.Format(_T("%.2f"), SpecData.fFineLineWidthGroup[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Narrow Trace Violation0"));
	strData.Format(_T("%.2f"), SpecData.fFineNarrowTraceViolation[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Wide Trace Violation0"));
	strData.Format(_T("%.2f"), SpecData.fFineWideTraceViolation[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Line Width Group"));
	strData.Format(_T("%.2f"), SpecData.fFineLineWidthGroup[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Narrow Trace Violation"));
	strData.Format(_T("%.2f"), SpecData.fFineNarrowTraceViolation[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Fine Line"));
	strIndex.Format(_T("Preset Fine Wide Trace Violation"));
	strData.Format(_T("%.2f"), SpecData.fFineWideTraceViolation[0]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);


	//Space Spec
	strTitle.Format(_T("Preset Spec Space"));
	strIndex.Format(_T("Preset Min Space Gray Spec"));
	strData.Format(_T("%d"), SpecData.nMinSpaceGraySpec);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20090412 hjc
	strTitle.Format(_T("Preset Spec Space"));
	strIndex.Format(_T("Preset Neib Space Gray Diff"));
	strData.Format(_T("%d"), SpecData.nNeibSpGrayDiff);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Space"));	//150413 hjc mod
	strIndex.Format(_T("Preset US Dark Gray Minus"));
	strData.Format(_T("%d"), SpecData.nUSDarkGrayMinus);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
#if CUSTOMER_COMPANY == UMTC || CUSTOMER_COMPANY == SHINKO_DENKKI
	//Delete 20090426-ndy	//20091019 hjc mod
	strTitle.Format(_T("Preset Spec Space"));
	strIndex.Format(_T("Preset Min Space Width"));
	strData.Format(_T("%.1f"), SpecData.fMinSpWidth);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
#endif
	strTitle.Format(_T("Preset Spec Space"));
	strIndex.Format(_T("Preset Min Space Size"));
	strData.Format(_T("%s"), CharToString(SpecData.szMinSPSize));
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//150413 hjc add
	strTitle.Format(_T("Preset Spec Space"));
	strIndex.Format(_T("Preset Min Space Size Percent"));
	strData.Format(_T("%d"), SpecData.nMinSPPercent);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Space"));
	strIndex.Format(_T("Preset Space NG Filter Percent"));
	strData.Format(_T("%d"), SpecData.nSpaceNGFilterPercent);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20090405 hjc
	strTitle.Format(_T("Preset Spec Space"));
	strIndex.Format(_T("Preset Space WD Delta Outer Grad Violation"));
	strData.Format(_T("%.2f"), SpecData.fSpWdDeltaOuterGradViolation);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//---------------

	strTitle.Format(_T("Preset Spec Space"));
	strIndex.Format(_T("Preset Space WD Delta Grad Violation"));
	strData.Format(_T("%.2f"), SpecData.fSpWdDeltaGradViolation);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Space"));	//121226 hjc add
	strIndex.Format(_T("Preset Fine Min Space Size"));
	strData.Format(_T("%.1f"), SpecData.fFineMinSpWidth);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//Ext/Pin Hole Spec
	// except list
	//SpecData.szPADRLPrecName
	//SpecData.szLPADRLName
	//SpecData.szSPRLName
	//SpecData.szARLandPrecName
	//SpecData.szPADTipPrecName
	//SpecData.szPADFine_PrecName

	//150823 hjc add
	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Virtual Drill Diff Bright Gray"));
	strData.Format(_T("%d"), SpecData.nVDrillDiffBrightGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Virtual Drill Diff Dark Gray"));
	strData.Format(_T("%d"), SpecData.nVDrillDiffDarkGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Virtual Drill Pad Precision"));
	strData.Format(_T("%.1f"), SpecData.fVDPadPrecName);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20090419 hjc
	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Virtual Drill Location Tolerance"));
	strData.Format(_T("%.1f"), SpecData.fVDLocationTolerance);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//-----------

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Virtual Drill Pad Min"));
	strData.Format(_T("%.1f"), SpecData.fVDPadMin);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Pad Void Gray Spec"));
	strData.Format(_T("%d"), SpecData.nPADVoidGraySpec);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Pad Void Min"));
	strData.Format(_T("%f"), SpecData.fPADVoidMin);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Pad Tip Min"));
	strData.Format(_T("%.1f"), SpecData.fPADTipMin);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset AR Land Min"));
	strData.Format(_T("%.1f"), SpecData.fARLandMin);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Hole Fill Ext"));
	strData.Format(_T("%.1f"), SpecData.fHoleFillExt);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20100323 hjc add
	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset CO2Hole Fill Ext"));
	strData.Format(_T("%.1f"), SpecData.fCO2HoleFillExt);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Fine PAD Void Gray Spec"));
	strData.Format(_T("%d"), SpecData.nFinePADVoidGraySpec);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Fine PAD Void Min"));
	strData.Format(_T("%.1f"), SpecData.fFinePADVoidMin);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Pin Hole Gray Spec"));
	strData.Format(_T("%d"), SpecData.nPinHoleGraySpec);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Pin Hole Min"));
	strData.Format(_T("%.1f"), SpecData.fPinHoleMin);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Island Gray Spec"));
	strData.Format(_T("%d"), SpecData.nIsLandGraySpec);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Island Min"));
	strData.Format(_T("%.1f"), SpecData.fIsLandMin);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20090412 hjc
	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Island Extra Gray Spec"));
	strData.Format(_T("%d"), SpecData.nIsLandExtGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset Island Extra Min"));
	strData.Format(_T("%.1f"), SpecData.fIsLandExtMin);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//jun 20120903 for LG_CCL-Inspector
	strTitle.Format(_T("Preset Spec CCL Inspection"));
	strIndex.Format(_T("Preset CCL Gray Spec"));
	strData.Format(_T("%d"), SpecData.nCCLGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec CCL Inspection"));
	strIndex.Format(_T("Preset CCL Circularity"));
	strData.Format(_T("%.1f"), SpecData.fCCLCircularity);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec CCL Inspection"));
	strIndex.Format(_T("Preset CCL Defect Size"));
	strData.Format(_T("%.1f"), SpecData.fCCLDefSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//end

	//20100322 hjc add
	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset HoleLand Void Gray"));
	strData.Format(_T("%d"), SpecData.nHoleLandVoidGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset CO2Land Void Gray"));
	strData.Format(_T("%d"), SpecData.nCO2LandVoidGraySpec);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset CO2Land Min"));
	strData.Format(_T("%.1f"), SpecData.fCO2LandMin);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Extra PinHole"));
	strIndex.Format(_T("Preset CO2Land Align Mode"));
	strData.Format(_T("%s"), CharToString(SpecData.szCO2LandAlignMode));
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//---------------

	//Hole/VH Spec
	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset Hole Tolerance"));
	strData.Format(_T("%.1f"), SpecData.fHoleTolerance);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset Hole Dia Upper"));
	strData.Format(_T("%.1f"), SpecData.fHoleDiaUpper);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset Hole Dia Lower"));
	strData.Format(_T("%.1f"), SpecData.fHoleDiaLower);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset Hole Open Gray"));
	strData.Format(_T("%d"), SpecData.nHoleOpenGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset Hole Missing Gray"));
	strData.Format(_T("%d"), SpecData.nHoleMissingGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset Hole Inner Gray"));
	strData.Format(_T("%d"), SpecData.nHoleInnerGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset Hole RL Precision Name"));
	strData.Format(_T("%s"), CharToString(SpecData.szHoleRLPrecName));
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset Hole Def Size"));
	strData.Format(_T("%d"), SpecData.nHoleDefNum);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset VH Mode"));
	strData.Format(_T("%s"), CharToString(SpecData.szVHMode));
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset CO2 Missing Gray"));
	strData.Format(_T("%d"), SpecData.nCO2MissingGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset CO2 Hole Num"));
	strData.Format(_T("%d"), SpecData.nCO2HoleNum);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset CO2 Open Gray"));
	strData.Format(_T("%d"), SpecData.nCO2OpenGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset CO2 Miss Align Gray"));
	strData.Format(_T("%d"), SpecData.nCO2MisAgnGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset CO2 Miss Align Defect Percent"));
	strData.Format(_T("%d"), SpecData.nCO2MisAgnDefPercent);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset VH Edge Thr Diff Gray"));
	strData.Format(_T("%d"), SpecData.nVHEdgeThrDiffGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset VH BreakOut Gray"));
	strData.Format(_T("%d"), SpecData.nVHBreakOutGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset VH Dissmear Gray"));
	strData.Format(_T("%d"), SpecData.nVHDissmearGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Hole VH"));
	strIndex.Format(_T("Preset VH Conti BreakOut Num"));
	strData.Format(_T("%d"), SpecData.nVHContiBreakOutNum);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//Edge Spec
	strTitle.Format(_T("Preset Spec Edge"));
	strIndex.Format(_T("Preset Pad Edge Nick Gray"));
	strData.Format(_T("%d"), SpecData.nPadEdgeNickGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Edge"));	//120105 hjc add
	strIndex.Format(_T("Preset Pad Edge Neib Gray Diff"));
	strData.Format(_T("%d"), SpecData.nPadEdgeNeibGrayDiff);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//140127 hjc add
	strTitle.Format(_T("Preset Spec Edge"));
	strIndex.Format(_T("Preset Pad Edge BA Diff Dark Gray"));
	strData.Format(_T("%d"), SpecData.nPadEdgeBADiffDarkGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Edge"));
	strIndex.Format(_T("Preset Pad Edge Nick WD Delta Grad Violation"));
	strData.Format(_T("%.1f"), SpecData.fPadEdgeNickWdDeltaGradViolation);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Edge"));
	strIndex.Format(_T("Preset Pad Edge Excs WD Delta Grad Violation"));
	strData.Format(_T("%.1f"), SpecData.fPadEdgeExcsWdDeltaGradViolation);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20090412 hjc
	strTitle.Format(_T("Preset Spec Edge"));
	strIndex.Format(_T("Preset Pad VD Edge Gray"));
	strData.Format(_T("%d"), SpecData.nPadVDEdgeGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Edge"));
	strIndex.Format(_T("Preset Pad VD Edge Wd Delta Grad Violation"));
	strData.Format(_T("%.2f"), SpecData.fPadVDEdgeWdDeltaGradViolation);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//---------------

	strTitle.Format(_T("Preset Spec Edge"));
	strIndex.Format(_T("Preset Hole Edge Nick Gray"));
	strData.Format(_T("%d"), SpecData.nHoleEdgeNickGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Edge"));	//120109 hjc add
	strIndex.Format(_T("Preset Hole Edge Neib Gray Diff"));
	strData.Format(_T("%d"), SpecData.nHoleEdgeNeibGrayDiff);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Edge"));
	strIndex.Format(_T("Preset Hole Edge Nick WD Delta Grad Violation"));
	strData.Format(_T("%.1f"), SpecData.fHoleEdgeNickWdDeltaGradViolation);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Edge"));
	strIndex.Format(_T("Preset Hole Edge Excs WD Delta Grad Violation"));
	strData.Format(_T("%.1f"), SpecData.fHoleEdgeExcsWdDeltaGradViolation);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Edge"));
	strIndex.Format(_T("Preset Via Edge Nick Gray"));
	strData.Format(_T("%d"), SpecData.nViaEdgeNickGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Edge"));	//120109 hjc add
	strIndex.Format(_T("Preset Via Edge Neib Gray Diff"));
	strData.Format(_T("%d"), SpecData.nViaEdgeNeibGrayDiff);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Edge"));
	strIndex.Format(_T("Preset Via Edge Nick WD Delta Grad Violation"));
	strData.Format(_T("%.1f"), SpecData.fViaEdgeNickWdDeltaGradViolation);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Edge"));
	strIndex.Format(_T("Preset Via Edge Excs WD Delta Grad Violation"));
	strData.Format(_T("%.1f"), SpecData.fViaEdgeExcsWdDeltaGradViolation);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//Model Spec
	strTitle.Format(_T("Preset Spec Model"));
	strIndex.Format(_T("Preset PTModel Search Range Extension"));
	strData.Format(_T("%d"), pGlobalDoc->m_nPtSrchRngExt);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Model"));
	strIndex.Format(_T("Preset Align Tolerance"));
	strData.Format(_T("%d"), SpecData.nAlignTolerance);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Model"));
	strIndex.Format(_T("Preset Theta Align"));
	strData.Format(_T("%s"), pGlobalDoc->m_strThetaAlign);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Model"));
	strIndex.Format(_T("Preset Defect Mask Size"));
	strData.Format(_T("%.1f"), SpecData.fDefMaskSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec Model"));
	strIndex.Format(_T("Preset Near Defect Length"));
	strData.Format(_T("%.1f"), SpecData.fNearDefLen);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20100210 hjc add
	if (pGlobalDoc->m_bUseMultiVaccumControl)	//130311 hjc add
	{
		strTitle.Format(_T("Preset Spec Model"));
		strIndex.Format(_T("Preset Select Vaccum"));
		strData.Format(_T("%s"), CharToString(SpecData.strSelectVaccum));
		::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

		if (SpecData.strSelectVaccum == "Both")	//130215 hjc add
			SpecData.nSelectVaccum = 1;
		else if (SpecData.strSelectVaccum == "FirstOnly")
			SpecData.nSelectVaccum = 2;
	}
	else
	{
		strTitle.Format(_T("Preset Spec Model"));
		strIndex.Format(_T("Preset Select Vaccum"));
		::WritePrivateProfileString(strTitle, strIndex, _T("Both"), strPath);
		SpecData.nSelectVaccum = 1;
	}

	//2022 07 13 lgh 
	strTitle.Format(_T("Preset Spec Model"));
	strData.Format(_T("%d"), pGlobalDoc->m_nIRISPosID);
	::WritePrivateProfileString(strTitle, _T("IRISPosID"), strData, strPath);

	//ADDON Line Spec
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset GTC Shake Extend"));
	strData.Format(_T("%d"), SpecData.bGTCShakeExtend);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20101210 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Use PT Align Cell One"));
	strData.Format(_T("%d"), pGlobalDoc->m_bUsePTAlignCellOne);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply Stella Method"));
	strData.Format(_T("%d"), pMainFrame->m_bApplyStellaMethod);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20090902 hjc
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply Inclined Nick"));
	strData.Format(_T("%d"), pMainFrame->m_bChkInclinedNick);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//110518 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply Inclined Space"));
	strData.Format(_T("%d"), pMainFrame->m_bChkInclinedSpace);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//110526 hjc add	
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Apply Skip Check In VD Line"));
	strData.Format(_T("%d"), SpecData.bSkipChkInVDLine);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply Inclined Oblique Space"));
	strData.Format(_T("%d"), pMainFrame->m_bChkInclinedObliqueSpace);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20220316 LGH ADD
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset CheckProtFromSpaceWidth"));
	strData.Format(_T("%d"), SpecData.m_bCheckProtFromSpaceWidth);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20220513 add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Use Large Align Shift"));
	strData.Format(_T("%d"), SpecData.bLargeAlignShift);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20220513 add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Use Rough Surface Pattern"));
	strData.Format(_T("%d"), SpecData.bRoughSurface);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//121128 hjc add
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Apply Silver Paste Via"));
	strData.Format(_T("%d"), SpecData.bCheckSilverPasteVia);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Apply VH Out Break Count"));
	strData.Format(_T("%d"), SpecData.nVHOutBreakCnt);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//end
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));		//20230508 add
	strIndex.Format(_T("Preset Apply VH Taping Tolerence"));
	strData.Format(_T("%d"), SpecData.nVHTapingTolerence);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));		//20230627 add
	strIndex.Format(_T("Preset Apply VH Taping Min Max Diff"));
	strData.Format(_T("%d"), SpecData.nVHTapingMinMaxDiff);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));	//20230628 add
	strIndex.Format(_T("Preset Check Via Multi Dia"));
	strData.Format(_T("%d"), SpecData.bChkViaMultidia);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));		//20230711 add
	strIndex.Format(_T("Preset Apply VH Inner Gray"));
	strData.Format(_T("%d"), SpecData.nVHInnerGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));		//20230713 add
	strIndex.Format(_T("Preset Apply VH Min Max Dia Ratio"));
	strData.Format(_T("%d"), SpecData.nVHMinMaxDiaRatio);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20120418-ndy
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply Inclined Oblique Line"));
	strData.Format(_T("%d"), pMainFrame->m_bChkInclinedObliqueLine);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20101018 hjc
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply Inclined Short"));
	strData.Format(_T("%d"), pMainFrame->m_bChkInclinedShort);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//161228 LGH
	pGlobalDoc->SaveMachineLogicModeToPreset(INSP_MODE_NORMAL, strPath);
	pGlobalDoc->SaveMachineLogicModeToPreset(INSP_MODE_RED, strPath);
	pGlobalDoc->SaveMachineLogicModeToPreset(INSP_MODE_BLUE, strPath);

	//20091203 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply Measurement Method"));
	strData.Format(_T("%d"), pMainFrame->m_bCheckMeasurementMethod);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//140425 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply Pattern Tip Dead Zone"));
	strData.Format(_T("%d"), pMainFrame->m_bPatternTipDeadZone);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply Post Filtering"));
	strData.Format(_T("%d"), pMainFrame->m_bApplyPostFiltering);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply Space Post Filtering"));
	strData.Format(_T("%d"), pMainFrame->m_bApplySpaceFiltering);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Line Noise Filter Value"));
	strData.Format(_T("%d"), pMainFrame->m_nLineNoiseFilter);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	// 20090514 jsy
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Space Noise Filter Value"));
	strData.Format(_T("%d"), pMainFrame->m_nSpaceNoiseFilter);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	// 20090525 
	strTitle.Format(_T("Preset Pre System"));	//150413 hjc add
	strIndex.Format(_T("Preset Defect Merge Ratio OnTrace"));
	strData.Format(_T("%.2f"), pMainFrame->m_fDefectMergeRatioOnTrace);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Pad Tip Precision Nick Check"));
	strData.Format(_T("%.1f"), SpecData.fPADTipNickPrecSpec);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));	//130528 hjc add
	strIndex.Format(_T("Preset Space Neib Dark Gray Tot"));
	strData.Format(_T("%d"), SpecData.nNeibDarkGrayTot);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));	//130528 hjc add
	strIndex.Format(_T("Preset Space Neib Bright Gray Tot"));
	strData.Format(_T("%d"), SpecData.nNeibBrightGrayTot);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Pad Tip Tolerance"));
	strData.Format(_T("%.2f"), SpecData.fSROEExceptLen);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Pattern Tip Tolerance"));
	strData.Format(_T("%.2f"), SpecData.fOEExceptLen);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//150625 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Space Tip Tolerance"));
	strData.Format(_T("%.2f"), SpecData.fOEExceptSpaceLen);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Hole Tip Tolerance"));
	strData.Format(_T("%.2f"), SpecData.fARCO2JuncExceptLen);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Trace Shake Tolerance"));
	strData.Format(_T("%d"), pGlobalDoc->m_nShakeTolerance);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Line Width StepUp Sensitivity"));
	strData.Format(_T("%.1f"), pMainFrame->m_fLineWidthStepUpSensitivity);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Space Under Layer Effect Gray Plus"));
	strData.Format(_T("%d"), SpecData.nSpaceUnderLayerEffectGrayPlus);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));	//20230704 add
	strIndex.Format(_T("Preset Center Line Offset Tolerance"));
	strData.Format(_T("%d"), SpecData.nCenterlineOffsetTolerance);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//160330 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Space Under Layer Cut Threshold"));
	strData.Format(_T("%d"), SpecData.nUnderLayerCutTh);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Space Under Layer Lower Gray"));
	strData.Format(_T("%d"), SpecData.nSpUnderLayerLowerGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Space Under Layer Upper Gray"));
	strData.Format(_T("%d"), SpecData.nSpUnderLayerUpperGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Space Under Layer Def Size"));
	strData.Format(_T("%.2f"), SpecData.fSpUnderLayerDefSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//160330 hjc add end

	// 20090630 jsy	
	strTitle.Format(_T("Preset Pre System"));
	strIndex.Format(_T("Preset Line Wnd Boundary Gray Minus"));
	strData.Format(_T("%d"), SpecData.nLineWndBoundaryGrayMinus);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Pre System"));
	strIndex.Format(_T("Preset Space Wnd Boundary Gray Plus"));
	strData.Format(_T("%d"), SpecData.nSpaceWndBoundaryGrayPlus);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//111029 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply Dish Down"));
	strData.Format(_T("%d"), pMainFrame->m_bChkDishDown);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//111011 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply In Land Line"));
	strData.Format(_T("%d"), pMainFrame->m_bChkInLandLine);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//150710 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply Edge Spec Down"));
	strData.Format(_T("%d"), pMainFrame->m_bEdgeSpecDown);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//150710 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Edge Spec Down Pixel"));
	strData.Format(_T("%d"), SpecData.nEdgeSpecDownPxl);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//150817 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Exclude Spire"));
	strData.Format(_T("%d"), pMainFrame->m_bChkExcludeSpire);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//110701 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset PM Image Threshold Enhancement"));
	strData.Format(_T("%d"), SpecData.bPMImgThresholdEnhancement);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset PM Image Adaptive Threshold Ratio"));
	strData.Format(_T("%.2f"), SpecData.fAdaptiveThresholdRatio);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//end

	//130409 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset CompensateWD For Additive Process"));
	strData.Format(_T("%d"), pMainFrame->m_bCompensateWDForAdditiveProcess);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//150421 hjc add
	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Apply Master Real Same"));
	strData.Format(_T("%d"), pMainFrame->m_bMasterRealSameFlag);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));	//131216 hjc add
	strIndex.Format(_T("Preset VD Neib PM MinMax Diff Gray"));
	strData.Format(_T("%d"), SpecData.nVDNeibPMMinMaxDiffGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Line"));
	strIndex.Format(_T("Preset Linked Defect Count"));
	strData.Format(_T("%f"), SpecData.fLinkedDefectCntPix);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//end

	//ADDON Extra PinHole Spec
	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Dark Pinhole Gray Minus"));
	strData.Format(_T("%d"), SpecData.nDarkPinHoleGrayMinus);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Bright PAD Def Gray Plus"));
	strData.Format(_T("%d"), SpecData.nBrightPADDefGrayPlus);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Dark PAD Def Gray Minus"));
	strData.Format(_T("%d"), SpecData.nDarkPADDefGrayMinus);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));	//130528 hjc add
	strIndex.Format(_T("Preset Relative Pad Defect Size"));
	strData.Format(_T("%.2f"), SpecData.fRlsPadDefSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));	//130528 hjc add
	strIndex.Format(_T("Preset Relative PinHole Defect Size"));
	strData.Format(_T("%.2f"), SpecData.fRlsPinHoleDefSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));	//130529 hjc add
	strIndex.Format(_T("Preset Exclude PadDef Edge Pixel"));
	strData.Format(_T("%d"), SpecData.nExcludePadDefEdgePixel);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));	//130529 hjc add
	strIndex.Format(_T("Preset Exclude PinHole Edge Pixel"));
	strData.Format(_T("%d"), SpecData.nExcludePinHoleEdgePixel);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset PinHole Width Limit Pixel"));
	strData.Format(_T("%.2f"), SpecData.fPinHoleBreadthLimitPixel);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset PinHole Circularity Limit"));
	strData.Format(_T("%.2f"), SpecData.fPinHoleCompacenessLimit);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset PinHole Merge Pixel"));
	strData.Format(_T("%d"), SpecData.nPinHoleClosingIteration);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	// 20090512 add
	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset PinHole Merge Distance"));
	strData.Format(_T("%.1f"), SpecData.fPinHoleMergeDistance);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	// 20090326 ljg NY-add
	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset PinHole Noise Reduction Pixel"));
	strData.Format(_T("%d"), SpecData.nPinHoleOpeningIteration);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	// 120501 jsy add
	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset PadDef Noise Reduction Pixel"));
	strData.Format(_T("%d"), SpecData.nPadDefOpeningIteration);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	// 120501 jsy add
	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset PadDef Merge Pixel"));
	strData.Format(_T("%d"), SpecData.nPadDefClosingIteration);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Use Local RleBlock"));
	strData.Format(_T("%d"), SpecData.bUseLocalRleBlock);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//130604 hjc add
	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Use Relative PinHole Radient"));
	strData.Format(_T("%d"), SpecData.bUseRelPinHoleRadient);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Use Raw Gray for PinHole"));
	strData.Format(_T("%d"), SpecData.bUseRawGrayPinHole);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20090412 hjc Extra
	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Use Raw Gray for Island"));
	strData.Format(_T("%d"), SpecData.bUseRawGrayForIsland);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Bright Island Gray Plus"));
	strData.Format(_T("%d"), SpecData.nBrightIslandGrayPlus);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Dark Island Gray Minus"));
	strData.Format(_T("%d"), SpecData.nDarkIslandGrayMinus);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//-----------------

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Use Raw Gray for PADDefect"));
	strData.Format(_T("%d"), SpecData.bUseRawGrayPADDefect);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20190729 add start
	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Use New Raw Gray for PADDefect"));
	strData.Format(_T("%d"), SpecData.bUseNewRawGrayPADDefect);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Use New Raw Gray for PinHole"));
	strData.Format(_T("%d"), SpecData.bUseNewRawGrayPinHole);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset New Use Raw Gray for Island"));
	strData.Format(_T("%d"), SpecData.bUseNewRawGrayForIsland);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//20190729 add end

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Dark Gray Minus"));
	strData.Format(_T("%d"), SpecData.nSpLgDarkGrayMinus);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Dark Pixel Num"));
	strData.Format(_T("%d"), SpecData.nDarkSpaceMin);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Bright Pinhole Gray Plus"));
	strData.Format(_T("%d"), SpecData.nBrightPinHoleGrayPlus);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20090405 hjc
	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Dark Pinhole Neib Gray Minus Apply Ratio"));
	strData.Format(_T("%.2f"), SpecData.fDarkPinHoleNeibGrayMinusApplyRatio);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Bright Pinhole Neib Gray Plus Apply Ratio"));
	strData.Format(_T("%.2f"), SpecData.fBrightPinHoleNeibGrayPlusApplyRatio);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//----------------------------

	//20160108 ndy add - Start
	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Use Fine Extra Inspection for ExtraDefect"));
	strData.Format(_T("%d"), SpecData.bUseFineIslandInsp);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Fine Extra Relative Gray"));
	strData.Format(_T("(%d"), SpecData.nFineIslandRelativeGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Fine Extra Max Size"));
	strData.Format(_T("%d"), SpecData.nFineIslandMaxSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Fine Extra Mask Size"));
	strData.Format(_T("%d"), SpecData.nFineIslandMaskSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Use Fine PinHole Inspction for PinHoleDefect"));
	strData.Format(_T("%d"), SpecData.bUseFinePinHoleInsp);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Fine PinHole Relative Gray"));
	strData.Format(_T("%d"), SpecData.nFinePinHoleRelativeGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Fine PinHole Max Size"));
	strData.Format(_T("%d"), SpecData.nFinePinHoleMaxSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//20160108 ndy add - End

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));	//20230417 add start
	strIndex.Format(_T("Preset Sp Gradient Upper Limit"));
	strData.Format(_T("%d"), SpecData.nGradientUpperLimit);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Sp Gradient Threshold"));
	strData.Format(_T("%d"), SpecData.nGradientThreshold);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Sp Gradient Min Size"));
	strData.Format(_T("%d"), SpecData.nGradientMinSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset PadLg Gradient Upper Limit"));
	strData.Format(_T("%d"), SpecData.nPadLgGradientUpperLimit);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset PadLg Gradient Threshold"));
	strData.Format(_T("%d"), SpecData.nPadLgGradientThreshold);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset PadLg Gradient Min Size"));
	strData.Format(_T("%d"), SpecData.nPadLgGradientMinSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
	strIndex.Format(_T("Preset Use Relative Dark Gray Only"));
	strData.Format(_T("%d"), SpecData.bUseRlsDarkGrayOnly);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);		//20230417 add end

																			//ADDON Hole Via Spec
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset VH In-Out Gray Diff"));
	strData.Format(_T("%d"), SpecData.nCO2InOutGrayDiff);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset VH Inner Bright Def Percent"));
	strData.Format(_T("%d"), SpecData.nCO2InnerBrightDefPercent);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset VH Inner Saturation Gray"));
	strData.Format(_T("%d"), SpecData.nCO2InnerSaturationGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset VH Inner Bright Search Diameter Ratio"));
	strData.Format(_T("%.1f"), SpecData.fCO2InnerBrightSrchDiaRatio);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));			// 091214 jsy
	strIndex.Format(_T("Preset VH Inner Roughness"));
	strData.Format(_T("%.1f"), SpecData.fCO2InnerRoughness);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));			// 091214 jsy
	strIndex.Format(_T("Preset VH Inner Roughness Search Diameter Ratio"));
	strData.Format(_T("%.1f"), SpecData.fCO2InnerRoughnessSrchDiaRatio);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Use VD Ring Width Filter"));
	strData.Format(_T("%d"), SpecData.bUseVDRingWidthFilter);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20100517 hjc add
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Extension Hole Search"));
	strData.Format(_T("%d"), SpecData.bExtensionHoleSearch);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//130915 hjc add
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Inspection Large Hole"));
	strData.Format(_T("%d"), SpecData.bInspLargeHole);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//140325 hjc add
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Inspection Small Hole"));
	strData.Format(_T("%d"), SpecData.bInspSmallHole);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset VD Ring Width Pixel"));
	strData.Format(_T("%.1f"), SpecData.fVDRingWidthPixel);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset VH Ring Width Pixel"));
	strData.Format(_T("%.1f"), SpecData.fVHRingWidthPixel);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//120515 jsy - start
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset BT Via Min Length Pixel"));
	strData.Format(_T("%d"), SpecData.nBTViaMin);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset BT Via Closing Number"));
	strData.Format(_T("%d"), SpecData.nBTVRingClosingNumber);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset BT Via Upper Gray"));
	strData.Format(_T("%d"), SpecData.nBTVGraySpecUpper);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset BT Via Lower Gray"));
	strData.Format(_T("%d"), SpecData.nBTVGraySpecLower);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//120515 jsy - end

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset HoleLand Radius Ratio"));
	strData.Format(_T("%.2f"), SpecData.fHoleLandSizeRatio);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset AR Find Line Add Pixel"));
	strData.Format(_T("%d"), pGlobalDoc->m_nARFindLineAddPixel);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20100511 hjc add
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset AR Edge MinMax Diff Gray"));
	strData.Format(_T("%d"), SpecData.nAREdgeDiffGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset AR Break Count"));
	strData.Format(_T("%d"), SpecData.nARBreakCnt);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//end

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset VH Find Line Add Pixel"));
	strData.Format(_T("%d"), pGlobalDoc->m_nCO2FindLineAddPixel);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20091117
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Hole Meas Dia Successive Pixel"));
	strData.Format(_T("%d"), SpecData.nHoleMeasDiaSuccessivePixel);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//130726 hjc add
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset LargeCircle Check InnerOuter Pixels"));
	strData.Format(_T("%d"), SpecData.nLargeCircle_Check_InnerOuter_Pixels);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//141105 hjc add
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Diff Delta Pixel In ARCO2"));
	strData.Format(_T("%d"), SpecData.nDiffDeltaPxlARCO2);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//140325 hjc add
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset SmallCircle Check Inner Pixels"));
	strData.Format(_T("%d"), SpecData.nSmallCircle_Check_Inner_Pixels);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));	//120131 hjc add
	strIndex.Format(_T("Preset Hole Min Max Diff Gray Plus"));
	strData.Format(_T("%d"), SpecData.nVDHoleMinMaxDiffGrayPlus);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//121206 jsy - start
	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Dimple Lower Gray"));
	strData.Format(_T("%d"), SpecData.nDimpleLowerGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Dimple Upper Gray"));
	strData.Format(_T("%d"), SpecData.nDimpleUpperGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Dimple Copper Miss Num"));
	strData.Format(_T("%d"), SpecData.nDimpleCopperMissNum);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Dimple Copper Search Ratio"));
	strData.Format(_T("%.2f"), SpecData.fDimpleCopperSearchRatio);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Hole Via"));
	strIndex.Format(_T("Preset Dimple Ring Num"));
	strData.Format(_T("%d"), SpecData.nDimpleRingNum);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//121206 jsy - end

	//ADDON Edge Violation Spec
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Use fixed PM ID - Etching Pixels"));
	strData.Format(_T("%d"), SpecData.bUseFixedPMId);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//2022 12 16 lgh
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset ApplySCurveEdge"));
	strData.Format(_T("%d"), SpecData.bApplySCurveEdge);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);





	//130829 hjc add
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Check PAD Edge Limit"));
	strData.Format(_T("%d"), pMainFrame->m_bCheckPADEdgeLimit);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//131105 hjc add
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Edge Align Tolerence"));
	strData.Format(_T("%d"), pMainFrame->m_nEdgeAlignTol);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//131113 hjc add
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Edge Gray Check Range"));
	strData.Format(_T("%d"), pMainFrame->m_nEdgeGrayCheckRange);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//140121 hjc add
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Diff Edge Delta Pixel"));
	strData.Format(_T("%d"), pMainFrame->m_nDiffEdgeDeltaPixel);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//160318 hjc add
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Large Edge Nick Spec Down Size Pixel"));
	strData.Format(_T("%.2f"), pMainFrame->m_fLargeEdgeNickSpecDownSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Large Edge Prot Spec Down Size Pixel"));
	strData.Format(_T("%.2f"), pMainFrame->m_fLargeEdgeProtSpecDownSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//end

	//131031 hjc add
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Check Core Pad Tip"));
	strData.Format(_T("%d"), pMainFrame->m_bCheckCorePadTip);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Core Neutral Zone"));
	strData.Format(_T("%d"), SpecData.nCoreNeutralZone);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Core Diff Gray"));
	strData.Format(_T("%d"), SpecData.nCoreDiffGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Core Defect Size"));
	strData.Format(_T("%d"), SpecData.nCoreDefSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//end

	//111003 hjc add
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Extension Space Trace"));
	strData.Format(_T("%d"), SpecData.bExtensionSpaceTrace);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//140425 hjc add	
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Apply Wide Open"));
	strData.Format(_T("%d"), SpecData.bChkWideOpen);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Wide Open Pixel"));
	strData.Format(_T("%d"), SpecData.nWideOpenPxl);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//140425 hjc add end

	//20200511 add
	strTitle.Format(_T("Preset Spec AddOn Sud"));
	strIndex.Format(_T("Preset Pt Match Level"));
	strData.Format(_T("%d"), pGlobalDoc->m_nPtMatchLevel);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20210818 add	
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Apply Template Match"));
	strData.Format(_T("%d"), SpecData.bChkTemplateMatch);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//111005 hjc add
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Spectial Space MinMax Diff Gray"));
	strData.Format(_T("%d"), SpecData.nSpMinMaxDiffGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//end

	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset Fixed PM ID"));
	strData.Format(_T("%d"), SpecData.nFixedPMId);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20101201 hjc add
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset SPE Gray"));
	strData.Format(_T("%d"), SpecData.nSPEdgeNickGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset SPE Nick Size Pixel"));
	strData.Format(_T("%.2f"), SpecData.fSPEdgeNickWdDeltaGradViolation);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset SPE Prot Size Pixel"));
	strData.Format(_T("%.2f"), SpecData.fSPEdgeExcsWdDeltaGradViolation);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//131123 hjc add
	strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
	strIndex.Format(_T("Preset SPEdge Gray Diff"));
	strData.Format(_T("%d"), SpecData.nSPEdgeGrayDiff);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//end

	//ADDON Sud Spec	//	100429 ljh
	strTitle.Format(_T("Preset Spec AddOn Sud"));
	strIndex.Format(_T("Preset Sud InOut Lower Gray"));
	strData.Format(_T("%d"), SpecData.nSudInOutLowerGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Sud"));
	strIndex.Format(_T("Preset Sud InOut Upper Gray"));
	strData.Format(_T("%d"), SpecData.nSudInOutUpperGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Sud"));
	strIndex.Format(_T("Preset Sud InOut Def Size"));
	strData.Format(_T("%f"), SpecData.fSudInOutDefSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//110620 hjc add
	strTitle.Format(_T("Preset Spec AddOn Sud"));
	strIndex.Format(_T("Preset Check for Fiducial Mark"));
	strData.Format(_T("%d"), SpecData.bCheckFiducialMark);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Sud"));
	strIndex.Format(_T("Preset Fiducial Mark Def Area"));
	strData.Format(_T("%f"), SpecData.fFMDArea);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Sud"));
	strIndex.Format(_T("Preset Fiducial Mark Def SizeX"));
	strData.Format(_T("%f"), SpecData.fFMDSizeX);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Sud"));
	strIndex.Format(_T("Preset Fiducial Mark Def SizeY"));
	strData.Format(_T("%f"), SpecData.fFMDSizeY);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Sud"));
	strIndex.Format(_T("Preset Fiducial Mark PT Range Plus"));
	strData.Format(_T("%f"), SpecData.fFMDPtRangePlus);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Sud"));
	strIndex.Format(_T("Preset Fiducial Mark PT Score"));
	strData.Format(_T("%f"), SpecData.fFMDPtScore);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//end

	//150806 hjc add
	strTitle.Format(_T("Preset Spec AddOn Sud"));
	strIndex.Format(_T("Preset AICL Tolerance"));
	strData.Format(_T("%.2f"), SpecData.fAICLTolerance);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Spec AddOn Sud"));
	strIndex.Format(_T("Preset AICL Bound Check Gray"));
	strData.Format(_T("%d"), SpecData.nBoundChkGray);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//150827 hjc add
	strTitle.Format(_T("Preset Spec AddOn Sud"));
	strIndex.Format(_T("Preset AICL Shrink Size"));
	strData.Format(_T("%d"), SpecData.nShrinkSize);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	pGlobalDoc->SaveInspModeDataToPreset(INSP_MODE_NORMAL, strPath);
	pGlobalDoc->SaveInspModeDataToPreset(INSP_MODE_BLUE, strPath);
	pGlobalDoc->SaveInspModeDataToPreset(INSP_MODE_RED, strPath);


	////ADDON Inspection Logic Control Spec
	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Line Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspLine);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	////131104 hjc add
	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset SR Line Tip Extention Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspSrLineTipExt);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Space Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspSpace);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Pad Pixel Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspPadPixel);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Pat Pixel Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspPatPixel);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Space Pixel Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_nInspSpacePixel);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Virtual Drill Pixel Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspVDPixel);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Hole Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspHole);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Via Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspVia);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Dimple Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspDimple);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset CCL Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspCCL);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Only Via Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bUseOnlyViaInsp);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset BarType Via Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspBarTypeVia);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Edge Hole Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspContourAR);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Edge Via Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspContourVIA);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Edge Pad Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspContourLP);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	////110718 hjc add
	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset Edge VD Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspContourVD);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	////131212 hjc add
	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
	//strIndex.Format(_T("Preset SREdge Space Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspSREdgeSpace);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));	// 100429 ljh
	//strIndex.Format(_T("Preset SUD In Out Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspSudInOut);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);


	//strTitle.Format(_T("Preset Spec Inspection Logic Control"));	// 100510 jsy
	//strIndex.Format(_T("Preset SPE Space Inspection"));
	//strData.Format(_T("%d"), pGlobalDoc->m_bInspSPESpace);
	//::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Pre System Parameters"));
	strIndex.Format(_T("Preset Open Check Cell Bound"));
	strData.Format(_T("%d"), pGlobalDoc->m_nOpenChkCellBnd);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Pre System Parameters"));
	strIndex.Format(_T("Preset Nick Check Cell Bound"));
	strData.Format(_T("%d"), pGlobalDoc->m_nNickChkCellBnd);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Pre System Parameters"));
	strIndex.Format(_T("Preset Excs Check Cell Bound"));
	strData.Format(_T("%d"), pGlobalDoc->m_nExcsChkCellBnd);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//120521 hjc add
	strTitle.Format(_T("Preset Pre System Parameters"));
	strIndex.Format(_T("Preset Check Good Range For Line"));
	strData.Format(_T("%d"), pGlobalDoc->m_nChkGoodRangeForLine);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//111005 hjc add
	strTitle.Format(_T("Preset Pre System Parameters"));
	strIndex.Format(_T("Preset Min Space Check Bound Tip"));
	strData.Format(_T("%d"), pGlobalDoc->m_nMinSpCheckBoundTip);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Pre System Parameters"));
	strIndex.Format(_T("Preset Min Space Check Bound"));
	strData.Format(_T("%d"), pGlobalDoc->m_nMinSpCheckBound);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Pre System Parameters"));
	strIndex.Format(_T("Preset Min Space Check Bound Edge"));
	strData.Format(_T("%d"), pGlobalDoc->m_nMinSpCheckBoundEdge);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset Pre System Parameters"));
	strIndex.Format(_T("Preset UShort Check Bound Tip"));
	strData.Format(_T("%d"), pGlobalDoc->m_nUShortCheckBoundTip);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);
	//end

	//140702 hjc add
	strTitle.Format(_T("Preset Calibration Measure Offset Parameters"));
	strIndex.Format(_T("Preset Calib F"));
	strData.Format(_T("%.4f"), pGlobalDoc->m_fCalibF[INSP_MODE_NORMAL]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	//20200625 add
	strTitle.Format(_T("Preset Calibration Space Measure Offset Parameters"));
	strIndex.Format(_T("Preset Calib Sp F"));
	strData.Format(_T("%.4f"), pGlobalDoc->m_fSpCalibF[INSP_MODE_NORMAL]);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);


	//2021 06 29 lgh
	strData.Format(_T("%d"), SpecData.nCharInspectionGray);
	WritePrivateProfileString(_T("TextInspection"), _T("CharInspectionGray"), strData, strPath);

	strData.Format(_T("%.3f"), SpecData.dCharRegionUpperPercent);
	WritePrivateProfileString(_T("TextInspection"), _T("dCharRegionUpperPercent"), strData, strPath);

	strData.Format(_T("%.3f"), SpecData.dCharRegionLowerPercent);
	WritePrivateProfileString(_T("TextInspection"), _T("dCharRegionLowerPercent"), strData, strPath);


	int nMode = 0;
	for (nMode = INSP_MODE_RED; nMode < INSP_MODE_COUNT; nMode++)
	{
		CString strDelimter;

		strDelimter.Format(_T(" INSP%d"), nMode);

		strTitle.Format(_T("Preset Calibration Measure Offset Parameters"));
		strIndex.Format(_T("Preset Calib F"));
		strData.Format(_T("%.4f"), pGlobalDoc->m_fCalibF[nMode]);
		::WritePrivateProfileString(strTitle + strDelimter, strIndex, strData, strPath);

		strTitle.Format(_T("Preset Calibration Space Measure Offset Parameters"));	//20200625 add
		strIndex.Format(_T("Preset Calib Sp F"));
		strData.Format(_T("%.4f"), pGlobalDoc->m_fSpCalibF[nMode]);
		::WritePrivateProfileString(strTitle + strDelimter, strIndex, strData, strPath);
	}

	strTitle.Format(_T("Preset info"));
	strIndex.Format(_T("Host"));
	strData.Format(_T("%s"), strHostName);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	strTitle.Format(_T("Preset info"));
	strIndex.Format(_T("User"));
	strData.Format(_T("%s"), pGlobalDoc->m_strUserID);
	::WritePrivateProfileString(strTitle, strIndex, strData, strPath);

	::WritePrivateProfileString(_T("Preset info"), _T("User Name"), pGlobalDoc->m_strUserName, strPath);

	if (pGlobalView->m_nUserID == OPERATOR)
		::WritePrivateProfileString(_T("Preset info"), _T("User Access"), _T("Operator"), strPath);
	else if (pGlobalView->m_nUserID == ENGINEER)
		::WritePrivateProfileString(_T("Preset info"), _T("User Access"), _T("Engineer"), strPath);
	else
		::WritePrivateProfileString(_T("Preset info"), _T("User Access"), _T("Administrator"), strPath);

	CTime varTime = CTime::GetCurrentTime();
	CString strTemp;
	strTemp.Format(_T("%04d/%02d/%02d %02d:%02d:%02d"),
		varTime.GetYear(), varTime.GetMonth(), varTime.GetDay(), varTime.GetHour(), varTime.GetMinute(), varTime.GetSecond());

	::WritePrivateProfileString(_T("Preset info"), _T("SAVE TIME"), strTemp, strPath);

	GetDefaultSpecData();*/
}

void CDlgSpec::OnSelchangeComboDefaultSpecCombo()
{
	// TODO: Add your control notification handler code here
/*	int nIndex;
	CString strSpecPath;
	CString strMsg;
	CFileOperation fileOp(GetWindowVersion());
	strMsg.Format(_T("Are you change spec?"));

	if (pGlobalView->m_pDlgInspectionSub)
		pGlobalView->m_pDlgInspectionSub->m_PrevInfoPopUpDefectItem.Clear();

	if (!m_bBarcodeWork)
	{
#if CUSTOMER_COMPANY == DAEDUCK_APERIO
		if (pGlobalView->m_nUserID == OPERATOR)
		{
			if (!pMainFrame->CheckLogin())
			{
				if (pGlobalDoc->m_nSelectedLanguage == KOREA)
					strMsg.Format(_T("∑Œ±◊¿Œø° Ω«∆–«œø¥Ω¿¥œ¥Ÿ. ªÁøÎ¿⁄ ∑Œ±◊¿Œ »ƒ ¥ŸΩ√ Ω√µµ«œΩ Ω√ø¿."));
				else
					strMsg.Format(_T("Access denied. before delete the lot, you must loggined."));

				SaveLog(strMsg);
				return;
			}

			if (pGlobalView->m_nUserID == OPERATOR)
			{
				AfxMessageBox(_T("¿€æ˜¿⁄¥¬ ªÁøÎ «“ ºˆ æ¯Ω¿¥œ¥Ÿ. ø£¡ˆ¥œæÓ/ ∞¸∏Æ¿⁄∑Œ ∑Œ±◊¿Œ«œΩ Ω√ø¿"));
				m_DefaultSpecCombo.SetCurSel(m_nSpecComboIndex);	// 101011 jsy
				return;
			}

			CString strError;

			strError.Format(_T("ªÁøÎ¿⁄ %s∞° «¡∏Æº¬ Ω∫∆Â ¿˙¿Â ∏ﬁ¥∫ø° ¡¢±Ÿ«œø¥Ω¿¥œ¥Ÿ."), pGlobalDoc->m_strUserID);
			SaveLog(strError);
		}
#endif

		if (IDNO == AfxMessageBox(strMsg, MB_ICONQUESTION | MB_YESNO))
		{
			m_DefaultSpecCombo.SetCurSel(m_nSpecComboIndex);	// 101011 jsy
			return;
		}

		m_nSpecComboIndex = nIndex = m_DefaultSpecCombo.GetCurSel();
		if (nIndex == LB_ERR)
		{
			m_DefaultSpecCombo.ResetContent();
			return;
		}

		m_DefaultSpecCombo.GetLBText(nIndex, pGlobalView->m_strPresetSpecCurr);
		GetDlgItem(IDC_COMBO_DEFAULT_SPEC_COMBO)->SetWindowText(pGlobalView->m_strPresetSpecCurr);

		//20120629-ndy
		if (pGlobalDoc->m_bUseLocalSpecPreset)
			strSpecPath.Format(_T("%sSpecPreset\\%d\\%s.MSP"), pGlobalDoc->m_strLocSpecDir, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), pGlobalView->m_strPresetSpecCurr);
		else
		{
			if (!pGlobalDoc->m_bUseMultiPreset)	//130128 hjc add
				strSpecPath.Format(_T("%sSpecPreset\\%d\\%s.MSP"), pGlobalDoc->m_strIniSpecDir, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), pGlobalView->m_strPresetSpecCurr);
			else
				strSpecPath.Format(_T("%sSpecPreset%02d\\%d\\%s.MSP"), pGlobalDoc->m_strIniSpecDir, pGlobalDoc->m_nMultiPresetNumber, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), pGlobalView->m_strPresetSpecCurr);
		}

		LoadOriginDataTab(0);
		LoadOriginDataTab(1);
		LoadOriginDataTab(2);
		LoadOriginDataTab(3);
		//20090213
		LoadOriginDataTab(4);
		LoadOriginDataTab(5);
		LoadOriginDataTab(6);
		LoadOriginDataTab(7);	//20100322 hjc add
		pGlobalView->LoadSpecPreset(pGlobalView->m_strPresetSpecCurr, FALSE);	// 
		pGlobalView->LoadSpecPreset(pGlobalView->m_strPresetSpecCurr, TRUE);	// 
		pGlobalView->SetInspectSlideControl();
		CompareVariablesWithLoadPresetSpec();
		pGlobalDoc->ParseLineSpecs();
		DisplayChangedData();


		if (pGlobalDoc->m_bInspCCL[0])
		{
			pGlobalDoc->LoadBackupParameter(_T("c:\\aoiset\\cclmode.ini"));
			g_bGlassInspectMode = 2;

			CString strPath;
			strPath.Format(_T("%s%s\\%s.LSp"), pGlobalDoc->m_strLocSpecDir, pGlobalDoc->m_strModel, pGlobalDoc->m_strLayer);
			WritePrivateProfileString(_T("Model_Spec_Loc"), _T("GlassInspectMode"), _T("2"), strPath);
		}
		else
		{
			if (g_bGlassInspectMode == 2)
			{
				pGlobalDoc->LoadBackupParameter(_T("c:\\aoiset\\PCBmode.ini"));
				g_bGlassInspectMode = 0;

				CString strPath;
				strPath.Format(_T("%s%s\\%s.LSp"), pGlobalDoc->m_strLocSpecDir, pGlobalDoc->m_strModel, pGlobalDoc->m_strLayer);
				WritePrivateProfileString(_T("Model_Spec_Loc"), _T("GlassInspectMode"), _T("0"), strPath);
			}
		}

		//150529 hjc add
		int nTabNum = m_tabDlgInspection.GetCurSel();
		DisplaySpread(nTabNum);

		CString filePath, strPath;
		CFileFind finder;

		if (AoiParam()->m_bUseExtensionViaSpec && pGlobalDoc->m_nInspMode[AoiParam()->m_nCurrentInspectionMode] == VIA_MODE)
		{
			m_dlgViaSpec.CompareVariablesWithLoadPresetSpec();
			m_dlgViaSpec.DisplayChangedData();
			m_dlgViaSpec.DisplaySpread(m_dlgViaSpec.m_nTabNum);
		}

		filePath = pGlobalDoc->m_strLocSpecDir + pGlobalDoc->m_strModel;
		if (!finder.FindFile(filePath))
			if (!fileOp.DoCreateFolder(filePath, NULL))
				return;

		strPath.Format(_T("%s%s\\%s.LSp"), pGlobalDoc->m_strLocSpecDir, pGlobalDoc->m_strModel, pGlobalDoc->m_strLayer);

		::WritePrivateProfileString(_T("Model_Spec_Loc"), _T("Spec Preset Name"), pGlobalView->m_strPresetSpecCurr, strPath);

		pGlobalView->DispDefUserSelect(TRUE, TRUE);	//20120724-ndy


													//160328 LGH ADD
		if (pGlobalView->m_pDlgInspection->GetSafeHwnd())
		{
			pGlobalView->m_pDlgInspection->PostMessage(WM_CONTROL_DLG, 2, 0);
		}
		pGlobalDoc->m_bCheckMsgLSFilteringAlarm = TRUE;

#if MACHINE_MODEL == INSMART_GM4000
		Project()->m_CurrentSpecPreset.SetValid(TRUE);
		Project()->m_CurrentSpecPreset.SetRecipeName(pGlobalView->m_strPresetSpecCurr);
#endif


	}
	else
	{
		CString strSpecBackup = pGlobalView->m_strPresetSpecCurr;

		GetDlgItem(IDC_COMBO_DEFAULT_SPEC_COMBO)->SetWindowText(pGlobalView->m_strPresetSpecCurr);

		//20120629-ndy
		if (pGlobalDoc->m_bUseLocalSpecPreset)
			strSpecPath.Format(_T("%sSpecPreset\\%d\\%s.MSP"), pGlobalDoc->m_strLocSpecDir, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), pGlobalView->m_strPresetSpecCurr);
		else
		{
			if (!pGlobalDoc->m_bUseMultiPreset)	//130128 hjc add
				strSpecPath.Format(_T("%sSpecPreset\\%d\\%s.MSP"), pGlobalDoc->m_strIniSpecDir, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), pGlobalView->m_strPresetSpecCurr);
			else
				strSpecPath.Format(_T("%sSpecPreset%02d\\%d\\%s.MSP"), pGlobalDoc->m_strIniSpecDir, pGlobalDoc->m_nMultiPresetNumber, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), pGlobalView->m_strPresetSpecCurr);
		}

		LoadOriginDataTab(0);
		LoadOriginDataTab(1);
		LoadOriginDataTab(2);
		LoadOriginDataTab(3);
		//20090213
		LoadOriginDataTab(4);
		LoadOriginDataTab(5);
		LoadOriginDataTab(6);
		LoadOriginDataTab(7);	//20100322 hjc add

		pGlobalView->m_strPresetSpecCurr = strSpecBackup;

		m_bBarcodeWork = FALSE;

		pGlobalView->LoadSpecPreset(pGlobalView->m_strPresetSpecCurr, FALSE);	// 
		pGlobalView->LoadSpecPreset(pGlobalView->m_strPresetSpecCurr, TRUE);	// 

		pGlobalView->SetInspectSlideControl();
		CompareVariablesWithLoadPresetSpec();
		pGlobalDoc->ParseLineSpecs();
		DisplayChangedData();


		if (pGlobalDoc->m_bInspCCL[0])
		{
			pGlobalDoc->LoadBackupParameter(_T("c:\\aoiset\\cclmode.ini"));
			g_bGlassInspectMode = 2;

			CString strPath;
			strPath.Format(_T("%s%s\\%s.LSp"), pGlobalDoc->m_strLocSpecDir, pGlobalDoc->m_strModel, pGlobalDoc->m_strLayer);
			WritePrivateProfileString(_T("Model_Spec_Loc"), _T("GlassInspectMode"), _T("2"), strPath);
		}
		else
		{
			if (g_bGlassInspectMode == 2)
			{
				pGlobalDoc->LoadBackupParameter(_T("c:\\aoiset\\PCBmode.ini"));
				g_bGlassInspectMode = 0;

				CString strPath;
				strPath.Format(_T("%s%s\\%s.LSp"), pGlobalDoc->m_strLocSpecDir, pGlobalDoc->m_strModel, pGlobalDoc->m_strLayer);
				WritePrivateProfileString(_T("Model_Spec_Loc"), _T("GlassInspectMode"), _T("0"), strPath);
			}
		}

		//150529 hjc add
		int nTabNum = m_tabDlgInspection.GetCurSel();
		DisplaySpread(nTabNum);

		CString filePath, strPath;
		CFileFind finder;


		if (AoiParam()->m_bUseExtensionViaSpec && pGlobalDoc->m_nInspMode[AoiParam()->m_nCurrentInspectionMode] == VIA_MODE)
		{
			m_dlgViaSpec.CompareVariablesWithLoadPresetSpec();
			m_dlgViaSpec.DisplayChangedData();
			m_dlgViaSpec.DisplaySpread(m_dlgViaSpec.m_nTabNum);
		}

		filePath = pGlobalDoc->m_strLocSpecDir + pGlobalDoc->m_strModel;
		if (!finder.FindFile(filePath))
			if (!fileOp.DoCreateFolder(filePath, NULL))
				return;

		strPath.Format(_T("%s%s\\%s.LSp"), pGlobalDoc->m_strLocSpecDir, pGlobalDoc->m_strModel, pGlobalDoc->m_strLayer);

		::WritePrivateProfileString(_T("Model_Spec_Loc"), _T("Spec Preset Name"), pGlobalView->m_strPresetSpecCurr, strPath);

		pGlobalView->DispDefUserSelect(TRUE, TRUE);	//20120724-ndy

													//160328 LGH ADD
		if (pGlobalView->m_pDlgInspection->GetSafeHwnd())
		{
			pGlobalView->m_pDlgInspection->PostMessage(WM_CONTROL_DLG, 2, 0);
		}
		pGlobalDoc->m_bCheckMsgLSFilteringAlarm = TRUE;

#if MACHINE_MODEL == INSMART_GM4000
		Project()->m_CurrentSpecPreset.SetValid(TRUE);
		Project()->m_CurrentSpecPreset.SetRecipeName(pGlobalView->m_strPresetSpecCurr);
#endif
	}


	m_bMultilineSaved = 1;
	pGlobalView->m_bInitVisionAdjust = 0;
	pGlobalDoc->m_fEntireMeanLineWidthDiff = 0.0;
	pGlobalDoc->m_fEntireMeanFineLineWidthDiff = 0.0;
	g_nProcessStepState[PSTEP_ADJUST] = 0;*/
}

void CDlgSpec::LockingSpec()
{
	for (int iRow = 1; iRow <= m_Spread.GetMaxRows(); iRow++)
	{
		m_Spread.SetCol(1);
		m_Spread.SetRow(iRow);

		m_Spread.SetCellType(TYPE_STATIC);
		m_Spread.SetTypeVAlign(SSS_ALIGN_VCENTER);
		m_Spread.SetTypeAlign(SSS_ALIGN_CENTER);
	}
}

void CDlgSpec::OnDropdownComboDefaultSpecCombo()
{
	// TODO: Add your control notification handler code here
	//m_nSpecComboIndex = m_DefaultSpecCombo.GetCurSel();
}

//void CDlgSpec::OnButtonSetSpecLock() 	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
//{
/*	pGlobalView->m_pDlgSpec->m_Spread.AutoAttach();
	pGlobalView->m_pDlgSpec->m_Spread.SetEditMode(0);

	if (AoiParam()->m_bSecurityEnhanceMode)
	{
		if (pGlobalView->m_nUserID != OPERATOR)
		{
			CDlgPassWord dlgPassword;
			dlgPassword.m_bChkMagUseShow = FALSE;
			dlgPassword.DoModal();

			if (!dlgPassword.m_bPass)
				return;

			if (!dlgPassword.m_bAdmin)
				return;

			pGlobalDoc->SaveAccessLog(_T("Spec Lock"));

			DlgSpecLockNew dlg;
			dlg.m_nLanguage = pGlobalDoc->m_nSelectedLanguage;
			dlg.DoModal();

			CFileFind finder;
			CString strSpecNew;
			strSpecNew.Format(_T("%s%s\\%s_speclock.bin"),
				pGlobalDoc->m_strSpecDir,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer);

			if (finder.FindFile(strSpecNew))
			{
				LoadLockedSpecData(strSpecNew);
			}
			else if (finder.FindFile(SPEC_LOCK_1_PATH))
				LoadLockedSpecData(SPEC_LOCK_1_PATH);
			else if (finder.FindFile(SPEC_LOCK_2_PATH))
				LoadLockedSpecData(SPEC_LOCK_2_PATH);
			else
				AfxMessageBox(_T("[MSG515] Fail Save Spec Lock Data."));
		}
		else
		{
			CString strMsg;
			if (pGlobalDoc->m_nSelectedLanguage == KOREA)
			{
				AfxMessageBox(_T("SpecLock : ±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄∏∏ / ø£¡ˆ¥œæÓ∏∏ ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."), MB_ICONSTOP);
				SaveLog(strMsg);
				SaveLog(_T("SpecLock : ±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄/ø£¡ˆ¥œæÓ∏∏ Ω∫∆Â ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."));
			}
			else
			{
				AfxMessageBox(_T("SpecLock : Access denied. can't save preset spec"), MB_ICONSTOP);
				SaveLog(strMsg);
				SaveLog(_T("SpecLock : Access denied. can't save preset spec"));
			}
		}
	}
	else
	{
		// TODO: Add your control notification handler code here
		if ((pGlobalView->m_nUserID == ADMINISTRATOR || pGlobalView->m_nUserID == ENGINEER))
		{
			CDlgPassWord dlgPassword;
			dlgPassword.m_bChkMagUseShow = FALSE;
			dlgPassword.DoModal();
			if (!dlgPassword.m_bPass)
				return;

			DlgSpecLockNew dlg;
			dlg.m_nLanguage = pGlobalDoc->m_nSelectedLanguage;
			dlg.DoModal();

			CFileFind finder;

			CString strSpecNew;
			strSpecNew.Format(_T("%s%s\\%s_speclock.bin"),
				pGlobalDoc->m_strSpecDir,
				pGlobalDoc->m_strModel,
				pGlobalDoc->m_strLayer);

			if (finder.FindFile(strSpecNew))
			{
				LoadLockedSpecData(strSpecNew);
			}
			else if (finder.FindFile(SPEC_LOCK_1_PATH))
				LoadLockedSpecData(SPEC_LOCK_1_PATH);
			else if (finder.FindFile(SPEC_LOCK_2_PATH))
				LoadLockedSpecData(SPEC_LOCK_2_PATH);
			else
				AfxMessageBox(_T("[MSG515] Fail Save Spec Lock Data."));
		}
		else
		{
			CString strMsg;
			if (pGlobalDoc->m_nSelectedLanguage == KOREA)
			{
				AfxMessageBox(_T("SpecLock : ±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄∏∏ / ø£¡ˆ¥œæÓ∏∏ ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."), MB_ICONSTOP);
				SaveLog(strMsg);
				SaveLog(_T("SpecLock : ±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄/ø£¡ˆ¥œæÓ∏∏ Ω∫∆Â ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."));
			}
			else
			{
				AfxMessageBox(_T("SpecLock : Access denied. can't save preset spec"), MB_ICONSTOP);
				SaveLog(strMsg);
				SaveLog(_T("SpecLock : Access denied. can't save preset spec"));
			}
		}
	}

	if (pGlobalView->m_pDlgSpec && pGlobalView->m_pDlgSpec->IsWindowVisible())
	{
		pGlobalView->m_pDlgSpec->m_Spread.AutoAttach();
		pGlobalView->m_pDlgSpec->m_Spread.SetEditMode(0);
	}

	if (pGlobalView->m_pDlgSpec && pGlobalView->m_pDlgSpec->IsWindowVisible())
	{
		switch (pGlobalView->m_pDlgSpec->m_nTabNum)
		{
		case 0:
			pGlobalView->m_pDlgSpec->DisplaySpread(0);
			break;
		case 1:
			pGlobalView->m_pDlgSpec->DisplaySpread(1);
			break;
		case 2:
			pGlobalView->m_pDlgSpec->DisplaySpread(2);
			break;
		case 3:
			pGlobalView->m_pDlgSpec->DisplaySpread(3);
			break;
		case 4:
			pGlobalView->m_pDlgSpec->DisplaySpread(4);
			break;
		case 5:
			pGlobalView->m_pDlgSpec->DisplaySpread(5);
			break;
		case 6:
			pGlobalView->m_pDlgSpec->DisplaySpread(6);
			break;
		case 7:
			pGlobalView->m_pDlgSpec->DisplaySpread(7);	//20100322 hjc add
			break;
		}
	}

	if (pGlobalView->m_pDlgSpec->m_dlgViaSpec && pGlobalView->m_pDlgSpec->m_dlgViaSpec.IsWindowVisible())
	{
		switch (pGlobalView->m_pDlgSpec->m_dlgViaSpec.m_nTabNum)
		{
		case 0:
			pGlobalView->m_pDlgSpec->m_dlgViaSpec.DisplaySpread(0);
			break;
		case 1:
			pGlobalView->m_pDlgSpec->m_dlgViaSpec.DisplaySpread(1);
			break;
		case 2:
			pGlobalView->m_pDlgSpec->m_dlgViaSpec.DisplaySpread(2);
			break;
		}
	}
*/
//}

//void CDlgSpec::OnButtonSetLightLock()  	//20120326-ndy for Spec&Light Locking for only samsung busan HDI
//{
/*	if (AoiParam()->m_bSecurityEnhanceMode)
	{
		if ((pGlobalView->m_nUserID == ADMINISTRATOR))
		{
			CDlgPassWord dlgPassword;
			dlgPassword.m_bChkMagUseShow = FALSE;
			dlgPassword.DoModal();

			if (!dlgPassword.m_bPass)
				return;

			if (!dlgPassword.m_bAdmin)
				return;

			pGlobalDoc->SaveAccessLog(_T("LightLock"));


			CDlgSetLightLock dlg;

			dlg.DoModal();

			CFileFind ffinder;
			if (ffinder.FindFile(LIGHT_LOCK_1_PATH))
			{
				pGlobalView->LoadLockedLightData(LIGHT_LOCK_1_PATH);
				if (!ffinder.FindFile(LIGHT_LOCK_2_PATH))
				{
					CopyFileRepeat(LIGHT_LOCK_1_PATH, LIGHT_LOCK_2_PATH);
					SaveLog(_T("spec lock file was auto restored 2"));
				}
			}
			else if (ffinder.FindFile(LIGHT_LOCK_2_PATH))
			{
				pGlobalView->LoadLockedLightData(LIGHT_LOCK_2_PATH);
				if (!ffinder.FindFile(LIGHT_LOCK_1_PATH))
				{
					CopyFileRepeat(LIGHT_LOCK_2_PATH, LIGHT_LOCK_1_PATH);
					SaveLog(_T("spec lock file was auto restored 1"));
				}
			}
			else
			{
				pGlobalView->LoadLockedLightData(LIGHT_LOCK_DEFAULT_PATH);
			}

		}
		else
		{
			AfxMessageBox(_T("[MSG512] Only the administrator can access it. Enter administrator password"));
		}
	}
	else
	{
		// TODO: Add your control notification handler code here
		if ((pGlobalView->m_nUserID == ADMINISTRATOR || pGlobalView->m_nUserID == ENGINEER))
		{
			CDlgPassWord dlgPassword;
			dlgPassword.m_bChkMagUseShow = FALSE;
			dlgPassword.DoModal();
			if (!dlgPassword.m_bPass)
				return;

			CDlgSetLightLock dlgSetLightLock;
			dlgSetLightLock.DoModal();

			CFileFind ffinder;
			if (ffinder.FindFile(LIGHT_LOCK_1_PATH))
			{
				pGlobalView->LoadLockedLightData(LIGHT_LOCK_1_PATH);
				if (!ffinder.FindFile(LIGHT_LOCK_2_PATH))
				{
					CopyFileRepeat(LIGHT_LOCK_1_PATH, LIGHT_LOCK_2_PATH);
					SaveLog(_T("spec lock file was auto restored 2"));
				}
			}
			else if (ffinder.FindFile(LIGHT_LOCK_2_PATH))
			{
				pGlobalView->LoadLockedLightData(LIGHT_LOCK_2_PATH);
				if (!ffinder.FindFile(LIGHT_LOCK_1_PATH))
				{
					CopyFileRepeat(LIGHT_LOCK_2_PATH, LIGHT_LOCK_1_PATH);
					SaveLog(_T("spec lock file was auto restored 1"));
				}
			}
			else
			{
				pGlobalView->LoadLockedLightData(LIGHT_LOCK_DEFAULT_PATH);
			}
		}
		else
		{
			CString strMsg;
			if (pGlobalDoc->m_nSelectedLanguage == KOREA)
			{
				AfxMessageBox(_T("Light Lock : ±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄∏∏ / ø£¡ˆ¥œæÓ∏∏ ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."), MB_ICONSTOP);
				SaveLog(strMsg);
				SaveLog(_T("Light Lock : ±««—¿Ã æ¯Ω¿¥œ¥Ÿ. ∞¸∏Æ¿⁄/ø£¡ˆ¥œæÓ∏∏ Ω∫∆Â ¿˙¿Â¿Ã ∞°¥…«’¥œ¥Ÿ."));
			}
			else
			{
				AfxMessageBox(_T("Light Lock : Access denied. can't save preset spec"), MB_ICONSTOP);
				SaveLog(strMsg);
				SaveLog(_T("Light Lock : Access denied. can't save preset spec"));
			}
		}
	}*/
//}





void CDlgSpec::OnBnClickedOk()
{
	// TODO: ø©±‚ø° ƒ¡∆Æ∑— æÀ∏≤ √≥∏Æ±‚ ƒ⁄µÂ∏¶ √ﬂ∞°«’¥œ¥Ÿ.
	CDialog::OnOK();
}


BOOL CDlgSpec::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ø©±‚ø° √ﬂ∞° √ ±‚»≠ ¿€æ˜¿ª √ﬂ∞°«’¥œ¥Ÿ.
	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	SetForegroundWindow();

	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // øπø‹: OCX º”º∫ ∆‰¿Ã¡ˆ¥¬ FALSE∏¶ π›»Ø«ÿæﬂ «’¥œ¥Ÿ.
}

void CDlgSpec::Init()
{
	m_Spread.SetParentWnd(this, IDC_FPSPREAD_SPEC1);
	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	m_Spread.SetScrollBarStyle(SS_SCROLLBARSTYLE_CLASSIC);
	m_Spread.SetBool(SSB_HORZSCROLLBAR, 0);

	if (m_hDlgSpecBkBrush == NULL)
	{
		m_hDlgSpecBkBrush = CreateSolidBrush(RGB(183, 183, 183));
	}
	else
	{
		DeleteObject(m_hDlgSpecBkBrush);
		m_hDlgSpecBkBrush = CreateSolidBrush(RGB(183, 183, 183));
	}

	//GetDefaultSpecData();
	//DefineMasterLocalSpecColor();

	//InitTabCtrl();
	InitSpread();
	InitSpreadTab0();
	LoadSpreadDataTab0();

	m_Spread.Attach(ConvertTSpread(IDC_FPSPREAD_SPEC1));
	m_Spread.SetReDraw(TRUE);

	//SetSpecAccess(pGlobalView->m_nUserID); // syd-20100115

	//if (AoiParam()->m_bFontRead[pGlobalDoc->m_nSelectedLanguage])
	//{
	//	HFONT hfont = CreateFont(12, 0, 0, 0, 700, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfCharSet, 0, 0, 0, 0, AoiParam()->m_Language[pGlobalDoc->m_nSelectedLanguage].lfFaceName);
	//	LOGFONT lf;
	//	if (GetObject(hfont, sizeof(LOGFONT), &lf))
	//	{
	//		m_Spread.SetTextTip(2, 100, &lf, 0xFFFF, 0x800000);
	//	}

	//	if (hfont)
	//		DeleteObject(hfont);
	//}
	//else
	//{
	//	HFONT hfont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);// ANSI_VAR_FONT); //by khc 20070623
	//	if (hfont)
	//	{
	//		LOGFONT lf; //get the complete LOGFONT describing this font
	//		if (GetObject(hfont, sizeof(LOGFONT), &lf))
	//		{
	//			m_Spread.SetTextTip(2, 100, &lf, 0xFFFF, 0x800000);
	//		}
	//	}
	//}

	m_Spread.SetCellNoteIndicator(0);
	m_Spread.SetReDraw(TRUE);

}

