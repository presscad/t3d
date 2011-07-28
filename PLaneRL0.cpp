// PLaneRL0.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "PLaneRL0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CPLaneRL0 dialog


CPLaneRL0::CPLaneRL0(CWnd* pParent /*=NULL*/)
	: CDialog(CPLaneRL0::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPLaneRL0)
	m_L0 = 0;
	m_minR = 0;
	m_minL0 = 0;
	m_strrangR = _T("");
	m_ID = _T("");
	//}}AFX_DATA_INIT
}


void CPLaneRL0::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPLaneRL0)
	DDX_Control(pDX, IDC_COMBO_R, m_CBRadius);
	DDX_Text(pDX, IDC_EDIT_L0, m_L0);
	DDX_Text(pDX, IDC_EDIT_MINR, m_minR);
	DDX_Text(pDX, IDC_EDIT_MINl0, m_minL0);
	DDX_Text(pDX, IDC_EDIT_RANGER, m_strrangR);
	DDX_Text(pDX, IDC_EDIT_ID, m_ID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPLaneRL0, CDialog)
	//{{AFX_MSG_MAP(CPLaneRL0)
	ON_CBN_SELCHANGE(IDC_COMBO_R, OnSelchangeComboR)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CPLaneRL0 message handlers


//初始化信息	
BOOL CPLaneRL0::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//根據項目的設計速度，計算可以選擇的曲線半徑和曲線半徑範圍
	switch(	myDesingScheme.SchemeDatass[m_currentSchemeIndexs].designspeed)
	{
	case 160: //設計速度為160Km/h
		m_strrangR="2500～5000";//曲線半徑範圍
		m_CBRadius.ResetContent();
		m_CBRadius.AddString("1600");
		m_CBRadius.AddString("1800");
		m_CBRadius.AddString("2000");
		m_CBRadius.AddString("2500");
		m_CBRadius.AddString("2800");
		m_CBRadius.AddString("3000");
		m_CBRadius.AddString("3500");
		m_CBRadius.AddString("4000");
		m_CBRadius.AddString("4500");
		m_CBRadius.AddString("5000");
		m_CBRadius.AddString("6000");
		m_CBRadius.AddString("7000");
		m_CBRadius.AddString("8000");
		m_CBRadius.AddString("10000");
		m_CBRadius.AddString("12000");
		m_CBRadius.SetCurSel(0); //設置索引
		break;
	case 140:  //設計速度為140Km/h
		m_strrangR="2000～4000";
		m_CBRadius.ResetContent();
		m_CBRadius.AddString("1200");
		m_CBRadius.AddString("1400");
		m_CBRadius.AddString("1600");
		m_CBRadius.AddString("1800");
		m_CBRadius.AddString("2000");
		m_CBRadius.AddString("2500");
		m_CBRadius.AddString("2800");
		m_CBRadius.AddString("3000");
		m_CBRadius.AddString("3500");
		m_CBRadius.AddString("4000");
		m_CBRadius.AddString("4500");
		m_CBRadius.AddString("5000");
		m_CBRadius.AddString("6000");
		m_CBRadius.AddString("7000");
		m_CBRadius.AddString("8000");
		m_CBRadius.AddString("10000");
		m_CBRadius.AddString("12000");
		m_CBRadius.SetCurSel(0);
		break;
	case 120: //設計速度為120Km/h
		m_strrangR="1600～3000";
		m_CBRadius.ResetContent();
		m_CBRadius.AddString("800");
		m_CBRadius.AddString("1000");
		m_CBRadius.AddString("1200");
		m_CBRadius.AddString("1400");
		m_CBRadius.AddString("1600");
		m_CBRadius.AddString("1800");
		m_CBRadius.AddString("2000");
		m_CBRadius.AddString("2500");
		m_CBRadius.AddString("2800");
		m_CBRadius.AddString("3000");
		m_CBRadius.AddString("3500");
		m_CBRadius.AddString("4000");
		m_CBRadius.AddString("4500");
		m_CBRadius.AddString("5000");
		m_CBRadius.AddString("6000");
		m_CBRadius.AddString("7000");
		m_CBRadius.AddString("8000");
		m_CBRadius.AddString("10000");
		m_CBRadius.AddString("12000");
		m_CBRadius.SetCurSel(0);	
		break;
	case 100: //設計速度為100Km/h
		m_strrangR="1200～2500";
		m_CBRadius.ResetContent();
		m_CBRadius.AddString("600");
		m_CBRadius.AddString("700");
		m_CBRadius.AddString("800");
		m_CBRadius.AddString("1000");
		m_CBRadius.AddString("1200");
		m_CBRadius.AddString("1400");
		m_CBRadius.AddString("1600");
		m_CBRadius.AddString("1800");
		m_CBRadius.AddString("2000");
		m_CBRadius.AddString("2500");
		m_CBRadius.AddString("2800");
		m_CBRadius.AddString("3000");
		m_CBRadius.AddString("3500");
		m_CBRadius.AddString("4000");
		m_CBRadius.AddString("4500");
		m_CBRadius.AddString("5000");
		m_CBRadius.AddString("6000");
		m_CBRadius.AddString("7000");
		m_CBRadius.AddString("8000");
		m_CBRadius.AddString("10000");
		m_CBRadius.AddString("12000");
		break;
	case 80:  //設計速度為80Km/h
		m_strrangR="800～2000";
		m_CBRadius.ResetContent();
		m_CBRadius.AddString("550");
		m_CBRadius.AddString("600");
		m_CBRadius.AddString("700");
		m_CBRadius.AddString("800");
		m_CBRadius.AddString("1000");
		m_CBRadius.AddString("1200");
		m_CBRadius.AddString("1400");
		m_CBRadius.AddString("1600");
		m_CBRadius.AddString("1800");
		m_CBRadius.AddString("2000");
		m_CBRadius.AddString("2500");
		m_CBRadius.AddString("2800");
		m_CBRadius.AddString("3000");
		m_CBRadius.AddString("3500");
		m_CBRadius.AddString("4000");
		m_CBRadius.AddString("4500");
		m_CBRadius.AddString("5000");
		m_CBRadius.AddString("6000");
		m_CBRadius.AddString("7000");
		m_CBRadius.AddString("8000");
		m_CBRadius.AddString("10000");
		m_CBRadius.AddString("12000");
		break;
	}
 
	//根據選擇的曲線半徑,設置索引
	CString tt;
	m_minR=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].minRadius;
	for(int i=0;i<m_CBRadius.GetCount();i++)
	{
		m_CBRadius.GetLBText(i,tt);
		float mR=atof(tt);
		if(mR==m_minR)
		{
			m_CBRadius.SetCurSel(i);
			break; //退出
		}
	}

	m_L0=m_minL0;
	this->UpdateData(FALSE); //數據更新
	OnSelchangeComboR(); //當改變曲線半徑時,計算緩和曲線長
	
	
	return TRUE;  
}

