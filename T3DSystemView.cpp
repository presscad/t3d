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

#define PAI 3.1415926       //定義π常量
#define HDANGLE  52.706     //定義1弧度等於多少度(1弧度=180/PAI)
#define PAI_D180  PAI/180   //定義1度等於多少弧度(1度=PAI/180弧度)

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
	Init_data() ; // 初始化相關變量
	m_lpThread  = NULL;
	
}

CT3DSystemView::~CT3DSystemView()
{
}

BOOL CT3DSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	//設置窗口類型
	cs.style|=WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	return CView::PreCreateWindow(cs);
	
}

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemView drawing

//繪製三維場景
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
		
		// 獲得打印機頁面尺寸(像素)
		int cxPage = pDC->GetDeviceCaps(HORZRES);
		int cyPage = pDC->GetDeviceCaps(VERTRES);
		// 獲得打印機每英吋上的像素個數
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
		wglMakeCurrent( pDC->m_hDC, m_hRC );// 使 RC 與當前 DC 相關聯
		DrawScene() ; // 場景繪製
		if (m_movieCapture != NULL && m_Recording)
		{
			m_movieCapture->captureFrame();
		}
		glFlush();	
		::SwapBuffers(m_pDC->GetSafeHdc());	//交換緩衝區	 
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
	
	//獲取客戶區的設備描述表
	m_pDC=new CClientDC(this); 

	//初始化OpenGL
	InitializeOpenGL(m_pDC); 
	InitList() ; // 初始化顯示列表	
	
	return 0; 

}

BOOL CT3DSystemView::InitializeOpenGL(CDC *pDC)
{
	//進行opengl的初始化工作
	m_pDC=pDC; 
	//首先把DC的象素格式調整為指定的格式，以便後面對DC的使用
	SetupPixelFormat(); 
	//根據DC來創建RC
	m_hRC=::wglCreateContext(m_pDC->GetSafeHdc()); 
	//設置當前的RC，以後的畫圖操作都畫在m_pDC指向的DC上
	::wglMakeCurrent(m_pDC->GetSafeHdc() , m_hRC); 
	

	//判斷當前系統的OpenGL版本是否支持多重紋理擴展  判斷顯卡是否支持該擴展
	glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)		wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)		wglGetProcAddress("glMultiTexCoord2fARB");
	
	if(!glActiveTextureARB || !glMultiTexCoord2fARB)
	{
		MessageBox("當前OpenGL版本較低，不支持多重紋理\n擴展功能，請下載安裝新的版本！" ,  "多重紋理擴展錯誤" ,  MB_ICONSTOP);
		return FALSE;
	}

	m_cTxtSky.LoadGLTextures("Sky.bmp");	//加載背景天空的紋理影像

	m_cTxtureBP.LoadGLTextures("紋理\\邊坡防護\\拱形護坡1.bmp");
	m_cTxtureLJ.LoadGLTextures("紋理\\路肩\\1.bmp");
	m_cTxtureGdToLJ.LoadGLTextures("紋理\\路肩\\10.bmp");
	m_cTxtureSuigou.LoadGLTextures("紋理\\水溝\\水溝1.bmp");
	m_cTxturePT.LoadGLTextures("紋理\\邊坡平台\\邊坡平台1.bmp");
	m_cTxtureRailway.LoadGLTextures("紋理\\鐵路\\鐵路1.bmp");
	m_cBridgeHpm.LoadGLTextures("紋理\\橋下方護坡面\\1.bmp");//橋頭下方護坡面紋理
	m_cTunnel.LoadGLTextures("紋理\\隧道內牆\\1.bmp"); //隧道內牆紋理
	m_cTunnel_dm.LoadGLTextures("紋理\\隧道洞門\\2.bmp");//隧道洞門紋理
	m_cTunnel_dmwcBp.LoadGLTextures("紋理\\隧道洞門外側邊坡\\2.bmp");//隧道洞門外側邊坡*/

	
	return TRUE;

	

}

BOOL CT3DSystemView::SetupPixelFormat()
{
	//初始化象素格式以及選取合適的格式來創建RC
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR) ,  // pfd結構的大小 
			1 ,  // 版本號
			PFD_DRAW_TO_WINDOW | // 支持在窗口中繪圖 
			PFD_SUPPORT_OPENGL | // 支持 OpenGL 
			PFD_DOUBLEBUFFER| // 雙緩存模式
			PFD_STEREO |  //支持立體模式
			PFD_TYPE_RGBA ,  // RGBA 顏色模式 
			24 ,  // 24 位顏色深度
			0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  // 忽略顏色位 
			0 ,  // 沒有非透明度緩存 
			0 ,  // 忽略移位位 
			0 ,  // 無累加緩存 
			0 ,  0 ,  0 ,  0 ,  // 忽略累加位 
			32 ,  // 32 位深度緩存 
			0 ,  // 無模板緩存 
			0 ,  // 無輔助緩存 
			PFD_MAIN_PLANE ,  // 主層 
			0 ,  // 保留 
			0 ,  0 ,  0 // 忽略層 , 可見性和損毀掩模 
	}; 
	//在DC中選擇合適的象素格式並返回索引號
	int pixelformat;
	pixelformat=::ChoosePixelFormat(m_pDC->GetSafeHdc() , &pfd);
	if (pixelformat==0)
	{
		MessageBox("選擇像素格式失敗!" , "設置像素格式" , MB_ICONERROR);
		return FALSE;
	}
	//設置指定象素格式
	if (::SetPixelFormat(m_pDC->GetSafeHdc() , pixelformat , &pfd)==FALSE)
	{
		MessageBox("設置像素格式失敗!" , "設置像素格式" , MB_ICONERROR);
		return FALSE;
	}

	

	//測試當前設置和硬件顯卡是否支持立體模式
	unsigned char ucTest;
    glGetBooleanv (GL_STEREO ,  &ucTest);  
    if (!ucTest) 
	{
		return 1;
	}
	
	
	if((pfd.dwFlags & PFD_STEREO)==0)
		bStereoAvailable=FALSE ; // 顯卡不支持立體模式
	else
		bStereoAvailable=TRUE;
	
	CString stt[5];
	if(bStereoAvailable==FALSE) //如果顯卡不支持立體模式，給出可能的錯誤原因
	{
		stt[0]="１.圖形卡不支持立體緩衝;\n";
		stt[1]="２.圖形卡驅動程序不支持立體緩衝;\n";
		stt[2]="３.只有在特定的解析度或刷新率設置下 , 才可以支持立體緩衝;\n";
		stt[3]="４.立體緩衝需要特定的驅動配置以激活;";
		stt[4].Format("立體模式未被接受.可能有以下原因:\n%s%s%s%s" , stt[0] , stt[1] , stt[2] , stt[3]);
		MessageBox(stt[4] , "立體模式設置" , MB_ICONINFORMATION);
	}
	
	
}

void CT3DSystemView::OnSize(UINT nType ,  int cx ,  int cy) 
{
	CView::OnSize(nType ,  cx ,  cy);


	if(cy>0)
	{
		WinViewX = cx ; // 視口寬度
		WinViewY = cy ; // 視口高度
		glViewport(0 , 0 , cx , cy); //設置視口大小
        m_aspectRatio = (float)cx/(float)cy ; // 視口的橫縱比例
		glMatrixMode(GL_PROJECTION); //將當前矩陣設置為投影矩陣,指明當前矩陣為GL_PROJECTION 
		glLoadIdentity();    //將當前矩陣置換為單位陣        
		gluPerspective(50.0 + m_ViewWideNarrow , m_aspectRatio , m_near , m_far);		//:fovy=50.0 + m_ViewWideNarrow , 是視野角度
		m_FrustumAngle=2*asin(0.5*m_aspectRatio*tan((50.0 + m_ViewWideNarrow)*PAI_D180))*HDANGLE;
		m_es=m_SCREEN_HEIGHT*cos(m_viewdegree*PAI_D180)/(2*tan(m_FrustumAngle/2.0*PAI_D180));
		glMatrixMode(GL_MODELVIEW);	//將當前矩陣設置為模型矩陣		
		glLoadIdentity();	//將當前矩陣置換為單位陣 
	}			
}

//清除背景
BOOL CT3DSystemView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;	
}

//初始化相關變量
void CT3DSystemView::Init_data()
{
	m_ViewWideNarrow = 0.0f;	//初始飛行視口寬窄變量
	CWindowDC dc=NULL;
	m_SCREEN_WIDTH = ::GetDeviceCaps(dc , HORZRES);	//屏幕寬度
	m_SCREEN_HEIGHT = ::GetDeviceCaps(dc , VERTRES);	//屏幕高度
	m_near=1;	//觀察點與近側剪裁平面的距離
	m_far=5000 ; // 觀察點與遠側剪裁平面的距離

	m_currebtPhramid=0 ; // 當前影像紋理的LOD級別
	mTimeElaps=0 ; // 用於計算幀率的時間值
	
	m_stereo=FALSE; //關閉立體模式
	m_Drawmode=3 ; // 繪製模式(1://線框模式  2://渲暈模式	3://紋理模式)
	
	
	m_bCamraInit=FALSE ; // 相機未初始化
    m_bLoadInitDemData=FALSE ; // 地形和影像數據未調入 
	m_LodDemblockNumber=0 ; // 加載地形塊數量初始為0
	m_RenderDemblockNumber=0 ; // 渲染地形塊數量初始為0
	
	//相機參數向上矢量
	m_vUpVector.x=0; 
	m_vUpVector.y=1;
	m_vUpVector.z=0;
	
	
	m_viewdegree=0 ; // 初始視角增量 
	m_viewHeight=m_oldviewHeight=10 ; // 相機初始高度
	m_camraDistence=80 ; // 雙目立體模式下的左右相機初始間距
	m_heighScale=1.0 ; // 高程縮放係數

	m_Radius=50000 ; // 包圍球半徑
	m_R=5500 ; // 
	m_r=3500 ; // 

	m_BhasInitOCI=FALSE;	//初始OCI未初始化
	mTimeElaps=0 ; // 用於計算幀率的時間值
	
	m_maxHeight=-9999 ; // 初始最大高程
	m_minHeight=9999 ; // 初始最小高程

	//DE財形最大高程和最小高程對應的顏色初始值
	minZ_color_R=0;minZ_color_G=1;minZ_color_B=0 ; // 綠色
	maxZ_color_R=1;maxZ_color_G=0;maxZ_color_B=0 ; // 紅色
	
// 	m_bShowbreviary=TRUE ; // 是否顯示縮略圖

	m_shizxLength=20 ; // 查詢標誌十字線長度
	m_shuzxHeight=45 ; // 查詢標誌豎直線高度
	m_QueryLineWidth=1 ; // 查詢標誌線的寬度
	m_QueryColorR=255 ; // 查詢標誌線的顏色(紅)
	m_QueryColorG=255 ; // 查詢標誌線的顏色(綠)
	m_QueryColorB=0 ; // 查詢標誌線的顏色(藍)
	m_bSearchDistencePtNums=0;

	Derx=0;	//相機在X方向上的初始變化量
	Derz=0;	//相機在Z方向上的初始變化量
	m_Step_X=5.0;	//相機在X方向移動的步長初始值(鼠標控制)
	m_Step_Z=5.0;	//相機在Z方向移動的步長初始值(鼠標控制)
	m_xTrans=0;	//在X方向上移動的步長(鍵盤控制)
	m_zTrans=0;	//在Z方向上移動的步長(鍵盤控制)

	m_OrthoViewSize=0.3;//正射投影模式下視景體大小
	m_OrthotranslateX=m_OrthotranslateY=0;//正射投影X軸方向和Y軸方向移動的距離初值

	m_ViewType=GIS_VIEW_PERSPECTIVE;

	b_haveMadeRail3DwayList=FALSE; //是否已經有三維線路顯示列表(透視投影模式下)
	b_haveMadeRail3DwayList_Ortho=FALSE;//是否已經有三維線路顯示列表(正射投影模式下)
	b_haveTerrainZoomroadList=FALSE; //線路三維建模後是否建立了地形TIN模型的顯示列表

	//初始飛行固定高度變量
	m_StaticHeight = 80.0f;
	
	//初始飛行視口上下傾變量
	m_ViewUpDown = 0.0f;
	
	//初始飛行視口寬窄變量
	m_ViewWideNarrow = 0.0f;
	
	m_flyspeed=10;//飛行速度
	
	
	m_PreZooomLC=m_CurZooomLC=0;//漫遊時前一里程和當前里程

	b_haveGetRegion=FALSE;//標識是否建立線路封閉區域
	
	
	m_bridgeColorR=0; //橋樑欄杆顏色
	m_bridgeColorG=0;//橋樑欄杆顏
	m_bridgeColorB=255;//橋樑欄杆顏
	m_Bridge.m_Bridge_HLHeight=2.0; //橋樑欄杆高
	m_Bridge.m_Bridge_HLSpace=10;//橋樑欄杆間距
	m_Bridge.m_Bridge_HLWidth=3.0;//橋樑欄杆寬度
    m_Bridge.m_Bridge_QDSpace=40;//橋墩間距
	m_Bridge.m_Bridge_HPangle=45;//橋頭護坡傾角
	m_3DSfilename_QD=".\\模型\\橋樑墩台\\剛架式柔性墩\\模型文件.3DS";
	
	
	m_Railway.m_Railway_width=2.5;//路基斷面總寬度
	m_Railway.m_Lj_width=0.8;//路肩寬度
	m_Railway.m_GuiMianToLujianWidth=0.6;//碴肩至碴腳的高度
	m_Railway.m_Lj_Dh=m_Railway.m_GuiMianToLujianWidth*(1/1.75);//鐵軌到碴肩的距離
	m_Railway.m_TieGui_width=1.435;//鐵軌間距
	
	m_Tunnel.height=6.55; //隧道總高度
	m_Tunnel.Archeight=2;//隧道圓弧高度
	m_Tunnel.WallHeight=m_Tunnel.height-m_Tunnel.Archeight;////隧道立牆高度
	m_Tunnel.ArcSegmentNumber=20;//隧道圓弧分段數
	m_Tunnel.H=1.5;//隧道圓弧頂端再向上的高度(m_Tunnel.height+m_Tunnel.H=隧道洞門總高度)
	m_Tunnel.L=4.0;//隧道洞門頂端左右兩側延伸的寬度 
	m_Tunnel.width=m_Railway.m_Railway_width+2*(m_Railway.m_Lj_width+m_Railway.m_GuiMianToLujianWidth);
	
	
	m_shizxLength=20;
	m_shuzxHeight=45;

	m_NorthPtangle=90;//指北針初始指向角度(90度,即表示正北方向,在三維空間中則指向Z員負方向,即指向屏幕裡面)
	
	m_bShowbreviary=TRUE;//顯示縮略視圖

	m_PathFlag=FALSE;//是否成功打開飛行路徑
	m_FlyPause=FALSE;//標識是否暫停飛行
	
	
	m_3DSfilename_QD=".\\模型\\橋樑墩台\\剛架式柔性墩\\模型文件.3DS";
	
	
	DeleteFile("c:\\TEMP.AVI"); //刪除c:\\TEMP.AVI文件
    m_AviFilename="c:\\TEMP.AVI"; //AVI動畫初始文件名
	m_AVIFrame=15; //AVI頻率
	m_Recording=false; //標識是否正在捕捉視頻動畫
	
	m_RecordPicture=FALSE;     //錄像圖像序列的標誌	
    m_recordPictSpeed=100;	//錄製圖像的幀率
	m_PictureNumbers=0; //錄製圖像數量
	
}

//地形子塊和影像子塊的調入
BOOL CT3DSystemView::LoadInitDemData()
{
	if(theApp.bLoadImage==FALSE)//如果影像加載失敗 , 返回 
        return FALSE;

	if(theApp.bLoginSucceed==FALSE) //如果數據庫連接失敗 , 返回
		return FALSE;
	if(m_bLoadInitDemData==TRUE)	//如果初始地形和影像子塊已調入成功 , 返回
		return TRUE;

	if(theApp.m_BlockCols<=0 || theApp.m_BlockRows<=0) //如果地形塊的總行數或總列數<=0 , 返回
		return FALSE;
	else  //重新定義二維數組m_DemLod_My的大小 , 並為其分配內存
		m_AllocUnAlloc2D3D.Alloc2D_int(m_DemLod_My , theApp.m_BlockCols*theApp.m_BlockRows+1 , 3);
	
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	
	//在正射投影模式下地形的x , y中心坐標和x , y方向的比例
	m_ortho_CordinateOriginX=0.5;
	m_ortho_CordinateXYScale=(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);
	m_ortho_CordinateOriginY=m_ortho_CordinateOriginX*m_ortho_CordinateXYScale;
	
	double m_Sphere_x , m_Sphere_y;
	m_Sphere_x=(theApp.m_DemRightUp_x+theApp.m_DemLeftDown_x)/2.0 ; // 包圍球中心x坐標
	m_Sphere_y=(theApp.m_DemRightUp_y+theApp.m_DemLeftDown_y)/2.0 ; // 包圍球中心y坐標
	
	
	CString strsql;
	int mRowId , mColID;

	//打開數據庫表dem_block
	strsql="select *  from  dem_block order by 行號 , 列號";
	if(m_Recordset->State)	//如果m_Recordset已打開
		m_Recordset->Close() ; // 關閉
	try
	{
		m_Recordset->Open(_bstr_t(strsql) , (IDispatch*)(theApp.m_pConnection) , adOpenDynamic , adLockOptimistic , adCmdText);    
	}
	catch(_com_error& e)	//錯誤處理		
	{
		CString errormessage;
		errormessage.Format("打開數據庫表失敗!\r\n錯誤信息:%s" , e.ErrorMessage());
		AfxMessageBox(errormessage , MB_ICONSTOP , 0);
		m_Recordset->Close() ; // 關閉記錄集
		return FALSE ; // 返回
	} 
	
	long mcount;
    m_LodDemblockNumber=0 ; // 加載地形塊數量
	
	while(!m_Recordset->adoEOF)//如果沒有到數據庫尾
	{
		
		Thevalue = m_Recordset->GetCollect("中心坐標X"); 
		double m_demblock_centerx=(double)Thevalue ;	//得到DEM子塊中心x坐標
		
		Thevalue = m_Recordset->GetCollect("中心坐標Y"); 
		double m_demblock_centery=(double)Thevalue;	//得到DEM子塊中心y坐標
		
		//計算DEM子塊中心與包圍球中心距離
		double distence=sqrt((m_Sphere_x-m_demblock_centerx)*(m_Sphere_x-m_demblock_centerx)+
			(m_Sphere_y-m_demblock_centery)*(m_Sphere_y-m_demblock_centery));

		if(distence<m_Radius)//如果DEM子塊中心與包圍球中心距離<設置的包圍球半徑 , 則加載該地形子塊
		{
			Thevalue = m_Recordset->GetCollect("行號"); 
			mRowId=(long)Thevalue;
			
			Thevalue = m_Recordset->GetCollect("列號"); 
			mColID=(long)Thevalue;
			//存儲所加載的地形塊中心大地x , y坐標
			m_DemBlockCenterCoord[m_LodDemblockNumber][0]=m_demblock_centerx-theApp.m_DemLeftDown_x;
			m_DemBlockCenterCoord[m_LodDemblockNumber][1]=-(m_demblock_centery-theApp.m_DemLeftDown_y);
			
			m_lodDemBlock[m_LodDemblockNumber][0]=mRowId ; // 調入的地形塊的行號
			m_lodDemBlock[m_LodDemblockNumber][1]=mColID ; // 調入的地形塊的列號
			m_lodDemBlock[m_LodDemblockNumber][2]=m_LodDemblockNumber ; // 調入的地形塊數量
			
			mcount=(mRowId-1)*theApp.m_BlockCols+mColID ; // 計算調入的地形塊在所有DEM數據塊中的索引
			m_DemLodIndex[m_LodDemblockNumber]=mcount ; // 記錄調入的第m_LodDemblockNumber地形子塊的索引 
			m_DemLod_My[mcount][0]=mRowId;	//調入的地形塊的行號
			m_DemLod_My[mcount][1]=mColID;	//調入的地形塊的列號
			m_DemLod_My[mcount][2]=m_LodDemblockNumber;	//調入的地形塊數量
			m_pbm_DemLod[mcount]=true;
			if(m_LodDemblockNumber==0)//如果是第一次調入
			{
				m_loddem_StartRow=mRowId ; // 存儲調入的地形塊的起始行號
				m_loddem_StartCol=mColID ; // 存儲調入的地形塊的起始列號
			}
			m_LodDemblockNumber++; //調入地形塊數量+1
		}

		if(mRowId>(theApp.m_BlockRows/2.0+m_Radius/theApp.m_Dem_BlockWidth) && mColID>(theApp.m_BlockCols/2.0+m_Radius/theApp.m_Dem_BlockWidth) && distence>m_Radius)
			break;
			m_Recordset->MoveNext() ; // 
	}
	m_Recordset->Close() ; // 關閉數據庫表

	m_loddem_EndRow=mRowId ; // 存儲調入的地形塊的結束行號
	m_loddem_EndCol=mColID ; // 存儲調入的地形塊的結束列號

    if(m_LodDemblockNumber<=0) //如果加載地形塊數量<=0 , 表示調入失敗 , 返回
		return FALSE ; // 返回
	

    m_tempDemLodIndex=new int[m_LodDemblockNumber];
	//重新定義bsign數組大小(若值為1,表示調入的地形子塊參與繪製,=0,表示未參與繪製,被剔除掉了)
	m_bsign=new int[m_LodDemblockNumber];
	
	CString strtempfile="c:\\tempdem.txt" ; // 臨時ASCII文件 , 用於存儲從數據庫中讀取的DEM子塊數據
	ExporttotalDemToFIle(strtempfile);//從數據庫中讀取所有高程數據到數組中,是為了用來內插高程時用的	
	ReadHdata(strtempfile);//讀取DEM所有高種點到全局數組theApp.m_DemHeight[]中

	float iPer=100.0/m_LodDemblockNumber;
	for( int i=0;i<m_LodDemblockNumber;i++)
	{
		//將第m_lodDemBlock[i][0]行和第m_lodDemBlock[i][1]列的大二進制(BLOB)
		//DEM數據從數據庫中讀取並寫入臨時ASCII文件中
		ExportBlobDemToFIle(strtempfile , m_lodDemBlock[i][0] , m_lodDemBlock[i][1]);
		ReadDataFromFiles(strtempfile , i) ; // 從臨時的ASCII文件讀取DEM數據點到高程
	 	getDemBlockTexture(m_lodDemBlock[i][0] , m_lodDemBlock[i][1] , i) ; // 讀取並加載對應DEM地形子塊的影像紋理
		strsql.Format("正在加載地形與影像紋理數據 , 請稍候... , 已完成%.2f%s" , (i+1)*iPer , "%");
		pMainFrame->Set_BarText(4 , strsql , 0); 
	}
	pMainFrame->Set_BarText(4 , "加載地形與影像紋理數據完成!" , 0); 
	pMainFrame->Set_BarText(5 , " " , 60) ; // 加載完成，清空進度信息，並隱藏進度條控件
	m_bLoadInitDemData=TRUE ; // 數據加載成功

	double	mCx=(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x)/2.0 ; // 初始相機視點X坐標(位於地形的中心)
	double	mCz=-800 ; // 初始相機視點Z坐標

	if(m_bCamraInit==FALSE)//如果相機沒有初始化
	{
		m_bCamraInit=TRUE ; // 標識相機初始化
		float mDis=100 ; // 視點與觀察點初始距離

		//初始化相機 , 並記錄其各參數
		PositionCamera(
			mCx , 
			m_viewHeight+m_maxHeight*m_heighScale*1.0 , 
			mCz , 
			mCx , 
			m_viewHeight+m_maxHeight*m_heighScale*1.0-mDis*tan(m_viewdegree*PAI_D180) , 
			mCz-mDis , 
			0 , 1 , 0);
		
		//相機初始視點坐標
		m_originPosition=CVector3(mCx ,  m_viewHeight+m_maxHeight*m_heighScale*1.0 ,  mCz);
		//相機初始觀察點坐標
		m_originView=CVector3(mCx , m_viewHeight+m_maxHeight*m_heighScale*1.0-mDis*tan(m_viewdegree*PAI_D180) , mCz-mDis);
			
	}
	
	return TRUE;
}

//讀取DEM所有高種點到全局數組theApp.m_DemHeight[]中
void CT3DSystemView::ReadHdata(CString strfilename)
{
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	long i,j;
	CString tt;
	float hh;	
	FILE *fp=fopen(strfilename,"r");//打開DEM文件

	//讀取DEM文件頭信息
	fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s\n",tt);

	//重新定義全局數組theApp.m_DemHeight[]的大小,並分配內存
	theApp.m_DemHeight= new float[theApp.m_Dem_Rows*theApp.m_Dem_cols];
	float mPer=100.0/(theApp.m_Dem_Rows*theApp.m_Dem_cols);
	
	for (i=0;i<theApp.m_Dem_Rows;i++)
	{
		for (j=0;j<theApp.m_Dem_cols;j++)
		{
			fscanf(fp,"%f ",&hh);  //讀取高程
			theApp.m_DemHeight[i*theApp.m_Dem_cols+j]=hh;
		}
		fscanf(fp,"\n");  
	}
	
	fclose(fp); //關閉文件
	DeleteFile(strfilename); //刪除臨時文件
}

//從數據庫中讀取所有高程數據到數組中,是為了用來內插高程時用的
void CT3DSystemView::ExporttotalDemToFIle(CString strFilename)
{
	CString tt;
	int idcol=1;	
	tt.Format("SELECT DEM數據 FROM DEM_INFO WHERE 編號= :%d FOR UPDATE",1);
	myOci.ReadBOLBDataFromDB(strFilename,tt,1);//從數據庫中讀取DEM數據
}

//初始化相機 , 並記錄其各參數
void CT3DSystemView::PositionCamera(double positionX ,  double positionY ,  double positionZ ,  double viewX ,  double viewY ,  double viewZ ,  double upVectorX ,  double upVectorY ,  double upVectorZ)
{
	CVector3 vPosition	= CVector3(positionX ,  positionY ,  positionZ);
	CVector3 vView		= CVector3(viewX ,  viewY ,  viewZ);
	CVector3 vUpVector	= CVector3(upVectorX ,  upVectorY ,  upVectorZ);
	
	
	m_vPosition = vPosition;	//視點坐標				
	m_vView     = vView;		//觀察點坐標		
	m_vUpVector = vUpVector;	//向上矢量坐標			
	m_oldvPosition=m_vPosition; //保存當前視點坐標
}

//從DEM數據表中讀取的BLOB二進制的DEM數據，並寫入臨時ASCII格式的文件中，實現DEM數據讀取
void CT3DSystemView::ExportBlobDemToFIle(CString strFilename ,  int RowIndex ,  int ColIndex)
{
	CString tt;
	int idcol=(RowIndex-1)*theApp.m_BlockCols+ColIndex;	
	tt.Format("SELECT DEM數據 FROM dem_block WHERE 行號=%d AND 列號=%d AND 編號= :%d FOR UPDATE" , RowIndex , ColIndex , idcol);
	myOci.ReadBOLBDataFromDB(strFilename , tt , idcol) ; // 從數據庫中讀取BLOB數據
}

//從ASCII格式的文件中讀取DEM高程點數據 , 並寫入高程數組中
void CT3DSystemView::ReadDataFromFiles(CString strfiles ,  int Index)
{
	float hh; 
	int i , j;
    int mCount=theApp.m_Dem_BlockSize ; // 地形子塊大小(如分塊大小為33×33 , 則地形子塊大小=33 , 依次類推)
    FILE *fp=fopen(strfiles , "r") ; // 打開文件
	//循環讀取DEM數據
	for( i=0;i<mCount;i++)
	{
		for( j=0;j<mCount;j++)
		{
			fscanf(fp , "%f " , &hh);  
			
			m_pHeight_My[Index][i*mCount+j]=hh ; // 將DEM高程值寫入數組
			if(m_maxHeight<hh) m_maxHeight=hh; //計算最大高程值
			if(m_minHeight>hh && hh!=-9999) m_minHeight=hh ; // 計算最小高程值
			
		}
	}
	fclose(fp) ; // 關閉文件
	DeleteFile(strfiles) ; // 刪除臨時ASCII文件
}

//讀取並加載對應DEM地形子塊的影像紋理
void CT3DSystemView::getDemBlockTexture(int RowIndex ,  int ColIndex ,  int Index)
{
	CString strsql;
	int mID;
	_RecordsetPtr mRst;
	mRst.CreateInstance(_uuidof(Recordset));
		
	strsql.Format("select *  from TEXTURE WHERE 行號=%d AND 列號=%d  AND 紋理金子塔層號=%d" , RowIndex , ColIndex , m_currebtPhramid);
	try
	{
		//打開數據庫表
		mRst->Open(_bstr_t(strsql) , (IDispatch*)(theApp.m_pConnection) , adOpenDynamic , adLockOptimistic , adCmdText);    
	}
	
	catch(_com_error& e)	//出錯處理
	{
		CString errormessage;
		errormessage.Format("打開數據庫表失敗!\r\n錯誤信息:%s" , e.ErrorMessage());
		MessageBox(errormessage , "讀取影像紋理" , MB_ICONSTOP);
		mRst->Close() ; // 關閉數據庫表
		return;
	} 
	
	if(mRst->adoEOF)	
	{
		mRst->Close() ; // 關閉數據庫表
		return;
	}
	
	//得到第Index影像紋理塊的左下和右上x , y坐標
	Thevalue = mRst->GetCollect("左下角坐標X"); 
	m_Texturexy[Index][0]=(double)Thevalue;
	
	Thevalue = mRst->GetCollect("左下角坐標Y"); 
	m_Texturexy[Index][1]=(double)Thevalue;
	
	Thevalue = mRst->GetCollect("右上角坐標X"); 
	m_Texturexy[Index][2]=(double)Thevalue ;
	
	Thevalue = mRst->GetCollect("右上角坐標Y"); 
	m_Texturexy[Index][3]=(double)Thevalue;
	
	Thevalue = mRst->GetCollect("編號"); 
	mID=(long)Thevalue;
	
	mRst->Close() ; // 關閉數據庫表
	strsql.Format("C:\\%d_%d.bmp" , RowIndex , ColIndex) ; // 設置臨時影像紋理文件名
	if(ExportBlobTextureToFIle(strsql , RowIndex , ColIndex , mID)==TRUE)//從oracle數據庫表中讀取BLOB類型的影像紋理數據並寫入臨時影像紋理文件
		m_demTextureID[Index]=m_texturesName.LoadGLTextures(_bstr_t(strsql)) ; // 存儲調入的影像紋理子塊的紋理ID , 手於綁定紋理
	DeleteFile(strsql) ; // 刪除臨時文件

}

//初始化數組和OCI
void CT3DSystemView::Init_ArrayData()
{
	if(theApp.bLoadImage==FALSE) //如果影像紋理加載失敗，返回
        return ;
	
	if(theApp.bLoginSucceed==TRUE && m_BhasInitOCI==FALSE)//如果數據加載成功，但OCI未初始化
	{
		m_nMapSize=theApp.m_Dem_BlockSize-1 ; // 
		int blocks=m_nMapSize/2;
		//分配數組內存
		m_AllocUnAlloc2D3D.Alloc2D_float(m_pHeight_My , blocks*blocks , (m_nMapSize+1)*(m_nMapSize+1)) ; // 存儲調入地形子塊的高程點
		m_AllocUnAlloc2D3D.Alloc2D_bool(m_pbQuadMat , blocks*blocks , (m_nMapSize+1)*(m_nMapSize+1)) ; // 標識地形子塊的節點是否還需要繼續分割
		m_AllocUnAlloc2D3D.Alloc1D_bool(m_pbm_DemLod , theApp.m_BlockCols *theApp.m_BlockRows) ; // 標識地形塊是否被調入
		m_AllocUnAlloc2D3D.Alloc2D_int(m_DemLod_My , theApp.m_BlockCols*theApp.m_BlockRows+1 , 3) ; // 存儲調入地形子塊的行號 , 列號等信息
		if(m_BhasInitOCI==FALSE)//如果OCI還未被初始化
		{
			myOci.Init_OCI(); //初始化OCI
			m_BhasInitOCI=TRUE ; // 標識為TRUE  
		}
	}
}

