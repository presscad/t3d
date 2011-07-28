 
 
 

#if !defined(AFX_DESINGSCHEME_H__5B5184D2_8345_4FB9_A7DA_9D8B33E76043__INCLUDED_)
#define AFX_DESINGSCHEME_H__5B5184D2_8345_4FB9_A7DA_9D8B33E76043__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXSCHEMENUMS 25

//三維點坐標結構
typedef struct  
{
	double x;	//x坐標
	double y;	//y坐標
	double z;	//z坐標
}Cordinate3D, *PCordinate3D;


//排水溝總結構
typedef struct  
{
	Cordinate3D SuiGouL[6];//左側水溝結構
	Cordinate3D SuiGouR[6];//左側水溝結構
	BOOL bhaveSuiGou_L;//記錄左側是否有水溝 
	BOOL bhaveSuiGou_R;//記錄右側是否有水溝
	
}PaiSuiGou, *PPaiSuiGou;


//護坡結構
typedef struct  
{
	Cordinate3D Hp[3];//一階護坡的話個點三維坐標
	float h; //
	float m;
	float b;
	int style;//護坡類型
}HuPo, *PHuPo;

//路基總結構
typedef struct  
{
	HuPo HuPo_L[3];//左側護坡結構
	int Huponums_L;//左側護坡級數
	HuPo HuPo_R[3];//右側護坡結構
	int Huponums_R;//右側護坡級數
	int TW_left;//TW_left=-1:路塹  0:填挖平衡   1:路堤 99:橋隧中間點
	int TW_right;//TW_right=-1:路塹  0:填挖平衡   1:路堤  99:橋隧中間點
	double Lc;//里程
	CString strJDStyle;// 
}LuQianHuPo,*PLuQianHuPo;

typedef struct 
{
	long InsertIndex;
	CArray<PLuQianHuPo,PLuQianHuPo> tempHuPo;
}LuQianHuPoTemp,*PLuQianHuPoTemp;

//線路結構
typedef struct  
{
	double x1; //左側軌道點坐標
	double y1;
	double z1;
	
	double x2;//右側軌道點坐標
	double y2;
	double z2;

	int TW_left; //左側填挖類型
	int TW_right;//左側填挖類型
	float mAngle;//當前旋轉角度
	float QDHeight;//橋墩高度
}Railway3DCordinate, *PRailway3DCordinate;


//線路三維點綜合結構
typedef struct  
{
	double x;//點的x坐標
	double y;//點的y坐標
	double z;//點的z坐標
	CString strJDStyle;
	float dmh; //點的地面高程
	float Derh;//點的高差
	double Lc;//點的里程
}Cordinate, *PCordinate;

//隧道結構
typedef struct  
{

	double x1;//隧道左側邊點的x坐標
	double y1;//隧道左側邊點的y坐標
	double z1;//隧道左側邊點的z坐標
	
	double x2;//隧道右側邊點的x坐標
	double y2;//隧道右側邊點的y坐標
	double z2;//隧道右側邊點的z坐標
	
	int Tunnnelindex;//隧道在總線路隧道中的索引號
	CString name;//隧道名稱
	CArray<PCordinate,PCordinate> tunnelArc; //隧道內頂面圓弧點結構
	
}Railway3DTunnnel, *PRailway3DTunnnel;

//隧道斷面結構 
typedef struct  
{
	float	height; //隧道高度
	float	Archeight; //隧道圓弧高度
	float	WallHeight; //隧道立牆高度
	float	ArcSegmentNumber;//隧道圓弧分段數
	float	width; //隧道寬度
	float	H;//隧道圓弧頂端再向上的高度
	float	L;//隧道洞門頂端左右兩側延伸的寬度 
	
}Tunnel;

//隧道、橋樑信息結構
typedef struct 
{
	double StartLC; //隧道、橋樑的起始里程
	double EndLC;//隧道、橋樑的終點里程
	float mStartangle; //隧道、橋樑進口端角度
	float mEndAngle;  //隧道、橋樑出口端角度
	int startIndex; //進口端索引號
	int endIndex;//出口端端索引號
	Cordinate StartLeftXYZ;//進口端左側邊點的x,y,z坐標
	Cordinate StartRightXYZ;//進口端右側邊點的x,y,z坐標
	Cordinate EndLeftXYZ;//出口端左側邊點的x,y,z坐標
	Cordinate EndRightXYZ;//出口端右側邊點的x,y,z坐標
	CArray<PCordinate,PCordinate> m_ReginPt_Start;	//隧道/橋樑封閉區域邊界線路點(隧道進口)
	CArray<PCordinate,PCordinate> m_ReginPt_End;	//隧道/橋樑封閉區域邊界線路點(隧道出口)
}TunnnelBridgeInformation, *PTunnnelBridgeInformation;

