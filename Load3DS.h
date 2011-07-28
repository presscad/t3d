 
 

#if !defined(AFX_LOAD3DS_H__69E7E7AC_7A07_4479_9687_AC19CED0E3CF__INCLUDED_)
#define AFX_LOAD3DS_H__69E7E7AC_7A07_4479_9687_AC19CED0E3CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vector.h"
 
#include <vector>
using namespace std;


 
//  �򥻶�(Primary Chunk)�A����󪺶}�l
#define PRIMARY       0x4D4D

//  �D��(Main Chunks)
#define OBJECTINFO    0x3D3D				// �����H��������
#define VERSION       0x0002				// .3ds��󪺪���
#define EDITKEYFRAME  0xB000				// �Ҧ�����V�H�����Y��

 
//  ��H�����ũw�q(�]�A��H������M�ﹳ�^
#define MATERIAL	  0xAFFF				// �O�s���z�H��
#define OBJECT		  0x4000				// �O�s��H�����B���I���H��

 
//  ���誺���ũw�q
#define MATNAME       0xA000				// �O�s����W��
#define MATDIFFUSE    0xA020				// �ﹳ/���誺�C��
#define MATMAP        0xA200				// �s���誺�Y��
#define MATMAPFILE    0xA300				// �O�s���z�����W
 
//  ���誺���өw�q
#define  MAT_AMBIENT  0xA010
#define  MAT_SPECULAR 0xA030
#define  MAT_EMISSIVE 0xA040
 
#define OBJECT_MESH   0x4100			// �s������ﹳ	
 
//  OBJECT_MESH�����ũw�q
#define OBJECT_VERTICES     0x4110			// �ﹳ���I
#define OBJECT_FACES		0x4120			// ��H����
#define OBJECT_MATERIAL		0x4130			// ��H������
#define OBJECT_UV			0x4140			// ��H��UV���z����


 

// CLoad3DS���B�z�Ҧ����ˤJ�N�X
class CLoad3DS
{
 
public:
	
	
	struct tIndices {							

		unsigned short a, b, c, bVisible;		
	};

	// �O�s���H�������c
	struct tChunk
	{
		unsigned short int ID;					// ����ID		
		unsigned int length;					// ��������
		unsigned int bytesRead;					// �ݭnŪ�����ƾڪ��r�`��
	};

	// �O�s���H�������c
	struct tFace
	{
		int vertIndex[3];			// ���I����
		int coordIndex[3];			// ���z���Я���
	};

	// �O�s����H�������c��
	struct tMaterialInfo
	{
		char  strName[255];		// ���z�W��	
		char  strFile[255];		// �p�G�s�b���z�M�g�A�h��ܯ��z���W��	
		
		BYTE  color[3];			// ��H��RGB�C��	
		
		float  ambient[4];		//���誺���ҥ�		
		float  diffuse[4];		//���誺�X�g��		
		float  specular[4];		//���誺�譱��		
		float  emissive[4];		//���誺���Ϯg��		
		
		int   texureId;			// ���zID	
		float uTile;			// u ����	
		float vTile;			// v ����	
		float uOffset;			// u ���z����   
		float vOffset;			// v ���z����	
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

	
	
	// �ﹳ�H�������c
	struct t3DObject 
	{
		int  numOfVerts;			// �ҫ������I���ƥ�
		int  numOfFaces;			// �ҫ��������ƥ�
		int  numTexVertex;			// �ҫ������z���Ъ��ƥ�
		int  numOfMaterials;         // �ҫ������誺�ƥ�
		int  materialID;			// ���zID
		bool bHasTexture;			// �O�_�㦳���z�M�g
		char strName[255];			// ��H���W��
		CVector3  *pVerts;			// ��H�����I
		CVector3  *pNormals;		// ��H���k�V�q
		CVector2  *pTexVerts;		// ���zUV����
		tFace *pFaces;				// ��H�����H��
		tMatREF	      *pMaterialREFS;
		double m_minX;  //��H���̤px����
		double m_maxX;	//��H���̤jx����
		double m_minY;	//��H���̤py����
		double m_maxY;	//��H���̤jy����
		double m_minZ;	//��H���̤pz����
		double m_maxZ;	//��H���̤jz����
	};

	//  �ҫ��H�����c��
	struct t3DModel 
	{
		int numOfObjects;			// �ҫ�����H���ƥ�		
		int numOfMaterials;			// �ҫ������誺�ƥ�		
		vector<tMaterialInfo> vctMaterials;	// �������H��
		vector<t3DObject> vctObjects;		// �ҫ����ﹳ���H��
	};

public:
	void Bytes2Floats(BYTE *pbs,float *pfs,int num,float fsk);//�r�`�Ʋը�B�I��� 	
	
	CLoad3DS();			// ��l�Ƽƾڦ���						
	
	~CLoad3DS();
	bool Import3DS(t3DModel *pModel, char *strFileName);// �ˤJ3ds����ҫ����c��
private:
	int GetString(char *);//Ū�J�@�Ӧr�Ŧ�
	void ReadChunk(tChunk *);//Ū�J����ID���M�����r�`����
	void ProcessNextChunk(t3DModel *pModel, tChunk *);//Ū�X3ds��󪺥D�n����(�O�ӻ��k���)
	void ProcessNextObjectChunk(t3DModel *pModel, t3DObject *pObject, tChunk *);//�B�z�Ҧ�����󤤹�H���H��
	void ProcessNextMaterialChunk(t3DModel *pModel, tChunk *);//�B�z�Ҧ�������H��
	void ReadColorChunk(tMaterialInfo *pMaterial, tChunk *pChunk,USHORT typeFlag=0);// Ū�ﹳ�C�⪺RGB��
	void ReadVertices(t3DObject *pObject, tChunk *);	// Ū��H�����I
	void ReadVertexIndices(t3DObject *pObject, tChunk *);// Ū��H�����H��
	void ReadUVCoordinates(t3DObject *pObject, tChunk *);	// Ū��H�����z����
	void ReadObjectMaterial(t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk,vector<tMatREF*> *pvmatids);	// Ū�ᤩ��H������W��
	void ComputeNormals(t3DModel *pModel);// �p��ﹳ���I���k�V�q
	void CleanUp();// �������A���񤺦s�Ŷ�
	
	FILE *m_FilePointer;// �����w
};


#endif // !defined(AFX_LOAD3DS_H__69E7E7AC_7A07_4479_9687_AC19CED0E3CF__INCLUDED_)
