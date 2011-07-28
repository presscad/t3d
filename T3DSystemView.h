// T3DSystemView.h : interface of the CT3DSystemView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_T3DSYSTEMVIEW_H__3A8D7F07_F2EE_46F8_A484_C22327088E9C__INCLUDED_)
#define AFX_T3DSYSTEMVIEW_H__3A8D7F07_F2EE_46F8_A484_C22327088E9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum { QUERY_COORDINATE,QUERY_DISTENCE,SELECTLINE,SELECTFLYPATH};
enum {GIS_VIEW_ORTHO,GIS_VIEW_PERSPECTIVE};
enum {ORTHO_ZOOMIN,ORTHO_ZOOMOUT,ORTHO_PAN,ORTHO_ZOOMORIGIN,ORTHO_ZOOMWINDOW};
enum {GIS_FLY_STATICHEIGHT,	GIS_FLY_PATHHEIGHT};

#define MAX_TEXTURENUM  500  //定義最多可同時加載的地形塊數量

#include "AllocUnAlloc2D3D.h"
#include "Vector.h"	
#include "Texture.h"
#include "3DSModel.h"
#include "Delaunay.h"
#include "DXF.h"
#include "AVICapture.h"
#include "ClientCapture.h"	
#include "Snow.h"


#define SKYFRONT 0						// Give Front ID = 0
#define SKYBACK  1						// Give Back  ID = 1
#define SKYLEFT  2						// Give Left  ID = 2
#define SKYRIGHT 3						// Give Right ID = 3
#define SKYUP    4						// Give Up    ID = 4
#define SKYDOWN  5						// Give Down  ID = 5

//定義封閉區域線結構
typedef struct  
{
	int index;//封閉區索引號
	CArray<PCordinate,PCordinate> ReginPts;//線路封閉區域邊界點集合
	CArray<int,int>GridID;//所屬於分塊ID號(分塊標準按採用DEM分塊大小)
	double minx;//最小x坐標
	double miny;//最小y坐標
	double maxx;//最大x坐標
	double maxy;//最大y坐標
	
}Regions,*PRegions;


typedef struct  
{
	BOOL bInRegion;//節點塊是否在封閉區域(只有當節點4個角點個部不在封閉區域內才為真)
	
} BlockReginInfor,*PBlockReginInfor;

typedef struct
{
	int RegionNum;//該地形塊內封閉區域總數
	CArray<int,int>GridID;//所屬於分塊ID號(分塊標準按採用DEM分塊大小)
	CArray<PCordinate,PCordinate> ReginPts;//線路封閉區域邊界點集合
	double minx; //最小x坐標
	double miny;//最小y坐標
	double maxx;//最大x坐標
	double maxy;//最大y坐標
	
}BlockReginInforMe,*PBlockReginInforMe;

//定義地形塊離散點集合
typedef struct
{
	CArray<PCordinate,PCordinate> ReginPts;//地形塊線離散點集合(包括地形點和封閉區域點)
	int mDemBlockRow;//對應的DEM子塊的行號
	int mDemBlockCol;//對應的DEM子塊的列號
	
}BlockLSPts,*PBlockLSPts;


//三角形3個頂點信息
typedef struct
{
	Point Pt1;
	Point Pt2;
	Point Pt3;
}TriPt,*PTriPt;

//存儲每個地形塊內的三角形信息
typedef struct
{
	CArray<PTriPt,PTriPt>TriPts;
	int mDemBlockRow;//對應的DEM子塊的行號
	int mDemBlockCol;//對應的DEM子塊的列號
}BlockTriInfos,*PBlockTriInfos;




class CT3DSystemView : public CView
{
protected: // create from serialization only
	CT3DSystemView();
	DECLARE_DYNCREATE(CT3DSystemView)

// Attributes
public:
	CT3DSystemDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CT3DSystemView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CArray<PBlockTriInfos,PBlockTriInfos> m_BlockTriInfos;//存儲每個地形塊的三角形信息
	
	virtual ~CT3DSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CArray<PCordinate,PCordinate> m_FlayPath;//存儲進行飛行路徑選擇時所選擇的一系列點坐標
	CArray<PCordinate,PCordinate> m_FlayPathTempPts;//存儲臨時進行飛行路徑選擇時所選擇的一系列點坐標
	int m_flypathPtIndex; //飛行路徑坐標索引號
	int m_flyPathCurrentPtIndex;//在飛行過程中記錄當前路徑點的索引號,用於暫停飛行器
	BOOL m_FlyPause;//是否暫停飛行

