// DesingScheme.cpp: implementation of the CDesingScheme class.
 
 

#include "stdafx.h"
#include "DesingScheme.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 
// Construction/Destruction
 
#define PAI 3.1415926

CDesingScheme::CDesingScheme()
{
	InitMinR();
}

CDesingScheme::~CDesingScheme()
{

}

void CDesingScheme::InitMinR()
{

	
	m_minR160_L0[0][0]=40;m_minR160_L0[0][1]=40;
	m_minR160_L0[1][0]=50;m_minR160_L0[1][1]=40;
	m_minR160_L0[2][0]=60;m_minR160_L0[2][1]=50;
	m_minR160_L0[3][0]=70;m_minR160_L0[3][1]=50;
	m_minR160_L0[4][0]=70;m_minR160_L0[4][1]=50;
	m_minR160_L0[5][0]=70;m_minR160_L0[5][1]=60;
	m_minR160_L0[6][0]=70;m_minR160_L0[6][1]=60;
	m_minR160_L0[7][0]=80;m_minR160_L0[7][1]=70;
	m_minR160_L0[8][0]=90;m_minR160_L0[8][1]=70;
	m_minR160_L0[9][0]=90;m_minR160_L0[9][1]=80;
	m_minR160_L0[10][0]=100;m_minR160_L0[10][1]=90;
	m_minR160_L0[11][0]=110;m_minR160_L0[11][1]=100;
	m_minR160_L0[12][0]=140;m_minR160_L0[12][1]=120;
	m_minR160_L0[13][0]=160;m_minR160_L0[13][1]=140;
	m_minR160_L0[14][0]=170;m_minR160_L0[14][1]=160;

	
	m_minR140_L0[0][0]=20;m_minR140_L0[0][1]=20;
	m_minR140_L0[1][0]=30;m_minR140_L0[1][1]=20;
	m_minR140_L0[2][0]=40;m_minR140_L0[2][1]=20;
	m_minR140_L0[3][0]=50;m_minR140_L0[3][1]=30;
	m_minR140_L0[4][0]=50;m_minR140_L0[4][1]=30;
	m_minR140_L0[5][0]=60;m_minR140_L0[5][1]=40;
	m_minR140_L0[6][0]=60;m_minR140_L0[6][1]=40;
	m_minR140_L0[7][0]=60;m_minR140_L0[7][1]=40;
	m_minR140_L0[8][0]=70;m_minR140_L0[8][1]=50;
	m_minR140_L0[9][0]=70;m_minR140_L0[9][1]=50;
	m_minR140_L0[10][0]=80;m_minR140_L0[10][1]=60;
	m_minR140_L0[11][0]=80;m_minR140_L0[11][1]=70;
	m_minR140_L0[12][0]=90;m_minR140_L0[12][1]=80;
	m_minR140_L0[13][0]=100;m_minR140_L0[13][1]=80;
	m_minR140_L0[14][0]=110;m_minR140_L0[14][1]=100;
	m_minR140_L0[15][0]=130;m_minR140_L0[15][1]=110;
	m_minR140_L0[16][0]=150;m_minR140_L0[16][1]=130;

	
	m_minR120_L0[0][0]=20;m_minR120_L0[0][1]=20;
	m_minR120_L0[1][0]=20;m_minR120_L0[1][1]=20;
	m_minR120_L0[2][0]=30;m_minR120_L0[2][1]=20;
	m_minR120_L0[3][0]=30;m_minR120_L0[3][1]=20;
	m_minR120_L0[4][0]=30;m_minR120_L0[4][1]=20;
	m_minR120_L0[5][0]=40;m_minR120_L0[5][1]=30;
	m_minR120_L0[6][0]=40;m_minR120_L0[6][1]=30;
	m_minR120_L0[7][0]=50;m_minR120_L0[7][1]=30;
	m_minR120_L0[8][0]=50;m_minR120_L0[8][1]=40;
	m_minR120_L0[9][0]=50;m_minR120_L0[9][1]=40;
	m_minR120_L0[10][0]=50;m_minR120_L0[10][1]=40;
	m_minR120_L0[11][0]=60;m_minR120_L0[11][1]=40;
	m_minR120_L0[12][0]=60;m_minR120_L0[12][1]=50;
	m_minR120_L0[13][0]=70;m_minR120_L0[13][1]=60;
	m_minR120_L0[14][0]=70;m_minR120_L0[14][1]=60;
	m_minR120_L0[15][0]=80;m_minR120_L0[15][1]=70;
	m_minR120_L0[16][0]=90;m_minR120_L0[16][1]=80;
	m_minR120_L0[17][0]=120;m_minR120_L0[17][1]=100;
	m_minR120_L0[18][0]=150;m_minR120_L0[18][1]=130;

	
	m_minR100_L0[0][0]=20;m_minR100_L0[0][1]=20;
	m_minR100_L0[1][0]=20;m_minR100_L0[1][1]=20;
	m_minR100_L0[2][0]=20;m_minR100_L0[2][1]=20;
	m_minR100_L0[3][0]=20;m_minR100_L0[3][1]=20;
	m_minR100_L0[4][0]=20;m_minR100_L0[4][1]=20;
	m_minR100_L0[5][0]=20;m_minR100_L0[5][1]=20;
	m_minR100_L0[6][0]=30;m_minR100_L0[6][1]=20;
	m_minR100_L0[7][0]=30;m_minR100_L0[7][1]=20;
	m_minR100_L0[8][0]=40;m_minR100_L0[8][1]=20;
	m_minR100_L0[9][0]=40;m_minR100_L0[9][1]=20;
	m_minR100_L0[10][0]=40;m_minR100_L0[10][1]=30;
	m_minR100_L0[11][0]=40;m_minR100_L0[11][1]=30;
	m_minR100_L0[12][0]=50;m_minR100_L0[12][1]=40;
	m_minR100_L0[13][0]=50;m_minR100_L0[13][1]=40;
	m_minR100_L0[14][0]=50;m_minR100_L0[14][1]=40;
	m_minR100_L0[15][0]=60;m_minR100_L0[15][1]=40;
	m_minR100_L0[16][0]=60;m_minR100_L0[16][1]=50;
	m_minR100_L0[17][0]=70;m_minR100_L0[17][1]=60;
	m_minR100_L0[18][0]=80;m_minR100_L0[18][1]=70;
	m_minR100_L0[19][0]=100;m_minR100_L0[19][1]=90;
	m_minR100_L0[20][0]=120;m_minR100_L0[20][1]=100;
	m_minR100_L0[21][0]=130;m_minR100_L0[21][1]=110;
	
	
	m_minR80_L0[0][0]=20;m_minR80_L0[0][1]=20;
	m_minR80_L0[1][0]=20;m_minR80_L0[1][1]=20;
	m_minR80_L0[2][0]=20;m_minR80_L0[2][1]=20;
	m_minR80_L0[3][0]=20;m_minR80_L0[3][1]=20;
	m_minR80_L0[4][0]=20;m_minR80_L0[4][1]=20;
	m_minR80_L0[5][0]=20;m_minR80_L0[5][1]=20;
	m_minR80_L0[6][0]=20;m_minR80_L0[6][1]=20;
	m_minR80_L0[7][0]=20;m_minR80_L0[7][1]=20;
	m_minR80_L0[8][0]=20;m_minR80_L0[8][1]=20;
	m_minR80_L0[9][0]=20;m_minR80_L0[9][1]=20;
	m_minR80_L0[10][0]=20;m_minR80_L0[10][1]=20;
	m_minR80_L0[11][0]=30;m_minR80_L0[11][1]=20;
	m_minR80_L0[12][0]=30;m_minR80_L0[12][1]=20;
	m_minR80_L0[13][0]=30;m_minR80_L0[13][1]=20;
	m_minR80_L0[14][0]=40;m_minR80_L0[14][1]=20;
	m_minR80_L0[15][0]=40;m_minR80_L0[15][1]=20;
	m_minR80_L0[16][0]=40;m_minR80_L0[16][1]=30;
	m_minR80_L0[17][0]=40;m_minR80_L0[17][1]=30;
	m_minR80_L0[18][0]=50;m_minR80_L0[18][1]=40;
	m_minR80_L0[19][0]=50;m_minR80_L0[19][1]=40;
	m_minR80_L0[20][0]=60;m_minR80_L0[20][1]=50;
	m_minR80_L0[21][0]=60;m_minR80_L0[21][1]=50;
	m_minR80_L0[22][0]=60;m_minR80_L0[22][1]=60;
	
	
	m_minPriorityR160_L0[0]=40;	
	m_minPriorityR160_L0[1]=50;	
	m_minPriorityR160_L0[2]=60;	
	m_minPriorityR160_L0[3]=70;	
	m_minPriorityR160_L0[4]=70;	
	m_minPriorityR160_L0[5]=70;	
	m_minPriorityR160_L0[6]=70;	
	m_minPriorityR160_L0[7]=80;	
	m_minPriorityR160_L0[8]=90;	
	m_minPriorityR160_L0[9]=100;
	m_minPriorityR160_L0[10]=110;
	m_minPriorityR160_L0[11]=120;
	m_minPriorityR160_L0[12]=150;
	m_minPriorityR160_L0[13]=170;
	m_minPriorityR160_L0[14]=190;
	
	
	m_minPriorityR140_L0[0]=40;	
	m_minPriorityR140_L0[1]=40;	
	m_minPriorityR140_L0[2]=40;	
	m_minPriorityR140_L0[3]=50;	
	m_minPriorityR140_L0[4]=50;	
	m_minPriorityR140_L0[5]=60;	
	m_minPriorityR140_L0[6]=60;	
	m_minPriorityR140_L0[7]=60;	
	m_minPriorityR140_L0[8]=70;	
	m_minPriorityR140_L0[9]=80;
	m_minPriorityR140_L0[10]=90;
	m_minPriorityR140_L0[11]=90;
	m_minPriorityR140_L0[12]=100;
	m_minPriorityR140_L0[13]=120;
	m_minPriorityR140_L0[14]=130;
	m_minPriorityR140_L0[15]=150;
	m_minPriorityR140_L0[16]=190;

	
	m_minPriorityR120_L0[0]=40;	
	m_minPriorityR120_L0[1]=40;	
	m_minPriorityR120_L0[2]=40;	
	m_minPriorityR120_L0[3]=40;	
	m_minPriorityR120_L0[4]=40;	
	m_minPriorityR120_L0[5]=40;	
	m_minPriorityR120_L0[6]=40;	
	m_minPriorityR120_L0[7]=50;	
	m_minPriorityR120_L0[8]=50;	
	m_minPriorityR120_L0[9]=50;
	m_minPriorityR120_L0[10]=60;
	m_minPriorityR120_L0[11]=60;
	m_minPriorityR120_L0[12]=70;
	m_minPriorityR120_L0[13]=80;
	m_minPriorityR120_L0[14]=90;
	m_minPriorityR120_L0[15]=100;
	m_minPriorityR120_L0[16]=120;
	m_minPriorityR120_L0[17]=140;
	m_minPriorityR120_L0[18]=180;
	
}


 //�O�s���
void CDesingScheme::SavePlaneCurveData()
{

	CString tt;
	PLineCurve pTempCurveElements;
	
	double m_startLC=SchemeDatass[m_currentSchemeIndexs].StartLC; //�_�I���{
    	
	if(PtS_JD.GetSize()>1) //�p�G�]�p���I�Ƥj��1
	{
		//�p���1�ӥ��I"JD0"�����u�n��
		pTempCurveElements=JDCurveElementss[m_currentSchemeIndexs].GetAt(0);
		pTempCurveElements->ZH=pTempCurveElements->HZ=m_startLC; //�w���I���{ ���w�I���{
		pTempCurveElements->HY=pTempCurveElements->YH=m_startLC;
		pTempCurveElements->Alfa=pTempCurveElements->T=pTempCurveElements->L=0;
		pTempCurveElements->R=pTempCurveElements->RoateStyle=pTempCurveElements->E=0;
		pTempCurveElements->P=pTempCurveElements->L0=pTempCurveElements->Ly=pTempCurveElements->Jzxc=0;
		pTempCurveElements->JDLC=m_startLC; //���I���{
		pTempCurveElements->ID="JD0"; //���IID��
		pTempCurveElements->x=PtS_JD.GetAt(0)->x;//���Ix����
		pTempCurveElements->y=-PtS_JD.GetAt(0)->z;//���Iy����
		pTempCurveElements->z=PtS_JD.GetAt(0)->y;//���Iz����
		pTempCurveElements->Cneterx=pTempCurveElements->x;//���u���x����
		pTempCurveElements->Cnetery=pTempCurveElements->y;//���u���y����
		
		pTempCurveElements->ZH_xy=new  Cordinate;		 //���w�I����
		pTempCurveElements->ZH_xy->x=pTempCurveElements->x;
		pTempCurveElements->ZH_xy->y=pTempCurveElements->y;

		pTempCurveElements->HY_xy=new  Cordinate;		//�w���I����
		pTempCurveElements->HY_xy->x=pTempCurveElements->x;
		pTempCurveElements->HY_xy->y=pTempCurveElements->y;
		
		pTempCurveElements->YH_xy=new  Cordinate;		
		pTempCurveElements->YH_xy->x=pTempCurveElements->x;//��w�I����
		pTempCurveElements->YH_xy->y=pTempCurveElements->y;

		pTempCurveElements->HZ_xy=new  Cordinate;		
		pTempCurveElements->HZ_xy->x=pTempCurveElements->x;//�w���I����
		pTempCurveElements->HZ_xy->y=pTempCurveElements->y;
 
		//�p��̫�@�ӥ��IJDN�����u�n��
		pTempCurveElements=JDCurveElementss[m_currentSchemeIndexs].GetAt(PtS_JD.GetSize()-1);
		pTempCurveElements->Alfa=pTempCurveElements->T=pTempCurveElements->L=0; //���I�ਤ
 
		pTempCurveElements->RoateStyle=pTempCurveElements->E=0; //�~�ڶZ
 
		pTempCurveElements->Ly=pTempCurveElements->Jzxc=0; //�����u
		pTempCurveElements->Dist=pTempCurveElements->fwj=0; //���I����
 
		pTempCurveElements->x=PtS_JD.GetAt(PtS_JD.GetSize()-1)->x;//���Ix����
		pTempCurveElements->y=-PtS_JD.GetAt(PtS_JD.GetSize()-1)->z;//���Iy����
		pTempCurveElements->z=PtS_JD.GetAt(PtS_JD.GetSize()-1)->y;//���Iz����
		pTempCurveElements->Cneterx=pTempCurveElements->x; //���u���x����
		pTempCurveElements->Cnetery=pTempCurveElements->y;//���u���y����
		
		pTempCurveElements->ZH_xy=new  Cordinate;		//���w�I����
		pTempCurveElements->ZH_xy->x=pTempCurveElements->x;
		pTempCurveElements->ZH_xy->y=pTempCurveElements->y;
		
		pTempCurveElements->HY_xy=new  Cordinate;		//�w���I����
		pTempCurveElements->HY_xy->x=pTempCurveElements->x;
		pTempCurveElements->HY_xy->y=pTempCurveElements->y;
		
		pTempCurveElements->YH_xy=new  Cordinate;		//��w�I����
		pTempCurveElements->YH_xy->x=pTempCurveElements->x;
		pTempCurveElements->YH_xy->y=pTempCurveElements->y;
		
		pTempCurveElements->HZ_xy=new  Cordinate;		//�w���I����
		pTempCurveElements->HZ_xy->x=pTempCurveElements->x;
		pTempCurveElements->HZ_xy->y=pTempCurveElements->y;
		
 
		float dertE,dertN;
		float fwj,fwj2;
		
		long i;

		/*
		N
		|
		|
		|
		|
		|____________ E
		
		*/
		//�p����IJD1�P���IJDN�������I�����u�n��
		
		for(i=0;i<PtS_JD.GetSize()-1;i++)
		{
			dertE=PtS_JD.GetAt(i+1)->x-PtS_JD.GetAt(i)->x;
			dertN=(-PtS_JD.GetAt(i+1)->z)-(-PtS_JD.GetAt(i)->z);
			if( dertE>=0 && dertN>0)				//1�H��	
				fwj=atan(fabs(dertE/dertN));		//��쨤	
			else if(dertE>=0 && dertN<0)			//2�H��
				fwj=PAI-atan(fabs(dertE/dertN));	//��쨤	
			else if(dertE<0 && dertN<0)				//3�H��
				fwj=PAI+atan(fabs(dertE/dertN));	//��쨤	
			else if(dertE<0 && dertN>0)				//4�H��
				fwj=2*PAI-atan(fabs(dertE/dertN));
			else if(dertE>0 && dertN==0)	
				fwj=PAI/2.0;						//��쨤	
			else if(dertE<0 && dertN==0)		
				fwj=3*PAI/2.0;						//��쨤	
 
 
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->fwj=fwj;//��쨤	
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->Dist=sqrt(dertE*dertE+dertN*dertN);//���I�Z��	

			if( dertN>=0 && dertE>0)				//1�H��	
				fwj2=atan(fabs(dertN/dertE));		//��쨤2	
			else if(dertN>=0 && dertE<0)			//2�H��
			{
				fwj2=PAI-atan(fabs(dertN/dertE));	//��쨤2	
			}
			else if(dertN<0 && dertE<0)				//3�H��
				fwj2=PAI+atan(fabs(dertN/dertE));	//��쨤2	
			else if(dertN<0 && dertE>0)				//4�H��
				fwj2=2*PAI-atan(fabs(dertN/dertE));	//��쨤2	
			else if(dertN>0 && dertE==0)		
				fwj2=PAI/2.0;						//��쨤2	
			else if(dertN<0 && dertE==0)		
				fwj2=3*PAI/2.0;						//��쨤2	
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->fwj2=fwj2;

		}
		
        //�̫�@�ӥ��I����쨤2=0
		JDCurveElementss[m_currentSchemeIndexs].GetAt(PtS_JD.GetSize()-1)->fwj2=0;
		
		for(i=0;i<PtS_JD.GetSize()-2;i++)
		{			
			//���u�ਤ
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->fwj-JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->fwj;
			
			if(fabs(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa)>PAI)
			{
				if(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa<0)
					JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa=fabs(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa)-PAI;
			}
		
			if(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa>0)
				JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->RoateStyle=1;
			else if(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa<0)
				JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->RoateStyle=-1;
			
			
			if(PtS_JD.GetAt(i+1)->x-PtS_JD.GetAt(i)->x>0)
			{
				if(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa<0)
					JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa=-JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa;
			}

		
			float ftan=tan(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa/2.0);
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->T=\
				(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->R+\
				JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->P)*\
				tan(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa/2.0)+\
				JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->L0/2.0;
			
			
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->L=fabs(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa*JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->R)+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->L0;
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->ZH=JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->Dist-JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->T-JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->T+JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HZ;
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HZ=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->ZH+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->L;
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HY=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->ZH+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->L0;
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->YH=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HZ-JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->L0;		
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Ly=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->YH-JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HY;
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->JDLC=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->ZH+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->T;
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->E=(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->R+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->P)/cos(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa/2.0)-JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->R;
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->x=PtS_JD.GetAt(i+1)->x;
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->y=-PtS_JD.GetAt(i+1)->z;
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->z=PtS_JD.GetAt(i+1)->y;
			float distence=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->ZH-JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->JDLC;
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->ZH_xy=new  Cordinate;		
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->ZH_xy->x=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->x-JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->T*cos(JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->fwj2);
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->ZH_xy->y=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->y-JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->T*sin(JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->fwj2);
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HZ_xy=new  Cordinate;		
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HZ_xy->x=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->x+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->T*cos(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->fwj2);
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HZ_xy->y=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->y+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->T*sin(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->fwj2);
	
			double ptx,pty;
			float LL;
			float L0=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->L0;
			long R=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->R;
			LL=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HY-JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->ZH;
			ptx=LL-LL*LL*LL*LL*LL/(40.0*R*R*L0*L0)+LL*LL*LL*LL*LL*LL*LL*LL*LL/(3456.0*R*R*R*R*L0*L0*L0*L0);
			pty=LL*LL*LL/(6.0*R*L0)*(1-LL*LL*LL*LL/(56.0*R*R*L0*L0)+LL*LL*LL*LL*LL*LL*LL*LL/(7040.0*R*R*R*R*L0*L0*L0*L0));
			
			float xita=PAI/2.0-JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->fwj;
			double xc,yc;
			if(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->RoateStyle==-1)	//����
			{
				xc=cos(xita)*ptx-sin(xita)*pty+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->ZH_xy->x;
				yc=sin(xita)*ptx+cos(xita)*pty+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->ZH_xy->y;
			}
			else if(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->RoateStyle==1)	//�k��
			{
				xc=cos(xita)*ptx+sin(xita)*pty+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->ZH_xy->x;
				yc=sin(xita)*ptx-cos(xita)*pty+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->ZH_xy->y;
			}

			//�w���I����
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HY_xy=new  Cordinate;		
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HY_xy->x=xc;//�w��x����
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HY_xy->y=yc;//�w��y����
			
			
			xita=3*PAI/2.0-JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->fwj;
			if(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->RoateStyle==-1)	
			{
				xc=cos(xita)*ptx+sin(xita)*pty+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HZ_xy->x;
				yc=sin(xita)*ptx-cos(xita)*pty+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HZ_xy->y;
			}
			else if(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->RoateStyle==1)	
			{
				xc=cos(xita)*ptx-sin(xita)*pty+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HZ_xy->x;
				yc=sin(xita)*ptx+cos(xita)*pty+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HZ_xy->y;
			}

			//��w�I����
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->YH_xy=new  Cordinate;		
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->YH_xy->x=xc;//��wx����
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->YH_xy->y=yc;//��wy����
   
			double dx,dy;
			dx=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->YH_xy->x-JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HY_xy->x;
			dy=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->YH_xy->y-JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HY_xy->y;
			float rAngle=atan(dy/dx);
			float peiAngle=(PAI-fabs(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Alfa)+L0*1.0/JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->R)/2.0;
			float thetaAngle;
			double centerx,centery;

			if(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->RoateStyle==-1)	
			{
				if(dx>0)
				{
					thetaAngle=peiAngle+rAngle;
				}
				else if(dx<0)
				{
					thetaAngle=peiAngle+rAngle+PAI;
				}
				centerx=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HY_xy->x+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->R*cos(thetaAngle);
				centery=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HY_xy->y+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->R*sin(thetaAngle);			
			}
			else if(JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->RoateStyle==1)	
			{
				
				if(dx>0)
				{
					thetaAngle=peiAngle-rAngle;
				}
				else if(dx<0)
				{
					thetaAngle=peiAngle-rAngle+PAI;
				}
				centerx=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HY_xy->x+JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->R*cos(thetaAngle);
				centery=JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->HY_xy->y-JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->R*sin(thetaAngle);			

			}
			//���u���x,y����
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Cneterx=centerx;
			JDCurveElementss[m_currentSchemeIndexs].GetAt(i+1)->Cnetery=centery;
		}
			
		
		
		PLineCurve pPreCurveElements=JDCurveElementss[m_currentSchemeIndexs].GetAt(PtS_JD.GetSize()-2);
		pTempCurveElements =JDCurveElementss[m_currentSchemeIndexs].GetAt(PtS_JD.GetSize()-1);
		double x1=pPreCurveElements->HZ_xy->x;
		double y1=pPreCurveElements->HZ_xy->y;
		double x2=pTempCurveElements->x;
		double y2=pTempCurveElements->y;
		double dist=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
		double mlc=pPreCurveElements->HZ+dist;
		pTempCurveElements->ZH=pTempCurveElements->HZ=mlc;
		pTempCurveElements->HY=pTempCurveElements->YH=mlc;
		pTempCurveElements->JDLC=mlc;
		pTempCurveElements->L=0;
		pTempCurveElements->T=0;
		double m_EndLC=mlc;
		pTempCurveElements->fwj=0;
		pTempCurveElements->fwj2=0;
}

	
	SavePlaneCurveDataToDB(); //�O�s���u�n����ƾڮw��
	
    Save3DlineZX();//�b���I�������I�ëO�s��ƾڮw�M�Ʋդ�,�ѵ{�ǽե�
	
	::MessageBox(NULL,"��׫O�s���\","�O�s�]�p���!",MB_ICONINFORMATION);
	
}

