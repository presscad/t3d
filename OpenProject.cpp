// OpenProject.cpp : implementation file
 

#include "stdafx.h"
#include "MainFrm.h"
#include "OpenProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// COpenProject dialog




COpenProject::COpenProject(CWnd* pParent /*=NULL*/)
	: CDialog(COpenProject::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenProject)
	//}}AFX_DATA_INIT
}


void COpenProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenProject)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenProject, CDialog)
	//{{AFX_MSG_MAP(COpenProject)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// COpenProject message handlers

BOOL COpenProject::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitListCtrl();//初始化 ListCtrl控件
	
	LoadData();//從數據庫表中加載項目數據
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//從數據庫表中加載項目數據
void COpenProject::LoadData()
{
	CString strsql;

	//從存儲項目名稱、創建日期的Oralce用戶RW3D中讀取所有項目信息
	strsql="Provider=OraOLEDB.Oracle;User Id=RW3D;Password=aaa;";	//定義SQL字符串	
	try
	{
		HRESULT hr =m_Connection->Open(_bstr_t(strsql),"","",-1);//打開數據庫
		if(!SUCCEEDED(hr)) //如果打開失敗
		{
			MessageBox("數據庫連接失敗!","打開項目",MB_ICONINFORMATION);
			return ;//返回
		}
	}
	catch(_com_error& e)	//錯誤處理
	{
		CString errormessage;
		errormessage.Format("錯誤信息:%s",e.ErrorMessage());
		MessageBox("數據庫連接失敗!","打開項目文件",MB_ICONINFORMATION|MB_OK);
		return ;//返回
	} 
	
	//以項目創建日期為升序從Project中讀取所有項目信息
	strsql="select  *   from  Project ORDER BY 建立時間  ASC";  //定義SQL字符串	
	try
	{
		//打開數據表
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(m_Connection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//錯誤處理
	{
		CString errormessage;
		errormessage.Format("打開數據庫表失敗!\r\n錯誤信息:%s",e.ErrorMessage());
		MessageBox(errormessage,"裝載數據",MB_ICONSTOP);
		return;
	} 
	
	//刪除所有數據
	m_list.DeleteAllItems();
	mtotalProjects=0;//總項目數初始值=0
	
    CString tt[3];
	while(!m_Recordset->adoEOF)//如果沒有到記錄集尾
	{    
		Thevalue = m_Recordset->GetCollect("項目名稱"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt[1]=Thevalue.bstrVal;//項目名稱
		}
	
		Thevalue = m_Recordset->GetCollect("建立時間"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt[2]=Thevalue.bstrVal;//建立時間
		}

		tt[0].Format("%d",mtotalProjects+1);//序號

		//將項目名稱,建立時間信息寫入ListCtrl控件中
		m_list.InsertItem(mtotalProjects,tt[0]);      //序號
		m_list.SetItemText(mtotalProjects,1,tt[1]);   //項目名稱
		m_list.SetItemText(mtotalProjects,2,tt[2]);	//項目建立時間
		
		mtotalProjects++;//總項目數+1

		m_Recordset->MoveNext();//記錄集指針下移
	}  

	m_Recordset->Close();  //關閉記錄集
	m_Connection->Close();//關閉數據庫
	
	
}

//單擊ListCtrl控件響應函數,用來得到選擇的項目名稱
void COpenProject::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	NMLISTVIEW    *pNMListView = (NMLISTVIEW    *)pNMHDR;
	
	if(pNMListView->iItem >= 0) //如果選擇
    {
        m_nCurrentItem = pNMListView->iItem;//單擊項目的索引
        m_nCurrentSubItem = pNMListView->iSubItem;
		m_strProjectname=m_list.GetItemText(m_nCurrentItem,1);//得到選擇的項目名稱
    }
	*pResult = 0;
}


//打開項目
void COpenProject::OnButtonOpen() 
{
	CString strsql;

	if(mtotalProjects<=0)	
	{
		MessageBox("沒有項目！","打開項目",MB_ICONINFORMATION|MB_OK);
		return;
	}
	
	if(m_nCurrentItem<0)	
	{
		MessageBox("請選擇要打開的項目！","打開項目",MB_ICONINFORMATION|MB_OK);
		return;
	}
	
	if(	m_strProjectname.IsEmpty())
		return;
	
	BeginWaitCursor();

	
	theApp.m_username=m_strProjectname;
	theApp.m_userpassword="a";
	m_currentSchemeNames=m_strProjectname;
	
	if(theApp.m_pConnection->State) //如果數據庫已打開
		theApp.m_pConnection->Close(); //關閉連接
	
	strsql="Provider=OraOLEDB.Oracle;User Id="+theApp.m_username+";Password="+theApp.m_userpassword+";";
	try
	{
		HRESULT hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);
		if(!SUCCEEDED(hr))
		{
			MessageBox("數據庫連接失敗!","打開項目",MB_ICONINFORMATION);
			theApp.m_pConnection->Close();//關閉數據庫連接
			return ;
		}
	}
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("錯誤信息:%s",e.ErrorMessage());
		MessageBox(errormessage,"打開項目",MB_ICONINFORMATION);
		theApp.m_pConnection->Close();//關閉數據庫連接
		return ;
	} 

	
	//定義SQL字符串
	strsql="select *  from DEM_INFO ";  
	if(m_Recordset->State)	//如果m_Recordset已打開，先關閉
		m_Recordset->Close();
	
	try
	{
		//打開 DEM_INFO數據表,讀取DEM相關信息
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//錯誤處理
	{
		CString errormessage;
		errormessage.Format("打開數據庫表失敗!\r\n錯誤信息:%s",e.ErrorMessage());
		MessageBox(errormessage,"裝載數據",MB_ICONSTOP);
		m_Recordset->Close();
		return ;
	} 
 
    if(!m_Recordset->adoEOF)//如果沒有到記錄集末尾,表示有記錄
	{
		Thevalue = m_Recordset->GetCollect("DEM起點坐標X"); 
		theApp.m_DemLeftDown_x=(double)Thevalue;//DEM左下角x坐標

		Thevalue = m_Recordset->GetCollect("DEM起點坐標Y"); 
		theApp.m_DemLeftDown_y=(double)Thevalue;//DEM左下角y坐標

	
		Thevalue = m_Recordset->GetCollect("格網間距X"); 	
		theApp.m_Cell_xwidth=(long)Thevalue ;//DEM在x方向上格網點間距

		Thevalue = m_Recordset->GetCollect("格網間距Y"); 
		theApp.m_Cell_ywidth=(long)Thevalue;//DEM在y方向上格網點間距
		
		Thevalue = m_Recordset->GetCollect("DEM分塊大小"); 
		theApp.m_Dem_BlockSize=(long)Thevalue;//DEM分塊大小,即一個地形子塊的大小

		Thevalue = m_Recordset->GetCollect("DEM分塊行數"); 
		theApp.m_BlockRows=(long)Thevalue;//DEM分塊的總行數

		Thevalue = m_Recordset->GetCollect("DEM分塊列數"); 
		theApp.m_BlockCols=(long)Thevalue;//DEM分塊的總列數
		
		Thevalue = m_Recordset->GetCollect("原始DEM行數"); 
		theApp.m_Dem_Rows=(long)Thevalue;//DEM數據和總行數
 
		Thevalue = m_Recordset->GetCollect("原始DEM列數"); 
		theApp.m_Dem_cols=(long)Thevalue;//DEM數據和總列數
		
		Thevalue = m_Recordset->GetCollect("無效DEM值"); 
		theApp.m_DEM_IvalidValue=(long)Thevalue;//無效DEM數據點高程值
		
		//DEM地形子塊的寬度(即一個地形塊表示多少空間距離,若分塊大小=33,
		//DEM在x方向上格網點間距=20,則DEM地形子塊寬度=20*32=640米)
		theApp.m_Dem_BlockWidth=theApp.m_Cell_xwidth*(theApp.m_Dem_BlockSize-1);
		
		m_Recordset->Close();//關閉記錄集
	
		//DEM右上角x坐標
		theApp.m_DemRightUp_x=theApp.m_DemLeftDown_x+theApp.m_Cell_xwidth*(theApp.m_Dem_cols-1);
		//DEM右上角y坐標
		theApp.m_DemRightUp_y=theApp.m_DemLeftDown_y+theApp.m_Cell_ywidth*(theApp.m_Dem_Rows-1);

	}
	else
	{
		m_Recordset->Close();//關閉記錄集
		MessageBox("項目沒有數模數據!","打開項目",MB_ICONINFORMATION);
		return ;	//返回
	}


	//定義SQL字符串
	strsql="select *  from IMAGERECT_INFO ";  
	try
	{
		//打開 IMAGERECT_INFO數據表,讀取影像紋理相關信息
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//錯誤處理
	{
		CString errormessage;
		errormessage.Format("打開數據庫表失敗!\r\n錯誤信息:%s",e.ErrorMessage());
		MessageBox(errormessage,"裝載數據",MB_ICONSTOP);
		m_Recordset->Close();//關閉記錄集
		return ;	//返回
	} 
	
	
	if(!m_Recordset->adoEOF)	//如果沒有到記錄集末尾,表示有記錄
	{
		Thevalue = m_Recordset->GetCollect("左下角坐標X"); 
		theApp.m_TexturLeftDown_x=(double)Thevalue;//紋理左下角x坐標
		
		Thevalue = m_Recordset->GetCollect("左下角坐標Y"); 
		theApp.m_TexturLeftDown_y=(double)Thevalue;//紋理左下角y坐標
		
		Thevalue = m_Recordset->GetCollect("右上角坐標X"); 
		theApp.m_TexturRightUp_x=(double)Thevalue ;//紋理右上角x坐標
		
		Thevalue = m_Recordset->GetCollect("右上角坐標Y"); 
		theApp.m_TexturRightUp_y=(double)Thevalue;//紋理右上角y坐標
		
		Thevalue = m_Recordset->GetCollect("影像金字塔總數"); 
		theApp.m_ImagePyramidCount=(long)Thevalue;//紋理影像金字塔總數,即多少LOD級別
	
		Thevalue = m_Recordset->GetCollect("一級影像分辨率"); 
		theApp.m_ImageResolution[1]=(float)Thevalue;//紋理影像一級影像分辨率

		Thevalue = m_Recordset->GetCollect("二級影像分辨率"); 
		theApp.m_ImageResolution[2]=(float)Thevalue;//紋理影像二級影像分辨率

		Thevalue = m_Recordset->GetCollect("三級影像分辨率"); 
		theApp.m_ImageResolution[3]=(float)Thevalue;//紋理影像三級影像分辨率
	
		Thevalue = m_Recordset->GetCollect("四級影像分辨率"); 
		theApp.m_ImageResolution[4]=(float)Thevalue;//紋理影像四級影像分辨率
	
		Thevalue = m_Recordset->GetCollect("五級影像分辨率"); 
		theApp.m_ImageResolution[5]=(float)Thevalue;//紋理影像五級影像分辨率

		m_Recordset->Close();//關閉記錄集
		
	}
	else
	{
		m_Recordset->Close();//關閉記錄集
	}
   
  	
	
	theApp.bLoginSucceed=TRUE;//數據加載成功
	myOci.Init_OCI();//初始化OCI
	
	//定義SQL字符串	
	strsql.Format("select * from Scheme ORDER BY 方案名稱 ASC");
	if(m_Recordset->State)
		m_Recordset->Close();
	try
	{
		//打開 Scheme數據表,讀取打開方案的相關信息
		m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)		//錯誤處理
	{
		CString errormessage;
		errormessage.Format("打開數據庫表失敗!\r\n錯誤信息:%s",e.ErrorMessage());
		MessageBox(errormessage,"打開數據庫表",MB_ICONINFORMATION);
		m_Recordset->Close();//關閉記錄集
		return  ;//返回
	} 	
	
	//GetCollect():Ado獲取數據庫字段值函數
	m_SchemeNames.RemoveAll(); //清空，存儲方案名稱的全局數組
	int index=0; //讀取方案信息
	while(!m_Recordset->adoEOF)
	{
	
		Thevalue = m_Recordset->GetCollect("方案名稱"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].Schemename=Thevalue.bstrVal;//方案名稱
			m_SchemeNames.Add(myDesingScheme.SchemeDatass[index].Schemename);//存儲方案名稱到全局數組
		}

		Thevalue = m_Recordset->GetCollect("設計等級");
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strDesigngrade=Thevalue.bstrVal;//設計等級
			
		}
		
		Thevalue = m_Recordset->GetCollect("牽引種類"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strDraughtstyle=Thevalue.bstrVal;//牽引種類
		}
		

		Thevalue = m_Recordset->GetCollect("機車類型"); //機車類型
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strBlocomotiveStyle=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("閉塞方式"); //閉塞方式
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strCBbsStyle=Thevalue.bstrVal;
		}

		Thevalue = m_Recordset->GetCollect("地形地別");  //地形地別
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strTerrainstyle=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("工程條件"); //工程條件
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strEngineeringcondition=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("設計速度"); //設計速度
		myDesingScheme.SchemeDatass[index].designspeed=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("最小曲線半徑"); //最小曲線半徑
		myDesingScheme.SchemeDatass[index].minRadius=(long)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("到發線有效長度"); //到發線有效長度
		myDesingScheme.SchemeDatass[index].dxfLength=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("最小坡長"); //最小坡長
		myDesingScheme.SchemeDatass[index].minSlopeLength=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("最大坡度"); //最大坡度
		myDesingScheme.SchemeDatass[index].maxSlope=(double)Thevalue;		
	
		Thevalue = m_Recordset->GetCollect("最大坡度差"); //最大坡度差
		myDesingScheme.SchemeDatass[index].maxSlopePddsc=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("起點里程"); //起點里程
		myDesingScheme.SchemeDatass[index].StartLC=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("終點里程"); //終點里程
		myDesingScheme.SchemeDatass[index].EndLC=(double)Thevalue;		
		
		index++;	
		m_Recordset->MoveNext();//記錄集指針下移

	}
	m_Recordset->Close();//關閉記錄集
	if(m_SchemeNames.GetSize()>0)
	{
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		pMainFrame->AddSchemeName();
	}
	MessageBox("打開項目成功!","打開項目",MB_ICONINFORMATION);
    EndWaitCursor();//將光標切換為默認光標,結束等待
	EndDialog(IDOK);
}


