// DXF.cpp: implementation of the CDXF class.
 
 

#include "stdafx.h"
#include "DXF.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 
// Construction/Destruction
 

CDXF::CDXF()
{

}

CDXF::~CDXF()
{

}

//�}�lø�s����
void CDXF::DxfBeginDrawEnties(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SECTION\n"); //����o�O�@�Ӭq���}�l
	Dxffile->WriteString ("2\n");
	Dxffile->WriteString ("ENTITIES\n"); 
}

//ø�s���u
void CDXF::DxfDraw_Line(CStdioFile* Dxffile,CString Layername,int color,double x1, double y1, double z1, double x2, double y2, double z2)
{
	CString tt1[3],tt2[3],ttcolor;

	//�N(x1,y1,z1)�����ഫ���r�ū�
	tt1[0].Format ("%.3f",x1);
	tt1[1].Format ("%.3f",y1);
	tt1[2].Format ("%.3f",z1);

	//�N(x2,y2,z2)�����ഫ���r�ū�
	tt2[0].Format ("%.3f",x2);
	tt2[1].Format ("%.3f",y2);
	tt2[2].Format ("%.3f",z2);
	
	ttcolor.Format("%d",color);//�N�C����ಾ���r�ū�

	Dxffile->WriteString ("0\n"); 
	Dxffile->WriteString ("LINE\n"); //���Ѫ��u�}�l
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //�h�W
	Dxffile->WriteString ("62\n");
	Dxffile->WriteString (ttcolor+"\n"); //�C��
	Dxffile->WriteString ("6\n");
	Dxffile->WriteString ("CONTINUOUS\n"); //�u��
	Dxffile->WriteString ("10\n");  
	Dxffile->WriteString (tt1[0]+"\n"); //x1����
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt1[1]+"\n"); //y1����
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt1[2]+"\n"); //z1����
	
	Dxffile->WriteString ("11\n");
	Dxffile->WriteString (tt2[0]+"\n"); //x2����
	Dxffile->WriteString ("21\n");
	Dxffile->WriteString (tt2[1]+"\n"); //y2����
	Dxffile->WriteString ("31\n");
	Dxffile->WriteString (tt2[2]+"\n"); //z2����
}

//ø�s�I
void CDXF::DxfDraw_Point(CStdioFile* Dxffile,CString Layername, int color,double x, double y, double z)
{
	CString tt2[3],ttcolor;;

	//�N(x,y,z)�����ഫ���r�ū�
	tt2[0].Format ("%.3f",x);
	tt2[1].Format ("%.3f",y);
	tt2[2].Format ("%.3f",z);

	ttcolor.Format("%d",color);//�N�C����ಾ���r�ū�
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("POINT\n");//�����I�}�l
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //�h�W
	Dxffile->WriteString ("62\n");
	Dxffile->WriteString (ttcolor+"\n"); //�C��
	Dxffile->WriteString ("6\n");
	Dxffile->WriteString ("CONTINUOUS\n"); //�u��
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString (tt2[0]+"\n"); //�I��x����
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt2[1]+"\n"); //�I��x����
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt2[2]+"\n"); //�I��z����
}

//ø�s�h�q�u
void CDXF::DxfDraw_PolyLine(CStdioFile* Dxffile,CString Layername, double x, double y, double z)
{
	CString tt1[3];
	
	//�N(x,y,z)�����ഫ���r�ū�
	tt1[0].Format ("%.3f",x);
	tt1[1].Format ("%.3f",-y); 
	tt1[2].Format ("%.3f",z);


	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("VERTEX\n");//���ѳ��I�}�l
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //�h�W
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString (tt1[0]+"\n"); //�I��x����
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt1[1]+"\n"); //�I��y����
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt1[2]+"\n"); //�I��z����
}

//����ø�s�h�q�u
void CDXF::DxfEnd_polyline(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SEQEND\n"); //���ѵ���,����ӹ��骺�ƾڤw�g�����O�����F
}

//ø�s�h���
void CDXF::DxfDraw_Polygon(CStdioFile* Dxffile,CString Layername, double x, double y, double z)
{
	CString tt,tt1[3];

	//�N(x,y,z)�����ഫ���r�ū�
	tt1[0].Format ("%.3f",x);
	tt1[1].Format ("%.3f",y);
	tt1[2].Format ("%.3f",z);
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("VERTEX\n");//���ѳ��I�}�l
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //�h�W
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString (tt1[0]+"\n");//�I��x����
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt1[1]+"\n");//�I��y����
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt1[2]+"\n");//�I��z����
}

//����ø�s�h���
void CDXF::DxfEnd_polygon(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SEQEND\n");//���ѵ���,����ӹ��骺�ƾڤw�g�����O�����F
}

