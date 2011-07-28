// TextureLoad.cpp : implementation file
 

#include "stdafx.h"
 
#include "TextureLoad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CTextureLoad dialog

#define   BUFFERLEN   102400

CTextureLoad::CTextureLoad(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureLoad::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextureLoad)
	//}}AFX_DATA_INIT
}


void CTextureLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureLoad)
	DDX_Control(pDX, IDC_LIST_FILES, m_listfiles);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextureLoad, CDialog)
	//{{AFX_MSG_MAP(CTextureLoad)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CTextureLoad message handlers


//瀏覽外部紋理文件
void CTextureLoad::OnButtonBrowse() 
{
	CString  strFile,strFilter="Tif files(*.Tif)|*.Tif|\
							 BMP files(*.BMP)|*.BMP|\
							 Jpeg files(*.JPG)|*.JPG|\
							 GIF files(*.GIF)|*.GIF|\
							 PCX files(*.PCX)|*.PCX|\
							 Targa files(*.TGA)|*.TGA||";

	//定制打開文件對話框，使支持多項選擇(OFN_ALLOWMULTISELECT)
	CFileDialog   fdlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT,strFilter);     

	char  *pBuf= new  char[BUFFERLEN];//申請緩衝區
	
	fdlg.m_ofn.lpstrFile=pBuf;    //讓pBuf代替CFileDialog緩衝區	
	fdlg.m_ofn.lpstrFile[0]='\0';     
	fdlg.m_ofn.nMaxFile=BUFFERLEN; 


	int nCount=0;//初始選擇的文件數為0
	
	//如果成功，獲取對話框多項選擇的文件，並依次添加到列表框裡
	if(fdlg.DoModal()==IDOK)     
	{     
        //GetStartPosition():返回指示遍歷映射起始位置的POSITION位置，如果映射為空，則返回NULL
		POSITION  pos=fdlg.GetStartPosition();  
		m_listfiles.ResetContent();//清空列表框
	
		while(pos)   //如果映射不為空
		{   
			nCount++; 
			strFile=fdlg.GetNextPathName(pos);  //得到文件名
			m_listfiles.AddString(strFile);//將文件名加入到列表框
		}     
	}  
	
	delete[]  pBuf;   //回收緩衝區
}

//初始化對話框
BOOL CTextureLoad::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	myOci.Init_OCI();	//初始化OCI
	return TRUE;  
}

//對各級紋理影像逐個分塊處理,並寫入oracle數據庫中
void CTextureLoad::OnOK() 
{

	CString mfilename,stt,tt;

	BeginWaitCursor();

	CString tempDirctory="c:\\tempRailwayBmp";//存放紋理影像子塊的臨時文件夾
	DWORD  dwAttr=GetFileAttributes(tempDirctory);   //獲取文件夾屬性
	if(dwAttr==0xFFFFFFFF)  //如果該文件夾不存在就創建一個   
        CreateDirectory(tempDirctory,NULL);  //創建臨時文件夾

	m_listfiles.SetCurSel(0);
	m_listfiles.GetText(m_listfiles.GetCurSel(),mfilename);
	if(GetTextureRange(mfilename)==FALSE)
		return;
	
	//對各級紋理影像逐個分塊處理,並寫入oracle數據庫中
	for(int i=0;i<m_listfiles.GetCount();i++)
	{
		m_listfiles.SetCurSel(i); //設置列表框當前索引
		m_listfiles.GetText(m_listfiles.GetCurSel(),mfilename);//得到當前包含全路徑的影像文件名
		int nPos=mfilename.ReverseFind('\\');
		tt=mfilename.Mid(nPos+1,mfilename.GetLength()-nPos);//得到影像文件名
		
		stt.Format("正在處理：%s",tt);
		this->SetWindowText(stt);	//設置對話框標題
		SeperateImage(mfilename,i,tempDirctory);//對影像紋理進行分塊處理,並寫入oracle數據庫中	
	}	

	//將影像紋理總體信息寫入影像信息表中
	tt.Format("INSERT INTO IMAGERECT_INFO VALUES(%.3f,%.3f,%.3f,%.3f,%d,\
		%.2f,%.2f,%.2f,%.2f,%.2f)",theApp.m_TexturLeftDown_x,theApp.m_TexturLeftDown_y,\
		theApp.m_TexturRightUp_x,theApp.m_TexturRightUp_y,m_listfiles.GetCount(),\
		theApp.m_ImageResolution[1],theApp.m_ImageResolution[2],theApp.m_ImageResolution[3],\
		theApp.m_ImageResolution[4],theApp.m_ImageResolution[5]);
	theApp.m_pConnection->Execute (_bstr_t(tt),NULL,adCmdText);//執行SQL語句
	
	EndWaitCursor(); //將光標切換為默認光標,結束等待
	m_progress.ShowWindow(SW_HIDE);//隱藏進度條
	m_progress.SetPos(0);//恢復初始位置0值
	MessageBox("影像紋理文件寫入完成!","影像紋理入庫",MB_OK);
	RemoveDirectory(tempDirctory); //刪除臨時文件夾
	theApp.bLoadImage=TRUE;//加載影像成功
		
	CDialog::OnOK();
}