//橋樑結構
typedef struct  
{
	double x1; //橋樑起點x坐標
	double y1;//橋樑起點y坐標
	double z1;//橋樑起點z坐標
	double Lc1; //橋樑起點里程
	double x2;//橋樑終點x坐標
	double y2;//橋樑終點y坐標
	double z2;//橋樑終點z坐標
	double Lc2;//橋樑終點里程
	CString name;//橋樑名稱
}CordinateBridge, *PCordinateBridge;

//橋樑模型結構
typedef struct  
{
	float	m_Bridge_HLSpace;	//橋樑欄杆間距
	float	m_Bridge_HLWidth;	//橋樑欄杆寬度
	float	m_Bridge_HLHeight;	//橋樑欄杆高度
	float	m_Bridge_QDSpace;	//橋墩間距
	int     m_Bridge_HPangle;  //橋頭護坡傾角

}Bridge;

//設計方案信息結構
typedef struct 
{
	CString	Schemename;		//方案名稱			
	CString strDesigngrade;	//設計等級			
	CString strDraughtstyle;//牽引類型			
	CString strBlocomotiveStyle;//閉塞類型		
	CString strCBbsStyle;				
	CString strTerrainstyle;	//地形類別		
	CString strEngineeringcondition;	//工程條件
	int		designspeed;			//設計速度	
	int		minRadius;				//最小曲線半徑	
	int		dxfLength;				//到發線最小長度	
	float	minSlopeLength;			//最小坡長	
	float	maxSlope;				//最大坡度	
	float	maxSlopePddsc;			//最大坡度代數差
	double	StartLC;				//起始里程		
	double	EndLC;					//終止里程	
	int Index;						//方案索引	
}SchemeData, *PSchemeData;

//線路設計交點結構
typedef struct  
{
	CString  ID;	//交點ID號
	double  JDLC;	//交點里程
	float Alfa;		//交點轉角
	float fwj;		//交點偏角1
	float fwj2;		//交點偏角2
	float T;		//切線長
	int L0;			//緩和曲線長
	float L;		//曲線長
	float Ly;		//
	float Jzxc;		//夾直線長
	double HZ;		//緩直點里程
	double ZH;		//直緩點里程
	double HY;		//緩圓點里程
	double YH;		//圓緩點里程
	long R;			//曲線半徑
	float E;		//外矢距
	float P;		//
	float Dist;		//
	int  RoateStyle;//旋轉類型(左轉,右轉)
	double x; //交點x坐標
	double y;//交點y坐標
	double z;//交點z坐標
	
	PCordinate ZH_xy;//直緩點坐標
	PCordinate HZ_xy;//緩直點坐標
	PCordinate YH_xy;//圓緩點坐標
	PCordinate HY_xy;//緩圓點坐標
	
	double Cneterx; //曲線圓心x坐標
	double Cnetery;//曲線圓心y坐標
	
}LineCurve, *PLineCurve;

//路基斷面結構
typedef struct  
{
	float   m_Railway_width; //路基斷面總寬度
	float	m_Lj_width;	//路肩寬度
	float	m_Lj_Dh;	//碴肩至碴腳的高度
	float   m_GuiMianToLujianWidth;//鐵軌到碴肩的距離
	float	m_TieGui_width;	//鐵軌間距
	
}Railway;


typedef struct  
{
	long boreLayerID;
	BOOL bDraw;
}BoreLayerDraw, *PBoreLayerDraw;


typedef struct  
{
	double StartPt[3];
	double EndPt[3];
	int mlayerID;
}BoreSectionLine, *PBoreSectionLine;


class CDesingScheme 
{
public:
	int GetBlockID(double x,double y);
	void GetTunnelcordinate(float TotalHeight,float Archeight,float WallHeight,float Width,int  ArcSegmentNumber);
	void GetTieGuicordinate(float Railwaywidth, float m_GDwidth);
	void GetZhenMucordinate(float ZhenMuJJ,float Railwaywidth);
	void drawBitmapFormFile(CString BitmapFilePath, CDC *pDC, CRect rect);
	float GetDistenceXYZ(double x1, double y1, double z1, double x2, double y2,double z2);
	void GetBirdgeQDcordinate(float BridgeQDJJ);
	void GetHs(double x0,double y0,double z0,float alfa,float mangle,int Style,double *px,double *py,double *pz);
	void GetHpD(double x,double y,double z,float mAngle,float mHpangle,double *ax,double *ay,double *az);
	float GetANgle(double x1,double z1,double x2,double z2);
	void GetBirdgeLGcordinate(float BridgeLGJJ);
	void Get3DLineModelLast(double x1, double y1, double z1,double x2, double y2, double z2, float fRailwayWidth, float LjWidth, float h_FromGmToLj,float mWidthGuiMianToLujian,float mAngleLujinaToBianPo,CString strJDstyle,CString strJDstyleNext,long index,double mLC);
	void Get3DLineModel(double x1,double y1,double z1,double x2,double y2,double z2,float fRailwayWidth,float LjWidth,float h_FromGmToLj,float mWidthGuiMianToLujian,float mAngleLujinaToBianPo,CString strJDstyle,CString strJDstyleNext,long index,double mLC);
	void InertHuPoPts();
	double GetDistenceXY(double x1,double y1,double x2,double y2);
	void GetYQXXY(double centerx,double centery, long R, int RoateStyle, float LL,float alfa,double HY_xy_x,double HY_xy_y,double YH_xy_x,double YH_xy_y, double *xc, double *yc);
	void GetQLXY(float L0,long R,int RoateStyle,float LL,float fwj,double ZH_xy_x,double ZH_xy_y,double HZ_xy_x,double HZ_xy_y,double *xc,double *yc,int Q_H_L);
	void LoadData(CString strSchemeName);
	int GetMinRfromCriterion(int mspeed,int EngineeringConditionStyle);
	int GetMinL0(int mRindex);
	CString GetLC(double LC);
	void SavePlaneCurveData();
	
