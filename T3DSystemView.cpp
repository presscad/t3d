// T3DSystemView.cpp : implementation of the CT3DSystemView class
//

#include "stdafx.h"
#include "T3DSystem.h"

#include "T3DSystemDoc.h"
#include "T3DSystemView.h"
#include "MainFrm.h"
#include "OpenProject.h"
#include "SpaceSearchSet.h"
#include "PLaneRL0.h"
#include "TunncelPropertySet.h"
#include "BridgeSet.h"
#include "TextureBP.h"
#include "TextureLJ.h"
#include "TextureQLHpm.h"
#include "TextureTunnel.h"
#include "TextureTunnelDm.h"
#include "ModelMangerQD.h"
#include "DXF.h"
#include "AviParameter.h"
#include "RecordPictureSpeed.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PAI 3.1415926       //�w�q�k�`�q
#define HDANGLE  52.706     //�w�q1���׵���h�֫�(1����=180/PAI)
#define PAI_D180  PAI/180   //�w�q1�׵���h�֩���(1��=PAI/180����)

char g_sMediaPath[512];
UINT g_Texture[100] = {0};

GLfloat LightAmbient  [] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse  [] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition [] = { 0.0f, 0.0f, 2.0f, 1.0f };

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemView

IMPLEMENT_DYNCREATE(CT3DSystemView ,  CView)

BEGIN_MESSAGE_MAP(CT3DSystemView ,  CView)
	//{{AFX_MSG_MAP(CT3DSystemView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_MENU_OPENPROJECT ,  OnMenuOpenproject)
	ON_COMMAND(ID_DRAWMODE_LINE ,  OnDrawmodeLine)
	ON_COMMAND(ID_DRAWMODE_RENDER ,  OnDrawmodeRender)
	ON_COMMAND(ID_DRAWMODE_TEXTURE ,  OnDrawmodeTexture)
	ON_COMMAND(ID_SPACEQUERY_SET ,  OnSpacequerySet)
	ON_COMMAND(ID_QUERY_COORDINATE ,  OnQueryCoordinate)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_QUERY_DISTENCE ,  OnQueryDistence)
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_STEREO, OnMenuStereo)
	ON_UPDATE_COMMAND_UI(ID_MENU_STEREO, OnUpdateMenuStereo)
	ON_COMMAND(ID_MENU_PROJECTTIONORTHO, OnMenuProjecttionortho)
	ON_UPDATE_COMMAND_UI(ID_MENU_PROJECTTIONORTHO, OnUpdateMenuProjecttionortho)
	ON_COMMAND(ID_ORTHO_ZOOMIN, OnOrthoZoomIn)
	ON_UPDATE_COMMAND_UI(ID_ORTHO_ZOOMIN, OnUpdateOnOrthoZoomIn)
	ON_COMMAND(ID_ORTHO_ZOOMOUT, OnOrthoZoomOut)
	ON_UPDATE_COMMAND_UI(ID_ORTHO_ZOOMOUT, OnUpdateOnOrthoZoomOut)
	ON_COMMAND(ID_ORTHO_PAN, OnOrthoPan)
	ON_UPDATE_COMMAND_UI(ID_ORTHO_PAN, OnUpdateOnOrthoPan)
	ON_COMMAND(ID_ORTHO_ZOOMORIGIN, OnOrthoZoomOrigin)
	ON_UPDATE_COMMAND_UI(ID_ORTHO_ZOOMORIGIN, OnUpdateOnOrthoZoomOrigin)
	ON_COMMAND(ID_ORTHO_ZOOWINDOW, OnOrthoZoomWindow)
	ON_UPDATE_COMMAND_UI(ID_ORTHO_ZOOWINDOW, OnUpdateOnOrthoZoomWindow)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_MENU_LINEDESIGN, OnMenuLinedesign)
	ON_UPDATE_COMMAND_UI(ID_MENU_LINEDESIGN, OnUpdateMenuLinedesign)
	ON_UPDATE_COMMAND_UI(ID_QUERY_COORDINATE, OnUpdateQueryCoordinate)
	ON_UPDATE_COMMAND_UI(ID_QUERY_DISTENCE, OnUpdateQueryDistence)
	ON_COMMAND(ID_MENU_LINESAVESCHEME, OnMenuLinesavescheme)
	ON_UPDATE_COMMAND_UI(ID_MENU_PERSPECTIVE, OnUpdateMenuPerspective)
	ON_COMMAND(ID_MENU_PERSPECTIVE, OnMenuPerspective)
	ON_COMMAND(ID_MENU_BUILD3DLINEMODLE, OnMenuBuild3dlinemodle)
	ON_COMMAND(ID_FLY_ROUTINSCHEMELINE, OnFlyRoutinschemeline)
	ON_WM_TIMER()
	ON_COMMAND(ID_FLY_STOP, OnFlyStop)
	ON_COMMAND(ID_MENU_TUNNELSET, OnMenuTunnelset)
	ON_COMMAND(ID_MENU_BRIDGESET, OnMenuBridgeset)
	ON_COMMAND(ID_MENU_TEXTUREBP, OnMenuTexturebp)
	ON_COMMAND(ID_MENU_TEXTURELJ, OnMenuTexturelj)
	ON_COMMAND(ID_MENU_TEXTUREQLHPM, OnMenuTextureqlhpm)
	ON_COMMAND(ID_MENU_TEXTURETUNNEL, OnMenuTexturetunnel)
	ON_COMMAND(ID_MENU_TEXTURETUNNEL_DM, OnMenuTexturetunnelDm)
	ON_COMMAND(ID_PATH_MANUINPUT, OnPathManuinput)
	ON_COMMAND(ID_FLYPATH_SAVE, OnFlypathSave)
	ON_COMMAND(ID_FLPPATH_INTERPOLATION, OnFlppathInterpolation)
	ON_COMMAND(ID_FLY_OPENPATH, OnFlyOpenpath)
	ON_COMMAND(ID_FLY_ONOFFPATH, OnFlyOnoffpath)
	ON_UPDATE_COMMAND_UI(ID_FLY_ONOFFPATH, OnUpdateFlyOnoffpath)
	ON_COMMAND(ID_FLY_STATICHEIGHT, OnFlyStaticheight)
	ON_UPDATE_COMMAND_UI(ID_FLY_STATICHEIGHT, OnUpdateFlyStaticheight)
	ON_COMMAND(ID_FLY_ROUTINEHEIGHT, OnFlyRoutineheight)
	ON_UPDATE_COMMAND_UI(ID_FLY_ROUTINEHEIGHT, OnUpdateFlyRoutineheight)
	ON_COMMAND(ID_FLY_PLAYPAUSE, OnFlyPlaypause)
	ON_UPDATE_COMMAND_UI(ID_FLY_PLAYPAUSE, OnUpdateFlyPlaypause)
	ON_COMMAND(ID_FLY_ONESTEP, OnFlyOnestep)
	ON_COMMAND(ID_FLY_VIEW_ENLARGE, OnFlyViewEnlarge)
	ON_COMMAND(ID_FLY_VIEW_SMALL, OnFlyViewSmall)
	ON_COMMAND(ID_FLY_HEIGHT_UP, OnFlyHeightUp)
	ON_COMMAND(ID_FLY_HEIGHT_DOWN, OnFlyHeightDown)
	ON_COMMAND(ID_FLY_VIEW_DOWN, OnFlyViewDown)
	ON_COMMAND(ID_FLY_VIEW_UP, OnFlyViewUp)
	ON_COMMAND(ID_FLY_SPEED_UP, OnFlySpeedUp)
	ON_COMMAND(ID_FLY_SPEED_DOWN, OnFlySpeedDown)
	ON_COMMAND(ID_MENU_MODLEQD, OnMenuModleqd)
	ON_COMMAND(ID_MENU_OUPTCAD3DLINEMODEL, OnMenuOuptcad3dlinemodel)
	ON_COMMAND(ID_AVI_PARAMETER, OnAviParameter)
	ON_COMMAND(ID_AVI_START, OnAviStart)
	ON_COMMAND(ID_AVI_PAUSE, OnAviPause)
	ON_COMMAND(ID_AVI_END, OnAviEnd)
	ON_COMMAND(ID_SAVEPICTURE_SPEED, OnSavepictureSpeed)
	ON_COMMAND(ID_SAVEPICTURE_CONTINUE, OnSavepictureContinue)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_SAVEPICTURE_STOP, OnSavepictureStop)
	ON_COMMAND(ID_MENU_SAVESCREENTOBMP, OnMenuSavescreentobmp)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT ,  CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT ,  CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW ,  CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemView construction/destruction

PBlockTriInfos tempBlockTriInfos;

class GetBlockTriangles
{
public:
	GetBlockTriangles(long blockIndex) : MyblockIndex(blockIndex){}
	void operator()(const triangle& tri) const
	{
		
		const vertex * v0 = tri.GetVertex(0);
		const vertex * v1 = tri.GetVertex(1);
		const vertex * v2 = tri.GetVertex(2);
		
		
		PTriPt tempptript=new TriPt;
		tempptript->Pt1.x=v0->GetX(); tempptript->Pt1.y=v0->GetY();	tempptript->Pt1.z=v0->GetZ();
		tempptript->Pt2.x=v1->GetX(); tempptript->Pt2.y=v1->GetY();	tempptript->Pt2.z=v1->GetZ();
		tempptript->Pt3.x=v2->GetX(); tempptript->Pt3.y=v2->GetY();	tempptript->Pt3.z=v2->GetZ();
		tempBlockTriInfos->TriPts.Add(tempptript);
		
		
		
		
	}
protected:
	long MyblockIndex;
};


CT3DSystemView::CT3DSystemView()
{
	Init_data() ; // ��l�Ƭ����ܶq
	m_lpThread  = NULL;
	
}

CT3DSystemView::~CT3DSystemView()
{
}

BOOL CT3DSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	//�]�m���f����
	cs.style|=WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	return CView::PreCreateWindow(cs);
	
}

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemView drawing

//ø�s�T������
void CT3DSystemView::OnDraw(CDC* pDC)
{
	CT3DSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
//	m_snows.DrawSnow ();
//	return;

	if (pDC->IsPrinting()) 
	{
		CRect rcDIB;
		GetClientRect(&rcDIB);
		
		m_rcPrintRect=rcDIB;
		
		pDC->DPtoLP(&rcDIB);
		
		rcDIB.right = rcDIB.Width();
		rcDIB.bottom = rcDIB.Height();
		
		// ��o���L�������ؤo(����)
		int cxPage = pDC->GetDeviceCaps(HORZRES);
		int cyPage = pDC->GetDeviceCaps(VERTRES);
		// ��o���L���C�^�T�W�������Ӽ�
		int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
		int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);
		
		CRect rcDest;
		rcDest.top = rcDest.left = 0;
		rcDest.bottom = (int)(((double)rcDIB.Height() * cxPage * cyInch)
			/ ((double)rcDIB.Width() * cxInch));
		rcDest.right = cxPage;
		CapturedImage.OnDraw(pDC->m_hDC, &rcDest, &rcDIB);
	}
	else 
	{
		wglMakeCurrent( pDC->m_hDC, m_hRC );// �� RC �P��e DC �����p
		DrawScene() ; // ����ø�s
		if (m_movieCapture != NULL && m_Recording)
		{
			m_movieCapture->captureFrame();
		}
		glFlush();	
		::SwapBuffers(m_pDC->GetSafeHdc());	//�洫�w�İ�	 
	}
	

}

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemView printing

BOOL CT3DSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CT3DSystemView::OnBeginPrinting(CDC* /*pDC*/ ,  CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CT3DSystemView::OnEndPrinting(CDC* /*pDC*/ ,  CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemView diagnostics

#ifdef _DEBUG
void CT3DSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CT3DSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CT3DSystemDoc* CT3DSystemView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CT3DSystemDoc)));
	return (CT3DSystemDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemView message handlers

int CT3DSystemView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//����Ȥ�Ϫ��]�ƴy�z��
	m_pDC=new CClientDC(this); 

	//��l��OpenGL
	InitializeOpenGL(m_pDC); 
	InitList() ; // ��l����ܦC��	
	
	return 0; 

}

BOOL CT3DSystemView::InitializeOpenGL(CDC *pDC)
{
	//�i��opengl����l�Ƥu�@
	m_pDC=pDC; 
	//������DC���H���榡�վ㬰���w���榡�A�H�K�᭱��DC���ϥ�
	SetupPixelFormat(); 
	//�ھ�DC�ӳЫ�RC
	m_hRC=::wglCreateContext(m_pDC->GetSafeHdc()); 
	//�]�m��e��RC�A�H�᪺�e�Ͼާ@���e�bm_pDC���V��DC�W
	::wglMakeCurrent(m_pDC->GetSafeHdc() , m_hRC); 
	

	//�P�_��e�t�Ϊ�OpenGL�����O�_����h�����z�X�i  �P�_��d�O�_������X�i
	glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)		wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)		wglGetProcAddress("glMultiTexCoord2fARB");
	
	if(!glActiveTextureARB || !glMultiTexCoord2fARB)
	{
		MessageBox("��eOpenGL�������C�A������h�����z\n�X�i�\��A�ФU���w�˷s�������I" ,  "�h�����z�X�i���~" ,  MB_ICONSTOP);
		return FALSE;
	}

	m_cTxtSky.LoadGLTextures("Sky.bmp");	//�[���I���ѪŪ����z�v��

	m_cTxtureBP.LoadGLTextures("���z\\��Y���@\\�����@�Y1.bmp");
	m_cTxtureLJ.LoadGLTextures("���z\\����\\1.bmp");
	m_cTxtureGdToLJ.LoadGLTextures("���z\\����\\10.bmp");
	m_cTxtureSuigou.LoadGLTextures("���z\\����\\����1.bmp");
	m_cTxturePT.LoadGLTextures("���z\\��Y���x\\��Y���x1.bmp");
	m_cTxtureRailway.LoadGLTextures("���z\\�K��\\�K��1.bmp");
	m_cBridgeHpm.LoadGLTextures("���z\\���U���@�Y��\\1.bmp");//���Y�U���@�Y�����z
	m_cTunnel.LoadGLTextures("���z\\�G�D����\\1.bmp"); //�G�D���𯾲z
	m_cTunnel_dm.LoadGLTextures("���z\\�G�D�}��\\2.bmp");//�G�D�}�����z
	m_cTunnel_dmwcBp.LoadGLTextures("���z\\�G�D�}���~����Y\\2.bmp");//�G�D�}���~����Y*/

	
	return TRUE;

	

}

BOOL CT3DSystemView::SetupPixelFormat()
{
	//��l�ƶH���榡�H�ο���X�A���榡�ӳЫ�RC
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR) ,  // pfd���c���j�p 
			1 ,  // ������
			PFD_DRAW_TO_WINDOW | // ����b���f��ø�� 
			PFD_SUPPORT_OPENGL | // ��� OpenGL 
			PFD_DOUBLEBUFFER| // ���w�s�Ҧ�
			PFD_STEREO |  //�������Ҧ�
			PFD_TYPE_RGBA ,  // RGBA �C��Ҧ� 
			24 ,  // 24 ���C��`��
			0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  // �����C��� 
			0 ,  // �S���D�z���׽w�s 
			0 ,  // ��������� 
			0 ,  // �L�֥[�w�s 
			0 ,  0 ,  0 ,  0 ,  // �����֥[�� 
			32 ,  // 32 ��`�׽w�s 
			0 ,  // �L�ҪO�w�s 
			0 ,  // �L���U�w�s 
			PFD_MAIN_PLANE ,  // �D�h 
			0 ,  // �O�d 
			0 ,  0 ,  0 // �����h , �i���ʩM�l������ 
	}; 
	//�bDC����ܦX�A���H���榡�ê�^���޸�
	int pixelformat;
	pixelformat=::ChoosePixelFormat(m_pDC->GetSafeHdc() , &pfd);
	if (pixelformat==0)
	{
		MessageBox("��ܹ����榡����!" , "�]�m�����榡" , MB_ICONERROR);
		return FALSE;
	}
	//�]�m���w�H���榡
	if (::SetPixelFormat(m_pDC->GetSafeHdc() , pixelformat , &pfd)==FALSE)
	{
		MessageBox("�]�m�����榡����!" , "�]�m�����榡" , MB_ICONERROR);
		return FALSE;
	}

	

	//���շ�e�]�m�M�w����d�O�_�������Ҧ�
	unsigned char ucTest;
    glGetBooleanv (GL_STEREO ,  &ucTest);  
    if (!ucTest) 
	{
		return 1;
	}
	
	
	if((pfd.dwFlags & PFD_STEREO)==0)
		bStereoAvailable=FALSE ; // ��d���������Ҧ�
	else
		bStereoAvailable=TRUE;
	
	CString stt[5];
	if(bStereoAvailable==FALSE) //�p�G��d���������Ҧ��A���X�i�઺���~��]
	{
		stt[0]="��.�ϧΥd���������w��;\n";
		stt[1]="��.�ϧΥd�X�ʵ{�Ǥ��������w��;\n";
		stt[2]="��.�u���b�S�w���ѪR�שΨ�s�v�]�m�U , �~�i�H�������w��;\n";
		stt[3]="��.����w�Ļݭn�S�w���X�ʰt�m�H�E��;";
		stt[4].Format("����Ҧ����Q����.�i�঳�H�U��]:\n%s%s%s%s" , stt[0] , stt[1] , stt[2] , stt[3]);
		MessageBox(stt[4] , "����Ҧ��]�m" , MB_ICONINFORMATION);
	}
	
	
}

void CT3DSystemView::OnSize(UINT nType ,  int cx ,  int cy) 
{
	CView::OnSize(nType ,  cx ,  cy);


	if(cy>0)
	{
		WinViewX = cx ; // ���f�e��
		WinViewY = cy ; // ���f����
		glViewport(0 , 0 , cx , cy); //�]�m���f�j�p
        m_aspectRatio = (float)cx/(float)cy ; // ���f�����a���
		glMatrixMode(GL_PROJECTION); //�N��e�x�}�]�m����v�x�},������e�x�}��GL_PROJECTION 
		glLoadIdentity();    //�N��e�x�}�m�������}        
		gluPerspective(50.0 + m_ViewWideNarrow , m_aspectRatio , m_near , m_far);		//:fovy=50.0 + m_ViewWideNarrow , �O��������
		m_FrustumAngle=2*asin(0.5*m_aspectRatio*tan((50.0 + m_ViewWideNarrow)*PAI_D180))*HDANGLE;
		m_es=m_SCREEN_HEIGHT*cos(m_viewdegree*PAI_D180)/(2*tan(m_FrustumAngle/2.0*PAI_D180));
		glMatrixMode(GL_MODELVIEW);	//�N��e�x�}�]�m���ҫ��x�}		
		glLoadIdentity();	//�N��e�x�}�m�������} 
	}			
}

//�M���I��
BOOL CT3DSystemView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;	
}

//��l�Ƭ����ܶq
void CT3DSystemView::Init_data()
{
	m_ViewWideNarrow = 0.0f;	//��l������f�e���ܶq
	CWindowDC dc=NULL;
	m_SCREEN_WIDTH = ::GetDeviceCaps(dc , HORZRES);	//�̹��e��
	m_SCREEN_HEIGHT = ::GetDeviceCaps(dc , VERTRES);	//�̹�����
	m_near=1;	//�[���I�P�񰼰ŵ��������Z��
	m_far=5000 ; // �[���I�P�����ŵ��������Z��

	m_currebtPhramid=0 ; // ��e�v�����z��LOD�ŧO
	mTimeElaps=0 ; // �Ω�p��V�v���ɶ���
	
	m_stereo=FALSE; //��������Ҧ�
	m_Drawmode=3 ; // ø�s�Ҧ�(1://�u�ؼҦ�  2://��w�Ҧ�	3://���z�Ҧ�)
	
	
	m_bCamraInit=FALSE ; // �۾�����l��
    m_bLoadInitDemData=FALSE ; // �a�ΩM�v���ƾڥ��դJ 
	m_LodDemblockNumber=0 ; // �[���a�ζ��ƶq��l��0
	m_RenderDemblockNumber=0 ; // ��V�a�ζ��ƶq��l��0
	
	//�۾��ѼƦV�W�ڶq
	m_vUpVector.x=0; 
	m_vUpVector.y=1;
	m_vUpVector.z=0;
	
	
	m_viewdegree=0 ; // ��l�����W�q 
	m_viewHeight=m_oldviewHeight=10 ; // �۾���l����
	m_camraDistence=80 ; // ���إ���Ҧ��U�����k�۾���l���Z
	m_heighScale=1.0 ; // ���{�Y��Y��

	m_Radius=50000 ; // �]��y�b�|
	m_R=5500 ; // 
	m_r=3500 ; // 

	m_BhasInitOCI=FALSE;	//��lOCI����l��
	mTimeElaps=0 ; // �Ω�p��V�v���ɶ���
	
	m_maxHeight=-9999 ; // ��l�̤j���{
	m_minHeight=9999 ; // ��l�̤p���{

	//DE�]�γ̤j���{�M�̤p���{�������C���l��
	minZ_color_R=0;minZ_color_G=1;minZ_color_B=0 ; // ���
	maxZ_color_R=1;maxZ_color_G=0;maxZ_color_B=0 ; // ����
	
// 	m_bShowbreviary=TRUE ; // �O�_����Y����

	m_shizxLength=20 ; // �d�߼лx�Q�r�u����
	m_shuzxHeight=45 ; // �d�߼лx�ݪ��u����
	m_QueryLineWidth=1 ; // �d�߼лx�u���e��
	m_QueryColorR=255 ; // �d�߼лx�u���C��(��)
	m_QueryColorG=255 ; // �d�߼лx�u���C��(��)
	m_QueryColorB=0 ; // �d�߼лx�u���C��(��)
	m_bSearchDistencePtNums=0;

	Derx=0;	//�۾��bX��V�W����l�ܤƶq
	Derz=0;	//�۾��bZ��V�W����l�ܤƶq
	m_Step_X=5.0;	//�۾��bX��V���ʪ��B����l��(���б���)
	m_Step_Z=5.0;	//�۾��bZ��V���ʪ��B����l��(���б���)
	m_xTrans=0;	//�bX��V�W���ʪ��B��(��L����)
	m_zTrans=0;	//�bZ��V�W���ʪ��B��(��L����)

	m_OrthoViewSize=0.3;//���g��v�Ҧ��U������j�p
	m_OrthotranslateX=m_OrthotranslateY=0;//���g��vX�b��V�MY�b��V���ʪ��Z�����

	m_ViewType=GIS_VIEW_PERSPECTIVE;

	b_haveMadeRail3DwayList=FALSE; //�O�_�w�g���T���u����ܦC��(�z����v�Ҧ��U)
	b_haveMadeRail3DwayList_Ortho=FALSE;//�O�_�w�g���T���u����ܦC��(���g��v�Ҧ��U)
	b_haveTerrainZoomroadList=FALSE; //�u���T���ؼҫ�O�_�إߤF�a��TIN�ҫ�����ܦC��

	//��l����T�w�����ܶq
	m_StaticHeight = 80.0f;
	
	//��l������f�W�U���ܶq
	m_ViewUpDown = 0.0f;
	
	//��l������f�e���ܶq
	m_ViewWideNarrow = 0.0f;
	
	m_flyspeed=10;//����t��
	
	
	m_PreZooomLC=m_CurZooomLC=0;//���C�ɫe�@���{�M��e���{

	b_haveGetRegion=FALSE;//���ѬO�_�إ߽u���ʳ��ϰ�
	
	
	m_bridgeColorR=0; //��������C��
	m_bridgeColorG=0;//��������C
	m_bridgeColorB=255;//��������C
	m_Bridge.m_Bridge_HLHeight=2.0; //���������
	m_Bridge.m_Bridge_HLSpace=10;//����������Z
	m_Bridge.m_Bridge_HLWidth=3.0;//��������e��
    m_Bridge.m_Bridge_QDSpace=40;//���[���Z
	m_Bridge.m_Bridge_HPangle=45;//���Y�@�Y�ɨ�
	m_3DSfilename_QD=".\\�ҫ�\\���ټ[�x\\��[���X�ʼ[\\�ҫ����.3DS";
	
	
	m_Railway.m_Railway_width=2.5;//�����_���`�e��
	m_Railway.m_Lj_width=0.8;//���Ӽe��
	m_Railway.m_GuiMianToLujianWidth=0.6;//��Ӧ���}������
	m_Railway.m_Lj_Dh=m_Railway.m_GuiMianToLujianWidth*(1/1.75);//�K�y����Ӫ��Z��
	m_Railway.m_TieGui_width=1.435;//�K�y���Z
	
	m_Tunnel.height=6.55; //�G�D�`����
	m_Tunnel.Archeight=2;//�G�D�꩷����
	m_Tunnel.WallHeight=m_Tunnel.height-m_Tunnel.Archeight;////�G�D���𰪫�
	m_Tunnel.ArcSegmentNumber=20;//�G�D�꩷���q��
	m_Tunnel.H=1.5;//�G�D�꩷���ݦA�V�W������(m_Tunnel.height+m_Tunnel.H=�G�D�}���`����)
	m_Tunnel.L=4.0;//�G�D�}�����ݥ��k�ⰼ�������e�� 
	m_Tunnel.width=m_Railway.m_Railway_width+2*(m_Railway.m_Lj_width+m_Railway.m_GuiMianToLujianWidth);
	
	
	m_shizxLength=20;
	m_shuzxHeight=45;

	m_NorthPtangle=90;//���_�w��l���V����(90��,�Y��ܥ��_��V,�b�T���Ŷ����h���VZ���t��V,�Y���V�̹��̭�)
	
	m_bShowbreviary=TRUE;//����Y������

	m_PathFlag=FALSE;//�O�_���\���}������|
	m_FlyPause=FALSE;//���ѬO�_�Ȱ�����
	
	
	m_3DSfilename_QD=".\\�ҫ�\\���ټ[�x\\��[���X�ʼ[\\�ҫ����.3DS";
	
	
	DeleteFile("c:\\TEMP.AVI"); //�R��c:\\TEMP.AVI���
    m_AviFilename="c:\\TEMP.AVI"; //AVI�ʵe��l���W
	m_AVIFrame=15; //AVI�W�v
	m_Recording=false; //���ѬO�_���b�������W�ʵe
	
	m_RecordPicture=FALSE;     //�����Ϲ��ǦC���лx	
    m_recordPictSpeed=100;	//���s�Ϲ����V�v
	m_PictureNumbers=0; //���s�Ϲ��ƶq
	
}

//�a�Τl���M�v���l�����դJ
BOOL CT3DSystemView::LoadInitDemData()
{
	if(theApp.bLoadImage==FALSE)//�p�G�v���[������ , ��^ 
        return FALSE;

	if(theApp.bLoginSucceed==FALSE) //�p�G�ƾڮw�s������ , ��^
		return FALSE;
	if(m_bLoadInitDemData==TRUE)	//�p�G��l�a�ΩM�v���l���w�դJ���\ , ��^
		return TRUE;

	if(theApp.m_BlockCols<=0 || theApp.m_BlockRows<=0) //�p�G�a�ζ����`��Ʃ��`�C��<=0 , ��^
		return FALSE;
	else  //���s�w�q�G���Ʋ�m_DemLod_My���j�p , �ì�����t���s
		m_AllocUnAlloc2D3D.Alloc2D_int(m_DemLod_My , theApp.m_BlockCols*theApp.m_BlockRows+1 , 3);
	
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	
	//�b���g��v�Ҧ��U�a�Ϊ�x , y���ߧ��ЩMx , y��V�����
	m_ortho_CordinateOriginX=0.5;
	m_ortho_CordinateXYScale=(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);
	m_ortho_CordinateOriginY=m_ortho_CordinateOriginX*m_ortho_CordinateXYScale;
	
	double m_Sphere_x , m_Sphere_y;
	m_Sphere_x=(theApp.m_DemRightUp_x+theApp.m_DemLeftDown_x)/2.0 ; // �]��y����x����
	m_Sphere_y=(theApp.m_DemRightUp_y+theApp.m_DemLeftDown_y)/2.0 ; // �]��y����y����
	
	
	CString strsql;
	int mRowId , mColID;

	//���}�ƾڮw��dem_block
	strsql="select *  from  dem_block order by �渹 , �C��";
	if(m_Recordset->State)	//�p�Gm_Recordset�w���}
		m_Recordset->Close() ; // ����
	try
	{
		m_Recordset->Open(_bstr_t(strsql) , (IDispatch*)(theApp.m_pConnection) , adOpenDynamic , adLockOptimistic , adCmdText);    
	}
	catch(_com_error& e)	//���~�B�z		
	{
		CString errormessage;
		errormessage.Format("���}�ƾڮw����!\r\n���~�H��:%s" , e.ErrorMessage());
		AfxMessageBox(errormessage , MB_ICONSTOP , 0);
		m_Recordset->Close() ; // �����O����
		return FALSE ; // ��^
	} 
	
	long mcount;
    m_LodDemblockNumber=0 ; // �[���a�ζ��ƶq
	
	while(!m_Recordset->adoEOF)//�p�G�S����ƾڮw��
	{
		
		Thevalue = m_Recordset->GetCollect("���ߧ���X"); 
		double m_demblock_centerx=(double)Thevalue ;	//�o��DEM�l������x����
		
		Thevalue = m_Recordset->GetCollect("���ߧ���Y"); 
		double m_demblock_centery=(double)Thevalue;	//�o��DEM�l������y����
		
		//�p��DEM�l�����߻P�]��y���߶Z��
		double distence=sqrt((m_Sphere_x-m_demblock_centerx)*(m_Sphere_x-m_demblock_centerx)+
			(m_Sphere_y-m_demblock_centery)*(m_Sphere_y-m_demblock_centery));

		if(distence<m_Radius)//�p�GDEM�l�����߻P�]��y���߶Z��<�]�m���]��y�b�| , �h�[���Ӧa�Τl��
		{
			Thevalue = m_Recordset->GetCollect("�渹"); 
			mRowId=(long)Thevalue;
			
			Thevalue = m_Recordset->GetCollect("�C��"); 
			mColID=(long)Thevalue;
			//�s�x�ҥ[�����a�ζ����ߤj�ax , y����
			m_DemBlockCenterCoord[m_LodDemblockNumber][0]=m_demblock_centerx-theApp.m_DemLeftDown_x;
			m_DemBlockCenterCoord[m_LodDemblockNumber][1]=-(m_demblock_centery-theApp.m_DemLeftDown_y);
			
			m_lodDemBlock[m_LodDemblockNumber][0]=mRowId ; // �դJ���a�ζ����渹
			m_lodDemBlock[m_LodDemblockNumber][1]=mColID ; // �դJ���a�ζ����C��
			m_lodDemBlock[m_LodDemblockNumber][2]=m_LodDemblockNumber ; // �դJ���a�ζ��ƶq
			
			mcount=(mRowId-1)*theApp.m_BlockCols+mColID ; // �p��դJ���a�ζ��b�Ҧ�DEM�ƾڶ���������
			m_DemLodIndex[m_LodDemblockNumber]=mcount ; // �O���դJ����m_LodDemblockNumber�a�Τl�������� 
			m_DemLod_My[mcount][0]=mRowId;	//�դJ���a�ζ����渹
			m_DemLod_My[mcount][1]=mColID;	//�դJ���a�ζ����C��
			m_DemLod_My[mcount][2]=m_LodDemblockNumber;	//�դJ���a�ζ��ƶq
			m_pbm_DemLod[mcount]=true;
			if(m_LodDemblockNumber==0)//�p�G�O�Ĥ@���դJ
			{
				m_loddem_StartRow=mRowId ; // �s�x�դJ���a�ζ����_�l�渹
				m_loddem_StartCol=mColID ; // �s�x�դJ���a�ζ����_�l�C��
			}
			m_LodDemblockNumber++; //�դJ�a�ζ��ƶq+1
		}

		if(mRowId>(theApp.m_BlockRows/2.0+m_Radius/theApp.m_Dem_BlockWidth) && mColID>(theApp.m_BlockCols/2.0+m_Radius/theApp.m_Dem_BlockWidth) && distence>m_Radius)
			break;
			m_Recordset->MoveNext() ; // 
	}
	m_Recordset->Close() ; // �����ƾڮw��

	m_loddem_EndRow=mRowId ; // �s�x�դJ���a�ζ��������渹
	m_loddem_EndCol=mColID ; // �s�x�դJ���a�ζ��������C��

    if(m_LodDemblockNumber<=0) //�p�G�[���a�ζ��ƶq<=0 , ��ܽդJ���� , ��^
		return FALSE ; // ��^
	

    m_tempDemLodIndex=new int[m_LodDemblockNumber];
	//���s�w�qbsign�Ʋդj�p(�Y�Ȭ�1,��ܽդJ���a�Τl���ѻPø�s,=0,��ܥ��ѻPø�s,�Q�簣���F)
	m_bsign=new int[m_LodDemblockNumber];
	
	CString strtempfile="c:\\tempdem.txt" ; // �{��ASCII��� , �Ω�s�x�q�ƾڮw��Ū����DEM�l���ƾ�
	ExporttotalDemToFIle(strtempfile);//�q�ƾڮw��Ū���Ҧ����{�ƾڨ�Ʋդ�,�O���F�ΨӤ������{�ɥΪ�	
	ReadHdata(strtempfile);//Ū��DEM�Ҧ������I������Ʋ�theApp.m_DemHeight[]��

	float iPer=100.0/m_LodDemblockNumber;
	for( int i=0;i<m_LodDemblockNumber;i++)
	{
		//�N��m_lodDemBlock[i][0]��M��m_lodDemBlock[i][1]�C���j�G�i��(BLOB)
		//DEM�ƾڱq�ƾڮw��Ū���üg�J�{��ASCII���
		ExportBlobDemToFIle(strtempfile , m_lodDemBlock[i][0] , m_lodDemBlock[i][1]);
		ReadDataFromFiles(strtempfile , i) ; // �q�{�ɪ�ASCII���Ū��DEM�ƾ��I�찪�{
	 	getDemBlockTexture(m_lodDemBlock[i][0] , m_lodDemBlock[i][1] , i) ; // Ū���å[������DEM�a�Τl�����v�����z
		strsql.Format("���b�[���a�λP�v�����z�ƾ� , �еy��... , �w����%.2f%s" , (i+1)*iPer , "%");
		pMainFrame->Set_BarText(4 , strsql , 0); 
	}
	pMainFrame->Set_BarText(4 , "�[���a�λP�v�����z�ƾڧ���!" , 0); 
	pMainFrame->Set_BarText(5 , " " , 60) ; // �[�������A�M�Ŷi�׫H���A�����öi�ױ�����
	m_bLoadInitDemData=TRUE ; // �ƾڥ[�����\

	double	mCx=(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x)/2.0 ; // ��l�۾����IX����(���a�Ϊ�����)
	double	mCz=-800 ; // ��l�۾����IZ����

	if(m_bCamraInit==FALSE)//�p�G�۾��S����l��
	{
		m_bCamraInit=TRUE ; // ���Ѭ۾���l��
		float mDis=100 ; // ���I�P�[���I��l�Z��

		//��l�Ƭ۾� , �ðO����U�Ѽ�
		PositionCamera(
			mCx , 
			m_viewHeight+m_maxHeight*m_heighScale*1.0 , 
			mCz , 
			mCx , 
			m_viewHeight+m_maxHeight*m_heighScale*1.0-mDis*tan(m_viewdegree*PAI_D180) , 
			mCz-mDis , 
			0 , 1 , 0);
		
		//�۾���l���I����
		m_originPosition=CVector3(mCx ,  m_viewHeight+m_maxHeight*m_heighScale*1.0 ,  mCz);
		//�۾���l�[���I����
		m_originView=CVector3(mCx , m_viewHeight+m_maxHeight*m_heighScale*1.0-mDis*tan(m_viewdegree*PAI_D180) , mCz-mDis);
			
	}
	
	return TRUE;
}

//Ū��DEM�Ҧ������I������Ʋ�theApp.m_DemHeight[]��
void CT3DSystemView::ReadHdata(CString strfilename)
{
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	long i,j;
	CString tt;
	float hh;	
	FILE *fp=fopen(strfilename,"r");//���}DEM���

	//Ū��DEM����Y�H��
	fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s\n",tt);

	//���s�w�q�����Ʋ�theApp.m_DemHeight[]���j�p,�ä��t���s
	theApp.m_DemHeight= new float[theApp.m_Dem_Rows*theApp.m_Dem_cols];
	float mPer=100.0/(theApp.m_Dem_Rows*theApp.m_Dem_cols);
	
	for (i=0;i<theApp.m_Dem_Rows;i++)
	{
		for (j=0;j<theApp.m_Dem_cols;j++)
		{
			fscanf(fp,"%f ",&hh);  //Ū�����{
			theApp.m_DemHeight[i*theApp.m_Dem_cols+j]=hh;
		}
		fscanf(fp,"\n");  
	}
	
	fclose(fp); //�������
	DeleteFile(strfilename); //�R���{�ɤ��
}

//�q�ƾڮw��Ū���Ҧ����{�ƾڨ�Ʋդ�,�O���F�ΨӤ������{�ɥΪ�
void CT3DSystemView::ExporttotalDemToFIle(CString strFilename)
{
	CString tt;
	int idcol=1;	
	tt.Format("SELECT DEM�ƾ� FROM DEM_INFO WHERE �s��= :%d FOR UPDATE",1);
	myOci.ReadBOLBDataFromDB(strFilename,tt,1);//�q�ƾڮw��Ū��DEM�ƾ�
}

//��l�Ƭ۾� , �ðO����U�Ѽ�
void CT3DSystemView::PositionCamera(double positionX ,  double positionY ,  double positionZ ,  double viewX ,  double viewY ,  double viewZ ,  double upVectorX ,  double upVectorY ,  double upVectorZ)
{
	CVector3 vPosition	= CVector3(positionX ,  positionY ,  positionZ);
	CVector3 vView		= CVector3(viewX ,  viewY ,  viewZ);
	CVector3 vUpVector	= CVector3(upVectorX ,  upVectorY ,  upVectorZ);
	
	
	m_vPosition = vPosition;	//���I����				
	m_vView     = vView;		//�[���I����		
	m_vUpVector = vUpVector;	//�V�W�ڶq����			
	m_oldvPosition=m_vPosition; //�O�s��e���I����
}

//�qDEM�ƾڪ�Ū����BLOB�G�i�DEM�ƾڡA�üg�J�{��ASCII�榡����󤤡A��{DEM�ƾ�Ū��
void CT3DSystemView::ExportBlobDemToFIle(CString strFilename ,  int RowIndex ,  int ColIndex)
{
	CString tt;
	int idcol=(RowIndex-1)*theApp.m_BlockCols+ColIndex;	
	tt.Format("SELECT DEM�ƾ� FROM dem_block WHERE �渹=%d AND �C��=%d AND �s��= :%d FOR UPDATE" , RowIndex , ColIndex , idcol);
	myOci.ReadBOLBDataFromDB(strFilename , tt , idcol) ; // �q�ƾڮw��Ū��BLOB�ƾ�
}

//�qASCII�榡�����Ū��DEM���{�I�ƾ� , �üg�J���{�Ʋդ�
void CT3DSystemView::ReadDataFromFiles(CString strfiles ,  int Index)
{
	float hh; 
	int i , j;
    int mCount=theApp.m_Dem_BlockSize ; // �a�Τl���j�p(�p�����j�p��33��33 , �h�a�Τl���j�p=33 , �̦�����)
    FILE *fp=fopen(strfiles , "r") ; // ���}���
	//�`��Ū��DEM�ƾ�
	for( i=0;i<mCount;i++)
	{
		for( j=0;j<mCount;j++)
		{
			fscanf(fp , "%f " , &hh);  
			
			m_pHeight_My[Index][i*mCount+j]=hh ; // �NDEM���{�ȼg�J�Ʋ�
			if(m_maxHeight<hh) m_maxHeight=hh; //�p��̤j���{��
			if(m_minHeight>hh && hh!=-9999) m_minHeight=hh ; // �p��̤p���{��
			
		}
	}
	fclose(fp) ; // �������
	DeleteFile(strfiles) ; // �R���{��ASCII���
}

//Ū���å[������DEM�a�Τl�����v�����z
void CT3DSystemView::getDemBlockTexture(int RowIndex ,  int ColIndex ,  int Index)
{
	CString strsql;
	int mID;
	_RecordsetPtr mRst;
	mRst.CreateInstance(_uuidof(Recordset));
		
	strsql.Format("select *  from TEXTURE WHERE �渹=%d AND �C��=%d  AND ���z���l��h��=%d" , RowIndex , ColIndex , m_currebtPhramid);
	try
	{
		//���}�ƾڮw��
		mRst->Open(_bstr_t(strsql) , (IDispatch*)(theApp.m_pConnection) , adOpenDynamic , adLockOptimistic , adCmdText);    
	}
	
	catch(_com_error& e)	//�X���B�z
	{
		CString errormessage;
		errormessage.Format("���}�ƾڮw����!\r\n���~�H��:%s" , e.ErrorMessage());
		MessageBox(errormessage , "Ū���v�����z" , MB_ICONSTOP);
		mRst->Close() ; // �����ƾڮw��
		return;
	} 
	
	if(mRst->adoEOF)	
	{
		mRst->Close() ; // �����ƾڮw��
		return;
	}
	
	//�o���Index�v�����z�������U�M�k�Wx , y����
	Thevalue = mRst->GetCollect("���U������X"); 
	m_Texturexy[Index][0]=(double)Thevalue;
	
	Thevalue = mRst->GetCollect("���U������Y"); 
	m_Texturexy[Index][1]=(double)Thevalue;
	
	Thevalue = mRst->GetCollect("�k�W������X"); 
	m_Texturexy[Index][2]=(double)Thevalue ;
	
	Thevalue = mRst->GetCollect("�k�W������Y"); 
	m_Texturexy[Index][3]=(double)Thevalue;
	
	Thevalue = mRst->GetCollect("�s��"); 
	mID=(long)Thevalue;
	
	mRst->Close() ; // �����ƾڮw��
	strsql.Format("C:\\%d_%d.bmp" , RowIndex , ColIndex) ; // �]�m�{�ɼv�����z���W
	if(ExportBlobTextureToFIle(strsql , RowIndex , ColIndex , mID)==TRUE)//�qoracle�ƾڮw��Ū��BLOB�������v�����z�ƾڨüg�J�{�ɼv�����z���
		m_demTextureID[Index]=m_texturesName.LoadGLTextures(_bstr_t(strsql)) ; // �s�x�դJ���v�����z�l�������zID , ���j�w���z
	DeleteFile(strsql) ; // �R���{�ɤ��

}

//��l�ƼƲթMOCI
void CT3DSystemView::Init_ArrayData()
{
	if(theApp.bLoadImage==FALSE) //�p�G�v�����z�[�����ѡA��^
        return ;
	
	if(theApp.bLoginSucceed==TRUE && m_BhasInitOCI==FALSE)//�p�G�ƾڥ[�����\�A��OCI����l��
	{
		m_nMapSize=theApp.m_Dem_BlockSize-1 ; // 
		int blocks=m_nMapSize/2;
		//���t�Ʋդ��s
		m_AllocUnAlloc2D3D.Alloc2D_float(m_pHeight_My , blocks*blocks , (m_nMapSize+1)*(m_nMapSize+1)) ; // �s�x�դJ�a�Τl�������{�I
		m_AllocUnAlloc2D3D.Alloc2D_bool(m_pbQuadMat , blocks*blocks , (m_nMapSize+1)*(m_nMapSize+1)) ; // ���Ѧa�Τl�����`�I�O�_�ٻݭn�~�����
		m_AllocUnAlloc2D3D.Alloc1D_bool(m_pbm_DemLod , theApp.m_BlockCols *theApp.m_BlockRows) ; // ���Ѧa�ζ��O�_�Q�դJ
		m_AllocUnAlloc2D3D.Alloc2D_int(m_DemLod_My , theApp.m_BlockCols*theApp.m_BlockRows+1 , 3) ; // �s�x�դJ�a�Τl�����渹 , �C�����H��
		if(m_BhasInitOCI==FALSE)//�p�GOCI�٥��Q��l��
		{
			myOci.Init_OCI(); //��l��OCI
			m_BhasInitOCI=TRUE ; // ���Ѭ�TRUE  
		}
	}
}

//�H����l�ƩM�[���a�� , �v���ƾ�
void CT3DSystemView::InitTerr()
{
	Init_ArrayData() ; // ��l�ƼƲթMOCI
	if(LoadInitDemData()==FALSE) //�p�G�ƾڥ[������ , ��^
		return ; // ��^
}


//�T���a��ø�s(�T���a�δ�V)
void CT3DSystemView::DrawTerrain()
{
	if(theApp.bLoginSucceed==FALSE || m_bLoadInitDemData==FALSE)
		return;
	
	//glShadeModel��ƥΨӳ]�m���v���ĪG�A�D�n��GL_SMOOTH�MGL_FLAT��خĪG�A
	//�䤤GL_SMOOTH���q�{�ȡA��ܥ��Ƴ��v�ĪG�F
	glShadeModel(GL_SMOOTH);

	glDisable(GL_TEXTURE_2D) ; // ����2D���z�M�g�\��
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // ���TEXTURE0���]�m�ؼ�
	glEnable(GL_TEXTURE_2D) ; // �E��TEXTURE0�椸

	glActiveTextureARB(GL_TEXTURE1_ARB) ; // ���TEXTURE1���]�m�ؼ�
	glEnable(GL_TEXTURE_2D) ; // �E��TEXTURE1�椸 , �ҥ�2D���z�M�g
	glTexEnvi(GL_TEXTURE_ENV ,  GL_TEXTURE_ENV_MODE ,  GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV ,  GL_RGB_SCALE_ARB ,  2);
	glMatrixMode(GL_TEXTURE); //�w�q�x�}���ҫ����z�x�}
	glLoadIdentity() ; // �N��e�x�}�m�������x�}
	glDisable(GL_TEXTURE_2D) ; // �������z�\��
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // ���TEXTURE0���]�m�ؼ�
	SetDrawMode() ; // 
	
	
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();            
	gluPerspective(50.0 + m_ViewWideNarrow , (float)WinViewX/(float)WinViewY , m_near , m_far);		
	
	glMatrixMode(GL_MODELVIEW); //�w�q�x�}���ҫ��ҫ��x�}
	glLoadIdentity(); //�N��e�x�}�m�������x�}       

/*
	glClearDepth��Ƴ]�m�`�׽w�İϪ��A�����t�q�N�bOpenGL���fø�s���ϧβ`�J��̹������{�סA
	�`�ת��N�q�N�O�b�T���Ŷ�����z���Ъ��ƭȡAz��0�ɪ�ܦb�����W�A�A�N�ݤ��쵡�f�����ϧΤF�A
	  �ҥH�t�ȶV�p�A�V�������f�����V�̡A�������f�����ϧ����ڭ��[��̪��Z���ܻ��F�F
*/
	glClearDepth(1.0f); //�]�m��l�Ʋ`�׽w�s��
	glEnable(GL_DEPTH_TEST); // �ҥβ`�״���
	glDepthFunc(GL_LESS); //�b�ե�glEnable(GL_DEPTH_TEST); �}�ҳo�ӥ\��H��A��`���ܤƤp���e�`�׭ȮɡA��s�`�׭ȡC

	
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		
	
	int nCount=0;


	if(this->m_stereo==TRUE) //�p�G�O���إ���Ҧ�
	{
		SetCamra(1); //�]�m�۾�
	}
	else	//�D����
	{
		SetCamra(0) ; // �]�m�۾�
	}

	glViewport(0 ,  0 ,  WinViewX ,  WinViewY); //�]�m���f�j�p�M��m
	
	if(b_haveGetRegion==TRUE && m_ifZoomonRoad==TRUE)//�p�G�u�u����׺��C
	{
		DrawTerrainZoomonRoad() ; // ø�s�a�λP�T���u���ҫ�
	}
	else //��ø�s�a��
	{
		if(theApp.bLoginSucceed==TRUE && m_bLoadInitDemData==TRUE)
		{
			//�p��V�v
			float currentTime1 = timeGetTime() * 0.001f;
			nCountFrame++;
			CalculateViewPortTriCord(m_vPosition.x , m_vPosition.z , m_vView.x , m_vView.z);
			
			//���Ʋ�m_pbQuadMat���t���s(LOD�`�I���Ϊ��лx)
			for(int j=0;j<m_LodDemblockNumber;j++)
			{
				memset(m_pbQuadMat[j] , 0 , m_nMapSize*m_nMapSize);
			}
		
			CalcFPS() ; // �p��V�v

			//�Ыئa����ܦC��
			glNewList(m_TerrainList , GL_COMPILE_AND_EXECUTE);
				m_RenderDemblockNumber=0 ; // ��V���a�ζ��ƶq
				View=m_vView-m_vPosition;
				for(int i=0;i<m_LodDemblockNumber;i++)
				{
					mCurrentTextID=i;
					m_CurrentDemArrayIndex=i;
					glBindTexture(GL_TEXTURE_2D ,  m_demTextureID[i]) ; // �j�w��i�a��l�������z
					m_lodDemBlock[i][3]=0 ; // ��l�Ȭ����ѻP��V
					//�p�G��e�a�ζ����b�����餺
					if(bnTriangle(m_triPtA[0] , m_triPtA[1] , m_triPtB[0] , m_triPtB[1] , m_triPtC[0] , m_triPtC[1] , m_DemBlockCenterCoord[i][0] , m_DemBlockCenterCoord[i][1])==FALSE)
						continue;
					m_RenderDemblockNumber++ ; // ��V���a�ζ��ƶq+1
					m_lodDemBlock[i][3]=1 ; // ��e�a�ζ��ѻP��V
                    //���e�a�ζ��i��LOD�|�e�����
					UpdateQuad(m_nMapSize/2 , m_nMapSize/2 , m_nMapSize/2 , 1 , m_lodDemBlock[i][0] , m_lodDemBlock[i][1]);
					//��VLOD�|�e����Ϋ᪺��e�a�ζ� , �íp��X��e��ø�s���T�����`�ƶq
					nCount+= RenderQuad(m_nMapSize/2 , m_nMapSize/2 , m_nMapSize/2 , m_lodDemBlock[i][0] , m_lodDemBlock[i][1]);	
				}

				if(m_checkt==TRUE)//�p�G�i����~�t���X����
				{
					if(nCount>=m_maxTrinum) //�p�G�T���μƶq�W�L�̤j�T�����`��
						m_lodScreenError=m_lodScreenError*m_k1; //�̹��~�t�n�W�j
					if(nCount<=m_minTrinum) //�p�G�T���μƶq�p��̤p�T�����`��
					m_lodScreenError=m_lodScreenError/m_k2 ; // �̹��~�t�n��p
				}

			glEndList(); //������ܦC��
			
			CString	strText;
			strText.Format("�i���s/��V���ơj=%d/%d" , m_LodDemblockNumber , m_RenderDemblockNumber);
	  		pMainFrame->Set_BarText(0 , strText , 0); //��ܤ��s���M��V���a�ζ��ƶq
			
			if(m_bShowbreviary==TRUE)//����Y������
			{
				glViewport(WinViewX*5/6 ,  WinViewY*5/6 , WinViewX/6 ,  WinViewY/6);
				glCallList(m_TerrainList) ; // �եΦa����ܦC�� , �b�s�����fø�s�T���a��
				glViewport(0 ,  0 ,  WinViewX ,  WinViewY) ; // ���s�]�m���f�j�p
				
			}

			
			float currentTime2 = timeGetTime() * 0.001f;
			mTimeElaps+=currentTime2-currentTime1;
			if(mTimeElaps>=1.0)//�p�G�⦸�ɶ����j>=1��
			{
				strText.Format("�W�v %d FPS" , nCountFrame);
				pMainFrame->Set_BarText(1 , strText , 0); //�b���A����ܾ��W���ø�s�V�v
				mTimeElaps=nCountFrame=0;
				
			}
		

			strText.Format("�T���� %d " , nCount);
			pMainFrame->Set_BarText(2 , strText , 0); //�b���A����ܾ��W��ܷ�e�V��ø�s���a�ΤT�����`��
		}
	}


	glActiveTextureARB(GL_TEXTURE1_ARB) ; // ���TEXTURE1���]�m�ؼ�
	glDisable(GL_TEXTURE_2D) ; // ����TEXTURE1���z�\��
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // ���TEXTURE0���]�m�ؼ�		
	glDisable(GL_TEXTURE_2D) ; // ����TEXTURE0���z�\��
	glDisable(GL_DEPTH_TEST) ; // �����`�׽w�İϴ��ե\��
}

//�p��V�v
void CT3DSystemView::CalcFPS()
{
	static DWORD dwStart = 0;
	static nCount = 0;
	nCount++;
	DWORD dwNow = ::GetTickCount();//��^�q�{�ǱҰʨ�{�b�Ҹg�L���@���
	
	if(dwNow-dwStart>=1000)//�C1��p��@���V�v
	{
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		CString strText;
		strText.Format("�W�v %d FPS " , nCount , 0);
		pMainFrame->Set_BarText(1 , strText , 0); //�b���A��W���ܾ��O��ܴV�v��
		dwStart = dwNow;
		nCount = 0;
	}
}

//�]�m�۾�
void CT3DSystemView::SetCamra(int mStyle)
{
	
		switch(mStyle)
		{
		case 0://�D���إ���Ҧ�
			gluLookAt(m_vPosition.x ,  m_vPosition.y ,  m_vPosition.z , 	
				m_vView.x , 	 m_vView.y ,      m_vView.z , 	
				m_vUpVector.x ,  m_vUpVector.y ,  m_vUpVector.z);
			break;
		case 1://���إ���Ҧ� , ���۾�
			gluLookAt(m_vPosition.x-m_camraDistence/2.0 ,  m_vPosition.y ,  m_vPosition.z , 	
				m_vView.x , 	 m_vView.y ,      m_vView.z , 	
				m_vUpVector.x ,  m_vUpVector.y ,  m_vUpVector.z);
			break;
		case 2://���إ���Ҧ� , �k�۾�
			gluLookAt(m_vPosition.x+m_camraDistence/2.0 ,  m_vPosition.y ,  m_vPosition.z , 	
				m_vView.x , 	 m_vView.y ,      m_vView.z , 	
				m_vUpVector.x ,  m_vUpVector.y ,  m_vUpVector.z);
		}
		
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		CString strText;
		float dy=m_vPosition.y-m_vView.y;
		float dz=fabs(m_vPosition.z-m_vView.z);
		if(theApp.bLoginSucceed==TRUE) 
		{
			if(fabs(dz)<=0.000001)
				m_viewdegree=0;
			else
				m_viewdegree=HDANGLE*atan(dy/dz);
		}
		
		//�b���A����ܾ��W��ܬ����H��
		strText.Format("�i�������jA=%.2f" , m_viewdegree);
		pMainFrame->Set_BarText(3 , strText , 0); 
		
		if(m_ifZoomonRoad==FALSE)//�D�u�u����׺��C , �_�h , ��ܷ�e���{
		{
			strText.Format("���I����:x=%.3f , y=%.3f , z=%.3f" , m_vPosition.x  , m_vPosition.y , fabs(m_vPosition.z));
			pMainFrame->Set_BarText(4 , strText , 0); 
		}
		
		if(m_ifZoomonRoad==FALSE)//�D�u�u����׺��C , �_�h , ��ܷ�e���{
		{
			strText.Format("�[���I����:x=%.3f , y=%.3f , z=%.3f" , m_vView.x  , m_vView.y , fabs(m_vView.z));
			pMainFrame->Set_BarText(5 , strText , 0); 
		}
		
}

//��l����ܦC��
void CT3DSystemView::InitList()
{
	m_TerrainList=glGenLists(20);
	m_SkyList=m_TerrainList+1 ; // �I���Ѫ���ܦC��
	m_QLanList=m_TerrainList+2; //���������ܦC��
	m_QDList=m_TerrainList+3;//���پ��[��ܦC��
	m_Rail3DwayList=m_TerrainList+4; //�u���T���ҫ���ܦC��(�z����v�Ҧ�)
	m_HazardList_Ortho=m_TerrainList+5;//�u���T���ҫ���ܦC��(���g��v�Ҧ�)
	m_clockList=m_TerrainList+6;//�������_�w��ܦC��
	m_NavigateList=m_TerrainList+7;
	m_Rail3DwayList_Ortho=m_TerrainList+8;
	m_TerrainZoomroadList=m_TerrainList+9;
	m_TunnelDMList=m_TerrainList+10; //�G�D�}����ܦC��


	makeSkykList() ; // �ͦ�ø�s�I���Ѫ���ܦC��
	BuildQDModelList();//�ͦ����[��ܦC��
	makeQLList();//�ͦ��������//��ܦC��
	makeClockList();//�Ыخ������_�w��ܦC��
	BuildTunnelDMModelList();//�Ы��G�D�}����ܦC��
		
	
}

//�u�u����׺��C��ø�s�Q�u���ҫ��Ť��᪺�T���a��
void CT3DSystemView::DrawTerrainZoomonRoad()
{

	double x,y,z;
	if(theApp.bLoginSucceed==TRUE && m_bLoadInitDemData==TRUE && m_BlockTriInfos.GetSize()>0)
	{
		m_bShowbreviary=FALSE;
		glViewport(0, 0, WinViewX, WinViewY);
		
		
		float dz=m_maxHeight-m_minHeight;
		glLineWidth(2);
		
		float currentTime1 = timeGetTime() * 0.001f;
		nCountFrame++;
		CalculateViewPortTriCord(m_vPosition.x,m_vPosition.z,m_vView.x,m_vView.z);
		CalcFPS();
		
		for( long i=0;i<m_BlockTriInfos.GetSize();i++)
		{
			
			BOOL bt=GetIfINView(m_BlockTriInfos.GetAt(i)->mDemBlockRow,m_BlockTriInfos.GetAt(i)->mDemBlockCol); 
			if(bt==FALSE)
				continue;
			
			for(long j=0;j<m_BlockTriInfos.GetAt(i)->TriPts.GetSize();j++)
			{
				
				int mtextureID=(m_BlockTriInfos.GetAt(i)->mDemBlockRow-1)*theApp.m_BlockCols+(m_BlockTriInfos.GetAt(i)->mDemBlockCol-1);
				
				glBindTexture(GL_TEXTURE_2D, m_demTextureID[mtextureID]); //�j�w���z
				
				if(m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt1.x!=-9999)
				{
					
					{
						glBegin( GL_TRIANGLES);
						
						x=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt1.x;
						y=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt1.y;
						z=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt1.z;
						
						SetTextureCoordZoomRoad(x,y,m_BlockTriInfos.GetAt(i)->mDemBlockRow,m_BlockTriInfos.GetAt(i)->mDemBlockCol);
						glVertex3f(x,z,-y);
						
						x=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt2.x;
						y=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt2.y;
						z=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt2.z;
						SetTextureCoordZoomRoad(x,y,m_BlockTriInfos.GetAt(i)->mDemBlockRow,m_BlockTriInfos.GetAt(i)->mDemBlockCol);
						glVertex3f(x,z,-y);
						
						x=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt3.x;
						y=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt3.y;
						z=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt3.z;
						SetTextureCoordZoomRoad(x,y,m_BlockTriInfos.GetAt(i)->mDemBlockRow,m_BlockTriInfos.GetAt(i)->mDemBlockCol);
						glVertex3f(x,z,-y);
						glEnd();
					}
				}
			}
		}
		
		
		float currentTime2 = timeGetTime() * 0.001f;
		mTimeElaps+=currentTime2-currentTime1;
		
		if(mTimeElaps>=1.0)
		{
			CString strText;
			strText.Format("�W�v %d FPS",nCountFrame);
			
			mTimeElaps=nCountFrame=0;
			
		}
	}
}

//�P�_�a�θ`�I�O�_�b²�Ʈ��ε����餺
BOOL CT3DSystemView::bnTriangle(double cneterx ,  double cnetery ,  double x2 ,  double y2 ,  double x3 ,  double y3 ,  double x ,  double y)
{
	double m_dx , m_dz;
	float remianAngle;
	
	
	double d1 , d2;
	double mDis=(cneterx-x)*(cneterx-x)+(cnetery-y)*(cnetery-y);
	mDis=sqrt(mDis);
	if(mDis>=m_R)
		return FALSE;
	else if(mDis<=1000)
		return TRUE;
	
		
	m_dx=cneterx-x;
	m_dz=cnetery-y;
	
    if(m_dx<=0 && m_dz>=0) 
	{
		if(m_dx==0)	
			remianAngle=90;
		else
			remianAngle=atan(fabs(m_dz/m_dx))*HDANGLE;
		
	}
    else if(m_dx>=0 && m_dz>=0) 
	{
		if(m_dx==0)	
			remianAngle=90;
		else
			remianAngle=180-atan(fabs(m_dz/m_dx))*HDANGLE;
		
	}
    else if(m_dx>=0 && m_dz<=0) 
	{
		if(m_dx==0)	
			remianAngle=270;
		else
			remianAngle=180+atan(fabs(m_dz/m_dx))*HDANGLE;
		
	}
    else if(m_dx<=0 && m_dz<=0) 
	{
		if(m_dx==0)	
			remianAngle=270;
		else
			remianAngle=360-atan(fabs(m_dz/m_dx))*HDANGLE;
		
	}
	

	if(mDis<=m_R)
	{  
		if(remianAngle>=m_sectorStartAngle && remianAngle<=m_sectorEndAngle)
			return TRUE;
		else
		{
			d1=mCalF.GetPointToLineDistence(x , y , cneterx , cnetery , x2 , y2) ; // �p���I�쪽�u���Z��
			d2=mCalF.GetPointToLineDistence(x , y , cneterx , cnetery , x3 , y3) ; // �p���I�쪽�u���Z��
            if(d1<=m_r || d2<=m_r)
				return TRUE;
		}
	}
    else
	{
		if(remianAngle>=m_sectorStartAngle && remianAngle<=m_sectorEndAngle)
		{
			if(mDis<=m_R+m_r)
				return TRUE;
		}
		
	}
	
	return FALSE;
}

//�p��²�Ʈ��ε����餺���T�ӳ��I����
void CT3DSystemView::CalculateViewPortTriCord(double View_x ,  double View_z ,  double look_x ,  double look_z)
{
	double m_derx=look_x-View_x;
	double m_derz=look_z-View_z;
	float angle_arefa;
	
	m_triPtA[0]=View_x;m_triPtA[1]=View_z;
	
    if(m_derx<=0 && m_derz>0) 
	{
		if(m_derx==0)	
			angle_arefa=270;
		else
			angle_arefa=180+atan(fabs(m_derz/m_derx))*HDANGLE;
		
	}
    else if(m_derx>=0 && m_derz>0) 
	{
		if(m_derx==0)	
			angle_arefa=0;
		else
			angle_arefa=360-atan(fabs(m_derz/m_derx))*HDANGLE;
		
	}
    else if(m_derx>=0 && m_derz<0) 
	{
		if(m_derx==0)	
			angle_arefa=0;
		else
			angle_arefa=atan(fabs(m_derz/m_derx))*HDANGLE;
		
	}
    else if(m_derx<=0 && m_derz<0) 
	{
		if(m_derx==0)	
			angle_arefa=90;
		else
			angle_arefa=180-atan(fabs(m_derz/m_derx))*HDANGLE;
		
	}
	
	m_sectorStartAngle=angle_arefa-m_FrustumAngle/2;
	m_triPtB[0]=m_R*cos(m_sectorStartAngle*PAI_D180)+m_triPtA[0];
	m_triPtB[1]=-m_R*sin(m_sectorStartAngle*PAI_D180)+m_triPtA[1];
	
	m_sectorEndAngle=angle_arefa+m_FrustumAngle/2;
	m_triPtC[0]=m_R*cos(m_sectorEndAngle*PAI_D180)+m_triPtA[0];
	m_triPtC[1]=-m_R*sin(m_sectorEndAngle*PAI_D180)+m_triPtA[1];
	
	
	m_Viewpolygon[0].x=m_triPtA[0]; 	m_Viewpolygon[0].y=-m_triPtA[1];
	m_Viewpolygon[1].x=m_triPtB[0]; 	m_Viewpolygon[1].y=-m_triPtB[1];
	m_Viewpolygon[2].x=m_triPtC[0]; 	m_Viewpolygon[2].y=-m_triPtC[1];
	
	////�s�x���f�T�����Ϊ��T�ӧ����I�����̤j�̤p����
	m_Viewpolygon_Minx=m_Viewpolygon[0].x;
	m_Viewpolygon_Miny=m_Viewpolygon[0].y;
	m_Viewpolygon_Maxx=m_Viewpolygon[0].x;
	m_Viewpolygon_Maxy=m_Viewpolygon[0].y;
	
	if(m_Viewpolygon_Minx>m_Viewpolygon[1].x) m_Viewpolygon_Minx=m_Viewpolygon[1].x;
	if(m_Viewpolygon_Maxx<m_Viewpolygon[1].x) m_Viewpolygon_Maxx=m_Viewpolygon[1].x;
	if(m_Viewpolygon_Miny>m_Viewpolygon[1].y) m_Viewpolygon_Miny=m_Viewpolygon[1].y;
	if(m_Viewpolygon_Maxy<m_Viewpolygon[1].y) m_Viewpolygon_Maxy=m_Viewpolygon[1].y;
	
	if(m_Viewpolygon_Minx>m_Viewpolygon[2].x) m_Viewpolygon_Minx=m_Viewpolygon[2].x;
	if(m_Viewpolygon_Maxx<m_Viewpolygon[2].x) m_Viewpolygon_Maxx=m_Viewpolygon[2].x;
	if(m_Viewpolygon_Miny>m_Viewpolygon[2].y) m_Viewpolygon_Miny=m_Viewpolygon[2].y;
	if(m_Viewpolygon_Maxy<m_Viewpolygon[2].y) m_Viewpolygon_Maxy=m_Viewpolygon[2].y;
}

//��a�ζ��i��|�e��LOD����
void CT3DSystemView::UpdateQuad(int nXCenter ,  int nZCenter ,  int nSize ,  int nLevel ,  int mRowIndex ,  int mColIndex)
{
	double mx=(mColIndex-1)*theApp.m_Dem_BlockWidth;
	double mz=(mRowIndex-1)*theApp.m_Dem_BlockWidth;
	//�p�G�a�θ`�I���b�����餺 , ��^
	if(bnTriangle(m_triPtA[0] , m_triPtA[1] , m_triPtB[0] , m_triPtB[1] , m_triPtC[0] , m_triPtC[1] , nXCenter*theApp.m_Cell_xwidth+mx , -nZCenter*theApp.m_Cell_ywidth-mz)==FALSE)
		return ;
	
	
	if(m_ifZoomonRoad==FALSE) //�O�_�u�u����׺��C
	{
		CVector3 vPos=GetPos();
		
		CVector3 vDst(nXCenter*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter , nZCenter ,  mRowIndex ,  mColIndex) , -nZCenter*theApp.m_Cell_ywidth-(mRowIndex-1)*theApp.m_Dem_BlockWidth);
		float nDist=mCalF.maxValueXYZ(fabs(vPos.x-vDst.x) , fabs(vPos.y-vDst.y) , fabs(vPos.z-vDst.z));
		float es , em;
		
		em=GetNodeError(nXCenter ,  nZCenter ,  nSize , mRowIndex ,  mColIndex) ; // �p��`�I�~�t
		es=m_es*(em/nDist);
		if(es<m_lodScreenError) //�p�G�~�t�p��̹��~�t�n , ��ø�s
			return;
	}
		
	if(nSize>1) //��ܦa�ζ��`�I�ٻݭn�~�����
	{	
		m_pbQuadMat[m_CurrentDemArrayIndex][nXCenter+nZCenter*m_nMapSize]=true;		
		UpdateQuad(nXCenter-nSize/2 , nZCenter-nSize/2 , nSize/2 , nLevel+1 , mRowIndex ,  mColIndex) ; // ���Υ��U�l�`�I
		UpdateQuad(nXCenter+nSize/2 , nZCenter-nSize/2 , nSize/2 , nLevel+1 , mRowIndex ,  mColIndex) ; // ���Υk�U�l�`�I
		UpdateQuad(nXCenter+nSize/2 , nZCenter+nSize/2 , nSize/2 , nLevel+1 , mRowIndex ,  mColIndex) ; // ���Υk�W�l�`�I
		UpdateQuad(nXCenter-nSize/2 , nZCenter+nSize/2 , nSize/2 , nLevel+1 , mRowIndex ,  mColIndex) ; // ���Υ��W�l�`�I
	}
}

//�ھڸ`�I��X , Y�M�a�Τl�����渹�M�C���q���{�Ʋդ��o��������`�I���{��
float CT3DSystemView::GetHeightValue(int X ,  int Y ,  int mRowIndex ,  int mColIndex)
{
	return m_pHeight_My[m_CurrentDemArrayIndex][X+Y*(m_nMapSize+1)]*m_heighScale;
	
}

//�o��۾��[���I�T������
CVector3 CT3DSystemView::GetPos()
{
	return m_vPosition;
}

//�o��۾����I�T������
CVector3 CT3DSystemView::GetView()
{
	return m_vView;
}

//�o��۾��V�W�ڶq�T������
CVector3 CT3DSystemView::UpVector()
{
	return m_vUpVector;
}

//�o��۾��ưѼƪ�CVector3�����ܶq
CVector3 CT3DSystemView::Strafe()
{
	return m_vStrafe;
}


//�`�I�~�t�p��
float CT3DSystemView::GetNodeError(int nXCenter ,  int nZCenter ,  int nSize ,  int mRowIndex ,  int mColIndex)
{
	float nMax = GetHeightValue(nXCenter , nZCenter ,  mRowIndex ,  mColIndex);
	float nMin = nMax;
	float nH1 = GetHeightValue(nXCenter-nSize , nZCenter-nSize , mRowIndex ,  mColIndex);
	float nH2 = GetHeightValue(nXCenter+nSize , nZCenter-nSize , mRowIndex ,  mColIndex);
	float nH3 = GetHeightValue(nXCenter+nSize , nZCenter+nSize , mRowIndex ,  mColIndex);
	float nH4 = GetHeightValue(nXCenter-nSize , nZCenter+nSize , mRowIndex ,  mColIndex);
	if(nMax<nH1)nMax = nH1;
	if(nMax<nH2)nMax = nH2;
	if(nMax<nH3)nMax = nH3;
	if(nMax<nH4)nMax = nH4;
	if(nMin>nH1)nMin = nH1;
	if(nMin>nH2)nMin = nH2;
	if(nMin>nH3)nMin = nH3;
	if(nMin>nH4)nMin = nH4;
	return nMax-nMin;
}

//�ھڦa�ζ����渹�M�C���P�_�Ӷ��a�ζ��O�_���f�T���Τ�
BOOL CT3DSystemView::GetIfINView(int mBlockRow ,  int mBlockCol)
{
	Point *polygonPs;	
	polygonPs=new Point[4];

	polygonPs[0].x=(mBlockCol-1)*theApp.m_Dem_BlockWidth;
	polygonPs[0].y=(mBlockRow-1)*theApp.m_Dem_BlockWidth;
	
	polygonPs[1].x=polygonPs[0].x+theApp.m_Dem_BlockWidth;
	polygonPs[1].y=polygonPs[0].y;

	polygonPs[2].x=polygonPs[0].x;
	polygonPs[2].y=polygonPs[0].y+theApp.m_Dem_BlockWidth;

	polygonPs[3].x=polygonPs[1].x;
	polygonPs[3].y=polygonPs[2].y;



	BOOL Bt=FALSE;
	bool Fin=false;
	
   //���f�T����(���Ϊ�²��)�P�a�Τl��(�x��)�P�_�W�h�p�U:
/*
	�H�U�T�ر��p����@�س��{���Ӧa�Τl���ݭnø�s
	(1)���f�T���Χ������γ������f�T���γ��I���a�Τl��(�x��)��
	(2)�a�Τl��(�x��)���������f�T���Τ�
	(3)�a�Τl��(�x��)�P���f�T���Τ��ۥ�
*/
	////�s�x���f�T�����Ϊ��T�ӧ����I�����̤j�̤p����
	//�p�G���a�Τl�����̤px , y���г��j����f�T���Ϊ��̤jx , y����
	//    ���a�Τl�����̤jx , y���г��p����f�T���Ϊ��̤px , y����
	//�h�Ӧa�Τl���@�w�������f�T���Τ� , ���ݦA�i��P�_
	if(polygonPs[0].x>=m_Viewpolygon_Maxx || polygonPs[0].y>=m_Viewpolygon_Maxy)
		return FALSE;
	if(polygonPs[3].x<=m_Viewpolygon_Minx || polygonPs[3].y<=m_Viewpolygon_Miny)
		return FALSE;
	

		
	//(1)�u�n���f�T���Φ��@�ӳ��I���a�Τl��(�x��)���N��
	if(m_triPtA[0]>polygonPs[0].x && m_triPtA[0]<polygonPs[3].x && m_triPtA[1]<-polygonPs[0].y && m_triPtA[1]>-polygonPs[3].y) //�I�b�x�θ�
		Bt=TRUE;
	if(Bt==FALSE && m_triPtB[0]>polygonPs[0].x && m_triPtB[0]<polygonPs[3].x && m_triPtB[1]<-polygonPs[0].y && m_triPtB[1]>-polygonPs[3].y) //�I�b�x�θ�
		Bt=TRUE;
	if(Bt==FALSE && m_triPtC[0]>polygonPs[0].x && m_triPtC[0]<polygonPs[3].x && m_triPtC[1]<-polygonPs[0].y && m_triPtC[1]>-polygonPs[3].y) //�I�b�x�θ�
		Bt=TRUE;
	if(Bt==FALSE)
	{
		Bt=mCalF.InPolygon(m_Viewpolygon , 3 , polygonPs[0]);
		if(Bt==FALSE)
			Bt=mCalF.InPolygon(m_Viewpolygon , 3 , polygonPs[1]);
		if(Bt==FALSE)
			Bt=mCalF.InPolygon(m_Viewpolygon , 3 , polygonPs[2]);
		if(Bt==FALSE)
			Bt=mCalF.InPolygon(m_Viewpolygon , 3 , polygonPs[3]);
	}
	
	//�٦��i���V�a�Τl����
	//(1)�T���Ϊ��T����01 , 12 , 02
	//(2)�B�Ϊ�4���� 01 , 23 , 02 , 13
		
	//01��
	if(Bt==FALSE)
	{
		//�P�_����u�q�O�_�ۥ�(�����I)
		Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[1] , polygonPs[0] , polygonPs[1]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[1] , polygonPs[0] , polygonPs[2]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[1] , polygonPs[2] , polygonPs[3]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[1] , polygonPs[1] , polygonPs[3]);
	}

	//12��
	if(Bt==FALSE)
	{
		//�P�_����u�q�O�_�ۥ�(�����I)
		Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[1] ,  m_Viewpolygon[2] , polygonPs[0] , polygonPs[1]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[1] ,  m_Viewpolygon[2] , polygonPs[0] , polygonPs[2]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[1] ,  m_Viewpolygon[2] , polygonPs[2] , polygonPs[3]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[1] ,  m_Viewpolygon[2] , polygonPs[1] , polygonPs[3]);
	}

	//02��
	if(Bt==FALSE)
	{
		//�P�_����u�q�O�_�ۥ�(�����I)
		Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[2] , polygonPs[0] , polygonPs[1]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[2] , polygonPs[0] , polygonPs[2]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[2] , polygonPs[2] , polygonPs[3]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[2] , polygonPs[1] , polygonPs[3]);
	}
	return Bt;
}

//�]�m�u�����C�ɦa�ζ����z����
void CT3DSystemView::SetTextureCoordZoomRoad(double x ,  double z ,  int mRowIndex ,  int mColIndex)
{
	//�����a�ζ����̤px , y����
	double mminx=(mColIndex-1)*theApp.m_Dem_BlockWidth;
	double mminy=(mRowIndex-1)*theApp.m_Dem_BlockWidth;
	
	float u=(x-mminx)/theApp.m_Dem_BlockWidth;
	float v=(z-mminy)/theApp.m_Dem_BlockWidth;
	
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB ,  u ,  v);
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB ,  u ,  v);
}

//��V�a�θ`�I
int CT3DSystemView::RenderQuad(int nXCenter ,  int nZCenter ,  int nSize ,  int mRowIndex ,  int mColIndex)
{
	float hjh;
	int kk;
	CVector3 pos , VPos;

	
	int nH0 , nH1 , nH2 , nH3 , nH4;
	int nCount = 0;
	if(nSize>=1.0f)//�a�ζ��`�I�ؤo>=1.0�A��ܸӸ`�I�٦��l�`�I
	{
		//�`�I�����I�M4�Ө��I�����{
		nH0 = GetHeightValue(nXCenter , nZCenter ,  mRowIndex ,  mColIndex);
		nH1 = GetHeightValue(nXCenter-nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex);
		nH2 = GetHeightValue(nXCenter+nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex);
		nH3 = GetHeightValue(nXCenter+nSize , nZCenter+nSize ,  mRowIndex ,  mColIndex);
		nH4 = GetHeightValue(nXCenter-nSize , nZCenter+nSize ,  mRowIndex ,  mColIndex);
	}

	int mnum=0;

	double mx=(mColIndex-1)*theApp.m_Dem_BlockWidth;
	double mz=(mRowIndex-1)*theApp.m_Dem_BlockWidth;
	

	//�p�G�a�θ`�I���b�����餺 , ��^
	if(bnTriangle(m_triPtA[0] , m_triPtA[1] , m_triPtB[0] , m_triPtB[1] , m_triPtC[0] , m_triPtC[1] , nXCenter*theApp.m_Cell_xwidth+mx , -nZCenter*theApp.m_Cell_ywidth-mz)==FALSE)
		return 0;

	float dz=m_maxHeight-m_minHeight;

	double x , z;
	double xcenter , zcenter;


	/*
	����`�I�զ��ܷN��
	nH4
	  |----------------|nH3
	  |                |
	  |                |
	  |                |
	  |       nH0      |
	  |    �`�I����    |
	  |                |
	  |                |
	  |----------------|
      nH1              nH2 
	
	  �䤤���O�H�`�I����(nH0)�}�l�i��ø�s , 
	  
	���Ǭ�nH0--nH1--nH2--nH3--nH4--nH1
	�䤤�b4����W(nH1--nH2 , nH2--nH3 , nH3--nH4 , nH4--nH1)�i��|�ɥR�W�����I
	�H�����P���{�`�I����v���@�P�y�����Ŭ} , �]�N�O���@�Ӧa�θ`�I�ܤַ|��4�ӤT����

    �Y�ϸɥR����I , �䵲�G���M�O�H�`�I����nH0�}�l , ø�s�@�t�C�T
	����(�HGL_TRIANGLE_FAN�覡ø�s) , �H����ø�s�t��


	*/
	
	if(m_pbQuadMat[m_CurrentDemArrayIndex][nXCenter+nZCenter*m_nMapSize]==true /*&& nSize>1.0/nLodScale*/)			
			
	{
		nCount += RenderQuad(nXCenter-nSize/2 , nZCenter-nSize/2 , nSize/2 ,  mRowIndex ,  mColIndex);
		nCount += RenderQuad(nXCenter+nSize/2 , nZCenter-nSize/2 , nSize/2 ,  mRowIndex ,  mColIndex);
		nCount += RenderQuad(nXCenter+nSize/2 , nZCenter+nSize/2 , nSize/2 ,  mRowIndex ,  mColIndex);
		nCount += RenderQuad(nXCenter-nSize/2 , nZCenter+nSize/2 , nSize/2 ,  mRowIndex ,  mColIndex);
	}
	else
	{
			//�H����ø�s�a�ζ��`�I
			glBegin( GL_TRIANGLE_FAN );
		
				x=nXCenter*theApp.m_Cell_xwidth+mx;z=-nZCenter*theApp.m_Cell_ywidth-mz;
				VPos.x=x-m_vPosition.x;VPos.y=nH0-m_vPosition.y;VPos.z=z-m_vPosition.z;
				xcenter=x;
				zcenter=-z;
				if(DotProduct(View , VPos)>0) //�p�G�b���I�d��
				{	
					if(nH0!=theApp.m_DEM_IvalidValue)	//�p�G���{����
					{
						//�]�m�C��
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH0-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH0-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH0-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x , nH0 ,  z);  //�]�m�k�u
						SetTextureCoord(nXCenter , nZCenter ,  mRowIndex ,  mColIndex);  //�]�m���z����
						glVertex3i(x ,  nH0 ,  z) ; // �g�J�����I����
					}
					
				}
				x=(nXCenter-nSize)*theApp.m_Cell_xwidth+mx;z= -(nZCenter-nSize)*theApp.m_Cell_ywidth-mz;
				VPos.x=x-m_vPosition.x;VPos.y=nH1-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)
				{	

					if(nH1!=theApp.m_DEM_IvalidValue )	//�p�G���{����
					{
						//�]�m�C��
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH1-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH1-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH1-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x , nH1  ,  x);  //�]�m�k�u
						SetTextureCoord(nXCenter-nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex); //�]�m���z����
						glVertex3i(x , nH1  ,  z) ; // ���U���I
						CracksPatchTop(nXCenter , nZCenter , nSize , mRowIndex , mColIndex) ; // �`�I���_�׸�
						nCount++;
					}
				}
				if(nZCenter-nSize==0) 
				{
					for(kk=1;kk<=2*nSize-1;kk++)
					{
						hjh = GetHeightValue(nXCenter-nSize+kk , nZCenter-nSize ,  mRowIndex ,  mColIndex);
						x=(nXCenter-nSize+kk)*theApp.m_Cell_xwidth+mx;z=-(nZCenter-nSize)*theApp.m_Cell_ywidth-mz;
						VPos.x=x-m_vPosition.x;VPos.y=hjh-m_vPosition.y;VPos.z=z-m_vPosition.z;
						if(DotProduct(View , VPos)>0)//�p�G�`�I�b�b�����餺
						{	
							if(hjh!=theApp.m_DEM_IvalidValue)	//�p�G���{����	
							{
								//�]�m�C��
								glColor3f(
									(maxZ_color_R-minZ_color_R)*(hjh-m_minHeight)/dz+minZ_color_R , 
									(maxZ_color_G-minZ_color_G)*(hjh-m_minHeight)/dz+minZ_color_G , 
									(maxZ_color_B-minZ_color_B)*(hjh-m_minHeight)/dz+minZ_color_B);
								glNormal3f(x ,  hjh ,  z);  //�]�m�k�u
								SetTextureCoord(nXCenter-nSize+kk , nZCenter-nSize ,  mRowIndex ,  mColIndex); //�]�m���z����
								glVertex3i(x ,  hjh ,  z);
								
								mnum++;
							}
						}
						
					}
				
				}

					
				x=(nXCenter+nSize)*theApp.m_Cell_xwidth+mx;z=-(nZCenter-nSize)*theApp.m_Cell_ywidth-mz;
				
				VPos.x=x-m_vPosition.x;VPos.y=nH2-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)//�p�G�`�I�b�b�����餺
				{	
					if(nH2!=theApp.m_DEM_IvalidValue)	//�p�G���{����
					{
						//�]�m�C��
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH2-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH2-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH2-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x ,  nH2 ,  z) ; // �]�m�k�u
						SetTextureCoord(nXCenter+nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex); //�]�m���z����
						glVertex3i(x ,  nH2 ,  z) ; // ���W���I
						CracksPatchRight(nXCenter , nZCenter , nSize , mRowIndex , mColIndex) ; // �`�I���_�׸�
						nCount++;
					}
				}


				if(nXCenter+nSize>=m_nMapSize)
				{
					for(kk=1;kk<=2*nSize-1;kk++)
					{
						hjh = GetHeightValue(nXCenter+nSize , kk+(nZCenter-nSize) ,  mRowIndex ,  mColIndex);
						x=(nXCenter+nSize)*theApp.m_Cell_xwidth+mx;z=-(kk+(nZCenter-nSize))*theApp.m_Cell_ywidth-mz;
						
						VPos.x=x-m_vPosition.x;VPos.y=hjh-m_vPosition.y;VPos.z=z-m_vPosition.z;
						if(DotProduct(View , VPos)>0)//�p�G�`�I�b�b�����餺
						{	
							if(hjh!=theApp.m_DEM_IvalidValue)	//�p�G���{����	
							{
								//�]�m�C��
								glColor3f(
									(maxZ_color_R-minZ_color_R)*(hjh-m_minHeight)/dz+minZ_color_R , 
									(maxZ_color_G-minZ_color_G)*(hjh-m_minHeight)/dz+minZ_color_G , 
									(maxZ_color_B-minZ_color_B)*(hjh-m_minHeight)/dz+minZ_color_B);
								glNormal3f(x ,  hjh ,  z) ; // �]�m�k�u
								SetTextureCoord(nXCenter+nSize , kk+(nZCenter-nSize) ,  mRowIndex ,  mColIndex); //�]�m���z����
								glVertex3i(x ,  hjh ,  z);
								mnum++;
							}
						}
					}
				
				}


				x=(nXCenter+nSize)*theApp.m_Cell_xwidth+mx;z=-(nZCenter+nSize)*theApp.m_Cell_ywidth-mz;
				
				VPos.x=x-m_vPosition.x;VPos.y=nH3-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)//�p�G�`�I�b�b�����餺
				{	
					if(nH3!=theApp.m_DEM_IvalidValue)		//�p�G���{����
					{
						//�]�m�C��
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH3-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH3-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH3-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x ,  nH3 ,  z) ; // �]�m�k�u
						SetTextureCoord(nXCenter+nSize , nZCenter+nSize ,  mRowIndex ,  mColIndex); //�]�m���z����
						glVertex3i(x ,  nH3 ,  z) ; // �k�W���I
						CracksPatchBottom(nXCenter , nZCenter , nSize , mRowIndex , mColIndex) ; // �`�I���_�׸�
						nCount++;
					}
				}

				if(nZCenter+nSize>=m_nMapSize) 
				{
					for(kk=1;kk<=2*nSize-1;kk++)
					{
						hjh = GetHeightValue(nXCenter+nSize-kk , nZCenter+nSize ,  mRowIndex ,  mColIndex);
						x=(nXCenter+nSize-kk)*theApp.m_Cell_xwidth+mx;z=-(nZCenter+nSize)*theApp.m_Cell_ywidth-mz;
						
						VPos.x=x-m_vPosition.x;VPos.y=hjh-m_vPosition.y;VPos.z=z-m_vPosition.z;
						if(DotProduct(View , VPos)>0)//�p�G�`�I�b�b�����餺
						{	
							if(hjh!=theApp.m_DEM_IvalidValue)	//�p�G���{����	
							{
								//�]�m�C��
								glColor3f(
									(maxZ_color_R-minZ_color_R)*(hjh-m_minHeight)/dz+minZ_color_R , 
									(maxZ_color_G-minZ_color_G)*(hjh-m_minHeight)/dz+minZ_color_G , 
									(maxZ_color_B-minZ_color_B)*(hjh-m_minHeight)/dz+minZ_color_B);
								glNormal3f(x ,  hjh ,  z) ; // �]�m�k�u
								SetTextureCoord(nXCenter+nSize-kk , nZCenter+nSize ,  mRowIndex ,  mColIndex); //�]�m���z����
								glVertex3i(x ,  hjh ,  z);
								mnum++;
							}
						}
						
					}
				}

				
				x=(nXCenter-nSize)*theApp.m_Cell_xwidth+mx;z=-(nZCenter+nSize)*theApp.m_Cell_ywidth-mz;
				
				VPos.x=x-m_vPosition.x;VPos.y=nH4-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)//�p�G�`�I�b�b�����餺
				{	
					if(nH4!=theApp.m_DEM_IvalidValue)	//�p�G���{����	
					{	
						//�]�m�C��
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH4-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH4-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH4-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x ,  nH4 ,  z) ; // �]�m�k�u
						SetTextureCoord(nXCenter-nSize , nZCenter+nSize ,  mRowIndex ,  mColIndex) ; // �]�m���z����
						glVertex3i(x ,  nH4 ,  z) ; // ���W���I
						CracksPatchLeft(nXCenter , nZCenter , nSize , mRowIndex , mColIndex) ; // �`�I���_�׸�
						nCount++;
					}
				}
			
				if(nXCenter-nSize<=0) 
				{
					for(kk=2*nSize-1;kk>0;kk--)
					{
						hjh = GetHeightValue(nXCenter-nSize , kk+(nZCenter-nSize) ,  mRowIndex ,  mColIndex);
						x=(nXCenter-nSize)*theApp.m_Cell_xwidth+mx;z=-(kk+(nZCenter-nSize))*theApp.m_Cell_ywidth-mz;
						
						VPos.x=x-m_vPosition.x;VPos.y=hjh-m_vPosition.y;VPos.z=z-m_vPosition.z;
						if(DotProduct(View , VPos)>0)//�p�G�`�I�b�b�����餺
						{	
							if(hjh!=theApp.m_DEM_IvalidValue)	//�p�G���{����	
							{							
								//�]�m�C��
								glColor3f(
									(maxZ_color_R-minZ_color_R)*(hjh-m_minHeight)/dz+minZ_color_R , 
									(maxZ_color_G-minZ_color_G)*(hjh-m_minHeight)/dz+minZ_color_G , 
									(maxZ_color_B-minZ_color_B)*(hjh-m_minHeight)/dz+minZ_color_B);
								glNormal3f(x ,  hjh ,  z) ; // �]�m�k�u
								SetTextureCoord(nXCenter-nSize , kk+(nZCenter-nSize) ,  mRowIndex ,  mColIndex); //�]�m���z����
								glVertex3i(mx ,  hjh ,  z);
								mnum++;
							}
						}
					}
					
				}
				

				x=(nXCenter-nSize)*theApp.m_Cell_xwidth+mx;z=-(nZCenter-nSize)*theApp.m_Cell_ywidth-mz;
				VPos.x=x-m_vPosition.x;VPos.y=nH1-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)//�p�G�`�I�b�b�����餺
				{	
						
					if(nH1!=theApp.m_DEM_IvalidValue)	//�p�G���{����	
					{
						//�]�m�C��
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH1-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH1-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH1-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x ,  nH1 ,  z) ; // �]�m�k�u
						SetTextureCoord(nXCenter-nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex); //�]�m���z����
						glVertex3i(x ,  nH1 , z) ; // ���g���U���I
						nCount++;
					}
				}

				
			glEnd();
			
			nCount=nCount+mnum ; // �T���μƶq
			mnum=0;
		}
	return nCount ; // ��^�T���μƶq
}

//�]�m���z����
void CT3DSystemView::SetTextureCoord(float x ,  float z ,  int mRowIndex ,  int mColIndex)
{
	double X=x*theApp.m_Cell_xwidth;
	double Y=-z*theApp.m_Cell_xwidth;
	
	float u=(X)/(m_Texturexy[mCurrentTextID][2]-m_Texturexy[mCurrentTextID][0]);
	float v=-(Y)/(m_Texturexy[mCurrentTextID][3]-m_Texturexy[mCurrentTextID][1]);	
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB ,  u ,  v) ; // ���w�h�����z�椸TEXTURE0�����z����
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB ,  u ,  v) ; // ���w�h�����z�椸TEXTURE1�����z����
}

//�`�I���_�׸�(����)
void CT3DSystemView::CracksPatchBottom(int nXCenter ,  int nZCenter ,  int nSize ,  int mRowIndex ,  int mColIndex)
{
	if(nSize<=0) return;
	if(m_ifZoomonRoad==FALSE) return;
	
	if(nZCenter+2*nSize<m_nMapSize)
	{
		if(!m_pbQuadMat[m_CurrentDemArrayIndex][nXCenter+(nZCenter+2*nSize)*m_nMapSize])
			return;
	}
	else
		return;
	CracksPatchBottom(nXCenter+nSize/2 , nZCenter+nSize/2 , nSize/2 , mRowIndex ,  mColIndex) ; // �`�I���_�׸�
	SetTextureCoord(nXCenter , nZCenter+nSize ,  mRowIndex ,  mColIndex); //�]�m���z����
	glVertex3i(nXCenter*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter , nZCenter+nSize , mRowIndex ,  mColIndex) , -(nZCenter+nSize)*theApp.m_Cell_ywidth-((mRowIndex-1)*theApp.m_Dem_BlockWidth));
	CracksPatchBottom(nXCenter-nSize/2 , nZCenter+nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
}

//�`�I���_�׸�(����)
void CT3DSystemView::CracksPatchLeft(int nXCenter ,  int nZCenter ,  int nSize ,  int mRowIndex ,  int mColIndex)
{
	
	if(nSize<=0) return;
	if(m_ifZoomonRoad==FALSE) return;
	
	if(nXCenter-2*nSize>=0)
	{
		if(!m_pbQuadMat[m_CurrentDemArrayIndex][(nXCenter-2*nSize)+nZCenter*m_nMapSize])
			return;
	}
	else
		return;
	CracksPatchLeft(nXCenter-nSize/2 , nZCenter+nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
	SetTextureCoord(nXCenter-nSize , nZCenter ,  mRowIndex ,  mColIndex); //�]�m���z����
	glVertex3i((nXCenter-nSize)*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter-nSize , nZCenter , mRowIndex ,  mColIndex) , -nZCenter*theApp.m_Cell_ywidth-((mRowIndex-1)*theApp.m_Dem_BlockWidth));
	
	CracksPatchLeft(nXCenter-nSize/2 , nZCenter-nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
	
}
//�`�I���_�׸�(�k��)
void CT3DSystemView::CracksPatchRight(int nXCenter ,  int nZCenter ,  int nSize ,  int mRowIndex ,  int mColIndex)
{
	
	if(nSize<=0) return;
	if(m_ifZoomonRoad==FALSE) return;
	
	if(nXCenter+2*nSize<m_nMapSize)
	{
		if(!m_pbQuadMat[m_CurrentDemArrayIndex][(nXCenter+2*nSize)+nZCenter*m_nMapSize])
			return;
	}
	else
		return;
	CracksPatchRight(nXCenter+nSize/2 , nZCenter-nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
	SetTextureCoord(nXCenter+nSize , nZCenter ,  mRowIndex ,  mColIndex); //�]�m���z����
	glVertex3i((nXCenter+nSize)*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter+nSize , nZCenter , mRowIndex ,  mColIndex) , -nZCenter*theApp.m_Cell_ywidth-((mRowIndex-1)*theApp.m_Dem_BlockWidth));
	
	CracksPatchRight(nXCenter+nSize/2 , nZCenter+nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
}

//�`�I���_�׸�(����)
void CT3DSystemView::CracksPatchTop(int nXCenter ,  int nZCenter ,  int nSize ,  int mRowIndex ,  int mColIndex)
{
	if(nSize<=0) return;
	if(m_ifZoomonRoad==FALSE) return;
	
	if(nZCenter-2*nSize>=0)
	{
		if(!m_pbQuadMat[m_CurrentDemArrayIndex][nXCenter+(nZCenter-2*nSize)*m_nMapSize])
			return;
	}
	else
		return;
	CracksPatchTop(nXCenter-nSize/2 , nZCenter-nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
	SetTextureCoord(nXCenter , nZCenter-nSize ,  mRowIndex ,  mColIndex); //�]�m���z����
	glVertex3i(nXCenter*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter , nZCenter-nSize , mRowIndex ,  mColIndex) , -(nZCenter-nSize)*theApp.m_Cell_ywidth-((mRowIndex-1)*theApp.m_Dem_BlockWidth));
	CracksPatchTop(nXCenter+nSize/2 , nZCenter-nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
}

//����ø�s
void CT3DSystemView::DrawScene()
{
	InitTerr();
    SetDrawMode() ; // �]�mø�ϼҦ�


	if(this->m_stereo==TRUE)
	{
		SetCamra(1);
		glDrawBuffer(GL_BACK_LEFT);                      
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DrawSky();
		DrawClock();		
		DrawTerrain();
//		DrawRangeNavigate();

		glDrawBuffer(GL_BACK_RIGHT);                      
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SetCamra(2);
		DrawSky();
		DrawClock();
		glCallList(m_TerrainList);
//		glCallList(m_NavigateList);

	}
	else
	{
	//	SetCamra(0) ; // �]�m�۾�
		glDrawBuffer(GL_BACK);                     
		glClearColor(1.0f , 1.0f , 1.0f , 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DrawSky();
		if(m_ViewType==GIS_VIEW_ORTHO)		
		{
			DrawTerrain_ORTHO();
		}
		else if(m_ViewType==GIS_VIEW_PERSPECTIVE)
		{
			DrawClock();//ø�s�������_�w
			DrawTerrain() ; // �T���a��ø�s
			
		}
		
		if(m_QueryType==QUERY_COORDINATE || m_QueryType==QUERY_DISTENCE || m_QueryType==SELECTLINE)
			DrawSearchPoint() ; // ø�s�Ŷ��d�߼лx
		

		if(m_ViewType==GIS_VIEW_ORTHO)	
		{
			DrawRailwaythesme_Ortho();
		}
		else if(m_ViewType==GIS_VIEW_PERSPECTIVE) 
		{
			DrawRailwaythesme();
		}
		DrawTerrainDelaunay();	//ø�s�g�L�u���ؤT���ҫ᪺�T��Delaunay�a��
		DrawFlyPath();//ø�s������|

	}

}

//���}����
void CT3DSystemView::OnMenuOpenproject() 
{
	COpenProject dlg;
	BeginWaitCursor() ; // �եΥ������ܨF�|���� , �i�D�Τ�t�Φ�
	if(dlg.DoModal()==IDOK)
	{
		theApp.bLoadImage=TRUE ; // �v���[�����\
		OnDraw (GetDC()) ; // ���}���\ , ø�s�T������
	}
	EndWaitCursor();	//�N���Ф������q�{���� , ��������
}

//�qoracle�ƾڮw��Ū��BLOB�������v�����z�ƾڨüg�J�{�ɼv�����z���
BOOL CT3DSystemView::ExportBlobTextureToFIle(CString strFilename ,  int RowIndex ,  int ColIndex ,  int mID)
{
	CString tt;
	
	tt.Format("SELECT ���z�ƾ� FROM Texture WHERE �渹=%d AND �C��=%d AND ���z���l��h��=%d AND �s��= :%d FOR UPDATE" , RowIndex , ColIndex , m_currebtPhramid , mID);
	BOOL bt=myOci.ReadBOLBDataFromDB(strFilename , tt , mID) ; // �q�ƾڮw��Ū��BLOB�ƾ�
	return bt;
}

//�]�mø�ϼҦ�
void CT3DSystemView::SetDrawMode()
{
	switch(m_Drawmode)//ø�s�Ҧ� 
	{
	case 1://�u�ؼҦ�
		glDisable(GL_TEXTURE_2D) ; // �������z�\��
		glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
		break;
	case 2://��w�Ҧ�
		glDisable(GL_TEXTURE_2D) ; // �}�ү��z�\��
		glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
		break;
	case 3://���z�Ҧ�
		glEnable(GL_TEXTURE_2D) ; // �}�ү��z�\��
		glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
		break;
	}

	
}


//�u�ؼҦ�
void CT3DSystemView::OnDrawmodeLine() 
{

	if(m_Drawmode!=1) 
	{
		b_haveMadeRail3DwayList=FALSE;
		b_haveMadeRail3DwayList_Ortho=FALSE;
	}
	
	m_Drawmode =1;
	OnDraw (GetDC()) ; // ���}���\ , ø�s�T������
	
}

//��w�Ҧ�
void CT3DSystemView::OnDrawmodeRender() 
{
	if(m_Drawmode!=2) 
	{
		b_haveMadeRail3DwayList=FALSE;
		b_haveMadeRail3DwayList_Ortho=FALSE;
	}
	m_Drawmode =2;
	OnDraw (GetDC()) ; // ���}���\ , ø�s�T������
}

//���z�Ҧ�
void CT3DSystemView::OnDrawmodeTexture() 
{
	if(m_Drawmode!=3) 
	{
		b_haveMadeRail3DwayList=FALSE;
		b_haveMadeRail3DwayList_Ortho=FALSE;
	}
	m_Drawmode =3;
	OnDraw (GetDC()) ; // ���}���\ , ø�s�T������
}

//ø�s�ѪŭI��
void CT3DSystemView::DrawSky()
{
	
	glPushMatrix();
	SetSkyProjection() ; // �]�m�I���Ѫŧ�v
	glCallList(m_SkyList);
	if(m_bShowbreviary==TRUE)  //�p�G��ܾɯ��
	{
		SetSkyProjectionNavigate() ; // �]�m�ɯ�Ϫ��I���Ѫŧ�v
		glCallList(m_SkyList); ; // �եέI���Ѫ���ܦC��
	}
	glPopMatrix();
	glViewport(0 ,  0 ,  WinViewX , WinViewY) ; // ���s�]�m���f�j�p
	
}

//�I���Ѫŧ�v�]�m
void CT3DSystemView::SetSkyProjection()
{
	glViewport(0 ,  0 ,  WinViewX , WinViewY) ; // �]�m���f�j�p
	
    glMatrixMode( GL_PROJECTION ); //�N��e�x�}�]�m����v�x�}
    glLoadIdentity() ; // �N��e�x�}�m�������}  
	
    //�]�m���g��v������
	if (WinViewX <= WinViewY) 
		glOrtho (0.0f ,  1.0f ,  0.0f , 1.0f*(GLfloat)WinViewX/(GLfloat)WinViewY ,  -1.0f , 1.0f);
    else 
		glOrtho (0.0f , 1.0f*(GLfloat)WinViewY/(GLfloat)WinViewX ,  0.0f ,  1.0f ,  -1.0f ,  1.0f);
	
	glMatrixMode( GL_MODELVIEW ) ; // �N��e�x�}�]�m���ҫ��x�}	
	glLoadIdentity ();	//�N��e�x�}�m�������}  
}

//�I���Ѫžɯ�ϧ�v�]�m
void CT3DSystemView::SetSkyProjectionNavigate()
{
	glViewport(WinViewX*5/6 ,  WinViewY*5/6 , WinViewX/6 ,  WinViewY/6) ; // �]�m���f�j�p
	
    glMatrixMode( GL_PROJECTION ); //�N��e�x�}�]�m����v�x�}
    glLoadIdentity() ; // �N��e�x�}�m�������}  
	
	//�]�m���g��v������
    if (WinViewX <= WinViewY) 
		glOrtho (0.0f ,  1.0f ,  0.0f , 1.0f*(GLfloat)WinViewX/(GLfloat)WinViewY ,  -1.0f , 1.0f);
    else 
		glOrtho (0.0f , 1.0f*(GLfloat)WinViewY/(GLfloat)WinViewX ,  0.0f ,  1.0f ,  -1.0f ,  1.0f);
	
	glMatrixMode( GL_MODELVIEW ) ; // �N��e�x�}�]�m���ҫ��x�}	
	glLoadIdentity ();	//�N��e�x�}�m�������}  
}

//�ͦ�ø�s�I���Ѫ���ܦC��
void CT3DSystemView::makeSkykList()
{
	glNewList(m_SkyList , GL_COMPILE);
		DrawBackground(); //ø�s�I���Ѫ�         
	glEndList();
}

//ø�s�I���Ѫ�    
void CT3DSystemView::DrawBackground()
{
	glPushMatrix();	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	
	glPolygonMode(GL_FRONT_AND_BACK , GL_FILL); 
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D ,  m_cTxtSky.GetTxtID());
	
	glBegin(GL_QUADS);
	{			
		glTexCoord2f((float)0.0 ,  (float)1.0);	glVertex2f(0.0 , 1.0);
		glTexCoord2f((float)1.0 ,  (float)1.0);	glVertex2i(1.0 , 1.0);
		
		glTexCoord2f((float)1.0 ,  (float)0.0); glVertex2f(1.0f , 0.0f);
		glTexCoord2f((float)0.0 ,  (float)0.0); glVertex2f(0.0f , 0.0f);
	}
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK , GL_LINE); 
	glDisable(GL_TEXTURE_2D);	
	glEnable(GL_DEPTH_TEST);	
	glPopMatrix();
	
}

//���إ�����ܥ��}/����
void CT3DSystemView::OnMenuStereo() 
{
	if(m_stereo==TRUE)//�p�G�O����Ҧ�
		m_stereo=FALSE;//�лx������
	else ////�p�G���O����Ҧ�
	{
		m_stereo=TRUE;//�лx�����}
		
	}
	OnDraw (GetDC());//��s�T������
}

//�]�m"���إ���Ҧ�"�l���襤�лx
void CT3DSystemView::OnUpdateMenuStereo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(bStereoAvailable); //�p�G��ܤ��������Ҧ�
	pCmdUI->SetCheck(m_stereo);//�ھ�m_stereo�ȳ]�m�]�m"���إ���Ҧ�"�l���襤�лx
	
}

//�Ŷ��d�߼лx�]�m
void CT3DSystemView::OnSpacequerySet() 
{
	CSpaceSearchSet dlg;
	
	dlg.m_shizxLength=m_shizxLength ; // �d�߼лx�Q�r�u����
	dlg.m_shuzxHeight=m_shuzxHeight ; // �d�߼лx�ݪ��u����
	dlg.m_QueryLineWidth=m_QueryLineWidth ; // �d�߼лx�u���e��
	dlg.m_QueryColorR=m_QueryColorR ; // �d�߼лx�u���C��(��)
	dlg.m_QueryColorG=m_QueryColorG ; // �d�߼лx�u���C��(��)
	dlg.m_QueryColorB=m_QueryColorB ; // �d�߼лx�u���C��(��)
	if(dlg.DoModal()==IDOK) //�p�G��ܮإ��}���\
	{
		m_shizxLength=dlg.m_shizxLength ; // �o��s�]�m���d�߼лx�Q�r�u����
		m_shuzxHeight=dlg.m_shuzxHeight ; // �o��s�]�m���d�߼лx�ݪ��u����
		m_QueryLineWidth=dlg.m_QueryLineWidth ; // �o��s�]�m���d�߼лx�u���e��
		m_QueryColorR=dlg.m_QueryColorR ; // �o��s�]�m���d�߼лx�u���C��(��)
		m_QueryColorG=dlg.m_QueryColorG ; // �o��s�]�m���d�߼лx�u���C��(��)
		m_QueryColorB=dlg.m_QueryColorB ; // �o��s�]�m��//�d�߼лx�u���C��(��)
	}	
}


void CT3DSystemView::OnLButtonDown(UINT nFlags ,  CPoint point) 
{
	/**/
	if(m_ViewType==GIS_VIEW_ORTHO)	//�p�G�O���g��v�Ҧ�	
	{
		if(m_OrthoZommPan==ORTHO_ZOOMIN) //��j�v���Ҧ�
			OnOrthoZoomIn(); 
		else if(m_OrthoZommPan==ORTHO_ZOOMOUT)//�Y�p�v���Ҧ�
			OnOrthoZoomOut();
		else if(m_OrthoZommPan==ORTHO_PAN)//�����v���Ҧ�
		{
			m_preX=point.x;
			m_preY=point.y;
			OnOrthoPan();
		}
		else if(m_OrthoZommPan==ORTHO_ZOOMWINDOW) //�}����j�Ҧ�
		{
			if(m_pushNumb<=0) //
			{
				m_preX=point.x;//�O�����в�1�I����
				m_preY=point.y;
				
				m_pushNumb=1;
				SetCapture();
			}
			else if(m_pushNumb==1)
			{
				m_currentX=point.x;//�O�����в�2�I����
				m_currentY=point.y;
				
				m_OrthoZoomWindowRect_x1=mCalF.MinValueXY(m_preX,m_currentX);
				m_OrthoZoomWindowRect_y1=mCalF.MinValueXY(m_preY,m_currentY);
				m_OrthoZoomWindowRect_x2=mCalF.MaxValueXY(m_preX,m_currentX);
				m_OrthoZoomWindowRect_y2=mCalF.MaxValueXY(m_preY,m_currentY);
				
				float bl1=WinViewX/(m_OrthoZoomWindowRect_x2-m_OrthoZoomWindowRect_x1);
				float bl2=WinViewY/(m_OrthoZoomWindowRect_y2-m_OrthoZoomWindowRect_y1);
				float bl=bl1;
				if(bl>bl2)	
					bl=bl2;
				
				m_OrthoViewSize=m_OrthoViewSize/(1+bl/5);
				OnDraw (GetDC());
				m_pushNumb=0;
				ReleaseCapture();
				
			}
		}
		
	}


	if(m_QueryType==QUERY_COORDINATE)//�Ŷ��T�����Ьd��
	{
		m_bmouseView=false;
		m_oldMousePos=point;
		ScreenToGL(point);
	}
	else if(m_QueryType==QUERY_DISTENCE)//�Ŷ��Z���d��
	{
		m_bmouseView=false; // �������б��۾�����
		m_oldMousePos=point;
		ScreenToGL(point);
	}	
	else if(m_QueryType==SELECTLINE)
	{
		m_bmouseView=false; // �������б��۾�����
		m_oldMousePos=point;
		ScreenToGL(point); 
	}
	else if(m_QueryType==SELECTFLYPATH)//�i�歸����|���
	{
		m_bmouseView=false;
		m_oldMousePos=point;
		ScreenToGL(point);
	}
	else
	{
		m_bmouseView=true;
		m_oldMousePos=point;
	}

	CView::OnLButtonDown(nFlags ,  point);
}

//�d�ߤT������
void CT3DSystemView::OnQueryCoordinate() 
{
	m_OrthoZommPan=-1;
	if(m_QueryType==QUERY_COORDINATE) //�p�G��e�w�g�O�d�ߤT�����Ъ��A�A�h����
		m_QueryType=-1;
	else //�p�G��e�w�g���O�d�ߤT�����Ъ��A�A�h���}
		m_QueryType=QUERY_COORDINATE;
}

//�]�m�O�_�襤���A
void CT3DSystemView::OnUpdateQueryCoordinate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_QueryType==QUERY_COORDINATE);
	
}

//�d�ߪŶ��Z��
void CT3DSystemView::OnQueryDistence() 
{
	m_OrthoZommPan=-1;
	
	if(m_QueryType==QUERY_DISTENCE) //�p�G��e�w�g�O�d�ߪŶ��Z�����A�A�h����
		m_QueryType=-1;
	else // �p�G��e���O�d�ߪŶ��Z�����A�A�h�����A�h���}
		m_QueryType=QUERY_DISTENCE;
}

//�]�m�O�_�襤���A
void CT3DSystemView::OnUpdateQueryDistence(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_QueryType==QUERY_DISTENCE);
	
}

//
void CT3DSystemView::ScreenToGL(CPoint point)
{
	int mouse_x=point.x;
	int mouse_y=point.y;
	
	GLint viewport[4];
	GLdouble modelview[16] , projection[16];
	GLdouble wx , wy , wz;
	float winX , winY , winZ;
	
	glPushMatrix();
	glGetDoublev(GL_MODELVIEW_MATRIX ,  modelview);
	glGetDoublev(GL_PROJECTION_MATRIX ,  projection);
	glGetIntegerv(GL_VIEWPORT ,  viewport);
	glPopMatrix();
	
	winX=(float)mouse_x;
	winY=(float)viewport[3]-(float)mouse_y-1;
	glReadPixels(mouse_x , 
		int(winY) , 
		1 , 1 , 
		GL_DEPTH_COMPONENT , 
		GL_FLOAT , 
		&winZ);
	gluUnProject((GLdouble)winX , (GLdouble)winY , (GLdouble)
		winZ , modelview , projection , viewport , &wx , &wy , &wz);
	
	CString tt;
	

	
	
	if(winZ>=0 && winZ<1.0) 
	{
		if(m_QueryType==QUERY_COORDINATE)//�d�ߤT������
		{
			if(m_ViewType==GIS_VIEW_ORTHO) //�p�G�O���g��v�Ҧ�
			{
				double mx=wx+m_ortho_CordinateOriginX; //�p��x����
				double my=wy+m_ortho_CordinateOriginY; //�p��y����
				mx=theApp.m_DemLeftDown_x+mx*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//�ഫ���j�a����
				my=theApp.m_DemLeftDown_y+my*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//�ഫ���j�a����
				wz=m_demInsert.GetHeightValue(mx,my,2);//�qDEM�������X���������{
				tt.Format("��e����(x,y,z)=(%.3f,%.3f,%.3f)",mx,my,wz);
			}
			else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//�p�G�O�z����v�Ҧ�
			{
				tt.Format("��e����(x,y,z)=(%.3f,%.3f,%.3f)",wx+theApp.m_DemLeftDown_x,-wz+theApp.m_DemLeftDown_y,wy);	
				
			}
			pt1[0]=wx;pt1[1]=wy;pt1[2]=wz; //�d����o���T���j�a����
			OnDraw(GetWindowDC()); //��s�T������
			MessageBox(tt,"�T�����Ьd��",MB_ICONINFORMATION); //���X���Ьd�߫H��
		}	
		else if(m_QueryType==QUERY_DISTENCE) // �d�ߪŶ��Z��
		{
			if(	m_bSearchDistencePtNums>=2) // �p�G����I��2�ӡA�k�s
				m_bSearchDistencePtNums=0;
			
			m_bSearchDistencePtNums++ ; //  ����I�� + 1
			
			if(m_bSearchDistencePtNums==1) // �p�G�u��ܤF1���I
			{
				pt1[0]=wx;pt1[1]=wy;pt1[2]=wz;	// �N�T���I���Цs�x��Ʋ� pt1[] �̭�
			}
			else	//��ܤF����I�A�h��ܥi�H�p��Ŷ��Z���F		 		
			{
				pt2[0]=wx;pt2[1]=wy;pt2[2]=wz; // �N�T���I���Цs�x��Ʋ� pt2[] �̭�

				double mdistence;
				
				if(m_ViewType==GIS_VIEW_ORTHO)	 //�p�G�O���g��v�Ҧ�
				{
					double nx1,ny1,nz1,nx2,ny2,nz2;
					nx1=pt1[0]+m_ortho_CordinateOriginX;//�p��P1�Ix����
					nx1=theApp.m_DemLeftDown_x+nx1*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//�NP1�Ix�����ഫ���j�a����
					ny1=pt1[1]+m_ortho_CordinateOriginY;//�p��P1�Iy����
					ny1=theApp.m_DemLeftDown_y+ny1*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//�NP1�Iy�����ഫ���j�a����
					nz1	=m_demInsert.GetHeightValue(nx1,ny1,2);//�qDEM�������XP1�I���������{
					pt1[2]=nz1;
					
					nx2=pt2[0]+m_ortho_CordinateOriginX;//�p��P2�Ix����
					nx2=theApp.m_DemLeftDown_x+nx2*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//�NP2�Ix�����ഫ���j�a����
					ny2=pt2[1]+m_ortho_CordinateOriginY;//�p��P2�Iy����
					ny2=theApp.m_DemLeftDown_y+ny2*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//�NP2�Iy�����ഫ���j�a����
					nz2	=m_demInsert.GetHeightValue(nx2,ny2,2);//�qDEM�������XP2�I���������{
					pt2[2]=nz2;
					
					//�p��Z��
					mdistence=sqrt((nx2-nx1)*(nx2-nx1)+(ny2-ny1)*(ny2-ny1)+(nz2-nz1)*(nz2-nz1));
					tt.Format("���I��:\n(x1,y1,z1)=(%.3f,%.3f,%.3f)\n(x2,y2,z2)=(%.3f,%.3f,%.3f)\n�Z��Dis=%.3f",\
						nx1,ny1,nz1,nx2,ny2,nz2,mdistence);
					
				}
				else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//�p�G�O�z����v�Ҧ�
				{
					//�p��Z��
					mdistence=sqrt((pt2[0]-pt1[0])*(pt2[0]-pt1[0])+(pt2[1]-pt1[1])*(pt2[1]-pt1[1])+(pt2[2]-pt1[2])*(pt2[2]-pt1[2]));
					tt.Format("���I��:\n(x1,y1,z1)=(%.3f,%.3f,%.3f)\n(x2,y2,z2)=(%.3f,%.3f,%.3f)\n�Z��Dis=%.3f",pt1[0]+theApp.m_DemLeftDown_x,-pt1[2]+theApp.m_DemLeftDown_y,pt1[1],pt2[0]+theApp.m_DemLeftDown_x,-pt2[2]+theApp.m_DemLeftDown_y,pt2[1],mdistence);
				}
				
				OnDraw(GetWindowDC());//��s�T������
				MessageBox(tt,"�T���Z���d��",MB_ICONINFORMATION);//���X�Z���d�߫H��

			}
		}
		else if(m_QueryType==SELECTLINE) //�p�G�O�T����u�]�p
		{
			
			PCordinate ppt = new Cordinate;  //�w�q
			if( ppt == NULL )      //�p�G���� 
			{  
				AfxMessageBox( "Failed to add a new ppt"); 
				return ;        
			}
			
			if(m_ViewType==GIS_VIEW_ORTHO)	//�p�G�O���g��v�Ҧ�	
			{
				double mx=wx+m_ortho_CordinateOriginX; //�p��x����
				double my=wy+m_ortho_CordinateOriginY; //�p��y����
				mx=theApp.m_DemLeftDown_x+mx*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//�ഫ���j�a����
				my=theApp.m_DemLeftDown_y+my*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//�ഫ���j�a����
				wz=m_demInsert.GetHeightValue(mx,my,2);//�qDEM�������X���������{
				mx-=theApp.m_DemLeftDown_x;
				my-=theApp.m_DemLeftDown_y;
				ppt->x=mx;ppt->y=wz;ppt->z=-my; //�O���ഫ�᪺�]�p���I�T������				
			}
			else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//�p�G�O�z����v�Ҧ�
			{
				ppt->x=wx;ppt->y=wy;ppt->z=wz;  //�O���]�p���I�T������	
			}
			
			
			m_oldlinePtnums=myDesingScheme.PtS_JD.GetSize();//��e�u����׭즳�]�p���I��

			if(m_oldlinePtnums==0) //�p�G��e�u����רS���]�p���I,�Y�٨S���i��Ӥ�ת��]�p
			{
				myDesingScheme.PtS_JD.Add(ppt); //�[�J�]�p���I��PtS_JD�Ʋ�
				m_linePtnums=myDesingScheme.PtS_JD.GetSize();//��e�u����׭즳�]�p���I��
				
				PLineCurve pTempCurveElements = new LineCurve; //�w�q�s�����I�ܶq
				//�Ĥ@�ӳ]�p���I
				
				//���w���{=��ת��_�I���{   �w�����{=��ת��_�I���{
				pTempCurveElements->ZH=pTempCurveElements->HZ=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].StartLC;

				//�w�꨽�{=��ת��_�I���{   ��w���{=��ת��_�I���{
				pTempCurveElements->HY=pTempCurveElements->YH=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].StartLC;
				
				//��V���B���u���M���u��=0
				pTempCurveElements->Alfa=pTempCurveElements->T=pTempCurveElements->L=0;
			
				//���u�b�|�B���������B�~�ڶq�Z=0
				pTempCurveElements->R=pTempCurveElements->RoateStyle=pTempCurveElements->E=0;
				
				//�Y���B�w�M���u���B�ꦱ�u���B�����u��=0
				pTempCurveElements->P=pTempCurveElements->L0=pTempCurveElements->Ly=pTempCurveElements->Jzxc=0;

				//���I���{=��ת��_�I���{
				pTempCurveElements->JDLC=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].StartLC;

				//���IID="JD0";
				pTempCurveElements->ID="JD0";

				pTempCurveElements->x=myDesingScheme.PtS_JD.GetAt(0)->x;			//���I��x����				
				pTempCurveElements->y=fabs(myDesingScheme.PtS_JD.GetAt(0)->z);		//���I��yx����				
				pTempCurveElements->z=-myDesingScheme.PtS_JD.GetAt(0)->y;			//���I��z����

				//�[�J���I������DCurveElementss�ҪO�Ʋդ�
				myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].Add(pTempCurveElements); 
			}
			else  //�p�G��e�u����׳]�p���I��>0,��ܤw�g�i��Ӥ�ת��]�p
			{
				CPLaneRL0 dlg; 
				if(m_linePtnums<=0)
					m_linePtnums=myDesingScheme.PtS_JD.GetSize();
				tt.Format("JD%d",m_linePtnums); //���IID�۰ʼW�[
				
				dlg.m_ID=tt; //���IID
				if(dlg.DoModal()==IDOK) //�p�G���I�H���]�p���\
				{
					PLineCurve pTempCurveElements = new LineCurve; 
					
					pTempCurveElements->R=dlg.R;
					pTempCurveElements->L0=dlg.m_L0;
					pTempCurveElements->ID=dlg.m_ID;
					pTempCurveElements->P=(pTempCurveElements->L0*pTempCurveElements->L0)/(pTempCurveElements->R*24.0); 
					
					
					pTempCurveElements->x=ppt->x;
					pTempCurveElements->y=-ppt->z;
					pTempCurveElements->z=ppt->y;
					myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].Add(pTempCurveElements);
					myDesingScheme.PtS_JD.Add(ppt);
					
					
					m_linePtnums=myDesingScheme.PtS_JD.GetSize();
					
					if(myDesingScheme.PtS_JD.GetSize()>1)
						OnDraw(GetWindowDC());
					
				}
			}
			
		}
		else if(m_QueryType==SELECTFLYPATH) // �p�G�O�]�m������|
		{
			PCordinate ppt = new Cordinate;  
			if(m_ViewType==GIS_VIEW_ORTHO)	//�p�G�O���g��v�Ҧ�	
			{
				double mx=wx+m_ortho_CordinateOriginX;//�p��x����
				double my=wy+m_ortho_CordinateOriginY;//�p��y����
				mx=theApp.m_DemLeftDown_x+mx*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//�ഫ���j�a����
				my=theApp.m_DemLeftDown_y+my*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//�ഫ���j�a����
				wz=m_demInsert.GetHeightValue(mx,my,2);//�qDEM�������X���������{
				mx-=theApp.m_DemLeftDown_x; //x�����ܴ�
				my-=theApp.m_DemLeftDown_y;//y�����ܴ�
				ppt->x=mx;ppt->y=wz;ppt->z=-my; //�O��������|���T������
			}
			else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//�p�G�O�z����v�Ҧ�
			{
				ppt->x=wx;ppt->y=wy;ppt->z=wz;//�O��������|���T������
			}
			
			m_FlayPath.Add(ppt); //�N������|���T�����Цs�x��Ʋ�m_FlayPath
			OnDraw(GetDC()); //��s�T������,�Ψ����ø�s��������|
		}
	}
	else
	{
		MessageBox("���п���I������T , �к�T����I!");
		m_bSearchDistencePtNums=0;
	}
}

//ø�s�Ŷ��d�߼лx
void CT3DSystemView::DrawSearchPoint()
{
 
    glViewport(0 ,  0 ,  WinViewX ,  WinViewY) ; // ���s�]�m���f�j�p
	if(m_QueryType==QUERY_COORDINATE) //�T���Ŷ����Ьd��
	{
		if(pt1[0]!=-99999)
		{
			glLineWidth(m_QueryLineWidth) ; // �]�m�d�߼лx�u�e��
			glColor3f(m_QueryColorR/255.0 , m_QueryColorG/255.0 , m_QueryColorB/255.0) ; // �]�m�d�߼лx�u�C��
			//ø�s�Q�r���d�߼лx�u
			glBegin(GL_LINES);
				glVertex3f(pt1[0]-m_shizxLength , pt1[1] , pt1[2]);
				glVertex3f(pt1[0]+m_shizxLength , pt1[1] , pt1[2]);
				glEnd();
				
				glBegin(GL_LINES);
				glVertex3f(pt1[0] , pt1[1] , pt1[2]-m_shizxLength);
				glVertex3f(pt1[0] , pt1[1] , pt1[2]+m_shizxLength);
				glEnd();
				
				glBegin(GL_LINES);
				glVertex3f(pt1[0] , pt1[1] , pt1[2]);
				glVertex3f(pt1[0] , pt1[1]+m_shuzxHeight , pt1[2]);
			glEnd();
		}

	}
	else if(m_QueryType==QUERY_DISTENCE && m_bSearchDistencePtNums==2)//�T���Ŷ��Z���d��(�b��ܨ�ӪŶ��I����~����p��Ŷ��Z��)
	{
		glLineWidth(m_QueryLineWidth) ; // �]�m�d�߼лx�u�e��
		glColor3f(m_QueryColorR/255.0 , m_QueryColorG/255.0 , m_QueryColorB/255.0) ; // �]�m�d�߼лx�u�C��
		
		//ø�s�Q�r���d�߼лx�u
		glBegin(GL_LINES);
		glVertex3f(pt1[0]-m_shizxLength , pt1[1] , pt1[2]);
		glVertex3f(pt1[0]+m_shizxLength , pt1[1] , pt1[2]);
		glEnd();
		
		glBegin(GL_LINES);
		glVertex3f(pt1[0] , pt1[1] , pt1[2]-m_shizxLength);
		glVertex3f(pt1[0] , pt1[1] , pt1[2]+m_shizxLength);
		glEnd();
		
		glBegin(GL_LINES);
		glVertex3f(pt1[0] , pt1[1] , pt1[2]);
		glVertex3f(pt1[0] , pt1[1]+m_shuzxHeight , pt1[2]);
		glEnd();
		
		
		glBegin(GL_LINES);
		glVertex3f(pt2[0]-m_shizxLength , pt2[1] , pt2[2]);
		glVertex3f(pt2[0]+m_shizxLength , pt2[1] , pt2[2]);
		glEnd();
		
		glBegin(GL_LINES);
		glVertex3f (pt2[0] , pt2[1] , pt2[2]-m_shizxLength);
		glVertex3f (pt2[0] , pt2[1] , pt2[2]+m_shizxLength);
		glEnd();
		
		glBegin(GL_LINES);
		glVertex3f(pt2[0] , pt2[1] , pt2[2]);
		glVertex3f(pt2[0] , pt2[1]+m_shuzxHeight , pt2[2]);
		glEnd();
		
		
		glBegin(GL_LINES);
		glVertex3f(pt1[0] , pt1[1] , pt1[2]);
		glVertex3f(pt2[0] , pt2[1] , pt2[2]);
		glEnd();

		glLineWidth(1.0);

	}
	else if(m_QueryType==SELECTLINE ||myDesingScheme.PtS_JD.GetSize()>0 )//�p�G��e�w�g�T����u���A
	{
		//ø�s�ﵲ�L�{�����]�p���I�s�u
		m_oldlinePtnums=m_linePtnums;
		glColor3f(0,0,1);
		glLineWidth(2.0);
	
		
		if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//�p�G�O�z����v�Ҧ�
		{
			for (int i=0;i<myDesingScheme.PtS_JD.GetSize()-1;i++)
			{
				DrawCenterLine(i,TRUE,m_currentSchemeIndexs); //ø�s�u�����߽u
			}
		}
		else if(m_ViewType==GIS_VIEW_ORTHO)		//�p�G�O���g��v�Ҧ�
		{
			
			for (int i=0;i<myDesingScheme.PtS_JD.GetSize()-1;i++)
			{
				DrawCenterLine(i,TRUE,m_currentSchemeIndexs);//ø�s�u�����߽u
			}
		}
	}

}



//�T�����в�����
void CT3DSystemView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(theApp.bLoginSucceed==FALSE) //�O�ҥ����}���ت����p�U,���ݭn�T�����в������
		return ; //��^
	
	if(m_bmouseView==TRUE) //�p�G���б���������}��
	{
		mCamraUpdate(); //�ھڹ��ЩM��L��{�T�������۾������ʩM���౱��
		OnDraw (GetDC()); //��s�T������
		
	}
	CView::OnMouseMove(nFlags, point);
}

//�ھڹ��ЩM��L��{�T�������۾������ʩM���౱��
void CT3DSystemView::mCamraUpdate()
{
	CVector3 vCross = CrossProduct(m_vView - m_vPosition, m_vUpVector); //�e�n�p��
	m_vStrafe = Normalize(vCross); //vCross�k�@��
	SetViewByMouse(); //�q�L���й�{�۾�����
	CheckForMovement();//�q�L��L��{�۾�����
	m_vPosition.y+=(m_viewHeight-m_oldviewHeight); //�s���۾����Iy����
	m_oldviewHeight=m_viewHeight; //�O����e�۾����I����
}

//�q�L���й�{�۾�����
void CT3DSystemView::SetViewByMouse()
{
	if(m_bmouseView==false) //�p�G���б������������,��^
		return;
 
	float angleY = 0.0f;							
	float angleZ = 0.0f;							
	static float currentRotX = 0.0f;
	
	POINT mousePos;									
	GetCursorPos(&mousePos);//�o����Ъ���m�A�H�̹����Ъ��,�s�x��	mousePos�ܶq��			
	
	//�p�G���Ч��ШS���ܤ�,��^
	if( (mousePos.x == m_oldMousePos.x) && (mousePos.y == m_oldMousePos.y) )
		return;
	
   /* �﹫��y���Ыe�ᤧ�t�i���Y�p(�o���Y�p500��,�o�ӭȥi�ھڹ�ڦa�γ]�m),�p�GangleY��
	�Ӥj,��ܧY�Ϲ���y���Ыe�ᤧ�t�ܤp,�]�|�ɭP�T���a�γ����bY��V�W�ܤƫܤj*/
	angleY = (float)( (m_oldMousePos.x - mousePos.x) ) / 500.0f;

	/* �﹫��z���Ыe�ᤧ�t�i���Y�p(�o���Y�p4000��,�o�ӭȥi�ھڹ�ڦa�γ]�m),�p�GangleZ��
	�Ӥj,��ܧY�Ϲ���z���Ыe�ᤧ�t�ܤp,�]�|�ɭP�T���a�γ����bZ��V�W�ܤƫܤj*/
	angleZ = (float)( (m_oldMousePos.y - mousePos.y) ) / 4000.0f;
	
	currentRotX -= angleZ;  
	
	CVector3 vAxis = CrossProduct(m_vView - m_vPosition, m_vUpVector); //�e�n�p��
	vAxis = Normalize(vAxis);	//vAxis�k�@��
	
	RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);//�q�L���б���۾�������(�������)
	RotateView(angleY, 0, 1, 0);//�q�L���б���۾�������(�������)

	m_oldMousePos.x=mousePos.x;		//�O����e����x����
	m_oldMousePos.y=mousePos.y;		//�O����e����y����
		
}

//�q�L���б���۾�������(�������)
void CT3DSystemView::RotateView(float angle, float x, float y, float z)
{
	CVector3 vNewView;
	
	CVector3 vView = m_vView - m_vPosition;	//�۾����I�P�[���I�T�����Юt��	
	
	float cosTheta = (float)cos(angle); //�o����������cos��ƭ�
	float sinTheta = (float)sin(angle);//�o����������sin��ƭ�
	
	vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)		* vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;
	
	vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)		* vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;
	
	vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)		* vView.z;
	
	m_vView = m_vPosition + vNewView; //�o�����᪺�۾����I����

	GetNorthPtangle(); //�p��������_�w���V����
}

//�bZ�b��V�W���ʮɳ]�m�۾��[���I�M���I����
void CT3DSystemView::MoveCamera(float speed)
{
	CVector3 vVector = m_vView - m_vPosition;//�۾����I�P�[���I�T�����Юt��
	vVector = Normalize(vVector); //�۾����I�P�[���I�T�����Юt���k�@��
	m_vPosition.x += vVector.x * speed;	//�۾����Ix�s����	
	m_vPosition.z += vVector.z * speed;	//�۾����Iz�s����	
	m_vView.x += vVector.x * speed;		//�۾��[���Ix�s����
	m_vView.z += vVector.z * speed;		//�۾��[���Iz�s����
}

//�ھ���L����Ȩӭ��s�]�m�۾�
void CT3DSystemView::CheckForMovement()
{
	if(m_keynumber ==1)	// ���W�b�Y����A�V�����~����(Z�b����V)
	{		
		MoveCamera(m_Step_Z); //�bZ�b��V�W���ʮɳ]�m�۾��[���I�M���I����
	}
	
	if(m_keynumber ==2) 	// ���U�b�Y����A�V�����~����(Z�b�t��V)
	{
		MoveCamera(-m_Step_Z);	//�bZ�b��V�W���ʮɳ]�m�۾��[���I�M���I����
	}
	
	if(m_keynumber ==3)	// �����b�Y����A�V����V���ʳ���(X�b�t��V)
	{
		StrafeCamera(-m_Step_X);	//�bX�b��V�W���ʮɳ]�m�۾��[���I�M���I����
	}

	if(m_keynumber ==4)	// ���k�b�Y����A�V�k��V���ʳ���(X�b����V)
	{
		StrafeCamera(m_Step_X);	//�bX�b��V�W���ʮɳ]�m�۾��[���I�M���I����
	}

	Derx=m_vPosition.x-m_oldvPosition.x;//�۾����I�bX��V�W���ܤƶq�t��
	Derz=m_vPosition.z-m_oldvPosition.z;//�۾����I�bZ��V�W���ܤƶq�t��
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	
	//�p�G�۾����I�bX��V�W��Z��V�W���ܤƶq�t��>=DEM�a�Τl�����`�e�׮�,�դJ�s���a�ζ�
	if(fabs(Derz)>=theApp.m_Dem_BlockWidth || fabs(Derx)>=theApp.m_Dem_BlockWidth)
	{
		if(m_loddem_StartRow!=1 && m_loddem_StartCol!=1 \
			&& m_loddem_EndRow!=theApp.m_BlockRows && m_loddem_EndCol!=theApp.m_BlockCols)
		{
// 			LoadNewData();
		}
	}
}

//�bX�b��V�W���ʮɳ]�m�۾��[���I�M���I����
void CT3DSystemView::StrafeCamera(float speed)
{
	m_vPosition.x += m_vStrafe.x * speed;	//�۾����Ix�s����
	m_vPosition.z += m_vStrafe.z * speed;	//�۾����Iz�s����
	m_vView.x += m_vStrafe.x * speed;	//�۾��[���Ix�s����
	m_vView.z += m_vStrafe.z * speed;	//�۾��[���Iz�s����
}

//��L���U�T�����
void CT3DSystemView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  m_keynumber=0;

   switch (nChar) //�ھګ���r�ŨӶi������]�m
   {
   case VK_LEFT:  
	   m_keynumber=3;
	   m_xTrans-=m_Step_X;	//�bX��V�W���ʪ��Z���֭p
	   OnDraw (GetDC());	//��s�T������
	   break;
   case VK_RIGHT:
	   m_keynumber=4;
	   m_xTrans+=m_Step_X;	//�bX��V�W���ʪ��Z���֭p
	   OnDraw (GetDC());	//��s�T������
	   break;
   case VK_UP:
		m_zTrans -= m_Step_Z;	//�bZ��V�W���ʪ��Z���֭p
	    m_keynumber=1;
	   OnDraw (GetDC());	//��s�T������
	   break;
   case VK_DOWN:
		m_zTrans += m_Step_Z;	//�bZ��V�W���ʪ��Z���֭p
		m_keynumber=2;
	   OnDraw (GetDC());	//��s�T������
	   break;
	case 'F':     
		m_ViewWideNarrow += 1.0;	//��������W�j,�ݨ������d��W�j�F,�۷��۾����Y�V�̹��~��V����	
		OnDraw (GetDC());//��s�T������
		break;
	case 'V':     
		m_ViewWideNarrow -= 1.0;    //���������p,�ݨ������d���p�F,�۷��۾����Y�V�̹��̤�V����
		OnDraw (GetDC());//��s�T������
		break;
	case 'H':     					   //�����U��
		m_ViewUpDown -= 0.2;
		OnDraw (GetDC());//��s�T������
		break;
	case 'N':     					   //�����W��
		m_ViewUpDown += 0.2;
		OnDraw (GetDC());//��s�T������
		break;
	case 'J':     					   //�[�t
		m_flyspeed -= 1;
		if(m_flyspeed<=1)
			m_flyspeed=1;
		SetFLyTimer();//�]�m����p�ɾ�
		break;
	case 'M':     					   //��t
		m_flyspeed += 1;
		SetFLyTimer();//�]�m����p�ɾ�
		break;
	case 'G':     
		m_StaticHeight=m_StaticHeight*1.1;
		OnDraw (GetDC());//��s�T������
		break;
	case 'B':     
		m_StaticHeight=m_StaticHeight/1.1; //��֩T�w���氪��
		OnDraw (GetDC());//��s�T������
		break;
	case VK_F2:								 //��ܺ��C�������U
		DisplayHelp();					   
		break;
	case 'Z':								//�u��׽u���C
		OnFlyRoutinschemeline();					   
		break;
	case 'S':								//�����
		OnFlyStop();					   
		break;
	case 'P':								//�}�l/�Ȱ�����
		OnFlyPlaypause();					   
		break;
   }
	mCamraUpdate();	//���s�վ�۾�
	m_keynumber=0; //��_����0��

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//���U���Хk���T�����
void CT3DSystemView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_QueryType=-1;//�����T���Ŷ��d��,��u�]�p�B������|�]�m

	m_bmouseView=FALSE; //�������б��۾�����
	m_OrthoZommPan=-1;	//�������g��v�Ҧ��U��������
	
	CView::OnRButtonDown(nFlags, point);
}


//���"���g��v�Ҧ�"�T�����
void CT3DSystemView::OnMenuProjecttionortho() 
{
 	m_stereo=FALSE; //����
	m_ViewType =GIS_VIEW_ORTHO; //���g��v�Ҧ�
	SetProjection(); //���s�]�m
	OnDraw (GetDC());	//��s�T������
}

//"���g��v�Ҧ�"�]�m/�����襤�лx
void CT3DSystemView::OnUpdateMenuProjecttionortho(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ViewType ==GIS_VIEW_ORTHO);//�ھ�m_ViewType�ȬO�_�]�m�襤�лx
	
}

void CT3DSystemView::OnMenuPerspective() 
{
	m_ViewType =GIS_VIEW_PERSPECTIVE;
	SetProjection();//���s�]�m
	OnDraw (GetDC());	//��s�T������
	
}

//"�z����v�Ҧ�"�]�m/�����襤�лx
void CT3DSystemView::OnUpdateMenuPerspective(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ViewType ==GIS_VIEW_PERSPECTIVE);//�ھ�m_ViewType�ȬO�_�]�m�襤�лx
		pCmdUI->Enable(TRUE);
}


//�ھڧ�v�Ҧ������P,���s�]�m��v�Ѽ�
void CT3DSystemView::SetProjection()
{
	glViewport(0, 0, WinViewX, WinViewY);//�]�m���f�j�p
    glMatrixMode(GL_PROJECTION);//�N��e�x�}�]�m����v�x�}
    glLoadIdentity();//�N��e�x�}�m�������}
	
	if(m_ViewType==GIS_VIEW_ORTHO)	//�p�G��v�Ҧ������g��v�Ҧ�	
	{
		float MS=0.6; //��l���g��v���f�j�p,�o�ӭȥi�ھڦa�νd��ۦ�վ�
		if (WinViewX <= WinViewY) 
		{
			//�]�m���g��v����
			glOrtho (-MS, MS, -MS*(GLfloat)WinViewY/(GLfloat)WinViewX, 
				MS*(GLfloat)WinViewY/(GLfloat)WinViewX, -1,1);
			
			m_ViewXYscale=(GLfloat)WinViewY/(GLfloat)WinViewX;//�s�x���f�e�����
		}
		else 
		{
			//�]�m���g��v����
			glOrtho (-MS*(GLfloat)WinViewX/(GLfloat)WinViewY, 
				MS*(GLfloat)WinViewX/(GLfloat)WinViewY, -MS, MS, -1, 1);
			
			m_ViewXYscale=(GLfloat)WinViewX/(GLfloat)WinViewY;//�s�x���f�e�����
		}
	}
	else if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//�p�G��v�Ҧ����z����v�Ҧ�
	{
		//�]�m�z����v����
		gluPerspective(50.0 + m_ViewWideNarrow , m_aspectRatio , m_near , m_far);	
	}

	glMatrixMode(GL_MODELVIEW); //�N��e�x�}�]�m���ҫ��x�}		
	glLoadIdentity();   //�N��e�x�}�m�������}       
	
}

//ø�s���g��v�ޤW���T���a��
void CT3DSystemView::DrawTerrain_ORTHO()
{
	if(theApp.bLoginSucceed==FALSE || m_bLoadInitDemData==FALSE)
		return;
		

	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_TEXTURE_2D) ; // ����2D���z�M�g�\��
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // ���TEXTURE0���]�m�ؼ�
	glEnable(GL_TEXTURE_2D) ; // �E��TEXTURE0�椸
	
	glActiveTextureARB(GL_TEXTURE1_ARB) ; // ���TEXTURE1���]�m�ؼ�
	glEnable(GL_TEXTURE_2D) ; // �E��TEXTURE1�椸 , �ҥ�2D���z�M�g
	glTexEnvi(GL_TEXTURE_ENV ,  GL_TEXTURE_ENV_MODE ,  GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV ,  GL_RGB_SCALE_ARB ,  2);
	glMatrixMode(GL_TEXTURE); //�w�q�x�}���ҫ����z�x�}
	glLoadIdentity() ; // �N��e�x�}�m�������x�}
	glDisable(GL_TEXTURE_2D) ; // �������z�\��
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // ���TEXTURE0���]�m�ؼ�
	SetDrawMode() ; // 
				
	glClearDepth(1.0f); 
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LESS); 
	
    glViewport(0, 0, WinViewX, WinViewY);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho (-m_OrthoViewSize*m_ViewXYscale, m_OrthoViewSize*m_ViewXYscale,-m_OrthoViewSize,m_OrthoViewSize,-1,1);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();  
	
	glTranslatef(m_OrthotranslateX,m_OrthotranslateY,0);//����

	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		
	int nCount=0;
		
	for(int j=0;j<m_LodDemblockNumber;j++)
	{
		memset(m_pbQuadMat[j],0,m_nMapSize*m_nMapSize);
	}

	//�s����ܦC��
	 glNewList(m_TerrainList,GL_COMPILE_AND_EXECUTE);

	 m_RenderDemblockNumber=0;
	 glColor3f(1,0,1);
	 for(int i=0;i<m_LodDemblockNumber;i++)
	 {
		   mCurrentTextID=i;
			m_CurrentDemArrayIndex=i;
			glBindTexture(GL_TEXTURE_2D, m_demTextureID[i]);//�j�w���z
			m_lodDemBlock[i][3]=0;
			m_RenderDemblockNumber++;
			m_lodDemBlock[i][3]=1;
			DrawBlockOrtho(i); //ø�s�a�ζ�
	}

	glEndList();
	  
		
	CString strText;
	strText.Format("�i���s/��V���ơj=%d/%d",m_LodDemblockNumber,m_RenderDemblockNumber);
		pMainFrame->Set_BarText(0,strText,0); 

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);
	
	glActiveTextureARB(GL_TEXTURE0_ARB);		
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

//ø�s���g��v�Ҧ��U�a�ζ�
void CT3DSystemView::DrawBlockOrtho(int DemBlockIndex)
{
	float mcolorR,mcolorG;
	
	//�a�ζ�����x,y����
	double centerx=m_DemBlockCenterCoord[DemBlockIndex][0];
	double centery=fabs(m_DemBlockCenterCoord[DemBlockIndex][1]);
	
	
	double m_leftDownx,m_leftDowny,m_RightUpx,m_RightUpy;
	
	double Lx=(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);
	double Ly=(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y);
	
	m_leftDownx=centerx-theApp.m_Dem_BlockWidth/2-Lx/2;
	m_leftDowny=centery-theApp.m_Dem_BlockWidth/2-Ly/2;
	if((centerx+theApp.m_Dem_BlockWidth/2)>Lx)
		m_RightUpx=Lx-Lx/2;
	else
		m_RightUpx=centerx+theApp.m_Dem_BlockWidth/2-Lx/2;
	
	if((centery+theApp.m_Dem_BlockWidth/2)>Ly)
		m_RightUpy=Ly-Ly/2;
	else
		m_RightUpy=centery+theApp.m_Dem_BlockWidth/2-Ly/2;
	
	
	float m_scaleX=1.0/(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);
	float m_scaleY=1.0/(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y);
	double x1,y1,x2,y2;
	x1=m_leftDownx*m_scaleX;
	y1=m_leftDowny*m_scaleX;
	x2=m_RightUpx*m_scaleX;
	y2=m_RightUpy*m_scaleX;
	
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0.0f,0.0f);
	GetOrthoColor(x1,y1,&mcolorR,&mcolorG);
	glColor3f(mcolorR,mcolorG,0.5);
	glVertex2f(x1,y1);
	
	glTexCoord2f(1.0f,0.0f);
	GetOrthoColor(x2,y1,&mcolorR,&mcolorG);
	glColor3f(mcolorR,mcolorG,0.5);
	glVertex2f(x2,y1);
	
	glTexCoord2f(1.0f,1.0f);
	GetOrthoColor(x2,y2,&mcolorR,&mcolorG);
	glColor3f(mcolorR,mcolorG,0.5);
	glVertex2f(x2,y2);
	
	glTexCoord2f(0.0f,1.0f);
	GetOrthoColor(x1,y2,&mcolorR,&mcolorG);
	glColor3f(mcolorR,mcolorG,0.5);
	glVertex2f(x1,y2);
	glEnd();
	
}

void CT3DSystemView::GetOrthoColor(double x1, double y1, float *mColorR, float *mColorG)
{
	//return;
	double mx=(x1+m_ortho_CordinateOriginX)*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x)+theApp.m_DemLeftDown_x;
	double my=(y1+m_ortho_CordinateOriginY)*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)+theApp.m_DemLeftDown_y;
	double mz=m_demInsert.GetHeightValue(mx,my,2);
	//�̰����� 255,0,0  �̧C��� 0,255,0
	//Dr=255 DG=-255 DB=0
	*mColorR=(mz-m_minHeight)/(m_maxHeight-m_minHeight);
	*mColorG=1-(mz-m_minHeight)/(m_maxHeight-m_minHeight);
}

//��j�v��
void CT3DSystemView::OnOrthoZoomIn() 
{
	m_OrthoZommPan=ORTHO_ZOOMIN;
	m_OrthoViewSize=m_OrthoViewSize/1.1;
	
	OnDraw(GetDC());
	
}
//�Y�p�v��
void CT3DSystemView::OnOrthoZoomOut() 
{
	m_OrthoZommPan=ORTHO_ZOOMOUT;
	m_OrthoViewSize=m_OrthoViewSize*1.1;
	OnDraw(GetDC()); //��s�T������
	
}

//���ʼv��
void CT3DSystemView::OnOrthoPan() 
{
	m_OrthoZommPan=ORTHO_PAN;
	OnDraw(GetDC());//��s�T������
				
}

//��_��l�j�p
void CT3DSystemView::OnOrthoZoomOrigin() 
{
	m_OrthoZommPan=ORTHO_ZOOMORIGIN;
	m_OrthoViewSize=0.3;
	OnDraw(GetDC());//��s�T������
	
}

//�}���Y��
void CT3DSystemView::OnOrthoZoomWindow() 
{
	m_OrthoZommPan=ORTHO_ZOOMWINDOW;
	OnDraw(GetDC());//��s�T������
	
}

void CT3DSystemView:: OnUpdateOnOrthoZoomIn(CCmdUI*  pCmdUI)   
{   
	pCmdUI->Enable(m_ViewType==GIS_VIEW_ORTHO);   
}

void CT3DSystemView:: OnUpdateOnOrthoZoomOut(CCmdUI*  pCmdUI)   
{   
	pCmdUI->Enable(m_ViewType==GIS_VIEW_ORTHO);   
}

void CT3DSystemView:: OnUpdateOnOrthoPan(CCmdUI*  pCmdUI)   
{   
	pCmdUI->Enable(m_ViewType==GIS_VIEW_ORTHO);   
}

void CT3DSystemView:: OnUpdateOnOrthoZoomOrigin(CCmdUI*  pCmdUI)   
{   
	pCmdUI->Enable(m_ViewType==GIS_VIEW_ORTHO);   
}

void CT3DSystemView:: OnUpdateOnOrthoZoomWindow(CCmdUI*  pCmdUI)   
{   
	pCmdUI->Enable(m_ViewType==GIS_VIEW_ORTHO);   
}

//�T�����Х����_����
void CT3DSystemView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bmouseView=false; //�������б���۾��\��
	
	//�p�G�O���g��v�Ҧ��åB�O���ʱ���Ҧ��U
	if(m_ViewType==GIS_VIEW_ORTHO && m_OrthoZommPan==ORTHO_PAN)	
	{
		int dx=point.x-m_preX;//�bX��V���ʶZ�� 
		int dy=point.y-m_preY;//�bY��V���ʶZ��
		m_OrthotranslateX+=dx*0.00007;//X�Z���ܴ��쥿�g��v�Ҧ������ʭ�
		m_OrthotranslateY+=-dy*0.00007;//Y�Z���ܴ��쥿�g��v�Ҧ������ʭ�
		OnDraw (GetDC());//��s�T������
	}
	
	CView::OnLButtonUp(nFlags, point);
}

//�T����u�]�p
void CT3DSystemView::OnMenuLinedesign() 
{
	m_OrthoZommPan=-1;
	
	if(m_QueryType==SELECTLINE) //�p�G��e�w�g�T����u���A�A�h����
		m_QueryType=-1;
	else // //�p�G��e���O�T����u���A�A�h���}
		m_QueryType=SELECTLINE;
}

//�]�m�襤���A
void CT3DSystemView::OnUpdateMenuLinedesign(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_QueryType==SELECTLINE);
}


//ø�s���g��v�Ҧ��U���T���u��
void CT3DSystemView::DrawRailwaythesme_Ortho()
{
	CString tt,strSql,m_style;
// 	long i;

	//�p�G�ƾڮw�S���[�����\�νդJ�ƾڥ��ѡA��^
	if(theApp.bLoginSucceed==FALSE || m_bLoadInitDemData==FALSE)
		return;
	
	glLineWidth(4.0);//�]�m�u�e
	SetDrawMode();//�]�mø�ϼҦ�

	glViewport(0, 0, WinViewX, WinViewY);//���s�]�m���f�j�p
	
	if(b_haveMadeRail3DwayList_Ortho==FALSE )   //�p�G�٨S���c�ؽu���T���ҫ�����ܦC��
	{

		ReLoadCenterPt();//���s�q�ƾڮw��Ū���u�����u�����I�ƾ�
		
		glNewList(m_Rail3DwayList_Ortho,GL_COMPILE_AND_EXECUTE);//�Ы���ܦC��
				
			glColor3f(0.75,0.75,0.75);//�]�m�C��
			glLineWidth(1.0);//�]�m�u�e
		
				//1. ø�s����������Y
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());//�j�w������Y���z
				for (long i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
				{
					m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
					if(m_style!="�G�D�_�I" && m_style!="�G�D�����I" &&m_style!="�G�D���I" &&m_style!="���ٰ_�I"  &&m_style!="���٤����I" &&m_style!="���ٲ��I")
					{	
						DrawBP_Ortho(i,1);//ø�s����������Y
					}
					
				}
		
				//4.ø�s�k��������Y
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());//�j�w������Y���z
				
				for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
				{
					m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//���I����
					//�p�G���I�����O�D�G�D�M���٬q���I�A�hø�s������Y		
					
					if(m_style!="�G�D�_�I" && m_style!="�G�D�����I" &&m_style!="�G�D���I" &&m_style!="���ٰ_�I"  &&m_style!="���٤����I" &&m_style!="���ٲ��I")
					{
				
					    glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());//�j�w������Y���z
						DrawBP_Ortho(i,2);//ø�s�k��������Y
						glBindTexture(GL_TEXTURE_2D, m_cTxtureSuigou.GetTxtID());//�j�w�������z
						DrawSuiGou_Ortho(i);//ø�s����
						
					}
				}
		

		//5.ø�s���߽u		
		
		m_TempPts.RemoveAll();
		PCordinate pt;
		glLineWidth(8.0);
		glColor3f(1,0,1);


		for (i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			
			//�p�G���i��u���T���ؼҡA�h�ե�DrawCenterLine()���ø�s�u�����u
			if(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()<=0)
				DrawCenterLine(i,FALSE,m_currentSchemeIndexs);//ø�s�u�����u
			else
			{
			
				tt=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;

				if(tt!="�G�D�����I" && i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x;
					pt->y=-myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z; 
					pt->strJDStyle=tt;
					m_TempPts.Add(pt);
				}
				else //�G�D�������u�����a���H�U�A��ø�s
				{		
					if(m_TempPts.GetSize()>1)
					{	
				
						glBegin(GL_LINE_STRIP);

						for(int k=0;k<m_TempPts.GetSize();k++)
						{
							tt=m_TempPts.GetAt(k)->strJDStyle;
							if(tt=="���I����" || tt=="���w�I����" || tt=="�w���I����" || tt=="���I-���w�I����")
								glColor3f(1,0,0);
							else
								glColor3f(0,0,1);

							glVertex2f(GetOrthoX(m_TempPts.GetAt(k)->x),GetOrthoY(m_TempPts.GetAt(k)->y));
						}
						glEnd();
						m_TempPts.RemoveAll();
					}			
				}
			}
		}		


		//6.ø�s�y�D
		glBindTexture(GL_TEXTURE_2D, m_cTxtureRailway.GetTxtID());//�j�w�y�D���z
		glColor3f(0.5,0,0.4);//�]�m�C��
		glLineWidth(2.0);//�]�m�u�e
		
		CString tt1,tt2;
		for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			tt1=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//��e���I����
			tt2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;//�U�@���I����
			if(tt1!="�G�D�����I"  &&  tt2!="�G�D�����I")
			{
				//�H�x�Τ覡�s���e����{�y�D�_��
				glBegin(GL_POLYGON);
				glTexCoord2f(0.0f,0.0f);//�]�m���z����(��e�y�D�_�������I)
				glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1),\
					GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1));
				
				glTexCoord2f(1.0f,0.0f); //�]�m���z����(��e�y�D�_���k���I)
				glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2),\
					GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2));
				
				glTexCoord2f(1.0f,1.0f);//�]�m���z����(�U�@�e�y�D�_���k���I)
				glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
					GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
				
				glTexCoord2f(0.0f,1.0f);//�]�m���z����(�U�@�e�y�D�_�������I)
				glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
					GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
				
				glEnd();
			}
		
		}		


		//7.ø�s�D����Y
		glBindTexture(GL_TEXTURE_2D, m_cTxtureGdToLJ.GetTxtID());//�j�w�D����Y���z		
		glColor3f(1,1,0);//�]�m�C
		for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			tt1=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//��e���I����
			tt2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;//�U�@���I����
			if(tt1!="�G�D�����I"  &&  tt2!="�G�D�����I")
			{
				
			//�H�x�Τ覡�s���覡ø�s�����D����Y
			glBegin(GL_POLYGON);
			glTexCoord2f(1.0f,0.0f);//�]�m���z����(��e�����D����Y�����I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1),\
				GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1));
			
			glTexCoord2f(1.0f,1.0f);//�]�m���z����(��e�����D����Y�k���I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
				GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
			
			glTexCoord2f(0.0f,1.0f);//�]�m���z����(�U�@�����D����Y�k���I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
			
			glTexCoord2f(0.0f,0.0f);//�]�m���z����(�U�@�����D����Y�����I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1));			
			glEnd();
			
			//�H�x�Τ覡�s���覡ø�s�k���D����Y
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//�]�m���z����(��e�k���D����Y�����I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2),\
				GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2));
			
			glTexCoord2f(0.0f,1.0f);//�]�m���z����(��e�k���D����Y�k���I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
				GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
			
			glTexCoord2f(1.0f,1.0f);//�]�m���z����(�U�@�k���D����Y�k���I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
			
			glTexCoord2f(1.0f,0.0f);//�]�m���z����(�U�@�k���D����Y�����I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2));
			
			glEnd();
			}
		}		
		


		//8.ø�s����
		glBindTexture(GL_TEXTURE_2D, m_cTxtureLJ.GetTxtID());//�j�w���ӯ��z
		glColor3f(1,0.5,0.25);//�]�m�C��
		for (i=0;i<myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			tt1=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//��e���I����
			tt2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;//�U�@���I����
			if(tt1!="�G�D�����I"  &&  tt2!="�G�D�����I")
			{
				
			//�H�x�Τ覡�s���覡ø�s��������
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//�]�m���z����(��e���������_�������I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1));
			
			glTexCoord2f(0.0f,1.0f);//�]�m���z����(��e���������_���k���I)	
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
			
			glTexCoord2f(1.0f,1.0f);;//�]�m���z����(�U�@���������_���k���I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
			
			glTexCoord2f(1.0f,0.0f);//�]�m���z����(�U�@���������_�������I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1));
						
			glEnd();
			
			//�H�x�Τ覡�s���覡ø�s�k������
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//�]�m���z����(��e�k�������_�������I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2));
			
			
			glTexCoord2f(1.0f,0.0f);//�]�m���z����(��e�k�������_���k���I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2));
			
			glTexCoord2f(1.0f,1.0f);//�]�m���z����(�U�@�k�������_���k���I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
			
			glTexCoord2f(0.0f,1.0f);//�]�m���z����(�U�@�k�������_�������I)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
			
			glEnd();
			}
		}		

		glLineWidth(1.0);//��_�u�e
		glEndList();//������ܦC��
		b_haveMadeRail3DwayList_Ortho=TRUE;//���Ѥw�g�Ы���ܦC��
	}
	else  //�p�G�w�g�c�ؽu���T���ҫ�����ܦC��,�h�����ե���ܦC��
	{ 
		glCallList(m_Rail3DwayList_Ortho); //�եνu���T���ҫ���ܦC��
	}
	

}

//ø�s���߽u
//���a���H�U��������ø�s
void CT3DSystemView::DrawCenterLine(long index, BOOL ifSelectLine, int SchemeIndex)
{
	CString tt;
	double x1,y1,z1,x2,y2,z2;
	double x0,y0,z0;
	float DerDistence=2.0;

	float Dh;
	
	m_TempPts.RemoveAll();
	
	if(ifSelectLine==TRUE) //�b��u�]�p
	{
		Dh=5;
		x1=myDesingScheme.PtS_JD.GetAt(index)->x;
		y1=myDesingScheme.PtS_JD.GetAt(index)->y;
		z1=myDesingScheme.PtS_JD.GetAt(index)->z;
		
		x2=myDesingScheme.PtS_JD.GetAt(index+1)->x;
		y2=myDesingScheme.PtS_JD.GetAt(index+1)->y;
		z2=myDesingScheme.PtS_JD.GetAt(index+1)->z;
	}
	else  //���}���خ�,ø�s���}�����
	{
		Dh=5;
		x1=myDesingScheme.PtS_3DLineZX[SchemeIndex].GetAt(index)->x;
		y1=myDesingScheme.PtS_3DLineZX[SchemeIndex].GetAt(index)->y;
		z1=myDesingScheme.PtS_3DLineZX[SchemeIndex].GetAt(index)->z;
		
		x2=myDesingScheme.PtS_3DLineZX[SchemeIndex].GetAt(index+1)->x;
		y2=myDesingScheme.PtS_3DLineZX[SchemeIndex].GetAt(index+1)->y;
		z2=myDesingScheme.PtS_3DLineZX[SchemeIndex].GetAt(index+1)->z;
		
	}
	glColor3f(0,0,1);

	PCordinate pt;
	
	double L=myDesingScheme.GetDistenceXYZ(x1,y1,z1,x2,y2,z2);
	double L0=0;
	if(m_ViewType==GIS_VIEW_ORTHO) //�p�G�O���g��v�Ҧ�
	{		
		while(L0<=L)
		{
			
			x0=x1+L0/L*(x2-x1);
			y0=y1+L0/L*(y2-y1);//���p�u���{
			z0=z1+L0/L*(z2-z1);

			//�a�����{
			float dmh=m_demInsert.GetHeightValue(x0+theApp.m_DemLeftDown_x,-z0+theApp.m_DemLeftDown_y,2);
			if(y0>=dmh-Dh) //�]�p�u�I���{�j��a�����{
			{
				pt=new Cordinate;
				pt->x =x0;
				pt->y=y0;
				pt->z =z0;
				m_TempPts.Add(pt);
			}
			else
			{
				if(m_TempPts.GetSize()>1) //�{���I�Ƥj��1
				{	
					
					glBegin(GL_LINE_STRIP); //�H��u�Φ�ø�s
					
					for(int k=0;k<m_TempPts.GetSize();k++)
					{
						glVertex2f(GetOrthoX(m_TempPts.GetAt(k)->x),GetOrthoY(-m_TempPts.GetAt(k)->z));
					}
					glEnd();
					m_TempPts.RemoveAll(); //�M��
					L0-=DerDistence;
				}
			}

			L0+=DerDistence;
			if(L0>=L)
			{
				x0=x2;
				y0=y2;
				z0=z2;
				dmh=m_demInsert.GetHeightValue(x0+theApp.m_DemLeftDown_x,-z0+theApp.m_DemLeftDown_y,2);
				if(y0>=dmh-Dh ) //�]�p�u�I���{�j��a�����{
				{
					pt=new Cordinate;
					pt->x =x0;
					pt->y=y0;
					pt->z =z0;
					m_TempPts.Add(pt);
					if(m_TempPts.GetSize()>1)
					{	
						
						glBegin(GL_LINE_STRIP); //�H��u�Φ�ø�s
						
						for(int k=0;k<m_TempPts.GetSize();k++)
						{
							glVertex2f(GetOrthoX(m_TempPts.GetAt(k)->x),GetOrthoY(-m_TempPts.GetAt(k)->z));
						}
						glEnd();
						m_TempPts.RemoveAll();
						
					}
				}
				break;
			}
		
		}
		if(m_TempPts.GetSize()>1)//�{���I�Ƥj��1
		{	
			
			glBegin(GL_LINE_STRIP);  //�H��u�Φ�ø�s
			
			for(int k=0;k<m_TempPts.GetSize();k++)
			{
				glVertex2f(GetOrthoX(m_TempPts.GetAt(k)->x),GetOrthoY(-m_TempPts.GetAt(k)->z));
			}
			glEnd();
			m_TempPts.RemoveAll();
		}
	}
	else if (m_ViewType==GIS_VIEW_PERSPECTIVE) //�p�G�O�z����v�Ҧ�
	{
		while(L0<=L)
		{
			
			x0=x1+L0/L*(x2-x1);
			y0=y1+L0/L*(y2-y1);//�p�u���{
			z0=z1+L0/L*(z2-z1);
			
			//�a�����{
			float dmh=m_demInsert.GetHeightValue(x0+theApp.m_DemLeftDown_x,-z0+theApp.m_DemLeftDown_y,2);
			if(y0>=dmh-Dh)  //�]�p�u�I���{�j��a�����{
			{
				pt=new Cordinate;
				pt->x =x0;
				pt->y=y0;
				pt->z =z0;
				m_TempPts.Add(pt);
			}
			else
			{
				if(m_TempPts.GetSize()>1)
				{	
					
					glBegin(GL_LINE_STRIP);
					
					for(int k=0;k<m_TempPts.GetSize();k++)
					{
						glVertex3f(m_TempPts.GetAt(k)->x,m_TempPts.GetAt(k)->y,
							m_TempPts.GetAt(k)->z);
						
					}
					glEnd();
					m_TempPts.RemoveAll();
					L0-=DerDistence;
				}
			}
			
			L0+=DerDistence;
			if(L0>=L)
			{
				x0=x2;
				y0=y2;
				z0=z2;
				dmh=m_demInsert.GetHeightValue(x0+theApp.m_DemLeftDown_x,-z0+theApp.m_DemLeftDown_y,2);
				if(y0>=dmh-Dh )//�]�p�u�I���{�j��a�����{
				{
					pt=new Cordinate;
					pt->x =x0;
					pt->y=y0;
					pt->z =z0;
					m_TempPts.Add(pt);
					if(m_TempPts.GetSize()>1)
					{	
						
						glBegin(GL_LINE_STRIP);
						
						for(int k=0;k<m_TempPts.GetSize();k++)
						{
							glVertex3f(m_TempPts.GetAt(k)->x,m_TempPts.GetAt(k)->y,
								m_TempPts.GetAt(k)->z);
						}
						glEnd();
						m_TempPts.RemoveAll();
						
					}
				}
				break;
			}
		}

		if(m_TempPts.GetSize()>1)
		{	
			
			glBegin(GL_LINE_STRIP);
			
			for(int k=0;k<m_TempPts.GetSize();k++)
			{
				glVertex3f(m_TempPts.GetAt(k)->x,m_TempPts.GetAt(k)->y,
					m_TempPts.GetAt(k)->z);
				
			}
			glEnd();
			m_TempPts.RemoveAll();
		}

	}
	
	
}

//�p�⥿�g��v�Ҧ��Ux����
float CT3DSystemView::GetOrthoX(double x)
{
	float xt=x/(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x)-m_ortho_CordinateOriginX;
	return xt;
	
}

//�p�⥿�g��v�Ҧ��Uy����
float CT3DSystemView::GetOrthoY(double y)
{
	float yt=y/(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)*m_ortho_CordinateXYScale-m_ortho_CordinateOriginY;
	return yt;
	
}

//�O�s�]�p���
void CT3DSystemView::OnMenuLinesavescheme() 
{
	int manswer=MessageBox("�O�_�T�{�O�s���?","�O�s���",MB_ICONQUESTION|MB_YESNO);
	if(manswer==7)
		return;
	
	b_haveMadeRail3DwayList=FALSE;
	b_haveMadeRail3DwayList_Ortho=FALSE;
	if(myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].GetSize()>0)
	{
		myDesingScheme.m_bHaveSaveScheme=TRUE;
		myDesingScheme.SavePlaneCurveData();//�O�s���u�n����ƾڮw��	
	}	
	
}


//��{�z����v�Ҧ��U���u���T���ҫ�ø�s
void CT3DSystemView::DrawRailwaythesme()
{

	//���J�ݩʰ��
	glPushAttrib(GL_DEPTH_BUFFER_BIT|GL_ENABLE_BIT|GL_POLYGON_BIT );
		glEnable(GL_DEPTH_TEST|GL_CULL_FACE);
		glCullFace(GL_BACK);

	//�p�G�ƾڮw�S���[�����\�νդJ�ƾڥ��ѡA��^
	if(theApp.bLoginSucceed==FALSE || m_bLoadInitDemData==FALSE)
		return;
	
	CString tt,strSql;
	CString m_style,m_stylePre,m_styleNext;
	PCordinate pt;
	

	SetDrawMode();//�]�mø�ϼҦ�
	glViewport(0, 0, WinViewX, WinViewY); //���s�]�m���f�j�p
	
	
	if(b_haveMadeRail3DwayList==FALSE )  //�p�G�٨S���c�ؽu���T���ҫ�����ܦC��
	{

		
		ReLoadCenterPt();//���s�q�ƾڮw��Ū���u�����u�����I�ƾ�
			


		glNewList(m_Rail3DwayList,GL_COMPILE_AND_EXECUTE); //�Ы���ܦC��
		
		glColor3f(0.75,0.75,0.75);//�]�m�C��
		glLineWidth(2.0);//�]�m�u�e
		

		//1. ø�s���[
		myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].RemoveAll();
		myDesingScheme.GetBirdgeQDcordinate(m_Bridge.m_Bridge_QDSpace);//�ھھ��[���Z�p��]�m���[����
		for (long i=0;i<myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetSize();i++)
		{
		 	DrawSceneQD(myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->y1,\
				myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->z1,
				myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->y2,\
				myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->z2,
				myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->QDHeight);
		}		

		
		//2. �p���������T������
		myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].RemoveAll();
		myDesingScheme.GetBirdgeLGcordinate(m_Bridge.m_Bridge_HLSpace);//�ھھ�������Z�p��]�m���������
		
		//3. ø�s����������Y
		glColor3f(1,0,0);		
		int mBridgeIndex=0;//���٪�l���޸�
		glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID()); //�j�w������Y���z
		for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle; //���I����
			m_styleNext=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;	
		
			//�p�G���I�����O�D�G�D�M���٬q���I�A�hø�s������Y
			if(m_style!="�G�D�_�I" && m_style!="�G�D�����I" &&m_style!="�G�D���I" \
				&&m_style!="���٤����I" &&m_style!="���ٲ��I" && m_styleNext!="�G�D�_�I" )
			{	
				DrawBP(i,1); //ø�s����������Y
				
			}
			if(m_style=="���ٰ_�I" || m_style=="���ٲ��I")	
			{
				
				glColor3f(0.5,0,1);
				if(i>0)
				{
					//�U�@�I�B�����I����
					m_styleNext=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;
						//���ٰ_���I�B�@�Y
						//(�W�h�p�U:�p�G�O���٪����۳s,�h���ݭnø�s�@�Y)
						int Innum;
						//ø�s���٤U���@�Y��
						if(m_style=="���ٰ_�I")
							Innum=i;//i-1;
						else if(m_style=="���ٲ��I")
							Innum=i+1;
						
						//ø�s���٤U���@�Y��
						DrawQDHP(Innum,m_style,m_Bridge.m_Bridge_HPangle/180.0*PAI,m_styleNext,mBridgeIndex);
				
				}
				if(m_style=="���ٲ��I")
					mBridgeIndex++;
			}
		}


		//4.ø�s�k��������Y
		glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());//�j�w������Y���z
		for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//���I����
			m_styleNext=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;//�U�@�I�����I����
			

			//�p�G���I�����O�D�G�D�M���٬q���I�A�hø�s������Y		
			if(m_style!="�G�D�_�I" && m_style!="�G�D�����I" &&m_style!="�G�D���I" \
				&&m_style!="���٤����I" &&m_style!="���ٲ��I" && m_styleNext!="�G�D�_�I")
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				DrawBP(i,2);//ø�s�k��������Y
				
			}
			if(m_style!="�G�D�_�I" && m_style!="�G�D�����I"  \
				&& m_style!="���ٰ_�I" && m_style!="���٤����I" && m_style!="�G�D�����I" )
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureSuigou.GetTxtID());//�j�w�������z
				DrawSuiGou(i);//ø�s����
				
			}
		}
	


		//5.ø�s�u�����u
		glLineWidth(3.0);
		m_TempPts.RemoveAll();
		for ( i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1;i++)
		{

			//�p�G���i��u���T���ؼҡA�h�ե�DrawCenterLine()���ø�s�u�����u
			if(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()<=0)
				DrawCenterLine(i,FALSE,m_currentSchemeIndexs); //ø�s�u�����u
			else
			{				
				tt=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//���I����
				
				if(tt!="�G�D�����I" && i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x;
					pt->y=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->y; 
					pt->z=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z; 
					pt->strJDStyle=tt;
					m_TempPts.Add(pt);
				}
				else //�G�D�������u�����a���H�U�A��ø�s
				{		
					if(m_TempPts.GetSize()>1)
					{	
						
						glBegin(GL_LINE_STRIP);
						
						for(int k=0;k<m_TempPts.GetSize();k++)
						{
							tt=m_TempPts.GetAt(k)->strJDStyle;
							if(tt=="���I����" || tt=="���w�I����" || tt=="�w���I����" || tt=="���I-���w�I����")
								glColor3f(1,0,0);
							else
								glColor3f(0,0,1);
							glVertex3f(m_TempPts.GetAt(k)->x,m_TempPts.GetAt(k)->y,m_TempPts.GetAt(k)->z);							
						}
						glEnd();
						m_TempPts.RemoveAll();
					}
				}
			}
		}	


	
		///////////////////////////////
       //6.ø�s�y�D
		glBindTexture(GL_TEXTURE_2D, m_cTxtureRailway.GetTxtID()); //�j�w�y�D���z
	 	glLineWidth(2.0);//�]�m�u�e
		for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			
			if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Derh==0) //�p�G����0
				glColor3f(0,1,1); //�]�m�C��
			else
				glColor3f(1,0,1); //�]�m�C��
			float L=myDesingScheme.GetDistenceXY(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
		
			//�H�x�Τ覡�s���e����{�y�D�_��	
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f); //�]�m���z����(��e�y�D�_�������I)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1);
			glTexCoord2f(1.0f,0.0f); //�]�m���z����(��e�y�D�_���k���I)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(1.0f,L/10);//�]�m���z����(�U�@�e�y�D�_���k���I)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(0.0f,L/10); //�]�m���z����(�U�@�e�y�D�_�������I)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			
			glEnd();

		}		
	
		//7.ø�s�D����Y
		glBindTexture(GL_TEXTURE_2D, m_cTxtureGdToLJ.GetTxtID());//�j�w�D����Y���z
		glColor3f(1,1,0);//�]�m�C��
		for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			//�H�x�Τ覡�s���覡ø�s�����D����Y	
			glBegin(GL_POLYGON);
			glTexCoord2f(1.0f,0.0f);//�]�m���z����(��e�����D����Y�����I)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1);
			glTexCoord2f(1.0f,1.0f);//�]�m���z����(��e�����D����Y�k���I)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glTexCoord2f(0.0f,1.0f);//�]�m���z����(�U�@�����D����Y�k���I)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glTexCoord2f(0.0f,0.0f);//�]�m���z����(�U�@�����D����Y�����I)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1);
			
			glEnd();
			
			//�H�x�Τ覡�s���覡ø�s�k���D����Y
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//�]�m���z����(��e�k���D����Y�����I)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(0.0f,1.0f);//�]�m���z����(��e�k���D����Y�k���I)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(1.0f,1.0f);//�]�m���z����(�U�@�k���D����Y�k���I)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(1.0f,0.0f);//�]�m���z����(�U�@�k���D����Y�����I)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glEnd();
		}		
		
		//8.ø�s����
		glBindTexture(GL_TEXTURE_2D, m_cTxtureLJ.GetTxtID());//�j�w���ӯ��z
		glColor3f(1,0.5,0.25);//�]�m�C��
		for (i=0;i<myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			//�H�x�Τ覡�s���覡ø�s��������	
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//�]�m���z����(��e���������_�������I)
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1);
			glTexCoord2f(0.0f,1.0f);//�]�m���z����(��e���������_���k���I)	
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glTexCoord2f(1.0f,1.0f);//�]�m���z����(�U�@���������_���k���I)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glTexCoord2f(1.0f,0.0f);//�]�m���z����(�U�@���������_�������I)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1);
			
			glEnd();			

			//�H�x�Τ覡�s���覡ø�s�k������	
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//�]�m���z����(��e�k�������_�������I)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(1.0f,0.0f);//�]�m���z����(��e�k�������_���k���I)
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(1.0f,1.0f);//�]�m���z����(�U�@�k�������_���k���I)
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(0.0f,1.0f);//�]�m���z����(�U�@�k�������_�������I)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			
			glEnd();
		}		

		//9.ø�s�������
		DrawBridgeHL();

		//10.ø�s�G�D	
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].RemoveAll();//�G�D���мƾڼƲղM��
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].RemoveAll();//�G�D�H���ƾڼƲղM��
		//�ե�GetTunnelcordinate()��ƭ��s�p���G�D����
		myDesingScheme.GetTunnelcordinate(m_Tunnel.height,\
			m_Tunnel.Archeight,\
			m_Tunnel.WallHeight,\
			m_Tunnel.width/2.0,\
			m_Tunnel.ArcSegmentNumber);
		DrawTunnel(); //ø�s�G�D	
	
		glLineWidth(1.0);//��_�u�e
		glEndList();//������ܦC��
	
		b_haveMadeRail3DwayList=TRUE; //���Ѥw�g�Ы���ܦC��
	}
	else //�p�G�w�g�c�ؽu���T���ҫ�����ܦC��,�h�����ե���ܦC��
	{
		glCallList(m_Rail3DwayList);  //�եνu���T���ҫ���ܦC��
	}
	glPopAttrib();//�u�X�ݩʰ��
}

void CT3DSystemView::DrawBP(long index, int BPside)
{


	float mNCDistence=4.0;
	long i=index;

	int j;


	if(BPside==1) //����Y
	{
		
		int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_L;
		int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_L;

		if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->TW_left==0 ||\
			myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->TW_right==0)
				glColor3f(0,1,1);
		else
				glColor3f(1,0,0);
		
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				
				//�p�G���������ۦP(�P�����թθ���)
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f); 
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z);
					glTexCoord2f(0.0f,0.0f); 
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f); 
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,1.0f); 
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z);
					glEnd();
				}
				else  //�p�G���������ۦP(����,�����۳s)
				{
					
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z);
					glEnd();
					


	
					glBegin(GL_POLYGON);
						glTexCoord2f(0.0f,0.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z);
						glTexCoord2f(0.5f,0.5f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].z);
						glTexCoord2f(0.5f,1.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z);
						glTexCoord2f(1.0f,0.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
						glEnd();
	
					

					
				}
				if(j>0) 
					{
						glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
						glBegin(GL_POLYGON);
						glTexCoord2f(0.0f,0.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
						glTexCoord2f(1.0f,0.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z);
						glTexCoord2f(1.0f,1.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z);
						glTexCoord2f(0.0f,1.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
						glEnd();
	
					
					}
	
			}
		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z);
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z);
					glEnd();
					
				
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z);
					glEnd();
					
				}
			

				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
					
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glEnd();
				}

			}
			
		}
		
	}
	else if(BPside==2) 
	{
		
		int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_R;
		int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_R;
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z);
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z);
					glEnd();
					

			
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glEnd();
			

					
				}
				
				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());

					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glEnd();
				}
			}
		


		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z);
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z);
					glEnd();
					
						
		
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z);
					glEnd();
	
				}
				
				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glEnd();
				}
			}

		}
		
	}
	
	glLineWidth(1.0);
	glColor3f(1,1,1);

	
	

}

void CT3DSystemView::DrawBP_Ortho(long index, int BPside)
{

	float mNCDistence=4.0;
	long i=index;

	int j;


	glLineWidth(2.0);
	glColor3f(1,0,0);

	if(BPside==1) 
	{
		
		int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_L;
		int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_L;
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				
				
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f); 
			
			
			
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z));
					
					glTexCoord2f(0.0f,0.0f); 
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f); 
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,1.0f); 
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z));
					
					glEnd();
				}
				else 
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z));
					
					glEnd();
					


					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z));
					
					glTexCoord2f(0.5f,0.5f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].z));
					
					glTexCoord2f(0.5f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
					
					glEnd();


					
				}
			
	
				if(j>0) 
					{
						glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
					
						
						glBegin(GL_POLYGON);
						glTexCoord2f(0.0f,0.0f);
 
 
 
						glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
							GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
						
						glTexCoord2f(1.0f,0.0f);
 
 
 
						glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x),\
							GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z));
						
						glTexCoord2f(1.0f,1.0f);
 
 
 
						glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x),\
							GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z));
						
						glTexCoord2f(0.0f,1.0f);
 
 
 
						glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
							GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
						
						glEnd();
	
					
					}
	
			}
		
			
		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z));
					
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z));
					
					glEnd();
					
				
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z));
					
					glEnd();
					
				}
			

				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
					
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
					
					glEnd();
				}

			}
			
		}
		
	}
	else if(BPside==2) 
	{
		
		int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_R;
		int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_R;
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z));
					
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z));
					
					glEnd();
					

			
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].z));
					
					glTexCoord2f(1.0f,1.0f);
	
	
	
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
						
					glEnd();
			

					
				}
				
				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());

					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
					
					glEnd();
				}
			}
		


		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z));
					
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z));
					
					glEnd();
					
						
		
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z));
					
					glEnd();
	
				}
				
				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
					
					glEnd();
				}
			}

		}
		
	}
	
	glLineWidth(1.0);
	glColor3f(1,1,1);

}

void CT3DSystemView::DrawSuiGou(long index)
{
	glColor3f(1.0,0.4,1);
	glLineWidth(2.0);

 /*
 //4.�D���k���������I����
	/*
	�Ƥ�����4���I�T�w,���O��1-4���I,�䤤0���I��LjToBp�I,�w�s�x
		5____4  1____0
   (b4) \     /(b3)
		3\___/2

	�䤤:
	�����`�� SuiGou_h,
	�������e�� SuiGou_b1,
	�������e�� SuiGou_b2,
	�����~��Y���e��  SuiGou_b3
	��������Y[�a�����@��]�ײv SuiGou_m1,
	�����~��Y[��������@��]�ײv SuiGou_m2,
	float SuiGou_h,SuiGou_b1,SuiGou_b2,SuiGou_b3,SuiGou_b4,SuiGou_m1,SuiGou_m2;
	SuiGou_b2=0.4;//�������e��[�W�d�n�D]
	SuiGou_h=0.6;//�����`��[�W�d�n�D]
	SuiGou_b3=0.3;
	SuiGou_b4=0.6;//�����~��Y���e��[�W�d�n�D:����:0.8  ����:0.6 ,�o�̬��F²�K,�Τ@����0.6]
	SuiGou_m1=SuiGou_m2=1;//��/�~��Y�ײv[�W�d�n�D]
    SuiGou_b1=SuiGou_h/SuiGou_m1+SuiGou_h/SuiGou_m2+SuiGou_b2;//�������e��
	�ҥH�����`�e��=0.6+2*0.6+0.4+0.3=2.5
 */
 	float SGLL=2.5;//2.8;
//	float b=
	if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_L==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_L==TRUE)
	{
		glBegin(GL_QUAD_STRIP);
		for(int i=5;i>=0;i--)
		{

			switch(i)
			{
			case 5:
				glTexCoord2f(0.0f,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z);
				glTexCoord2f(0.0f,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z);
				break;	
			case 4:
				glTexCoord2f(0.6f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z);
				glTexCoord2f(0.6f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z);
				break;	
			case 3:
				glTexCoord2f(1.2f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z);
				glTexCoord2f(1.2f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z);
				break;		
			case 2:
				glTexCoord2f(1.6f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z);
				glTexCoord2f(1.6f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z);
				break;		
			case 1:
				glTexCoord2f(2.2f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z);
				glTexCoord2f(2.2f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z);
				break;		
			case 0:
				glTexCoord2f(1.0f,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z);
				glTexCoord2f(1.0f,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z);
				break;		
			}

		}
		glEnd();
	}
	else if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_L==FALSE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_L==TRUE)
	{
		//��e�I�S������,�ӤU�@�I������
		
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(1.0f,0.0f); 
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index)->x1,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index)->y1,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index)->z1);
			glTexCoord2f(0.0f,1.0f); 
			glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[5].x,
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[5].y,	
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[5].z);
			glTexCoord2f(0.6f/SGLL,1.0f); 
			glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[4].x,
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[4].y,	
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[4].z);
			
			glTexCoord2f(1.2f/SGLL,1.0f); 
			glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[3].x,
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[3].y,	
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[3].z);
			glTexCoord2f(1.6f/SGLL,1.0f); 
			glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[2].x,
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[2].y,	
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[2].z);
			glTexCoord2f(2.2f/SGLL,1.0f); 
			glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[1].x,
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[1].y,	
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[1].z);
			glTexCoord2f(1.0f,1.0f); 
			glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[0].x,
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[0].y,	
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[0].z);
			
		glEnd();
	}
	else if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_L==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_L==FALSE)
	{
		//��e�I������,�ӤU�@�I�S������
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(1.0f,1.0f); 
		glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index+1)->x1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index+1)->y1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index+1)->z1);
		glTexCoord2f(0.0f,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[5].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[5].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[5].z);
		glTexCoord2f(0.6f/SGLL,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[4].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[4].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[4].z);
		
		glTexCoord2f(1.2f/SGLL,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[3].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[3].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[3].z);
		glTexCoord2f(1.6f/SGLL,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[2].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[2].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[2].z);
		glTexCoord2f(2.2f/SGLL,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[1].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[1].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[1].z);
		glTexCoord2f(1.0f,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[0].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[0].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[0].z);
		
		glEnd();
		
		
	}
	
	if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_R==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_R==TRUE)
	{
		glBegin(GL_QUAD_STRIP);
		for(int i=5;i>=0;i--)
		{

			switch(i)
			{
			case 5:
				glTexCoord2f(1.0f,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z);
				glTexCoord2f(1.0f,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z);
				break;	
			case 4:
				glTexCoord2f(1.9f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z);
				glTexCoord2f(1.9f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z);
				break;	
			case 3:
				glTexCoord2f(1.3f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z);
				glTexCoord2f(1.3f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z);
				break;		
			case 2:
				glTexCoord2f(0.9f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z);
				glTexCoord2f(0.9f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z);
				break;		
			case 1:
				glTexCoord2f(0.3f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z);
				glTexCoord2f(0.3f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z);
				break;		
			case 0:
				glTexCoord2f(0.0f,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z);
				glTexCoord2f(0.0f,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z);
				break;		
			}

		}
		glEnd();
	}
	else if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_R==FALSE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_R==TRUE)
	{
		//��e�I�S������,�ӤU�@�I������
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.0f,0.0f); 
		glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index)->x2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index)->y2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index)->z2);
		glTexCoord2f(1.0f,1.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[5].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[5].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[5].z);
		glTexCoord2f(1.9f/SGLL,1.0f);  
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[4].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[4].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[4].z);
		glTexCoord2f(1.3f/SGLL,1.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[3].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[3].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[3].z);
		glTexCoord2f(0.9f/SGLL,1.0f);  
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[2].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[2].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[2].z);
		glTexCoord2f(0.3f/SGLL,1.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[1].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[1].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[1].z);
		glTexCoord2f(0.0f,1.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[0].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[0].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[0].z);
		
		glEnd();
	}
	else if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_R==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_R==FALSE)
	{
		//��e�I������,�ӤU�@�I�S������
		
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(1.0f,1.0f); 
		glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index+1)->x2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index+1)->y2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index+1)->z2);
		glTexCoord2f(1.0f,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[5].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[5].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[5].z);
		glTexCoord2f(1.9f/SGLL,0.0f);  
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[4].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[4].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[4].z);
		glTexCoord2f(1.3f/SGLL,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[3].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[3].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[3].z);
		glTexCoord2f(0.9f/SGLL,0.0f);  
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[2].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[2].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[2].z);
		glTexCoord2f(0.3f/SGLL,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[1].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[1].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[1].z);
		glTexCoord2f(0.0f,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[0].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[0].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[0].z);
		
		glEnd();
	}
	

	glLineWidth(1.0);
	glColor3f(1,1,1);
	
}

void CT3DSystemView::DrawSuiGou_Ortho(long index)
{
	glColor3f(1.0,0.4,1);
	glLineWidth(2.0);

	
	float SGLL=2.8;
	
	if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_L==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_L==TRUE)
	{
		glBegin(GL_QUAD_STRIP);
		for(int i=5;i>=0;i--)
		{
			switch(i)
			{
			case 5:
				glTexCoord2f(0.0f,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z));

				glTexCoord2f(0.0f,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z));
				
				break;	
			case 4:
				glTexCoord2f(0.5f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z));
				
				glTexCoord2f(0.5f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z));
				
				break;	
			case 3:
				glTexCoord2f(1.3f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z));
				
				glTexCoord2f(1.3f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z));
				
				break;		
			case 2:
				glTexCoord2f(1.7f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z));
				
				glTexCoord2f(1.7f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z));
				
				break;		
			case 1:
				glTexCoord2f(2.5f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z));
				
				glTexCoord2f(2.5f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z));
				
				break;		
			case 0:
				glTexCoord2f(1.0f,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z));
				
				glTexCoord2f(1.0f,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z));
				
				break;		
			}

		}
		glEnd();
	}
	
	
	if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_R==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_R==TRUE)
	{

		glBegin(GL_QUAD_STRIP);
		for(int i=5;i>=0;i--)
		{

			switch(i)
			{
			case 5:
				glTexCoord2f(0.0f,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z));
				
				glTexCoord2f(0.0f,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z));
				
				break;	
			case 4:
				glTexCoord2f(0.5f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z));
				
				glTexCoord2f(0.5f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z));
				
				break;	
			case 3:
				glTexCoord2f(1.3f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z));
				
				glTexCoord2f(1.3f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z));
				
				break;		
			case 2:
				glTexCoord2f(1.7f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z));
				
				glTexCoord2f(1.7f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z));
				
				break;		
			case 1:
				glTexCoord2f(2.5f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z));
				
				glTexCoord2f(2.5f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z));
				
				break;		
			case 0:
				glTexCoord2f(1.0f,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z));
				
				glTexCoord2f(1.0f,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z));
				
				break;		
			}

		}
		glEnd();
	}

	glLineWidth(1.0);
	glColor3f(1,1,1);
}

//ø�s���٤U���@�Y��
void CT3DSystemView::DrawQDHP(long Index, CString mCurrentPtstyle, float mHPangle, CString mNextPtstyle, int mBridgeIndex)
{
	//	�p�G�O���G�����۳s,�h���ݭnø�s�@�Y)
	if(mNextPtstyle=="�G�D�_�I")
		return;
	//	�ѻPø�s�@�Y�����I

	//	����:�@�Y�IHuPo_L+PtS_RailwayLj3D�����I(x1,y1,z1)
	//	�k��:PtS_RailwayLj3D�����I(x2,y2,z2)+�@�Y�IHuPo_R
			
	//�ھڬO���ٰ_�I(mCurrentPtstyle="���ٰ_�I")�٬O
	//���ٲ��I(mCurrentPtstyle="���ٲ��I")�Ӥ��O�i��ø�s,�G
	//���@�Y������V�O�ۤϪ�
	double x1,y1,z1,x2,y2,z2;
	double tx,ty,tz;
	
	PCordinate pt;
	
	int i;
	double ax,ay,az;
	int N1,N2;

	
	N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->Huponums_L-1;//������Y��
	N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->Huponums_R-1;//�k����Y��

	if(N1<0 || N2<0)
		return;

	x1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_L[N1].Hp[2].x;
	y1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_L[N1].Hp[2].y;
	z1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_L[N1].Hp[2].z;
	x2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_R[N2].Hp[2].x;
	y2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_R[N2].Hp[2].y,
	z2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_R[N2].Hp[2].z;
	
		
	float dx=x2-x1;
	float dz=z2-z1;
	float mangle;
	
	if(mCurrentPtstyle=="���ٰ_�I")
	{
		if(fabs(dx)<=0.000001) 
		{
			mangle=0;
		}  
		else 
		{
			mangle=atan(fabs(dz/dx));
			if(dx>=0 && dz<=0)  //1�H��
			{
				mangle=PAI/2+mangle;
			}
			else if(dx<=0 && dz<=0) //2�H�� 
			{
				mangle=PAI*3.0/2-mangle;
			}
			else if(dx<=0 && dz>=0) //3�H��
			{
				mangle=2*PAI-mangle;
			}
			else if(dx>=0 && dz>=0) //4�H��
			{
				mangle=PAI/2-mangle;
			}
			
		}
	}
	else if(mCurrentPtstyle=="���ٲ��I")
	{
		if(fabs(dx)<=0.000001) 
		{
			mangle=PAI*3.0/2;
		}  
		else 
		{
			mangle=atan(fabs(dz/dx));
			if(dx>=0 && dz<=0)  //1�H��
			{
				mangle=2*PAI-mangle;
			}
			else if(dx<=0 && dz<=0) //2�H�� 
			{
				mangle=PAI/2-mangle;
			}
			else if(dx<=0 && dz>=0) //3�H��
			{
				mangle=PAI/2+mangle;
			}
			else if(dx>=0 && dz>=0) //4�H��
			{
				mangle=PAI*3.0/2-mangle;
			}
			
		}
	}
	
		//	(1)//���ٰ_�I�@�Y��
		PtBridgeHPUp.RemoveAll();
		PtBridgeHPDown.RemoveAll();
	
		//�̦��D�o�����w�@�Y�����׻P�a�������I
		//(1)�����@�Y�I
		for(i=N1;i>=0;i--)
		{
			for(int j=2;j>=0;j--)
			{
				tx=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_L[i].Hp[j].x;
				ty=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_L[i].Hp[j].y;
				tz=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_L[i].Hp[j].z;
				myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
				pt=new Cordinate;
				pt->x=ax;pt->y=ay;pt->z=az;
				PtBridgeHPDown.Add(pt);
				pt=new Cordinate;
				pt->x=tx;pt->y=ty;pt->z=tz;
				PtBridgeHPUp.Add(pt); //�[�J�@�Y��
			}
		}
	
		//(2) ��������TO��Y�I
		tx=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(Index)->x1;
		ty=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(Index)->y1;
		tz=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(Index)->z1;
		myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
		pt=new Cordinate;
		pt->x=ax;pt->y=ay;pt->z=az;
		PtBridgeHPDown.Add(pt);
		pt=new Cordinate;
		pt->x=tx;pt->y=ty;pt->z=tz;
		PtBridgeHPUp.Add(pt);
		
		//(3) ���������I
		tx=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(Index)->x1;
		ty=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(Index)->y1;
		tz=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(Index)->z1;
		myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
		pt=new Cordinate;
		pt->x=ax;pt->y=ay;pt->z=az;
		PtBridgeHPDown.Add(pt);
		pt=new Cordinate;
		pt->x=tx;pt->y=ty;pt->z=tz;
		PtBridgeHPUp.Add(pt);
		
		//(4) ���߽u
		tx=myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(Index)->x1;
		ty=myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(Index)->y1;
		tz=myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(Index)->z1;
		myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
		pt=new Cordinate;
		pt->x=ax;pt->y=ay;pt->z=az;
		PtBridgeHPDown.Add(pt);
		pt=new Cordinate;
		pt->x=tx;pt->y=ty;pt->z=tz;
		PtBridgeHPUp.Add(pt);
		
		//(5) �k�������I
			tx=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(Index)->x2;
			ty=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(Index)->y2;
			tz=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(Index)->z2;
			myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
			pt=new Cordinate;
			pt->x=ax;pt->y=ay;pt->z=az;
			PtBridgeHPDown.Add(pt);
			pt=new Cordinate;
			pt->x=tx;pt->y=ty;pt->z=tz;
			PtBridgeHPUp.Add(pt);
			
		//(6) �k������TO��Y�I
			tx=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(Index)->x2;
			ty=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(Index)->y2;
			tz=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(Index)->z2;
			myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
			pt=new Cordinate;
			pt->x=ax;pt->y=ay;pt->z=az;
			PtBridgeHPDown.Add(pt);
			pt=new Cordinate;
			pt->x=tx;pt->y=ty;pt->z=tz;
			PtBridgeHPUp.Add(pt);
			
		
			//(7)�k���@�Y�I
			for(i=0;i<=N2;i++)
			{
				for(int j=0;j<=2;j++)
				{
					
					tx=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_R[i].Hp[j].x;
					ty=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_R[i].Hp[j].y;
					tz=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_R[i].Hp[j].z;
					myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
					pt=new Cordinate;
					pt->x=ax;pt->y=ay;pt->z=az;
					PtBridgeHPDown.Add(pt);
					pt=new Cordinate;
					pt->x=tx;pt->y=ty;pt->z=tz;
					PtBridgeHPUp.Add(pt);
				}
			}
	
		glLineWidth(4.0);
		glColor3f(1,0,1);

	//�O���@�Y�U�����P�a�����I
	if(mCurrentPtstyle=="���ٰ_�I")
	{
		myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeIndex)->m_ReginPt_Start.RemoveAll();
		for(int j=0;j<PtBridgeHPDown.GetSize();j++)
		{
			pt=new Cordinate;
			pt->x=PtBridgeHPDown.GetAt(j)->x;
			pt->y=PtBridgeHPDown.GetAt(j)->y;
			pt->z=PtBridgeHPDown.GetAt(j)->z;
			myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeIndex)->m_ReginPt_Start.Add(pt);
		}
	}
	else if(mCurrentPtstyle=="���ٲ��I")
	{
		myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeIndex)->m_ReginPt_End.RemoveAll();
		for(int j=0;j<PtBridgeHPDown.GetSize();j++)
		{
			pt=new Cordinate;
			pt->x=PtBridgeHPDown.GetAt(j)->x;
			pt->y=PtBridgeHPDown.GetAt(j)->y;
			pt->z=PtBridgeHPDown.GetAt(j)->z;
			myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeIndex)->m_ReginPt_End.Add(pt);
		}
	}
	



		double mMin_X,mMin_Y,mMax_X,mMax_Y,Lx,Ly;
		GetMinMaxXY_bridgeHPm(&mMin_X,&mMin_Y,&mMax_X,&mMax_Y);
		Lx=mMax_X-mMin_X;
		Ly=mMax_Y-mMin_Y;

		glBindTexture(GL_TEXTURE_2D, m_cBridgeHpm.GetTxtID());
		glBegin(GL_TRIANGLE_STRIP);
		for(i=0;i<PtBridgeHPDown.GetSize();i++)
		{
			glTexCoord2f((PtBridgeHPUp.GetAt(i)->x-mMin_X)/Lx,(PtBridgeHPUp.GetAt(i)->y-mMin_Y)/Ly);
			glVertex3f(PtBridgeHPUp.GetAt(i)->x,PtBridgeHPUp.GetAt(i)->y,PtBridgeHPUp.GetAt(i)->z);
			glTexCoord2f((PtBridgeHPDown.GetAt(i)->x-mMin_X)/Lx,(PtBridgeHPDown.GetAt(i)->y-mMin_Y)/Ly);
			glVertex3f(PtBridgeHPDown.GetAt(i)->x,PtBridgeHPDown.GetAt(i)->y,PtBridgeHPDown.GetAt(i)->z);
		}
		glEnd();


		
		glColor3f(1,1,1);
		glLineWidth(0);
		

}

//ø�s���[
void CT3DSystemView::DrawSceneQD(double x1, double y1, double z1, double x2, double y2, double z2, float QDheight)
{
	//���[���㦳���e��
	float Xwidth=m_Railway.m_Railway_width+2*m_Railway.m_Lj_width+2*m_Railway.m_GuiMianToLujianWidth;
	float mangle=myDesingScheme.GetANgle(x1,z1,x2,z2); //�p����[�ҫ������઺����(�Ϥ��P�u������)
	if(mangle>180)
		mangle=mangle-180;
	
	float xscale=Xwidth/(m_QD_maxx-m_QD_minx); //�p����[�ҫ��bX��V�W���Y����(�e��)
	float yscale=QDheight/(m_QD_maxy-m_QD_miny);//�p����[�ҫ��bY��V�W���Y����(����)
	
	glPushMatrix(); //���J���
	glScalef(xscale,yscale,1); //���[�Y��
	glTranslatef(((x1+x2)/2-(m_QD_maxx+m_QD_minx)/2)/xscale,y2/yscale-m_QD_maxy,(z1+z2)/2); //����
	glRotatef(mangle,0,1,0); //����
	glCallList(m_QDList); //�եξ��[��ܦC��ø�s���[
	glPopMatrix(); //�u�X���
	
}


//ø�s�G�D
void CT3DSystemView::DrawTunnel()
{
//	m_Tunnel.H;//�G�D�꩷���ݦA�V�W������
//	m_Tunnel.L;//�G�D�}�����ݥ��k�ⰼ�������e�� 
		
	glColor3f(1,1,1);
	glLineWidth(2.0);
	int index=0;
	
	long m_StartIndex,m_EndIndex;//�s�x��e�G�D�_�ק����I�b�Ҧ��G�D�ƾڧ��Ъ����޸�
	m_StartIndex=-1;
	
	//�ھکҦ��G�D������(�G�D�����Hx=y=-1�����j,)
	//�p�U�ܨҼƾڻ���,��ܦ@��2���G�D
	/*
	12345,67,89
	12345,67,89
	12345,67,89
	.....
	12345,67,89
	-1,-1,-1
	12345,67,89
	12345,67,89
	12345,67,89
	.....
	12345,67,89
	-1,-1,-1
	*/
	//
	for (long i=0;i<myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetSize();i++)
	{
		if(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->x1!=-1 && \
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->y1!=-1)
		{
			if(m_StartIndex<0)
				m_StartIndex=i; //��e�G�D�_�l�����I�b�Ҧ��G�D�����Ъ����޸�
		}
		else
		{
			m_EndIndex=i-1;//��e�G�D�פ���I�b�Ҧ��G�D�����Ъ����޸�(m_EndIndex-m_StartIndex�T�w�F��e�G�D�Ѧh�֭ӧ����I�զ�)
			DrawTunnelEach(m_StartIndex,m_EndIndex,index,m_Tunnel.H,m_Tunnel.L); //ø�s�G�D(index:��ܷ�D�G�D�b�Ҧ��G�D������,�Y��D�G�D�O�u�����ĴX���G�D
			index++; //�G�D�����޸�+1
			m_StartIndex=-1;//��_��-1
		}
	}
	
}

void CT3DSystemView::GetMinMaxXY_bridgeHPm(double *minx, double *miny, double *maxx, double *maxy)
{
	*minx=PtBridgeHPDown.GetAt(0)->x;
	*miny=PtBridgeHPDown.GetAt(0)->y;
	*maxx=PtBridgeHPUp.GetAt(0)->x;
	*maxy=PtBridgeHPUp.GetAt(0)->y;
	
	for(int i=0;i<PtBridgeHPDown.GetSize();i++)
	{
		if(*minx>PtBridgeHPDown.GetAt(i)->x) *minx=PtBridgeHPDown.GetAt(i)->x;
		if(*miny>PtBridgeHPDown.GetAt(i)->y) *miny=PtBridgeHPDown.GetAt(i)->y;
		if(*maxx<PtBridgeHPDown.GetAt(i)->x) *maxx=PtBridgeHPDown.GetAt(i)->x;
		if(*maxy<PtBridgeHPDown.GetAt(i)->y) *maxy=PtBridgeHPDown.GetAt(i)->y;
	}
	
	for(i=0;i<PtBridgeHPUp.GetSize();i++)
	{
		if(*minx>PtBridgeHPUp.GetAt(i)->x) *minx=PtBridgeHPUp.GetAt(i)->x;
		if(*miny>PtBridgeHPUp.GetAt(i)->y) *miny=PtBridgeHPUp.GetAt(i)->y;
		if(*maxx<PtBridgeHPUp.GetAt(i)->x) *maxx=PtBridgeHPUp.GetAt(i)->x;
		if(*maxy<PtBridgeHPUp.GetAt(i)->y) *maxy=PtBridgeHPUp.GetAt(i)->y;
	}
	
}

//ø�s�G�D
/*�Ѽƻ���:
mStartindex:��e�G�D�_�l�����I�b�Ҧ��G�D�����мƾڪ����޸�
mEndIndex://��e�G�D�פ���I�b�Ҧ��G�D�����мƾڪ����޸�
mTunnelIndex:��ܷ�D�G�D�b�Ҧ��G�D������,�Y��D�G�D�O�u�����ĴX���G�D(���]�@4���G�D,�hmTunnelIndex=0,1,2,3)
H:�G�D�꩷���ݦA�V�W������
L:�G�D�}�����ݥ��k�ⰼ�������e�� 
*/
void CT3DSystemView::DrawTunnelEach(long mStartindex, long mEndIndex, int mTunnelIndex, float H, float L)
{
	double minx,miny,Lx,Ly;
	
	//(1)ø�s�G�D�X�f�}��
	glBindTexture(GL_TEXTURE_2D, m_cTunnel_dm.GetTxtID()); //�j�w�G�D�X�f�}�����z
	DrawTunnelDM(
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mEndIndex)->x1,\
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mEndIndex)->y1,\
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mEndIndex)->z1,\
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mEndIndex)->x2,\
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mEndIndex)->y2,\
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mEndIndex)->z2,\
		H,L,mEndIndex,mTunnelIndex,FALSE,\
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelIndex)->mEndAngle\
		);
	
	/*	�ھ��G�D�X�f�}�����k�ⰼ���𩳤U�ݧ���(x,y1,z1),(x2,y2,z2)	*/

	//(2)ø�s�G�D����
	glBindTexture(GL_TEXTURE_2D, m_cTunnel.GetTxtID());//�j�w�G�D�������z
	for ( long i=mStartindex;i<mEndIndex;i++)
	{
	//	glBindTexture(GL_TEXTURE_2D, m_cTunnel.GetTxtID());//�j�w�G�D�������z
		
			//��������
			glBegin(GL_POLYGON ); 
				glTexCoord2f(0,0);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->y1,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glTexCoord2f(0,1);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->y1+m_Tunnel.WallHeight,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glTexCoord2f(1,1);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->y1+m_Tunnel.WallHeight,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
				glTexCoord2f(1,0);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glEnd();

			//�k������
			glBegin(GL_POLYGON ); 
			glTexCoord2f(1,0);
			glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->y2,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(1,1);
			glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->y2+m_Tunnel.WallHeight,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(0,1);
			glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->y2+m_Tunnel.WallHeight,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(0,0);
			glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glEnd();

			
	//		glBindTexture(GL_TEXTURE_2D, m_cTunnel.GetTxtID());
			//���ݶ꩷
			int mNums=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetSize();

			minx=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(mNums-1)->x;
			miny=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(mNums-1)->z;
			Lx=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(0)->x-minx;
			Ly=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(0)->z-miny;
			
			//ø�s���{���_�������ݶ꩷,�H�s��h��Τ覡ø�s(GL_QUAD_STRIP)
			glColor3f(1,0,0);
			glBegin(GL_QUAD_STRIP );
				glTexCoord2f(0,0);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(0)->x,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(0)->y,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(0)->z);
				
				glTexCoord2f(0,1);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(0)->x,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(0)->y,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(0)->z);
				
				glTexCoord2f(1.0/m_Tunnel.ArcSegmentNumber,0);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(1)->x,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(1)->y,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(1)->z);
			
				glTexCoord2f(1.0/m_Tunnel.ArcSegmentNumber,1);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(1)->x,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(1)->y,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(1)->z);
				
			
				for(int n=2;n<myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetSize();n++)
				{
					
					glTexCoord2f(n*1.0/m_Tunnel.ArcSegmentNumber,0);
					glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(n)->x,\
						myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(n)->y,\
						myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(n)->z);
					
					glTexCoord2f(n*1.0/m_Tunnel.ArcSegmentNumber,1);
					glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(n)->x,\
						myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(n)->y,\
						myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(n)->z);
					
				}
			
			glEnd();

			glColor3f(1,1,1);
			
		}
		
		//ø�s�G�D�i�X�f�}��
		glBindTexture(GL_TEXTURE_2D, m_cTunnel_dm.GetTxtID());//�j�w�G�D�i�f�}�����z
		DrawTunnelDM(
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mStartindex)->x1,\
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mStartindex)->y1,\
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mStartindex)->z1,\
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mStartindex)->x2,\
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mStartindex)->y2,\
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mStartindex)->z2,\
			H,L,mStartindex,mTunnelIndex,TRUE,\
			myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelIndex)->mStartangle\
			);
}

//ø�s�G�D�}��
/*
�Ѽƻ���:
x1,y1,z1:�G�D�}�����ⰼ���𩳤U�ݧ���
x2,y2,z2:�G�D�}���k�ⰼ���𩳤U�ݧ���
H;�G�D�꩷���ݦA�V�W������
L:�G�D�}�����ݥ��k�ⰼ�������e��
index:�G�D�}���������I�b�Ҧ��G�D���ƾڧ��Ъ����޸�
tunnelIndex;��D�G�D�b�Ҧ��G�D������,�Y��D�G�D�O�u�����ĴX���G�D
bstartDM:��ܬO�G�D�i�f�}��(bstartDM=TRUE)�٬O�G�D�X�f�}��((bstartDM=FALSE)
mangle:�}�������V����
  */
void CT3DSystemView::DrawTunnelDM(double x1, double y1, double z1, double x2, double y2, double z2, float H, float L, int index, int tunnelIndex, BOOL bstartDM, float mangle)
{
//�Ҷǻ�������P6(x1,y1,z1),P5(x2,y2,z2)
//H:�q�꩷���ݦV�W������(�]�N�O�n�b�꩷���ݦA�[�@�w������,�@���}�����`����)
//L:�q���𥿤W��V,�V�k�X�i���Z��,�c�����𦡬}�����c
//�HGL_TRIANGLEø�s��P1p2p6  ��P3p4p5 
//P2P3������ m_Tunnel.ArcSegmentNumber�ƶq�I,�P�꩷�I�۹���,�HGL_TRIANGLE_STRIPø�s
/*
�G�D�}���ܷN�Ϲ�(���𦡬}��)
	P1   L   P2          P3   L   P4
	--------- |-----------|----------
	 \        |      h_   |        /
	  \       |           |       /   
	   \      |  �꩷���� |      /
	    \     |           |     /
		 \    |           |    /
		  \   |           |   /
		   \  |           |  /
	     P7_\_|_P6______P5|_/P8
*/


	double P1[3],P2[3],P3[3],P4[3],P5[3],P6[3],P7[3],P8[3];
	double A1[3],A2[3],A3[3],A4[3],A5[3],A6[3];
	double Lx,Ly,minx,miny,maxx,maxy;
	

	P6[0]=x1;P6[1]=y1;P6[2]=z1;
	P5[0]=x2;P5[1]=y2;P5[2]=z2;
	
	long mIn;
	if(bstartDM==TRUE)//�}���i�f
		mIn=myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->startIndex-1;//���ޭ�
	else
		mIn=myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->endIndex-1;//���ޭ�

	P7[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[1].x;
	P7[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[1].y;
	P7[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[1].z;

	P8[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[1].x;
	P8[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[1].y;
	P8[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[1].z;
	
		
	//(1)�D�XP2,P3���� P2,P3���Z��=m_Tunnel.width
	P2[0]=x1;P2[1]=y1+m_Tunnel.height+H;P2[2]=z1;
	P3[0]=x2;P3[1]=y2+m_Tunnel.height+H;P3[2]=z2;
	
	//(2)�D�XP1,P4����
	P1[0]=P2[0]-L*cos(mangle);P1[1]=P2[1];P1[2]=P2[2]+L*sin(mangle);
	P4[0]=P3[0]+L*cos(mangle);P4[1]=P3[1];P4[2]=P3[2]-L*sin(mangle);
		
	
	//////////////////////////////////////////////////////////////////////////
	//���[���㦳���e��
	float Xwidth=fabs(P4[0]-P1[0]);
	float Yheight=fabs(P3[1]-P5[1]);
	mangle=myDesingScheme.GetANgle(x1,z1,x2,z2); //�p���G�D�}���ҫ������઺����(�Ϥ��P�u������)
	
	float xscale=Xwidth/(m_TunnelDM_maxx-m_TunnelDM_minx); //�p���G�D�}���ҫ��bX��V�W���Y����(�e��)
	float yscale=Yheight/(m_TunnelDM_maxy-m_TunnelDM_miny);//�p���G�D�}���ҫ��bY��V�W���Y����(����)
	glPushMatrix(); //���J���
	glScalef(xscale,yscale,1); //�G�D�}���Y��
	glTranslatef(((x1+x2)/2-(m_TunnelDM_maxx+m_TunnelDM_minx)/2)/xscale,((y1+y2)/2-(m_TunnelDM_maxy+m_TunnelDM_miny)/2)/yscale,(z1+z2)/2); //����
	glRotatef(mangle,0,1,0); //����
	glCallList(m_TunnelDMList); //�ե��G�D�}����ܦC��ø�s���[
	glPopMatrix(); //�u�X���
	
	//////////////////////////////////////////////////////////////////////////
	
//	return;

	

	PCordinate pt;

	if(bstartDM==TRUE)//�}���i�f
	{
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_Start.RemoveAll();
		
		//�p���G�D�}���i�f�U�I����
		pt=new Cordinate;
		pt->x =P1[0];	pt->y =P1[1];	pt->z =P1[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_Start.Add(pt);
	
		pt=new Cordinate;
		pt->x =P2[0];	pt->y =P2[1];	pt->z =P2[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_Start.Add(pt);
	
		pt=new Cordinate;
		pt->x =P3[0];	pt->y =P3[1];	pt->z =P3[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_Start.Add(pt);
		
		pt=new Cordinate;
		pt->x =P4[0];	pt->y =P4[1];	pt->z =P4[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_Start.Add(pt);
		
	}
	else
	{
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_End.RemoveAll();
		
		//�p���G�D�}���X�f�U�I����
		pt=new Cordinate;
		pt->x =P1[0];	pt->y =P1[1];	pt->z =P1[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_End.Add(pt);
		
		pt=new Cordinate;
		pt->x =P2[0];	pt->y =P2[1];	pt->z =P2[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_End.Add(pt);
		
		pt=new Cordinate;
		pt->x =P3[0];	pt->y =P3[1];	pt->z =P3[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_End.Add(pt);
		
		pt=new Cordinate;
		pt->x =P4[0];	pt->y =P4[1];	pt->z =P4[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_End.Add(pt);
	}


		float m_L=0.8;//
		A1[0]=P1[0]-m_L*sin(mangle);A1[1]=P1[1];A1[2]=P1[2]-m_L*cos(mangle);
		A2[0]=P2[0]-m_L*sin(mangle);A2[1]=P2[1];A2[2]=P2[2]-m_L*cos(mangle);
		A3[0]=P3[0]-m_L*sin(mangle);A3[1]=P3[1];A3[2]=P3[2]-m_L*cos(mangle);
		A4[0]=P4[0]-m_L*sin(mangle);A4[1]=P4[1];A4[2]=P4[2]-m_L*cos(mangle);
		
		
		if(bstartDM==TRUE)//�p�G�O�G�D�i�f�}��
		{
			Lx=P4[0]-P1[0];
			Ly=P1[1]-P7[1];
			minx=P1[0];
			miny=P7[1];
		}
		else  //�p�G�O�G�D�X�f�}��
		{
			Lx=P1[0]-P4[0];
			Ly=P1[1]-P7[1];
			minx=P4[0];
			miny=P7[1];
		}

			glLineWidth(3.0);  //�]�m�u�e

			glColor3f(1,0,1); //�]�m�C��
			glBegin(GL_TRIANGLE_STRIP); //�H�s���u�覡ø�s
			glVertex3dv(A1);
			glVertex3dv(P1);
			glVertex3dv(A2);
			glVertex3dv(P2);
			glVertex3dv(A3);
			glVertex3dv(P3);
			glVertex3dv(A4);
			glVertex3dv(P4);
			glEnd();


			glColor3f(0.4,0.2,1);
			glBegin(GL_TRIANGLES); //�H�T���Χ�ø�s(p1P2P7)
				glTexCoord2f((P1[0]-minx)/Lx,1);
				glVertex3dv(P1);
				glTexCoord2f((P2[0]-minx)/Lx,1);
				glVertex3dv(P2);
				glTexCoord2f((P7[0]-minx)/Lx,0);
				glVertex3dv(P7);
			glEnd();

			glBegin(GL_TRIANGLES);//�H�T���Χ�ø�s(p2P7P6)
				glTexCoord2f((P2[0]-minx)/Lx,1);
				glVertex3dv(P2);
				glTexCoord2f((P7[0]-minx)/Lx,0);
				glVertex3dv(P7);
				glTexCoord2f((P6[0]-minx)/Lx,0);
				glVertex3dv(P6);
			glEnd();

			glBegin(GL_TRIANGLES);//�H�T���Χ�ø�s(p3P5P8)
				glTexCoord2f((P3[0]-minx)/Lx,1);
				glVertex3dv(P3);
				glTexCoord2f((P5[0]-minx)/Lx,0);
				glVertex3dv(P5);
				glTexCoord2f((P8[0]-minx)/Lx,0);
				glVertex3dv(P8);
			glEnd();

			glBegin(GL_TRIANGLES);//�H�T���Χ�ø�s(p3P8P4)
			glTexCoord2f((P3[0]-minx)/Lx,1);
			glVertex3dv(P3);
			glTexCoord2f((P8[0]-minx)/Lx,0);
			glVertex3dv(P8);
			glTexCoord2f((P4[0]-minx)/Lx,1);
			glVertex3dv(P4);
			glEnd();
			
			
			//ø�s���ݶ꩷
			int mNums=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(index)->tunnelArc.GetSize();
			double tx,ty,tz;
			double rx,ry,rz;
			glBegin(GL_TRIANGLE_STRIP);
			for(int i=0;i<mNums;i++)
			{
				tx=P3[0]+i*(P2[0]-P3[0])/(mNums-1);
				ty=P3[1];
				tz=P3[2]+i*(P2[2]-P3[2])/(mNums-1);
				glTexCoord2f((tx-minx)/Lx,(ty-miny)/Ly);
				glVertex3f(tx,ty,tz);
				rx=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(index)->tunnelArc.GetAt(i)->x;
				ry=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(index)->tunnelArc.GetAt(i)->y;
				rz=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(index)->tunnelArc.GetAt(i)->z;
				glTexCoord2f((rx-minx)/Lx,(ry-miny)/Ly);
				glVertex3f(rx,ry,rz);
			}
		glEnd();
		
//-----------�ʳ��}���P������ɳB
		//ø�s�}��
		if(bstartDM==TRUE)//�}���i�f
		{
			glBindTexture(GL_TEXTURE_2D, m_cTunnel_dmwcBp.GetTxtID());
			//(1)����
			if(mIn>=1)
			{
				A1[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_L[0].Hp[2].x;
				A1[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_L[0].Hp[2].y;
				A1[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_L[0].Hp[2].z;
				
				A2[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_L[0].Hp[1].x;
				A2[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_L[0].Hp[1].y;
				A2[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_L[0].Hp[1].z;
				
				A3[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[1].x;
				A3[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[1].y;
				A3[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[1].z;
				
				A4[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[0].x;
				A4[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[0].y;
				A4[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[0].z;
			
				A5[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[3].x;
				A5[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[3].y;
				A5[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[3].z;
			
				A6[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[2].x;
				A6[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[2].y;
				A6[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[2].z;
				
				//�D minx,maxx,miny,maxy;
				
				minx=miny=999999999;
				maxx=maxy=-999999999;
				if(minx>A1[0]) minx=A1[0];
				if(maxx<A1[0]) maxx=A1[0];
				if(miny>A1[1]) miny=A1[1];
				if(maxy<A1[1]) maxy=A1[1];
				
				if(minx>A2[0]) minx=A2[0];
				if(maxx<A2[0]) maxx=A2[0];
				if(miny>A2[1]) miny=A2[1];
				if(maxy<A2[1]) maxy=A2[1];
				
				if(minx>A3[0]) minx=A3[0];
				if(maxx<A3[0]) maxx=A3[0];
				if(miny>A3[1]) miny=A3[1];
				if(maxy<A3[1]) maxy=A3[1];
				
				if(minx>A4[0]) minx=A4[0];
				if(maxx<A4[0]) maxx=A4[0];
				if(miny>A4[1]) miny=A4[1];
				if(maxy<A4[1]) maxy=A4[1];
			
				if(minx>A5[0]) minx=A5[0];
				if(maxx<A5[0]) maxx=A5[0];
				if(miny>A5[1]) miny=A5[1];
				if(maxy<A5[1]) maxy=A5[1];
				
				if(minx>A6[0]) minx=A6[0];
				if(maxx<A6[0]) maxx=A6[0];
				if(miny>A6[1]) miny=A6[1];
				if(maxy<A6[1]) maxy=A6[1];
				
				if(minx>P1[0]) minx=P1[0];
				if(maxx<P1[0]) maxx=P1[0];
				if(miny>P1[1]) miny=P1[1];
				if(maxy<P1[1]) maxy=P1[1];
				
				if(minx>P7[0]) minx=P7[0];
				if(maxx<P7[0]) maxx=P7[0];
				if(miny>P7[1]) miny=P7[1];
				if(maxy<P7[1]) maxy=P7[1];
				
		
				
				float L1,L2;
				L1=myDesingScheme.GetDistenceXYZ(A1[0],A1[1],A1[2],P1[0],P1[1],P1[2]);
				L2=myDesingScheme.GetDistenceXYZ(A2[0],A2[1],A2[2],A3[0],A3[1],A3[2]);

				int bsign;
				if(A2[2]>=A3[2])
					bsign=-1;
				else
					bsign=1;
		
				minx=A1[0]+bsign*L1;
				maxx=P7[0];
			
				Lx=maxx-minx;
				Ly=maxy-miny;
				
				glColor3f(1,1,0);
				glBegin(GL_TRIANGLE_FAN);
					glTexCoord2f((P1[0]-minx)/Lx,(P1[1]-miny)/Ly);
					glVertex3dv(P1);
					glTexCoord2f((A1[0]-minx+bsign*L1)/Lx,(A1[1]-miny)/Ly);
					glVertex3dv(A1);
					glTexCoord2f((A2[0]-minx+bsign*L2)/Lx,(A2[1]-miny)/Ly);
					glVertex3dv(A2);
					glTexCoord2f((A3[0]-minx)/Lx,(A3[1]-miny)/Ly);
					glVertex3dv(A3);
					glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
					glVertex3dv(A4);
					glTexCoord2f((P7[0]-minx)/Lx,(P7[1]-miny)/Ly);
					glVertex3dv(P7);
				glEnd();
				
					
				glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f((P7[0]-minx)/Lx,(P7[1]-miny)/Ly);
				glVertex3dv(P7);
				glTexCoord2f((A6[0]-minx)/Lx,(A6[1]-miny)/Ly);
				glVertex3dv(A6);
				glTexCoord2f((A5[0]-minx)/Lx,(A5[1]-miny)/Ly);
				glVertex3dv(A5);
				glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
				glVertex3dv(A4);
				glEnd();
			

			//(2)�k��
			A1[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_R[0].Hp[2].x;
			A1[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_R[0].Hp[2].y;
			A1[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_R[0].Hp[2].z;
			
			A2[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_R[0].Hp[1].x;
			A2[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_R[0].Hp[1].y;
			A2[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_R[0].Hp[1].z;
			
			A3[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[1].x;
			A3[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[1].y;
			A3[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[1].z;
			
			A4[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[0].x;
			A4[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[0].y;
			A4[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[0].z;
			
			A5[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[3].x;
			A5[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[3].y;
			A5[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[3].z;
			
			A6[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[2].x;
			A6[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[2].y;
			A6[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[2].z;
			
			//�D minx,maxx,miny,maxy;
			
			minx=miny=999999999;
			maxx=maxy=-999999999;
			if(minx>A1[0]) minx=A1[0];
			if(maxx<A1[0]) maxx=A1[0];
			if(miny>A1[1]) miny=A1[1];
			if(maxy<A1[1]) maxy=A1[1];
			
			if(minx>A2[0]) minx=A2[0];
			if(maxx<A2[0]) maxx=A2[0];
			if(miny>A2[1]) miny=A2[1];
			if(maxy<A2[1]) maxy=A2[1];
			
			if(minx>A3[0]) minx=A3[0];
			if(maxx<A3[0]) maxx=A3[0];
			if(miny>A3[1]) miny=A3[1];
			if(maxy<A3[1]) maxy=A3[1];
			
			if(minx>A4[0]) minx=A4[0];
			if(maxx<A4[0]) maxx=A4[0];
			if(miny>A4[1]) miny=A4[1];
			if(maxy<A4[1]) maxy=A4[1];
			
			if(minx>A5[0]) minx=A5[0];
			if(maxx<A5[0]) maxx=A5[0];
			if(miny>A5[1]) miny=A5[1];
			if(maxy<A5[1]) maxy=A5[1];
			
			if(minx>A6[0]) minx=A6[0];
			if(maxx<A6[0]) maxx=A6[0];
			if(miny>A6[1]) miny=A6[1];
			if(maxy<A6[1]) maxy=A6[1];
			
			if(minx>P4[0]) minx=P4[0];
			if(maxx<P4[0]) maxx=P4[0];
			if(miny>P4[1]) miny=P4[1];
			if(maxy<P4[1]) maxy=P4[1];
			
			if(minx>P8[0]) minx=P8[0];
			if(maxx<P8[0]) maxx=P8[0];
			if(miny>P8[1]) miny=P8[1];
			if(maxy<P8[1]) maxy=P8[1];
			
		//	
			L1=myDesingScheme.GetDistenceXYZ(A1[0],A1[1],A1[2],P1[0],P1[1],P1[2]);
			L2=myDesingScheme.GetDistenceXYZ(A2[0],A2[1],A2[2],A3[0],A3[1],A3[2]);
			
			
			if(A2[2]>=A3[2])
				bsign=1;
			else
				bsign=-1;
			
			maxx=A1[0]+bsign*L1;
			minx=P8[0];
			
			Lx=maxx-minx;
			Ly=maxy-miny;
			
			
			glColor3f(1,1,0);
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f((P4[0]-minx)/Lx,(P4[1]-miny)/Ly);
			glVertex3dv(P4);
			glTexCoord2f((A1[0]-minx+bsign*L1)/Lx,(A1[1]-miny)/Ly);
			glVertex3dv(A1);
			glTexCoord2f((A2[0]-minx+bsign*L2)/Lx,(A2[1]-miny)/Ly);
			glVertex3dv(A2);
			glTexCoord2f((A3[0]-minx)/Lx,(A3[1]-miny)/Ly);
			glVertex3dv(A3);
			glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
			glVertex3dv(A4);
			glTexCoord2f((P8[0]-minx)/Lx,(P8[1]-miny)/Ly);
			glVertex3dv(P8);
			glEnd();
			
			
			
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f((P8[0]-minx)/Lx,(P8[1]-miny)/Ly);
			glVertex3dv(P8);
			glTexCoord2f((A6[0]-minx)/Lx,(A6[1]-miny)/Ly);
			glVertex3dv(A6);
			glTexCoord2f((A5[0]-minx)/Lx,(A5[1]-miny)/Ly);
			glVertex3dv(A5);
			glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
			glVertex3dv(A4);
			glEnd();
			}
		}
		else if(bstartDM==FALSE)//�}���X�f
		{
			glBindTexture(GL_TEXTURE_2D, m_cTunnel_dmwcBp.GetTxtID());
			
			//(1)����
			A1[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_L[0].Hp[2].x;
			A1[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_L[0].Hp[2].y;
			A1[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_L[0].Hp[2].z;
			
			A2[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_L[0].Hp[1].x;
			A2[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_L[0].Hp[1].y;
			A2[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_L[0].Hp[1].z;
			
			A3[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[1].x;
			A3[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[1].y;
			A3[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[1].z;
			
			A4[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[0].x;
			A4[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[0].y;
			A4[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[0].z;
		
			A5[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[3].x;
			A5[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[3].y;
			A5[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[3].z;
		
			A6[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[2].x;
			A6[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[2].y;
			A6[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[2].z;
			
			//�D minx,maxx,miny,maxy;
			
			minx=miny=999999999;
			maxx=maxy=-999999999;
			if(minx>A1[0]) minx=A1[0];
			if(maxx<A1[0]) maxx=A1[0];
			if(miny>A1[1]) miny=A1[1];
			if(maxy<A1[1]) maxy=A1[1];
			
			if(minx>A2[0]) minx=A2[0];
			if(maxx<A2[0]) maxx=A2[0];
			if(miny>A2[1]) miny=A2[1];
			if(maxy<A2[1]) maxy=A2[1];
			
			if(minx>A3[0]) minx=A3[0];
			if(maxx<A3[0]) maxx=A3[0];
			if(miny>A3[1]) miny=A3[1];
			if(maxy<A3[1]) maxy=A3[1];
			
			if(minx>A4[0]) minx=A4[0];
			if(maxx<A4[0]) maxx=A4[0];
			if(miny>A4[1]) miny=A4[1];
			if(maxy<A4[1]) maxy=A4[1];
		
			if(minx>A5[0]) minx=A5[0];
			if(maxx<A5[0]) maxx=A5[0];
			if(miny>A5[1]) miny=A5[1];
			if(maxy<A5[1]) maxy=A5[1];
			
			if(minx>A6[0]) minx=A6[0];
			if(maxx<A6[0]) maxx=A6[0];
			if(miny>A6[1]) miny=A6[1];
			if(maxy<A6[1]) maxy=A6[1];
			
			if(minx>P1[0]) minx=P1[0];
			if(maxx<P1[0]) maxx=P1[0];
			if(miny>P1[1]) miny=P1[1];
			if(maxy<P1[1]) maxy=P1[1];
			
			if(minx>P7[0]) minx=P7[0];
			if(maxx<P7[0]) maxx=P7[0];
			if(miny>P7[1]) miny=P7[1];
			if(maxy<P7[1]) maxy=P7[1];
			
	
			
			float L1,L2;
			L1=myDesingScheme.GetDistenceXYZ(A1[0],A1[1],A1[2],P1[0],P1[1],P1[2]);
			L2=myDesingScheme.GetDistenceXYZ(A2[0],A2[1],A2[2],A3[0],A3[1],A3[2]);

			int bsign;
			if(A2[2]>=A3[2])
				bsign=-1;
			else
				bsign=1;
	
			minx=A1[0]+bsign*L1;
			maxx=P7[0];
		
			Lx=maxx-minx;
			Ly=maxy-miny;
			
			glColor3f(1,1,0);
			glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f((P1[0]-minx)/Lx,(P1[1]-miny)/Ly);
				glVertex3dv(P1);
				glTexCoord2f((A1[0]-minx+bsign*L1)/Lx,(A1[1]-miny)/Ly);
				glVertex3dv(A1);
				glTexCoord2f((A2[0]-minx+bsign*L2)/Lx,(A2[1]-miny)/Ly);
				glVertex3dv(A2);
				glTexCoord2f((A3[0]-minx)/Lx,(A3[1]-miny)/Ly);
				glVertex3dv(A3);
				glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
				glVertex3dv(A4);
				glTexCoord2f((P7[0]-minx)/Lx,(P7[1]-miny)/Ly);
				glVertex3dv(P7);
			glEnd();
			
				
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f((P7[0]-minx)/Lx,(P7[1]-miny)/Ly);
			glVertex3dv(P7);
			glTexCoord2f((A6[0]-minx)/Lx,(A6[1]-miny)/Ly);
			glVertex3dv(A6);
			glTexCoord2f((A5[0]-minx)/Lx,(A5[1]-miny)/Ly);
			glVertex3dv(A5);
			glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
			glVertex3dv(A4);
			glEnd();
		

			//(2)�k��
			A1[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_R[0].Hp[2].x;
			A1[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_R[0].Hp[2].y;
			A1[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_R[0].Hp[2].z;
			
			A2[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_R[0].Hp[1].x;
			A2[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_R[0].Hp[1].y;
			A2[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_R[0].Hp[1].z;
			
			A3[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[1].x;
			A3[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[1].y;
			A3[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[1].z;
			
			A4[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[0].x;
			A4[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[0].y;
			A4[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[0].z;
			
			A5[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[3].x;
			A5[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[3].y;
			A5[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[3].z;
			
			A6[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[2].x;
			A6[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[2].y;
			A6[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[2].z;
			
			//�D minx,maxx,miny,maxy;
			
			minx=miny=999999999;
			maxx=maxy=-999999999;
			if(minx>A1[0]) minx=A1[0];
			if(maxx<A1[0]) maxx=A1[0];
			if(miny>A1[1]) miny=A1[1];
			if(maxy<A1[1]) maxy=A1[1];
			
			if(minx>A2[0]) minx=A2[0];
			if(maxx<A2[0]) maxx=A2[0];
			if(miny>A2[1]) miny=A2[1];
			if(maxy<A2[1]) maxy=A2[1];
			
			if(minx>A3[0]) minx=A3[0];
			if(maxx<A3[0]) maxx=A3[0];
			if(miny>A3[1]) miny=A3[1];
			if(maxy<A3[1]) maxy=A3[1];
			
			if(minx>A4[0]) minx=A4[0];
			if(maxx<A4[0]) maxx=A4[0];
			if(miny>A4[1]) miny=A4[1];
			if(maxy<A4[1]) maxy=A4[1];
			
			if(minx>A5[0]) minx=A5[0];
			if(maxx<A5[0]) maxx=A5[0];
			if(miny>A5[1]) miny=A5[1];
			if(maxy<A5[1]) maxy=A5[1];
			
			if(minx>A6[0]) minx=A6[0];
			if(maxx<A6[0]) maxx=A6[0];
			if(miny>A6[1]) miny=A6[1];
			if(maxy<A6[1]) maxy=A6[1];
			
			if(minx>P4[0]) minx=P4[0];
			if(maxx<P4[0]) maxx=P4[0];
			if(miny>P4[1]) miny=P4[1];
			if(maxy<P4[1]) maxy=P4[1];
			
			if(minx>P8[0]) minx=P8[0];
			if(maxx<P8[0]) maxx=P8[0];
			if(miny>P8[1]) miny=P8[1];
			if(maxy<P8[1]) maxy=P8[1];
			
		//	
			L1=myDesingScheme.GetDistenceXYZ(A1[0],A1[1],A1[2],P1[0],P1[1],P1[2]);
			L2=myDesingScheme.GetDistenceXYZ(A2[0],A2[1],A2[2],A3[0],A3[1],A3[2]);
			
			
			if(A2[2]>=A3[2])
				bsign=1;
			else
				bsign=-1;
			
			maxx=A1[0]+bsign*L1;
			minx=P8[0];
			
			Lx=maxx-minx;
			Ly=maxy-miny;
			
			
			glColor3f(1,1,0);
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f((P4[0]-minx)/Lx,(P4[1]-miny)/Ly);
			glVertex3dv(P4);
			glTexCoord2f((A1[0]-minx+bsign*L1)/Lx,(A1[1]-miny)/Ly);
			glVertex3dv(A1);
			glTexCoord2f((A2[0]-minx+bsign*L2)/Lx,(A2[1]-miny)/Ly);
			glVertex3dv(A2);
			glTexCoord2f((A3[0]-minx)/Lx,(A3[1]-miny)/Ly);
			glVertex3dv(A3);
			glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
			glVertex3dv(A4);
			glTexCoord2f((P8[0]-minx)/Lx,(P8[1]-miny)/Ly);
			glVertex3dv(P8);
			glEnd();
			
			
			
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f((P8[0]-minx)/Lx,(P8[1]-miny)/Ly);
			glVertex3dv(P8);
			glTexCoord2f((A6[0]-minx)/Lx,(A6[1]-miny)/Ly);
			glVertex3dv(A6);
			glTexCoord2f((A5[0]-minx)/Lx,(A5[1]-miny)/Ly);
			glVertex3dv(A5);
			glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
			glVertex3dv(A4);
			glEnd();
		}

		glColor3f(1,1,1);
		glLineWidth(0);
}



//�u���T���ؼ�
void CT3DSystemView::OnMenuBuild3dlinemodle() 
{
	BeginWaitCursor();
	b_haveGetRegion=FALSE;//�O�_�w����ʳ��ϰ�
	
	myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_RailwayBP3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].RemoveAll();
	

	if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()<2)
		return;
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	float iPer=100.0/(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1);
	CString tt;
	
	
	for (long i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1;i++)
	{	
		
		if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->Lc<=
			myDesingScheme.SchemeDatass[m_currentSchemeIndexs].EndLC)
		{
			myDesingScheme.Get3DLineModel(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->y,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->x,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->y,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->z,\
				m_Railway.m_Railway_width,m_Railway.m_Lj_width,m_Railway.m_Lj_Dh,\
				m_Railway.m_GuiMianToLujianWidth,45,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle,\
				i,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Lc
				);
		}
		tt.Format("���b�i��u���T���ؼ� , �еy��... , �w����%.2f%s" , (i+1)*iPer , "%");
		pMainFrame->Set_BarText(4 , tt , 0); 
		
	}
	

	if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)->Lc<=
		myDesingScheme.SchemeDatass[m_currentSchemeIndexs].EndLC)
	{
		myDesingScheme.Get3DLineModelLast(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-2)->x,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-2)->y,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-2)->z,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)->x,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)->y,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)->z,\
			m_Railway.m_Railway_width,m_Railway.m_Lj_width,m_Railway.m_Lj_Dh,\
			m_Railway.m_GuiMianToLujianWidth,45,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-2)->strJDStyle,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)->strJDStyle,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-2,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-2)->Lc\
			);
	}

	
	pMainFrame->Set_BarText(4 , "�[���a�λP�v�����z�ƾڧ���!" , 0); 
	b_haveMadeRail3DwayList=FALSE;
	b_haveMadeRail3DwayList_Ortho=FALSE;
	OnDraw (GetDC()); //��s�T������
	
}

//�u��׽u���C,�]�N���N��e�u����פ��߽u�@�����C���|�Ӥw	
void CT3DSystemView::OnFlyRoutinschemeline() 
{
	m_R=3000;
	m_r=2000;
	
	if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()<=1)
	{
		if(m_FlayPath.GetSize()<=0) //�����e�O�����|���C���A
			m_PathFlag=FALSE; //���ѭ�����|�L��
		else
			m_PathFlag=TRUE; //���ѭ�����|����
		return;
	}
	
	m_FlayPath.RemoveAll();//������|�ƲղM��
	PCordinate ppt=NULL;
	//�N�u�����u�@��������|
	for(int i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize();i++)
	{
		ppt = new Cordinate;
		ppt->x=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x;//x����
		ppt->y=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->y;//y����
		ppt->z=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z;//z����
		ppt->Lc=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Lc;//���{
		m_FlayPath.Add(ppt); //�N�u�����u�����I�[�J������|�Ʋդ�
	}
	
	if(m_FlayPath.GetSize()>1) //�p�G������|����
	{
		m_bmouseView=FALSE; //����б�������\��
		//	m_ShowFlyPath=TRUE;
// 		m_ShowFlyPath=FALSE;//�u���T�����C���ݭn��ܸ��|,�v�T�ĪG
		m_PathFlag=TRUE; //���ѭ�����|����
		m_ifZoomonRoad=TRUE; //���Ѫu�u����׺��C
		m_far=1500; //�u���T�����C��,�����f���Z���ܤp�@��,�ŵ����@�Ǭݤ���
		//������,�[�ֺ��C�t��,��ӬO10000,�۷��10����,�u���T�����C�ɤ���
		//�n�o��j
		
	}
	else
	{
		m_ifZoomonRoad=FALSE; //���Ѫu�u����׺��C��FALSE
	}
	
	OnFlyRoutineheight();	//���۹ﰪ�׭���	
}





//�ھں��C���|���{�����I�p��۾��U�Ѽ�
void CT3DSystemView::GetCameraCorrdinate(double x1, double y1, double z1, double x2, double y2, double z2)
{
	//(x1,y1,x1):������|��e�I����
	//(x2,y2,x2):������|�U�@�I����
	

	if(m_FlyHeightType == GIS_FLY_STATICHEIGHT)	//�T�w���׭���覡
	{
		m_vView.x=x2;//�[���Ix����
		m_vView.y=m_StaticHeight;//�[���Iy����=y2+m_StaticHeight�T�w���׭�
		m_vView.z=z2;//�[���Iz����

		m_vPosition.x=x1;//���Ix����
		m_vPosition.y=m_vView.y;//���Iy����=�[���Iy����
		m_vPosition.z=z1;//���Iz����
	}
	//���۹ﰪ��(�Y�u���|)���C�ɡA�ݭp��@�Ӱ򥻰���
	else if(m_FlyHeightType == GIS_FLY_PATHHEIGHT)
	{
		m_vView.x=x2; //�[���Ix����
		m_vView.y=y2+m_StaticHeight; //�[���Iy����=y2+m_StaticHeight�T�w���׭�
		m_vView.z=z2;//�[���Iz����
		
		//�D�G�I�����Z��
		float distance = sqrt((x2-x1)*(x2-x1)+(z2-z1)*(z2-z1));
		//�ھڶɨ��p�Ⱚ�׮t
		float dh = distance * tan(m_ViewUpDown * PAI_D180);
		
		m_vPosition.x=x1;//���Ix����
		m_vPosition.y=m_vView.y+dh;//���Iy����=�[���Iy����+���t
		m_vPosition.z=z1;//���Iz����
	}
}

//�p�⺩�C�ɪ��t��
void CT3DSystemView::CalZoomSpeed(float mCurZooomLC)
{
	static DWORD dwStart = 0;
	DWORD dwNow = ::GetTickCount();
	if(dwNow-dwStart>=100) //0.1��
	{
		long fgf=dwNow-dwStart;
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		CString strText;
		strText.Format("���C�t��= %.3f ��/�� ",(mCurZooomLC-m_PreZooomLC)/(((dwNow-dwStart)/1000.0)),0);
		pMainFrame->Set_BarText(4,strText,0); 
		dwStart = dwNow;
		m_PreZooomLC=mCurZooomLC;
		
	}
}



void CT3DSystemView::BuildQDModelList()
{
	g_3dsModels=new C3DSModel;
	char *str = new char[256]; 
	
	CString str3DSfilename;
	
	strcpy(g_sMediaPath,m_3DSfilename_QD);
	GetFilePath(g_sMediaPath);
	g_3dsModels->LoadModelFromFile((LPTSTR)(LPCTSTR)m_3DSfilename_QD);
	
	glNewList(m_QDList,GL_COMPILE);
	g_3dsModels->Draw(2,&m_QD_minx,&m_QD_maxx,&m_QD_miny,&m_QD_maxy,&m_QD_minz,&m_QD_maxz);	
	glEndList();
	
}

//�Ы��G�D�}����ܦC��
void CT3DSystemView::BuildTunnelDMModelList()
{
	g_3dsModels=new C3DSModel;
	char *str = new char[256]; 
	
	CString str3DSfilename;
	
	m_3DSfilename_TunnelDM=".\\�ҫ�\\�G�D�}��\\���𦡬}��\\�ҫ����.3DS";
	strcpy(g_sMediaPath,m_3DSfilename_TunnelDM);
	GetFilePath(g_sMediaPath);
	g_3dsModels->LoadModelFromFile((LPTSTR)(LPCTSTR)m_3DSfilename_TunnelDM);
	
	glNewList(m_TunnelDMList,GL_COMPILE);
	g_3dsModels->Draw(2,&m_TunnelDM_minx,&m_TunnelDM_maxx,&m_TunnelDM_miny,&m_TunnelDM_maxy,&m_TunnelDM_minz,&m_TunnelDM_maxz);	
	glEndList();

}


void CT3DSystemView::makeQLList()
{
	glNewList(m_QLanList,GL_COMPILE);
		DrawCylinder(m_Bridge.m_Bridge_HLWidth/100.0,m_Bridge.m_Bridge_HLHeight,500);
	glEndList();
	
}

//�e��W
void CT3DSystemView::DrawCylinder(GLfloat radii, GLfloat Height, GLint segmentNum)
{
	if(radii==0   ||   Height==0)   
		return;   
	GLint j,k;   
	GLfloat x,y;   
		
	
	glBegin(GL_TRIANGLE_STRIP);
	for(j=0,k=0;j<=segmentNum;j++,k++)
	{
		x=cos(2.0*PI*j/(double)segmentNum);
		y=sin(2.0*PI*j/(double)segmentNum);
		if(k==segmentNum)
			k=0;
		
		glTexCoord2f(x/radii,0);
		glVertex3f(x*radii, 0,-y*radii);
		
		glTexCoord2f(x/radii,1);
		glVertex3f(x*radii,Height,-y*radii);
		
	}
	glEnd();
}

//�G�D�ѼƳ]�m
void CT3DSystemView::OnMenuTunnelset() 
{
	CTunncelPropertySet dlg;
	dlg.m_tunnel_height=m_Tunnel.height;//�G�D�`����
	dlg.m_tunnel_Archeight=m_Tunnel.Archeight;//�G�D�꩷����
	dlg.m_tunnel_WallHeight =m_Tunnel.height-m_Tunnel.Archeight;//�G�D���𰪫�
	dlg.m_tunnel_ArcSegmentNumber=m_Tunnel.ArcSegmentNumber;//�G�D�꩷���q��
	dlg.m_tunnel_H=m_Tunnel.H ;//�G�D�꩷���ݦA�V�W������
	dlg.m_tunnel_L=m_Tunnel.L;//�G�D�}�����ݥ��k�ⰼ�������e�� 
	if(dlg.DoModal()==IDOK)
	{
		m_Tunnel.height=dlg.m_tunnel_height;//�G�D�`����
		m_Tunnel.Archeight=dlg.m_tunnel_Archeight;//�G�D�꩷����
		m_Tunnel.WallHeight =m_Tunnel.height-m_Tunnel.Archeight;;//�G�D���𰪫�
		m_Tunnel.ArcSegmentNumber=dlg.m_tunnel_ArcSegmentNumber;//�G�D�꩷���q��
		m_Tunnel.H= dlg.m_tunnel_H;//�G�D�꩷���ݦA�V�W������
		m_Tunnel.L=dlg.m_tunnel_L;//�G�D�}�����ݥ��k�ⰼ�������e�� 
		b_haveMadeRail3DwayList=FALSE; //���G�D�ѼƧ��ܮ�,�ݭn���s�c����ܦC��(�z����v�Ҧ�)
		b_haveMadeRail3DwayList_Ortho=FALSE;//���G�D�ѼƧ��ܮ�,�ݭn���s�c����ܦC��(���g��v�Ҧ�)
		OnDraw (GetDC()); //��s�T������
	}	
}

//�]�m���ٰѼ�
void CT3DSystemView::OnMenuBridgeset() 
{
	CBridgeSet dlg;
	dlg.m_Bridge_HLHeight=m_Bridge.m_Bridge_HLHeight;//���������
	dlg.m_Bridge_HLSpace=m_Bridge.m_Bridge_HLSpace;//����������Z
	dlg.m_Bridge_HLWidth=m_Bridge.m_Bridge_HLWidth;//��������e��
	dlg.m_Bridge_QDSpace=m_Bridge.m_Bridge_QDSpace;//���[���Z
	dlg.m_Bridge_HPangle=m_Bridge.m_Bridge_HPangle;//���Y�@�Y�ɨ�
	dlg.m_bridgeColorR=m_bridgeColorR;//��������C��
	dlg.m_bridgeColorG=m_bridgeColorG;//��������C��
	dlg.m_bridgeColorB=m_bridgeColorB;//��������C��

	if(dlg.DoModal()==IDOK)
	{
		m_Bridge.m_Bridge_HLHeight=dlg.m_Bridge_HLHeight;//���������
		m_Bridge.m_Bridge_HLSpace=dlg.m_Bridge_HLSpace;;//����������Z
		m_Bridge.m_Bridge_HLWidth=dlg.m_Bridge_HLWidth;//��������e��
		m_Bridge.m_Bridge_QDSpace=dlg.m_Bridge_QDSpace;//���[���Z
		m_Bridge.m_Bridge_HPangle=dlg.m_Bridge_HPangle;//���Y�@�Y�ɨ�
		m_bridgeColorR=dlg.m_bridgeColorR;//��������C��
		m_bridgeColorG=dlg.m_bridgeColorG;//��������C��
		m_bridgeColorB=dlg.m_bridgeColorB;////��������C��
		b_haveMadeRail3DwayList=FALSE;
		b_haveMadeRail3DwayList_Ortho=FALSE;
		makeQLList(); //���s�ͦ����������ܦC��
		OnDraw (GetDC()); //��s�T������
	}	
}

//ø�s�������
void CT3DSystemView::DrawBridgeHL()
{
		//ø�s�������
		glPushAttrib(GL_TEXTURE_BIT|GL_POLYGON_BIT);
			glDisable(GL_TEXTURE_2D); //�������z
			glPolygonMode(GL_FRONT_AND_BACK ,GL_LINE);	//�H�u��ø�s
			glColor3f(m_bridgeColorR/255.0,m_bridgeColorG/255.0,m_bridgeColorB/255.0);//�]�m��������C��
			glLineWidth(m_Bridge.m_Bridge_HLWidth); //�]�mø�s������u�e
		for (long i=0;i<myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			
			//�p�G��e�M�U�@�����������!=-1�A�hø�s�������
			if(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y1!=-1)
			{	
				
				//�����������������u
				glBegin(GL_LINES);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1+m_Bridge.m_Bridge_HLHeight/2.0,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y1+m_Bridge.m_Bridge_HLHeight/2.0,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
				glEnd();

				//��������������ݾ�u
				glBegin(GL_LINES);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1+m_Bridge.m_Bridge_HLHeight,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y1+m_Bridge.m_Bridge_HLHeight,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
				glEnd();


				//�k���������������u
				glBegin(GL_LINES);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y2+m_Bridge.m_Bridge_HLHeight/2.0,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z2);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y2+m_Bridge.m_Bridge_HLHeight/2.0,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
				glEnd();
				
				//�k������������ݾ�u
				glBegin(GL_LINES);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y2+m_Bridge.m_Bridge_HLHeight,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z2);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y2+m_Bridge.m_Bridge_HLHeight,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
				glEnd();

				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glCallList(m_QLanList);//�եξ��������ܦC��ø�s������W������߬W
				glPopMatrix();


		
				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z2);
				glCallList(m_QLanList);//�եξ��������ܦC��ø�s�k����W������߬W
				glPopMatrix();
			
			}
			
			if(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1==-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1==-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->x1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->y1!=-1)
			{
				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->y1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->z1);
				glCallList(m_QLanList);//�եξ��������ܦC��ø�s������W������߬W
				glPopMatrix();
				
				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->y2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->z2);
				glCallList(m_QLanList);//�եξ��������ܦC��ø�s�k����W������߬W
				glPopMatrix();
				
			}
			if(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x1==-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y1==-1)
			{
				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glCallList(m_QLanList);//�եξ��������ܦC��ø�s������W������߬W
				glPopMatrix();
				
				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z2);
				glCallList(m_QLanList);//�եξ��������ܦC��ø�s�k����W������߬W
				glPopMatrix();
				
			}

		
		}
		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK ,GL_FILL);	
		glPopAttrib();
}

//���s�q�ƾڮw��Ū���u�����u�����I�ƾ�
void CT3DSystemView::ReLoadCenterPt()
{
	CString tt,strSql;
	PCordinate pt;
	
	//���sŪ����ת����u�����u���мƾ�
	//		if(myDesingScheme.SchemeDatass[m_currentSchemeIndexs].EndLC<=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].StartLC)
	//			strSql.Format("SELECT *  FROM  T3DLineZxCorrdinate WHERE ��צW��='%s' ORDER BY ���{ ASC",\
	//			myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename);
	//		else	
	strSql.Format("SELECT *  FROM  T3DLineZxCorrdinate WHERE ��צW��='%s' \
		ORDER BY ���{ ASC",\
		myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename\
		);
	
	try
	{
		//			if(m_Recordset->State) //�p�G
		//				m_Recordset->Close();
		m_Recordset->Open((_bstr_t)strSql,(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);   //���}�ƾڪ� 
	}
	
	catch(_com_error& e)	//���~����
	{
		CString errormessage;
		errormessage.Format("���}����!\r\n���~�H��:%s",e.ErrorMessage());
		::MessageBox(NULL,errormessage,"���}�ƾڪ�",MB_ICONSTOP);
		return;
	} 
	
	myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].RemoveAll(); //�M�Žu�����u�Ʋ�PtS_3DLineZX[]
	while (!m_Recordset->adoEOF)
	{
		pt=new Cordinate;
		
		Thevalue = m_Recordset->GetCollect("x����"); 
		pt->x=(double)Thevalue; //�u�����u�I��x����
		
		Thevalue = m_Recordset->GetCollect("y����"); 
		pt->y=(double)Thevalue;//�u�����u�I��y����
		
		Thevalue = m_Recordset->GetCollect("z����"); 
		pt->z=(double)Thevalue;//�u�����u�I��z����
		
		Thevalue = m_Recordset->GetCollect("��������"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt=Thevalue.bstrVal;
			pt->strJDStyle=tt; //�u�����u�I��x����
		}
		
		Thevalue = m_Recordset->GetCollect("�a�����{"); 
		pt->dmh=(double)Thevalue; //�������a�����{
		
		Thevalue = m_Recordset->GetCollect("�����"); 
		pt->Derh=(double)Thevalue; //�����������
		
		Thevalue = m_Recordset->GetCollect("���{"); 
		pt->Lc=(double)Thevalue;//���������{
		
		myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].Add(pt); //�s�x�u�����u���мƾ�
		m_Recordset->MoveNext(); //���w�U��
		
	}
	m_Recordset->Close(); //�����O����
	
}

//��Y���z
void CT3DSystemView::OnMenuTexturebp() 
{
	CTextureBP	dlg;
	CString strTexturename;

	if(dlg.DoModal()==IDOK) //�p�G�HIDOK�覡������ܮ�
	{
		strTexturename="���z\\��Y���@\\"+dlg.m_BPtextureName; //�o�쯾�z���W���|�W
		m_cTxtureBP.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename); //�[����Y���z
		b_haveMadeRail3DwayList=FALSE; //�T���u����ܦC����Ѭ�FALSE,��ܻݭn���s�c�ؽu���T���ҫ��C��(�z����v�Ҧ��U)
		b_haveMadeRail3DwayList_Ortho=FALSE;//�T���u����ܦC����Ѭ�FALSE,��ܻݭn���s�c�ؽu���T���ҫ��C��(���g��v�Ҧ��U)
		OnDraw (GetDC()); //��s�T������
	}	
}

//���ӯ��z
void CT3DSystemView::OnMenuTexturelj() 
{
	CTextureLJ	dlg;
	CString strTexturename;
	if(dlg.DoModal()==IDOK)//�p�G�HIDOK�覡������ܮ�
	{
		strTexturename="���z\\����\\"+dlg.m_LJtextureName;//�o�쯾�z���W���|�W
		m_cTxtureLJ.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//�[�����ӯ��z
		b_haveMadeRail3DwayList=FALSE; //�T���u����ܦC����Ѭ�FALSE,��ܻݭn���s�c�ؽu���T���ҫ��C��(�z����v�Ҧ��U)
		b_haveMadeRail3DwayList_Ortho=FALSE;//�T���u����ܦC����Ѭ�FALSE,��ܻݭn���s�c�ؽu���T���ҫ��C��(���g��v�Ҧ��U)
		OnDraw (GetDC());//��s�T������
	}	
}

//�����@�Y�����z
void CT3DSystemView::OnMenuTextureqlhpm() 
{
	CTextureQLHpm	dlg;
	CString strTexturename;
	if(dlg.DoModal()==IDOK)//�p�G�HIDOK�覡������ܮ�
	{
		strTexturename="���z\\���U���@�Y��\\"+dlg.m_HQMtextureName;//�o�쯾�z���W���|�W
		m_cBridgeHpm.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//�[�����ӯ��z
		b_haveMadeRail3DwayList=FALSE; //�T���u����ܦC����Ѭ�FALSE,��ܻݭn���s�c�ؽu���T���ҫ��C��(�z����v�Ҧ��U)
		b_haveMadeRail3DwayList_Ortho=FALSE;//�T���u����ܦC����Ѭ�FALSE,��ܻݭn���s�c�ؽu���T���ҫ��C��(���g��v�Ҧ��U)
		OnDraw (GetDC());//��s�T������
	}	
}

//�G�D���𯾲z
void CT3DSystemView::OnMenuTexturetunnel() 
{

	CTextureTunnel	dlg;
	CString strTexturename;
	if(dlg.DoModal()==IDOK)//�p�G�HIDOK�覡������ܮ�
	{
		strTexturename="���z\\�G�D����\\"+dlg.m_TunneltextureName;//�o�쯾�z���W���|�W
		m_cTunnel.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//�[�����ӯ��z
		b_haveMadeRail3DwayList=FALSE; //�T���u����ܦC����Ѭ�FALSE,��ܻݭn���s�c�ؽu���T���ҫ��C��(�z����v�Ҧ��U)
		b_haveMadeRail3DwayList_Ortho=FALSE;//�T���u����ܦC����Ѭ�FALSE,��ܻݭn���s�c�ؽu���T���ҫ��C��(���g��v�Ҧ��U)
		OnDraw (GetDC());//��s�T������
	}		
}

//�G�D�}�����z
void CT3DSystemView::OnMenuTexturetunnelDm() 
{
	CTextureTunnelDm	dlg;
	CString strTexturename;
	if(dlg.DoModal()==IDOK)//�p�G�HIDOK�覡������ܮ�
	{
		strTexturename="���z\\�G�D�}��\\"+dlg.m_TunnelDmtextureName;//�o�쯾�z���W���|�W
		m_cTunnel_dm.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//�[�����ӯ��z
		strTexturename="���z\\�G�D�}���~����Y\\"+dlg.m_TunnelDmtextureName;//�o�쯾�z���W���|�W
		m_cTunnel_dmwcBp.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//�G�D�}���~����Y
		
		b_haveMadeRail3DwayList=FALSE; //�T���u����ܦC����Ѭ�FALSE,��ܻݭn���s�c�ؽu���T���ҫ��C��(�z����v�Ҧ��U)
		b_haveMadeRail3DwayList_Ortho=FALSE;//�T���u����ܦC����Ѭ�FALSE,��ܻݭn���s�c�ؽu���T���ҫ��C��(���g��v�Ҧ��U)
		OnDraw (GetDC());//��s�T������
	}		
}

//�������_�w��ø�s
void CT3DSystemView::DrawClock()
{
//	if(m_bShowClocFlag==FALSE) return;
	
	glPushMatrix(); //���J�x�}���
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); //�uø�s�覡
		glDisable(GL_TEXTURE_2D);	//�������z	
		SetClockProjectionNavigate(); //�]�m���_�w����v�Ѽ�
		glCallList(m_clockList);//�եΫ��_�w��������ܦC��
		DrawNorthPt();	//ø�s���_�w
		
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //��Rø�s�覡
		glEnable(GL_TEXTURE_2D);//���}���z	
		glLineWidth(1.0); //�]�m�u�e
		glColor3f(1.0, 1.0, 1.0); //�]�m�C��
	glPopMatrix();//�u�X�x�}���
}

void CT3DSystemView::SetClockProjectionNavigate()
{
	float wh=120; //�]�m����������
	glViewport(0, WinViewY-wh,wh, wh);//�]�m���f��m�M�j�p
    glMatrixMode( GL_PROJECTION ); //�]�m��e�x�}���z���x�}
    glLoadIdentity(); //�N��e�x�}�m�������} 
	glOrtho (0.0f,1.0,0.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode( GL_MODELVIEW );//�]�m��e�x�}���ҫ��x�}
	glLoadIdentity ();//�N��e�x�}�m�������} 
}

//�Ыخ������_�w��ܦC��
void CT3DSystemView::makeClockList()
{
	glNewList(m_clockList,GL_COMPILE); //�Ы���ܦC��
	float R=0.5,x,y;//������L�b�|
	int i;

	glColor3f(0.0, 1.0, 1.0); //�]�m��r�C��

	x=R*cos((0)*PAI_D180)+0.37;//�[�W�����q�A�ǳƼg�J�r��"E"�A��ܨ��3
	y=R*sin((0)*PAI_D180)+0.48;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"E"); //�b�]�m���Ц�m�g�JE�A��ܤ�V�u�F�v

	x=R*cos((90)*PAI_D180)+0.47;//�[�W�����q�A�ǳƼg�J�r��"N"�A��ܨ��12
	y=R*sin((90)*PAI_D180)+0.36;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"N");//�b�]�m���Ц�m�g�JN�A��ܤ�V�u�_�v
	
	x=R*cos((180)*PAI_D180)+0.59;//�[�W�����q�A�ǳƼg�J�r��"W" �A��ܨ��9
	y=R*sin((180)*PAI_D180)+0.48;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"W");//�b�]�m���Ц�m�g�JW�A��ܤ�V�u��v

	x=R*cos((270)*PAI_D180)+0.48;//�[�W�����q�A�ǳƼg�J�r��"S" �A��ܨ��6
	y=R*sin((270)*PAI_D180)+0.58;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"S");//�b�]�m���Ц�m�g�JS�A��ܤ�V�u�n�v
	
	glColor3f(1.0, 1.0, 1.0); //�]�m������׼Ʀr�C��
	
	x=R*cos((30)*PAI_D180)+0.39; //�]�m����
	y=R*sin((30)*PAI_D180)+0.43;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"2"); //�g�J�Ʀr���
	
	
	x=R*cos((60)*PAI_D180)+0.42;
	y=R*sin((60)*PAI_D180)+0.40;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"1");//�g�J�Ʀr���1
	
	
	x=R*cos((120)*PAI_D180)+0.49;
	y=R*sin((120)*PAI_D180)+0.38;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"11");//�g�J�Ʀr���11
	
	x=R*cos((150)*PAI_D180)+0.55;
	y=R*sin((150)*PAI_D180)+0.42;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"10");//�g�J�Ʀr���10


	x=R*cos((210)*PAI_D180)+0.58;
	y=R*sin((210)*PAI_D180)+0.53;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"8");//�g�J�Ʀr���8

	x=R*cos((240)*PAI_D180)+0.54;
	y=R*sin((240)*PAI_D180)+0.58;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"7");//�g�J�Ʀr���7


	x=R*cos((300)*PAI_D180)+0.43;
	y=R*sin((300)*PAI_D180)+0.58;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"5");//�g�J�Ʀr���5

	x=R*cos((330)*PAI_D180)+0.40;
	y=R*sin((330)*PAI_D180)+0.52;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"4");//�g�J�Ʀr���4
	
    //�]�m�����ꤺ��L���C��
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(2.0); //�]�m�u�e
    //ø�s������~��L
	glBegin(GL_LINE_STRIP);
		for ( i=0;i<=360;i++)
		{
			 x=R*cos(i*PAI_D180)+0.5;
			 y=R*sin(i*PAI_D180)+0.5;
			glVertex2f(x,y);
		}
	glEnd();
	
	//ø�s��������ܤp�ɤ��������,�ζ��I���	
	float d;
	for (i=0;i<=360;i+=6)
	{

		switch(i)
		{
		case 0: //�bN(12�I)�B
			glColor3f(0.0, 1.0, 1.0);//�]�m�C��
			glPointSize(4.0); //�]�m�I���j�p
			break;
		case 90://�bW(9�I)�B
			glColor3f(0.0, 1.0, 1.0);//�]�m�C��
			glPointSize(4.0); //�]�m�I���j�p
			break;
		case 180://�bS(6�I)�B
			glColor3f(0.0, 1.0, 1.0);//�]�m�C��
			glPointSize(4.0); //�]�m�I���j�p
			break;
		case 270://�bE(3�I)�B
			glColor3f(0.0, 1.0, 1.0);//�]�m�C��
			glPointSize(4.0); //�]�m�I���j�p
			break;
		default:
			glColor3f(0.77, 0.67, 0.95);//�]�m�C��
			glPointSize(2.0); //�]�m�I���j�p
			break;
		}
	
		if(i%30==0 && i%90!=0)//�b��ɨ�B(�p7�I,8�I��)
		{	
			glColor3f(1.0, 0.0, 1.0);//�]�m�C��
			glPointSize(3.0);//�]�m�I���j�p
		}
		
		d=0.04;//�����q
		x=R*cos(i*PAI_D180)+0.5;//�p��x����
		y=R*sin(i*PAI_D180)+0.5;//�p��y����
		
		//ø�s�I�лx
		glBegin(GL_POINTS);
			x=x-d*cos(i*PAI_D180);
			y=y-d*sin(i*PAI_D180);
			glVertex2f(x,y);
		glEnd();
		}
	glLineWidth(1.0); //�]�m�u�e
	glEndList();//������ܦC��
	
}

//ø�s���_�w
void CT3DSystemView::DrawNorthPt()
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //�H��R�覡ø�s
	glDisable(GL_TEXTURE_2D); //�������z		
	float R=0.5;
		
	float x1,y1,x2,y2,x3,y3;
	float mPtangle=25;
	float tempangle;
	float L,L1,L2;
	L1=0.3; 
	L2=0.2;
	x1=0.5;y1=0.5; //��������I���СA���_�w��¶���I�i����V����
	x3=x1+L1*cos((m_NorthPtangle)*PAI_D180);
	y3=y1+L1*sin((m_NorthPtangle)*PAI_D180);

	//�p�G���_�w���V������1�H��
	if(m_NorthPtangle>=0 && m_NorthPtangle<=90)
	{	tempangle=m_NorthPtangle-mPtangle;
		L=0.1/cos(mPtangle*PAI_D180);
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1-L2*sin(tempangle*PAI_D180);
		
		glColor3f(1.0, 1.0, 0.0); //�]�m�C��
		glBegin(GL_TRIANGLES);//ø�s�����T����
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
		
		glColor3f(1.0, 0.0, 0.0); //�]�m�C��
		tempangle=m_NorthPtangle+mPtangle;
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1-L2*sin(tempangle*PAI_D180);
		glBegin(GL_TRIANGLES);//ø�s�k���T����
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
	}

	//�p�G���_�w���V������2�H��
	if(m_NorthPtangle>90 && m_NorthPtangle<=180)
	{	

	tempangle=180-m_NorthPtangle-mPtangle;
	x2=x1+L2*cos(tempangle*PAI_D180);
	y2=y1-L2*sin(tempangle*PAI_D180);
	
	glColor3f(1.0, 1.0, 0.0); //�]�m�C��
	glBegin(GL_TRIANGLES);//ø�s�����T����
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
	glEnd();
	
	glColor3f(1.0, 0.0, 0.0); //�]�m�C��
	tempangle=180-m_NorthPtangle+mPtangle;
	x2=x1+L2*cos(tempangle*PAI_D180);
	y2=y1-L2*sin(tempangle*PAI_D180);
	glBegin(GL_TRIANGLES);//ø�s�k���T����
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
	glEnd();
	}

	//�p�G���_�w���V������3�H��
	if(m_NorthPtangle>180 && m_NorthPtangle<=270)
	{	
		
		tempangle=m_NorthPtangle-180-mPtangle;
		x2=x1+L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		
		glColor3f(1.0, 1.0, 0.0);//�]�m�C��
		glBegin(GL_TRIANGLES);//ø�s�����T����
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
		
		glColor3f(1.0, 0.0, 0.0);//�]�m�C��
		tempangle=m_NorthPtangle-180+mPtangle;
		x2=x1+L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		glBegin(GL_TRIANGLES);//ø�s�k���T����
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
	}

	//�p�G���_�w���V������4�H��
	if(m_NorthPtangle>270 && m_NorthPtangle<=360)
	{	
		
		tempangle=360-m_NorthPtangle-mPtangle;
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		
		glColor3f(1.0, 1.0, 0.0);//�]�m�C��
		glBegin(GL_TRIANGLES);//ø�s�����T����
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
		
		glColor3f(1.0, 0.0, 0.0);//�]�m�C��
		tempangle=360-m_NorthPtangle+mPtangle;
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		glBegin(GL_TRIANGLES);//ø�s�k���T����
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
	}

	glColor3f(0.4, 0.47, 0.72);//�]�m�C��
	glLineWidth(2.0); //�]�m�u�e
	glBegin(GL_LINES); //���_�w�U�u���u
		glVertex2f(x1,y1);
		x2=x1-0.1*cos((m_NorthPtangle)*PAI_D180);
		y2=y1-0.1*sin((m_NorthPtangle)*PAI_D180);
		glVertex2f(x2,y2);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); 
	glEnable(GL_TEXTURE_2D); //�}�ү��z		
	glLineWidth(1.0);//�]�m�u�e
}

//�b���w��m��X�奻
void CT3DSystemView::PrintText(float x, float y, char *string)
{
	int length;
	length = (int) strlen(string); //�r�Ŧ����
	glRasterPos2f(x,y); //�w���e����
	for (int m=0;m<length;m++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[m]);//�Φ�Ϥ覡�����w���r��ø�s�@�Ӧr�Ŧ�
	}
	
}

 //�ھڬ۾������I���ЩM�[���I���Эp��������_�w���V����
void CT3DSystemView::GetNorthPtangle()
{
	if(theApp.bLoginSucceed==FALSE) return;
	
	float dx,dz,ar;
	dx=m_vPosition.x-m_vView.x;//�۾����I�P�[���Ix���Ф��t
	dz=m_vPosition.z-m_vView.z;//�۾����I�P�[���Iz���Ф��t
	
	if(dx==0) //�p�Gdx==0
	{
		if(dz>=0) //�p�Gdz>=0
			m_NorthPtangle=90; ////���_�w��l���V����=90�A���V�̹��̭��]Z�b�t��V�^
		else
			m_NorthPtangle=270;////���_�w��l���V����=270�A���V�̹��~���]Z�b����V�^
	}
	else
	{
		if(dx>0) 
		{
			if(dz>0) //��2�H��
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=90+ar*HDANGLE;//���_�w��l���V����
			}
			else    //��3�H��
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=270-ar*HDANGLE;//���_�w��l���V����
			}
		}
		
		if(dx<0)
		{
			if(dz>0)  //��1�H��
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=90-ar*HDANGLE;//���_�w��l���V����
			}
			else    //��4�H��
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=270+ar*HDANGLE;//���_�w��l���V����
			}
		}
		
	}
}


//����ʳ��ϰ�
void CT3DSystemView::GetRoadCloseRegion()
{
	CString tt,m_style,m_style2;
	
	PCordinate pt=NULL;
	mRegions.RemoveAll();
	
	int m_reginNums=0; //�ʳ��ϰ��
	int mBridgeindex=0;//���ٯ��ު�l��
	int mTunnelindex=0;//�G�D���ު�l��

	m_ReginPtsLeft.RemoveAll(); //����ɫʳ��ϰ�ƾ��I�M��
	m_ReginPtsRight.RemoveAll();//�k��ɫʳ��ϰ�ƾ��I�M��

	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	float fPer=100.0/(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1);
	for (long i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
	{

		tt.Format("���b�c�ؽu�������ʳ��ϰ�,�w���� %.2f%s",(i+1)*fPer,"%");
		pMainFrame->Set_BarText(4 , tt , 0); 
	
		//�u����e�_�����I����
		m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
		//�u���U�@�_�����I����
		m_style2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;
		//�p�G���I�����D���٩M�G�D�I
		if(m_style!="�G�D�_�I" && m_style!="�G�D�����I" &&m_style!="�G�D���I" \
			&&m_style!="���ٰ_�I"  &&m_style!="���٤����I" &&m_style!="���ٲ��I" \
			&& m_style2!="�G�D�_�I")
		{
			//�u����e�_��������Y��
			int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_L-1;
			//�u���U�@�_��������Y��
			int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_L-1;
			
			//�p�G���{���_����Y����������P
			if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->TW_left!=\
				myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->TW_left)
			{
				if(N1>=0) //�p�G�u����e�_��������Y��>=1
				{
					for(int m=N1;m>=0;m--) //�q�̰��@����Y�}�l�O���Ҧ���Y�I
					{
						for(int n=2;n>=0;n--)
						{
							pt=new Cordinate;
							pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].x;
							pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].y;
							pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].z;
							m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
						}
						
					}
				}
				else //�u����e�_��������n�O��������I,�h�����N������Y�I�@������I
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1;
					m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
				}

				if(N2>=0) //�p�G�u���U�@�_��������Y��>=1
				{
					for(int m=0;m<=N2;m++) //�q�̧C�@����Y�}�l�O���Ҧ���Y�I
					{
						for(int n=0;n<=2;n++)
						{
							pt=new Cordinate;
							pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].x;
							pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].y;
							pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].z;
							m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
						}
						
					}
				}
				else //�u���U�@�_��������n�O��������I,�h�����N������Y�I�@������I
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1;
					m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
				}
				
			}
			else //�p�G���{���_����Y��������ۦP,
			{
				//�p��u����e�_���迳����g�J����ɧ����I�ƾ�
				if(N1>=0) //�p�G�u����e�_��������Y��>=1
				{
					if(N1<=N2) //�p�G�u����e�_��������Y��<=�u���U�@�_��������Y��,�u�O����e�_���̰��@����Y�I����
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N1].Hp[2].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N1].Hp[2].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N1].Hp[2].z;
						m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
					}
					else //�p�G�u����e�_��������Y��>�u���U�@�_��������Y��
					{
						for(int m=N2+1;m<=N1;m++) //�ݭn�q�W�ܤU�O����U�@�_���h�X����Y�Ҧ���Y�I����
						{
							for(int n=2;n>=0;n--)
							{
								pt=new Cordinate;
								pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].x;
								pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].y;
								pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].z;
								m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
							}
								
						}
						//�u�ݭn�O���u���U�@�_�����̰��@����Y�I����
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N2].Hp[1].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N2].Hp[1].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N2].Hp[1].z;
						m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
						
					}
				}
				else  //�u����e�_��������n�O��������I,�h�����N������Y�I�@������I
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1;
					m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
				}

				//�p��u���U�@�_���迳����g�J����ɧ����I�ƾ�
				if(N2>=0) //�p�G�u���U�@�_��������Y��>=1
				{
					if(N2<=N1)//�p�G�u���U�@�_��������Y��<=�u����e��������Y��,�u�O���U�@�_���̰��@����Y�I����
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N2].Hp[2].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N2].Hp[2].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N2].Hp[2].z;
						m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
					}
					else  //�p�G�u���U�@�_��������Y��>�u����e�_��������Y��
					{
						for(int m=N1+1;m<=N2;m++)//�ݭn�q�U�ܤW�O�����e�_���h�X����Y�Ҧ���Y�I����
						{
							for(int n=0;n<=2;n++)
							{
								pt=new Cordinate;
								pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].x;
								pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].y;
								pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].z;
								m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
							}
							
						}
						//�ɥR�u���U�@�_��������e�_���̰��@�Ū���Y�I����
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N1].Hp[1].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N1].Hp[1].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N1].Hp[1].z;
						m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
						
					}
				}
				else  //�u���U�@�_��������n�O��������I,�h�����N������Y�I�@������I
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1;
					m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
				}
			}	
				
		}
		else //�p�G���I�����O"�G�D�_�I",��ܹJ��F�G�D�_�l��
		{
			
			if(m_style=="�G�D�_�I")
			{
				//�u���e�@���I������Y��
				int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->Huponums_L-1;
				for(int j=N1;j>0;j--) //�O���u���e�@�_�������Ҧ���Y�I
				{
					for(int k=2;k>=0;k--) //�C�@����Y��3���I�զ�
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_L[j].Hp[k].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_L[j].Hp[k].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_L[j].Hp[k].z;
						m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
						
					}
				}

				//�o���G�D�i�f�}���B���Ҧ������I�ƾ�,�@������I�ƾ�
				int M=myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_Start.GetSize();
				for(int k=0;k<M;k++)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_Start.GetAt(k)->x;
					pt->y =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_Start.GetAt(k)->y;
					pt->z =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_Start.GetAt(k)->z;
					m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
				}

				WriteRegionPts(m_reginNums,TRUE,-1);//��e�ʳ��ϰ쵲��,�g�J��������I���мƾ�
				m_ReginPtsLeft.RemoveAll();//�ƲղM��
				m_reginNums++; //�ʳ��ϰ��+1
							
			}
			else if(m_style=="���ٰ_�I") //�p�G���I�����O"���ٰ_�I"
			{
				//�o��Ӿ��ٰ_�l�I�B�U�ոլ��@�Y�I��,,�@������I�ƾ�
				int M=myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_Start.GetSize();
				for(int k=0;k<M;k++)
				{
					
					pt=new Cordinate;
					pt->x =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_Start.GetAt(k)->x;
					pt->y =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_Start.GetAt(k)->y;
					pt->z =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_Start.GetAt(k)->z;
					m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
					
				}
				WriteRegionPts(m_reginNums,TRUE,-1);//��e�ʳ��ϰ쵲��,�g�J��������I���мƾ�
				m_ReginPtsLeft.RemoveAll();//�ƲղM��
				m_reginNums++;//�ʳ��ϰ��+1
				
			}			
			
			else if (m_style=="�G�D���I")//�p�G���I�����O"�G�D���I",��ܹJ��F�G�D�פ��,��ܷs���ʳ��ϰ�}�l�F
			{
				
				//�o���G�D�X�f�}���B���Ҧ������I�ƾ�,�@������I�ƾ�
				int M=myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_End.GetSize();
				for(int k=M-1;k>=0;k--)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_End.GetAt(k)->x;
					pt->y =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_End.GetAt(k)->y;
					pt->z =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_End.GetAt(k)->z;
					m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
					
				}

				//�u���U�@�_��������Y��
				int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_L-1;
                //�ɥR�u���U�@�_��������1�ųs�Y���̰��I����
				pt=new Cordinate;
				pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[0].Hp[2].x;
				pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[0].Hp[2].y;
				pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[0].Hp[2].z;
				m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
				
				//�O���u���U�@�_��������Y��2�Ũ�̽ը�ũҦ���Y�I����,�@������I�ƾ�
				for(int j=1;j<=N1;j++)
				{
					for(int k=0;k<=2;k++)
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[k].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[k].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[k].z;
						m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
					}
				}
				mTunnelindex++; //��F�G�D�פ��,��ܤ@�y�G�D�����F,�G�D����+1
			}
			
			else if (m_style=="���ٲ��I") //�p�G���I�����O"���ٲ��I",��ܹJ��F���ٲפ��,��ܷs���ʳ��ϰ�}�l�F
			{
				
				//�o����ٵ����B�U�誺�Ҧ��@�Y�I���мƾ�,�@������I�ƾ�
				int M=myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_End.GetSize();
				for(int k=M-1;k>=0;k--)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_End.GetAt(k)->x;
					pt->y =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_End.GetAt(k)->y;
					pt->z =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_End.GetAt(k)->z;
					m_ReginPtsLeft.Add(pt);//�s�x�I���мƾ�
					
				}

				mBridgeindex++; //��F���ٲפ��,��ܤ@�y���ٵ����F,���ٯ��޸�+1
			}
			
			
		}

	}

	m_reginNums=0;
	m_ReginPtsRight.RemoveAll(); //�k������I�M��
	for ( i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		tt.Format("���b�c�ؽu���k���ʳ��ϰ�,�w���� %.2f%s",(i+1)*fPer,"%");
		pMainFrame->Set_BarText(4 , tt , 0); 

		//�u����e�_�����I����
		m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
 		//�u���U�@�_�����I����
		m_style2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;
		
		//�p�G���I�����D���٩M�G�D�I
		if(m_style!="�G�D�_�I" && m_style!="�G�D�����I" &&m_style!="�G�D���I"\
			&&m_style!="���ٰ_�I"  &&m_style!="���٤����I" &&m_style!="���ٲ��I" \
			&&m_style2!="�G�D�_�I")
		{
			//�u����e�_���k����Y��
			int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_R-1;
			//�u���U�@�_���k����Y��
			int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_R-1;
			//�p�G���{���_����Y����������P
			if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->TW_right!=\
				myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->TW_right)
			{
				if(N1>=0)  //�p�G�u����e�_���k����Y��>=1
				{
					for(int m=N1;m>=0;m--) //�q�̰��@����Y�}�l�O���Ҧ���Y�I
					{
						for(int n=2;n>=0;n--)
						{
							pt=new Cordinate;
							pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].x;
							pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].y;
							pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].z;
							m_ReginPtsRight.Add(pt);//�s�x�I���мƾ�
						}
						
					}
				}
				else//�u����e�_���k����n�O��������I,�h�����N������Y�I�@������I
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2;
					m_ReginPtsRight.Add(pt);
				}
				
				if(N2>=0) //�p�G�u���U�@�_���k����Y��>=1
				{
					for(int m=0;m<=N2;m++) //�q�̧C�@����Y�}�l�O���Ҧ���Y�I
					{
						for(int n=0;n<=2;n++)
						{
							pt=new Cordinate;
							pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].x;
							pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].y;
							pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].z;
							m_ReginPtsRight.Add(pt);//�s�x�I���мƾ�
						}
						
					}
				}
				else//�u���U�@�_���k����n�O��������I,�h�����N������Y�I�@������I
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2;
					m_ReginPtsRight.Add(pt);//�s�x�I���мƾ�
				}
				
			}
			else//�p�G���{���_����Y��������ۦP
			{
				//�p��u����e�_��������ɧ����I�ƾ�
				if(N1>=0) //�p�G�u����e�_���k����Y��>=1
				{
					if(N1<=N2)//�p�G�u����e�_���k����Y��<=�u���U�@�_���k����Y��,�u�O����e�_���̰��@����Y�I����
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N1].Hp[2].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N1].Hp[2].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N1].Hp[2].z;
						m_ReginPtsRight.Add(pt);//�s�x�I���мƾ�
					}
					else //�p�G�u����e�_���k����Y��>�u���U�@�_���k����Y��
					{
						for(int m=N2+1;m<=N1;m++) //�ݭn�q�W�ܤU�O����U�@�_���h�X����Y�Ҧ���Y�I����
						{
							for(int n=2;n>=0;n--)
							{
								pt=new Cordinate;
								pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].x;
								pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].y;
								pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].z;
								m_ReginPtsRight.Add(pt);//�s�x�I���мƾ�
							}
						}
						//�u�ݭn�O���u���U�@�_�����̰��@����Y�I����
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N2].Hp[1].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N2].Hp[1].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N2].Hp[1].z;
						m_ReginPtsRight.Add(pt);//�s�x�I���мƾ�
					}		
				}
				else //�u����e�_���k����n�O��������I,�h�����N������Y�I�@������I
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2;
					m_ReginPtsRight.Add(pt);	//�s�x�I���мƾ�
				}
			
				//�p��u���U�@�_�����Ӽg�J����ɧ����I�ƾ�
				if(N2>=0) //�p�G�u���U�@�_���k����Y��>=1
				{				
					if(N2<=N1)//�p�G�u���U�@�_���k����Y��<=�u����e���k����Y��,�u�O���U�@�_���̰��@����Y�I����
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N2].Hp[2].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N2].Hp[2].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N2].Hp[2].z;
						m_ReginPtsRight.Add(pt);//�s�x�I���мƾ�
					}
					else//�p�G�u���U�@�_���k����Y��>�u����e�_���k����Y��
					{
						for(int m=N1+1;m<=N2;m++)//�ݭn�q�U�ܤW�O�����e�_���h�X����Y�Ҧ���Y�I����
						{
							for(int n=0;n<=2;n++)
							{
								pt=new Cordinate;
								pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].x;
								pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].y;
								pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].z;
								m_ReginPtsRight.Add(pt);//�s�x�I���мƾ�
							}
						}
						//�ɥR�u���U�@�_��������e�_���̰��@�Ū���Y�I����
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N1].Hp[1].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N1].Hp[1].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N1].Hp[1].z;
						m_ReginPtsRight.Add(pt);//�s�x�I���мƾ�
						
					}
				}
				else  //�u���U�@�_���k����n�O��������I,�h�����N������Y�I�@������I
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2;
					m_ReginPtsRight.Add(pt);//�s�x�I���мƾ�
				}
			}
		}
		else
		{
			if(m_style=="�G�D�_�I") //�p�G���I�����O"�G�D�_�I",��ܹJ��F�G�D�_�l��
			{
				//�u���e�@���I�k����Y��
				int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->Huponums_R-1;
				for(int j=N1;j>0;j--)//�O���u���e�@�_���k���Ҧ���Y�I
				{
					for(int k=2;k>=0;k--)//�C�@����Y��3���I�զ�
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_R[j].Hp[k].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_R[j].Hp[k].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_R[j].Hp[k].z;
						m_ReginPtsRight.Add(pt);//�s�x�I���мƾ�
						
					}
				}

				WriteRegionPts(m_reginNums,FALSE,1); //��e�ʳ��ϰ쵲��,�g�J�k������I���мƾ�
				m_ReginPtsRight.RemoveAll();//�ƲղM��
				m_reginNums++;//�ʳ��ϰ��+1
				
			}
			else if(m_style=="���ٰ_�I")//�p�G���I�����O"���ٰ_�I"
			{
				WriteRegionPts(m_reginNums,FALSE,1);//��e�ʳ��ϰ쵲��,�g�J�k������I���мƾ�
				m_ReginPtsRight.RemoveAll();//�ƲղM��
				m_reginNums++;//�ʳ��ϰ��+1
				
			}			
			else if(m_style=="�G�D���I")//�p�G���I�����O"�G�D���I",��ܹJ��F�G�D�פ��,��ܷs���ʳ��ϰ�}�l�F
			{

				//�o���G�D�X�f�}���B���Ҧ������I�ƾ�,�@������I�ƾ�
				int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_R-1;
				for(int j=1;j<=N1;j++)
				{
					for(int k=0;k<=2;k++)
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[k].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[k].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[k].z;
						m_ReginPtsRight.Add(pt);//�s�x�I���мƾ�
					}
				}
				mTunnelindex++;//��F�G�D�פ��,��ܤ@�y�G�D�����F,�G�D����+1
			}
			
			else if (m_style=="���ٲ��I")//�p�G���I�����O"���ٲ��I",��ܹJ��F���ٲפ��,��ܷs���ʳ��ϰ�}�l�F
			{
				mBridgeindex++;//��F���ٲפ��,��ܤ@�y���ٵ����F,���ٯ��޸�+1
			}
		}
		
	}

	//�藍�X�z���举�ϰ�i��M�z
	for(i=0;i<mRegions.GetSize();i++)
	{
		if(mRegions.GetAt(i)->ReginPts.GetSize()<=1) //�p�G�ʳ��ϰ�ƾ��I<=1
		{
			mRegions.RemoveAt(i);//����
		}
	}
}

//ø�s�g�L�u���ؤT���ҫ᪺�T���a��TIN
void CT3DSystemView::DrawTerrainDelaunay()
{
	
	if(b_haveTerrainZoomroadList==TRUE)   //�p�G�w���c�ؽu���T���ҫ�����ܦC��
	{
		glCallList(m_TerrainZoomroadList);
		return;
	}


	if(m_currentSchemeIndexs<0) //�p�G��e�u����ׯ���<0�A��^
		return;
	
	if(	b_haveGetRegion==TRUE) //�p�G�w�g����u���ʳ��ϰ�A��^
		return;
	//�S���g�L�u���T���ؼҪ�^
	if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()<=1)
		return;
	if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()<=1)
		return;
	
	BeginWaitCursor();
	
	CString m_style,m_style2;
	long i;

	//�Ыؽu���T���ؼҫ�O�_�إߤF�a��TIN�ҫ�����ܦC��
	glNewList(m_TerrainZoomroadList,GL_COMPILE_AND_EXECUTE);
	
	glPushAttrib(GL_TEXTURE_BIT|GL_POLYGON_BIT);
	glDisable(GL_TEXTURE_2D); //�������z
	glLineWidth(2.0); //�]�m�u�e
	glColor3f(0.2,0,1.0); //�]�m�C��
	
	GetRoadCloseRegion();//����ʳ��ϰ�
	BuildTerrainRegionInfo(); //�p��C�Ӧa�ζ��s�P�ʳ��ϰ쪺�Ҧ��a�μƾڶ�
	m_BlockTriInfos.RemoveAll(); //�a�ζ��T�����H���M��
	
	CString tt;
	float fPer=100.0/m_BlockLSPts.GetSize();
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	for( i=0;i<m_BlockLSPts.GetSize();i++)   
	{
		tt.Format("���bø�s�a��TIN�ҫ�,�w���� %.2f%s",(i+1)*fPer,"%");
		pMainFrame->Set_BarText(4 , tt , 0); 
		
		DrawTerrainTIN(i); //�HTIN�覡ø�s�a�ζ�i
		tempBlockTriInfos=new BlockTriInfos;
		for_each(m_Triangles.begin(), m_Triangles.end(), GetBlockTriangles(i));
		AddBlcokTri(i,m_BlockLSPts.GetAt(i)->mDemBlockRow,m_BlockLSPts.GetAt(i)->mDemBlockCol);//�[�J��e�a�ζ����T�����ƾ�(�P�ɭn�簣���u���ʳ��ϰ쪺�Ҧ��T����)
	}
	glEndList();
	b_haveTerrainZoomroadList=TRUE;//�u���T���ؼҫ�O�_�إߤF�a��TIN�ҫ�����ܦC��
	EndWaitCursor();
	MessageBox("�ؼҧ���","�u���T���ؼ�",MB_ICONINFORMATION);
	pMainFrame->Set_BarText(4 , "�[���a�λP�v�����z�ƾڧ���!" , 0); 
}

//�N����I���мƾڼg�J�ʳ��ϰ�
void CT3DSystemView::WriteRegionPts(int index, BOOL bAddorAppend, int mLeftorRight)
{
	PRegions tempregion=new Regions;
	PCordinate pt=NULL;
	
	if(bAddorAppend==TRUE)  //�p�G�O�W�[����I�AmRegions�Ʋշs�W�[����
	{
		tempregion->index=index; //�ʳ��ϰ����
		for(long i=0;i<m_ReginPtsLeft.GetSize();i++)//�Ҧ�������I�ƾ�
		{
			pt=new Cordinate;
			pt->x=m_ReginPtsLeft.GetAt(i)->x;
			pt->y=m_ReginPtsLeft.GetAt(i)->y;
			pt->z=m_ReginPtsLeft.GetAt(i)->z;
			tempregion->ReginPts.Add(pt);//�s�x���{�ɼƲդ�
		}
		mRegions.Add(tempregion);//�[�J��ɼƾ�
	}
	else if(bAddorAppend==FALSE)  //�p�G���O�s�W�ƾڡA�����VmRegions�Ʋկ��ަ�m�g�J�ƾ�
	{
		//�Ҧ��k����I�ƾ�
		for(long i=m_ReginPtsRight.GetSize()-1;i>=0;i--)
		{
			pt=new Cordinate;
			pt->x=m_ReginPtsRight.GetAt(i)->x;
			pt->y=m_ReginPtsRight.GetAt(i)->y;
			pt->z=m_ReginPtsRight.GetAt(i)->z;
			mRegions.GetAt(index)->ReginPts.Add(pt);//�[�J�k����I�ƾ�
		}
		m_ReginPtsRight.RemoveAll();//�k����I�ƲղM��
		
		
	}
}

//�ھګʳ��ϰ���ɤW���ƾ��I�A�p��ӫʳ��ϰ��V���a�ζ�ID��
//�Y�ʳ��ϰ��V�h�Ӧa�ζ��A�h��O�����a�ζ�ID���]���h��
void CT3DSystemView::GetRegionID(long index)
{
	double x,y;
	int ID;
	mRegions.GetAt(index)->GridID.RemoveAll();
	for(long i=0;i<mRegions.GetAt(index)->ReginPts.GetSize();i++)
	{
		
		x=mRegions.GetAt(index)->ReginPts.GetAt(i)->x;//�ʳ��ϰ���ɤW���ƾ��I��x����	
		y=-mRegions.GetAt(index)->ReginPts.GetAt(i)->z;//�ʳ��ϰ���ɤW���ƾ��I��y����
		
		ID=GetBlockID(x,y);	//�ھ�x,y���ШD�����ݩ󪺦a�ζ���ID��
		
		bool bhaveExit=FALSE; //��l���Ѭ�FALSE
		for(int k=0;k<mRegions.GetAt(index)->GridID.GetSize();k++)
		{
			int mid=mRegions.GetAt(index)->GridID.GetAt(k);
			if(ID==mid) //�p�G�D�o�a�ζ�ID���b�O������ID���ۦP�A�h�����A���A�O��
			{
				bhaveExit=TRUE;
				break;
			}
		}
		if(bhaveExit==FALSE) ////�p�G�D�o�a�ζ�ID���P�Ҧ��O������ID�����P�A�h�O��
			mRegions.GetAt(index)->GridID.Add(ID);//�O��ID��
	}
}

//�p��C�Ӧa�ζ��s�P�ʳ��ϰ쪺�Ҧ��a�μƾڶ�
void CT3DSystemView::BuildTerrainRegionInfo()
{
	//�p�G�S���a�μƾ�
	if(theApp.m_BlockRows*theApp.m_BlockCols<=0)
		return;

	long i,j;
	//�p��C�ӫʳ��l�ϰ쪺�̤p�̤jx,y����
	for( i=0;i<mRegions.GetSize();i++)
	{
		GetRegionID(i);//�o��ʳ��ϰ�ID
		double minx,miny,maxx,maxy;
		minx=miny=999999999;
		maxx=maxy=-999999999;
		//�p��ʳ��̤j,�̤p����
		for( j=0;j<mRegions.GetAt(i)->ReginPts.GetSize();j++)
		{
			if(minx>mRegions.GetAt(i)->ReginPts.GetAt(j)->x)
				minx=mRegions.GetAt(i)->ReginPts.GetAt(j)->x;
			if(miny>-mRegions.GetAt(i)->ReginPts.GetAt(j)->z)
				miny=-mRegions.GetAt(i)->ReginPts.GetAt(j)->z;
			if(maxx<mRegions.GetAt(i)->ReginPts.GetAt(j)->x)
				maxx=mRegions.GetAt(i)->ReginPts.GetAt(j)->x;
			if(maxy<-mRegions.GetAt(i)->ReginPts.GetAt(j)->z)
				maxy=-mRegions.GetAt(i)->ReginPts.GetAt(j)->z;
			
		}
		mRegions.GetAt(i)->minx=minx;
		mRegions.GetAt(i)->miny=miny;
		mRegions.GetAt(i)->maxx=maxx;
		mRegions.GetAt(i)->maxy=maxy;
	}
	
	b_haveGetRegion=TRUE; //���Ѥw�p��ʳ��ϰ쬰TRUE

	//���s�w�q�Ʋդj�p�A�ä��t���s
	mBlockReginInforMe=new CArray<PBlockReginInforMe,PBlockReginInforMe>[theApp.m_BlockRows*theApp.m_BlockCols];
	m_BlockLSPts.RemoveAll();//�M��

	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	float fper=100.0/(theApp.m_BlockRows*theApp.m_BlockCols);
	CString tt;
	for(i=1;i<=theApp.m_BlockRows;i++)
	{
		for( j=1;j<=theApp.m_BlockCols;j++)
		{
			tt.Format("���b�p��C�Ӧa�ζ��s�P�ʳ��ϰ쪺�Ҧ��a�μƾڶ�,�w���� %.2f%s",i*j*fper,"%");
			pMainFrame->Set_BarText(4 , tt , 0); 
			
			GetBlockInregion(i,j); //�o��a�ζ��ʳ��ϰ�H��
			WriteBlockLsPts(i,j);//�N�a�ζ��ʳ��ϰ�H���g�J
		}
	}
}

//ø�s�a�ζ��T�����a��
void CT3DSystemView::DrawTerrainTIN(long blockIndex)
{
	m_Vertices.clear(); //���I�M��
	m_Triangles.clear();//�T���βM��
	double x,y,z;
	
	CDelaunay d; //�w�qCDelaunay�ܶq
	//����Y�Ӧa�ζ����Ҧ����Ħa�μƾ��I,�ѻP�a�ΤT�������c��
	for(long j=0;j<m_BlockLSPts.GetAt(blockIndex)->ReginPts.GetSize();j++)
	{
		x=m_BlockLSPts.GetAt(blockIndex)->ReginPts.GetAt(j)->x; //x����
		y=-m_BlockLSPts.GetAt(blockIndex)->ReginPts.GetAt(j)->z;//y����
		z=m_BlockLSPts.GetAt(blockIndex)->ReginPts.GetAt(j)->y;//z����(���{)
		if(z!=theApp.m_DEM_IvalidValue) //�p�G���{�O�L�ĭ�,�N���ѻP�T�����c��
			m_Vertices.insert(vertex(x, y,z));
	}
	d.Triangulate(m_Vertices, m_Triangles);//�ھڦa�μƾ��I(m_Vertices���s�x)�c�ئa�ΤT����
}

//�[�J��e�a�ζ����T�����ƾ�(�P�ɭn�簣���u���ʳ��ϰ쪺�Ҧ��T����)
void CT3DSystemView::AddBlcokTri(int blockIndex, int DemblcokRow, int DemblcokCol)
{
	for(long i=0;i<tempBlockTriInfos->TriPts.GetSize();i++)
	{
		//�P�_�a�ζ�TIN�T���άO�_���a�ζ����ʳ��ϰ줺
		BOOL bOk=GetTriOutRegion(\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt1.x,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt1.y,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt2.x,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt2.y,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt3.x,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt3.y,\
			blockIndex);
		if(bOk==TRUE) //�p�G�T���άO���a�ζ����ʳ��ϰ줺,�Hx����=-9999�Ӽ���
			tempBlockTriInfos->TriPts.GetAt(i)->Pt1.x=-9999;
	}
	
	tempBlockTriInfos->mDemBlockRow=DemblcokRow;//��e�a�ζ����渹
	tempBlockTriInfos->mDemBlockCol=DemblcokCol;//��e�a�ζ����C��
	m_BlockTriInfos.Add(tempBlockTriInfos);//�[�J��e�a�ζ����T�����H��
}

//�P�_�a�ζ�TIN�T���άO�_���a�ζ����ʳ��ϰ줺
BOOL CT3DSystemView::GetTriOutRegion(double x1, double y1, double x2, double y2, double x3, double y3, int blockIndex)
{
	Point *polygon;	
	Point pt;
	bool b1,b2,b3;	
	int m_a1,m_a2,m_a3;
	m_a1=m_a2=m_a3=0; //��l���Ѭ�0

	//���e�a�ζ����@�����ʳ��ϰ�i��P�_
	//mBlockReginInforMe[blockIndex].GetSize()�G��e�a�ζ����@�����ʳ��ϰ��`��
	for(int i=0;i<mBlockReginInforMe[blockIndex].GetSize();i++)
	{
		//�p�G�T���Ϊ��T���I�������ʳ��ϰ�̤j�̤p�x����ɤ��~
		//�h�ӤT���Υ����ʳ��ϰ�~,���ݥέ簣
		if((x1<mBlockReginInforMe[blockIndex].GetAt(i)->minx && \
			x2<mBlockReginInforMe[blockIndex].GetAt(i)->minx && \
			x3<mBlockReginInforMe[blockIndex].GetAt(i)->minx)|| \
			(x1>mBlockReginInforMe[blockIndex].GetAt(i)->maxx && \
			x2>mBlockReginInforMe[blockIndex].GetAt(i)->maxx && \
			x3>mBlockReginInforMe[blockIndex].GetAt(i)->maxx)|| \
			(y1<mBlockReginInforMe[blockIndex].GetAt(i)->miny && \
			y2<mBlockReginInforMe[blockIndex].GetAt(i)->miny && \
			y3<mBlockReginInforMe[blockIndex].GetAt(i)->miny)|| \
			(y1>mBlockReginInforMe[blockIndex].GetAt(i)->maxy && \
			y2>mBlockReginInforMe[blockIndex].GetAt(i)->maxy && \
			y3>mBlockReginInforMe[blockIndex].GetAt(i)->maxy))
		{
			m_a1=m_a2=m_a3=0;//3�I�����ʳ��ϰ줺�A�T�I���ѥ���0
		}
		else
		{
			//Ū���ʳ��ϰ�Ҧ�������I
			long M=mBlockReginInforMe[blockIndex].GetAt(i)->ReginPts.GetSize();
			polygon=new Point[M];
			for(long j=0;j<M;j++)
			{
				polygon[j].x=mBlockReginInforMe[blockIndex].GetAt(i)->ReginPts.GetAt(j)->x;
				polygon[j].y=-mBlockReginInforMe[blockIndex].GetAt(i)->ReginPts.GetAt(j)->z;
			}
			
			
			pt.x=x1; pt.y=y1;
			b1=mCalF.InPolygon(polygon,M,pt);//�P�_�I(x1,y1)�O�_���ӫʳ��ϰ줺
			if(b1==true) //�p�G���
				m_a1=1;
			
			pt.x=x2; pt.y=y2;
			b2=mCalF.InPolygon(polygon,M,pt);//�P�_�I(x2,y2)�O�_���ӫʳ��ϰ줺
			if(b2==true)//�p�G���
				m_a2=1;
			
			pt.x=x3; pt.y=y3;//�P�_�I(x3,y3)�O�_���ӫʳ��ϰ줺
			b3=mCalF.InPolygon(polygon,M,pt);
			if(b3==true)//�p�G���
				m_a3=1;
			
			//�p�G3�I����󤺳��Φb�ʳ��ϰ���ɤW,�ݭn�i�@�B�P�_
			//�]���p�G3�I�����ʳ��ϰ���ɤW,�ӤT���ι�ڤW�O���ʳ��ϰ줧�~ ,���ݭn�R��
			if(m_a1==1 && m_a2==1 && m_a3==1)
			{
				pt.x=(x1+x2)/2; pt.y=(y1+y2)/2; //(x1,y1)�M(x2,y2)���I����
				b1=mCalF.InPolygon(polygon,M,pt);//�P�_���I�_���ӫʳ��ϰ줺
				if(b1==false)//�p�G�����
					m_a1=0;
				
				if(m_a1==1) //�p�G(x1,y1)�M(x2,y2)���I���Ц��ӫʳ��ϰ줺
				{
					pt.x=(x2+x3)/2; pt.y=(y2+y3)/2;//(x2,y2)�M(x3,y3)���I����
					b1=mCalF.InPolygon(polygon,M,pt);//�P�_���I�_���ӫʳ��ϰ줺
					if(b2==false)//�p�G�����
						m_a2=0;
				}
				
				if(m_a1==1 && m_a2==1) //�p�G(x1,y1)�M(x2,y2)�H��(x2,y2)�M(x3,y3)�����I���Ц��ӫʳ��ϰ줺
				{
					pt.x=(x1+x3)/2; pt.y=(y1+y3)/2;//(x1,y1)�M(x3,y3)���I����
					b3=mCalF.InPolygon(polygon,M,pt);
					if(b3==false)//�p�G�����
						m_a3=0;
				}
			} 
			
			
			
			if(m_a1+m_a2+m_a3>=3) //�p�G�T���Ϊ�3�I�H�ΤT�䤤�I�����ʳ��ϰ줺, �h�ӤT���Φ��ʳ��ϰ줺
			{
				return TRUE; //��^TURE,��ܤT���Φ��ʳ��ϰ줺,�ݭn�簣
				break;
				
			}
		}
	}
	
	return FALSE;//��^FALSE,��ܤT���Τ����ʳ��ϰ줺,���ݭn�簣
}

//�o��a�ζ��ʳ��ϰ�H��
void CT3DSystemView::GetBlockInregion(int blockRow, int blockCol)
{
	int bInCur,bInPre;
	double minx,miny,maxx,maxy;
	double block_minx,block_miny,block_maxx,block_maxy;

	/*
					-------------(block_maxx,block_maxy)
					|        	|
					|        	|
					|        	|
					|        	|
					|        	|
					-------------
				(block_minx,block_miny)
	*/

	block_minx=(blockCol-1)*theApp.m_Dem_BlockWidth;//�a�ζ��̤px����
	block_maxx=blockCol*theApp.m_Dem_BlockWidth;//�a�ζ��̤jx����
	block_miny=(blockRow-1)*theApp.m_Dem_BlockWidth;//�a�ζ��̤py����
	block_maxy=blockRow*theApp.m_Dem_BlockWidth;//�a�ζ��̤jy����
	
	int Mnus;
	PCordinate pt;
	Point  edgePts[4];
	
	long iNdex=(blockRow-1)*theApp.m_BlockCols+(blockCol-1);//�ھڦ�C���p��a�ζ��b�Ҧ��a�ζ���������
	PBlockReginInforMe tempReginInforMe;
	
	for(long i=0;i<mRegions.GetSize();i++)
	{
		tempReginInforMe=new BlockReginInforMe;
		//�p�G
		//(1)��e�ʳ��ϰ쪺�̤px����>=�a�ζ��̤px����
		//(2)��e�ʳ��ϰ쪺�̤jx����<=�a�ζ��̤jx����
		//(3)��e�ʳ��ϰ쪺�̤py����>=�a�ζ��̤py����
		//(4)��e�ʳ��ϰ쪺�̤jy����<=�a�ζ��̤jy����
		///�|�ӱ����������,��ܸӫʳ��l�ϰ짹������e�a�ζ���
		if(mRegions.GetAt(i)->minx>=block_minx &&\
			mRegions.GetAt(i)->maxx<=block_maxx&&\
			mRegions.GetAt(i)->miny>=block_miny &&\
			mRegions.GetAt(i)->maxy<=block_maxy)
		{
			//�����ʳ��ϰ�ƾ��I
			tempReginInforMe->ReginPts.Copy(mRegions.GetAt(i)->ReginPts);
			tempReginInforMe->minx=mRegions.GetAt(i)->minx;
			tempReginInforMe->miny=mRegions.GetAt(i)->miny;
			tempReginInforMe->maxx=mRegions.GetAt(i)->maxx;
			tempReginInforMe->maxy=mRegions.GetAt(i)->maxy;
			mBlockReginInforMe[iNdex].Add(tempReginInforMe);//
		}
		else 
		{
			//�p�G
			//(1)��e�ʳ��ϰ쪺�̤px����>�a�ζ��̤jx����
			//(2)��e�ʳ��ϰ쪺�̤jx����<�a�ζ��̤px����
			//(3)��e�ʳ��ϰ쪺�̤py����>�a�ζ��̤jy����
			//(4)��e�ʳ��ϰ쪺�̤jy����<�a�ζ��̤py����
			//�|�ӱ��󺡨��䤤���@��,�O�ʳ��l�ϰ쥲�����a�ζ���
			if(mRegions.GetAt(i)->minx>block_maxx ||
				mRegions.GetAt(i)->maxx<block_minx||\
				mRegions.GetAt(i)->miny>block_maxy ||
				mRegions.GetAt(i)->maxy<=block_miny)
			{
			//	Sleep(0);
			}
			else
			{
				bInCur=bInPre=1;
				
				for(long j=0;j<mRegions.GetAt(i)->ReginPts.GetSize();j++)
				{
					double x=mRegions.GetAt(i)->ReginPts.GetAt(j)->x;
					double y=-mRegions.GetAt(i)->ReginPts.GetAt(j)->z;
					double z=mRegions.GetAt(i)->ReginPts.GetAt(j)->y;
				    //�p�G�I(x,y,z)���a�ζ���(�]�A�b�a�ζ���ɤW)
					if(x>=block_minx &&	x<=block_maxx&&\
						y>=block_miny && y<=block_maxy)
					{
						bInCur=1; //���ѫʳ��ϰ�����IPi(x,y,z)���a�ζ���
						
						if(j>0 && bInCur*bInPre==-1)
						{
							//�p��ʳ��l�ϰ�P��e�a�ζ��|����ɽu�����I����,�D�o�����I����
							//�]�N�@���Ӧa�ζ����ƾ��I�ѻP�a��ø�s.
							GetBlockEdgeJd(block_minx,block_miny,block_maxx,block_maxy,i,j,&Mnus,edgePts);
							for(int k=0;k<Mnus;k++)
							{
								pt=new Cordinate;
								pt->x=edgePts[k].x;pt->y=edgePts[k].y;pt->z=edgePts[k].z;
								tempReginInforMe->ReginPts.Add(pt);//�O���ƾ��I
							}
						}
						
						pt=new Cordinate;
						pt->x=x;pt->y=z;pt->z=-y;//�����ܴ�
						tempReginInforMe->ReginPts.Add(pt);//�O���ƾ��I
						
					}
					else 
					{
						bInCur=-1;//���ѫʳ��ϰ�����IPi(x,y,z)���a�ζ��~ 
						if(j>0 && bInCur*bInPre==-1)
						{
							//�p��ʳ��l�ϰ�P��e�a�ζ��|����ɽu�����I����,�D�o�����I����
							//�]�N�@���Ӧa�ζ����ƾ��I�ѻP�a��ø�s.
							GetBlockEdgeJd(block_minx,block_miny,block_maxx,block_maxy,i,j,&Mnus,edgePts);
							for(int k=0;k<Mnus;k++) //�N���a�ζ�������������I�s�x
							{
								pt=new Cordinate;
								pt->x=edgePts[k].x;pt->y=edgePts[k].y;pt->z=edgePts[k].z;
								tempReginInforMe->ReginPts.Add(pt);//�O���ƾ��I
							}
						}
						
					}
					bInPre=bInCur;
				}

				//�p��̤p�̤jx,y����
				minx=miny=999999999;
				maxx=maxy=-999999999;
				for(long k=0;k<tempReginInforMe->ReginPts.GetSize();k++)
				{
					if(minx>tempReginInforMe->ReginPts.GetAt(k)->x)
						minx=tempReginInforMe->ReginPts.GetAt(k)->x;
					if(miny>-tempReginInforMe->ReginPts.GetAt(k)->z)
						miny=-tempReginInforMe->ReginPts.GetAt(k)->z;
					if(maxx<tempReginInforMe->ReginPts.GetAt(k)->x)
						maxx=tempReginInforMe->ReginPts.GetAt(k)->x;
					if(maxy<-tempReginInforMe->ReginPts.GetAt(k)->z)
						maxy=-tempReginInforMe->ReginPts.GetAt(k)->z;
					
				}
				
				tempReginInforMe->minx=minx;
				tempReginInforMe->miny=miny;
				tempReginInforMe->maxx=maxx;
				tempReginInforMe->maxy=maxy;
				mBlockReginInforMe[iNdex].Add(tempReginInforMe);//�O���ʳ��ϰ�H��
			}
		}
	}
}

//�g�J�a�ζ������мƾ�
void CT3DSystemView::WriteBlockLsPts(long Blcokrow, long Blcokcol)
{
	PBlockLSPts tempBlockLSPts=new BlockLSPts;
	
	tempBlockLSPts->ReginPts.RemoveAll();
	
	PCordinate pt=new Cordinate;
	double x,y,z;
	long INX,mTerrainBlockID;
	mTerrainBlockID=(Blcokrow-1)*theApp.m_BlockCols+Blcokcol-1;//�a�ζ���ID��

    //�ھڦa�ζ��������j�p,�̦��N�Ҧ��a�μƾ��I�g�J�a�ζ��ʳ��ϰ�Ʋդ�
	for(int i=0;i<theApp.m_Dem_BlockSize;i++)
	{
		for (int j=0;j<theApp.m_Dem_BlockSize;j++)
		{
			
			x=(Blcokcol-1)*theApp.m_Dem_BlockWidth+j*theApp.m_Cell_xwidth;//�ഫ�᪺X����
			y=(Blcokrow-1)*theApp.m_Dem_BlockWidth+i*theApp.m_Cell_ywidth;//�ഫ�᪺Y����
			
			INX=i*theApp.m_Dem_BlockSize+j;
			z=m_pHeight_My[mTerrainBlockID][INX];//�D�o���������{��
			
            pt=new Cordinate;
			pt->x =x;
			pt->y=z;
			pt->z =-y;
			tempBlockLSPts->ReginPts.Add(pt);//�[�J�ƾ��I
		}
	}
	
	//�[�J�ʳ��ϰ���a�ζ��λP�a�ζ���ɬۥ檺�ƾ��I
	long iNdex=(Blcokrow-1)*theApp.m_BlockCols+(Blcokcol-1);
	for(int k=0;k<mBlockReginInforMe[iNdex].GetSize();k++)
	{
		tempBlockLSPts->ReginPts.Append(mBlockReginInforMe[iNdex].GetAt(k)->ReginPts);
	}
	
	tempBlockLSPts->mDemBlockRow=Blcokrow; //��e�a�ζ��������渹
	tempBlockLSPts->mDemBlockCol=Blcokcol; //��e�a�ζ��������f��
	m_BlockLSPts.Add(tempBlockLSPts);//��e�a�ζ����Ҧ��ƾ��I
	
}

//�p��ʳ��l�ϰ�P��e�a�ζ��|����ɽu�����I����,�D�o�����I����
//�]�N�@���Ӧa�ζ����ƾ��I�ѻP�a��ø�s.
void CT3DSystemView::GetBlockEdgeJd(double block_minx, double block_miny, double block_maxx, double block_maxy, long RegionsIndex, long ReginPtsIndex, int *jdNus, Point edgePts[])
{
	Point p1,p2,q1,q2,crossPoint;
	
	int m=0; //��l���I�Ƭ�0
	bool bCross=false; //��l���ۥ�
	
	//��e�ʳ��ϰ���{������I
	q1.x=mRegions.GetAt(RegionsIndex)->ReginPts.GetAt(ReginPtsIndex)->x;
	q1.y=-mRegions.GetAt(RegionsIndex)->ReginPts.GetAt(ReginPtsIndex)->z;
	q2.x=mRegions.GetAt(RegionsIndex)->ReginPts.GetAt(ReginPtsIndex-1)->x;
	q2.y=-mRegions.GetAt(RegionsIndex)->ReginPts.GetAt(ReginPtsIndex-1)->z;
	
	
	//�a�ζ��W��ɽu
	p1.x =block_minx;p1.y=block_maxy;
	p2.x =block_maxx;p2.y=block_maxy;
	
	//�p��Op1p2���u�Pq1q2���u�O�_�ۥ�
	crossPoint =mCalF.GetCrossPoint(p1,p2,q1,q2,&bCross);
	if(bCross==true)  //�p�G�ۥ�,����P�a�ζ��W��ɽu�ۥ�
	{
		edgePts[m].x=crossPoint.x; //�O�����Ix����
		edgePts[m].z=-crossPoint.y;//�O�����Iz����
		//�qDEM�������X���{,�D�o���Iy����
		edgePts[m].y=m_demInsert.GetHeightValue(edgePts[m].x+theApp.m_DemLeftDown_x,-edgePts[m].z+theApp.m_DemLeftDown_y,2);
		m++; //���I�ƥ[1
	}
	
	//�a�ζ�����ɽu
	p1.x =block_minx;p1.y=block_maxy;
	p2.x =block_minx;p2.y=block_miny;
	
	//�p��Op1p2���u�Pq1q2���u�O�_�ۥ�
	crossPoint =mCalF.GetCrossPoint(p1,p2,q1,q2,&bCross);
	if(bCross==true) //�p�G�ۥ�,����P�a�ζ�����ɽu�ۥ�
	{
		edgePts[m].x=crossPoint.x;//�O�����Ix����
		edgePts[m].z=-crossPoint.y;//�O�����Iz����
		//�qDEM�������X���{,�D�o���Iy����
		edgePts[m].y=m_demInsert.GetHeightValue(edgePts[m].x+theApp.m_DemLeftDown_x,-edgePts[m].z+theApp.m_DemLeftDown_y,2);
		m++;//���I�ƥ[1
	}
	
	//�a�ζ��U��ɽu
	p1.x =block_minx;p1.y=block_miny;
	p2.x =block_maxx;p2.y=block_miny;
	
	//�p��Op1p2���u�Pq1q2���u�O�_�ۥ�
	crossPoint =mCalF.GetCrossPoint(p1,p2,q1,q2,&bCross);
	if(bCross==true) //�p�G�ۥ�,����P�a�ζ��U��ɽu�ۥ�
	{
		edgePts[m].x=crossPoint.x;//�O�����Ix����
		edgePts[m].z=-crossPoint.y;//�O�����Iz����
		//�qDEM�������X���{,�D�o���Iy����
		edgePts[m].y=m_demInsert.GetHeightValue(edgePts[m].x+theApp.m_DemLeftDown_x,-edgePts[m].z+theApp.m_DemLeftDown_y,2);
		m++;//���I�ƥ[1
	}
	
	//�a�ζ��k��ɽu
	p1.x =block_maxx;p1.y=block_maxy;
	p2.x =block_maxx;p2.y=block_miny;

	//�p��Op1p2���u�Pq1q2���u�O�_�ۥ�
	crossPoint =mCalF.GetCrossPoint(p1,p2,q1,q2,&bCross);
	if(bCross==true)//�p�G�ۥ�,����P�a�ζ��k��ɽu�ۥ�
	{
		edgePts[m].x=crossPoint.x;
		edgePts[m].z=-crossPoint.y;
		//�qDEM�������X���{,�D�o���Iy����
		edgePts[m].y=m_demInsert.GetHeightValue(edgePts[m].x+theApp.m_DemLeftDown_x,-edgePts[m].z+theApp.m_DemLeftDown_y,2);
		m++;//���I�ƥ[1
	}
	
	*jdNus=m; //��^�D�o���I��		
}



//�ھڦa���I��x,y �H���p��Ӧa���I���ݪ��b�ζ�ID��
int CT3DSystemView::GetBlockID(double x, double y)
{
	//	theApp.m_BlockCols//DEM���`�C��
	//	theApp.m_BlockRows;//DEM���`���
	//	theApp.m_Dem_BlockWidth//�C��DEM���e��
	//	���ݩ��,�C�p���k
	
	int mrow,mcol;
	if((y/theApp.m_Dem_BlockWidth)==(int)(y/theApp.m_Dem_BlockWidth))
		mrow=y/theApp.m_Dem_BlockWidth;
	else
		mrow=(int)(y/theApp.m_Dem_BlockWidth)+1;
	if(mrow<=0) //�p�G�渹<=0,�渹=1
		mrow=1;
	
	if((x/theApp.m_Dem_BlockWidth)==(int)(x/theApp.m_Dem_BlockWidth))
		mcol=x/theApp.m_Dem_BlockWidth;
	else
		mcol=(int)(x/theApp.m_Dem_BlockWidth)+1;
	if(mcol<=0)//�p�G�C��<=0,�C��=1
		mcol=1;
	int ID=(mrow-1)*theApp.m_BlockCols+mcol;
	return ID; //��^ID��
}

//�]�m������|
void CT3DSystemView::OnPathManuinput() 
{
	m_ShowFlyPath=TRUE;  //���ѬO�_��ܭ�����|
	m_QueryType=SELECTFLYPATH;//�i�歸����|���
	m_FlayPath.RemoveAll();//�s�x�i�歸����|���мƲղM��
}

//ø�s������|
void CT3DSystemView::DrawFlyPath()
{
	//�p�G��ܭ�����|�åB������|�����I��>1,�~ø�s������|
	if(m_ShowFlyPath==TRUE  && m_FlayPath.GetSize()>1)//�i�歸����|���
	{
		glPushMatrix(); //���J�x�}���
		glDisable(GL_TEXTURE_2D);//�������z(�Y������|���ĥί��z)
		glLineWidth(3.0);//�]�m������|�u�e
		glColor3f(0,1,1); //�]�m������|�C��
		if(m_ViewType==GIS_VIEW_ORTHO)	//ø�s���g��v�Ҧ��U��������|
		{
			glBegin(GL_LINE_STRIP); //�H��u�覡ø�s������|
			for(int i=0;i<m_FlayPath.GetSize();i++)
				glVertex2f(GetOrthoX(m_FlayPath.GetAt(i)->x),GetOrthoY(-m_FlayPath.GetAt(i)->z));
			glEnd();
			
			//�b������|�C�ӧ����I�Bø�s�I��[�H���ѨC�ӧ����I
			for(i=0;i<m_FlayPath.GetSize();i++)
			{
				glColor3f(0,0.5,0.5); //�I���C��
				glPointSize(4.0); //�I���j�p
				glBegin(GL_POINTS);
					glVertex2f(GetOrthoX(m_FlayPath.GetAt(i)->x),GetOrthoY(-m_FlayPath.GetAt(i)->z));
				glEnd();
			}
			glPointSize(0); //��_�I���q�{�j�p
			
		}
		else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) //ø�s�z����v�Ҧ��U��������|
		{
			glBegin(GL_LINE_STRIP);
			for(int i=0;i<m_FlayPath.GetSize();i++)
				glVertex3f(m_FlayPath.GetAt(i)->x, m_FlayPath.GetAt(i)->y, m_FlayPath.GetAt(i)->z);
			glEnd();
			
		}
		glEnable(GL_TEXTURE_2D); //�}�ү��z
		glLineWidth(1.0); //��_�u�e
		glColor3f(1,1,1); //��_�C��
		glPopMatrix(); //�u�X�x�}���
	}
}

//���|���д���
void CT3DSystemView::OnFlppathInterpolation() 
{
	float m_InsertDdis=10; //���ȶ��Z 
	
	double x1,y1,z1,x2,y2,z2;
	PCordinate ppt ;  
	
	m_FlayPathTempPts.RemoveAll(); //�{�ɦs�x������|
	for(int i=0;i<m_FlayPath.GetSize()-1;i++)
	{
		x1=m_FlayPath.GetAt(i)->x; //���������|��e�I��x����
		y1=m_FlayPath.GetAt(i)->y; //���������|��e�I��y����
		z1=m_FlayPath.GetAt(i)->z; //���������|��e�I��z����
		
		x2=m_FlayPath.GetAt(i+1)->x; //���������|�U�@�I��x����
		y2=m_FlayPath.GetAt(i+1)->y;//���������|�U�@�I��y����
		z2=m_FlayPath.GetAt(i+1)->z;//���������|�U�@�I��z����
		
		if(i==0) //�p�G�O������|���_�l�I,�h�O��
		{
			ppt = new Cordinate;
			ppt->x=x1;
			ppt->y=y1;
			ppt->z=z1;
			m_FlayPathTempPts.Add(ppt);
		}
		
		//�p�⭸����|��e�I�P�U�@�I���Z��
		double L=myDesingScheme.GetDistenceXYZ(x1,y1,z1,x2,y2,z2);
		int M=L/m_InsertDdis; //�p���������������I��
		for(int j=1;j<=M;j++)
		{
			//�u�ʤ����p��X�s�������I���T������
			ppt = new Cordinate;
			ppt->x=x1+j*m_InsertDdis/L*(x2-x1);
			ppt->z=z1+j*m_InsertDdis/L*(z2-z1);
			ppt->y=m_demInsert.GetHeightValue(ppt->x+theApp.m_DemLeftDown_x,-ppt->z+theApp.m_DemLeftDown_y,2);
			m_FlayPathTempPts.Add(ppt); //�O�������I����
			
		}
		
		ppt = new Cordinate;
		ppt->x=x2;
		ppt->y=y2;
		ppt->z=z2;
		m_FlayPathTempPts.Add(ppt); //�N������|�U�@�I�����Ф]�O���b��
		
	}
	
	m_FlayPath.RemoveAll(); //������|�ƲղM��
	for(i=0;i<m_FlayPathTempPts.GetSize();i++)
	{
		ppt = new Cordinate;
		ppt->x=m_FlayPathTempPts.GetAt(i)->x;
		ppt->y=m_FlayPathTempPts.GetAt(i)->y;
		ppt->z=m_FlayPathTempPts.GetAt(i)->z;
		m_FlayPath.Add(ppt); //���s��R������|�Ʋ�
		
	}
	OnDraw(GetDC()); //��s�T������
	MessageBox("���|���д��ȧ���!","���|���д���",MB_ICONINFORMATION);	
}

//�O�s������|
void CT3DSystemView::OnFlypathSave() 
{
	CString 	NeededFile;
	char 		FileFilter[] = "������|(*.pth)|*.pth||";

	//�]�m����ܮ��ݩ�
	DWORD 		FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog FileDialogBoxFile(FALSE, NULL, 0, FileDialogFlag, FileFilter, this);
	FileDialogBoxFile.m_ofn.lpstrTitle = "�O�s������|���";
	char		FileName[200];
	
	CString tt[3];
	if( FileDialogBoxFile.DoModal() == IDOK ) //�p�G��ܮئ��G���}
	{	
		NeededFile = FileDialogBoxFile.GetPathName(); //�o����W
		sprintf(FileName, "%s", NeededFile);
		if(strcmp(FileDialogBoxFile.GetFileExt(),"pth")!=0) 
			strcat(FileName,".pth"); //�K�[������|����X�i�W
		
		if(FlyPathSave(FileName)) //�p�G������|�O�s���\
			MessageBox("���|�I�O�s����","�O�s������|",MB_ICONWARNING);
		
	}			
}

//������|�O�s
int CT3DSystemView::FlyPathSave(char *pathfile)
{
	FILE	*fpw;
	char	message[200];
	
	if((fpw = fopen(pathfile, "w")) == NULL)//�p�G�g�J��󥢱�
  	{ 
		sprintf(message, "��� %s �ЫصL��", pathfile);
		MessageBox(message,"�O�s������|���Ш���",MB_ICONWARNING);
		return 0; //��^����
  	}
	
	
	fprintf(fpw, "%d\n", m_FlayPath.GetSize());//�g�J������|�����I�`��
	for(int i=0;i<m_FlayPath.GetSize();i++)
	{
		//�V���fpw��g�J������|�����I���T������
		fprintf(fpw, "%lf,%lf,%lf\n",m_FlayPath.GetAt(i)->x, m_FlayPath.GetAt(i)->y, m_FlayPath.GetAt(i)->z);
		
	}
	
	fclose(fpw); //�������
	
	return 1;  //��^���\
}

//���}������|
void CT3DSystemView::OnFlyOpenpath() 
{
	CString 	NeededFile;
	char 		FileFilter[] = "������|(*.pth)|*.pth||";
	//�]�m����ܮ��ݩ�
	DWORD 		FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog FileDialogBoxFile(TRUE, NULL, 0, FileDialogFlag, FileFilter, this);
	FileDialogBoxFile.m_ofn.lpstrTitle = "���}������|���";
	char		FileName[200];
	
	CString tt[3];
	if( FileDialogBoxFile.DoModal() == IDOK )//�p�G��ܮئ��G���}
	{	
		NeededFile = FileDialogBoxFile.GetPathName();//�o����W
		sprintf(FileName, "%s", NeededFile);
		if(strcmp(FileDialogBoxFile.GetFileExt(),"pth")!=0) 
			strcat(FileName,".pth");//�K�[������|����X�i�W
		
		if(FlyPathRead(FileName)) //Ū��������|���ƾڰʺA�Ʋդ�
			MessageBox("���}���|�I����","����",MB_ICONWARNING);
		if(m_FlayPath.GetSize()>1) //�p�G������|�ƾڧ����I��>1
		{
			m_ShowFlyPath=TRUE; //��ܭ�����|
			m_PathFlag=TRUE; //���ѭ�����|���}���\
		}
		else
			m_PathFlag=FALSE;//���ѭ�����|���}����
	}			
}

//Ū��������|���ƾڰʺA�Ʋդ�
int CT3DSystemView::FlyPathRead(char *pathfile)
{
	CString tt,m_strszLine;
	PCordinate ppt = new Cordinate;  
	
	m_FlayPath.RemoveAll(); //������|�ƲղM��
	
	CStdioFile m_inFile;	
			
	if(m_inFile.Open (pathfile,CFile::modeRead)==FALSE) //���}���
	{
		return 0; //��^���Ѽлx
	}
	m_inFile.ReadString(m_strszLine); //Ū��������|�����I�`��
	while( m_inFile.ReadString(m_strszLine))
	{
		ppt = new Cordinate;
		
		m_strszLine.TrimLeft(" ");
		m_strszLine.TrimRight("	");
		int nPos=m_strszLine.Find(",");
		tt=m_strszLine.Left(nPos);
		ppt->x=atof(tt);
		m_strszLine=m_strszLine.Right(m_strszLine.GetLength()-nPos-1);
		nPos=m_strszLine.Find(",");
		tt=m_strszLine.Left(nPos);
		ppt->y=atof(tt); 
		m_strszLine=m_strszLine.Right(m_strszLine.GetLength()-nPos-1);
		ppt->z=atof(m_strszLine);
		m_FlayPath.Add(ppt); //�O��������|�����I
		
	}
	m_inFile.Close(); //�������
	
	return 1; //��^���\�лx
}

//��ܩ�����������|
void CT3DSystemView::OnFlyOnoffpath() 
{
	if(m_ShowFlyPath==TRUE) //�p�G��e�O��ܭ�����|
		m_ShowFlyPath=FALSE; //���ѳ]�m��FALSE
	else
		m_ShowFlyPath=TRUE; //�Ϥ�,�]�m��TRUE	
	OnDraw(GetDC());  //��s�T������ 
	
}

//�ھ�m_ShowFlyPath�ȭק���奻
void CT3DSystemView::OnUpdateFlyOnoffpath(CCmdUI* pCmdUI) 
{
	if(m_ShowFlyPath==TRUE) //�p�G��e�O��ܭ�����|
		pCmdUI->SetText("����������|"); //�N���W�ٳ]�m��"����������|"
	else   //�p�G��e�O����������|
		pCmdUI->SetText("��ܭ�����|");//�N���W�ٳ]�m��"��ܭ�����|"
}

//���T�w���׺��C
void CT3DSystemView::OnFlyStaticheight() 
{
	if(m_FlayPath.GetSize()<=0) //�p�G������|�����I�ƶq<=0�A�Y������|����
	{
		MessageBox("�S����J���|���","�����s��",MB_ICONWARNING);
		return;
	}
	
	m_R=4000;
	m_r=3000;
	
	m_FlyHeightType = GIS_FLY_STATICHEIGHT; //�]�m���C�������T�w���׺��C
	m_StaticHeight = (m_maxHeight+m_minHeight)/4.0;  //���T�w���׭�=�a�γ̤j�M�̤p���ת�1/4
	m_flypathPtIndex=0; //������|���Я���=0
	
	SetFLyTimer();	//�]�m�T�����C�p�ɾ�
}

void CT3DSystemView::OnUpdateFlyStaticheight(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	m_PathFlag == TRUE); //�ھڬO�_�㦳���ĭ�����|�ȳ]�m��檬�A
	if (m_FlyHeightType==GIS_FLY_STATICHEIGHT) //�p�G��e�O"�u�T�w���׺��C"�覡
        pCmdUI->SetCheck(TRUE); //���e�]�m�襤�лx"��"
    else
		pCmdUI->SetCheck(FALSE); //�_�h���]�m		
}

//�]�m����p�ɾ�
void CT3DSystemView::SetFLyTimer()
{
	SetTimer(1,m_flyspeed,0); //m_flyspeed:����p�ɾ��ɶ����j,
	
}

//�p�ɾ�
void CT3DSystemView::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 1:  //�T�����C
		if(m_flypathPtIndex<=m_FlayPath.GetSize()-2) //�p�G��e������|�����I����<=���|�����I�`��-1
		{
			//�ھں��C���|���{�����I�p��۾��U�Ѽ�
			GetCameraCorrdinate(
				m_FlayPath.GetAt(m_flypathPtIndex)->x,\
				m_FlayPath.GetAt(m_flypathPtIndex)->y,\
				m_FlayPath.GetAt(m_flypathPtIndex)->z,\
				m_FlayPath.GetAt(m_flypathPtIndex+1)->x,\
				m_FlayPath.GetAt(m_flypathPtIndex+1)->y,\
				m_FlayPath.GetAt(m_flypathPtIndex+1)->z
				);
			if(m_ifZoomonRoad==TRUE)//�p�G�u�u����׺��C
			{
				//�p���e���{
				CString tt,tt2;
				tt=myDesingScheme.GetLC(m_FlayPath.GetAt(m_flypathPtIndex)->Lc);
				tt2="��e���{="+tt;
				CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
				pMainFrame->Set_BarText(5,tt2,0); 
				CalZoomSpeed(m_FlayPath.GetAt(m_flypathPtIndex)->Lc);
			}
			else
			{
				double L=myDesingScheme.GetDistenceXYZ(
					m_FlayPath.GetAt(m_flypathPtIndex)->x,\
					m_FlayPath.GetAt(m_flypathPtIndex)->y,\
					m_FlayPath.GetAt(m_flypathPtIndex)->z,\
					m_FlayPath.GetAt(m_flypathPtIndex+1)->x,\
					m_FlayPath.GetAt(m_flypathPtIndex+1)->y,\
					m_FlayPath.GetAt(m_flypathPtIndex+1)->z
					);
					m_CurZooomLC+=L;
					CalZoomSpeed(m_CurZooomLC);
			}
			OnDraw(GetDC()); //��s�T������
			m_flypathPtIndex++; //������|��e���Я��޸�+1
		}

		else
		{
			m_flypathPtIndex=0; //��F�����,�N������|��e���Я��޸����m��0,�Y�q������|�_�l�I�}�l���C
		}
		break;
	case 2: //���s�Ϲ��ǦC
		RecordPictures();
		break;
	case 3:
	//	m_snows.DrawSnow ();
		break;
	}
	
	CView::OnTimer(nIDEvent);
}

//���۹ﰪ�׺��C�覡
void CT3DSystemView::OnFlyRoutineheight() 
{
	if(m_FlayPath.GetSize()<=0)//�p�G������|�����I�ƶq<=0�A�Y������|����
	{
		MessageBox("�S����J���|���","�����s��",MB_ICONWARNING);
		return;
	}
	
	m_FlyHeightType = GIS_FLY_PATHHEIGHT;//�]�m���C�������۹ﰪ�׺��C
	m_R=3000;
	m_r=2000;
	
	if(m_ifZoomonRoad==TRUE) 
		m_StaticHeight =5;
	else
		m_StaticHeight =80; //�]�m�۹ﰪ�t��
	
	m_flypathPtIndex=0;//������|���Ъ�l����=0
	SetFLyTimer();	//�]�m�T�����C�p�ɾ�
}

//�]�m���O�_�]�m�襤����"��"
void CT3DSystemView::OnUpdateFlyRoutineheight(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	m_PathFlag == TRUE); //�ھڬO�_�㦳���ĭ�����|�ȳ]�m��檬�A
	if (m_FlyHeightType==GIS_FLY_PATHHEIGHT) //�p�G��e�O"�u�۹ﰪ�׺��C"�覡
        pCmdUI->SetCheck(TRUE); //���e�]�m�襤�лx"��"
    else
		pCmdUI->SetCheck(FALSE); //�_�h���]�m	
}

//�}�l/�Ȱ����C
void CT3DSystemView::OnFlyPlaypause() 
{
	if(m_FlyPause==FALSE) //�p�G���O�Ȱ����C,�Y�B�󺩹C���A
	{
		m_FlyPause=TRUE; //�]�m�Ȱ�����m_FlyPause=TRUE
		KillTimer(1); //�P���w�ɾ�1
	}
	else //�p�G�B�󺩹C���A
	{
		m_FlyPause=FALSE; //�]�m�Ȱ�����m_FlyPause=FALSE
		SetFLyTimer();//�]�m����ɶ���,�~�򺩹C
	}
}

//�ھ�m_FlyPause�ȳ]�m���ID_FLY_PLAYPAUSE�奻
void CT3DSystemView::OnUpdateFlyPlaypause(CCmdUI* pCmdUI) 
{
	if(m_FlyPause==TRUE) //�p�G�B�󺩹C���A
		pCmdUI->SetText("�}�l���C"); //�]�m���ID_FLY_PLAYPAUSE�奻
	else  //�p�G���O�Ȱ����C,�Y�B�󺩹C���A
		pCmdUI->SetText("�Ȱ����C");//�]�m���ID_FLY_PLAYPAUSE�奻
	
}

//����C
void CT3DSystemView::OnFlyStop() 
{
	KillTimer(1); //�P���w�ɾ�1
	m_flypathPtIndex=0;//������|���Я���=0
	m_FlyPause=FALSE; //�Ȱ����Ѭ�FALSE
	m_ifZoomonRoad=FALSE; //���Ѫu�u����׽u���C��FALSE
	m_far=10000;	//��_gluPerspective()��Ʃw�q���I�Y�骺���ŵ��������Z��
}

//��B�e�i
void CT3DSystemView::OnFlyOnestep() 
{
	//�p�G������|���Я���>=0�åB<������|�����`��-1,�ӱ����ܪ��O
	//�u�n������|���Я��ިS���쭸����|��,�N�i�H�����B�e�i
	if(m_flypathPtIndex>=0 && m_flypathPtIndex<m_FlayPath.GetSize()-1)
	{
		
		KillTimer(1);	//�P���w�ɾ�1		
		m_FlyPause=TRUE;//�Ȱ����Ѭ�TRUE
		//�ھں��C���|���{�����I�p��۾��U�Ѽ�
		GetCameraCorrdinate(
			m_FlayPath.GetAt(m_flypathPtIndex)->x,\
			m_FlayPath.GetAt(m_flypathPtIndex)->y,\
			m_FlayPath.GetAt(m_flypathPtIndex)->z,\
			m_FlayPath.GetAt(m_flypathPtIndex+1)->x,\
			m_FlayPath.GetAt(m_flypathPtIndex+1)->y,\
			m_FlayPath.GetAt(m_flypathPtIndex+1)->z
			);
		
		OnDraw(GetDC()); //��s�T������ 
		m_flypathPtIndex++; //��e����|���Я���+1
	}	
}

//��������X�j
void CT3DSystemView::OnFlyViewEnlarge() 
{
	m_ViewWideNarrow += 5.0; //m_ViewWideNarrow�ȼW�[
	OnDraw (GetDC()); //��s�T������
}

//���������p
void CT3DSystemView::OnFlyViewSmall() 
{
	m_ViewWideNarrow -= 5.0;//m_ViewWideNarrow�ȴ�p
	OnDraw (GetDC());//��s�T������
}

//���氪�׼W�[
void CT3DSystemView::OnFlyHeightUp() 
{
	m_StaticHeight += 8;// ���׭ȼW�[(�B��=8,�i���N�]�w)
	OnDraw (GetDC());//��s�T������	
}

//���氪�׭��C
void CT3DSystemView::OnFlyHeightDown() 
{
	m_StaticHeight -= 8;// ���׭ȼW�[(�B��=8,�i���N�]�w)
	OnDraw (GetDC());//��s�T������	
	
}

//��������W��(����)
void CT3DSystemView::OnFlyViewUp() 
{
	m_ViewUpDown += 1.0;
	OnDraw (GetDC());//��s�T������	
}

//��������U��(����)
void CT3DSystemView::OnFlyViewDown() 
{
	m_ViewUpDown -= 1.0;
	OnDraw (GetDC());//��s�T������	
}

//�[�t
void CT3DSystemView::OnFlySpeedUp() 
{
	m_flyspeed-=2; //����ɪ��p�ɾ��ɶ����j��� 
	if(m_flyspeed<=1) //�p�G�p�ɾ��ɶ����j<=1,�h��
		m_flyspeed=1;
	SetFLyTimer();	//�]�m����p�ɾ�
}

//��t
void CT3DSystemView::OnFlySpeedDown() 
{
	m_flyspeed+=2;//����ɪ��p�ɾ��ɶ����j�W�[ 
	SetFLyTimer();//�]�m����p�ɾ�
}

//�T�����C�վ�������U
void CT3DSystemView::DisplayHelp()
{
	char str[20][50],strdis[2000];
	
	strdis[0]='\0';
	
	strcpy(str[0]," �V����   ���e��V����\n");
	strcpy(str[1]," �V����   �����V����\n");
	strcpy(str[2]," �V����   ������V����\n");
	strcpy(str[3]," �V����   ���k��V����\n");
	strcpy(str[4],"  J ��    ����[�t\n");
	strcpy(str[5],"  M ��    �����t\n");
	strcpy(str[6],"  F ��    ��������W�j\n");
	strcpy(str[7],"  V ��    ���������p\n");
	strcpy(str[8],"  G ��     �ɰ����氪��\n");
	strcpy(str[9],"  B ��     ���C���氪��\n");
	strcpy(str[10],"  H ��    �����[��W��\n");
	strcpy(str[11],"  N ��    �����[��U��\n");
	strcpy(str[12],"  Z ��    �u��׽u���C\n");
	strcpy(str[13],"  P ��    �}�l/�Ȱ����C\n");
	strcpy(str[14],"  S ��    ����C");
	
	for(int i=0;i<15; i++)
		strcat(strdis,str[i]);
	
	MessageBox(strdis,"�T�����C���仡��",MB_OK);
}

//���[�ҫ�
void CT3DSystemView::OnMenuModleqd() 
{
	CModelMangerQD dlg;
	if(dlg.DoModal()==IDOK) //�p�G��ܮإHIDOK�覡����
	{
		if(!dlg.m_3DSfilename_QD.IsEmpty()) //�p�G���[�ҫ��W�٤�����
		{
			m_3DSfilename_QD=dlg.m_3DSfilename_QD; //�o����[�ҫ��W��
			BuildQDModelList(); //���s�c�ؾ��[�ҫ���ܦC��
			
		}
	}	
}

//��X�u���T���ҫ���CAD
void CT3DSystemView::OnMenuOuptcad3dlinemodel() 
{
	CString tt,DxfFilename;
	
	CDXF mdxf;
	CStdioFile *Dxffile=new CStdioFile;
	CFileDialog fielDlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"AutoCAD Dxf(*.dxf)|*dxf||",NULL);
	
	fielDlg.m_ofn.lpstrTitle = "��X�u���T���ҫ���CAD";   
	
	if(fielDlg.DoModal()==IDCANCEL) //���}��ܮ�
		return;
	
	DxfFilename=fielDlg.GetPathName(); //�o��DXF���W
	if(DxfFilename.IsEmpty()) //�p�GDXF���W���šA��^
		return;

	//�T�ODXF���H".dxf"�X�i�W����
	tt=DxfFilename.Right(4);
	tt.MakeUpper();
	if(strcmp(tt,".DXF")!=0)
		DxfFilename+=".dxf";
	
	//�p�G�s�Ыت�DXF���w�g���}�A���X���H��	 
	if(Dxffile->Open (DxfFilename,CFile::modeCreate | CFile::modeWrite)==FALSE)
	{
		this->MessageBox("���"+DxfFilename+"�w�Q�䥦�{�ǥ��}�Φ���,�������A��!","��X�u���T���ҫ���CAD",MB_ICONINFORMATION);
		return;
	}

	mdxf.DxfHeader(Dxffile); //�g�JDXF����Y
	mdxf.DxfLineType(Dxffile);//�g�JDXF�u���w�q
	mdxf.DxfBeginDrawEnties(Dxffile); //�}�l�g�J�ϧι���

	//�g�J�u�����߽u����
	for (long i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		
		mdxf.DxfDraw_Line(Dxffile,"�u�����߽u",1,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x,\
			-myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->y,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->x,\
			-myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->z,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->y);
	}	

	//�g�J�ⰼ�y�D�����s�u����
	for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ�y�D�����s�u",6,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ�y�D�����s�u",6,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ�y�D�����s�u",6,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ�y�D�����s�u",6,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1);
	}		

	//�g�J�ⰼ��Ӧ���}�����s�u����
	for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		
	
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��Ӧ���}�����s�u",3,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��Ӧ���}�����s�u",3,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��Ӧ���}�����s�u",3,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��Ӧ���}�����s�u",3,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1);
		
		
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��Ӧ���}�����s�u",3,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��Ӧ���}�����s�u",3,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��Ӧ���}�����s�u",3,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��Ӧ���}�����s�u",3,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2);
		

	}
	
	//�g�J�ⰼ��}�ܸ��Ӷ����s�u����
	for (i=0;i<myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()-1;i++)
	{
	
		
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��}�ܸ��Ӷ����s�u",4,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��}�ܸ��Ӷ����s�u",4,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��}�ܸ��Ӷ����s�u",4,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��}�ܸ��Ӷ����s�u",4,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1);
		
		
		
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��}�ܸ��Ӷ����s�u",4,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��}�ܸ��Ӷ����s�u",4,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��}�ܸ��Ӷ����s�u",4,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2);
		mdxf.DxfDraw_Line(Dxffile,"�ⰼ��}�ܸ��Ӷ����s�u",4,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2);
		
	}		
	
	//�g�J������Y����(�G�D�M���٤��g�J)
	for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		tt=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
		if(tt!="�G�D�_�I" && tt!="�G�D�����I" &&tt!="�G�D���I" &&tt!="���ٰ_�I"  &&tt!="���٤����I" &&tt!="���ٲ��I")
		{	
			DrawBP_CAD(i,1,Dxffile);//������Y
		
		}
	}
	
	//�g�J�k����Y�M�ⰼ��������(�G�D�M���٤��g�J)
	for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		tt=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
		if(tt!="�G�D�_�I" && tt!="�G�D�����I" &&tt!="�G�D���I" &&tt!="���ٰ_�I"  &&tt!="���٤����I" &&tt!="���ٲ��I")
		{
			DrawBP_CAD(i,2,Dxffile); //�k����Y
			DrawSuiGou_CAD(i,2,Dxffile);//�ⰼ����
		
		}
	}
	
	mdxf.DxfSectionEnd(Dxffile); //�g�J��󵲧��лx
	tt.Format("dxf���%s�w��X����!",DxfFilename);
	MessageBox(tt,"��X�ϧΨ�AuotCAD",MB_ICONINFORMATION); //���XDXF����X�����H��
		
}

//�g�J�ⰼ��Y������DXF���(�G�D�M���٤��g�J)
void CT3DSystemView::DrawBP_CAD(long index, int BPside, CStdioFile *Dxffile)
{
	long i=index;

	int j;


	if(BPside==1) 
	{
		
		int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_L;
		int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_L;
	
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				
				
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].style)
				{

					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y);
				}
				else 
				{
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y);
				}
			
	
				if(j>0) 
					{
						glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
						mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y);
						mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y);
						mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
						mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
						
				}
	
			}
			
		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].style)
				{
 
 					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y);
					
				}
				else
				{
 
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y);

 
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y);
					
					
				}
			

				if(j>0) 
				{
 
 					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					
				}

			}
			
		}
		
	}
	else if(BPside==2) 
	{
		
		int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_R;
		int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_R;
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].style)
				{
 
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x)
					{
					}
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y);
					
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y);					
				}
				else
				{
 
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y);
					
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y);
					
				}
				
				if(j>0) 
				{
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					
				}
			}
		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].style)
				{
 
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y);
					
				}
				else
				{
 
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y);
					

					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y);
					
				}
				
				if(j>0) 
				{
 
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"������Y�u",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					
				}
			}

		}
		
	}
}

void CT3DSystemView::DrawSuiGou_CAD(long index, int BPside, CStdioFile *Dxffile)
{
	float SGLL=2.8;
	int i;
	
	if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_L==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_L==TRUE)
	{
		
		for( i=0;i<=5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"����",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y);
		}
		for( i=0;i<5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"����",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i+1].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i+1].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i+1].y);
		}
		
		for( i=0;i<5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"����",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i+1].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i+1].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i+1].y);
		}
		
		
	}
	
	
	if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_R==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_R==TRUE)
	{
		for( i=0;i<=5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"����",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y);
		}
		for( i=0;i<5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"����",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i+1].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i+1].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i+1].y);
		}
		
		for( i=0;i<5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"����",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i+1].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i+1].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i+1].y);
		}
		
	}
}

//�ʵe���s�ѼƳ]�m
void CT3DSystemView::OnAviParameter() 
{
	CRect rect;
	this->GetClientRect(&rect); //�o��Ȥ�Ϥj�p��
	
	CAviParameter	 dlg;
	

	//�T�OAVI�e�שM���צ���
    if(m_MovieWidth<=0 || m_MovieHeight<=0)
	{
		m_MovieWidth=rect.right; //AVI���e��
		m_MovieHeight=rect.bottom;//AVI������
	}
	
	
	dlg.m_MoviemaxWidth=rect.right;   //AVI���̤j�e��
	dlg.m_MoviemaxHeight=rect.bottom; //AVI���̤j����
	
	dlg.m_AviFilename=m_AviFilename;  //AVI���W
	dlg.m_AVIFrame=m_AVIFrame;//AVI�����s�W�v
	
	dlg.m_MovieWidth=m_MovieWidth; //AVI���e��
    dlg.m_MovieHeight=m_MovieHeight; //AVI������ 
	
	if(dlg.DoModal ()==IDOK)  
	{
		m_AviFilename=dlg.m_AviFilename; //AVI���W
		m_AVIFrame=dlg.m_AVIFrame; //AVI�����s�W�v
		m_MovieWidth=dlg.m_MovieWidth;  //AVI���e��
		m_MovieHeight=dlg.m_MovieHeight; //AVI������ 
	}	
}



//�}�l���s�ʵe
void CT3DSystemView::OnAviStart() 
{
	if(m_Beginrecording==TRUE)  //�p�G�}�l���s�ʵe����m_Beginrecording=TRUE,��ܤw�g���b���s�ʵe,��^
	{
		recordBegin(); //�O���}�l���s�ʵe
		return; //��^
	}
	
	//���}AVI�O�s���
	CFileDialog fd(FALSE,"avi",0,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY|OFN_PATHMUSTEXIST,"Microsoft AVI (*.avi)|*.avi||");
	
	CDC *dc=GetDC();
	wglMakeCurrent( dc->m_hDC, m_hRC );//�NRC�P��eDC���p
	
	CRect rect;
	GetClientRect(&rect); //�o��Ȥ�u�j
	
	//�T�OAVI�e�שM���צ���
	if(m_MovieWidth<=0 ||m_MovieHeight<=0) 
	{
		m_MovieWidth=rect.right;
		m_MovieHeight=rect.bottom;
	}
	
	BeginWaitCursor(); //��ܨF�|����
    bool success = false;

	//�N�����쪺�ƾڼg�JAVI���
	success = BeginMovieCapture(m_AviFilename,m_MovieWidth,m_MovieHeight,m_AVIFrame);
	if (!success)
    {
        MessageBox("������s�ʵe!", "���s�ʵe", MB_OK | MB_ICONERROR);
		return;
    }
	
	if (m_movieCapture != NULL)
    {
        if (isRecording())
            OnAviPause(); //�Ȱ����s�ʵe
        else
            recordBegin(); //�}�l���s�ʵe
    }
	
    EndWaitCursor();//�����F�|����,��_���`����
	
	wglMakeCurrent( 0, 0 );//����DC�MRC 
	ReleaseDC(dc);	//����dc		
}

//�}�l����
bool CT3DSystemView::BeginMovieCapture(CString filename, int width, int height, float framerate)
{
	m_movieCapture = new CAVICapture();
	//�]�mAVI���W�١B���s�V���j�p�B���s�V�v�BAVI������Y�覡���H��
    bool success = m_movieCapture->start(filename, width, height, framerate);
    if (success) //�p�G�]�m���\
        initMovieCapture(m_movieCapture); //��l��m_movieCapture�ܶq
    else
        delete m_movieCapture; //�p�G����,�R��m_movieCapture
    
    return success;
}

//��l��m_movieCapture�ܶq
void CT3DSystemView::initMovieCapture(CAVICapture *mc)
{
	if (m_movieCapture == NULL)
        m_movieCapture = mc;
	
}

//����O�_�b���s�ʵe
bool CT3DSystemView::isRecording()
{
	return m_Recording;
	
}

//�p�Gm_movieCapture����NULL,��l�Ʀ��\,�h�]�m���s����=true
void CT3DSystemView::recordBegin()
{
	if (m_movieCapture != NULL) //�p�Gm_movieCapture����NULL
        m_Recording = true;
	
}

//�Ȱ����s�ʵe
void CT3DSystemView::OnAviPause() 
{
	m_Recording = false;
}

//�������s�ʵe
void CT3DSystemView::OnAviEnd() 
{
	if (m_movieCapture != NULL) //�p�Gm_movieCapture ������,��ܤw�����ƾ�
	{
        recordEnd(); //�������s�ʵe		
	}		
}

//�������s�ʵe
void CT3DSystemView::recordEnd()
{
	if (m_movieCapture != NULL) //�p�Gm_movieCapture ������,��ܤw�����ƾ�
    {
        OnAviPause();//�Ȱ�,�N�������ƾڤ��A�g�J���
        m_movieCapture->end();//�������s
        delete m_movieCapture; //�R��m_movieCapture(�̭��]�t���s���ƾ�)
        m_movieCapture = NULL; //���s�]�mm_movieCapture����
    }
}

//�]�m�Ϲ��Ķ��W�v
void CT3DSystemView::OnSavepictureSpeed() 
{
	CRecordPictureSpeed	 dlg;
	dlg.m_recordPictSpeed=m_recordPictSpeed;//��e�ҳ]�m���Ķ��Ϲ��W�v
	if(dlg.DoModal ()==IDOK) //�p�G��ܮإHIDOK�覡����
	{
		m_recordPictSpeed=dlg.m_recordPictSpeed; //�o��s�]�m���Ķ��Ϲ��W�v
	}			
}


//����(�Ϲ��ǦC)
void CT3DSystemView::OnSavepictureContinue() 
{
	m_RecordPicture=TRUE;  //�����Ϲ��ǦC���лx��TRUE
	SetPictureName(); //�]�m���s�Ϲ��ɪ���l���W��
	SetTimer(2,m_recordPictSpeed,NULL);	 //�]�m���s�Ϲ��p�ɾ�
	
}

//�]�m���s�Ϲ��ɪ���l���W�١A�᭱�Ķ����Ϲ����W���H����l���W+���s�Ǹ��զ�
void CT3DSystemView::SetPictureName()
{
	CFileDialog FileDialog( FALSE, _T("bmp"), _T("*.bmp"), OFN_HIDEREADONLY,
		_T("Windows Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL );
	
	if(FileDialog.DoModal() == IDOK) //���}����ܮ�
	{
		m_RecordPicturename = FileDialog.GetPathName(); //�o��Ϲ����W
		
	}	
}

//���s�Ϲ��ǦC
void CT3DSystemView::RecordPictures()
{
	
	CString str,str1,fname;
	
	str.Format("%s",m_RecordPicturename);
	int n=str.GetLength ();
	str=str.Left (n-4);
	m_PictureNumbers++; //�Ķ����Ϲ��ƶq+1
	
	str1.Format ("%d",m_PictureNumbers);
	switch(str1.GetLength ())
	{
		case 1:str1="0000"+str1;break;
		case 2:str1="000"+str1;break;
		case 3:str1="00"+str1;break;
		case 4:str1="0"+str1;break;
	}
	
	fname=str+str1+".bmp"; //�o��n�O�s����Ϥ��W
	CRect rcDIB;
	GetClientRect(&rcDIB);
    
	OnDraw (GetDC());//��s�T������ 
	CapturedImage.Capture(GetDC(), rcDIB);
	
	CapturedImage.WriteDIB(fname); //�N�Ķ����ƾڼg�J��Ϥ����
	CapturedImage.Release();	//����CapturedImage
}

//���L�w��
void CT3DSystemView::OnFilePrintPreview() 
{
	CRect rcDIB;
	GetClientRect(&rcDIB); //�o��Ȥ�Ϥj�p
	OnDraw (GetDC()); //��s�T������ 
	CapturedImage.Capture(GetDC(), rcDIB);//�NDDB�ϧ��ഫ���P�]�ƵL�������DIB
	CView::OnFilePrintPreview(); //�ե�	CView::OnFilePrintPreview()��ƥ��L�w��
}

//��������Ϲ�
void CT3DSystemView::OnSavepictureStop() 
{
	m_RecordPicture=FALSE; //���ѿ��s�Ϲ���FALSE
	KillTimer(2);	//�P���p�⾹2	
	
}

//�O�s�̹�����
void CT3DSystemView::OnMenuSavescreentobmp() 
{
	CString strFilename;
	
	HDC   dc;   
	dc=::GetDC(NULL);   
	CRect rcDIB;
	GetClientRect(&rcDIB);
	rcDIB.right = rcDIB.Width();
	rcDIB.bottom = rcDIB.Height();
	HBITMAP mybitmap=GetSrcBit(dc,rcDIB.Width(),rcDIB.Height());
	
	CFileDialog FileDialog( FALSE, _T("bmp"), _T("*.bmp"), OFN_HIDEREADONLY,
		_T("Windows Bitmap Files (*.bmp)|*.bmp||"), NULL );
	if(FileDialog.DoModal()==IDOK)
	{
		strFilename=FileDialog.GetPathName(); //�o���Ϥ��W
		if(!strFilename.IsEmpty()) //�p�G��Ϥ��W����
		{
			DeleteFile(strFilename); //�R���즳���
			BOOL bOK=SaveBmp(mybitmap,strFilename);  //�O�s���Ϥ��
			if(bOK==TRUE) //�p�G�O�s���\
				MessageBox("�Ϲ��O�s���\","�O�s�̹�����",MB_ICONINFORMATION);
			else
				MessageBox("�Ϲ��O�s����","�O�s�̹�����",MB_ICONINFORMATION);
		}
		
	}	
}

//�O�s��Ϩ���
BOOL CT3DSystemView::SaveBmp(HBITMAP hBitmap, CString FileName)
{
	//�]�ƴy�z��   
	HDC   hDC;   
	//��e����v�U�C�H���Ҧ��r�`��   
	int   iBits;   
	//��Ϥ��C�H���Ҧ��r�`��   
	WORD   wBitCount;   
	//�w�q�զ�O�j�p�A   ��Ϥ������r�`�j�p   �A��Ϥ��j�p   �A   �g�J���r�`��     
	DWORD   dwPaletteSize=0,   dwBmBitsSize=0,   dwDIBSize=0,   dwWritten=0;     
	//����ݩʵ��c     
	BITMAP   Bitmap;       
	//��Ϥ���Y���c   
	BITMAPFILEHEADER   bmfHdr;       
	//��ϫH���Y���c     
	BITMAPINFOHEADER   bi;       
	//���V��ϫH���Y���c       
	LPBITMAPINFOHEADER   lpbi;       
	//�w�q���A���t���s�y�`�A�զ�O�y�`     
	HANDLE   fh,   hDib,   hPal,hOldPal=NULL;     
    
	//�p���Ϥ��C�ӹ����Ҧ��r�`��     
	hDC   =   CreateDC("DISPLAY",   NULL,   NULL,   NULL);   
	iBits   =   GetDeviceCaps(hDC,   BITSPIXEL)   *   GetDeviceCaps(hDC,   PLANES);     
	DeleteDC(hDC);     
	if   (iBits   <=   1)   wBitCount   =   1;     
	else   if   (iBits   <=   4)     wBitCount   =   4;     
	else   if   (iBits   <=   8)     wBitCount   =   8;     
	else       wBitCount   =   24;     
    
	GetObject(hBitmap,   sizeof(Bitmap),   (LPSTR)&Bitmap);    //�O�s��Ϥ��e�q�LGetObject��ƨ��o��Ϫ���
	bi.biSize   =   sizeof(BITMAPINFOHEADER);   
	bi.biWidth   =   Bitmap.bmWidth;   
	bi.biHeight   =   Bitmap.bmHeight;   
	bi.biPlanes   =   1;   
	bi.biBitCount   =   wBitCount;   
	bi.biCompression   =   BI_RGB;   
	bi.biSizeImage   =   0;   
	bi.biXPelsPerMeter   =   0;   
	bi.biYPelsPerMeter   =   0;   
	bi.biClrImportant   =   0;   
	bi.biClrUsed   =   0;   
    
	dwBmBitsSize   =   ((Bitmap.bmWidth   *   wBitCount   +   31)   /   32)   *   4   *   Bitmap.bmHeight;   
    
	//����Ϥ��e���t���s     
	hDib   =   GlobalAlloc(GHND,dwBmBitsSize   +   dwPaletteSize   +   sizeof(BITMAPINFOHEADER));     
	lpbi   =   (LPBITMAPINFOHEADER)GlobalLock(hDib);     
	*lpbi   =   bi;     
    
	//   �B�z�զ�O       
	hPal   =   GetStockObject(DEFAULT_PALETTE);     
	if   (hPal)     
	{     
		hDC   =   ::GetDC(NULL);     
		hOldPal   =   ::SelectPalette(hDC,   (HPALETTE)hPal,   FALSE);     
		RealizePalette(hDC);     
	}   
	
	//�o��DC��ϥy�` 
	GetDIBits(hDC,   hBitmap,   0,   (UINT)   Bitmap.bmHeight,   (LPSTR)lpbi   +   sizeof(BITMAPINFOHEADER)     
		+dwPaletteSize,   (BITMAPINFO   *)lpbi,   DIB_RGB_COLORS);     
    
	//��_�զ�O       
	if   (hOldPal)     
	{     
		::SelectPalette(hDC,   (HPALETTE)hOldPal,   TRUE);     
		RealizePalette(hDC);     
		::ReleaseDC(NULL,   hDC);     
	}     
    
	//�Ыئ�Ϥ��       
	fh   =   CreateFile(FileName,   GENERIC_WRITE,0,   NULL,   CREATE_ALWAYS,     
		FILE_ATTRIBUTE_NORMAL   |   FILE_FLAG_SEQUENTIAL_SCAN,   NULL);     
    
	if   (fh   ==   INVALID_HANDLE_VALUE)     return   FALSE;     
    
	//   �]�m��Ϥ���Y     
	bmfHdr.bfType   =   0x4D42;   //   "BM"     
	dwDIBSize   =   sizeof(BITMAPFILEHEADER)   +   sizeof(BITMAPINFOHEADER)   +   dwPaletteSize   +   dwBmBitsSize;       
	bmfHdr.bfSize   =   dwDIBSize;     
	bmfHdr.bfReserved1   =   0;     
	bmfHdr.bfReserved2   =   0;     
	bmfHdr.bfOffBits   =   (DWORD)sizeof(BITMAPFILEHEADER)   +   (DWORD)sizeof(BITMAPINFOHEADER)   +   dwPaletteSize;     
	//   �g�J��Ϥ���Y     
	WriteFile(fh,   (LPSTR)&bmfHdr,   sizeof(BITMAPFILEHEADER),   &dwWritten,   NULL);     
	//   �g�J��Ϥ���l���e     
	WriteFile(fh,   (LPSTR)lpbi,   dwDIBSize,   &dwWritten,   NULL);     
	//�M��       
	GlobalUnlock(hDib);     
	GlobalFree(hDib);     
	CloseHandle(fh);     
    
	return   TRUE;   
}

//�o��DC��ϥy�`
HBITMAP CT3DSystemView::GetSrcBit(HDC hDC, DWORD BitWidth, DWORD BitHeight)
{
	HDC   hBufDC;   
	HBITMAP   hBitmap,   hBitTemp;   
    
	//�Ыس]�ƤW�U��(HDC)   
	hBufDC   =   CreateCompatibleDC(hDC);   
    
	//�Ы�HBITMAP   
	hBitmap   =   CreateCompatibleBitmap(hDC,   BitWidth,   BitHeight);   
	hBitTemp   =   (HBITMAP)   SelectObject(hBufDC,   hBitmap);   
    
	//�o���Ͻw�İ�   
	StretchBlt(hBufDC,   0,   0,   BitWidth,   BitHeight,   
		hDC,   0,   0,   BitWidth,   BitHeight,   SRCCOPY);   
    
	//�o��̲ת���ϫH��   
	hBitmap   =   (HBITMAP)   SelectObject(hBufDC,   hBitTemp);   
    
	//���񤺦s   
    
	DeleteObject(hBitTemp);   
	::DeleteDC(hBufDC);   
    
	return   hBitmap;   
}