//信息初始化和加載地形 , 影像數據
void CT3DSystemView::InitTerr()
{
	Init_ArrayData() ; // 初始化數組和OCI
	if(LoadInitDemData()==FALSE) //如果數據加載失敗 , 返回
		return ; // 返回
}


//三維地形繪製(三維地形渲染)
void CT3DSystemView::DrawTerrain()
{
	if(theApp.bLoginSucceed==FALSE || m_bLoadInitDemData==FALSE)
		return;
	
	//glShadeModel函數用來設置陰影的效果，主要有GL_SMOOTH和GL_FLAT兩種效果，
	//其中GL_SMOOTH為默認值，表示平滑陰影效果；
	glShadeModel(GL_SMOOTH);

	glDisable(GL_TEXTURE_2D) ; // 關閉2D紋理映射功能
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // 選擇TEXTURE0為設置目標
	glEnable(GL_TEXTURE_2D) ; // 激活TEXTURE0單元

	glActiveTextureARB(GL_TEXTURE1_ARB) ; // 選擇TEXTURE1為設置目標
	glEnable(GL_TEXTURE_2D) ; // 激活TEXTURE1單元 , 啟用2D紋理映射
	glTexEnvi(GL_TEXTURE_ENV ,  GL_TEXTURE_ENV_MODE ,  GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV ,  GL_RGB_SCALE_ARB ,  2);
	glMatrixMode(GL_TEXTURE); //定義矩陣為模型紋理矩陣
	glLoadIdentity() ; // 將當前矩陣置換為單位矩陣
	glDisable(GL_TEXTURE_2D) ; // 關閉紋理功能
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // 選擇TEXTURE0為設置目標
	SetDrawMode() ; // 
	
	
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();            
	gluPerspective(50.0 + m_ViewWideNarrow , (float)WinViewX/(float)WinViewY , m_near , m_far);		
	
	glMatrixMode(GL_MODELVIEW); //定義矩陣為模型模型矩陣
	glLoadIdentity(); //將當前矩陣置換為單位矩陣       

/*
	glClearDepth函數設置深度緩衝區的，它的含義就在OpenGL窗口繪製的圖形深入到屏幕中的程度，
	深度的意義就是在三維空間中的z坐標的數值，z取0時表示在平面上，你就看不到窗口中的圖形了，
	  所以負值越小，越遠離窗口平面向裡，說明窗口中的圖形離我們觀察者的距離變遠了；
*/
	glClearDepth(1.0f); //設置初始化深度緩存值
	glEnable(GL_DEPTH_TEST); // 啟用深度測試
	glDepthFunc(GL_LESS); //在調用glEnable(GL_DEPTH_TEST); 開啟這個功能以後，當深度變化小於當前深度值時，更新深度值。

	
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		
	
	int nCount=0;


	if(this->m_stereo==TRUE) //如果是雙目立體模式
	{
		SetCamra(1); //設置相機
	}
	else	//非立體
	{
		SetCamra(0) ; // 設置相機
	}

	glViewport(0 ,  0 ,  WinViewX ,  WinViewY); //設置視口大小和位置
	
	if(b_haveGetRegion==TRUE && m_ifZoomonRoad==TRUE)//如果沿線路方案漫遊
	{
		DrawTerrainZoomonRoad() ; // 繪製地形與三維線路模型
	}
	else //僅繪製地形
	{
		if(theApp.bLoginSucceed==TRUE && m_bLoadInitDemData==TRUE)
		{
			//計算幀率
			float currentTime1 = timeGetTime() * 0.001f;
			nCountFrame++;
			CalculateViewPortTriCord(m_vPosition.x , m_vPosition.z , m_vView.x , m_vView.z);
			
			//為數組m_pbQuadMat分配內存(LOD節點分割的標誌)
			for(int j=0;j<m_LodDemblockNumber;j++)
			{
				memset(m_pbQuadMat[j] , 0 , m_nMapSize*m_nMapSize);
			}
		
			CalcFPS() ; // 計算幀率

			//創建地形顯示列表
			glNewList(m_TerrainList , GL_COMPILE_AND_EXECUTE);
				m_RenderDemblockNumber=0 ; // 渲染的地形塊數量
				View=m_vView-m_vPosition;
				for(int i=0;i<m_LodDemblockNumber;i++)
				{
					mCurrentTextID=i;
					m_CurrentDemArrayIndex=i;
					glBindTexture(GL_TEXTURE_2D ,  m_demTextureID[i]) ; // 綁定第i地表子塊的紋理
					m_lodDemBlock[i][3]=0 ; // 初始值為未參與渲染
					//如果當前地形塊不在視景體內
					if(bnTriangle(m_triPtA[0] , m_triPtA[1] , m_triPtB[0] , m_triPtB[1] , m_triPtC[0] , m_triPtC[1] , m_DemBlockCenterCoord[i][0] , m_DemBlockCenterCoord[i][1])==FALSE)
						continue;
					m_RenderDemblockNumber++ ; // 渲染的地形塊數量+1
					m_lodDemBlock[i][3]=1 ; // 當前地形塊參與渲染
                    //對當前地形塊進行LOD四叉樹分割
					UpdateQuad(m_nMapSize/2 , m_nMapSize/2 , m_nMapSize/2 , 1 , m_lodDemBlock[i][0] , m_lodDemBlock[i][1]);
					//渲染LOD四叉樹分割後的當前地形塊 , 並計算出當前所繪製的三角形總數量
					nCount+= RenderQuad(m_nMapSize/2 , m_nMapSize/2 , m_nMapSize/2 , m_lodDemBlock[i][0] , m_lodDemBlock[i][1]);	
				}

				if(m_checkt==TRUE)//如果進行錯誤負反饋控制
				{
					if(nCount>=m_maxTrinum) //如果三角形數量超過最大三角形總數
						m_lodScreenError=m_lodScreenError*m_k1; //屏幕誤差τ增大
					if(nCount<=m_minTrinum) //如果三角形數量小於最小三角形總數
					m_lodScreenError=m_lodScreenError/m_k2 ; // 屏幕誤差τ減小
				}

			glEndList(); //結束顯示列表
			
			CString	strText;
			strText.Format("【內存/渲染塊數】=%d/%d" , m_LodDemblockNumber , m_RenderDemblockNumber);
	  		pMainFrame->Set_BarText(0 , strText , 0); //顯示內存中和渲染的地形塊數量
			
			if(m_bShowbreviary==TRUE)//顯示縮略視圖
			{
				glViewport(WinViewX*5/6 ,  WinViewY*5/6 , WinViewX/6 ,  WinViewY/6);
				glCallList(m_TerrainList) ; // 調用地形顯示列表 , 在新的視口繪製三維地形
				glViewport(0 ,  0 ,  WinViewX ,  WinViewY) ; // 重新設置視口大小
				
			}

			
			float currentTime2 = timeGetTime() * 0.001f;
			mTimeElaps+=currentTime2-currentTime1;
			if(mTimeElaps>=1.0)//如果兩次時間間隔>=1秒
			{
				strText.Format("頻率 %d FPS" , nCountFrame);
				pMainFrame->Set_BarText(1 , strText , 0); //在狀態欄指示器上顯示繪製幀率
				mTimeElaps=nCountFrame=0;
				
			}
		

			strText.Format("三角形 %d " , nCount);
			pMainFrame->Set_BarText(2 , strText , 0); //在狀態欄指示器上顯示當前幀所繪製的地形三角形總數
		}
	}


	glActiveTextureARB(GL_TEXTURE1_ARB) ; // 選擇TEXTURE1為設置目標
	glDisable(GL_TEXTURE_2D) ; // 關閉TEXTURE1紋理功能
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // 選擇TEXTURE0為設置目標		
	glDisable(GL_TEXTURE_2D) ; // 關閉TEXTURE0紋理功能
	glDisable(GL_DEPTH_TEST) ; // 關閉深度緩衝區測試功能
}

//計算幀率
void CT3DSystemView::CalcFPS()
{
	static DWORD dwStart = 0;
	static nCount = 0;
	nCount++;
	DWORD dwNow = ::GetTickCount();//返回從程序啟動到現在所經過的毫秒數
	
	if(dwNow-dwStart>=1000)//每1秒計算一次幀率
	{
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		CString strText;
		strText.Format("頻率 %d FPS " , nCount , 0);
		pMainFrame->Set_BarText(1 , strText , 0); //在狀態欄上指示器是顯示幀率值
		dwStart = dwNow;
		nCount = 0;
	}
}

//設置相機
void CT3DSystemView::SetCamra(int mStyle)
{
	
		switch(mStyle)
		{
		case 0://非雙目立體模式
			gluLookAt(m_vPosition.x ,  m_vPosition.y ,  m_vPosition.z , 	
				m_vView.x , 	 m_vView.y ,      m_vView.z , 	
				m_vUpVector.x ,  m_vUpVector.y ,  m_vUpVector.z);
			break;
		case 1://雙目立體模式 , 左相機
			gluLookAt(m_vPosition.x-m_camraDistence/2.0 ,  m_vPosition.y ,  m_vPosition.z , 	
				m_vView.x , 	 m_vView.y ,      m_vView.z , 	
				m_vUpVector.x ,  m_vUpVector.y ,  m_vUpVector.z);
			break;
		case 2://雙目立體模式 , 右相機
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
		
		//在狀態欄指示器上顯示相關信息
		strText.Format("【俯視角】A=%.2f" , m_viewdegree);
		pMainFrame->Set_BarText(3 , strText , 0); 
		
		if(m_ifZoomonRoad==FALSE)//非沿線路方案漫遊 , 否則 , 顯示當前里程
		{
			strText.Format("視點坐標:x=%.3f , y=%.3f , z=%.3f" , m_vPosition.x  , m_vPosition.y , fabs(m_vPosition.z));
			pMainFrame->Set_BarText(4 , strText , 0); 
		}
		
		if(m_ifZoomonRoad==FALSE)//非沿線路方案漫遊 , 否則 , 顯示當前里程
		{
			strText.Format("觀察點坐標:x=%.3f , y=%.3f , z=%.3f" , m_vView.x  , m_vView.y , fabs(m_vView.z));
			pMainFrame->Set_BarText(5 , strText , 0); 
		}
		
}

//初始化顯示列表
void CT3DSystemView::InitList()
{
	m_TerrainList=glGenLists(20);
	m_SkyList=m_TerrainList+1 ; // 背景天空顯示列表
	m_QLanList=m_TerrainList+2; //橋樑欄杆顯示列表
	m_QDList=m_TerrainList+3;//橋樑橋墩顯示列表
	m_Rail3DwayList=m_TerrainList+4; //線路三維模型顯示列表(透視投影模式)
	m_HazardList_Ortho=m_TerrainList+5;//線路三維模型顯示列表(正射投影模式)
	m_clockList=m_TerrainList+6;//時鐘指北針顯示列表
	m_NavigateList=m_TerrainList+7;
	m_Rail3DwayList_Ortho=m_TerrainList+8;
	m_TerrainZoomroadList=m_TerrainList+9;
	m_TunnelDMList=m_TerrainList+10; //隧道洞門顯示列表


	makeSkykList() ; // 生成繪製背景天空顯示列表
	BuildQDModelList();//生成橋墩顯示列表
	makeQLList();//生成橋樑欄杆//顯示列表
	makeClockList();//創建時鐘指北針顯示列表
	BuildTunnelDMModelList();//創建隧道洞門顯示列表
		
	
}

//沿線路方案漫遊時繪製被線路模型剪切後的三維地形
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
				
				glBindTexture(GL_TEXTURE_2D, m_demTextureID[mtextureID]); //綁定紋理
				
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
			strText.Format("頻率 %d FPS",nCountFrame);
			
			mTimeElaps=nCountFrame=0;
			
		}
	}
}

//判斷地形節點是否在簡化扇形視景體內
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
			d1=mCalF.GetPointToLineDistence(x , y , cneterx , cnetery , x2 , y2) ; // 計算點到直線的距離
			d2=mCalF.GetPointToLineDistence(x , y , cneterx , cnetery , x3 , y3) ; // 計算點到直線的距離
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

//計算簡化扇形視景體內的三個頂點坐標
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
	
	////存儲視口三角扇形的三個坐標點中的最大最小坐標
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

//對地形塊進行四叉樹LOD分割
void CT3DSystemView::UpdateQuad(int nXCenter ,  int nZCenter ,  int nSize ,  int nLevel ,  int mRowIndex ,  int mColIndex)
{
	double mx=(mColIndex-1)*theApp.m_Dem_BlockWidth;
	double mz=(mRowIndex-1)*theApp.m_Dem_BlockWidth;
	//如果地形節點不在視景體內 , 返回
	if(bnTriangle(m_triPtA[0] , m_triPtA[1] , m_triPtB[0] , m_triPtB[1] , m_triPtC[0] , m_triPtC[1] , nXCenter*theApp.m_Cell_xwidth+mx , -nZCenter*theApp.m_Cell_ywidth-mz)==FALSE)
		return ;
	
	
	if(m_ifZoomonRoad==FALSE) //是否沿線路方案漫遊
	{
		CVector3 vPos=GetPos();
		
		CVector3 vDst(nXCenter*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter , nZCenter ,  mRowIndex ,  mColIndex) , -nZCenter*theApp.m_Cell_ywidth-(mRowIndex-1)*theApp.m_Dem_BlockWidth);
		float nDist=mCalF.maxValueXYZ(fabs(vPos.x-vDst.x) , fabs(vPos.y-vDst.y) , fabs(vPos.z-vDst.z));
		float es , em;
		
		em=GetNodeError(nXCenter ,  nZCenter ,  nSize , mRowIndex ,  mColIndex) ; // 計算節點誤差
		es=m_es*(em/nDist);
		if(es<m_lodScreenError) //如果誤差小於屏幕誤差τ , 不繪製
			return;
	}
		
	if(nSize>1) //表示地形塊節點還需要繼續分割
	{	
		m_pbQuadMat[m_CurrentDemArrayIndex][nXCenter+nZCenter*m_nMapSize]=true;		
		UpdateQuad(nXCenter-nSize/2 , nZCenter-nSize/2 , nSize/2 , nLevel+1 , mRowIndex ,  mColIndex) ; // 分割左下子節點
		UpdateQuad(nXCenter+nSize/2 , nZCenter-nSize/2 , nSize/2 , nLevel+1 , mRowIndex ,  mColIndex) ; // 分割右下子節點
		UpdateQuad(nXCenter+nSize/2 , nZCenter+nSize/2 , nSize/2 , nLevel+1 , mRowIndex ,  mColIndex) ; // 分割右上子節點
		UpdateQuad(nXCenter-nSize/2 , nZCenter+nSize/2 , nSize/2 , nLevel+1 , mRowIndex ,  mColIndex) ; // 分割左上子節點
	}
}

//根據節點的X , Y和地形子塊的行號和列號從高程數組中得到對應的節點高程值
float CT3DSystemView::GetHeightValue(int X ,  int Y ,  int mRowIndex ,  int mColIndex)
{
	return m_pHeight_My[m_CurrentDemArrayIndex][X+Y*(m_nMapSize+1)]*m_heighScale;
	
}

//得到相機觀察點三維坐標
CVector3 CT3DSystemView::GetPos()
{
	return m_vPosition;
}

//得到相機視點三維坐標
CVector3 CT3DSystemView::GetView()
{
	return m_vView;
}

//得到相機向上矢量三維坐標
CVector3 CT3DSystemView::UpVector()
{
	return m_vUpVector;
}

//得到相機事參數的CVector3類型變量
CVector3 CT3DSystemView::Strafe()
{
	return m_vStrafe;
}


//節點誤差計算
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

//根據地形塊的行號和列號判斷該項地形塊是否視口三角形內
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
	
   //視口三角形(扇形的簡化)與地形子塊(矩形)判斷規則如下:
/*
	以下三種情況任何一種都認為該地形子塊需要繪製
	(1)視口三角形完全位於或部分視口三角形頂點位於地形子塊(矩形)內
	(2)地形子塊(矩形)完全位於視口三角形內
	(3)地形子塊(矩形)與視口三角形內相交
*/
	////存儲視口三角扇形的三個坐標點中的最大最小坐標
	//如果１地形子塊的最小x , y坐標都大於視口三角形的最大x , y坐標
	//    ２地形子塊的最大x , y坐標都小於視口三角形的最小x , y坐標
	//則該地形子塊一定不位於視口三角形內 , 不需再進行判斷
	if(polygonPs[0].x>=m_Viewpolygon_Maxx || polygonPs[0].y>=m_Viewpolygon_Maxy)
		return FALSE;
	if(polygonPs[3].x<=m_Viewpolygon_Minx || polygonPs[3].y<=m_Viewpolygon_Miny)
		return FALSE;
	

		
	//(1)只要視口三角形有一個頂點位於地形子塊(矩形)內就算
	if(m_triPtA[0]>polygonPs[0].x && m_triPtA[0]<polygonPs[3].x && m_triPtA[1]<-polygonPs[0].y && m_triPtA[1]>-polygonPs[3].y) //點在矩形裡
		Bt=TRUE;
	if(Bt==FALSE && m_triPtB[0]>polygonPs[0].x && m_triPtB[0]<polygonPs[3].x && m_triPtB[1]<-polygonPs[0].y && m_triPtB[1]>-polygonPs[3].y) //點在矩形裡
		Bt=TRUE;
	if(Bt==FALSE && m_triPtC[0]>polygonPs[0].x && m_triPtC[0]<polygonPs[3].x && m_triPtC[1]<-polygonPs[0].y && m_triPtC[1]>-polygonPs[3].y) //點在矩形裡
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
	
	//還有可能穿越地形子塊而
	//(1)三角形的三條邊01 , 12 , 02
	//(2)矯形的4條邊 01 , 23 , 02 , 13
		
	//01邊
	if(Bt==FALSE)
	{
		//判斷兩條線段是否相交(有交點)
		Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[1] , polygonPs[0] , polygonPs[1]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[1] , polygonPs[0] , polygonPs[2]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[1] , polygonPs[2] , polygonPs[3]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[1] , polygonPs[1] , polygonPs[3]);
	}

	//12邊
	if(Bt==FALSE)
	{
		//判斷兩條線段是否相交(有交點)
		Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[1] ,  m_Viewpolygon[2] , polygonPs[0] , polygonPs[1]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[1] ,  m_Viewpolygon[2] , polygonPs[0] , polygonPs[2]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[1] ,  m_Viewpolygon[2] , polygonPs[2] , polygonPs[3]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[1] ,  m_Viewpolygon[2] , polygonPs[1] , polygonPs[3]);
	}

	//02邊
	if(Bt==FALSE)
	{
		//判斷兩條線段是否相交(有交點)
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

//設置線路漫遊時地形塊紋理坐標
void CT3DSystemView::SetTextureCoordZoomRoad(double x ,  double z ,  int mRowIndex ,  int mColIndex)
{
	//對應地形塊的最小x , y坐標
	double mminx=(mColIndex-1)*theApp.m_Dem_BlockWidth;
	double mminy=(mRowIndex-1)*theApp.m_Dem_BlockWidth;
	
	float u=(x-mminx)/theApp.m_Dem_BlockWidth;
	float v=(z-mminy)/theApp.m_Dem_BlockWidth;
	
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB ,  u ,  v);
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB ,  u ,  v);
}

