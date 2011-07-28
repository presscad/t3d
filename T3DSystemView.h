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

#define MAX_TEXTURENUM  500  //�w�q�̦h�i�P�ɥ[�����a�ζ��ƶq

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

//�w�q�ʳ��ϰ�u���c
typedef struct  
{
	int index;//�ʳ��ϯ��޸�
	CArray<PCordinate,PCordinate> ReginPts;//�u���ʳ��ϰ�����I���X
	CArray<int,int>GridID;//���ݩ����ID��(�����зǫ��ĥ�DEM�����j�p)
	double minx;//�̤px����
	double miny;//�̤py����
	double maxx;//�̤jx����
	double maxy;//�̤jy����
	
}Regions,*PRegions;


typedef struct  
{
	BOOL bInRegion;//�`�I���O�_�b�ʳ��ϰ�(�u����`�I4�Ө��I�ӳ����b�ʳ��ϰ줺�~���u)
	
} BlockReginInfor,*PBlockReginInfor;

typedef struct
{
	int RegionNum;//�Ӧa�ζ����ʳ��ϰ��`��
	CArray<int,int>GridID;//���ݩ����ID��(�����зǫ��ĥ�DEM�����j�p)
	CArray<PCordinate,PCordinate> ReginPts;//�u���ʳ��ϰ�����I���X
	double minx; //�̤px����
	double miny;//�̤py����
	double maxx;//�̤jx����
	double maxy;//�̤jy����
	
}BlockReginInforMe,*PBlockReginInforMe;

//�w�q�a�ζ������I���X
typedef struct
{
	CArray<PCordinate,PCordinate> ReginPts;//�a�ζ��u�����I���X(�]�A�a���I�M�ʳ��ϰ��I)
	int mDemBlockRow;//������DEM�l�����渹
	int mDemBlockCol;//������DEM�l�����C��
	
}BlockLSPts,*PBlockLSPts;


//�T����3�ӳ��I�H��
typedef struct
{
	Point Pt1;
	Point Pt2;
	Point Pt3;
}TriPt,*PTriPt;

