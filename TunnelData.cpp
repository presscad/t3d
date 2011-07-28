// TunnelData.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "TunnelData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CTunnelData dialog


CTunnelData::CTunnelData(CWnd* pParent /*=NULL*/)
	: CDialog(CTunnelData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTunnelData)
	m_endLC = 0.0;
	m_length = 0.0f;
	m_name = _T("");
	m_startLc = 0.0;
	//}}AFX_DATA_INIT
}


void CTunnelData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTunnelData)
	DDX_Text(pDX, IDC_EDIT_ENDLC, m_endLC);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_length);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_STARTLC, m_startLc);
	DDX_Control(pDX, IDC_MSFLEXGRID, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTunnelData, CDialog)
	//{{AFX_MSG_MAP(CTunnelData)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, OnButtonOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CTunnelData message handlers

BOOL CTunnelData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	m_pRecordset.CreateInstance(_uuidof(Recordset));
	m_bChageData=FALSE;

	InitGrid();
	LoadData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTunnelData::InitGrid()
{
	m_grid.SetCols(5);
	m_grid.SetColWidth(0,400);
	m_grid.SetColWidth(1,1000);
	m_grid.SetColWidth(2,1300);
	m_grid.SetColWidth(3,1300);
	m_grid.SetColWidth(4,1200);
	
	m_grid.SetTextMatrix(0,0,"�Ǹ�");
	m_grid.SetTextMatrix(0,1,"�G�D�W��");
	m_grid.SetTextMatrix(0,2,"�_�I���{");
	m_grid.SetTextMatrix(0,3,"���I���{");
	m_grid.SetTextMatrix(0,4,"�G�D����");
	
}

