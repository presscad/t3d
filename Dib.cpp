// Dib.cpp: implementation of the CDib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dib.h"
#include "windowsX.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDib::CDib()
{
	m_pBmFileHeader=NULL;
	m_pBmInfo=NULL;
	m_pBmInfoHeader=NULL;
	m_pRGBTable=0;
	m_pDibBits=0;
}

CDib::CDib(const char* fileName)
{
	//裝載位圖
	LoadBitmapFile(fileName);
}


CDib::~CDib()
{
	GlobalFreePtr(m_pBmInfo);
}

void CDib::LoadBitmapFile(const char* fileName)
{
	//打開位圖文件
	CFile file(fileName,CFile::modeRead);
	
	//將位圖文件頭讀入內存
	BITMAPFILEHEADER bmFileHeader;
	file.Read((void*)&bmFileHeader,sizeof(bmFileHeader));

	//檢查是否為位圖
	if(bmFileHeader.bfType!=0x4d42)
	{
		AfxMessageBox("Not a bitmap file");
		m_pBmFileHeader=0;
		m_pBmInfo=0;
		m_pBmInfoHeader=0;
		m_pRGBTable=0;
		m_pDibBits=0;
		m_numColors=0;

	}
	else
	{
		DWORD fileLength=file.GetLength();
		DWORD dibSize=fileLength-sizeof(bmFileHeader);

		//分配全局內存
		BYTE* pDib=(BYTE*)GlobalAllocPtr(GMEM_MOVEABLE,dibSize);
		
		pDib=new BYTE[dibSize];

		file.Read(pDib,dibSize);
		file.Close();

		//初始化指向結構BITMAPINFO和BITMAPINFOHEADER的指針
		m_pBmInfo=(LPBITMAPINFO)pDib;
		m_pBmInfoHeader=(LPBITMAPINFOHEADER)pDib;
		
		//獲得位圖大小
		m_pBmInfoHeader->biSizeImage=GetDibSizeImage();
		m_pDibBits=pDib+m_pBmInfoHeader->biSize;
	}
}

DWORD CDib::GetDibSizeImage()
{
	if(m_pBmInfoHeader->biSizeImage==0)
	{
		//單行字節數,即寬度
		DWORD byteWidth=(DWORD)GetDibWidth();

		//高度
		DWORD height=(DWORD)GetDibHeight();

		DWORD imageSize=byteWidth*height;

		return imageSize;
	}
	else 
		return m_pBmInfoHeader->biSizeImage;
}

UINT CDib::GetDibWidth()
{
	return (UINT)m_pBmInfoHeader->biWidth;
}

UINT CDib::GetDibHeight()
{
	return (UINT)m_pBmInfoHeader->biHeight;
}

LPBITMAPINFOHEADER CDib::GetDibInfoHeaderPtr()
{
	return m_pBmInfoHeader;
}

LPBITMAPINFO CDib::GetDIbInfoPtr()
{
	return m_pBmInfo;
}


BYTE* CDib::GetDibBitsPtr()
{
	return m_pDibBits;
}