	CArray<PCordinate,PCordinate> m_TempPts;
	BOOL m_ifZoomonRoad; //標識是否沿線路方案漫遊
	
	CArray<PCordinate,PCordinate> m_ReginPtsLeft;//線路封閉區域邊界左側線路點
	CArray<PCordinate,PCordinate> m_ReginPtsRight;//線路封閉區域邊界右側線路點
	CArray<PRegions,PRegions> mRegions;//線路封閉區域邊界點
	
	CArray<PBlockReginInforMe,PBlockReginInforMe> *mBlockReginInforMe;//地形節點三角形是否位於封閉區域邊界信息
	
	CArray<PBlockLSPts,PBlockLSPts> m_BlockLSPts;//
	
	//{{AFX_MSG(CT3DSystemView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMenuOpenproject();
	afx_msg void OnDrawmodeLine();
	afx_msg void OnDrawmodeRender();
	afx_msg void OnDrawmodeTexture();
	afx_msg void OnSpacequerySet();
	afx_msg void OnQueryCoordinate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnQueryDistence();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuStereo();
	afx_msg void OnUpdateMenuStereo(CCmdUI* pCmdUI);
	afx_msg void OnMenuProjecttionortho();
	afx_msg void OnUpdateMenuProjecttionortho(CCmdUI* pCmdUI);
	afx_msg void OnOrthoZoomIn();
	afx_msg void OnUpdateOnOrthoZoomIn(CCmdUI*  pCmdUI);   
	afx_msg void OnOrthoZoomOut();
	afx_msg void OnUpdateOnOrthoZoomOut(CCmdUI*  pCmdUI);   
	afx_msg void OnOrthoPan();
	afx_msg void OnUpdateOnOrthoPan(CCmdUI*  pCmdUI);   
	afx_msg void OnOrthoZoomOrigin();
	afx_msg void OnUpdateOnOrthoZoomOrigin(CCmdUI*  pCmdUI);   
	afx_msg void OnOrthoZoomWindow();
	afx_msg void OnUpdateOnOrthoZoomWindow(CCmdUI*  pCmdUI);   
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMenuLinedesign();
	afx_msg void OnUpdateMenuLinedesign(CCmdUI* pCmdUI);
	afx_msg void OnUpdateQueryCoordinate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateQueryDistence(CCmdUI* pCmdUI);
	afx_msg void OnMenuLinesavescheme();
	afx_msg void OnUpdateMenuPerspective(CCmdUI* pCmdUI);
	afx_msg void OnMenuPerspective();
	afx_msg void OnMenuBuild3dlinemodle();
	afx_msg void OnFlyRoutinschemeline();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFlyStop();
	afx_msg void OnMenuTunnelset();
	afx_msg void OnMenuBridgeset();
	afx_msg void OnMenuTexturebp();
	afx_msg void OnMenuTexturelj();
	afx_msg void OnMenuTextureqlhpm();
	afx_msg void OnMenuTexturetunnel();
	afx_msg void OnMenuTexturetunnelDm();
	afx_msg void OnPathManuinput();
	afx_msg void OnFlypathSave();
	afx_msg void OnFlppathInterpolation();
	afx_msg void OnFlyOpenpath();
	afx_msg void OnFlyOnoffpath();
	afx_msg void OnUpdateFlyOnoffpath(CCmdUI* pCmdUI);
	afx_msg void OnFlyStaticheight();
	afx_msg void OnUpdateFlyStaticheight(CCmdUI* pCmdUI);
	afx_msg void OnFlyRoutineheight();
	afx_msg void OnUpdateFlyRoutineheight(CCmdUI* pCmdUI);
	afx_msg void OnFlyPlaypause();
	afx_msg void OnUpdateFlyPlaypause(CCmdUI* pCmdUI);
	afx_msg void OnFlyOnestep();
	afx_msg void OnFlyViewEnlarge();
	afx_msg void OnFlyViewSmall();
	afx_msg void OnFlyHeightUp();
	afx_msg void OnFlyHeightDown();
	afx_msg void OnFlyViewDown();
	afx_msg void OnFlyViewUp();
	afx_msg void OnFlySpeedUp();
	afx_msg void OnFlySpeedDown();
	afx_msg void OnMenuModleqd();
	afx_msg void OnMenuOuptcad3dlinemodel();
	afx_msg void OnAviParameter();
	afx_msg void OnAviStart();
	afx_msg void OnAviPause();
	afx_msg void OnAviEnd();
	afx_msg void OnSavepictureSpeed();
	afx_msg void OnSavepictureContinue();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnSavepictureStop();
	afx_msg void OnMenuSavescreentobmp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HBITMAP GetSrcBit(HDC hDC, DWORD BitWidth, DWORD BitHeight);
	BOOL SaveBmp(HBITMAP hBitmap, CString FileName);
	void RecordPictures();
	void SetPictureName();
	void recordEnd();
	void recordBegin();
	bool isRecording();
	void initMovieCapture(CAVICapture *mc);
	bool BeginMovieCapture(CString filename, int width, int height, float framerate);
	void DrawSuiGou_CAD(long index, int BPside,CStdioFile* Dxffile);
	void DrawBP_CAD(long index, int BPside,CStdioFile* Dxffile);
	void DisplayHelp();
	int FlyPathRead(char *pathfile);
	int FlyPathSave(char *pathfile);
	void DrawFlyPath();
	int GetBlockID(double x, double y);
	void GetRoadCloseRegion();
	void GetBlockEdgeJd(double block_minx, double block_miny, double block_maxx, double block_maxy, long RegionsIndex, long ReginPtsIndex, int *jdNus, Point edgePts[]);
	void WriteBlockLsPts(long Blcokrow, long Blcokcol);
	void GetBlockInregion(int blockRow, int blockCol);
	BOOL GetTriOutRegion(double x1, double y1, double x2, double y2, double x3, double y3, int blockIndex);
	void AddBlcokTri(int blockIndex, int DemblcokRow, int DemblcokCol);
	void DrawTerrainTIN(long blockIndex);
	void BuildTerrainRegionInfo();
	void GetRegionID(long index);
	void WriteRegionPts(int index, BOOL bAddorAppend,int mLeftorRight);
	void DrawTerrainDelaunay();
	void GetNorthPtangle();
	void PrintText(float x, float y, char *string);
	void DrawNorthPt();
	void makeClockList();
	void SetClockProjectionNavigate();
	void DrawClock();
	void ReLoadCenterPt();
	void DrawBridgeHL();
	void DrawCylinder(GLfloat radii, GLfloat Height, GLint segmentNum);
	void makeQLList();
	void BuildQDModelList();
	void BuildTunnelDMModelList();//創建隧道洞門顯示列表
	void CalZoomSpeed(float mCurZooomLC);
	void GetCameraCorrdinate(double x1, double y1, double z1, double x2, double y2, double z2);
	void SetFLyTimer();
	void DrawTunnelDM(double x1, double y1, double z1, double x2, double y2, double z2, float H, float L, int index, int tunnelIndex, BOOL bstartDM,float mangle);
	void DrawTunnelEach(long mStartindex, long mEndIndex,int mTunnelIndex,float H,float L);
	void GetMinMaxXY_bridgeHPm(double *minx, double *miny, double *maxx, double *maxy);
	void DrawTunnel();
	void DrawSceneQD(double x1, double y1, double z1, double x2, double y2, double z2, float QDheight);
	void DrawQDHP(long Index, CString mCurrentPtstyle, float mHPangle, CString mNextPtstyle,int mBridgeIndex);
	void DrawSuiGou_Ortho(long index);
	void DrawSuiGou(long index);
	void DrawBP_Ortho(long index, int BPside);
	void DrawBP(long index, int BPside);
	void DrawRailwaythesme();
	void DrawCenterLine(long index,BOOL ifSelectLine,int SchemeIndex);
	void DrawRailwaythesme_Ortho();
	float GetOrthoX(double x);	//計算正射投影模式下x坐標
	float GetOrthoY(double y);	//計算正射投影模式下y坐標
	void ExporttotalDemToFIle(CString strFilename);
	void ReadHdata(CString strfilename);
	void GetOrthoColor(double x1,double y1,float *mColorR,float *mColorG);
	void DrawBlockOrtho(int DemBlockIndex);
	void DrawTerrain_ORTHO();
	void SetProjection();
	void mCamraUpdate();
	void CheckForMovement();
	void MoveCamera(float speed);
	void RotateView(float angle, float x, float y, float z);
	void SetViewByMouse();
	void StrafeCamera(float speed);
	void DrawSearchPoint();
	void ScreenToGL(CPoint point);
	void SetDrawMode();
	BOOL ExportBlobTextureToFIle(CString strFilename, int RowIndex, int ColIndex,int mID);
	void DrawScene();
	void SetTextureCoord(float x, float z,int mRowIndex,int mColIndex);
	int RenderQuad(int nXCenter, int nZCenter, int nSize,int mRowIndex,int mColIndex);
	void CracksPatchTop(int nXCenter, int nZCenter, int nSize,int mRowIndex,int mColIndex);
	void CracksPatchRight(int nXCenter, int nZCenter, int nSize,int mRowIndex,int mColIndex);
	void CracksPatchLeft(int nXCenter, int nZCenter, int nSize,int mRowIndex,int mColIndex);
	void CracksPatchBottom(int nXCenter, int nZCenter, int nSize,int mRowIndex,int mColIndex);
	void SetTextureCoordZoomRoad(double x, double z,int mRowIndex,int mColIndex);
	BOOL GetIfINView(int mBlockRow,int mBlockCol);
	float GetNodeError(int nXCenter, int nZCenter, int nSize, int mRowIndex, int mColIndex);
	float GetHeightValue(int X, int Y,int mRowIndex,int mColIndex);
	void UpdateQuad(int nXCenter, int nZCenter, int nSize, int nLevel,int mRowIndex,int mColIndex);
	void CalculateViewPortTriCord(double View_x, double View_z, double look_x, double look_z);
	BOOL bnTriangle(double cneterx, double cnetery, double x2, double y2, double x3, double y3, double x, double y);
	void DrawTerrainZoomonRoad();
	void InitList();
	void SetCamra(int mStyle);
	void CalcFPS();
	void DrawTerrain();
	void InitTerr();
	void Init_ArrayData();
	void getDemBlockTexture(int RowIndex, int ColIndex, int Index);
	void ReadDataFromFiles(CString strfiles, int Index);
	void ExportBlobDemToFIle(CString strFilename, int RowIndex, int ColIndex);
	void PositionCamera(double positionX, double positionY, double positionZ, double viewX, double viewY, double viewZ, double upVectorX, double upVectorY, double upVectorZ);
	void Init_data();
	CVector3 Strafe();
	CVector3 UpVector();
	CVector3 GetView();
	CVector3 GetPos();

