// AviParameter1.cpp : implementation file
//

#include "stdafx.h"
#include "T3DSystem.h"
#include "AviParameter1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAviParameter dialog


CAviParameter::CAviParameter(CWnd* pParent /*=NULL*/)
	: CDialog(CAviParameter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAviParameter)
	m_AviFilename = _T("");
	m_AVIFrame = 0;
	m_AVIHeight = 0;
	m_AVIWidth = 0;
	//}}AFX_DATA_INIT
}


void CAviParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAviParameter)
	DDX_Control(pDX, IDC_SLIDER_MOVIE_WIDTH, m_Slider_AVIWidth);
	DDX_Control(pDX, IDC_SLIDER_MOVIE_HEIGHT, m_Slider_AVIHeight);
	DDX_Control(pDX, IDC_SLIDER_FRAME, m_slider_frame);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_AviFilename);
	DDX_Text(pDX, IDC_EDIT_FRAME, m_AVIFrame);
	DDX_Text(pDX, IDC_EDIT_MOVIE_HEIGHT, m_AVIHeight);
	DDX_Text(pDX, IDC_EDIT_MOVIE_WIDTH, m_AVIWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAviParameter, CDialog)
	//{{AFX_MSG_MAP(CAviParameter)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAviParameter message handlers

//�Ы�AVI���
void CAviParameter::OnButtonBrowse() 
{
	CString s;
	s="Microsoft AVI (*.avi)|*.avi||";
	CFileDialog fd(FALSE,"avi",0,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY|OFN_PATHMUSTEXIST,s);
	if(fd.DoModal ()==IDOK) //�p�G����ܮإ��}���\
	{
		m_AviFilename=fd.GetPathName();  //�o��ʵe���W
		this->UpdateData (FALSE); //�ƾڧ�s
		if(m_AviFilename.IsEmpty ()) //�p�G�ʵe���W����
		{
			this->MessageBox ("���W���ର��!","�ʵe���Ѽ�",MB_OK|MB_ICONERROR);
			return; //��^
		}
	}
}

//�T��IDOK���s����
void CAviParameter::OnOK() 
{
	if(this->UpdateData ()==TRUE )
	{
		if(m_AviFilename.IsEmpty ()) //�p�G���W�ʵe���W���šA��^
			return;
		this->EndDialog (IDOK); 
	}		
	
	CDialog::OnOK();
}

//��l�ƫH��
BOOL CAviParameter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_slider_frame.SetRange (1,30); //�]�m�����V�v�d��
	m_slider_frame.SetPos (m_AVIFrame); //�]�m�����V�v��l��
	
	m_Slider_AVIWidth.SetRange (1,m_MoviemaxWidth);//�]�m�����ϰ�e�׽d��
	m_Slider_AVIHeight.SetRange (1,m_MoviemaxHeight);//�]�m�����ϰ�e�ת�l��
	
	m_Slider_AVIWidth.SetPos (m_MovieWidth);//�]�m�����ϰ찪�׽d��
	m_Slider_AVIHeight.SetPos (m_MovieHeight);//�]�m�����ϰ찪�ת�l��
	
	m_AVIHeight=m_MovieWidth; //�ʵe����
	m_AVIWidth=m_MovieHeight;//�ʵe�e��
	
    this->UpdateData (FALSE); //��s����ƾ�

	return TRUE;  
}

//�T�������u�ʱ�����
void CAviParameter::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	this->UpdateData(TRUE); //��s�ܶq�ƾ�
	
	switch(pScrollBar->GetDlgCtrlID())
	{
	case  IDC_SLIDER_FRAME: //�p�G�O�����V�v
		m_AVIFrame=m_slider_frame.GetPos (); //�o�쮷���V�v
		break;
	case  IDC_SLIDER_MOVIE_WIDTH://�p�G�O�����ϰ�e��
		m_AVIWidth=m_Slider_AVIWidth.GetPos (); //�o��AVI���e��
		m_MovieWidth=m_AVIWidth;
		break;
	case  IDC_SLIDER_MOVIE_HEIGHT://�p�G�O�����ϰ찪��
		m_AVIHeight=m_Slider_AVIHeight.GetPos (); //�o��AVI������
		m_MovieHeight=m_AVIHeight;
		break;
	}
	
    this->UpdateData(FALSE);//��s����ƾ�
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