//���{�榡�ഫ 
CString CDesingScheme::GetLC(double LC)
{
	CString tt,tt1,tt2;
	
	if(LC==0) //�p�G���{==0
	{
		tt.Format("K%d+%.3f",0,0); //���{�榡�ഫ
		return tt;		
	}
	
	int L1=int(LC/1000.0); //���{�㤽����
	float L2=LC-L1*1000;//�Ѿl�̼�
	
	if(L2>99) //�p�G�Ѿl�̼Ƥj��99�]��ܬO3��ơ^
	{
		tt2.Format("%.3f",L2);//�Ѿl�̼Ʈ榡�ഫ
	}
	else if(L2>9)//�p�G�Ѿl�̼Ƥj��9�]��ܬO2��ơ^
	{
		tt2.Format("0%.3f",L2);//�Ѿl�̼Ʈ榡�ഫ
	}
	else //�p�G�Ѿl�̼ƬO1���
	{
		tt2.Format("00%.3f",L2);//�Ѿl�̼Ʈ榡�ഫ
	}
	tt1.Format("K%d+",L1);//���{�㤽���Ʈ榡�ഫ
	tt=tt1+tt2; //���騽�{�榡�ഫ
	return tt; //��^�ഫ�ᨽ�{�r�Ŧ�
}

 //�O�s���u�n����ƾڮw��
void CDesingScheme::SavePlaneCurveDataToDB()
{
	CString tt;

	m_pRecordset.CreateInstance("ADODB.Recordset");   
	tt.Format("DELETE FROM  Scheme_plane_CureveData WHERE ��צW��='%s'",SchemeDatass[m_currentSchemeIndexs].Schemename);
	
	hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 
	if(!SUCCEEDED(hr))
	{
		AfxMessageBox("�R���ƾڥ���!",MB_ICONINFORMATION);
		return;
	}
	
	tt.Format("DELETE FROM  Scheme_plane_CureveData_XY WHERE ��צW��='%s'",SchemeDatass[m_currentSchemeIndexs].Schemename);
	hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 
	if(!SUCCEEDED(hr))
	{
		AfxMessageBox("�R���ƾڥ���!",MB_ICONINFORMATION);
		return;
	}

	for(long i=0;i<JDCurveElementss[m_currentSchemeIndexs].GetSize();i++)
	{
	tt.Format("INSERT INTO Scheme_plane_CureveData VALUES(\
	'%s','%s',%.3f,%.3f,%.3f,\
	%d,%d,%.3f,%.3f,%.3f,%.3f,\
	%.3f,%.3f,%.3f,\
	%.3f,%.3f,%d,\
	%.3f,%.3f,%.3f,%.3f,%d)",\
	SchemeDatass[m_currentSchemeIndexs].Schemename,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ID,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->Alfa,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->fwj,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->fwj2,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->RoateStyle,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->L0,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->T,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->L,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->Ly,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HY,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->YH,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HZ,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->E,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->P,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->R,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->JDLC,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->x,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->y,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->z,
	i+1							
	);

	try
	{
		hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 
		if(!SUCCEEDED(hr))
		{
			AfxMessageBox("��׫O�s����!",MB_ICONINFORMATION);
			return;
		}
	}
	
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("���~�H��:%s",e.ErrorMessage());
		AfxMessageBox(errormessage,MB_ICONINFORMATION);
		return;
	} 
	tt.Format("INSERT INTO Scheme_plane_CureveData_XY VALUES(\
	'%s','%s',\
	%.3f,%.3f,\
	%.3f,%.3f,%.3f,%.3f,\
	%.3f,%.3f,%.3f,%.3f,%d)",\
	SchemeDatass[m_currentSchemeIndexs].Schemename,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ID,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->Cneterx,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->Cnetery,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH_xy->x,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH_xy->y,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HY_xy->x,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HY_xy->y,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->YH_xy->x,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->YH_xy->y,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HZ_xy->x,
	JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HZ_xy->y,
	i+1								
	);
	try
	{
		hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 
		if(!SUCCEEDED(hr))
		{
			AfxMessageBox("��׫O�s����!",MB_ICONINFORMATION);
			return;
		}
	}
	
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("���~�H��:%s",e.ErrorMessage());
		AfxMessageBox(errormessage,MB_ICONINFORMATION);
		return;
	} 
	
	}
	