	void SetSkyProjection(); //背景天空投影設置
	void SetSkyProjectionNavigate();//背景天空導航圖投影設置
	void DrawBackground();////繪製背景天空
	void makeSkykList();
	void DrawSky();
	
	

	CDC*	    m_pDC;			
	HGLRC		m_hRC;	
	
	int m_SCREEN_WIDTH;		//屏幕寬度
	int m_SCREEN_HEIGHT;	//屏幕高度
	
	int WinViewX,WinViewY;	//存儲所定義視口的寬度和高度
	BOOL bStereoAvailable;	//顯卡是否支持立體顯示
	
	GLfloat m_ViewWideNarrow;   //用來調整gluPerspective()函數定義平截頭體的視野的角度(增大或減小)
	double m_near,m_far;	//gluPerspective()函數定義平截頭體的近剪裁平面和遠剪裁平面的距離
	float m_aspectRatio; //gluPerspective()函數定義的平截頭體的縱橫比
	float m_FrustumAngle;
	float m_viewdegree;	//觀察點與視點之間的俯視角
	float m_es;
	
	//在正射投影模式下地形的x,y中心坐標和x,y方向的比例
	float m_ortho_CordinateOriginX;//在正射投影模式下地形的x中心坐標
	float m_ortho_CordinateOriginY;//在正射投影模式下地形的y中心坐標
	float m_ortho_CordinateXYScale;//在正射投影模式下地形的x,y方向的比例
	
