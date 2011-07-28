// TunncelPropertySet.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "TunncelPropertySet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CTunncelPropertySet dialog


CTunncelPropertySet::CTunncelPropertySet(CWnd* pParent /*=NULL*/)
	: CDialog(CTunncelPropertySet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTunncelPropertySet)
	m_tunnel_height = 0.0f;
	m_tunnel_ArcSegmentNumber = 0;
	m_tunnel_Archeight = 0.0f;
	m_tunnel_WallHeight = 0.0f;
	m_tunnel_H = 0.0f;
	m_tunnel_L = 0.0f;
	//}}AFX_DATA_INIT
}


void CTunncelPropertySet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTunncelPropertySet)
	DDX_Text(pDX, IDC_EDIT_TUNNELHEIGHT, m_tunnel_height);
	DDX_Text(pDX, IDC_EDIT_ARCSEGMENTNUMBERS, m_tunnel_ArcSegmentNumber);
	DDV_MinMaxInt(pDX, m_tunnel_ArcSegmentNumber, 5, 100);
	DDX_Text(pDX, IDC_EDIT_ARCHEIGHT, m_tunnel_Archeight);
	DDX_Text(pDX, IDC_EDIT_WALLHEIGHT, m_tunnel_WallHeight);
	DDX_Text(pDX, IDC_EDIT_H, m_tunnel_H);
	DDX_Text(pDX, IDC_EDIT_L, m_tunnel_L);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTunncelPropertySet, CDialog)
	//{{AFX_MSG_MAP(CTunncelPropertySet)
	ON_EN_CHANGE(IDC_EDIT_ARCHEIGHT, OnChangeEditArcheight)
	ON_EN_CHANGE(IDC_EDIT_TUNNELHEIGHT, OnChangeEditTunnelheight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CTunncelPropertySet message handlers

void CTunncelPropertySet::OnOK() 
{
	this->UpdateData();
	//�G�D���ݶ꩷����
	if(m_tunnel_Archeight>m_tunnel_height)
	{
		MessageBox("�G�D���ݶ꩷���פ���j���G�D�`����!","�ƾ��ˬd",MB_ICONSTOP);
		return;
	}

	if(m_tunnel_ArcSegmentNumber<5)
	{
		MessageBox("�G�D���ݶ꩷���q�Ƥ���p��5!","�ƾ��ˬd",MB_ICONSTOP);
		return;
	}
	if(m_tunnel_ArcSegmentNumber>100)
	{
		MessageBox("�G�D���ݶ꩷���q�Ƥ���j��100!","�ƾ��ˬd",MB_ICONSTOP);
		return;
	}
	


	CDialog::OnOK();
}

BOOL CTunncelPropertySet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	�K���G�D����: 
//		(1)���U�o��:��6��,�e12.88��(��u4.88) 
//		(2)�q�O�o��:��6.55��,�e12.88��(��u4.88)

/*
	m_tunnel_height=6.55;//�G�D�`����
	m_tunnel_ArcSegmentNumber=20;//��꩷���q��(�]�N�O��ꦱ�u�W�ļ��I��)
	m_tunnel_Archeight=2;//�G�D���ݾ�꩷����
	m_tunnel_ArcCYdistence=10;//�u�u����V�ļ˶��Z
	m_tunnel_WallHeight=m_tunnel_height-m_tunnel_Archeight;////�G�D�U�ݥ��𰪫�
*/
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTunncelPropertySet::OnChangeEditArcheight() 
{
	this->UpdateData();
	m_tunnel_WallHeight=m_tunnel_height-m_tunnel_Archeight;
	this->UpdateData(FALSE);
}

void CTunncelPropertySet::OnChangeEditTunnelheight() 
{
	this->UpdateData();
	m_tunnel_WallHeight=m_tunnel_height-m_tunnel_Archeight;
	this->UpdateData(FALSE);
	
}
