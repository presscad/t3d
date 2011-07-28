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

	CString strtable[200];//���ؤ��̦h�i�Ыت��ƶq

	CString strsql;//�Ω�s�xSQL�r�Ŧ�
	CString m_username,m_userpassword;	//�s�x�s�Ыت��Τ�W�M�K�X

	this->UpdateData();//��s�ƾ�

	if(m_projectname.IsEmpty()) //���ئW�٤��ର��
	{
		MessageBox("���ئW�٤��ର��!","�s�ض���",MB_ICONINFORMATION);
		return FALSE; //��^
	}
	
	m_username=m_projectname;//�s�Ыت�Oracle�Τ�W

	//�s�Ыت�Oracle�Τ�K�X,�i���N�]�w,�o�̪������@�w�q�{��,�O�F����K,
	//���}���خ�,�N���ݭn��J���ت��K�X�N�i�H�������}����)
	m_userpassword="a"; //�s�Ыت�Oracle�Τ�K�X

	theApp.m_username=m_username;//Oracle�ƾڮw�t�κ޲z���Τ�W
	theApp.m_userpassword=m_userpassword;//Oracle�ƾڮw�t�κ޲z���K�X
	theApp.m_servername=m_servername;//Oracle�ƾڮw�t�κ޲z���A�Ⱦ��W
	
	if(FAILED(CoInitialize (NULL)))   //��l��ADO
	{
		MessageBox ("ADO��l�ƥ���!","�n���ƾڮw",MB_ICONERROR);
		return FALSE;
	}
		
	//�Ы�m_pConnection��ҥy�`
	HRESULT hr = theApp.m_pConnection.CreateInstance("ADODB.Connection");	
	
	if(theApp.m_pConnection->State) //�p�G�ƾڮw�w���}
		theApp.m_pConnection->Close(); //�����s��
	
	//�Ы�SQL�r�Ŧ�
	strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_systemname+";Password="+m_systempassword+";";
	try
	{
		hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//���}Oracle�t�κ޲z���Τ�
		if(!SUCCEEDED(hr)) //���}����
		{
			MessageBox("�t�κ޲z���ƾڮw�s������!","�n���ƾڮw",MB_ICONINFORMATION);
			return FALSE;	//��^
		}
	}
	catch(_com_error& e)	//���~�B�z
	{
		CString errormessage;
		errormessage.Format("���~�H��:%s",e.ErrorMessage());
		errormessage="�t�κ޲z���Τ�W�B�K�X�ΪA�Ⱦ��W���~!";
		MessageBox(errormessage,"�n���ƾڮw",MB_ICONINFORMATION);//���X���~�E�_�H��
		return FALSE;	//��^
	} 
 
    //�Ыؤ@�ӷs�Τ�A �Ω�s�x�ҫت����ئW��
	CString tname,tpass;
	tname="RW3D";	//�]�w���Τ�W��(�i���N�Τ�W)
	tpass="aaa";	//�]�w���Τ�K�X(�i���N�K�X)
	strsql.Format("SELECT * FROM dba_users WHERE  username='%s'",tname);
	theApp.m_pRecordset.CreateInstance(_uuidof(Recordset));

	//�qOracle��dba_users������O�_���ҳ]�w���Τ�
	theApp.m_pRecordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	if(theApp.m_pRecordset->adoEOF) //�p�G�S���ӥΤ�,�h�Ы�
	{
		theApp.m_pRecordset->Close();//������
		strsql = "CREATE USER  " + tname + "  IDENTIFIED BY   " + tpass;
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//�Ыس]�w���Τ�
		
		strsql = "GRANT CREATE SESSION,CREATE TABLE ,UNLIMITED TABLESPACE ,DBA to " + tname;
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//���t�Ыت��v��
		theApp.m_pConnection->Close();//�����ƾڮw�s��
		
		strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+tname+";Password="+tpass+";";
		hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//�s���s�Ыت��Τ�
		strsql= "CREATE TABLE Project(���ئW�� VARCHAR2(50),�إ߮ɶ� VARCHAR2(20))";
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//�b�s�Ыت��Τ�U�Ыت�Project
		theApp.m_pConnection->Close();//�����ƾڮw�s��
	
		//���s�s��Oracle�t�κ޲z���Τ�
		strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_systemname+";Password="+m_systempassword+";";
		hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);
	}
	else //�p�G�s�x���ئW�٪��Τ�w�g�s�b,�N���A�ݭn�ЫؤF(�Y�u�O�Ĥ@���s�ض��خ�,�|�Ыئs�x���ئW�٪��Τ�M�ƾڪ�)
		theApp.m_pRecordset->Close(); //�����O����

	
   //�Ыض���(�ھڶ��ئW�ٳЫ�Oracle�s�Τ�)
	strsql = "CREATE USER  " + m_username + "  IDENTIFIED BY   " + m_userpassword;
	try
	{
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//�Ы�Oracle�s�Τ�
		if(!SUCCEEDED(hr)) //�p�G�Ыإ���
		{
			MessageBox("���سЫإ���!","�Ыطs����",MB_ICONINFORMATION);
			return FALSE;	//��^
		}

		//���Ыض��ت��s�Τ���t�Ыإ���(CREATE SESSION,),�Ыت�(CREATE TABLE),
		//�L���s��Ŷ�(UNLIMITED TABLESPACE)���v��
		strsql = "GRANT CREATE SESSION,CREATE TABLE ,UNLIMITED TABLESPACE to " + m_username;
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);
		if(!SUCCEEDED(hr))//�p�G�v����ȥ���
		{
			MessageBox("�v����ȥ���!","�Ыطs����",MB_ICONINFORMATION);
			return FALSE;//��^
		}
		theApp.m_pConnection->Close();//�����O����
	} 		

	catch(_com_error& e)	//���~�B�z
	{
		CString errormessage;
		
		if(e.WCode()==3092) //�p�G���ؤw�g�s�b
		{
			errormessage="���� "+m_username+" �w�g�s�b,�O�_�R��?";	
			int nanswer=MessageBox(errormessage,"�Ыطs����",MB_ICONINFORMATION|MB_YESNO);
			if(nanswer==6)	//�R���w������
			{
				strsql="Drop user "+m_username+"  cascade";
				hr =theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//�R���w������
				if(!SUCCEEDED(hr))	//�p�G�R�����إ���
					MessageBox("�R�����إ���","�R������",MB_ICONINFORMATION);
				else
					MessageBox("�R�����ا���","�R������",MB_ICONINFORMATION);
				
			}
		}
		
		else	//�䥦���~�H��
		{
			errormessage.Format("���~�H��:%s",e.ErrorMessage());
			MessageBox(errormessage,"�Ыطs����",MB_ICONINFORMATION);
		}
		return FALSE;	//��^
	} 

	//�s���ھڶ��ئW�ٳЫت��s�Τ�
	strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_username+";Password="+m_userpassword+";";
	try
	{
		hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//�s���ھڶ��ئW�ٳЫت��s�Τ�
		if(!SUCCEEDED(hr))//�p�G�s���s�Τᥢ��
		{
			MessageBox("�ƾڮw�s������!","�Ыطs����",MB_ICONINFORMATION);
			return FALSE;	//��^
		}
	    	
	}
	catch(_com_error& e)	//���~�B�z
	{
		CString errormessage;
		WORD nWcode=e.WCode(); 
		if(e.WCode()==0) //���ؤ�W���~
		{	errormessage="���ؤ�W���~!";
			MessageBox(errormessage,"�Ыطs����",MB_ICONINFORMATION);
			return FALSE;	//��^
		}
		else	//�䥦���~�H��
		{	
			errormessage.Format("���~�H��:%s",e.ErrorMessage());
			MessageBox(errormessage,"�Ыطs����",MB_ICONINFORMATION);
			return FALSE; 	//��^
		}
	} 

	//�U���N�X���b�ھڶ��ئW�ٳЫت��s�Τ�U�Ыؼƾڪ�pDEM�ƾڪ�,�v���ƾڪ�
	int index=-1;

	//1.DEM�a�ΫH����
	index++;
	strtable[index]= "CREATE TABLE DEM_INFO(DEM�_�I����X NUMBER(10,3),\
		DEM�_�I����Y NUMBER(10,3),������ZX NUMBER(3),\
		������ZY NUMBER(3),DEM�����j�p NUMBER(3),\
		DEM������� NUMBER(6),DEM�����C�� NUMBER(6),\
		��lDEM��� NUMBER(10),��lDEM�C�� NUMBER(10),\
		DEM�ƾ� BLOB,�s�� NUMBER(2),�L��DEM�� NUMBER(10))";	
	

	//2.DEM�a�Τl���ƾڪ�
	index++;
	strtable[index]= "CREATE TABLE dem_block(�渹 NUMBER(6),\
			�C�� NUMBER(6),DEM�ƾ� BLOB,�s�� NUMBER(6),\
			���ߧ���X NUMBER(10,3),���ߧ���Y NUMBER(10,3))";	

	//3.DEM�a�Τl���H����
	index++;
	strtable[index]= "CREATE TABLE dem_subblock(�渹 NUMBER(6),\
		�C�� NUMBER(6),DEM�ƾ� BLOB,���ݶ��� NUMBER(6),�s�� NUMBER(6))";	
			
	//4.�v�����z��
	index++;
	strtable[index]= "CREATE TABLE texture(�渹 NUMBER(6),\
		  �C�� NUMBER(6),���� NUMBER(6),�e�� NUMBER(6),\
		  ���z���l��h�� NUMBER(6),���z�ƾ� BLOB,�s�� NUMBER(6),\
		  ���U������X NUMBER(10,3),���U������Y NUMBER(10,3),\
		  �k�W������X NUMBER(10,3),�k�W������Y NUMBER(10,3))";	
				
	//5.�v��LOD�H����
	index++;
	strtable[index]= "CREATE TABLE IMAGERECT_INFO(���U������X NUMBER(10,3),\
		 ���U������Y NUMBER(10,3),�k�W������X NUMBER(10,3),\
		 �k�W������Y NUMBER(10,3),�v�����r���`�� NUMBER(2),\
		 �@�żv������v NUMBER(6,2),�G�żv������v NUMBER(6,2),\
		 �T�żv������v NUMBER(6,2),\
		 �|�żv������v NUMBER(6,2),���żv������v NUMBER(6,2))";

	index++;
	
	//6.���ؤ�׼ƾڪ�
	strtable[index]= "CREATE TABLE Scheme (\
		 ��צW�� VARCHAR2(100), �]�p���� VARCHAR2(20),\
		 �o�޺��� VARCHAR2(10),�������� VARCHAR2(50),����覡 VARCHAR2(50),\
		 �a�Φa�O VARCHAR2(12), �u�{���� VARCHAR2(20),�]�p�t�� NUMBER(6),\
		 �̤p���u�b�| NUMBER(6),��o�u���Ī��� NUMBER(6),\
		 �̤p�Y�� NUMBER(6,2),�̤j�Y�� NUMBER(6,2),�̤j�Y�׮t NUMBER(6,2),\
		 �_�I���{ NUMBER(20,3),���I���{ NUMBER(20,3))";
	
	index++;
	strtable[index]= "CREATE TABLE T3DLineZxCorrdinate (\
		  ��צW�� VARCHAR2(100),�Ǹ� NUMBER(10), x���� NUMBER(20,3),\
		  y���� NUMBER(20,3),z���� NUMBER(20,3),�������� VARCHAR2(30),\
		  �a�����{ NUMBER(20,3),����� NUMBER(20,3),���{ NUMBER(20,3))";
	

	index++;
	strtable[index]= "CREATE TABLE Scheme_plane_CureveData (\
		  ��צW�� VARCHAR2(100),���I�s�� VARCHAR2(50),\
		  �ਤ NUMBER(10,3),��쨤1 NUMBER(10,3),��쨤2 NUMBER(10,3),\
		  ��V NUMBER(2),�w�M���u��  NUMBER(6),\
		  ���u�� NUMBER(15,3),���u�� NUMBER(15,3),\
		  �ꦱ�u�� NUMBER(15,3),���w�I���{ NUMBER(20,3),\
		  �w���I���{ NUMBER(20,3),��w�I���{ NUMBER(20,3),\
		  �w���I���{ NUMBER(20,3),�~�ڶZ NUMBER(10,3),\
		  �����Z NUMBER(10,3),���u�b�| NUMBER(10),\
		  ���I���{ NUMBER(20,3),���Ix���� NUMBER(20,3),\
		  ���Iy���� NUMBER(20,3),���Iz���� NUMBER(20,3),\
		  ���I�Ǹ� NUMBER(10))";
	
	index++;
	strtable[index]= "CREATE TABLE Scheme_plane_CureveData_XY (\
		 ��צW�� VARCHAR2(100),���I�s�� VARCHAR2(50),\
		 ���x���� NUMBER(20,3),���y���� NUMBER(20,3),\
		 ���wx���� NUMBER(20,3),���wy���� NUMBER(20,3),\
		 �w��x���� NUMBER(20,3),�w��y���� NUMBER(20,3),\
		 ��wx���� NUMBER(20,3),��wy���� NUMBER(20,3),\
		 �w��x���� NUMBER(20,3),�w��y���� NUMBER(20,3),\
		 ���I�Ǹ� NUMBER(10))";
	

	index++;
	strtable[index]= "CREATE TABLE PriorityRadius (\
		�樮�t�� NUMBER(4), ���u�b�|�̤p�� NUMBER(6),\
		���u�b�|�̤j�� NUMBER(6))";
	
	index++;
	strtable[index]= "CREATE TABLE MinRadius (\
		�樮�t�� NUMBER(4), �@��a�q NUMBER(6),\
		�x���a�q NUMBER(6))";
	
	index++;
	strtable[index]= "CREATE TABLE T3DLineZxCorrdinateZDM (\
		 ��צW�� VARCHAR2(100),�Ǹ� NUMBER(10), x���� NUMBER(20,3),\
		 y���� NUMBER(20,3),z���� NUMBER(20,3),�������� VARCHAR2(30),\
		 �a�����{ NUMBER(20,3),����� NUMBER(20,3),���{\
		 NUMBER(20,3),���I���{ NUMBER(20,3))";
	
	
	index++;
	strtable[index]= "CREATE TABLE ZDmJDCurve (\
		 ��צW�� VARCHAR2(100), �Y�� NUMBER(20,3),\
		 �Y�v NUMBER(20,3),�ܩY�I�θ� NUMBER(20,3),�а� VARCHAR2(30),\
		 �ݦ��u�b�| NUMBER(20,3),�~�ڶZ NUMBER(20,3),���u�� NUMBER(20,3),\
		 �Y�ץN�Ʈt NUMBER(20,3),�Ǹ� NUMBER(10),��V���� NUMBER(2),\
		 ���w�I���{ NUMBER(20,3),���w�I�а� NUMBER(20,3),\
		 �w���I���{ NUMBER(20,3),�w���I�а� NUMBER(20,3))";
	index++;
	strtable[index]= "CREATE TABLE zdmSegmentGeoFeature (\
		   ���q�_�l���{ NUMBER(10,3),���q���I���{ NUMBER(10,3),\
		   �u�{�a��S�x VARCHAR2(2000),��צW�� VARCHAR2(100))";
	
	index++;
	strtable[index]= "CREATE TABLE Tunnel (\
			 �G�D�W�� VARCHAR2(400),�G�D�_�I���{ NUMBER(20,3),\
			 �G�D���I���{ NUMBER(20,3), �G�D���� NUMBER(20,3),��צW�� VARCHAR2(200))";

	index++;
	strtable[index]= "CREATE TABLE Bridge (\
		 ���٦W�� VARCHAR2(400),���ٰ_�I���{ NUMBER(20,3),\
		 ���ٲ��I���{ NUMBER(20,3), ���٪��� NUMBER(20,3),\
		 ��צW�� VARCHAR2(200))";

	index++;
	strtable[index]= "CREATE TABLE StationTable (\
		�����W�� VARCHAR2(200),�������� VARCHAR2(50),\
		���{ NUMBER(20,3), ��צW�� VARCHAR2(200))";

	/*
		�٥i�H�~��Ыةһݭn���ƾڪ�
	*/

	//�ЫةҦ��ƾڪ�
	for(int i=0;i<=index;i++)
	{

		HRESULT hr=theApp.m_pConnection->Execute (_bstr_t(strtable[i]),NULL,adCmdText);//�Ыت�
		if(!SUCCEEDED(hr)) //�p�G��Ыإ���,�h�R���ھڶ��ئW�ٷs�Ыت��Τ�
		{
			MessageBox("��Ыإ���!","�n���ƾڮw",MB_ICONINFORMATION);
			strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_systemname+";Password="+m_systempassword+";";
			hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//���s�s��Oracle�t�κ޲z���Τ�
			strsql = "DROP USER  " + m_username + "  CASCADE   " ;
			hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//�R���s�Ыت��Τ�			
			return FALSE;

		}
	}
	theApp.m_pConnection->Close();//�����ƾڮw�s��

	
	
	//���}�Ω�s�x�ҫت����ئW�٪��Τ�
	strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+tname+";Password="+tpass+";";
	hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);
	if(!SUCCEEDED(hr))//���}����
	{
		MessageBox("�ƾڮw���}���~!");
	}
	//�U���o�춵�سЫت�����M�ɶ��H��
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
	hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//�N���سЫت�����M�ɶ��H���g�JProject��
	theApp.m_pConnection->Close();//�����ƾڮw�s��
	
	//���s�s���ھڶ��ئW�ٳЫت��s�Τ�
	strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_username+";Password="+m_userpassword+";";
	hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);	//�s���ƾڮw
	theApp.bLoginSucceed=TRUE; //�ƾڮw�n�����\
	MessageBox("���سЫئ��\!","�Ыطs����",MB_ICONINFORMATION);
	
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

//�T�w
void CNewProject::OnOK() 
{
	BeginWaitCursor();//�N���Ф��������ݥ���
	if(CreateNewProject()==TRUE) //�Ыطs����
	{
		EndWaitCursor();//�N���Ф������q�{����,��������
		CDialog::OnOK();//����
	}
	else
	{
		EndWaitCursor();//�N���Ф������q�{����,��������
	}
	
}
