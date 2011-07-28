
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

//�ե�WriteWindowToDIB()��ƱNDDB�ϧ��ഫ���P�]�ƵL�������DIB
void CClientCapture::Capture(CDC *dc, CRect rectDIB) 
{
	WriteWindowToDIB(dc, rectDIB);
}

//�NDDB�ϧ��ഫ���P�]�ƵL�������DIB
BOOL CClientCapture::WriteWindowToDIB( CDC* dc, CRect rect)
{
	CBitmap 	bitmap;
	CDC 		memDC;

	memDC.CreateCompatibleDC(dc); 
	bitmap.CreateCompatibleBitmap(dc, rect.Width(),rect.Height() );
	
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.BitBlt(0, 0, rect.Width(),rect.Height(), dc, 0, 0, SRCCOPY); 

	// �Ы��޿�զ�O
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

	// �ഫDDB��DIB      BI_RGB
	hDIB = DDBToDIB( bitmap, BI_RGB, &pal, dc);

	if( hDIB == NULL )
		return FALSE;

	return TRUE;
}

//�̹��ϧΥ��L�w��
BOOL CClientCapture::Paint(HDC hDC, CPalette * m_pPalette, LPRECT lpDCRect, LPRECT lpDIBRect) const
{

	if (!m_pBMI)
		return FALSE;

	HPALETTE hPal = NULL;           // DIB���զ�O
	HPALETTE hOldPal = NULL;        // �H�e���զ�O

	// ��oDIB�զ�O�A�M��N��]�m��]�ƴy�z��DC��
	if (m_pPalette != NULL)
	{
		hPal = (HPALETTE) m_pPalette->m_hObject;
		hOldPal = ::SelectPalette(hDC, hPal, TRUE);
	}
	//  �]�m�ϥΩԦ��Ҧ�
	::SetStretchBltMode(hDC, COLORONCOLOR);
	BOOL bSuccess = FALSE;
	//  �P�_�O�_�ϥΩԦ�
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
 
	// ���s�]�m�Ѫ��զ�O
	if (hOldPal != NULL)
	{
		::SelectPalette(hDC, hOldPal, TRUE);
	}

	
   return bSuccess;
}

//  �U����ƪ��\��O�NDDB�ഫ��DIB
HANDLE CClientCapture::DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal, 	CDC *dc) 
{
	BITMAP			bm;
	BITMAPINFOHEADER	bi; //�w�q��ϫH���Y,��ϫH���Y�]�t�F��ӹ����ҥΦr�`�ƥH�δy�z�C�⪺�榡�A���~�٥]�A��Ϫ��e�סB���סB�ؼг]�ƪ��쥭���ơB�Ϲ������Y�榡
	LPBITMAPINFOHEADER 	lpbi;
	DWORD			dwLen;
	HANDLE			handle; 
	HDC 			hDC;
	HPALETTE		hPal; //�զ�O
	
	ASSERT( bitmap.GetSafeHandle() ); //��o�y�`

	if( dwCompression == BI_BITFIELDS ) //�����BI_BITFIELDS���Y����,��^
		return NULL;

	// �p�G�S���զ�O
	hPal = (HPALETTE) pPal->GetSafeHandle();
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

	// ��o��ϫH��
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

	// ��l�Ʀ�Ϫ��Y�H��
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

	// �p��H���Y���j�p�M�C���
	int nColors = (1 << bi.biBitCount);
	if( nColors > 256 ) 
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// ��o�]�ƴy�z��
	hDC = dc->GetSafeHdc();
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);
	
	// ���t���s�귽�O�s��ϫH���Y�M�C���
	if(hDIB) GlobalFree( hDIB );

	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDIB){
		SelectPalette(hDC,hPal,FALSE);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	//  ��obiSizeImage���ƭ�
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
			(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// �p�G��^0,�h��ʭp��
	if (bi.biSizeImage == 0)
	{
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
						* bi.biHeight;

		//  �p�G�ĥ����Y��k
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

	// ���t���s�귽�O�s�Ҧ�����H��
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);
		hDIB = 0;
		// ��ܭ�l�զ�O
		SelectPalette(hDC,hPal,FALSE);

		return NULL;
	}

	// ��o��Ϫ���H��
	lpbi = (LPBITMAPINFOHEADER)hDIB;
	m_pBMI = (LPBITMAPINFO)hDIB;
	m_pBits = (LPBYTE)hDIB + (bi.biSize + nColors * sizeof(RGBQUAD));

	// �̫���oDIB
	BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
				0L,						// �}�l���˽u
				(DWORD)bi.biHeight,		// ���˽u�`��
				(LPBYTE) m_pBits, 		// �s���ϦU��ƾڪ��a�}
				(LPBITMAPINFO)lpbi,		// �s���ϫH�����a�}
				(DWORD)DIB_RGB_COLORS);	// �ϥ�RGB�C���

	if( !bGotBits )
	{
		GlobalFree(hDIB);
		hDIB = 0;
		SelectPalette(hDC,hPal,FALSE);

		return NULL;
	}

	SelectPalette(hDC,hPal,FALSE); //��ܽզ�O

	return hDIB;
}

DWORD CClientCapture::Height() const
{
	if (!m_pBMI)
		return 0;
	// ��^DIB������
	return m_pBMI->bmiHeader.biHeight;
}

void CClientCapture::OnDraw(HDC hDC, CRect rcRect, CRect rect)
{
	Paint(hDC, &pal, rcRect, rect);
}

//  �U����ƪ��\��O�NDIB�H���g�J��Ϥ��
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

	// ��g����Y�H�� 
	hdr.bfType		= ((WORD) ('M' << 8) | 'B');	// is always "BM"
	hdr.bfSize		= GlobalSize (hDIB) + sizeof( hdr );
	hdr.bfReserved1 	= 0;
	hdr.bfReserved2 	= 0;
	hdr.bfOffBits		= (DWORD) (sizeof( hdr ) + lpbi->biSize +
						nColors * sizeof(RGBQUAD));

	// �g�J����Y 
	file.Write( &hdr, sizeof(hdr) );

	// �g�JDIB�Y�M��ϼƾ� 
	file.Write( lpbi, GlobalSize(hDIB) );
	
	file.Close(); //�������

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