//刪除項目
void COpenProject::OnButtonDelete() 
{
	HRESULT hr;
	CString trsql;
	
	
	if(mtotalProjects<=0)	//如果項目的總數<=0，表示還沒有建立項目，不能刪除 
	{
		MessageBox("沒有項目！","刪除項目",MB_ICONINFORMATION|MB_OK);
		return;
	}

	if(m_nCurrentItem<0)	//如果沒有選中ListCtrl控件的項目，返回
	{
		MessageBox("請選擇要刪除的項目！","刪除項目",MB_ICONINFORMATION|MB_OK);
		return;
	}

	//當前打開項目不能刪除
	if(strcmp(theApp.m_username,m_strProjectname)==0)
	{
		MessageBox("當前打開項目為"+m_strProjectname+",不能刪除!","刪除項目",MB_ICONSTOP|MB_OK);
		return;
	}

	//如果m_Connection已處於連接狀態，先關閉，否則再次連接時將出錯
	if(m_Connection->State)
		m_Connection->Close();
	
	BeginWaitCursor();//調用本函數顯示沙漏光標,告訴用戶系統忙
	
	//定義SQL字符串
	CString strsql="Provider=OraOLEDB.Oracle;User Id=RW3D;Password=aaa;";
	try
	{
		hr =m_Connection->Open(_bstr_t(strsql),"","",-1);//連接存儲項目名稱、創建日期的Oralce用戶RW3D
		
		if(!SUCCEEDED(hr))//如果數據庫連接失敗
		{
			MessageBox("數據庫連接失敗!","刪除項目",MB_ICONINFORMATION);
			m_Connection->Close();//關閉連接
			EndWaitCursor();//撤消沙漏光標,並恢復以前的光標
			return ;//返回
		}
	}
	catch(_com_error& e)	//錯誤處理
	{
		CString errormessage;
		errormessage.Format("錯誤信息:%s",e.ErrorMessage());
		MessageBox(errormessage,"刪除項目",MB_ICONINFORMATION);
		m_Connection->Close();//關閉連接
		EndWaitCursor();//撤消沙漏光標,並恢復以前的光標
		return ;//返回
	} 
 
	int manwer=MessageBox("是否刪除項目?","刪除項目",MB_ICONINFORMATION|MB_YESNO);
	if(manwer==7)//如果不刪除項目，返回
		return ;

//	drop tablespace XXXX INCLUDING CONTENTS; 
//	drop user XXXX cascade;
//	Oracle中drop user和drop user cascade的區別
//		drop user ； 僅僅是刪除用戶，
//		drop user ××  cascade ；會刪除此用戶名下的所有表和視圖。加參數就是為了刪除這個用戶下的所有對象! 

	//創建SQL字符串
//	strsql="Provider=OraOLEDB.Oracle;Data Source="+theApp.m_servername+";User Id="+theApp.m_systemname+";Password="+theApp.m_userpassword+";";
//	theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//打開Oracle系統管理員用戶
//	strsql="Drop user "+m_strProjectname+"  cascade";
//	theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);

	
	//定義SQL字符串,(刪除用戶)
	//刪除項目用戶和此用戶名下的所有表和視圖(參數 cascade就是為了刪除這個用戶下的所有對象!)
	strsql="Drop user "+m_strProjectname+"  cascade";
	try
	{
		hr =m_Connection->Execute (_bstr_t(strsql),NULL,adCmdText);//刪除項目
		if(!SUCCEEDED(hr))
		{
			MessageBox("刪除項目失敗!","刪除項目",MB_ICONINFORMATION);
			m_Connection->Close();//關閉連接
			EndWaitCursor();//撤消沙漏光標,並恢復以前的光標
			return ;//返回
		}
	}
	catch(_com_error& e)	//錯誤處理
	{
		CString errormessage;
		errormessage.Format("錯誤信息:%s",e.ErrorMessage());
		m_Connection->Close();//關閉連接
		MessageBox(errormessage,"刪除項目",MB_ICONINFORMATION);
		EndWaitCursor();//撤消沙漏光標,並恢復以前的光標
		return ;//返回
	} 

	strsql.Format("Delete  from Project WHERE 項目名稱='%s'",m_strProjectname);
	hr =m_Connection->Execute (_bstr_t(strsql),NULL,adCmdText);
	m_Connection->Close();//關閉連接
	
	MessageBox("項目刪除成功!","刪除項目",MB_ICONINFORMATION);

	m_nCurrentItem=-1; //恢復為選中狀態
	LoadData(); //重新加載項目數據
	EndWaitCursor();//撤消沙漏光標,並恢復以前的光標
	
}



