// RecordPictureSpeed.cpp : implementation file
//

#include "stdafx.h"
#include "T3DSystem.h"
#include "RecordPictureSpeed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordPictureSpeed dialog


CRecordPictureSpeed::CRecordPictureSpeed(CWnd* pParent /*=NULL*/)
	: CDialog(CRecordPictureSpeed::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecordPictureSpeed)
	m_recordPictSpeed = 0;
	//}}AFX_DATA_INIT
}


void CRecordPictureSpeed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecordPictureSpeed)
	DDX_Control(pDX, IDC_SLIDER_RECORDPICTURE_SPEED, m_slider_recordpictSpeed);
	DDX_Text(pDX, IDC_EDIT_RECORDPICTURESPEED, m_recordPictSpeed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecordPictureSpeed, CDialog)
	//{{AFX_MSG_MAP(CRecordPictureSpeed)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecordPictureSpeed message handlers

//��l�ƫH��
BOOL CRecordPictureSpeed::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_slider_recordpictSpeed.SetRange (1,2000); //�]�m�Ķ��Ϲ����W�v�d��A�Y�C�j�h�ֲ@����s�@�T�Ϲ�
	m_slider_recordpictSpeed.SetPos (m_recordPictSpeed); //�]�m��e�Ķ��Ϲ����W�v
    this->UpdateData (FALSE); //�ƾڧ�s
	
	
	return TRUE;  
}

//�T�������u�ʱ�����
void CRecordPictureSpeed::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	this->UpdateData(TRUE); //��s�ܶq�ƾ�
	
	//�p�G�OIDC_SLIDER_RECORDPICTURE_SPEED����
	if(pScrollBar->GetDlgCtrlID() ==IDC_SLIDER_RECORDPICTURE_SPEED)
	{
		m_recordPictSpeed=m_slider_recordpictSpeed.GetPos (); //�o��ҳ]�m���Ķ��Ϲ��W�v
		this->UpdateData(FALSE);//�ƾڧ�s
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