//	::MessageBox(NULL,"��׫O�s���\","�O�s�]�p���!",MB_ICONINFORMATION);
}


 
int CDesingScheme::GetMinL0(int mRindex)
{
	int m_minL0;
	switch(	SchemeDatass[m_currentSchemeIndexs].designspeed)
	{
	case 160:
		if(SchemeDatass[m_currentSchemeIndexs].strEngineeringcondition=="�@��a�q")
			m_minL0=m_minR160_L0[14-mRindex][0];
		else
			m_minL0=m_minR160_L0[14-mRindex][1];
		break;
	case 140:
		if(SchemeDatass[m_currentSchemeIndexs].strEngineeringcondition=="�@��a�q")
			m_minL0=m_minR140_L0[16-mRindex][0];
		else
			m_minL0=m_minR140_L0[16-mRindex][1];
		break;
	case 120:
		if(SchemeDatass[m_currentSchemeIndexs].strEngineeringcondition=="�@��a�q")
			m_minL0=m_minR120_L0[18-mRindex][0];
		else
			m_minL0=m_minR120_L0[18-mRindex][1];
		break;
	case 100:
		if(SchemeDatass[m_currentSchemeIndexs].strEngineeringcondition=="�@��a�q")
			m_minL0=m_minR100_L0[21-mRindex][0];
		else
			m_minL0=m_minR100_L0[21-mRindex][1];
		break;
	case 80:
		if(SchemeDatass[m_currentSchemeIndexs].strEngineeringcondition=="�@��a�q")
			m_minL0=m_minR80_L0[22-mRindex][0];
		else
			m_minL0=m_minR80_L0[22-mRindex][1];
		break;
	}
	
	return m_minL0;

}

 
int CDesingScheme::GetMinRfromCriterion(int mspeed, int EngineeringConditionStyle)
{

	int mcriterionMinR;

    switch(mspeed)
	{
	case 160:
		if(EngineeringConditionStyle==0) 
			mcriterionMinR=2000;	
		else
			mcriterionMinR=1600;	
		break;
	case 140:
		if(EngineeringConditionStyle==0) 
			mcriterionMinR=1600;	
		else
			mcriterionMinR=1200;	
		break;
	case 120:
		if(EngineeringConditionStyle==0) 
			mcriterionMinR=1200;	
		else
			mcriterionMinR=800;	
		break;
	case 100:
		if(EngineeringConditionStyle==0) 
			mcriterionMinR=800;	
		else
			mcriterionMinR=600;	
		break;
		
	case 80:
		if(EngineeringConditionStyle==0) 
			mcriterionMinR=600;	
		else
			mcriterionMinR=500;	
		break;
	}
	
	return mcriterionMinR;
}

 
void CDesingScheme::LoadData(CString strSchemeName)
{
	
	_RecordsetPtr   m_pRecordset;
	_variant_t Thevalue;  
	variant_t RecordsAffected;
	m_pRecordset.CreateInstance("ADODB.Recordset");   
	
	CString strSql;
	strSql.Format("Select *   from  Scheme WHERE ��צW�� ='%s'",strSchemeName);  
	try
	{
		m_pRecordset->Open((_bstr_t)strSql,(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("���}����!\r\n���~�H��:%s",e.ErrorMessage());
		::MessageBox(NULL,errormessage,"���}�ƾڪ�",MB_ICONSTOP);
		return;
	} 
	
	
	CString tt,tt2;
	
 
 

	myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename=strSchemeName;

 	
	if(!m_pRecordset->adoEOF)
	{
		Thevalue = m_pRecordset->GetCollect("�]�p����"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			SchemeDatass[m_currentSchemeIndexs].strDesigngrade=Thevalue.bstrVal;
		

		}
		
		Thevalue = m_pRecordset->GetCollect("�o�޺���"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			SchemeDatass[m_currentSchemeIndexs].strDraughtstyle=Thevalue.bstrVal;
		
		}
		

		Thevalue = m_pRecordset->GetCollect("��������"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			SchemeDatass[m_currentSchemeIndexs].strBlocomotiveStyle=Thevalue.bstrVal;
		
		}
		
		Thevalue = m_pRecordset->GetCollect("����覡"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			SchemeDatass[m_currentSchemeIndexs].strCBbsStyle=Thevalue.bstrVal;
		
		}

		Thevalue = m_pRecordset->GetCollect("�a�Φa�O"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			SchemeDatass[m_currentSchemeIndexs].strTerrainstyle=Thevalue.bstrVal;
		
		}
		
		Thevalue = m_pRecordset->GetCollect("�u�{����"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			SchemeDatass[m_currentSchemeIndexs].strEngineeringcondition=Thevalue.bstrVal;
		
		}
		
		Thevalue = m_pRecordset->GetCollect("�]�p�t��"); 
		SchemeDatass[m_currentSchemeIndexs].designspeed=(short)Thevalue;
		
		Thevalue = m_pRecordset->GetCollect("�̤p���u�b�|"); 
		SchemeDatass[m_currentSchemeIndexs].minRadius=(long)Thevalue;
		
		Thevalue = m_pRecordset->GetCollect("��o�u���Ī���"); 
		SchemeDatass[m_currentSchemeIndexs].dxfLength=(short)Thevalue;
		
		Thevalue = m_pRecordset->GetCollect("�̤p�Y��"); 
		SchemeDatass[m_currentSchemeIndexs].minSlopeLength=(double)Thevalue;		
		
		Thevalue = m_pRecordset->GetCollect("�̤j�Y��"); 
		SchemeDatass[m_currentSchemeIndexs].maxSlope=(double)Thevalue;		
	
		Thevalue = m_pRecordset->GetCollect("�̤j�Y�׮t"); 
		SchemeDatass[m_currentSchemeIndexs].maxSlopePddsc=(double)Thevalue;		
		
		Thevalue = m_pRecordset->GetCollect("�_�I���{"); 
		SchemeDatass[m_currentSchemeIndexs].StartLC=(double)Thevalue;		
		
		Thevalue = m_pRecordset->GetCollect("���I���{"); 
		SchemeDatass[m_currentSchemeIndexs].EndLC=(double)Thevalue;		
		
 
 
 
	}
	
	m_pRecordset->Close();
}

 
 
void CDesingScheme::GetQLXY(float L0, long R, int RoateStyle, float LL, float fwj, double ZH_xy_x, double ZH_xy_y, double HZ_xy_x, double HZ_xy_y, double *xc, double *yc, int Q_H_L)
{
	double ptx,pty;
	ptx=LL-LL*LL*LL*LL*LL/(40.0*R*R*L0*L0)+LL*LL*LL*LL*LL*LL*LL*LL*LL/(3456.0*R*R*R*R*L0*L0*L0*L0);
	pty=LL*LL*LL/(6.0*R*L0)*(1-LL*LL*LL*LL/(56.0*R*R*L0*L0)+LL*LL*LL*LL*LL*LL*LL*LL/(7040.0*R*R*R*R*L0*L0*L0*L0));
	float xita;
	if(Q_H_L==1)
	{		
		xita=PAI/2.0-fwj;
		
		if(RoateStyle==-1)	
		{
			*xc=cos(xita)*ptx-sin(xita)*pty+ZH_xy_x;
			*yc=sin(xita)*ptx+cos(xita)*pty+ZH_xy_y;
		}
		else if(RoateStyle==1)	
		{
			*xc=cos(xita)*ptx+sin(xita)*pty+ZH_xy_x;
			*yc=sin(xita)*ptx-cos(xita)*pty+ZH_xy_y;
		}
	}
	else     
	{
		xita=3*PAI/2.0-fwj; 
		if(RoateStyle==-1)	
		{
			*xc=cos(xita)*ptx+sin(xita)*pty+HZ_xy_x;
			*yc=sin(xita)*ptx-cos(xita)*pty+HZ_xy_y;
		}
		else if(RoateStyle==1)	
		{
			*xc=cos(xita)*ptx-sin(xita)*pty+HZ_xy_x;
			*yc=sin(xita)*ptx+cos(xita)*pty+HZ_xy_y;
		}
	}
}

 
void CDesingScheme::GetYQXXY(double centerx, double centery, long R, int RoateStyle, float LL, float alfa, double HY_xy_x, double HY_xy_y, double YH_xy_x, double YH_xy_y, double *xc, double *yc)
{
	double dx,dy;
		dx=HY_xy_x-centerx;
		dy=HY_xy_y-centery;
	
		
		float peiAngle=atan(dy/dx);
		
		float thetaAngle=LL*1.0/R;
		float rAngle;

		if(RoateStyle==-1)	
		{
			if(dx>0)
			{
				rAngle=peiAngle+thetaAngle;
			}
			else if(dx<0)
			{
				rAngle=peiAngle+thetaAngle-PAI;
			}
		}
		else if(RoateStyle==1)	
		{
			
			if(dx>0)
			{
				rAngle=peiAngle-thetaAngle;
			}
			else if(dx<0)
			{
				rAngle=peiAngle-thetaAngle+PAI;
			}
		}
		*xc=centerx+R*cos(rAngle);
		*yc=centery+R*sin(rAngle);			
}

 
double CDesingScheme::GetDistenceXY(double x1, double y1,  double x2, double y2)
{
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

 
float CDesingScheme::GetDistenceXYZ(double x1, double y1, double z1, double x2, double y2, double z2)
{
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));	
}


//�b���I�������I�ëO�s��ƾڮw�M�Ʋդ�,�ѵ{�ǽե�
void CDesingScheme::Save3DlineZX()
{

	int mNCDistence=4;

	double x1,y1,z1,x2,y2,z2,x3,y3,z3;
	float ZH_h,HZ_h;
	CString m_strPtStyle;
	PtS_3DLineZX[m_currentSchemeIndexs].RemoveAll();
	PtS_Railway3D[m_currentSchemeIndexs].RemoveAll();
	PtS_RailwayLj3D[m_currentSchemeIndexs].RemoveAll();
	PtS_RailwayLjToBP3D[m_currentSchemeIndexs].RemoveAll();
	PtS_RailwayBP3D[m_currentSchemeIndexs].RemoveAll();
	PtS_HuPo[m_currentSchemeIndexs].RemoveAll();
	PtS_PaiSuiGou[m_currentSchemeIndexs].RemoveAll();
	
	PCordinate ppt;
	for (long i=0;i<JDCurveElementss[m_currentSchemeIndexs].GetSize();i++)
	{
		
		if(i==0 || i==JDCurveElementss[m_currentSchemeIndexs].GetSize()-1)
		{
			
			ppt=new Cordinate;
			ppt->x=PtS_JD.GetAt(i)->x;
			ppt->y=PtS_JD.GetAt(i)->y;
			ppt->z=PtS_JD.GetAt(i)->z;
			ppt->dmh=m_demInsert.GetHeightValue(ppt->x+theApp.m_DemLeftDown_x,-ppt->z+theApp.m_DemLeftDown_y,2);
			ppt->Derh=ppt->y-ppt->dmh;
			ppt->strJDStyle="���I����";
			ppt->Lc=JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH;
			if(i==0) 
				PtS_3DLineZX[m_currentSchemeIndexs].Add(ppt);
			else  
			{			
				double L1=GetDistenceXY(PtS_JD.GetAt(i-1)->x,\
					PtS_JD.GetAt(i-1)->z,PtS_JD.GetAt(i)->x,\
					PtS_JD.GetAt(i)->z);
				double L2=GetDistenceXY(PtS_JD.GetAt(i-1)->x,\
					PtS_JD.GetAt(i-1)->z,\
					JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->HZ_xy->x,\
					-JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->HZ_xy->y);
				y1=PtS_JD.GetAt(i-1)->y;
				y2=PtS_JD.GetAt(i)->y;
				float HZ_h=y1+L2/L1*(y2-y1);
				float ZH_h=PtS_JD.GetAt(i)->y;
				double LZH2=JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH-JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->HZ;
				
				NeiChaDian(LZH2,\
				JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->HZ_xy->x,\
				HZ_h,\
				-JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->HZ_xy->y,\
				JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH_xy->x,\
				ZH_h,\
				-JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH_xy->y,JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->HZ);
				PtS_3DLineZX[m_currentSchemeIndexs].RemoveAt(PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1);
				PtS_3DLineZX[m_currentSchemeIndexs].Add(ppt);
			}

		}
			
		
		else if(i>0 && i<JDCurveElementss[m_currentSchemeIndexs].GetSize()-1)//��e���Ii���O��ת��̫�@�ӥ��I,���w�M���u�q,���u�q
		{
			
			x1=PtS_JD.GetAt(i-1)->x; 
			y1=PtS_JD.GetAt(i-1)->y;
			z1=PtS_JD.GetAt(i-1)->z;
		
			x2=PtS_JD.GetAt(i)->x; 
			y2=PtS_JD.GetAt(i)->y;
			z2=PtS_JD.GetAt(i)->z;
			
			x3=PtS_JD.GetAt(i+1)->x; 
			y3=PtS_JD.GetAt(i+1)->y;
			z3=PtS_JD.GetAt(i+1)->z;

			double L1=GetDistenceXY(x1,z1,x2,z2);
			double tx=JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH_xy->x;
			double tz=-JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH_xy->y;
			
			double LZH=GetDistenceXY(x1,z1,tx,tz);
			ZH_h=y1+LZH/L1*(y2-y1);
			
			
			
			double LZH2=GetDistenceXY(\
				JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->HZ_xy->x,\
				-JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->HZ_xy->y,\
				JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH_xy->x,\
				-JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH_xy->y);
			
			tx=JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->HZ_xy->x;
			tz=-JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->HZ_xy->y;
			double LHZ=GetDistenceXY(x1,z1,tx,tz);
			HZ_h=y1+LHZ/L1*(y2-y1);
			

			NeiChaDian(LZH2,\
				JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->HZ_xy->x,\
				HZ_h,\
				-JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->HZ_xy->y,\
				JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH_xy->x,\
				ZH_h,\
				-JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH_xy->y,\
				JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->HZ);

	
		
			L1=GetDistenceXY(x2,z2,x3,z3);
			tx=JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HZ_xy->x;
			tz=-JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HZ_xy->y;
			LHZ=GetDistenceXY(x2,z2,tx,tz);
			HZ_h=y2+LHZ/L1*(y3-y2);
		
			
			
			float Derh=HZ_h-ZH_h;
			float LL=JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HZ-JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH;
			float L0=JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->L0;
			BOOL bEnd=FALSE;
			float k=0;
			while (k<L0 && bEnd==FALSE)
			{
				float h=ZH_h+k*Derh/LL;
				k+=mNCDistence;
				if(k>L0) 
				{
					k=L0;
					bEnd=TRUE;
				}
				
				GetQLXY(L0,JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->R,\
					JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->RoateStyle,\
					k,JDCurveElementss[m_currentSchemeIndexs].GetAt(i-1)->fwj,\
					JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH_xy->x,\
					JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH_xy->y,0,0,&x1,&y1,1);
				
				if(k==L0)
					m_strPtStyle="�w���I����";
				else
					m_strPtStyle="�e�w�M���u�q�I����";
			
				ppt=new Cordinate;
				ppt->x=x1;
				ppt->y=h;
				ppt->z=-y1;
				ppt->dmh=m_demInsert.GetHeightValue(ppt->x+theApp.m_DemLeftDown_x,-ppt->z+theApp.m_DemLeftDown_y,2);
				ppt->Derh=ppt->y-ppt->dmh;
				ppt->strJDStyle=m_strPtStyle;
				ppt->Lc=k+JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH;
				PtS_3DLineZX[m_currentSchemeIndexs].Add(ppt);
				
			}
			
			
			float Ly=JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->Ly;
			k=0;
			bEnd=FALSE;
			while(k<Ly && bEnd==FALSE)
			{
				k+=mNCDistence;
				if(k>Ly) 
				{
					k=Ly;
					bEnd=TRUE;
				}
				float h=ZH_h+(k+L0)*Derh/LL;
				GetYQXXY(JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->Cneterx,JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->Cnetery,\
					JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->R,JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->RoateStyle,\
					k,JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->Alfa,JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HY_xy->x,\
					JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HY_xy->y,\
					JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->YH_xy->x,JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->YH_xy->y,\
					&x1,&y1);
			
				if(k==Ly)
					m_strPtStyle="��w�I����";
				else
					m_strPtStyle="�ꦱ�u�q�I����";
				
				ppt=new Cordinate;
				ppt->x=x1;
				ppt->y=h;
				ppt->z=-y1;
				ppt->dmh=m_demInsert.GetHeightValue(ppt->x+theApp.m_DemLeftDown_x,-ppt->z+theApp.m_DemLeftDown_y,2);
				ppt->Derh=ppt->y-ppt->dmh;
				ppt->strJDStyle=m_strPtStyle;
				ppt->Lc=k+JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HY;
				PtS_3DLineZX[m_currentSchemeIndexs].Add(ppt);
				
			}
		
			
			k=L0;
			bEnd=FALSE;
			
			float L3=JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->YH-JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->ZH;
			while(k>0 && bEnd==FALSE)
			{
				k-=mNCDistence;
				float h=ZH_h+((L0-k)+L3)*Derh/LL;

				if(k<0) 
				{
					k=0;
					bEnd=FALSE;
				}
			
				GetQLXY(L0,JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->R,JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->RoateStyle,\
					k,JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->fwj,0,0,JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HZ_xy->x,\
					JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->HZ_xy->y,&x1,&y1,2);
			
				if(k==0)
					m_strPtStyle="�w���I����";
				else
					m_strPtStyle="��w�M���u�q�I����";
				
				ppt=new Cordinate;
				ppt->x=x1;
				ppt->y=h;
				ppt->z=-y1;
				ppt->dmh=m_demInsert.GetHeightValue(ppt->x+theApp.m_DemLeftDown_x,-ppt->z+theApp.m_DemLeftDown_y,2);
				ppt->Derh=ppt->y-ppt->dmh;
				ppt->strJDStyle=m_strPtStyle;
				ppt->Lc=(L0-k)+JDCurveElementss[m_currentSchemeIndexs].GetAt(i)->YH;
				
				PtS_3DLineZX[m_currentSchemeIndexs].Add(ppt);
				
			}
		}
	}
	
	Save3DlineZXCorrdinateToDB();	
			
}

 
void CDesingScheme::Save3DlineZXCorrdinateToDB()
{
	CString tt;

	m_pRecordset.CreateInstance("ADODB.Recordset");   
	tt.Format("DELETE FROM  T3DLineZxCorrdinate WHERE ��צW��='%s'",SchemeDatass[m_currentSchemeIndexs].Schemename);
	
	hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 
	if(!SUCCEEDED(hr))
	{
		AfxMessageBox("�R���ƾڥ���!",MB_ICONINFORMATION);
		return;
	}

	for(long i=0;i<PtS_3DLineZX[m_currentSchemeIndexs].GetSize();i++)
	{
		tt.Format("INSERT INTO T3DLineZxCorrdinate VALUES(\
			'%s',%ld,%.3f,%.3f,%.3f,'%s',%.3f,%.3f,%.3f)",\
			SchemeDatass[m_currentSchemeIndexs].Schemename,
			i+1,
			PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x,
			PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->y,
			PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z,
			PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle,
			PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->dmh,
			PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Derh,
			PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Lc
		);
		try
		{
			hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 
			if(!SUCCEEDED(hr))
			{
				AfxMessageBox("��׫O�s����!",MB_ICONINFORMATION);
				return;
			}
		}
	
		catch(_com_error& e)	
		{
			CString errormessage;
			errormessage.Format("���~�H��:%s",e.ErrorMessage());
			AfxMessageBox(errormessage,MB_ICONINFORMATION);
			return;
		} 
	}	
}

 
 

void CDesingScheme::Get3DLineModel(double x1, double y1, double z1,double x2, double y2, double z2, float fRailwayWidth, float LjWidth, float h_FromGmToLj,float mWidthGuiMianToLujian,float mAngleLujinaToBianPo,CString strJDstyle,CString strJDstyleNext,long index,double mLC)
{
 
	
	float mangle;
	float dx=x2-x1;
	float dz=z2-z1;
	
	double x11,y11,z11,x12,y12,z12;
	double x21,y21,z21,x22,y22,z22;

	//fRailwayWidth�G��u�a�q�D�ɳ����e��
	float L1=fRailwayWidth/2.0;

    //�ھڽu���e�ᤤ�߽u���T�����Эp���K�y�������k�I��x,y,z����
	Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);

	PRailway3DCordinate pt;
	pt=new Railway3DCordinate;
	pt->x1=x11;	pt->y1=y11;	pt->z1=z11;
	pt->x2=x12;	pt->y2=y12;	pt->z2=z12;
	PtS_Railway3D[m_currentSchemeIndexs].Add(pt);
	
	//�ھڽu���e�ᤤ�߽u���T�����Эp��D�ɳ������k�I��x,y,z����
	L1=fRailwayWidth/2.0+mWidthGuiMianToLujian;
	Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
	pt=new Railway3DCordinate;
	pt->x1=x11;	pt->y1=y11-h_FromGmToLj;	pt->z1=z11;
	pt->x2=x12;	pt->y2=y12-h_FromGmToLj;	pt->z2=z12;
	PtS_RailwayLj3D[m_currentSchemeIndexs].Add(pt);
	
	
	//�ھڽu���e�ᤤ�߽u���T�����Эp����}���k�I��x,y,z���� LjWidth=��Ӧ���}�������Z��
	L1=fRailwayWidth/2.0+mWidthGuiMianToLujian+LjWidth;
	Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
	pt=new Railway3DCordinate;
	pt->x1=x11;	pt->y1=y11-h_FromGmToLj;pt->z1=z11;
	pt->x2=x12;	pt->y2=y12-h_FromGmToLj;	pt->z2=z12;

		
	//�ھڽu���e�ᤤ�߽u���T�����Эp��p����򭱥��k�I��x,y,z����
	pt->TW_left=GetTW(pt->x1, pt->z1, pt->y1);//�p�⥪��Y���������
	pt->TW_right=GetTW(pt->x2, pt->z2, pt->y2);//�p��k��Y���������
 	pt->mAngle=mangle; //
	PtS_RailwayLjToBP3D[m_currentSchemeIndexs].Add(pt);//�s�x��Y���������������
	PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(0)->x1;

		
	//4.�D���k���������I����
		/*
		�Ƥ�����4���I�T�w,���O��1-4���I,�䤤0���I��LjToBp�I,�w�s�x
		5____4     1____0
		(b4) \     /(b3)
	         3\___/2
		�䤤:
		�����`�� SuiGou_h,
		�������e�� SuiGou_b1,
		�������e�� SuiGou_b2,
		�����~��Y���e��  SuiGou_b3
		��������Y[�a�����@��]�ײv SuiGou_m1,
		�����~��Y[��������@��]�ײv SuiGou_m2,
		
		*/
		//
		float SuiGou_h,SuiGou_b1,SuiGou_b2,SuiGou_b3,SuiGou_b4,SuiGou_m1,SuiGou_m2;
		SuiGou_b2=0.4;//�������e��[�W�d�n�D]
		SuiGou_h=0.6;//�����`��[�W�d�n�D]
		SuiGou_b3=0.3;
		SuiGou_b4=0.6;//�����~��Y���e��[�W�d�n�D:����:0.8  ����:0.6 ,�o�̬��F²�K,�Τ@����0.6]
		SuiGou_m1=SuiGou_m2=1;//��/�~��Y�ײv[�W�d�n�D]
		SuiGou_b1=SuiGou_h/SuiGou_m1+SuiGou_h/SuiGou_m2+SuiGou_b2;//�������e��
			
		PPaiSuiGou ptt;
		ptt=new PaiSuiGou;

		
		//�p�⥪�ΰ�����0�I������
		if(pt->TW_left==-1 || pt->TW_right==-1)
		{
			ptt->SuiGouL[0].x=pt->x1;ptt->SuiGouL[0].y=	pt->y1;ptt->SuiGouL[0].z=pt->z1;
			ptt->SuiGouR[0].x=pt->x2;ptt->SuiGouR[0].y=pt->y2;ptt->SuiGouR[0].z=pt->z2;
		}

		//�p�⥪�ΰ�����1�I������
		if(pt->TW_left==-1 || pt->TW_right==-1)
		{
			L1=fRailwayWidth/2.0+mWidthGuiMianToLujian+LjWidth+SuiGou_b3;
			Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
			ptt->SuiGouL[1].x=x11;ptt->SuiGouL[1].y=pt->y1;ptt->SuiGouL[1].z=z11;
			ptt->SuiGouR[1].x=x12;ptt->SuiGouR[1].y=pt->y2;ptt->SuiGouR[1].z=z12;
		}
		
		//�p�⥪�ΰ�����2�I������
		if(pt->TW_left==-1 || pt->TW_right==-1)
		{
			L1=fRailwayWidth/2.0+mWidthGuiMianToLujian+LjWidth+SuiGou_h/SuiGou_m1+SuiGou_b3;
			Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
			ptt->SuiGouL[2].x=x11;ptt->SuiGouL[2].y=pt->y1-SuiGou_h;ptt->SuiGouL[2].z=z11;
			ptt->SuiGouR[2].x=x12;ptt->SuiGouR[2].y=pt->y2-SuiGou_h;ptt->SuiGouR[2].z=z12;
		}

		//�p�⥪�ΰ�����3�I������
		if(pt->TW_left==-1 || pt->TW_right==-1)
		{
			L1=fRailwayWidth/2.0+mWidthGuiMianToLujian+LjWidth+SuiGou_h/SuiGou_m1+SuiGou_b2+SuiGou_b3;
			Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
			ptt->SuiGouL[3].x=x11;ptt->SuiGouL[3].y=pt->y1-SuiGou_h;ptt->SuiGouL[3].z=z11;
			ptt->SuiGouR[3].x=x12;ptt->SuiGouR[3].y=pt->y2-SuiGou_h;ptt->SuiGouR[3].z=z12;
		}

		//�p�⥪�ΰ�����4�I������
		if(pt->TW_left==-1 || pt->TW_right==-1)
		{
			L1=fRailwayWidth/2.0+mWidthGuiMianToLujian+LjWidth+SuiGou_b1+SuiGou_b3;
			Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
			ptt->SuiGouL[4].x=x11;ptt->SuiGouL[4].y=pt->y1;ptt->SuiGouL[4].z=z11;
			ptt->SuiGouR[4].x=x12;ptt->SuiGouR[4].y=pt->y2;ptt->SuiGouR[4].z=z12;
		}
		
		//�p�⥪�ΰ�����5�I������
		if(pt->TW_left==-1 || pt->TW_right==-1)
		{
			L1=fRailwayWidth/2.0+mWidthGuiMianToLujian+LjWidth+SuiGou_b1+SuiGou_b3+SuiGou_b4;
			Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
			ptt->SuiGouL[5].x=x11;ptt->SuiGouL[5].y=pt->y1;ptt->SuiGouL[5].z=z11;
			ptt->SuiGouR[5].x=x12;ptt->SuiGouR[5].y=pt->y2;ptt->SuiGouR[5].z=z12;
		}
		
		if(pt->TW_left==-1)		//����
			ptt->bhaveSuiGou_L=TRUE; //��ܥ���������(��Y���������ժ����p�U�]�m����)
		else
		{
			ptt->bhaveSuiGou_L=FALSE;  //��ܨS������
			//�S�����������p�U,����4,5�I�P0�I���X
			ptt->SuiGouL[4].x=pt->x1;ptt->SuiGouL[4].y=	pt->y1;ptt->SuiGouL[4].z=pt->z1;
			ptt->SuiGouL[5].x=pt->x1;ptt->SuiGouL[5].y=	pt->y1;ptt->SuiGouL[5].z=pt->z1;
		}
		
		if(pt->TW_right==-1)		//����	
			ptt->bhaveSuiGou_R=TRUE; //��ܥk��������(��Y���������ժ����p�U�]�m����)
		else
		{
			ptt->bhaveSuiGou_R=FALSE;//��ܨS������
			//�S�����������p�U,����4,5�I�P0�I���X
			ptt->SuiGouR[4].x=pt->x2;ptt->SuiGouR[4].y=pt->y2;ptt->SuiGouR[4].z=pt->z2;
			ptt->SuiGouR[5].x=pt->x2;ptt->SuiGouR[5].y=pt->y2;ptt->SuiGouR[5].z=pt->z2;
		}	

		PtS_PaiSuiGou[m_currentSchemeIndexs].Add(ptt); //�N�p�⪺�����I���Цs�x�bPtS_PaiSuiGou[]�Ʋդ�
		
		if(strJDstyle!="���٤����I" && strJDstyle!="�G�D�����I" ) //�p�G�u�������I�������O"���٤����I"�M"�G�D�����I"
		{	
			
			if(strJDstyle=="�G�D���I" && strJDstyleNext=="���ٰ_�I" ) //�����G�D�����۳s,���]�m��Y
			{	
				PLuQianHuPo ptt;
				ptt= new LuQianHuPo;
				ptt->Huponums_L =0; //������Y�Ƭ�0
				ptt->Huponums_R =0; //�k����Y�Ƭ�0
				ptt->TW_left=99; //��ܤ��ݭn�]�m��Y
				ptt->TW_right=99;//��ܤ��ݭn�]�m��Y
				ptt->strJDStyle=strJDstyle; //���I����
				ptt->Lc=mLC; //���I���{
				PtS_HuPo[m_currentSchemeIndexs].Add(ptt);//���G���I
			}
			else //���`��Y�B
			{
				L1=fRailwayWidth/2.0+mWidthGuiMianToLujian+LjWidth+SuiGou_b1+SuiGou_b3;
			
				//�p�⥪����Y�I�P�a�������I����
				GetDMJD(x1,y1,z1,x2,y2,z2,L1,pt->y1,pt->x1, pt->z1,pt->TW_left,-1,\
					ptt->SuiGouL[4].x,ptt->SuiGouL[4].y,ptt->SuiGouL[4].z,\
					ptt->SuiGouL[5].x,ptt->SuiGouL[5].y,ptt->SuiGouL[5].z,mLC,strJDstyle);

				//�p��k����Y�I�P�a�������I����
				GetDMJD(x1,y1,z1,x2,y2,z2,L1,pt->y2,pt->x2, pt->z2,pt->TW_right,1,\
					ptt->SuiGouR[4].x,ptt->SuiGouR[4].y,ptt->SuiGouR[4].z,\
					ptt->SuiGouR[5].x,ptt->SuiGouR[5].y,ptt->SuiGouR[5].z,mLC,strJDstyle);
			}
		}
		else //�p�G�u�������I�����O"���٤����I"���G�D�����I",�h���ݭn�]�m��Y
		{
			PLuQianHuPo ptt;
			ptt= new LuQianHuPo;
			ptt->Huponums_L =0; //������Y�Ƭ�0
			ptt->Huponums_R =0; //�k����Y�Ƭ�0
			ptt->TW_left=99; //��ܤ��ݭn�]�m��Y
			ptt->TW_right=99;//��ܤ��ݭn�]�m��Y
			ptt->strJDStyle=strJDstyle; //���I����
			ptt->Lc=mLC; //���I���{
			//���G���I
			PtS_HuPo[m_currentSchemeIndexs].Add(ptt);
		}
	
}

