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
	
	InitListCtrl();//��l�� ListCtrl����
	
	LoadData();//�q�ƾڮw���[�����ؼƾ�
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//�q�ƾڮw���[�����ؼƾ�
void COpenProject::LoadData()
{
	CString strsql;

	//�q�s�x���ئW�١B�Ыؤ����Oralce�Τ�RW3D��Ū���Ҧ����ثH��
	strsql="Provider=OraOLEDB.Oracle;User Id=RW3D;Password=aaa;";	//�w�qSQL�r�Ŧ�	
	try
	{
		HRESULT hr =m_Connection->Open(_bstr_t(strsql),"","",-1);//���}�ƾڮw
		if(!SUCCEEDED(hr)) //�p�G���}����
		{
			MessageBox("�ƾڮw�s������!","���}����",MB_ICONINFORMATION);
			return ;//��^
		}
	}
	catch(_com_error& e)	//���~�B�z
	{
		CString errormessage;
		errormessage.Format("���~�H��:%s",e.ErrorMessage());
		MessageBox("�ƾڮw�s������!","���}���ؤ��",MB_ICONINFORMATION|MB_OK);
		return ;//��^
	} 
	
	//�H���سЫؤ�����ɧǱqProject��Ū���Ҧ����ثH��
	strsql="select  *   from  Project ORDER BY �إ߮ɶ�  ASC";  //�w�qSQL�r�Ŧ�	
	try
	{
		//���}�ƾڪ�
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(m_Connection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//���~�B�z
	{
		CString errormessage;
		errormessage.Format("���}�ƾڮw����!\r\n���~�H��:%s",e.ErrorMessage());
		MessageBox(errormessage,"�˸��ƾ�",MB_ICONSTOP);
		return;
	} 
	
	//�R���Ҧ��ƾ�
	m_list.DeleteAllItems();
	mtotalProjects=0;//�`���ؼƪ�l��=0
	
    CString tt[3];
	while(!m_Recordset->adoEOF)//�p�G�S����O������
	{    
		Thevalue = m_Recordset->GetCollect("���ئW��"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt[1]=Thevalue.bstrVal;//���ئW��
		}
	
		Thevalue = m_Recordset->GetCollect("�إ߮ɶ�"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt[2]=Thevalue.bstrVal;//�إ߮ɶ�
		}

		tt[0].Format("%d",mtotalProjects+1);//�Ǹ�

		//�N���ئW��,�إ߮ɶ��H���g�JListCtrl����
		m_list.InsertItem(mtotalProjects,tt[0]);      //�Ǹ�
		m_list.SetItemText(mtotalProjects,1,tt[1]);   //���ئW��
		m_list.SetItemText(mtotalProjects,2,tt[2]);	//���ثإ߮ɶ�
		
		mtotalProjects++;//�`���ؼ�+1

		m_Recordset->MoveNext();//�O�������w�U��
	}  

	m_Recordset->Close();  //�����O����
	m_Connection->Close();//�����ƾڮw
	
	
}

//����ListCtrl�����T�����,�Ψӱo���ܪ����ئW��
void COpenProject::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	NMLISTVIEW    *pNMListView = (NMLISTVIEW    *)pNMHDR;
	
	if(pNMListView->iItem >= 0) //�p�G���
    {
        m_nCurrentItem = pNMListView->iItem;//�������ت�����
        m_nCurrentSubItem = pNMListView->iSubItem;
		m_strProjectname=m_list.GetItemText(m_nCurrentItem,1);//�o���ܪ����ئW��
    }
	*pResult = 0;
}


//���}����
void COpenProject::OnButtonOpen() 
{
	CString strsql;

	if(mtotalProjects<=0)	
	{
		MessageBox("�S�����ءI","���}����",MB_ICONINFORMATION|MB_OK);
		return;
	}
	
	if(m_nCurrentItem<0)	
	{
		MessageBox("�п�ܭn���}�����ءI","���}����",MB_ICONINFORMATION|MB_OK);
		return;
	}
	
	if(	m_strProjectname.IsEmpty())
		return;
	
	BeginWaitCursor();

	
	theApp.m_username=m_strProjectname;
	theApp.m_userpassword="a";
	m_currentSchemeNames=m_strProjectname;
	
	if(theApp.m_pConnection->State) //�p�G�ƾڮw�w���}
		theApp.m_pConnection->Close(); //�����s��
	
	strsql="Provider=OraOLEDB.Oracle;User Id="+theApp.m_username+";Password="+theApp.m_userpassword+";";
	try
	{
		HRESULT hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);
		if(!SUCCEEDED(hr))
		{
			MessageBox("�ƾڮw�s������!","���}����",MB_ICONINFORMATION);
			theApp.m_pConnection->Close();//�����ƾڮw�s��
			return ;
		}
	}
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("���~�H��:%s",e.ErrorMessage());
		MessageBox(errormessage,"���}����",MB_ICONINFORMATION);
		theApp.m_pConnection->Close();//�����ƾڮw�s��
		return ;
	} 

	
	//�w�qSQL�r�Ŧ�
	strsql="select *  from DEM_INFO ";  
	if(m_Recordset->State)	//�p�Gm_Recordset�w���}�A������
		m_Recordset->Close();
	
	try
	{
		//���} DEM_INFO�ƾڪ�,Ū��DEM�����H��
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//���~�B�z
	{
		CString errormessage;
		errormessage.Format("���}�ƾڮw����!\r\n���~�H��:%s",e.ErrorMessage());
		MessageBox(errormessage,"�˸��ƾ�",MB_ICONSTOP);
		m_Recordset->Close();
		return ;
	} 
 
    if(!m_Recordset->adoEOF)//�p�G�S����O��������,��ܦ��O��
	{
		Thevalue = m_Recordset->GetCollect("DEM�_�I����X"); 
		theApp.m_DemLeftDown_x=(double)Thevalue;//DEM���U��x����

		Thevalue = m_Recordset->GetCollect("DEM�_�I����Y"); 
		theApp.m_DemLeftDown_y=(double)Thevalue;//DEM���U��y����

	
		Thevalue = m_Recordset->GetCollect("������ZX"); 	
		theApp.m_Cell_xwidth=(long)Thevalue ;//DEM�bx��V�W����I���Z

		Thevalue = m_Recordset->GetCollect("������ZY"); 
		theApp.m_Cell_ywidth=(long)Thevalue;//DEM�by��V�W����I���Z
		
		Thevalue = m_Recordset->GetCollect("DEM�����j�p"); 
		theApp.m_Dem_BlockSize=(long)Thevalue;//DEM�����j�p,�Y�@�Ӧa�Τl�����j�p

		Thevalue = m_Recordset->GetCollect("DEM�������"); 
		theApp.m_BlockRows=(long)Thevalue;//DEM�������`���

		Thevalue = m_Recordset->GetCollect("DEM�����C��"); 
		theApp.m_BlockCols=(long)Thevalue;//DEM�������`�C��
		
		Thevalue = m_Recordset->GetCollect("��lDEM���"); 
		theApp.m_Dem_Rows=(long)Thevalue;//DEM�ƾکM�`���
 
		Thevalue = m_Recordset->GetCollect("��lDEM�C��"); 
		theApp.m_Dem_cols=(long)Thevalue;//DEM�ƾکM�`�C��
		
		Thevalue = m_Recordset->GetCollect("�L��DEM��"); 
		theApp.m_DEM_IvalidValue=(long)Thevalue;//�L��DEM�ƾ��I���{��
		
		//DEM�a�Τl�����e��(�Y�@�Ӧa�ζ���ܦh�֪Ŷ��Z��,�Y�����j�p=33,
		//DEM�bx��V�W����I���Z=20,�hDEM�a�Τl���e��=20*32=640��)
		theApp.m_Dem_BlockWidth=theApp.m_Cell_xwidth*(theApp.m_Dem_BlockSize-1);
		
		m_Recordset->Close();//�����O����
	
		//DEM�k�W��x����
		theApp.m_DemRightUp_x=theApp.m_DemLeftDown_x+theApp.m_Cell_xwidth*(theApp.m_Dem_cols-1);
		//DEM�k�W��y����
		theApp.m_DemRightUp_y=theApp.m_DemLeftDown_y+theApp.m_Cell_ywidth*(theApp.m_Dem_Rows-1);

	}
	else
	{
		m_Recordset->Close();//�����O����
		MessageBox("���بS���ƼҼƾ�!","���}����",MB_ICONINFORMATION);
		return ;	//��^
	}


	//�w�qSQL�r�Ŧ�
	strsql="select *  from IMAGERECT_INFO ";  
	try
	{
		//���} IMAGERECT_INFO�ƾڪ�,Ū���v�����z�����H��
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//���~�B�z
	{
		CString errormessage;
		errormessage.Format("���}�ƾڮw����!\r\n���~�H��:%s",e.ErrorMessage());
		MessageBox(errormessage,"�˸��ƾ�",MB_ICONSTOP);
		m_Recordset->Close();//�����O����
		return ;	//��^
	} 
	
	
	if(!m_Recordset->adoEOF)	//�p�G�S����O��������,��ܦ��O��
	{
		Thevalue = m_Recordset->GetCollect("���U������X"); 
		theApp.m_TexturLeftDown_x=(double)Thevalue;//���z���U��x����
		
		Thevalue = m_Recordset->GetCollect("���U������Y"); 
		theApp.m_TexturLeftDown_y=(double)Thevalue;//���z���U��y����
		
		Thevalue = m_Recordset->GetCollect("�k�W������X"); 
		theApp.m_TexturRightUp_x=(double)Thevalue ;//���z�k�W��x����
		
		Thevalue = m_Recordset->GetCollect("�k�W������Y"); 
		theApp.m_TexturRightUp_y=(double)Thevalue;//���z�k�W��y����
		
		Thevalue = m_Recordset->GetCollect("�v�����r���`��"); 
		theApp.m_ImagePyramidCount=(long)Thevalue;//���z�v�����r���`��,�Y�h��LOD�ŧO
	
		Thevalue = m_Recordset->GetCollect("�@�żv������v"); 
		theApp.m_ImageResolution[1]=(float)Thevalue;//���z�v���@�żv������v

		Thevalue = m_Recordset->GetCollect("�G�żv������v"); 
		theApp.m_ImageResolution[2]=(float)Thevalue;//���z�v���G�żv������v

		Thevalue = m_Recordset->GetCollect("�T�żv������v"); 
		theApp.m_ImageResolution[3]=(float)Thevalue;//���z�v���T�żv������v
	
		Thevalue = m_Recordset->GetCollect("�|�żv������v"); 
		theApp.m_ImageResolution[4]=(float)Thevalue;//���z�v���|�żv������v
	
		Thevalue = m_Recordset->GetCollect("���żv������v"); 
		theApp.m_ImageResolution[5]=(float)Thevalue;//���z�v�����żv������v

		m_Recordset->Close();//�����O����
		
	}
	else
	{
		m_Recordset->Close();//�����O����
	}
   
  	
	
	theApp.bLoginSucceed=TRUE;//�ƾڥ[�����\
	myOci.Init_OCI();//��l��OCI
	
	//�w�qSQL�r�Ŧ�	
	strsql.Format("select * from Scheme ORDER BY ��צW�� ASC");
	if(m_Recordset->State)
		m_Recordset->Close();
	try
	{
		//���} Scheme�ƾڪ�,Ū�����}��ת������H��
		m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)		//���~�B�z
	{
		CString errormessage;
		errormessage.Format("���}�ƾڮw����!\r\n���~�H��:%s",e.ErrorMessage());
		MessageBox(errormessage,"���}�ƾڮw��",MB_ICONINFORMATION);
		m_Recordset->Close();//�����O����
		return  ;//��^
	} 	
	
	//GetCollect():Ado����ƾڮw�r�q�Ȩ��
	m_SchemeNames.RemoveAll(); //�M�šA�s�x��צW�٪������Ʋ�
	int index=0; //Ū����׫H��
	while(!m_Recordset->adoEOF)
	{
	
		Thevalue = m_Recordset->GetCollect("��צW��"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].Schemename=Thevalue.bstrVal;//��צW��
			m_SchemeNames.Add(myDesingScheme.SchemeDatass[index].Schemename);//�s�x��צW�٨�����Ʋ�
		}

		Thevalue = m_Recordset->GetCollect("�]�p����");
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strDesigngrade=Thevalue.bstrVal;//�]�p����
			
		}
		
		Thevalue = m_Recordset->GetCollect("�o�޺���"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strDraughtstyle=Thevalue.bstrVal;//�o�޺���
		}
		

		Thevalue = m_Recordset->GetCollect("��������"); //��������
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strBlocomotiveStyle=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("����覡"); //����覡
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strCBbsStyle=Thevalue.bstrVal;
		}

		Thevalue = m_Recordset->GetCollect("�a�Φa�O");  //�a�Φa�O
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strTerrainstyle=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("�u�{����"); //�u�{����
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strEngineeringcondition=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("�]�p�t��"); //�]�p�t��
		myDesingScheme.SchemeDatass[index].designspeed=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("�̤p���u�b�|"); //�̤p���u�b�|
		myDesingScheme.SchemeDatass[index].minRadius=(long)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("��o�u���Ī���"); //��o�u���Ī���
		myDesingScheme.SchemeDatass[index].dxfLength=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("�̤p�Y��"); //�̤p�Y��
		myDesingScheme.SchemeDatass[index].minSlopeLength=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("�̤j�Y��"); //�̤j�Y��
		myDesingScheme.SchemeDatass[index].maxSlope=(double)Thevalue;		
	
		Thevalue = m_Recordset->GetCollect("�̤j�Y�׮t"); //�̤j�Y�׮t
		myDesingScheme.SchemeDatass[index].maxSlopePddsc=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("�_�I���{"); //�_�I���{
		myDesingScheme.SchemeDatass[index].StartLC=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("���I���{"); //���I���{
		myDesingScheme.SchemeDatass[index].EndLC=(double)Thevalue;		
		
		index++;	
		m_Recordset->MoveNext();//�O�������w�U��

	}
	m_Recordset->Close();//�����O����
	if(m_SchemeNames.GetSize()>0)
	{
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		pMainFrame->AddSchemeName();
	}
	MessageBox("���}���ئ��\!","���}����",MB_ICONINFORMATION);
    EndWaitCursor();//�N���Ф������q�{����,��������
	EndDialog(IDOK);
}


