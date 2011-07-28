// ModelMangerQD.cpp : implementation file
//

#include "stdafx.h"
#include "T3DSystem.h"
#include "ModelMangerQD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelMangerQD dialog


CModelMangerQD::CModelMangerQD(CWnd* pParent /*=NULL*/)
	: CDialog(CModelMangerQD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModelMangerQD)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CModelMangerQD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModelMangerQD)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModelMangerQD, CDialog)
	//{{AFX_MSG_MAP(CModelMangerQD)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelMangerQD message handlers

void CModelMangerQD::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}


//��l�ƫH��
BOOL CModelMangerQD::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitData(); //��l�ƾ��[�ҫ�
	
	return TRUE;  
}

//��l�ƾ��[�ҫ�
void CModelMangerQD::InitData()
{
	m_list.ResetContent(); //�M��
	m_list.AddString("�����X�ʼ[");
	m_list.AddString("��W�����[");
	m_list.AddString("��[���X�ʼ[");
	m_list.AddString("�V�X���W�����[");
	m_list.AddString("�Ƭ[�άX�ʼ[");
	m_list.AddString("�W�X�U��[");
	m_list.AddString("���W�����[");
	m_list.AddString("�׹a�����[");
	m_list.AddString("���O���x�ξ��[");
	m_list.AddString("���O����ݧξ��[");
	m_list.AddString("���O����ξ��[");
	m_list.AddString("�O�������˾��[");
	m_list.SetCurSel(0); //�q�{��ܶ�����1���ҫ�
	
}

//�T���ҫ���ܧ��ܮɪ�����
void CModelMangerQD::OnSelchangeList() 
{
	CString BitmapFilePath,strFilename,tt;
	
	int index=m_list.GetCurSel(); //�o��C��ť��e����
	if(index<0) //�p�G��e����<0�A��^
		return;
	
	m_list.GetText(index,tt); //�o��ҫ����W
	
	strFilename.Format("%s\\%s.bmp",tt,tt);
	CDC *pdc=GetDC();
	CRect rect;
	GetDlgItem(IDC_STATIC_BMP)->GetWindowRect(rect);//�o��IDC_STATIC_BMP���󪺫Ȥ�Ϥj�p
	this->ScreenToClient(rect);//�N�̹������ഫ���Τ᧤��
	
	BitmapFilePath=".\\�ҫ�\\���ټ[�x\\"+strFilename;
	m_3DSfilename_QD.Format(".\\�ҫ�\\���ټ[�x\\%s\\�ҫ����.3ds",tt);//�o��ҫ��]�t������|�����W

	//�N�襤���ҫ��v���bIDC_STATIC_BMP�Wø�s
	myDesingScheme.drawBitmapFormFile(BitmapFilePath,pdc,rect);	
	
	
}
