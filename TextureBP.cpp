// TextureBP.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "TextureBP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CTextureBP dialog


CTextureBP::CTextureBP(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureBP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextureBP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTextureBP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureBP)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextureBP, CDialog)
	//{{AFX_MSG_MAP(CTextureBP)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CTextureBP message handlers

//初始化信息
BOOL CTextureBP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitTexture();//初始化紋理名稱，並填寫到列表框控件中 
	return TRUE; 
}

//初始化紋理名稱，並填寫到列表框控件中 
void CTextureBP::InitTexture()
{
	CString tt;
	m_list.ResetContent(); //清空
	for(int i=1;i<=6;i++)  //紋理文件名稱(可根據實際的紋理數進行更改)
	{
		tt.Format("拱形護坡%d.bmp",i); //紋理文件名稱(可根據實際的紋理文件名稱進行更改)
		m_list.AddString(tt);	//加入列表框控件中
	}
	for(i=1;i<=6;i++)  
	{
		tt.Format("菱形護坡%d.bmp",i);//紋理文件名稱(可根據實際的紋理文件名稱進行更改)
		m_list.AddString(tt);		//加入列表框控件中
	}
	m_list.AddString("菱形骨架.bmp");//加入列表框控件中
	m_list.AddString("平形護坡.bmp");//加入列表框控件中

	m_list.SetCurSel(0);//默認選擇項為第1項紋理
	OnSelchangeList(); //響應紋理選擇改變時的消息
}

//響應紋理選擇改變時的消息
void CTextureBP::OnSelchangeList() 
{
	m_list.GetText(m_list.GetCurSel(),m_BPtextureName);//得到紋理文件名
	CDC *pdc=GetDC();
	CRect rect;
	GetDlgItem(IDC_STATIC_BMP)->GetWindowRect(rect); //得到IDC_STATIC_BMP控件的客戶區大小
	this->ScreenToClient(rect); //將屏幕坐標轉換成用戶坐標
	CString BitmapFilePath;
	
	BitmapFilePath="./紋理\\邊坡防護\\"+m_BPtextureName;//紋理文件全路徑名稱
	myDesingScheme.drawBitmapFormFile(BitmapFilePath,pdc,rect); //將選中的紋理影像在IDC_STATIC_BMP上繪製
}
