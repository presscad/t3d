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
		ID_INDICATOR_LOADRENDERDEM,//【內存/渲染塊數】
		ID_INDICATOR_FPS,//刷新頻率
		ID_INDICATOR_TRINUMBER,//三角形數
		ID_INDICATOR_FSANGLE,//【俯視角】=
		ID_INDICATOR_VIEWPOS,//視點坐標
		ID_INDICATOR_PROGRESSBAR,//進度條
		
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
  //   skinppLoadSkin(_T("skin\\AlphaOS.ssk")); //加載皮膚
	
}

CMainFrame::~CMainFrame()
{
//	skinppExitSkin(); //退出界面庫，做清理工作。
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

	//創建正射投影模式下的工具欄
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

	//設置各指示器的索引、寬度等信息
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
	EnableDocking(CBRS_ALIGN_ANY);//	工具欄
	DockControlBar(&m_wndToolBar);
	
	m_wndOrthoToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);//工具欄
	DockControlBar(&m_wndOrthoToolBar);
	m_wndOrthoToolBar.ShowWindow(SW_SHOW);	//工具欄可見
	
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

//根據索引在狀態欄上顯示相關信息
void CMainFrame::Set_BarText(int index, CString strText, int nPos)
{
	switch(index)
	{
	case 0://【內存/渲染塊數】
		m_wndStatusBar.SetPaneText (index,strText);
		break;
	case 1://刷新頻率
		m_wndStatusBar.SetPaneText (index,strText);
		break;
	case 2: //三角形數
		m_wndStatusBar.SetPaneText (index,strText);
		break;
	case 3: //【俯視角】
		m_wndStatusBar.SetPaneText (index,strText);
		break;
	case 4: //視點坐標
		m_wndStatusBar.SetPaneText (index,strText);
		break;
	case 5: //進度條

		if(nPos<=0)
		{
			m_progress.ShowWindow(SW_HIDE);//隱藏進度條
			m_wndStatusBar.SetPaneText (index,strText);
		}
		else
		{	
	//		m_progress.ShowWindow(SW_SHOW);//顯示進度條
	//		m_progress.SetPos(nPos);
		}

		break;
		
	}
}

//刷新狀態欄指示器上的進度條
void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	//得到狀態欄指示器上存放進度條的客戶區大小
	m_wndStatusBar.GetItemRect(m_wndStatusBar.CommandToIndex(ID_INDICATOR_PROGRESSBAR),&rect);
	if (!m_progress.m_hWnd)  //如果沒有創建進度條控件，則創建                     
	{
		m_progress.Create(WS_CHILD|PBS_SMOOTH , rect, &m_wndStatusBar, 123);
	}
	else
	{
		m_progress.MoveWindow(rect);    //將進度條移動到狀態欄指示器上對應的位置   
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
	
 
	strsql.Format("select * FROM  Scheme_plane_CureveData WHERE 方案名稱='%s' ORDER BY 交點序號 ASC",m_currentSchemeNames);	
	try
	{
		m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	
	{
		
		CString errormessage;
		errormessage.Format("打開數據庫表失敗!\r\n錯誤信息:%s",e.ErrorMessage());
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
		Thevalue = m_Recordset->GetCollect("交點編號"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt=Thevalue.bstrVal;
			pTempCurveElements->ID=tt;
		}
	
		Thevalue = m_Recordset->GetCollect("轉角"); 
		pTempCurveElements->Alfa=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("方位角1"); 
		pTempCurveElements->fwj=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("方位角2"); 
		pTempCurveElements->fwj2=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("轉向"); 
		pTempCurveElements->RoateStyle=(short)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("緩和曲線長"); 
		pTempCurveElements->L0=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("切線長"); 
		pTempCurveElements->T=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("曲線長"); 
		pTempCurveElements->L=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("圓曲線長"); 
		pTempCurveElements->Ly=(double)Thevalue;

		Thevalue = m_Recordset->GetCollect("直緩點里程"); 
		pTempCurveElements->ZH=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("緩圓點里程"); 
		pTempCurveElements->HY=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("圓緩點里程"); 
		pTempCurveElements->YH=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("緩直點里程"); 
		pTempCurveElements->HZ=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("外矢距"); 
		pTempCurveElements->E=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("內移距"); 
		pTempCurveElements->P=(double)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("曲線半徑"); 
		pTempCurveElements->R=(long)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("交點里程"); 
		pTempCurveElements->JDLC=(long)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("交點x坐標"); 
		pTempCurveElements->x=(double)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("交點y坐標"); 
		pTempCurveElements->y=(double)Thevalue;
	
		Thevalue = m_Recordset->GetCollect("交點z坐標"); 
		pTempCurveElements->z=(double)Thevalue;
		
 
		myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].Add(pTempCurveElements);
	
		ppt=new Cordinate;
		ppt->x=pTempCurveElements->x;ppt->y=pTempCurveElements->z;ppt->z=-pTempCurveElements->y;
		myDesingScheme.PtS_JD.Add(ppt);
		
		m_Recordset->MoveNext();
	}
	m_Recordset->Close();


	
	
	strsql.Format("select * FROM  Scheme_plane_CureveData_XY WHERE 方案名稱='%s' ORDER BY 交點序號 ASC",m_currentSchemeNames);	
	try
	{
		m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	
	{
		
		CString errormessage;
		errormessage.Format("打開數據庫表失敗!\r\n錯誤信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
		m_Recordset->Close();
		return;
	} 

	long n=0;
	while(!m_Recordset->adoEOF)
	{
		pTempCurveElements=myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].GetAt(n);
	
 
 
 
 
 
		
		Thevalue = m_Recordset->GetCollect("圓心x坐標"); 
		pTempCurveElements->Cneterx=(double)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("圓心y坐標"); 
		pTempCurveElements->Cnetery=(double)Thevalue;
		
		pTempCurveElements->ZH_xy=new  Cordinate;		
		Thevalue = m_Recordset->GetCollect("直緩x坐標"); 
		pTempCurveElements->ZH_xy->x=(double)Thevalue;
		Thevalue = m_Recordset->GetCollect("直緩y坐標"); 
		pTempCurveElements->ZH_xy->y=(double)Thevalue;
	
		pTempCurveElements->HY_xy=new  Cordinate;		
		Thevalue = m_Recordset->GetCollect("緩圓x坐標"); 
		pTempCurveElements->HY_xy->x=(double)Thevalue;
		Thevalue = m_Recordset->GetCollect("緩圓y坐標"); 
		pTempCurveElements->HY_xy->y=(double)Thevalue;

		pTempCurveElements->YH_xy=new  Cordinate;		
		Thevalue = m_Recordset->GetCollect("圓緩x坐標"); 
		pTempCurveElements->YH_xy->x=(double)Thevalue;
		Thevalue = m_Recordset->GetCollect("圓緩y坐標"); 
		pTempCurveElements->YH_xy->y=(double)Thevalue;
		
		pTempCurveElements->HZ_xy=new  Cordinate;		
		Thevalue = m_Recordset->GetCollect("緩直x坐標"); 
		pTempCurveElements->HZ_xy->x=(double)Thevalue;
		Thevalue = m_Recordset->GetCollect("緩直y坐標"); 
		pTempCurveElements->HZ_xy->y=(double)Thevalue;
		
		n++;
		m_Recordset->MoveNext();
	}
	m_Recordset->Close();
   	


}