//�ھڽu���e�ᤤ�߽u���I���T�����Эp������������_�����k�I��x,y,z����
void CDesingScheme::Get3DCorrdinate(double x1, double y1, double z1, double x2, double y2, double z2, float dx,float dz,float L, double *x11, double *y11, double *z11, double *x12, double *y12, double *z12, double *x21, double *y21, double *z21, double *x22, double *y22, double *z22,float *angle)
{
	float mangle;
	if(fabs(dx)<=0.000001)  //�p�G�e��u�����u�I��X���Ф��t<=0.000001,�h�{�����I�զ������u�����Y�b
	{
		if(dz<0) 
			mangle=PAI/2.0;   //�p�Gdz<0,���u����=90
		else
			mangle=3/2.0*PAI;   //�p�Gdz<0,���u����=270
	
		//�p��u�����u��e�I(x1,y1,z1)�����������I�T������
		*x11=x1-L*sin(mangle);
		*y11=y1;	
		*z11=z1;
		
		//�p��u�����u�U�@�I(x2,y2,z2)�����������I�T������
		*x21=x2-L*sin(mangle);
		*y21=y2;	
		*z21=z2;
		*angle=mangle;
	}  
	else //�ھ�fabs(dz/dx)�ȭp��e��u�����u�I�c�������u����
	{
		mangle=atan(fabs(dz/dx));
		if(dx>=0 && dz<=0)  //1 �H��
		{
			//�p��u�����u��e�I(x1,y1,z1)�����������I�T������
			*x11=x1-L*sin(mangle);
			*y11=y1;	
			*z11=z1-L*cos(mangle);
		
			//�p��u�����u�U�@�I(x2,y2,z2)�����������I�T������
			*x21=x2-L*sin(mangle);
			*y21=y2;	
			*z21=z2-L*cos(mangle);
			*angle=mangle;
		}
		else if(dx<=0 && dz<=0) //2 �H��
		{
			//�p��u�����u��e�I(x1,y1,z1)�����������I�T������
			*x11=x1-L*sin(mangle);
			*y11=y1;	
			*z11=z1+L*cos(mangle);

			//�p��u�����u�U�@�I(x2,y2,z2)�����������I�T������
			*x21=x2-L*sin(mangle);
			*y21=y2;	
			*z21=z2+L*cos(mangle);

			*angle=PAI-mangle;
		}
		else if(dx<=0 && dz>=0) //3 �H��
		{
			//�p��u�����u��e�I(x1,y1,z1)�����������I�T������
			*x11=x1+L*sin(mangle);
			*y11=y1;	
			*z11=z1+L*cos(mangle);
			
			//�p��u�����u�U�@�I(x2,y2,z2)�����������I�T������
			*x21=x2+L*sin(mangle);
			*y21=y2;	
			*z21=z2+L*cos(mangle);	
			*angle=PAI+mangle;
		}
		else if(dx>=0 && dz>=0) //4 �H��
		{
			//�p��u�����u��e�I(x1,y1,z1)�����������I�T������
			*x11=x1+L*sin(mangle);
			*y11=y1;	
			*z11=z1-L*cos(mangle);
			
			//�p��u�����u�U�@�I(x2,y2,z2)�����������I�T������
			*x21=x2+L*sin(mangle);
			*y21=y2;	
			*z21=z2-L*cos(mangle);
			*angle=2*PAI-mangle;
		}
	}
	
	//�p��u�����u��e�I(x1,y1,z1)�������k���I�T������
	*x12=2*x1-*x11;
	*y12=2*y1-*y11;
	*z12=2*z1-*z11;
	
	//�p��u�����u�U�@�I(x2,y2,z2)�������k���I�T������
	*x22=2*x2-*x21;
	*y22=2*y2-*y21;
	*z22=2*z2-*z21;
	
}

float CDesingScheme::GetH(float L, float Afla, float mAngle,double x0,double z0,int mLeftRight,double *xx,double *zz)
{
	double x,z;
	float peita;

    
	if(mAngle>=0 && mAngle<=PAI/2.0) 
	{
		peita=PAI/2-mAngle;
		x=mLeftRight*L*cos(Afla)*cos(peita)+x0;
		z=mLeftRight*L*cos(Afla)*sin(peita)+z0;
	}
	else if(mAngle>PAI/2.0 && mAngle<=PAI)	
	{
		peita=mAngle-PAI/2;
		x=mLeftRight*L*cos(Afla)*cos(peita)+x0;
		z=-mLeftRight*L*cos(Afla)*sin(peita)+z0;
	}
	else if(mAngle>PAI&& mAngle<=PAI*3/2.0)	
	{
		peita=PAI*3.0/2-mAngle;
		x=-mLeftRight*L*cos(Afla)*cos(peita)+x0;
		z=-mLeftRight*L*cos(Afla)*sin(peita)+z0;
	}
	else if(mAngle>PAI*3/2.0&& mAngle<=PAI*2.0)	
	{
		peita=mAngle-PAI*3.0/2;
		x=-mLeftRight*L*cos(Afla)*cos(peita)+x0;
		z=mLeftRight*L*cos(Afla)*sin(peita)+z0;
	}

	float mh=m_demInsert.GetHeightValue(x+theApp.m_DemLeftDown_x,-z+theApp.m_DemLeftDown_y,2);
	
	*xx=x;
	*zz=z;
	return mh;
	
}


//�p����Y���������
int CDesingScheme::GetTW(double x, double z, float H)
{
	int mTW;
	double tx1=x+theApp.m_DemLeftDown_x; //�Nx,y�����ഫ���j�a����
	double  ty1=-z+theApp.m_DemLeftDown_y;
	if(tx1>theApp.m_DemRightUp_x)	//����x���жW�X���	
		tx1=theApp.m_DemRightUp_x;
	if(ty1>theApp.m_DemRightUp_y)	//����y���жW�X���		
		ty1=theApp.m_DemRightUp_y;
	float mh=m_demInsert.GetHeightValue(tx1,ty1,2); //�qDEM�������p��a���I���{
	if(fabs(H-mh)<=0.001) //�p�G�������I�����{�P�������U�誺�a���I���{���t<=0.001
		mTW=0; //�{���O��������I(�Y���0�I)
	else if(H<mh) 
		mTW=-1;  //<�������U�誺�a���I���{,������
	else
		mTW=1;  //>�������U�誺�a���I���{,������

	return mTW;  //��^�p�⪺��Y�������

}

//�p����Y�I�P�a�ѽu�����I���� 
void CDesingScheme::GetBpJD(float H0, float Afla, float mangle, double x0, double z0, int bsignTW, int mLeftRight, double *tx, double *ty, double *tz)
{
	double xx,zz;
	float L=0.1;
	float h1=-999;
	float hNew=-9999;
	float m_bc=0.2;//
	float DerC=0.05; //0.05
	while(fabs(h1-hNew)>DerC) 
	{
		h1=H0-bsignTW*L*sin(Afla);
		hNew=GetH(L,Afla,mangle,x0,z0,mLeftRight,&xx,&zz); //�������a�����{
	
	//	L+=m_bc;
	
		if(bsignTW==-1)
		{
			if(h1-hNew>0) //�p�G�W�X�F�a��
			{
				hNew=h1;

			}
			else //�٬O�C��a�ѽu
			{
				L=L*1.1;
			}
		}
		else  if(bsignTW==1)
		{
			if(h1-hNew<0)
			{
				hNew=h1;
			}
			else
			{
				L=L*1.1;
			}
		}
	}
	if(fabs(h1-hNew)<DerC)	
	{
		if(mLeftRight==-1)
		{
 
			*tx=xx;
			*ty=hNew;
			*tz=zz;
 
		}
		else  
		{
		
			*tx=xx;
			*ty=hNew;
			*tz=zz;               
		}
	}
	
}

 


 
float CDesingScheme::GetAlfa(int mTW)
{
	float Afla;
	
	if(mTW==1)
		Afla=30.0/180*PAI;
	else if(mTW==-1)
		Afla=30.0/180*PAI;
	return Afla;
}

 
void CDesingScheme::NeiChaDian(float ZHLength, double x1, double y1, double z1, double x2, double y2, double z2,double lc)
{
	
	float h;
	
	int m_XX;
	double x,z;
	float dx,dz;
	float mangle;
	PCordinate ppt;
	dx=x2-x1;
	dz=z2-z1;
	if(fabs(dx)<=0.000001)
	{
		if(z2<z1)
			mangle=PAI/2.0;
		else
			mangle=PAI*3/2.0;	
	}
	else
	{
		mangle=atan(fabs(dz/dx));
		if(dx>=0 && dz<=0) 
			m_XX=1;
		else if(dx<=0 && dz<=0) 
			m_XX=2;
		else if(dx<=0 && dz>=0) 
			m_XX=3;
		else if(dx>=0 && dz>=0) 
			m_XX=4;
	}

	float lt=0;
	float dh=(y2-y1)/ZHLength;
	while(lt<ZHLength)
	{
		lt+=10;
		if(lt>ZHLength)
			break;
		h=y1+lt*dh;
		switch(m_XX)
		{
		case 1:   
			x=lt*cos(mangle)+x1;
			z=-lt*sin(mangle)+z1;
			break;
		case 2:   
			x=-lt*cos(mangle)+x1;
			z=-lt*sin(mangle)+z1;
			break;	
		case 3:   
			x=-lt*cos(mangle)+x1;
			z=lt*sin(mangle)+z1;
			break;	
		case 4:   
			x=lt*cos(mangle)+x1;
			z=lt*sin(mangle)+z1;
			break;				
		}
	
		ppt=new Cordinate;
		ppt->x=x;
		ppt->y=h;
		ppt->z=z;
		ppt->dmh=m_demInsert.GetHeightValue(ppt->x+theApp.m_DemLeftDown_x,-ppt->z+theApp.m_DemLeftDown_y,2);
		ppt->Derh=ppt->y-ppt->dmh;		
		ppt->strJDStyle="���I-���w�I����";
		ppt->Lc=lc+lt;
		PtS_3DLineZX[m_currentSchemeIndexs].Add(ppt);
	}
	ppt=new Cordinate;
	ppt->x=x2;
	ppt->y=y2;
	ppt->z=z2;
	ppt->dmh=m_demInsert.GetHeightValue(ppt->x+theApp.m_DemLeftDown_x,-ppt->z+theApp.m_DemLeftDown_y,2);
	ppt->Derh=ppt->y-ppt->dmh;				
	ppt->strJDStyle="���w�I����";
	ppt->Lc=lc+ZHLength;
	PtS_3DLineZX[m_currentSchemeIndexs].Add(ppt);
	
}



void CDesingScheme::Get3DLineModelLast(double x1, double y1, double z1, double x2, double y2, double z2, float fRailwayWidth, float LjWidth, float h_FromGmToLj, float mWidthGuiMianToLujian, float mAngleLujinaToBianPo,CString strJDstyle,CString strJDstyleNext,long index,double mLC)
{
 
	
	float mangle;
	float dx=x2-x1;
	float dz=z2-z1;
	
	double x11,y11,z11,x12,y12,z12;
	double x21,y21,z21,x22,y22,z22;

	float L1=fRailwayWidth/2.0;

    
	Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);

	PRailway3DCordinate pt;
	

	pt=new Railway3DCordinate;
	pt->x1=x21;	pt->y1=y21;	pt->z1=z21;
	pt->x2=x22;	pt->y2=y22;	pt->z2=z22;
	PtS_Railway3D[m_currentSchemeIndexs].Add(pt);
	

	
	L1=fRailwayWidth/2.0+mWidthGuiMianToLujian;
	Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);

	pt=new Railway3DCordinate;
	pt->x1=x21;	pt->y1=y21-h_FromGmToLj;pt->z1=z21;
	pt->x2=x22;	pt->y2=y22-h_FromGmToLj;pt->z2=z22;
	PtS_RailwayLj3D[m_currentSchemeIndexs].Add(pt);

	
	
	L1=fRailwayWidth/2.0+mWidthGuiMianToLujian+LjWidth;
	Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
	
	pt=new Railway3DCordinate;
	pt->x1=x21;	pt->y1=y21-h_FromGmToLj;pt->z1=z21;
	pt->x2=x22;	pt->y2=y22-h_FromGmToLj;pt->z2=z22;
	
	
	pt->TW_left=GetTW(pt->x1, pt->z1, pt->y1);
	pt->TW_right=GetTW(pt->x2, pt->z2, pt->y2);
 	pt->mAngle=mangle;
	PtS_RailwayLjToBP3D[m_currentSchemeIndexs].Add(pt);
	
	
	
	pt->TW_left=GetTW(pt->x1, pt->z1, pt->y1);
	pt->TW_right=GetTW(pt->x2, pt->z2, pt->y2);
	pt->mAngle=mangle;

	float SuiGou_h,SuiGou_b1,SuiGou_b2,SuiGou_b3,SuiGou_b4,SuiGou_m1,SuiGou_m2;
	SuiGou_b2=0.4;
	SuiGou_h=0.6;
	SuiGou_b3=0.3;
	SuiGou_b4=0.5;
	SuiGou_m1=SuiGou_m2=1;
    SuiGou_b1=SuiGou_h/SuiGou_m1+SuiGou_h/SuiGou_m2+SuiGou_b2;
	
	
	
	
	PPaiSuiGou ptt;
	ptt=new PaiSuiGou;
	
	
	if(pt->TW_left==-1 || pt->TW_right==-1)
	{
		ptt->SuiGouL[0].x=pt->x1;ptt->SuiGouL[0].y=	pt->y1;ptt->SuiGouL[0].z=pt->z1;
		ptt->SuiGouR[0].x=pt->x2;ptt->SuiGouR[0].y=pt->y2;ptt->SuiGouR[0].z=pt->z2;
	}
	
	
	if(pt->TW_left==-1 || pt->TW_right==-1)
	{
		L1=fRailwayWidth/2.0+mWidthGuiMianToLujian+LjWidth+SuiGou_b3;
		Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
		ptt->SuiGouL[1].x=x21;ptt->SuiGouL[1].y=pt->y1;ptt->SuiGouL[1].z=z21;
		ptt->SuiGouR[1].x=x22;ptt->SuiGouR[1].y=pt->y2;ptt->SuiGouR[1].z=z22;
	}
	
	
	if(pt->TW_left==-1 || pt->TW_right==-1)
	{
		L1=fRailwayWidth/2.0+mWidthGuiMianToLujian+LjWidth+SuiGou_h/SuiGou_m1+SuiGou_b3;
		Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
		ptt->SuiGouL[2].x=x21;ptt->SuiGouL[2].y=pt->y1-SuiGou_h;ptt->SuiGouL[2].z=z21;
		ptt->SuiGouR[2].x=x22;ptt->SuiGouR[2].y=pt->y2-SuiGou_h;ptt->SuiGouR[2].z=z22;
	}
	
	
	if(pt->TW_left==-1 || pt->TW_right==-1)
	{
		L1=fRailwayWidth/2.0+mWidthGuiMianToLujian+LjWidth+SuiGou_h/SuiGou_m1+SuiGou_b2+SuiGou_b3;
		Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
		ptt->SuiGouL[3].x=x21;ptt->SuiGouL[3].y=pt->y1-SuiGou_h;ptt->SuiGouL[3].z=z21;
		ptt->SuiGouR[3].x=x22;ptt->SuiGouR[3].y=pt->y2-SuiGou_h;ptt->SuiGouR[3].z=z22;
	}
	
	
	if(pt->TW_left==-1 || pt->TW_right==-1)
	{
		L1=fRailwayWidth/2.0+mWidthGuiMianToLujian+LjWidth+SuiGou_b1+SuiGou_b3;
		Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
		ptt->SuiGouL[4].x=x21;ptt->SuiGouL[4].y=pt->y1;ptt->SuiGouL[4].z=z21;
		ptt->SuiGouR[4].x=x22;ptt->SuiGouR[4].y=pt->y2;ptt->SuiGouR[4].z=z22;
	}
	
	
	if(pt->TW_left==-1 || pt->TW_right==-1)
	{
		L1=fRailwayWidth/2.0+mWidthGuiMianToLujian+LjWidth+SuiGou_b1+SuiGou_b3+SuiGou_b4;
		Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
		ptt->SuiGouL[5].x=x21;ptt->SuiGouL[5].y=pt->y1;ptt->SuiGouL[5].z=z21;
		ptt->SuiGouR[5].x=x22;ptt->SuiGouR[5].y=pt->y2;ptt->SuiGouR[5].z=z22;
	}
	
	if(pt->TW_left==-1)		
		ptt->bhaveSuiGou_L=TRUE;
	else
	{
		ptt->bhaveSuiGou_L=FALSE;
		ptt->SuiGouL[4].x=pt->x1;ptt->SuiGouL[4].y=	pt->y1;ptt->SuiGouL[4].z=pt->z1;
		ptt->SuiGouL[5].x=pt->x1;ptt->SuiGouL[5].y=	pt->y1;ptt->SuiGouL[5].z=pt->z1;
	}
	
	if(pt->TW_right==-1)		
		ptt->bhaveSuiGou_R=TRUE;
	else
	{
		ptt->bhaveSuiGou_R=FALSE;
		ptt->SuiGouR[4].x=pt->x2;ptt->SuiGouR[4].y=pt->y2;ptt->SuiGouR[4].z=pt->z2;
		ptt->SuiGouR[5].x=pt->x2;ptt->SuiGouR[5].y=pt->y2;ptt->SuiGouR[5].z=pt->z2;
	}	
	
	PtS_PaiSuiGou[m_currentSchemeIndexs].Add(ptt);

	
	if(strJDstyle!="���٤����I" && strJDstyle!="�G�D�����I" )
	{	
		GetDMJD(x1,y1,z1,x2,y2,z2,L1,pt->y1,pt->x1, pt->z1,pt->TW_left,-1,\
			ptt->SuiGouL[4].x,ptt->SuiGouL[4].y,ptt->SuiGouL[4].z,\
			ptt->SuiGouL[5].x,ptt->SuiGouL[5].y,ptt->SuiGouL[5].z,mLC,strJDstyle);
		GetDMJD(x1,y1,z1,x2,y2,z2,L1,pt->y2,pt->x2, pt->z2,pt->TW_right,1,\
			ptt->SuiGouR[4].x,ptt->SuiGouR[4].y,ptt->SuiGouR[4].z,\
			ptt->SuiGouR[5].x,ptt->SuiGouR[5].y,ptt->SuiGouR[5].z,mLC,strJDstyle);
	}
	else
	{
		PLuQianHuPo ptt;
		ptt= new LuQianHuPo;
		ptt->Huponums_L =0;
		ptt->Huponums_R =0;
		PtS_HuPo[m_currentSchemeIndexs].Add(ptt);
	}
	
}

