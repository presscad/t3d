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


//�s���~�����z���
void CTextureLoad::OnButtonBrowse() 
{
	CString  strFile,strFilter="Tif files(*.Tif)|*.Tif|\
							 BMP files(*.BMP)|*.BMP|\
							 Jpeg files(*.JPG)|*.JPG|\
							 GIF files(*.GIF)|*.GIF|\
							 PCX files(*.PCX)|*.PCX|\
							 Targa files(*.TGA)|*.TGA||";

	//�w��}����ܮءA�Ϥ���h�����(OFN_ALLOWMULTISELECT)
	CFileDialog   fdlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT,strFilter);     

	char  *pBuf= new  char[BUFFERLEN];//�ӽнw�İ�
	
	fdlg.m_ofn.lpstrFile=pBuf;    //��pBuf�N��CFileDialog�w�İ�	
	fdlg.m_ofn.lpstrFile[0]='\0';     
	fdlg.m_ofn.nMaxFile=BUFFERLEN; 


	int nCount=0;//��l��ܪ����Ƭ�0
	
	//�p�G���\�A�����ܮئh����ܪ����A�è̦��K�[��C��ظ�
	if(fdlg.DoModal()==IDOK)     
	{     
        //GetStartPosition():��^���ܹM���M�g�_�l��m��POSITION��m�A�p�G�M�g���šA�h��^NULL
		POSITION  pos=fdlg.GetStartPosition();  
		m_listfiles.ResetContent();//�M�ŦC���
	
		while(pos)   //�p�G�M�g������
		{   
			nCount++; 
			strFile=fdlg.GetNextPathName(pos);  //�o����W
			m_listfiles.AddString(strFile);//�N���W�[�J��C���
		}     
	}  
	
	delete[]  pBuf;   //�^���w�İ�
}

//��l�ƹ�ܮ�
BOOL CTextureLoad::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	myOci.Init_OCI();	//��l��OCI
	return TRUE;  
}

//��U�ů��z�v���v�Ӥ����B�z,�üg�Joracle�ƾڮw��
void CTextureLoad::OnOK() 
{

	CString mfilename,stt,tt;

	BeginWaitCursor();

	CString tempDirctory="c:\\tempRailwayBmp";//�s�񯾲z�v���l�����{�ɤ��
	DWORD  dwAttr=GetFileAttributes(tempDirctory);   //�������ݩ�
	if(dwAttr==0xFFFFFFFF)  //�p�G�Ӥ�󧨤��s�b�N�Ыؤ@��   
        CreateDirectory(tempDirctory,NULL);  //�Ы��{�ɤ��

	m_listfiles.SetCurSel(0);
	m_listfiles.GetText(m_listfiles.GetCurSel(),mfilename);
	if(GetTextureRange(mfilename)==FALSE)
		return;
	
	//��U�ů��z�v���v�Ӥ����B�z,�üg�Joracle�ƾڮw��
	for(int i=0;i<m_listfiles.GetCount();i++)
	{
		m_listfiles.SetCurSel(i); //�]�m�C��ط�e����
		m_listfiles.GetText(m_listfiles.GetCurSel(),mfilename);//�o���e�]�t�����|���v�����W
		int nPos=mfilename.ReverseFind('\\');
		tt=mfilename.Mid(nPos+1,mfilename.GetLength()-nPos);//�o��v�����W
		
		stt.Format("���b�B�z�G%s",tt);
		this->SetWindowText(stt);	//�]�m��ܮؼ��D
		SeperateImage(mfilename,i,tempDirctory);//��v�����z�i������B�z,�üg�Joracle�ƾڮw��	
	}	

	//�N�v�����z�`��H���g�J�v���H����
	tt.Format("INSERT INTO IMAGERECT_INFO VALUES(%.3f,%.3f,%.3f,%.3f,%d,\
		%.2f,%.2f,%.2f,%.2f,%.2f)",theApp.m_TexturLeftDown_x,theApp.m_TexturLeftDown_y,\
		theApp.m_TexturRightUp_x,theApp.m_TexturRightUp_y,m_listfiles.GetCount(),\
		theApp.m_ImageResolution[1],theApp.m_ImageResolution[2],theApp.m_ImageResolution[3],\
		theApp.m_ImageResolution[4],theApp.m_ImageResolution[5]);
	theApp.m_pConnection->Execute (_bstr_t(tt),NULL,adCmdText);//����SQL�y�y
	
	EndWaitCursor(); //�N���Ф������q�{����,��������
	m_progress.ShowWindow(SW_HIDE);//���öi�ױ�
	m_progress.SetPos(0);//��_��l��m0��
	MessageBox("�v�����z���g�J����!","�v�����z�J�w",MB_OK);
	RemoveDirectory(tempDirctory); //�R���{�ɤ��
	theApp.bLoadImage=TRUE;//�[���v�����\
		
	CDialog::OnOK();
}

