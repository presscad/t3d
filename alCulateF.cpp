// alCulateF.cpp: implementation of the CalCulateF class.
 
 

#include "stdafx.h"
#include "alCulateF.h"
// #include "LoadDefaultRSGeodata.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 
// Construction/Destruction
 
const float PAI=3.1415926;

const   double   INFINITY     =   1e10;     
const   double   ESP   =   1e-5;     
const   int   MAX_N           =   1000;     

CalCulateF::CalCulateF()
{

}

CalCulateF::~CalCulateF()
{

}

 
double CalCulateF::Multiply(Point p1, Point p2, Point p0)
{
	return ((p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y));
}

 
bool CalCulateF::IsOnline(Point point, LineSegment line)
{
	return((fabs(Multiply(line.pt1,line.pt2,point)) < ESP ) &&   
		( ( point.x - line.pt1.x ) * ( point.x - line.pt2.x ) <= 0 ) &&   
		( ( point.y - line.pt1.y ) * ( point.y - line.pt2.y ) <= 0 ) ); 
	
}

 //�P�_�⪽�u�O�_�ۥ�
bool CalCulateF::Intersect(LineSegment L1, LineSegment L2)
{
	return( (max(L1.pt1.x, L1.pt2.x) >= min(L2.pt1.x, L2.pt2.x)) &&   
		(max(L2.pt1.x, L2.pt2.x) >= min(L1.pt1.x, L1.pt2.x)) &&   
		(max(L1.pt1.y, L1.pt2.y) >= min(L2.pt1.y, L2.pt2.y)) &&   
		(max(L2.pt1.y, L2.pt2.y) >= min(L1.pt1.y, L1.pt2.y)) &&   
		(Multiply(L2.pt1, L1.pt2, L1.pt1) * Multiply(L1.pt2, L2.pt2, L1.pt1) >= 0) &&   
		(Multiply(L1.pt1, L2.pt2, L2.pt1) * Multiply(L2.pt2, L1.pt2, L2.pt1) >= 0)   
		);  
	
}

 //�I�O�_�b�h��Τ�
//�I�]x,y�^.�h��Υ�p1(x1,y1),p2(x2,y2),p3(x3,y3),p4(x4,y4)�զ�.
//
//�A�g�夣�L����k�F�G 

// �\��G�P�_�I�O�_�b�h��Τ� 
// ��k�G�D�ѳq�L���I�������u�P�h��ΦU�䪺���I 
// ���סG������I���_�ơA����! 
//�ѼơG 
// POINT p ���w���Y���I 
// LPPOINT ptPolygon �h��Ϊ��U�ӳ��I���С]�����I�i�H���@�P�^ 
// int nCount �h��Ωw�I���Ӽ� 