//�ھھ�������Z�p��]�m���������
void CDesingScheme::GetBirdgeLGcordinate(float BridgeLGJJ)
{
	double x1,z1,y1,x2,y2,z2;
	double x3,z3,y3,x4,y4,z4;
	CString m_style;
	
	BOOL bfirst=TRUE;
	float dx=0;
	PRailway3DCordinate pt;
	PTunnnelBridgeInformation tempBridgeInformation;
	
	long N;

	for (long i=0;i<PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		
		m_style=PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//���I����
		//�p�G���I�����O"���ٰ_�I,���ٲ��I"��"���٤����I",��ܸ��I�O�o�ݩ���ٳ���
		if(m_style=="���ٰ_�I" || m_style=="���ٲ��I" || m_style=="���٤����I") 
		{	
			
			//�o���e�I�u����Y�����I���T������
			x1=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1;
			y1=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1;
			z1=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1;

			//�o��U�@�I�u����Y�����I���T������
			x2=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1;
			y2=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1;
			z2=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1;
			
			
			//�o���e�I�u����Y�k���I���T������
			x3=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2;
			y3=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2;
			z3=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2;
			
			//�o��U�@�I�u����Y�k���I���T������
			x4=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2;
			y4=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2;
			z4=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2;
		
			pt=new Railway3DCordinate;
			pt->x1 =x1;
			pt->y1 =y1;
			pt->z1 =z1;
			pt->x2 =x3;
			pt->y2 =y3;
			pt->z2 =z3;

			if(m_style=="���ٰ_�I") //�p�G�O"���ٰ_�I"
			{
				//�p����٫H��
				tempBridgeInformation=new TunnnelBridgeInformation;
				tempBridgeInformation->startIndex=i+1; //���ٰ_�I���ƾڰ_�I����
				tempBridgeInformation->StartLC=PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Lc; //���ٰ_�I���{
				
				tempBridgeInformation->StartLeftXYZ.x=pt->x1;//���ٰ_�I������x,y,z����
				tempBridgeInformation->StartLeftXYZ.y=pt->y1;
				tempBridgeInformation->StartLeftXYZ.z=pt->z1;
				tempBridgeInformation->StartRightXYZ.x=pt->x2;//���ٰ_�I�k����x,y,z����
				tempBridgeInformation->StartRightXYZ.y=pt->y2;
				tempBridgeInformation->StartRightXYZ.z=pt->z2;
				
			}
			else if(m_style=="���ٲ��I")//�p�G�O"���ٲ��I"
			{
				tempBridgeInformation->endIndex=i; //���ٲ��I���ƾڰ_�I����
				tempBridgeInformation->EndLC=PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Lc;//���ٲ��I���{
				
				tempBridgeInformation->EndLeftXYZ.x=pt->x1;//���ٲ��I������x,y,z����
				tempBridgeInformation->EndLeftXYZ.y=pt->y1;
				tempBridgeInformation->EndLeftXYZ.z=pt->z1;
				tempBridgeInformation->EndRightXYZ.x=pt->x2;//���ٲ��I�k����x,y,z����
				tempBridgeInformation->EndRightXYZ.y=pt->y2;
				tempBridgeInformation->EndRightXYZ.z=pt->z2;
				BridgeInfor[m_currentSchemeIndexs].Add(tempBridgeInformation); //�s�x���٫H��
			}
			
			//�p��(x1,y1,z1)t (x2,y2,z2)�����Z��,+0.0001�O���F����p��~�t
			float length=GetDistenceXY(x1,z1,x2,z2)+0.001;
			int nums=(int)((length+dx)/BridgeLGJJ);//�ھڨ��I�Z���M��������Z�p�����]�m���������
			for(int j=1;j<=nums;j++)
			{
				N++;
				float L=j*BridgeLGJJ-dx;
				pt=new Railway3DCordinate;

				//�u�ʤ����p��]�m����������I���T������
				pt->x1=x1+L/length*(x2-x1);
				pt->y1=y1+L/length*(y2-y1);
				pt->z1=z1+L/length*(z2-z1);
				
				//�u�ʤ����p��]�m�k��������I���T������
				pt->x2=x3+L/length*(x4-x3);
				pt->y2=y3+L/length*(y4-y3);
				pt->z2=z3+L/length*(z4-z3);

				PtS_BridgeLG3D[m_currentSchemeIndexs].Add(pt);//�s�x��������мƾ�
			}
			dx+=length-nums*BridgeLGJJ; //�Ѿl�Z��,�p�G<=0.01,�h�{����0
			if(dx<=0.01) dx=0;

			if(m_style=="���ٲ��I") //�p�G�O"���ٲ��I"
			{
				pt=new Railway3DCordinate; 
				pt->x1 =-1;   //=-1��ܷ�e���ٵ����лx
				pt->y1 =-1;
				pt->z1 =-1;
				pt->x2 =-1; 
				pt->y2 =-1;
				pt->z2 =-1;
				PtS_BridgeLG3D[m_currentSchemeIndexs].Add(pt);//�s�x��������мƾ�
			}
		}	
	}
		
}

 


float CDesingScheme::GetANgle(double x1, double z1, double x2, double z2)
{

	float mangle;
	float dx=x2-x1;
	float dz=z2-z1;
	float RotateAngle=0;
	float tempangle;
	if(fabs(dx)<=0.000001) 
	{
		if(dz<0)
			mangle=PAI/2.0;  
		else
			mangle=3/2.0*PAI;  
	
		RotateAngle=0;
	}  
	else
	{
		mangle=atan(fabs(dz/dx));
		tempangle=mangle;
		if(dx>=0 && dz<=0) 
		{
			mangle=mangle;
		//	RotateAngle=tempangle+PAI/2.0;
			RotateAngle=-(PAI/2.0-tempangle);
		}
		else if(dx<=0 && dz<=0) 
		{
			mangle=PAI-mangle;
			RotateAngle=PAI/2.0-tempangle;
		}
		else if(dx<=0 && dz>=0) 
		{
			mangle=PAI+mangle;
		//	RotateAngle=PAI/2.0+tempangle;
			RotateAngle=-(PAI/2.0-tempangle);
		}
		else if(dx>=0 && dz>=0) 
		{
			mangle=2*PAI-mangle;
		//	RotateAngle=PAI-tempangle;
			RotateAngle=(PAI/2.0-tempangle);
		}
	}
	
	RotateAngle=RotateAngle*180/3.1415926;
	return mangle*180/3.1415926;
	
}

 
 
 
 
 
void CDesingScheme::GetHs(double x0, double y0, double z0, float alfa, float mangle, int Style, double *px, double *py, double *pz)
{
	float L=0.1;
	float h1=-999;
	float hNew=-9999;
	float H0=y0;
	double xx,zz;
	while(fabs(h1-hNew)>0.01) 
	{
		h1=H0-L*sin(alfa);
		hNew=GetHBridgeHP(L,alfa,mangle,x0,z0,Style,&xx,&zz);
		L+=0.01;
	
		if(h1-hNew<0)
		{
			hNew=h1;
		}
		
	}
	if(fabs(h1-hNew)<0.01)	
	{
		*px=xx;
		*py=hNew;
		*pz=zz;
	
	}
	

}

float CDesingScheme::GetHBridgeHP(float L, float alfa, float mangle, double x0, double z0, int Style, double *xx, double *zz)
{
	float peita;
	double x,z;

    
	if(mangle>=0 && mangle<=PAI/2.0) 
	{
		peita=PAI/2-mangle;
		x=Style*L*cos(alfa)*cos(peita)+x0;
		z=Style*L*cos(alfa)*sin(peita)+z0;
	}
	else if(mangle>PAI/2.0 && mangle<=PAI)	
	{
		peita=mangle-PAI/2;
		x=Style*L*cos(alfa)*cos(peita)+x0;
		z=-Style*L*cos(alfa)*sin(peita)+z0;
	}
	else if(mangle>PAI&& mangle<=PAI*3/2.0)	
	{
		peita=PAI*3.0/2-mangle;
		x=-Style*L*cos(alfa)*cos(peita)+x0;
		z=-Style*L*cos(alfa)*sin(peita)+z0;
	}
	else if(mangle>PAI*3/2.0&& mangle<=PAI*2.0)	
	{
		peita=mangle-PAI*3.0/2;
		x=-Style*L*cos(alfa)*cos(peita)+x0;
		z=Style*L*cos(alfa)*sin(peita)+z0;
	}

	float mh=m_demInsert.GetHeightValue(x+theApp.m_DemLeftDown_x,-z+theApp.m_DemLeftDown_y,2);
	
	*xx=x;
	*zz=z;
	return mh;

}

//�ھھ��[���Z�p��]�m���[����
void CDesingScheme::GetBirdgeQDcordinate(float BridgeQDJJ)
{
	double x1,z1,y1,x2,y2,z2;
	double x3,z3,y3,x4,y4,z4;
	
	BOOL bFind=FALSE;
	float dx=0;
	PRailway3DCordinate pt;
	CString m_style,m_stylePre;

	float length=0;

	
	for (long i=0;i<PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		m_style=PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//���I����
		
		//�p�G���I�����O"���ٰ_�I,���ٲ��I"��"���٤����I",��ܸ��I�O�o�ݩ���ٳ���
		if(m_style=="���ٰ_�I" || m_style=="���ٲ��I" || m_style=="���٤����I") 
		{	

			if(m_style=="���ٰ_�I" && i>0 ) //�p�G�O"���ٰ_�I"
			{
					//�o��e�@�I�u����Y�����I���T������
					x1=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i-1)->x1;
					y1=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i-1)->y1;
					z1=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i-1)->z1;
					
					//�o���e�I�u����Y�����I���T������
					x2=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1;
					y2=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1;
					z2=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1;
					
					
					//�o��e�@�I�u����Y�k���I���T������
					x3=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i-1)->x2;
					y3=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i-1)->y2;
					z3=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i-1)->z2;
					
					//�o���e�I�u����Y�k���I���T������
					x4=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2;
					y4=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2;
					z4=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2;

					//�p��(x1,y1,z1)t (x2,y2,z2)�����Z��,+0.0001�O���F����p��~�t
					float templength=GetDistenceXY(x1,z1,x2,z2)+0.0001; 
					int Num=templength/BridgeQDJJ; //�ھڨ��I�Z���M���[���Z�p�����]�m�����[��
				
					for(int m=1;m<=Num;m++)
					{
						pt=new Railway3DCordinate;
						
						//�u�ʤ����p��]�m���[�I�����������������T������
						pt->x1=x1+(i*BridgeQDJJ)/templength*(x2-x1);
						pt->y1=y1+(i*BridgeQDJJ)/templength*(y2-y1);
						pt->z1=z1+(i*BridgeQDJJ)/templength*(z2-z1);
						
						
						//�u�ʤ����p��]�m���[�I���k�������������T������
						pt->x2=x3+(i*BridgeQDJJ)/templength*(x4-x3);
						pt->y2=y3+(i*BridgeQDJJ)/templength*(y4-y3);
						pt->z2=z3+(i*BridgeQDJJ)/templength*(z4-z3);

						//�ھ�DEM�����p�⥪�����������I���a�����{
						float h1=m_demInsert.GetHeightValue(pt->x1+theApp.m_DemLeftDown_x,-pt->z1+theApp.m_DemLeftDown_y,2);
						
						//�ھ�DEM�����p��k�����������I���a�����{
						float h2=m_demInsert.GetHeightValue(pt->x2+theApp.m_DemLeftDown_x,-pt->z2+theApp.m_DemLeftDown_y,2);
						float H=pt->y1-h1; //���[����(�ھڥ��������I�p��)
						if(H<(pt->y2-h2)) //�p�GH<pt->y2-h2(�ھڥk�������I�p�⪺����)
							H=pt->y2-h2;  //���s�p����[����			
						pt->QDHeight=H;//���[����
						/*
						�W�z�N�X�q����,���[���ר����k���p�⪺�̤j����.�Ҧp�����p��H=4.56,�k���p���oH=4.78,�h��H=4.78
						*/

						PtS_BridgeQD3D[m_currentSchemeIndexs].Add(pt); //�s�x���[�T������
						bFind=TRUE; //������
						
					}
					length=templength-BridgeQDJJ*Num;//�p��Ѿl�Z��
					if(fabs(length)<=0.001) //�p�G�Ѿl�Z�������<=0.001,�h�{����,���A�]�m���[
						length=0;
				
			}
			else  //�p�G�O"���ٲ��I"��"���٤����I"
			{
				
				//�o���e�I�u����Y�����I���T������
				x1=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1;
				y1=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1;
				z1=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1;
				
				//�o���e�I�u����Y�k���I���T������
				x2=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1;
				y2=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1;
				z2=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1;
				
				
				//�o���U�@�I�u����Y�����I���T������
				x3=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2;
				y3=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2;
				z3=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2;
				
				//�o���U�@�I�u����Y�k���I���T������
				x4=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2;
				y4=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2;
				z4=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2;

				//�p��(x1,y1,z1)t (x2,y2,z2)�����Z��,+0.0001�O���F����p��~�t
				float templength=GetDistenceXY(x1,z1,x2,z2)+0.0001;

				length+=templength; //��e���]�m���[�Z���֭p
				if(length>=BridgeQDJJ) //�p�G���I�Z���j����[���Z,��ܻݭn�b���I���]�m���[
				{
					pt=new Railway3DCordinate;
					
					
					//�u�ʤ����p��]�m���[�I�����������������T������
					pt->x1=x1+(templength-(length-BridgeQDJJ))/templength*(x2-x1);
					pt->y1=y1+(templength-(length-BridgeQDJJ))/templength*(y2-y1);
					pt->z1=z1+(templength-(length-BridgeQDJJ))/templength*(z2-z1);
					
					
					//�u�ʤ����p��]�m���[�I���k�������������T������
					pt->x2=x3+(templength-(length-BridgeQDJJ))/templength*(x4-x3);
					pt->y2=y3+(templength-(length-BridgeQDJJ))/templength*(y4-y3);
					pt->z2=z3+(templength-(length-BridgeQDJJ))/templength*(z4-z3);
					
					//�ھ�DEM�����p�⥪�����������I���a�����{
					float h1=m_demInsert.GetHeightValue(pt->x1+theApp.m_DemLeftDown_x,-pt->z1+theApp.m_DemLeftDown_y,2);
					
					//�ھ�DEM�����p��k�����������I���a�����{
					float h2=m_demInsert.GetHeightValue(pt->x2+theApp.m_DemLeftDown_x,-pt->z2+theApp.m_DemLeftDown_y,2);
					float H=pt->y1-h1;//���[����(�ھڥ��������I�p��)
					if(H<(pt->y2-h2))//�p�GH<pt->y2-h2(�ھڥk�������I�p�⪺����)
						H=pt->y2-h2;	//���s�p����[����		
					pt->QDHeight=H;//���[����

					PtS_BridgeQD3D[m_currentSchemeIndexs].Add(pt);//�s�x���[�T������
					
					length=length-BridgeQDJJ;//�p��s���Ѿl�Z��length
					if(fabs(length)<=0.001)//�p�G�Ѿl�Z�������<=0.001,�h�{����,���A�]�m���[
						length=0;
					bFind=TRUE; 
				}
			}
		}
		else
		{
			if(bFind==TRUE) 
				length=0;
		}
	
	}
}


 //�N�襤�����z�v���b����Ȥ�ϤWø�s
