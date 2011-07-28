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

//��l�ƫH��
BOOL CTextureBP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitTexture();//��l�Ư��z�W�١A�ö�g��C��ر��� 
	return TRUE; 
}

//��l�Ư��z�W�١A�ö�g��C��ر��� 
void CTextureBP::InitTexture()
{
	CString tt;
	m_list.ResetContent(); //�M��
	for(int i=1;i<=6;i++)  //���z���W��(�i�ھڹ�ڪ����z�ƶi����)
	{
		tt.Format("�����@�Y%d.bmp",i); //���z���W��(�i�ھڹ�ڪ����z���W�ٶi����)
		m_list.AddString(tt);	//�[�J�C��ر���
	}
	for(i=1;i<=6;i++)  
	{
		tt.Format("�٧��@�Y%d.bmp",i);//���z���W��(�i�ھڹ�ڪ����z���W�ٶi����)
		m_list.AddString(tt);		//�[�J�C��ر���
	}
	m_list.AddString("�٧ΰ��[.bmp");//�[�J�C��ر���
	m_list.AddString("�����@�Y.bmp");//�[�J�C��ر���

	m_list.SetCurSel(0);//�q�{��ܶ�����1�����z
	OnSelchangeList(); //�T�����z��ܧ��ܮɪ�����
}

//�T�����z��ܧ��ܮɪ�����
void CTextureBP::OnSelchangeList() 
{
	m_list.GetText(m_list.GetCurSel(),m_BPtextureName);//�o�쯾�z���W
	CDC *pdc=GetDC();
	CRect rect;
	GetDlgItem(IDC_STATIC_BMP)->GetWindowRect(rect); //�o��IDC_STATIC_BMP���󪺫Ȥ�Ϥj�p
	this->ScreenToClient(rect); //�N�̹������ഫ���Τ᧤��
	CString BitmapFilePath;
	
	BitmapFilePath="./���z\\��Y���@\\"+m_BPtextureName;//���z�������|�W��
	myDesingScheme.drawBitmapFormFile(BitmapFilePath,pdc,rect); //�N�襤�����z�v���bIDC_STATIC_BMP�Wø�s
}