//渲染地形節點
int CT3DSystemView::RenderQuad(int nXCenter ,  int nZCenter ,  int nSize ,  int mRowIndex ,  int mColIndex)
{
	float hjh;
	int kk;
	CVector3 pos , VPos;

	
	int nH0 , nH1 , nH2 , nH3 , nH4;
	int nCount = 0;
	if(nSize>=1.0f)//地形塊節點尺寸>=1.0，表示該節點還有子節點
	{
		//節點中心點和4個角點的高程
		nH0 = GetHeightValue(nXCenter , nZCenter ,  mRowIndex ,  mColIndex);
		nH1 = GetHeightValue(nXCenter-nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex);
		nH2 = GetHeightValue(nXCenter+nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex);
		nH3 = GetHeightValue(nXCenter+nSize , nZCenter+nSize ,  mRowIndex ,  mColIndex);
		nH4 = GetHeightValue(nXCenter-nSize , nZCenter+nSize ,  mRowIndex ,  mColIndex);
	}

	int mnum=0;

	double mx=(mColIndex-1)*theApp.m_Dem_BlockWidth;
	double mz=(mRowIndex-1)*theApp.m_Dem_BlockWidth;
	

	//如果地形節點不在視景體內 , 返回
	if(bnTriangle(m_triPtA[0] , m_triPtA[1] , m_triPtB[0] , m_triPtB[1] , m_triPtC[0] , m_triPtC[1] , nXCenter*theApp.m_Cell_xwidth+mx , -nZCenter*theApp.m_Cell_ywidth-mz)==FALSE)
		return 0;

	float dz=m_maxHeight-m_minHeight;

	double x , z;
	double xcenter , zcenter;


	/*
	格網節點組成示意圖
	nH4
	  |----------------|nH3
	  |                |
	  |                |
	  |                |
	  |       nH0      |
	  |    節點中心    |
	  |                |
	  |                |
	  |----------------|
      nH1              nH2 
	
	  其中都是以節點中心(nH0)開始進行繪製 , 
	  
	順序為nH0--nH1--nH2--nH3--nH4--nH1
	其中在4條邊上(nH1--nH2 , nH2--nH3 , nH3--nH4 , nH4--nH1)可能會補充上相應點
	以消除與相臨節點分辨率不一致造成的空洞 , 也就是說一個地形節點至少會有4個三角形

    即使補充辦界點 , 其結果仍然是以節點中心nH0開始 , 繪製一系列三
	角形(以GL_TRIANGLE_FAN方式繪製) , 以提高繪製速度


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
			//以扇形繪製地形塊節點
			glBegin( GL_TRIANGLE_FAN );
		
				x=nXCenter*theApp.m_Cell_xwidth+mx;z=-nZCenter*theApp.m_Cell_ywidth-mz;
				VPos.x=x-m_vPosition.x;VPos.y=nH0-m_vPosition.y;VPos.z=z-m_vPosition.z;
				xcenter=x;
				zcenter=-z;
				if(DotProduct(View , VPos)>0) //如果在視點範圍內
				{	
					if(nH0!=theApp.m_DEM_IvalidValue)	//如果高程有效
					{
						//設置顏色
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH0-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH0-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH0-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x , nH0 ,  z);  //設置法線
						SetTextureCoord(nXCenter , nZCenter ,  mRowIndex ,  mColIndex);  //設置紋理坐標
						glVertex3i(x ,  nH0 ,  z) ; // 寫入中心點坐標
					}
					
				}
				x=(nXCenter-nSize)*theApp.m_Cell_xwidth+mx;z= -(nZCenter-nSize)*theApp.m_Cell_ywidth-mz;
				VPos.x=x-m_vPosition.x;VPos.y=nH1-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)
				{	

					if(nH1!=theApp.m_DEM_IvalidValue )	//如果高程有效
					{
						//設置顏色
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH1-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH1-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH1-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x , nH1  ,  x);  //設置法線
						SetTextureCoord(nXCenter-nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex); //設置紋理坐標
						glVertex3i(x , nH1  ,  z) ; // 左下角點
						CracksPatchTop(nXCenter , nZCenter , nSize , mRowIndex , mColIndex) ; // 節點裂縫修補
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
						if(DotProduct(View , VPos)>0)//如果節點在在視景體內
						{	
							if(hjh!=theApp.m_DEM_IvalidValue)	//如果高程有效	
							{
								//設置顏色
								glColor3f(
									(maxZ_color_R-minZ_color_R)*(hjh-m_minHeight)/dz+minZ_color_R , 
									(maxZ_color_G-minZ_color_G)*(hjh-m_minHeight)/dz+minZ_color_G , 
									(maxZ_color_B-minZ_color_B)*(hjh-m_minHeight)/dz+minZ_color_B);
								glNormal3f(x ,  hjh ,  z);  //設置法線
								SetTextureCoord(nXCenter-nSize+kk , nZCenter-nSize ,  mRowIndex ,  mColIndex); //設置紋理坐標
								glVertex3i(x ,  hjh ,  z);
								
								mnum++;
							}
						}
						
					}
				
				}

					
				x=(nXCenter+nSize)*theApp.m_Cell_xwidth+mx;z=-(nZCenter-nSize)*theApp.m_Cell_ywidth-mz;
				
				VPos.x=x-m_vPosition.x;VPos.y=nH2-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)//如果節點在在視景體內
				{	
					if(nH2!=theApp.m_DEM_IvalidValue)	//如果高程有效
					{
						//設置顏色
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH2-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH2-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH2-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x ,  nH2 ,  z) ; // 設置法線
						SetTextureCoord(nXCenter+nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex); //設置紋理坐標
						glVertex3i(x ,  nH2 ,  z) ; // 左上角點
						CracksPatchRight(nXCenter , nZCenter , nSize , mRowIndex , mColIndex) ; // 節點裂縫修補
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
						if(DotProduct(View , VPos)>0)//如果節點在在視景體內
						{	
							if(hjh!=theApp.m_DEM_IvalidValue)	//如果高程有效	
							{
								//設置顏色
								glColor3f(
									(maxZ_color_R-minZ_color_R)*(hjh-m_minHeight)/dz+minZ_color_R , 
									(maxZ_color_G-minZ_color_G)*(hjh-m_minHeight)/dz+minZ_color_G , 
									(maxZ_color_B-minZ_color_B)*(hjh-m_minHeight)/dz+minZ_color_B);
								glNormal3f(x ,  hjh ,  z) ; // 設置法線
								SetTextureCoord(nXCenter+nSize , kk+(nZCenter-nSize) ,  mRowIndex ,  mColIndex); //設置紋理坐標
								glVertex3i(x ,  hjh ,  z);
								mnum++;
							}
						}
					}
				
				}


				x=(nXCenter+nSize)*theApp.m_Cell_xwidth+mx;z=-(nZCenter+nSize)*theApp.m_Cell_ywidth-mz;
				
				VPos.x=x-m_vPosition.x;VPos.y=nH3-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)//如果節點在在視景體內
				{	
					if(nH3!=theApp.m_DEM_IvalidValue)		//如果高程有效
					{
						//設置顏色
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH3-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH3-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH3-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x ,  nH3 ,  z) ; // 設置法線
						SetTextureCoord(nXCenter+nSize , nZCenter+nSize ,  mRowIndex ,  mColIndex); //設置紋理坐標
						glVertex3i(x ,  nH3 ,  z) ; // 右上角點
						CracksPatchBottom(nXCenter , nZCenter , nSize , mRowIndex , mColIndex) ; // 節點裂縫修補
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
						if(DotProduct(View , VPos)>0)//如果節點在在視景體內
						{	
							if(hjh!=theApp.m_DEM_IvalidValue)	//如果高程有效	
							{
								//設置顏色
								glColor3f(
									(maxZ_color_R-minZ_color_R)*(hjh-m_minHeight)/dz+minZ_color_R , 
									(maxZ_color_G-minZ_color_G)*(hjh-m_minHeight)/dz+minZ_color_G , 
									(maxZ_color_B-minZ_color_B)*(hjh-m_minHeight)/dz+minZ_color_B);
								glNormal3f(x ,  hjh ,  z) ; // 設置法線
								SetTextureCoord(nXCenter+nSize-kk , nZCenter+nSize ,  mRowIndex ,  mColIndex); //設置紋理坐標
								glVertex3i(x ,  hjh ,  z);
								mnum++;
							}
						}
						
					}
				}

				
				x=(nXCenter-nSize)*theApp.m_Cell_xwidth+mx;z=-(nZCenter+nSize)*theApp.m_Cell_ywidth-mz;
				
				VPos.x=x-m_vPosition.x;VPos.y=nH4-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)//如果節點在在視景體內
				{	
					if(nH4!=theApp.m_DEM_IvalidValue)	//如果高程有效	
					{	
						//設置顏色
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH4-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH4-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH4-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x ,  nH4 ,  z) ; // 設置法線
						SetTextureCoord(nXCenter-nSize , nZCenter+nSize ,  mRowIndex ,  mColIndex) ; // 設置紋理坐標
						glVertex3i(x ,  nH4 ,  z) ; // 左上角點
						CracksPatchLeft(nXCenter , nZCenter , nSize , mRowIndex , mColIndex) ; // 節點裂縫修補
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
						if(DotProduct(View , VPos)>0)//如果節點在在視景體內
						{	
							if(hjh!=theApp.m_DEM_IvalidValue)	//如果高程有效	
							{							
								//設置顏色
								glColor3f(
									(maxZ_color_R-minZ_color_R)*(hjh-m_minHeight)/dz+minZ_color_R , 
									(maxZ_color_G-minZ_color_G)*(hjh-m_minHeight)/dz+minZ_color_G , 
									(maxZ_color_B-minZ_color_B)*(hjh-m_minHeight)/dz+minZ_color_B);
								glNormal3f(x ,  hjh ,  z) ; // 設置法線
								SetTextureCoord(nXCenter-nSize , kk+(nZCenter-nSize) ,  mRowIndex ,  mColIndex); //設置紋理坐標
								glVertex3i(mx ,  hjh ,  z);
								mnum++;
							}
						}
					}
					
				}
				

				x=(nXCenter-nSize)*theApp.m_Cell_xwidth+mx;z=-(nZCenter-nSize)*theApp.m_Cell_ywidth-mz;
				VPos.x=x-m_vPosition.x;VPos.y=nH1-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)//如果節點在在視景體內
				{	
						
					if(nH1!=theApp.m_DEM_IvalidValue)	//如果高程有效	
					{
						//設置顏色
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH1-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH1-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH1-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x ,  nH1 ,  z) ; // 設置法線
						SetTextureCoord(nXCenter-nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex); //設置紋理坐標
						glVertex3i(x ,  nH1 , z) ; // 重寫左下角點
						nCount++;
					}
				}

				
			glEnd();
			
			nCount=nCount+mnum ; // 三角形數量
			mnum=0;
		}
	return nCount ; // 返回三角形數量
}

//設置紋理坐標
void CT3DSystemView::SetTextureCoord(float x ,  float z ,  int mRowIndex ,  int mColIndex)
{
	double X=x*theApp.m_Cell_xwidth;
	double Y=-z*theApp.m_Cell_xwidth;
	
	float u=(X)/(m_Texturexy[mCurrentTextID][2]-m_Texturexy[mCurrentTextID][0]);
	float v=-(Y)/(m_Texturexy[mCurrentTextID][3]-m_Texturexy[mCurrentTextID][1]);	
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB ,  u ,  v) ; // 指定多重紋理單元TEXTURE0的紋理坐標
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB ,  u ,  v) ; // 指定多重紋理單元TEXTURE1的紋理坐標
}

//節點裂縫修補(底部)
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
	CracksPatchBottom(nXCenter+nSize/2 , nZCenter+nSize/2 , nSize/2 , mRowIndex ,  mColIndex) ; // 節點裂縫修補
	SetTextureCoord(nXCenter , nZCenter+nSize ,  mRowIndex ,  mColIndex); //設置紋理坐標
	glVertex3i(nXCenter*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter , nZCenter+nSize , mRowIndex ,  mColIndex) , -(nZCenter+nSize)*theApp.m_Cell_ywidth-((mRowIndex-1)*theApp.m_Dem_BlockWidth));
	CracksPatchBottom(nXCenter-nSize/2 , nZCenter+nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
}

//節點裂縫修補(左側)
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
	SetTextureCoord(nXCenter-nSize , nZCenter ,  mRowIndex ,  mColIndex); //設置紋理坐標
	glVertex3i((nXCenter-nSize)*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter-nSize , nZCenter , mRowIndex ,  mColIndex) , -nZCenter*theApp.m_Cell_ywidth-((mRowIndex-1)*theApp.m_Dem_BlockWidth));
	
	CracksPatchLeft(nXCenter-nSize/2 , nZCenter-nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
	
}
//節點裂縫修補(右側)
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
	SetTextureCoord(nXCenter+nSize , nZCenter ,  mRowIndex ,  mColIndex); //設置紋理坐標
	glVertex3i((nXCenter+nSize)*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter+nSize , nZCenter , mRowIndex ,  mColIndex) , -nZCenter*theApp.m_Cell_ywidth-((mRowIndex-1)*theApp.m_Dem_BlockWidth));
	
	CracksPatchRight(nXCenter+nSize/2 , nZCenter+nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
}

//節點裂縫修補(頂部)
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
	SetTextureCoord(nXCenter , nZCenter-nSize ,  mRowIndex ,  mColIndex); //設置紋理坐標
	glVertex3i(nXCenter*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter , nZCenter-nSize , mRowIndex ,  mColIndex) , -(nZCenter-nSize)*theApp.m_Cell_ywidth-((mRowIndex-1)*theApp.m_Dem_BlockWidth));
	CracksPatchTop(nXCenter+nSize/2 , nZCenter-nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
}

//場景繪製
void CT3DSystemView::DrawScene()
{
	InitTerr();
    SetDrawMode() ; // 設置繪圖模式


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
	//	SetCamra(0) ; // 設置相機
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
			DrawClock();//繪製時鐘指北針
			DrawTerrain() ; // 三維地形繪製
			
		}
		
		if(m_QueryType==QUERY_COORDINATE || m_QueryType==QUERY_DISTENCE || m_QueryType==SELECTLINE)
			DrawSearchPoint() ; // 繪製空間查詢標誌
		

		if(m_ViewType==GIS_VIEW_ORTHO)	
		{
			DrawRailwaythesme_Ortho();
		}
		else if(m_ViewType==GIS_VIEW_PERSPECTIVE) 
		{
			DrawRailwaythesme();
		}
		DrawTerrainDelaunay();	//繪製經過線路建三維模後的三維Delaunay地形
		DrawFlyPath();//繪製飛行路徑

	}

}

//打開項目
void CT3DSystemView::OnMenuOpenproject() 
{
	COpenProject dlg;
	BeginWaitCursor() ; // 調用本函數顯示沙漏光標 , 告訴用戶系統忙
	if(dlg.DoModal()==IDOK)
	{
		theApp.bLoadImage=TRUE ; // 影像加載成功
		OnDraw (GetDC()) ; // 打開成功 , 繪製三維場景
	}
	EndWaitCursor();	//將光標切換為默認光標 , 結束等待
}

//從oracle數據庫表中讀取BLOB類型的影像紋理數據並寫入臨時影像紋理文件
BOOL CT3DSystemView::ExportBlobTextureToFIle(CString strFilename ,  int RowIndex ,  int ColIndex ,  int mID)
{
	CString tt;
	
	tt.Format("SELECT 紋理數據 FROM Texture WHERE 行號=%d AND 列號=%d AND 紋理金子塔層號=%d AND 編號= :%d FOR UPDATE" , RowIndex , ColIndex , m_currebtPhramid , mID);
	BOOL bt=myOci.ReadBOLBDataFromDB(strFilename , tt , mID) ; // 從數據庫中讀取BLOB數據
	return bt;
}

//設置繪圖模式
void CT3DSystemView::SetDrawMode()
{
	switch(m_Drawmode)//繪製模式 
	{
	case 1://線框模式
		glDisable(GL_TEXTURE_2D) ; // 關閉紋理功能
		glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
		break;
	case 2://渲暈模式
		glDisable(GL_TEXTURE_2D) ; // 開啟紋理功能
		glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
		break;
	case 3://紋理模式
		glEnable(GL_TEXTURE_2D) ; // 開啟紋理功能
		glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
		break;
	}

	
}


//線框模式
void CT3DSystemView::OnDrawmodeLine() 
{

	if(m_Drawmode!=1) 
	{
		b_haveMadeRail3DwayList=FALSE;
		b_haveMadeRail3DwayList_Ortho=FALSE;
	}
	
	m_Drawmode =1;
	OnDraw (GetDC()) ; // 打開成功 , 繪製三維場景
	
}

//渲暈模式
void CT3DSystemView::OnDrawmodeRender() 
{
	if(m_Drawmode!=2) 
	{
		b_haveMadeRail3DwayList=FALSE;
		b_haveMadeRail3DwayList_Ortho=FALSE;
	}
	m_Drawmode =2;
	OnDraw (GetDC()) ; // 打開成功 , 繪製三維場景
}

//紋理模式
void CT3DSystemView::OnDrawmodeTexture() 
{
	if(m_Drawmode!=3) 
	{
		b_haveMadeRail3DwayList=FALSE;
		b_haveMadeRail3DwayList_Ortho=FALSE;
	}
	m_Drawmode =3;
	OnDraw (GetDC()) ; // 打開成功 , 繪製三維場景
}

//繪製天空背景
void CT3DSystemView::DrawSky()
{
	
	glPushMatrix();
	SetSkyProjection() ; // 設置背景天空投影
	glCallList(m_SkyList);
	if(m_bShowbreviary==TRUE)  //如果顯示導航圖
	{
		SetSkyProjectionNavigate() ; // 設置導航圖的背景天空投影
		glCallList(m_SkyList); ; // 調用背景天空顯示列表
	}
	glPopMatrix();
	glViewport(0 ,  0 ,  WinViewX , WinViewY) ; // 重新設置視口大小
	
}

//背景天空投影設置
void CT3DSystemView::SetSkyProjection()
{
	glViewport(0 ,  0 ,  WinViewX , WinViewY) ; // 設置視口大小
	
    glMatrixMode( GL_PROJECTION ); //將當前矩陣設置為投影矩陣
    glLoadIdentity() ; // 將當前矩陣置換為單位陣  
	
    //設置正射投影視景體
	if (WinViewX <= WinViewY) 
		glOrtho (0.0f ,  1.0f ,  0.0f , 1.0f*(GLfloat)WinViewX/(GLfloat)WinViewY ,  -1.0f , 1.0f);
    else 
		glOrtho (0.0f , 1.0f*(GLfloat)WinViewY/(GLfloat)WinViewX ,  0.0f ,  1.0f ,  -1.0f ,  1.0f);
	
	glMatrixMode( GL_MODELVIEW ) ; // 將當前矩陣設置為模型矩陣	
	glLoadIdentity ();	//將當前矩陣置換為單位陣  
}

//背景天空導航圖投影設置
void CT3DSystemView::SetSkyProjectionNavigate()
{
	glViewport(WinViewX*5/6 ,  WinViewY*5/6 , WinViewX/6 ,  WinViewY/6) ; // 設置視口大小
	
    glMatrixMode( GL_PROJECTION ); //將當前矩陣設置為投影矩陣
    glLoadIdentity() ; // 將當前矩陣置換為單位陣  
	
	//設置正射投影視景體
    if (WinViewX <= WinViewY) 
		glOrtho (0.0f ,  1.0f ,  0.0f , 1.0f*(GLfloat)WinViewX/(GLfloat)WinViewY ,  -1.0f , 1.0f);
    else 
		glOrtho (0.0f , 1.0f*(GLfloat)WinViewY/(GLfloat)WinViewX ,  0.0f ,  1.0f ,  -1.0f ,  1.0f);
	
	glMatrixMode( GL_MODELVIEW ) ; // 將當前矩陣設置為模型矩陣	
	glLoadIdentity ();	//將當前矩陣置換為單位陣  
}

//生成繪製背景天空顯示列表
void CT3DSystemView::makeSkykList()
{
	glNewList(m_SkyList , GL_COMPILE);
		DrawBackground(); //繪製背景天空         
	glEndList();
}

//繪製背景天空    
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

//雙目立體顯示打開/關閉
void CT3DSystemView::OnMenuStereo() 
{
	if(m_stereo==TRUE)//如果是立體模式
		m_stereo=FALSE;//標誌為關閉
	else ////如果不是立體模式
	{
		m_stereo=TRUE;//標誌為打開
		
	}
	OnDraw (GetDC());//刷新三維場景
}

//設置"雙目立體模式"子菜單選中標誌
void CT3DSystemView::OnUpdateMenuStereo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(bStereoAvailable); //如果顯示不支持立體模式
	pCmdUI->SetCheck(m_stereo);//根據m_stereo值設置設置"雙目立體模式"子菜單選中標誌
	
}

//空間查詢標誌設置
void CT3DSystemView::OnSpacequerySet() 
{
	CSpaceSearchSet dlg;
	
	dlg.m_shizxLength=m_shizxLength ; // 查詢標誌十字線長度
	dlg.m_shuzxHeight=m_shuzxHeight ; // 查詢標誌豎直線高度
	dlg.m_QueryLineWidth=m_QueryLineWidth ; // 查詢標誌線的寬度
	dlg.m_QueryColorR=m_QueryColorR ; // 查詢標誌線的顏色(紅)
	dlg.m_QueryColorG=m_QueryColorG ; // 查詢標誌線的顏色(綠)
	dlg.m_QueryColorB=m_QueryColorB ; // 查詢標誌線的顏色(藍)
	if(dlg.DoModal()==IDOK) //如果對話框打開成功
	{
		m_shizxLength=dlg.m_shizxLength ; // 得到新設置的查詢標誌十字線長度
		m_shuzxHeight=dlg.m_shuzxHeight ; // 得到新設置的查詢標誌豎直線高度
		m_QueryLineWidth=dlg.m_QueryLineWidth ; // 得到新設置的查詢標誌線的寬度
		m_QueryColorR=dlg.m_QueryColorR ; // 得到新設置的查詢標誌線的顏色(紅)
		m_QueryColorG=dlg.m_QueryColorG ; // 得到新設置的查詢標誌線的顏色(綠)
		m_QueryColorB=dlg.m_QueryColorB ; // 得到新設置的//查詢標誌線的顏色(藍)
	}	
}


void CT3DSystemView::OnLButtonDown(UINT nFlags ,  CPoint point) 
{
	/**/
	if(m_ViewType==GIS_VIEW_ORTHO)	//如果是正射投影模式	
	{
		if(m_OrthoZommPan==ORTHO_ZOOMIN) //放大影像模式
			OnOrthoZoomIn(); 
		else if(m_OrthoZommPan==ORTHO_ZOOMOUT)//縮小影像模式
			OnOrthoZoomOut();
		else if(m_OrthoZommPan==ORTHO_PAN)//平移影像模式
		{
			m_preX=point.x;
			m_preY=point.y;
			OnOrthoPan();
		}
		else if(m_OrthoZommPan==ORTHO_ZOOMWINDOW) //開窗放大模式
		{
			if(m_pushNumb<=0) //
			{
				m_preX=point.x;//記錄鼠標第1點坐標
				m_preY=point.y;
				
				m_pushNumb=1;
				SetCapture();
			}
			else if(m_pushNumb==1)
			{
				m_currentX=point.x;//記錄鼠標第2點坐標
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


	if(m_QueryType==QUERY_COORDINATE)//空間三維坐標查詢
	{
		m_bmouseView=false;
		m_oldMousePos=point;
		ScreenToGL(point);
	}
	else if(m_QueryType==QUERY_DISTENCE)//空間距離查詢
	{
		m_bmouseView=false; // 關閉鼠標控相機旋轉
		m_oldMousePos=point;
		ScreenToGL(point);
	}	
	else if(m_QueryType==SELECTLINE)
	{
		m_bmouseView=false; // 關閉鼠標控相機旋轉
		m_oldMousePos=point;
		ScreenToGL(point); 
	}
	else if(m_QueryType==SELECTFLYPATH)//進行飛行路徑選擇
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

//查詢三維坐標
void CT3DSystemView::OnQueryCoordinate() 
{
	m_OrthoZommPan=-1;
	if(m_QueryType==QUERY_COORDINATE) //如果當前已經是查詢三維坐標狀態，則關閉
		m_QueryType=-1;
	else //如果當前已經不是查詢三維坐標狀態，則打開
		m_QueryType=QUERY_COORDINATE;
}

//設置是否選中狀態
void CT3DSystemView::OnUpdateQueryCoordinate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_QueryType==QUERY_COORDINATE);
	
}

//查詢空間距離
void CT3DSystemView::OnQueryDistence() 
{
	m_OrthoZommPan=-1;
	
	if(m_QueryType==QUERY_DISTENCE) //如果當前已經是查詢空間距離狀態，則關閉
		m_QueryType=-1;
	else // 如果當前不是查詢空間距離狀態，則關閉，則打開
		m_QueryType=QUERY_DISTENCE;
}

//設置是否選中狀態
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
		if(m_QueryType==QUERY_COORDINATE)//查詢三維坐標
		{
			if(m_ViewType==GIS_VIEW_ORTHO) //如果是正射投影模式
			{
				double mx=wx+m_ortho_CordinateOriginX; //計算x坐標
				double my=wy+m_ortho_CordinateOriginY; //計算y坐標
				mx=theApp.m_DemLeftDown_x+mx*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//轉換為大地坐標
				my=theApp.m_DemLeftDown_y+my*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//轉換為大地坐標
				wz=m_demInsert.GetHeightValue(mx,my,2);//從DEM中內插出對應的高程
				tt.Format("當前坐標(x,y,z)=(%.3f,%.3f,%.3f)",mx,my,wz);
			}
			else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//如果是透視投影模式
			{
				tt.Format("當前坐標(x,y,z)=(%.3f,%.3f,%.3f)",wx+theApp.m_DemLeftDown_x,-wz+theApp.m_DemLeftDown_y,wy);	
				
			}
			pt1[0]=wx;pt1[1]=wy;pt1[2]=wz; //查詢獲得的三維大地坐標
			OnDraw(GetWindowDC()); //刷新三維場景
			MessageBox(tt,"三維坐標查詢",MB_ICONINFORMATION); //給出坐標查詢信息
		}	
		else if(m_QueryType==QUERY_DISTENCE) // 查詢空間距離
		{
			if(	m_bSearchDistencePtNums>=2) // 如果選擇點數2個，歸零
				m_bSearchDistencePtNums=0;
			
			m_bSearchDistencePtNums++ ; //  選擇點數 + 1
			
			if(m_bSearchDistencePtNums==1) // 如果只選擇了1個點
			{
				pt1[0]=wx;pt1[1]=wy;pt1[2]=wz;	// 將三維點坐標存儲到數組 pt1[] 裡面
			}
			else	//選擇了兩個點，則表示可以計算空間距離了		 		
			{
				pt2[0]=wx;pt2[1]=wy;pt2[2]=wz; // 將三維點坐標存儲到數組 pt2[] 裡面

				double mdistence;
				
				if(m_ViewType==GIS_VIEW_ORTHO)	 //如果是正射投影模式
				{
					double nx1,ny1,nz1,nx2,ny2,nz2;
					nx1=pt1[0]+m_ortho_CordinateOriginX;//計算P1點x坐標
					nx1=theApp.m_DemLeftDown_x+nx1*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//將P1點x坐標轉換為大地坐標
					ny1=pt1[1]+m_ortho_CordinateOriginY;//計算P1點y坐標
					ny1=theApp.m_DemLeftDown_y+ny1*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//將P1點y坐標轉換為大地坐標
					nz1	=m_demInsert.GetHeightValue(nx1,ny1,2);//從DEM中內插出P1點對應的高程
					pt1[2]=nz1;
					
					nx2=pt2[0]+m_ortho_CordinateOriginX;//計算P2點x坐標
					nx2=theApp.m_DemLeftDown_x+nx2*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//將P2點x坐標轉換為大地坐標
					ny2=pt2[1]+m_ortho_CordinateOriginY;//計算P2點y坐標
					ny2=theApp.m_DemLeftDown_y+ny2*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//將P2點y坐標轉換為大地坐標
					nz2	=m_demInsert.GetHeightValue(nx2,ny2,2);//從DEM中內插出P2點對應的高程
					pt2[2]=nz2;
					
					//計算距離
					mdistence=sqrt((nx2-nx1)*(nx2-nx1)+(ny2-ny1)*(ny2-ny1)+(nz2-nz1)*(nz2-nz1));
					tt.Format("兩點為:\n(x1,y1,z1)=(%.3f,%.3f,%.3f)\n(x2,y2,z2)=(%.3f,%.3f,%.3f)\n距離Dis=%.3f",\
						nx1,ny1,nz1,nx2,ny2,nz2,mdistence);
					
				}
				else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//如果是透視投影模式
				{
					//計算距離
					mdistence=sqrt((pt2[0]-pt1[0])*(pt2[0]-pt1[0])+(pt2[1]-pt1[1])*(pt2[1]-pt1[1])+(pt2[2]-pt1[2])*(pt2[2]-pt1[2]));
					tt.Format("兩點為:\n(x1,y1,z1)=(%.3f,%.3f,%.3f)\n(x2,y2,z2)=(%.3f,%.3f,%.3f)\n距離Dis=%.3f",pt1[0]+theApp.m_DemLeftDown_x,-pt1[2]+theApp.m_DemLeftDown_y,pt1[1],pt2[0]+theApp.m_DemLeftDown_x,-pt2[2]+theApp.m_DemLeftDown_y,pt2[1],mdistence);
				}
				
				OnDraw(GetWindowDC());//刷新三維場景
				MessageBox(tt,"三維距離查詢",MB_ICONINFORMATION);//給出距離查詢信息

			}
		}
		else if(m_QueryType==SELECTLINE) //如果是三維選線設計
		{
			
			PCordinate ppt = new Cordinate;  //定義
			if( ppt == NULL )      //如果失敗 
			{  
				AfxMessageBox( "Failed to add a new ppt"); 
				return ;        
			}
			
			if(m_ViewType==GIS_VIEW_ORTHO)	//如果是正射投影模式	
			{
				double mx=wx+m_ortho_CordinateOriginX; //計算x坐標
				double my=wy+m_ortho_CordinateOriginY; //計算y坐標
				mx=theApp.m_DemLeftDown_x+mx*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//轉換為大地坐標
				my=theApp.m_DemLeftDown_y+my*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//轉換為大地坐標
				wz=m_demInsert.GetHeightValue(mx,my,2);//從DEM中內插出對應的高程
				mx-=theApp.m_DemLeftDown_x;
				my-=theApp.m_DemLeftDown_y;
				ppt->x=mx;ppt->y=wz;ppt->z=-my; //記錄轉換後的設計交點三維坐標				
			}
			else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//如果是透視投影模式
			{
				ppt->x=wx;ppt->y=wy;ppt->z=wz;  //記錄設計交點三維坐標	
			}
			
			
			m_oldlinePtnums=myDesingScheme.PtS_JD.GetSize();//當前線路方案原有設計交點數

			if(m_oldlinePtnums==0) //如果當前線路方案沒有設計交點,即還沒有進行該方案的設計
			{
				myDesingScheme.PtS_JD.Add(ppt); //加入設計交點到PtS_JD數組
				m_linePtnums=myDesingScheme.PtS_JD.GetSize();//當前線路方案原有設計交點數
				
				PLineCurve pTempCurveElements = new LineCurve; //定義新的交點變量
				//第一個設計交點
				
				//直緩里程=方案的起點里程   緩直里程=方案的起點里程
				pTempCurveElements->ZH=pTempCurveElements->HZ=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].StartLC;

				//緩圓里程=方案的起點里程   圓緩里程=方案的起點里程
				pTempCurveElements->HY=pTempCurveElements->YH=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].StartLC;
				
				//轉向角、切線長和曲線長=0
				pTempCurveElements->Alfa=pTempCurveElements->T=pTempCurveElements->L=0;
			
				//曲線半徑、旋轉類型、外矢量距=0
				pTempCurveElements->R=pTempCurveElements->RoateStyle=pTempCurveElements->E=0;
				
				//坡長、緩和曲線長、圓曲線長、夾直線長=0
				pTempCurveElements->P=pTempCurveElements->L0=pTempCurveElements->Ly=pTempCurveElements->Jzxc=0;

				//交點里程=方案的起點里程
				pTempCurveElements->JDLC=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].StartLC;

				//交點ID="JD0";
				pTempCurveElements->ID="JD0";

				pTempCurveElements->x=myDesingScheme.PtS_JD.GetAt(0)->x;			//交點的x坐標				
				pTempCurveElements->y=fabs(myDesingScheme.PtS_JD.GetAt(0)->z);		//交點的yx坐標				
				pTempCurveElements->z=-myDesingScheme.PtS_JD.GetAt(0)->y;			//交點的z坐標

				//加入交點元素到DCurveElementss模板數組中
				myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].Add(pTempCurveElements); 
			}
			else  //如果當前線路方案設計交點數>0,表示已經進行該方案的設計
			{
				CPLaneRL0 dlg; 
				if(m_linePtnums<=0)
					m_linePtnums=myDesingScheme.PtS_JD.GetSize();
				tt.Format("JD%d",m_linePtnums); //交點ID自動增加
				
				dlg.m_ID=tt; //交點ID
				if(dlg.DoModal()==IDOK) //如果交點信息設計成功
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
		else if(m_QueryType==SELECTFLYPATH) // 如果是設置飛行路徑
		{
			PCordinate ppt = new Cordinate;  
			if(m_ViewType==GIS_VIEW_ORTHO)	//如果是正射投影模式	
			{
				double mx=wx+m_ortho_CordinateOriginX;//計算x坐標
				double my=wy+m_ortho_CordinateOriginY;//計算y坐標
				mx=theApp.m_DemLeftDown_x+mx*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//轉換為大地坐標
				my=theApp.m_DemLeftDown_y+my*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//轉換為大地坐標
				wz=m_demInsert.GetHeightValue(mx,my,2);//從DEM中內插出對應的高程
				mx-=theApp.m_DemLeftDown_x; //x坐標變換
				my-=theApp.m_DemLeftDown_y;//y坐標變換
				ppt->x=mx;ppt->y=wz;ppt->z=-my; //記錄飛行路徑的三維坐標
			}
			else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//如果是透視投影模式
			{
				ppt->x=wx;ppt->y=wy;ppt->z=wz;//記錄飛行路徑的三維坐標
			}
			
			m_FlayPath.Add(ppt); //將飛行路徑的三維坐標存儲到數組m_FlayPath
			OnDraw(GetDC()); //刷新三維場景,用來顯示繪製的飛行路徑
		}
	}
	else
	{
		MessageBox("鼠標選擇點不夠精確 , 請精確選擇點!");
		m_bSearchDistencePtNums=0;
	}
}

//繪製空間查詢標誌
void CT3DSystemView::DrawSearchPoint()
{
 
    glViewport(0 ,  0 ,  WinViewX ,  WinViewY) ; // 重新設置視口大小
	if(m_QueryType==QUERY_COORDINATE) //三維空間坐標查詢
	{
		if(pt1[0]!=-99999)
		{
			glLineWidth(m_QueryLineWidth) ; // 設置查詢標誌線寬度
			glColor3f(m_QueryColorR/255.0 , m_QueryColorG/255.0 , m_QueryColorB/255.0) ; // 設置查詢標誌線顏色
			//繪製十字型查詢標誌線
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
	else if(m_QueryType==QUERY_DISTENCE && m_bSearchDistencePtNums==2)//三維空間距離查詢(在選擇兩個空間點之後才能夠計算空間距離)
	{
		glLineWidth(m_QueryLineWidth) ; // 設置查詢標誌線寬度
		glColor3f(m_QueryColorR/255.0 , m_QueryColorG/255.0 , m_QueryColorB/255.0) ; // 設置查詢標誌線顏色
		
		//繪製十字型查詢標誌線
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
	else if(m_QueryType==SELECTLINE ||myDesingScheme.PtS_JD.GetSize()>0 )//如果當前已經三維選線狀態
	{
		//繪製選結過程中的設計交點連線
		m_oldlinePtnums=m_linePtnums;
		glColor3f(0,0,1);
		glLineWidth(2.0);
	
		
		if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//如果是透視投影模式
		{
			for (int i=0;i<myDesingScheme.PtS_JD.GetSize()-1;i++)
			{
				DrawCenterLine(i,TRUE,m_currentSchemeIndexs); //繪製線路中心線
			}
		}
		else if(m_ViewType==GIS_VIEW_ORTHO)		//如果是正射投影模式
		{
			
			for (int i=0;i<myDesingScheme.PtS_JD.GetSize()-1;i++)
			{
				DrawCenterLine(i,TRUE,m_currentSchemeIndexs);//繪製線路中心線
			}
		}
	}

}



//響應鼠標移到函數
void CT3DSystemView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(theApp.bLoginSucceed==FALSE) //保證未打開項目的情況下,不需要響應鼠標移到消息
		return ; //返回
	
	if(m_bmouseView==TRUE) //如果鼠標控制場景打開時
	{
		mCamraUpdate(); //根據鼠標和鍵盤實現三維場景相機的移動和旋轉控制
		OnDraw (GetDC()); //刷新三維場景
		
	}
	CView::OnMouseMove(nFlags, point);
}

//根據鼠標和鍵盤實現三維場景相機的移動和旋轉控制
void CT3DSystemView::mCamraUpdate()
{
	CVector3 vCross = CrossProduct(m_vView - m_vPosition, m_vUpVector); //叉積計算
	m_vStrafe = Normalize(vCross); //vCross歸一化
	SetViewByMouse(); //通過鼠標實現相機控制
	CheckForMovement();//通過鍵盤實現相機控制
	m_vPosition.y+=(m_viewHeight-m_oldviewHeight); //新的相機視點y坐標
	m_oldviewHeight=m_viewHeight; //記錄當前相機視點高度
}

//通過鼠標實現相機控制
void CT3DSystemView::SetViewByMouse()
{
	if(m_bmouseView==false) //如果鼠標控制場景關閉時,返回
		return;
 
	float angleY = 0.0f;							
	float angleZ = 0.0f;							
	static float currentRotX = 0.0f;
	
	POINT mousePos;									
	GetCursorPos(&mousePos);//得到光標的位置，以屏幕坐標表示,存儲到	mousePos變量裡			
	
	//如果鼠標坐標沒有變化,返回
	if( (mousePos.x == m_oldMousePos.x) && (mousePos.y == m_oldMousePos.y) )
		return;
	
   /* 對鼠標y坐標前後之差進行縮小(這裡縮小500倍,這個值可根據實際地形設置),如果angleY值
	太大,表示即使鼠標y坐標前後之差很小,也會導致三維地形場景在Y方向上變化很大*/
	angleY = (float)( (m_oldMousePos.x - mousePos.x) ) / 500.0f;

	/* 對鼠標z坐標前後之差進行縮小(這裡縮小4000倍,這個值可根據實際地形設置),如果angleZ值
	太大,表示即使鼠標z坐標前後之差很小,也會導致三維地形場景在Z方向上變化很大*/
	angleZ = (float)( (m_oldMousePos.y - mousePos.y) ) / 4000.0f;
	
	currentRotX -= angleZ;  
	
	CVector3 vAxis = CrossProduct(m_vView - m_vPosition, m_vUpVector); //叉積計算
	vAxis = Normalize(vAxis);	//vAxis歸一化
	
	RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);//通過鼠標控制相機的旋轉(旋轉視角)
	RotateView(angleY, 0, 1, 0);//通過鼠標控制相機的旋轉(旋轉視角)

	m_oldMousePos.x=mousePos.x;		//記錄當前鼠標x坐標
	m_oldMousePos.y=mousePos.y;		//記錄當前鼠標y坐標
		
}

//通過鼠標控制相機的旋轉(旋轉視角)
void CT3DSystemView::RotateView(float angle, float x, float y, float z)
{
	CVector3 vNewView;
	
	CVector3 vView = m_vView - m_vPosition;	//相機視點與觀察點三維坐標差值	
	
	float cosTheta = (float)cos(angle); //得到旋轉視角的cos函數值
	float sinTheta = (float)sin(angle);//得到旋轉視角的sin函數值
	
	vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)		* vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;
	
	vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)		* vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;
	
	vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)		* vView.z;
	
	m_vView = m_vPosition + vNewView; //得到旋轉後的相機視點坐標

	GetNorthPtangle(); //計算時鐘指北針指向角度
}

//在Z軸方向上移動時設置相機觀察點和視點坐標
void CT3DSystemView::MoveCamera(float speed)
{
	CVector3 vVector = m_vView - m_vPosition;//相機視點與觀察點三維坐標差值
	vVector = Normalize(vVector); //相機視點與觀察點三維坐標差值歸一化
	m_vPosition.x += vVector.x * speed;	//相機視點x新坐標	
	m_vPosition.z += vVector.z * speed;	//相機視點z新坐標	
	m_vView.x += vVector.x * speed;		//相機觀察點x新坐標
	m_vView.z += vVector.z * speed;		//相機觀察點z新坐標
}

//根據鍵盤按鍵值來重新設置相機
void CT3DSystemView::CheckForMovement()
{
	if(m_keynumber ==1)	// ↑上箭頭按鍵，向場景外移動(Z軸正方向)
	{		
		MoveCamera(m_Step_Z); //在Z軸方向上移動時設置相機觀察點和視點坐標
	}
	
	if(m_keynumber ==2) 	// ↓下箭頭按鍵，向場景外移動(Z軸負方向)
	{
		MoveCamera(-m_Step_Z);	//在Z軸方向上移動時設置相機觀察點和視點坐標
	}
	
	if(m_keynumber ==3)	// ←左箭頭按鍵，向左方向移動場景(X軸負方向)
	{
		StrafeCamera(-m_Step_X);	//在X軸方向上移動時設置相機觀察點和視點坐標
	}

	if(m_keynumber ==4)	// →右箭頭按鍵，向右方向移動場景(X軸正方向)
	{
		StrafeCamera(m_Step_X);	//在X軸方向上移動時設置相機觀察點和視點坐標
	}

	Derx=m_vPosition.x-m_oldvPosition.x;//相機視點在X方向上的變化量差值
	Derz=m_vPosition.z-m_oldvPosition.z;//相機視點在Z方向上的變化量差值
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	
	//如果相機視點在X方向上或Z方向上的變化量差值>=DEM地形子塊的總寬度時,調入新的地形塊
	if(fabs(Derz)>=theApp.m_Dem_BlockWidth || fabs(Derx)>=theApp.m_Dem_BlockWidth)
	{
		if(m_loddem_StartRow!=1 && m_loddem_StartCol!=1 \
			&& m_loddem_EndRow!=theApp.m_BlockRows && m_loddem_EndCol!=theApp.m_BlockCols)
		{
// 			LoadNewData();
		}
	}
}

//在X軸方向上移動時設置相機觀察點和視點坐標
void CT3DSystemView::StrafeCamera(float speed)
{
	m_vPosition.x += m_vStrafe.x * speed;	//相機視點x新坐標
	m_vPosition.z += m_vStrafe.z * speed;	//相機視點z新坐標
	m_vView.x += m_vStrafe.x * speed;	//相機觀察點x新坐標
	m_vView.z += m_vStrafe.z * speed;	//相機觀察點z新坐標
}

