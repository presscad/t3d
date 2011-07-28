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

//開始繪製實體
void CDXF::DxfBeginDrawEnties(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SECTION\n"); //表明這是一個段的開始
	Dxffile->WriteString ("2\n");
	Dxffile->WriteString ("ENTITIES\n"); 
}

//繪製直線
void CDXF::DxfDraw_Line(CStdioFile* Dxffile,CString Layername,int color,double x1, double y1, double z1, double x2, double y2, double z2)
{
	CString tt1[3],tt2[3],ttcolor;

	//將(x1,y1,z1)坐標轉換為字符型
	tt1[0].Format ("%.3f",x1);
	tt1[1].Format ("%.3f",y1);
	tt1[2].Format ("%.3f",z1);

	//將(x2,y2,z2)坐標轉換為字符型
	tt2[0].Format ("%.3f",x2);
	tt2[1].Format ("%.3f",y2);
	tt2[2].Format ("%.3f",z2);
	
	ttcolor.Format("%d",color);//將顏色值轉移為字符型

	Dxffile->WriteString ("0\n"); 
	Dxffile->WriteString ("LINE\n"); //標識直線開始
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //層名
	Dxffile->WriteString ("62\n");
	Dxffile->WriteString (ttcolor+"\n"); //顏色
	Dxffile->WriteString ("6\n");
	Dxffile->WriteString ("CONTINUOUS\n"); //線型
	Dxffile->WriteString ("10\n");  
	Dxffile->WriteString (tt1[0]+"\n"); //x1坐標
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt1[1]+"\n"); //y1坐標
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt1[2]+"\n"); //z1坐標
	
	Dxffile->WriteString ("11\n");
	Dxffile->WriteString (tt2[0]+"\n"); //x2坐標
	Dxffile->WriteString ("21\n");
	Dxffile->WriteString (tt2[1]+"\n"); //y2坐標
	Dxffile->WriteString ("31\n");
	Dxffile->WriteString (tt2[2]+"\n"); //z2坐標
}

//繪製點
void CDXF::DxfDraw_Point(CStdioFile* Dxffile,CString Layername, int color,double x, double y, double z)
{
	CString tt2[3],ttcolor;;

	//將(x,y,z)坐標轉換為字符型
	tt2[0].Format ("%.3f",x);
	tt2[1].Format ("%.3f",y);
	tt2[2].Format ("%.3f",z);

	ttcolor.Format("%d",color);//將顏色值轉移為字符型
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("POINT\n");//標識點開始
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //層名
	Dxffile->WriteString ("62\n");
	Dxffile->WriteString (ttcolor+"\n"); //顏色
	Dxffile->WriteString ("6\n");
	Dxffile->WriteString ("CONTINUOUS\n"); //線型
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString (tt2[0]+"\n"); //點的x坐標
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt2[1]+"\n"); //點的x坐標
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt2[2]+"\n"); //點的z坐標
}

//繪製多段線
void CDXF::DxfDraw_PolyLine(CStdioFile* Dxffile,CString Layername, double x, double y, double z)
{
	CString tt1[3];
	
	//將(x,y,z)坐標轉換為字符型
	tt1[0].Format ("%.3f",x);
	tt1[1].Format ("%.3f",-y); 
	tt1[2].Format ("%.3f",z);


	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("VERTEX\n");//標識頂點開始
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //層名
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString (tt1[0]+"\n"); //點的x坐標
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt1[1]+"\n"); //點的y坐標
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt1[2]+"\n"); //點的z坐標
}

//結束繪製多段線
void CDXF::DxfEnd_polyline(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SEQEND\n"); //標識結束,表明該實體的數據已經全部記錄完了
}

//繪製多邊形
void CDXF::DxfDraw_Polygon(CStdioFile* Dxffile,CString Layername, double x, double y, double z)
{
	CString tt,tt1[3];

	//將(x,y,z)坐標轉換為字符型
	tt1[0].Format ("%.3f",x);
	tt1[1].Format ("%.3f",y);
	tt1[2].Format ("%.3f",z);
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("VERTEX\n");//標識頂點開始
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //層名
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString (tt1[0]+"\n");//點的x坐標
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt1[1]+"\n");//點的y坐標
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt1[2]+"\n");//點的z坐標
}

