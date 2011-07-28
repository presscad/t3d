// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "T3DSystem.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
		ID_INDICATOR_LOADRENDERDEM,//�i���s/��V���ơj
		ID_INDICATOR_FPS,//��s�W�v
		ID_INDICATOR_TRINUMBER,//�T���μ�
		ID_INDICATOR_FSANGLE,//�i�������j=
		ID_INDICATOR_VIEWPOS,//���I����
		ID_INDICATOR_PROGRESSBAR,//�i�ױ�
		
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
  //   skinppLoadSkin(_T("skin\\AlphaOS.ssk")); //�[���ֽ�
	
}

CMainFrame::~CMainFrame()
{
//	skinppExitSkin(); //�h�X�ɭ��w�A���M�z�u�@�C
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      
	}

	//�Ыإ��g��v�Ҧ��U���u����
	if (!m_wndOrthoToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD  | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndOrthoToolBar.LoadToolBar(IDR_TOOLBAR_ORTHO))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	//�]�m�U���ܾ������ޡB�e�׵��H��
	m_wndStatusBar.SetPaneInfo(0, ID_INDICATOR_LOADRENDERDEM,SBPS_NORMAL,155);
	m_wndStatusBar.SetPaneInfo(1, ID_INDICATOR_FPS,SBPS_NORMAL,85);
	m_wndStatusBar.SetPaneInfo(2, ID_INDICATOR_TRINUMBER,SBPS_NORMAL,90);
	m_wndStatusBar.SetPaneInfo(3, ID_INDICATOR_FSANGLE,SBPS_NORMAL,120);
	m_wndStatusBar.SetPaneInfo(4, ID_INDICATOR_VIEWPOS,SBPS_NORMAL,350);
	m_wndStatusBar.SetPaneInfo(5, ID_INDICATOR_PROGRESSBAR,SBPS_STRETCH,100);


	RECT rect;
	int index=m_wndToolBar.CommandToIndex(ID_TOOL_SCHEME);
    m_wndToolBar.SetButtonInfo(index, ID_TOOL_SCHEME, TBBS_SEPARATOR, 120);
    m_wndToolBar.GetItemRect(index, &rect);
    rect.top+=2;
    rect.bottom += 200;

	if (!m_wndToolBar.m_wndScheme.Create(WS_CHILD|WS_VISIBLE | CBS_AUTOHSCROLL | 
		CBS_DROPDOWNLIST | CBS_HASSTRINGS ,
		rect, &m_wndToolBar, ID_TOOL_SCHEME))
    {
		TRACE0("Failed to create combo-box\n");
		return FALSE;
    }
    m_wndToolBar.m_wndScheme.ShowWindow(SW_SHOW);

	
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);//	�u����
	DockControlBar(&m_wndToolBar);
	
	m_wndOrthoToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);//�u����
	DockControlBar(&m_wndOrthoToolBar);
	m_wndOrthoToolBar.ShowWindow(SW_SHOW);	//�u����i��
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

//�ھگ��ަb���A��W��ܬ����H��
void CMainFrame::Set_BarText(int index, CString strText, int nPos)
{
	switch(index)
	{
	case 0://�i���s/��V���ơj
		m_wndStatusBar.SetPaneText (index,strText);
		break;
	case 1://��s�W�v
		m_wndStatusBar.SetPaneText (index,strText);
		break;
	case 2: //�T���μ�
		m_wndStatusBar.SetPaneText (index,strText);
		break;
	case 3: //�i�������j
		m_wndStatusBar.SetPaneText (index,strText);
		break;
	case 4: //���I����
		m_wndStatusBar.SetPaneText (index,strText);
		break;
	case 5: //�i�ױ�

		if(nPos<=0)
		{
			m_progress.ShowWindow(SW_HIDE);//���öi�ױ�
			m_wndStatusBar.SetPaneText (index,strText);
		}
		else
		{	
	//		m_progress.ShowWindow(SW_SHOW);//��ܶi�ױ�
	//		m_progress.SetPos(nPos);
		}

		break;
		
	}
}

//��s���A����ܾ��W���i�ױ�
void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	//�o�쪬�A����ܾ��W�s��i�ױ����Ȥ�Ϥj�p
	m_wndStatusBar.GetItemRect(m_wndStatusBar.CommandToIndex(ID_INDICATOR_PROGRESSBAR),&rect);
	if (!m_progress.m_hWnd)  //�p�G�S���Ыضi�ױ�����A�h�Ы�                     
	{
		m_progress.Create(WS_CHILD|PBS_SMOOTH , rect, &m_wndStatusBar, 123);
	}
	else
	{
		m_progress.MoveWindow(rect);    //�N�i�ױ����ʨ쪬�A����ܾ��W��������m   
	}
}



void CMainFrame::AddSchemeName()
{
	m_wndToolBar.m_wndScheme.ResetContent();
	for(int i=0;i<m_SchemeNames.GetSize();i++)
	{
		m_wndToolBar.m_wndScheme.AddString(m_SchemeNames.GetAt(i));
		
	}
	if(m_wndToolBar.m_wndScheme.GetCount()>0)
	{
		m_wndToolBar.m_wndScheme.SetCurSel(0);
		OnSelectScheme();
	}
	myDesingScheme.m_TotalSchemeNums=m_wndToolBar.m_wndScheme.GetCount();
	if(myDesingScheme.m_TotalSchemeNums<0)
		myDesingScheme.m_TotalSchemeNums=0;
}