	AllocUnAlloc2D3D m_AllocUnAlloc2D3D;//定義用於實現對一維、二維和三維數組分配和銷毀內存的類變量。
	BOOL m_BhasInitOCI;//標識是否初始化OCI
	int m_nMapSize;//記錄地形子塊大小,渲染地形使用
	long m_Radius;//包圍球半徑,用來實現對地形剪裁(位於包圍球半徑以便的地形塊不需繪製)
	float m_lodScreenError;//設定的屏幕誤差

	//視景體剪裁半徑
	long m_R;
	long m_r;
	
	
	//地形參數變量
	int m_loddem_StartRow;//存儲調入的地形塊的起始行
	int m_loddem_StartCol;//存儲調入的地形塊的起始列
	int m_loddem_EndRow;//存儲調入的地形塊的結束行
	int m_loddem_EndCol;//存儲調入的地形塊的結束列
	float **m_pHeight_My;//存儲調入地形子塊的高程點
	int m_LodDemblockNumber; //存儲所加載的地形塊數量
	double m_DemBlockCenterCoord[MAX_TEXTURENUM][2]; //存儲所加載的地形塊中心大地坐標
	int m_lodDemBlock[MAX_TEXTURENUM][4];//存儲調入的地形塊的行號,列號,調入的地形塊數量
	bool *m_pbm_DemLod;//標識地形塊是否被調入
	int **m_DemLod_My;//存儲調入地形子塊的行號,列號等信息
	int m_DemLodIndex[MAX_TEXTURENUM];//存儲調入的地形子塊的索引號
	int *m_tempDemLodIndex;//存儲前一DEM子塊的索引
	int *m_bsign;//標識所調入的地形塊是否參與繪製(若值為1,表示調入的地形子塊參與繪製,=0,表示未參與繪製,位於視景體外,被剔除掉了)
	bool **m_pbQuadMat;//標識地形子塊的節點是否還需要繼續分割
	float  m_maxHeight,m_minHeight;//DEM數據點的最大最小高程值
	float m_heighScale;//DEM數據點高程式縮放比例( <1:高程減小 =1:高程不變 >1:高程增大)
	bool m_bLoadInitDemData;//標識加載初始化地形和影像紋理是否成功
	