//鍵盤按下響應函數
void CT3DSystemView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  m_keynumber=0;

   switch (nChar) //根據按鍵字符來進行相應設置
   {
   case VK_LEFT:  
	   m_keynumber=3;
	   m_xTrans-=m_Step_X;	//在X方向上移動的距離累計
	   OnDraw (GetDC());	//刷新三維場景
	   break;
   case VK_RIGHT:
	   m_keynumber=4;
	   m_xTrans+=m_Step_X;	//在X方向上移動的距離累計
	   OnDraw (GetDC());	//刷新三維場景
	   break;
   case VK_UP:
		m_zTrans -= m_Step_Z;	//在Z方向上移動的距離累計
	    m_keynumber=1;
	   OnDraw (GetDC());	//刷新三維場景
	   break;
   case VK_DOWN:
		m_zTrans += m_Step_Z;	//在Z方向上移動的距離累計
		m_keynumber=2;
	   OnDraw (GetDC());	//刷新三維場景
	   break;
	case 'F':     
		m_ViewWideNarrow += 1.0;	//飛行視野增大,看見場景範圍增大了,相當於相機鏡頭向屏幕外方向移動	
		OnDraw (GetDC());//刷新三維場景
		break;
	case 'V':     
		m_ViewWideNarrow -= 1.0;    //飛行視野減小,看見場景範圍減小了,相當於相機鏡頭向屏幕裡方向移動
		OnDraw (GetDC());//刷新三維場景
		break;
	case 'H':     					   //視角下傾
		m_ViewUpDown -= 0.2;
		OnDraw (GetDC());//刷新三維場景
		break;
	case 'N':     					   //視角上傾
		m_ViewUpDown += 0.2;
		OnDraw (GetDC());//刷新三維場景
		break;
	case 'J':     					   //加速
		m_flyspeed -= 1;
		if(m_flyspeed<=1)
			m_flyspeed=1;
		SetFLyTimer();//設置飛行計時器
		break;
	case 'M':     					   //減速
		m_flyspeed += 1;
		SetFLyTimer();//設置飛行計時器
		break;
	case 'G':     
		m_StaticHeight=m_StaticHeight*1.1;
		OnDraw (GetDC());//刷新三維場景
		break;
	case 'B':     
		m_StaticHeight=m_StaticHeight/1.1; //減少固定飛行高度
		OnDraw (GetDC());//刷新三維場景
		break;
	case VK_F2:								 //顯示漫遊熱鍵幫助
		DisplayHelp();					   
		break;
	case 'Z':								//沿方案線漫遊
		OnFlyRoutinschemeline();					   
		break;
	case 'S':								//停止飛行
		OnFlyStop();					   
		break;
	case 'P':								//開始/暫停飛行
		OnFlyPlaypause();					   
		break;
   }
	mCamraUpdate();	//重新調整相機
	m_keynumber=0; //恢復按鍵0值

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//按下鼠標右鍵響應函數
void CT3DSystemView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_QueryType=-1;//關閉三維空間查詢,選線設計、飛行路徑設置

	m_bmouseView=FALSE; //關閉鼠標控相機旋轉
	m_OrthoZommPan=-1;	//關閉正射投影模式下場景控制
	
	CView::OnRButtonDown(nFlags, point);
}


//菜單"正射投影模式"響應函數
void CT3DSystemView::OnMenuProjecttionortho() 
{
 	m_stereo=FALSE; //關閉
	m_ViewType =GIS_VIEW_ORTHO; //正射投影模式
	SetProjection(); //重新設置
	OnDraw (GetDC());	//刷新三維場景
}

//"正射投影模式"設置/取消選中標誌
void CT3DSystemView::OnUpdateMenuProjecttionortho(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ViewType ==GIS_VIEW_ORTHO);//根據m_ViewType值是否設置選中標誌
	
}

void CT3DSystemView::OnMenuPerspective() 
{
	m_ViewType =GIS_VIEW_PERSPECTIVE;
	SetProjection();//重新設置
	OnDraw (GetDC());	//刷新三維場景
	
}

//"透視投影模式"設置/取消選中標誌
void CT3DSystemView::OnUpdateMenuPerspective(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ViewType ==GIS_VIEW_PERSPECTIVE);//根據m_ViewType值是否設置選中標誌
		pCmdUI->Enable(TRUE);
}


//根據投影模式的不同,重新設置投影參數
void CT3DSystemView::SetProjection()
{
	glViewport(0, 0, WinViewX, WinViewY);//設置視口大小
    glMatrixMode(GL_PROJECTION);//將當前矩陣設置為投影矩陣
    glLoadIdentity();//將當前矩陣置換為單位陣
	
	if(m_ViewType==GIS_VIEW_ORTHO)	//如果投影模式為正射投影模式	
	{
		float MS=0.6; //初始正射投影窗口大小,這個值可根據地形範圍自行調整
		if (WinViewX <= WinViewY) 
		{
			//設置正射投影視體
			glOrtho (-MS, MS, -MS*(GLfloat)WinViewY/(GLfloat)WinViewX, 
				MS*(GLfloat)WinViewY/(GLfloat)WinViewX, -1,1);
			
			m_ViewXYscale=(GLfloat)WinViewY/(GLfloat)WinViewX;//存儲視口寬高比例
		}
		else 
		{
			//設置正射投影視體
			glOrtho (-MS*(GLfloat)WinViewX/(GLfloat)WinViewY, 
				MS*(GLfloat)WinViewX/(GLfloat)WinViewY, -MS, MS, -1, 1);
			
			m_ViewXYscale=(GLfloat)WinViewX/(GLfloat)WinViewY;//存儲視口寬高比例
		}
	}
	else if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//如果投影模式為透視投影模式
	{
		//設置透視投影視體
		gluPerspective(50.0 + m_ViewWideNarrow , m_aspectRatio , m_near , m_far);	
	}

	glMatrixMode(GL_MODELVIEW); //將當前矩陣設置為模型矩陣		
	glLoadIdentity();   //將當前矩陣置換為單位陣       
	
}

//繪製正射投影栻上的三維地形
void CT3DSystemView::DrawTerrain_ORTHO()
{
	if(theApp.bLoginSucceed==FALSE || m_bLoadInitDemData==FALSE)
		return;
		

	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_TEXTURE_2D) ; // 關閉2D紋理映射功能
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // 選擇TEXTURE0為設置目標
	glEnable(GL_TEXTURE_2D) ; // 激活TEXTURE0單元
	
	glActiveTextureARB(GL_TEXTURE1_ARB) ; // 選擇TEXTURE1為設置目標
	glEnable(GL_TEXTURE_2D) ; // 激活TEXTURE1單元 , 啟用2D紋理映射
	glTexEnvi(GL_TEXTURE_ENV ,  GL_TEXTURE_ENV_MODE ,  GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV ,  GL_RGB_SCALE_ARB ,  2);
	glMatrixMode(GL_TEXTURE); //定義矩陣為模型紋理矩陣
	glLoadIdentity() ; // 將當前矩陣置換為單位矩陣
	glDisable(GL_TEXTURE_2D) ; // 關閉紋理功能
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // 選擇TEXTURE0為設置目標
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
	
	glTranslatef(m_OrthotranslateX,m_OrthotranslateY,0);//移動

	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		
	int nCount=0;
		
	for(int j=0;j<m_LodDemblockNumber;j++)
	{
		memset(m_pbQuadMat[j],0,m_nMapSize*m_nMapSize);
	}

	//新建顯示列表
	 glNewList(m_TerrainList,GL_COMPILE_AND_EXECUTE);

	 m_RenderDemblockNumber=0;
	 glColor3f(1,0,1);
	 for(int i=0;i<m_LodDemblockNumber;i++)
	 {
		   mCurrentTextID=i;
			m_CurrentDemArrayIndex=i;
			glBindTexture(GL_TEXTURE_2D, m_demTextureID[i]);//綁定紋理
			m_lodDemBlock[i][3]=0;
			m_RenderDemblockNumber++;
			m_lodDemBlock[i][3]=1;
			DrawBlockOrtho(i); //繪製地形塊
	}

	glEndList();
	  
		
	CString strText;
	strText.Format("【內存/渲染塊數】=%d/%d",m_LodDemblockNumber,m_RenderDemblockNumber);
		pMainFrame->Set_BarText(0,strText,0); 

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);
	
	glActiveTextureARB(GL_TEXTURE0_ARB);		
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

//繪製正射投影模式下地形塊
void CT3DSystemView::DrawBlockOrtho(int DemBlockIndex)
{
	float mcolorR,mcolorG;
	
	//地形塊中心x,y坐標
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
	//最高紅色 255,0,0  最低綠色 0,255,0
	//Dr=255 DG=-255 DB=0
	*mColorR=(mz-m_minHeight)/(m_maxHeight-m_minHeight);
	*mColorG=1-(mz-m_minHeight)/(m_maxHeight-m_minHeight);
}

//放大影像
void CT3DSystemView::OnOrthoZoomIn() 
{
	m_OrthoZommPan=ORTHO_ZOOMIN;
	m_OrthoViewSize=m_OrthoViewSize/1.1;
	
	OnDraw(GetDC());
	
}
//縮小影像
void CT3DSystemView::OnOrthoZoomOut() 
{
	m_OrthoZommPan=ORTHO_ZOOMOUT;
	m_OrthoViewSize=m_OrthoViewSize*1.1;
	OnDraw(GetDC()); //刷新三維場景
	
}

//移動影像
void CT3DSystemView::OnOrthoPan() 
{
	m_OrthoZommPan=ORTHO_PAN;
	OnDraw(GetDC());//刷新三維場景
				
}

//恢復初始大小
void CT3DSystemView::OnOrthoZoomOrigin() 
{
	m_OrthoZommPan=ORTHO_ZOOMORIGIN;
	m_OrthoViewSize=0.3;
	OnDraw(GetDC());//刷新三維場景
	
}

//開窗縮放
void CT3DSystemView::OnOrthoZoomWindow() 
{
	m_OrthoZommPan=ORTHO_ZOOMWINDOW;
	OnDraw(GetDC());//刷新三維場景
	
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

//響應鼠標左鍵抬起消息
void CT3DSystemView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bmouseView=false; //關閉鼠標旋轉相機功能
	
	//如果是正射投影模式並且是移動控制模式下
	if(m_ViewType==GIS_VIEW_ORTHO && m_OrthoZommPan==ORTHO_PAN)	
	{
		int dx=point.x-m_preX;//在X方向移動距離 
		int dy=point.y-m_preY;//在Y方向移動距離
		m_OrthotranslateX+=dx*0.00007;//X距離變換到正射投影模式的移動值
		m_OrthotranslateY+=-dy*0.00007;//Y距離變換到正射投影模式的移動值
		OnDraw (GetDC());//刷新三維場景
	}
	
	CView::OnLButtonUp(nFlags, point);
}

//三維選線設計
void CT3DSystemView::OnMenuLinedesign() 
{
	m_OrthoZommPan=-1;
	
	if(m_QueryType==SELECTLINE) //如果當前已經三維選線狀態，則關閉
		m_QueryType=-1;
	else // //如果當前不是三維選線狀態，則打開
		m_QueryType=SELECTLINE;
}

//設置選中狀態
void CT3DSystemView::OnUpdateMenuLinedesign(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_QueryType==SELECTLINE);
}


//繪製正射投影模式下的三維線路
void CT3DSystemView::DrawRailwaythesme_Ortho()
{
	CString tt,strSql,m_style;
// 	long i;

	//如果數據庫沒有加載成功或調入數據失敗，返回
	if(theApp.bLoginSucceed==FALSE || m_bLoadInitDemData==FALSE)
		return;
	
	glLineWidth(4.0);//設置線寬
	SetDrawMode();//設置繪圖模式

	glViewport(0, 0, WinViewX, WinViewY);//重新設置視口大小
	
	if(b_haveMadeRail3DwayList_Ortho==FALSE )   //如果還沒有構建線路三維模型的顯示列表
	{

		ReLoadCenterPt();//重新從數據庫中讀取線路中線坐標點數據
		
		glNewList(m_Rail3DwayList_Ortho,GL_COMPILE_AND_EXECUTE);//創建顯示列表
				
			glColor3f(0.75,0.75,0.75);//設置顏色
			glLineWidth(1.0);//設置線寬
		
				//1. 繪製左側路基邊坡
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());//綁定路基邊坡紋理
				for (long i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
				{
					m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
					if(m_style!="隧道起點" && m_style!="隧道中間點" &&m_style!="隧道終點" &&m_style!="橋樑起點"  &&m_style!="橋樑中間點" &&m_style!="橋樑終點")
					{	
						DrawBP_Ortho(i,1);//繪製左側路基邊坡
					}
					
				}
		
				//4.繪製右側路基邊坡
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());//綁定路基邊坡紋理
				
				for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
				{
					m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//交點類型
					//如果交點類型是非隧道和橋樑段的點，則繪製路基邊坡		
					
					if(m_style!="隧道起點" && m_style!="隧道中間點" &&m_style!="隧道終點" &&m_style!="橋樑起點"  &&m_style!="橋樑中間點" &&m_style!="橋樑終點")
					{
				
					    glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());//綁定路基邊坡紋理
						DrawBP_Ortho(i,2);//繪製右側路基邊坡
						glBindTexture(GL_TEXTURE_2D, m_cTxtureSuigou.GetTxtID());//綁定水溝紋理
						DrawSuiGou_Ortho(i);//繪製水溝
						
					}
				}
		

		//5.繪製中心線		
		
		m_TempPts.RemoveAll();
		PCordinate pt;
		glLineWidth(8.0);
		glColor3f(1,0,1);


		for (i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			
			//如果未進行線路三維建模，則調用DrawCenterLine()函數繪製線路中線
			if(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()<=0)
				DrawCenterLine(i,FALSE,m_currentSchemeIndexs);//繪製線路中線
			else
			{
			
				tt=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;

				if(tt!="隧道中間點" && i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x;
					pt->y=-myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z; 
					pt->strJDStyle=tt;
					m_TempPts.Add(pt);
				}
				else //隧道部分的線路位於地面以下，不繪製
				{		
					if(m_TempPts.GetSize()>1)
					{	
				
						glBegin(GL_LINE_STRIP);

						for(int k=0;k<m_TempPts.GetSize();k++)
						{
							tt=m_TempPts.GetAt(k)->strJDStyle;
							if(tt=="交點坐標" || tt=="直緩點坐標" || tt=="緩直點坐標" || tt=="交點-直緩點坐標")
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


		//6.繪製軌道
		glBindTexture(GL_TEXTURE_2D, m_cTxtureRailway.GetTxtID());//綁定軌道紋理
		glColor3f(0.5,0,0.4);//設置顏色
		glLineWidth(2.0);//設置線寬
		
		CString tt1,tt2;
		for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			tt1=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//當前交點類型
			tt2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;//下一交點類型
			if(tt1!="隧道中間點"  &&  tt2!="隧道中間點")
			{
				//以矩形方式連接前後相臨軌道斷面
				glBegin(GL_POLYGON);
				glTexCoord2f(0.0f,0.0f);//設置紋理坐標(當前軌道斷面左側點)
				glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1),\
					GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1));
				
				glTexCoord2f(1.0f,0.0f); //設置紋理坐標(當前軌道斷面右側點)
				glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2),\
					GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2));
				
				glTexCoord2f(1.0f,1.0f);//設置紋理坐標(下一前軌道斷面右側點)
				glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
					GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
				
				glTexCoord2f(0.0f,1.0f);//設置紋理坐標(下一前軌道斷面左側點)
				glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
					GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
				
				glEnd();
			}
		
		}		


		//7.繪製道床邊坡
		glBindTexture(GL_TEXTURE_2D, m_cTxtureGdToLJ.GetTxtID());//綁定道床邊坡紋理		
		glColor3f(1,1,0);//設置顏
		for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			tt1=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//當前交點類型
			tt2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;//下一交點類型
			if(tt1!="隧道中間點"  &&  tt2!="隧道中間點")
			{
				
			//以矩形方式連接方式繪製左側道床邊坡
			glBegin(GL_POLYGON);
			glTexCoord2f(1.0f,0.0f);//設置紋理坐標(當前左側道床邊坡左側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1),\
				GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1));
			
			glTexCoord2f(1.0f,1.0f);//設置紋理坐標(當前左側道床邊坡右側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
				GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
			
			glTexCoord2f(0.0f,1.0f);//設置紋理坐標(下一左側道床邊坡右側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
			
			glTexCoord2f(0.0f,0.0f);//設置紋理坐標(下一左側道床邊坡左側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1));			
			glEnd();
			
			//以矩形方式連接方式繪製右側道床邊坡
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//設置紋理坐標(當前右側道床邊坡左側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2),\
				GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2));
			
			glTexCoord2f(0.0f,1.0f);//設置紋理坐標(當前右側道床邊坡右側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
				GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
			
			glTexCoord2f(1.0f,1.0f);//設置紋理坐標(下一右側道床邊坡右側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
			
			glTexCoord2f(1.0f,0.0f);//設置紋理坐標(下一右側道床邊坡左側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2));
			
			glEnd();
			}
		}		
		


		//8.繪製路肩
		glBindTexture(GL_TEXTURE_2D, m_cTxtureLJ.GetTxtID());//綁定路肩紋理
		glColor3f(1,0.5,0.25);//設置顏色
		for (i=0;i<myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			tt1=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//當前交點類型
			tt2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;//下一交點類型
			if(tt1!="隧道中間點"  &&  tt2!="隧道中間點")
			{
				
			//以矩形方式連接方式繪製左側路肩
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//設置紋理坐標(當前左側路肩斷面左側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1));
			
			glTexCoord2f(0.0f,1.0f);//設置紋理坐標(當前左側路肩斷面右側點)	
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
			
			glTexCoord2f(1.0f,1.0f);;//設置紋理坐標(下一左側路肩斷面右側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
			
			glTexCoord2f(1.0f,0.0f);//設置紋理坐標(下一左側路肩斷面左側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1));
						
			glEnd();
			
			//以矩形方式連接方式繪製右側路肩
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//設置紋理坐標(當前右側路肩斷面左側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2));
			
			
			glTexCoord2f(1.0f,0.0f);//設置紋理坐標(當前右側路肩斷面右側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2));
			
			glTexCoord2f(1.0f,1.0f);//設置紋理坐標(下一右側路肩斷面右側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
			
			glTexCoord2f(0.0f,1.0f);//設置紋理坐標(下一右側路肩斷面左側點)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
			
			glEnd();
			}
		}		

		glLineWidth(1.0);//恢復線寬
		glEndList();//結束顯示列表
		b_haveMadeRail3DwayList_Ortho=TRUE;//標識已經創建顯示列表
	}
	else  //如果已經構建線路三維模型的顯示列表,則直接調用顯示列表
	{ 
		glCallList(m_Rail3DwayList_Ortho); //調用線路三維模型顯示列表
	}
	

}

//繪製中心線
//位於地面以下的部分不繪製
void CT3DSystemView::DrawCenterLine(long index, BOOL ifSelectLine, int SchemeIndex)
{
	CString tt;
	double x1,y1,z1,x2,y2,z2;
	double x0,y0,z0;
	float DerDistence=2.0;

	float Dh;
	
	m_TempPts.RemoveAll();
	
	if(ifSelectLine==TRUE) //在選線設計
	{
		Dh=5;
		x1=myDesingScheme.PtS_JD.GetAt(index)->x;
		y1=myDesingScheme.PtS_JD.GetAt(index)->y;
		z1=myDesingScheme.PtS_JD.GetAt(index)->z;
		
		x2=myDesingScheme.PtS_JD.GetAt(index+1)->x;
		y2=myDesingScheme.PtS_JD.GetAt(index+1)->y;
		z2=myDesingScheme.PtS_JD.GetAt(index+1)->z;
	}
	else  //打開項目時,繪製打開的方案
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
	if(m_ViewType==GIS_VIEW_ORTHO) //如果是正射投影模式
	{		
		while(L0<=L)
		{
			
			x0=x1+L0/L*(x2-x1);
			y0=y1+L0/L*(y2-y1);//高計線高程
			z0=z1+L0/L*(z2-z1);

			//地面高程
			float dmh=m_demInsert.GetHeightValue(x0+theApp.m_DemLeftDown_x,-z0+theApp.m_DemLeftDown_y,2);
			if(y0>=dmh-Dh) //設計線點高程大於地面高程
			{
				pt=new Cordinate;
				pt->x =x0;
				pt->y=y0;
				pt->z =z0;
				m_TempPts.Add(pt);
			}
			else
			{
				if(m_TempPts.GetSize()>1) //臨時點數大於1
				{	
					
					glBegin(GL_LINE_STRIP); //以折線形式繪製
					
					for(int k=0;k<m_TempPts.GetSize();k++)
					{
						glVertex2f(GetOrthoX(m_TempPts.GetAt(k)->x),GetOrthoY(-m_TempPts.GetAt(k)->z));
					}
					glEnd();
					m_TempPts.RemoveAll(); //清空
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
				if(y0>=dmh-Dh ) //設計線點高程大於地面高程
				{
					pt=new Cordinate;
					pt->x =x0;
					pt->y=y0;
					pt->z =z0;
					m_TempPts.Add(pt);
					if(m_TempPts.GetSize()>1)
					{	
						
						glBegin(GL_LINE_STRIP); //以折線形式繪製
						
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
		if(m_TempPts.GetSize()>1)//臨時點數大於1
		{	
			
			glBegin(GL_LINE_STRIP);  //以折線形式繪製
			
			for(int k=0;k<m_TempPts.GetSize();k++)
			{
				glVertex2f(GetOrthoX(m_TempPts.GetAt(k)->x),GetOrthoY(-m_TempPts.GetAt(k)->z));
			}
			glEnd();
			m_TempPts.RemoveAll();
		}
	}
	else if (m_ViewType==GIS_VIEW_PERSPECTIVE) //如果是透視投影模式
	{
		while(L0<=L)
		{
			
			x0=x1+L0/L*(x2-x1);
			y0=y1+L0/L*(y2-y1);//計線高程
			z0=z1+L0/L*(z2-z1);
			
			//地面高程
			float dmh=m_demInsert.GetHeightValue(x0+theApp.m_DemLeftDown_x,-z0+theApp.m_DemLeftDown_y,2);
			if(y0>=dmh-Dh)  //設計線點高程大於地面高程
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
				if(y0>=dmh-Dh )//設計線點高程大於地面高程
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

//計算正射投影模式下x坐標
float CT3DSystemView::GetOrthoX(double x)
{
	float xt=x/(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x)-m_ortho_CordinateOriginX;
	return xt;
	
}

//計算正射投影模式下y坐標
float CT3DSystemView::GetOrthoY(double y)
{
	float yt=y/(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)*m_ortho_CordinateXYScale-m_ortho_CordinateOriginY;
	return yt;
	
}

//保存設計方案
void CT3DSystemView::OnMenuLinesavescheme() 
{
	int manswer=MessageBox("是否確認保存方案?","保存方案",MB_ICONQUESTION|MB_YESNO);
	if(manswer==7)
		return;
	
	b_haveMadeRail3DwayList=FALSE;
	b_haveMadeRail3DwayList_Ortho=FALSE;
	if(myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].GetSize()>0)
	{
		myDesingScheme.m_bHaveSaveScheme=TRUE;
		myDesingScheme.SavePlaneCurveData();//保存曲線要素到數據庫中	
	}	
	
}


//實現透視投影模式下的線路三維模型繪製
void CT3DSystemView::DrawRailwaythesme()
{

	//壓入屬性堆棧
	glPushAttrib(GL_DEPTH_BUFFER_BIT|GL_ENABLE_BIT|GL_POLYGON_BIT );
		glEnable(GL_DEPTH_TEST|GL_CULL_FACE);
		glCullFace(GL_BACK);

	//如果數據庫沒有加載成功或調入數據失敗，返回
	if(theApp.bLoginSucceed==FALSE || m_bLoadInitDemData==FALSE)
		return;
	
	CString tt,strSql;
	CString m_style,m_stylePre,m_styleNext;
	PCordinate pt;
	

	SetDrawMode();//設置繪圖模式
	glViewport(0, 0, WinViewX, WinViewY); //重新設置視口大小
	
	
	if(b_haveMadeRail3DwayList==FALSE )  //如果還沒有構建線路三維模型的顯示列表
	{

		
		ReLoadCenterPt();//重新從數據庫中讀取線路中線坐標點數據
			


		glNewList(m_Rail3DwayList,GL_COMPILE_AND_EXECUTE); //創建顯示列表
		
		glColor3f(0.75,0.75,0.75);//設置顏色
		glLineWidth(2.0);//設置線寬
		

		//1. 繪製橋墩
		myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].RemoveAll();
		myDesingScheme.GetBirdgeQDcordinate(m_Bridge.m_Bridge_QDSpace);//根據橋墩間距計算設置橋墩坐標
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

		
		//2. 計算橋樑欄杆三維坐標
		myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].RemoveAll();
		myDesingScheme.GetBirdgeLGcordinate(m_Bridge.m_Bridge_HLSpace);//根據橋欄杆間距計算設置橋欄杆坐標
		
		//3. 繪製左側路基邊坡
		glColor3f(1,0,0);		
		int mBridgeIndex=0;//橋樑初始索引號
		glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID()); //綁定路基邊坡紋理
		for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle; //交點類型
			m_styleNext=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;	
		
			//如果交點類型是非隧道和橋樑段的點，則繪製路基邊坡
			if(m_style!="隧道起點" && m_style!="隧道中間點" &&m_style!="隧道終點" \
				&&m_style!="橋樑中間點" &&m_style!="橋樑終點" && m_styleNext!="隧道起點" )
			{	
				DrawBP(i,1); //繪製左側路基邊坡
				
			}
			if(m_style=="橋樑起點" || m_style=="橋樑終點")	
			{
				
				glColor3f(0.5,0,1);
				if(i>0)
				{
					//下一點處的交點類型
					m_styleNext=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;
						//橋樑起終點處護坡
						//(規則如下:如果是橋樑直接相連,則不需要繪製護坡)
						int Innum;
						//繪製橋樑下方護坡面
						if(m_style=="橋樑起點")
							Innum=i;//i-1;
						else if(m_style=="橋樑終點")
							Innum=i+1;
						
						//繪製橋樑下方護坡面
						DrawQDHP(Innum,m_style,m_Bridge.m_Bridge_HPangle/180.0*PAI,m_styleNext,mBridgeIndex);
				
				}
				if(m_style=="橋樑終點")
					mBridgeIndex++;
			}
		}


		//4.繪製右側路基邊坡
		glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());//綁定路基邊坡紋理
		for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//交點類型
			m_styleNext=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;//下一點的交點類型
			

			//如果交點類型是非隧道和橋樑段的點，則繪製路基邊坡		
			if(m_style!="隧道起點" && m_style!="隧道中間點" &&m_style!="隧道終點" \
				&&m_style!="橋樑中間點" &&m_style!="橋樑終點" && m_styleNext!="隧道起點")
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				DrawBP(i,2);//繪製右側路基邊坡
				
			}
			if(m_style!="隧道起點" && m_style!="隧道中間點"  \
				&& m_style!="橋樑起點" && m_style!="橋樑中間點" && m_style!="隧道中間點" )
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureSuigou.GetTxtID());//綁定水溝紋理
				DrawSuiGou(i);//繪製水溝
				
			}
		}
	


		//5.繪製線路中線
		glLineWidth(3.0);
		m_TempPts.RemoveAll();
		for ( i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1;i++)
		{

			//如果未進行線路三維建模，則調用DrawCenterLine()函數繪製線路中線
			if(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()<=0)
				DrawCenterLine(i,FALSE,m_currentSchemeIndexs); //繪製線路中線
			else
			{				
				tt=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//交點類型
				
				if(tt!="隧道中間點" && i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x;
					pt->y=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->y; 
					pt->z=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z; 
					pt->strJDStyle=tt;
					m_TempPts.Add(pt);
				}
				else //隧道部分的線路位於地面以下，不繪製
				{		
					if(m_TempPts.GetSize()>1)
					{	
						
						glBegin(GL_LINE_STRIP);
						
						for(int k=0;k<m_TempPts.GetSize();k++)
						{
							tt=m_TempPts.GetAt(k)->strJDStyle;
							if(tt=="交點坐標" || tt=="直緩點坐標" || tt=="緩直點坐標" || tt=="交點-直緩點坐標")
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
       //6.繪製軌道
		glBindTexture(GL_TEXTURE_2D, m_cTxtureRailway.GetTxtID()); //綁定軌道紋理
	 	glLineWidth(2.0);//設置線寬
		for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			
			if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Derh==0) //如果挖為0
				glColor3f(0,1,1); //設置顏色
			else
				glColor3f(1,0,1); //設置顏色
			float L=myDesingScheme.GetDistenceXY(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
		
			//以矩形方式連接前後相臨軌道斷面	
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f); //設置紋理坐標(當前軌道斷面左側點)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1);
			glTexCoord2f(1.0f,0.0f); //設置紋理坐標(當前軌道斷面右側點)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(1.0f,L/10);//設置紋理坐標(下一前軌道斷面右側點)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(0.0f,L/10); //設置紋理坐標(下一前軌道斷面左側點)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			
			glEnd();

		}		
	
		//7.繪製道床邊坡
		glBindTexture(GL_TEXTURE_2D, m_cTxtureGdToLJ.GetTxtID());//綁定道床邊坡紋理
		glColor3f(1,1,0);//設置顏色
		for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			//以矩形方式連接方式繪製左側道床邊坡	
			glBegin(GL_POLYGON);
			glTexCoord2f(1.0f,0.0f);//設置紋理坐標(當前左側道床邊坡左側點)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1);
			glTexCoord2f(1.0f,1.0f);//設置紋理坐標(當前左側道床邊坡右側點)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glTexCoord2f(0.0f,1.0f);//設置紋理坐標(下一左側道床邊坡右側點)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glTexCoord2f(0.0f,0.0f);//設置紋理坐標(下一左側道床邊坡左側點)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1);
			
			glEnd();
			
			//以矩形方式連接方式繪製右側道床邊坡
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//設置紋理坐標(當前右側道床邊坡左側點)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(0.0f,1.0f);//設置紋理坐標(當前右側道床邊坡右側點)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(1.0f,1.0f);//設置紋理坐標(下一右側道床邊坡右側點)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(1.0f,0.0f);//設置紋理坐標(下一右側道床邊坡左側點)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glEnd();
		}		
		
		//8.繪製路肩
		glBindTexture(GL_TEXTURE_2D, m_cTxtureLJ.GetTxtID());//綁定路肩紋理
		glColor3f(1,0.5,0.25);//設置顏色
		for (i=0;i<myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			//以矩形方式連接方式繪製左側路肩	
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//設置紋理坐標(當前左側路肩斷面左側點)
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1);
			glTexCoord2f(0.0f,1.0f);//設置紋理坐標(當前左側路肩斷面右側點)	
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glTexCoord2f(1.0f,1.0f);//設置紋理坐標(下一左側路肩斷面右側點)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glTexCoord2f(1.0f,0.0f);//設置紋理坐標(下一左側路肩斷面左側點)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1);
			
			glEnd();			

			//以矩形方式連接方式繪製右側路肩	
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//設置紋理坐標(當前右側路肩斷面左側點)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(1.0f,0.0f);//設置紋理坐標(當前右側路肩斷面右側點)
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(1.0f,1.0f);//設置紋理坐標(下一右側路肩斷面右側點)
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(0.0f,1.0f);//設置紋理坐標(下一右側路肩斷面左側點)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			
			glEnd();
		}		

		//9.繪製橋樑欄杆
		DrawBridgeHL();

		//10.繪製隧道	
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].RemoveAll();//隧道坐標數據數組清空
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].RemoveAll();//隧道信息數據數組清空
		//調用GetTunnelcordinate()函數重新計算隧道坐標
		myDesingScheme.GetTunnelcordinate(m_Tunnel.height,\
			m_Tunnel.Archeight,\
			m_Tunnel.WallHeight,\
			m_Tunnel.width/2.0,\
			m_Tunnel.ArcSegmentNumber);
		DrawTunnel(); //繪製隧道	
	
		glLineWidth(1.0);//恢復線寬
		glEndList();//結束顯示列表
	
		b_haveMadeRail3DwayList=TRUE; //標識已經創建顯示列表
	}
	else //如果已經構建線路三維模型的顯示列表,則直接調用顯示列表
	{
		glCallList(m_Rail3DwayList);  //調用線路三維模型顯示列表
	}
	glPopAttrib();//彈出屬性堆棧
}

