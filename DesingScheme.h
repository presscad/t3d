 
 
 

#if !defined(AFX_DESINGSCHEME_H__5B5184D2_8345_4FB9_A7DA_9D8B33E76043__INCLUDED_)
#define AFX_DESINGSCHEME_H__5B5184D2_8345_4FB9_A7DA_9D8B33E76043__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXSCHEMENUMS 25

//�T���I���е��c
typedef struct  
{
	double x;	//x����
	double y;	//y����
	double z;	//z����
}Cordinate3D, *PCordinate3D;


//�Ƥ����`���c
typedef struct  
{
	Cordinate3D SuiGouL[6];//�����������c
	Cordinate3D SuiGouR[6];//�����������c
	BOOL bhaveSuiGou_L;//�O�������O�_������ 
	BOOL bhaveSuiGou_R;//�O���k���O�_������
	
}PaiSuiGou, *PPaiSuiGou;


//�@�Y���c
typedef struct  
{
	Cordinate3D Hp[3];//�@���@�Y���ܭ��I�T������
	float h; //
	float m;
	float b;
	int style;//�@�Y����
}HuPo, *PHuPo;

//�����`���c
typedef struct  
{
	HuPo HuPo_L[3];//�����@�Y���c
	int Huponums_L;//�����@�Y�ż�
	HuPo HuPo_R[3];//�k���@�Y���c
	int Huponums_R;//�k���@�Y�ż�
	int TW_left;//TW_left=-1:����  0:�������   1:���� 99:���G�����I
	int TW_right;//TW_right=-1:����  0:�������   1:����  99:���G�����I
	double Lc;//���{
	CString strJDStyle;// 
}LuQianHuPo,*PLuQianHuPo;

typedef struct 
{
	long InsertIndex;
	CArray<PLuQianHuPo,PLuQianHuPo> tempHuPo;
}LuQianHuPoTemp,*PLuQianHuPoTemp;

//�u�����c
typedef struct  
{
	double x1; //�����y�D�I����
	double y1;
	double z1;
	
	double x2;//�k���y�D�I����
	double y2;
	double z2;

	int TW_left; //�����������
	int TW_right;//�����������
	float mAngle;//��e���ਤ��
	float QDHeight;//���[����
}Railway3DCordinate, *PRailway3DCordinate;


//�u���T���I��X���c
typedef struct  
{
	double x;//�I��x����
	double y;//�I��y����
	double z;//�I��z����
	CString strJDStyle;
	float dmh; //�I���a�����{
	float Derh;//�I�����t
	double Lc;//�I�����{
}Cordinate, *PCordinate;

//�G�D���c
typedef struct  
{

	double x1;//�G�D�������I��x����
	double y1;//�G�D�������I��y����
	double z1;//�G�D�������I��z����
	
	double x2;//�G�D�k�����I��x����
	double y2;//�G�D�k�����I��y����
	double z2;//�G�D�k�����I��z����
	
	int Tunnnelindex;//�G�D�b�`�u���G�D�������޸�
	CString name;//�G�D�W��
	CArray<PCordinate,PCordinate> tunnelArc; //�G�D�������꩷�I���c
	
}Railway3DTunnnel, *PRailway3DTunnnel;

//�G�D�_�����c 
typedef struct  
{
	float	height; //�G�D����
	float	Archeight; //�G�D�꩷����
	float	WallHeight; //�G�D���𰪫�
	float	ArcSegmentNumber;//�G�D�꩷���q��
	float	width; //�G�D�e��
	float	H;//�G�D�꩷���ݦA�V�W������
	float	L;//�G�D�}�����ݥ��k�ⰼ�������e�� 
	
}Tunnel;

