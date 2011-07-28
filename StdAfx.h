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

//�[�J��OpenGL�Y��󪺤ޥ�
#include <gl/glew.h>   //OpenGL�X�i,�u�n�]�t�@��glew.h�Y���A�N��ϥ�gl,glu,glext,wgl,glx���������
#include <gl/glut.h>   //glut.h�n��bglew.h���᭱
#include <gl/glaux.h> //glaux.h�O���U�Y���

//�n���{�ǽեμƾǨ�Ʈw,�@�Ǽƾǭp�⪺�����������{�O��bmath.h�̪�,
//�ҥH�A�N�i�H�����Τ���,�Ӥ������߬O����{������
#include <math.h> //�ƾǨ�Ʈw�Y���

#include "SkinPPWTL.h"  //�ֽ����


//�[�Jaxftmp1.h�O�������ҪO(MFC�ҪO��)���Y���,�խY�b�{�Ǥ��Ψ�FCArray,
// CObList���ƾڵ��c��,����N�o�[���Ӥ��C
#include  <afxtempl.h> 


//�ޤJADO�w���A�H�ϽsĶ���ॿ�T�sĶ
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#include "icrsint.h"	
#include <adoid.h>		
#include <afxdb.h> 

#include "alCulateF.h"

//�[�J������ܶqtheApp�����ޥ�
#include "T3DSystem.h"
extern CT3DSystemApp theApp;

//�[�J��OCI�����ޥ�
#include <oci.h>   
#include "OCIclass.h"
extern COCIclass myOci;//�w�qOCI�������ܶq

//ADO�ƾڮw
extern _RecordsetPtr m_Recordset; 
extern variant_t RecordsAffected;
extern _variant_t Thevalue;  
extern _ConnectionPtr m_Connection;


#include "DesingScheme.h"
extern CDesingScheme myDesingScheme;

#include "GetDemInsertValue.h"
extern CGetDemInsertValue m_demInsert;

extern int m_currentSchemeIndexs;   

#include <mmsystem.h> //windows���P�h�C�馳�����j�h�Ʊ��f�A��s�W�v�p��Ϊ��ɶ��p���ơ]timeGetTime()�^�]�bmmsystem.h��

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