//結束繪製多邊形
void CDXF::DxfEnd_polygon(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SEQEND\n");//標識結束,表明該實體的數據已經全部記錄完了
}

//繪製DXF文件頭
void CDXF::DxfHeader(CStdioFile* Dxffile)
{
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SECTION\n"); //表明這是一個段的開始
	Dxffile->WriteString ("2\n");
	Dxffile->WriteString ("HEADER\n"); //標識標題段開始
	Dxffile->WriteString ("9\n");

	Dxffile->WriteString ("$LIMMIN\n");//儲當前空間的左下方圖形界限
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("0\n");
	
	Dxffile->WriteString ("9\n");
	Dxffile->WriteString ("$LIMMAX\n");//儲當前空間的右上方圖形界限
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("5000\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("420\n");
	
	Dxffile->WriteString ("9\n");
	Dxffile->WriteString ("$VIEWCTR\n");//存儲當前視口中視圖的中心點
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("430\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("210\n");
	
	Dxffile->WriteString ("9\n");
	Dxffile->WriteString ("$VIEWSIZE\n"); //視口大小
	Dxffile->WriteString ("40\n");
	Dxffile->WriteString ("5000\n");
	
	Dxffile->WriteString ("9\n");
	Dxffile->WriteString ("$TEXTSTYLE\n"); //方案類型
	Dxffile->WriteString ("7\n");
	Dxffile->WriteString ("HZ\n");
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("ENDSEC\n"); //表明這一段結束了
	
}

//定義直線線型
void CDXF::DxfLineType(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SECTION\n"); //表明這是一個段的開始
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
	Dxffile->WriteString ("ENDSEC\n");//表明這一段結束了
}

//DXF文件結束
void CDXF::DxfSectionEnd(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("ENDSEC\n");//表明這一段結束了
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("EOF\n"); //表明這個DXF 文件結束了
	Dxffile->Close ();
}

//開始繪製多段線標誌
void CDXF::DxfStart_polyline(CStdioFile* Dxffile,CString Layername,double elevation,float startWidth,float endWidth,int mcolor)
{
	CString tt;
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("POLYLINE\n"); //標識為多段線 POLYLINE
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //層名
	Dxffile->WriteString ("66\n");
	Dxffile->WriteString ("1\n");
	Dxffile->WriteString ("62\n");//顏色
	tt.Format("%d\n",mcolor);
	Dxffile->WriteString (tt);  
	Dxffile->WriteString ("70\n");
	Dxffile->WriteString ("0\n");   //是否封閉(=0:不封閉 =1:封閉)
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("30\n");
	tt.Format ("%.3f",elevation);
	Dxffile->WriteString (tt+"\n");
	Dxffile->WriteString ("40\n"); //標高
	tt.Format("%.2f\n",startWidth); //起始線段寬度
	Dxffile->WriteString (tt);
	Dxffile->WriteString ("41\n");
	tt.Format("%.2f\n",endWidth);//終止線段寬度
	Dxffile->WriteString (tt);
}

//開始繪製多邊形標誌
void CDXF::DxfStart_polygon(CStdioFile* Dxffile,double elevation)
{
	CString tt;
	tt.Format ("%.3f",elevation); //標高
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("POLYLINE\n");
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString ("poline_layer\n");
	Dxffile->WriteString ("66\n");
	Dxffile->WriteString ("1\n");
	Dxffile->WriteString ("62\n");
	Dxffile->WriteString ("4\n"); //顏色
	Dxffile->WriteString ("70\n");
	Dxffile->WriteString ("1\n"); //是否封閉(=0:不封閉 =1:封閉)
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt+"\n");//標高
	Dxffile->WriteString ("40\n");
	Dxffile->WriteString ("0\n");//起始線段寬度
	Dxffile->WriteString ("41\n");
	Dxffile->WriteString ("0\n");//終止線段寬度
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
