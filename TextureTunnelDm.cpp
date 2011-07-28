// TextureTunnelDm.cpp : implementation file
//

#include "stdafx.h"
#include "T3DSystem.h"
#include "TextureTunnelDm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextureTunnelDm dialog


CTextureTunnelDm::CTextureTunnelDm(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureTunnelDm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextureTunnelDm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTextureTunnelDm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureTunnelDm)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextureTunnelDm, CDialog)
	//{{AFX_MSG_MAP(CTextureTunnelDm)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextureTunnelDm message handlers

void CTextureTunnelDm::InitTexture()
{
	CString tt;
	m_list.ResetContent();//�M��
	for(int i=1;i<=4;i++)  //���z���W��(�i�ھڹ�ڪ����z�ƶi����)
	{
		tt.Format("%d.bmp",i);
		m_list.AddString(tt);		//�[�J�C��ر���		
	}
	
	m_list.SetCurSel(0);//�q�{��ܶ�����1�����z
	OnSelchangeList(); //�T�����z��ܧ��ܮɪ�����
}

BOOL CTextureTunnelDm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitTexture();//��l�Ư��z�W�١A�ö�g��C��ر��� 
	return TRUE;  
}

//�T�����z��ܧ��ܮɪ�����
void CTextureTunnelDm::OnSelchangeList() 
{
	m_TextureIndex=m_list.GetCurSel()+1;
	m_list.GetText(m_list.GetCurSel(),m_TunnelDmtextureName);//�o�쯾�z���W
	CDC *pdc=GetDC();
	CRect rect;
	GetDlgItem(IDC_STATIC_BMP)->GetWindowRect(rect);//�o��IDC_STATIC_BMP���󪺫Ȥ�Ϥj�p
	this->ScreenToClient(rect);
	CString BitmapFilePath;//�N�̹������ഫ���Τ᧤��
	BitmapFilePath="./���z\\�G�D�}��\\"+m_TunnelDmtextureName;//���z�������|�W��
	myDesingScheme.drawBitmapFormFile(BitmapFilePath,pdc,rect);//�N�襤�����z�v���bIDC_STATIC_BMP�Wø�s
	
}