//�s�x�C�Ӧa�ζ������T���ΫH��
typedef struct
{
	CArray<PTriPt,PTriPt>TriPts;
	int mDemBlockRow;//������DEM�l�����渹
	int mDemBlockCol;//������DEM�l�����C��
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
	CArray<PBlockTriInfos,PBlockTriInfos> m_BlockTriInfos;//�s�x�C�Ӧa�ζ����T���ΫH��
	
	virtual ~CT3DSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CArray<PCordinate,PCordinate> m_FlayPath;//�s�x�i�歸����|��ܮɩҿ�ܪ��@�t�C�I����
	CArray<PCordinate,PCordinate> m_FlayPathTempPts;//�s�x�{�ɶi�歸����|��ܮɩҿ�ܪ��@�t�C�I����
	int m_flypathPtIndex; //������|���Я��޸�
	int m_flyPathCurrentPtIndex;//�b����L�{���O����e���|�I�����޸�,�Ω�Ȱ����澹
	BOOL m_FlyPause;//�O�_�Ȱ�����

	CArray<PCordinate,PCordinate> m_TempPts;
	BOOL m_ifZoomonRoad; //���ѬO�_�u�u����׺��C
	
	CArray<PCordinate,PCordinate> m_ReginPtsLeft;//�u���ʳ��ϰ���ɥ����u���I
	CArray<PCordinate,PCordinate> m_ReginPtsRight;//�u���ʳ��ϰ���ɥk���u���I
	CArray<PRegions,PRegions> mRegions;//�u���ʳ��ϰ�����I
	
	CArray<PBlockReginInforMe,PBlockReginInforMe> *mBlockReginInforMe;//�a�θ`�I�T���άO�_���ʳ��ϰ���ɫH��
	
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
	void BuildTunnelDMModelList();//�Ы��G�D�}����ܦC��
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
	float GetOrthoX(double x);	//�p�⥿�g��v�Ҧ��Ux����
	float GetOrthoY(double y);	//�p�⥿�g��v�Ҧ��Uy����
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

	void SetSkyProjection(); //�I���Ѫŧ�v�]�m
	void SetSkyProjectionNavigate();//�I���Ѫžɯ�ϧ�v�]�m
	void DrawBackground();////ø�s�I���Ѫ�
	void makeSkykList();
	void DrawSky();
	
	

	CDC*	    m_pDC;			
	HGLRC		m_hRC;	
	
	int m_SCREEN_WIDTH;		//�̹��e��
	int m_SCREEN_HEIGHT;	//�̹�����
	
	int WinViewX,WinViewY;	//�s�x�ҩw�q���f���e�שM����
	BOOL bStereoAvailable;	//��d�O�_����������
	
	GLfloat m_ViewWideNarrow;   //�Ψӽվ�gluPerspective()��Ʃw�q���I�Y�骺����������(�W�j�δ�p)
	double m_near,m_far;	//gluPerspective()��Ʃw�q���I�Y�骺��ŵ������M���ŵ��������Z��
	float m_aspectRatio; //gluPerspective()��Ʃw�q�����I�Y�骺�a���
	float m_FrustumAngle;
	float m_viewdegree;	//�[���I�P���I������������
	float m_es;
	
	//�b���g��v�Ҧ��U�a�Ϊ�x,y���ߧ��ЩMx,y��V�����
	float m_ortho_CordinateOriginX;//�b���g��v�Ҧ��U�a�Ϊ�x���ߧ���
	float m_ortho_CordinateOriginY;//�b���g��v�Ҧ��U�a�Ϊ�y���ߧ���
	float m_ortho_CordinateXYScale;//�b���g��v�Ҧ��U�a�Ϊ�x,y��V�����
	
	AllocUnAlloc2D3D m_AllocUnAlloc2D3D;//�w�q�Ω��{��@���B�G���M�T���Ʋդ��t�M�P�����s�����ܶq�C
	BOOL m_BhasInitOCI;//���ѬO�_��l��OCI
	int m_nMapSize;//�O���a�Τl���j�p,��V�a�Ψϥ�
	long m_Radius;//�]��y�b�|,�Ψӹ�{��a�ΰŵ�(���]��y�b�|�H�K���a�ζ�����ø�s)
	float m_lodScreenError;//�]�w���̹��~�t

	//������ŵ��b�|
	long m_R;
	long m_r;
	
	
	//�a�ΰѼ��ܶq
	int m_loddem_StartRow;//�s�x�դJ���a�ζ����_�l��
	int m_loddem_StartCol;//�s�x�դJ���a�ζ����_�l�C
	int m_loddem_EndRow;//�s�x�դJ���a�ζ���������
	int m_loddem_EndCol;//�s�x�դJ���a�ζ��������C
	float **m_pHeight_My;//�s�x�դJ�a�Τl�������{�I
	int m_LodDemblockNumber; //�s�x�ҥ[�����a�ζ��ƶq
	double m_DemBlockCenterCoord[MAX_TEXTURENUM][2]; //�s�x�ҥ[�����a�ζ����ߤj�a����
	int m_lodDemBlock[MAX_TEXTURENUM][4];//�s�x�դJ���a�ζ����渹,�C��,�դJ���a�ζ��ƶq
	bool *m_pbm_DemLod;//���Ѧa�ζ��O�_�Q�դJ
	int **m_DemLod_My;//�s�x�դJ�a�Τl�����渹,�C�����H��
	int m_DemLodIndex[MAX_TEXTURENUM];//�s�x�դJ���a�Τl�������޸�
	int *m_tempDemLodIndex;//�s�x�e�@DEM�l��������
	int *m_bsign;//���ѩҽդJ���a�ζ��O�_�ѻPø�s(�Y�Ȭ�1,��ܽդJ���a�Τl���ѻPø�s,=0,��ܥ��ѻPø�s,��������~,�Q�簣���F)
	bool **m_pbQuadMat;//���Ѧa�Τl�����`�I�O�_�ٻݭn�~�����
	float  m_maxHeight,m_minHeight;//DEM�ƾ��I���̤j�̤p���{��
	float m_heighScale;//DEM�ƾ��I���{���Y����( <1:���{��p =1:���{���� >1:���{�W�j)
	bool m_bLoadInitDemData;//���ѥ[����l�Ʀa�ΩM�v�����z�O�_���\
	
	//���z�Ѽ��ܶq
	double m_Texturexy[MAX_TEXTURENUM][4];//�s�x�դJ���v�����z�l�������U�M���W��x,y����
	int m_demTextureID[MAX_TEXTURENUM];//�s�x�դJ���v�����z�l�������zID,���j�w���z
	int m_currebtPhramid; //�s�x��e�v�����z��LOD�ŧO
	CTexture m_texturesName; //�w�qCTexture�����ܶq,�Ω��{�v�����z���[�� 
	CTexture m_cTxtSky;//�w�qCTexture�����ܶq,�Ω��{�I���Ѫů��z���[�� 
	
	
	//�۾��Ѽ��ܶq 
	BOOL m_bCamraInit;//���Ѭ۾��O�_��l�� 
	CVector3 m_vPosition;	//�۾����I����
	CVector3 m_vView;		//�۾��[���I����
	CVector3 m_vUpVector;	//�۾��V���T���ڶq
	CVector3 m_oldvPosition;//�۾��e�@���I����
	float m_viewHeight;//���I����
	float m_oldviewHeight;//�e�@���I����
	float m_camraDistence;//�۾��Z�� 
	CVector3 m_originView;//�۾���l���I����
	CVector3	m_originPosition;//�۾���l�[���I����
	
	
	//�Ω�p��۾��ưѼƪ�CVector3�����ܶq
	CVector3 m_vStrafe;		
	CVector3 View;		

	//��s�W�v�Ѽ�
	float mTimeElaps; //�Ω�p���s�W�v���ɶ���
	int nCountFrame;//ø�s���V��
	
	//�̹��~�t�t���X�Ѽ�
	BOOL    m_checkt; //���ѬO�_���}�̹��~�t�t���X�\��
	long	m_maxTrinum;//�̤j�T���μƶq
	long	m_minTrinum;//�̤p�T���μƶq
	float	m_k1; //��j�Ѽ�
	float	m_k2;//�Y�p�Ѽ�

	int m_Drawmode; //ø�s�Ҧ�(1://�u�ؼҦ�  2://��w�Ҧ�	3://���z�Ҧ�)
 	BOOL m_stereo;  //�O�_����Ҧ�(TRUE:���� FALSE:�D����)
	BOOL m_bShowbreviary;//�O�_����Y������
	
	//������Ѽ�
	float m_sectorStartAngle,m_sectorEndAngle;
	double m_triPtA[2],m_triPtB[2],m_triPtC[2];
	Point m_Viewpolygon[3];	 //�s�x���f�T�����Ϊ��T�ӧ����I
	//�s�x���f�T�����Ϊ��T�ӧ����I�����̤j�̤p����
	double m_Viewpolygon_Minx,m_Viewpolygon_Miny,m_Viewpolygon_Maxx,m_Viewpolygon_Maxy;

	
	//��V�Ѽ�
	int  m_RenderDemblockNumber;//��V���a�ζ��ƶq
	int mCurrentTextID;//��e��V�a�ζ������zID��
	int m_CurrentDemArrayIndex;//��e��V�a�ζ����Ʋկ���

	//��ܦC��Ѽ� 
	GLuint m_clockList; //�������_�w��ܦC��
	GLuint m_SkyList;//�I���Ѫ���ܦC��
	GLuint m_TerrainList;
	GLuint m_TerrainZoomroadList;
	GLuint m_NavigateList;
	GLuint m_HazardList;
	GLuint m_HazardList_Ortho;
	GLuint m_TunnelDMList;//�G�D�}����ܦC��

	GLuint m_FAHPList;
	GLuint m_Rail3DwayList; //�u���T���ҫ���ܦC��(�z����v�Ҧ�)
	GLuint m_Rail3DwayList_Ortho;//�u���T���ҫ���ܦC��(���g��v�Ҧ�)
	GLuint m_Rail3DwayList_Ortho_Multi;
	GLuint m_QDList;//���پ��[��ܦC��
	GLuint m_QMList;
	GLuint m_QLanList;//���������ܦC��
//	GLuint m_TrainList;// �����ҫ���
	GLuint m_SelectBridgeList;//
	

	CalCulateF mCalF;//������p�⤽�@���ܶq 

	//�s�x�̤j�B�̤p���{�������B��B�ŤT�⪺�C���
	float minZ_color_R,minZ_color_G,minZ_color_B;
	float maxZ_color_R,maxZ_color_G,maxZ_color_B;
	
	//�Ŷ��d�߼лx�Ѽ�
	int		m_shizxLength;//�d�߼лx���Q�r�u����
	int		m_shuzxHeight;//�d�߼лx���ݪ��u����
	int m_QueryLineWidth;//�d�߼лx�u���e��
	int m_QueryColorR,m_QueryColorG,m_QueryColorB;//�d�߼лx�u���C��(��,��,��)
	
	//�Ŷ��d�߼лx
	BOOL m_bSearchCorrdinate;
	BOOL m_bSearchDistence;
	BYTE m_QueryType; //���ѪŶ��d�����O
	int m_bSearchDistencePtNums;//�d�߮��I�����Ŷ��I��
	double pt1[3],pt2[3];//�s�x�d�ߪ�����
	long m_linePtnums;//��e�u����׳]�p���I�`��
	long m_oldlinePtnums; //�즳�u����׳]�p���I��
	
	
	bool m_bmouseView;	//�O�_�_�ι��б���۾�
	POINT m_oldMousePos;//�e�@���Ц�m
	
	//�۾�����Ѽ�
	float	m_Step_X; //�۾��bX��V���ʪ��B��(���б���)
	float	m_Step_Z; //�۾��bZ��V���ʪ��B��(���б���)
	float Derx;	//�۾����I�bX��V�W���ܤƶq
	float Derz;	//�۾����I�bZ��V�W���ܤƶq

	float m_xTrans;	//�bX��V�W���ʪ��Z��(��L����)
	float m_zTrans;	//�bZ��V�W���ʪ��Z��(��L����)
	int m_keynumber;//������L�����

	BYTE m_ViewType;   // ���ѧ�v�覡���O
	float m_ViewXYscale;//�s�x���f���e���
	float m_OrthoViewSize;//���g��v�Ҧ��U������j�p
	float m_OrthotranslateX,m_OrthotranslateY;//���g��v�Ҧ��UX�b��V�MY�b��V���ʪ��Z����
	BYTE m_OrthoZommPan; //���g��v�Ҧ��U��������Ҧ�
	//�}���Y��ɰO���x�ε��f�����U�M�k�Wx,y����
	int m_OrthoZoomWindowRect_x1,m_OrthoZoomWindowRect_y1,m_OrthoZoomWindowRect_x2,m_OrthoZoomWindowRect_y2;
	int m_preX,m_preY; //�e�@����
	int m_currentX,m_currentY;//��e����
	int m_pushNumb;//���䦸��
	
	BOOL b_haveMadeRail3DwayList; //�O�_�w�g���T���u����ܦC��(�z����v�Ҧ��U)
	BOOL b_haveMadeRail3DwayList_Ortho;//�O�_�w�g���T���u����ܦC��(���g��v�Ҧ��U)
	BOOL b_haveTerrainZoomroadList;///�u���T���ؼҫ�O�_�إߤF�a��TIN�ҫ�����ܦC��
	
	Bridge m_Bridge; //����
	Tunnel  m_Tunnel; //�G�D
	Railway m_Railway; //�u�����򵲺c
	
	
	
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
	
	CTexture m_cTxtureBP; //������Y���z
	CTexture m_cTxtureLJ;//���ӯ��z
	CTexture m_cTxtureGdToLJ;//�D����Y���z
	CTexture m_cTxtureRailway;//�y�D���z
	CTexture m_cTxtureSuigou;//�������z
	CTexture m_cBridgeHpm; ////���Y�U���@�Y�����z
	CTexture m_cBridgeHL; //����
	CTexture m_cTxturePT;//��Y���x���z	
	CTexture m_cTunnel;//�G�D���𯾲z
	CTexture m_cTunnel_dm;//�G�D�}�����z
	CTexture m_cTunnel_dmwcBp;//�G�D�}���~����Y���z
	

	//������|�Ѽ�
	GLfloat m_StaticHeight;		//�T�w���氪��
	GLfloat m_ViewUpDown;		//�����W,�U��
	int m_flyspeed;//����ɪ��p�ɾ��ɶ����j 
	BOOL m_PathFlag;//�O�_��J������|
	
	int m_bridgeColorR,m_bridgeColorG,m_bridgeColorB; //�����C��	
	CArray<PCordinate,PCordinate> PtBridgeHPUp;
	CArray<PCordinate,PCordinate> PtBridgeHPDown;
	
	BOOL b_haveGetRegion;//���ѬO�_�إ߽u���ʳ��ϰ�
	
	double m_PreZooomLC;//���C�ɰO���e�@���{
	double m_CurZooomLC;//���C�ɰO����e���{
	
	CString m_3DSfilename_QD; //���[�ҫ����W��
	CString m_3DSfilename_TunnelDM; //�G�D�}���ҫ����W��
	
	float m_NorthPtangle; //���_�w��l���V����
	
	CDXF mdxf; //�w�qDXF�ܶq
	

	vertexSet m_Vertices; //�s�x���I����
	triangleSet m_Triangles; //�s�x�T���μƾ�

	BOOL m_bSelectFlyPath; //���Ѧb�i�歸����|����� 
	BOOL m_ShowFlyPath; //���ѬO�_��ܭ�����|

	BYTE m_FlyHeightType;//�T�����C����(�T�w���׺��C,�T�w���t���C)
	

	//���sAVI�Ѽ�
	int m_MovieWidth;  //AVI���e��
	int m_MovieHeight; //AVI������ 
	int m_MoviemaxWidth;  //AVI���̤j�e��
	int m_MoviemaxHeight; //AVI���̤j���� 
	int m_AVIFrame;  //AVI�����V�v
	CString m_AviFilename; //AVI���W
	BOOL m_Beginrecording;       //�}�l���sAVI���W�ʵe���лx
	CAVICapture *m_movieCapture; //�����ʵe
	bool m_Recording; //���ѬO�_���b�������W�ʵe
	

//	
	//���s�Ϲ��ǦC�Ѽ�
	CClientCapture CapturedImage;
	CString m_RecordPicturename; //���s�Ϲ��W��
    int		m_PictureNumbers; //���s�Ϲ����ƶq
	int		m_recordPictSpeed;  //�Ķ��Ϲ����W�v�A�Y�C�j�h�ֲ@����s�@�T�Ϲ�
	BOOL	m_RecordPicture;     //�����Ϲ��ǦC���лx
	CRect m_rcPrintRect;  //�O���Ϲ��Ȥ�Ϥj�p
	
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
