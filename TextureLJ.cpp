// TextureLJ.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "TextureLJ.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CTextureLJ dialog


CTextureLJ::CTextureLJ(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureLJ::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextureLJ)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTextureLJ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureLJ)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextureLJ, CDialog)
	//{{AFX_MSG_MAP(CTextureLJ)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CTextureLJ message handlers

BOOL CTextureLJ::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitTexture();//��l�Ư��z�W�١A�ö�g��C��ر��� 
	
	return TRUE; 
}


void CTextureLJ::InitTexture()
{
	CString tt;
	m_list.ResetContent();//�M��
	for(int i=1;i<=12;i++)  //���z���W��(�i�ھڹ�ڪ����z�ƶi����)
	{
		tt.Format("%d.bmp",i);
		m_list.AddString(tt);		//�[�J�C��ر���
	}

	m_list.SetCurSel(0);//�q�{��ܶ�����1�����z
	OnSelchangeList(); //�T�����z��ܧ��ܮɪ�����
}

//�T�����z��ܧ��ܮɪ�����
void CTextureLJ::OnSelchangeList() 
{
	m_list.GetText(m_list.GetCurSel(),m_LJtextureName);//�o�쯾�z���W
	CDC *pdc=GetDC();
	CRect rect;
	GetDlgItem(IDC_STATIC_BMP)->GetWindowRect(rect);//�o��IDC_STATIC_BMP���󪺫Ȥ�Ϥj�p
	this->ScreenToClient(rect); //�N�̹������ഫ���Τ᧤��
	CString BitmapFilePath;
	BitmapFilePath="./���z\\����\\"+m_LJtextureName;//���z�������|�W��
	myDesingScheme.drawBitmapFormFile(BitmapFilePath,pdc,rect);	//�N�襤�����z�v���bIDC_STATIC_BMP�Wø�s
}
