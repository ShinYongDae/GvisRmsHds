#pragma once

#include "Spread8/Include/Ssdllmfc.h"
#include "afxwin.h"
#include "afxcmn.h"

#ifdef _WIN64
#ifdef UNICODE
#pragma comment(lib,"Spread8/Lib/SPR64DU80")
#else
#pragma comment(lib,"Spread8/Lib/SPR64D80")
#endif
#else
#ifdef UNICODE
#pragma comment(lib,"Spread8/Lib/SPR32DU80")
#else
#pragma comment(lib,"Spread8/Lib/SPR32D80")
#endif
#endif


//Spread Sheet Cell Type
#define TYPE_DEFAULT		1
#define TYPE_COMBO			8
#define TYPE_CHECK			10
#define TYPE_BUTTON			7
#define TYPE_STATIC			5

#define SS_ALIGN_LEFT		0
#define SS_ALIGN_RIGHT		1
#define SS_ALIGN_CENTER		2

// CDlgSpec 대화 상자입니다.

class CDlgSpec : public CDialog
{
	DECLARE_DYNAMIC(CDlgSpec)

	TSpreadEx	m_Spread;
	HBRUSH m_hDlgSpecBkBrush;


	void Init();
	void Close();

	void AtDlgShow();
	void AtDlgHide();
	void AutoChangeSpecControl(int nDefType, int nRecordK);
	void RefreshDataColor(int nTabNum);
	void SetSpecAccessItem(int nTab, int nRow);
	CString CheckLock(int tab, int Row, CString strVal);
	void LockingSpec();
	void ChangeSpecFromEasy(int Col, int Row);
	void DisplaySpec(void);
	CString GetSpecName(int tab, int row);
	int Level2Number(CString strLvl);
	void DecisionPixelAdjust(CString strName, int nLevelVal, int PrecisionStepSize, int* nHighest, int* nVeryHigh, int* nHigh, int* nNormal, int* nLow, int* nVeryLow, int* nLowest);
	BOOL GetDefaultSpecData();

	void DisplaySpread(int nTabNum);
	void ChangeSpecSpreadCaption(int nTab);
	void RefreshSheetOnChanging();
	void DisplayChangedData();
	void SetGroupBackColor();
	void DisplaySelectRow();

	void InitSpread();
	void InitSpreadTab0();
	void InitSpreadTab1();
	void InitSpreadTab2();
	void InitSpreadTab3();
	void InitSpreadTab4();
	void InitSpreadTab5();
	void InitSpreadTab6();
	void InitSpreadTab7();

	void TabChange(int nTap);
	void TabRestore();

	void RecoverOriginData();
	void LoadOriginDataTab(int nTabNum);
	void LoadOriginDataTab0();
	void LoadOriginDataTab1();
	void LoadOriginDataTab2();
	void LoadOriginDataTab3();
	void LoadOriginDataTab4();
	void LoadOriginDataTab5();
	void LoadOriginDataTab6();
	void LoadOriginDataTab7();

	void LoadSpreadDataTab0();
	void LoadSpreadDataTab1();
	void LoadSpreadDataTab2();
	void LoadSpreadDataTab3();
	void LoadSpreadDataTab4();
	void LoadSpreadDataTab5();
	void LoadSpreadDataTab6();
	void LoadSpreadDataTab7();
	void CheckOriginDataTab0();
	void CheckOriginDataTab1();
	void CheckOriginDataTab2();
	void CheckOriginDataTab3();
	void CheckOriginDataTab4();
	void CheckOriginDataTab5();
	void CheckOriginDataTab6();
	void CheckOriginDataTab7();

public:
	CDlgSpec(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSpec();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SPEC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_DefaultSpecCombo;
	CTabCtrl m_tabDlgInspection;

	afx_msg LRESULT OnClickFpspread1(WPARAM, LPARAM);
	afx_msg LRESULT OnDblClickFpspread1(WPARAM, LPARAM);
	afx_msg LRESULT OnComboCloseUpFpspread1(WPARAM, LPARAM);
	afx_msg LRESULT OnLeaveCellFpspread1(WPARAM, LPARAM);
	afx_msg LRESULT OnButtonClickedFpspreadDown(WPARAM, LPARAM);
	afx_msg LRESULT OnKeyDownFpspread1(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseDownFpspread1(short Button, short Shift, long x, long y);

	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonSaveDefaultLocalSpec();
	afx_msg void OnSelchangeComboDefaultSpecCombo();
	afx_msg void OnDropdownComboDefaultSpecCombo();
};