void CTunnelData::LoadData()
{
	
	CString tt;
	
	
	tt.Format("SELECT *  FROM  Tunnel WHERE ��צW��='%s' ORDER BY  �G�D�_�I���{ ASC",myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename);
	try
	{
		m_pRecordset->Open((_bstr_t)tt,(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("���}����!\r\n���~�H��:%s",e.ErrorMessage());
		::MessageBox(NULL,errormessage,"���}�ƾڪ�",MB_ICONSTOP);
		return;
	} 
	
	m_totalNums=0;
	while (!m_pRecordset->adoEOF)
	{
		m_totalNums++;
		m_grid.SetRows(m_totalNums+1);
		tt.Format("%d",m_totalNums);
		m_grid.SetTextMatrix(m_totalNums,0,tt);
		
		Thevalue = m_pRecordset->GetCollect("�G�D�W��"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			m_name=Thevalue.bstrVal;
			m_grid.SetTextMatrix(m_totalNums,1,m_name);
		}
		
		
		Thevalue = m_pRecordset->GetCollect("�G�D�_�I���{"); 
		tt.Format("%.3f",(double)Thevalue);
		m_grid.SetTextMatrix(m_totalNums,2,tt);
		
		Thevalue = m_pRecordset->GetCollect("�G�D���I���{"); 
		tt.Format("%.3f",(double)Thevalue);
		m_grid.SetTextMatrix(m_totalNums,3,tt);
		
		Thevalue = m_pRecordset->GetCollect("�G�D����"); 
		tt.Format("%.3f",(double)Thevalue);
		m_grid.SetTextMatrix(m_totalNums,4,tt);
		
		
		m_pRecordset->MoveNext();
	}
	m_grid.SetRows(m_totalNums+1);
	
	m_pRecordset->Close();
}

void CTunnelData::OnButtonAdd() 
{
	
	this->UpdateData();
	if(CheckValid(TRUE)==FALSE)
		return;

	m_length=m_endLC-m_startLc;
	this->UpdateData(FALSE);

	CString tt;

	tt.Format("INSERT INTO Tunnel VALUES(\
		  '%s',%.3f,%.3f,%.3f,'%s')",\
		  m_name,
		  m_startLc,
		  m_endLC,
		  m_length,
		  myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename
		  );
	try
	{
		hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 
		if(!SUCCEEDED(hr))
		{
			AfxMessageBox("�W�[�ƾ�!",MB_ICONINFORMATION);
			return;
		}
	}

	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("���~�H��:%s",e.ErrorMessage());
		AfxMessageBox(errormessage,MB_ICONINFORMATION);
		return;
	} 

	LoadData();


	MessageBox("�W�[�ƾڦ��\","�W�[�ƾ�",MB_ICONINFORMATION);
	m_bChageData=TRUE;

		
}

BOOL CTunnelData::CheckValid(BOOL ADDorEDit)
{
	this->UpdateData();

	if(m_startLc>=m_endLC)
	{
		MessageBox("�_�I���{����<=���I���{","�ƾ��ˬd",MB_ICONSTOP);
		return FALSE;
	}
	
	if(m_name.IsEmpty())
	{
		MessageBox("�W�٤��ର��","�ƾ��ˬd",MB_ICONSTOP);
		return FALSE;
		
	}
	
	CString tt;
	
	if(ADDorEDit==TRUE) 
		tt.Format("SELECT *  FROM  Tunnel WHERE ��צW��='%s' AND \
		�G�D�W��='%s'",myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename,m_name);
	else
		tt.Format("SELECT *  FROM  Tunnel WHERE ��צW��='%s' AND \
		  �G�D�W��='%s' AND �G�D�W��!='%s'" ,myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename,m_name,m_oldname);

	try
	{
		m_pRecordset->Open((_bstr_t)tt,(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("���}����!\r\n���~�H��:%s",e.ErrorMessage());
		::MessageBox(NULL,errormessage,"���}�ƾڪ�",MB_ICONSTOP);
		return FALSE;
	} 
	
	if (!m_pRecordset->adoEOF)
	{
		tt.Format("�G�D�W��[%s]�w�g�s�b!",m_name);
		MessageBox(tt,"�W�[�ƾ�",MB_ICONSTOP);
		m_pRecordset->Close();
		return FALSE;
	}
	m_pRecordset->Close();

	 return TRUE;

}

void CTunnelData::OnButtonExit() 
{
	EndDialog(IDOK);	
}

BEGIN_EVENTSINK_MAP(CTunnelData, CDialog)
    //{{AFX_EVENTSINK_MAP(CTunnelData)
	ON_EVENT(CTunnelData, IDC_MSFLEXGRID, -600 /* Click */, OnClickMsflexgrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CTunnelData::OnClickMsflexgrid() 
{

 
	if(m_totalNums<=0) 
		return;
	
	int m_curRow=m_grid.GetRow();
	if(m_curRow<=0) 
		return;
	

	m_name=m_grid.GetTextMatrix(m_curRow,1);
	m_startLc=atof(m_grid.GetTextMatrix(m_curRow,2));
	m_endLC=atof(m_grid.GetTextMatrix(m_curRow,3));
	m_length=atof(m_grid.GetTextMatrix(m_curRow,4));

	m_oldname=m_name;
	
	this->UpdateData(FALSE);
	
	
}

void CTunnelData::OnButtonEdit() 
{

	this->UpdateData();

	int m_curRow=m_grid.GetRow();
	if(m_curRow<=0) 
		return;

	if(CheckValid(FALSE)==FALSE)
		return;
	
	

	m_length=m_endLC-m_startLc;
	this->UpdateData(FALSE);
	
	CString tt;
	

	tt.Format("DELETE FROM  Tunnel WHERE �G�D�W��='%s' AND ��צW��='%s'",\
		m_oldname,myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename);
	hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 

	tt.Format("INSERT INTO Tunnel VALUES(\
		'%s',%.3f,%.3f,%.3f,'%s')",\
		m_name,
		m_startLc,
		m_endLC,
		m_length,
		myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename
		);

		hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 
		if(!SUCCEEDED(hr))
		{
			AfxMessageBox("�W�[�ƾ�!",MB_ICONINFORMATION);
			return;
		}


	LoadData();
	
	MessageBox("�ק�ƾڦ��\","�ק�ƾ�",MB_ICONINFORMATION);
	m_bChageData=TRUE;

}

void CTunnelData::OnButtonDelete() 
{
	int m_curRow=m_grid.GetRow();
	if(m_curRow<=0) 
		return;
	

	m_length=m_endLC-m_startLc;
	this->UpdateData(FALSE);
	
	CString tt;
	

	tt.Format("DELETE FROM  Tunnel WHERE �G�D�W��='%s' AND ��צW��='%s'",\
		m_oldname,myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename);
	
	try
	{
		hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 
		if(!SUCCEEDED(hr))
		{
			AfxMessageBox("�R���ƾ�!",MB_ICONINFORMATION);
			return;
		}
	}
	
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("���~�H��:%s",e.ErrorMessage());
		AfxMessageBox(errormessage,MB_ICONINFORMATION);
		return;
	} 

	LoadData();

	MessageBox("�R���ƾڦ��\","�R���ƾ�",MB_ICONINFORMATION);
	m_bChageData=TRUE;
	
}

void CTunnelData::OnButtonOutput() 
{
	WriteToExcel();
	
}

void CTunnelData::WriteToExcel()
{
	CString sExcelFile,sTableFile,sSql,sDriver;
	CDatabase database;
	
	sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)"; 
	CFileDialog dlg(FALSE,"Excel���",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"Excel���(*.xls)|*.xls||",NULL);
	dlg.m_ofn.lpstrTitle="��X��Excel���";
	
	if(dlg.DoModal()==IDCANCEL)		return;
	
	sExcelFile=dlg.GetPathName();
	
	
	
	DeleteFile(sExcelFile);
	sTableFile=dlg.GetFileTitle();	
	
	try
	{
		
		sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, sExcelFile, sExcelFile);
		
		
		if( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
		{
			
			
		sSql = "CREATE TABLE "+sTableFile+" (�G�D�W�� TEXT,�G�D�_�I���{  NUMBER,\
			�G�D���I���{ NUMBER,�G�D���� NUMBER)";
		
		database.ExecuteSQL(sSql);
			
			for(int i=0;i<m_grid.GetRows ()-1;i++)
			{
			sSql.Format("INSERT INTO "+sTableFile+"	VALUES('%s',%.3f,%.3f,%.3f)",\
				m_grid.GetTextMatrix (i+1,1),\
				atof(m_grid.GetTextMatrix (i+1,2)),\
				atof(m_grid.GetTextMatrix (i+1,3)),\
				atof(m_grid.GetTextMatrix (i+1,4)));
			database.ExecuteSQL(sSql);
			}
		} 
		
		database.Close();		
		this->MessageBox("Excel��� "+sExcelFile+" �w��X���\!","��X��Excel���",MB_ICONINFORMATION);
	}
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("���~�H��:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);
	} 
}