bool CalCulateF::InPolygon(Point polygon[], int n, Point point)
{
	if (n == 1) 
	{   
		return ( (fabs(polygon[0].x - point.x) < ESP) && (fabs(polygon[0].y - point.y) < ESP) );   
	} 
	else if (n == 2)  
	{   
		LineSegment side;   
		side.pt1 = polygon[0];   
		side.pt2 = polygon[1];   
		return IsOnline(point, side);   
	}   
	
	int count = 0;   
	LineSegment line;   
	line.pt1 = point;   
	line.pt2.y = point.y;   
	line.pt2.x = - INFINITY;   
	
	for( int i = 0; i < n; i++ ) 
	{   
		
		LineSegment side;   
		side.pt1 = polygon[i];   
		side.pt2 = polygon[(i + 1) % n];   
		
		if( IsOnline(point, side) ) 
		{   
			return true;   
		}   
		
		
		if( fabs(side.pt1.y - side.pt2.y) < ESP ) 
		{   
			continue;   
		}   
		
		if( IsOnline(side.pt1, line) ) 
		{   
			if( side.pt1.y > side.pt2.y ) 
				count++;   
		} 
		else if( IsOnline(side.pt2, line) ) 
		{   
			if( side.pt2.y > side.pt1.y )  
				count++;   
		}  
		else if( Intersect(line, side) )  
		{   
			count++;   
		}   
	}   
	
	return ( count % 2 == 1 );   
}

 
CString CalCulateF::RadianToDegree(float RadianAngle)
{
	CString tt;
	if(RadianAngle==0)
	{
		tt.Format("%2d�X%2d��%2d��",0,0,0);
		return tt;
	}
	
	float mangle=RadianAngle*180.0/PAI;
	int m_D=int(mangle);
	mangle= mangle-m_D;
	float mangle2=mangle*60;
	int m_F=int(mangle2);
	mangle2=mangle2-m_F;
	int m_M=int(mangle2*60); 
	
	CString tt1,tt2,tt3;
	if(m_D>9)
		tt1.Format("%d�X",m_D);
	else
		tt1.Format("0%d�X",m_D);
	
	if(m_F>9)
		tt2.Format("%d��",m_F);
	else
		tt2.Format("0%d��",m_F);
	
	if(m_M>9)
		tt3.Format("%d��",m_M);
	else
		tt3.Format("0%d��",m_M);
	
	tt=tt1+tt2+tt3;
	return tt;
}

 
void CalCulateF::GetTWArea(double *mareaT, double *mareaW)
{
 
	
	float areaT,areaW;
	SectionTW m_secTW;
	CString tt;

	m_SectionTW.RemoveAll();
 
	for(long i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize();i++)
	{

		GetDMArea(i,&areaT,&areaW);
		m_secTW.m_LC=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Lc;
		m_secTW.m_TArea=areaT;
		m_secTW.m_WArea=areaW;
	
		tt=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
		if(tt=="���ٰ_�I" || tt=="���ٲ��I" ||tt=="���٤����I")
			m_secTW.m_Style=3;
		else if(tt=="�G�D�_�I" || tt=="�G�D���I" ||tt=="�G�D�����I")
			m_secTW.m_Style=2;
	
		if(areaT>0 && areaW<=0)
			m_secTW.m_Style=1;
		else if(areaT<=0 && areaW>0)
			m_secTW.m_Style=-1;
		else 
			m_secTW.m_Style=0;
		
		
		m_SectionTW.Add(m_secTW);
	}	

	double m_totalarea_T, m_totalarea_W;
	m_totalarea_T=m_totalarea_W=0;
	
	double mT,mW;
	float A1,A2,m,L;
	float mA;
	for(i=0;i<m_SectionTW.GetSize()-1;i++)
	{

		int style=m_SectionTW.GetAt(i).m_Style;
		
		if(style!=2 && style!=3)//���O�G�D�M���٬q
		{
			L=m_SectionTW.GetAt(i+1).m_LC-m_SectionTW.GetAt(i).m_LC;
			A1=m_SectionTW.GetAt(i).m_TArea;
			A2=m_SectionTW.GetAt(i+1).m_TArea;
			
			if(A2<A1)
			{
				mA=A1;
				A1=A2;
				A2=mA;
			}
			
			if(A2<=0)
				m=0;
			else
				m=A1/A2;
			
			mT=1.0/3*(A1+A2)*L*(1+sqrt(m)/(1+m));

			A1=m_SectionTW.GetAt(i).m_WArea;
			A2=m_SectionTW.GetAt(i+1).m_WArea;
			if(A2<A1)
			{
				mA=A1;
				A1=A2;
				A2=mA;
			}
			
			if(A2<=0)
				m=0;
			else
				m=A1/A2;

			mW=1.0/3*(A1+A2)*L*(1+sqrt(m)/(1+m));
	
			m_totalarea_T+=mT;
			m_totalarea_W+=mW;
		}
	}
	
	
	
	tt.Format("%.3f",m_totalarea_T);
	*mareaT=atof(tt);	
	tt.Format("%.3f",m_totalarea_W);
	*mareaW=atof(tt);	
	
}

 
void CalCulateF::GetDMArea(int indexZH, float *mareaT, float *mareaW)
{
	double x1,double y1,double x2,double y2;
	double z1,z2;

	float area;
	
	int i,j,T;
	float m_area_W=0;
	float m_area_T=0;

	
	
	for(i=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->Huponums_L-1;i>=0;i--)
	{
		for(j=2;j>0;j--)
		{
			
			x1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->HuPo_L[i].Hp[j].x;
			z1=-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->HuPo_L[i].Hp[j].z;
			y1=m_demInsert.GetHeightValue(x1+theApp.m_DemLeftDown_x,z1+theApp.m_DemLeftDown_y,2);
		
			
			x2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->HuPo_L[i].Hp[j-1].x;
			z2=-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->HuPo_L[i].Hp[j-1].z;
			y2=m_demInsert.GetHeightValue(x2+theApp.m_DemLeftDown_x,z2+theApp.m_DemLeftDown_y,2);
			
			T=GetTXArea(x1,myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->HuPo_L[i].Hp[j].y,x1,y1,
				x2,myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->HuPo_L[i].Hp[j-1].y,x2,y2,&area);
			if(T==-1)
				m_area_W+=area;
			else if(T==1)
				m_area_T+=area;
			
		}
	}

	
	if( myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->bhaveSuiGou_L)
	{
		for(j=5;j>0;j--)
		{
			
			x1=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouL[j].x;
			z1=-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouL[j].z;
			y1=m_demInsert.GetHeightValue(x1+theApp.m_DemLeftDown_x,z1+theApp.m_DemLeftDown_y,2);
	
			
			x2=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouL[j-1].x;
			z2=-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouL[j-1].z;
			y2=m_demInsert.GetHeightValue(x2+theApp.m_DemLeftDown_x,z2+theApp.m_DemLeftDown_y,2);

			
			T=GetTXArea(x1,myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouL[j].y,x1,y1,
				x2,myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouL[j-1].y,x2,y2,&area);
			if(T==-1)
				m_area_W+=area;
			else if(T==1)
				m_area_T+=area;
			

		}
	}
	
	
	
	x1=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(indexZH)->x1;
	z1=-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(indexZH)->z1;
	y1=m_demInsert.GetHeightValue(x1+theApp.m_DemLeftDown_x,z1+theApp.m_DemLeftDown_y,2);

	
	x2=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(indexZH)->x1;
	z2=-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(indexZH)->z1;
	y2=m_demInsert.GetHeightValue(x2+theApp.m_DemLeftDown_x,z2+theApp.m_DemLeftDown_y,2);
	
	
	T=GetTXArea(x1,myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(indexZH)->y1,x1,y1,
		x2,myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(indexZH)->y1,x2,y2,&area);
	if(T==-1)
		m_area_W+=area;
	else if(T==1)
		m_area_T+=area;

	
	x1=x2;y1=y2;z1=z2;
	
	x2=myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(indexZH)->x1;
	z2=-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(indexZH)->z1;
	y2=m_demInsert.GetHeightValue(x2+theApp.m_DemLeftDown_x,z2+theApp.m_DemLeftDown_y,2);
	
	T=GetTXArea(x1,myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(indexZH)->y1,x1,y1,
		x2,myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(indexZH)->y1,x2,y2,&area);
	if(T==-1)
		m_area_W+=area;
	else if(T==1)
		m_area_T+=area;

	x1=x2;y1=y2;z1=z2;
	
	x2=myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(indexZH)->x2;
	z2=-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(indexZH)->z2;
	y2=m_demInsert.GetHeightValue(x2+theApp.m_DemLeftDown_x,z2+theApp.m_DemLeftDown_y,2);
	
	T=GetTXArea(x1,myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(indexZH)->y1,x1,y1,
		x2,myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(indexZH)->y2,x2,y2,&area);
	if(T==-1)
		m_area_W+=area;
	else if(T==1)
		m_area_T+=area;

	x1=x2;y1=y2;z1=z2;
	
	x2=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(indexZH)->x2;
	z2=-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(indexZH)->z2;
	y2=m_demInsert.GetHeightValue(x2+theApp.m_DemLeftDown_x,z2+theApp.m_DemLeftDown_y,2);
	
	T=GetTXArea(x1,myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(indexZH)->y2,x1,y1,
		x2,myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(indexZH)->y2,x2,y2,&area);
	if(T==-1)
		m_area_W+=area;
	else if(T==1)
		m_area_T+=area;


	x1=x2;y1=y2;z1=z2;
	
	x2=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(indexZH)->x2;
	z2=-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(indexZH)->z2;
	y2=m_demInsert.GetHeightValue(x2+theApp.m_DemLeftDown_x,z2+theApp.m_DemLeftDown_y,2);
	
	T=GetTXArea(x1,myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(indexZH)->y2,x1,y1,
		x2,myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(indexZH)->y2,x2,y2,&area);
	if(T==-1)
		m_area_W+=area;
	else if(T==1)
		m_area_T+=area;

	

	
	if( myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->bhaveSuiGou_R)
	{
		x1=x2;y1=y2;z1=z2;
		
		x2=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouR[0].x;
		z2=-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouR[0].z;
		y2=m_demInsert.GetHeightValue(x2+theApp.m_DemLeftDown_x,z2+theApp.m_DemLeftDown_y,2);
		
		
		T=GetTXArea(x1,myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(indexZH)->y2,x1,y1,
			x2,myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouR[0].y,x2,y2,&area);
		if(T==-1)
			m_area_W+=area;
		else if(T==1)
			m_area_T+=area;
	}
	
	
	if( myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->bhaveSuiGou_R)
	{
		for(j=0;j<5;j++)
		{
			
			x1=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouR[j].x;
			z1=-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouR[j].z;
			y1=m_demInsert.GetHeightValue(x1+theApp.m_DemLeftDown_x,z1+theApp.m_DemLeftDown_y,2);
			
			
			x2=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouR[j+1].x;
			z2=-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouR[j+1].z;
			y2=m_demInsert.GetHeightValue(x2+theApp.m_DemLeftDown_x,z2+theApp.m_DemLeftDown_y,2);
			
			
			T=GetTXArea(x1,myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouR[j].y,x1,y1,
				x2,myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(indexZH)->SuiGouR[j+1].y,x2,y2,&area);
			if(T==-1)
				m_area_W+=area;
			else if(T==1)
				m_area_T+=area;
			
			
		}
	}

	
	for(i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->Huponums_R;i++)
	{
		for(j=0;j<2;j++)
		{
			
			x1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->HuPo_R[i].Hp[j].x;
			z1=-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->HuPo_R[i].Hp[j].z;
			y1=m_demInsert.GetHeightValue(x1+theApp.m_DemLeftDown_x,z1+theApp.m_DemLeftDown_y,2);
			
			
			x2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->HuPo_R[i].Hp[j+1].x;
			z2=-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->HuPo_R[i].Hp[j+1].z;
			y2=m_demInsert.GetHeightValue(x2+theApp.m_DemLeftDown_x,z2+theApp.m_DemLeftDown_y,2);
			
			T=GetTXArea(x1,myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->HuPo_R[i].Hp[j].y,x1,y1,
				x2,myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(indexZH)->HuPo_R[i].Hp[j+1].y,x2,y2,&area);
			if(T==-1)
				m_area_W+=area;
			else if(T==1)
				m_area_T+=area;
			
		}
	}

	*mareaT=m_area_T;
	*mareaW=m_area_W;
	
}

 
int CalCulateF::GetTXArea(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, float *marea)
{
	double b1=fabs(y2-y1);
	double b2=fabs(y4-y3);
	double h=fabs(x4-x1);
	
	*marea=(b1+b2)*h/2.0;
	if(y2>y1 || y4>y3) 
		return -1;
	else if(y2<y1 || y4<y3) 
		return 1;
	else
		return 0;
}

