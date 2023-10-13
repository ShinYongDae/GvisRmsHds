// DisplayImage.h: interface for the CDisplayImage class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _DISPLAY_WINDOW_CLASS_DEF_H_
#define _DISPLAY_WINDOW_CLASS_DEF_H_



class CDisplayImage  
{
public:
					CDisplayImage();
	virtual			~CDisplayImage();
	BOOL			CreateBitmapInfo(int width, int height, int bitcount);
	void			DrawImage(HDC hDC, void* pImg, int dx, int dy, int dw, int dh);
	void			DrawImageEx(HDC hDC, void* pImg, int dx, int dy, int dw, int dh);
protected:
	HPALETTE		m_hPal;						// HPALETTE
	int				m_Width;					// Image width	
	int				m_Height;					// Image heigth
	int				m_Bitcount;					// bit per pixel
	void*			m_lpbi;						// LPBITMAPINFO
};

#endif // _DISPLAY_WINDOW_CLASS_DEF_H_
