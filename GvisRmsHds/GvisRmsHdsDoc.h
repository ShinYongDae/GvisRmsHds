
// GvisRmsHdsDoc.h : CGvisRmsHdsDoc 클래스의 인터페이스
//


#pragma once

#define MAX_HOLE_TYPE				64
#define LIGHT_CHANNEL_NUM			16
#define	MAX_CLIENT					6	// Maximum Client number
#define MAX_MASTERBK_LOC_NUM		10	//ndy070620 - for Multi Master BackUp

typedef enum 
{
	INSP_MODE_NORMAL = 0, INSP_MODE_RED, INSP_MODE_BLUE, INSP_MODE_COUNT, INSP_MODE_BLUE_RED = 10
} INSPECTION_MODE;


typedef struct tagSRO
{
	double dDiameterSpecUpper;//직경 크기 스펙 +-
	double dDiameterSpecLower;//직경 크기 스펙 +-
	double dDiameterCalibUm; // 외부 보정량
	double dCircleShiftSpecUm;// 편심 허용량
	double dCompactnessSpec;// 원형도 스펙
	double dInnerPadDotDefectSpecUm;//내부 불량 크기
	double dAreaPercent;// 면적 비율
	float   fModifiedHoleDiameter;	// um	// 20120229 ljh
	float   fHoleDiameter;

	int nSROGray;
	int nPrecision;

}SROSpec;

typedef struct tagInsVia
{
	int nViaInnerDefGray;	//20191122 add start // VH 없음 밝기
	int nViaInnerDefSize;  //VH 없음 크기
	int nViaMissingGray;
	int nViaMissingSize;   //20191122 add end
	float fViaHoleTolerance; // 홀편심한도 (um) //4
	float fViaHoleDiaUpperPercent; // 크기 상한 (%) //4
	float fViaHoleDiaLowerPercent; // 크기 하한 (%) //4 
	float m_fTaperWidth;
	float m_fInnerDiamterWidthDiff;
	float m_fInnerCompactness;
	int nViaInnerEdgeGray; //Inner Edge Gray 홀내 에지 밝기[Gray] // 4
	float fViaInnerEdgeSizePxl; // Inner Edge Size 홀내 에지 크기 (Pixel) // 4
	int nViaOuterEdgeGray; //	Inner Edge Gray 홀외곽 에지 밝기[Gray] // 4
	float fViaOuterEdgeSizePxl; // 	Inner Edge Size 홀외곽 에지 크기 (Pixel) //4
}InsViaSpec; //28 byte