/*  
�P�_����u�q�O�_�ۥ�(�����I)  
*/  
bool CalCulateF::IsLineSegmentCross(Point pFirst1, Point pFirst2, Point pSecond1, Point pSecond2)
{
    //�C�ӽu�q�����I���b�t�@�ӽu�q�����k���P���A�h���_�w�u�q�ۥ�   
    //�������V�q(x1,y1)->(x2,y2),�P�_�I(x3,y3)�b�V�q������,�k��,�٬O�u�W.   
    //p=x1(y3-y2)+x2(y1-y3)+x3(y2-y1).p<0 ����,    p=0 �u�W, p>0 �k��   
    long Linep1,Linep2;   
    //�P�_pSecond1�MpSecond2�O�_�bpFirst1->pFirst2�ⰼ   
    Linep1 = pFirst1.x * (pSecond1.y - pFirst2.y) +   
        pFirst2.x * (pFirst1.y - pSecond1.y) +   
        pSecond1.x * (pFirst2.y - pFirst1.y);   
    Linep2 = pFirst1.x * (pSecond2.y - pFirst2.y) +   
        pFirst2.x * (pFirst1.y - pSecond2.y) +   
        pSecond2.x * (pFirst2.y - pFirst1.y);   
    if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1==0 && Linep2==0))//�Ÿ��첧�ά�0:pSecond1�MpSecond2�bpFirst1->pFirst2�P��   
    {   
        return false;   
    }   
    //�P�_pFirst1�MpFirst2�O�_�bpSecond1->pSecond2�ⰼ   
    Linep1 = pSecond1.x * (pFirst1.y - pSecond2.y) +   
        pSecond2.x * (pSecond1.y - pFirst1.y) +   
        pFirst1.x * (pSecond2.y - pSecond1.y);   
    Linep2 = pSecond1.x * (pFirst2.y - pSecond2.y) +   
        pSecond2.x * (pSecond1.y - pFirst2.y) +   
        pFirst2.x * (pSecond2.y - pSecond1.y);   
    if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1==0 && Linep2==0))//�Ÿ��첧�ά�0:pFirst1�MpFirst2�bpSecond1->pSecond2�P��   
    {   
        return false;   
    }   
    //�_�h�P���ۥ�   
    return true;   
	
}

