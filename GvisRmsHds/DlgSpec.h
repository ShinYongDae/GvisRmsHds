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

#define SPREAD_GROUP_COLOR		RGB(235,255,255)
#define SPREAD_GROUP_COLOR1		RGB(252,255,215)
#define SPREAD_GROUP_COLOR2		RGB(237,254,231)
#define SPREAD_GROUP_COLOR3		RGB(255,244,231)
#define SPREAD_GROUP_COLOR4		RGB(254,236,188)
#define SPREAD_GROUP_COLOR5		RGB(210,240,155)

#define DEFAULT_PANEL_SIZE_X 410
#define DEFAULT_PANEL_SIZE_Y 510

// CDlgSpec 대화 상자입니다.

class CDlgSpec : public CDialog
{
	DECLARE_DYNAMIC(CDlgSpec)

	// spec

	// Spec Line Group
	double	m_fNominalLine;
	double	m_fRealNormLine;
	double	m_fMinCheckWidth;
	int     m_nNickNGFilterPercent[15];
	int	    m_nExcsNGFilterPercent[15];
	int	    m_nSpaceNGFilterPercent;
	float   m_fSpWdDeltaOuterGradViolation;   //20090405 hjc
	float   m_fSpWdDeltaGradViolation;
	float   m_fFineMinSpWidth;	//121226 hjc add
								//----------
	CString	m_strNick[15];
	int		m_nNickPercent[15];	//150413 hjc add
	int		m_nFineNickPercent[15];
	int		m_nNickGray;	//measure gray
	int		m_nOpenGray;	//150410 hjc add
	int		m_nHalfSideNickDiffBrightGray;	//150413 hjc add
	int		m_nHalfSideNickDiffDarkGray;
	CString	m_strProtrusion[15];
	int		m_nProtrusionPercent[15];
	int		m_nFineProtrusionPercent[15];
	int		m_MinSpGray;
	CString	m_strMinSP;
	int		m_nMinSPPercent;
	int     m_nNeibSpGrayDiff;	//20090412 hjc
	int     m_nUSDarkGrayMinus;	//150413 hjc add
	double	m_fMinSpWidth;
	int		m_nLeadOpenGray;
	double	m_fTollerance;
	CString	m_strThetaAlign;
	double	m_fCompPADLen;

	//20090216 Spec Fines
	//170403 hjc add
	int		m_nFineNickGray;
	int		m_nFineOpenGray;
	int		m_nFineHalfSideNickDiffBrightGray;
	int		m_nFineHalfSideNickDiffDarkGray;
	//170403 hjc add end
	double	m_fFineMinCheckWidth;
	CString	m_strFineNick[15];
	CString	m_strFineProtrusion[15];
	int     m_nFineNickNGFilterPercent[15];
	int	    m_nFineExcsNGFilterPercent[15];
	float   m_fFineLineWdDeltaGradViolation[15];
	float   m_fFineExcsWdDeltaGradViolation[15];

	// syd-091008
	int		m_nFineLineWidthGroupNum;
	float	m_fFineLineWidthGroup[15];
	float   m_fFineNarrowTraceViolation[15];
	float   m_fFineWideTraceViolation[15];
	//-----------------------------

	//20090228 hjc add Edges
	int     m_nPadEdgeNickGray;
	int		m_nPadEdgeNeibGrayDiff;	//120105 hjc add
	int		m_nPadEdgeBADiffDarkGray;
	float   m_fPadEdgeNickWdDeltaGradViolation;
	float   m_fPadEdgeExcsWdDeltaGradViolation;
	int     m_nPadVDEdgeGray;    //20090412 hjc
	float   m_fPadVDEdgeWdDeltaGradViolation;	 //20090412 hjc

												 //111214 hjc add
	int     m_nHoleEdgeNickGray;
	int		m_nHoleEdgeNeibGrayDiff;	//120109 hjc add
	float   m_fHoleEdgeNickWdDeltaGradViolation;
	float   m_fHoleEdgeExcsWdDeltaGradViolation;

	int     m_nViaEdgeNickGray;
	int		m_nViaEdgeNeibGrayDiff;		//120109 hjc add
	float   m_fViaEdgeNickWdDeltaGradViolation;
	float   m_fViaEdgeExcsWdDeltaGradViolation;
	//---------------------

	float   m_fLineWdDeltaGradViolation[15];
	float   m_fExcsWdDeltaGradViolation[15];

	int		m_nLineWidthGroupNum;
	float	m_fLineWidthGroup[15];
	float	m_fLineWidthGroupLower[15];

	float   m_fNarrowTraceViolation[15];
	float   m_fWideTraceViolation[15];

