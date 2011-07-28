// DemLoad.cpp : implementation file
 

#include "stdafx.h"
 
#include "DemLoad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


 
// CDemLoad dialog

CDemLoad::CDemLoad(CWnd* pParent /*=NULL*/)
	: CDialog(CDemLoad::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemLoad)
	m_DemFileName = _T("");
	m_strblockinfo = _T("");
	m_strsubblockinfo = _T("");
	//}}AFX_DATA_INIT
}


void CDemLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemLoad)
	DDX_Control(pDX, IDC_COMBO_SUBBLOCKSIZE, m_subCombolblockSize);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Text(pDX, IDC_EDIT_DEMFILE, m_DemFileName);
	DDX_Text(pDX, IDC_EDIT_BLOCKINFOR, m_strblockinfo);
	DDX_Text(pDX, IDC_EDIT_SUBBLOCKINFOR, m_strsubblockinfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDemLoad, CDialog)
	//{{AFX_MSG_MAP(CDemLoad)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_SEPERATE, OnButtonSeperate)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBBLOCKSIZE, OnSelchangeComboSubblocksize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CDemLoad message handlers

//將DEM子塊數據寫入數據庫中
void CDemLoad::AddDemBlockDataToDB(int RowIndex, int ColIndex, CString strfilenaem, long ID)
{
	CString tt;
	double centerx,centery;

	//DEM子塊的中心坐標
	centerx=theApp.m_DemLeftDown_x+((ColIndex-1)+1.0/2)*theApp.m_Dem_BlockWidth;
	centery=theApp.m_DemLeftDown_y+((RowIndex-1)+1.0/2)*theApp.m_Dem_BlockWidth;

	tt.Format("INSERT INTO dem_block VALUES(%d,%d,EMPTY_BLOB(),%ld,%.3f,%.3f)",\
		RowIndex,ColIndex,ID,centerx,centery);

	myOci.AddNormalDataToDB(tt);//將常規數據類型寫入oralce數據庫中

	tt.Format("SELECT DEM數據 FROM dem_block WHERE 行號=%d AND 列號=%d AND 編號= :%d FOR UPDATE",RowIndex,ColIndex,ID)  ;
	myOci.AddBOLBDataToDB(strfilenaem,tt,ID);//將DEM分塊文件作為BLOB類型數據類型寫入oralce數據庫中
	
}


//初始化DEM分塊大小
void CDemLoad::Init_BlockSize()
{
	long mvalue=1;
	int m;
	CString tt;
	m_subCombolblockSize.ResetContent ();
	for(int i=1;i<=9;i++)
	{
		m=1;
		for(int j=1;j<=i;j++)
			m=m*2;
		mvalue=m*16+1;
		tt.Format("%d",mvalue);
		tt=tt+"×"+tt;
		m_subCombolblockSize.AddString (tt);
	}
	m_subCombolblockSize.SetCurSel (0);
	OnSelchangeComboSubblocksize();
}

 
void CDemLoad::OnButtonBrowse() 
{


	CString tt,stt;
	FILE *fp;

	CFileDialog FileDialog(TRUE,"DEM數據文件",NULL,OFN_HIDEREADONLY \
		| OFN_OVERWRITEPROMPT,\
		"DEM數據文件(*.dem)|*.dem|\
		文本格式(*.txt)|*.txt||",NULL);
	
	FileDialog.m_ofn.lpstrTitle="打開DEM數據文件";	


	if(FileDialog.DoModal() == IDOK)
		m_DemFileName = FileDialog.GetPathName();
	else
		return;	
	this->UpdateData(FALSE);
	

	
    if((fp=fopen(m_DemFileName,"r"))==NULL)
		
    {
		MessageBox("地面模型文件不存在!","初始化地面模型",MB_ICONINFORMATION+MB_OK);
		exit(-1);
	}

}

 
void CDemLoad::OnButtonSeperate() 
{
	CString stt;
	
	BeginWaitCursor();
    m_progress.ShowWindow(SW_SHOW);

	DWORD   dw1=GetTickCount();   
	tempDemDirctory="c:\\tempRailwayDem";
	DWORD  dwAttr=GetFileAttributes(tempDemDirctory);   
	if(dwAttr==0xFFFFFFFF)     
        CreateDirectory(tempDemDirctory,NULL);  //創建臨時文件夾
	
	SeperateDem(m_DemFileName,m_subBlockSize);//分塊處理

	DWORD   dw2=GetTickCount();   
	DWORD   dw3=dw2-dw1; 
	stt.Format("%.3f秒!",dw3/1000.0);
	EndWaitCursor(); //將光標切換為默認光標,結束等待
	RemoveDirectory(tempDemDirctory);//刪除臨時文件夾
	
	SetWindowText("數模讀取與分塊處理");	
	m_progress.ShowWindow(SW_HIDE);//隱藏進度條
	m_progress.SetPos(0);
	MessageBox("數模讀取與分塊處理完成，共用時"+stt,"數模讀取與分塊處理",MB_ICONINFORMATION|MB_OK);
	EndDialog(IDOK);//以IDOK模式關閉對話框
	
}