Point CalCulateF::GetCrossPoint(Point p1, Point p2, Point q1, Point q2,bool *bCross)
{
    //�����ۥ�D�X���~�O�u�q�����I�A���O�U�����{�Ǭq�O�q�Ϊ�   
  //  ASSERT(IsLineSegmentCross(p1,p2,q1,q2)==true);   
	Point crossPoint;   

	if(IsLineSegmentCross(p1,p2,q1,q2)!=true)
	{
		*bCross=false;
		return crossPoint;
	}
    /*�ھڨ��I���Ƭ��зǦ��A�i�ӨD�u�ʤ�{��*/  
   
    long tempLeft,tempRight;   
   
	//�Dx����   
    tempLeft = (q2.x - q1.x) * (p1.y - p2.y) - (p2.x - p1.x) * (q1.y - q2.y);   
    tempRight = (p1.y - q1.y) * (p2.x - p1.x) * (q2.x - q1.x) + q1.x * (q2.y - q1.y) * (p2.x - p1.x) - p1.x * (p2.y - p1.y) * (q2.x - q1.x);   
    crossPoint.x =(double)tempRight / (double)tempLeft;   
   
	//�Dy����     
    tempLeft = (p1.x - p2.x) * (q2.y - q1.y) - (p2.y - p1.y) * (q1.x - q2.x);   
    tempRight = p2.y * (p1.x - p2.x) * (q2.y - q1.y) + (q2.x- p2.x) * (q2.y - q1.y) * (p1.y - p2.y) - q2.y * (q1.x - q2.x) * (p2.y - p1.y);   
    crossPoint.y =(double)tempRight / (double)tempLeft ;   
    
	*bCross=true;
	return crossPoint;   
	
}