	// 20170111 jjjj with hjc
	// Spec PAD BALLs	//20170112 hjc
	CString	m_strPadBallPrec;		//PAD
	CString	m_strLP_Prec;			//Large PAD
	CString	m_strSP_Prec;			//Space PAD		
	CString	m_strSPExt_Prec;		//Space PAD Ext	
	CString	m_strFPad_Prec;			//Fine PAD		
	CString m_strARLand_Prec;	    //ARLand		
	CString	m_strCO2Land_Prec;		//CO2Land		
	CString	m_strPadTip_Prec;		//PAD Tip		
									//20170112 hjc end

	CString m_strCO2LandAlignMode;	//20100322 hjc
	int		m_nIsLandGray;
	int		m_nIsLandExtGray;		//20090412 hjc
	int		m_nHoleLandVoidGray;	//20100322 hjc
	int		m_nCO2LandVoidGraySpec; //20100322 hjc 
	double	m_fARLandMin;
	double	m_fPADTipMin;
	double  m_fCO2LandMin;		//20100322 hjc
	double	m_fVDPadMin;
	double	m_fIsLandMin;
	double	m_fIsLandExtMin;		//20090412 hjc
	int		m_nCCLGray;				//jun 20120903 for LG_CCL-Inspector
	float	m_fCCLDefSize;
	float	m_fCCLCircularity;
	int		m_nPinHoleGray;
	int     m_nPADVoidGray;
	double	m_fPinHoleMin;
	double	m_fPADVoidMin;
	int     m_nFinePADVoidGraySpec;		//20090419 hjc
	float   m_fVDLocationTolerance;		//20090419 hjc
	float   m_fFineVDPadMin;		//20090419 hjc

									// Holes
	double	m_fHoleTolerance;
	CString	m_strHolePrec;
	int		m_nHoleOpenGray;
	int		m_nHoleMissingGray;
	int		m_nHoleDefSize;

	//20090311 hjc add
	float   m_fHoleDiaLower;
	float   m_fHoleDiaUpper;
	int     m_nHoleInnerGray;
	//-------

	// CO2
	int		m_nCO2MissingGray;
	int		m_nCO2HoleNum;
	int		m_nCO2OpenGray;
	//	double	m_fOpenCO2Len;
	int		m_nCO2MisAgnGray;
	int		m_nCO2MisAgnDefPercent;

	// Others
	CString	m_cboPTMOD_SIZE;
	CString m_strSelectVaccum;	//20100210 hjc add
	double	m_fDefMaskSize;
	double	m_fNearDefLen;
	int		m_nAlignTolerance;
	double m_dPanelSizeX;
	double m_dPanelSizeY;


	int m_nLockedSpecNickDiffBrightGrayUpperLimit;	//150413 hjc add
	int m_nLockedSpecNickDiffBrightGrayLowerLimit;
	int m_nLockedSpecNickDiffDarkGrayUpperLimit;
	int m_nLockedSpecNickDiffDarkGrayLowerLimit;
	int m_nLockedSpecExcsGrayLowerLimit;
	int m_nLockedSpecExcsGrayUpperLimit;
	int m_nLockedSpecLeadOpenGrayUpperLimit;
	int m_nLockedSpecLeadOpenGrayLowerLimit;
	double m_fLockedSpecMinChkWidthUpperLimit;
	double m_fLockedSpecMinChkWidthLowerLimit;
	int m_nLockedSpecExcsNGFilterPercentUpperLimit;
	int m_nLockedSpecExcsNGFilterPercentLowerLimit;
	int m_nLockedSpecMinSpGrayUpperLimit;
	int m_nLockedSpecMinSpGrayLowerLimit;
	int m_nLockedSpecNeibSpGrayDiffUpperLimit;
	int m_nLockedSpecNeibSpGrayDiffLowerLimit;
	double m_fLockedSpecMinSpWidthUpperLimit;
	double m_fLockedSpecMinSpWidthLowerLimit;
	int m_nLockedSpecSpaceNGFilterPercentUpperLimit;
	int m_nLockedSpecSpaceNGFilterPercentLowerLimit;

	int m_nSpecComboIndex;

	//20210629 lgh add
	int m_nCharInspectionGray;
	double m_dCharRegionUpperPercent;
	double m_dCharRegionLowerPercent;

	BOOL m_PADARFlag;
	BOOL m_PADCO2Flag;
	BOOL m_PADTipFlag;
	BOOL m_PADSmFlag;
	BOOL m_PADLgFlag;
	BOOL m_PADSpaceFlag;


	void InitSpecParam();
	void InitSpecTempParam();
	// end spec


	// Tab
	long m_lOldSelectRow[8]; // Tab 6ea
	long m_lNewSelectRow[8]; // Tab 6ea
	long m_lChangedDataSpreadCellPos[8]; // Tab 6ea

	void InitTab();
	// end Tab


	TSpreadEx		m_Spread;
	HBRUSH			m_hDlgSpecBkBrush;
	CString			m_strMainFont;
	CFont			m_FontOfTabCtrl;
	int				m_nTabNum;
	float			m_fDataFontSize;
	LOGFONT			m_Language;
	BOOL			m_bEnableCheckBox;

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

	void InitTabCtrl();
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