//當改變曲線半徑時,計算緩和曲線長
void CPLaneRL0::OnSelchangeComboR() 
{
	this->UpdateData();

	CString tt;

	switch(	myDesingScheme.SchemeDatass[m_currentSchemeIndexs].designspeed)
	{
		case 160: //設計速度為160Km/h
			m_L0=myDesingScheme.m_minPriorityR160_L0[14-m_CBRadius.GetCurSel()];
			break;
		case 140: //設計速度為140Km/h
			m_L0=myDesingScheme.m_minPriorityR140_L0[16-m_CBRadius.GetCurSel()];
			break;
		case 120:  //設計速度為120Km/h
			m_L0=myDesingScheme.m_minPriorityR120_L0[18-m_CBRadius.GetCurSel()];
			break;
	}

	m_minL0=myDesingScheme.GetMinL0(m_CBRadius.GetCurSel()); //最小緩和曲線長
	this->UpdateData(FALSE); //數據更新
}


//確定
void CPLaneRL0::OnOK() 
{
	this->UpdateData(); //更新數據
	CString tt;
	
	if(m_ID.IsEmpty()) //如果交點ID為空
	{
		MessageBox("交點編號不能為空!","交點編號檢查",MB_ICONSTOP);
		return;
	}

	m_CBRadius.GetLBText(m_CBRadius.GetCurSel(),tt); //曲線半徑
	R=atoi(tt);
	if(R<m_minR) //如果曲線半徑小於最小曲線半徑
	{
		MessageBox("曲線半徑小於最小曲線半徑!","曲線半徑檢查",MB_ICONSTOP);
		return;
	}
	if(m_L0<m_minL0)
	{
		MessageBox("緩和曲線長度小於最小緩和曲線長度!","緩和曲線長度檢查",MB_ICONSTOP);
		return;
	}

	CDialog::OnOK();
}





