//�G�D�B���٫H�����c
typedef struct 
{
	double StartLC; //�G�D�B���٪��_�l���{
	double EndLC;//�G�D�B���٪����I���{
	float mStartangle; //�G�D�B���ٶi�f�ݨ���
	float mEndAngle;  //�G�D�B���٥X�f�ݨ���
	int startIndex; //�i�f�ݯ��޸�
	int endIndex;//�X�f�ݺݯ��޸�
	Cordinate StartLeftXYZ;//�i�f�ݥ������I��x,y,z����
	Cordinate StartRightXYZ;//�i�f�ݥk�����I��x,y,z����
	Cordinate EndLeftXYZ;//�X�f�ݥ������I��x,y,z����
	Cordinate EndRightXYZ;//�X�f�ݥk�����I��x,y,z����
	CArray<PCordinate,PCordinate> m_ReginPt_Start;	//�G�D/���٫ʳ��ϰ���ɽu���I(�G�D�i�f)
	CArray<PCordinate,PCordinate> m_ReginPt_End;	//�G�D/���٫ʳ��ϰ���ɽu���I(�G�D�X�f)
}TunnnelBridgeInformation, *PTunnnelBridgeInformation;

//���ٵ��c
typedef struct  
{
	double x1; //���ٰ_�Ix����
	double y1;//���ٰ_�Iy����
	double z1;//���ٰ_�Iz����
	double Lc1; //���ٰ_�I���{
	double x2;//���ٲ��Ix����
	double y2;//���ٲ��Iy����
	double z2;//���ٲ��Iz����
	double Lc2;//���ٲ��I���{
	CString name;//���٦W��
}CordinateBridge, *PCordinateBridge;

//���ټҫ����c
typedef struct  
{
	float	m_Bridge_HLSpace;	//����������Z
	float	m_Bridge_HLWidth;	//��������e��
	float	m_Bridge_HLHeight;	//�����������
	float	m_Bridge_QDSpace;	//���[���Z
	int     m_Bridge_HPangle;  //���Y�@�Y�ɨ�

}Bridge;

//�]�p��׫H�����c
typedef struct 
{
	CString	Schemename;		//��צW��			
	CString strDesigngrade;	//�]�p����			
	CString strDraughtstyle;//�o������			
	CString strBlocomotiveStyle;//��������		
	CString strCBbsStyle;				
	CString strTerrainstyle;	//�a�����O		
	CString strEngineeringcondition;	//�u�{����
	int		designspeed;			//�]�p�t��	
	int		minRadius;				//�̤p���u�b�|	
	int		dxfLength;				//��o�u�̤p����	
	float	minSlopeLength;			//�̤p�Y��	
	float	maxSlope;				//�̤j�Y��	
	float	maxSlopePddsc;			//�̤j�Y�ץN�Ʈt
	double	StartLC;				//�_�l���{		
	double	EndLC;					//�פ�{	
	int Index;						//��ׯ���	
}SchemeData, *PSchemeData;

//�u���]�p���I���c
typedef struct  
{
	CString  ID;	//���IID��
	double  JDLC;	//���I���{
	float Alfa;		//���I�ਤ
	float fwj;		//���I����1
	float fwj2;		//���I����2
	float T;		//���u��
	int L0;			//�w�M���u��
	float L;		//���u��
	float Ly;		//
	float Jzxc;		//�����u��
	double HZ;		//�w���I���{
	double ZH;		//���w�I���{
	double HY;		//�w���I���{
	double YH;		//��w�I���{
	long R;			//���u�b�|
	float E;		//�~�ڶZ
	float P;		//
	float Dist;		//
	int  RoateStyle;//��������(����,�k��)
	double x; //���Ix����
	double y;//���Iy����
	double z;//���Iz����
	
	PCordinate ZH_xy;//���w�I����
	PCordinate HZ_xy;//�w���I����
	PCordinate YH_xy;//��w�I����
	PCordinate HY_xy;//�w���I����
	
	double Cneterx; //���u���x����
	double Cnetery;//���u���y����
	
}LineCurve, *PLineCurve;

//�����_�����c
typedef struct  
{
	float   m_Railway_width; //�����_���`�e��
	float	m_Lj_width;	//���Ӽe��
	float	m_Lj_Dh;	//��Ӧ���}������
	float   m_GuiMianToLujianWidth;//�K�y����Ӫ��Z��
	float	m_TieGui_width;	//�K�y���Z
	
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





