//�N���z�v���i������B�z,�üg�Joracle�ƾڮw��
void CTextureLoad::SeperateImage(CString mfilename, int m_phramidLayer,CString tempDirctory)
{
	
		CString stt,strfile;
        m_pImageObject=new CImageObject;
		
		m_pImageObject->Load(mfilename,NULL,-1,-1);//�[���v�����z
		long m_height=m_pImageObject->GetHeight();//�o�쯾�z����
		long m_width=m_pImageObject->GetWidth();//�o�쯾�z�e��

		//��eLOD�ŧO�����z����v
		theApp.m_ImageResolution[m_phramidLayer]=(theApp.m_TexturRightUp_x-theApp.m_TexturLeftDown_x)/m_width;
	

		//���z�v���l�����e��
		int m_fg_width=theApp.m_Dem_BlockWidth/theApp.m_ImageResolution[m_phramidLayer]; 
		//���z�v���l��������
		int m_fg_height=theApp.m_Dem_BlockWidth/theApp.m_ImageResolution[m_phramidLayer];

		//�p���eLOD�Ū����z�v���������`���
		if(m_height%m_fg_height==0)
			m_totalRows=m_height/m_fg_height;
		else
		{
			m_totalRows=m_height/m_fg_height+1;
			
		}
		
		//�p���eLOD�Ū����z�v���������`�C��
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
			
			//�]�m�i�ױ���
			m_progress.SetPos((i*m_totalCols+j+1)*100.0/(m_totalRows*m_totalCols));
			int mleftx=(j-0)*m_fg_width;	    //�v���l�����U��x����
			int mlefty=(m_totalRows-i-1)*m_fg_height;	//�v���l�����U��y����
			int mrightx=mleftx+m_fg_width-1;	//�v���l���k�W��x����
			int mrigty=mlefty+m_fg_height-1;	//�v���l���k�W��y����
			m_pImageObject->Crop( mleftx, mlefty, mrightx, mrigty);	//Ū����mleftx�Bmlefty�Bmrightx�Mmrigty�ҽT�w���v���l��
			stt.Format("%s\\%s@%d_%d.bmp",tempDirctory,strfile,i,j);
			m_pImageObject->Save( stt, 1);//�NŪ�����v���l���s�x���{�ɤ��
			int m_subImageWidth=m_pImageObject->GetWidth();//�o��v���l�����e��
			int m_subImageHeight=m_pImageObject->GetHeight();//�o��v���l��������
		    //�N�v���l���HBLOB�ƾ������g�Joracle�ƾڮw��
			WriteImageToDB(stt,i+1,j+1,m_subImageHeight,m_subImageWidth,m_phramidLayer,m_fg_width,m_fg_height);
			DeleteFile(stt);
			m_pImageObject->Load(mfilename,NULL,-1,-1);//���s�[����l�v��
			}
		}
}

