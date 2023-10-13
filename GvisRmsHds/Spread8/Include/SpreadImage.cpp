#include "stdafx.h"
#include "SpreadImage.h"


CSpreadImage::CSpreadImage(HWND hWnd)
{
	m_hBitmap = NULL;
	m_memhdc = NULL;
	m_pDC = NULL;
	m_pBitMap = NULL;
	m_pOld = NULL;
	m_pThumbBuffer = nullptr;
	m_bLoaded = 0;
	m_BufferSize = 0;
	m_bLoadFromBuffer = 0;
}



BOOL CSpreadImage::LoadFromBufferMono(BYTE* pImagePtr,int sizex,int sizey)
{
	if(m_bLoaded)
		Free();

	if(m_pThumbBuffer && m_BufferSize < sizex*sizey*3)
	{
		delete [] m_pThumbBuffer;
		m_pThumbBuffer = nullptr;
	}

	m_nBufferSizeX = sizex;
	m_nBufferSizeY = sizey;
	m_BufferSize = sizex*sizey*3;

	if(m_pThumbBuffer == nullptr)
		m_pThumbBuffer = new BYTE[m_BufferSize];

	for ( int k = 0; k < sizey; k++)
	{
		for(int j = 0; j < sizex; j++)
		{
			m_pThumbBuffer[3*((sizex-1-k)*sizex+j)+0] = pImagePtr[k*sizex+j];
			m_pThumbBuffer[3*((sizex-1-k)*sizex+j)+1] = pImagePtr[k*sizex+j];
			m_pThumbBuffer[3*((sizex-1-k)*sizex+j)+2] = pImagePtr[k*sizex+j];
		}
	}
	
	m_bitmap.CreateBitmapInfo(sizex,sizey,24);

	m_bLoaded = TRUE;
	m_bLoadFromBuffer = TRUE;

	return m_bLoaded;
}

BOOL CSpreadImage::Load(CString strImagePath)
{
	if(m_bLoaded)
	{
		Free();
	}

	m_bLoaded = 0;

	CFileFind finder;

	if(!finder.FindFile(strImagePath))
	{
		return FALSE;
	}

	m_strLoadedPath = strImagePath;

	m_hBitmap= (HBITMAP)::LoadImage(NULL,strImagePath, IMAGE_BITMAP, NULL , NULL , LR_LOADFROMFILE);

	if(m_hBitmap)
	{
		m_pBitMap=CBitmap::FromHandle(m_hBitmap);
		m_bLoaded = TRUE;
	}

	return m_bLoaded;
}


void CSpreadImage::DrawBitMap(CDC* pDC,int x,int y,int width,int height)
{
	if(m_bLoaded == 0)
		return;

	if(pDC->GetSafeHdc())
	{
		if(m_bLoadFromBuffer)
		{
			//from dv
			BITMAPINFO bmi2;
			bmi2.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi2.bmiHeader.biWidth  = 100;
			bmi2.bmiHeader.biHeight = 100;
			bmi2.bmiHeader.biPlanes = 1;
			bmi2.bmiHeader.biBitCount = 24;
			bmi2.bmiHeader.biCompression = BI_RGB;
			bmi2.bmiHeader.biSizeImage = 0;
			bmi2.bmiHeader.biXPelsPerMeter = 0;
			bmi2.bmiHeader.biYPelsPerMeter = 0;
			bmi2.bmiHeader.biClrUsed = 0;
			bmi2.bmiHeader.biClrImportant = 0;



			//비트 맵을 하나 만든다.
			CBitmap tmpThumbBitMap;
			tmpThumbBitMap.CreateCompatibleBitmap(pDC,100,100);

			::SetDIBits(pDC->GetSafeHdc(),tmpThumbBitMap,0,100,m_pThumbBuffer,&bmi2,DIB_RGB_COLORS);
			CDC dcMemory2;
			dcMemory2.CreateCompatibleDC(pDC);

			CBitmap * pOldBitmap2 = dcMemory2.SelectObject(&tmpThumbBitMap);

			pDC->SetStretchBltMode(COLORONCOLOR);
			pDC->StretchBlt(x, y, width, height ,&dcMemory2,0,0 ,m_nBufferSizeX, m_nBufferSizeY, SRCCOPY);

			dcMemory2.SelectObject(pOldBitmap2);
			tmpThumbBitMap.DeleteObject();

		}
		else
		{
			CDC dcMem;
			dcMem.CreateCompatibleDC(pDC);

			m_pBitMap=CBitmap::FromHandle(m_hBitmap);

			m_pOld = dcMem.SelectObject(m_pBitMap);

			m_pBitMap->GetObject(sizeof(m_bmInfo), &m_bmInfo);

			pDC->SetStretchBltMode(COLORONCOLOR);
			pDC->StretchBlt(x, y, width, height ,&dcMem,0,0 ,m_bmInfo.bmWidth, m_bmInfo.bmHeight, SRCCOPY);

			dcMem.SelectObject(m_pOld);
		}
	}
}

