// NewProject.cpp : implementation file
 

#include "stdafx.h"
 
#include "NewProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CNewProject dialog




CNewProject::CNewProject(CWnd* pParent /*=NULL*/)
	: CDialog(CNewProject::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewProject)
	m_systemname = _T("");
	m_systempassword = _T("");
	m_projectname = _T("");
	m_servername = _T("");
	//}}AFX_DATA_INIT
}


void CNewProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProject)
	DDX_Text(pDX, IDC_SYSTEM_NAME, m_systemname);
	DDX_Text(pDX, IDC_SYSTEM_PASSWORD, m_systempassword);
	DDX_Text(pDX, IDC_EDIT_PROJECTNAME, m_projectname);
	DDX_Text(pDX, IDC_SYSTEM_SERVERNAME, m_servername);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProject, CDialog)
	//{{AFX_MSG_MAP(CNewProject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CNewProject message handlers

BOOL CNewProject::CreateNewProject()
{
	_bstr_t Sql;

	CString strtable[200];//項目中最多可創建的數量

	CString strsql;//用於存儲SQL字符串
	CString m_username,m_userpassword;	//存儲新創建的用戶名和密碼

	this->UpdateData();//更新數據

	if(m_projectname.IsEmpty()) //項目名稱不能為空
	{
		MessageBox("項目名稱不能為空!","新建項目",MB_ICONINFORMATION);
		return FALSE; //返回
	}
	
	m_username=m_projectname;//新創建的Oracle用戶名

	//新創建的Oracle用戶密碼,可任意設定,這裡直接給一定默認值,是了為方便,
	//當打開項目時,就不需要輸入項目的密碼就可以直接打開項目)
	m_userpassword="a"; //新創建的Oracle用戶密碼

	theApp.m_username=m_username;//Oracle數據庫系統管理員用戶名
	theApp.m_userpassword=m_userpassword;//Oracle數據庫系統管理員密碼
	theApp.m_servername=m_servername;//Oracle數據庫系統管理員服務器名
	
	if(FAILED(CoInitialize (NULL)))   //初始化ADO
	{
		MessageBox ("ADO初始化失敗!","登錄數據庫",MB_ICONERROR);
		return FALSE;
	}
		
	//創建m_pConnection實例句柄
	HRESULT hr = theApp.m_pConnection.CreateInstance("ADODB.Connection");	
	
	if(theApp.m_pConnection->State) //如果數據庫已打開
		theApp.m_pConnection->Close(); //關閉連接
	
	//創建SQL字符串
	strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_systemname+";Password="+m_systempassword+";";
	try
	{
		hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//打開Oracle系統管理員用戶
		if(!SUCCEEDED(hr)) //打開失敗
		{
			MessageBox("系統管理員數據庫連接失敗!","登錄數據庫",MB_ICONINFORMATION);
			return FALSE;	//返回
		}
	}
	catch(_com_error& e)	//錯誤處理
	{
		CString errormessage;
		errormessage.Format("錯誤信息:%s",e.ErrorMessage());
		errormessage="系統管理員用戶名、密碼或服務器名錯誤!";
		MessageBox(errormessage,"登錄數據庫",MB_ICONINFORMATION);//給出錯誤診斷信息
		return FALSE;	//返回
	} 
 
    //創建一個新用戶， 用於存儲所建的項目名稱
	CString tname,tpass;
	tname="RW3D";	//設定的用戶名稱(可任意用戶名)
	tpass="aaa";	//設定的用戶密碼(可任意密碼)
	strsql.Format("SELECT * FROM dba_users WHERE  username='%s'",tname);
	theApp.m_pRecordset.CreateInstance(_uuidof(Recordset));

	//從Oracle的dba_users表中選取是否有所設定的用戶
	theApp.m_pRecordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	if(theApp.m_pRecordset->adoEOF) //如果沒有該用戶,則創建
	{
		theApp.m_pRecordset->Close();//關閉表
		strsql = "CREATE USER  " + tname + "  IDENTIFIED BY   " + tpass;
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//創建設定的用戶
		
		strsql = "GRANT CREATE SESSION,CREATE TABLE ,UNLIMITED TABLESPACE ,DBA to " + tname;
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//分配創建表等權限
		theApp.m_pConnection->Close();//關閉數據庫連接
		
		strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+tname+";Password="+tpass+";";
		hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//連接新創建的用戶
		strsql= "CREATE TABLE Project(項目名稱 VARCHAR2(50),建立時間 VARCHAR2(20))";
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//在新創建的用戶下創建表Project
		theApp.m_pConnection->Close();//關閉數據庫連接
	
		//重新連接Oracle系統管理員用戶
		strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_systemname+";Password="+m_systempassword+";";
		hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);
	}
	else //如果存儲項目名稱的用戶已經存在,就不再需要創建了(即只是第一次新建項目時,會創建存儲項目名稱的用戶和數據表)
		theApp.m_pRecordset->Close(); //關閉記錄集

	
   //創建項目(根據項目名稱創建Oracle新用戶)
	strsql = "CREATE USER  " + m_username + "  IDENTIFIED BY   " + m_userpassword;
	try
	{
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//創建Oracle新用戶
		if(!SUCCEEDED(hr)) //如果創建失敗
		{
			MessageBox("項目創建失敗!","創建新項目",MB_ICONINFORMATION);
			return FALSE;	//返回
		}

		//為創建項目的新用戶分配創建任務(CREATE SESSION,),創建表(CREATE TABLE),
		//無限製表空間(UNLIMITED TABLESPACE)的權限
		strsql = "GRANT CREATE SESSION,CREATE TABLE ,UNLIMITED TABLESPACE to " + m_username;
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);
		if(!SUCCEEDED(hr))//如果權限賦值失敗
		{
			MessageBox("權限賦值失敗!","創建新項目",MB_ICONINFORMATION);
			return FALSE;//返回
		}
		theApp.m_pConnection->Close();//關閉記錄集
	} 		

	catch(_com_error& e)	//錯誤處理
	{
		CString errormessage;
		
		if(e.WCode()==3092) //如果項目已經存在
		{
			errormessage="項目 "+m_username+" 已經存在,是否刪除?";	
			int nanswer=MessageBox(errormessage,"創建新項目",MB_ICONINFORMATION|MB_YESNO);
			if(nanswer==6)	//刪除已有項目
			{
				strsql="Drop user "+m_username+"  cascade";
				hr =theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//刪除已有項目
				if(!SUCCEEDED(hr))	//如果刪除項目失敗
					MessageBox("刪除項目失敗","刪除項目",MB_ICONINFORMATION);
				else
					MessageBox("刪除項目完成","刪除項目",MB_ICONINFORMATION);
				
			}
		}
		
		else	//其它錯誤信息
		{
			errormessage.Format("錯誤信息:%s",e.ErrorMessage());
			MessageBox(errormessage,"創建新項目",MB_ICONINFORMATION);
		}
		return FALSE;	//返回
	} 

	//連接根據項目名稱創建的新用戶
	strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_username+";Password="+m_userpassword+";";
	try
	{
		hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//連接根據項目名稱創建的新用戶
		if(!SUCCEEDED(hr))//如果連接新用戶失敗
		{
			MessageBox("數據庫連接失敗!","創建新項目",MB_ICONINFORMATION);
			return FALSE;	//返回
		}
	    	
	}
	catch(_com_error& e)	//錯誤處理
	{
		CString errormessage;
		WORD nWcode=e.WCode(); 
		if(e.WCode()==0) //項目戶名錯誤
		{	errormessage="項目戶名錯誤!";
			MessageBox(errormessage,"創建新項目",MB_ICONINFORMATION);
			return FALSE;	//返回
		}
		else	//其它錯誤信息
		{	
			errormessage.Format("錯誤信息:%s",e.ErrorMessage());
			MessageBox(errormessage,"創建新項目",MB_ICONINFORMATION);
			return FALSE; 	//返回
		}
	} 

	//下面代碼為在根據項目名稱創建的新用戶下創建數據表如DEM數據表,影像數據表等
	int index=-1;

	//1.DEM地形信息表
	index++;
	strtable[index]= "CREATE TABLE DEM_INFO(DEM起點坐標X NUMBER(10,3),\
		DEM起點坐標Y NUMBER(10,3),格網間距X NUMBER(3),\
		格網間距Y NUMBER(3),DEM分塊大小 NUMBER(3),\
		DEM分塊行數 NUMBER(6),DEM分塊列數 NUMBER(6),\
		原始DEM行數 NUMBER(10),原始DEM列數 NUMBER(10),\
		DEM數據 BLOB,編號 NUMBER(2),無效DEM值 NUMBER(10))";	
	

	//2.DEM地形子塊數據表
	index++;
	strtable[index]= "CREATE TABLE dem_block(行號 NUMBER(6),\
			列號 NUMBER(6),DEM數據 BLOB,編號 NUMBER(6),\
			中心坐標X NUMBER(10,3),中心坐標Y NUMBER(10,3))";	

	//3.DEM地形子塊信息表
	index++;
	strtable[index]= "CREATE TABLE dem_subblock(行號 NUMBER(6),\
		列號 NUMBER(6),DEM數據 BLOB,所屬塊號 NUMBER(6),編號 NUMBER(6))";	
			
	//4.影像紋理表
	index++;
	strtable[index]= "CREATE TABLE texture(行號 NUMBER(6),\
		  列號 NUMBER(6),長度 NUMBER(6),寬度 NUMBER(6),\
		  紋理金子塔層號 NUMBER(6),紋理數據 BLOB,編號 NUMBER(6),\
		  左下角坐標X NUMBER(10,3),左下角坐標Y NUMBER(10,3),\
		  右上角坐標X NUMBER(10,3),右上角坐標Y NUMBER(10,3))";	
				
	//5.影像LOD信息表
	index++;
	strtable[index]= "CREATE TABLE IMAGERECT_INFO(左下角坐標X NUMBER(10,3),\
		 左下角坐標Y NUMBER(10,3),右上角坐標X NUMBER(10,3),\
		 右上角坐標Y NUMBER(10,3),影像金字塔總數 NUMBER(2),\
		 一級影像分辨率 NUMBER(6,2),二級影像分辨率 NUMBER(6,2),\
		 三級影像分辨率 NUMBER(6,2),\
		 四級影像分辨率 NUMBER(6,2),五級影像分辨率 NUMBER(6,2))";

	index++;
	
	//6.項目方案數據表
	strtable[index]= "CREATE TABLE Scheme (\
		 方案名稱 VARCHAR2(100), 設計等級 VARCHAR2(20),\
		 牽引種類 VARCHAR2(10),機車類型 VARCHAR2(50),閉塞方式 VARCHAR2(50),\
		 地形地別 VARCHAR2(12), 工程條件 VARCHAR2(20),設計速度 NUMBER(6),\
		 最小曲線半徑 NUMBER(6),到發線有效長度 NUMBER(6),\
		 最小坡長 NUMBER(6,2),最大坡度 NUMBER(6,2),最大坡度差 NUMBER(6,2),\
		 起點里程 NUMBER(20,3),終點里程 NUMBER(20,3))";
	
	index++;
	strtable[index]= "CREATE TABLE T3DLineZxCorrdinate (\
		  方案名稱 VARCHAR2(100),序號 NUMBER(10), x坐標 NUMBER(20,3),\
		  y坐標 NUMBER(20,3),z坐標 NUMBER(20,3),坐標類型 VARCHAR2(30),\
		  地面高程 NUMBER(20,3),填挖高 NUMBER(20,3),里程 NUMBER(20,3))";
	

	index++;
	strtable[index]= "CREATE TABLE Scheme_plane_CureveData (\
		  方案名稱 VARCHAR2(100),交點編號 VARCHAR2(50),\
		  轉角 NUMBER(10,3),方位角1 NUMBER(10,3),方位角2 NUMBER(10,3),\
		  轉向 NUMBER(2),緩和曲線長  NUMBER(6),\
		  切線長 NUMBER(15,3),曲線長 NUMBER(15,3),\
		  圓曲線長 NUMBER(15,3),直緩點里程 NUMBER(20,3),\
		  緩圓點里程 NUMBER(20,3),圓緩點里程 NUMBER(20,3),\
		  緩直點里程 NUMBER(20,3),外矢距 NUMBER(10,3),\
		  內移距 NUMBER(10,3),曲線半徑 NUMBER(10),\
		  交點里程 NUMBER(20,3),交點x坐標 NUMBER(20,3),\
		  交點y坐標 NUMBER(20,3),交點z坐標 NUMBER(20,3),\
		  交點序號 NUMBER(10))";
	
	index++;
	strtable[index]= "CREATE TABLE Scheme_plane_CureveData_XY (\
		 方案名稱 VARCHAR2(100),交點編號 VARCHAR2(50),\
		 圓心x坐標 NUMBER(20,3),圓心y坐標 NUMBER(20,3),\
		 直緩x坐標 NUMBER(20,3),直緩y坐標 NUMBER(20,3),\
		 緩圓x坐標 NUMBER(20,3),緩圓y坐標 NUMBER(20,3),\
		 圓緩x坐標 NUMBER(20,3),圓緩y坐標 NUMBER(20,3),\
		 緩直x坐標 NUMBER(20,3),緩直y坐標 NUMBER(20,3),\
		 交點序號 NUMBER(10))";
	

	index++;
	strtable[index]= "CREATE TABLE PriorityRadius (\
		行車速度 NUMBER(4), 曲線半徑最小值 NUMBER(6),\
		曲線半徑最大值 NUMBER(6))";
	
	index++;
	strtable[index]= "CREATE TABLE MinRadius (\
		行車速度 NUMBER(4), 一般地段 NUMBER(6),\
		困難地段 NUMBER(6))";
	
	index++;
	strtable[index]= "CREATE TABLE T3DLineZxCorrdinateZDM (\
		 方案名稱 VARCHAR2(100),序號 NUMBER(10), x坐標 NUMBER(20,3),\
		 y坐標 NUMBER(20,3),z坐標 NUMBER(20,3),坐標類型 VARCHAR2(30),\
		 地面高程 NUMBER(20,3),填挖高 NUMBER(20,3),里程\
		 NUMBER(20,3),交點里程 NUMBER(20,3))";
	
	
	index++;
	strtable[index]= "CREATE TABLE ZDmJDCurve (\
		 方案名稱 VARCHAR2(100), 坡長 NUMBER(20,3),\
		 坡率 NUMBER(20,3),變坡點樁號 NUMBER(20,3),標高 VARCHAR2(30),\
		 豎曲線半徑 NUMBER(20,3),外矢距 NUMBER(20,3),切線長 NUMBER(20,3),\
		 坡度代數差 NUMBER(20,3),序號 NUMBER(10),轉向類型 NUMBER(2),\
		 直緩點里程 NUMBER(20,3),直緩點標高 NUMBER(20,3),\
		 緩直點里程 NUMBER(20,3),緩直點標高 NUMBER(20,3))";
	index++;
	strtable[index]= "CREATE TABLE zdmSegmentGeoFeature (\
		   分段起始里程 NUMBER(10,3),分段終點里程 NUMBER(10,3),\
		   工程地質特徵 VARCHAR2(2000),方案名稱 VARCHAR2(100))";
	
	index++;
	strtable[index]= "CREATE TABLE Tunnel (\
			 隧道名稱 VARCHAR2(400),隧道起點里程 NUMBER(20,3),\
			 隧道終點里程 NUMBER(20,3), 隧道長度 NUMBER(20,3),方案名稱 VARCHAR2(200))";

	index++;
	strtable[index]= "CREATE TABLE Bridge (\
		 橋樑名稱 VARCHAR2(400),橋樑起點里程 NUMBER(20,3),\
		 橋樑終點里程 NUMBER(20,3), 橋樑長度 NUMBER(20,3),\
		 方案名稱 VARCHAR2(200))";

	index++;
	strtable[index]= "CREATE TABLE StationTable (\
		車站名稱 VARCHAR2(200),車站類型 VARCHAR2(50),\
		里程 NUMBER(20,3), 方案名稱 VARCHAR2(200))";

	/*
		還可以繼續創建所需要的數據表
	*/

	//創建所有數據表
	for(int i=0;i<=index;i++)
	{

		HRESULT hr=theApp.m_pConnection->Execute (_bstr_t(strtable[i]),NULL,adCmdText);//創建表
		if(!SUCCEEDED(hr)) //如果表創建失敗,則刪除根據項目名稱新創建的用戶
		{
			MessageBox("表創建失敗!","登錄數據庫",MB_ICONINFORMATION);
			strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_systemname+";Password="+m_systempassword+";";
			hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//重新連接Oracle系統管理員用戶
			strsql = "DROP USER  " + m_username + "  CASCADE   " ;
			hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//刪除新創建的用戶			
			return FALSE;

		}
	}
	theApp.m_pConnection->Close();//關閉數據庫連接

	
	
	//打開用於存儲所建的項目名稱的用戶
	strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+tname+";Password="+tpass+";";
	hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);
	if(!SUCCEEDED(hr))//打開失敗
	{
		MessageBox("數據庫打開錯誤!");
	}
	//下面得到項目創建的日期和時間信息
	CString stt;
	CTime time = CTime::GetCurrentTime();   
	int m_nYear = time.GetYear();     
	int m_nMonth = time.GetMonth();     
	int m_nDay = time.GetDay();     
	int m_nHour = time.GetHour();     
	int m_nMinute = time.GetMinute();   
	int m_nSecond = time.GetSecond();   
	stt.Format("%4d-%2d-%2d",m_nYear,m_nMonth,m_nDay);
	strsql.Format("INSERT INTO Project VALUES('%s','%s')",m_username,stt);
	hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//將項目創建的日期和時間信息寫入Project表中
	theApp.m_pConnection->Close();//關閉數據庫連接
	
	//重新連接根據項目名稱創建的新用戶
	strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_username+";Password="+m_userpassword+";";
	hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);	//連接數據庫
	theApp.bLoginSucceed=TRUE; //數據庫登錄成功
	MessageBox("項目創建成功!","創建新項目",MB_ICONINFORMATION);
	
	return TRUE;
}

BOOL CNewProject::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_servername="test";
	m_systemname="system";
	m_systempassword="manager";
	this->UpdateData(FALSE);
	
	return TRUE;  
}

//確定
void CNewProject::OnOK() 
{
	BeginWaitCursor();//將光標切換為等待光標
	if(CreateNewProject()==TRUE) //創建新項目
	{
		EndWaitCursor();//將光標切換為默認光標,結束等待
		CDialog::OnOK();//結束
	}
	else
	{
		EndWaitCursor();//將光標切換為默認光標,結束等待
	}
	
}
