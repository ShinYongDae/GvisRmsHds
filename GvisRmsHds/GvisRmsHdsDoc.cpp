
// GvisRmsHdsDoc.cpp : CGvisRmsHdsDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "GvisRmsHds.h"
#endif

#include "GvisRmsHdsDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGvisRmsHdsDoc

IMPLEMENT_DYNCREATE(CGvisRmsHdsDoc, CDocument)

BEGIN_MESSAGE_MAP(CGvisRmsHdsDoc, CDocument)
END_MESSAGE_MAP()


// CGvisRmsHdsDoc 생성/소멸

CGvisRmsHdsDoc::CGvisRmsHdsDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_nSpecNickGrayLowerLimit = 10;
	m_nSpecNickGrayUpperLimit = 250;
	m_nSpecOpenGrayLowerLimit = 10;
	m_nSpecOpenGrayUpperLimit = 250;
}

CGvisRmsHdsDoc::~CGvisRmsHdsDoc()
{
}

BOOL CGvisRmsHdsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CGvisRmsHdsDoc serialization

void CGvisRmsHdsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CGvisRmsHdsDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CGvisRmsHdsDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGvisRmsHdsDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGvisRmsHdsDoc 진단

#ifdef _DEBUG
void CGvisRmsHdsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGvisRmsHdsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGvisRmsHdsDoc 명령