	//紋理參數變量
	double m_Texturexy[MAX_TEXTURENUM][4];//存儲調入的影像紋理子塊的左下和左上角x,y坐標
	int m_demTextureID[MAX_TEXTURENUM];//存儲調入的影像紋理子塊的紋理ID,手於綁定紋理
	int m_currebtPhramid; //存儲當前影像紋理的LOD級別
	CTexture m_texturesName; //定義CTexture類的變量,用於實現影像紋理的加載 
	CTexture m_cTxtSky;//定義CTexture類的變量,用於實現背景天空紋理的加載 
	
	
	//相機參數變量 
	BOOL m_bCamraInit;//標識相機是否初始化 
	CVector3 m_vPosition;	//相機視點坐標
	CVector3 m_vView;		//相機觀察點坐標
	CVector3 m_vUpVector;	//相機向中三維矢量
	CVector3 m_oldvPosition;//相機前一視點坐標
	float m_viewHeight;//視點高度
	float m_oldviewHeight;//前一視點高度
	float m_camraDistence;//相機距離 
	CVector3 m_originView;//相機初始視點坐標
	CVector3	m_originPosition;//相機初始觀察點坐標
	
	
	//用於計算相機事參數的CVector3類型變量
	CVector3 m_vStrafe;		
	CVector3 View;		

	//刷新頻率參數
	float mTimeElaps; //用於計算刷新頻率的時間值
	int nCountFrame;//繪製的幀數
	
	//屏幕誤差負反饋參數
	BOOL    m_checkt; //標識是否打開屏幕誤差負反饋功能
	long	m_maxTrinum;//最大三角形數量
	long	m_minTrinum;//最小三角形數量
	float	m_k1; //放大參數
	float	m_k2;//縮小參數

	int m_Drawmode; //繪製模式(1://線框模式  2://渲暈模式	3://紋理模式)
 	BOOL m_stereo;  //是否立體模式(TRUE:立體 FALSE:非立體)
	BOOL m_bShowbreviary;//是否顯示縮略視圖
	
	//視景體參數
	float m_sectorStartAngle,m_sectorEndAngle;
	double m_triPtA[2],m_triPtB[2],m_triPtC[2];
	Point m_Viewpolygon[3];	 //存儲視口三角扇形的三個坐標點
	//存儲視口三角扇形的三個坐標點中的最大最小坐標
	double m_Viewpolygon_Minx,m_Viewpolygon_Miny,m_Viewpolygon_Maxx,m_Viewpolygon_Maxy;

	
	//渲染參數
	int  m_RenderDemblockNumber;//渲染的地形塊數量
	int mCurrentTextID;//當前渲染地形塊的紋理ID號
	int m_CurrentDemArrayIndex;//當前渲染地形塊的數組索引