void CSpreadImage::Free()
{
	m_bLoaded = 0;
	m_BufferSize =0;
	m_bLoadFromBuffer = 0;
	if(m_pThumbBuffer)
	{
		delete [] m_pThumbBuffer;
		m_pThumbBuffer = nullptr;
	}
	if(m_hBitmap)
	{
		::DeleteObject(m_hBitmap);
		m_hBitmap = 0;
	}

	m_pBitMap = nullptr;
}

CSpreadImage::~CSpreadImage()
{
	Free();
	m_memhdc = 0;
	m_pDC = nullptr;
}

CSpreadImageManager::CSpreadImageManager()
{
	m_hParentWnd = nullptr;
	m_nMaxImage = 1000;
	m_vecImagelist.reserve(m_nMaxImage);
}

void CSpreadImageManager::Initilaize(int nMaxImageCount,HWND hControl)
{
	m_hParentWnd = hControl;
	m_nMaxImage = nMaxImageCount;
}

BOOL CSpreadImageManager::SetPicture(CString strFile,long nCol,long nRow,int nSheet)
{
	INT64 ImageID = MAKEINT64(nCol,nRow);

	if(m_vecImagelist.size() > m_nMaxImage)
	{
		return FALSE;
	}

	int nOldKey = 0;
	if(m_idtoindex.Lookup(ImageID,nOldKey))
	{
		return m_vecImagelist[nOldKey]->Load(strFile);
	}

	CSpreadImage* image = new CSpreadImage(m_hParentWnd);

	if(image->Load(strFile))
	{
		m_vecImagelist.push_back(image);

		int nKey = m_vecImagelist.size() - 1;

		m_idtoindex.SetAt(ImageID,nKey);			
	}
	else
	{
		delete image;
		image = nullptr;
		return FALSE;
	}

	return TRUE;
}

BOOL CSpreadImageManager::SetPictureBuffer(BYTE* pBuffer,int nSizeX,int nSizeY,long nCol,long nRow)
{
	INT64 ImageID = MAKEINT64(nCol,nRow);

	if(m_vecImagelist.size() > m_nMaxImage)
	{
		return FALSE;
	}

	int nOldKey = 0;
	if(m_idtoindex.Lookup(ImageID,nOldKey))
	{
		return m_vecImagelist[nOldKey]->LoadFromBufferMono(pBuffer,nSizeX,nSizeY);
	}

	CSpreadImage* image = new CSpreadImage(m_hParentWnd);

	if(image->LoadFromBufferMono(pBuffer,nSizeX,nSizeY))
	{
		m_vecImagelist.push_back(image);

		int nKey = m_vecImagelist.size() - 1;

		m_idtoindex.SetAt(ImageID,nKey);			
	}
	else
	{
		delete image;
		image = nullptr;
		return FALSE;
	}

	return TRUE;
}

//Sheet는 Reserved code
void CSpreadImageManager::DrawPicture(long nCol,long nRow,int nSheet,CDC* pDC,LPSS_DRAWITEMSTRUCT lpDrawItem)
{
	INT64 ImageID = MAKEINT64(nCol,nRow);
	int nKey = 0;
	if(m_idtoindex.Lookup(ImageID,nKey))
	{
		int xOffset = (lpDrawItem->Rect.right - lpDrawItem->Rect.left) / 100;
		int yOffset = (lpDrawItem->Rect.bottom - lpDrawItem->Rect.top) / 100;
		int xLeft = lpDrawItem->Rect.left + xOffset;
		int yTop = lpDrawItem->Rect.top + yOffset;
		int xRight = lpDrawItem->Rect.right - xOffset;
		int yBottom = lpDrawItem->Rect.bottom - yOffset;

		m_vecImagelist[nKey]->DrawBitMap(pDC,xLeft, yTop, xRight - xLeft, yBottom - yTop);
	}
}

void CSpreadImageManager::DrawPictureEx(LPSS_DRAWITEMSTRUCT lpDrawItem)
{
	INT64 ImageID = lpDrawItem->lStyle;
	int nKey = 0;
	if(ImageID>=0 && ImageID < m_vecImagelist.size())
	{
		CDC* pDC = CDC::FromHandle(lpDrawItem->hDC);
		int xOffset = (lpDrawItem->Rect.right - lpDrawItem->Rect.left) / 100;
		int yOffset = (lpDrawItem->Rect.bottom - lpDrawItem->Rect.top) / 100;
		int xLeft = lpDrawItem->Rect.left + xOffset;
		int yTop = lpDrawItem->Rect.top + yOffset;
		int xRight = lpDrawItem->Rect.right - xOffset;
		int yBottom = lpDrawItem->Rect.bottom - yOffset;

		m_vecImagelist[ImageID]->DrawBitMap(pDC,xLeft, yTop, xRight - xLeft, yBottom - yTop);
	}
}

void CSpreadImageManager::Reset()
{
	int i = 0;

	for(i=0; i<m_vecImagelist.size(); i++)
	{
		CSpreadImage* pImage=(CSpreadImage*)m_vecImagelist[i];
		delete pImage;
		pImage = nullptr;
	}

	m_vecImagelist.clear();
	m_idtoindex.RemoveAll();
}
