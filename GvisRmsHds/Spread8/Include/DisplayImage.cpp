// DisplayImage.cpp: implementation of the CDisplayImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DisplayImage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDisplayImage::CDisplayImage()
{
	m_hPal		= NULL;
	m_Width		= 0;
	m_Height	= 0;
	m_Bitcount	= 0;
	m_lpbi		= NULL;
}

CDisplayImage::~CDisplayImage()
{
	if(m_lpbi != NULL)
	{
		free(m_lpbi);
		m_lpbi = NULL;
	}

	if(m_hPal != NULL)
	{
		::DeleteObject(m_hPal);
		m_hPal = NULL;
	}
}

BOOL CDisplayImage::CreateBitmapInfo(int width, int height, int bitcount)
{
	WORD        ClrUsed =0;

	m_Width		= width;
	m_Height	= height;
	m_Bitcount	= bitcount;
	
	if(m_lpbi != NULL)
	{
		free(m_lpbi);	
		m_lpbi = NULL;
	}

	switch(bitcount)
	{
	case 8:
		ClrUsed = 256;
		m_lpbi = malloc(sizeof(BITMAPINFOHEADER) + 1024);
		if(m_lpbi == NULL)		return FALSE;
		break;
	case 24:
		ClrUsed = 0;
		m_lpbi = malloc(sizeof(BITMAPINFO));
		if(m_lpbi == NULL)		return FALSE;
		break;
	}

	// Set LPBITMAPINFOHEADER
	LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)(m_lpbi);
	lpbmi->biSize			 = sizeof(BITMAPINFOHEADER);
	lpbmi->biWidth			 = width;
	lpbmi->biHeight			 = height;
	lpbmi->biPlanes			 = 1;
	lpbmi->biBitCount		 = bitcount;
	lpbmi->biCompression	 = BI_RGB;
	lpbmi->biSizeImage		 = height*(DWORD)((width*bitcount/8+3)&~3);
	lpbmi->biXPelsPerMeter   = 0;
	lpbmi->biYPelsPerMeter   = 0;
	lpbmi->biClrUsed		 = ClrUsed;	
	lpbmi->biClrImportant	 = 0;

	// Create palette
	if(bitcount == 8)		// Gray image
	{
		int i, Size;
		BYTE*		pPal	= (BYTE*)lpbmi;
		DWORD		offDest = sizeof(BITMAPINFOHEADER);
		Size				= sizeof(LOGPALETTE) + 1024;		//1024 is sizeof(PALETTEENTRY)*ClrUsed;
		LOGPALETTE*	pLP		= (LOGPALETTE*)malloc(Size);
		if(pLP == NULL)
		{
			free(m_lpbi);
			m_lpbi = NULL;
			return FALSE;
		}

		pLP->palVersion		= 0x300;
		pLP->palNumEntries	= ClrUsed;

		for( i = 0 ; i < 256 ; i++ )
		{
			pPal[offDest++]				= (BYTE)i;
			pPal[offDest++]				= (BYTE)i;
			pPal[offDest++]				= (BYTE)i;
			pPal[offDest++]				= 0x00;

			pLP->palPalEntry[i].peRed	= (BYTE)i;
			pLP->palPalEntry[i].peGreen = (BYTE)i;
			pLP->palPalEntry[i].peBlue	= (BYTE)i;
			pLP->palPalEntry[i].peFlags = 0x00;
		}

		if(m_hPal != NULL)
			::DeleteObject(m_hPal);
		m_hPal = ::CreatePalette(pLP);
		free(pLP);
	}

	return TRUE;
}

void CDisplayImage::DrawImage(HDC hDC, void* pImg, int dx, int dy, int dw, int dh)
{
	HPALETTE		hOldPal = NULL;
	LPBITMAPINFO	lpbi	= (LPBITMAPINFO)(m_lpbi);
				

	if(m_Bitcount != 24)
	{
		hOldPal = ::SelectPalette( hDC, m_hPal, TRUE );
		::RealizePalette(hDC);
	}

	// Display image : 
	// DIB format stores flipped-over buffer image. For the display image buffer, scan the image from the end .     
	::SetStretchBltMode( hDC, COLORONCOLOR );
	::StretchDIBits(	hDC,			// hDC
						dx,				// XDest
						dy,				// YDest
						dw,				// nDestWidth
						dh,				// nDestHeight
						0,				// XSrc
						m_Height,		// YSrc
						m_Width,		// nSrcWidth
						-m_Height,		// nSrcHeight
						pImg,			// lpBits
						lpbi,			// lpBitsInfo
						DIB_RGB_COLORS,	// wUsage
						SRCCOPY);		// dwROP


	if( hOldPal != NULL )	::SelectPalette(hDC, hOldPal, TRUE);
}

void CDisplayImage::DrawImageEx(HDC hDC, void* pImg, int dx, int dy, int dw, int dh)
{
	HPALETTE		hOldPal = NULL;
	LPBITMAPINFO	lpbi	= (LPBITMAPINFO)(m_lpbi);


	if(m_Bitcount != 24)
	{
		hOldPal = ::SelectPalette( hDC, m_hPal, TRUE );
		::RealizePalette(hDC);
	}
		memset(pImg,0,sizeof(BYTE)*m_Width*m_Height);
	// Display image : 
	// DIB format stores flipped-over buffer image. For the display image buffer, scan the image from the end .     
	::SetStretchBltMode( hDC, COLORONCOLOR );
	::StretchDIBits(	hDC,			// hDC
		dx,				// XDest
		dy,				// YDest
		dw,				// nDestWidth
		dh,				// nDestHeight
		0,				// XSrc
		0,		// YSrc
		m_Width,		// nSrcWidth
		m_Height,		// nSrcHeight
		pImg,			// lpBits
		lpbi,			// lpBitsInfo
		DIB_RGB_COLORS,	// wUsage
		SRCCOPY);		// dwROP

	if( hOldPal != NULL )	::SelectPalette(hDC, hOldPal, TRUE);
}