//初始化信息
BOOL CDemLoad::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_progress.SetRange(0,100);//設置進度條控件範圍
	
	Init_BlockSize();//初始化DEM分塊大小
	
	myOci.Init_OCI();//初始化OCI

	return TRUE;  
}


//分塊選項改變時,計算DEM子塊分塊大小
void CDemLoad::OnSelchangeComboSubblocksize() 
{
	int mIndex=	m_subCombolblockSize.GetCurSel();
	CString tt;
	m_subCombolblockSize.GetLBText(mIndex,tt);
	int mPos=tt.Find("×",1);
	tt=tt.Left(mPos);
	m_subBlockSize=atoi(tt);	
}

 
//根據所設置的分塊大小，對DEM文件進行分塊並寫入Oralce數據庫中
void CDemLoad::SeperateDem(CString strfilename, int BlockSize)
{
	long i,j;
	GLint m_DEM_X_neednumber,m_DEM_Y_neednumber;
	CString *strfiles;
	CStdioFile *Sfiles;
	
	float hh;	
	CString tt,stt;
	CString m_TerrainFileName;

	FILE *fp=fopen(strfilename,"r");//打開DEM文件

	fscanf(fp,"%s",tt);theApp.m_DemLeftDown_x=atof(tt);//得到DEM數據的左下角大地x坐標
    fscanf(fp,"%s",tt);theApp.m_DemLeftDown_y=atof(tt);//得到DEM數據的左下角大地y坐標
    fscanf(fp,"%s",tt);theApp.m_Cell_xwidth=atoi(tt);//得到DEM數據在x方向上數據點間距
    fscanf(fp,"%s",tt);theApp.m_Cell_ywidth=atoi(tt);//得到DEM數據在y方向上數據點間距
    fscanf(fp,"%s",tt);theApp.m_Dem_cols=atoi(tt);//得到DEM數據總列數
    fscanf(fp,"%s",tt);theApp.m_Dem_Rows=atoi(tt);//得到DEM數據總行數
    fscanf(fp,"%s\n",tt);theApp.m_DEM_IvalidValue=atoi(tt);//得到DEM數據無效數據值
    
    theApp.m_Dem_BlockSize=m_subBlockSize;//DEM分塊大小
	theApp.m_DemRightUp_x=theApp.m_DemLeftDown_x+theApp.m_Cell_xwidth*(theApp.m_Dem_cols-1);//DEM右上角x坐標
	theApp.m_DemRightUp_y=theApp.m_DemLeftDown_y+theApp.m_Cell_ywidth*(theApp.m_Dem_Rows-1);//DEM右上角y坐標
	theApp.m_Dem_BlockWidth=theApp.m_Cell_xwidth*(theApp.m_Dem_BlockSize-1);//DEM子塊總寬度

	
	SetWindowText("正在進行數模分塊處理....");	

	if(theApp.m_Dem_Rows<=BlockSize)//如果DEM總行數小於所設置的分塊大小,則DEM子塊總行數=1
	{
		theApp.m_BlockRows=1;
		m_DEM_Y_neednumber=BlockSize-theApp.m_Dem_Rows;//在Y方向(行)需要添加無效數據的行數
	}
	else  //如果DEM總行數大於所設置的分塊大小,計算DEM子塊總行數
	{
		if((theApp.m_Dem_Rows-BlockSize) % (BlockSize-1)==0)//如果DEM總行數是分塊大小的整數倍
		{
			theApp.m_BlockRows=(theApp.m_Dem_Rows-BlockSize) /(BlockSize-1)+1;
			m_DEM_Y_neednumber=0;//在Y方向上不需要添加無效數據
		}
		else
		{
			theApp.m_BlockRows=(theApp.m_Dem_Rows-BlockSize) /(BlockSize-1)+2;//分塊總行數
			m_DEM_Y_neednumber=theApp.m_BlockRows*(BlockSize-1)+1-theApp.m_Dem_Rows;//在Y方向(行)需要添加無效數據的行數
		}
	}
		
	if(theApp.m_Dem_cols<=BlockSize)//如果DEM總列數小於所設置的分塊大小,則DEM子塊總列數=1
	{
		theApp.m_BlockCols=1;//則DEM子塊總列數=1
		m_DEM_X_neednumber=BlockSize-theApp.m_Dem_cols;//需要在x方向(列)添加無效數據的列數
	}
	else //如果DEM總列數大於所設置的分塊大小,計算DEM子塊總列數
	{
		if((theApp.m_Dem_cols-BlockSize) % (BlockSize-1)==0)//如果DEM總列數是分塊大小的整數倍
		{
			theApp.m_BlockCols=(theApp.m_Dem_cols-BlockSize) /(BlockSize-1)+1;
			m_DEM_X_neednumber=0;//在X方向上不需要添加無效數據
		}
		else
		{
			theApp.m_BlockCols=(theApp.m_Dem_cols-BlockSize) /(BlockSize-1)+2;//分塊總列數
			m_DEM_X_neednumber=theApp.m_BlockCols*(BlockSize-1)+1-theApp.m_Dem_cols;//在X方向(列)需要添加無效數據的列數
		}
	}
	
	
        //重新定義m_pHeight數組大小
		m_pHeight= new float[BlockSize*BlockSize];

		//根據分塊的總行數和總列數重新定義strfiles和Sfiles大小,用來存儲每個子塊數據的文件名
		strfiles =new CString [theApp.m_BlockRows*theApp.m_BlockCols];		
		Sfiles =new CStdioFile [theApp.m_BlockRows*theApp.m_BlockCols];
		
		//根據分塊的總行數和總列數,建立臨時文件,用來存儲子塊數據
		for ( i=0;i<theApp.m_BlockRows;i++)
		{
			for ( j=0;j<theApp.m_BlockCols;j++)
			{
				//獲得文件名
				tt.Format("%d.txt",j+i*theApp.m_BlockCols+1);
				strfiles[j+i*theApp.m_BlockCols]=tempDemDirctory+"\\block_"+tt;
				//創建文件
				Sfiles[j+i*theApp.m_BlockCols].Open (strfiles[j+i*theApp.m_BlockCols],CFile::modeCreate | CFile::modeWrite);
				Sfiles[j+i*theApp.m_BlockCols].Close();//關閉文件
			}
		}
	

	long mto=theApp.m_Dem_Rows*theApp.m_Dem_cols;
	
	int mColsdatanum=0;
	int mCurrentRow,mCurrentCol;
	int m_oldcurrentRow=-1;

	CString *strSaveUpText;
	strSaveUpText= new CString [theApp.m_BlockCols];

	//
	theApp.m_DemHeight= new float[theApp.m_Dem_Rows*theApp.m_Dem_cols];
	
	//根據分塊的總行數和總列數\和分塊大小,對DEM數據進行了分塊處理,將數據寫入對應的DEM子塊數據文件中
	for (i=1;i<=theApp.m_Dem_Rows;i++)
	{	
		m_progress.SetPos (i*(100.0/theApp.m_Dem_Rows));		
		if(i<=BlockSize)
			mCurrentRow=1;
		else
		{
			if((i-1)%(BlockSize-1)==0)
				mCurrentRow=(i-1)/(BlockSize-1);
            else
				mCurrentRow=(i-1)/(BlockSize-1)+1;
		}

        if(m_oldcurrentRow!=mCurrentRow)
		{
			if(m_oldcurrentRow>0)
			{
				for ( int k=0;k<theApp.m_BlockCols;k++)
				{
					Sfiles[k+(m_oldcurrentRow-1)*theApp.m_BlockCols].Close();
				}
			}

			for (  int k=0;k<theApp.m_BlockCols;k++)
			{
				Sfiles[k+(mCurrentRow-1)*theApp.m_BlockCols].Open (strfiles[k+(mCurrentRow-1)*theApp.m_BlockCols],CFile::modeCreate |CFile::modeWrite);
			}
		}
	
		stt="";	

		mColsdatanum=0;
		for (j=1;j<=theApp.m_Dem_cols;j++)
		{
			if(j<=BlockSize)
				mCurrentCol=1;
			else
			{
				if((j-1)%(BlockSize-1)==0)
					mCurrentCol=(j-1)/(BlockSize-1);
				else
					mCurrentCol=(j-1)/(BlockSize-1)+1;
			}

			fscanf(fp,"%f ",&hh);  //讀取高程
			tt.Format("%.3f	",hh);//高程精度取小數點後3位
			theApp.m_DemHeight[(i-1)*theApp.m_Dem_cols+(j-1)]=hh;
			stt=stt+tt;
			mColsdatanum++;
			if(mColsdatanum % BlockSize==0 || j==theApp.m_Dem_cols )
				{
				if(j==theApp.m_Dem_cols)
				{
				
					//對於不足分塊大小的子塊數據,以無效數據補充
					int pos=BlockSize-mColsdatanum;
					for(int k=1;k<=pos;k++)
					{
					
						tt.Format("%d",theApp.m_DEM_IvalidValue);
						stt=stt+tt;
					}
				}
				stt=stt+"\n";
			    if(mCurrentRow>1 && m_oldcurrentRow!=mCurrentRow)
				{
					
					Sfiles[(mCurrentRow-1)*theApp.m_BlockCols+mCurrentCol-1].WriteString(strSaveUpText[mCurrentCol-1]);

				}
				Sfiles[(mCurrentRow-1)*theApp.m_BlockCols+mCurrentCol-1].WriteString (stt);
		
                if((i-1)% (BlockSize-1)==0 && (i>1 && i<theApp.m_Dem_Rows)) 
				{
					int ms=(i-1)/(BlockSize-1)*theApp.m_BlockCols+mCurrentCol-1;
					Sfiles[ms].Open(strfiles[ms],CFile::modeCreate |CFile::modeWrite);
				
					Sfiles[ms].WriteString (stt);//將數據寫入文件
					Sfiles[ms].Close();
					strSaveUpText[mCurrentCol-1]=stt;
				}
			
				if(mColsdatanum % BlockSize==0) 
				{
					stt=tt;
					mColsdatanum=1;
				}
				else
				{
					stt="";
					if(j<theApp.m_Dem_cols) mColsdatanum=0;
				}
				if(i>=theApp.m_Dem_Rows && j>=theApp.m_Dem_cols)
				{
				
					int pos=m_DEM_Y_neednumber;
					for(int p=1;p<=theApp.m_BlockCols;p++)
					{
						for(int k=1;k<=pos;k++)
						{
							stt="";
							//對於不足分塊大小的子塊數據,以無效數據補充
							for(int m=1;m<=BlockSize+1;m++)
							{
							
								tt.Format("	%d",theApp.m_DEM_IvalidValue);
								stt=stt+tt;
							}
							stt=stt+"\n";
							Sfiles[theApp.m_BlockCols*theApp.m_BlockRows-(theApp.m_BlockCols-p+1)].WriteString (stt);
						}
					}
					
				}
							
			}
			
		}
		fscanf(fp,"\n");  
		m_oldcurrentRow=mCurrentRow;
	
	}

	//關閉所打開的臨時文件
	for ( int k=0;k<theApp.m_BlockCols;k++)
	{
		Sfiles[k+(theApp.m_BlockRows-1)*theApp.m_BlockCols].Close();
	}

	//寫入數據庫之前,先刪除dem_block(DEM數據表中的原來所有數據)
	//是為了防止對同一數據文件多次寫入數據庫中的重複寫入錯誤
	CString strSql;
	strSql="DELETE FROM dem_block";
	HRESULT hr=theApp.m_pConnection->Execute (_bstr_t(strSql),NULL,adCmdText);
	if(!SUCCEEDED(hr))
	{
		MessageBox("刪除失敗!","寫入DEM數據到數據庫",MB_ICONSTOP);
		return;
	}
	//依次將分塊捕撈DEM子塊數據文件寫入oracle數據庫中
    SetWindowText("將數模分塊數據寫入數據庫...");	
	for ( i=0;i<theApp.m_BlockRows;i++)
	{
			for ( j=0;j<theApp.m_BlockCols;j++)
			{
				m_progress.SetPos ((i*theApp.m_BlockCols+j+1)*(100.0/(theApp.m_BlockRows*theApp.m_BlockCols)));
				AddDemBlockDataToDB(i+1,j+1,strfiles[i*theApp.m_BlockCols+j],i*theApp.m_BlockCols+j+1);
			}
	}
	
	fclose(fp);  //關閉文件
	
	WriteTotalDemToBlob(strfilename);//將DEM數據寫入oralce數據庫中

}



