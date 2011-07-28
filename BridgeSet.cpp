// BridgeSet.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "BridgeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CBridgeSet dialog


CBridgeSet::CBridgeSet(CWnd* pParent /*=NULL*/)
	: CDialog(CBridgeSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBridgeSet)
	m_Bridge_HLSpace = 0.0f;
	m_Bridge_HLWidth = 0.0f;
	m_Bridge_HLHeight = 0.0f;
	m_Bridge_QDSpace = 0.0f;
	m_Bridge_SetHeight = 0.0f;
	m_Bridge_HPangle = 0;
	//}}AFX_DATA_INIT
}


void CBridgeSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBridgeSet)
	DDX_Text(pDX, IDC_EDIT_HLSPACE, m_Bridge_HLSpace);
	DDX_Text(pDX, IDC_EDIT_HLWIDTH, m_Bridge_HLWidth);
	DDX_Text(pDX, IDC_EDIT_HLHEIGHT, m_Bridge_HLHeight);
	DDX_Text(pDX, IDC_EDIT_QDSPACE, m_Bridge_QDSpace);
	DDX_Text(pDX, IDC_EDIT_SETBRIDGEHEIGHT, m_Bridge_SetHeight);
	DDX_Text(pDX, IDC_EDIT_HPANGLE, m_Bridge_HPangle);
	DDX_Control(pDX, IDC_MSFLEXGRID, m_gridColor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBridgeSet, CDialog)
	//{{AFX_MSG_MAP(CBridgeSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CBridgeSet message handlers

//�T���u�T�w�v���s����
void CBridgeSet::OnOK() 
{
	this->UpdateData(); //�ƾڧ�s
	
	CDialog::OnOK();
}

//��l�ƫH��
BOOL CBridgeSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//��l�ƪ�汱��
	m_gridColor.SetColWidth(0,3000);//�]�m�C�e
	m_gridColor.SetRowHeight(0,400);//�]�m�氪
	m_gridColor.SetRow(0); //�]�m��e�欰��0��
	m_gridColor.SetCol(0);//�]�m��e�C����0�C
	m_gridColor.SetCellBackColor(RGB(m_bridgeColorR,m_bridgeColorG,m_bridgeColorB));//�]�m�I����
	
	return TRUE;  
}

BEGIN_EVENTSINK_MAP(CBridgeSet, CDialog)
    //{{AFX_EVENTSINK_MAP(CBridgeSet)
	ON_EVENT(CBridgeSet, IDC_MSFLEXGRID, -600 /* Click */, OnClickMsflexgrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

//�T��������汱�����
void CBridgeSet::OnClickMsflexgrid() 
{
	CColorDialog colorDlg;
	
	if(colorDlg.DoModal()==IDOK)
	{
		long m_color=colorDlg.GetColor(); //�o���C��
		m_bridgeColorR=GetRValue(m_color); //������q 
		m_bridgeColorG=GetGValue(m_color);//�����q 
		m_bridgeColorB=GetBValue(m_color);//�Ŧ���q 
		m_gridColor.SetRow(0); //�]�m��e�欰��0��
		m_gridColor.SetCol(0);//�]�m��e�C����0�C
		m_gridColor.SetCellBackColor(m_color);//�]�m�I����
	}	
	
}