void CT3DSystemView::DrawBP(long index, int BPside)
{


	float mNCDistence=4.0;
	long i=index;

	int j;


	if(BPside==1) //左邊坡
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
				
				//如果路基類型相同(同為路塹或路堤)
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
				else  //如果路基類型相同(路塹,路堤相連)
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
 //4.求左右側水溝交點坐標
	/*
	排水溝由4個點確定,分別為1-4號點,其中0號點為LjToBp點,已存儲
		5____4  1____0
   (b4) \     /(b3)
		3\___/2

	其中:
	側溝深度 SuiGou_h,
	側溝頂寬度 SuiGou_b1,
	側溝底寬度 SuiGou_b2,
	側溝外邊坡的寬度  SuiGou_b3
	側溝內邊坡[靠近路基一側]斜率 SuiGou_m1,
	側溝外邊坡[遠離路基一側]斜率 SuiGou_m2,
	float SuiGou_h,SuiGou_b1,SuiGou_b2,SuiGou_b3,SuiGou_b4,SuiGou_m1,SuiGou_m2;
	SuiGou_b2=0.4;//側溝底寬度[規範要求]
	SuiGou_h=0.6;//側溝深度[規範要求]
	SuiGou_b3=0.3;
	SuiGou_b4=0.6;//側溝外邊坡的寬度[規範要求:路塹:0.8  路堤:0.6 ,這裡為了簡便,統一取為0.6]
	SuiGou_m1=SuiGou_m2=1;//內/外邊坡斜率[規範要求]
    SuiGou_b1=SuiGou_h/SuiGou_m1+SuiGou_h/SuiGou_m2+SuiGou_b2;//側溝頂寬度
	所以水溝總寬度=0.6+2*0.6+0.4+0.3=2.5
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
		//當前點沒有水溝,而下一點有水溝
		
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
		//當前點有水溝,而下一點沒有水溝
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
		//當前點沒有水溝,而下一點有水溝
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
		//當前點有水溝,而下一點沒有水溝
		
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

//繪製橋樑下方護坡面
void CT3DSystemView::DrawQDHP(long Index, CString mCurrentPtstyle, float mHPangle, CString mNextPtstyle, int mBridgeIndex)
{
	//	如果是橋隧直接相連,則不需要繪製護坡)
	if(mNextPtstyle=="隧道起點")
		return;
	//	參與繪製護坡面的點

	//	左側:護坡點HuPo_L+PtS_RailwayLj3D左側點(x1,y1,z1)
	//	右側:PtS_RailwayLj3D左側點(x2,y2,z2)+護坡點HuPo_R
			
	//根據是橋樑起點(mCurrentPtstyle="橋樑起點")還是
	//橋樑終點(mCurrentPtstyle="橋樑終點")來分別進行繪製,二
	//者護坡面的方向是相反的
	double x1,y1,z1,x2,y2,z2;
	double tx,ty,tz;
	
	PCordinate pt;
	
	int i;
	double ax,ay,az;
	int N1,N2;

	
	N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->Huponums_L-1;//左側邊坡數
	N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->Huponums_R-1;//右側邊坡數

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
	
	if(mCurrentPtstyle=="橋樑起點")
	{
		if(fabs(dx)<=0.000001) 
		{
			mangle=0;
		}  
		else 
		{
			mangle=atan(fabs(dz/dx));
			if(dx>=0 && dz<=0)  //1象限
			{
				mangle=PAI/2+mangle;
			}
			else if(dx<=0 && dz<=0) //2象限 
			{
				mangle=PAI*3.0/2-mangle;
			}
			else if(dx<=0 && dz>=0) //3象限
			{
				mangle=2*PAI-mangle;
			}
			else if(dx>=0 && dz>=0) //4象限
			{
				mangle=PAI/2-mangle;
			}
			
		}
	}
	else if(mCurrentPtstyle=="橋樑終點")
	{
		if(fabs(dx)<=0.000001) 
		{
			mangle=PAI*3.0/2;
		}  
		else 
		{
			mangle=atan(fabs(dz/dx));
			if(dx>=0 && dz<=0)  //1象限
			{
				mangle=2*PAI-mangle;
			}
			else if(dx<=0 && dz<=0) //2象限 
			{
				mangle=PAI/2-mangle;
			}
			else if(dx<=0 && dz>=0) //3象限
			{
				mangle=PAI/2+mangle;
			}
			else if(dx>=0 && dz>=0) //4象限
			{
				mangle=PAI*3.0/2-mangle;
			}
			
		}
	}
	
		//	(1)//橋樑起點護坡面
		PtBridgeHPUp.RemoveAll();
		PtBridgeHPDown.RemoveAll();
	
		//依次求得按給定護坡面角度與地面的交點
		//(1)左側護坡點
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
				PtBridgeHPUp.Add(pt); //加入護坡面
			}
		}
	
		//(2) 左側路肩TO邊坡點
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
		
		//(3) 左側路肩點
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
		
		//(4) 中心線
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
		
		//(5) 右側路肩點
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
			
		//(6) 右側路肩TO邊坡點
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
			
		
			//(7)右側護坡點
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

	//記錄護坡下面的與地面交點
	if(mCurrentPtstyle=="橋樑起點")
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
	else if(mCurrentPtstyle=="橋樑終點")
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

//繪製橋墩
void CT3DSystemView::DrawSceneQD(double x1, double y1, double z1, double x2, double y2, double z2, float QDheight)
{
	//橋墩應具有的寬度
	float Xwidth=m_Railway.m_Railway_width+2*m_Railway.m_Lj_width+2*m_Railway.m_GuiMianToLujianWidth;
	float mangle=myDesingScheme.GetANgle(x1,z1,x2,z2); //計算橋墩模型應旋轉的角度(使之與線路垂直)
	if(mangle>180)
		mangle=mangle-180;
	
	float xscale=Xwidth/(m_QD_maxx-m_QD_minx); //計算橋墩模型在X方向上的縮放比例(寬度)
	float yscale=QDheight/(m_QD_maxy-m_QD_miny);//計算橋墩模型在Y方向上的縮放比例(高度)
	
	glPushMatrix(); //壓入堆棧
	glScalef(xscale,yscale,1); //橋墩縮放
	glTranslatef(((x1+x2)/2-(m_QD_maxx+m_QD_minx)/2)/xscale,y2/yscale-m_QD_maxy,(z1+z2)/2); //平移
	glRotatef(mangle,0,1,0); //旋轉
	glCallList(m_QDList); //調用橋墩顯示列表繪製橋墩
	glPopMatrix(); //彈出堆棧
	
}


//繪製隧道
void CT3DSystemView::DrawTunnel()
{
//	m_Tunnel.H;//隧道圓弧頂端再向上的高度
//	m_Tunnel.L;//隧道洞門頂端左右兩側延伸的寬度 
		
	glColor3f(1,1,1);
	glLineWidth(2.0);
	int index=0;
	
	long m_StartIndex,m_EndIndex;//存儲當前隧道起終坐標點在所有隧道數據坐標的索引號
	m_StartIndex=-1;
	
	//根據所有隧道的坐標(隧道之間以x=y=-1為分隔,)
	//如下示例數據說明,表示共有2個隧道
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
				m_StartIndex=i; //當前隧道起始坐標點在所有隧道的坐標的索引號
		}
		else
		{
			m_EndIndex=i-1;//當前隧道終止坐標點在所有隧道的坐標的索引號(m_EndIndex-m_StartIndex確定了當前隧道由多少個坐標點組成)
			DrawTunnelEach(m_StartIndex,m_EndIndex,index,m_Tunnel.H,m_Tunnel.L); //繪製隧道(index:表示當道隧道在所有隧道的索引,即當道隧道是線路中第幾個隧道
			index++; //隧道的索引號+1
			m_StartIndex=-1;//恢復為-1
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

//繪製隧道
/*參數說明:
mStartindex:當前隧道起始坐標點在所有隧道的坐標數據的索引號
mEndIndex://當前隧道終止坐標點在所有隧道的坐標數據的索引號
mTunnelIndex:表示當道隧道在所有隧道的索引,即當道隧道是線路中第幾個隧道(假設共4個隧道,則mTunnelIndex=0,1,2,3)
H:隧道圓弧頂端再向上的高度
L:隧道洞門頂端左右兩側延伸的寬度 
*/
void CT3DSystemView::DrawTunnelEach(long mStartindex, long mEndIndex, int mTunnelIndex, float H, float L)
{
	double minx,miny,Lx,Ly;
	
	//(1)繪製隧道出口洞門
	glBindTexture(GL_TEXTURE_2D, m_cTunnel_dm.GetTxtID()); //綁定隧道出口洞門紋理
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
	
	/*	根據隧道出口洞門左右兩側立牆底下端坐標(x,y1,z1),(x2,y2,z2)	*/

	//(2)繪製隧道內部
	glBindTexture(GL_TEXTURE_2D, m_cTunnel.GetTxtID());//綁定隧道內部紋理
	for ( long i=mStartindex;i<mEndIndex;i++)
	{
	//	glBindTexture(GL_TEXTURE_2D, m_cTunnel.GetTxtID());//綁定隧道內部紋理
		
			//左側立牆
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

			//右側立牆
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
			//頂端圓弧
			int mNums=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetSize();

			minx=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(mNums-1)->x;
			miny=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(mNums-1)->z;
			Lx=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(0)->x-minx;
			Ly=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(0)->z-miny;
			
			//繪製相臨兩斷面的頂端圓弧,以連續多邊形方式繪製(GL_QUAD_STRIP)
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
		
		//繪製隧道進出口洞門
		glBindTexture(GL_TEXTURE_2D, m_cTunnel_dm.GetTxtID());//綁定隧道進口洞門紋理
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

//繪製隧道洞門
/*
參數說明:
x1,y1,z1:隧道洞門左兩側立牆底下端坐標
x2,y2,z2:隧道洞門右兩側立牆底下端坐標
H;隧道圓弧頂端再向上的高度
L:隧道洞門頂端左右兩側延伸的寬度
index:隧道洞門的坐標點在所有隧道的數據坐標的索引號
tunnelIndex;當道隧道在所有隧道的索引,即當道隧道是線路中第幾個隧道
bstartDM:表示是隧道進口洞門(bstartDM=TRUE)還是隧道出口洞門((bstartDM=FALSE)
mangle:洞門的走向角度
  */
void CT3DSystemView::DrawTunnelDM(double x1, double y1, double z1, double x2, double y2, double z2, float H, float L, int index, int tunnelIndex, BOOL bstartDM, float mangle)
{
//所傳遞的坐標P6(x1,y1,z1),P5(x2,y2,z2)
//H:從圓弧頂端向上的高度(也就是要在圓弧頂端再加一定的高度,作為洞門的總高度)
//L:從立牆正上方向,向右擴展的距離,構成端牆式洞門結構
//以GL_TRIANGLE繪製△P1p2p6  △P3p4p5 
//P2P3間分為 m_Tunnel.ArcSegmentNumber數量點,與圓弧點相對應,以GL_TRIANGLE_STRIP繪製
/*
隧道洞門示意圖圖(端牆式洞門)
	P1   L   P2          P3   L   P4
	--------- |-----------|----------
	 \        |      h_   |        /
	  \       |           |       /   
	   \      |  圓弧頂端 |      /
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
	if(bstartDM==TRUE)//洞門進口
		mIn=myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->startIndex-1;//索引值
	else
		mIn=myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->endIndex-1;//索引值

	P7[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[1].x;
	P7[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[1].y;
	P7[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[1].z;

	P8[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[1].x;
	P8[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[1].y;
	P8[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[1].z;
	
		
	//(1)求出P2,P3坐標 P2,P3間距離=m_Tunnel.width
	P2[0]=x1;P2[1]=y1+m_Tunnel.height+H;P2[2]=z1;
	P3[0]=x2;P3[1]=y2+m_Tunnel.height+H;P3[2]=z2;
	
	//(2)求出P1,P4坐標
	P1[0]=P2[0]-L*cos(mangle);P1[1]=P2[1];P1[2]=P2[2]+L*sin(mangle);
	P4[0]=P3[0]+L*cos(mangle);P4[1]=P3[1];P4[2]=P3[2]-L*sin(mangle);
		
	
	//////////////////////////////////////////////////////////////////////////
	//橋墩應具有的寬度
	float Xwidth=fabs(P4[0]-P1[0]);
	float Yheight=fabs(P3[1]-P5[1]);
	mangle=myDesingScheme.GetANgle(x1,z1,x2,z2); //計算隧道洞門模型應旋轉的角度(使之與線路垂直)
	
	float xscale=Xwidth/(m_TunnelDM_maxx-m_TunnelDM_minx); //計算隧道洞門模型在X方向上的縮放比例(寬度)
	float yscale=Yheight/(m_TunnelDM_maxy-m_TunnelDM_miny);//計算隧道洞門模型在Y方向上的縮放比例(高度)
	glPushMatrix(); //壓入堆棧
	glScalef(xscale,yscale,1); //隧道洞門縮放
	glTranslatef(((x1+x2)/2-(m_TunnelDM_maxx+m_TunnelDM_minx)/2)/xscale,((y1+y2)/2-(m_TunnelDM_maxy+m_TunnelDM_miny)/2)/yscale,(z1+z2)/2); //平移
	glRotatef(mangle,0,1,0); //旋轉
	glCallList(m_TunnelDMList); //調用隧道洞門顯示列表繪製橋墩
	glPopMatrix(); //彈出堆棧
	
	//////////////////////////////////////////////////////////////////////////
	
//	return;

	

	PCordinate pt;

	if(bstartDM==TRUE)//洞門進口
	{
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_Start.RemoveAll();
		
		//計算隧道洞門進口各點坐標
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
		
		//計算隧道洞門出口各點坐標
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
		
		
		if(bstartDM==TRUE)//如果是隧道進口洞門
		{
			Lx=P4[0]-P1[0];
			Ly=P1[1]-P7[1];
			minx=P1[0];
			miny=P7[1];
		}
		else  //如果是隧道出口洞門
		{
			Lx=P1[0]-P4[0];
			Ly=P1[1]-P7[1];
			minx=P4[0];
			miny=P7[1];
		}

			glLineWidth(3.0);  //設置線寬

			glColor3f(1,0,1); //設置顏色
			glBegin(GL_TRIANGLE_STRIP); //以連續折線方式繪製
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
			glBegin(GL_TRIANGLES); //以三角形形繪製(p1P2P7)
				glTexCoord2f((P1[0]-minx)/Lx,1);
				glVertex3dv(P1);
				glTexCoord2f((P2[0]-minx)/Lx,1);
				glVertex3dv(P2);
				glTexCoord2f((P7[0]-minx)/Lx,0);
				glVertex3dv(P7);
			glEnd();

			glBegin(GL_TRIANGLES);//以三角形形繪製(p2P7P6)
				glTexCoord2f((P2[0]-minx)/Lx,1);
				glVertex3dv(P2);
				glTexCoord2f((P7[0]-minx)/Lx,0);
				glVertex3dv(P7);
				glTexCoord2f((P6[0]-minx)/Lx,0);
				glVertex3dv(P6);
			glEnd();

			glBegin(GL_TRIANGLES);//以三角形形繪製(p3P5P8)
				glTexCoord2f((P3[0]-minx)/Lx,1);
				glVertex3dv(P3);
				glTexCoord2f((P5[0]-minx)/Lx,0);
				glVertex3dv(P5);
				glTexCoord2f((P8[0]-minx)/Lx,0);
				glVertex3dv(P8);
			glEnd();

			glBegin(GL_TRIANGLES);//以三角形形繪製(p3P8P4)
			glTexCoord2f((P3[0]-minx)/Lx,1);
			glVertex3dv(P3);
			glTexCoord2f((P8[0]-minx)/Lx,0);
			glVertex3dv(P8);
			glTexCoord2f((P4[0]-minx)/Lx,1);
			glVertex3dv(P4);
			glEnd();
			
			
			//繪製頂端圓弧
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
		
//-----------封閉洞門與路基邊界處
		//繪製洞門
		if(bstartDM==TRUE)//洞門進口
		{
			glBindTexture(GL_TEXTURE_2D, m_cTunnel_dmwcBp.GetTxtID());
			//(1)左側
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
				
				//求 minx,maxx,miny,maxy;
				
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
			

			//(2)右側
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
			
			//求 minx,maxx,miny,maxy;
			
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
		else if(bstartDM==FALSE)//洞門出口
		{
			glBindTexture(GL_TEXTURE_2D, m_cTunnel_dmwcBp.GetTxtID());
			
			//(1)左側
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
			
			//求 minx,maxx,miny,maxy;
			
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
		

			//(2)右側
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
			
			//求 minx,maxx,miny,maxy;
			
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



//線路三維建模
void CT3DSystemView::OnMenuBuild3dlinemodle() 
{
	BeginWaitCursor();
	b_haveGetRegion=FALSE;//是否已獲取封閉區域
	
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
		tt.Format("正在進行線路三維建模 , 請稍候... , 已完成%.2f%s" , (i+1)*iPer , "%");
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

	
	pMainFrame->Set_BarText(4 , "加載地形與影像紋理數據完成!" , 0); 
	b_haveMadeRail3DwayList=FALSE;
	b_haveMadeRail3DwayList_Ortho=FALSE;
	OnDraw (GetDC()); //刷新三維場景
	
}

//沿方案線漫遊,也就不將當前線路方案中心線作為漫遊路徑而已	
void CT3DSystemView::OnFlyRoutinschemeline() 
{
	m_R=3000;
	m_r=2000;
	
	if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()<=1)
	{
		if(m_FlayPath.GetSize()<=0) //表明當前是按路徑漫遊狀態
			m_PathFlag=FALSE; //標識飛行路徑無效
		else
			m_PathFlag=TRUE; //標識飛行路徑有效
		return;
	}
	
	m_FlayPath.RemoveAll();//飛行路徑數組清空
	PCordinate ppt=NULL;
	//將線路中線作為飛行路徑
	for(int i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize();i++)
	{
		ppt = new Cordinate;
		ppt->x=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x;//x坐標
		ppt->y=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->y;//y坐標
		ppt->z=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z;//z坐標
		ppt->Lc=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Lc;//里程
		m_FlayPath.Add(ppt); //將線路中線坐標點加入飛行路徑數組中
	}
	
	if(m_FlayPath.GetSize()>1) //如果飛行路徑有效
	{
		m_bmouseView=FALSE; //停止鼠標旋轉視角功能
		//	m_ShowFlyPath=TRUE;
// 		m_ShowFlyPath=FALSE;//線路三維漫遊不需要顯示路徑,影響效果
		m_PathFlag=TRUE; //標識飛行路徑有效
		m_ifZoomonRoad=TRUE; //標識沿線路方案漫遊
		m_far=1500; //線路三維漫遊時,讓視口遠距離變小一些,剪裁掉一些看不見
		//的元素,加快漫遊速度,原來是10000,相當於10公里,線路三維漫遊時不需
		//要這麼大
		
	}
	else
	{
		m_ifZoomonRoad=FALSE; //標識沿線路方案漫遊為FALSE
	}
	
	OnFlyRoutineheight();	//按相對高度飛行	
}





//根據漫遊路徑相臨坐標點計算相機各參數
void CT3DSystemView::GetCameraCorrdinate(double x1, double y1, double z1, double x2, double y2, double z2)
{
	//(x1,y1,x1):飛行路徑當前點坐標
	//(x2,y2,x2):飛行路徑下一點坐標
	

	if(m_FlyHeightType == GIS_FLY_STATICHEIGHT)	//固定高度飛行方式
	{
		m_vView.x=x2;//觀察點x坐標
		m_vView.y=m_StaticHeight;//觀察點y坐標=y2+m_StaticHeight固定高度值
		m_vView.z=z2;//觀察點z坐標

		m_vPosition.x=x1;//視點x坐標
		m_vPosition.y=m_vView.y;//視點y坐標=觀察點y坐標
		m_vPosition.z=z1;//視點z坐標
	}
	//按相對高度(即沿路徑)漫遊時，需計算一個基本高度
	else if(m_FlyHeightType == GIS_FLY_PATHHEIGHT)
	{
		m_vView.x=x2; //觀察點x坐標
		m_vView.y=y2+m_StaticHeight; //觀察點y坐標=y2+m_StaticHeight固定高度值
		m_vView.z=z2;//觀察點z坐標
		
		//求二點之間距離
		float distance = sqrt((x2-x1)*(x2-x1)+(z2-z1)*(z2-z1));
		//根據傾角計算高度差
		float dh = distance * tan(m_ViewUpDown * PAI_D180);
		
		m_vPosition.x=x1;//視點x坐標
		m_vPosition.y=m_vView.y+dh;//視點y坐標=觀察點y坐標+高差
		m_vPosition.z=z1;//視點z坐標
	}
}

//計算漫遊時的速度
void CT3DSystemView::CalZoomSpeed(float mCurZooomLC)
{
	static DWORD dwStart = 0;
	DWORD dwNow = ::GetTickCount();
	if(dwNow-dwStart>=100) //0.1秒
	{
		long fgf=dwNow-dwStart;
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		CString strText;
		strText.Format("漫遊速度= %.3f 米/秒 ",(mCurZooomLC-m_PreZooomLC)/(((dwNow-dwStart)/1000.0)),0);
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

//創建隧道洞門顯示列表
void CT3DSystemView::BuildTunnelDMModelList()
{
	g_3dsModels=new C3DSModel;
	char *str = new char[256]; 
	
	CString str3DSfilename;
	
	m_3DSfilename_TunnelDM=".\\模型\\隧道洞門\\端牆式洞門\\模型文件.3DS";
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

//畫圓柱
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

//隧道參數設置
void CT3DSystemView::OnMenuTunnelset() 
{
	CTunncelPropertySet dlg;
	dlg.m_tunnel_height=m_Tunnel.height;//隧道總高度
	dlg.m_tunnel_Archeight=m_Tunnel.Archeight;//隧道圓弧高度
	dlg.m_tunnel_WallHeight =m_Tunnel.height-m_Tunnel.Archeight;//隧道立牆高度
	dlg.m_tunnel_ArcSegmentNumber=m_Tunnel.ArcSegmentNumber;//隧道圓弧分段數
	dlg.m_tunnel_H=m_Tunnel.H ;//隧道圓弧頂端再向上的高度
	dlg.m_tunnel_L=m_Tunnel.L;//隧道洞門頂端左右兩側延伸的寬度 
	if(dlg.DoModal()==IDOK)
	{
		m_Tunnel.height=dlg.m_tunnel_height;//隧道總高度
		m_Tunnel.Archeight=dlg.m_tunnel_Archeight;//隧道圓弧高度
		m_Tunnel.WallHeight =m_Tunnel.height-m_Tunnel.Archeight;;//隧道立牆高度
		m_Tunnel.ArcSegmentNumber=dlg.m_tunnel_ArcSegmentNumber;//隧道圓弧分段數
		m_Tunnel.H= dlg.m_tunnel_H;//隧道圓弧頂端再向上的高度
		m_Tunnel.L=dlg.m_tunnel_L;//隧道洞門頂端左右兩側延伸的寬度 
		b_haveMadeRail3DwayList=FALSE; //當隧道參數改變時,需要重新構建顯示列表(透視投影模式)
		b_haveMadeRail3DwayList_Ortho=FALSE;//當隧道參數改變時,需要重新構建顯示列表(正射投影模式)
		OnDraw (GetDC()); //刷新三維場景
	}	
}

//設置橋樑參數
void CT3DSystemView::OnMenuBridgeset() 
{
	CBridgeSet dlg;
	dlg.m_Bridge_HLHeight=m_Bridge.m_Bridge_HLHeight;//橋樑欄杆高
	dlg.m_Bridge_HLSpace=m_Bridge.m_Bridge_HLSpace;//橋樑欄杆間距
	dlg.m_Bridge_HLWidth=m_Bridge.m_Bridge_HLWidth;//橋樑欄杆寬度
	dlg.m_Bridge_QDSpace=m_Bridge.m_Bridge_QDSpace;//橋墩間距
	dlg.m_Bridge_HPangle=m_Bridge.m_Bridge_HPangle;//橋頭護坡傾角
	dlg.m_bridgeColorR=m_bridgeColorR;//橋樑欄杆顏色
	dlg.m_bridgeColorG=m_bridgeColorG;//橋樑欄杆顏色
	dlg.m_bridgeColorB=m_bridgeColorB;//橋樑欄杆顏色

	if(dlg.DoModal()==IDOK)
	{
		m_Bridge.m_Bridge_HLHeight=dlg.m_Bridge_HLHeight;//橋樑欄杆高
		m_Bridge.m_Bridge_HLSpace=dlg.m_Bridge_HLSpace;;//橋樑欄杆間距
		m_Bridge.m_Bridge_HLWidth=dlg.m_Bridge_HLWidth;//橋樑欄杆寬度
		m_Bridge.m_Bridge_QDSpace=dlg.m_Bridge_QDSpace;//橋墩間距
		m_Bridge.m_Bridge_HPangle=dlg.m_Bridge_HPangle;//橋頭護坡傾角
		m_bridgeColorR=dlg.m_bridgeColorR;//橋樑欄杆顏色
		m_bridgeColorG=dlg.m_bridgeColorG;//橋樑欄杆顏色
		m_bridgeColorB=dlg.m_bridgeColorB;////橋樑欄杆顏色
		b_haveMadeRail3DwayList=FALSE;
		b_haveMadeRail3DwayList_Ortho=FALSE;
		makeQLList(); //重新生成橋樑欄杆顯示列表
		OnDraw (GetDC()); //刷新三維場景
	}	
}

//繪製橋樑欄杆
void CT3DSystemView::DrawBridgeHL()
{
		//繪製橋樑欄杆
		glPushAttrib(GL_TEXTURE_BIT|GL_POLYGON_BIT);
			glDisable(GL_TEXTURE_2D); //關閉紋理
			glPolygonMode(GL_FRONT_AND_BACK ,GL_LINE);	//以線型繪製
			glColor3f(m_bridgeColorR/255.0,m_bridgeColorG/255.0,m_bridgeColorB/255.0);//設置橋樑欄杆顏色
			glLineWidth(m_Bridge.m_Bridge_HLWidth); //設置繪製欄杆的線寬
		for (long i=0;i<myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			
			//如果當前和下一橋樑欄杆坐標!=-1，則繪製橋樑欄杆
			if(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y1!=-1)
			{	
				
				//左側橋樑欄杆中間橫線
				glBegin(GL_LINES);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1+m_Bridge.m_Bridge_HLHeight/2.0,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y1+m_Bridge.m_Bridge_HLHeight/2.0,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
				glEnd();

				//左側橋樑欄杆頂端橫線
				glBegin(GL_LINES);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1+m_Bridge.m_Bridge_HLHeight,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y1+m_Bridge.m_Bridge_HLHeight,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
				glEnd();


				//右側橋樑欄杆中間橫線
				glBegin(GL_LINES);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y2+m_Bridge.m_Bridge_HLHeight/2.0,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z2);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y2+m_Bridge.m_Bridge_HLHeight/2.0,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
				glEnd();
				
				//右側橋樑欄杆頂端橫線
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
				glCallList(m_QLanList);//調用橋樑欄杆顯示列表繪製左側圓柱形欄杆立柱
				glPopMatrix();


		
				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z2);
				glCallList(m_QLanList);//調用橋樑欄杆顯示列表繪製右側圓柱形欄杆立柱
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
				glCallList(m_QLanList);//調用橋樑欄杆顯示列表繪製左側圓柱形欄杆立柱
				glPopMatrix();
				
				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->y2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->z2);
				glCallList(m_QLanList);//調用橋樑欄杆顯示列表繪製右側圓柱形欄杆立柱
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
				glCallList(m_QLanList);//調用橋樑欄杆顯示列表繪製左側圓柱形欄杆立柱
				glPopMatrix();
				
				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z2);
				glCallList(m_QLanList);//調用橋樑欄杆顯示列表繪製右側圓柱形欄杆立柱
				glPopMatrix();
				
			}

		
		}
		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK ,GL_FILL);	
		glPopAttrib();
}

//重新從數據庫中讀取線路中線坐標點數據
void CT3DSystemView::ReLoadCenterPt()
{
	CString tt,strSql;
	PCordinate pt;
	
	//重新讀取方案的的線路中線坐標數據
	//		if(myDesingScheme.SchemeDatass[m_currentSchemeIndexs].EndLC<=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].StartLC)
	//			strSql.Format("SELECT *  FROM  T3DLineZxCorrdinate WHERE 方案名稱='%s' ORDER BY 里程 ASC",\
	//			myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename);
	//		else	
	strSql.Format("SELECT *  FROM  T3DLineZxCorrdinate WHERE 方案名稱='%s' \
		ORDER BY 里程 ASC",\
		myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename\
		);
	
	try
	{
		//			if(m_Recordset->State) //如果
		//				m_Recordset->Close();
		m_Recordset->Open((_bstr_t)strSql,(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);   //打開數據表 
	}
	
	catch(_com_error& e)	//錯誤捕捉
	{
		CString errormessage;
		errormessage.Format("打開表失敗!\r\n錯誤信息:%s",e.ErrorMessage());
		::MessageBox(NULL,errormessage,"打開數據表",MB_ICONSTOP);
		return;
	} 
	
	myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].RemoveAll(); //清空線路中線數組PtS_3DLineZX[]
	while (!m_Recordset->adoEOF)
	{
		pt=new Cordinate;
		
		Thevalue = m_Recordset->GetCollect("x坐標"); 
		pt->x=(double)Thevalue; //線路中線點的x坐標
		
		Thevalue = m_Recordset->GetCollect("y坐標"); 
		pt->y=(double)Thevalue;//線路中線點的y坐標
		
		Thevalue = m_Recordset->GetCollect("z坐標"); 
		pt->z=(double)Thevalue;//線路中線點的z坐標
		
		Thevalue = m_Recordset->GetCollect("坐標類型"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt=Thevalue.bstrVal;
			pt->strJDStyle=tt; //線路中線點的x類型
		}
		
		Thevalue = m_Recordset->GetCollect("地面高程"); 
		pt->dmh=(double)Thevalue; //對應的地面高程
		
		Thevalue = m_Recordset->GetCollect("填挖高"); 
		pt->Derh=(double)Thevalue; //對應的填挖高
		
		Thevalue = m_Recordset->GetCollect("里程"); 
		pt->Lc=(double)Thevalue;//對應的里程
		
		myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].Add(pt); //存儲線路中線坐標數據
		m_Recordset->MoveNext(); //指針下移
		
	}
	m_Recordset->Close(); //關閉記錄集
	
}

//邊坡紋理
void CT3DSystemView::OnMenuTexturebp() 
{
	CTextureBP	dlg;
	CString strTexturename;

	if(dlg.DoModal()==IDOK) //如果以IDOK方式關閉對話框
	{
		strTexturename="紋理\\邊坡防護\\"+dlg.m_BPtextureName; //得到紋理文件名路徑名
		m_cTxtureBP.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename); //加載邊坡紋理
		b_haveMadeRail3DwayList=FALSE; //三維線路顯示列表標識為FALSE,表示需要重新構建線路三維模型列表(透視投影模式下)
		b_haveMadeRail3DwayList_Ortho=FALSE;//三維線路顯示列表標識為FALSE,表示需要重新構建線路三維模型列表(正射投影模式下)
		OnDraw (GetDC()); //刷新三維場景
	}	
}

//路肩紋理
void CT3DSystemView::OnMenuTexturelj() 
{
	CTextureLJ	dlg;
	CString strTexturename;
	if(dlg.DoModal()==IDOK)//如果以IDOK方式關閉對話框
	{
		strTexturename="紋理\\路肩\\"+dlg.m_LJtextureName;//得到紋理文件名路徑名
		m_cTxtureLJ.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//加載路肩紋理
		b_haveMadeRail3DwayList=FALSE; //三維線路顯示列表標識為FALSE,表示需要重新構建線路三維模型列表(透視投影模式下)
		b_haveMadeRail3DwayList_Ortho=FALSE;//三維線路顯示列表標識為FALSE,表示需要重新構建線路三維模型列表(正射投影模式下)
		OnDraw (GetDC());//刷新三維場景
	}	
}

//橋樑護坡面紋理
void CT3DSystemView::OnMenuTextureqlhpm() 
{
	CTextureQLHpm	dlg;
	CString strTexturename;
	if(dlg.DoModal()==IDOK)//如果以IDOK方式關閉對話框
	{
		strTexturename="紋理\\橋下方護坡面\\"+dlg.m_HQMtextureName;//得到紋理文件名路徑名
		m_cBridgeHpm.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//加載路肩紋理
		b_haveMadeRail3DwayList=FALSE; //三維線路顯示列表標識為FALSE,表示需要重新構建線路三維模型列表(透視投影模式下)
		b_haveMadeRail3DwayList_Ortho=FALSE;//三維線路顯示列表標識為FALSE,表示需要重新構建線路三維模型列表(正射投影模式下)
		OnDraw (GetDC());//刷新三維場景
	}	
}

//隧道內牆紋理
void CT3DSystemView::OnMenuTexturetunnel() 
{

	CTextureTunnel	dlg;
	CString strTexturename;
	if(dlg.DoModal()==IDOK)//如果以IDOK方式關閉對話框
	{
		strTexturename="紋理\\隧道內牆\\"+dlg.m_TunneltextureName;//得到紋理文件名路徑名
		m_cTunnel.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//加載路肩紋理
		b_haveMadeRail3DwayList=FALSE; //三維線路顯示列表標識為FALSE,表示需要重新構建線路三維模型列表(透視投影模式下)
		b_haveMadeRail3DwayList_Ortho=FALSE;//三維線路顯示列表標識為FALSE,表示需要重新構建線路三維模型列表(正射投影模式下)
		OnDraw (GetDC());//刷新三維場景
	}		
}

//隧道洞門紋理
void CT3DSystemView::OnMenuTexturetunnelDm() 
{
	CTextureTunnelDm	dlg;
	CString strTexturename;
	if(dlg.DoModal()==IDOK)//如果以IDOK方式關閉對話框
	{
		strTexturename="紋理\\隧道洞門\\"+dlg.m_TunnelDmtextureName;//得到紋理文件名路徑名
		m_cTunnel_dm.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//加載路肩紋理
		strTexturename="紋理\\隧道洞門外側邊坡\\"+dlg.m_TunnelDmtextureName;//得到紋理文件名路徑名
		m_cTunnel_dmwcBp.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//隧道洞門外側邊坡
		
		b_haveMadeRail3DwayList=FALSE; //三維線路顯示列表標識為FALSE,表示需要重新構建線路三維模型列表(透視投影模式下)
		b_haveMadeRail3DwayList_Ortho=FALSE;//三維線路顯示列表標識為FALSE,表示需要重新構建線路三維模型列表(正射投影模式下)
		OnDraw (GetDC());//刷新三維場景
	}		
}

//時鐘指北針的繪製
void CT3DSystemView::DrawClock()
{
//	if(m_bShowClocFlag==FALSE) return;
	
	glPushMatrix(); //壓入矩陣堆棧
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); //線繪製方式
		glDisable(GL_TEXTURE_2D);	//關閉紋理	
		SetClockProjectionNavigate(); //設置指北針的投影參數
		glCallList(m_clockList);//調用指北針時鐘的顯示列表
		DrawNorthPt();	//繪製指北針
		
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //填充繪製方式
		glEnable(GL_TEXTURE_2D);//打開紋理	
		glLineWidth(1.0); //設置線寬
		glColor3f(1.0, 1.0, 1.0); //設置顏色
	glPopMatrix();//彈出矩陣堆棧
}

void CT3DSystemView::SetClockProjectionNavigate()
{
	float wh=120; //設置時鐘的高度
	glViewport(0, WinViewY-wh,wh, wh);//設置視口位置和大小
    glMatrixMode( GL_PROJECTION ); //設置當前矩陣為透視矩陣
    glLoadIdentity(); //將當前矩陣置換為單位陣 
	glOrtho (0.0f,1.0,0.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode( GL_MODELVIEW );//設置當前矩陣為模型矩陣
	glLoadIdentity ();//將當前矩陣置換為單位陣 
}

//創建時鐘指北針顯示列表
void CT3DSystemView::makeClockList()
{
	glNewList(m_clockList,GL_COMPILE); //創建顯示列表
	float R=0.5,x,y;//時鐘圓盤半徑
	int i;

	glColor3f(0.0, 1.0, 1.0); //設置文字顏色

	x=R*cos((0)*PAI_D180)+0.37;//加上偏移量，準備寫入字母"E"，表示刻度3
	y=R*sin((0)*PAI_D180)+0.48;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"E"); //在設置坐標位置寫入E，表示方向「東」

	x=R*cos((90)*PAI_D180)+0.47;//加上偏移量，準備寫入字母"N"，表示刻度12
	y=R*sin((90)*PAI_D180)+0.36;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"N");//在設置坐標位置寫入N，表示方向「北」
	
	x=R*cos((180)*PAI_D180)+0.59;//加上偏移量，準備寫入字母"W" ，表示刻度9
	y=R*sin((180)*PAI_D180)+0.48;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"W");//在設置坐標位置寫入W，表示方向「西」

	x=R*cos((270)*PAI_D180)+0.48;//加上偏移量，準備寫入字母"S" ，表示刻度6
	y=R*sin((270)*PAI_D180)+0.58;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"S");//在設置坐標位置寫入S，表示方向「南」
	
	glColor3f(1.0, 1.0, 1.0); //設置時鐘刻度數字顏色
	
	x=R*cos((30)*PAI_D180)+0.39; //設置坐標
	y=R*sin((30)*PAI_D180)+0.43;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"2"); //寫入數字刻度
	
	
	x=R*cos((60)*PAI_D180)+0.42;
	y=R*sin((60)*PAI_D180)+0.40;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"1");//寫入數字刻度1
	
	
	x=R*cos((120)*PAI_D180)+0.49;
	y=R*sin((120)*PAI_D180)+0.38;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"11");//寫入數字刻度11
	
	x=R*cos((150)*PAI_D180)+0.55;
	y=R*sin((150)*PAI_D180)+0.42;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"10");//寫入數字刻度10


	x=R*cos((210)*PAI_D180)+0.58;
	y=R*sin((210)*PAI_D180)+0.53;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"8");//寫入數字刻度8

	x=R*cos((240)*PAI_D180)+0.54;
	y=R*sin((240)*PAI_D180)+0.58;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"7");//寫入數字刻度7


	x=R*cos((300)*PAI_D180)+0.43;
	y=R*sin((300)*PAI_D180)+0.58;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"5");//寫入數字刻度5

	x=R*cos((330)*PAI_D180)+0.40;
	y=R*sin((330)*PAI_D180)+0.52;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"4");//寫入數字刻度4
	
    //設置時鐘圓內圓盤的顏色
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(2.0); //設置線寬
    //繪製時鐘圓外圓盤
	glBegin(GL_LINE_STRIP);
		for ( i=0;i<=360;i++)
		{
			 x=R*cos(i*PAI_D180)+0.5;
			 y=R*sin(i*PAI_D180)+0.5;
			glVertex2f(x,y);
		}
	glEnd();
	
	//繪製時鐘內表示小時之間的刻度,用圓點表示	
	float d;
	for (i=0;i<=360;i+=6)
	{

		switch(i)
		{
		case 0: //在N(12點)處
			glColor3f(0.0, 1.0, 1.0);//設置顏色
			glPointSize(4.0); //設置點的大小
			break;
		case 90://在W(9點)處
			glColor3f(0.0, 1.0, 1.0);//設置顏色
			glPointSize(4.0); //設置點的大小
			break;
		case 180://在S(6點)處
			glColor3f(0.0, 1.0, 1.0);//設置顏色
			glPointSize(4.0); //設置點的大小
			break;
		case 270://在E(3點)處
			glColor3f(0.0, 1.0, 1.0);//設置顏色
			glPointSize(4.0); //設置點的大小
			break;
		default:
			glColor3f(0.77, 0.67, 0.95);//設置顏色
			glPointSize(2.0); //設置點的大小
			break;
		}
	
		if(i%30==0 && i%90!=0)//在整時刻處(如7點,8點等)
		{	
			glColor3f(1.0, 0.0, 1.0);//設置顏色
			glPointSize(3.0);//設置點的大小
		}
		
		d=0.04;//偏移量
		x=R*cos(i*PAI_D180)+0.5;//計算x坐標
		y=R*sin(i*PAI_D180)+0.5;//計算y坐標
		
		//繪製點標誌
		glBegin(GL_POINTS);
			x=x-d*cos(i*PAI_D180);
			y=y-d*sin(i*PAI_D180);
			glVertex2f(x,y);
		glEnd();
		}
	glLineWidth(1.0); //設置線寬
	glEndList();//結束顯示列表
	
}

//繪製指北針
void CT3DSystemView::DrawNorthPt()
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //以填充方式繪製
	glDisable(GL_TEXTURE_2D); //關閉紋理		
	float R=0.5;
		
	float x1,y1,x2,y2,x3,y3;
	float mPtangle=25;
	float tempangle;
	float L,L1,L2;
	L1=0.3; 
	L2=0.2;
	x1=0.5;y1=0.5; //時鐘圓心點坐標，指北針圍繞該點進行指向旋轉
	x3=x1+L1*cos((m_NorthPtangle)*PAI_D180);
	y3=y1+L1*sin((m_NorthPtangle)*PAI_D180);

	//如果指北針指向角位於第1象限
	if(m_NorthPtangle>=0 && m_NorthPtangle<=90)
	{	tempangle=m_NorthPtangle-mPtangle;
		L=0.1/cos(mPtangle*PAI_D180);
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1-L2*sin(tempangle*PAI_D180);
		
		glColor3f(1.0, 1.0, 0.0); //設置顏色
		glBegin(GL_TRIANGLES);//繪製左側三角形
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
		
		glColor3f(1.0, 0.0, 0.0); //設置顏色
		tempangle=m_NorthPtangle+mPtangle;
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1-L2*sin(tempangle*PAI_D180);
		glBegin(GL_TRIANGLES);//繪製右側三角形
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
	}

	//如果指北針指向角位於第2象限
	if(m_NorthPtangle>90 && m_NorthPtangle<=180)
	{	

	tempangle=180-m_NorthPtangle-mPtangle;
	x2=x1+L2*cos(tempangle*PAI_D180);
	y2=y1-L2*sin(tempangle*PAI_D180);
	
	glColor3f(1.0, 1.0, 0.0); //設置顏色
	glBegin(GL_TRIANGLES);//繪製左側三角形
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
	glEnd();
	
	glColor3f(1.0, 0.0, 0.0); //設置顏色
	tempangle=180-m_NorthPtangle+mPtangle;
	x2=x1+L2*cos(tempangle*PAI_D180);
	y2=y1-L2*sin(tempangle*PAI_D180);
	glBegin(GL_TRIANGLES);//繪製右側三角形
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
	glEnd();
	}

	//如果指北針指向角位於第3象限
	if(m_NorthPtangle>180 && m_NorthPtangle<=270)
	{	
		
		tempangle=m_NorthPtangle-180-mPtangle;
		x2=x1+L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		
		glColor3f(1.0, 1.0, 0.0);//設置顏色
		glBegin(GL_TRIANGLES);//繪製左側三角形
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
		
		glColor3f(1.0, 0.0, 0.0);//設置顏色
		tempangle=m_NorthPtangle-180+mPtangle;
		x2=x1+L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		glBegin(GL_TRIANGLES);//繪製右側三角形
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
	}

	//如果指北針指向角位於第4象限
	if(m_NorthPtangle>270 && m_NorthPtangle<=360)
	{	
		
		tempangle=360-m_NorthPtangle-mPtangle;
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		
		glColor3f(1.0, 1.0, 0.0);//設置顏色
		glBegin(GL_TRIANGLES);//繪製左側三角形
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
		
		glColor3f(1.0, 0.0, 0.0);//設置顏色
		tempangle=360-m_NorthPtangle+mPtangle;
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		glBegin(GL_TRIANGLES);//繪製右側三角形
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
	}

	glColor3f(0.4, 0.47, 0.72);//設置顏色
	glLineWidth(2.0); //設置線寬
	glBegin(GL_LINES); //指北針下短直線
		glVertex2f(x1,y1);
		x2=x1-0.1*cos((m_NorthPtangle)*PAI_D180);
		y2=y1-0.1*sin((m_NorthPtangle)*PAI_D180);
		glVertex2f(x2,y2);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); 
	glEnable(GL_TEXTURE_2D); //開啟紋理		
	glLineWidth(1.0);//設置線寬
}

//在指定位置輸出文本
void CT3DSystemView::PrintText(float x, float y, char *string)
{
	int length;
	length = (int) strlen(string); //字符串長度
	glRasterPos2f(x,y); //定位當前光標
	for (int m=0;m<length;m++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[m]);//用位圖方式按指定的字體繪製一個字符串
	}
	
}

 //根據相機的視點坐標和觀察點坐標計算時鐘指北針指向角度
void CT3DSystemView::GetNorthPtangle()
{
	if(theApp.bLoginSucceed==FALSE) return;
	
	float dx,dz,ar;
	dx=m_vPosition.x-m_vView.x;//相機視點與觀察點x坐標之差
	dz=m_vPosition.z-m_vView.z;//相機視點與觀察點z坐標之差
	
	if(dx==0) //如果dx==0
	{
		if(dz>=0) //如果dz>=0
			m_NorthPtangle=90; ////指北針初始指向角度=90，指向屏幕裡面（Z軸負方向）
		else
			m_NorthPtangle=270;////指北針初始指向角度=270，指向屏幕外面（Z軸正方向）
	}
	else
	{
		if(dx>0) 
		{
			if(dz>0) //第2象限
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=90+ar*HDANGLE;//指北針初始指向角度
			}
			else    //第3象限
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=270-ar*HDANGLE;//指北針初始指向角度
			}
		}
		
		if(dx<0)
		{
			if(dz>0)  //第1象限
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=90-ar*HDANGLE;//指北針初始指向角度
			}
			else    //第4象限
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=270+ar*HDANGLE;//指北針初始指向角度
			}
		}
		
	}
}


//獲取封閉區域
void CT3DSystemView::GetRoadCloseRegion()
{
	CString tt,m_style,m_style2;
	
	PCordinate pt=NULL;
	mRegions.RemoveAll();
	
	int m_reginNums=0; //封閉區域數
	int mBridgeindex=0;//橋樑索引初始值
	int mTunnelindex=0;//隧道索引初始值

	m_ReginPtsLeft.RemoveAll(); //左邊界封閉區域數據點清空
	m_ReginPtsRight.RemoveAll();//右邊界封閉區域數據點清空

	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	float fPer=100.0/(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1);
	for (long i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
	{

		tt.Format("正在構建線路左側封閉區域,已完成 %.2f%s",(i+1)*fPer,"%");
		pMainFrame->Set_BarText(4 , tt , 0); 
	
		//線路當前斷面交點類型
		m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
		//線路下一斷面交點類型
		m_style2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;
		//如果交點類型非橋樑和隧道點
		if(m_style!="隧道起點" && m_style!="隧道中間點" &&m_style!="隧道終點" \
			&&m_style!="橋樑起點"  &&m_style!="橋樑中間點" &&m_style!="橋樑終點" \
			&& m_style2!="隧道起點")
		{
			//線路當前斷面左側邊坡數
			int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_L-1;
			//線路下一斷面左側邊坡數
			int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_L-1;
			
			//如果相臨兩斷面邊坡填挖類型不同
			if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->TW_left!=\
				myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->TW_left)
			{
				if(N1>=0) //如果線路當前斷面左側邊坡數>=1
				{
					for(int m=N1;m>=0;m--) //從最高一級邊坡開始記錄所有邊坡點
					{
						for(int n=2;n>=0;n--)
						{
							pt=new Cordinate;
							pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].x;
							pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].y;
							pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].z;
							m_ReginPtsLeft.Add(pt);//存儲點坐標數據
						}
						
					}
				}
				else //線路當前斷面左側剛好是填挖平衡點,則直接將路肩邊坡點作為邊界點
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1;
					m_ReginPtsLeft.Add(pt);//存儲點坐標數據
				}

				if(N2>=0) //如果線路下一斷面左側邊坡數>=1
				{
					for(int m=0;m<=N2;m++) //從最低一級邊坡開始記錄所有邊坡點
					{
						for(int n=0;n<=2;n++)
						{
							pt=new Cordinate;
							pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].x;
							pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].y;
							pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].z;
							m_ReginPtsLeft.Add(pt);//存儲點坐標數據
						}
						
					}
				}
				else //線路下一斷面左側剛好是填挖平衡點,則直接將路肩邊坡點作為邊界點
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1;
					m_ReginPtsLeft.Add(pt);//存儲點坐標數據
				}
				
			}
			else //如果相臨兩斷面邊坡填挖類型相同,
			{
				//計算線路當前斷面方興未艾寫入的邊界坐標點數據
				if(N1>=0) //如果線路當前斷面左側邊坡數>=1
				{
					if(N1<=N2) //如果線路當前斷面左側邊坡數<=線路下一斷面左側邊坡數,只記錄當前斷面最高一級邊坡點坐標
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N1].Hp[2].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N1].Hp[2].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N1].Hp[2].z;
						m_ReginPtsLeft.Add(pt);//存儲點坐標數據
					}
					else //如果線路當前斷面左側邊坡數>線路下一斷面左側邊坡數
					{
						for(int m=N2+1;m<=N1;m++) //需要從上至下記錄比下一斷面多出的邊坡所有邊坡點坐標
						{
							for(int n=2;n>=0;n--)
							{
								pt=new Cordinate;
								pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].x;
								pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].y;
								pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].z;
								m_ReginPtsLeft.Add(pt);//存儲點坐標數據
							}
								
						}
						//只需要記錄線路下一斷面的最高一級邊坡點坐標
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N2].Hp[1].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N2].Hp[1].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N2].Hp[1].z;
						m_ReginPtsLeft.Add(pt);//存儲點坐標數據
						
					}
				}
				else  //線路當前斷面左側剛好是填挖平衡點,則直接將路肩邊坡點作為邊界點
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1;
					m_ReginPtsLeft.Add(pt);//存儲點坐標數據
				}

				//計算線路下一斷面方興未艾寫入的邊界坐標點數據
				if(N2>=0) //如果線路下一斷面左側邊坡數>=1
				{
					if(N2<=N1)//如果線路下一斷面左側邊坡數<=線路當前面左側邊坡數,只記錄下一斷面最高一級邊坡點坐標
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N2].Hp[2].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N2].Hp[2].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N2].Hp[2].z;
						m_ReginPtsLeft.Add(pt);//存儲點坐標數據
					}
					else  //如果線路下一斷面左側邊坡數>線路當前斷面左側邊坡數
					{
						for(int m=N1+1;m<=N2;m++)//需要從下至上記錄比當前斷面多出的邊坡所有邊坡點坐標
						{
							for(int n=0;n<=2;n++)
							{
								pt=new Cordinate;
								pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].x;
								pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].y;
								pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].z;
								m_ReginPtsLeft.Add(pt);//存儲點坐標數據
							}
							
						}
						//補充線路下一斷面對應當前斷面最高一級的邊坡點坐標
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N1].Hp[1].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N1].Hp[1].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N1].Hp[1].z;
						m_ReginPtsLeft.Add(pt);//存儲點坐標數據
						
					}
				}
				else  //線路下一斷面左側剛好是填挖平衡點,則直接將路肩邊坡點作為邊界點
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1;
					m_ReginPtsLeft.Add(pt);//存儲點坐標數據
				}
			}	
				
		}
		else //如果交點類型是"隧道起點",表示遇到了隧道起始端
		{
			
			if(m_style=="隧道起點")
			{
				//線路前一交點左側邊坡數
				int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->Huponums_L-1;
				for(int j=N1;j>0;j--) //記錄線路前一斷面左側所有邊坡點
				{
					for(int k=2;k>=0;k--) //每一級邊坡由3個點組成
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_L[j].Hp[k].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_L[j].Hp[k].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_L[j].Hp[k].z;
						m_ReginPtsLeft.Add(pt);//存儲點坐標數據
						
					}
				}

				//得到隧道進口洞門處的所有坐標點數據,作為邊界點數據
				int M=myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_Start.GetSize();
				for(int k=0;k<M;k++)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_Start.GetAt(k)->x;
					pt->y =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_Start.GetAt(k)->y;
					pt->z =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_Start.GetAt(k)->z;
					m_ReginPtsLeft.Add(pt);//存儲點坐標數據
				}

				WriteRegionPts(m_reginNums,TRUE,-1);//當前封閉區域結束,寫入左側邊界點坐標數據
				m_ReginPtsLeft.RemoveAll();//數組清空
				m_reginNums++; //封閉區域數+1
							
			}
			else if(m_style=="橋樑起點") //如果交點類型是"橋樑起點"
			{
				//得到該橋樑起始點處下試試看護坡點數,,作為邊界點數據
				int M=myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_Start.GetSize();
				for(int k=0;k<M;k++)
				{
					
					pt=new Cordinate;
					pt->x =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_Start.GetAt(k)->x;
					pt->y =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_Start.GetAt(k)->y;
					pt->z =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_Start.GetAt(k)->z;
					m_ReginPtsLeft.Add(pt);//存儲點坐標數據
					
				}
				WriteRegionPts(m_reginNums,TRUE,-1);//當前封閉區域結束,寫入左側邊界點坐標數據
				m_ReginPtsLeft.RemoveAll();//數組清空
				m_reginNums++;//封閉區域數+1
				
			}			
			
			else if (m_style=="隧道終點")//如果交點類型是"隧道終點",表示遇到了隧道終止端,表示新的封閉區域開始了
			{
				
				//得到隧道出口洞門處的所有坐標點數據,作為邊界點數據
				int M=myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_End.GetSize();
				for(int k=M-1;k>=0;k--)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_End.GetAt(k)->x;
					pt->y =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_End.GetAt(k)->y;
					pt->z =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_End.GetAt(k)->z;
					m_ReginPtsLeft.Add(pt);//存儲點坐標數據
					
				}

				//線路下一斷面左側邊坡數
				int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_L-1;
                //補充線路下一斷面左側第1級連坡的最高點坐標
				pt=new Cordinate;
				pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[0].Hp[2].x;
				pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[0].Hp[2].y;
				pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[0].Hp[2].z;
				m_ReginPtsLeft.Add(pt);//存儲點坐標數據
				
				//記錄線路下一斷面左側邊坡第2級到最調到級所有邊坡點坐標,作為邊界點數據
				for(int j=1;j<=N1;j++)
				{
					for(int k=0;k<=2;k++)
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[k].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[k].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[k].z;
						m_ReginPtsLeft.Add(pt);//存儲點坐標數據
					}
				}
				mTunnelindex++; //到了隧道終止端,表示一座隧道結束了,隧道索引+1
			}
			
			else if (m_style=="橋樑終點") //如果交點類型是"橋樑終點",表示遇到了橋樑終止端,表示新的封閉區域開始了
			{
				
				//得到橋樑結束處下方的所有護坡點坐標數據,作為邊界點數據
				int M=myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_End.GetSize();
				for(int k=M-1;k>=0;k--)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_End.GetAt(k)->x;
					pt->y =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_End.GetAt(k)->y;
					pt->z =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_End.GetAt(k)->z;
					m_ReginPtsLeft.Add(pt);//存儲點坐標數據
					
				}

				mBridgeindex++; //到了橋樑終止端,表示一座橋樑結束了,橋樑索引號+1
			}
			
			
		}

	}

	m_reginNums=0;
	m_ReginPtsRight.RemoveAll(); //右側邊界點清空
	for ( i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		tt.Format("正在構建線路右側封閉區域,已完成 %.2f%s",(i+1)*fPer,"%");
		pMainFrame->Set_BarText(4 , tt , 0); 

		//線路當前斷面交點類型
		m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
 		//線路下一斷面交點類型
		m_style2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;
		
		//如果交點類型非橋樑和隧道點
		if(m_style!="隧道起點" && m_style!="隧道中間點" &&m_style!="隧道終點"\
			&&m_style!="橋樑起點"  &&m_style!="橋樑中間點" &&m_style!="橋樑終點" \
			&&m_style2!="隧道起點")
		{
			//線路當前斷面右側邊坡數
			int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_R-1;
			//線路下一斷面右側邊坡數
			int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_R-1;
			//如果相臨兩斷面邊坡填挖類型不同
			if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->TW_right!=\
				myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->TW_right)
			{
				if(N1>=0)  //如果線路當前斷面右側邊坡數>=1
				{
					for(int m=N1;m>=0;m--) //從最高一級邊坡開始記錄所有邊坡點
					{
						for(int n=2;n>=0;n--)
						{
							pt=new Cordinate;
							pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].x;
							pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].y;
							pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].z;
							m_ReginPtsRight.Add(pt);//存儲點坐標數據
						}
						
					}
				}
				else//線路當前斷面右側剛好是填挖平衡點,則直接將路肩邊坡點作為邊界點
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2;
					m_ReginPtsRight.Add(pt);
				}
				
				if(N2>=0) //如果線路下一斷面右側邊坡數>=1
				{
					for(int m=0;m<=N2;m++) //從最低一級邊坡開始記錄所有邊坡點
					{
						for(int n=0;n<=2;n++)
						{
							pt=new Cordinate;
							pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].x;
							pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].y;
							pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].z;
							m_ReginPtsRight.Add(pt);//存儲點坐標數據
						}
						
					}
				}
				else//線路下一斷面右側剛好是填挖平衡點,則直接將路肩邊坡點作為邊界點
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2;
					m_ReginPtsRight.Add(pt);//存儲點坐標數據
				}
				
			}
			else//如果相臨兩斷面邊坡填挖類型相同
			{
				//計算線路當前斷面左側邊界坐標點數據
				if(N1>=0) //如果線路當前斷面右側邊坡數>=1
				{
					if(N1<=N2)//如果線路當前斷面右側邊坡數<=線路下一斷面右側邊坡數,只記錄當前斷面最高一級邊坡點坐標
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N1].Hp[2].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N1].Hp[2].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N1].Hp[2].z;
						m_ReginPtsRight.Add(pt);//存儲點坐標數據
					}
					else //如果線路當前斷面右側邊坡數>線路下一斷面右側邊坡數
					{
						for(int m=N2+1;m<=N1;m++) //需要從上至下記錄比下一斷面多出的邊坡所有邊坡點坐標
						{
							for(int n=2;n>=0;n--)
							{
								pt=new Cordinate;
								pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].x;
								pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].y;
								pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].z;
								m_ReginPtsRight.Add(pt);//存儲點坐標數據
							}
						}
						//只需要記錄線路下一斷面的最高一級邊坡點坐標
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N2].Hp[1].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N2].Hp[1].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N2].Hp[1].z;
						m_ReginPtsRight.Add(pt);//存儲點坐標數據
					}		
				}
				else //線路當前斷面右側剛好是填挖平衡點,則直接將路肩邊坡點作為邊界點
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2;
					m_ReginPtsRight.Add(pt);	//存儲點坐標數據
				}
			
				//計算線路下一斷面應該寫入的邊界坐標點數據
				if(N2>=0) //如果線路下一斷面右側邊坡數>=1
				{				
					if(N2<=N1)//如果線路下一斷面右側邊坡數<=線路當前面右側邊坡數,只記錄下一斷面最高一級邊坡點坐標
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N2].Hp[2].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N2].Hp[2].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N2].Hp[2].z;
						m_ReginPtsRight.Add(pt);//存儲點坐標數據
					}
					else//如果線路下一斷面右側邊坡數>線路當前斷面右側邊坡數
					{
						for(int m=N1+1;m<=N2;m++)//需要從下至上記錄比當前斷面多出的邊坡所有邊坡點坐標
						{
							for(int n=0;n<=2;n++)
							{
								pt=new Cordinate;
								pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].x;
								pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].y;
								pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].z;
								m_ReginPtsRight.Add(pt);//存儲點坐標數據
							}
						}
						//補充線路下一斷面對應當前斷面最高一級的邊坡點坐標
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N1].Hp[1].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N1].Hp[1].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N1].Hp[1].z;
						m_ReginPtsRight.Add(pt);//存儲點坐標數據
						
					}
				}
				else  //線路下一斷面右側剛好是填挖平衡點,則直接將路肩邊坡點作為邊界點
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2;
					m_ReginPtsRight.Add(pt);//存儲點坐標數據
				}
			}
		}
		else
		{
			if(m_style=="隧道起點") //如果交點類型是"隧道起點",表示遇到了隧道起始端
			{
				//線路前一交點右側邊坡數
				int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->Huponums_R-1;
				for(int j=N1;j>0;j--)//記錄線路前一斷面右側所有邊坡點
				{
					for(int k=2;k>=0;k--)//每一級邊坡由3個點組成
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_R[j].Hp[k].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_R[j].Hp[k].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_R[j].Hp[k].z;
						m_ReginPtsRight.Add(pt);//存儲點坐標數據
						
					}
				}

				WriteRegionPts(m_reginNums,FALSE,1); //當前封閉區域結束,寫入右側邊界點坐標數據
				m_ReginPtsRight.RemoveAll();//數組清空
				m_reginNums++;//封閉區域數+1
				
			}
			else if(m_style=="橋樑起點")//如果交點類型是"橋樑起點"
			{
				WriteRegionPts(m_reginNums,FALSE,1);//當前封閉區域結束,寫入右側邊界點坐標數據
				m_ReginPtsRight.RemoveAll();//數組清空
				m_reginNums++;//封閉區域數+1
				
			}			
			else if(m_style=="隧道終點")//如果交點類型是"隧道終點",表示遇到了隧道終止端,表示新的封閉區域開始了
			{

				//得到隧道出口洞門處的所有坐標點數據,作為邊界點數據
				int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_R-1;
				for(int j=1;j<=N1;j++)
				{
					for(int k=0;k<=2;k++)
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[k].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[k].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[k].z;
						m_ReginPtsRight.Add(pt);//存儲點坐標數據
					}
				}
				mTunnelindex++;//到了隧道終止端,表示一座隧道結束了,隧道索引+1
			}
			
			else if (m_style=="橋樑終點")//如果交點類型是"橋樑終點",表示遇到了橋樑終止端,表示新的封閉區域開始了
			{
				mBridgeindex++;//到了橋樑終止端,表示一座橋樑結束了,橋樑索引號+1
			}
		}
		
	}

	//對不合理的邊蜀區域進行清理
	for(i=0;i<mRegions.GetSize();i++)
	{
		if(mRegions.GetAt(i)->ReginPts.GetSize()<=1) //如果封閉區域數據點<=1
		{
			mRegions.RemoveAt(i);//移除
		}
	}
}

//繪製經過線路建三維模後的三維地形TIN
void CT3DSystemView::DrawTerrainDelaunay()
{
	
	if(b_haveTerrainZoomroadList==TRUE)   //如果已成構建線路三維模型的顯示列表
	{
		glCallList(m_TerrainZoomroadList);
		return;
	}


	if(m_currentSchemeIndexs<0) //如果當前線路方案索引<0，返回
		return;
	
	if(	b_haveGetRegion==TRUE) //如果已經獲取線路封閉區域，返回
		return;
	//沒有經過線路三維建模返回
	if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()<=1)
		return;
	if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()<=1)
		return;
	
	BeginWaitCursor();
	
	CString m_style,m_style2;
	long i;

	//創建線路三維建模後是否建立了地形TIN模型的顯示列表
	glNewList(m_TerrainZoomroadList,GL_COMPILE_AND_EXECUTE);
	
	glPushAttrib(GL_TEXTURE_BIT|GL_POLYGON_BIT);
	glDisable(GL_TEXTURE_2D); //關閉紋理
	glLineWidth(2.0); //設置線寬
	glColor3f(0.2,0,1.0); //設置顏色
	
	GetRoadCloseRegion();//獲取封閉區域
	BuildTerrainRegionInfo(); //計算每個地形塊連同封閉區域的所有地形數據集
	m_BlockTriInfos.RemoveAll(); //地形塊三角網信息清空
	
	CString tt;
	float fPer=100.0/m_BlockLSPts.GetSize();
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	for( i=0;i<m_BlockLSPts.GetSize();i++)   
	{
		tt.Format("正在繪製地形TIN模型,已完成 %.2f%s",(i+1)*fPer,"%");
		pMainFrame->Set_BarText(4 , tt , 0); 
		
		DrawTerrainTIN(i); //以TIN方式繪製地形塊i
		tempBlockTriInfos=new BlockTriInfos;
		for_each(m_Triangles.begin(), m_Triangles.end(), GetBlockTriangles(i));
		AddBlcokTri(i,m_BlockLSPts.GetAt(i)->mDemBlockRow,m_BlockLSPts.GetAt(i)->mDemBlockCol);//加入當前地形塊有三角網數據(同時要剔除位於線路封閉區域的所有三角形)
	}
	glEndList();
	b_haveTerrainZoomroadList=TRUE;//線路三維建模後是否建立了地形TIN模型的顯示列表
	EndWaitCursor();
	MessageBox("建模完成","線路三維建模",MB_ICONINFORMATION);
	pMainFrame->Set_BarText(4 , "加載地形與影像紋理數據完成!" , 0); 
}

//將邊界點坐標數據寫入封閉區域
void CT3DSystemView::WriteRegionPts(int index, BOOL bAddorAppend, int mLeftorRight)
{
	PRegions tempregion=new Regions;
	PCordinate pt=NULL;
	
	if(bAddorAppend==TRUE)  //如果是增加邊界點，mRegions數組新增加元素
	{
		tempregion->index=index; //封閉區域索引
		for(long i=0;i<m_ReginPtsLeft.GetSize();i++)//所有左邊界點數據
		{
			pt=new Cordinate;
			pt->x=m_ReginPtsLeft.GetAt(i)->x;
			pt->y=m_ReginPtsLeft.GetAt(i)->y;
			pt->z=m_ReginPtsLeft.GetAt(i)->z;
			tempregion->ReginPts.Add(pt);//存儲到臨時數組中
		}
		mRegions.Add(tempregion);//加入邊界數據
	}
	else if(bAddorAppend==FALSE)  //如果不是新增數據，直接向mRegions數組索引位置寫入數據
	{
		//所有右邊界點數據
		for(long i=m_ReginPtsRight.GetSize()-1;i>=0;i--)
		{
			pt=new Cordinate;
			pt->x=m_ReginPtsRight.GetAt(i)->x;
			pt->y=m_ReginPtsRight.GetAt(i)->y;
			pt->z=m_ReginPtsRight.GetAt(i)->z;
			mRegions.GetAt(index)->ReginPts.Add(pt);//加入右邊界點數據
		}
		m_ReginPtsRight.RemoveAll();//右邊界點數組清空
		
		
	}
}

//根據封閉區域邊界上的數據點，計算該封閉區域穿越的地形塊ID號
//若封閉區域穿越多個地形塊，則其記錄的地形塊ID號也有多個
void CT3DSystemView::GetRegionID(long index)
{
	double x,y;
	int ID;
	mRegions.GetAt(index)->GridID.RemoveAll();
	for(long i=0;i<mRegions.GetAt(index)->ReginPts.GetSize();i++)
	{
		
		x=mRegions.GetAt(index)->ReginPts.GetAt(i)->x;//封閉區域邊界上的數據點的x坐標	
		y=-mRegions.GetAt(index)->ReginPts.GetAt(i)->z;//封閉區域邊界上的數據點的y坐標
		
		ID=GetBlockID(x,y);	//根據x,y坐標求取所屬於的地形塊的ID號
		
		bool bhaveExit=FALSE; //初始標識為FALSE
		for(int k=0;k<mRegions.GetAt(index)->GridID.GetSize();k++)
		{
			int mid=mRegions.GetAt(index)->GridID.GetAt(k);
			if(ID==mid) //如果求得地形塊ID號在記錄中的ID號相同，則忽略，不再記錄
			{
				bhaveExit=TRUE;
				break;
			}
		}
		if(bhaveExit==FALSE) ////如果求得地形塊ID號與所有記錄中的ID號不同，則記錄
			mRegions.GetAt(index)->GridID.Add(ID);//記錄ID號
	}
}

//計算每個地形塊連同封閉區域的所有地形數據集
void CT3DSystemView::BuildTerrainRegionInfo()
{
	//如果沒有地形數據
	if(theApp.m_BlockRows*theApp.m_BlockCols<=0)
		return;

	long i,j;
	//計算每個封閉子區域的最小最大x,y坐標
	for( i=0;i<mRegions.GetSize();i++)
	{
		GetRegionID(i);//得到封閉區域ID
		double minx,miny,maxx,maxy;
		minx=miny=999999999;
		maxx=maxy=-999999999;
		//計算封閉最大,最小坐標
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
	
	b_haveGetRegion=TRUE; //標識已計算封閉區域為TRUE

	//重新定義數組大小，並分配內存
	mBlockReginInforMe=new CArray<PBlockReginInforMe,PBlockReginInforMe>[theApp.m_BlockRows*theApp.m_BlockCols];
	m_BlockLSPts.RemoveAll();//清空

	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	float fper=100.0/(theApp.m_BlockRows*theApp.m_BlockCols);
	CString tt;
	for(i=1;i<=theApp.m_BlockRows;i++)
	{
		for( j=1;j<=theApp.m_BlockCols;j++)
		{
			tt.Format("正在計算每個地形塊連同封閉區域的所有地形數據集,已完成 %.2f%s",i*j*fper,"%");
			pMainFrame->Set_BarText(4 , tt , 0); 
			
			GetBlockInregion(i,j); //得到地形塊封閉區域信息
			WriteBlockLsPts(i,j);//將地形塊封閉區域信息寫入
		}
	}
}

//繪製地形塊三角網地形
void CT3DSystemView::DrawTerrainTIN(long blockIndex)
{
	m_Vertices.clear(); //頂點清除
	m_Triangles.clear();//三角形清除
	double x,y,z;
	
	CDelaunay d; //定義CDelaunay變量
	//獲取某個地形塊內所有有效地形數據點,參與地形三角網的構建
	for(long j=0;j<m_BlockLSPts.GetAt(blockIndex)->ReginPts.GetSize();j++)
	{
		x=m_BlockLSPts.GetAt(blockIndex)->ReginPts.GetAt(j)->x; //x坐標
		y=-m_BlockLSPts.GetAt(blockIndex)->ReginPts.GetAt(j)->z;//y坐標
		z=m_BlockLSPts.GetAt(blockIndex)->ReginPts.GetAt(j)->y;//z坐標(高程)
		if(z!=theApp.m_DEM_IvalidValue) //如果高程是無效值,將不參與三角網構建
			m_Vertices.insert(vertex(x, y,z));
	}
	d.Triangulate(m_Vertices, m_Triangles);//根據地形數據點(m_Vertices中存儲)構建地形三角網
}

//加入當前地形塊有三角網數據(同時要剔除位於線路封閉區域的所有三角形)
void CT3DSystemView::AddBlcokTri(int blockIndex, int DemblcokRow, int DemblcokCol)
{
	for(long i=0;i<tempBlockTriInfos->TriPts.GetSize();i++)
	{
		//判斷地形塊TIN三角形是否位於地形塊內封閉區域內
		BOOL bOk=GetTriOutRegion(\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt1.x,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt1.y,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt2.x,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt2.y,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt3.x,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt3.y,\
			blockIndex);
		if(bOk==TRUE) //如果三角形是位於地形塊內封閉區域內,以x坐標=-9999來標識
			tempBlockTriInfos->TriPts.GetAt(i)->Pt1.x=-9999;
	}
	
	tempBlockTriInfos->mDemBlockRow=DemblcokRow;//當前地形塊的行號
	tempBlockTriInfos->mDemBlockCol=DemblcokCol;//當前地形塊的列號
	m_BlockTriInfos.Add(tempBlockTriInfos);//加入當前地形塊的三角網信息
}

//判斷地形塊TIN三角形是否位於地形塊內封閉區域內
BOOL CT3DSystemView::GetTriOutRegion(double x1, double y1, double x2, double y2, double x3, double y3, int blockIndex)
{
	Point *polygon;	
	Point pt;
	bool b1,b2,b3;	
	int m_a1,m_a2,m_a3;
	m_a1=m_a2=m_a3=0; //初始標識為0

	//對當前地形塊內共有的封閉區域進行判斷
	//mBlockReginInforMe[blockIndex].GetSize()：當前地形塊內共有的封閉區域總數
	for(int i=0;i<mBlockReginInforMe[blockIndex].GetSize();i++)
	{
		//如果三角形的三個點全部位於封閉區域最大最小矩形邊界之外
		//則該三角形必位於封閉區域外,不需用剔除
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
			m_a1=m_a2=m_a3=0;//3點都位於封閉區域內，三點標識全為0
		}
		else
		{
			//讀取封閉區域所有的邊界點
			long M=mBlockReginInforMe[blockIndex].GetAt(i)->ReginPts.GetSize();
			polygon=new Point[M];
			for(long j=0;j<M;j++)
			{
				polygon[j].x=mBlockReginInforMe[blockIndex].GetAt(i)->ReginPts.GetAt(j)->x;
				polygon[j].y=-mBlockReginInforMe[blockIndex].GetAt(i)->ReginPts.GetAt(j)->z;
			}
			
			
			pt.x=x1; pt.y=y1;
			b1=mCalF.InPolygon(polygon,M,pt);//判斷點(x1,y1)是否位於該封閉區域內
			if(b1==true) //如果位於
				m_a1=1;
			
			pt.x=x2; pt.y=y2;
			b2=mCalF.InPolygon(polygon,M,pt);//判斷點(x2,y2)是否位於該封閉區域內
			if(b2==true)//如果位於
				m_a2=1;
			
			pt.x=x3; pt.y=y3;//判斷點(x3,y3)是否位於該封閉區域內
			b3=mCalF.InPolygon(polygon,M,pt);
			if(b3==true)//如果位於
				m_a3=1;
			
			//如果3點都位於內部或在封閉區域邊界上,需要進一步判斷
			//因為如果3點都位於封閉區域邊界上,該三角形實際上是位於封閉區域之外 ,不需要刪除
			if(m_a1==1 && m_a2==1 && m_a3==1)
			{
				pt.x=(x1+x2)/2; pt.y=(y1+y2)/2; //(x1,y1)和(x2,y2)中點坐標
				b1=mCalF.InPolygon(polygon,M,pt);//判斷中點否位於該封閉區域內
				if(b1==false)//如果不位於
					m_a1=0;
				
				if(m_a1==1) //如果(x1,y1)和(x2,y2)中點坐標位於該封閉區域內
				{
					pt.x=(x2+x3)/2; pt.y=(y2+y3)/2;//(x2,y2)和(x3,y3)中點坐標
					b1=mCalF.InPolygon(polygon,M,pt);//判斷中點否位於該封閉區域內
					if(b2==false)//如果不位於
						m_a2=0;
				}
				
				if(m_a1==1 && m_a2==1) //如果(x1,y1)和(x2,y2)以及(x2,y2)和(x3,y3)的中點坐標位於該封閉區域內
				{
					pt.x=(x1+x3)/2; pt.y=(y1+y3)/2;//(x1,y1)和(x3,y3)中點坐標
					b3=mCalF.InPolygon(polygon,M,pt);
					if(b3==false)//如果不位於
						m_a3=0;
				}
			} 
			
			
			
			if(m_a1+m_a2+m_a3>=3) //如果三角形的3點以及三邊中點都位於封閉區域內, 則該三維形位於封閉區域內
			{
				return TRUE; //返回TURE,表示三角形位於封閉區域內,需要剔除
				break;
				
			}
		}
	}
	
	return FALSE;//返回FALSE,表示三角形不位於封閉區域內,不需要剔除
}

//得到地形塊封閉區域信息
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

	block_minx=(blockCol-1)*theApp.m_Dem_BlockWidth;//地形塊最小x坐標
	block_maxx=blockCol*theApp.m_Dem_BlockWidth;//地形塊最大x坐標
	block_miny=(blockRow-1)*theApp.m_Dem_BlockWidth;//地形塊最小y坐標
	block_maxy=blockRow*theApp.m_Dem_BlockWidth;//地形塊最大y坐標
	
	int Mnus;
	PCordinate pt;
	Point  edgePts[4];
	
	long iNdex=(blockRow-1)*theApp.m_BlockCols+(blockCol-1);//根據行列號計算地形塊在所有地形塊中的索引
	PBlockReginInforMe tempReginInforMe;
	
	for(long i=0;i<mRegions.GetSize();i++)
	{
		tempReginInforMe=new BlockReginInforMe;
		//如果
		//(1)當前封閉區域的最小x坐標>=地形塊最小x坐標
		//(2)當前封閉區域的最大x坐標<=地形塊最大x坐標
		//(3)當前封閉區域的最小y坐標>=地形塊最小y坐標
		//(4)當前封閉區域的最大y坐標<=地形塊最大y坐標
		///四個條件全滿足時,表示該封閉子區域完全位於當前地形塊內
		if(mRegions.GetAt(i)->minx>=block_minx &&\
			mRegions.GetAt(i)->maxx<=block_maxx&&\
			mRegions.GetAt(i)->miny>=block_miny &&\
			mRegions.GetAt(i)->maxy<=block_maxy)
		{
			//拷貝封閉區域數據點
			tempReginInforMe->ReginPts.Copy(mRegions.GetAt(i)->ReginPts);
			tempReginInforMe->minx=mRegions.GetAt(i)->minx;
			tempReginInforMe->miny=mRegions.GetAt(i)->miny;
			tempReginInforMe->maxx=mRegions.GetAt(i)->maxx;
			tempReginInforMe->maxy=mRegions.GetAt(i)->maxy;
			mBlockReginInforMe[iNdex].Add(tempReginInforMe);//
		}
		else 
		{
			//如果
			//(1)當前封閉區域的最小x坐標>地形塊最大x坐標
			//(2)當前封閉區域的最大x坐標<地形塊最小x坐標
			//(3)當前封閉區域的最小y坐標>地形塊最大y坐標
			//(4)當前封閉區域的最大y坐標<地形塊最小y坐標
			//四個條件滿足其中之一時,是封閉子區域必不位於地形塊內
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
				    //如果點(x,y,z)位於地形塊內(包括在地形塊邊界上)
					if(x>=block_minx &&	x<=block_maxx&&\
						y>=block_miny && y<=block_maxy)
					{
						bInCur=1; //標識封閉區域邊界點Pi(x,y,z)位於地形塊內
						
						if(j>0 && bInCur*bInPre==-1)
						{
							//計算封閉子區域與當前地形塊四條邊界線的交點坐標,求得的交點坐標
							//也將作為該地形塊的數據點參與地形繪製.
							GetBlockEdgeJd(block_minx,block_miny,block_maxx,block_maxy,i,j,&Mnus,edgePts);
							for(int k=0;k<Mnus;k++)
							{
								pt=new Cordinate;
								pt->x=edgePts[k].x;pt->y=edgePts[k].y;pt->z=edgePts[k].z;
								tempReginInforMe->ReginPts.Add(pt);//記錄數據點
							}
						}
						
						pt=new Cordinate;
						pt->x=x;pt->y=z;pt->z=-y;//坐標變換
						tempReginInforMe->ReginPts.Add(pt);//記錄數據點
						
					}
					else 
					{
						bInCur=-1;//標識封閉區域邊界點Pi(x,y,z)位於地形塊外 
						if(j>0 && bInCur*bInPre==-1)
						{
							//計算封閉子區域與當前地形塊四條邊界線的交點坐標,求得的交點坐標
							//也將作為該地形塊的數據點參與地形繪製.
							GetBlockEdgeJd(block_minx,block_miny,block_maxx,block_maxy,i,j,&Mnus,edgePts);
							for(int k=0;k<Mnus;k++) //將位於地形塊內的部分邊界點存儲
							{
								pt=new Cordinate;
								pt->x=edgePts[k].x;pt->y=edgePts[k].y;pt->z=edgePts[k].z;
								tempReginInforMe->ReginPts.Add(pt);//記錄數據點
							}
						}
						
					}
					bInPre=bInCur;
				}

				//計算最小最大x,y坐標
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
				mBlockReginInforMe[iNdex].Add(tempReginInforMe);//記錄封閉區域信息
			}
		}
	}
}

//寫入地形塊的坐標數據
void CT3DSystemView::WriteBlockLsPts(long Blcokrow, long Blcokcol)
{
	PBlockLSPts tempBlockLSPts=new BlockLSPts;
	
	tempBlockLSPts->ReginPts.RemoveAll();
	
	PCordinate pt=new Cordinate;
	double x,y,z;
	long INX,mTerrainBlockID;
	mTerrainBlockID=(Blcokrow-1)*theApp.m_BlockCols+Blcokcol-1;//地形塊的ID號

    //根據地形塊的分塊大小,依次將所有地形數據點寫入地形塊封閉區域數組中
	for(int i=0;i<theApp.m_Dem_BlockSize;i++)
	{
		for (int j=0;j<theApp.m_Dem_BlockSize;j++)
		{
			
			x=(Blcokcol-1)*theApp.m_Dem_BlockWidth+j*theApp.m_Cell_xwidth;//轉換後的X坐標
			y=(Blcokrow-1)*theApp.m_Dem_BlockWidth+i*theApp.m_Cell_ywidth;//轉換後的Y坐標
			
			INX=i*theApp.m_Dem_BlockSize+j;
			z=m_pHeight_My[mTerrainBlockID][INX];//求得對應的高程值
			
            pt=new Cordinate;
			pt->x =x;
			pt->y=z;
			pt->z =-y;
			tempBlockLSPts->ReginPts.Add(pt);//加入數據點
		}
	}
	
	//加入封閉區域位於地形塊或與地形塊邊界相交的數據點
	long iNdex=(Blcokrow-1)*theApp.m_BlockCols+(Blcokcol-1);
	for(int k=0;k<mBlockReginInforMe[iNdex].GetSize();k++)
	{
		tempBlockLSPts->ReginPts.Append(mBlockReginInforMe[iNdex].GetAt(k)->ReginPts);
	}
	
	tempBlockLSPts->mDemBlockRow=Blcokrow; //當前地形塊對應的行號
	tempBlockLSPts->mDemBlockCol=Blcokcol; //當前地形塊對應的殞號
	m_BlockLSPts.Add(tempBlockLSPts);//當前地形塊的所有數據點
	
}

//計算封閉子區域與當前地形塊四條邊界線的交點坐標,求得的交點坐標
//也將作為該地形塊的數據點參與地形繪製.
void CT3DSystemView::GetBlockEdgeJd(double block_minx, double block_miny, double block_maxx, double block_maxy, long RegionsIndex, long ReginPtsIndex, int *jdNus, Point edgePts[])
{
	Point p1,p2,q1,q2,crossPoint;
	
	int m=0; //初始交點數為0
	bool bCross=false; //初始不相交
	
	//當前封閉區域相臨兩邊界點
	q1.x=mRegions.GetAt(RegionsIndex)->ReginPts.GetAt(ReginPtsIndex)->x;
	q1.y=-mRegions.GetAt(RegionsIndex)->ReginPts.GetAt(ReginPtsIndex)->z;
	q2.x=mRegions.GetAt(RegionsIndex)->ReginPts.GetAt(ReginPtsIndex-1)->x;
	q2.y=-mRegions.GetAt(RegionsIndex)->ReginPts.GetAt(ReginPtsIndex-1)->z;
	
	
	//地形塊上邊界線
	p1.x =block_minx;p1.y=block_maxy;
	p2.x =block_maxx;p2.y=block_maxy;
	
	//計算是p1p2直線與q1q2直線是否相交
	crossPoint =mCalF.GetCrossPoint(p1,p2,q1,q2,&bCross);
	if(bCross==true)  //如果相交,表明與地形塊上邊界線相交
	{
		edgePts[m].x=crossPoint.x; //記錄交點x坐標
		edgePts[m].z=-crossPoint.y;//記錄交點z坐標
		//從DEM中內插出高程,求得交點y坐標
		edgePts[m].y=m_demInsert.GetHeightValue(edgePts[m].x+theApp.m_DemLeftDown_x,-edgePts[m].z+theApp.m_DemLeftDown_y,2);
		m++; //交點數加1
	}
	
	//地形塊左邊界線
	p1.x =block_minx;p1.y=block_maxy;
	p2.x =block_minx;p2.y=block_miny;
	
	//計算是p1p2直線與q1q2直線是否相交
	crossPoint =mCalF.GetCrossPoint(p1,p2,q1,q2,&bCross);
	if(bCross==true) //如果相交,表明與地形塊左邊界線相交
	{
		edgePts[m].x=crossPoint.x;//記錄交點x坐標
		edgePts[m].z=-crossPoint.y;//記錄交點z坐標
		//從DEM中內插出高程,求得交點y坐標
		edgePts[m].y=m_demInsert.GetHeightValue(edgePts[m].x+theApp.m_DemLeftDown_x,-edgePts[m].z+theApp.m_DemLeftDown_y,2);
		m++;//交點數加1
	}
	
	//地形塊下邊界線
	p1.x =block_minx;p1.y=block_miny;
	p2.x =block_maxx;p2.y=block_miny;
	
	//計算是p1p2直線與q1q2直線是否相交
	crossPoint =mCalF.GetCrossPoint(p1,p2,q1,q2,&bCross);
	if(bCross==true) //如果相交,表明與地形塊下邊界線相交
	{
		edgePts[m].x=crossPoint.x;//記錄交點x坐標
		edgePts[m].z=-crossPoint.y;//記錄交點z坐標
		//從DEM中內插出高程,求得交點y坐標
		edgePts[m].y=m_demInsert.GetHeightValue(edgePts[m].x+theApp.m_DemLeftDown_x,-edgePts[m].z+theApp.m_DemLeftDown_y,2);
		m++;//交點數加1
	}
	
	//地形塊右邊界線
	p1.x =block_maxx;p1.y=block_maxy;
	p2.x =block_maxx;p2.y=block_miny;

	//計算是p1p2直線與q1q2直線是否相交
	crossPoint =mCalF.GetCrossPoint(p1,p2,q1,q2,&bCross);
	if(bCross==true)//如果相交,表明與地形塊右邊界線相交
	{
		edgePts[m].x=crossPoint.x;
		edgePts[m].z=-crossPoint.y;
		//從DEM中內插出高程,求得交點y坐標
		edgePts[m].y=m_demInsert.GetHeightValue(edgePts[m].x+theApp.m_DemLeftDown_x,-edgePts[m].z+theApp.m_DemLeftDown_y,2);
		m++;//交點數加1
	}
	
	*jdNus=m; //返回求得交點數		
}



//根據地形點的x,y 人材計算該地形點所屬的在形塊ID號
int CT3DSystemView::GetBlockID(double x, double y)
{
	//	theApp.m_BlockCols//DEM塊總列數
	//	theApp.m_BlockRows;//DEM塊總行數
	//	theApp.m_Dem_BlockWidth//每個DEM塊寬度
	//	所屬於行,列計算方法
	
	int mrow,mcol;
	if((y/theApp.m_Dem_BlockWidth)==(int)(y/theApp.m_Dem_BlockWidth))
		mrow=y/theApp.m_Dem_BlockWidth;
	else
		mrow=(int)(y/theApp.m_Dem_BlockWidth)+1;
	if(mrow<=0) //如果行號<=0,行號=1
		mrow=1;
	
	if((x/theApp.m_Dem_BlockWidth)==(int)(x/theApp.m_Dem_BlockWidth))
		mcol=x/theApp.m_Dem_BlockWidth;
	else
		mcol=(int)(x/theApp.m_Dem_BlockWidth)+1;
	if(mcol<=0)//如果列號<=0,列號=1
		mcol=1;
	int ID=(mrow-1)*theApp.m_BlockCols+mcol;
	return ID; //返回ID號
}

//設置飛行路徑
void CT3DSystemView::OnPathManuinput() 
{
	m_ShowFlyPath=TRUE;  //標識是否顯示飛行路徑
	m_QueryType=SELECTFLYPATH;//進行飛行路徑選擇
	m_FlayPath.RemoveAll();//存儲進行飛行路徑坐標數組清空
}

//繪製飛行路徑
void CT3DSystemView::DrawFlyPath()
{
	//如果顯示飛行路徑並且飛行路徑坐標點數>1,才繪製飛行路徑
	if(m_ShowFlyPath==TRUE  && m_FlayPath.GetSize()>1)//進行飛行路徑選擇
	{
		glPushMatrix(); //壓入矩陣堆棧
		glDisable(GL_TEXTURE_2D);//關閉紋理(即飛行路徑不採用紋理)
		glLineWidth(3.0);//設置飛行路徑線寬
		glColor3f(0,1,1); //設置飛行路徑顏色
		if(m_ViewType==GIS_VIEW_ORTHO)	//繪製正射投影模式下的飛行路徑
		{
			glBegin(GL_LINE_STRIP); //以折線方式繪製飛行路徑
			for(int i=0;i<m_FlayPath.GetSize();i++)
				glVertex2f(GetOrthoX(m_FlayPath.GetAt(i)->x),GetOrthoY(-m_FlayPath.GetAt(i)->z));
			glEnd();
			
			//在飛行路徑每個坐標點處繪製點圓加以標識每個坐標點
			for(i=0;i<m_FlayPath.GetSize();i++)
			{
				glColor3f(0,0.5,0.5); //點的顏色
				glPointSize(4.0); //點的大小
				glBegin(GL_POINTS);
					glVertex2f(GetOrthoX(m_FlayPath.GetAt(i)->x),GetOrthoY(-m_FlayPath.GetAt(i)->z));
				glEnd();
			}
			glPointSize(0); //恢復點的默認大小
			
		}
		else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) //繪製透視投影模式下的飛行路徑
		{
			glBegin(GL_LINE_STRIP);
			for(int i=0;i<m_FlayPath.GetSize();i++)
				glVertex3f(m_FlayPath.GetAt(i)->x, m_FlayPath.GetAt(i)->y, m_FlayPath.GetAt(i)->z);
			glEnd();
			
		}
		glEnable(GL_TEXTURE_2D); //開啟紋理
		glLineWidth(1.0); //恢復線寬
		glColor3f(1,1,1); //恢復顏色
		glPopMatrix(); //彈出矩陣堆棧
	}
}

//路徑坐標插值
void CT3DSystemView::OnFlppathInterpolation() 
{
	float m_InsertDdis=10; //插值間距 
	
	double x1,y1,z1,x2,y2,z2;
	PCordinate ppt ;  
	
	m_FlayPathTempPts.RemoveAll(); //臨時存儲飛行路徑
	for(int i=0;i<m_FlayPath.GetSize()-1;i++)
	{
		x1=m_FlayPath.GetAt(i)->x; //獲取飛行路徑當前點的x坐標
		y1=m_FlayPath.GetAt(i)->y; //獲取飛行路徑當前點的y坐標
		z1=m_FlayPath.GetAt(i)->z; //獲取飛行路徑當前點的z坐標
		
		x2=m_FlayPath.GetAt(i+1)->x; //獲取飛行路徑下一點的x坐標
		y2=m_FlayPath.GetAt(i+1)->y;//獲取飛行路徑下一點的y坐標
		z2=m_FlayPath.GetAt(i+1)->z;//獲取飛行路徑下一點的z坐標
		
		if(i==0) //如果是飛行路徑的起始點,則記錄
		{
			ppt = new Cordinate;
			ppt->x=x1;
			ppt->y=y1;
			ppt->z=z1;
			m_FlayPathTempPts.Add(ppt);
		}
		
		//計算飛行路徑當前點與下一點的距離
		double L=myDesingScheme.GetDistenceXYZ(x1,y1,z1,x2,y2,z2);
		int M=L/m_InsertDdis; //計算應內插的坐標點數
		for(int j=1;j<=M;j++)
		{
			//線性內插計算出新的內插點的三維坐標
			ppt = new Cordinate;
			ppt->x=x1+j*m_InsertDdis/L*(x2-x1);
			ppt->z=z1+j*m_InsertDdis/L*(z2-z1);
			ppt->y=m_demInsert.GetHeightValue(ppt->x+theApp.m_DemLeftDown_x,-ppt->z+theApp.m_DemLeftDown_y,2);
			m_FlayPathTempPts.Add(ppt); //記錄內插點坐標
			
		}
		
		ppt = new Cordinate;
		ppt->x=x2;
		ppt->y=y2;
		ppt->z=z2;
		m_FlayPathTempPts.Add(ppt); //將飛行路徑下一點的坐標也記錄在內
		
	}
	
	m_FlayPath.RemoveAll(); //飛行路徑數組清空
	for(i=0;i<m_FlayPathTempPts.GetSize();i++)
	{
		ppt = new Cordinate;
		ppt->x=m_FlayPathTempPts.GetAt(i)->x;
		ppt->y=m_FlayPathTempPts.GetAt(i)->y;
		ppt->z=m_FlayPathTempPts.GetAt(i)->z;
		m_FlayPath.Add(ppt); //重新填充飛行路徑數組
		
	}
	OnDraw(GetDC()); //刷新三維場景
	MessageBox("路徑坐標插值完成!","路徑坐標插值",MB_ICONINFORMATION);	
}

//保存飛行路徑
void CT3DSystemView::OnFlypathSave() 
{
	CString 	NeededFile;
	char 		FileFilter[] = "飛行路徑(*.pth)|*.pth||";

	//設置文件對話框屬性
	DWORD 		FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog FileDialogBoxFile(FALSE, NULL, 0, FileDialogFlag, FileFilter, this);
	FileDialogBoxFile.m_ofn.lpstrTitle = "保存飛行路徑文件";
	char		FileName[200];
	
	CString tt[3];
	if( FileDialogBoxFile.DoModal() == IDOK ) //如果對話框成果打開
	{	
		NeededFile = FileDialogBoxFile.GetPathName(); //得到文件名
		sprintf(FileName, "%s", NeededFile);
		if(strcmp(FileDialogBoxFile.GetFileExt(),"pth")!=0) 
			strcat(FileName,".pth"); //添加飛行路徑文件擴展名
		
		if(FlyPathSave(FileName)) //如果飛行路徑保存成功
			MessageBox("路徑點保存完畢","保存飛行路徑",MB_ICONWARNING);
		
	}			
}

//飛行路徑保存
int CT3DSystemView::FlyPathSave(char *pathfile)
{
	FILE	*fpw;
	char	message[200];
	
	if((fpw = fopen(pathfile, "w")) == NULL)//如果寫入文件失敗
  	{ 
		sprintf(message, "文件 %s 創建無效", pathfile);
		MessageBox(message,"保存飛行路徑坐標到文件",MB_ICONWARNING);
		return 0; //返回失敗
  	}
	
	
	fprintf(fpw, "%d\n", m_FlayPath.GetSize());//寫入飛行路徑坐標點總數
	for(int i=0;i<m_FlayPath.GetSize();i++)
	{
		//向文件fpw國寫入飛行路徑坐標點的三維坐標
		fprintf(fpw, "%lf,%lf,%lf\n",m_FlayPath.GetAt(i)->x, m_FlayPath.GetAt(i)->y, m_FlayPath.GetAt(i)->z);
		
	}
	
	fclose(fpw); //關閉文件
	
	return 1;  //返回成功
}

//打開飛行路徑
void CT3DSystemView::OnFlyOpenpath() 
{
	CString 	NeededFile;
	char 		FileFilter[] = "飛行路徑(*.pth)|*.pth||";
	//設置文件對話框屬性
	DWORD 		FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog FileDialogBoxFile(TRUE, NULL, 0, FileDialogFlag, FileFilter, this);
	FileDialogBoxFile.m_ofn.lpstrTitle = "打開飛行路徑文件";
	char		FileName[200];
	
	CString tt[3];
	if( FileDialogBoxFile.DoModal() == IDOK )//如果對話框成果打開
	{	
		NeededFile = FileDialogBoxFile.GetPathName();//得到文件名
		sprintf(FileName, "%s", NeededFile);
		if(strcmp(FileDialogBoxFile.GetFileExt(),"pth")!=0) 
			strcat(FileName,".pth");//添加飛行路徑文件擴展名
		
		if(FlyPathRead(FileName)) //讀取飛行路徑文件數據動態數組中
			MessageBox("打開路徑點完畢","提示",MB_ICONWARNING);
		if(m_FlayPath.GetSize()>1) //如果飛行路徑數據坐標點數>1
		{
			m_ShowFlyPath=TRUE; //顯示飛行路徑
			m_PathFlag=TRUE; //標識飛行路徑打開成功
		}
		else
			m_PathFlag=FALSE;//標識飛行路徑打開失敗
	}			
}

//讀取飛行路徑文件數據動態數組中
int CT3DSystemView::FlyPathRead(char *pathfile)
{
	CString tt,m_strszLine;
	PCordinate ppt = new Cordinate;  
	
	m_FlayPath.RemoveAll(); //飛行路徑數組清空
	
	CStdioFile m_inFile;	
			
	if(m_inFile.Open (pathfile,CFile::modeRead)==FALSE) //打開文件
	{
		return 0; //返回失敗標誌
	}
	m_inFile.ReadString(m_strszLine); //讀取飛行路徑坐標點總數
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
		m_FlayPath.Add(ppt); //記錄飛行路徑坐標點
		
	}
	m_inFile.Close(); //關閉文件
	
	return 1; //返回成功標誌
}

//顯示或關閉飛行路徑
void CT3DSystemView::OnFlyOnoffpath() 
{
	if(m_ShowFlyPath==TRUE) //如果當前是顯示飛行路徑
		m_ShowFlyPath=FALSE; //標識設置為FALSE
	else
		m_ShowFlyPath=TRUE; //反之,設置為TRUE	
	OnDraw(GetDC());  //刷新三維場景 
	
}

//根據m_ShowFlyPath值修改菜單文本
void CT3DSystemView::OnUpdateFlyOnoffpath(CCmdUI* pCmdUI) 
{
	if(m_ShowFlyPath==TRUE) //如果當前是顯示飛行路徑
		pCmdUI->SetText("關閉飛行路徑"); //將菜單名稱設置為"關閉飛行路徑"
	else   //如果當前是關閉飛行路徑
		pCmdUI->SetText("顯示飛行路徑");//將菜單名稱設置為"顯示飛行路徑"
}

//按固定高度漫遊
void CT3DSystemView::OnFlyStaticheight() 
{
	if(m_FlayPath.GetSize()<=0) //如果飛行路徑坐標點數量<=0，即飛行路徑為空
	{
		MessageBox("沒有輸入路徑文件","飛行瀏覽",MB_ICONWARNING);
		return;
	}
	
	m_R=4000;
	m_r=3000;
	
	m_FlyHeightType = GIS_FLY_STATICHEIGHT; //設置漫遊類型為固定高度漫遊
	m_StaticHeight = (m_maxHeight+m_minHeight)/4.0;  //取固定高度值=地形最大和最小高度的1/4
	m_flypathPtIndex=0; //飛行路徑坐標索引=0
	
	SetFLyTimer();	//設置三維漫遊計時器
}

void CT3DSystemView::OnUpdateFlyStaticheight(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	m_PathFlag == TRUE); //根據是否具有有效飛行路徑值設置菜單狀態
	if (m_FlyHeightType==GIS_FLY_STATICHEIGHT) //如果當前是"沿固定高度漫遊"方式
        pCmdUI->SetCheck(TRUE); //菜單前設置選中標誌"√"
    else
		pCmdUI->SetCheck(FALSE); //否則不設置		
}

//設置飛行計時器
void CT3DSystemView::SetFLyTimer()
{
	SetTimer(1,m_flyspeed,0); //m_flyspeed:飛行計時器時間間隔,
	
}

//計時器
void CT3DSystemView::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 1:  //三維漫遊
		if(m_flypathPtIndex<=m_FlayPath.GetSize()-2) //如果當前飛行路徑坐標點索引<=路徑坐標點總數-1
		{
			//根據漫遊路徑相臨坐標點計算相機各參數
			GetCameraCorrdinate(
				m_FlayPath.GetAt(m_flypathPtIndex)->x,\
				m_FlayPath.GetAt(m_flypathPtIndex)->y,\
				m_FlayPath.GetAt(m_flypathPtIndex)->z,\
				m_FlayPath.GetAt(m_flypathPtIndex+1)->x,\
				m_FlayPath.GetAt(m_flypathPtIndex+1)->y,\
				m_FlayPath.GetAt(m_flypathPtIndex+1)->z
				);
			if(m_ifZoomonRoad==TRUE)//如果沿線路方案漫遊
			{
				//計算當前里程
				CString tt,tt2;
				tt=myDesingScheme.GetLC(m_FlayPath.GetAt(m_flypathPtIndex)->Lc);
				tt2="當前里程="+tt;
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
			OnDraw(GetDC()); //刷新三維場景
			m_flypathPtIndex++; //飛行路徑當前坐標索引號+1
		}

		else
		{
			m_flypathPtIndex=0; //到了飛行尾,將飛行路徑當前坐標索引號重置為0,即從飛行路徑起始點開始漫遊
		}
		break;
	case 2: //錄製圖像序列
		RecordPictures();
		break;
	case 3:
	//	m_snows.DrawSnow ();
		break;
	}
	
	CView::OnTimer(nIDEvent);
}

//按相對高度漫遊方式
void CT3DSystemView::OnFlyRoutineheight() 
{
	if(m_FlayPath.GetSize()<=0)//如果飛行路徑坐標點數量<=0，即飛行路徑為空
	{
		MessageBox("沒有輸入路徑文件","飛行瀏覽",MB_ICONWARNING);
		return;
	}
	
	m_FlyHeightType = GIS_FLY_PATHHEIGHT;//設置漫遊類型為相對高度漫遊
	m_R=3000;
	m_r=2000;
	
	if(m_ifZoomonRoad==TRUE) 
		m_StaticHeight =5;
	else
		m_StaticHeight =80; //設置相對高差值
	
	m_flypathPtIndex=0;//飛行路徑坐標初始索引=0
	SetFLyTimer();	//設置三維漫遊計時器
}

//設置菜單是否設置選中標識"√"
void CT3DSystemView::OnUpdateFlyRoutineheight(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	m_PathFlag == TRUE); //根據是否具有有效飛行路徑值設置菜單狀態
	if (m_FlyHeightType==GIS_FLY_PATHHEIGHT) //如果當前是"沿相對高度漫遊"方式
        pCmdUI->SetCheck(TRUE); //菜單前設置選中標誌"√"
    else
		pCmdUI->SetCheck(FALSE); //否則不設置	
}

//開始/暫停漫遊
void CT3DSystemView::OnFlyPlaypause() 
{
	if(m_FlyPause==FALSE) //如果不是暫停漫遊,即處於漫遊狀態
	{
		m_FlyPause=TRUE; //設置暫停標識m_FlyPause=TRUE
		KillTimer(1); //銷毀定時器1
	}
	else //如果處於漫遊狀態
	{
		m_FlyPause=FALSE; //設置暫停標識m_FlyPause=FALSE
		SetFLyTimer();//設置飛行時間器,繼續漫遊
	}
}

//根據m_FlyPause值設置菜單ID_FLY_PLAYPAUSE文本
void CT3DSystemView::OnUpdateFlyPlaypause(CCmdUI* pCmdUI) 
{
	if(m_FlyPause==TRUE) //如果處於漫遊狀態
		pCmdUI->SetText("開始漫遊"); //設置菜單ID_FLY_PLAYPAUSE文本
	else  //如果不是暫停漫遊,即處於漫遊狀態
		pCmdUI->SetText("暫停漫遊");//設置菜單ID_FLY_PLAYPAUSE文本
	
}

//停止漫遊
void CT3DSystemView::OnFlyStop() 
{
	KillTimer(1); //銷毀定時器1
	m_flypathPtIndex=0;//飛行路徑坐標索引=0
	m_FlyPause=FALSE; //暫停標識為FALSE
	m_ifZoomonRoad=FALSE; //標識沿線路方案線漫遊為FALSE
	m_far=10000;	//恢復gluPerspective()函數定義平截頭體的遠剪裁平面的距離
}

//單步前進
void CT3DSystemView::OnFlyOnestep() 
{
	//如果飛行路徑坐標索引>=0並且<飛行路徑坐標總數-1,該條件表示的是
	//只要飛行路徑坐標索引沒有到飛行路徑尾,就可以執行單步前進
	if(m_flypathPtIndex>=0 && m_flypathPtIndex<m_FlayPath.GetSize()-1)
	{
		
		KillTimer(1);	//銷毀定時器1		
		m_FlyPause=TRUE;//暫停標識為TRUE
		//根據漫遊路徑相臨坐標點計算相機各參數
		GetCameraCorrdinate(
			m_FlayPath.GetAt(m_flypathPtIndex)->x,\
			m_FlayPath.GetAt(m_flypathPtIndex)->y,\
			m_FlayPath.GetAt(m_flypathPtIndex)->z,\
			m_FlayPath.GetAt(m_flypathPtIndex+1)->x,\
			m_FlayPath.GetAt(m_flypathPtIndex+1)->y,\
			m_FlayPath.GetAt(m_flypathPtIndex+1)->z
			);
		
		OnDraw(GetDC()); //刷新三維場景 
		m_flypathPtIndex++; //當前行路徑坐標索引+1
	}	
}

//飛行視野擴大
void CT3DSystemView::OnFlyViewEnlarge() 
{
	m_ViewWideNarrow += 5.0; //m_ViewWideNarrow值增加
	OnDraw (GetDC()); //刷新三維場景
}

//飛行視野減小
void CT3DSystemView::OnFlyViewSmall() 
{
	m_ViewWideNarrow -= 5.0;//m_ViewWideNarrow值減小
	OnDraw (GetDC());//刷新三維場景
}

//飛行高度增加
void CT3DSystemView::OnFlyHeightUp() 
{
	m_StaticHeight += 8;// 高度值增加(步長=8,可任意設定)
	OnDraw (GetDC());//刷新三維場景	
}

//飛行高度降低
void CT3DSystemView::OnFlyHeightDown() 
{
	m_StaticHeight -= 8;// 高度值增加(步長=8,可任意設定)
	OnDraw (GetDC());//刷新三維場景	
	
}

//飛行視角上傾(仰視)
void CT3DSystemView::OnFlyViewUp() 
{
	m_ViewUpDown += 1.0;
	OnDraw (GetDC());//刷新三維場景	
}

//飛行視角下傾(俯視)
void CT3DSystemView::OnFlyViewDown() 
{
	m_ViewUpDown -= 1.0;
	OnDraw (GetDC());//刷新三維場景	
}

//加速
void CT3DSystemView::OnFlySpeedUp() 
{
	m_flyspeed-=2; //飛行時的計時器時間間隔減少 
	if(m_flyspeed<=1) //如果計時器時間間隔<=1,則有
		m_flyspeed=1;
	SetFLyTimer();	//設置飛行計時器
}

//減速
void CT3DSystemView::OnFlySpeedDown() 
{
	m_flyspeed+=2;//飛行時的計時器時間間隔增加 
	SetFLyTimer();//設置飛行計時器
}

//三維漫遊調整熱鍵幫助
void CT3DSystemView::DisplayHelp()
{
	char str[20][50],strdis[2000];
	
	strdis[0]='\0';
	
	strcpy(str[0]," 向↑鍵   往前方向移動\n");
	strcpy(str[1]," 向↓鍵   往後方向移動\n");
	strcpy(str[2]," 向→鍵   往左方向移動\n");
	strcpy(str[3]," 向←鍵   往右方向移動\n");
	strcpy(str[4],"  J 鍵    飛行加速\n");
	strcpy(str[5],"  M 鍵    飛行減速\n");
	strcpy(str[6],"  F 鍵    飛行視野增大\n");
	strcpy(str[7],"  V 鍵    飛行視野減小\n");
	strcpy(str[8],"  G 鍵     升高飛行高度\n");
	strcpy(str[9],"  B 鍵     降低飛行高度\n");
	strcpy(str[10],"  H 鍵    飛行觀察上傾\n");
	strcpy(str[11],"  N 鍵    飛行觀察下傾\n");
	strcpy(str[12],"  Z 鍵    沿方案線漫遊\n");
	strcpy(str[13],"  P 鍵    開始/暫停漫遊\n");
	strcpy(str[14],"  S 鍵    停止漫遊");
	
	for(int i=0;i<15; i++)
		strcat(strdis,str[i]);
	
	MessageBox(strdis,"三維漫遊熱鍵說明",MB_OK);
}

//橋墩模型
void CT3DSystemView::OnMenuModleqd() 
{
	CModelMangerQD dlg;
	if(dlg.DoModal()==IDOK) //如果對話框以IDOK方式關閉
	{
		if(!dlg.m_3DSfilename_QD.IsEmpty()) //如果橋墩模型名稱不為空
		{
			m_3DSfilename_QD=dlg.m_3DSfilename_QD; //得到橋墩模型名稱
			BuildQDModelList(); //重新構建橋墩模型顯示列表
			
		}
	}	
}

//輸出線路三維模型到CAD
void CT3DSystemView::OnMenuOuptcad3dlinemodel() 
{
	CString tt,DxfFilename;
	
	CDXF mdxf;
	CStdioFile *Dxffile=new CStdioFile;
	CFileDialog fielDlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"AutoCAD Dxf(*.dxf)|*dxf||",NULL);
	
	fielDlg.m_ofn.lpstrTitle = "輸出線路三維模型到CAD";   
	
	if(fielDlg.DoModal()==IDCANCEL) //打開對話框
		return;
	
	DxfFilename=fielDlg.GetPathName(); //得到DXF文件名
	if(DxfFilename.IsEmpty()) //如果DXF文件名為空，返回
		return;

	//確保DXF文件以".dxf"擴展名結尾
	tt=DxfFilename.Right(4);
	tt.MakeUpper();
	if(strcmp(tt,".DXF")!=0)
		DxfFilename+=".dxf";
	
	//如果新創建的DXF文件已經打開，給出錯信息	 
	if(Dxffile->Open (DxfFilename,CFile::modeCreate | CFile::modeWrite)==FALSE)
	{
		this->MessageBox("文件"+DxfFilename+"已被其它程序打開或佔用,請關閉再試!","輸出線路三維模型到CAD",MB_ICONINFORMATION);
		return;
	}

	mdxf.DxfHeader(Dxffile); //寫入DXF文件頭
	mdxf.DxfLineType(Dxffile);//寫入DXF線型定義
	mdxf.DxfBeginDrawEnties(Dxffile); //開始寫入圖形實體

	//寫入線路中心線部分
	for (long i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		
		mdxf.DxfDraw_Line(Dxffile,"線路中心線",1,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x,\
			-myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->y,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->x,\
			-myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->z,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->y);
	}	

	//寫入兩側軌道間的連線部分
	for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		mdxf.DxfDraw_Line(Dxffile,"兩側軌道間的連線",6,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2);
		mdxf.DxfDraw_Line(Dxffile,"兩側軌道間的連線",6,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"兩側軌道間的連線",6,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"兩側軌道間的連線",6,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1);
	}		

	//寫入兩側碴肩至碴腳間的連線部分
	for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		
	
		mdxf.DxfDraw_Line(Dxffile,"兩側碴肩至碴腳間的連線",3,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"兩側碴肩至碴腳間的連線",3,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"兩側碴肩至碴腳間的連線",3,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1);
		mdxf.DxfDraw_Line(Dxffile,"兩側碴肩至碴腳間的連線",3,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1);
		
		
		mdxf.DxfDraw_Line(Dxffile,"兩側碴肩至碴腳間的連線",3,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"兩側碴肩至碴腳間的連線",3,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"兩側碴肩至碴腳間的連線",3,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2);
		mdxf.DxfDraw_Line(Dxffile,"兩側碴肩至碴腳間的連線",3,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2);
		

	}
	
	//寫入兩側碴腳至路肩間的連線部分
	for (i=0;i<myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()-1;i++)
	{
	
		
		mdxf.DxfDraw_Line(Dxffile,"兩側碴腳至路肩間的連線",4,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"兩側碴腳至路肩間的連線",4,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"兩側碴腳至路肩間的連線",4,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1);
		mdxf.DxfDraw_Line(Dxffile,"兩側碴腳至路肩間的連線",4,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1);
		
		
		
		mdxf.DxfDraw_Line(Dxffile,"兩側碴腳至路肩間的連線",4,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"兩側碴腳至路肩間的連線",4,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"兩側碴腳至路肩間的連線",4,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2);
		mdxf.DxfDraw_Line(Dxffile,"兩側碴腳至路肩間的連線",4,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2);
		
	}		
	
	//寫入左側邊坡部分(隧道和橋樑不寫入)
	for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		tt=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
		if(tt!="隧道起點" && tt!="隧道中間點" &&tt!="隧道終點" &&tt!="橋樑起點"  &&tt!="橋樑中間點" &&tt!="橋樑終點")
		{	
			DrawBP_CAD(i,1,Dxffile);//左側邊坡
		
		}
	}
	
	//寫入右側邊坡和兩側水溝部分(隧道和橋樑不寫入)
	for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		tt=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
		if(tt!="隧道起點" && tt!="隧道中間點" &&tt!="隧道終點" &&tt!="橋樑起點"  &&tt!="橋樑中間點" &&tt!="橋樑終點")
		{
			DrawBP_CAD(i,2,Dxffile); //右側邊坡
			DrawSuiGou_CAD(i,2,Dxffile);//兩側水溝
		
		}
	}
	
	mdxf.DxfSectionEnd(Dxffile); //寫入文件結束標誌
	tt.Format("dxf文件%s已輸出完成!",DxfFilename);
	MessageBox(tt,"輸出圖形到AuotCAD",MB_ICONINFORMATION); //給出DXF文件輸出完成信息
		
}

//寫入兩側邊坡部分到DXF文件中(隧道和橋樑不寫入)
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

					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y);
				}
				else 
				{
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
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
						mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y);
						mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y);
						mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
						mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
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
 
 					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y);
					
				}
				else
				{
 
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y);

 
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y);
					
					
				}
			

				if(j>0) 
				{
 
 					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
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
 
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x)
					{
					}
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y);
					
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y);					
				}
				else
				{
 
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y);
					
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y);
					
				}
				
				if(j>0) 
				{
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
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
 
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y);
					
				}
				else
				{
 
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y);
					

					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y);
					
				}
				
				if(j>0) 
				{
 
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"路基邊坡線",2,\
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
			
			mdxf.DxfDraw_Line(Dxffile,"水溝",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y);
		}
		for( i=0;i<5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"水溝",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i+1].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i+1].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i+1].y);
		}
		
		for( i=0;i<5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"水溝",5,\
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
			
			mdxf.DxfDraw_Line(Dxffile,"水溝",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y);
		}
		for( i=0;i<5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"水溝",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i+1].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i+1].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i+1].y);
		}
		
		for( i=0;i<5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"水溝",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i+1].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i+1].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i+1].y);
		}
		
	}
}

//動畫錄製參數設置
void CT3DSystemView::OnAviParameter() 
{
	CRect rect;
	this->GetClientRect(&rect); //得到客戶區大小不
	
	CAviParameter	 dlg;
	

	//確保AVI寬度和高度有效
    if(m_MovieWidth<=0 || m_MovieHeight<=0)
	{
		m_MovieWidth=rect.right; //AVI的寬度
		m_MovieHeight=rect.bottom;//AVI的高度
	}
	
	
	dlg.m_MoviemaxWidth=rect.right;   //AVI的最大寬度
	dlg.m_MoviemaxHeight=rect.bottom; //AVI的最大高度
	
	dlg.m_AviFilename=m_AviFilename;  //AVI文件名
	dlg.m_AVIFrame=m_AVIFrame;//AVI文件錄製頻率
	
	dlg.m_MovieWidth=m_MovieWidth; //AVI的寬度
    dlg.m_MovieHeight=m_MovieHeight; //AVI的高度 
	
	if(dlg.DoModal ()==IDOK)  
	{
		m_AviFilename=dlg.m_AviFilename; //AVI文件名
		m_AVIFrame=dlg.m_AVIFrame; //AVI文件錄製頻率
		m_MovieWidth=dlg.m_MovieWidth;  //AVI的寬度
		m_MovieHeight=dlg.m_MovieHeight; //AVI的高度 
	}	
}



//開始錄製動畫
void CT3DSystemView::OnAviStart() 
{
	if(m_Beginrecording==TRUE)  //如果開始錄製動畫標識m_Beginrecording=TRUE,表示已經正在錄製動畫,返回
	{
		recordBegin(); //記錄開始錄製動畫
		return; //返回
	}
	
	//打開AVI保存文件
	CFileDialog fd(FALSE,"avi",0,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY|OFN_PATHMUSTEXIST,"Microsoft AVI (*.avi)|*.avi||");
	
	CDC *dc=GetDC();
	wglMakeCurrent( dc->m_hDC, m_hRC );//將RC與當前DC關聯
	
	CRect rect;
	GetClientRect(&rect); //得到客戶工大
	
	//確保AVI寬度和高度有效
	if(m_MovieWidth<=0 ||m_MovieHeight<=0) 
	{
		m_MovieWidth=rect.right;
		m_MovieHeight=rect.bottom;
	}
	
	BeginWaitCursor(); //顯示沙漏光標
    bool success = false;

	//將捕捉到的數據寫入AVI文件中
	success = BeginMovieCapture(m_AviFilename,m_MovieWidth,m_MovieHeight,m_AVIFrame);
	if (!success)
    {
        MessageBox("不能錄製動畫!", "錄製動畫", MB_OK | MB_ICONERROR);
		return;
    }
	
	if (m_movieCapture != NULL)
    {
        if (isRecording())
            OnAviPause(); //暫停錄製動畫
        else
            recordBegin(); //開始錄製動畫
    }
	
    EndWaitCursor();//結束沙漏光標,恢復正常光標
	
	wglMakeCurrent( 0, 0 );//釋放DC和RC 
	ReleaseDC(dc);	//釋放dc		
}

//開始捕捉
bool CT3DSystemView::BeginMovieCapture(CString filename, int width, int height, float framerate)
{
	m_movieCapture = new CAVICapture();
	//設置AVI文件名稱、錄製幀的大小、錄製幀率、AVI文件壓縮方式等信息
    bool success = m_movieCapture->start(filename, width, height, framerate);
    if (success) //如果設置成功
        initMovieCapture(m_movieCapture); //初始化m_movieCapture變量
    else
        delete m_movieCapture; //如果失敗,刪除m_movieCapture
    
    return success;
}

//初始化m_movieCapture變量
void CT3DSystemView::initMovieCapture(CAVICapture *mc)
{
	if (m_movieCapture == NULL)
        m_movieCapture = mc;
	
}

//獲取是否在錄製動畫
bool CT3DSystemView::isRecording()
{
	return m_Recording;
	
}

//如果m_movieCapture不為NULL,初始化成功,則設置錄製標識=true
void CT3DSystemView::recordBegin()
{
	if (m_movieCapture != NULL) //如果m_movieCapture不為NULL
        m_Recording = true;
	
}

//暫停錄製動畫
void CT3DSystemView::OnAviPause() 
{
	m_Recording = false;
}

//結束錄製動畫
void CT3DSystemView::OnAviEnd() 
{
	if (m_movieCapture != NULL) //如果m_movieCapture 不為空,表示已捕捉數據
	{
        recordEnd(); //結束錄製動畫		
	}		
}

//結束錄製動畫
void CT3DSystemView::recordEnd()
{
	if (m_movieCapture != NULL) //如果m_movieCapture 不為空,表示已捕捉數據
    {
        OnAviPause();//暫停,將捕捉的數據不再寫入文件
        m_movieCapture->end();//結束錄製
        delete m_movieCapture; //刪除m_movieCapture(裡面包含錄製的數據)
        m_movieCapture = NULL; //重新設置m_movieCapture為空
    }
}

//設置圖像採集頻率
void CT3DSystemView::OnSavepictureSpeed() 
{
	CRecordPictureSpeed	 dlg;
	dlg.m_recordPictSpeed=m_recordPictSpeed;//當前所設置的採集圖像頻率
	if(dlg.DoModal ()==IDOK) //如果對話框以IDOK方式關閉
	{
		m_recordPictSpeed=dlg.m_recordPictSpeed; //得到新設置的採集圖像頻率
	}			
}


//錄像(圖像序列)
void CT3DSystemView::OnSavepictureContinue() 
{
	m_RecordPicture=TRUE;  //錄像圖像序列的標誌為TRUE
	SetPictureName(); //設置錄製圖像時的初始文件名稱
	SetTimer(2,m_recordPictSpeed,NULL);	 //設置錄製圖像計時器
	
}

//設置錄製圖像時的初始文件名稱，後面採集的圖像文件名均以此初始文件名+錄製序號組成
void CT3DSystemView::SetPictureName()
{
	CFileDialog FileDialog( FALSE, _T("bmp"), _T("*.bmp"), OFN_HIDEREADONLY,
		_T("Windows Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL );
	
	if(FileDialog.DoModal() == IDOK) //打開文件對話框
	{
		m_RecordPicturename = FileDialog.GetPathName(); //得到圖像文件名
		
	}	
}

//錄製圖像序列
void CT3DSystemView::RecordPictures()
{
	
	CString str,str1,fname;
	
	str.Format("%s",m_RecordPicturename);
	int n=str.GetLength ();
	str=str.Left (n-4);
	m_PictureNumbers++; //採集的圖像數量+1
	
	str1.Format ("%d",m_PictureNumbers);
	switch(str1.GetLength ())
	{
		case 1:str1="0000"+str1;break;
		case 2:str1="000"+str1;break;
		case 3:str1="00"+str1;break;
		case 4:str1="0"+str1;break;
	}
	
	fname=str+str1+".bmp"; //得到要保存的位圖文件名
	CRect rcDIB;
	GetClientRect(&rcDIB);
    
	OnDraw (GetDC());//刷新三維場景 
	CapturedImage.Capture(GetDC(), rcDIB);
	
	CapturedImage.WriteDIB(fname); //將採集的數據寫入位圖中文件中
	CapturedImage.Release();	//釋放CapturedImage
}

//打印預覽
void CT3DSystemView::OnFilePrintPreview() 
{
	CRect rcDIB;
	GetClientRect(&rcDIB); //得到客戶區大小
	OnDraw (GetDC()); //刷新三維場景 
	CapturedImage.Capture(GetDC(), rcDIB);//將DDB圖形轉換為與設備無關的位圖DIB
	CView::OnFilePrintPreview(); //調用	CView::OnFilePrintPreview()函數打印預覽
}

//停止錄像圖像
void CT3DSystemView::OnSavepictureStop() 
{
	m_RecordPicture=FALSE; //標識錄製圖像為FALSE
	KillTimer(2);	//銷毀計算器2	
	
}

//保存屏幕到位圖
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
		strFilename=FileDialog.GetPathName(); //得到位圖文件名
		if(!strFilename.IsEmpty()) //如果位圖文件名為空
		{
			DeleteFile(strFilename); //刪除原有文件
			BOOL bOK=SaveBmp(mybitmap,strFilename);  //保存到位圖文件
			if(bOK==TRUE) //如果保存成功
				MessageBox("圖像保存成功","保存屏幕到位圖",MB_ICONINFORMATION);
			else
				MessageBox("圖像保存失敗","保存屏幕到位圖",MB_ICONINFORMATION);
		}
		
	}	
}

//保存位圖到文件
BOOL CT3DSystemView::SaveBmp(HBITMAP hBitmap, CString FileName)
{
	//設備描述表   
	HDC   hDC;   
	//當前分辨率下每象素所佔字節數   
	int   iBits;   
	//位圖中每象素所佔字節數   
	WORD   wBitCount;   
	//定義調色板大小，   位圖中像素字節大小   ，位圖文件大小   ，   寫入文件字節數     
	DWORD   dwPaletteSize=0,   dwBmBitsSize=0,   dwDIBSize=0,   dwWritten=0;     
	//位圖屬性結構     
	BITMAP   Bitmap;       
	//位圖文件頭結構   
	BITMAPFILEHEADER   bmfHdr;       
	//位圖信息頭結構     
	BITMAPINFOHEADER   bi;       
	//指向位圖信息頭結構       
	LPBITMAPINFOHEADER   lpbi;       
	//定義文件，分配內存句柄，調色板句柄     
	HANDLE   fh,   hDib,   hPal,hOldPal=NULL;     
    
	//計算位圖文件每個像素所佔字節數     
	hDC   =   CreateDC("DISPLAY",   NULL,   NULL,   NULL);   
	iBits   =   GetDeviceCaps(hDC,   BITSPIXEL)   *   GetDeviceCaps(hDC,   PLANES);     
	DeleteDC(hDC);     
	if   (iBits   <=   1)   wBitCount   =   1;     
	else   if   (iBits   <=   4)     wBitCount   =   4;     
	else   if   (iBits   <=   8)     wBitCount   =   8;     
	else       wBitCount   =   24;     
    
	GetObject(hBitmap,   sizeof(Bitmap),   (LPSTR)&Bitmap);    //保存位圖文件前通過GetObject函數取得位圖長度
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
    
	//為位圖內容分配內存     
	hDib   =   GlobalAlloc(GHND,dwBmBitsSize   +   dwPaletteSize   +   sizeof(BITMAPINFOHEADER));     
	lpbi   =   (LPBITMAPINFOHEADER)GlobalLock(hDib);     
	*lpbi   =   bi;     
    
	//   處理調色板       
	hPal   =   GetStockObject(DEFAULT_PALETTE);     
	if   (hPal)     
	{     
		hDC   =   ::GetDC(NULL);     
		hOldPal   =   ::SelectPalette(hDC,   (HPALETTE)hPal,   FALSE);     
		RealizePalette(hDC);     
	}   
	
	//得到DC位圖句柄 
	GetDIBits(hDC,   hBitmap,   0,   (UINT)   Bitmap.bmHeight,   (LPSTR)lpbi   +   sizeof(BITMAPINFOHEADER)     
		+dwPaletteSize,   (BITMAPINFO   *)lpbi,   DIB_RGB_COLORS);     
    
	//恢復調色板       
	if   (hOldPal)     
	{     
		::SelectPalette(hDC,   (HPALETTE)hOldPal,   TRUE);     
		RealizePalette(hDC);     
		::ReleaseDC(NULL,   hDC);     
	}     
    
	//創建位圖文件       
	fh   =   CreateFile(FileName,   GENERIC_WRITE,0,   NULL,   CREATE_ALWAYS,     
		FILE_ATTRIBUTE_NORMAL   |   FILE_FLAG_SEQUENTIAL_SCAN,   NULL);     
    
	if   (fh   ==   INVALID_HANDLE_VALUE)     return   FALSE;     
    
	//   設置位圖文件頭     
	bmfHdr.bfType   =   0x4D42;   //   "BM"     
	dwDIBSize   =   sizeof(BITMAPFILEHEADER)   +   sizeof(BITMAPINFOHEADER)   +   dwPaletteSize   +   dwBmBitsSize;       
	bmfHdr.bfSize   =   dwDIBSize;     
	bmfHdr.bfReserved1   =   0;     
	bmfHdr.bfReserved2   =   0;     
	bmfHdr.bfOffBits   =   (DWORD)sizeof(BITMAPFILEHEADER)   +   (DWORD)sizeof(BITMAPINFOHEADER)   +   dwPaletteSize;     
	//   寫入位圖文件頭     
	WriteFile(fh,   (LPSTR)&bmfHdr,   sizeof(BITMAPFILEHEADER),   &dwWritten,   NULL);     
	//   寫入位圖文件其餘內容     
	WriteFile(fh,   (LPSTR)lpbi,   dwDIBSize,   &dwWritten,   NULL);     
	//清除       
	GlobalUnlock(hDib);     
	GlobalFree(hDib);     
	CloseHandle(fh);     
    
	return   TRUE;   
}

//得到DC位圖句柄
HBITMAP CT3DSystemView::GetSrcBit(HDC hDC, DWORD BitWidth, DWORD BitHeight)
{
	HDC   hBufDC;   
	HBITMAP   hBitmap,   hBitTemp;   
    
	//創建設備上下文(HDC)   
	hBufDC   =   CreateCompatibleDC(hDC);   
    
	//創建HBITMAP   
	hBitmap   =   CreateCompatibleBitmap(hDC,   BitWidth,   BitHeight);   
	hBitTemp   =   (HBITMAP)   SelectObject(hBufDC,   hBitmap);   
    
	//得到位圖緩衝區   
	StretchBlt(hBufDC,   0,   0,   BitWidth,   BitHeight,   
		hDC,   0,   0,   BitWidth,   BitHeight,   SRCCOPY);   
    
	//得到最終的位圖信息   
	hBitmap   =   (HBITMAP)   SelectObject(hBufDC,   hBitTemp);   
    
	//釋放內存   
    
	DeleteObject(hBitTemp);   
	::DeleteDC(hBufDC);   
    
	return   hBitmap;   
}




