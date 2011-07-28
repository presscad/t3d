// ZdmGeoSegmentFeatures.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "ZdmGeoSegmentFeatures.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CZdmGeoSegmentFeatures dialog


CZdmGeoSegmentFeatures::CZdmGeoSegmentFeatures(CWnd* pParent /*=NULL*/)
	: CDialog(CZdmGeoSegmentFeatures::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZdmGeoSegmentFeatures)
	m_SegmentendLC = 0.0;
	m_SegmentstartLC = 0.0;
	m_geoFeature = _T("");
	//}}AFX_DATA_INIT
}


void CZdmGeoSegmentFeatures::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZdmGeoSegmentFeatures)
	DDX_Text(pDX, IDC_EDIT_ENDLC, m_SegmentendLC);
	DDX_Text(pDX, IDC_EDIT_STARTLC, m_SegmentstartLC);
	DDX_Text(pDX, IDC_EDIT_GEOFEATURE, m_geoFeature);
	DDX_Control(pDX, IDC_MSFLEXGRID, m_grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZdmGeoSegmentFeatures, CDialog)
	//{{AFX_MSG_MAP(CZdmGeoSegmentFeatures)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CZdmGeoSegmentFeatures message handlers

 
void CZdmGeoSegmentFeatures::OnButtonAdd() 
{

	CString tt;

	this->UpdateData();
	if(CheckValid()==FALSE)
		return;

	m_TotalNums++;
	m_grid.SetRows(m_TotalNums+1); 
	
	tt.Format("INSERT INTO zdmSegmentGeoFeature VALUES (%.3f,%.3f,'%s','%s')",\
		m_SegmentstartLC,m_SegmentendLC,m_geoFeature,\
		myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename);
	try
	{
		hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 
		if(!SUCCEEDED(hr))
		{
			MessageBox("�W�[����","�W�[�ƾ�",MB_ICONSTOP);
			return;
		}
	}
	catch(_com_error& e)	
	{
		MessageBox("�W�[����!","�W�[�ƾ�",MB_ICONSTOP);
	} 
	

	tt.Format("%.3f",m_SegmentstartLC);
	m_grid.SetTextMatrix(m_TotalNums,1,tt);
	tt.Format("%.3f",m_SegmentendLC);
	m_grid.SetTextMatrix(m_TotalNums,2,tt);
	m_grid.SetTextMatrix(m_TotalNums,3,m_geoFeature);

	MessageBox("�W�[���\","�W�[�ƾ�",MB_ICONINFORMATION);
	

}

BOOL CZdmGeoSegmentFeatures::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_pRecordset.CreateInstance(_uuidof(Recordset));
	
	m_TotalNums=0;

	InitGrid();
	LoadData();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CZdmGeoSegmentFeatures::InitGrid()
{
	m_grid.SetCols(4);
	m_grid.SetColWidth(0,400);
	m_grid.SetColWidth(1,1400);
	m_grid.SetColWidth(2,1400);
	m_grid.SetColWidth(3,3000);
	
	m_grid.SetTextMatrix(0,0,"�Ǹ�");
	m_grid.SetTextMatrix(0,1,"���q�_�l���{");
	m_grid.SetTextMatrix(0,2,"���q���I���{");
	m_grid.SetTextMatrix(0,3,"�u�{�a��S�x");
	
	
}

void CZdmGeoSegmentFeatures::LoadData()
{
	CString tt;
	tt.Format("select * from zdmSegmentGeoFeature ORDER BY ���q�_�l���{");
	m_pRecordset->Open(_bstr_t(tt),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	m_TotalNums=0;
	while(!m_pRecordset->adoEOF)
	{
		m_TotalNums++;
		m_grid.SetRows(m_TotalNums+1);

		Thevalue=m_pRecordset->GetCollect("���q�_�l���{"); 
		m_SegmentstartLC=(double)Thevalue;
		tt.Format("%.3f",m_SegmentstartLC);
		m_grid.SetTextMatrix(m_TotalNums,1,tt);
		
		Thevalue=m_pRecordset->GetCollect("���q���I���{"); 
		m_SegmentendLC=(double)Thevalue;
		tt.Format("%.3f",m_SegmentendLC);
		m_grid.SetTextMatrix(m_TotalNums,2,tt);
	
		Thevalue=m_pRecordset->GetCollect("�u�{�a��S�x"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			m_geoFeature=Thevalue.bstrVal;
		}
		m_grid.SetTextMatrix(m_TotalNums,3,m_geoFeature);
		
		m_pRecordset->MoveNext();
	}
	m_pRecordset->Close();
		
}



BOOL CZdmGeoSegmentFeatures::CheckValid()
{
	this->UpdateData();

	if(this->m_geoFeature.IsEmpty())
	{
		MessageBox("�a��S�x���ର��","�ƾ��ˬd",MB_ICONSTOP);
		return FALSE;
	}
	
	if(m_SegmentstartLC>m_SegmentendLC)
	{
		MessageBox("���q�_�l���{����j����q���I���{","�ƾ��ˬd",MB_ICONSTOP);
		return FALSE;
	}

		
	for(int i=1;i<m_TotalNums;i++)
	{
		double L1=atof(m_grid.GetTextMatrix(i,2));
		double L2=atof(m_grid.GetTextMatrix(i+1,1));
		if(L1<L2)
		{
			MessageBox("�U���q�_�l���{����p��W�@���q���I���{","�ƾ��ˬd",MB_ICONSTOP);
			return FALSE;
		}
	}

	return TRUE;

}

BEGIN_EVENTSINK_MAP(CZdmGeoSegmentFeatures, CDialog)
    //{{AFX_EVENTSINK_MAP(CZdmGeoSegmentFeatures)
	ON_EVENT(CZdmGeoSegmentFeatures, IDC_MSFLEXGRID, -600 /* Click */, OnClickMsflexgrid, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CZdmGeoSegmentFeatures::OnClickMsflexgrid() 
{
	
	int row=m_grid.GetRow();
	if(m_TotalNums<1 || row<1 )
		return;
	
	this->UpdateData();
	
	m_SegmentstartLC=atof(m_grid.GetTextMatrix(row,1));
	m_SegmentendLC=atof(m_grid.GetTextMatrix(row,2));
	m_geoFeature=m_grid.GetTextMatrix(row,3);
	
	m_oldSegmentstartLC=m_SegmentstartLC;
	m_oldSegmentendLC=m_SegmentendLC;
	
	this->UpdateData(FALSE);

}

void CZdmGeoSegmentFeatures::OnButtonDelete() 
{
	int row=m_grid.GetRow();
	if(m_TotalNums<1 || row<1 )
		return;

	CString strSql;

	m_SegmentstartLC=atof(m_grid.GetTextMatrix(row,1));
	m_SegmentendLC=atof(m_grid.GetTextMatrix(row,2));
	
	 
	strSql.Format("DELETE   from  zdmSegmentGeoFeature where ���q�_�l���{=%.3f \
		AND ���q���I���{=%.3f AND�@��צW��='%s'",\
		m_SegmentstartLC,m_SegmentendLC,\
		myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename); 
	hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 
	
	if(!SUCCEEDED(hr))
	{
		MessageBox("�R������!","�R���ƾ�",MB_ICONSTOP);
		return;
	}	
	LoadData();
	MessageBox("�R�����\","�R���ƾ�",MB_ICONINFORMATION);
	
}

void CZdmGeoSegmentFeatures::OnButtonExit() 
{
	EndDialog(IDCANCEL);
}

void CZdmGeoSegmentFeatures::OnButtonEdit() 
{
	int row=m_grid.GetRow();
	if(m_TotalNums<1 || row<1 )
		return;
	
	CString tt,strSql;
	
	this->UpdateData();


	tt.Format("%.3f",m_SegmentstartLC);
	m_grid.SetTextMatrix(row,1,tt);
	
	tt.Format("%.3f",m_SegmentendLC);
	m_grid.SetTextMatrix(row,2,tt);
	
	m_grid.SetTextMatrix(row,3,m_geoFeature);
	
	if(CheckValid()==FALSE)
		return;
	
	strSql.Format("DELETE   from  zdmSegmentGeoFeature where \
		���q�_�l���{=%.3f AND ���q���I���{=%.3f AND ��צW��='%s'",\
		m_oldSegmentstartLC,m_oldSegmentendLC,\
		myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename); 
	hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 
	
	tt.Format("INSERT INTO zdmSegmentGeoFeature VALUES (%.3f,%.3f,'%s','%s')",\
		m_SegmentstartLC,m_SegmentendLC,m_geoFeature,\
		myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename);
	try
	{
		hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 
		if(!SUCCEEDED(hr))
		{
			MessageBox("�ק異��","�ק�ƾ�",MB_ICONSTOP);
			return;
		}
	}
	catch(_com_error& e)	
	{
		MessageBox("�ק異��!","�ק�ƾ�",MB_ICONSTOP);
	} 
	
	MessageBox("�ק令�\","�ק�ƾ�",MB_ICONINFORMATION);
	

}





