//將紋理影像進行分塊處理,並寫入oracle數據庫中
void CTextureLoad::SeperateImage(CString mfilename, int m_phramidLayer,CString tempDirctory)
{
	
		CString stt,strfile;
        m_pImageObject=new CImageObject;
		
		m_pImageObject->Load(mfilename,NULL,-1,-1);//加載影像紋理
		long m_height=m_pImageObject->GetHeight();//得到紋理高度
		long m_width=m_pImageObject->GetWidth();//得到紋理寬度

		//當前LOD級別的紋理分辨率
		theApp.m_ImageResolution[m_phramidLayer]=(theApp.m_TexturRightUp_x-theApp.m_TexturLeftDown_x)/m_width;
	

		//紋理影像子塊的寬度
		int m_fg_width=theApp.m_Dem_BlockWidth/theApp.m_ImageResolution[m_phramidLayer]; 
		//紋理影像子塊的高度
		int m_fg_height=theApp.m_Dem_BlockWidth/theApp.m_ImageResolution[m_phramidLayer];

		//計算當前LOD級的紋理影像分塊的總行數
		if(m_height%m_fg_height==0)
			m_totalRows=m_height/m_fg_height;
		else
		{
			m_totalRows=m_height/m_fg_height+1;
			
		}
		
		//計算當前LOD級的紋理影像分塊的總列數
		if(m_width%m_fg_width==0)
			m_totalCols=m_width/m_fg_width;
		else
		{
			m_totalCols=m_width/m_fg_width+1;
			
		}		
		
		int nPos=mfilename.ReverseFind('\\');
		strfile=mfilename.Mid(nPos+1,mfilename.GetLength()-nPos-5);

		for(int i=0;i<m_totalRows;i++)
		{
			for(int j=0;j<m_totalCols;j++)
			{
			
			//設置進度條值
			m_progress.SetPos((i*m_totalCols+j+1)*100.0/(m_totalRows*m_totalCols));
			int mleftx=(j-0)*m_fg_width;	    //影像子塊左下角x坐標
			int mlefty=(m_totalRows-i-1)*m_fg_height;	//影像子塊左下角y坐標
			int mrightx=mleftx+m_fg_width-1;	//影像子塊右上角x坐標
			int mrigty=mlefty+m_fg_height-1;	//影像子塊右上角y坐標
			m_pImageObject->Crop( mleftx, mlefty, mrightx, mrigty);	//讀取由mleftx、mlefty、mrightx和mrigty所確定的影像子塊
			stt.Format("%s\\%s@%d_%d.bmp",tempDirctory,strfile,i,j);
			m_pImageObject->Save( stt, 1);//將讀取的影像子塊存儲到臨時文件中
			int m_subImageWidth=m_pImageObject->GetWidth();//得到影像子塊的寬度
			int m_subImageHeight=m_pImageObject->GetHeight();//得到影像子塊的高度
		    //將影像子塊以BLOB數據類型寫入oracle數據庫中
			WriteImageToDB(stt,i+1,j+1,m_subImageHeight,m_subImageWidth,m_phramidLayer,m_fg_width,m_fg_height);
			DeleteFile(stt);
			m_pImageObject->Load(mfilename,NULL,-1,-1);//重新加載原始影像
			}
		}
}