	//顯示列表參數 
	GLuint m_clockList; //時鐘指北針顯示列表
	GLuint m_SkyList;//背景天空顯示列表
	GLuint m_TerrainList;
	GLuint m_TerrainZoomroadList;
	GLuint m_NavigateList;
	GLuint m_HazardList;
	GLuint m_HazardList_Ortho;
	GLuint m_TunnelDMList;//隧道洞門顯示列表

	GLuint m_FAHPList;
	GLuint m_Rail3DwayList; //線路三維模型顯示列表(透視投影模式)
	GLuint m_Rail3DwayList_Ortho;//線路三維模型顯示列表(正射投影模式)
	GLuint m_Rail3DwayList_Ortho_Multi;
	GLuint m_QDList;//橋樑橋墩顯示列表
	GLuint m_QMList;
	GLuint m_QLanList;//橋樑欄杆顯示列表
//	GLuint m_TrainList;// 火車模型的
	GLuint m_SelectBridgeList;//
	

	CalCulateF mCalF;//視景體計算公共類變量 

	//存儲最大、最小高程對應戲、綠、藍三色的顏色值
	float minZ_color_R,minZ_color_G,minZ_color_B;
	float maxZ_color_R,maxZ_color_G,maxZ_color_B;
	
	//空間查詢標誌參數
	int		m_shizxLength;//查詢標誌的十字線長度
	int		m_shuzxHeight;//查詢標誌的豎直線長度
	int m_QueryLineWidth;//查詢標誌線的寬度
	int m_QueryColorR,m_QueryColorG,m_QueryColorB;//查詢標誌線的顏色(紅,綠,藍)
	
	//空間查詢標誌
	BOOL m_bSearchCorrdinate;
	BOOL m_bSearchDistence;
	BYTE m_QueryType; //標識空間查詢類別
	int m_bSearchDistencePtNums;//查詢時點取的空間點數
	double pt1[3],pt2[3];//存儲查詢的坐標
	long m_linePtnums;//當前線路方案設計交點總數
	long m_oldlinePtnums; //原有線路方案設計交點數
	
	
	bool m_bmouseView;	//是否起用鼠標控制相機
	POINT m_oldMousePos;//前一鼠標位置
	
	//相機旋轉參數
	float	m_Step_X; //相機在X方向移動的步長(鼠標控制)
	float	m_Step_Z; //相機在Z方向移動的步長(鼠標控制)
	float Derx;	//相機視點在X方向上的變化量
	float Derz;	//相機視點在Z方向上的變化量

	float m_xTrans;	//在X方向上移動的距離(鍵盤控制)
	float m_zTrans;	//在Z方向上移動的距離(鍵盤控制)
	int m_keynumber;//標識鍵盤按鍵值

	BYTE m_ViewType;   // 標識投影方式類別
	float m_ViewXYscale;//存儲視口高寬比例
	float m_OrthoViewSize;//正射投影模式下視景體大小
	float m_OrthotranslateX,m_OrthotranslateY;//正射投影模式下X軸方向和Y軸方向移動的距離值
	BYTE m_OrthoZommPan; //正射投影模式下場景控制模式
	//開窗縮放時記錄矩形窗口的左下和右上x,y坐標
	int m_OrthoZoomWindowRect_x1,m_OrthoZoomWindowRect_y1,m_OrthoZoomWindowRect_x2,m_OrthoZoomWindowRect_y2;
	int m_preX,m_preY; //前一坐標
	int m_currentX,m_currentY;//當前坐標
	int m_pushNumb;//按鍵次數
	
	BOOL b_haveMadeRail3DwayList; //是否已經有三維線路顯示列表(透視投影模式下)
	BOOL b_haveMadeRail3DwayList_Ortho;//是否已經有三維線路顯示列表(正射投影模式下)
	BOOL b_haveTerrainZoomroadList;///線路三維建模後是否建立了地形TIN模型的顯示列表
	
	Bridge m_Bridge; //橋樑
	Tunnel  m_Tunnel; //隧道
	Railway m_Railway; //線路路基結構
	
	
	
