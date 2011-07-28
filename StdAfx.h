// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__BD8FF39F_D5C6_4316_A31B_EB7ED84348B4__INCLUDED_)
#define AFX_STDAFX_H__BD8FF39F_D5C6_4316_A31B_EB7ED84348B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//加入對OpenGL頭文件的引用
#include <gl/glew.h>   //OpenGL擴展,只要包含一個glew.h頭文件，就能使用gl,glu,glext,wgl,glx的全部函數
#include <gl/glut.h>   //glut.h要放在glew.h的後面
#include <gl/glaux.h> //glaux.h是輔助頭文件

//聲明程序調用數學函數庫,一些數學計算的公式的具體實現是放在math.h裡的,
//所以你就可以直接用公式,而不用關心是怎麼實現公式的
#include <math.h> //數學函數庫頭文件

#include "SkinPPWTL.h"  //皮膚文件


//加入axftmp1.h是收集類模板(MFC模板類)的頭文件,倘若在程序中用到了CArray,
// CObList等數據結構時,那麼就得加載該文件。
#include  <afxtempl.h> 


//引入ADO庫文件，以使編譯器能正確編譯
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#include "icrsint.h"	
#include <adoid.h>		
#include <afxdb.h> 

#include "alCulateF.h"

//加入對全局變量theApp的的引用
#include "T3DSystem.h"
extern CT3DSystemApp theApp;

//加入對OCI的的引用
#include <oci.h>   
#include "OCIclass.h"
extern COCIclass myOci;//定義OCI類全局變量

//ADO數據庫
extern _RecordsetPtr m_Recordset; 
extern variant_t RecordsAffected;
extern _variant_t Thevalue;  
extern _ConnectionPtr m_Connection;


#include "DesingScheme.h"
extern CDesingScheme myDesingScheme;

#include "GetDemInsertValue.h"
extern CGetDemInsertValue m_demInsert;

extern int m_currentSchemeIndexs;   

#include <mmsystem.h> //windows中與多媒體有關的大多數接口，刷新頻率計算用的時間計算函數（timeGetTime()）也在mmsystem.h中

extern CArray<int,int>m_SchemeGrade;   
extern CArray<CString,CString>m_SchemeNames;  
extern CString m_currentSchemeNames;   
extern CString m_PrecurrentSchemeNames;   


extern char g_sAppPath[512];
extern char g_sMediaPath[512];
extern UINT g_Texture[100];

void CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID);
void GetFilePath(char * filename);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BD8FF39F_D5C6_4316_A31B_EB7ED84348B4__INCLUDED_)
