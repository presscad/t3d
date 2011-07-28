// SpaceSearchSet.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "SpaceSearchSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CSpaceSearchSet dialog


CSpaceSearchSet::CSpaceSearchSet(CWnd* pParent /*=NULL*/)
	: CDialog(CSpaceSearchSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpaceSearchSet)
	m_shizxLength = 5;
	m_shuzxHeight =20;
	//}}AFX_DATA_INIT
}


void CSpaceSearchSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpaceSearchSet)
	DDX_Control(pDX, IDC_COMBOL_WIDTH, m_combolWidth);
	DDX_Text(pDX, IDC_EDIT_SHIZXLENGTH, m_shizxLength);
	DDX_Text(pDX, IDC_EDIT_SHUZXHEIGHT, m_shuzxHeight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpaceSearchSet, CDialog)
	//{{AFX_MSG_MAP(CSpaceSearchSet)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, OnButtonColor)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CSpaceSearchSet message handlers

// 顏色按鈕響應函數
void CSpaceSearchSet::OnButtonColor() 
{
	CColorDialog colorDlg;//定義顏色對話框變量
	if(colorDlg.DoModal()==IDOK)//如果顏色對話框打開成功
	{
		long m_color=colorDlg.GetColor();//得到所選擇的顏色
		pbrush.DeleteObject ();//刪除pbrush畫刷對像
		pbrush.CreateSolidBrush (m_color);//根據所選擇的顏色重新創建畫刷
		CButton *pbutton=(CButton*)GetDlgItem(IDC_BUTTON_COLOR);
		CRect rect;
		pbutton->GetClientRect(rect);
		pbutton->InvalidateRect(rect,TRUE);//刷新顏色按鈕響,
		
		m_QueryColorR=GetRValue(m_color);//得到所選擇的顏色的紅色
		m_QueryColorG=GetGValue(m_color);//得到所選擇的顏色的綠色
		m_QueryColorB=GetBValue(m_color);//得到所選擇的顏色的藍色
	
	}		
}

//根據顏色按鈕選擇的顏色填充其背景
HBRUSH CSpaceSearchSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->GetDlgCtrlID()== IDC_BUTTON_COLOR)//如果控件ID=IDC_BUTTON_COLOR,用pbrush畫刷填按鈕背景
		return pbrush;
	else //否則,返回默認畫刷
		return hbr;
	
}

//信息初始化
BOOL CSpaceSearchSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	myedit[0].SubclassDlgItem(IDC_EDIT_SHIZXLENGTH,this);
//	myedit[1].SubclassDlgItem(IDC_EDIT_SHUZXHEIGHT,this);
		
	m_combolWidth.ResetContent();//存儲標誌線寬度的下拉框清空
	for(int i=1;i<=20;i++)//線寬最大寬度為20
	{
		CString tt;
		tt.Format("%d",i);
		m_combolWidth.AddString(tt);
	}

	//設置下拉框的當前選擇項
	if(m_QueryLineWidth>0)
		m_combolWidth.SetCurSel(m_QueryLineWidth-1);
	else
		m_combolWidth.SetCurSel(0);

	this->UpdateData(FALSE);//數據變量更新
	
	//根據標誌線顏色創建畫刷
	pbrush.CreateSolidBrush(RGB(m_QueryColorR,m_QueryColorG,m_QueryColorB));
	
	return TRUE;  
}

BOOL CSpaceSearchSet::PreTranslateMessage(MSG* pMsg) 
{
 
	if(pMsg->wParam == VK_RETURN)//如果按鈕是回車鍵
	{
		CDialog *pWnd=(CDialog*)GetParent();
		pWnd->NextDlgCtrl ();
		return FALSE;
	}	
	else
		return CDialog::PreTranslateMessage(pMsg);
}


//確定掃鈕響應函數
void CSpaceSearchSet::OnOK() 
{
	this->UpdateData();//更新數據
	CString tt;
	m_combolWidth.GetLBText(m_combolWidth.GetCurSel(),tt);//得到
	m_QueryLineWidth=m_combolWidth.GetCurSel();//得到標誌線寬度
	CDialog::OnOK();//以IDOK模式關閉退出對話框
}