void CMainFrame::OnSelectScheme()
{
	CString strSchemeName;
	m_wndToolBar.m_wndScheme.GetWindowText(strSchemeName);
	m_currentSchemeIndexs=m_wndToolBar.m_wndScheme.GetCurSel();
	m_currentSchemeNames=strSchemeName; 
	myDesingScheme.LoadData(strSchemeName);	
	LoadSchemeData();
	myDesingScheme.JDCurveElements.RemoveAll();
}

void CMainFrame::LoadSchemeData()
{	
	CString tt,strsql;
	
 
	strsql.Format("select * FROM  Scheme_plane_CureveData WHERE ��צW��='%s' ORDER BY ���I�Ǹ� ASC",m_currentSchemeNames);	
	try
	{
		m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	
	{
		
		CString errormessage;
		errormessage.Format("���}�ƾڮw����!\r\n���~�H��:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		m_Recordset->Close();
		return;
	} 

 
	myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_JD.RemoveAll();
	PCordinate ppt;
	PLineCurve pTempCurveElements;
	while(!m_Recordset->adoEOF)
	{
		pTempCurveElements=new LineCurve;
		Thevalue = m_Recordset->GetCollect("���I�s��"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt=Thevalue.bstrVal;
			pTempCurveElements->ID=tt;
		}
	
		Thevalue = m_Recordset->GetCollect("�ਤ"); 
		pTempCurveElements->Alfa=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("��쨤1"); 
		pTempCurveElements->fwj=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("��쨤2"); 
		pTempCurveElements->fwj2=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("��V"); 
		pTempCurveElements->RoateStyle=(short)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("�w�M���u��"); 
		pTempCurveElements->L0=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("���u��"); 
		pTempCurveElements->T=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("���u��"); 
		pTempCurveElements->L=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("�ꦱ�u��"); 
		pTempCurveElements->Ly=(double)Thevalue;

		Thevalue = m_Recordset->GetCollect("���w�I���{"); 
		pTempCurveElements->ZH=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("�w���I���{"); 
		pTempCurveElements->HY=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("��w�I���{"); 
		pTempCurveElements->YH=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("�w���I���{"); 
		pTempCurveElements->HZ=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("�~�ڶZ"); 
		pTempCurveElements->E=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("�����Z"); 
		pTempCurveElements->P=(double)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("���u�b�|"); 
		pTempCurveElements->R=(long)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("���I���{"); 
		pTempCurveElements->JDLC=(long)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("���Ix����"); 
		pTempCurveElements->x=(double)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("���Iy����"); 
		pTempCurveElements->y=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("���Iz����"); 
		pTempCurveElements->z=(double)Thevalue;
		
 
		myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].Add(pTempCurveElements);
	
		ppt=new Cordinate;
		ppt->x=pTempCurveElements->x;ppt->y=pTempCurveElements->z;ppt->z=-pTempCurveElements->y;
		myDesingScheme.PtS_JD.Add(ppt);
		
		m_Recordset->MoveNext();
	}
	m_Recordset->Close();


	
	
	strsql.Format("select * FROM  Scheme_plane_CureveData_XY WHERE ��צW��='%s' ORDER BY ���I�Ǹ� ASC",m_currentSchemeNames);	
	try
	{
		m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	
	{
		
		CString errormessage;
		errormessage.Format("���}�ƾڮw����!\r\n���~�H��:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		m_Recordset->Close();
		return;
	} 

	long n=0;
	while(!m_Recordset->adoEOF)
	{
		pTempCurveElements=myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].GetAt(n);
	
 
 
 
 
 
		
		Thevalue = m_Recordset->GetCollect("���x����"); 
		pTempCurveElements->Cneterx=(double)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("���y����"); 
		pTempCurveElements->Cnetery=(double)Thevalue;
		
		pTempCurveElements->ZH_xy=new  Cordinate;		
		Thevalue = m_Recordset->GetCollect("���wx����"); 
		pTempCurveElements->ZH_xy->x=(double)Thevalue;
		Thevalue = m_Recordset->GetCollect("���wy����"); 
		pTempCurveElements->ZH_xy->y=(double)Thevalue;
	
		pTempCurveElements->HY_xy=new  Cordinate;		
		Thevalue = m_Recordset->GetCollect("�w��x����"); 
		pTempCurveElements->HY_xy->x=(double)Thevalue;
		Thevalue = m_Recordset->GetCollect("�w��y����"); 
		pTempCurveElements->HY_xy->y=(double)Thevalue;

		pTempCurveElements->YH_xy=new  Cordinate;		
		Thevalue = m_Recordset->GetCollect("��wx����"); 
		pTempCurveElements->YH_xy->x=(double)Thevalue;
		Thevalue = m_Recordset->GetCollect("��wy����"); 
		pTempCurveElements->YH_xy->y=(double)Thevalue;
		
		pTempCurveElements->HZ_xy=new  Cordinate;		
		Thevalue = m_Recordset->GetCollect("�w��x����"); 
		pTempCurveElements->HZ_xy->x=(double)Thevalue;
		Thevalue = m_Recordset->GetCollect("�w��y����"); 
		pTempCurveElements->HZ_xy->y=(double)Thevalue;
		
		n++;
		m_Recordset->MoveNext();
	}
	m_Recordset->Close();
   	


}