//將影像子塊以BLOB數據類型寫入oracle數據庫中
BOOL CTextureLoad::WriteImageToDB(CString strFile, int m_RowIndex, int m_ColIndex, int m_height, int m_width, int m_phramidLayer,int m_fg_width,int m_fg_height)
{
	
	CString tt;
	
	double m_leftdownx,m_leftdowny,m_rightUpx,m_rightUpy;

	//計算將影像子塊的左下和左上角x,y大地坐標
	m_leftdownx=(m_ColIndex-1)*m_fg_width*theApp.m_ImageResolution[m_phramidLayer]+theApp.m_TexturLeftDown_x;
	m_leftdowny=(m_RowIndex-1)*m_fg_height*theApp.m_ImageResolution[m_phramidLayer]+theApp.m_TexturLeftDown_y;
	m_rightUpx=m_leftdownx+m_width*theApp.m_ImageResolution[m_phramidLayer];
	m_rightUpy=m_leftdowny+m_height*theApp.m_ImageResolution[m_phramidLayer];

	int m_ID=(m_RowIndex-1)*m_totalCols+m_ColIndex;//影像子塊的ID號

	tt.Format("INSERT INTO texture VALUES(%d,%d,%d,%d,%d,EMPTY_BLOB(),\
		%ld,%.3f,%.3f,%.3f,%.3f)",\
		m_RowIndex,m_ColIndex,m_height,m_width,m_phramidLayer,m_ID,\
		m_leftdownx,m_leftdowny,m_rightUpx,m_rightUpy);
	
	//調用OCI公共類的AddNormalDataToDB函數，將常規數據類型的數據寫入oracle數據庫中
	myOci.AddNormalDataToDB(tt);

	//調用OCI公共類的AddBOLBDataToDB函數，將BLOB類型的數據寫入oracle數據庫中
	tt.Format("SELECT 紋理數據 FROM texture WHERE 行號=%d AND 列號=%d AND 紋理金子塔層號=%d AND 編號= :%d FOR UPDATE",m_RowIndex,m_ColIndex,m_phramidLayer,m_ID)  ;
	myOci.AddBOLBDataToDB(strFile,tt,m_ID);
	
	return TRUE;
}

//銷毀對話框
void CTextureLoad::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_pImageObject=NULL;
	delete m_pImageObject;
	
}

 
//將最後一級紋理影像不進行分塊直接寫入數據庫中,將其作為導航圖紋理
BOOL CTextureLoad::WriteLittleLodImageToDB(CString strFile)
{
	
	CString tt;
	int m_ID=1;
	
	tt.Format("INSERT INTO texture_LitLOD VALUES(EMPTY_BLOB(),%d)",m_ID);
	//調用OCI公共類的AddNormalDataToDB函數，將常規數據類型的數據寫入oracle數據庫中
	myOci.AddNormalDataToDB(tt);
	
	tt.Format("SELECT 紋理數據 FROM texture_LitLOD WHERE  編號= :%d FOR UPDATE",m_ID)  ;
	//調用OCI公共類的AddBOLBDataToDB函數，將BLOB類型的數據寫入oracle數據庫中
	myOci.AddBOLBDataToDB(strFile,tt,m_ID);
	return TRUE;
}


//得到影像紋理的左下和右上角 x,y坐標
BOOL CTextureLoad::GetTextureRange(CString tcrPathname)
{
	/*
	
	影像紋理坐標文件是以項目名稱同名的，擴展名為".tod"的文件中存儲的，其格式為：
	lb: 781395.000	1869975.000
	rt: 797995.000	1876275.000
	其中	第一行的lb:表示影像紋理的左下角x,y坐標
			第二行的rt:表示影像紋理的右上角x,y坐標
	*/
	CString tt,strpath;
	int	pos=tcrPathname.ReverseFind('\\');
	strpath=tcrPathname.Left(pos);
	pos=strpath.ReverseFind('\\');
	tt=strpath.Right(strpath.GetLength()-pos-1);
    FILE *fp;
	tt=strpath+"\\"+tt+".tod";//得到影像範圍文件名
	
	if((fp=fopen(tt,"r"))==NULL)//如果文件打開失敗
    {
		MessageBox("影像範圍文件"+tt+"不存在!","讀取影像範圍文件",MB_ICONINFORMATION+MB_OK);
		fclose(fp);	//關閉文件
		return FALSE;//返回FALSE
	}
	else
	{
		fscanf(fp,"%s",tt);//得到lb:字符串
		fscanf(fp,"%s",tt);theApp.m_TexturLeftDown_x=atof(tt);//紋理的左下角x坐標
		fscanf(fp,"%s\n",tt);theApp.m_TexturLeftDown_y=atof(tt);//紋理的左x,y坐標
		fscanf(fp,"%s",tt);//得到rt:字符串
		fscanf(fp,"%s",tt);theApp.m_TexturRightUp_x=atof(tt);//紋理的右上角x坐標
		fscanf(fp,"%s\n",tt);theApp.m_TexturRightUp_y=atof(tt);//紋理的右上角y坐標
		fclose(fp);//關閉文件
		return TRUE;//返回TRUE
		
	}
	
}