//�D���u�q�P�h��Ϊ����I,�p�G��,��^�Ҧ����I
bool CalCulateF::GetLinePolygonJD(Point polygon[], int n, Point p1, Point P2, Point *pts,int *m_JdNums)
{
	//�p�G�h��εJ�I<=1,��^
	if(n<=1)
		return false;

	bool bCross;

	 Point q1, q2;
	 Point crossPoint; 

	 int Jdnums=0; //���I�`��

	 pts=new Point[n];

	 //�̦��q�h��Τ��������{���I�զ����u�q,�P�J�����u�i����I�p�⦨���P�_
	 
	 for(int i=0;i<n-1;i++)
	 {
		 q1.x =polygon[i].x;
		 q1.y =polygon[i].y;
		 q2.x =polygon[i+1].x;
		 q2.y =polygon[i+1].y;
		 crossPoint =GetCrossPoint(p1,P2,q1,q2,&bCross);
		if(bCross==true) //�p�G�����I
		{
			//�s�x���I����
			pts[Jdnums].x=crossPoint.x;
			pts[Jdnums].y=crossPoint.y;
			Jdnums++;//���I��+1
		}

	 }
	 
	 *m_JdNums=Jdnums;
	return true;	
}

//�p���I�쪽�u���Z��
double CalCulateF::GetPointToLineDistence(double ptx, double pty, double Linex1, double Liney1, double Linex2, double Liney2)
{
	double Dis;
	double d1=Linex2-Linex1;
	double d2=Liney2-Liney1;
	if(d1==0)	
	{
		Dis=fabs(ptx-Linex1);
		return Dis;
	}
	if(d2==0)	
	{
		Dis=fabs(pty-Liney1);
		return Dis;
	}
	float a=d2,b=-d1,c=d1*Liney1-d2*Linex1;
	Dis=fabs(a*ptx+b*pty+c)/sqrt(a*a+b*b);
    return Dis;
}

double CalCulateF::MinValueXY(double x1, double x2)
{
	if(x1<=x2)
		return x1;
	else
		return x2;
}

double CalCulateF::MaxValueXY(double x1, double x2)
{
	if(x1>=x2)
		return x1;
	else
		return x2;
}

//�o��x , y , z���Ф����̤j��
double CalCulateF::maxValueXYZ(double dx ,  double dy ,  double dz)
{
	double dd=dx;
	if(dd<dy) dd=dy;
	if(dd<dz) dd=dz;
	return dd;
}