typedef struct
{
	InsViaSpec ViaSpec; //170317 lgh
	SROSpec SRSpec[MAX_HOLE_TYPE];
	BOOL bLargeAlignShift;
	BOOL bRoughSurface;	//20220823 add

	BOOL m_bCheckProtFromSpaceWidth;

	double fNominalLineWidth;	// Norminal Line width of design time
	double fRealNominalLineWidth; // Real Norminal Line width of run time
	double fMinLineWidth;		// Minimum Check Width in [um]

	float fNickRatio;
	float fExcsRatio;
	float fSpaceRatio;

	int    nNickGraySpec;		// Measure Spec
	int    nOpenGraySpec;		//150410 hjc add
	char   szNickSize[15][64];		// detect precision(string) of nick defect
	int    nNickPercent[15];		// detect precision(%) of nick defect 

	int    nMinSpaceGraySpec;	// gray spec of minimum space violation defect detecttion
	char   szMinSPSize[15];		// detect precision(string) of minimum space violation defect
	int    nMinSPPercent;		// detect precision(%) of PAD minimum space violation defect

	int    nThinIter;			// iteration value of thinning to pattern 
	int    nMinSpaceThinIter;	// iteration value of thinning to minimum space   

	double fMinSpWidth;			// minimum space width

	BOOL   bOneSideCheckUShort;  // 2007.3.11 ljg add,

	char   szProtrusionSize[15][64];// detect precision(string) of protrusion defect
	int    nProtrusionPercent[15];  // detect precision(%) of protrusion defect

	int    nInspectLight[LIGHT_CHANNEL_NUM][INSP_MODE_COUNT];

	//161228 lgh for ibiden 
	int    nDirectLight1[INSP_MODE_COUNT];		// illumination level of direct light system #1(Left side) 0
	int    nDirectLight2[INSP_MODE_COUNT];		// illumination level of direct light system #2(Right side) 
	int    nDiffuse1LightL[INSP_MODE_COUNT];		// illumination level of indirect light system #1(Right side) 
	int    nDiffuse1LightR[INSP_MODE_COUNT];		// illumination level of indirect light system #2(Right side)
	int    nDiffuse2LightL[INSP_MODE_COUNT];		// illumination level of indirect light system #1(Right side) 
	int    nDiffuse2LightR[INSP_MODE_COUNT];		// illumination level of indirect light system #2(Right side) 

													//111110 hjc add
	int    nDirectLight1N[INSP_MODE_COUNT];		// illumination level of direct light system #1(Left side) 
	int    nDirectLight2N[INSP_MODE_COUNT];		// illumination level of direct light system #2(Right side) 
	int    nDiffuse1LightL2[INSP_MODE_COUNT];		// illumination level of indirect light system #1(Right side) 
	int    nDiffuse1LightR2[INSP_MODE_COUNT];		// illumination level of indirect light system #2(Right side)
	int    nDiffuse2LightL2[INSP_MODE_COUNT];		// illumination level of indirect light system #1(Right side) 
	int    nDiffuse2LightR2[INSP_MODE_COUNT];		// illumination level of indirect light system #2(Right side)

	int    nLightChValue13[INSP_MODE_COUNT];		// 13
	int    nLightChValue14[INSP_MODE_COUNT];		// 14

													//20210408 KSJ ADD
	int    nLightChValue15[INSP_MODE_COUNT];		// 15
	int    nLightChValue16[INSP_MODE_COUNT];		// 16


	int    nFocusAdjustLight[32];		// illumination level of indirect light system #2(Right side) 
	int    nAlignLight[32];		// illumination level of indirect light system #2(Right side) 



								//end

	double fDefMaskSize;		// double type defect mask size
	int    nDefMaskSize;		// integer type defect mask size

	double fNearDefLen;			// double type near defect length
	int    nNearDefLen;			// integer type near defect length

	int    nLeadOpenGray;		// gray spec of lead portion

	short  nUseManualLUT[INSP_MODE_COUNT];       // 20080326 ljg add
	short  nThreshold[INSP_MODE_COUNT];
	short  nPTModThreshold[INSP_MODE_COUNT];
	short  nPTModUpperGray[INSP_MODE_COUNT];		//20160921-ndy add
	short  nPTModLowerGray[INSP_MODE_COUNT];		//20160921-ndy add
	short  HistoThreshold[INSP_MODE_COUNT];      // 20090721 ljg add
	short  nLowerGray[INSP_MODE_COUNT];
	short  nUpperGray[INSP_MODE_COUNT];

	short  nHoleInnerGray;

	// ---------------------------------------
	// Related RLE Precision Spec  20170111 mod by ljg

	int   m_nCadEtchedPixels;

	int   m_nCricSPadOffset;
	int   m_nCricLPadOffset;
	int   m_nCricSpaceOffset;
	int   m_nCricSpaceExtOffset;  // 20170111 jjjj
	int   m_nCricARLandOffset;
	int   m_nCricCO2LandOffset;
	int   m_nCricPTipOffset;
	int   m_nCricPadFineOffset;  // 20170111 jjjj

	char  szPADRLPrecName[64];       // Pad
	char  szLPADRLName[64];          // Large PAD
	char  szSPRLName[64];            // Space PAD 
	char  szSPACEEXTRLName[64];      // Space Ext PAD   // 20170111 jjjj
	char  szPADFine_PrecName[15];	 // Fine PAD
	char  szARLandPrecName[64];      // ARLand
	char  szCO2LandPrecName[64];     // CO2Land
	char  szPADTipPrecName[64];      // PadTip

	int   PADRL_Prec;
	int   LPADRL_Prec;
	int   LSpaceRL_Prec;
	int   SpaceExtRL_Prec;          // 20170111 jjjj
	int   ARLand_Prec;
	int   CO2Land_Prec;
	int   PADTip_Prec;
	int	  PADFine_Prec;		       // FinePAD

								   //	int   nCO2Land_Prec;	       // 20100322 hjc add, 20170111 buf fix, delete, nCO2Land_Prec -> CO2Land_Prec

	int   nRLEPrecisionStepSize;	//150623 hjc add

									// Related RLE Precision Spec
									// ---------------------------------------

	char  szHoleRLPrecName[10];      // Inner Hole RLE
	double fHoleTolerance;     // double type hole tolerance

	int    nHoleRLPrec;			// Hole 내부 검퍊E불감큱E크콅E
	int    nHoleMissingGray;		// gray spec of hole defect detecttion
	int    nHoleOpenGray;		// Hole Open Gray
	int    nHoleDefNum;         // Hole 내부 불량크콅E

	int	   nVDrillDiffBrightGray;	//150606 hjc mod nVDrillPixelGray => nVDrillDiffBrightGray
	int    nVDrillDiffDarkGray;		//150606 hjc add
	int    nVDLocationTolerancePixel;

	int    nCO2MissingGray;
	int    nCO2MisAgnGray;
	int    nCO2HoleNum;
	int    nCO2MisAgnDefPercent;
	int    nCO2OpenGray;
	int    nCO2InOutGrayDiff;
	int	   nCO2InnerBrightDefPercent;
	int	   nCO2InnerSaturationGray;
	float  fCO2InnerBrightSrchDiaRatio;
	float  fCO2InnerRoughness;
	float  fCO2InnerRoughnessSrchDiaRatio;

	int    nVHEdgeThrDiffGray;
	int    nVHBreakOutGray;
	int    nVHDissmearGray;
	int    nVHContiBreakOutNum;
	char   szVHMode[10];

	int    nSpaceNGFilterPercent;
	int    nNickNGFilterPercent[15];		// Nick NG Filter
	int    nExcsNGFilterPercent[15];		// Excs NG Filter

	int    nIsLandMode;
	char   szIsLandMode[10];
	double fIsLandMin;
	double fIsLandExtMin;	//20090412 hjc
	int    nIsLandMin;
	int    nIsLandExtMin;	//20090412 hjc
	int    nIsLandGraySpec;
	int    nIsLandExtGray;	//20090412 hjc	
	int    nPinHoleGraySpec;
	int    nPADVoidGraySpec;

	int    nCCLGray;	//jun 20120903 for LG_CCL-Inspector
	float  fCCLDefSize;
	float  fCCLCircularity;

	int    nHoleLandVoidGray; //20100322 hjc add

	int    nPinHoleMode;
	char   szPinHoleMode[10];
	double fARLandMin;
	double fPADTipMin;
	double fPinHoleMin;
	double fPADVoidMin;
	int    nARLandMin;
	int    nPADTipMin;
	int    nPinHoleMin;
	int    nPADVoidMin;

	int    nCO2LandMin;
	int    nCO2LandVoidGraySpec;

	char   szCO2LandAlignMode[10];	//20100322 hjc add
	float  fVDLocationTolerance;
	double fVDPadMin;
	int    nVDPadMin;
	int    nCO2LandAlignMode;	//20100322 hjc add

								//20100322 hjc add CO2 Spec
	float fCO2LandMin;
	//end

	// 	char   szVDPadPrecName[10];
	double fVDPadPrecName;
	int    nVDTemplete_Prec;

	// 2006.7.3 add 
	char   PCBProcessMethod_Name[20];    // 기판제조공법

	double fFocusPos;       // 2005,10,15일 Actual Focus pos. = Original Focus pos. + User/Laser thickness
	double fFocus2Pos;
	double fMagPos;			// 2005,10,31일 추가,khc
	double fInspZoomPos;			// 2013,05,02일 추가,syd
	double fIrisPosDefault;
	// 2001.8.16 Temp 
	double fVariZoomPos;    // 1 camera 방식 2005,10,15일 short?E【?double?E막?변컖Ekhc

	int    nAlignTolerance;	// Alignment tolerance
	char   strSelectVaccum[10];
	int    nSelectVaccum;

	CString m_strRefLoc[MAX_CLIENT];
	CString m_strReferShared;
	CString m_strAOIRefer;
	CString m_strRefDataPCName;   // 20100706 add

	int	    m_nMasterBKNum;			//ndy070620 - for Multi Master Data
	CString m_strMasterBK[MAX_MASTERBK_LOC_NUM][MAX_CLIENT];	//ndy070620 - for Multi Master Data

	int    nPTModelSize;   // Pattern model size

	BOOL   bGTCShakeExtend;
	int    nGTCShakeNumber;
	int    nResizingSize;

	int    nMasterLoc;    // Master Location

	float  fAICLTolerance;	//140826 hjc add
	int    nBoundChkGray;	//150806 hjc add
	int    nShrinkSize;		//150827 hjc add
	float  fOEExceptSpaceLen;	//150625 hjc add
	float  fOEExceptLen;
	float  fSROEExceptLen;
	float  fARCO2JuncExceptLen;

	CString m_strCADImgPath;
	CString m_strCADImgBackUpPath;

	double fHoleFillExt;
	int    nHoleFillExt;

	//20100323 hjc add
	double fCO2HoleFillExt;
	int    nCO2HoleFillExt;

	float  fPADTipNickPrecSpec;

	int   m_nPtCreateExtLen;
	int   nBestPMIndex;         // 최픸E에칭(축소) 넘퉩E

								//20090216 Spec Fines
								//170403 hjc add
	int    nFineNickGraySpec;
	int    nFineOpenGraySpec;
	int	   nFineHalfSideNickDiffBrightGray;
	int	   nFineHalfSideNickDiffDarkGray;
	//170403 hjc add end
	float  fFineMinLineWidth;
	char   szFineNickSize[15][64];
	char   szFineProtrusionSize[15][64];

	int    nFineNickNGFilterPercent[15];
	int    nFineExcsNGFilterPercent[15];

	float  fFineLineWdDeltaGradViolation[15];
	float  fFineExcsWdDeltaGradViolation[15];

	int		nFineLineWidthGroupNum;
	int		nFineWideTraceViolationPix100[15];	//20091008 hjc add
	int		nFineNarrowTraceViolationPix100[15];
	float	fFineLineWidthGroup[15];
	float	fFineWideTraceViolation[15];
	float	fFineNarrowTraceViolation[15];
	int  	nFineLineWidthGroupPix100[15];

	//20090216 chg
	int    nFineNickPercent[15];
	int    nFineProtrusionPercent[15];
	//-------------------------------------

	float fHoleDiaUpper;
	float fHoleDiaLower;

	float fHoleLandSizeRatio;        // 2007.5.1 ljg add

	int   nAREdgeDiffGray;
	int   nARBreakCnt;
	int	  nHalfSideNickDiffBrightGray;	//150413 hjc add
	int	  nHalfSideNickDiffDarkGray;

	float fLineWdDeltaGradViolation[15];
	float fSpWdDeltaOuterGradViolation;		  //20090405 hjc	
	float fSpWdDeltaGradViolation;        // 20090117 ljg add
	float fExcsWdDeltaGradViolation[15];

	int		nLineWidthGroupNum;

	float	fLineWidthGroupLower[15]; // 170524
	float	fLineWidthGroup[15];
	float	fWideTraceViolation[15];
	float	fNarrowTraceViolation[15];

	float   fLineWidthGroupAdjusted[15]; //161128 lgh


	int    	nLineWidthGroupPix100[15];// 만들어 놓고 안 쓰는 스펙 1
	int		nWideTraceViolationPix100[15];	// 만들어 놓고 안 쓰는 스펙 2
	int		nNarrowTraceViolationPix100[15]; // 만들어 놓고 안 쓰는 스펙 3	

	float fHoleEdgeExcsWdDeltaGradViolation;  // 20080517
	float fHoleEdgeNickWdDeltaGradViolation;  // 20080517
	float fViaEdgeNickWdDeltaGradViolation;   // 20080928
	float fViaEdgeExcsWdDeltaGradViolation;   // 20080928
	float fPadEdgeExcsWdDeltaGradViolation;   // 20080928
	float fPadEdgeNickWdDeltaGradViolation;   // 20080928

	int nHoleEdgeNickGray;  // 20080928
	int nHoleEdgeNeibGrayDiff;	//120109 hjc add
	int nPadEdgeNickGray;   // 20080928
	int nPadEdgeNeibGrayDiff;	//120105 hjc add
	int nPadEdgeBADiffDarkGray;		//140127 hjc add
	int nPadVDEdgeGray;		//20090412 hjc	
	int nViaEdgeNickGray;   // 20080928
	int nViaEdgeNeibGrayDiff;	//120109 hjc add
	float fPadVDEdgeWdDeltaGradViolation;   //20090412 hjc

	double	fFinePADVoidMin;	// 20080525		//090324-ndy
	int		nFinePADVoidMin;
	short	nFinePADVoidGraySpec;  // 20080525

	float	fPADNickDentWidthRatio;    // 2007.11.22 kjj add
	float	fPADNickExcsWidthRatio;    // 2007.11.22 kjj add
	float	fNickDentWidthRatio;    // 2007.11.22 kjj add
	float	fNickExcsWidthRatio;    // 2007.11.22 kjj add

	float   fFineMinSpWidth;	//121226 hjc add

	int		nSpLgDarkGrayMinus;
	int		nDarkSpaceMin;
	int     nNeibDarkGrayTot;	//130528 hjc add
	int     nNeibBrightGrayTot;

	int     nSpBoundSearchLimitPixel;  // 130925 ljg add

	int		nNeibSpGrayDiff;		//20090405 hjc
	int		nUSDarkGrayMinus;
	int     nVDNeibPMMinMaxDiffGray;	//131216 hjc add, sp81
	int     nMeasureNum;		//150921 hjc add

	int		nBrightPinHoleGrayPlus;  // 20090324 ljg
	int		nDarkPinHoleGrayMinus;
	float	fBrightPinHoleNeibGrayPlusApplyRatio;  //20090405 hjc
	float	fDarkPinHoleNeibGrayMinusApplyRatio;  //20090405 hjc
	float   fSpMMDiffAlphaPlus;		//150413 hjc add
	int		nBrightDarkPinHoleMinPixel;
	float	fPinHoleBreadthLimitPixel;
	float	fPinHoleCompacenessLimit;
	int		nPinHoleClosingIteration;
	int		nPinHoleOpeningIteration;  // 20090326 ljg NY-add
	int		nPadDefClosingIteration;	// 120501 jsy
	int		nPadDefOpeningIteration;
	int		 nBrightPADDefGrayPlus;
	int		nDarkPADDefGrayMinus;  // 20090324 ljg
	int     nExcludePadDefEdgePixel;	//130529 hjc add for Relative spec
	int     nExcludePinHoleEdgePixel;   //130529 hjc add for Relative spec

	float   fRlsPadDefSize;
	float   fRlsPinHoleDefSize;
	float	fPinHoleMergeDistance;  // 20090512 add
	int		 nPinHoleMergeDistancePixel;

	int		 nInnerDefArea;
	int		nVHRadiusMask;
	float	fCheckVHLandRadiusRatio;
	int		nCheckVHLandDefGray;
	int		nCheckVHLandDefSize;

	float	fVDRingWidthPixel;      // 20080430 add
	float	fVHRingWidthPixel;      // 120410 jsy

	BOOL	bUseVDRingWidthFilter;  // 20080430 add
	BOOL	bExtensionHoleSearch;	//20100517 hjc add
	BOOL    bInspLargeHole;		//130915 hjc add
	BOOL    bInspSmallHole;		//140325 hjc add
	/*
	float	fHoleLimitOfMaxDiameterPixel;	//20091117 add
	int     nLargeHoleBoundaryLimit;	//130726 hjc add
	int     nSmallHoleBoundaryLimit;	//140325 hjc add
	*/
	int	    nHoleMeasDiaSuccessivePixel;	//20160503 add
	int     nLargeCircle_Check_InnerOuter_Pixels;	//130726 hjc add
	int     nSmallCircle_Check_Inner_Pixels;	//140325 hjc add
	int		nDiffDeltaPxlARCO2;			//141105 hjc add
	int     nVDHoleMinMaxDiffGrayPlus;	//120131 hjc add

	BOOL	bUseRawGrayPinHole;	//20080516 add
	BOOL	bUseRawGrayForIsland;	//20090412 hjc
	BOOL	bUseRawGrayPADDefect;	//20080516 add
									//20190729 add start
	BOOL	bUseNewRawGrayPADDefect;
	BOOL	bUseNewRawGrayPinHole;
	BOOL	bUseNewRawGrayForIsland;
	//20190729 add end
	BOOL	bUseLocalRleBlock;
	BOOL    bUseRelPinHoleRadient;	//130604 hjc add for Relative Pinhole logic

	int		nDimpleUpperGray;
	int     nDimpleLowerGray;
	int		nDimpleCopperMissNum;
	float	fDimpleCopperSearchRatio;
	int		nDimpleRingNum;

	//20090412 Island add
	int		nBrightIslandGrayPlus;
	int		nDarkIslandGrayMinus;
	//----------

	BOOL	bUseFixedPMId;  // 20090305 ljg
	int		nFixedPMId;      // 20090305 ljg
	BOOL	bExtensionSpaceTrace;	//111003 hjc add for youngjin
	int		nSpMinMaxDiffGray;	//111005 hjc add
	BOOL    bChkWideOpen;	//140425 hjc add
	int     nWideOpenPxl;
	BOOL	bChkTemplateMatch;	//20210818 add

								//20101201 hjc add
	int     nSPEdgeNickGray;
	float   fSPEdgeNickWdDeltaGradViolation;
	float   fSPEdgeExcsWdDeltaGradViolation;
	int     nSPEdgeGrayDiff;	//131123 hjc add

								//131031 hjc add
	int     nCoreNeutralZone;
	int     nCoreDiffGray;
	int     nCoreDefSize;
	//end

	//110701 hjc add
	BOOL    bPMImgThresholdEnhancement;
	float   fAdaptiveThresholdRatio;

	int     nEdgeSpecDownPxl;	//150817 hjc add

	int		nSpaceUnderLayerEffectGrayPlus; // 20090301 ljg
	int		nCenterlineOffsetTolerance;		//20230704 add
											//160330 hjc add
	int     nUnderLayerCutTh;
	int     nSpUnderLayerLowerGray;
	int     nSpUnderLayerUpperGray;
	float   fSpUnderLayerDefSize;
	//160330 hjc add end
	int		nLineWndBoundaryGrayMinus;	// 20090630 jsy
	int		nSpaceWndBoundaryGrayPlus;

	int		nScaleThetaAlignPoint;   // 20090710 ljg
	int		nPreAlignPTModelSize;    // 20090710 ljg

	int		nSudInOutLowerGray;		// 20100429 jsy
	BOOL	bImagePolarity;
	int		nSudInOutUpperGray;		// 20100429 ljh
	float	fSudInOutDefSize;

	//110620 hjc add
	BOOL    bCheckFiducialMark;
	float   fFMDArea;
	float   fFMDSizeX;
	float   fFMDSizeY;
	float   fFMDPtRangePlus;	//110621 hjc add
	float   fFMDPtScore;
	//end
	BOOL    bPtModelUsingTinyFeature;
	int     nTinyFeaturePitch;

	int     nUnderLayer;	//160330 hjc add
	float	fMLSResolution;			// 100708 ljh
	BOOL	bAutoMeasureLineSpace;	// 100708 ljh

	int		nBlobBlockNum;			// 100819 jsy
	BOOL	bPadTestRLRegionSaperate;	// 100819 jsy

	BOOL	bSkipChkInVDLine;	//110526 hjc add
	BOOL	bCheckSilverPasteVia;	//121128 hjc add
	int		nVHOutBreakCnt;	//121128 hjc add
	int     nVHTapingTolerence;	//20230508 add
	int     nVHTapingMinMaxDiff;	//20230627 add
	BOOL	bChkViaMultidia;		//20230628 add
	int     nVHInnerGray;			//20230711 add
	int     nVHMinMaxDiaRatio;			//20230713 add

	int		nBTViaMin;				//120515 jsy
	int		nBTVRingClosingNumber;
	int		nBTVGraySpecUpper;
	int		nBTVGraySpecLower;

	float	fLinkedDefectCntPix;	//121022 hjc add

	float	fPanelWidth;
	float	fPanelHeight;
	float	fInspectionWidth;
	float	fInspectionHeight;

	float SpaceNGFilterF;
	float NickNGFilterF;
	float ExcsNGFilterF;

	//150514 lgh add for scale	
	double dReferenceCamScaleX;
	double dReferenceCamScaleY;

	//20160108 ndy add - Start
	BOOL	bUseFinePinHoleInsp;
	int		nFinePinHoleRelativeGray;
	int		nFinePinHoleMaxSize;
	BOOL	bUseFineIslandInsp;
	int		nFineIslandRelativeGray;
	int		nFineIslandMaxSize;
	int		nFineIslandMaskSize;
	//20160108 ndy add - End
	int		nGradientUpperLimit;	//20230417 add start
	int		nGradientThreshold;
	int		nGradientMinSize;
	int		nPadLgGradientUpperLimit;
	int		nPadLgGradientThreshold;
	int		nPadLgGradientMinSize;
	BOOL	bUseRlsDarkGrayOnly;	//20230417 add end

									//170206 lgh
	int nAnalogGain[INSP_MODE_COUNT];
	int nSystemGain[INSP_MODE_COUNT];

	double dPanelSizeX;
	double dPanelSizeY;

	int nHighPeakGray;
	int nLowPeakGray;

	//20210629 lgh add
	int nCharInspectionGray;
	double dCharRegionUpperPercent;
	double dCharRegionLowerPercent;
	BOOL bEnableCharInspection;

	BOOL bApplySCurveEdge;
	BOOL bLightAverageOn;
	double dAvgLightValueRef;
	int nSysGainoffset;
	int nLightCheckKey;
	BOOL bNearDefLenDevide;
} SPEC_DATA;


class CGvisRmsHdsDoc : public CDocument
{
	BOOL LoadSpecPreset(CString nSelectString, BOOL bUseTempBuf);

protected: // serialization에서만 만들어집니다.
	CGvisRmsHdsDoc();
	DECLARE_DYNCREATE(CGvisRmsHdsDoc)

// 특성입니다.
public:
	SPEC_DATA SpecData;
	int m_nSpecNickGrayLowerLimit;
	int m_nSpecNickGrayUpperLimit;
	int m_nSpecOpenGrayLowerLimit;
	int m_nSpecOpenGrayUpperLimit;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CGvisRmsHdsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