//�N�v���l���HBLOB�ƾ������g�Joracle�ƾڮw��
BOOL CTextureLoad::WriteImageToDB(CString strFile, int m_RowIndex, int m_ColIndex, int m_height, int m_width, int m_phramidLayer,int m_fg_width,int m_fg_height)
{
	
	CString tt;
	
	double m_leftdownx,m_leftdowny,m_rightUpx,m_rightUpy;

	//�p��N�v���l�������U�M���W��x,y�j�a����
	m_leftdownx=(m_ColIndex-1)*m_fg_width*theApp.m_ImageResolution[m_phramidLayer]+theApp.m_TexturLeftDown_x;
	m_leftdowny=(m_RowIndex-1)*m_fg_height*theApp.m_ImageResolution[m_phramidLayer]+theApp.m_TexturLeftDown_y;
	m_rightUpx=m_leftdownx+m_width*theApp.m_ImageResolution[m_phramidLayer];
	m_rightUpy=m_leftdowny+m_height*theApp.m_ImageResolution[m_phramidLayer];

	int m_ID=(m_RowIndex-1)*m_totalCols+m_ColIndex;//�v���l����ID��

	tt.Format("INSERT INTO texture VALUES(%d,%d,%d,%d,%d,EMPTY_BLOB(),\
		%ld,%.3f,%.3f,%.3f,%.3f)",\
		m_RowIndex,m_ColIndex,m_height,m_width,m_phramidLayer,m_ID,\
		m_leftdownx,m_leftdowny,m_rightUpx,m_rightUpy);
	
	//�ե�OCI���@����AddNormalDataToDB��ơA�N�`�W�ƾ��������ƾڼg�Joracle�ƾڮw��
	myOci.AddNormalDataToDB(tt);

	//�ե�OCI���@����AddBOLBDataToDB��ơA�NBLOB�������ƾڼg�Joracle�ƾڮw��
	tt.Format("SELECT ���z�ƾ� FROM texture WHERE �渹=%d AND �C��=%d AND ���z���l��h��=%d AND �s��= :%d FOR UPDATE",m_RowIndex,m_ColIndex,m_phramidLayer,m_ID)  ;
	myOci.AddBOLBDataToDB(strFile,tt,m_ID);
	
	return TRUE;
}

//�P����ܮ�
void CTextureLoad::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_pImageObject=NULL;
	delete m_pImageObject;
	
}

 
//�N�̫�@�ů��z�v�����i����������g�J�ƾڮw��,�N��@���ɯ�ϯ��z
BOOL CTextureLoad::WriteLittleLodImageToDB(CString strFile)
{
	
	CString tt;
	int m_ID=1;
	
	tt.Format("INSERT INTO texture_LitLOD VALUES(EMPTY_BLOB(),%d)",m_ID);
	//�ե�OCI���@����AddNormalDataToDB��ơA�N�`�W�ƾ��������ƾڼg�Joracle�ƾڮw��
	myOci.AddNormalDataToDB(tt);
	
	tt.Format("SELECT ���z�ƾ� FROM texture_LitLOD WHERE  �s��= :%d FOR UPDATE",m_ID)  ;
	//�ե�OCI���@����AddBOLBDataToDB��ơA�NBLOB�������ƾڼg�Joracle�ƾڮw��
	myOci.AddBOLBDataToDB(strFile,tt,m_ID);
	return TRUE;
}


//�o��v�����z�����U�M�k�W�� x,y����
BOOL CTextureLoad::GetTextureRange(CString tcrPathname)
{
	/*
	
	�v�����z���Ф��O�H���ئW�٦P�W���A�X�i�W��".tod"����󤤦s�x���A��榡���G
	lb: 781395.000	1869975.000
	rt: 797995.000	1876275.000
	�䤤	�Ĥ@�檺lb:��ܼv�����z�����U��x,y����
			�ĤG�檺rt:��ܼv�����z���k�W��x,y����
	*/
	CString tt,strpath;
	int	pos=tcrPathname.ReverseFind('\\');
	strpath=tcrPathname.Left(pos);
	pos=strpath.ReverseFind('\\');
	tt=strpath.Right(strpath.GetLength()-pos-1);
    FILE *fp;
	tt=strpath+"\\"+tt+".tod";//�o��v���d����W
	
	if((fp=fopen(tt,"r"))==NULL)//�p�G��󥴶}����
    {
		MessageBox("�v���d����"+tt+"���s�b!","Ū���v���d����",MB_ICONINFORMATION+MB_OK);
		fclose(fp);	//�������
		return FALSE;//��^FALSE
	}
	else
	{
		fscanf(fp,"%s",tt);//�o��lb:�r�Ŧ�
		fscanf(fp,"%s",tt);theApp.m_TexturLeftDown_x=atof(tt);//���z�����U��x����
		fscanf(fp,"%s\n",tt);theApp.m_TexturLeftDown_y=atof(tt);//���z����x,y����
		fscanf(fp,"%s",tt);//�o��rt:�r�Ŧ�
		fscanf(fp,"%s",tt);theApp.m_TexturRightUp_x=atof(tt);//���z���k�W��x����
		fscanf(fp,"%s\n",tt);theApp.m_TexturRightUp_y=atof(tt);//���z���k�W��y����
		fclose(fp);//�������
		return TRUE;//��^TRUE
		
	}
	
}
