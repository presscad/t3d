
#include "stdafx.h"
#include "ClientCapture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)

/////////////////////////////////////////////////////////////////////////////
// CClientCapture::CClientCapture - Constructor

CClientCapture::CClientCapture()
{
	m_pBMI = 0;
	m_pBits = 0;
	hDIB = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CClientCapture::~CClientCapture - Destructor

CClientCapture::~CClientCapture()
{
	if(hDIB)
		GlobalFree( hDIB );
	hDIB = 0;
	m_pBMI = 0;
	m_pBits = 0;

}

//調用WriteWindowToDIB()函數將DDB圖形轉換為與設備無關的位圖DIB
void CClientCapture::Capture(CDC *dc, CRect rectDIB) 
{
	WriteWindowToDIB(dc, rectDIB);
}

//將DDB圖形轉換為與設備無關的位圖DIB
BOOL CClientCapture::WriteWindowToDIB( CDC* dc, CRect rect)
{
	CBitmap 	bitmap;
	CDC 		memDC;

	memDC.CreateCompatibleDC(dc); 
	bitmap.CreateCompatibleBitmap(dc, rect.Width(),rect.Height() );
	
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.BitBlt(0, 0, rect.Width(),rect.Height(), dc, 0, 0, SRCCOPY); 

	// 創建邏輯調色板
	if( dc->GetDeviceCaps(RASTERCAPS) & RC_PALETTE )
	{
		UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * 256);
		LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];
		pLP->palVersion = 0x300;

		pLP->palNumEntries = GetSystemPaletteEntries( *dc, 0, 255, pLP->palPalEntry );

		pal.CreatePalette( pLP );

		delete[] pLP;
	}

	memDC.SelectObject(pOldBitmap);

	// 轉換DDB到DIB      BI_RGB
	hDIB = DDBToDIB( bitmap, BI_RGB, &pal, dc);

	if( hDIB == NULL )
		return FALSE;

	return TRUE;
}

//屏幕圖形打印預覽
BOOL CClientCapture::Paint(HDC hDC, CPalette * m_pPalette, LPRECT lpDCRect, LPRECT lpDIBRect) const
{

	if (!m_pBMI)
		return FALSE;

	HPALETTE hPal = NULL;           // DIB的調色板
	HPALETTE hOldPal = NULL;        // 以前的調色板

	// 獲得DIB調色板，然後將其設置到設備描述表DC中
	if (m_pPalette != NULL)
	{
		hPal = (HPALETTE) m_pPalette->m_hObject;
		hOldPal = ::SelectPalette(hDC, hPal, TRUE);
	}
	//  設置使用拉伸模式
	::SetStretchBltMode(hDC, COLORONCOLOR);
	BOOL bSuccess = FALSE;
	//  判斷是否使用拉伸
	if ((RECTWIDTH(lpDCRect)  == RECTWIDTH(lpDIBRect)) && 
		(RECTHEIGHT(lpDCRect) == RECTHEIGHT(lpDIBRect)))
		bSuccess = ::SetDIBitsToDevice(hDC, lpDCRect->left, lpDCRect->top, 
						RECTWIDTH(lpDCRect), RECTHEIGHT(lpDCRect), lpDIBRect->left,
						(int)Height() - lpDIBRect->top - RECTHEIGHT(lpDIBRect),
					    0, (WORD)Height(), m_pBits, m_pBMI, DIB_RGB_COLORS);   
	else
		bSuccess = ::StretchDIBits(hDC, lpDCRect->left, lpDCRect->top, 
						RECTWIDTH(lpDCRect),RECTHEIGHT(lpDCRect), lpDIBRect->left, 
						lpDIBRect->top,RECTWIDTH(lpDIBRect),RECTHEIGHT(lpDIBRect),
						m_pBits, m_pBMI, DIB_RGB_COLORS, SRCCOPY);    
 
	// 重新設置老的調色板
	if (hOldPal != NULL)
	{
		::SelectPalette(hDC, hOldPal, TRUE);
	}

	
   return bSuccess;
}

