// T3DSystem.h : main header file for the T3DSYSTEM application
//

#if !defined(AFX_T3DSYSTEM_H__69B8CF59_C9BD_4A0C_AE2E_29DA887EA781__INCLUDED_)
#define AFX_T3DSYSTEM_H__69B8CF59_C9BD_4A0C_AE2E_29DA887EA781__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemApp:
// See T3DSystem.cpp for the implementation of this class
//

class CT3DSystemApp : public CWinApp
{
public:
	
	float *m_DemHeight;
	
	int keynumber;
	int m_Drawmode;
	BOOL stereo;
	
	BOOL bLoadImage;//標識加載影像是否成功
	
	BOOL bLoginSucceed;

	_ConnectionPtr m_pConnection;
	_ConnectionPtr m_Dataconn;
	_RecordsetPtr m_pRecordset;
	
	CString	m_username;
	CString	m_servername;
	CString	m_userpassword;
	
	
	double m_TexturLeftDown_x,m_TexturLeftDown_y;
	double m_TexturRightUp_x,m_TexturRightUp_y;
	int m_ImagePyramidCount;
	float m_ImageResolution[10];
	
	
	
	int m_Rows,m_Cols;
	int m_Cell_xwidth,m_Cell_ywidth;
	
	int m_Dem_cols,m_Dem_Rows;		
	int m_Dem_xcell,m_Dem_ycell;	
	
    double m_DemLeftDown_x,m_DemLeftDown_y;//DEM左下角x,y坐標
    double m_DemRightUp_x,m_DemRightUp_y;//DEM右上角x,y坐標
	
    int m_Dem_BlockSize;//DEM數據分塊大小(如分塊大小為33×33,則DEM數據分塊大小=33,依次類推)
	int m_BlockRows,m_BlockCols;//DEM數據根據設置的分塊大小後所共分塊的總行數和總列數

	//DEM地形子塊的總寬度(即一個地形塊表示的空間距離,若分塊大小=33,//DEM在x方向上格網點間距=20,則DEM地形子塊寬度=20*32=640米)
	int m_Dem_BlockWidth;//DEM子塊總寬度
	float m_MaxZ_Height;//DEM中所有點最大高程
	float m_MinZ_Height;//DEM中所有點最小高程
	long m_DEM_IvalidValue;//DEM中無效高程值
	
	int Insertmethod_style;
	
	BOOL b_haveDeletScheme;
	

	
	CT3DSystemApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CT3DSystemApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CT3DSystemApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
		
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T3DSYSTEM_H__69B8CF59_C9BD_4A0C_AE2E_29DA887EA781__INCLUDED_)