void CDesingScheme::drawBitmapFormFile(CString BitmapFilePath, CDC *pDC, CRect rect)
{
	HANDLE   filehandle=::LoadImage(NULL,BitmapFilePath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);  //�[���v����� 
	if(filehandle!=NULL)   //�p�G�[�����\
	{   
		CBitmap   bmp;   
		if(bmp.Attach(filehandle))   
		{   
			BITMAP   bmpInfo;   
			bmp.GetBitmap(&bmpInfo);   //����귽��ϫH��
			CDC   dcMemory;   
			dcMemory.CreateCompatibleDC(pDC);   //�Ыؤ@�ӻP�S�w�]�Ƴ����@�P�����s�]�Ƴ���
			dcMemory.SelectObject(&bmp);   //���bmp�ﹳ����w���]�ƤW�U�����Ҥ�,�ӷs�ﹳ�������e���ۦP��������H
			//�]�m���w�]�����Ҥ�����ϩԦ��Ҧ�. HALFTONE�G�N���x�ΰϤ��������M�g��ؼЯx�ΰϪ����������A
			//�л\�ؼй��������@���C��P���������C�Ⱶ��C
			
			//StretchBlt():���x�Τ��ƻs�@�Ӧ�Ϩ�ؼЯx��,���n�ɫ��ثe�ؼг]�Ƴ]�m���Ҧ��i��Ϲ����Ԧ������Y�C
			pDC->StretchBlt(rect.left,rect.top,rect.Width(),rect.Height(),&dcMemory,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,SRCCOPY);   
			bmp.Detach();   //�P��bmp�ﹳ
		}   
	}   
}


 
void CDesingScheme::GetZhenMucordinate(float ZhenMuJJ, float Railwaywidth)
{
	
	int y=PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize();
	
	
	if(PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()<=0)
		return;
	
	PRailway3DCordinate pt;
    
	
	double x1,z1,y1,x2,y2,z2;
	double x3,z3,y3,x4,y4,z4;
	
	float dx=0;
	float mclae;	
 
	mclae=0;
	


	for (long i=0;i<PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		
			
			x1=PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1+mclae*(PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1-PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1);
			y1=PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1+mclae*(PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1-PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1);
			z1=PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1+mclae*(PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1-PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1);
	
			x2=PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1+mclae*(PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1-PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1);
			y2=PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1+mclae*(PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1-PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
			z2=PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1+mclae*(PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1-PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			
			
			
			x3=PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2+mclae*(PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2-PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2);
			y3=PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2+mclae*(PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2-PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2);
			z3=PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2+mclae*(PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2-PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2);
			
			x4=PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2+mclae*(PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2-PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2);
			y4=PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2+mclae*(PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2-PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
			z4=PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2+mclae*(PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2-PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2);


			if(i==0) 
			{
				pt=new Railway3DCordinate;
					
				pt->x1 =x1;
				pt->y1 =y1;
				pt->z1 =z1;
				pt->x2 =x3;
				pt->y2 =y3;
				pt->z2 =z3;
				
				PtS_RailwayZhenMu[m_currentSchemeIndexs].Add(pt);
				dx=0;
			}
			
			float length=PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->Lc-PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Lc;
		
				int nums=(int)((length+dx)/ZhenMuJJ);
				for(int j=1;j<=nums;j++)
				{
					
					float L=j*ZhenMuJJ-dx;
					pt=new Railway3DCordinate;
					
					pt->x1=x1+L/length*(x2-x1);
					pt->y1=y1+L/length*(y2-y1);
					pt->z1=z1+L/length*(z2-z1);
					pt->x2=x3+L/length*(x4-x3);
					pt->y2=y3+L/length*(y4-y3);
					pt->z2=z3+L/length*(z4-z3);
					PtS_RailwayZhenMu[m_currentSchemeIndexs].Add(pt);
				}

				dx+=length-nums*ZhenMuJJ;
				if(fabs(dx)<=0.01) dx=0;
	}	

}


 
void CDesingScheme::GetTieGuicordinate( float Railwaywidth, float m_GDwidth)
{
	PRailway3DCordinate pt;
    
	double x1,z1,y1,x2,y2,z2;
	float L=(Railwaywidth-m_GDwidth)/2;

	for(long i=0;i<myDesingScheme.PtS_RailwayZhenMu[m_currentSchemeIndexs].GetSize();i++)
	{
		x1=myDesingScheme.PtS_RailwayZhenMu[m_currentSchemeIndexs].GetAt(i)->x1;
		y1=myDesingScheme.PtS_RailwayZhenMu[m_currentSchemeIndexs].GetAt(i)->y1;
		z1=myDesingScheme.PtS_RailwayZhenMu[m_currentSchemeIndexs].GetAt(i)->z1;
		x2=myDesingScheme.PtS_RailwayZhenMu[m_currentSchemeIndexs].GetAt(i)->x2;
		y2=myDesingScheme.PtS_RailwayZhenMu[m_currentSchemeIndexs].GetAt(i)->y2;
		z2=myDesingScheme.PtS_RailwayZhenMu[m_currentSchemeIndexs].GetAt(i)->z2;

		pt=new Railway3DCordinate;
		
		pt->x1=x1+L/Railwaywidth*(x2-x1);
		pt->y1=y1+L/Railwaywidth*(y2-y1);
		pt->z1=z1+L/Railwaywidth*(z2-z1);
		
		pt->x2=x2+L/Railwaywidth*(x1-x2);
		pt->y2=y2+L/Railwaywidth*(y1-y2);
		pt->z2=z2+L/Railwaywidth*(z1-z2);
		PtS_RailwayTieGui[m_currentSchemeIndexs].Add(pt);
	}
}


//�p����Y�P�b�������I���� 
void CDesingScheme::GetDMJD(double x1, double y1, double z1, double x2, double y2, double z2,float L,float h0, double x0,double z0,int TW, int LeftRight,\
							double tx0,double ty0,double tz0,double tx1,double ty1,double tz1,double mLC,CString strJDstyle)
{
	double x11,y11,z11,x12,y12,z12;
	double x21,y21,z21,x22,y22,z22;
	double xx,yy,zz;
	float L1,mangle,Afla;
	float dx=x2-x1; //
	float dz=z2-z1;
	float hNew;

	PLuQianHuPo ptt;
	ptt= new LuQianHuPo;

	//�ھڳW�d�]�m�������@�Y�ƭ�
	float h1=8; //1����Y�Y��
	float h2=12;//2����Y�Y��
	float b2=1;//1����Y���x�e��
	float b3=1;//2����Y���x�e��
	float m1=1; //1����Y�Y�v
	float m2=1.5;//2����Y�Y�v
	float hqm=0.75; //�@�𪺩Y�v
	
	
	//�ھڳW�d�]�m�������@�Y�ƭ�
	float Lt_h1=6;  //1����Y�Y��
	float Lt_h2=12;//2����Y�Y��
	float Lt_m1=1.5; //1����Y�Y�v
	float Lt_m2=1.75;//2����Y�Y�v
	float Lt_b=2.0; //��Y���x�e��
	
	float m_threshodld=0.001;  //�]�w���H��

	if(LeftRight==-1) //������Y
	{
		if(TW==-1) //�p�G�O����
		{
 
			L1=h1*m1+L;
			Afla=atan(1.0/m1);
			Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
			hNew=GetH(h1*m1,Afla,mangle,x11,z11,LeftRight,&xx,&zz);//�p������a���I���{��
		
			//�p�G�ھڳ]�m��1����Y����(h1)�M1����Y�Y�v(m1),�p�⪺�a���I���{�P
			//��Y�I�M�Y�������t�����<=�]�w���H��m_threshodld
			if(fabs(hNew-h0-h1)<=m_threshodld) 
			{
				ptt->Huponums_L =1; //�����u��1����Y,��Y�Ƭ�1
				//�O�������U��Y�I�����ЩM�����ݩʭ�

				//��Y0�I���T������
				ptt->HuPo_L[0].Hp[0].x =tx0; 
				ptt->HuPo_L[0].Hp[0].y =ty0;
				ptt->HuPo_L[0].Hp[0].z =tz0;
			
				//��Y1�I���T������
				ptt->HuPo_L[0].Hp[1].x =tx1;
				ptt->HuPo_L[0].Hp[1].y =ty1;
				ptt->HuPo_L[0].Hp[1].z =tz1;
				
				//��Y2�I���T������
				ptt->HuPo_L[0].Hp[2].x =xx;
				ptt->HuPo_L[0].Hp[2].y =hNew;
				ptt->HuPo_L[0].Hp[2].z =zz;

				ptt->HuPo_L[0].h=8; //��Y���Y��
				ptt->HuPo_L[0].m=1; //��Y���Y�v
				ptt->HuPo_L[0].style=0; //��Y������(�@�Y)

				PtS_HuPo[m_currentSchemeIndexs].Add(ptt); //�s�x��Y�ƾ�
			}
			else if(hNew-h0-h1<0) //�p�G���t�p��0,��ܳ]�m1�ũY��h1��,�Y�}�I�w�g�i�J�a���H�U�F,���Y��h1�]�m�j�F,�Y�u�]�m<h1�����Y���N�i�H�F
			{
			
				//���N�p����Y�Y�}�P�a�������I����
				GetBpJD(ty1, Afla, mangle, tx1, tz1,TW,-1,&xx,&yy,&zz);
				
				ptt->Huponums_L =1; //�����u��1����Y,��Y�Ƭ�1
				
				//��Y0�I���T������
				ptt->HuPo_L[0].Hp[0].x =tx0;
				ptt->HuPo_L[0].Hp[0].y =ty0;
				ptt->HuPo_L[0].Hp[0].z =tz0;
				
				//��Y1�I���T������
				ptt->HuPo_L[0].Hp[1].x =tx1;
				ptt->HuPo_L[0].Hp[1].y =ty1;
				ptt->HuPo_L[0].Hp[1].z =tz1;

				//��Y2�I���T������
				ptt->HuPo_L[0].Hp[2].x =xx;
				ptt->HuPo_L[0].Hp[2].y =yy;
				ptt->HuPo_L[0].Hp[2].z =zz;

				ptt->HuPo_L[0].h=yy-h0; //��Y���Y��
				ptt->HuPo_L[0].m=1;  //��Y���Y�v
				ptt->HuPo_L[0].style=0;  //��Y������(�@�Y)

				PtS_HuPo[m_currentSchemeIndexs].Add(ptt);//�s�x��Y�ƾ�
				
			}
			//�p�G���t�j��0,��ܳ]�m1�ũY��h1��,�Y�}�I���P�a���ۥ�,�ݭn�~��]�m�G����Y
			else if(hNew-h0-h1>0)
			{
				
				L1=h1*m1+L;
				Afla=atan(1.0/m1);
				Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
				hNew=h0+h1;
			
				//�s�x1����Y���ƾ�

				//��Y0�I���T������
				ptt->HuPo_L[0].Hp[0].x =tx0;
				ptt->HuPo_L[0].Hp[0].y =ty0;
				ptt->HuPo_L[0].Hp[0].z =tz0;

				//��Y1�I���T������
				ptt->HuPo_L[0].Hp[1].x =tx1;
				ptt->HuPo_L[0].Hp[1].y =ty1;
				ptt->HuPo_L[0].Hp[1].z =tz1;
			
				//��Y2�I���T������
				ptt->HuPo_L[0].Hp[2].x =x11;
				ptt->HuPo_L[0].Hp[2].y =hNew;
				ptt->HuPo_L[0].Hp[2].z =z11;

				ptt->HuPo_L[0].h=8;//��Y���Y��
				ptt->HuPo_L[0].m=1; //��Y���Y�v
				ptt->HuPo_L[0].style=0;  //��Y������(�@�Y)
			
				//�p��2����Y���ƾ�
				L1=L+h1*m1+b2;
				Afla=atan(1.0/m2);
				Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
				hNew=GetH(h2*m2,Afla,mangle,x11,z11,LeftRight,&xx,&zz);
				//�p�G�ھڳ]�m��2����Y����(h2)�M2����Y�Y�v(m2),�p�⪺�a���I���{�P
				//��Y�I�M�Y�������t�����<=�]�w���H��m_threshodld
				if(fabs(hNew-h0-h1-h2)<=m_threshodld) 	
				{
					//�s�x2����Y���ƾ�

					ptt->Huponums_L =2; //������Y�Ƭ�2
					
					//2����Y0�I������=1����Y2�I������(�Y2����Y��1����Y��2�I)
					ptt->HuPo_L[1].Hp[0].x =ptt->HuPo_L[0].Hp[2].x;
					ptt->HuPo_L[1].Hp[0].y =ptt->HuPo_L[0].Hp[2].y;
					ptt->HuPo_L[1].Hp[0].z =ptt->HuPo_L[0].Hp[2].z;
					
					//2����Y1�I������
					ptt->HuPo_L[1].Hp[1].x =x11;
					ptt->HuPo_L[1].Hp[1].y =ptt->HuPo_L[1].Hp[0].y;
					ptt->HuPo_L[1].Hp[1].z =z11;
					
					//2����Y2�I������
					ptt->HuPo_L[1].Hp[2].x =xx;
					ptt->HuPo_L[1].Hp[2].y =hNew;
					ptt->HuPo_L[1].Hp[2].z =zz;

					ptt->HuPo_L[1].h=12;//2����Y���Y��
					ptt->HuPo_L[1].m=1;//2����Y���Y�v
					ptt->HuPo_L[1].b=b2;//2����Y�����x�e��
					ptt->HuPo_L[1].style=0; //��Y������(�@�Y)

					PtS_HuPo[m_currentSchemeIndexs].Add(ptt);//�s�x��Y�ƾ�
				}
				//�p�G�ھڳ]�m��2����Y����(h2)�M2����Y�Y�v(m2),�p�⪺�a���I���{�P
				//��Y�I�M�Y�������t<0,��ܳ]�m2�ũY��h2��,
				//�Y�}�I�w�g�i�J�a���H�U�F,���Y��h2�]�m�j�F,�ݭn���s�p�����ӳ]�m��2�ũY��
				else if(hNew-h0-h1-h2<0)
				{
					Afla=atan(1.0/m2);
					GetBpJD(h0+h1, Afla, mangle, x11, z11,TW,-1,&xx,&yy,&zz);//�p����Y�I�P�a�ѽu�����I���� 
					ptt->Huponums_L =2; //������Y�Ƭ�2
				
					//2����Y0�I������=1����Y2�I������(�Y2����Y��1����Y��2�I)
					ptt->HuPo_L[1].Hp[0].x =ptt->HuPo_L[0].Hp[2].x;
					ptt->HuPo_L[1].Hp[0].y =ptt->HuPo_L[0].Hp[2].y;
					ptt->HuPo_L[1].Hp[0].z =ptt->HuPo_L[0].Hp[2].z;
					
					//2����Y1�I������
					ptt->HuPo_L[1].Hp[1].x =x11;
					ptt->HuPo_L[1].Hp[1].y =ptt->HuPo_L[1].Hp[0].y;
					ptt->HuPo_L[1].Hp[1].z =z11;

					//2����Y2�I������
					ptt->HuPo_L[1].Hp[2].x =xx;
					ptt->HuPo_L[1].Hp[2].y =yy;
					ptt->HuPo_L[1].Hp[2].z =zz;

					ptt->HuPo_L[1].h=yy-h0-h1;//2����Y���Y��
					ptt->HuPo_L[1].m=1; //2����Y���Y�v
					ptt->HuPo_L[1].b=0;//2����Y�����x�e��=0(�����P�a���ۥ�)
					ptt->HuPo_L[1].style=0;//��Y������(�@�Y)

					PtS_HuPo[m_currentSchemeIndexs].Add(ptt); //�s�x��Y�ƾ�
				}

				//�p�G�ھڳ]�m��2����Y����(h2)�M2����Y�Y�v(m2),�p�⪺�a���I���{�P
				//��Y�I�M�Y�������t>0,��ܳ]�m2�ũY��h2��,
				//�Y�}�I������a��,�h����2����Y,�b1����Y�W�����]�m�@��
				else if(hNew-h0-h1-h2>0)
				{

					float hh=5; //�@���l�̤p����=5
					float hNew2=999;

					//���N�p���@��P�a�������I
					while(hNew2-(h0+h1+hh)>5 && hh<15)
					{
						Afla=atan(1.0/hqm);
					
						L1=h1*m1+hh*hqm+L+b2+b3;
						Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
						Afla=atan(1.0/m2);
						GetBpJD(h0+h1+hh, Afla, mangle, x11, z11,TW,-1,&xx,&yy,&zz);
						hNew2=yy;
						float ddh=hNew2-(h0+h1+hh);
						hh++;
					}
					
					//�b�@��W�]�m��Y,
					ptt->HuPo_L[2].Hp[1].x =x11;
					ptt->HuPo_L[2].Hp[1].z =z11;
					
					ptt->Huponums_L =3; //������Y�Ƭ�3

					//�ק�2����Y0�I������
					ptt->HuPo_L[1].Hp[0].x =ptt->HuPo_L[0].Hp[2].x;
					ptt->HuPo_L[1].Hp[0].y =ptt->HuPo_L[0].Hp[2].y;
					ptt->HuPo_L[1].Hp[0].z =ptt->HuPo_L[0].Hp[2].z;

					//�p��2����Y1�I������
					L1=h1*m1+L+b2;
					Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
					ptt->HuPo_L[1].Hp[1].x =x11;
					ptt->HuPo_L[1].Hp[1].y =ptt->HuPo_L[1].Hp[0].y;
					ptt->HuPo_L[1].Hp[1].z =z11;
					
					//�p��2����Y2�I������
					L1=h1*m1+hh*hqm+L+b2;
					Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
					ptt->HuPo_L[1].Hp[2].x =x11;
					ptt->HuPo_L[1].Hp[2].y =h0+h1+hh;
					ptt->HuPo_L[1].Hp[2].z =z11;
					
					ptt->HuPo_L[1].h=hh;//2����Y���Y��
					ptt->HuPo_L[1].m=1;//2����Y���Y�v
					ptt->HuPo_L[1].b=0;//2����Y�����x�e��
					ptt->HuPo_L[1].style=1;//��Y������(�@��)
					
					//����Y0�I������
					ptt->HuPo_L[2].Hp[0].x =ptt->HuPo_L[1].Hp[2].x;
					ptt->HuPo_L[2].Hp[0].y =ptt->HuPo_L[1].Hp[2].y;
					ptt->HuPo_L[2].Hp[0].z =ptt->HuPo_L[1].Hp[2].z;
					
					ptt->HuPo_L[2].Hp[1].y =ptt->HuPo_L[2].Hp[0].y;
				
					//3����Y2�I������
					ptt->HuPo_L[2].Hp[2].x =xx;
					ptt->HuPo_L[2].Hp[2].y =yy;
					ptt->HuPo_L[2].Hp[2].z =zz;
					ptt->HuPo_L[2].h=hNew2-(h0+h1+hh);//3����Y���Y��
					ptt->HuPo_L[2].m=1;//3����Y���Y�v
					ptt->HuPo_L[2].b=0;//2����Y�����x�e��=0(�����P�a���ۥ�)
					ptt->HuPo_L[2].style=0;//�@�Y

					PtS_HuPo[m_currentSchemeIndexs].Add(ptt); //�s�x��Y�ƾ�
				}
			}
			
		}
 		else if(TW==1)//����
		{
 			L1=Lt_h1*Lt_m1+L;
			Afla=atan(1.0/Lt_m1);
			Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
			hNew=GetH(Lt_h1*Lt_m1,Afla,mangle,x11,z11,LeftRight,&xx,&zz);
			if(fabs(h0-hNew-Lt_h1)<=m_threshodld)
			{
				ptt->Huponums_L =1;
				ptt->HuPo_L[0].Hp[0].x =tx0;
				ptt->HuPo_L[0].Hp[0].y =ty0;
				ptt->HuPo_L[0].Hp[0].z =tz0;
				ptt->HuPo_L[0].Hp[1].x =tx1;
				ptt->HuPo_L[0].Hp[1].y =ty1;
				ptt->HuPo_L[0].Hp[1].z =tz1;
				ptt->HuPo_L[0].Hp[2].x =xx;
				ptt->HuPo_L[0].Hp[2].y =hNew;
				ptt->HuPo_L[0].Hp[2].z =zz;
				ptt->HuPo_L[0].h=8;
				ptt->HuPo_L[0].m=Lt_m1;
				ptt->HuPo_L[0].style=0;
				
				PtS_HuPo[m_currentSchemeIndexs].Add(ptt);
			}
			else if(h0-hNew-Lt_h1<0)
			{
			
				GetBpJD(ty1, Afla, mangle, tx1, tz1,TW,-1,&xx,&yy,&zz);
				ptt->Huponums_L =1;
				ptt->HuPo_L[0].Hp[0].x =tx0;
				ptt->HuPo_L[0].Hp[0].y =ty0;
				ptt->HuPo_L[0].Hp[0].z =tz0;
				ptt->HuPo_L[0].Hp[1].x =tx1;
				ptt->HuPo_L[0].Hp[1].y =ty1;
				ptt->HuPo_L[0].Hp[1].z =tz1;
				ptt->HuPo_L[0].Hp[2].x =xx;
				ptt->HuPo_L[0].Hp[2].y =yy;
				ptt->HuPo_L[0].Hp[2].z =zz;
				ptt->HuPo_L[0].h=h0-yy;
				ptt->HuPo_L[0].m=Lt_m1;
				ptt->HuPo_L[0].style=0;
				PtS_HuPo[m_currentSchemeIndexs].Add(ptt);
				
			}
			else if(h0-hNew-Lt_h1>0)//�@���@�Y�S���P�a���ۥ�,����a�����{,�ݭn�~��h���@�Y
			{
				L1=Lt_h1*Lt_m1+L;
				Afla=atan(1.0/Lt_m1);
				Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
				hNew=h0-Lt_h1;
			
				ptt->HuPo_L[0].Hp[0].x =tx0;
				ptt->HuPo_L[0].Hp[0].y =ty0;
				ptt->HuPo_L[0].Hp[0].z =tz0;
				ptt->HuPo_L[0].Hp[1].x =tx1;
				ptt->HuPo_L[0].Hp[1].y =ty1;
				ptt->HuPo_L[0].Hp[1].z =tz1;
				ptt->HuPo_L[0].Hp[2].x =x11;
				ptt->HuPo_L[0].Hp[2].y =hNew;
				ptt->HuPo_L[0].Hp[2].z =z11;
				ptt->HuPo_L[0].h=Lt_h1;
				ptt->HuPo_L[0].m=Lt_m1;
				ptt->HuPo_L[0].style=0;
				
				L1=Lt_h1*Lt_m1+Lt_h2*Lt_m2+L+Lt_b;
			
				Afla=atan(1.0/Lt_m2);  
				Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
				hNew=GetH(Lt_h2*Lt_m2,Afla,mangle,x11,z11,LeftRight,&xx,&zz);
				if(fabs(h0-hNew-Lt_h1-Lt_h2)<=m_threshodld)
				{
					ptt->Huponums_L =2;
					ptt->HuPo_L[1].Hp[0].x =ptt->HuPo_L[0].Hp[2].x;
					ptt->HuPo_L[1].Hp[0].y =ptt->HuPo_L[0].Hp[2].y;
					ptt->HuPo_L[1].Hp[0].z =ptt->HuPo_L[0].Hp[2].z;
					ptt->HuPo_L[1].Hp[1].x =x11;
					ptt->HuPo_L[1].Hp[1].y =ptt->HuPo_L[1].Hp[0].y;
					ptt->HuPo_L[1].Hp[1].z =z11;
					ptt->HuPo_L[1].Hp[2].x =xx;
					ptt->HuPo_L[1].Hp[2].y =hNew;
					ptt->HuPo_L[1].Hp[2].z =zz;
					ptt->HuPo_L[1].h=12;
					ptt->HuPo_L[1].m=Lt_m2;
					ptt->HuPo_L[1].b=Lt_b;
					ptt->HuPo_L[1].style=0;
					PtS_HuPo[m_currentSchemeIndexs].Add(ptt);
				}
				else if(h0-hNew-Lt_h1-Lt_h2<0)
				{
					L1=Lt_h1*Lt_m1+L+Lt_b;
					Afla=atan(1.0/Lt_m2);  
					Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
					GetBpJD(h0-Lt_h1, Afla, mangle, x11, z11,TW,-1,&xx,&yy,&zz);
					ptt->Huponums_L =2;
					ptt->HuPo_L[1].Hp[0].x =ptt->HuPo_L[0].Hp[2].x;
					ptt->HuPo_L[1].Hp[0].y =ptt->HuPo_L[0].Hp[2].y;
					ptt->HuPo_L[1].Hp[0].z =ptt->HuPo_L[0].Hp[2].z;
					ptt->HuPo_L[1].Hp[1].x =x11;
					ptt->HuPo_L[1].Hp[1].y =ptt->HuPo_L[1].Hp[0].y;
					ptt->HuPo_L[1].Hp[1].z =z11;
					ptt->HuPo_L[1].Hp[2].x =xx;
					ptt->HuPo_L[1].Hp[2].y =yy;
					ptt->HuPo_L[1].Hp[2].z =zz;
					ptt->HuPo_L[1].h=ptt->HuPo_L[1].Hp[0].y-yy;
					ptt->HuPo_L[1].m=Lt_m2;
					ptt->HuPo_L[1].b=Lt_b;
					ptt->HuPo_L[1].style=0;
					PtS_HuPo[m_currentSchemeIndexs].Add(ptt);
				}
				
				
				else if(h0-hNew-Lt_h1-Lt_h2>0)
				{
					
					float hh=3;
				
					float hNew2=-999;
					while(h0-(Lt_h1+hh+hNew2)>6 && hh<10)
					{
						Afla=atan(1.0/Lt_m2);
					
						L1=Lt_h1*Lt_m1+hh*Lt_m2+L+Lt_b+0.6;
						Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
					
					
						Afla=atan(1.0/0.25); 
					
						GetBpJD(h0-Lt_h1-hh, Afla, mangle, x11, z11,TW,-1,&xx,&yy,&zz);
						hNew2=yy;
						float ddh=h0-Lt_h1-hh-hNew2;
						hh++;
					}
					
					ptt->HuPo_L[2].Hp[1].x =x11;
					ptt->HuPo_L[2].Hp[1].z =z11;
					
					ptt->Huponums_L =3;
					ptt->HuPo_L[1].Hp[0].x =ptt->HuPo_L[0].Hp[2].x;
					ptt->HuPo_L[1].Hp[0].y =ptt->HuPo_L[0].Hp[2].y;
					ptt->HuPo_L[1].Hp[0].z =ptt->HuPo_L[0].Hp[2].z;
					L1=Lt_h1*Lt_m1+L+Lt_b;
					Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
					ptt->HuPo_L[1].Hp[1].x =x11;
					ptt->HuPo_L[1].Hp[1].y =ptt->HuPo_L[1].Hp[0].y;
					ptt->HuPo_L[1].Hp[1].z =z11;
					
					L1=Lt_h1*Lt_m1+hh*Lt_m2+L;
					Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
					ptt->HuPo_L[1].Hp[2].x =x11;
					ptt->HuPo_L[1].Hp[2].y =h0-Lt_h1-hh;
					ptt->HuPo_L[1].Hp[2].z =z11;
					
					ptt->HuPo_L[1].h=hh;
					ptt->HuPo_L[1].m=Lt_m1;
					ptt->HuPo_L[1].b=0;
					ptt->HuPo_L[1].style=0;
					
					ptt->HuPo_L[2].Hp[0].x =ptt->HuPo_L[1].Hp[2].x;
					ptt->HuPo_L[2].Hp[0].y =ptt->HuPo_L[1].Hp[2].y;
					ptt->HuPo_L[2].Hp[0].z =ptt->HuPo_L[1].Hp[2].z;
 
					ptt->HuPo_L[2].Hp[1].y =ptt->HuPo_L[2].Hp[0].y;
 
					ptt->HuPo_L[2].Hp[2].x =xx;
					ptt->HuPo_L[2].Hp[2].y =yy;
					ptt->HuPo_L[2].Hp[2].z =zz;
					ptt->HuPo_L[2].h=h0-h1-hh-hNew2;
					ptt->HuPo_L[2].m=0.25;
					ptt->HuPo_L[2].b=0;
					ptt->HuPo_L[2].style=2;

					PtS_HuPo[m_currentSchemeIndexs].Add(ptt);
				}
			}
		}
		else if(TW==0)//����
		{
			ptt->Huponums_L =1;
			ptt->HuPo_L[0].Hp[0].x =tx0;
			ptt->HuPo_L[0].Hp[0].y =ty0;
			ptt->HuPo_L[0].Hp[0].z =tz0;
			ptt->HuPo_L[0].Hp[1].x =tx0;
			ptt->HuPo_L[0].Hp[1].y =ty0;
			ptt->HuPo_L[0].Hp[1].z =tz0;
			ptt->HuPo_L[0].Hp[2].x =tx0;
			ptt->HuPo_L[0].Hp[2].y =ty0;
			ptt->HuPo_L[0].Hp[2].z =tz0;
			
		}

		long MN=PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;
		PtS_HuPo[m_currentSchemeIndexs].GetAt(MN)->TW_left=TW;
		PtS_HuPo[m_currentSchemeIndexs].GetAt(MN)->Lc=mLC;
		PtS_HuPo[m_currentSchemeIndexs].GetAt(MN)->strJDStyle=strJDstyle;
	}
    else if(LeftRight==1) //�k
	{
		if(TW==-1)
		{
  
			L1=h1*m1+L;
			Afla=atan(1.0/m1);
			Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
			hNew=GetH(h1*m1,Afla,mangle,x12,z12,LeftRight,&xx,&zz);
			if(fabs(hNew-h0-h1)<=m_threshodld)
			{
				ptt=PtS_HuPo[m_currentSchemeIndexs].GetAt(PtS_HuPo[m_currentSchemeIndexs].GetSize()-1);
				ptt->Huponums_R =1;
				ptt->HuPo_R[0].Hp[0].x =tx0;
				ptt->HuPo_R[0].Hp[0].y =ty0;
				ptt->HuPo_R[0].Hp[0].z =tz0;
				ptt->HuPo_R[0].Hp[1].x =tx1;
				ptt->HuPo_R[0].Hp[1].y =ty1;
				ptt->HuPo_R[0].Hp[1].z =tz1;
				ptt->HuPo_R[0].Hp[2].x =xx;
				ptt->HuPo_R[0].Hp[2].y =hNew;
				ptt->HuPo_R[0].Hp[2].z =zz;
				ptt->HuPo_R[0].h=8;
				ptt->HuPo_R[0].m=1;
				ptt->HuPo_R[0].style=0;

			
			}
			else if(hNew-h0-h1<0)
			{
			
				GetBpJD(ty1, Afla, mangle, tx1, tz1,TW,1,&xx,&yy,&zz);
				ptt=PtS_HuPo[m_currentSchemeIndexs].GetAt(PtS_HuPo[m_currentSchemeIndexs].GetSize()-1);
				ptt->Huponums_R =1;
				ptt->HuPo_R[0].Hp[0].x =tx0;
				ptt->HuPo_R[0].Hp[0].y =ty0;
				ptt->HuPo_R[0].Hp[0].z =tz0;
				ptt->HuPo_R[0].Hp[1].x =tx1;
				ptt->HuPo_R[0].Hp[1].y =ty1;
				ptt->HuPo_R[0].Hp[1].z =tz1;
				ptt->HuPo_R[0].Hp[2].x =xx;
				ptt->HuPo_R[0].Hp[2].y =yy;
				ptt->HuPo_R[0].Hp[2].z =zz;
				ptt->HuPo_R[0].h=yy-h0;
				ptt->HuPo_R[0].m=1;
				ptt->HuPo_R[0].style=0;
			
				
			}
			else if(hNew-h0-h1>0)
			{
				
				L1=h1*m1+L;
				Afla=atan(1.0/m1);
				Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
				hNew=h0+h1;
			

				ptt=PtS_HuPo[m_currentSchemeIndexs].GetAt(PtS_HuPo[m_currentSchemeIndexs].GetSize()-1);

				ptt->HuPo_R[0].Hp[0].x =tx0;
				ptt->HuPo_R[0].Hp[0].y =ty0;
				ptt->HuPo_R[0].Hp[0].z =tz0;
				ptt->HuPo_R[0].Hp[1].x =tx1;
				ptt->HuPo_R[0].Hp[1].y =ty1;
				ptt->HuPo_R[0].Hp[1].z =tz1;
				ptt->HuPo_R[0].Hp[2].x =x12;
				ptt->HuPo_R[0].Hp[2].y =hNew;
				ptt->HuPo_R[0].Hp[2].z =z12;
				ptt->HuPo_R[0].h=8;
				ptt->HuPo_R[0].m=1;
				ptt->HuPo_R[0].style=0;
				
			
				
 
 
 
			
				L1=L+h1*m1+b2;
			
				Afla=atan(1.0/1.5);
				Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
				hNew=GetH(h2*m2,Afla,mangle,x12,z12,LeftRight,&xx,&zz);
				if(fabs(hNew-h0-h1-h2)<=m_threshodld)
				{
					ptt->Huponums_R =2;
					ptt->HuPo_R[1].Hp[0].x =ptt->HuPo_R[0].Hp[2].x;
					ptt->HuPo_R[1].Hp[0].y =ptt->HuPo_R[0].Hp[2].y;
					ptt->HuPo_R[1].Hp[0].z =ptt->HuPo_R[0].Hp[2].z;
					ptt->HuPo_R[1].Hp[1].x =x12;
					ptt->HuPo_R[1].Hp[1].y =ptt->HuPo_R[1].Hp[0].y;
					ptt->HuPo_R[1].Hp[1].z =z12;
					ptt->HuPo_R[1].Hp[2].x =xx;
					ptt->HuPo_R[1].Hp[2].y =hNew;
					ptt->HuPo_R[1].Hp[2].z =zz;
					ptt->HuPo_R[1].h=12;
					ptt->HuPo_R[1].m=1;
					ptt->HuPo_R[1].b=b2;
					ptt->HuPo_R[1].style=0;
				
				}
				else if(hNew-h0-h1-h2<0)
				{
					Afla=atan(1.0/1.5);
					GetBpJD(h0+h1, Afla, mangle, x12, z12,TW,1,&xx,&yy,&zz);
					ptt->Huponums_R =2;
					ptt->HuPo_R[1].Hp[0].x =ptt->HuPo_R[0].Hp[2].x;
					ptt->HuPo_R[1].Hp[0].y =ptt->HuPo_R[0].Hp[2].y;
					ptt->HuPo_R[1].Hp[0].z =ptt->HuPo_R[0].Hp[2].z;
					ptt->HuPo_R[1].Hp[1].x =x12;
					ptt->HuPo_R[1].Hp[1].y =ptt->HuPo_R[1].Hp[0].y;
					ptt->HuPo_R[1].Hp[1].z =z12;
					ptt->HuPo_R[1].Hp[2].x =xx;
					ptt->HuPo_R[1].Hp[2].y =yy;
					ptt->HuPo_R[1].Hp[2].z =zz;
					ptt->HuPo_R[1].h=yy-h0-h1;
					ptt->HuPo_R[1].m=1;
					ptt->HuPo_R[1].b=0;
					ptt->HuPo_R[1].style=0;
				
				}
				
				
				else if(hNew-h0-h1-h2>0)
				{
				
					float hh=5;
				
					float hNew2=999;
					while(hNew2-(h0+h1+hh)>5 && hh<15)
					{
						Afla=atan(1.0/hqm);
					
						L1=h1*m1+hh*hqm+L+b2+b3;
						Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
					
					
						Afla=atan(1.0/m2);
					
						GetBpJD(h0+h1+hh, Afla, mangle, x12, z12,TW,1,&xx,&yy,&zz);
						hNew2=yy;
						float ddh=hNew2-(h0+h1+hh);
						hh++;
					}
					
					ptt->HuPo_R[2].Hp[1].x =x12;
					ptt->HuPo_R[2].Hp[1].z =z12;
					
					ptt->Huponums_R =3;
					ptt->HuPo_R[1].Hp[0].x =ptt->HuPo_R[0].Hp[2].x;
					ptt->HuPo_R[1].Hp[0].y =ptt->HuPo_R[0].Hp[2].y;
					ptt->HuPo_R[1].Hp[0].z =ptt->HuPo_R[0].Hp[2].z;
					L1=h1*m1+L+b2;
					Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
					ptt->HuPo_R[1].Hp[1].x =x12;
					ptt->HuPo_R[1].Hp[1].y =ptt->HuPo_R[1].Hp[0].y;
					ptt->HuPo_R[1].Hp[1].z =z12;
					
					L1=h1*m1+hh*hqm+L+b2;
					Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
					ptt->HuPo_R[1].Hp[2].x =x12;
					ptt->HuPo_R[1].Hp[2].y =h0+h1+hh;
					ptt->HuPo_R[1].Hp[2].z =z12;
					
					ptt->HuPo_R[1].h=hh;
					ptt->HuPo_R[1].m=1;
					ptt->HuPo_R[1].b=0;
					ptt->HuPo_R[1].style=1;
					
					ptt->HuPo_R[2].Hp[0].x =ptt->HuPo_R[1].Hp[2].x;
					ptt->HuPo_R[2].Hp[0].y =ptt->HuPo_R[1].Hp[2].y;
					ptt->HuPo_R[2].Hp[0].z =ptt->HuPo_R[1].Hp[2].z;
 
					ptt->HuPo_R[2].Hp[1].y =ptt->HuPo_R[2].Hp[0].y;
 
					ptt->HuPo_R[2].Hp[2].x =xx;
					ptt->HuPo_R[2].Hp[2].y =yy;
					ptt->HuPo_R[2].Hp[2].z =zz;
					ptt->HuPo_R[2].h=hNew2-(h0+h1+hh);
					ptt->HuPo_R[2].m=1;	
					ptt->HuPo_R[2].b=0;
					ptt->HuPo_R[2].style=0;

				
				}
			}
		}
		else if(TW==1)
		{
 
			L1=Lt_h1*Lt_m1+L;
			Afla=atan(1.0/Lt_m1);
			Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
			hNew=GetH(Lt_h1*Lt_m1,Afla,mangle,x12,z12,LeftRight,&xx,&zz);
			if(fabs(h0-hNew-Lt_h1)<=m_threshodld)
			{
				ptt=PtS_HuPo[m_currentSchemeIndexs].GetAt(PtS_HuPo[m_currentSchemeIndexs].GetSize()-1);
				ptt->Huponums_R =1;
				ptt->HuPo_R[0].Hp[0].x =tx0;
				ptt->HuPo_R[0].Hp[0].y =ty0;
				ptt->HuPo_R[0].Hp[0].z =tz0;
				ptt->HuPo_R[0].Hp[1].x =tx1;
				ptt->HuPo_R[0].Hp[1].y =ty1;
				ptt->HuPo_R[0].Hp[1].z =tz1;
				ptt->HuPo_R[0].Hp[2].x =xx;
				ptt->HuPo_R[0].Hp[2].y =hNew;
				ptt->HuPo_R[0].Hp[2].z =zz;
				ptt->HuPo_R[0].h=8;
				ptt->HuPo_R[0].m=Lt_m1;
				ptt->HuPo_R[0].style=0;
				
			
			}
			else if(h0-hNew-Lt_h1<0)
			{
			
				GetBpJD(ty1, Afla, mangle, tx1, tz1,TW,1,&xx,&yy,&zz);
				ptt=PtS_HuPo[m_currentSchemeIndexs].GetAt(PtS_HuPo[m_currentSchemeIndexs].GetSize()-1);
				ptt->Huponums_R =1;
				ptt->HuPo_R[0].Hp[0].x =tx0;
				ptt->HuPo_R[0].Hp[0].y =ty0;
				ptt->HuPo_R[0].Hp[0].z =tz0;
				ptt->HuPo_R[0].Hp[1].x =tx1;
				ptt->HuPo_R[0].Hp[1].y =ty1;
				ptt->HuPo_R[0].Hp[1].z =tz1;
				ptt->HuPo_R[0].Hp[2].x =xx;
				ptt->HuPo_R[0].Hp[2].y =yy;
				ptt->HuPo_R[0].Hp[2].z =zz;
				ptt->HuPo_R[0].h=h0-yy;
				ptt->HuPo_R[0].m=Lt_m1;
				ptt->HuPo_R[0].style=0;
			
				
			}
			else if(h0-hNew-Lt_h1>0)
			{
				ptt=PtS_HuPo[m_currentSchemeIndexs].GetAt(PtS_HuPo[m_currentSchemeIndexs].GetSize()-1);

				
				L1=Lt_h1*Lt_m1+L;
				Afla=atan(1.0/Lt_m1);
				Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
				hNew=h0-Lt_h1;
			
				ptt->HuPo_R[0].Hp[0].x =tx0;
				ptt->HuPo_R[0].Hp[0].y =ty0;
				ptt->HuPo_R[0].Hp[0].z =tz0;
				ptt->HuPo_R[0].Hp[1].x =tx1;
				ptt->HuPo_R[0].Hp[1].y =ty1;
				ptt->HuPo_R[0].Hp[1].z =tz1;
				ptt->HuPo_R[0].Hp[2].x =x12;
				ptt->HuPo_R[0].Hp[2].y =hNew;
				ptt->HuPo_R[0].Hp[2].z =z12;
				ptt->HuPo_R[0].h=Lt_h1;
				ptt->HuPo_R[0].m=Lt_m1;
				ptt->HuPo_R[0].style=0;
				
				
 
 
 
				
				
				L1=Lt_h1*Lt_m1+Lt_h2*Lt_m2+L+Lt_b;
			
				Afla=atan(1.0/Lt_m2);  
				Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
				hNew=GetH(Lt_h2*Lt_m2,Afla,mangle,x12,z12,LeftRight,&xx,&zz);
				if(fabs(h0-hNew-Lt_h1-Lt_h2)<=m_threshodld)
				{
					ptt->Huponums_R =2;
					ptt->HuPo_R[1].Hp[0].x =ptt->HuPo_R[0].Hp[2].x;
					ptt->HuPo_R[1].Hp[0].y =ptt->HuPo_R[0].Hp[2].y;
					ptt->HuPo_R[1].Hp[0].z =ptt->HuPo_R[0].Hp[2].z;
					ptt->HuPo_R[1].Hp[1].x =x12;
					ptt->HuPo_R[1].Hp[1].y =ptt->HuPo_R[1].Hp[0].y;
					ptt->HuPo_R[1].Hp[1].z =z12;
					ptt->HuPo_R[1].Hp[2].x =xx;
					ptt->HuPo_R[1].Hp[2].y =hNew;
					ptt->HuPo_R[1].Hp[2].z =zz;
					ptt->HuPo_R[1].h=12;
					ptt->HuPo_R[1].m=Lt_m2;
					ptt->HuPo_R[1].b=Lt_b;
					ptt->HuPo_R[1].style=0;
				
				}
				else if(h0-hNew-Lt_h1-Lt_h2<0)
				{
					L1=Lt_h1*Lt_m1+L+Lt_b;
					Afla=atan(1.0/Lt_m2);  
					Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
					GetBpJD(h0-Lt_h1, Afla, mangle, x12, z12,TW,1,&xx,&yy,&zz);
					ptt->Huponums_R =2;
					ptt->HuPo_R[1].Hp[0].x =ptt->HuPo_R[0].Hp[2].x;
					ptt->HuPo_R[1].Hp[0].y =ptt->HuPo_R[0].Hp[2].y;
					ptt->HuPo_R[1].Hp[0].z =ptt->HuPo_R[0].Hp[2].z;
					ptt->HuPo_R[1].Hp[1].x =x12;
					ptt->HuPo_R[1].Hp[1].y =ptt->HuPo_R[1].Hp[0].y;
					ptt->HuPo_R[1].Hp[1].z =z12;
					ptt->HuPo_R[1].Hp[2].x =xx;
					ptt->HuPo_R[1].Hp[2].y =yy;
					ptt->HuPo_R[1].Hp[2].z =zz;
					ptt->HuPo_R[1].h=ptt->HuPo_R[1].Hp[0].y-yy;
					ptt->HuPo_R[1].m=Lt_m2;
					ptt->HuPo_R[1].b=Lt_b;
					ptt->HuPo_R[1].style=0;
				
				}
				
				
				else if(h0-hNew-Lt_h1-Lt_h2>0)
				{
				
					float hh=3;
				
					float hNew2=-999;
					while(h0-(Lt_h1+hh+hNew2)>6 && hh<10)
					{
						Afla=atan(1.0/Lt_m2);
					
						L1=Lt_h1*Lt_m1+hh*Lt_m2+L+Lt_b+0.6;
						Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
					
					
						Afla=atan(1.0/0.25); 
				
						GetBpJD(h0-Lt_h1-hh, Afla, mangle, x12, z12,TW,1,&xx,&yy,&zz);
						hNew2=yy;
						float ddh=h0-Lt_h1-hh-hNew2;
						hh++;
					}
					
					ptt->HuPo_R[2].Hp[1].x =x12;
					ptt->HuPo_R[2].Hp[1].z =z12;
					
					ptt->Huponums_R =3;
					ptt->HuPo_R[1].Hp[0].x =ptt->HuPo_R[0].Hp[2].x;
					ptt->HuPo_R[1].Hp[0].y =ptt->HuPo_R[0].Hp[2].y;
					ptt->HuPo_R[1].Hp[0].z =ptt->HuPo_R[0].Hp[2].z;
					L1=Lt_h1*Lt_m1+L+Lt_b;
					Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
					ptt->HuPo_R[1].Hp[1].x =x12;
					ptt->HuPo_R[1].Hp[1].y =ptt->HuPo_R[1].Hp[0].y;
					ptt->HuPo_R[1].Hp[1].z =z12;
					
					L1=Lt_h1*Lt_m1+hh*Lt_m2+L;
					Get3DCorrdinate(x1,y1,z1,x2,y2,z2,dx,dz,L1,&x11,&y11,&z11,&x12,&y12,&z12,&x21,&y21,&z21,&x22,&y22,&z22,&mangle);
					ptt->HuPo_R[1].Hp[2].x =x12;
					ptt->HuPo_R[1].Hp[2].y =h0-Lt_h1-hh;
					ptt->HuPo_R[1].Hp[2].z =z12;
					
					ptt->HuPo_R[1].h=hh;
					ptt->HuPo_R[1].m=Lt_m1;
					ptt->HuPo_R[1].b=0;
					ptt->HuPo_R[1].style=0;
					
					ptt->HuPo_R[2].Hp[0].x =ptt->HuPo_R[1].Hp[2].x;
					ptt->HuPo_R[2].Hp[0].y =ptt->HuPo_R[1].Hp[2].y;
					ptt->HuPo_R[2].Hp[0].z =ptt->HuPo_R[1].Hp[2].z;
 
					ptt->HuPo_R[2].Hp[1].y =ptt->HuPo_R[2].Hp[0].y;
 
					ptt->HuPo_R[2].Hp[2].x =xx;
					ptt->HuPo_R[2].Hp[2].y =yy;
					ptt->HuPo_R[2].Hp[2].z =zz;
					ptt->HuPo_R[2].h=h0-h1-hh-hNew2;
					ptt->HuPo_R[2].m=0.25;
					ptt->HuPo_R[2].b=0;
					ptt->HuPo_R[2].style=2;

				
				}
			}
		}
		else if(TW==0)//����
		{
			Sleep(0);
			ptt->Huponums_R =1;
			ptt->HuPo_R[0].Hp[0].x =tx0;
			ptt->HuPo_R[0].Hp[0].y =ty0;
			ptt->HuPo_R[0].Hp[0].z =tz0;
			ptt->HuPo_R[0].Hp[1].x =tx0;
			ptt->HuPo_R[0].Hp[1].y =ty0;
			ptt->HuPo_R[0].Hp[1].z =tz0;
			ptt->HuPo_R[0].Hp[2].x =tx0;
			ptt->HuPo_R[0].Hp[2].y =ty0;
			ptt->HuPo_R[0].Hp[2].z =tz0;
			
		}
		
		long MN=PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;
		PtS_HuPo[m_currentSchemeIndexs].GetAt(MN)->TW_right=TW;
		
	}

}


 

void CDesingScheme::GetHpD(double x, double y, double z, float mAngle, float mHpangle,double *ax,double *ay,double *az)
{
	double tx,tz;
	float peita;
	
	float L=0;
	float h1=999;
	float hNew=-9999;
	float m_bc=0.2;
	float DerC=0.05;
	while(fabs(h1-hNew)>DerC) 
	{
	//	ty=y-L*sin(mHpangle);
		h1=y-L*sin(mHpangle);
		
		if(mAngle>=0 && mAngle<=PAI/2.0) //1�H
		{
			
			peita=mAngle;
			tx=x+L*cos(mHpangle)*cos(peita);
			tz=z-L*cos(mHpangle)*sin(peita);
		}
		else if(mAngle>PAI/2.0 && mAngle<=PAI)	
		{
			peita=PAI-mAngle;
			tx=x-L*cos(mHpangle)*cos(peita);
			tz=z-L*cos(mHpangle)*sin(peita);
		}
		else if(mAngle>PAI&& mAngle<=PAI*3/2.0)	
		{
			peita=mAngle-PAI;
			tx=x-L*cos(mHpangle)*cos(peita);
			tz=z+L*cos(mHpangle)*sin(peita);
		}
		else if(mAngle>PAI*3/2.0&& mAngle<=PAI*2.0)	
		{
			peita=2*PAI-mAngle;
			tx=x+L*cos(mHpangle)*cos(peita);
			tz=z+L*cos(mHpangle)*sin(peita);
		}
		hNew=m_demInsert.GetHeightValue(tx+theApp.m_DemLeftDown_x,-tz+theApp.m_DemLeftDown_y,2);
		L+=m_bc;
		if(h1-hNew<0)
		{
			hNew=h1;
			break;
		}
	}
	*ax=tx;
	*ay=hNew;
	*az=tz;
}

/*
�Ѽƻ����G
TotalHeight�G�G�D�`����    Archeight�G�G�D�꩷����   WallHeight�G�G�D���𰪫�
Width�G�G�D�e��   ArcSegmentNumber�G�G�D�꩷���q��
*/
//�D�G�D�_�����I���ЩM�G�D�����H��
void CDesingScheme::GetTunnelcordinate(float TotalHeight, float Archeight, float WallHeight, float Width,  int ArcSegmentNumber)
{
	PRailway3DTunnnel pt;//�s�x�G�D�I
	PTunnnelBridgeInformation tempTunnnelInfor; //�s�x�G�D�H��
	
	double x1,z1,y1;
	double x3,z3,y3;
	
	if(PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetSize()<=0) //�p�G��e����٨S���u�����u�ƾ�,��^
		return;
	
	
	CString m_style;
	
	int index=0;
	//�ھڧ����I�����`���P�_�G�D
	for (long i=0;i<PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		//��e�u�����u�I������
		m_style=PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;

		//�p�G�I������"�G�D�_�I","�G�D���I"��"�G�D�����I",�Y���I���G�D�������I
		if(m_style=="�G�D�_�I" || m_style=="�G�D���I" || m_style=="�G�D�����I") 
		{	
			//�����G�D����U���I����
			x1=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1;
			y1=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1;
			z1=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1;
			
			//�k���G�D����U���I����
			x3=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2;
			y3=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2;
			z3=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2;
			
			pt=new Railway3DTunnnel;
			
			//�G�D��������U���I����
			pt->x1 =x1;
			pt->y1 =y1;
			pt->z1 =z1;
			
			//�G�D�k������U���I����
			pt->x2 =x3;
			pt->y2 =y3;
			pt->z2 =z3;
			
			if(m_style=="�G�D�_�I") //�p�G�O"�G�D�_�I"
			{
				pt->Tunnnelindex=index; 
				index++;
				tempTunnnelInfor=new TunnnelBridgeInformation;
				tempTunnnelInfor->startIndex=i+1; //�O����e�G�D���_�I�b�u�������I���Ǹ�
				tempTunnnelInfor->StartLC=PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Lc; //��e�G�D���_�I���{
				
			}
			
			PtS_Tunnel3D[m_currentSchemeIndexs].Add(pt);//�[�J�G�D���k�����I�ƾ�
			
			float mAngle;
			//�p���G�D���ݶ꩷�������I
			//�G�D���ݶ꩷��{����k�O,�ĥξ���{�ھ�ArcSegmentNumber�����I�ƭp��զ����ݶ꩷�U�����I���T������
			//�o�ǦU�����I�U�����I�s���_��,�c���G�D���ݶ꩷.
			GetTunnelArcCordinate( TotalHeight,  Archeight,  WallHeight,  Width,  ArcSegmentNumber,pt->x1,pt->y1+WallHeight,pt->z1,pt->x2,pt->y2+WallHeight,pt->z2,&mAngle);
	
			if(m_style=="�G�D�_�I")
			{				
				tempTunnnelInfor->mStartangle=mAngle;//�G�D�}���i�f����
			}
			else if(m_style=="�G�D���I")
			{
				tempTunnnelInfor->mEndAngle=mAngle; //�G�D�}���X�f����
				tempTunnnelInfor->endIndex=i+1;//�O����e�G�D�����I�b�u�������I���Ǹ�
				tempTunnnelInfor->EndLC=PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Lc;//��e�G�D�����I���{
				TunnelInfor[m_currentSchemeIndexs].Add(tempTunnnelInfor);//�s�x��e�G�D�H��
			}

			
			if(m_style=="�G�D���I") //�p�G�O"�G�D���I"
			{
				pt=new Railway3DTunnnel; 
				pt->x1 =-1;  //-1��ܳo�O�G�D�X�f��
				pt->y1 =-1;  //-1��ܳo�O�G�D�X�f��
				pt->z1 =-1;	 //-1��ܳo�O�G�D�X�f��
				pt->x2 =-1;  //-1��ܳo�O�G�D�X�f��
				pt->y2 =-1;	 //-1��ܳo�O�G�D�X�f��
				pt->z2 =-1;	 //-1��ܳo�O�G�D�X�f��
				PtS_Tunnel3D[m_currentSchemeIndexs].Add(pt); //�s�x�G�D�ƾ�
			}
			
		}
	}
}

//�p���G�D���ݶ꩷�������I
//�G�D���ݶ꩷��{����k�O,�ĥξ���{�ھ�ArcSegmentNumber�����I�ƭp��զ����ݶ꩷�U�����I���T������
//�o�ǦU�����I�U�����I�s���_��,�c���G�D���ݶ꩷.
/*
�Ѽƻ����G
TotalHeight�G�G�D�`����    Archeight�G�G�D�꩷����   WallHeight�G�G�D���𰪫�
Width�G�G�D�e��   ArcSegmentNumber�G�G�D�꩷���q��
(x1,y1,z1):�G�D�������𩳧���   (x2,y2,z2):�G�D�k�����𩳧���
*mAngle:��^���{�G�D�_�������V
*/
void CDesingScheme::GetTunnelArcCordinate(float TotalHeight, float Archeight, float WallHeight, float Width, int ArcSegmentNumber, double x1, double y1, double z1, double x2, double y2, double z2,float *mAngle)
{

	// *mAngle:�G�D�}��������

	float a=Width;//�����b
	float b=Archeight;//���u�b
	double x0,y0,z0;
	
	//��꩷��ߧ���
	x0=(x1+x2)/2;
	y0=(y1+y2)/2;
	z0=(z1+z2)/2;

	//�k��
	//x=x0+a*cos�c
	//y=y0+b*sin�c

	//����
	//x=x0-a*cos�c
	//y=y0-b*sin�c
	
	//(1)�D�XP2(x2,y2,z2)�PP1(x1,y1,z1)�զ����u������ Peita;
	float dx=x2-x1;
	float dz=z2-z1;
	float Peita;
	
	if(fabs(dx)<=0.000001) 
	{
		Peita=0;
	}  
	else 
	{
		float mangle=atan(fabs(dz/dx));
		if(dx>=0 && dz<=0)  //1�H��
		{
			Peita=mangle;
		}
		else if(dx<=0 && dz<=0) //2�H�� 
		{
			Peita=PAI-mangle;
		}
		else if(dx<=0 && dz>=0) //3�H��
		{
			Peita=PAI+mangle;
		}
		else if(dx>=0 && dz>=0) //4�H��
		{
			Peita=2*PAI-mangle;
		}
		
	}

	*mAngle=Peita;

	//�D����	
	//�l�׳��O�@�b�����,�q�G�D�k�ݶ}�l�쥪�ݵ���
	PCordinate pt;
	
	float mangleDerta=PAI/ArcSegmentNumber;
	float Alfa;
	for(int i=0;i<=ArcSegmentNumber;i++)
	{
		Alfa=i*mangleDerta;
		pt=new Cordinate;
		if(i==0) //�p�G�O�_�I
		{
			pt->x=x2;
			pt->y=y2;
			pt->z=z2;
		}
		else if(i==ArcSegmentNumber) //�p�G�O���I
		{
			pt->x=x1;
			pt->y=y1;
			pt->z=z1;
			
		}
		else //�䥦�����������I
		{
			pt->x=x0+a*cos(Alfa)*cos(Peita); //�ھھ��x���Эp�⤽��,�p��[�꩷�����Ix����
			pt->y=y0+fabs(b*sin(Alfa));//�ھھ��y���Эp�⤽��,�p��[�꩷�����Iy����
			if(fabs(x2-x1)<=0.00001) //����G�D�_���PX�b����
				pt->z=z1+(ArcSegmentNumber-i)*(z2-z1)/ArcSegmentNumber*sin(Alfa);
			else
				pt->z=z1+(pt->x-x1)/(x2-x1)*(z2-z1);
			
		}
		//�s�x�p�⪺�G�D�_���꩷�����I������
		PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(PtS_Tunnel3D[m_currentSchemeIndexs].GetSize()-1)->tunnelArc.Add(pt);
	}

}

void CDesingScheme::InertHuPoPts()
{
	PLuQianHuPo ptt;
	double  x1,y1,z1,x2,y2,z2;
	
	PtSHuPoTemp.RemoveAll();

	for(long i=0;i<PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
	{
	
		int S1=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->TW_left;
		int S2=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->TW_left;

		int S3=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->TW_right;
		int S4=PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->TW_right;
		
		if(S1*S2<0 && S3*S4>0)//�������ջP�����۳s,�k�����ۦP����,�ݭn�i�椺���B�z
		{
			//(1)�索���i�椺��
			x1=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[0].Hp[0].x;
			y1=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[0].Hp[0].y;
			z1=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[0].Hp[0].z;

			x2=PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[0].Hp[0].x;
			y2=PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[0].Hp[0].y;
			z2=PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[0].Hp[0].z;

		    int N1=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_L-1;
			int N2=PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_L-1;
			//���{����Y���P�a�����I�B���{�P�u�����߽u���{�t��
			float H1=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N1].Hp[2].y;
			H1=H1-PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[0].Hp[0].y;

			float H2=PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N1].Hp[2].y;
			H2=H2-PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[0].Hp[0].y;
			
			float t=fabs((H1/H2));
		
			ptt= new LuQianHuPo;
			ptt->Huponums_L =1;
			ptt->TW_left=0;

			for(int k=0;k<=2;k++)
			{
				ptt->HuPo_L[0].Hp[k].x=(x1+t*x2)/(1+t);
				ptt->HuPo_L[0].Hp[k].y=(y1+t*y2)/(1+t);
				ptt->HuPo_L[0].Hp[k].z=(z1+t*z2)/(1+t);
			}

			N1=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_R-1;
			N2=PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_R-1;
			
			int mMinN=N1;
			if(mMinN>N2)
				mMinN=N2;

			//����Y�Ƴ̤֪��@�䬰���
			for(int j=0;j<=mMinN;j++)
			{
				for(int k=0;k<=2;k++)
				{
					x1=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[k].x;
					y1=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[k].y;
					z1=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[k].z;

					x2=PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[k].x;
					y2=PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[k].y;
					z2=PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[k].z;
					
					ptt->HuPo_R[j].Hp[k].x=(x1+t*x2)/(1+t);
					ptt->HuPo_R[j].Hp[k].y=(y1+t*y2)/(1+t);
					ptt->HuPo_R[j].Hp[k].z=(z1+t*z2)/(1+t);
				
				}
				ptt->HuPo_R[j].h=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].h;
				ptt->HuPo_R[j].m=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].m;
				ptt->HuPo_R[j].b=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].b;
				ptt->HuPo_R[j].style=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].style;
			}
			double L1=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Lc;
			double L2=PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Lc;
			ptt->Lc=(L1+t*L2)/(1+t);
			ptt->Huponums_R=mMinN+1;
			ptt->TW_right=S3;
			ptt->strJDStyle=PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->strJDStyle;

			PLuQianHuPoTemp ptempHPLQ;
			ptempHPLQ=new  LuQianHuPoTemp;
			ptempHPLQ->tempHuPo.Add(ptt);
			ptempHPLQ->InsertIndex=i+1;
			PtSHuPoTemp.Add(ptempHPLQ);
		//	PtS_HuPo[m_currentSchemeIndexs].InsertAt(i+1,ptt);
		}
	}

	for(i=0;i<PtSHuPoTemp.GetSize();i++)
	{
		ptt= new LuQianHuPo;
		
		ptt=*PtSHuPoTemp.GetAt(i)->tempHuPo.GetData();
		int index=PtSHuPoTemp.GetAt(i)->InsertIndex;
		PtS_HuPo[m_currentSchemeIndexs].InsertAt(index,ptt);
	}
}
//�ھڦa���I��x,y �H���p��Ӧa���I���ݪ��b�ζ�ID��
int CDesingScheme::GetBlockID(double x, double y)
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