BOOL CGvisRmsHdsDoc::LoadSpecPreset(CString nSelectString, BOOL bUseTempBuf)	
{
	CString strPath, strData;
	CString strTitle, strIndex;
	TCHAR szData[1024];
	CString strTemp;
	CString strTitleMsg, strMsg;
	CFileFind find;
	BOOL bTempData;
	int idx;
	int i;
/*
	//20120629-ndy
	if (m_bUseLocalSpecPreset)
		strPath.Format(_T("%sSpecPreset\\%d\\%s.MSP"), m_strLocSpecDir, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), nSelectString);
	else
	{
		if (!m_bUseMultiPreset)	//130128 hjc add
			strPath.Format(_T("%sSpecPreset\\%d\\%s.MSP"), m_strIniSpecDir, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), nSelectString);
		else
			strPath.Format(_T("%sSpecPreset%02d\\%d\\%s.MSP"), m_strIniSpecDir, m_nMultiPresetNumber, (int)(round(SizeData[COMMON_PARAMETER].fPixelSize * 100)), nSelectString);
	}

	if (!find.FindFile(strPath))
		return FALSE;

	CString strCopy;

	strCopy.Format(_T("%sSpecPreset.msp"), m_strSharedDir);

	if (CopyFileRepeat(strPath, strCopy))
		strPath = strCopy;

	//Line Spec
	if (bUseTempBuf)
	{
		//170320 lgh add for insvia
		strTitle.Format(_T("Preset Spec InsVia"));
		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Shift Tolerance"), NULL, szData, sizeof(szData), strPath))
			SpecTempData.ViaSpec.fViaHoleTolerance = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Size Upper Size Limit"), NULL, szData, sizeof(szData), strPath))
			SpecTempData.ViaSpec.fViaHoleDiaUpperPercent = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Size Lower Size Limit"), NULL, szData, sizeof(szData), strPath))
			SpecTempData.ViaSpec.fViaHoleDiaLowerPercent = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Inner Edge Gray"), NULL, szData, sizeof(szData), strPath))
			SpecTempData.ViaSpec.nViaInnerEdgeGray = _ttoi(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Inner Edge Size Pixel"), NULL, szData, sizeof(szData), strPath))
			SpecTempData.ViaSpec.fViaInnerEdgeSizePxl = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Outer Edge Gray"), NULL, szData, sizeof(szData), strPath))
			SpecTempData.ViaSpec.nViaOuterEdgeGray = _ttoi(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Outer Edge Size Pixel"), NULL, szData, sizeof(szData), strPath))
			SpecTempData.ViaSpec.fViaOuterEdgeSizePxl = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Taper Width"), NULL, szData, sizeof(szData), strPath))
			SpecTempData.ViaSpec.m_fTaperWidth = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Inner Diameter"), NULL, szData, sizeof(szData), strPath))
			SpecTempData.ViaSpec.m_fInnerDiamterWidthDiff = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Inner Compactness"), NULL, szData, sizeof(szData), strPath))
			SpecTempData.ViaSpec.m_fInnerCompactness = _ttof(szData);

		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("Preset Meas Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nNickGraySpec = _ttoi(szData);
		else
			SpecTempData.nNickGraySpec = SpecData.nThreshold[0];

		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("Preset Nick Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nOpenGraySpec = _ttoi(szData);

		//170403 hjc add
		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Meas Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nFineNickGraySpec = _ttoi(szData);
		else
			SpecTempData.nFineNickGraySpec = SpecData.nNickGraySpec;

		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Nick Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nFineOpenGraySpec = _ttoi(szData);
		else
			SpecTempData.nFineOpenGraySpec = SpecData.nNickGraySpec;
		//170403 hjc add end

		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("Preset Lead Open Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nLeadOpenGray = _ttoi(szData);
#if CUSTOMER_COMPANY == UMTC
		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("Preset Min Line Width"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fMinLineWidth = _ttof(szData);
#endif

		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Min Space Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		{
			StringToChar(szData, SpecTempData.szMinSPSize);
		}

		BOOL bMLT = 0;
		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("New MultiLineSpec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			bMLT = _ttoi(szData);

		if (bMLT)
		{
			//멀티라인도 프리셋에 포함할 것인가... 고민...
			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Line Width Group Num"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			{
				SpecTempData.nLineWidthGroupNum = _ttoi(szData);
			}
		}
		else
		{
			SpecTempData.nLineWidthGroupNum = SpecData.nLineWidthGroupNum;
		}

		if (SpecTempData.nLineWidthGroupNum == 0)
		{
			if (m_bUseCombo)	//150611 hjc add
			{
				strTitle.Format(_T("Preset Spec Line"));
				strIndex.Format(_T("Preset Nick Size"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				{
					StringToChar(szData, SpecTempData.szNickSize[0]);
					SpecTempData.nNickPercent[0] = _ttoi(m_pDlgSpec->GetNickRange(szData));
				}

				strTitle.Format(_T("Preset Spec Line"));
				strIndex.Format(_T("Preset Protrusion Size"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				{
					StringToChar(szData, SpecTempData.szProtrusionSize[0]);
					SpecTempData.nProtrusionPercent[0] = _ttoi(m_pDlgSpec->GetProtRange(szData));
				}

				strTitle.Format(_T("Preset Spec Fine Line"));
				strIndex.Format(_T("Preset Fine Nick Size"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				{
					StringToChar(szData, SpecTempData.szFineNickSize[0]);
					SpecTempData.nFineNickPercent[0] = _ttoi(m_pDlgSpec->GetNickRange(szData));
				}
				strTitle.Format(_T("Preset Spec Fine Line"));
				strIndex.Format(_T("Preset Fine Protrusion Size"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				{
					StringToChar(szData, SpecTempData.szFineProtrusionSize[0]);
					SpecTempData.nFineProtrusionPercent[0] = _ttoi(m_pDlgSpec->GetProtRange(szData));
				}
			}
			else
			{
				strTitle.Format(_T("Preset Spec Line"));	//150413 hjc add
				strIndex.Format(_T("Preset Nick Size Percent"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
					SpecTempData.nNickPercent[0] = _ttoi(szData);
				else	//150611 hjc mod
				{
					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Nick Size"));
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						//					strcpy(SpecTempData.szNickSize, szData);
						StringToChar(szData, SpecTempData.szNickSize[0]);

					if (strcmp(SpecTempData.szNickSize[0], "Highest") == 0)
						SpecTempData.nNickPercent[0] = 90;
					else if (strcmp(SpecTempData.szNickSize[0], "VeryHigh") == 0)
						SpecTempData.nNickPercent[0] = 80;
					else if (strcmp(SpecTempData.szNickSize[0], "High") == 0)
						SpecTempData.nNickPercent[0] = 70;
					else if (strcmp(SpecTempData.szNickSize[0], "Normal") == 0)
						SpecTempData.nNickPercent[0] = 60;
					else if (strcmp(SpecTempData.szNickSize[0], "Low") == 0)
						SpecTempData.nNickPercent[0] = 50;
					else if (strcmp(SpecTempData.szNickSize[0], "VeryLow") == 0)
						SpecTempData.nNickPercent[0] = 40;
					else if (strcmp(SpecTempData.szNickSize[0], "Lowest") == 0)
						SpecTempData.nNickPercent[0] = 30;
					else if (strcmp(SpecTempData.szNickSize[0], "MaxLimit") == 0)
						SpecTempData.nNickPercent[0] = 10;
					else
						;
				}

				strTitle.Format(_T("Preset Spec Line"));	//150413 hjc add
				strIndex.Format(_T("Preset Protrusion Size Percent"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
					SpecTempData.nProtrusionPercent[0] = _ttoi(szData);
				else	//150611 hjc add
				{
					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Protrusion Size"));
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						//					strcpy(SpecTempData.szProtrusionSize, szData);
						StringToChar(szData, SpecTempData.szProtrusionSize[0]);

					if (strcmp(SpecTempData.szProtrusionSize[0], "Highest") == 0)
						SpecTempData.nProtrusionPercent[0] = 110;
					if (strcmp(SpecTempData.szProtrusionSize[0], "VeryHigh") == 0)
						SpecTempData.nProtrusionPercent[0] = 120;
					else if (strcmp(SpecTempData.szProtrusionSize[0], "High") == 0)
						SpecTempData.nProtrusionPercent[0] = 130;
					else if (strcmp(SpecTempData.szProtrusionSize[0], "Normal") == 0)
						SpecTempData.nProtrusionPercent[0] = 140;
					else if (strcmp(SpecTempData.szProtrusionSize[0], "Low") == 0)
						SpecTempData.nProtrusionPercent[0] = 150;
					else if (strcmp(SpecTempData.szProtrusionSize[0], "VeryLow") == 0)
						SpecTempData.nProtrusionPercent[0] = 160;
					else if (strcmp(SpecTempData.szProtrusionSize[0], "Lowest") == 0)
						SpecTempData.nProtrusionPercent[0] = 170;
					else if (strcmp(SpecTempData.szProtrusionSize[0], "MaxLimit") == 0)
						SpecTempData.nProtrusionPercent[0] = 190;
					else
						;
				}

				strTitle.Format(_T("Preset Spec Fine Line"));	//150413 hjc add
				strIndex.Format(_T("Preset Fine Nick Size Percent"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
					SpecTempData.nFineNickPercent[0] = _ttoi(szData);
				else
				{
					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Nick Size"));
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						//					strcpy(SpecTempData.szFineNickSize, szData);
						StringToChar(szData, SpecTempData.szFineNickSize[0]);

					//150413 hjc add
					if (strcmp(SpecTempData.szFineNickSize[0], "Highest") == 0)
						SpecTempData.nFineNickPercent[0] = 90;
					else if (strcmp(SpecTempData.szFineNickSize[0], "VeryHigh") == 0)
						SpecTempData.nFineNickPercent[0] = 80;
					else if (strcmp(SpecTempData.szFineNickSize[0], "High") == 0)
						SpecTempData.nFineNickPercent[0] = 70;
					else if (strcmp(SpecTempData.szFineNickSize[0], "Normal") == 0)
						SpecTempData.nFineNickPercent[0] = 60;
					else if (strcmp(SpecTempData.szFineNickSize[0], "Low") == 0)
						SpecTempData.nFineNickPercent[0] = 50;
					else if (strcmp(SpecTempData.szFineNickSize[0], "VeryLow") == 0)
						SpecTempData.nFineNickPercent[0] = 40;
					else if (strcmp(SpecTempData.szFineNickSize[0], "Lowest") == 0)
						SpecTempData.nFineNickPercent[0] = 30;
					else if (strcmp(SpecTempData.szFineNickSize[0], "MaxLimit") == 0)
						SpecTempData.nFineNickPercent[0] = 10;
					else
						;
				}

				strTitle.Format(_T("Preset Spec Fine Line"));	//150413 hjc add
				strIndex.Format(_T("Preset Fine Protrusion Size Percent"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
					SpecTempData.nFineProtrusionPercent[0] = _ttoi(szData);
				else
				{
					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Protrusion Size"));
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						//					strcpy(SpecTempData.szFineProtrusionSize, szData);
						StringToChar(szData, SpecTempData.szFineProtrusionSize[0]);

					if (strcmp(SpecTempData.szFineProtrusionSize[0], "Highest") == 0)
						SpecTempData.nFineProtrusionPercent[0] = 110;
					if (strcmp(SpecTempData.szFineProtrusionSize[0], "VeryHigh") == 0)
						SpecTempData.nFineProtrusionPercent[0] = 120;
					else if (strcmp(SpecTempData.szFineProtrusionSize[0], "High") == 0)
						SpecTempData.nFineProtrusionPercent[0] = 130;
					else if (strcmp(SpecTempData.szFineProtrusionSize[0], "Normal") == 0)
						SpecTempData.nFineProtrusionPercent[0] = 140;
					else if (strcmp(SpecTempData.szFineProtrusionSize[0], "Low") == 0)
						SpecTempData.nFineProtrusionPercent[0] = 150;
					else if (strcmp(SpecTempData.szFineProtrusionSize[0], "VeryLow") == 0)
						SpecTempData.nFineProtrusionPercent[0] = 160;
					else if (strcmp(SpecTempData.szFineProtrusionSize[0], "Lowest") == 0)
						SpecTempData.nFineProtrusionPercent[0] = 170;
					else if (strcmp(SpecTempData.szFineProtrusionSize[0], "MaxLimit") == 0)
						SpecTempData.nFineProtrusionPercent[0] = 190;
					else
						;
				}

				strTitle.Format(_T("Preset Spec Space"));
				strIndex.Format(_T("Preset Min Space Size Percent"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
					SpecTempData.nMinSPPercent = _ttoi(szData);
				else
				{
					strTitle.Format(_T("Preset Spec Space"));
					strIndex.Format(_T("Preset Min Space Size"));
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						//					strcpy(SpecTempData.szMinSPSize, szData);
						StringToChar(szData, SpecTempData.szMinSPSize);

					if (strcmp(SpecTempData.szMinSPSize, "Highest") == 0)	//150413 hjc add
						SpecTempData.nMinSPPercent = 90;
					if (strcmp(SpecTempData.szMinSPSize, "VeryHigh") == 0)
						SpecTempData.nMinSPPercent = 80;
					else if (strcmp(SpecTempData.szMinSPSize, "High") == 0)
						SpecTempData.nMinSPPercent = 70;
					else if (strcmp(SpecTempData.szMinSPSize, "Normal") == 0)
						SpecTempData.nMinSPPercent = 60;
					else if (strcmp(SpecTempData.szMinSPSize, "Low") == 0)
						SpecTempData.nMinSPPercent = 50;
					else if (strcmp(SpecTempData.szMinSPSize, "VeryLow") == 0)
						SpecTempData.nMinSPPercent = 40;
					else if (strcmp(SpecTempData.szMinSPSize, "Lowest") == 0)
						SpecTempData.nMinSPPercent = 30;
					else
						;
				}
			}
		}

		if (SpecTempData.nLineWidthGroupNum == 0)
		{
			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Nick NG Filter Percent"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.nNickNGFilterPercent[0] = _ttoi(szData);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Excs NG Filter Percent"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.nExcsNGFilterPercent[0] = _ttoi(szData);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Line WD Delta Grad Violation"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.fLineWdDeltaGradViolation[0] = _ttof(szData);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Excs WD Delta Grad Violation"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.fExcsWdDeltaGradViolation[0] = _ttof(szData);
		}

		if (SpecTempData.nLineWidthGroupNum > 0 && SpecTempData.nLineWidthGroupNum< 1000)		//20091019 hjc mod
		{
			if (bMLT)
			{
				for (i = 0; i < SpecTempData.nLineWidthGroupNum + 1; i++)
				{
					if (m_bUseCombo)	//150611 hjc add
					{
						strTitle.Format(_T("Preset Spec Line"));
						strIndex.Format(_T("Preset Nick Size%d"), i);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						{
							StringToChar(szData, SpecTempData.szNickSize[i]);
							SpecTempData.nNickPercent[i] = _ttoi(m_pDlgSpec->GetNickRange(szData));
						}

						strTitle.Format(_T("Preset Spec Line"));
						strIndex.Format(_T("Preset Protrusion Size%d"), i);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						{
							StringToChar(szData, SpecTempData.szProtrusionSize[i]);
							SpecTempData.nProtrusionPercent[i] = _ttoi(m_pDlgSpec->GetNickRange(szData));
						}
						strTitle.Format(_T("Preset Spec Fine Line"));
						strIndex.Format(_T("Preset Fine Nick Size%d"), i);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						{
							StringToChar(szData, SpecTempData.szFineNickSize[i]);
							SpecTempData.nFineNickPercent[i] = _ttoi(m_pDlgSpec->GetNickRange(szData));
						}

						strTitle.Format(_T("Preset Spec Fine Line"));
						strIndex.Format(_T("Preset Fine Protrusion Size%d"), i);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						{
							StringToChar(szData, SpecTempData.szFineProtrusionSize[i]);
							SpecTempData.nFineProtrusionPercent[i] = _ttoi(m_pDlgSpec->GetNickRange(szData));
						}

					}
					else
					{
						strTitle.Format(_T("Preset Spec Line"));	//150413 hjc add
						strIndex.Format(_T("Preset Nick Size Percent%d"), i);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
							SpecTempData.nNickPercent[i] = _ttoi(szData);
						else	//150611 hjc mod
						{
							strTitle.Format(_T("Preset Spec Line"));
							strIndex.Format(_T("Preset Nick Size%d"), i);
							if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
								StringToChar(szData, SpecTempData.szNickSize[i]);

							if (strcmp(SpecTempData.szNickSize[i], "Highest") == 0)
								SpecTempData.nNickPercent[i] = 90;
							else if (strcmp(SpecTempData.szNickSize[i], "VeryHigh") == 0)
								SpecTempData.nNickPercent[i] = 80;
							else if (strcmp(SpecTempData.szNickSize[i], "High") == 0)
								SpecTempData.nNickPercent[i] = 70;
							else if (strcmp(SpecTempData.szNickSize[i], "Normal") == 0)
								SpecTempData.nNickPercent[i] = 60;
							else if (strcmp(SpecTempData.szNickSize[i], "Low") == 0)
								SpecTempData.nNickPercent[i] = 50;
							else if (strcmp(SpecTempData.szNickSize[i], "VeryLow") == 0)
								SpecTempData.nNickPercent[i] = 40;
							else if (strcmp(SpecTempData.szNickSize[i], "Lowest") == 0)
								SpecTempData.nNickPercent[i] = 30;
							else if (strcmp(SpecTempData.szNickSize[i], "MaxLimit") == 0)
								SpecTempData.nNickPercent[i] = 10;
							else
								;
						}

						strTitle.Format(_T("Preset Spec Line"));	//150413 hjc add
						strIndex.Format(_T("Preset Protrusion Size Percent%d"), i);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
							SpecTempData.nProtrusionPercent[i] = _ttoi(szData);
						else	//150611 hjc add
						{
							strTitle.Format(_T("Preset Spec Line"));
							strIndex.Format(_T("Preset Protrusion Size%d"), i);
							if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
								//					strcpy(SpecTempData.szProtrusionSize, szData);
								StringToChar(szData, SpecTempData.szProtrusionSize[i]);

							if (strcmp(SpecTempData.szProtrusionSize[i], "Highest") == 0)
								SpecTempData.nProtrusionPercent[i] = 110;
							if (strcmp(SpecTempData.szProtrusionSize[i], "VeryHigh") == 0)
								SpecTempData.nProtrusionPercent[i] = 120;
							else if (strcmp(SpecTempData.szProtrusionSize[i], "High") == 0)
								SpecTempData.nProtrusionPercent[i] = 130;
							else if (strcmp(SpecTempData.szProtrusionSize[i], "Normal") == 0)
								SpecTempData.nProtrusionPercent[i] = 140;
							else if (strcmp(SpecTempData.szProtrusionSize[i], "Low") == 0)
								SpecTempData.nProtrusionPercent[i] = 150;
							else if (strcmp(SpecTempData.szProtrusionSize[i], "VeryLow") == 0)
								SpecTempData.nProtrusionPercent[i] = 160;
							else if (strcmp(SpecTempData.szProtrusionSize[i], "Lowest") == 0)
								SpecTempData.nProtrusionPercent[i] = 170;
							else if (strcmp(SpecTempData.szProtrusionSize[i], "MaxLimit") == 0)
								SpecTempData.nProtrusionPercent[i] = 190;
							else
								;
						}

						strTitle.Format(_T("Preset Spec Fine Line"));	//150413 hjc add
						strIndex.Format(_T("Preset Fine Nick Size Percent%d"), i);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
							SpecTempData.nFineNickPercent[i] = _ttoi(szData);
						else
						{
							strTitle.Format(_T("Preset Spec Fine Line"));
							strIndex.Format(_T("Preset Fine Nick Size%d"), i);
							if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
								StringToChar(szData, SpecTempData.szFineNickSize[i]);

							//150413 hjc add
							if (strcmp(SpecTempData.szFineNickSize[i], "Highest") == 0)
								SpecTempData.nFineNickPercent[i] = 90;
							else if (strcmp(SpecTempData.szFineNickSize[i], "VeryHigh") == 0)
								SpecTempData.nFineNickPercent[i] = 80;
							else if (strcmp(SpecTempData.szFineNickSize[i], "High") == 0)
								SpecTempData.nFineNickPercent[i] = 70;
							else if (strcmp(SpecTempData.szFineNickSize[i], "Normal") == 0)
								SpecTempData.nFineNickPercent[i] = 60;
							else if (strcmp(SpecTempData.szFineNickSize[i], "Low") == 0)
								SpecTempData.nFineNickPercent[i] = 50;
							else if (strcmp(SpecTempData.szFineNickSize[i], "VeryLow") == 0)
								SpecTempData.nFineNickPercent[i] = 40;
							else if (strcmp(SpecTempData.szFineNickSize[i], "Lowest") == 0)
								SpecTempData.nFineNickPercent[i] = 30;
							else if (strcmp(SpecTempData.szFineNickSize[i], "MaxLimit") == 0)
								SpecTempData.nFineNickPercent[i] = 10;
							else
								;
						}

						strTitle.Format(_T("Preset Spec Fine Line"));	//150413 hjc add
						strIndex.Format(_T("Preset Fine Protrusion Size Percent%d"), i);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
							SpecTempData.nFineProtrusionPercent[i] = _ttoi(szData);
						else
						{
							strTitle.Format(_T("Preset Spec Fine Line"));
							strIndex.Format(_T("Preset Fine Protrusion Size%d"), i);
							if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
								StringToChar(szData, SpecTempData.szFineProtrusionSize[i]);

							if (strcmp(SpecTempData.szFineProtrusionSize[i], "Highest") == 0)
								SpecTempData.nFineProtrusionPercent[i] = 110;
							if (strcmp(SpecTempData.szFineProtrusionSize[i], "VeryHigh") == 0)
								SpecTempData.nFineProtrusionPercent[i] = 120;
							else if (strcmp(SpecTempData.szFineProtrusionSize[i], "High") == 0)
								SpecTempData.nFineProtrusionPercent[i] = 130;
							else if (strcmp(SpecTempData.szFineProtrusionSize[i], "Normal") == 0)
								SpecTempData.nFineProtrusionPercent[i] = 140;
							else if (strcmp(SpecTempData.szFineProtrusionSize[i], "Low") == 0)
								SpecTempData.nFineProtrusionPercent[i] = 150;
							else if (strcmp(SpecTempData.szFineProtrusionSize[i], "VeryLow") == 0)
								SpecTempData.nFineProtrusionPercent[i] = 160;
							else if (strcmp(SpecTempData.szFineProtrusionSize[i], "Lowest") == 0)
								SpecTempData.nFineProtrusionPercent[i] = 170;
							else if (strcmp(SpecTempData.szFineProtrusionSize[i], "MaxLimit") == 0)
								SpecTempData.nFineProtrusionPercent[i] = 190;
							else
								;
						}

					}


					if (m_bUseCombo)
					{
						StringToChar(pGlobalDoc->GetNickRangeReverse(SpecTempData.nFineNickPercent[i]), SpecTempData.szFineNickSize[i]);
						StringToChar(pGlobalDoc->GetProtRangeReverse(SpecTempData.nFineProtrusionPercent[i]), SpecTempData.szFineProtrusionSize[i]);
						StringToChar(pGlobalDoc->GetNickRangeReverse(SpecTempData.nNickPercent[i]), SpecTempData.szNickSize[i]);
						StringToChar(pGlobalDoc->GetProtRangeReverse(SpecTempData.nProtrusionPercent[i]), SpecTempData.szProtrusionSize[i]);
					}


					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Nick NG Filter Percent%d"), i);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecTempData.nNickNGFilterPercent[i] = _ttoi(szData);

					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Excs NG Filter Percent%d"), i);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecTempData.nExcsNGFilterPercent[i] = _ttoi(szData);

					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Line WD Delta Grad Violation%d"), i);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecTempData.fLineWdDeltaGradViolation[i] = _ttof(szData);

					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Excs WD Delta Grad Violation%d"), i);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecTempData.fExcsWdDeltaGradViolation[i] = _ttof(szData);

					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Narrow Trace Violation%d"), i);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecTempData.fNarrowTraceViolation[i] = _ttof(szData);

					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Wide Trace Violation%d"), i);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecTempData.fWideTraceViolation[i] = _ttof(szData);
				}
			}
			else
			{
				for (i = 0; i < 15; i++)
				{
					sprintf(SpecTempData.szNickSize[i], "%s", SpecData.szNickSize[i]);
					sprintf(SpecTempData.szProtrusionSize[i], "%s", SpecData.szProtrusionSize[i]);
					sprintf(SpecTempData.szFineNickSize[i], "%s", SpecData.szFineNickSize[i]);
					sprintf(SpecTempData.szFineProtrusionSize[i], "%s", SpecData.szFineProtrusionSize[i]);
					SpecTempData.nNickPercent[i] = SpecData.nNickPercent[i];
					SpecTempData.nProtrusionPercent[i] = SpecData.nProtrusionPercent[i];
					SpecTempData.nFineNickPercent[i] = SpecData.nFineProtrusionPercent[i];
					SpecTempData.nNickNGFilterPercent[i] = SpecData.nNickNGFilterPercent[i];
					SpecTempData.nExcsNGFilterPercent[i] = SpecData.nExcsNGFilterPercent[i];
					SpecTempData.fLineWdDeltaGradViolation[i] = SpecData.fLineWdDeltaGradViolation[i];
					SpecTempData.fExcsWdDeltaGradViolation[i] = SpecData.fExcsWdDeltaGradViolation[i];
					SpecTempData.fNarrowTraceViolation[i] = SpecData.fNarrowTraceViolation[i];
					SpecTempData.fWideTraceViolation[i] = SpecData.fWideTraceViolation[i];
				}
			}
		}
		else
		{
			//SpecData.nLineWidthGroupNum = 0;

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Line Width Group0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.fLineWidthGroup[0] = _ttof(szData);

			//170524 lgh
			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Line Width GroupLower0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.fLineWidthGroupLower[0] = _ttof(szData);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Narrow Trace Violation0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.fNarrowTraceViolation[0] = _ttof(szData);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Wide Trace Violation0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.fWideTraceViolation[0] = _ttof(szData);
		}

		//Fine Line Spec
		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Min Line Width"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fFineMinLineWidth = _ttof(szData);

		if (SpecTempData.nLineWidthGroupNum <= 0)
		{
			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Nick NG Filter Percent"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.nFineNickNGFilterPercent[0] = _ttoi(szData);

			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Excs NG Filter Percent"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.nFineExcsNGFilterPercent[0] = _ttoi(szData);

			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Line WD Delta Grad Violation"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.fFineLineWdDeltaGradViolation[0] = _ttof(szData);

			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Excs WD Delta Grad Violation"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.fFineExcsWdDeltaGradViolation[0] = _ttof(szData);
		}

		if (SpecTempData.nLineWidthGroupNum > 0)		//20091019 hjc mod
		{
			if (bMLT)
			{
				for (idx = 0; idx < SpecTempData.nLineWidthGroupNum + 1; idx++)
				{
					SpecTempData.fFineLineWidthGroup[idx] = SpecData.fLineWidthGroup[idx];

					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Narrow Trace Violation%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecTempData.fFineNarrowTraceViolation[idx] = _ttof(szData);

					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Wide Trace Violation%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecTempData.fFineWideTraceViolation[idx] = _ttof(szData);

					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Nick NG Filter Percent%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecTempData.nFineNickNGFilterPercent[idx] = _ttoi(szData);

					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Excs NG Filter Percent%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecTempData.nFineExcsNGFilterPercent[idx] = _ttoi(szData);

					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Line WD Delta Grad Violation%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecTempData.fFineLineWdDeltaGradViolation[idx] = _ttof(szData);

					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Excs WD Delta Grad Violation%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecTempData.fFineExcsWdDeltaGradViolation[idx] = _ttof(szData);
				}
			}
			else
			{
				for (i = 0; i < 15; i++)
				{
					SpecTempData.fFineNarrowTraceViolation[i] = SpecData.fFineNarrowTraceViolation[i];
					SpecTempData.fFineWideTraceViolation[i] = SpecData.fFineWideTraceViolation[i];
					SpecTempData.nFineNickNGFilterPercent[i] = SpecData.nFineNickNGFilterPercent[i];
					SpecTempData.nFineExcsNGFilterPercent[i] = SpecData.nFineExcsNGFilterPercent[i];
					SpecTempData.fFineLineWdDeltaGradViolation[i] = SpecData.fFineLineWdDeltaGradViolation[i];
					SpecTempData.fFineExcsWdDeltaGradViolation[i] = SpecData.fFineExcsWdDeltaGradViolation[i];
				}
			}
		}
		else
		{
			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Line Width Group0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.fFineLineWidthGroup[0] = _ttof(szData);

			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Narrow Trace Violation0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.fFineNarrowTraceViolation[0] = _ttof(szData);

			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Wide Trace Violation0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.fFineWideTraceViolation[0] = _ttof(szData);
		}

		//150515 hjc add end

		//Space Spec
		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Min Space Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nMinSpaceGraySpec = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Neib Space Gray Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nNeibSpGrayDiff = _ttoi(szData);

		//150529 hjc mod
		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset US Dark Gray Minus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nUSDarkGrayMinus = _ttoi(szData);
		else
		{
			strTitle.Format(_T("Preset Spec AddOn Line"));
			strIndex.Format(_T("Preset US Dark Gray Minus"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.nUSDarkGrayMinus = _ttoi(szData);
			else
				SpecTempData.nUSDarkGrayMinus = 45;
		}
#if CUSTOMER_COMPANY == UMTC 
		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Min Space Width"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fMinSpWidth = _ttof(szData);
#endif
		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Space NG Filter Percent"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSpaceNGFilterPercent = _ttoi(szData);

		//20090405 hjc
		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Space WD Delta Outer Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fSpWdDeltaOuterGradViolation = _ttof(szData);

		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Space WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fSpWdDeltaGradViolation = _ttof(szData);

		//		strTitle.Format(_T("Preset Spec Space"));
		//		strIndex.Format(_T("Preset HLG Space Width Percent"));
		//		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//			SpecTempData.fHLGSpWidthPercent = _ttof(szData);

		strTitle.Format(_T("Preset Spec Space"));	//121226 hjc add
		strIndex.Format(_T("Preset Fine Min Space Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fFineMinSpWidth = _ttof(szData);

		//Ext/Pin Hole Spec
		//150823 hjc add
		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Virtual Drill Diff Bright Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nVDrillDiffBrightGray = _ttoi(szData);
		else
		{
			if (m_nVDMeanDiff > 0)
				SpecTempData.nVDrillDiffBrightGray = 255 - m_nVDMeanDiff;
			else
			{
#if MACHINE_MODEL == INSPRO_GM_PLUS || MACHINE_MODEL == INSMART_GM4000 || MACHINE_MODEL == INSPRO_GM 
				SpecTempData.nVDrillDiffBrightGray = 0;	//150823 hjc mod
#else
				SpecTempData.nVDrillDiffBrightGray = 40;
#endif
			}
		}

		//150606 hjc add
		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Virtual Drill Diff Dark Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nVDrillDiffDarkGray = _ttoi(szData);
		else
		{
			strTitle.Format(_T("Preset Spec Extra PinHole"));
			strIndex.Format(_T("Preset Virtual Drill Pixel Gray"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.nVDrillDiffDarkGray = _ttoi(szData);
			else
				SpecTempData.nVDrillDiffDarkGray = 120;
		}

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Virtual Drill Pad Precision"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fVDPadPrecName = _ttof(szData);

		//20090419 hjc
		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Virtual Drill Location Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fVDLocationTolerance = _ttof(szData);
		//

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Virtual Drill Pad Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fVDPadMin = _ttof(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Pad Void Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nPADVoidGraySpec = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Pad Void Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fPADVoidMin = _ttof(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Pad Tip Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fPADTipMin = _ttof(szData);

		//20100322 hjc add
		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset HoleLand Void Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nHoleLandVoidGray = _ttoi(szData);
		else
			SpecTempData.nHoleLandVoidGray = SpecData.nPADVoidGraySpec;

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset CO2Land Void Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCO2LandVoidGraySpec = _ttoi(szData);
		else
			SpecTempData.nCO2LandVoidGraySpec = 120;

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset CO2Land Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fCO2LandMin = _ttof(szData);
		else
			SpecTempData.fCO2LandMin = 15 * SizeData[COMMON_PARAMETER].fPixelSize;

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset CO2Land Align Mode"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			//			strcpy(SpecTempData.szCO2LandAlignMode, szData);
			StringToChar(szData, SpecTempData.szCO2LandAlignMode);
		else
			strcpy(SpecTempData.szCO2LandAlignMode, "Yes");
		//end

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset AR Land Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fARLandMin = _ttof(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Hole Fill Ext"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fHoleFillExt = _ttof(szData);

		//20100323 hjc add
		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset CO2Hole Fill Ext"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fCO2HoleFillExt = _ttof(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Fine PAD Void Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nFinePADVoidGraySpec = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Fine PAD Void Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fFinePADVoidMin = _ttof(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Pin Hole Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nPinHoleGraySpec = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Pin Hole Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fPinHoleMin = _ttof(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Island Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nIsLandGraySpec = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Island Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fIsLandMin = _ttof(szData);
		//20090412 hjc
		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Island Extra Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nIsLandExtGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Island Extra Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fIsLandExtMin = _ttof(szData);

		//jun 20120903 for LG_CCL-Inspector
		strTitle.Format(_T("Preset Spec CCL Inspection"));
		strIndex.Format(_T("Preset CCL Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCCLGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec CCL Inspection"));
		strIndex.Format(_T("Preset CCL Circularity"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fCCLCircularity = _ttof(szData);

		strTitle.Format(_T("Preset Spec CCL Inspection"));
		strIndex.Format(_T("Preset CCL Defect Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fCCLDefSize = _ttof(szData);

		//Hole/VH Spec
		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fHoleTolerance = _ttof(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Dia Upper"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fHoleDiaUpper = _ttof(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Dia Lower"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fHoleDiaLower = _ttof(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Open Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nHoleOpenGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Missing Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nHoleMissingGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Inner Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nHoleInnerGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole RL Precision Name"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			//			strcpy(SpecTempData.szHoleRLPrecName, szData);
			StringToChar(szData, SpecTempData.szHoleRLPrecName);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Def Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nHoleDefNum = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset VH Mode"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			//			strcpy(SpecTempData.szVHMode, szData);
			StringToChar(szData, SpecTempData.szVHMode);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset CO2 Missing Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCO2MissingGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset CO2 Hole Num"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCO2HoleNum = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset CO2 Open Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCO2OpenGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset CO2 Miss Align Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCO2MisAgnGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset CO2 Miss Align Defect Percent"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCO2MisAgnDefPercent = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset VH Edge Thr Diff Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nVHEdgeThrDiffGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset VH BreakOut Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nVHBreakOutGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset VH Dissmear Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nVHDissmearGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset VH Conti BreakOut Num"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nVHContiBreakOutNum = _ttoi(szData);

		//Edge Spec
		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Pad Edge Nick Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nPadEdgeNickGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Edge"));	//120105 hjc add
		strIndex.Format(_T("Preset Pad Edge Neib Gray Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nPadEdgeNeibGrayDiff = _ttoi(szData);

		//140127 hjc add
		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Pad Edge BA Diff Dark Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nPadEdgeBADiffDarkGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Pad Edge Nick WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fPadEdgeNickWdDeltaGradViolation = _ttof(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Pad Edge Excs WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fPadEdgeExcsWdDeltaGradViolation = _ttof(szData);

		//20090412 hjc
		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Pad VD Edge Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nPadVDEdgeGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Pad VD Edge Wd Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fPadVDEdgeWdDeltaGradViolation = _ttof(szData);
		//------------------

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Hole Edge Nick Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nHoleEdgeNickGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Edge"));	//120109 hjc add
		strIndex.Format(_T("Preset Hole Edge Neib Gray Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nHoleEdgeNeibGrayDiff = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Hole Edge Nick WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fHoleEdgeNickWdDeltaGradViolation = _ttof(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Hole Edge Excs WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fHoleEdgeExcsWdDeltaGradViolation = _ttof(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Via Edge Nick Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nViaEdgeNickGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Edge"));	//120109 hjc add
		strIndex.Format(_T("Preset Via Edge Neib Gray Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nViaEdgeNeibGrayDiff = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Via Edge Nick WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fViaEdgeNickWdDeltaGradViolation = _ttof(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Via Edge Excs WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fViaEdgeExcsWdDeltaGradViolation = _ttof(szData);

		//Model Spec
		strTitle.Format(_T("Preset Spec Model"));
		strIndex.Format(_T("Preset PTModel Search Range Extension"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nPtSrchRngExtTemp = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Model"));
		strIndex.Format(_T("Preset Align Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nAlignTolerance = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Model"));
		strIndex.Format(_T("Preset Theta Align"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_strThetaAlignTemp.Format(_T("%s"), szData);

		strTitle.Format(_T("Preset Spec Model"));
		strIndex.Format(_T("Preset Defect Mask Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fDefMaskSize = _ttof(szData);

		strTitle.Format(_T("Preset Spec Model"));
		strIndex.Format(_T("Preset Near Defect Length"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fNearDefLen = _ttof(szData);

		//20100210 hjc add
		if (m_bUseMultiVaccumControl)
		{
			strTitle.Format(_T("Preset Spec Model"));
			strIndex.Format(_T("Preset Select Vaccum"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				//				strcpy(SpecTempData.strSelectVaccum, szData);
				StringToChar(szData, SpecTempData.strSelectVaccum);

			if (SpecTempData.strSelectVaccum == "Both")	//130215 hjc add
				SpecData.nSelectVaccum = 1;
			else if (SpecTempData.strSelectVaccum == "FirstOnly")
				SpecData.nSelectVaccum = 2;
		}
		else
		{
			strTitle.Format(_T("Preset Spec Model"));
			strIndex.Format(_T("Preset Select Vaccum"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				strcpy(SpecTempData.strSelectVaccum, "Both");
			SpecData.nSelectVaccum = 1;		//130215 hjc add
		}

		//ADDON Line Spec
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset GTC Shake Extend"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bGTCShakeExtend = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Stella Method"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bApplyStellaMethodTemp = _ttoi(szData);

		//20090902 hjc
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Inclined Nick"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkInclinedNickTemp = _ttoi(szData);

		//111024 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Inclined Short"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkInclinedShortTemp = _ttoi(szData);

		//110518 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Inclined Space"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkInclinedSpaceTemp = _ttoi(szData);

		//110526 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Apply Skip Check In VD Line"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bSkipChkInVDLine = _ttoi(szData);

		//121128 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Apply Silver Paste Via"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bCheckSilverPasteVia = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Apply VH Out Break Count"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nVHOutBreakCnt = _ttoi(szData);
		//end

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));	//20230508 add
		strIndex.Format(_T("Preset Apply VH Taping Tolerence"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nVHTapingTolerence = _ttoi(szData);
		else
			SpecTempData.nVHTapingTolerence = 0;

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));	//20230627 add
		strIndex.Format(_T("Preset Apply VH Taping Min Max Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nVHTapingMinMaxDiff = _ttoi(szData);
		else
			SpecTempData.nVHTapingMinMaxDiff = 0;

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));	//20230628 add
		strIndex.Format(_T("Preset Check Via Multi Dia"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bChkViaMultidia = _ttoi(szData);
		else
			SpecTempData.bChkViaMultidia = FALSE;

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));	//20230711 add
		strIndex.Format(_T("Preset Apply VH Inner Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nVHInnerGray = _ttoi(szData);
		else
			SpecTempData.nVHInnerGray = 100;

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));	//20230713 add
		strIndex.Format(_T("Preset Apply VH Min Max Dia Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nVHMinMaxDiaRatio = _ttoi(szData);
		else
			SpecTempData.nVHMinMaxDiaRatio = 60;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Inclined Oblique Space"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkInclinedObliqueSpaceTemp = _ttoi(szData);
		//end

		//20220316 LGH ADD
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset CheckProtFromSpaceWidth"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.m_bCheckProtFromSpaceWidth = _ttoi(szData);

		//20220513 add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Use Large Align Shift"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bLargeAlignShift = _ttoi(szData);

		//20220823 add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Use Rough Surface Pattern"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bRoughSurface = _ttoi(szData);

		//20120418-ndy
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Inclined Oblique Line"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkInclinedObliqueLineTemp = _ttoi(szData);


		pGlobalDoc->LoadMachineLogicModeFromPresetTemp(INSP_MODE_NORMAL, strPath);
		pGlobalDoc->LoadMachineLogicModeFromPresetTemp(INSP_MODE_RED, strPath);
		pGlobalDoc->LoadMachineLogicModeFromPresetTemp(INSP_MODE_BLUE, strPath);

	
		////150817 hjc add
		//strTitle.Format(_T("Preset Spec AddOn Line"));
		//strIndex.Format(_T("Preset Product TSP"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//pMainFrame->m_bProductTSPTemp = _ttoi(szData);
		//else
		//pMainFrame->m_bProductTSPTemp = FALSE;

		////140503 hjc add
		//strTitle.Format(_T("Preset Spec AddOn Line"));
		//strIndex.Format(_T("Preset Adaptive Threshold"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//pMainFrame->m_bAdaptiveThTemp = _ttoi(szData);
		//else
		//pMainFrame->m_bAdaptiveThTemp = FALSE;

		////20100427 hjc
		//strTitle.Format(_T("Preset Spec AddOn Line"));
		//strIndex.Format(_T("Preset Apply GM Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//pMainFrame->m_bGMCheckTemp = _ttoi(szData);
		//else
		//pMainFrame->m_bGMCheckTemp = FALSE;

		////150527 hjc add
		//strTitle.Format(_T("Preset Spec AddOn Line"));
		//strIndex.Format(_T("Preset Apply Bare White Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//pMainFrame->m_bChkBareWhiteTemp = _ttoi(szData);
		//else
		//pMainFrame->m_bChkBareWhiteTemp = FALSE;
		
		//20091203 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Measurement Method"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bCheckMeasurementMethodTemp = _ttoi(szData);
		else
			pMainFrame->m_bCheckMeasurementMethodTemp = TRUE;
		//

		//140425 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Pattern Tip Dead Zone"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bPatternTipDeadZoneTemp = _ttoi(szData);
		else
			pMainFrame->m_bPatternTipDeadZoneTemp = TRUE;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Post Filtering"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bApplyPostFilteringTemp = _ttoi(szData);

		//20090514 jsy		
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Space Post Filtering"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bApplySpaceFilteringTemp = _ttoi(szData);

		// 20090525 ljg
		strTitle.Format(_T("Preset Pre System"));
		strIndex.Format(_T("Preset Defect Merge Ratio OnTrace"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_fDefectMergeRatioOnTraceTemp = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Line Noise Filter Value"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_nLineNoiseFilterTemp = _ttoi(szData);

		// 20090514 jsy
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Noise Filter Value"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_nSpaceNoiseFilterTemp = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Pad Tip Precision Nick Check"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fPADTipNickPrecSpec = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));	//130528 hjc add
		strIndex.Format(_T("Preset Space Neib Dark Gray Tot"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nNeibDarkGrayTot = _ttoi(szData);
		else
			SpecTempData.nNeibDarkGrayTot = 2;

		strTitle.Format(_T("Preset Spec AddOn Line"));	//130528 hjc add
		strIndex.Format(_T("Preset Space Neib Bright Gray Tot"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nNeibBrightGrayTot = _ttoi(szData);
		else
			SpecTempData.nNeibBrightGrayTot = 1;

		strTitle.Format(_T("Preset Pre System"));
		strIndex.Format(_T("Preset Sp Bound Search Limit Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSpBoundSearchLimitPixel = _ttoi(szData);
		else
			SpecTempData.nSpBoundSearchLimitPixel = 1;

		strTitle.Format(_T("Preset Pre System"));
		strIndex.Format(_T("Preset Sp Min Max Alpha Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fSpMMDiffAlphaPlus = _ttof(szData);
		else
			SpecTempData.fSpMMDiffAlphaPlus = 0.5;

		//140826 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset AICL Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fAICLTolerance = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Pad Tip Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fSROEExceptLen = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Pattern Tip Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fOEExceptLen = _ttof(szData);

		//150625 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Tip Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fOEExceptSpaceLen = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Hole Tip Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fARCO2JuncExceptLen = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Trace Shake Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nShakeToleranceTemp = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Line Width StepUp Sensitivity"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_fLineWidthStepUpSensitivityTemp = _ttof(szData);
		else
		{
#if MACHINE_MODEL == INSPRO_GM_PLUS || MACHINE_MODEL == INSMART_GM4000 || MACHINE_MODEL == INSPRO_GM
			pMainFrame->m_fLineWidthStepUpSensitivityTemp = 0.0;	              // Default : 0.5f
#else
			pMainFrame->m_fLineWidthStepUpSensitivityTemp = 0.5f;
#endif
		}

		//160330 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Under Layer Cut Threshold"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nUnderLayerCutTh = _ttoi(szData);
		else
			SpecTempData.nUnderLayerCutTh = 0;	//20220823 mod 75;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Under Layer Lower Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSpUnderLayerLowerGray = _ttoi(szData);
		else
			SpecTempData.nSpUnderLayerLowerGray = 15;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Under Layer Upper Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSpUnderLayerUpperGray = _ttoi(szData);
		else
			SpecTempData.nSpUnderLayerUpperGray = 25;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Under Layer Def Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fSpUnderLayerDefSize = _ttof(szData);
		else
			SpecTempData.fSpUnderLayerDefSize = 3.0f;
		//160330 hjc add end

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Under Layer Effect Gray Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSpaceUnderLayerEffectGrayPlus = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));		//20230704 add
		strIndex.Format(_T("Preset Center Line Offset Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCenterlineOffsetTolerance = _ttoi(szData);
		else
			SpecTempData.nCenterlineOffsetTolerance = 4;

		// 20090630 jsy
		strTitle.Format(_T("Preset Pre System"));
		strIndex.Format(_T("Preset Line Wnd Boundary Gray Minus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nLineWndBoundaryGrayMinus = _ttoi(szData);

		strTitle.Format(_T("Preset Pre System"));
		strIndex.Format(_T("Preset Space Wnd Boundary Gray Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSpaceWndBoundaryGrayPlus = _ttoi(szData);

		//151201 hjc add
		strTitle.Format(_T("Preset Pre System"));
		strIndex.Format(_T("Preset Use Broad Cast"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			AoiParam()->m_bUseAlignBroadCast = _ttoi(szData);
		else
		{
#if MACHINE_MODEL == INSMART_GM4000
			AoiParam()->m_bUseAlignBroadCast = 1;
#else
			AoiParam()->m_bUseAlignBroadCast = 0;
#endif
		}
		//110601 hjc add
		//strTitle.Format(_T("Preset Spec AddOn Line"));
		//strIndex.Format(_T("Preset Apply HalfSide Relative Bright Gray"));

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset HalfSide Nick Diff Bright Gray"));	//121224 hjc mod
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nHalfSideNickDiffBrightGray = _ttoi(szData);
		else
			SpecTempData.nHalfSideNickDiffBrightGray = 35;


		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset HalfSide Nick Diff Dark Gray"));	//121224 hjc mod
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nHalfSideNickDiffDarkGray = _ttoi(szData);
		//end

		//170403 hjc add
		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine HalfSide Nick Diff Bright Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nFineHalfSideNickDiffBrightGray = _ttoi(szData);
		else
			SpecTempData.nFineHalfSideNickDiffBrightGray = 35;

		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine HalfSide Nick Diff Dark Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nFineHalfSideNickDiffDarkGray = _ttoi(szData);
		else
			SpecTempData.nFineHalfSideNickDiffDarkGray = 35;
		//170403 hjc add end

		//111029 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Dish Down"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkDishDownTemp = _ttoi(szData);

		//111011 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply In Land Line"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkInLandLineTemp = _ttoi(szData);

		//150817 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Edge Spec Down"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bEdgeSpecDownTemp = _ttoi(szData);
		else
			pMainFrame->m_bEdgeSpecDownTemp = FALSE;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Edge Spec Down Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nEdgeSpecDownPxl = _ttoi(szData);
		else
			SpecTempData.nEdgeSpecDownPxl = 1;


		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Exclude Spire"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkExcludeSpireTemp = _ttoi(szData);
		else
		{
#if MACHINE_MODEL == INSPRO_GM_PLUS || MACHINE_MODEL == INSMART_GM4000 || MACHINE_MODEL == INSPRO_GM
			pMainFrame->m_bChkExcludeSpireTemp = TRUE;
#else
			pMainFrame->m_bChkExcludeSpireTemp = FALSE;
#endif
		}

		//130409 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset CompensateWD For Additive Process"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bCompensateWDForAdditiveProcessTemp = _ttoi(szData);
		else
			pMainFrame->m_bCompensateWDForAdditiveProcessTemp = TRUE;

		//150421 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Master Real Same"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bMasterRealSameFlagTemp = _ttoi(szData);
		else
			pMainFrame->m_bMasterRealSameFlagTemp = TRUE;

		//131216 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Check VD Neiber Space"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		{
			bTempData = _ttoi(szData);
			//141012 hjc mod
			if (bTempData)
			{
				strTitle.Format(_T("Preset Spec AddOn Line"));	//131216 hjc add
				strIndex.Format(_T("Preset VD Neib PM MinMax Diff Gray"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
					SpecTempData.nVDNeibPMMinMaxDiffGray = _ttoi(szData);
				else
					SpecTempData.nVDNeibPMMinMaxDiffGray = 40;
			}
			else
				SpecTempData.nVDNeibPMMinMaxDiffGray = 0;
		}
		else
		{
			strTitle.Format(_T("Preset Spec AddOn Line"));	//131216 hjc add
			strIndex.Format(_T("Preset VD Neib PM MinMax Diff Gray"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecTempData.nVDNeibPMMinMaxDiffGray = _ttoi(szData);
			else
				SpecTempData.nVDNeibPMMinMaxDiffGray = 40;
		}

		//110701 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset PM Image Threshold Enhancement"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bPMImgThresholdEnhancement = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset PM Image Adaptive Threshold Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fAdaptiveThresholdRatio = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Linked Defect Count"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fLinkedDefectCntPix = _ttof(szData);
		//end

		//ADDON Extra PinHole Spec
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Dark Pinhole Gray Minus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nDarkPinHoleGrayMinus = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Bright PAD Def Gray Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nBrightPADDefGrayPlus = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Dark PAD Def Gray Minus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nDarkPADDefGrayMinus = _ttoi(szData);

		//130528 hjc add
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Relative Pad Defect Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fRlsPadDefSize = _ttof(szData);
		else
			SpecTempData.fRlsPadDefSize = 50.0f;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Relative PinHole Defect Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fRlsPinHoleDefSize = _ttof(szData);
		else
			SpecTempData.fRlsPinHoleDefSize = 60.0f;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));	//130529 hjc add
		strIndex.Format(_T("Preset Exclude PadDef Edge Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nExcludePadDefEdgePixel = _ttoi(szData);
		else
			SpecTempData.nExcludePadDefEdgePixel = 3;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));	//130529 hjc add
		strIndex.Format(_T("Preset Exclude PinHole Edge Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nExcludePinHoleEdgePixel = _ttoi(szData);
		else
			SpecTempData.nExcludePinHoleEdgePixel = 5;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PinHole Width Limit Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fPinHoleBreadthLimitPixel = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PinHole Circularity Limit"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fPinHoleCompacenessLimit = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PinHole Merge Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nPinHoleClosingIteration = _ttoi(szData);

		// 20090326 ljg NY-add
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PinHole Noise Reduction Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nPinHoleOpeningIteration = _ttoi(szData);

		// 120501 jsy
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PadDef Merge Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nPadDefClosingIteration = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PadDef Noise Reduction Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nPadDefOpeningIteration = _ttoi(szData);

		// 20090512 add
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PinHole Merge Distance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fPinHoleMergeDistance = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use Local RleBlock"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseLocalRleBlock = _ttoi(szData);

		//130604 hjc add
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use Relative PinHole Radient"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseRelPinHoleRadient = _ttoi(szData);
		else
			SpecTempData.bUseRelPinHoleRadient = TRUE;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use Raw Gray for PinHole"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseRawGrayPinHole = _ttoi(szData);

		//20090412 hjc
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use Raw Gray for Island"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseRawGrayForIsland = _ttoi(szData);
		else
			SpecTempData.bUseRawGrayForIsland = 0;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Bright Island Gray Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nBrightIslandGrayPlus = _ttoi(szData);
		else
			SpecTempData.nBrightIslandGrayPlus = 30;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Dark Island Gray Minus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nDarkIslandGrayMinus = _ttoi(szData);
		else
			SpecTempData.nDarkIslandGrayMinus = 30;
		//------------------

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use Raw Gray for PADDefect"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseRawGrayPADDefect = _ttoi(szData);

		//20190729 add start
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use New Raw Gray for PADDefect"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseNewRawGrayPADDefect = _ttoi(szData);
		else
			SpecTempData.bUseNewRawGrayPADDefect = FALSE;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use New Raw Gray for PinHole"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseNewRawGrayPinHole = _ttoi(szData);
		else
			SpecTempData.bUseNewRawGrayPinHole = FALSE;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use New Raw Gray for Island"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseNewRawGrayForIsland = _ttoi(szData);
		else
			SpecTempData.bUseNewRawGrayForIsland = FALSE;
		//20190729 add end

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Dark Gray Minus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSpLgDarkGrayMinus = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Dark Pixel Num"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nDarkSpaceMin = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Bright Pinhole Gray Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nBrightPinHoleGrayPlus = _ttoi(szData);

		//20090405 hjc
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Dark Pinhole Neib Gray Minus Apply Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fDarkPinHoleNeibGrayMinusApplyRatio = _ttof(szData);
		else
			SpecTempData.fDarkPinHoleNeibGrayMinusApplyRatio = 0.5f;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Bright Pinhole Neib Gray Plus Apply Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fBrightPinHoleNeibGrayPlusApplyRatio = _ttof(szData);
		else
			SpecTempData.fBrightPinHoleNeibGrayPlusApplyRatio = 0.5f;

		//20160108 ndy add - Start
#if MACHINE_MODEL == INSMART_GM4000
		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Use Fine Extra Inspection for ExtraDefect");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseFineIslandInsp = atoi(szData);
		else
			SpecTempData.bUseFineIslandInsp = TRUE;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Fine Extra Relative Gray");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nFineIslandRelativeGray = atoi(szData);
		else
			SpecTempData.nFineIslandRelativeGray = 30;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Fine Extra Max Size");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nFineIslandMaxSize = atoi(szData);
		else
			SpecTempData.nFineIslandMaxSize = 25;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Fine Extra Mask Size");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nFineIslandMaskSize = atoi(szData);
		else
			SpecTempData.nFineIslandMaskSize = 2;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Use Fine PinHole Inspction for PinHoleDefect");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseFinePinHoleInsp = atoi(szData);
		else
			SpecTempData.bUseFinePinHoleInsp = TRUE;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Fine PinHole Relative Gray");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nFinePinHoleRelativeGray = atoi(szData);
		else
			SpecTempData.nFinePinHoleRelativeGray = 20;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Fine PinHole Max Size");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nFinePinHoleMaxSize = atoi(szData);
		else
			SpecTempData.nFinePinHoleMaxSize = 25;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));		//20230417 add start
		strIndex.Format(_T("Preset Sp Gradient Upper Limit"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nGradientUpperLimit = _ttoi(szData);
		else
			SpecTempData.nGradientUpperLimit = 100;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Sp Gradient Threshold"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nGradientThreshold = _ttoi(szData);
		else
			SpecTempData.nGradientThreshold = 15;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Sp Gradient Min Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nGradientMinSize = _ttoi(szData);
		else
			SpecTempData.nGradientMinSize = 0;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PadLg Gradient Upper Limit"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nPadLgGradientUpperLimit = _ttoi(szData);
		else
			SpecTempData.nPadLgGradientUpperLimit = 200;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PadLg Gradient Threshold"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nPadLgGradientThreshold = _ttoi(szData);
		else
			SpecTempData.nPadLgGradientThreshold = 45;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PadLg Gradient Min Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nPadLgGradientMinSize = _ttoi(szData);
		else
			SpecTempData.nPadLgGradientMinSize = 0;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use Relative Dark Gray Only"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseRlsDarkGrayOnly = _ttoi(szData);
		else
			SpecTempData.bUseRlsDarkGrayOnly = FALSE;	//20230417 add end

														//20160610 ndy add - Start
		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Use SmallFeature Inspection");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseSmallFeatureDefect = atoi(szData);
		else
			SpecTempData.bUseSmallFeatureDefect = TRUE;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset SmallFeature Extra Gray");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSmallFeatureExtraGray = atoi(szData);
		else
			SpecTempData.nSmallFeatureExtraGray = 80;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset SmallFeature PinHole Gray");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSmallFeaturePinHoleGray = atoi(szData);
		else
			SpecTempData.nSmallFeaturePinHoleGray = 230;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Use TinyFeature Inspection");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseTinyFeatureDefect = atoi(szData);
		else
			SpecTempData.bUseTinyFeatureDefect = TRUE;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset TinyFeature PAD Gray");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nTinyFeaturePADGray = atoi(szData);
		else
			SpecTempData.nTinyFeaturePADGray = 60;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset TinyFeature PAD Size Upper Ratio");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nTinyFeaturePADSizeUpperRatio = atoi(szData);
		else
			SpecTempData.nTinyFeaturePADSizeUpperRatio = 25;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset TinyFeature PAD Size Lower Ratio");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nTinyFeaturePADSizeLowerRatio = atoi(szData);
		else
			SpecTempData.nTinyFeaturePADSizeLowerRatio = 25;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset TinyFeature Hole Gray");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nTinyFeatureHoleGray = atoi(szData);
		else
			SpecTempData.nTinyFeatureHoleGray = 190;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset TinyFeature Hole Size Upper Ratio");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nTinyFeatureHoleSizeUpperRatio = atoi(szData);
		else
			SpecTempData.nTinyFeatureHoleSizeUpperRatio = 25;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset TinyFeature Hole Size Lower Ratio");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nTinyFeatureHoleSizeLowerRatio = atoi(szData);
		else
			SpecTempData.nTinyFeatureHoleSizeLowerRatio = 25;
		//20160610 ndy add - End
#endif
		//20160108 ndy add - End
		//------------------------------------------------
		//ADDON Hole Via Spec
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH In-Out Gray Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCO2InOutGrayDiff = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Inner Bright Def Percent"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCO2InnerBrightDefPercent = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Inner Saturation Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCO2InnerSaturationGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Inner Bright Search Diameter Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fCO2InnerBrightSrchDiaRatio = _ttof(szData);

		// 091214 jsy
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Inner Roughness"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fCO2InnerRoughness = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Inner Roughness Search Diameter Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fCO2InnerRoughnessSrchDiaRatio = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Use VD Ring Width Filter"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseVDRingWidthFilter = _ttoi(szData);

		//20100517 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Extension Hole Search"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bExtensionHoleSearch = _ttoi(szData);
		//end

		//130915 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Inspection Large Hole"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bInspLargeHole = _ttoi(szData);

		//140325 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Inspection Small Hole"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bInspSmallHole = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VD Ring Width Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fVDRingWidthPixel = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Ring Width Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fVHRingWidthPixel = _ttof(szData);

		//120515 jsy - start
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset BT Via Min Length Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nBTViaMin = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset BT Via Closing Number"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nBTVRingClosingNumber = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset BT Via Upper Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nBTVGraySpecUpper = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset BT Via Lower Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nBTVGraySpecLower = _ttof(szData);
		//120515 jsy - end



		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset HoleLand Radius Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fHoleLandSizeRatio = _ttof(szData);

		//20100511 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset AR Edge MinMax Diff Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nAREdgeDiffGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset AR Break Count"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nARBreakCnt = _ttoi(szData);
		//end

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset AR Find Line Add Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nARFindLineAddPixelTemp = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Find Line Add Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nCO2FindLineAddPixelTemp = _ttoi(szData);

		//20091117
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Hole Meas Dia Successive Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nHoleMeasDiaSuccessivePixel = _ttoi(szData);

		//130726 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset LargeCircle Check InnerOuter Pixels"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nLargeCircle_Check_InnerOuter_Pixels = _ttoi(szData);

		//140325 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset SmallCircle Check Inner Pixels"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSmallCircle_Check_Inner_Pixels = _ttoi(szData);

		//141105 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Diff Delta Pixel In ARCO2"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nDiffDeltaPxlARCO2 = _ttoi(szData);
		else
		{
#if CUSTOMER_COMPANY == SAMSUNG_DAEJEON
			SpecTempData.nDiffDeltaPxlARCO2 = 0;	//141105 hjc add	
#else
			SpecTempData.nDiffDeltaPxlARCO2 = 3;	//141105 hjc add	
#endif
		}

		//120131 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Hole Min Max Diff Gray Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nVDHoleMinMaxDiffGrayPlus = _ttoi(szData);

		//121206 jsy - start
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Dimple Lower Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nDimpleLowerGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Dimple Upper Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nDimpleUpperGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Dimple Copper Miss Num"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nDimpleCopperMissNum = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Dimple Copper Search Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fDimpleCopperSearchRatio = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Dimple Ring Num"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nDimpleRingNum = _ttoi(szData);
		//121206 jsy - end

		//ADDON Edge Violation Spec

		//2022 12 16 lgh add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset ApplySCurveEdge"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bApplySCurveEdge = _ttoi(szData);



		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Use fixed PM ID - Etching Pixels"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseFixedPMId = _ttoi(szData);

		//111003 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Extension Space Trace"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bExtensionSpaceTrace = _ttoi(szData);

		//111005 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Spectial Space MinMax Diff Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSpMinMaxDiffGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Fixed PM ID"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nFixedPMId = _ttoi(szData);

		//140425 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Apply Wide Open"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bChkWideOpen = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Wide Open Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nWideOpenPxl = _ttoi(szData);
		//140425 hjc add end

		//20200511 add
		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Pt Match Level"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nPtMatchLevelTemp = _ttoi(szData);
		else
		{
			if (0 < ::GetPrivateProfileString(_T("Spec"), _T("PtMatchLevel"), NULL, szData, sizeof(szData), SPEC_PARAM_PATH))
				m_nPtMatchLevelTemp = _ttoi(szData);
			else
				m_nPtMatchLevelTemp = 4;
		}
		//20210818 add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Apply Template Match"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bChkTemplateMatch = _ttoi(szData);

		//130829 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Check PAD Edge Limit"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bCheckPADEdgeLimitTemp = _ttoi(szData);

		//131105 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Edge Align Tolerence"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_nEdgeAlignTolTemp = _ttoi(szData);

		//131113 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Edge Gray Check Range"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_nEdgeGrayCheckRangeTemp = _ttoi(szData);

		//140121 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Diff Edge Delta Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_nDiffEdgeDeltaPixelTemp = _ttoi(szData);
		//160318 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Large Edge Nick Spec Down Size Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_fLargeEdgeNickSpecDownSizeTemp = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Large Edge Prot Spec Down Size Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_fLargeEdgeProtSpecDownSizeTemp = _ttof(szData);
		//131031 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Check Core Pad Tip"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bCheckCorePadTipTemp = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Core Neutral Zone"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCoreNeutralZone = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Core Diff Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCoreDiffGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Core Defect Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCoreDefSize = _ttoi(szData);
		//end

		//20101201 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset SPE Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSPEdgeNickGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset SPE Nick Size Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fSPEdgeNickWdDeltaGradViolation = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset SPE Prot Size Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fSPEdgeExcsWdDeltaGradViolation = _ttof(szData);

		//131123 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset SPEdge Gray Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSPEdgeGrayDiff = _ttoi(szData);	//131123 hjc add
															//end

															//	100429 jsy
		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Sud InOut Lower Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSudInOutLowerGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Sud InOut Upper Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSudInOutUpperGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Sud InOut Def Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fSudInOutDefSize = _ttof(szData);

		//150806 hjc add
		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset AICL Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fAICLTolerance = _ttof(szData);
		else
			SpecTempData.fAICLTolerance = 15.0f;

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset AICL Bound Check Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nBoundChkGray = _ttoi(szData);
		else
			SpecTempData.nBoundChkGray = 35;

		//150827 hjc add
		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset AICL Shrink Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nShrinkSize = _ttoi(szData);
		else
			SpecTempData.nShrinkSize = 0;

		//110620 hjc add
		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Check for Fiducial Mark"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bCheckFiducialMark = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Fiducial Mark Def Area"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fFMDArea = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Fiducial Mark Def SizeX"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fFMDSizeX = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Fiducial Mark Def SizeY"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fFMDSizeY = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Fiducial Mark PT Range Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fFMDPtRangePlus = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Fiducial Mark PT Score"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.fFMDPtScore = _ttof(szData);
		//end


		//161228 lgh
		pGlobalDoc->LoadInspModeTempDataFromPreset(INSP_MODE_NORMAL, strPath);
		pGlobalDoc->LoadInspModeTempDataFromPreset(INSP_MODE_RED, strPath);
		pGlobalDoc->LoadInspModeTempDataFromPreset(INSP_MODE_RED, strPath);
		

		////ADDON Inspection Logic Control Spec
		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Line Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspLineTemp = _ttoi(szData);

		////131104 hjc add
		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Line Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspSrLineTipExtTemp = _ttoi(szData);
		//else
		//m_bInspSrLineTipExtTemp = FALSE;

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Space Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspSpaceTemp = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Pad Pixel Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspPadPixelTemp = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Pat Pixel Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspPatPixelTemp = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Space Pixel Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_nInspSpacePixelTemp = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Virtual Drill Pixel Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspVDPixelTemp = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Hole Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspHoleTemp = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Via Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspViaTemp = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Dimple Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspDimpleTemp = _ttoi(szData);
		//else
		//m_bInspDimpleTemp = FALSE; //120502 jsy

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset CCL Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspCCLTemp = _ttoi(szData);
		//else
		//m_bInspCCLTemp = FALSE; //120502 jsy

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Only Via Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bUseOnlyViaInspTemp = _ttoi(szData);
		//else
		//m_bUseOnlyViaInspTemp = FALSE; //120502 jsy

		////120806 hjc add
		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset BarType Via Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspBarTypeViaTemp = _ttoi(szData);
		//else
		//m_bInspBarTypeViaTemp = FALSE;

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Edge Hole Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspContourARTemp = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Edge Via Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspContourVIATemp = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Edge Pad Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspContourLPTemp = _ttoi(szData);

		////110718 hjc add
		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Edge VD Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspContourVDTemp = _ttoi(szData);

		////131212 hjc add
		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset SREdge Space Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspSREdgeSpaceTemp = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));	//	100429 ljh
		//strIndex.Format(_T("Preset SUD In Out Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspSudInOutTemp = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));	//	100510 jsy
		//strIndex.Format(_T("Preset SPE Space Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspSPESpaceTemp = _ttoi(szData);
		
		//20100514 hjc add
		strTitle.Format(_T("Preset Pre System Parameters"));
		strIndex.Format(_T("Preset Open Check Cell Bound"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nOpenChkCellBndTemp = _ttoi(szData);

		strTitle.Format(_T("Preset Pre System Parameters"));
		strIndex.Format(_T("Preset Nick Check Cell Bound"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nNickChkCellBndTemp = _ttoi(szData);

		strTitle.Format(_T("Preset Pre System Parameters"));
		strIndex.Format(_T("Preset Excs Check Cell Bound"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nExcsChkCellBndTemp = _ttoi(szData);
		//end

		//120521 hjc add
		strTitle.Format(_T("Preset Pre System Parameters"));
		strIndex.Format(_T("Preset Check Good Range For Line"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nChkGoodRangeForLineTemp = _ttoi(szData);
		else
			m_nChkGoodRangeForLineTemp = 75;

		//111005 hjc add
		strTitle.Format(_T("Preset Pre System Parameters"));
		strIndex.Format(_T("Preset Min Space Check Bound Tip"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nMinSpCheckBoundTipTemp = _ttoi(szData);

		strTitle.Format(_T("Preset Pre System Parameters"));
		strIndex.Format(_T("Preset Min Space Check Bound"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nMinSpCheckBoundTemp = _ttoi(szData);

		strTitle.Format(_T("Preset Pre System Parameters"));
		strIndex.Format(_T("Preset Min Space Check Bound Edge"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nMinSpCheckBoundEdgeTemp = _ttoi(szData);

		strTitle.Format(_T("Preset Pre System Parameters"));
		strIndex.Format(_T("Preset UShort Check Bound Tip"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nUShortCheckBoundTipTemp = _ttoi(szData);
		//end


		strTitle.Format(_T("TextInspection"));
		strIndex.Format(_T("CharInspectionGray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nCharInspectionGray = _ttoi(szData);


		strTitle.Format(_T("TextInspection"));
		strIndex.Format(_T("dCharRegionUpperPercent"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.dCharRegionUpperPercent = _ttof(szData);

		strTitle.Format(_T("TextInspection"));
		strIndex.Format(_T("dCharRegionLowerPercent"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.dCharRegionLowerPercent = _ttof(szData);

	}
	else
	{

		strTitle.Format(_T("Preset Spec InsVia"));

		//170320 lgh add for insvia
		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Shift Tolerance"), NULL, szData, sizeof(szData), strPath))
			SpecData.ViaSpec.fViaHoleTolerance = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Size Upper Size Limit"), NULL, szData, sizeof(szData), strPath))
			SpecData.ViaSpec.fViaHoleDiaUpperPercent = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Size Lower Size Limit"), NULL, szData, sizeof(szData), strPath))
			SpecData.ViaSpec.fViaHoleDiaLowerPercent = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Inner Edge Gray"), NULL, szData, sizeof(szData), strPath))
			SpecData.ViaSpec.nViaInnerEdgeGray = _ttoi(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Inner Edge Size Pixel"), NULL, szData, sizeof(szData), strPath))
			SpecData.ViaSpec.fViaInnerEdgeSizePxl = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Outer Edge Gray"), NULL, szData, sizeof(szData), strPath))
			SpecData.ViaSpec.nViaOuterEdgeGray = _ttoi(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Outer Edge Size Pixel"), NULL, szData, sizeof(szData), strPath))
			SpecData.ViaSpec.fViaOuterEdgeSizePxl = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Taper Width"), NULL, szData, sizeof(szData), strPath))
			SpecData.ViaSpec.m_fTaperWidth = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Inner Diameter"), NULL, szData, sizeof(szData), strPath))
			SpecData.ViaSpec.m_fInnerDiamterWidthDiff = _ttof(szData);

		if (0 < ::GetPrivateProfileString(strTitle, _T("VH Inner Compactness"), NULL, szData, sizeof(szData), strPath))
			SpecData.ViaSpec.m_fInnerCompactness = _ttof(szData);

		//add end

		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("Preset Meas Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nNickGraySpec = _ttoi(szData);
		else
			SpecData.nNickGraySpec = SpecData.nThreshold[0];

		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("Preset Nick Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nOpenGraySpec = _ttoi(szData);

		//170403 hjc add
		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Meas Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nFineNickGraySpec = _ttoi(szData);
		else
			SpecData.nFineNickGraySpec = SpecData.nNickGraySpec;

		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Nick Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nFineOpenGraySpec = _ttoi(szData);
		else
			SpecData.nFineOpenGraySpec = SpecData.nNickGraySpec;
		//170403 hjc add end

		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("Preset Lead Open Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nLeadOpenGray = _ttoi(szData);
#if CUSTOMER_COMPANY == UMTC 

		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("Preset Min Line Width"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fMinLineWidth = _ttof(szData);

#endif
		BOOL bMLT = 0;
		strTitle.Format(_T("Preset Spec Line"));
		strIndex.Format(_T("New MultiLineSpec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			bMLT = _ttoi(szData);

		if (bMLT)
		{
			//멀티라인도 프리셋에 포함할 것인가... 고민...
			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Line Width Group Num"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.nLineWidthGroupNum = _ttoi(szData);
		}

		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Min Space Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		{
			StringToChar(szData, SpecData.szMinSPSize);
		}

		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Min Space Size Percent"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nMinSPPercent = _ttoi(szData);
		else
		{
			strTitle.Format(_T("Preset Spec Space"));
			strIndex.Format(_T("Preset Min Space Size"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				StringToChar(szData, SpecData.szMinSPSize);

			if (strcmp(SpecData.szMinSPSize, "Highest") == 0)	//150413 hjc add
				SpecData.nMinSPPercent = 90;
			if (strcmp(SpecData.szMinSPSize, "VeryHigh") == 0)
				SpecData.nMinSPPercent = 80;
			else if (strcmp(SpecData.szMinSPSize, "High") == 0)
				SpecData.nMinSPPercent = 70;
			else if (strcmp(SpecData.szMinSPSize, "Normal") == 0)
				SpecData.nMinSPPercent = 60;
			else if (strcmp(SpecData.szMinSPSize, "Low") == 0)
				SpecData.nMinSPPercent = 50;
			else if (strcmp(SpecData.szMinSPSize, "VeryLow") == 0)
				SpecData.nMinSPPercent = 40;
			else if (strcmp(SpecData.szMinSPSize, "Lowest") == 0)
				SpecData.nMinSPPercent = 30;
			else
				;

		}

		if (SpecData.nLineWidthGroupNum == 0)
		{
			if (m_bUseCombo)	//150611 hjc add
			{
				//170608 lgh fix
				strTitle.Format(_T("Preset Spec Line"));
				strIndex.Format(_T("Preset Nick Size"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				{
					StringToChar(szData, SpecData.szNickSize[0]);
					SpecData.nNickPercent[0] = _ttoi(m_pDlgSpec->GetNickRange(szData));
				}

				strTitle.Format(_T("Preset Spec Line"));
				strIndex.Format(_T("Preset Protrusion Size"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				{
					StringToChar(szData, SpecData.szProtrusionSize[0]);
					SpecData.nProtrusionPercent[0] = _ttoi(m_pDlgSpec->GetProtRange(szData));
				}

				strTitle.Format(_T("Preset Spec Fine Line"));
				strIndex.Format(_T("Preset Fine Nick Size"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				{
					StringToChar(szData, SpecData.szFineNickSize[0]);
					SpecData.nFineNickPercent[0] = _ttoi(m_pDlgSpec->GetNickRange(szData));
				}

				strTitle.Format(_T("Preset Spec Fine Line"));
				strIndex.Format(_T("Preset Fine Protrusion Size"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				{
					StringToChar(szData, SpecData.szFineProtrusionSize[0]);
					SpecData.nFineProtrusionPercent[0] = _ttoi(m_pDlgSpec->GetProtRange(szData));
				}
			}
			else
			{
				strTitle.Format(_T("Preset Spec Line"));	//150413 hjc add
				strIndex.Format(_T("Preset Nick Size Percent"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
					SpecData.nNickPercent[0] = _ttoi(szData);
				else
				{
					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Nick Size"));
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						StringToChar(szData, SpecData.szNickSize[0]);

					if (strcmp(SpecData.szNickSize[0], "Highest") == 0)
						SpecData.nNickPercent[0] = 90;
					else if (strcmp(SpecData.szNickSize[0], "VeryHigh") == 0)
						SpecData.nNickPercent[0] = 80;
					else if (strcmp(SpecData.szNickSize[0], "High") == 0)
						SpecData.nNickPercent[0] = 70;
					else if (strcmp(SpecData.szNickSize[0], "Normal") == 0)
						SpecData.nNickPercent[0] = 60;
					else if (strcmp(SpecData.szNickSize[0], "Low") == 0)
						SpecData.nNickPercent[0] = 50;
					else if (strcmp(SpecData.szNickSize[0], "VeryLow") == 0)
						SpecData.nNickPercent[0] = 40;
					else if (strcmp(SpecData.szNickSize[0], "Lowest") == 0)
						SpecData.nNickPercent[0] = 30;
					else if (strcmp(SpecTempData.szNickSize[0], "MaxLimit") == 0)
						SpecData.nNickPercent[0] = 10;
					else
						;
				}

				strTitle.Format(_T("Preset Spec Line"));	//150413 hjc add
				strIndex.Format(_T("Preset Protrusion Size Percent"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
					SpecData.nProtrusionPercent[0] = _ttoi(szData);
				else
				{
					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Protrusion Size"));
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						StringToChar(szData, SpecData.szProtrusionSize[0]);

					if (strcmp(SpecData.szProtrusionSize[0], "Highest") == 0)
						SpecData.nProtrusionPercent[0] = 110;
					if (strcmp(SpecData.szProtrusionSize[0], "VeryHigh") == 0)
						SpecData.nProtrusionPercent[0] = 120;
					else if (strcmp(SpecData.szProtrusionSize[0], "High") == 0)
						SpecData.nProtrusionPercent[0] = 130;
					else if (strcmp(SpecData.szProtrusionSize[0], "Normal") == 0)
						SpecData.nProtrusionPercent[0] = 140;
					else if (strcmp(SpecData.szProtrusionSize[0], "Low") == 0)
						SpecData.nProtrusionPercent[0] = 150;
					else if (strcmp(SpecData.szProtrusionSize[0], "VeryLow") == 0)
						SpecData.nProtrusionPercent[0] = 160;
					else if (strcmp(SpecData.szProtrusionSize[0], "Lowest") == 0)
						SpecData.nProtrusionPercent[0] = 170;
					else if (strcmp(SpecData.szProtrusionSize[0], "MaxLimit") == 0)
						SpecData.nProtrusionPercent[0] = 190;
					else
						;
				}

				strTitle.Format(_T("Preset Spec Fine Line"));
				strIndex.Format(_T("Preset Fine Nick Size Percent"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
					SpecData.nFineNickPercent[0] = _ttoi(szData);
				else	//150611 hjc add
				{
					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Nick Size"));
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						StringToChar(szData, SpecData.szFineNickSize[0]);

					if (strcmp(SpecData.szFineNickSize[0], "Highest") == 0)
						SpecData.nFineNickPercent[0] = 90;
					else if (strcmp(SpecData.szFineNickSize[0], "VeryHigh") == 0)
						SpecData.nFineNickPercent[0] = 80;
					else if (strcmp(SpecData.szFineNickSize[0], "High") == 0)
						SpecData.nFineNickPercent[0] = 70;
					else if (strcmp(SpecData.szFineNickSize[0], "Normal") == 0)
						SpecData.nFineNickPercent[0] = 60;
					else if (strcmp(SpecData.szFineNickSize[0], "Low") == 0)
						SpecData.nFineNickPercent[0] = 50;
					else if (strcmp(SpecData.szFineNickSize[0], "VeryLow") == 0)
						SpecData.nFineNickPercent[0] = 40;
					else if (strcmp(SpecData.szFineNickSize[0], "Lowest") == 0)
						SpecData.nFineNickPercent[0] = 30;
					else if (strcmp(SpecData.szFineNickSize[0], "MaxLimit") == 0)
						SpecData.nFineNickPercent[0] = 10;
					else
						;
				}

				strTitle.Format(_T("Preset Spec Fine Line"));
				strIndex.Format(_T("Preset Fine Protrusion Size Percent"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
					SpecData.nFineProtrusionPercent[0] = _ttoi(szData);
				else
				{
					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Protrusion Size"));
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						StringToChar(szData, SpecData.szFineProtrusionSize[0]);

					if (strcmp(SpecData.szFineNickSize[0], "Highest") == 0)
						SpecData.nFineNickPercent[0] = 90;
					else if (strcmp(SpecData.szFineNickSize[0], "VeryHigh") == 0)
						SpecData.nFineNickPercent[0] = 80;
					else if (strcmp(SpecData.szFineNickSize[0], "High") == 0)
						SpecData.nFineNickPercent[0] = 70;
					else if (strcmp(SpecData.szFineNickSize[0], "Normal") == 0)
						SpecData.nFineNickPercent[0] = 60;
					else if (strcmp(SpecData.szFineNickSize[0], "Low") == 0)
						SpecData.nFineNickPercent[0] = 50;
					else if (strcmp(SpecData.szFineNickSize[0], "VeryLow") == 0)
						SpecData.nFineNickPercent[0] = 40;
					else if (strcmp(SpecData.szFineNickSize[0], "Lowest") == 0)
						SpecData.nFineNickPercent[0] = 30;
					else if (strcmp(SpecData.szFineNickSize[0], "MaxLimit") == 0)
						SpecData.nFineNickPercent[0] = 10;
					else
						;
				}

			}

		}

		if (SpecData.nLineWidthGroupNum == 0)
		{
			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Nick NG Filter Percent"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.nNickNGFilterPercent[0] = _ttoi(szData);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Excs NG Filter Percent"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.nExcsNGFilterPercent[0] = _ttoi(szData);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Line WD Delta Grad Violation"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.fLineWdDeltaGradViolation[0] = _ttof(szData);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Excs WD Delta Grad Violation"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.fExcsWdDeltaGradViolation[0] = _ttof(szData);
		}

		if (SpecData.nLineWidthGroupNum > 10000)
		{
			//GvisMessageBox(_T("[MSG650] Line Width Group number Error!!!!!"));
			SpecData.nLineWidthGroupNum = 0;
		}

		if (SpecData.nLineWidthGroupNum > 0)		//20091019 hjc mod
		{
			if (bMLT)
			{
				for (idx = 1; idx < SpecData.nLineWidthGroupNum + 1; idx++)
				{
					if (m_bUseCombo)	//150611 hjc add
					{
						//170608 lgh fix
						strTitle.Format(_T("Preset Spec Line"));
						strIndex.Format(_T("Preset Nick Size%d"), idx);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						{
							StringToChar(szData, SpecData.szNickSize[idx]);
							SpecData.nNickPercent[idx] = _ttoi(m_pDlgSpec->GetNickRange(szData));
						}

						strTitle.Format(_T("Preset Spec Line"));
						strIndex.Format(_T("Preset Protrusion Size%d"), idx);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						{
							StringToChar(szData, SpecData.szProtrusionSize[idx]);
							SpecData.nProtrusionPercent[idx] = _ttoi(m_pDlgSpec->GetProtRange(szData));
						}

						strTitle.Format(_T("Preset Spec Fine Line"));
						strIndex.Format(_T("Preset Fine Nick Size%d"), idx);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						{
							StringToChar(szData, SpecData.szFineNickSize[idx]);
							SpecData.nFineNickPercent[idx] = _ttoi(m_pDlgSpec->GetNickRange(szData));
						}

						strTitle.Format(_T("Preset Spec Fine Line"));
						strIndex.Format(_T("Preset Fine Protrusion Size%d"), idx);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						{
							StringToChar(szData, SpecData.szFineProtrusionSize[idx]);
							SpecData.nFineProtrusionPercent[idx] = _ttoi(m_pDlgSpec->GetProtRange(szData));
						}
					}
					else
					{
						strTitle.Format(_T("Preset Spec Line"));	//150413 hjc add
						strIndex.Format(_T("Preset Nick Size Percent%d"), idx);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
							SpecData.nNickPercent[idx] = _ttoi(szData);
						else
						{
							strTitle.Format(_T("Preset Spec Line"));
							strIndex.Format(_T("Preset Nick Size%d"), idx);
							if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
								StringToChar(szData, SpecData.szNickSize[idx]);

							if (strcmp(SpecData.szNickSize[idx], "Highest") == 0)
								SpecData.nNickPercent[idx] = 90;
							else if (strcmp(SpecData.szNickSize[idx], "VeryHigh") == 0)
								SpecData.nNickPercent[idx] = 80;
							else if (strcmp(SpecData.szNickSize[idx], "High") == 0)
								SpecData.nNickPercent[idx] = 70;
							else if (strcmp(SpecData.szNickSize[idx], "Normal") == 0)
								SpecData.nNickPercent[idx] = 60;
							else if (strcmp(SpecData.szNickSize[idx], "Low") == 0)
								SpecData.nNickPercent[idx] = 50;
							else if (strcmp(SpecData.szNickSize[idx], "VeryLow") == 0)
								SpecData.nNickPercent[idx] = 40;
							else if (strcmp(SpecData.szNickSize[idx], "Lowest") == 0)
								SpecData.nNickPercent[idx] = 30;
							else if (strcmp(SpecTempData.szNickSize[idx], "MaxLimit") == 0)
								SpecData.nNickPercent[idx] = 10;
							else
								;
						}

						strTitle.Format(_T("Preset Spec Line"));	//150413 hjc add
						strIndex.Format(_T("Preset Protrusion Size Percent%d"), idx);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
							SpecData.nProtrusionPercent[idx] = _ttoi(szData);
						else
						{
							strTitle.Format(_T("Preset Spec Line"));
							strIndex.Format(_T("Preset Protrusion Size%d"), idx);
							if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
								StringToChar(szData, SpecData.szProtrusionSize[idx]);

							if (strcmp(SpecData.szProtrusionSize[idx], "Highest") == 0)
								SpecData.nProtrusionPercent[idx] = 110;
							if (strcmp(SpecData.szProtrusionSize[idx], "VeryHigh") == 0)
								SpecData.nProtrusionPercent[idx] = 120;
							else if (strcmp(SpecData.szProtrusionSize[idx], "High") == 0)
								SpecData.nProtrusionPercent[idx] = 130;
							else if (strcmp(SpecData.szProtrusionSize[idx], "Normal") == 0)
								SpecData.nProtrusionPercent[idx] = 140;
							else if (strcmp(SpecData.szProtrusionSize[idx], "Low") == 0)
								SpecData.nProtrusionPercent[idx] = 150;
							else if (strcmp(SpecData.szProtrusionSize[idx], "VeryLow") == 0)
								SpecData.nProtrusionPercent[idx] = 160;
							else if (strcmp(SpecData.szProtrusionSize[idx], "Lowest") == 0)
								SpecData.nProtrusionPercent[idx] = 170;
							else if (strcmp(SpecData.szProtrusionSize[idx], "MaxLimit") == 0)
								SpecData.nProtrusionPercent[idx] = 190;
							else
								;
						}

						strTitle.Format(_T("Preset Spec Fine Line"));
						strIndex.Format(_T("Preset Fine Nick Size Percent%d"), idx);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
							SpecData.nFineNickPercent[idx] = _ttoi(szData);
						else	//150611 hjc add
						{
							strTitle.Format(_T("Preset Spec Fine Line"));
							strIndex.Format(_T("Preset Fine Nick Size%d"), idx);
							if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
								StringToChar(szData, SpecData.szFineNickSize[idx]);

							if (strcmp(SpecData.szFineNickSize[idx], "Highest") == 0)
								SpecData.nFineNickPercent[idx] = 90;
							else if (strcmp(SpecData.szFineNickSize[idx], "VeryHigh") == 0)
								SpecData.nFineNickPercent[idx] = 80;
							else if (strcmp(SpecData.szFineNickSize[idx], "High") == 0)
								SpecData.nFineNickPercent[idx] = 70;
							else if (strcmp(SpecData.szFineNickSize[idx], "Normal") == 0)
								SpecData.nFineNickPercent[idx] = 60;
							else if (strcmp(SpecData.szFineNickSize[idx], "Low") == 0)
								SpecData.nFineNickPercent[idx] = 50;
							else if (strcmp(SpecData.szFineNickSize[idx], "VeryLow") == 0)
								SpecData.nFineNickPercent[idx] = 40;
							else if (strcmp(SpecData.szFineNickSize[idx], "Lowest") == 0)
								SpecData.nFineNickPercent[idx] = 30;
							else if (strcmp(SpecData.szFineNickSize[0], "MaxLimit") == 0)
								SpecData.nFineNickPercent[idx] = 10;
							else
								;
						}

						strTitle.Format(_T("Preset Spec Fine Line"));
						strIndex.Format(_T("Preset Fine Protrusion Size Percent%d"), idx);
						if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
							SpecData.nFineProtrusionPercent[idx] = _ttoi(szData);
						else
						{
							strTitle.Format(_T("Preset Spec Fine Line"));
							strIndex.Format(_T("Preset Fine Protrusion Size%d"), idx);
							if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
								StringToChar(szData, SpecData.szFineProtrusionSize[idx]);

							if (strcmp(SpecData.szFineNickSize[idx], "Highest") == 0)
								SpecData.nFineNickPercent[idx] = 90;
							else if (strcmp(SpecData.szFineNickSize[idx], "VeryHigh") == 0)
								SpecData.nFineNickPercent[idx] = 80;
							else if (strcmp(SpecData.szFineNickSize[idx], "High") == 0)
								SpecData.nFineNickPercent[idx] = 70;
							else if (strcmp(SpecData.szFineNickSize[idx], "Normal") == 0)
								SpecData.nFineNickPercent[idx] = 60;
							else if (strcmp(SpecData.szFineNickSize[idx], "Low") == 0)
								SpecData.nFineNickPercent[idx] = 50;
							else if (strcmp(SpecData.szFineNickSize[idx], "VeryLow") == 0)
								SpecData.nFineNickPercent[idx] = 40;
							else if (strcmp(SpecData.szFineNickSize[idx], "Lowest") == 0)
								SpecData.nFineNickPercent[idx] = 30;
							else if (strcmp(SpecData.szFineNickSize[idx], "MaxLimit") == 0)
								SpecData.nFineNickPercent[idx] = 10;
							else
								;
						}

					}


					if (m_bUseCombo)
					{
						StringToChar(pGlobalDoc->GetNickRangeReverse(SpecData.nFineNickPercent[idx]), SpecData.szFineNickSize[idx]);
						StringToChar(pGlobalDoc->GetProtRangeReverse(SpecData.nFineProtrusionPercent[idx]), SpecData.szFineProtrusionSize[idx]);
						StringToChar(pGlobalDoc->GetNickRangeReverse(SpecData.nNickPercent[idx]), SpecData.szNickSize[idx]);
						StringToChar(pGlobalDoc->GetProtRangeReverse(SpecData.nProtrusionPercent[idx]), SpecData.szProtrusionSize[idx]);
					}


					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Nick NG Filter Percent%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecData.nNickNGFilterPercent[idx] = _ttoi(szData);

					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Excs NG Filter Percent%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecData.nExcsNGFilterPercent[idx] = _ttoi(szData);

					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Line WD Delta Grad Violation%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecData.fLineWdDeltaGradViolation[idx] = _ttof(szData);

					strTitle.Format(_T("Preset Spec Line"));
					strIndex.Format(_T("Preset Excs WD Delta Grad Violation%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecData.fExcsWdDeltaGradViolation[idx] = _ttof(szData);
				}
			}
		}
		else
		{
			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Line Width Group0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.fLineWidthGroup[0] = _ttof(szData);

			//170524 lgh
			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Line Width GroupLower0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.fLineWidthGroupLower[0] = _ttof(szData);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Narrow Trace Violation0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.fNarrowTraceViolation[0] = _ttof(szData);

			strTitle.Format(_T("Preset Spec Line"));
			strIndex.Format(_T("Preset Wide Trace Violation0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.fWideTraceViolation[0] = _ttof(szData);
			
			////161205 lgh
			//strTitle.Format(_T("Preset Spec Line"));
			//strIndex.Format(_T("Preset TraceWidthAdjustVal0"));
			//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			//SpecData.fLineWidthGroupAdjusted[0] = _ttof(szData);
			
		}

		//Fine Line Spec
		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine Min Line Width"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fFineMinLineWidth = _ttof(szData);

		if (SpecData.nLineWidthGroupNum == 0 || bMLT)
		{
			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Nick NG Filter Percent"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.nFineNickNGFilterPercent[0] = _ttoi(szData);

			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Excs NG Filter Percent"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.nFineExcsNGFilterPercent[0] = _ttoi(szData);

			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Line WD Delta Grad Violation"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.fFineLineWdDeltaGradViolation[0] = _ttof(szData);

			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Excs WD Delta Grad Violation"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.fFineExcsWdDeltaGradViolation[0] = _ttof(szData);
		}

		//잘못하면 기존 그룹이 날아간다. 의도치 않게.ㅋ
		if (SpecData.nLineWidthGroupNum > 0)		//20091019 hjc mod
		{
			if (bMLT)
			{
				for (idx = 1; idx < SpecData.nLineWidthGroupNum + 1; idx++)
				{
					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Nick NG Filter Percent%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecData.nFineNickNGFilterPercent[idx] = _ttoi(szData);

					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Excs NG Filter Percent%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecData.nFineExcsNGFilterPercent[idx] = _ttoi(szData);

					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Line WD Delta Grad Violation%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecData.fFineLineWdDeltaGradViolation[idx] = _ttof(szData);

					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Excs WD Delta Grad Violation%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecData.fFineExcsWdDeltaGradViolation[idx] = _ttof(szData);

					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Narrow Trace Violation%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecData.fFineNarrowTraceViolation[idx] = _ttof(szData);

					strTitle.Format(_T("Preset Spec Fine Line"));
					strIndex.Format(_T("Preset Fine Wide Trace Violation%d"), idx);
					if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
						SpecData.fFineWideTraceViolation[idx] = _ttof(szData);

				}
			}
		}
		else
		{
			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Line Width Group0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.fFineLineWidthGroup[0] = _ttof(szData);

			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Narrow Trace Violation0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.fFineNarrowTraceViolation[0] = _ttof(szData);

			strTitle.Format(_T("Preset Spec Fine Line"));
			strIndex.Format(_T("Preset Fine Wide Trace Violation0"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.fFineWideTraceViolation[0] = _ttof(szData);
		}
		//150515 hjc add end

		//Space Spec
		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Min Space Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nMinSpaceGraySpec = _ttoi(szData);

		//20090420 hjc add
		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Neib Space Gray Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nNeibSpGrayDiff = _ttoi(szData);

		//150529 hjc mod
		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset US Dark Gray Minus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nUSDarkGrayMinus = _ttoi(szData);
		else
		{
			strTitle.Format(_T("Preset Spec AddOn Line"));
			strIndex.Format(_T("Preset US Dark Gray Minus"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.nUSDarkGrayMinus = _ttoi(szData);
			else
				SpecData.nUSDarkGrayMinus = 45;
		}

#if CUSTOMER_COMPANY == UMTC || CUSTOMER_COMPANY == SHINKO_DENKKI
#if CUSTOMER_COMPANY ==DAEDUCK_APERIO
		if (!g_bUseWidthCompensation)
		{
			strTitle.Format(_T("Preset Spec Space"));
			strIndex.Format(_T("Preset Min Space Width"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.fMinSpWidth = _ttof(szData);
		}
#else
		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Min Space Width"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fMinSpWidth = _ttof(szData);
#endif
#endif
		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Space NG Filter Percent"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nSpaceNGFilterPercent = _ttoi(szData);

		//20090405 hjc
		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Space WD Delta Outer Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fSpWdDeltaOuterGradViolation = _ttof(szData);

		strTitle.Format(_T("Preset Spec Space"));
		strIndex.Format(_T("Preset Space WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fSpWdDeltaGradViolation = _ttof(szData);

		//		strTitle.Format(_T("Preset Spec Space");
		//		strIndex.Format(_T("Preset HLG Space Width Percent");
		//		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//			SpecData.fHLGSpWidthPercent = _ttof(szData);

		strTitle.Format(_T("Preset Spec Space"));	//121226 hjc add
		strIndex.Format(_T("Preset Fine Min Space Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fFineMinSpWidth = _ttof(szData);

		//Ext/Pin Hole Spec
		//150823 hjc add
		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Virtual Drill Diff Bright Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nVDrillDiffBrightGray = _ttoi(szData);
		else
		{
			if (m_nVDMeanDiff > 0)
				SpecData.nVDrillDiffBrightGray = 255 - m_nVDMeanDiff;
			else
			{
#if MACHINE_MODEL == INSPRO_GM_PLUS || MACHINE_MODEL == INSMART_GM4000 || MACHINE_MODEL == INSPRO_GM 
				SpecData.nVDrillDiffBrightGray = 0;	//150823 hjc mod
#else
				SpecData.nVDrillDiffBrightGray = 40;
#endif
			}
		}

		//150606 hjc add
		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Virtual Drill Diff Dark Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nVDrillDiffDarkGray = _ttoi(szData);
		else
		{
			strTitle.Format(_T("Preset Spec Extra PinHole"));
			strIndex.Format(_T("Preset Virtual Drill Pixel Gray"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.nVDrillDiffDarkGray = _ttoi(szData);
			else
				SpecData.nVDrillDiffDarkGray = 120;
		}

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Virtual Drill Pad Precision"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fVDPadPrecName = _ttof(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Virtual Drill Pad Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fVDPadMin = _ttof(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Pad Void Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nPADVoidGraySpec = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Pad Void Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fPADVoidMin = _ttof(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Pad Tip Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fPADTipMin = _ttof(szData);

		//20100322 hjc add
		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset HoleLand Void Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nHoleLandVoidGray = _ttoi(szData);
		else
			SpecData.nHoleLandVoidGray = SpecData.nPADVoidGraySpec;

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset CO2Land Void Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCO2LandVoidGraySpec = _ttoi(szData);
		else
			SpecData.nCO2LandVoidGraySpec = 120;

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset CO2Land Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fCO2LandMin = _ttof(szData);
		else
			SpecData.fCO2LandMin = 15 * SizeData[COMMON_PARAMETER].fPixelSize;

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset CO2Land Align Mode"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			StringToChar(szData, SpecData.szCO2LandAlignMode);
		else
			strcpy(SpecData.szCO2LandAlignMode, "Yes");
		//end

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset AR Land Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fARLandMin = _ttof(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Hole Fill Ext"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fHoleFillExt = _ttof(szData);

		//20100323 hjc add
		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset CO2Hole Fill Ext"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fCO2HoleFillExt = _ttof(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Fine PAD Void Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nFinePADVoidGraySpec = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Fine PAD Void Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fFinePADVoidMin = _ttof(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Pin Hole Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nPinHoleGraySpec = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Pin Hole Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fPinHoleMin = _ttof(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Island Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nIsLandGraySpec = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Island Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fIsLandMin = _ttof(szData);
		//20090412 hjc
		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Island Extra Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nIsLandExtGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Island Extra Min"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fIsLandExtMin = _ttof(szData);

		//jun 20120903 for LG_CCL-Inspector
		strTitle.Format(_T("Preset Spec CCL Inspection"));
		strIndex.Format(_T("Preset CCL Gray Spec"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCCLGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec CCL Inspection"));
		strIndex.Format(_T("Preset CCL Circularity"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fCCLCircularity = _ttof(szData);

		strTitle.Format(_T("Preset Spec CCL Inspection"));
		strIndex.Format(_T("Preset CCL Defect Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fCCLDefSize = _ttof(szData);

		//20090420 hjc add
		strTitle.Format(_T("Preset Spec Extra PinHole"));
		strIndex.Format(_T("Preset Virtual Drill Location Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fVDLocationTolerance = _ttof(szData);

		//Hole/VH Spec
		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fHoleTolerance = _ttof(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Dia Upper"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fHoleDiaUpper = _ttof(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Dia Lower"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fHoleDiaLower = _ttof(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Open Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nHoleOpenGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Missing Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nHoleMissingGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Inner Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nHoleInnerGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole RL Precision Name"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			StringToChar(szData, SpecData.szHoleRLPrecName);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset Hole Def Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nHoleDefNum = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset VH Mode"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			StringToChar(szData, SpecData.szVHMode);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset CO2 Missing Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCO2MissingGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset CO2 Hole Num"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCO2HoleNum = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset CO2 Open Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCO2OpenGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset CO2 Miss Align Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCO2MisAgnGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset CO2 Miss Align Defect Percent"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCO2MisAgnDefPercent = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset VH Edge Thr Diff Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nVHEdgeThrDiffGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset VH BreakOut Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nVHBreakOutGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset VH Dissmear Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nVHDissmearGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Hole VH"));
		strIndex.Format(_T("Preset VH Conti BreakOut Num"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nVHContiBreakOutNum = _ttoi(szData);

		//Edge Spec
		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Pad Edge Nick Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nPadEdgeNickGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Edge"));	//120105 hjc add
		strIndex.Format(_T("Preset Pad Edge Neib Gray Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nPadEdgeNeibGrayDiff = _ttoi(szData);

		//140127 hjc add
		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Pad Edge BA Diff Dark Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nPadEdgeBADiffDarkGray = _ttoi(szData);
		else
			SpecData.nPadEdgeBADiffDarkGray = 60;

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Pad Edge Nick WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fPadEdgeNickWdDeltaGradViolation = _ttof(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Pad Edge Excs WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fPadEdgeExcsWdDeltaGradViolation = _ttof(szData);

		//20090420 hjc add
		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Pad VD Edge Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nPadVDEdgeGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Pad VD Edge Wd Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fPadVDEdgeWdDeltaGradViolation = _ttof(szData);
		//------------------

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Hole Edge Nick Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nHoleEdgeNickGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Edge"));	//120109 hjc add
		strIndex.Format(_T("Preset Hole Edge Neib Gray Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nHoleEdgeNeibGrayDiff = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Hole Edge Nick WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fHoleEdgeNickWdDeltaGradViolation = _ttof(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Hole Edge Excs WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fHoleEdgeExcsWdDeltaGradViolation = _ttof(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Via Edge Nick Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nViaEdgeNickGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Edge"));	//120109 hjc add
		strIndex.Format(_T("Preset Via Edge Neib Gray Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nViaEdgeNeibGrayDiff = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Via Edge Nick WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fViaEdgeNickWdDeltaGradViolation = _ttof(szData);

		strTitle.Format(_T("Preset Spec Edge"));
		strIndex.Format(_T("Preset Via Edge Excs WD Delta Grad Violation"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fViaEdgeExcsWdDeltaGradViolation = _ttof(szData);

		//Model Spec
		strTitle.Format(_T("Preset Spec Model"));
		strIndex.Format(_T("Preset PTModel Search Range Extension"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nPtSrchRngExt = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Model"));
		strIndex.Format(_T("Preset Align Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nAlignTolerance = _ttoi(szData);

		strTitle.Format(_T("Preset Spec Model"));
		strIndex.Format(_T("Preset Theta Align"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_strThetaAlign.Format(_T("%s"), szData);

		strTitle.Format(_T("Preset Spec Model"));
		strIndex.Format(_T("Preset Defect Mask Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fDefMaskSize = _ttof(szData);

		strTitle.Format(_T("Preset Spec Model"));
		strIndex.Format(_T("Preset Near Defect Length"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fNearDefLen = _ttof(szData);

		//20100210 hjc add
		if (m_bUseMultiVaccumControl)
		{
			strTitle.Format(_T("Preset Spec Model"));
			strIndex.Format(_T("Preset Select Vaccum"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				StringToChar(szData, SpecData.strSelectVaccum);

			if (SpecData.strSelectVaccum == "Both")	//130215 hjc add
				SpecData.nSelectVaccum = 1;
			else if (SpecData.strSelectVaccum == "FirstOnly")
				SpecData.nSelectVaccum = 2;
		}
		else
		{
			strTitle.Format(_T("Preset Spec Model"));
			strIndex.Format(_T("Preset Select Vaccum"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				strcpy(SpecData.strSelectVaccum, "Both");

			SpecData.nSelectVaccum = 1;		//130215 hjc add
		}

		//ADDON Line Spec
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset GTC Shake Extend"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bGTCShakeExtend = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Stella Method"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bApplyStellaMethod = _ttoi(szData);

		//20090902 hjc
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Inclined Nick"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkInclinedNick = _ttoi(szData);

		//111024 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Inclined Short"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkInclinedShort = _ttoi(szData);

		//110518 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Inclined Space"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkInclinedSpace = _ttoi(szData);

		//110526 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Apply Skip Check In VD Line"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bSkipChkInVDLine = _ttoi(szData);

		//121128 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Apply Silver Paste Via"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bCheckSilverPasteVia = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Apply VH Out Break Count"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nVHOutBreakCnt = _ttoi(szData);
		//end

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));	//20230508 add
		strIndex.Format(_T("Preset Apply VH Taping Tolerence"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nVHTapingTolerence = _ttoi(szData);
		else
			SpecData.nVHTapingTolerence = 0;

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));	//20230627 add
		strIndex.Format(_T("Preset Apply VH Taping Min Max Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nVHTapingMinMaxDiff = _ttoi(szData);
		else
			SpecData.nVHTapingMinMaxDiff = 0;

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));	//20230628 add
		strIndex.Format(_T("Preset Check Via Multi Dia"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bChkViaMultidia = _ttoi(szData);
		else
			SpecData.bChkViaMultidia = FALSE;

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));	//20230711 add
		strIndex.Format(_T("Preset Apply VH Inner Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nVHInnerGray = _ttoi(szData);
		else
			SpecData.nVHInnerGray = 100;

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));	//20230713 add
		strIndex.Format(_T("Preset Apply VH Min Max Dia Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nVHMinMaxDiaRatio = _ttoi(szData);
		else
			SpecTempData.nVHMinMaxDiaRatio = 60;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Inclined Oblique Space"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkInclinedObliqueSpace = _ttoi(szData);
		//end

		//20220316 LGH ADD
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset CheckProtFromSpaceWidth"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.m_bCheckProtFromSpaceWidth = _ttoi(szData);

		//20220513 add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Use Large Align Shift"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bLargeAlignShift = _ttoi(szData);

		//20220823 add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Use Rough Surface Pattern"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bRoughSurface = _ttoi(szData);

		//20120418-ndy
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Inclined Oblique Line"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkInclinedObliqueLine = _ttoi(szData);

		//16128 lgh
		pGlobalDoc->LoadMachineLogicModeFromPreset(INSP_MODE_NORMAL, strPath);
		pGlobalDoc->LoadMachineLogicModeFromPreset(INSP_MODE_RED, strPath);
		pGlobalDoc->LoadMachineLogicModeFromPreset(INSP_MODE_BLUE, strPath);


		//20091203 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Measurement Method"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bCheckMeasurementMethod = _ttoi(szData);
		else
			pMainFrame->m_bCheckMeasurementMethod = FALSE;

		//140425 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("PatternTipDeadZone"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bPatternTipDeadZone = _ttoi(szData);
		else
			pMainFrame->m_bPatternTipDeadZone = FALSE;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Post Filtering"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bApplyPostFiltering = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Space Post Filtering"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bApplySpaceFiltering = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Line Noise Filter Value"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_nLineNoiseFilter = _ttoi(szData);

		// 20090514 jsy
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Noise Filter Value"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_nSpaceNoiseFilter = _ttoi(szData);

		// 20090525 ljg 
		strTitle.Format(_T("Preset Pre System"));
		strIndex.Format(_T("Preset Defect Merge Ratio OnTrace"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_fDefectMergeRatioOnTrace = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Pad Tip Precision Nick Check"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fPADTipNickPrecSpec = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));	//130528 hjc add
		strIndex.Format(_T("Preset Space Neib Dark Gray Tot"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nNeibDarkGrayTot = _ttoi(szData);
		else
			SpecData.nNeibDarkGrayTot = 2;

		strTitle.Format(_T("Preset Spec AddOn Line"));	//130528 hjc add
		strIndex.Format(_T("Preset Space Neib Bright Gray Tot"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nNeibBrightGrayTot = _ttoi(szData);
		else
			SpecData.nNeibBrightGrayTot = 1;

		strTitle.Format(_T("Preset Pre System"));	// 130925 ljg add
		strIndex.Format(_T("Preset Sp Bound Search Limit Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nSpBoundSearchLimitPixel = _ttoi(szData);
		else
			SpecData.nSpBoundSearchLimitPixel = 1;

		strTitle.Format(_T("Preset Pre System"));
		strIndex.Format(_T("Preset Sp Min Max Alpha Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fSpMMDiffAlphaPlus = _ttof(szData);
		else
			SpecData.fSpMMDiffAlphaPlus = 0.5;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Pad Tip Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fSROEExceptLen = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Pattern Tip Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fOEExceptLen = _ttof(szData);

		//150625 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Tip Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fOEExceptSpaceLen = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Hole Tip Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fARCO2JuncExceptLen = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Trace Shake Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nShakeTolerance = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Line Width StepUp Sensitivity"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_fLineWidthStepUpSensitivity = _ttof(szData);
		else
		{
#if MACHINE_MODEL == INSPRO_GM_PLUS || MACHINE_MODEL == INSMART_GM4000 || MACHINE_MODEL == INSPRO_GM
			pMainFrame->m_fLineWidthStepUpSensitivity = 0.0;	              // Default : 0.5f
#else
			pMainFrame->m_fLineWidthStepUpSensitivity = 0.5f;
#endif
		}

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Under Layer Effect Gray Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nSpaceUnderLayerEffectGrayPlus = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));		//20230704 add
		strIndex.Format(_T("Preset Center Line Offset Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCenterlineOffsetTolerance = _ttoi(szData);
		else
			SpecData.nCenterlineOffsetTolerance = 4;

		//160330 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Under Layer Cut Threshold"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nUnderLayerCutTh = _ttoi(szData);
		else
			SpecData.nUnderLayerCutTh = 0;	//20220823 mod 75;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Under Layer Lower Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nSpUnderLayerLowerGray = _ttoi(szData);
		else
			SpecData.nSpUnderLayerLowerGray = 15;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Under Layer Upper Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nSpUnderLayerUpperGray = _ttoi(szData);
		else
			SpecData.nSpUnderLayerUpperGray = 25;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Space Under Layer Def Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fSpUnderLayerDefSize = _ttof(szData);
		else
			SpecData.fSpUnderLayerDefSize = 3.0f;
		//160330 hjc add end
		//110601 hjc add
		//strTitle.Format(_T("Preset Spec AddOn Line"));
		//strIndex.Format(_T("Preset Apply HalfSide Relative Bright Gray"));

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset HalfSide Nick Diff Bright Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nHalfSideNickDiffBrightGray = _ttoi(szData);
		else
			SpecData.nHalfSideNickDiffBrightGray = 35;	//110601 hjc add	//121224 hjc mod


		strTitle.Format(_T("Preset Spec AddOn Line"));		//121224 hjc mod
		strIndex.Format(_T("Preset HalfSide Nick Diff Dark Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nHalfSideNickDiffDarkGray = _ttoi(szData);
		//end

		//170403 hjc add
		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine HalfSide Nick Diff Bright Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nFineHalfSideNickDiffBrightGray = _ttoi(szData);
		else
			SpecData.nFineHalfSideNickDiffBrightGray = 35;

		strTitle.Format(_T("Preset Spec Fine Line"));
		strIndex.Format(_T("Preset Fine HalfSide Nick Diff Dark Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nFineHalfSideNickDiffDarkGray = _ttoi(szData);
		else
			SpecData.nFineHalfSideNickDiffDarkGray = 35;
		//170403 hjc add end

		//111029 hjc add		
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Dish Down"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkDishDown = _ttoi(szData);

		//110701 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset PM Image Threshold Enhancement"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bPMImgThresholdEnhancement = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset PM Image Adaptive Threshold Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fAdaptiveThresholdRatio = _ttof(szData);
		//end

		//111011 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply In Land Line"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkInLandLine = _ttoi(szData);

		//150817 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Edge Spec Down"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bEdgeSpecDown = _ttoi(szData);
		else
			pMainFrame->m_bEdgeSpecDown = FALSE;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Edge Spec Down Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nEdgeSpecDownPxl = _ttoi(szData);
		else
			SpecData.nEdgeSpecDownPxl = 1;

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Exclude Spire"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bChkExcludeSpire = _ttoi(szData);
		else
		{
#if MACHINE_MODEL == INSPRO_GM_PLUS || MACHINE_MODEL == INSMART_GM4000 || MACHINE_MODEL == INSPRO_GM
			pMainFrame->m_bChkExcludeSpire = TRUE;
#else
			pMainFrame->m_bChkExcludeSpire = FALSE;
#endif
		}

		//130409 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset CompensateWD For Additive Process"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bCompensateWDForAdditiveProcess = _ttoi(szData);
		else
			pMainFrame->m_bCompensateWDForAdditiveProcess = TRUE;


		//150421 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Apply Master Real Same"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bMasterRealSameFlag = _ttoi(szData);
		else
			pMainFrame->m_bMasterRealSameFlag = TRUE;

		//131216 hjc add
		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Check VD Neiber Space"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		{
			bTempData = _ttoi(szData);
			//141012 hjc mod
			if (bTempData)
			{
				strTitle.Format(_T("Preset Spec AddOn Line"));	//131216 hjc add
				strIndex.Format(_T("Preset VD Neib PM MinMax Diff Gray"));
				if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
					SpecData.nVDNeibPMMinMaxDiffGray = _ttoi(szData);
				else
					SpecData.nVDNeibPMMinMaxDiffGray = 40;
			}
			else
				SpecData.nVDNeibPMMinMaxDiffGray = 0;
		}
		else
		{
			strTitle.Format(_T("Preset Spec AddOn Line"));	//131216 hjc add
			strIndex.Format(_T("Preset VD Neib PM MinMax Diff Gray"));
			if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
				SpecData.nVDNeibPMMinMaxDiffGray = _ttoi(szData);
			else
				SpecData.nVDNeibPMMinMaxDiffGray = 40;
		}

		strTitle.Format(_T("Preset Spec AddOn Line"));
		strIndex.Format(_T("Preset Linked Defect Count"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fLinkedDefectCntPix = _ttof(szData);

		//ADDON Extra PinHole Spec
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Dark Pinhole Gray Minus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nDarkPinHoleGrayMinus = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Bright PAD Def Gray Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nBrightPADDefGrayPlus = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Dark PAD Def Gray Minus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nDarkPADDefGrayMinus = _ttoi(szData);

		//130528 hjc add
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Relative Pad Defect Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fRlsPadDefSize = _ttof(szData);
		else
			SpecData.fRlsPadDefSize = 50.0f;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Relative PinHole Defect Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fRlsPinHoleDefSize = _ttof(szData);
		else
			SpecData.fRlsPinHoleDefSize = 60.0f;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));	//130529 hjc add
		strIndex.Format(_T("Preset Exclude PadDef Edge Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nExcludePadDefEdgePixel = _ttoi(szData);
		else
			SpecData.nExcludePadDefEdgePixel = 3;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));	//130529 hjc add
		strIndex.Format(_T("Preset Exclude PinHole Edge Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nExcludePinHoleEdgePixel = _ttoi(szData);
		else
			SpecData.nExcludePinHoleEdgePixel = 5;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PinHole Width Limit Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fPinHoleBreadthLimitPixel = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PinHole Circularity Limit"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fPinHoleCompacenessLimit = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PinHole Merge Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nPinHoleClosingIteration = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PinHole Noise Reduction Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nPinHoleOpeningIteration = _ttoi(szData);

		// 20090512
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PinHole Merge Distance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fPinHoleMergeDistance = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use Local RleBlock"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bUseLocalRleBlock = _ttoi(szData);

		//130604 hjc add
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use Relative PinHole Radient"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bUseRelPinHoleRadient = _ttoi(szData);
		else
			SpecData.bUseRelPinHoleRadient = TRUE;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use Raw Gray for PinHole"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bUseRawGrayPinHole = _ttoi(szData);

		//20090412 hjc
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use Raw Gray for Island"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bUseRawGrayForIsland = _ttoi(szData);
		else
			SpecData.bUseRawGrayForIsland = 0;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Bright Island Gray Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nBrightIslandGrayPlus = _ttoi(szData);
		else
			SpecData.nBrightIslandGrayPlus = 30;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Dark Island Gray Minus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nDarkIslandGrayMinus = _ttoi(szData);
		else
			SpecData.nDarkIslandGrayMinus = 30;
		//------------------

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use Raw Gray for PADDefect"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bUseRawGrayPADDefect = _ttoi(szData);

		//20190729 add start
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use New Raw Gray for PADDefect"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bUseNewRawGrayPADDefect = _ttoi(szData);
		else
			SpecData.bUseNewRawGrayPADDefect = FALSE;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use New Raw Gray for PinHole"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bUseNewRawGrayPinHole = _ttoi(szData);
		else
			SpecData.bUseNewRawGrayPinHole = FALSE;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use New Raw Gray for Island"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bUseNewRawGrayForIsland = _ttoi(szData);
		else
			SpecData.bUseNewRawGrayForIsland = FALSE;
		//20190729 add end

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Dark Gray Minus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nSpLgDarkGrayMinus = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Dark Pixel Num"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nDarkSpaceMin = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Bright Pinhole Gray Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nBrightPinHoleGrayPlus = _ttoi(szData);

		//20090405 hjc
		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Dark Pinhole Neib Gray Minus Apply Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fDarkPinHoleNeibGrayMinusApplyRatio = _ttof(szData);
		else
			SpecData.fDarkPinHoleNeibGrayMinusApplyRatio = 0.5f;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Bright Pinhole Neib Gray Plus Apply Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fBrightPinHoleNeibGrayPlusApplyRatio = _ttof(szData);
		else
			SpecData.fBrightPinHoleNeibGrayPlusApplyRatio = 0.5f;

		//20160108 ndy add - Start
#if MACHINE_MODEL == INSMART_GM4000
		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Use Fine Extra Inspection for ExtraDefect");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bUseFineIslandInsp = atoi(szData);
		else
			SpecData.bUseFineIslandInsp = TRUE;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Fine Extra Relative Gray");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nFineIslandRelativeGray = atoi(szData);
		else
			SpecData.nFineIslandRelativeGray = 30;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Fine Extra Max Size");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nFineIslandMaxSize = atoi(szData);
		else
			SpecData.nFineIslandMaxSize = 25;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Fine Extra Mask Size");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nFineIslandMaskSize = atoi(szData);
		else
			SpecData.nFineIslandMaskSize = 2;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Use Fine PinHole Inspction for PinHoleDefect");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bUseFinePinHoleInsp = atoi(szData);
		else
			SpecData.bUseFinePinHoleInsp = TRUE;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Fine PinHole Relative Gray");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nFinePinHoleRelativeGray = atoi(szData);
		else
			SpecData.nFinePinHoleRelativeGray = 20;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Fine PinHole Max Size");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nFinePinHoleMaxSize = atoi(szData);
		else
			SpecData.nFinePinHoleMaxSize = 25;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));		//20230417 add start
		strIndex.Format(_T("Preset Sp Gradient Upper Limit"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nGradientUpperLimit = _ttoi(szData);
		else
			SpecData.nGradientUpperLimit = 100;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Sp Gradient Threshold"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nGradientThreshold = _ttoi(szData);
		else
			SpecData.nGradientThreshold = 15;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Sp Gradient Min Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nGradientMinSize = _ttoi(szData);
		else
			SpecData.nGradientMinSize = 0;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PadLg Gradient Upper Limit"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nPadLgGradientUpperLimit = _ttoi(szData);
		else
			SpecData.nPadLgGradientUpperLimit = 200;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PadLg Gradient Threshold"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nPadLgGradientThreshold = _ttoi(szData);
		else
			SpecData.nPadLgGradientThreshold = 45;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset PadLg Gradient Min Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nPadLgGradientMinSize = _ttoi(szData);
		else
			SpecData.nPadLgGradientMinSize = 0;

		strTitle.Format(_T("Preset Spec AddOn Extra PinHole"));
		strIndex.Format(_T("Preset Use Relative Dark Gray Only"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bUseRlsDarkGrayOnly = _ttoi(szData);
		else
			SpecData.bUseRlsDarkGrayOnly = FALSE;	//20230417 add end	

													//20160610 ndy add - Start
		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Use SmallFeature Inspection");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseSmallFeatureDefect = atoi(szData);
		else
			SpecTempData.bUseSmallFeatureDefect = TRUE;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset SmallFeature Extra Gray");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSmallFeatureExtraGray = atoi(szData);
		else
			SpecTempData.nSmallFeatureExtraGray = 80;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset SmallFeature PinHole Gray");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nSmallFeaturePinHoleGray = atoi(szData);
		else
			SpecTempData.nSmallFeaturePinHoleGray = 230;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset Use TinyFeature Inspection");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.bUseTinyFeatureDefect = atoi(szData);
		else
			SpecTempData.bUseTinyFeatureDefect = TRUE;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset TinyFeature PAD Gray");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nTinyFeaturePADGray = atoi(szData);
		else
			SpecTempData.nTinyFeaturePADGray = 60;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset TinyFeature PAD Size Upper Ratio");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nTinyFeaturePADSizeUpperRatio = atoi(szData);
		else
			SpecTempData.nTinyFeaturePADSizeUpperRatio = 25;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset TinyFeature PAD Size Lower Ratio");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nTinyFeaturePADSizeLowerRatio = atoi(szData);
		else
			SpecTempData.nTinyFeaturePADSizeLowerRatio = 25;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset TinyFeature Hole Gray");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nTinyFeatureHoleGray = atoi(szData);
		else
			SpecTempData.nTinyFeatureHoleGray = 190;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset TinyFeature Hole Size Upper Ratio");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nTinyFeatureHoleSizeUpperRatio = atoi(szData);
		else
			SpecTempData.nTinyFeatureHoleSizeUpperRatio = 25;

		strTitle.Format("Preset Spec AddOn Extra PinHole");
		strIndex.Format("Preset TinyFeature Hole Size Lower Ratio");
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecTempData.nTinyFeatureHoleSizeLowerRatio = atoi(szData);
		else
			SpecTempData.nTinyFeatureHoleSizeLowerRatio = 25;
		//20160610 ndy add - End
#endif
		//20160108 ndy add - End
		//------------------------------------------------

		//ADDON Hole Via Spec
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH In-Out Gray Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCO2InOutGrayDiff = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Inner Bright Def Percent"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCO2InnerBrightDefPercent = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Inner Saturation Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCO2InnerSaturationGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Inner Bright Search Diameter Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fCO2InnerBrightSrchDiaRatio = _ttof(szData);

		// 091214 jsy
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Inner Roughness"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fCO2InnerRoughness = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Inner Roughness Search Diameter Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fCO2InnerRoughnessSrchDiaRatio = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Use VD Ring Width Filter"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bUseVDRingWidthFilter = _ttoi(szData);

		//20100517 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Extension Hole Search"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bExtensionHoleSearch = _ttoi(szData);
		//end

		//130915 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Inspection Large Hole"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bInspLargeHole = _ttoi(szData);

		//140325 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Inspection Small Hole"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bInspSmallHole = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VD Ring Width Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fVDRingWidthPixel = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Ring Width Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fVHRingWidthPixel = _ttof(szData);

		//120515 jsy - start
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset BT Via Min Length Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nBTViaMin = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset BT Via Closing Number"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nBTVRingClosingNumber = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset BT Via Upper Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nBTVGraySpecUpper = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset BT Via Lower Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nBTVGraySpecLower = _ttof(szData);
		//120515 jsy - end


		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset HoleLand Radius Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fHoleLandSizeRatio = _ttof(szData);

		//20100511 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset AR Edge MinMax Diff Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nAREdgeDiffGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset AR Break Count"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nARBreakCnt = _ttoi(szData);
		//end

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset AR Find Line Add Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nARFindLineAddPixel = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset VH Find Line Add Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nCO2FindLineAddPixel = _ttoi(szData);

		//20091117
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Hole Meas Dia Successive Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nHoleMeasDiaSuccessivePixel = _ttoi(szData);

		//130726 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset LargeCircle Check InnerOuter Pixels"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nLargeCircle_Check_InnerOuter_Pixels = _ttoi(szData);

		//140325 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset SmallCircle Check Inner Pixels"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nSmallCircle_Check_Inner_Pixels = _ttoi(szData);

		//141105 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Diff Delta Pixel In ARCO2"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nDiffDeltaPxlARCO2 = _ttoi(szData);
		else
		{
#if CUSTOMER_COMPANY == SAMSUNG_DAEJEON
			SpecData.nDiffDeltaPxlARCO2 = 0;	//141105 hjc add	
#else
			SpecData.nDiffDeltaPxlARCO2 = 3;	//141105 hjc add	
#endif
		}

		//120131 hjc add
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Hole Min Max Diff Gray Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nVDHoleMinMaxDiffGrayPlus = _ttoi(szData);

		//121206 jsy - start
		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Dimple Lower Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nDimpleLowerGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Dimple Upper Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nDimpleUpperGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Dimple Copper Miss Num"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nDimpleCopperMissNum = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Dimple Copper Search Ratio"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fDimpleCopperSearchRatio = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Hole Via"));
		strIndex.Format(_T("Preset Dimple Ring Num"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nDimpleRingNum = _ttoi(szData);
		//121206 jsy - end

		//ADDON Edge Violation Spec
		//2022 12 16 lgh add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset ApplySCurveEdge"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bApplySCurveEdge = _ttoi(szData);


		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Use fixed PM ID - Etching Pixels"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bUseFixedPMId = _ttoi(szData);

		//111003 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Extension Space Trace"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bExtensionSpaceTrace = _ttoi(szData);

		//111005 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Spectial Space MinMax Diff Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nSpMinMaxDiffGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Fixed PM ID"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nFixedPMId = _ttoi(szData);

		//140425 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Apply Wide Open"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bChkWideOpen = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Wide Open Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nWideOpenPxl = _ttoi(szData);
		//140425 hjc add end

		//20200511 add
		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Pt Match Level"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nPtMatchLevel = _ttoi(szData);
		else
		{
			if (0 < ::GetPrivateProfileString(_T("Spec"), _T("PtMatchLevel"), NULL, szData, sizeof(szData), SPEC_PARAM_PATH))
				m_nPtMatchLevel = _ttoi(szData);
			else
				m_nPtMatchLevel = 4;
		}
		//20210818 add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Apply Template Match"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bChkTemplateMatch = _ttoi(szData);

		//130829 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Check PAD Edge Limit"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bCheckPADEdgeLimit = _ttoi(szData);

		//131105 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Edge Align Tolerence"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_nEdgeAlignTol = _ttoi(szData);
		else
			pMainFrame->m_nEdgeAlignTol = 3;

		//131113 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Edge Gray Check Range"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_nEdgeGrayCheckRange = _ttoi(szData);
		else
			pMainFrame->m_nEdgeGrayCheckRange = 4;

		//140121 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Diff Edge Delta Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_nDiffEdgeDeltaPixel = _ttoi(szData);
		else
			pMainFrame->m_nDiffEdgeDeltaPixel = 1;

		//160318 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Large Edge Nick Spec Down Size Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_fLargeEdgeNickSpecDownSize = _ttof(szData);
		else
			pMainFrame->m_fLargeEdgeNickSpecDownSize = 0.5f;

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Large Edge Prot Spec Down Size Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_fLargeEdgeProtSpecDownSize = _ttof(szData);
		else
			pMainFrame->m_fLargeEdgeProtSpecDownSize = 0.5f;
		//end

		//131031 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Check Core Pad Tip"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			pMainFrame->m_bCheckCorePadTip = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Core Neutral Zone"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCoreNeutralZone = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Core Diff Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCoreDiffGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset Core Defect Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCoreDefSize = _ttoi(szData);
		//end

		//20101201 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset SPE Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nSPEdgeNickGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset SPE Nick Size Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fSPEdgeNickWdDeltaGradViolation = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset SPE Prot Size Pixel"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fSPEdgeExcsWdDeltaGradViolation = _ttof(szData);

		//131123 hjc add
		strTitle.Format(_T("Preset Spec AddOn Edge Violation"));
		strIndex.Format(_T("Preset SPEdge Gray Diff"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nSPEdgeGrayDiff = _ttoi(szData);	//131123 hjc add
														//end

														//150806 hjc add ====
		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Sud InOut Lower Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nSudInOutLowerGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Sud InOut Upper Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nSudInOutUpperGray = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Sud InOut Def Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fSudInOutDefSize = _ttof(szData);

		//150806 hjc add
		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset AICL Tolerance"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fAICLTolerance = _ttof(szData);
		else
			SpecData.fAICLTolerance = 15.0f;

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset AICL Bound Check Gray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nBoundChkGray = _ttoi(szData);
		else
			SpecData.nBoundChkGray = 35;

		//150827 hjc add
		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset AICL Shrink Size"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nShrinkSize = _ttoi(szData);
		else
			SpecData.nShrinkSize = 0;

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Check for Fiducial Mark"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.bCheckFiducialMark = _ttoi(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Fiducial Mark Def Area"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fFMDArea = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Fiducial Mark Def SizeX"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fFMDSizeX = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Fiducial Mark Def SizeY"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fFMDSizeY = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Fiducial Mark PT Range Plus"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fFMDPtRangePlus = _ttof(szData);

		strTitle.Format(_T("Preset Spec AddOn Sud"));
		strIndex.Format(_T("Preset Fiducial Mark PT Score"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.fFMDPtScore = _ttof(szData);
		//150806 hjc add end ====

		//161228 lgh
		pGlobalDoc->LoadInspModeDataFromPreset(INSP_MODE_NORMAL, strPath);
		pGlobalDoc->LoadInspModeDataFromPreset(INSP_MODE_RED, strPath);
		pGlobalDoc->LoadInspModeDataFromPreset(INSP_MODE_BLUE, strPath);

		
		////ADDON Inspection Logic Control Spec
		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Line Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspLine = _ttoi(szData);

		////131104 hjc add
		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset SR Line Tip Extention Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspSrLineTipExt = _ttoi(szData);
		//else
		//m_bInspSrLineTipExt = FALSE;

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Space Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspSpace = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Pad Pixel Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspPadPixel = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Pat Pixel Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspPatPixel = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Space Pixel Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_nInspSpacePixel = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Virtual Drill Pixel Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspVDPixel = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Hole Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspHole = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Via Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspVia = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Dimple Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspDimple = _ttoi(szData);
		//else
		//m_bInspDimple = FALSE; //120502 jsy

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset CCL Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspCCL = _ttoi(szData);
		//else
		//m_bInspCCL = FALSE; //120502 jsy

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset OnlyVia Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bUseOnlyViaInsp = _ttoi(szData);
		//else
		//m_bUseOnlyViaInsp = FALSE; //120502 jsy

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset BarType Via Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspBarTypeVia = _ttoi(szData);
		//else
		//m_bInspBarTypeVia = FALSE; //120515 jsy

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Edge Hole Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspContourAR = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Edge Via Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspContourVIA = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Edge Pad Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspContourLP = _ttoi(szData);

		////110718 hjc add
		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset Edge VD Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspContourVD = _ttoi(szData);

		////131212 hjc add
		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));
		//strIndex.Format(_T("Preset SREdge Space Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspSREdgeSpace = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));	//	100429 lj)
		//strIndex.Format(_T("Preset SUD In Out Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspSudInOut = _ttoi(szData);

		//strTitle.Format(_T("Preset Spec Inspection Logic Control"));	//	100510 jsy
		//strIndex.Format(_T("Preset SPE Space Inspection"));
		//if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		//m_bInspSPESpace = _ttoi(szData);
		
		//20100514 hjc add
		strTitle.Format(_T("Preset Pre System Parameters"));	//	100510 jsy
		strIndex.Format(_T("Preset Open Check Cell Bound"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nOpenChkCellBnd = _ttoi(szData);

		strTitle.Format(_T("Preset Pre System Parameters"));	//	100510 jsy
		strIndex.Format(_T("Preset Nick Check Cell Bound"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nNickChkCellBnd = _ttoi(szData);

		strTitle.Format(_T("Preset Pre System Parameters"));	//	100510 jsy
		strIndex.Format(_T("Preset Excs Check Cell Bound"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nExcsChkCellBnd = _ttoi(szData);
		//end

		//120521 hjc add
		strTitle.Format(_T("Preset Pre System Parameters"));
		strIndex.Format(_T("Preset Check Good Range For Line"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nChkGoodRangeForLine = _ttoi(szData);
		else
			m_nChkGoodRangeForLine = 75;

		//111005 hjc add
		strTitle.Format(_T("Preset Pre System Parameters"));
		strIndex.Format(_T("Preset Min Space Check Bound Tip"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nMinSpCheckBoundTip = _ttoi(szData);

		strTitle.Format(_T("Preset Pre System Parameters"));
		strIndex.Format(_T("Preset Min Space Check Bound"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nMinSpCheckBound = _ttoi(szData);

		strTitle.Format(_T("Preset Pre System Parameters"));
		strIndex.Format(_T("Preset Min Space Check Bound Edge"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nMinSpCheckBoundEdge = _ttoi(szData);

		strTitle.Format(_T("Preset Pre System Parameters"));
		strIndex.Format(_T("Preset UShort Check Bound Tip"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			m_nUShortCheckBoundTip = _ttoi(szData);



		strTitle.Format(_T("TextInspection"));
		strIndex.Format(_T("CharInspectionGray"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.nCharInspectionGray = _ttoi(szData);


		strTitle.Format(_T("TextInspection"));
		strIndex.Format(_T("dCharRegionUpperPercent"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.dCharRegionUpperPercent = _ttof(szData);

		strTitle.Format(_T("TextInspection"));
		strIndex.Format(_T("dCharRegionLowerPercent"));
		if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
			SpecData.dCharRegionLowerPercent = _ttof(szData);

		//end
	}


	//2022 07 13 lgh add
	strTitle.Format(_T("Preset Spec Model"));
	if (0 < ::GetPrivateProfileString(strTitle, _T("IRISPosID"), NULL, szData, sizeof(szData), strPath))
		m_nIRISPosID = _ttoi(szData);


	//140702 hjc add
	strTitle.Format(_T("Preset Calibration Measure Offset Parameters"));
	strIndex.Format(_T("Preset Calib F"));
	if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		m_fCalibF[INSP_MODE_NORMAL] = _ttof(szData);
	else
	{
		strData.Format(_T("Res_%.3f"), SizeData[COMMON_PARAMETER].fPixelSizeX);
		if (0 < ::GetPrivateProfileString(_T("CalibF"), strData, NULL, szData, sizeof(szData), SPEC_PARAM_PATH))
			m_fCalibF[INSP_MODE_NORMAL] = _ttof(szData);
		else
			m_fCalibF[INSP_MODE_NORMAL] = 1.45;
	}

	//140702 hjc add
	strTitle.Format(_T("Preset Calibration Space Measure Offset Parameters"));
	strIndex.Format(_T("Preset Calib Sp F"));
	if (0 < ::GetPrivateProfileString(strTitle, strIndex, NULL, szData, sizeof(szData), strPath))
		m_fSpCalibF[INSP_MODE_NORMAL] = _ttof(szData);
	else
	{
		strData.Format(_T("Res_%.3f"), SizeData[COMMON_PARAMETER].fPixelSizeX);
		if (0 < ::GetPrivateProfileString(_T("SpCalibF"), strData, NULL, szData, sizeof(szData), SPEC_PARAM_PATH))
			m_fSpCalibF[INSP_MODE_NORMAL] = _ttof(szData);
		else
			m_fSpCalibF[INSP_MODE_NORMAL] = 0.97;
	}

	int nMode = 0;
	for (nMode = INSP_MODE_RED; nMode < INSP_MODE_COUNT; nMode++)
	{
		CString strDelimter;

		strDelimter.Format(_T(" INSP%d"), nMode);
		strTitle.Format(_T("Preset Calibration Measure Offset Parameters"));
		strIndex.Format(_T("Preset Calib F"));
		if (0 < ::GetPrivateProfileString(strTitle + strDelimter, strIndex, NULL, szData, sizeof(szData), strPath))
			m_fCalibF[nMode] = _ttof(szData);
		else
		{
			strData.Format(_T("Res_%.3f"), SizeData[COMMON_PARAMETER].fPixelSizeX);
			if (0 < ::GetPrivateProfileString(_T("CalibF") + strDelimter, strData, NULL, szData, sizeof(szData), SPEC_PARAM_PATH))
				m_fCalibF[nMode] = _ttof(szData);
			else
				m_fCalibF[nMode] = m_fCalibF[INSP_MODE_NORMAL];
		}
		//20200625 add
		strTitle.Format(_T("Preset Calibration Space Measure Offset Parameters"));
		strIndex.Format(_T("Preset Calib Sp F"));
		if (0 < ::GetPrivateProfileString(strTitle + strDelimter, strIndex, NULL, szData, sizeof(szData), strPath))
			m_fSpCalibF[nMode] = _ttof(szData);
		else
		{
			strData.Format(_T("Res_%.3f"), SizeData[COMMON_PARAMETER].fPixelSizeX);
			if (0 < ::GetPrivateProfileString(_T("SpCalibF") + strDelimter, strData, NULL, szData, sizeof(szData), SPEC_PARAM_PATH))
				m_fSpCalibF[nMode] = _ttof(szData);
			else
				m_fSpCalibF[nMode] = m_fSpCalibF[INSP_MODE_NORMAL];
		}
	}

	//170317 LGH
	if (AoiParam()->m_bUseCamMasterInspectionMode && AoiParam()->m_nCamMasterSpecMode != DONT_CARE_LGOIC)
	{
		pGlobalDoc->SetInspectionMode(INSP_MODE_NORMAL, AoiParam()->m_nCamMasterSpecMode);
		pGlobalDoc->SetInspectionMode(INSP_MODE_BLUE, AoiParam()->m_nCamMasterSpecMode);
		pGlobalDoc->SetInspectionMode(INSP_MODE_RED, AoiParam()->m_nCamMasterSpecMode);

		switch (AoiParam()->m_nCamMasterSpecMode)
		{
		case GM_MODE:
		case BARE_MODE:
			pGlobalDoc->ClearInspLogicMode();
			m_bUseOnlyViaInsp[0] = 0;
			m_bInspContourAR[0] = 1;
			m_bInspContourLP[0] = 1;
			m_bInspContourVIA[0] = 1;
			m_bInspContourVD[0] = 1;	//110718 hjc add
			m_bInspSREdgeSpace[0] = 0;	//131212 hjc add	
			m_bInspVDPixel[0] = 1;
			m_bInspHole[0] = 1;
			m_bInspLine[0] = 1;
			m_bInspSrLineTipExt[0] = 0;	//131104 hjc add	
			m_bInspPadPixel[0] = 1;
			m_bInspPatPixel[0] = 1;
			m_bInspSpace[0] = 1;
			m_nInspSpacePixel[0] = 1;
			m_bInspVia[0] = 1;
			m_bInspDimple[0] = 0;
			m_bInspSudInOut[0] = 0;
			m_bInspSPESpace[0] = 0;
			m_bInspSROpen[0] = 0;
			break;

		case BARVIA_MODE:
			break;

		case ADAPTIVE_THRESHOLD:
			break;

		case VIA_MODE:
			pGlobalDoc->ClearInspLogicMode();
			m_bUseOnlyViaInsp[INSP_MODE_NORMAL] = TRUE;
			m_bUseOnlyViaInsp[INSP_MODE_BLUE] = TRUE;
			m_bUseOnlyViaInsp[INSP_MODE_RED] = TRUE;
			m_bInspPatPixel[INSP_MODE_NORMAL] = TRUE;
			m_bInspVia[INSP_MODE_NORMAL] = TRUE;
			m_bInspPatPixel[INSP_MODE_BLUE] = TRUE;
			m_bInspVia[INSP_MODE_BLUE] = TRUE;
			m_bInspPatPixel[INSP_MODE_RED] = TRUE;
			m_bInspVia[INSP_MODE_RED] = TRUE;
			break;

		case CCL_MODE:
			pGlobalDoc->ClearInspLogicMode();
			m_bInspPatPixel[INSP_MODE_NORMAL] = TRUE;
			m_bInspPatPixel[INSP_MODE_RED] = TRUE;
			m_bInspPatPixel[INSP_MODE_BLUE] = TRUE;
			break;
		}
	}
	else
		pGlobalDoc->CheckBareAndOtherMode();

	m_bCheckMsgLSFilteringAlarm = TRUE;
	pGlobalView->DispDefUserSelect(TRUE, TRUE);	//20120724-ndy
	*/
	return TRUE;
}