//�R������
void COpenProject::OnButtonDelete() 
{
	HRESULT hr;
	CString trsql;
	
	
	if(mtotalProjects<=0)	//�p�G���ت��`��<=0�A����٨S���إ߶��ءA����R�� 
	{
		MessageBox("�S�����ءI","�R������",MB_ICONINFORMATION|MB_OK);
		return;
	}

	if(m_nCurrentItem<0)	//�p�G�S���襤ListCtrl���󪺶��ءA��^
	{
		MessageBox("�п�ܭn�R�������ءI","�R������",MB_ICONINFORMATION|MB_OK);
		return;
	}

	//��e���}���ؤ���R��
	if(strcmp(theApp.m_username,m_strProjectname)==0)
	{
		MessageBox("��e���}���ج�"+m_strProjectname+",����R��!","�R������",MB_ICONSTOP|MB_OK);
		return;
	}

	//�p�Gm_Connection�w�B��s�����A�A�������A�_�h�A���s���ɱN�X��
	if(m_Connection->State)
		m_Connection->Close();
	
	BeginWaitCursor();//�եΥ������ܨF�|����,�i�D�Τ�t�Φ�
	
	//�w�qSQL�r�Ŧ�
	CString strsql="Provider=OraOLEDB.Oracle;User Id=RW3D;Password=aaa;";
	try
	{
		hr =m_Connection->Open(_bstr_t(strsql),"","",-1);//�s���s�x���ئW�١B�Ыؤ����Oralce�Τ�RW3D
		
		if(!SUCCEEDED(hr))//�p�G�ƾڮw�s������
		{
			MessageBox("�ƾڮw�s������!","�R������",MB_ICONINFORMATION);
			m_Connection->Close();//�����s��
			EndWaitCursor();//�M���F�|����,�ë�_�H�e������
			return ;//��^
		}
	}
	catch(_com_error& e)	//���~�B�z
	{
		CString errormessage;
		errormessage.Format("���~�H��:%s",e.ErrorMessage());
		MessageBox(errormessage,"�R������",MB_ICONINFORMATION);
		m_Connection->Close();//�����s��
		EndWaitCursor();//�M���F�|����,�ë�_�H�e������
		return ;//��^
	} 
 
	int manwer=MessageBox("�O�_�R������?","�R������",MB_ICONINFORMATION|MB_YESNO);
	if(manwer==7)//�p�G���R�����ءA��^
		return ;

//	drop tablespace XXXX INCLUDING CONTENTS; 
//	drop user XXXX cascade;
//	Oracle��drop user�Mdrop user cascade���ϧO
//		drop user �F �ȶȬO�R���Τ�A
//		drop user �ѡ�  cascade �F�|�R�����Τ�W�U���Ҧ���M���ϡC�[�ѼƴN�O���F�R���o�ӥΤ�U���Ҧ���H! 

	//�Ы�SQL�r�Ŧ�
//	strsql="Provider=OraOLEDB.Oracle;Data Source="+theApp.m_servername+";User Id="+theApp.m_systemname+";Password="+theApp.m_userpassword+";";
//	theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//���}Oracle�t�κ޲z���Τ�
//	strsql="Drop user "+m_strProjectname+"  cascade";
//	theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);

	
	//�w�qSQL�r�Ŧ�,(�R���Τ�)
	//�R�����إΤ�M���Τ�W�U���Ҧ���M����(�Ѽ� cascade�N�O���F�R���o�ӥΤ�U���Ҧ���H!)
	strsql="Drop user "+m_strProjectname+"  cascade";
	try
	{
		hr =m_Connection->Execute (_bstr_t(strsql),NULL,adCmdText);//�R������
		if(!SUCCEEDED(hr))
		{
			MessageBox("�R�����إ���!","�R������",MB_ICONINFORMATION);
			m_Connection->Close();//�����s��
			EndWaitCursor();//�M���F�|����,�ë�_�H�e������
			return ;//��^
		}
	}
	catch(_com_error& e)	//���~�B�z
	{
		CString errormessage;
		errormessage.Format("���~�H��:%s",e.ErrorMessage());
		m_Connection->Close();//�����s��
		MessageBox(errormessage,"�R������",MB_ICONINFORMATION);
		EndWaitCursor();//�M���F�|����,�ë�_�H�e������
		return ;//��^
	} 

	strsql.Format("Delete  from Project WHERE ���ئW��='%s'",m_strProjectname);
	hr =m_Connection->Execute (_bstr_t(strsql),NULL,adCmdText);
	m_Connection->Close();//�����s��
	
	MessageBox("���اR�����\!","�R������",MB_ICONINFORMATION);

	m_nCurrentItem=-1; //��_���襤���A
	LoadData(); //���s�[�����ؼƾ�
	EndWaitCursor();//�M���F�|����,�ë�_�H�e������
	
}