//  下面函數的功能是將DDB轉換到DIB
HANDLE CClientCapture::DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal, 	CDC *dc) 
{
	BITMAP			bm;
	BITMAPINFOHEADER	bi; //定義位圖信息頭,位圖信息頭包含了單個像素所用字節數以及描述顏色的格式，此外還包括位圖的寬度、高度、目標設備的位平面數、圖像的壓縮格式
	LPBITMAPINFOHEADER 	lpbi;
	DWORD			dwLen;
	HANDLE			handle; 
	HDC 			hDC;
	HPALETTE		hPal; //調色板
	
	ASSERT( bitmap.GetSafeHandle() ); //獲得句柄

	if( dwCompression == BI_BITFIELDS ) //不支持BI_BITFIELDS壓縮類型,返回
		return NULL;

	// 如果沒有調色板
	hPal = (HPALETTE) pPal->GetSafeHandle();
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

	// 獲得位圖信息
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

	// 初始化位圖的頭信息
	bi.biSize		= sizeof(BITMAPINFOHEADER);
	bi.biWidth		= bm.bmWidth;
	bi.biHeight 		= bm.bmHeight;
	bi.biPlanes 		= 1;
	bi.biBitCount		= bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression	= dwCompression;
	bi.biSizeImage		= 0;
	bi.biXPelsPerMeter	= 0;
	bi.biYPelsPerMeter	= 0;
	bi.biClrUsed		= 0;
	bi.biClrImportant	= 0;

	// 計算信息頭的大小和顏色表
	int nColors = (1 << bi.biBitCount);
	if( nColors > 256 ) 
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// 獲得設備描述表
	hDC = dc->GetSafeHdc();
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);
	
	// 分配內存資源保存位圖信息頭和顏色表
	if(hDIB) GlobalFree( hDIB );

	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDIB){
		SelectPalette(hDC,hPal,FALSE);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	//  獲得biSizeImage的數值
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
			(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// 如果返回0,則手動計算
	if (bi.biSizeImage == 0)
	{
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
						* bi.biHeight;

		//  如果採用壓縮算法
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

	// 分配內存資源保存所有的位信息
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);
		hDIB = 0;
		// 選擇原始調色板
		SelectPalette(hDC,hPal,FALSE);

		return NULL;
	}

	// 獲得位圖的位信息
	lpbi = (LPBITMAPINFOHEADER)hDIB;
	m_pBMI = (LPBITMAPINFO)hDIB;
	m_pBits = (LPBYTE)hDIB + (bi.biSize + nColors * sizeof(RGBQUAD));

	// 最後獲得DIB
	BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
				0L,						// 開始掃瞄線
				(DWORD)bi.biHeight,		// 掃瞄線總數
				(LPBYTE) m_pBits, 		// 存放位圖各位數據的地址
				(LPBITMAPINFO)lpbi,		// 存放位圖信息的地址
				(DWORD)DIB_RGB_COLORS);	// 使用RGB顏色表

	if( !bGotBits )
	{
		GlobalFree(hDIB);
		hDIB = 0;
		SelectPalette(hDC,hPal,FALSE);

		return NULL;
	}

	SelectPalette(hDC,hPal,FALSE); //選擇調色板

	return hDIB;
}

DWORD CClientCapture::Height() const
{
	if (!m_pBMI)
		return 0;
	// 返回DIB的高度
	return m_pBMI->bmiHeader.biHeight;
}

void CClientCapture::OnDraw(HDC hDC, CRect rcRect, CRect rect)
{
	Paint(hDC, &pal, rcRect, rect);
}

//  下面函數的功能是將DIB信息寫入位圖文件
BOOL CClientCapture::WriteDIB( CString csFile)
{
	BITMAPFILEHEADER	hdr;
	LPBITMAPINFOHEADER	lpbi;

	if (!hDIB)
		return FALSE;

	CFile file;
	if( !file.Open( csFile, CFile::modeWrite|CFile::modeCreate) )
		return FALSE;

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	int nColors = 1 << lpbi->biBitCount;
	if( nColors > 256 ) 
		nColors = 0;

	// 填寫文件頭信息 
	hdr.bfType		= ((WORD) ('M' << 8) | 'B');	// is always "BM"
	hdr.bfSize		= GlobalSize (hDIB) + sizeof( hdr );
	hdr.bfReserved1 	= 0;
	hdr.bfReserved2 	= 0;
	hdr.bfOffBits		= (DWORD) (sizeof( hdr ) + lpbi->biSize +
						nColors * sizeof(RGBQUAD));

	// 寫入文件頭 
	file.Write( &hdr, sizeof(hdr) );

	// 寫入DIB頭和位圖數據 
	file.Write( lpbi, GlobalSize(hDIB) );
	
	file.Close(); //關閉文件

	return TRUE;
}

void CClientCapture::Release()
{
	if(hDIB)
		GlobalFree( hDIB );
	hDIB = 0;
	m_pBMI = 0;
	m_pBits = 0;

}
