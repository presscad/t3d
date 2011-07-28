// SpaceSearchSet.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "SpaceSearchSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CSpaceSearchSet dialog


CSpaceSearchSet::CSpaceSearchSet(CWnd* pParent /*=NULL*/)
	: CDialog(CSpaceSearchSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpaceSearchSet)
	m_shizxLength = 5;
	m_shuzxHeight =20;
	//}}AFX_DATA_INIT
}


void CSpaceSearchSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpaceSearchSet)
	DDX_Control(pDX, IDC_COMBOL_WIDTH, m_combolWidth);
	DDX_Text(pDX, IDC_EDIT_SHIZXLENGTH, m_shizxLength);
	DDX_Text(pDX, IDC_EDIT_SHUZXHEIGHT, m_shuzxHeight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpaceSearchSet, CDialog)
	//{{AFX_MSG_MAP(CSpaceSearchSet)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, OnButtonColor)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CSpaceSearchSet message handlers

// �C����s�T�����
void CSpaceSearchSet::OnButtonColor() 
{
	CColorDialog colorDlg;//�w�q�C���ܮ��ܶq
	if(colorDlg.DoModal()==IDOK)//�p�G�C���ܮإ��}���\
	{
		long m_color=colorDlg.GetColor();//�o��ҿ�ܪ��C��
		pbrush.DeleteObject ();//�R��pbrush�e��ﹳ
		pbrush.CreateSolidBrush (m_color);//�ھکҿ�ܪ��C�⭫�s�Ыصe��
		CButton *pbutton=(CButton*)GetDlgItem(IDC_BUTTON_COLOR);
		CRect rect;
		pbutton->GetClientRect(rect);
		pbutton->InvalidateRect(rect,TRUE);//��s�C����s�T,
		
		m_QueryColorR=GetRValue(m_color);//�o��ҿ�ܪ��C�⪺����
		m_QueryColorG=GetGValue(m_color);//�o��ҿ�ܪ��C�⪺���
		m_QueryColorB=GetBValue(m_color);//�o��ҿ�ܪ��C�⪺�Ŧ�
	
	}		
}

//�ھ��C����s��ܪ��C���R��I��
HBRUSH CSpaceSearchSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->GetDlgCtrlID()== IDC_BUTTON_COLOR)//�p�G����ID=IDC_BUTTON_COLOR,��pbrush�e�����s�I��
		return pbrush;
	else //�_�h,��^�q�{�e��
		return hbr;
	
}

//�H����l��
BOOL CSpaceSearchSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	myedit[0].SubclassDlgItem(IDC_EDIT_SHIZXLENGTH,this);
//	myedit[1].SubclassDlgItem(IDC_EDIT_SHUZXHEIGHT,this);
		
	m_combolWidth.ResetContent();//�s�x�лx�u�e�ת��U�ԮزM��
	for(int i=1;i<=20;i++)//�u�e�̤j�e�׬�20
	{
		CString tt;
		tt.Format("%d",i);
		m_combolWidth.AddString(tt);
	}

	//�]�m�U�Ԯت���e��ܶ�
	if(m_QueryLineWidth>0)
		m_combolWidth.SetCurSel(m_QueryLineWidth-1);
	else
		m_combolWidth.SetCurSel(0);

	this->UpdateData(FALSE);//�ƾ��ܶq��s
	
	//�ھڼлx�u�C��Ыصe��
	pbrush.CreateSolidBrush(RGB(m_QueryColorR,m_QueryColorG,m_QueryColorB));
	
	return TRUE;  
}

BOOL CSpaceSearchSet::PreTranslateMessage(MSG* pMsg) 
{
 
	if(pMsg->wParam == VK_RETURN)//�p�G���s�O�^����
	{
		CDialog *pWnd=(CDialog*)GetParent();
		pWnd->NextDlgCtrl ();
		return FALSE;
	}	
	else
		return CDialog::PreTranslateMessage(pMsg);
}


//�T�w���s�T�����
void CSpaceSearchSet::OnOK() 
{
	this->UpdateData();//��s�ƾ�
	CString tt;
	m_combolWidth.GetLBText(m_combolWidth.GetCurSel(),tt);//�o��
	m_QueryLineWidth=m_combolWidth.GetCurSel();//�o��лx�u�e��
	CDialog::OnOK();//�HIDOK�Ҧ������h�X��ܮ�
}
