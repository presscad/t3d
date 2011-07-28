// BridgeData.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "BridgeData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CBridgeData dialog


CBridgeData::CBridgeData(CWnd* pParent /*=NULL*/)
	: CDialog(CBridgeData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBridgeData)
	m_endLC = 0.0;
	m_length = 0.0;
	m_name = _T("");
	m_startLc = 0.0;
	//}}AFX_DATA_INIT
}


void CBridgeData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBridgeData)
	DDX_Text(pDX, IDC_EDIT_ENDLC, m_endLC);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_length);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_STARTLC, m_startLc);
	DDX_Control(pDX, IDC_MSFLEXGRID, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBridgeData, CDialog)
	//{{AFX_MSG_MAP(CBridgeData)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT, OnButtonOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CBridgeData message handlers


BOOL CBridgeData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	m_pRecordset.CreateInstance(_uuidof(Recordset));
	
	m_bChageData=FALSE;
	InitGrid();
	LoadData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CBridgeData::InitGrid()
{
	m_grid.SetCols(5);
	m_grid.SetColWidth(0,400);
	m_grid.SetColWidth(1,1000);
	m_grid.SetColWidth(2,1300);
	m_grid.SetColWidth(3,1300);
	m_grid.SetColWidth(4,1200);
	
	m_grid.SetTextMatrix(0,0,"�Ǹ�");
	m_grid.SetTextMatrix(0,1,"���٦W��");
	m_grid.SetTextMatrix(0,2,"�_�I���{");
	m_grid.SetTextMatrix(0,3,"���I���{");
	m_grid.SetTextMatrix(0,4,"���٪���");
	
}

void CBridgeData::LoadData()
{
	
 
 
	
	CString tt;
	
	
	tt.Format("SELECT *  FROM  Bridge WHERE ��צW��='%s' ORDER BY  ���ٰ_�I���{ ASC",myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename);
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
		
		Thevalue = m_pRecordset->GetCollect("���٦W��"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			m_name=Thevalue.bstrVal;
			m_grid.SetTextMatrix(m_totalNums,1,m_name);
		}
		
		
		Thevalue = m_pRecordset->GetCollect("���ٰ_�I���{"); 
		tt.Format("%.3f",(double)Thevalue);
		m_grid.SetTextMatrix(m_totalNums,2,tt);
		
		Thevalue = m_pRecordset->GetCollect("���ٲ��I���{"); 
		tt.Format("%.3f",(double)Thevalue);
		m_grid.SetTextMatrix(m_totalNums,3,tt);
		
		Thevalue = m_pRecordset->GetCollect("���٪���"); 
		tt.Format("%.3f",(double)Thevalue);
		m_grid.SetTextMatrix(m_totalNums,4,tt);
		
		
		m_pRecordset->MoveNext();
	}
	m_grid.SetRows(m_totalNums+1);
	
	m_pRecordset->Close();
}

void CBridgeData::OnButtonAdd() 
{
	
	this->UpdateData();
	if(CheckValid(TRUE)==FALSE)
		return;

	m_length=m_endLC-m_startLc;
	this->UpdateData(FALSE);

	CString tt;

	tt.Format("INSERT INTO Bridge VALUES(\
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

BOOL CBridgeData::CheckValid(BOOL ADDorEDit)
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
		tt.Format("SELECT *  FROM  Bridge WHERE ��צW��='%s' AND \
		���٦W��='%s'",myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename,m_name);
	else
		tt.Format("SELECT *  FROM  Bridge WHERE ��צW��='%s' AND \
		  ���٦W��='%s' AND ���٦W��!='%s'" ,myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename,m_name,m_oldname);

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
		tt.Format("���٦W��[%s]�w�g�s�b!",m_name);
		MessageBox(tt,"�W�[�ƾ�",MB_ICONSTOP);
		m_pRecordset->Close();
		return FALSE;
	}
	m_pRecordset->Close();

	 return TRUE;

}

void CBridgeData::OnButtonExit() 
{
	EndDialog(IDOK);	
}


void CBridgeData::OnClickMsflexgrid() 
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

void CBridgeData::OnButtonEdit() 
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
	

	tt.Format("DELETE FROM  Bridge WHERE ���٦W��='%s' AND ��צW��='%s'",\
		m_oldname,myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename);

	hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 
	
	tt.Format("INSERT INTO Bridge VALUES(\
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

void CBridgeData::OnButtonDelete() 
{
	int m_curRow=m_grid.GetRow();
	if(m_curRow<=0) 
		return;
	

	m_length=m_endLC-m_startLc;

	this->UpdateData(FALSE);
	
	CString tt;
	
	tt.Format("DELETE FROM  Bridge WHERE ���٦W��='%s' AND ��צW��='%s'",\
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

void CBridgeData::OnButtonOutput() 
{
	WriteToExcel();
	
}

void CBridgeData::WriteToExcel()
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
			
			
		sSql = "CREATE TABLE "+sTableFile+" (���٦W�� TEXT,���ٰ_�I���{  NUMBER,\
			���ٲ��I���{ NUMBER,���٪��� NUMBER)";
		
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

BEGIN_EVENTSINK_MAP(CBridgeData, CDialog)
    //{{AFX_EVENTSINK_MAP(CBridgeData)
	ON_EVENT(CBridgeData, IDC_MSFLEXGRID, -600 /* Click */, OnClickMsflexgrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