	C3DSModel *g_3dsModels; 
	BOOL bHaveLoadModel;
	double m_QD_minx,m_QD_miny,m_QD_maxx,m_QD_maxy,m_QD_minz,m_QD_maxz; 
	double m_QM_minx,m_QM_miny,m_QM_maxx,m_QM_maxy,m_QM_minz,m_QM_maxz;	
	double m_Train_minx,m_Train_miny,m_Train_maxx,m_Train_maxy,m_Train_minz,m_Train_maxz; 
	double m_TunnelDM_minx,m_TunnelDM_miny,m_TunnelDM_maxx,m_TunnelDM_maxy,m_TunnelDM_minz,m_TunnelDM_maxz; 
	

	CTexture m_txture;
	CTexture m_cTxtureDetail;
	CTexture m_txt;
	CTexture m_cTxtDetail;
	CTexture m_LitLodtextureName;
	
	CTexture m_cTxtureBP; //路基邊坡紋理
	CTexture m_cTxtureLJ;//路肩紋理
	CTexture m_cTxtureGdToLJ;//道床邊坡紋理
	CTexture m_cTxtureRailway;//軌道紋理
	CTexture m_cTxtureSuigou;//水溝紋理
	CTexture m_cBridgeHpm; ////橋頭下方護坡面紋理
	CTexture m_cBridgeHL; //橋欄
	CTexture m_cTxturePT;//邊坡平台紋理	
	CTexture m_cTunnel;//隧道內牆紋理
	CTexture m_cTunnel_dm;//隧道洞門紋理
	CTexture m_cTunnel_dmwcBp;//隧道洞門外側邊坡紋理
	

	//飛行路徑參數
	GLfloat m_StaticHeight;		//固定飛行高度
	GLfloat m_ViewUpDown;		//視角上,下傾
	int m_flyspeed;//飛行時的計時器時間間隔 
	BOOL m_PathFlag;//是否輸入飛行路徑
	
	int m_bridgeColorR,m_bridgeColorG,m_bridgeColorB; //橋樑顏色	
	CArray<PCordinate,PCordinate> PtBridgeHPUp;
	CArray<PCordinate,PCordinate> PtBridgeHPDown;
	
	BOOL b_haveGetRegion;//標識是否建立線路封閉區域
	
	double m_PreZooomLC;//漫遊時記錄前一里程
	double m_CurZooomLC;//漫遊時記錄當前里程
	
	CString m_3DSfilename_QD; //橋墩模型文件名稱
	CString m_3DSfilename_TunnelDM; //隧道洞門模型文件名稱
	
	float m_NorthPtangle; //指北針初始指向角度
	
	CDXF mdxf; //定義DXF變量
	

	vertexSet m_Vertices; //存儲頂點坐標
	triangleSet m_Triangles; //存儲三角形數據

	BOOL m_bSelectFlyPath; //標識在進行飛行路徑的選取 
	BOOL m_ShowFlyPath; //標識是否顯示飛行路徑

	BYTE m_FlyHeightType;//三維漫遊類型(固定高度漫遊,固定高差漫遊)
	

	//錄製AVI參數
	int m_MovieWidth;  //AVI的寬度
	int m_MovieHeight; //AVI的高度 
	int m_MoviemaxWidth;  //AVI的最大寬度
	int m_MoviemaxHeight; //AVI的最大高度 
	int m_AVIFrame;  //AVI捕捉幀率
	CString m_AviFilename; //AVI文件名
	BOOL m_Beginrecording;       //開始錄製AVI視頻動畫的標誌
	CAVICapture *m_movieCapture; //捕捉動畫
	bool m_Recording; //標識是否正在捕捉視頻動畫
	

//	
	//錄製圖像序列參數
	CClientCapture CapturedImage;
	CString m_RecordPicturename; //錄製圖像名稱
    int		m_PictureNumbers; //錄製圖像的數量
	int		m_recordPictSpeed;  //採集圖像的頻率，即每隔多少毫秒錄製一幅圖像
	BOOL	m_RecordPicture;     //錄像圖像序列的標誌
	CRect m_rcPrintRect;  //記錄圖像客戶區大小
	
	BOOL SetupPixelFormat();
	BOOL InitializeOpenGL(CDC *pDC);
	BOOL LoadInitDemData();

	Snow m_snows;
	CWinThread* m_lpThread;
	
};

#ifndef _DEBUG  // debug version in T3DSystemView.cpp
inline CT3DSystemDoc* CT3DSystemView::GetDocument()
   { return (CT3DSystemDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T3DSYSTEMVIEW_H__3A8D7F07_F2EE_46F8_A484_C22327088E9C__INCLUDED_)