//ø�sDXF����Y
void CDXF::DxfHeader(CStdioFile* Dxffile)
{
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SECTION\n"); //����o�O�@�Ӭq���}�l
	Dxffile->WriteString ("2\n");
	Dxffile->WriteString ("HEADER\n"); //���Ѽ��D�q�}�l
	Dxffile->WriteString ("9\n");

	Dxffile->WriteString ("$LIMMIN\n");//�x��e�Ŷ������U��ϧάɭ�
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("0\n");
	
	Dxffile->WriteString ("9\n");
	Dxffile->WriteString ("$LIMMAX\n");//�x��e�Ŷ����k�W��ϧάɭ�
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("5000\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("420\n");
	
	Dxffile->WriteString ("9\n");
	Dxffile->WriteString ("$VIEWCTR\n");//�s�x��e���f�����Ϫ������I
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("430\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("210\n");
	
	Dxffile->WriteString ("9\n");
	Dxffile->WriteString ("$VIEWSIZE\n"); //���f�j�p
	Dxffile->WriteString ("40\n");
	Dxffile->WriteString ("5000\n");
	
	Dxffile->WriteString ("9\n");
	Dxffile->WriteString ("$TEXTSTYLE\n"); //�������
	Dxffile->WriteString ("7\n");
	Dxffile->WriteString ("HZ\n");
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("ENDSEC\n"); //����o�@�q�����F
	
}

//�w�q���u�u��
void CDXF::DxfLineType(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SECTION\n"); //����o�O�@�Ӭq���}�l
	Dxffile->WriteString ("2\n");
	Dxffile->WriteString ("TABLES\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("TABLE\n");
	Dxffile->WriteString ("2\n");
	Dxffile->WriteString ("LTYPE\n");
	
	Dxffile->WriteString ("70\n");
	Dxffile->WriteString ("1\n");
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("LTYPE\n");
	
	Dxffile->WriteString ("2\n");
	Dxffile->WriteString ("CONTINUOUS\n");
	Dxffile->WriteString ("70\n");
	Dxffile->WriteString ("64\n");
	Dxffile->WriteString ("3\n");
	Dxffile->WriteString ("Solid line\n");
	Dxffile->WriteString ("72\n");
	Dxffile->WriteString ("65\n");
	Dxffile->WriteString ("73\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("40\n");
	Dxffile->WriteString ("0.0\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("ENDTAB\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("ENDSEC\n");//����o�@�q�����F
}

//DXF��󵲧�
void CDXF::DxfSectionEnd(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("ENDSEC\n");//����o�@�q�����F
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("EOF\n"); //����o��DXF ��󵲧��F
	Dxffile->Close ();
}

//�}�lø�s�h�q�u�лx
void CDXF::DxfStart_polyline(CStdioFile* Dxffile,CString Layername,double elevation,float startWidth,float endWidth,int mcolor)
{
	CString tt;
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("POLYLINE\n"); //���Ѭ��h�q�u POLYLINE
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //�h�W
	Dxffile->WriteString ("66\n");
	Dxffile->WriteString ("1\n");
	Dxffile->WriteString ("62\n");//�C��
	tt.Format("%d\n",mcolor);
	Dxffile->WriteString (tt);  
	Dxffile->WriteString ("70\n");
	Dxffile->WriteString ("0\n");   //�O�_�ʳ�(=0:���ʳ� =1:�ʳ�)
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("30\n");
	tt.Format ("%.3f",elevation);
	Dxffile->WriteString (tt+"\n");
	Dxffile->WriteString ("40\n"); //�а�
	tt.Format("%.2f\n",startWidth); //�_�l�u�q�e��
	Dxffile->WriteString (tt);
	Dxffile->WriteString ("41\n");
	tt.Format("%.2f\n",endWidth);//�פ�u�q�e��
	Dxffile->WriteString (tt);
}

//�}�lø�s�h��μлx
void CDXF::DxfStart_polygon(CStdioFile* Dxffile,double elevation)
{
	CString tt;
	tt.Format ("%.3f",elevation); //�а�
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("POLYLINE\n");
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString ("poline_layer\n");
	Dxffile->WriteString ("66\n");
	Dxffile->WriteString ("1\n");
	Dxffile->WriteString ("62\n");
	Dxffile->WriteString ("4\n"); //�C��
	Dxffile->WriteString ("70\n");
	Dxffile->WriteString ("1\n"); //�O�_�ʳ�(=0:���ʳ� =1:�ʳ�)
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt+"\n");//�а�
	Dxffile->WriteString ("40\n");
	Dxffile->WriteString ("0\n");//�_�l�u�q�e��
	Dxffile->WriteString ("41\n");
	Dxffile->WriteString ("0\n");//�פ�u�q�e��
}


void CDXF::DxfDraw_Circle(CStdioFile *Dxffile, double centerx, double centery, float R, int mcolor)
{
	CString tt;
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("CIRCLE\n");
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString ("Circle_layer\n");
	Dxffile->WriteString ("62\n");
	tt.Format("%d\n",mcolor);
	Dxffile->WriteString (tt);  
	Dxffile->WriteString ("10\n");
	tt.Format("%f\n",centerx);
	Dxffile->WriteString (tt);
	Dxffile->WriteString ("20\n");
	tt.Format("%f\n",centery);
	Dxffile->WriteString (tt);
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("40\n");   
	tt.Format("%f\n",R);
	Dxffile->WriteString (tt);
}

void CDXF::DxfDraw_Text(CStdioFile *Dxffile, CString strlayername, double x, double y, float HW_Scale, int fonhHeight, float InAngle, CString strText, int style)
{
	CString tt,tt1[3];
	
	tt1[0].Format ("%.3f",x);
	tt1[1].Format ("%.3f",y);
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("text\n");
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString ("layrtname\n");
	Dxffile->WriteString ("62\n");
	Dxffile->WriteString ("2\n"); 
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString (tt1[0]+"\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt1[1]+"\n");
	Dxffile->WriteString ("40\n");
	tt.Format("%d\n",fonhHeight);
	Dxffile->WriteString (tt);
	Dxffile->WriteString ("1\n");
	Dxffile->WriteString (strText+"\n");
	Dxffile->WriteString ("41\n");
	tt.Format("%f\n",HW_Scale);
	Dxffile->WriteString (tt);
	Dxffile->WriteString ("71\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("50\n");
	tt.Format("%f\n",InAngle);
	Dxffile->WriteString (tt);
	
	
	
	Dxffile->WriteString ("7\n");
	tt.Format("%d\n",style);
	Dxffile->WriteString (tt);
}