//打開項目
BOOL  COpenProject::OpenProjects(int NewOrOpen)
{
	CString strsql;

	
	BeginWaitCursor();
	
	//定義SQL字符串
	strsql="select *  from DEM_INFO ";  
	if(m_Recordset->State)	//如果m_Recordset已打開，先關閉
		m_Recordset->Close();
	
	try
	{
		//打開 DEM_INFO數據表,讀取DEM相關信息
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//錯誤處理
	{
		CString errormessage;
		errormessage.Format("打開數據庫表失敗!\r\n錯誤信息:%s",e.ErrorMessage());
		MessageBox(errormessage,"裝載數據",MB_ICONSTOP);
		return FALSE;
	} 
 
    if(!m_Recordset->adoEOF)//如果沒有到記錄集末尾,表示有記錄
	{
		Thevalue = m_Recordset->GetCollect("DEM起點坐標X"); 
		theApp.m_DemLeftDown_x=(double)Thevalue;//DEM左下角x坐標

		Thevalue = m_Recordset->GetCollect("DEM起點坐標Y"); 
		theApp.m_DemLeftDown_y=(double)Thevalue;//DEM左下角y坐標

	
		Thevalue = m_Recordset->GetCollect("格網間距X"); 	
		theApp.m_Cell_xwidth=(long)Thevalue ;//DEM在x方向上格網點間距

		Thevalue = m_Recordset->GetCollect("格網間距Y"); 
		theApp.m_Cell_ywidth=(long)Thevalue;//DEM在y方向上格網點間距
		
		Thevalue = m_Recordset->GetCollect("DEM分塊大小"); 
		theApp.m_Dem_BlockSize=(long)Thevalue;//DEM分塊大小,即一個地形子塊的大小

		Thevalue = m_Recordset->GetCollect("DEM分塊行數"); 
		theApp.m_BlockRows=(long)Thevalue;//DEM分塊的總行數

		Thevalue = m_Recordset->GetCollect("DEM分塊列數"); 
		theApp.m_BlockCols=(long)Thevalue;//DEM分塊的總列數
		
		Thevalue = m_Recordset->GetCollect("原始DEM行數"); 
		theApp.m_Dem_Rows=(long)Thevalue;//DEM數據和總行數
 
		Thevalue = m_Recordset->GetCollect("原始DEM列數"); 
		theApp.m_Dem_cols=(long)Thevalue;//DEM數據和總列數
		
		Thevalue = m_Recordset->GetCollect("無效DEM值"); 
		theApp.m_DEM_IvalidValue=(long)Thevalue;//無效DEM數據點高程值
		
		//DEM地形子塊的寬度(即一個地形塊表示多少空間距離,若分塊大小=33,
		//DEM在x方向上格網點間距=20,則DEM地形子塊寬度=20*32=640米)
		theApp.m_Dem_BlockWidth=theApp.m_Cell_xwidth*(theApp.m_Dem_BlockSize-1);
		
		m_Recordset->Close();//關閉記錄集
	
		//DEM右上角x坐標
		theApp.m_DemRightUp_x=theApp.m_DemLeftDown_x+theApp.m_Cell_xwidth*(theApp.m_Dem_cols-1);
		//DEM右上角y坐標
		theApp.m_DemRightUp_y=theApp.m_DemLeftDown_y+theApp.m_Cell_ywidth*(theApp.m_Dem_Rows-1);

	}
	else
	{
		m_Recordset->Close();//關閉記錄集
		MessageBox("項目沒有數模數據!","打開項目",MB_ICONINFORMATION);
		return FALSE;	//返回
	}


	//定義SQL字符串
	strsql="select *  from IMAGERECT_INFO ";  
	try
	{
		//打開 IMAGERECT_INFO數據表,讀取影像紋理相關信息
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//錯誤處理
	{
		CString errormessage;
		errormessage.Format("打開數據庫表失敗!\r\n錯誤信息:%s",e.ErrorMessage());
		MessageBox(errormessage,"裝載數據",MB_ICONSTOP);
		m_Recordset->Close();//關閉記錄集
		return FALSE;	//返回
	} 
	
	
	if(!m_Recordset->adoEOF)	//如果沒有到記錄集末尾,表示有記錄
	{
		Thevalue = m_Recordset->GetCollect("左下角坐標X"); 
		theApp.m_TexturLeftDown_x=(double)Thevalue;//紋理左下角x坐標
		
		Thevalue = m_Recordset->GetCollect("左下角坐標Y"); 
		theApp.m_TexturLeftDown_y=(double)Thevalue;//紋理左下角y坐標
		
		Thevalue = m_Recordset->GetCollect("右上角坐標X"); 
		theApp.m_TexturRightUp_x=(double)Thevalue ;//紋理右上角x坐標
		
		Thevalue = m_Recordset->GetCollect("右上角坐標Y"); 
		theApp.m_TexturRightUp_y=(double)Thevalue;//紋理右上角y坐標
		
		Thevalue = m_Recordset->GetCollect("影像金字塔總數"); 
		theApp.m_ImagePyramidCount=(long)Thevalue;//紋理影像金字塔總數,即多少LOD級別
	
		Thevalue = m_Recordset->GetCollect("一級影像分辨率"); 
		theApp.m_ImageResolution[1]=(float)Thevalue;//紋理影像一級影像分辨率

		Thevalue = m_Recordset->GetCollect("二級影像分辨率"); 
		theApp.m_ImageResolution[2]=(float)Thevalue;//紋理影像二級影像分辨率

		Thevalue = m_Recordset->GetCollect("三級影像分辨率"); 
		theApp.m_ImageResolution[3]=(float)Thevalue;//紋理影像三級影像分辨率
	
		Thevalue = m_Recordset->GetCollect("四級影像分辨率"); 
		theApp.m_ImageResolution[4]=(float)Thevalue;//紋理影像四級影像分辨率
	
		Thevalue = m_Recordset->GetCollect("五級影像分辨率"); 
		theApp.m_ImageResolution[5]=(float)Thevalue;//紋理影像五級影像分辨率

		m_Recordset->Close();//關閉記錄集
		
	}
	else
	{
		m_Recordset->Close();//關閉記錄集
	}
   
  	
	
	theApp.bLoginSucceed=TRUE;//數據加載成功
	myOci.Init_OCI();//初始化OCI
	
	//定義SQL字符串	
	strsql.Format("select * from Scheme ORDER BY 方案名稱 ASC");
	if(m_Recordset->State)
		m_Recordset->Close();
	try
	{
		//打開 Scheme數據表,讀取打開方案的相關信息
		m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)		//錯誤處理
	{
		CString errormessage;
		errormessage.Format("打開數據庫表失敗!\r\n錯誤信息:%s",e.ErrorMessage());
		MessageBox(errormessage,"打開數據庫表",MB_ICONINFORMATION);
		m_Recordset->Close();//關閉記錄集
		return  FALSE;//返回
	} 	
	
	m_SchemeNames.RemoveAll();	
	//GetCollect():Ado獲取數據庫字段值函數
	int index=0; //讀取方案信息
	while(!m_Recordset->adoEOF)
	{
	
		Thevalue = m_Recordset->GetCollect("方案名稱"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].Schemename=Thevalue.bstrVal;//方案名稱
			m_SchemeNames.Add(myDesingScheme.SchemeDatass[index].Schemename);
			
		}

		Thevalue = m_Recordset->GetCollect("設計等級");
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strDesigngrade=Thevalue.bstrVal;//設計等級
			
		}
		
		Thevalue = m_Recordset->GetCollect("牽引種類"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strDraughtstyle=Thevalue.bstrVal;//牽引種類
		}
		

		Thevalue = m_Recordset->GetCollect("機車類型"); //機車類型
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strBlocomotiveStyle=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("閉塞方式"); //閉塞方式
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strCBbsStyle=Thevalue.bstrVal;
		}

		Thevalue = m_Recordset->GetCollect("地形地別");  //地形地別
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strTerrainstyle=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("工程條件"); //工程條件
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strEngineeringcondition=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("設計速度"); //設計速度
		myDesingScheme.SchemeDatass[index].designspeed=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("最小曲線半徑"); //最小曲線半徑
		myDesingScheme.SchemeDatass[index].minRadius=(long)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("到發線有效長度"); //到發線有效長度
		myDesingScheme.SchemeDatass[index].dxfLength=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("最小坡長"); //最小坡長
		myDesingScheme.SchemeDatass[index].minSlopeLength=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("最大坡度"); //最大坡度
		myDesingScheme.SchemeDatass[index].maxSlope=(double)Thevalue;		
	
		Thevalue = m_Recordset->GetCollect("最大坡度差"); //最大坡度差
		myDesingScheme.SchemeDatass[index].maxSlopePddsc=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("起點里程"); //起點里程
		myDesingScheme.SchemeDatass[index].StartLC=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("終點里程"); //終點里程
		myDesingScheme.SchemeDatass[index].EndLC=(double)Thevalue;		
		
		index++;	
		m_Recordset->MoveNext();//記錄集指針下移

	}
	m_Recordset->Close();//關閉記錄集
	
	if(m_SchemeNames.GetSize()>0)
	{
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		pMainFrame->AddSchemeName();
	}

//	if(NewOrOpen==1) //	1:打開項目  -1:新建項目
	MessageBox("打開項目成功!","打開項目",MB_ICONINFORMATION);
    
    EndWaitCursor();//將光標切換為默認光標,結束等待

	return TRUE; //返回
	
}

//初始化 ListCtrl控件
void COpenProject::InitListCtrl()
{
	// 	1.新加ListControl 控件，屬性中的style屬性頁下的View選擇Report。
	m_list.InsertColumn(0,"序號");          //插入列
	m_list.InsertColumn(1,"項目名稱");
	m_list.InsertColumn(2,"項目創建日期");

	CRect rect;
	m_list.GetClientRect(rect);    //獲得當前客戶區信息                 
	m_list.SetColumnWidth(0,rect.Width()/5);   //設置列的寬度     
	m_list.SetColumnWidth(1,rect.Width()/3);
	m_list.SetColumnWidth(2,rect.Width()/3);
	
	//設置ListControl 控件風格為網格和整行選擇模式
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_GRIDLINES|   LVS_EX_FULLROWSELECT);
}

