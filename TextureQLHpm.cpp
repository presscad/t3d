// TextureQLHpm.cpp : implementation file
//

#include "stdafx.h"
#include "T3DSystem.h"
#include "TextureQLHpm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextureQLHpm dialog


CTextureQLHpm::CTextureQLHpm(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureQLHpm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextureQLHpm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTextureQLHpm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureQLHpm)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextureQLHpm, CDialog)
	//{{AFX_MSG_MAP(CTextureQLHpm)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextureQLHpm message handlers

//��l�Ư��z�W�١A�ö�g��C��ر��� 
void CTextureQLHpm::InitTexture()
{
	CString tt;
	m_list.ResetContent();//�M��
	for(int i=1;i<=3;i++)  //���z���W��(�i�ھڹ�ڪ����z�ƶi����)
	{
		tt.Format("%d.bmp",i);
		m_list.AddString(tt);	//�[�J�C��ر���	
	}

	m_list.SetCurSel(0);//�q�{��ܶ�����1�����z
	OnSelchangeList(); //�T�����z��ܧ��ܮɪ�����
}

BOOL CTextureQLHpm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitTexture();//��l�Ư��z�W�١A�ö�g��C��ر��� 
	return TRUE; 
}

//�T�����z��ܧ��ܮɪ�����
void CTextureQLHpm::OnSelchangeList() 
{
	m_list.GetText(m_list.GetCurSel(),m_HQMtextureName);//�o�쯾�z���W
	CDC *pdc=GetDC();
	CRect rect;
	GetDlgItem(IDC_STATIC_BMP)->GetWindowRect(rect);//�o��IDC_STATIC_BMP���󪺫Ȥ�Ϥj�p
	this->ScreenToClient(rect);//�N�̹������ഫ���Τ᧤��
	CString BitmapFilePath;
	BitmapFilePath="./���z\\���U���@�Y��\\"+m_HQMtextureName;//���z�������|�W��
	myDesingScheme.drawBitmapFormFile(BitmapFilePath,pdc,rect);//�N�襤�����z�v���bIDC_STATIC_BMP�Wø�s
}