//得到分塊大小
int CDemLoad::GetBlcokSize(int currentSel)
{
	int m=1;
	for(int i=0;i<currentSel;i++)
		m=m*2;
	return m*32+1;
}

//從DEM分塊文件中讀取數據 
void CDemLoad::ReadDemDataFromFiles(CString strfiles, int Index)
{
	float hh; 
	int i,j;
    int mCount=theApp.m_Dem_BlockSize;
    FILE *fp=fopen(strfiles,"r");//打開文件
	
	for( i=0;i<mCount;i++) //等比例DEM子塊的行、列數年是相同的(如33×33,65×65等等)
	{
		for( j=0;j<mCount;j++)
		{
			fscanf(fp,"%f ",&hh);  
			
			m_pHeight[i*mCount+j]=hh;
			
		}
	}
	fclose(fp);//關閉文件
	DeleteFile(strfiles);//刪除臨時分塊文件
}

 
//根據行、列索引值計算對應DEM數據點的高程
float CDemLoad::HH(int mRows, int mCols)
{
	return m_pHeight[mRows*theApp.m_Dem_BlockSize+mCols];
}


//將DEM數據寫入oralce數據庫中
void CDemLoad::WriteTotalDemToBlob(CString strfile)
{
	CString tt;

	
	tt.Format("INSERT INTO DEM_INFO VALUES(%.3f,%.3f,%d,%d,%d,%d,%d,%d,%d,EMPTY_BLOB(),%d,%d)",\
		theApp.m_DemLeftDown_x,theApp.m_DemLeftDown_y,theApp.m_Cell_xwidth,\
		theApp.m_Cell_ywidth,theApp.m_Dem_BlockSize,theApp.m_BlockRows,\
		theApp.m_BlockCols,theApp.m_Dem_Rows,theApp.m_Dem_cols,1,theApp.m_DEM_IvalidValue);

	myOci.AddNormalDataToDB(tt);//將常規數據類型寫入oralce數據庫中
	
	tt.Format("SELECT DEM數據 FROM DEM_INFO WHERE 編號= :%d FOR UPDATE",1)  ;
	myOci.AddBOLBDataToDB(strfile,tt,1);//將DEM分塊文件作為BLOB類型數據類型寫入oralce數據庫中

	
}





















