#pragma once
#include <vector>
#include "Ssdllmfc.h"
#include "DisplayImage.h"
//161018 LGH FOR SPREAD 8.0 64BIT 64BIT에서는 LOADPICTURE가 안된다 18...


#define MAKEINT64(a,b) ((INT64)((INT64)a << 31 | (INT64)b));

class CSpreadImage
{
public:
	HBITMAP m_hBitmap;
	HDC m_memhdc;
	CDC* m_pDC;
	CBitmap* m_pBitMap;
	CBitmap* m_pOld;
	BITMAP m_bmInfo;
	BOOL m_bLoaded;
	BYTE* m_pThumbBuffer;
	CString m_strLoadedPath;
	UINT_PTR m_BufferSize;
	CSpreadImage(HWND hWnd = NULL);
	BOOL Load(CString strImagePath);
	void DrawBitMap(CDC* pDC,int x,int y,int width,int height);
	void Free();
	BOOL LoadFromBufferMono(BYTE* pImagePtr,int sizex,int sizey);
	BOOL m_bLoadFromBuffer;
	int m_nBufferSizeX;
	int m_nBufferSizeY;
	CDisplayImage m_bitmap;
	~CSpreadImage();

};

class CSpreadImageManager
{
	public:
	int m_nMaxImage;
	HWND m_hParentWnd;
	CSpreadImageManager();
	std::vector<CSpreadImage*>m_vecImagelist;
	CMap<INT64,INT64,int,int>m_idtoindex;
	CMap<int,int,INT64,INT64>m_IndextoID;


	void Initilaize(int nMaxImageCount,HWND hControl);
	BOOL SetPicture(CString strFile,long nCol,long nRow,int nSheet);
	
	BOOL SetPictureBuffer(BYTE* pBuffer,int nSizeX,int nSizeY,long nCol,long nRow,int nSheet);
	BOOL SetPictureBuffer(BYTE* pBuffer,int nSizeX,int nSizeY,long nCol,long nRow);
	//Sheet는 Reserved code
	void DrawPicture(long nCol,long nRow,int nSheet,CDC* pDC,LPSS_DRAWITEMSTRUCT lpDrawItem);
	void DrawPictureEx(LPSS_DRAWITEMSTRUCT lpDrawItem);
	void Reset();

	long GetKey(long nCol,long nRow)
	{
		int nValue = 0;
		INT64 nFindKey = MAKEINT64(nCol,nRow);

		if(m_idtoindex.Lookup(nFindKey,nValue))
		{
			return nValue;
		}
		else
			return -1;
	}
};