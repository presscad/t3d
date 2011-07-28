// GetDemInsertValue.cpp: implementation of the CGetDemInsertValue class.
 
 

#include "stdafx.h"
 
#include "GetDemInsertValue.h"
#include <WINDOWSX.H>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 
// Construction/Destruction
 


CGetDemInsertValue::CGetDemInsertValue()
{

}

CGetDemInsertValue::~CGetDemInsertValue()
{

}

 
float CGetDemInsertValue::GetDistence(double x1, double y1, double x2, double y2)
{
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

/*
�����I�c���DEM�O�b��l�ƾڧe�������G�A�έ즳�����DEM�K�פ����ɻݨϥΪ���k�C
��򥻫���O�G��ܤ@�X�z���ƾǼҫ��A�Q�Τw���I�W���H���D�X��ƪ��ݩw�Y�ơA
�M��D��W�h����I�W�����{�ȡC
�����I�c���DEM�ұĥΪ��O������k�A���Ȫ���k�ܦh�A�p���Z���[�v�k�B
�h���������k�B�˱���Ƥ����k�B�h����ƪk�����C�j�q�������ҩ��A
�ѩ��ڦa�Ϊ��D��í�ʡA���P��������k��DEM����רõL��ۼv�T�A
�D�n���M���l�ļ��I���K�שM���G�C
²��ӱ`�Ϊ����u�ʤ����k�M���u�ʦh���������k�C
*/


/*
 �u�ʤ���:

  �u�ʤ����O�N����椸�������ӤT����,�p��,�C�ӤT���ΥѤT�ӳ��I�T�w�ߤ@
  ����,�䤺���L�{�p�U:
  �Ĥ@�B:�����I�k�@��(normalisation)
  x0=(xp-x1)/g    y0=(yp-y1)/g
 */
float CGetDemInsertValue::LinearInterpolation(int mStartrow,int mStartCol,\
										  double mx,double my)
{
	int tr;
	float hh;
	double px,py;
	double x1,y1,h1,x2,y2,h2,x3,y3,h3,x4,y4,h4;
	x1=(mStartCol)*theApp.m_Cell_xwidth+theApp.m_DemLeftDown_x;
	y1=(mStartrow)*theApp.m_Cell_xwidth+theApp.m_DemLeftDown_y;
	h1=theApp.m_DemHeight[(mStartrow)*theApp.m_Dem_cols+(mStartCol)];
	x2=x1;y2=y1+theApp.m_Cell_xwidth;h2=theApp.m_DemHeight[(mStartrow+1)*theApp.m_Dem_cols+(mStartCol)];
	x3=x1+theApp.m_Cell_xwidth;y3=y2;h3=theApp.m_DemHeight[(mStartrow+1)*theApp.m_Dem_cols+(mStartCol+1)];
	x4=x3;y4=y1;h4=theApp.m_DemHeight[(mStartrow)*theApp.m_Dem_cols+(mStartCol+1)];
	
	px=(mx-x1)/theApp.m_Cell_xwidth;
	py=(my-y1)/theApp.m_Cell_xwidth;
	tr=0;
	if(px<py) tr=1;
	hh=tr*(h1+(h3-h2)*px+(h2-h1)*py)+(1-tr)*(h1+(h4-h1)*px+(h3-h4)*py);
	return hh;
		
}


 
float CGetDemInsertValue::biLinearInterpolation(int mStartrow, int mStartCol,double mx, double my)
{
	float hh;
	double px,py;
	double x1,y1,h1,x2,y2,h2,x3,y3,h3,x4,y4,h4;
	x1=(mStartCol)*theApp.m_Cell_xwidth+theApp.m_DemLeftDown_x;
	y1=(mStartrow)*theApp.m_Cell_xwidth+theApp.m_DemLeftDown_y;
	h1=theApp.m_DemHeight[(mStartrow)*theApp.m_Dem_cols+(mStartCol)];
	x2=x1;y2=y1+theApp.m_Cell_xwidth;h2=theApp.m_DemHeight[(mStartrow+1)*theApp.m_Dem_cols+(mStartCol)];
	x3=x1+theApp.m_Cell_xwidth;y3=y2;h3=theApp.m_DemHeight[(mStartrow+1)*theApp.m_Dem_cols+(mStartCol+1)];
	x4=x3;y4=y1;h4=theApp.m_DemHeight[(mStartrow)*theApp.m_Dem_cols+(mStartCol+1)];
	
	px=(mx-x1)/theApp.m_Cell_xwidth;
	py=(my-y1)/theApp.m_Cell_xwidth;

	hh=h1+(h4-h1)*px+(h2-h1)*py+(h1-h2+h3-h4)*px*py;
	return hh;
	
}

 
/*
�Z���˼ƭ������Ƥ�k�O�@�ӥ[�v�������Ȫk�A�i�H�i��T����
�Ϊ̶�ƪ��覡���ȡC�覸�ѼƱ�����v�Y�Ʀp���H�����}�@�Ӯ�
�����I�Z�����W�[�ӤU���C���@�Ӹ��j���覸�A���񪺼ƾ��I�Q
���w�@�Ӹ������v�����B�A���@�Ӹ��p���覸�A�v��������æa
���t���U�ƾ��I�C �p��@�Ӯ�����I�ɵ����@�ӯS�w�ƾ��I���v��
�P���w�覸���q���I���[���I���ӵ��I�Q�ᤩ�Z���˼Ʀ���ҡC��
�p��@�Ӯ�����I�ɡA�t�����v���O�@�Ӥ��ơA�Ҧ��v�����`�M��
��1.0�C��@���[���I�P�@�Ӯ�����I���X�ɡA���[���I�Q�����@��
��ڬ� 1.0 ���v���A�Ҧ��䥦�[���I�Q�����@�ӴX�G�� 0.0 ���v
���C�������A�ӵ��I�Q�ᵹ�P�[���I�@�P���ȡC�o�N�O�@�ӷǽT��
�ȡC �Z���˼ƪk���S�x���@�O�n�b����ϰ줺���ͳ�¶�[���I��m
��"����"�C�ζZ���˼Ʈ���Ʈɥi�H���w�@�Ӷ�ưѼơC�j��s��
��ưѼƫO�ҡA���@�ӯS�w�����I�A�S�������[���I�Q�ᤩ����
���v�ȡA�Y���[���I�P�ӵ��I���X�]�O�p���C��ưѼƳq�L�פäw
�Q���Ȫ�����ӭ��C"����"�v�T�C 
*/
float CGetDemInsertValue::InverseDistancetoaPower(int mStartrow,int mStartCol,\
				 double mx,double my, int mtotalPoins,float smoothParameter)
{
	float hh;

	/*smoothParameter:��ưѼơC�j��s����ưѼƫO�ҡA���@�ӯS�w�����I�A�S�������[���I�Q�ᤩ����
		���v�ȡA�Y���[���I�P�ӵ��I���X�]�O�p���C��ưѼƳq�L�פäw
		�Q���Ȫ�����ӭ��C"����"�v�T�C */
/*
	double S;
	long N;
	
	
	N=theApp.m_Dem_cols*theApp.m_Dem_Rows;
	S=(theApp.m_Dem_cols-1)*(theApp.m_Dem_Rows-1)*theApp.m_Cell_xwidth*theApp.m_Cell_xwidth;
	
	float m_RectongleWidth;
	int k=7;
	m_RectongleWidth=sqrt(S/N*k);
*/

	float dx=mx-mStartCol*theApp.m_Cell_xwidth-theApp.m_DemLeftDown_x;
	float dy=my-mStartrow*theApp.m_Cell_xwidth-theApp.m_DemLeftDown_y;
	
	int row1,col1,row2,col2;

/*
	
	if(dx<=theApp.m_Cell_xwidth/2.0)
	{
		col1=mStartCol-1;
		if(col1<0)
			col1=0;
		col2=mStartCol+1;
		if(col2>theApp.m_Dem_cols)
			col2=theApp.m_Dem_cols;
	}
	else
	{
		col1=mStartCol;
		col2=mStartCol+2;
		if(col2>theApp.m_Dem_cols)
			col2=theApp.m_Dem_cols;
		
	}

	if(dy<=theApp.m_Cell_xwidth/2.0)
	{
		row1=mStartrow-1;
		if(row1<0)
			row1=0;
		row2=mStartrow+1;
		if(row2>theApp.m_Dem_Rows)
			row2=theApp.m_Dem_Rows;
		
	}
	else
	{
		row1=mStartrow;
		row2=mStartrow+2;
		if(row2>theApp.m_Dem_Rows)
			row2=theApp.m_Dem_Rows;
		
	}*/

	
	
	
	if(dx<=theApp.m_Cell_xwidth/2.0)
	{
		col1=mStartCol-1;
		if(col1<0)
			col1=0;
		col2=mStartCol+1;
		if(col2>theApp.m_Dem_cols-1)
			col2=theApp.m_Dem_cols-1;
	}
	else
	{
		col1=mStartCol;
		col2=mStartCol+2;
		if(col2>theApp.m_Dem_cols-1)
			col2=theApp.m_Dem_cols-1;
		
	}
	
	if(dy<=theApp.m_Cell_xwidth/2.0)
	{
		row1=mStartrow-1;
		if(row1<0)
			row1=0;
		row2=mStartrow+1;
		if(row2>theApp.m_Dem_Rows-1)
			row2=theApp.m_Dem_Rows-1;
		
	}
	else
	{
		row1=mStartrow;
		row2=mStartrow+2;
		if(row2>theApp.m_Dem_Rows-1)
			row2=theApp.m_Dem_Rows-1;
		
	}
	

	int i,j;
	float distence;
	float PiZi,Pi,SumPi;
	PiZi=SumPi=0;

	for(i=row1;i<=row2;i++)
	{
		for(j=col1;j<=col2;j++)
		{
			distence=GetDistence(mx,my,j*theApp.m_Cell_xwidth+theApp.m_DemLeftDown_x,i*theApp.m_Cell_xwidth+theApp.m_DemLeftDown_y);
			if(distence==0)
				Pi=1.0*smoothParameter;
			else
				Pi=1.0/(distence*distence)*smoothParameter;
			SumPi+=Pi;
			PiZi+=Pi*theApp.m_DemHeight[i*theApp.m_Dem_cols+j];
		}
	}
	hh=PiZi*1.0/SumPi;

	return hh;

}



float CGetDemInsertValue::GetHeightValue(double x, double y, int method_style)
{
	int mStartrow,mStartCol;
	double mLx,mLy;
	float h;
	CString tt;
	

	if(x<theApp.m_DemLeftDown_x)
	{
		x=theApp.m_DemLeftDown_x;
		tt.Format("x���Фp��̤p���x��%.4f",theApp.m_DemLeftDown_x);
	//	::MessageBox(NULL,tt,"�������{",MB_ICONINFORMATION);
	//	return -9999;
	}
	
	if(x>theApp.m_DemRightUp_x)
	{
		x=theApp.m_DemRightUp_x;
		tt.Format("x���Фj��̤j���x��%.4f",theApp.m_DemRightUp_x);
	//	::MessageBox(NULL,tt,"�������{",MB_ICONINFORMATION);
	//	return -9999;
	}
	
	if(y<theApp.m_DemLeftDown_y)
	{
		y=theApp.m_DemLeftDown_y;
	//	tt.Format("y���Фp��̤p���y��%.4f",theApp.m_DemLeftDown_y);
	//	::MessageBox(NULL,tt,"�������{",MB_ICONINFORMATION);
	//	return -9999;
	}
	
	if(y>theApp.m_DemRightUp_y)
	{
		y=theApp.m_DemRightUp_y;
	//	tt.Format("y���Фj��̤j���y��%.4f",theApp.m_DemRightUp_y);
	//	::MessageBox(NULL,tt,"�������{",MB_ICONINFORMATION);
	//	return -9999;
	}
	
	mLx=x-theApp.m_DemLeftDown_x;
	mLy=y-theApp.m_DemLeftDown_y;
	
	mStartCol=(int)(mLx/theApp.m_Cell_xwidth);
	mStartrow=(int)(mLy/theApp.m_Cell_xwidth);
	
	if(mLx/theApp.m_Cell_xwidth==mStartCol && mLy/theApp.m_Cell_xwidth==mStartrow)
	{
		h=theApp.m_DemHeight[(mStartrow)*theApp.m_Dem_cols+(mStartCol)];
		return h;
	}

	
	switch(theApp.Insertmethod_style) 
	{
	case 0: 
		h=LinearInterpolation(mStartrow, mStartCol, x, y);
		break;
	case 1:
		
		h=biLinearInterpolation(mStartrow, mStartCol, x, y);
		break;
	case 2:
		
		h=InverseDistancetoaPower(mStartrow, mStartCol,x, y, 8, 0.9);
		break;
	case 3:
		h=trendFace(mStartrow, mStartCol, x, y);
		break;
	case 4:
		h=GetKrikingValue(mStartrow, mStartCol,x, y);
		break;
	}
	return  h;
}

/*
Kriging�ƾǼҫ��O�ѫn�D�q���a�z�ǮaP1G1Krige�����ޤJ���@�ت�
���w���L�{,�æ]���өR�W.���O�إߦb�ܲ���Ʋz�פ��R��¦�W,�靈��
�ϰ줺���ϰ���ܶq���ȶi��L�����u���p(best linearun biased estimator,BLUE)
���@�ؤ�k.�o�ؤ�k�P�ǲδ��Ȥ�k�����P���B,�b����p���[���˥��ƭȮ�,��
�ȦҼ{�ݴ����I�P�F���[���ƾ��I���Ŷ���m,�٦Ҽ{�F�U�F���I����
����m���Y,�ӥB�Q�Τw���[���ȪŶ����G�����c�S�I,�Ϩ���p��ǲΤ�k���T,
��ŦX��ڨåi�H�����קK�t�λ~�t���ͪ�"�̽�����".���b�a��έp�ǤιϹ��B�z
���譱��o�F�s�x���Ψ���a��,Kriging��k�N�O��C�@�ļ˭Ȥ��O�ᤩ�@�w���v�t
��,�A�i��[�v�����Ӧ��p�ݦ��ȫݦ��IV���u��ZV�����p��Z*K�O���p�줺n�Ӥw
����ZA���u�ʲզX:Zk=�U�faZa.Kriging��k�N�O�D�X���v�Y��KA(A=1,2,,,n),
��Z*K��ZV���L�����p�q,�B����p��t�̤p.
	�ѩ��s�ت��M���󤣦P,�٦��䥦�U�ئU�˪��J�̪����Ȥ�k"��ϰ���ܶq
	�A�q��ƥ��A���G�ɥi�ĥι�ƥ��A�J�̪��k;��ϰ���ܶq�s�b�}���{�H��
�i�ĥΪx�J�̪��k;��ϰ���ܶq���[�s�b�u��S���Ȯɥi�ĥΫ��ܧJ�̪��k;���
�@�լ������ϰ���ܶq�ݭn�ѨM�D�n�ܶq�M�䥦�ܶq����P���Ȱ��D�ɥi�ĥΨ�P
�J�̪��k"����ϥήɻݭn�ҹ�ϰ���ܶq���S�x,�H��γ̬��X�A�����Ȥ�k"
�䤤�̰�!�̭��n���γ̼s�����O���q�J�̪��k�C
*/
float CGetDemInsertValue::kriging(float dx, float dy, int mode, int item, float *Z_s, double *pos, float c0, float c1, float a, float *result)
{
	int dim,i,j,k;
   
    float *Cd,test_t;
  
    float *D,*tempD,*V,*temp;


 
    dim = item + 1;  

/* allocate V D array */
 
 
 
 

    V = (float *)GlobalAllocPtr(GMEM_MOVEABLE,sizeof (float) * dim * dim);
	D = (float *)GlobalAllocPtr(GMEM_MOVEABLE,sizeof (float) * dim );
	tempD= (float *)GlobalAllocPtr(GMEM_MOVEABLE,sizeof (float) * dim );
    temp = (float *)GlobalAllocPtr(GMEM_MOVEABLE,sizeof (float) * dim * dim);
/* allocate Cd array */
 
 
 
 

 
 

    Cd = (float *) GlobalAllocPtr(GMEM_MOVEABLE,sizeof (float) * dim * dim);
    
    /* caculate the distance between sample datas put into Cd array*/
    for ( i=0; i< dim-1 ;i++)
        for (j=i; j < dim-1 ; j++)
		{
            test_t =( pos[i*2]-pos[j*2] )*( pos[i*2]-pos[j*2])+
                    ( pos[i*2+1]-pos[j*2+1] )*( pos[i*2+1]-pos[j*2+1] );
            Cd[i*dim+j]=(float) sqrt( test_t );
        }
    
    for ( i=0; i< dim-1 ;i++) 
	{
        V[i*dim+dim-1]= 1;
        V[(dim-1)*(dim)+i]=1;
	}
    
    V[(dim-1)*(dim)+i] = 0;

	/* caculate the variogram of sample datas and put into  V array */
	/*�p��ļ��I�����ܶq[�ܤưO��]��,�é�J�Ʋ�V��,��ڤW�N�O�p��x�}������
	r11-----rnn
	
	r11		r12		...		r1n		1
	r21		r22		...		r2n		1
	...		...		...		...		1
	...		...		...		...		1
	...		...		...		...		1
	rn1		rn2		...		rnn     1
	1        1      ...      1      0
	*/
 
 
    for ( i=0; i< dim-1 ;i++)
        for (j=i; j < dim-1; j++) 
		{
            switch( mode )
			{
                case 1 : /* �y�μҦ� */
                         if ( Cd[i*dim+j] < a )
                            V[i*dim+j] = V[j*dim+i] = (float)(c0 + c1*(
                                         1.5*Cd[i*dim+j]/a - 0.5*(Cd[i*dim+j]/a)*
                                         (Cd[i*dim+j]/a)*(Cd[i*dim+j]/a)));
                         else
                            V[i*dim+j] = V[j*dim+i] = c0 + c1;
                         break;
                case 2 : /* ���ƼҦ� */
                         V[i*dim+j] = V[j*dim+i] =(float)( c0 + c1 *( 1 - 
                                      exp(-3*Cd[i*dim+j]/a) ));
                         break;
                case 3 : /* �����Ҧ� */
                         V[i*dim+j] = V[j*dim+i] = (float)(c0 + c1 *( 1 -
                                      exp(-3*Cd[i*dim+j]*Cd[i*dim+j]/a/a)));
                         break;
                default: V[i*dim+j] = V[j*dim+i] =(float)(1*Cd[i*dim+j]);
                         break;
            }
        }

    /* release Cd array */
   GlobalFreePtr(Cd);
    

    
	for(k=0;k<dim*dim;k++)
	   temp[k]=V[k];


	for(k=0;k<dim-1;k++)
	{
		test_t =( dx-pos[2*k] ) *( dx-pos[2*k] )+( dy-pos[2*k+1])*( dy-pos[2*k+1] );
		test_t = (float)(sqrt( test_t ));
		switch( mode )
		{
		case 1 : /* Spher mode */
			if ( test_t < a )
				D[k] = (float)(c0 + c1*(
				1.5*test_t/a - 0.5*(test_t/a)*
				(test_t/a)*(test_t/a)));
			else
				D[k] = c0 + c1;
			break;
		case 2 : /* Expon mode */
			D[k] = (float)(c0 + c1 *( 1 - 
				exp(-3*test_t/a)));
			break;
		case 3 : /* Gauss mode */
			D[k] = (float)(c0 + c1 *( 1 -
				exp(-3*test_t*test_t/a/a)));
			break;
		default: D[k]=(float)(1*test_t);
			break;
		}
		
	}
	D[dim-1]=1;
	
	
	
	for(k=0;k<dim*dim;k++)
		V[k]=temp[k];
	
	for(k=0;k<dim-1;k++)
			tempD[k]=D[k];

	agaus(V,D,dim);
	
		
	
	test_t=0;
	for(k=0;k<dim-1;k++)	
		test_t+=D[k]*Z_s[k];
	
	
	float m_squareError=0;
    for(k=0;k<dim-1;k++)
		m_squareError+=D[k]*tempD[k];
	m_squareError+=tempD[dim-1];
	

  
	CString tt;
	tt.Format("�p���=%f,��t=%f",test_t,m_squareError);
	AfxMessageBox(tt);

   
  
	GlobalFreePtr(V);
	GlobalFreePtr(D);
	GlobalFreePtr(tempD);
	GlobalFreePtr(temp);

	return test_t;

}
 
 
int CGetDemInsertValue::agaus(float *a, float *b, int n)
{ 
	int *js,l,k,i,j,is,p,q;
	float d,t;
	js=(int *)malloc(n*sizeof(int));
	l=1;
	for (k=0;k<=n-2;k++)
	{ 
		d=0.0;
		for (i=k;i<=n-1;i++)
			for (j=k;j<=n-1;j++)
			{ t=(float)fabs(a[i*n+j]);
			if (t>d) { d=t; js[k]=j; is=i;}
			}
			if (d+1.0==1.0) 
				l=0;
			else
			{ 
				if (js[k]!=k)
					for (i=0;i<=n-1;i++)
					{
						p=i*n+k; q=i*n+js[k];
						t=a[p]; a[p]=a[q]; a[q]=t;
					}
					if (is!=k)
					{ 
						for (j=k;j<=n-1;j++)
						{
							p=k*n+j; q=is*n+j;
							t=a[p]; a[p]=a[q]; a[q]=t;
						}
						t=b[k]; b[k]=b[is]; b[is]=t;
					}
			}
			if (l==0)
			{ 
				free(js);
				return(0);
			}
			
			d=a[k*n+k];
			for (j=k+1;j<=n-1;j++)
			{
				p=k*n+j; 
				a[p]=a[p]/d;
			}
			
			b[k]=b[k]/d;
			for (i=k+1;i<=n-1;i++)
			{ 
				for (j=k+1;j<=n-1;j++)
				{ 
					p=i*n+j;
					a[p]=a[p]-a[i*n+k]*a[k*n+j];
				}
				b[i]=b[i]-a[i*n+k]*b[k];
			}
	}
	d=a[(n-1)*n+n-1];
	if (fabs(d)+1.0==1.0)
	{ 
		free(js);
		return(0);
	}
	b[n-1]=b[n-1]/d;
	for (i=n-2;i>=0;i--)
	{ 
		t=0.0;
		for (j=i+1;j<=n-1;j++)
			t=t+a[i*n+j]*b[j];
		b[i]=b[i]-t;
	}
	js[n-1]=n-1;
	for (k=n-1;k>=0;k--)
		if (js[k]!=k)
		{ 
			t=b[k]; b[k]=b[js[k]]; b[js[k]]=t;
		}
		free(js);
		return(1);
}


float CGetDemInsertValue::GetKrikingValue(int mStartrow, int mStartCol, double mx, double my)
{
	long i,j;

	float dx=mx-mStartCol*theApp.m_Cell_xwidth-theApp.m_DemLeftDown_x;
	float dy=my-mStartrow*theApp.m_Cell_xwidth-theApp.m_DemLeftDown_y;
	
	int row1,col1,row2,col2;
	
	
	if(dx<=theApp.m_Cell_xwidth/2.0)
	{
		col1=mStartCol-1;
		col2=mStartCol+1;
		if(col2>theApp.m_Dem_cols)
			col2=theApp.m_Dem_cols;
	}
	else
	{
		col1=mStartCol;
		col2=mStartCol+2;
		if(col2>theApp.m_Dem_cols)
			col2=theApp.m_Dem_cols;
		
	}
	
	if(dy<=theApp.m_Cell_xwidth/2.0)
	{
		row1=mStartrow-1;
		row2=mStartrow+1;
		if(row2>theApp.m_Dem_Rows)
			row2=theApp.m_Dem_Rows;
		
	}
	else
	{
		row1=mStartrow;
		row2=mStartrow+2;
		if(row2>theApp.m_Dem_Rows)
			row2=theApp.m_Dem_Rows;
		
	}


	float C0,  C1,  a;
	float *Z_s;
	double *pos;
	float *result;
				
	
	C0=4;
	C1=0.8;
	a=2*theApp.m_Cell_xwidth;
	
	int mode=1;
    int item=(row2-row1+1)*(col2-col1+1);
	
	Z_s=new float[item];
	for(i=row1;i<=row2;i++)
	{
		for(j=col1;j<=col2;j++)
			Z_s[(i-row1)*(col2-col1+1)+j-col1]=theApp.m_DemHeight[i*theApp.m_Dem_cols+j];
	}
	
	int m_P=1;
	pos= new double[item*2];
	for(i=row1;i<=row2;i++)
	{
		for(j=col1;j<=col2;j++)
		{
			int mm=((i-row1)*(col2-col1+1)+j-col1)*2;
			pos[mm]=(j-col1)*theApp.m_Cell_xwidth;
			pos[mm+1]=(i-row1)*theApp.m_Cell_xwidth;

		}
	}

 
 

	float h=kriging( dx,dy,mode,  item, Z_s,  pos,  C0,  C1,  a, result);
	return h;

}

 
float CGetDemInsertValue::trendFace(int mStartrow, int mStartCol, double mx, double my)
{
	long i,j;
	float h;

	float dx=mx-mStartCol*theApp.m_Cell_xwidth-theApp.m_DemLeftDown_x;
	float dy=my-mStartrow*theApp.m_Cell_xwidth-theApp.m_DemLeftDown_y;
	
	int row1,col1,row2,col2;
	
	
	if(dx<=theApp.m_Cell_xwidth/2.0)
	{
		col1=mStartCol-1;
		col2=mStartCol+1;
		if(col2>theApp.m_Dem_cols)
			col2=theApp.m_Dem_cols;
	}
	else
	{
		col1=mStartCol;
		col2=mStartCol+2;
		if(col2>theApp.m_Dem_cols)
			col2=theApp.m_Dem_cols;
		
	}
	
	if(dy<=theApp.m_Cell_xwidth/2.0)
	{
		row1=mStartrow-1;
		row2=mStartrow+1;
		if(row2>theApp.m_Dem_Rows)
			row2=theApp.m_Dem_Rows;
		
	}
	else
	{
		row1=mStartrow;
		row2=mStartrow+2;
		if(row2>theApp.m_Dem_Rows)
			row2=theApp.m_Dem_Rows;
		
	}
	
	
	float *Z_s;
	double *pos;
	
    int item=(row2-row1+1)*(col2-col1+1);
	
	Z_s=new float[item];
	for(i=row1;i<=row2;i++)
	{
		for(j=col1;j<=col2;j++)
			Z_s[(i-row1)*(col2-col1+1)+j-col1]=theApp.m_DemHeight[i*theApp.m_Dem_cols+j];
	}
	
	int m_P=1;
	pos= new double[item*2];
	for(i=row1;i<=row2;i++)
	{
		for(j=col1;j<=col2;j++)
		{
			int mm=((i-row1)*(col2-col1+1)+j-col1)*2;
			pos[mm]=j*theApp.m_Cell_xwidth+theApp.m_DemLeftDown_x;
			pos[mm+1]=i*theApp.m_Cell_xwidth+theApp.m_DemLeftDown_y;
			
		}
	}

	float *D,*V;
	
	/* allocate V D array */
	
	
	
	
    V = (float *)GlobalAllocPtr(GMEM_MOVEABLE,sizeof (float) * 4 * 4);
	D = (float *)GlobalAllocPtr(GMEM_MOVEABLE,sizeof (float) * 4 );

	double ss[9];
	for(i=0;i<9;i++) ss[i]=0;
	V[0]=item;
	for(i=1;i<=item;i++)
	{
		int mm=(i-1)*2;
		ss[1]+=pos[mm];
		ss[2]+=pos[mm+1];
		ss[3]+=(pos[mm]*pos[mm]);
		ss[4]+=(pos[mm]*pos[mm+1]);
		ss[5]+=(pos[mm+1]*pos[mm+1]);
		ss[6]+=Z_s[i-1];
		ss[7]+=(pos[mm]*Z_s[i-1]);
		ss[8]+=(pos[mm+1]*Z_s[i-1]);
		
	}
	V[1]=V[4]=ss[1];
	V[2]=V[8]=ss[2];
	V[3]=1;
	V[5]=ss[3];
	V[6]=V[9]=ss[4];
	V[7]=1;
	V[10]=ss[5];
	V[11]=V[12]=V[13]=V[14]=1;
	V[15]=0;
	
	D[0]=ss[6];
	D[1]=ss[7];
	D[2]=ss[8];	
	D[3]=1;

	
	agaus(V,D,4);
	
	
	
    
	h=D[0]+D[1]*mx+D[2]*my;

	
	GlobalFreePtr(V);
	GlobalFreePtr(D);
	return h;

	
}
