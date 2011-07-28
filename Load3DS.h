 
 

#if !defined(AFX_LOAD3DS_H__69E7E7AC_7A07_4479_9687_AC19CED0E3CF__INCLUDED_)
#define AFX_LOAD3DS_H__69E7E7AC_7A07_4479_9687_AC19CED0E3CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vector.h"
 
#include <vector>
using namespace std;


 
//  基本塊(Primary Chunk)，位於文件的開始
#define PRIMARY       0x4D4D

//  主塊(Main Chunks)
#define OBJECTINFO    0x3D3D				// 網格對象的版本號
#define VERSION       0x0002				// .3ds文件的版本
#define EDITKEYFRAME  0xB000				// 所有關鍵幀信息的頭部

 
//  對象的次級定義(包括對象的材質和對像）
#define MATERIAL	  0xAFFF				// 保存紋理信息
#define OBJECT		  0x4000				// 保存對象的面、頂點等信息

 
//  材質的次級定義
#define MATNAME       0xA000				// 保存材質名稱
#define MATDIFFUSE    0xA020				// 對像/材質的顏色
#define MATMAP        0xA200				// 新材質的頭部
#define MATMAPFILE    0xA300				// 保存紋理的文件名
 
//  材質的光照定義
#define  MAT_AMBIENT  0xA010
#define  MAT_SPECULAR 0xA030
#define  MAT_EMISSIVE 0xA040
 
#define OBJECT_MESH   0x4100			// 新的網格對像	
 
//  OBJECT_MESH的次級定義
#define OBJECT_VERTICES     0x4110			// 對像頂點
#define OBJECT_FACES		0x4120			// 對象的面
#define OBJECT_MATERIAL		0x4130			// 對象的材質
#define OBJECT_UV			0x4140			// 對象的UV紋理坐標


 

// CLoad3DS類處理所有的裝入代碼
class CLoad3DS
{
 
public:
	
	
	struct tIndices {							

		unsigned short a, b, c, bVisible;		
	};

	// 保存塊信息的結構
	struct tChunk
	{
		unsigned short int ID;					// 塊的ID		
		unsigned int length;					// 塊的長度
		unsigned int bytesRead;					// 需要讀的塊數據的字節數
	};

	// 保存面信息的結構
	struct tFace
	{
		int vertIndex[3];			// 頂點索引
		int coordIndex[3];			// 紋理坐標索引
	};

	// 保存材質信息的結構體
	struct tMaterialInfo
	{
		char  strName[255];		// 紋理名稱	
		char  strFile[255];		// 如果存在紋理映射，則表示紋理文件名稱	
		
		BYTE  color[3];			// 對象的RGB顏色	
		
		float  ambient[4];		//材質的環境光		
		float  diffuse[4];		//材質的出射光		
		float  specular[4];		//材質的鏡面光		
		float  emissive[4];		//材質的漫反射光		
		
		int   texureId;			// 紋理ID	
		float uTile;			// u 重複	
		float vTile;			// v 重複	
		float uOffset;			// u 紋理偏移   
		float vOffset;			// v 紋理偏移	
	} ;
						
	
	class tMatREF
	{
	public:
		int nMaterialID;
		USHORT *pFaceIndexs;
		int nFaceNum;
		bool bHasTexture;
	public:
		tMatREF()
		{
			nMaterialID=-1;
			nFaceNum=0;
			pFaceIndexs=NULL;
			bHasTexture=false;
		}
	};

	
	
	// 對像信息的結構
	struct t3DObject 
	{
		int  numOfVerts;			// 模型中頂點的數目
		int  numOfFaces;			// 模型中面的數目
		int  numTexVertex;			// 模型中紋理坐標的數目
		int  numOfMaterials;         // 模型中材質的數目
		int  materialID;			// 紋理ID
		bool bHasTexture;			// 是否具有紋理映射
		char strName[255];			// 對象的名稱
		CVector3  *pVerts;			// 對象的頂點
		CVector3  *pNormals;		// 對象的法向量
		CVector2  *pTexVerts;		// 紋理UV坐標
		tFace *pFaces;				// 對象的面信息
		tMatREF	      *pMaterialREFS;
		double m_minX;  //對象的最小x坐標
		double m_maxX;	//對象的最大x坐標
		double m_minY;	//對象的最小y坐標
		double m_maxY;	//對象的最大y坐標
		double m_minZ;	//對象的最小z坐標
		double m_maxZ;	//對象的最大z坐標
	};

	//  模型信息結構體
	struct t3DModel 
	{
		int numOfObjects;			// 模型中對象的數目		
		int numOfMaterials;			// 模型中材質的數目		
		vector<tMaterialInfo> vctMaterials;	// 材質鏈表信息
		vector<t3DObject> vctObjects;		// 模型中對像鏈表信息
	};

public:
	void Bytes2Floats(BYTE *pbs,float *pfs,int num,float fsk);//字節數組到浮點轉化 	
	
	CLoad3DS();			// 初始化數據成員						
	
	~CLoad3DS();
	bool Import3DS(t3DModel *pModel, char *strFileName);// 裝入3ds文件到模型結構中
private:
	int GetString(char *);//讀入一個字符串
	void ReadChunk(tChunk *);//讀入塊的ID號和它的字節長度
	void ProcessNextChunk(t3DModel *pModel, tChunk *);//讀出3ds文件的主要部分(是個遞歸函數)
	void ProcessNextObjectChunk(t3DModel *pModel, t3DObject *pObject, tChunk *);//處理所有的文件中對象的信息
	void ProcessNextMaterialChunk(t3DModel *pModel, tChunk *);//處理所有的材質信息
	void ReadColorChunk(tMaterialInfo *pMaterial, tChunk *pChunk,USHORT typeFlag=0);// 讀對像顏色的RGB值
	void ReadVertices(t3DObject *pObject, tChunk *);	// 讀對象的頂點
	void ReadVertexIndices(t3DObject *pObject, tChunk *);// 讀對象的面信息
	void ReadUVCoordinates(t3DObject *pObject, tChunk *);	// 讀對象的紋理坐標
	void ReadObjectMaterial(t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk,vector<tMatREF*> *pvmatids);	// 讀賦予對象的材質名稱
	void ComputeNormals(t3DModel *pModel);// 計算對像頂點的法向量
	void CleanUp();// 關閉文件，釋放內存空間
	
	FILE *m_FilePointer;// 文件指針
};


#endif // !defined(AFX_LOAD3DS_H__69E7E7AC_7A07_4479_9687_AC19CED0E3CF__INCLUDED_)