//���}����
BOOL  COpenProject::OpenProjects(int NewOrOpen)
{
	CString strsql;

	
	BeginWaitCursor();
	
	//�w�qSQL�r�Ŧ�
	strsql="select *  from DEM_INFO ";  
	if(m_Recordset->State)	//�p�Gm_Recordset�w���}�A������
		m_Recordset->Close();
	
	try
	{
		//���} DEM_INFO�ƾڪ�,Ū��DEM�����H��
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//���~�B�z
	{
		CString errormessage;
		errormessage.Format("���}�ƾڮw����!\r\n���~�H��:%s",e.ErrorMessage());
		MessageBox(errormessage,"�˸��ƾ�",MB_ICONSTOP);
		return FALSE;
	} 
 
    if(!m_Recordset->adoEOF)//�p�G�S����O��������,��ܦ��O��
	{
		Thevalue = m_Recordset->GetCollect("DEM�_�I����X"); 
		theApp.m_DemLeftDown_x=(double)Thevalue;//DEM���U��x����

		Thevalue = m_Recordset->GetCollect("DEM�_�I����Y"); 
		theApp.m_DemLeftDown_y=(double)Thevalue;//DEM���U��y����

	
		Thevalue = m_Recordset->GetCollect("������ZX"); 	
		theApp.m_Cell_xwidth=(long)Thevalue ;//DEM�bx��V�W����I���Z

		Thevalue = m_Recordset->GetCollect("������ZY"); 
		theApp.m_Cell_ywidth=(long)Thevalue;//DEM�by��V�W����I���Z
		
		Thevalue = m_Recordset->GetCollect("DEM�����j�p"); 
		theApp.m_Dem_BlockSize=(long)Thevalue;//DEM�����j�p,�Y�@�Ӧa�Τl�����j�p

		Thevalue = m_Recordset->GetCollect("DEM�������"); 
		theApp.m_BlockRows=(long)Thevalue;//DEM�������`���

		Thevalue = m_Recordset->GetCollect("DEM�����C��"); 
		theApp.m_BlockCols=(long)Thevalue;//DEM�������`�C��
		
		Thevalue = m_Recordset->GetCollect("��lDEM���"); 
		theApp.m_Dem_Rows=(long)Thevalue;//DEM�ƾکM�`���
 
		Thevalue = m_Recordset->GetCollect("��lDEM�C��"); 
		theApp.m_Dem_cols=(long)Thevalue;//DEM�ƾکM�`�C��
		
		Thevalue = m_Recordset->GetCollect("�L��DEM��"); 
		theApp.m_DEM_IvalidValue=(long)Thevalue;//�L��DEM�ƾ��I���{��
		
		//DEM�a�Τl�����e��(�Y�@�Ӧa�ζ���ܦh�֪Ŷ��Z��,�Y�����j�p=33,
		//DEM�bx��V�W����I���Z=20,�hDEM�a�Τl���e��=20*32=640��)
		theApp.m_Dem_BlockWidth=theApp.m_Cell_xwidth*(theApp.m_Dem_BlockSize-1);
		
		m_Recordset->Close();//�����O����
	
		//DEM�k�W��x����
		theApp.m_DemRightUp_x=theApp.m_DemLeftDown_x+theApp.m_Cell_xwidth*(theApp.m_Dem_cols-1);
		//DEM�k�W��y����
		theApp.m_DemRightUp_y=theApp.m_DemLeftDown_y+theApp.m_Cell_ywidth*(theApp.m_Dem_Rows-1);

	}
	else
	{
		m_Recordset->Close();//�����O����
		MessageBox("���بS���ƼҼƾ�!","���}����",MB_ICONINFORMATION);
		return FALSE;	//��^
	}


	//�w�qSQL�r�Ŧ�
	strsql="select *  from IMAGERECT_INFO ";  
	try
	{
		//���} IMAGERECT_INFO�ƾڪ�,Ū���v�����z�����H��
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//���~�B�z
	{
		CString errormessage;
		errormessage.Format("���}�ƾڮw����!\r\n���~�H��:%s",e.ErrorMessage());
		MessageBox(errormessage,"�˸��ƾ�",MB_ICONSTOP);
		m_Recordset->Close();//�����O����
		return FALSE;	//��^
	} 
	
	
	if(!m_Recordset->adoEOF)	//�p�G�S����O��������,��ܦ��O��
	{
		Thevalue = m_Recordset->GetCollect("���U������X"); 
		theApp.m_TexturLeftDown_x=(double)Thevalue;//���z���U��x����
		
		Thevalue = m_Recordset->GetCollect("���U������Y"); 
		theApp.m_TexturLeftDown_y=(double)Thevalue;//���z���U��y����
		
		Thevalue = m_Recordset->GetCollect("�k�W������X"); 
		theApp.m_TexturRightUp_x=(double)Thevalue ;//���z�k�W��x����
		
		Thevalue = m_Recordset->GetCollect("�k�W������Y"); 
		theApp.m_TexturRightUp_y=(double)Thevalue;//���z�k�W��y����
		
		Thevalue = m_Recordset->GetCollect("�v�����r���`��"); 
		theApp.m_ImagePyramidCount=(long)Thevalue;//���z�v�����r���`��,�Y�h��LOD�ŧO
	
		Thevalue = m_Recordset->GetCollect("�@�żv������v"); 
		theApp.m_ImageResolution[1]=(float)Thevalue;//���z�v���@�żv������v

		Thevalue = m_Recordset->GetCollect("�G�żv������v"); 
		theApp.m_ImageResolution[2]=(float)Thevalue;//���z�v���G�żv������v

		Thevalue = m_Recordset->GetCollect("�T�żv������v"); 
		theApp.m_ImageResolution[3]=(float)Thevalue;//���z�v���T�żv������v
	
		Thevalue = m_Recordset->GetCollect("�|�żv������v"); 
		theApp.m_ImageResolution[4]=(float)Thevalue;//���z�v���|�żv������v
	
		Thevalue = m_Recordset->GetCollect("���żv������v"); 
		theApp.m_ImageResolution[5]=(float)Thevalue;//���z�v�����żv������v

		m_Recordset->Close();//�����O����
		
	}
	else
	{
		m_Recordset->Close();//�����O����
	}
   
  	
	
	theApp.bLoginSucceed=TRUE;//�ƾڥ[�����\
	myOci.Init_OCI();//��l��OCI
	
	//�w�qSQL�r�Ŧ�	
	strsql.Format("select * from Scheme ORDER BY ��צW�� ASC");
	if(m_Recordset->State)
		m_Recordset->Close();
	try
	{
		//���} Scheme�ƾڪ�,Ū�����}��ת������H��
		m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)		//���~�B�z
	{
		CString errormessage;
		errormessage.Format("���}�ƾڮw����!\r\n���~�H��:%s",e.ErrorMessage());
		MessageBox(errormessage,"���}�ƾڮw��",MB_ICONINFORMATION);
		m_Recordset->Close();//�����O����
		return  FALSE;//��^
	} 	
	
	m_SchemeNames.RemoveAll();	
	//GetCollect():Ado����ƾڮw�r�q�Ȩ��
	int index=0; //Ū����׫H��
	while(!m_Recordset->adoEOF)
	{
	
		Thevalue = m_Recordset->GetCollect("��צW��"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].Schemename=Thevalue.bstrVal;//��צW��
			m_SchemeNames.Add(myDesingScheme.SchemeDatass[index].Schemename);
			
		}

		Thevalue = m_Recordset->GetCollect("�]�p����");
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strDesigngrade=Thevalue.bstrVal;//�]�p����
			
		}
		
		Thevalue = m_Recordset->GetCollect("�o�޺���"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strDraughtstyle=Thevalue.bstrVal;//�o�޺���
		}
		

		Thevalue = m_Recordset->GetCollect("��������"); //��������
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strBlocomotiveStyle=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("����覡"); //����覡
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strCBbsStyle=Thevalue.bstrVal;
		}

		Thevalue = m_Recordset->GetCollect("�a�Φa�O");  //�a�Φa�O
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strTerrainstyle=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("�u�{����"); //�u�{����
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strEngineeringcondition=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("�]�p�t��"); //�]�p�t��
		myDesingScheme.SchemeDatass[index].designspeed=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("�̤p���u�b�|"); //�̤p���u�b�|
		myDesingScheme.SchemeDatass[index].minRadius=(long)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("��o�u���Ī���"); //��o�u���Ī���
		myDesingScheme.SchemeDatass[index].dxfLength=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("�̤p�Y��"); //�̤p�Y��
		myDesingScheme.SchemeDatass[index].minSlopeLength=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("�̤j�Y��"); //�̤j�Y��
		myDesingScheme.SchemeDatass[index].maxSlope=(double)Thevalue;		
	
		Thevalue = m_Recordset->GetCollect("�̤j�Y�׮t"); //�̤j�Y�׮t
		myDesingScheme.SchemeDatass[index].maxSlopePddsc=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("�_�I���{"); //�_�I���{
		myDesingScheme.SchemeDatass[index].StartLC=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("���I���{"); //���I���{
		myDesingScheme.SchemeDatass[index].EndLC=(double)Thevalue;		
		
		index++;	
		m_Recordset->MoveNext();//�O�������w�U��

	}
	m_Recordset->Close();//�����O����
	
	if(m_SchemeNames.GetSize()>0)
	{
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		pMainFrame->AddSchemeName();
	}

//	if(NewOrOpen==1) //	1:���}����  -1:�s�ض���
	MessageBox("���}���ئ��\!","���}����",MB_ICONINFORMATION);
    
    EndWaitCursor();//�N���Ф������q�{����,��������

	return TRUE; //��^
	
}

//��l�� ListCtrl����
void COpenProject::InitListCtrl()
{
	// 	1.�s�[ListControl ����A�ݩʤ���style�ݩʭ��U��View���Report�C
	m_list.InsertColumn(0,"�Ǹ�");          //���J�C
	m_list.InsertColumn(1,"���ئW��");
	m_list.InsertColumn(2,"���سЫؤ��");

	CRect rect;
	m_list.GetClientRect(rect);    //��o��e�Ȥ�ϫH��                 
	m_list.SetColumnWidth(0,rect.Width()/5);   //�]�m�C���e��     
	m_list.SetColumnWidth(1,rect.Width()/3);
	m_list.SetColumnWidth(2,rect.Width()/3);
	
	//�]�mListControl ���󭷮欰����M����ܼҦ�
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_GRIDLINES|   LVS_EX_FULLROWSELECT);
}