	SchemeData SchemeDatass[MAXSCHEMENUMS];
	
	
	CArray<PLineCurve,PLineCurve> JDCurveElements;
	CArray<PLineCurve,PLineCurve> JDCurveElementss[MAXSCHEMENUMS];
	CArray<PCordinate,PCordinate> PtS_JD;
	CArray<PCordinate,PCordinate> PtS_3DLineZX[MAXSCHEMENUMS];;

	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_Railway3D[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayLj3D[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayLjToBP3D[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayBP3D[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_BridgeLG3D[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_BridgeQD3D[MAXSCHEMENUMS];
	CArray<PRailway3DTunnnel,PRailway3DTunnnel> PtS_Tunnel3D[MAXSCHEMENUMS];
	CArray<PTunnnelBridgeInformation,PTunnnelBridgeInformation> TunnelInfor[MAXSCHEMENUMS];
	CArray<PTunnnelBridgeInformation,PTunnnelBridgeInformation> BridgeInfor[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayZhenMu[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayTieGui[MAXSCHEMENUMS];

	CArray<PPaiSuiGou,PPaiSuiGou> PtS_PaiSuiGou[MAXSCHEMENUMS];

	CArray<PLuQianHuPo,PLuQianHuPo> PtS_HuPo[MAXSCHEMENUMS];
	CArray<PLuQianHuPoTemp,PLuQianHuPoTemp> PtSHuPoTemp;
	
	
	CArray<long,long>m_borelayerID;
	CArray<PBoreLayerDraw,PBoreLayerDraw>m_BorelayerDraw;
	CArray<PBoreSectionLine,PBoreSectionLine> P_BoreSectionLine[3];
	BOOL bDrawTerrSurface;
	
	int m_minR160_L0[15][2];
	int m_minR140_L0[17][2];
	int m_minR120_L0[19][2];
	int m_minR100_L0[22][2];
	int m_minR80_L0[23][2];
	
	int m_minPriorityR160_L0[15];
	int m_minPriorityR140_L0[17];
	int m_minPriorityR120_L0[19];
	
	int  m_TotalSchemeNums;
	
	BOOL m_bHaveSaveScheme;
	
	CDesingScheme();
   	virtual ~CDesingScheme();

private:
	void GetTunnelArcCordinate(float TotalHeight, float Archeight, float WallHeight, float Width, int ArcSegmentNumber,double x1,double y1,double z1,double x2,double y2,double z2,float *mAngle);
	void GetBpJD(float H0, float Afla, float mangle, double x0, double z0,int bsignTW,int mLeftRight,double *tx,double *ty,double *tz);
	void GetDMJD(double x1, double y1, double z1,double x2, double y2, double z2,float L, float h0,double x0,double z0,int TW,int LeftRight,\
		double tx0,double ty0,double tz0,double tx1,double ty1,double tz1,double mLC,CString strJDstyle);
	float GetHBridgeHP(float L,float alfa,float mangle,double x0,double z0,int Style,double *xx,double *zz);
	int GetTW(double x,double z,float H);
	float GetH(float L, float Afla, float mAngle,double x0,double z0,int mLeftRight,double *xx,double *zz);
	void Get3DCorrdinate(double x1, double y1, double z1,double x2, double y2, double z2,float dx,float dz, float L,double *x11,double *y11,double *z11,double *x12,double *y12,double *z12,double *x21,double *y21,double *z21,double *x22,double *y22,double *z22 ,float *angle);
	void Save3DlineZXCorrdinateToDB();
	void Save3DlineZX();
	void SavePlaneCurveDataToDB();
	void InitMinR();
	void NeiChaDian(float ZHLength, double x1, double y1, double z1, double x2, double y2, double z2,double lc);
	float GetAlfa(int mTW);
		
	_RecordsetPtr m_pRecordset;
	HRESULT hr;
	_variant_t  Thevalue;  
	_variant_t RecordsAffected;
	
};

#endif // !defined(AFX_DESINGSCHEME_H__5B5184D2_8345_4FB9_A7DA_9D8B33E76043__INCLUDED_)





















