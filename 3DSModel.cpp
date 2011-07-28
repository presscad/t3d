// 3DSModel.cpp: implementation of the C3DSModel class.
 
 
 
 
 
 
 

#include "stdafx.h"
#include "3DSModel.h"

 
// Construction/Destruction
 
C3DSModel::C3DSModel()
{
	m_sFileName[0]=0;
	m_bModelOK=FALSE;

	m_3DModel.numOfMaterials=0;
	m_3DModel.numOfObjects=0;
	m_3DModel.vctMaterials.clear();
	m_3DModel.vctObjects.clear();
}
C3DSModel::~C3DSModel()
{

	for(int i = 0; i < m_3DModel.numOfObjects; i++)
	{
		
		delete [] m_3DModel.vctObjects[i].pFaces;
		delete [] m_3DModel.vctObjects[i].pNormals;
		delete [] m_3DModel.vctObjects[i].pVerts;
		delete [] m_3DModel.vctObjects[i].pTexVerts;
		for(int j=0;j<m_3DModel.vctObjects[i].numOfMaterials;j++)
			delete[] m_3DModel.vctObjects[i].pMaterialREFS[j].pFaceIndexs;
		delete [] m_3DModel.vctObjects[i].pMaterialREFS;
	}

}
 
BOOL C3DSModel::Draw(int m_drawStyle,double *minx,double *maxx,double *miny,double *maxy,double *minz,double *maxz)
{
	CLoad3DS::tMatREF *pmatref;
	CLoad3DS::tMaterialInfo *pmat;
	CLoad3DS::t3DObject *pObject;
	
	for(int i = 0; i < m_3DModel.numOfObjects; i++) // �M���ҫ����Ҧ�����H
	{
		
		pObject = &m_3DModel.vctObjects[i];// ��o��e��ܪ���H
		
		for(int imat=0;imat<pObject->numOfMaterials;imat++)
		{
			
			pmatref=&pObject->pMaterialREFS[imat];
			
			pmat=&(m_3DModel.vctMaterials[pmatref->nMaterialID]);
			
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,pmat->ambient);
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,pmat->diffuse);
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,pmat->specular);
			glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,pmat->emissive);
			
			if(pmatref->bHasTexture) // �P�_�ӹ�H�O�_�����z�M�g
			{
				glEnable(GL_TEXTURE_2D);// ���}���z�M�g
				glEnable(GL_COLOR_MATERIAL); //�E�������C��]�����z�M�g�[�J�C��C�p�G���E�������C��,���z�N�@���O�������Ӫ��C��C���glColor3f(r,g,b)�N������C�⤣�_����@�ΡC�ҥH�E���L�O�D�`���n���^
				glColor3ub(255, 255, 255);
				glBindTexture(GL_TEXTURE_2D, m_3DModel.vctMaterials[pmatref->nMaterialID].texureId);
			} 
			else 
			{
				glDisable(GL_TEXTURE_2D);// �������z�M�g
				glDisable(GL_COLOR_MATERIAL);//���������C��
			}	
			
			if(m_drawStyle==3)
			{
				glDisable(GL_TEXTURE_2D); // �������z�M�g
			
			}
			
			
			
			glBegin(GL_TRIANGLES);// �}�lø�s�T����
			
			for(int nfindex = 0,j=0; nfindex < pmatref->nFaceNum; nfindex++)// �M���Ҧ�����
			{
				
				j=int(pmatref->pFaceIndexs[nfindex]);// ��o�C�ӭ�������
				
				// �M���T���Ϊ��Ҧ��I
				for(int whichVertex = 0; whichVertex < 3; whichVertex++)
				{
					
					int index = pObject->pFaces[j].vertIndex[whichVertex];// ��o����C���I������
					if(pObject->pVerts[ index ].z<=-3)
						int uu=0;
					
					// ���X�k�V�q
					glNormal3f(pObject->pNormals[ index ].x, pObject->pNormals[ index ].y, pObject->pNormals[ index ].z);
					
					
					if(pmatref->bHasTexture)	// �p�G�㦳���z
					{
						if(pObject->pTexVerts) 	// �p�G�ﹳ�㦳���z
						{
							glTexCoord2f(pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);// �]�m���z����
						}
					} 
					
					if(m_drawStyle==3)
					{
						GetColorRGB(pObject->m_minY,pObject->m_maxY,pObject->pVerts[ index ].y);
						glColor3f(m_Color_R,m_Color_G,m_Color_B); //�]�m�C��
					}
					
					
					glVertex3f(pObject->pVerts[ index ].x, pObject->pVerts[ index ].y, pObject->pVerts[ index ].z);
					
				}
			}
			glEnd();	// ø�s����			
		}
	}

	//��oø�s��H���̤p�M�̤jx,y,z����
	*minx=pObject->m_minX;
	*maxx=pObject->m_maxX;
	*miny=pObject->m_minY;
	*maxy=pObject->m_maxY;
	*minz=pObject->m_minZ;
	*maxz=pObject->m_maxZ;
	
	return TRUE;

}

//�q��󤤥[��3DS�ҫ�
BOOL C3DSModel::LoadModelFromFile(char* sfilename)
{

 
	static int ntextID=0;
	char stmp[512];
	
	strcpy(stmp,sfilename);//�N�r�ū��ܶq��ȵ�stmp
	
	CLoad3DS cLoad3ds;
	
	if(cLoad3ds.Import3DS(&m_3DModel, stmp)==false)	 //�p�G�[��3DS�ҫ�����
	{
		m_bModelOK=FALSE; //���ѥ[������
		return FALSE; //��^FALSE
	}
	
	
	for(int i = 0; i < m_3DModel.numOfMaterials; i++)
	{
		
		if(strlen(m_3DModel.vctMaterials[i].strFile) > 0)
		{
			strcpy(stmp,g_sMediaPath);
			strcat(stmp,m_3DModel.vctMaterials[i].strFile);
			CFileFind p;
			int nFound;
			nFound=p.FindFile(stmp);
			if(nFound!=NULL) 
			{
				
				
				CreateTexture(g_Texture,stmp , ntextID);	
				m_3DModel.vctMaterials[i].texureId = g_Texture[ntextID];
				ntextID++;
			}
		
		
		

		}
		else
			m_3DModel.vctMaterials[i].texureId = 0;
	}
	m_bModelOK=TRUE;
	return TRUE;
}
 
void C3DSModel::AlignBottom()
{
	CLoad3DS::t3DObject *pObject;
	float fminy=10000;
	float foffset=0;
	int i=0;
	
	for(i = 0; i < m_3DModel.numOfObjects; i++)
	{
		pObject = &m_3DModel.vctObjects[i];
		for(int j=0;j<pObject->numOfVerts;j++)
		{
			if(fminy>pObject->pVerts[j].y)fminy=pObject->pVerts[j].y;
		}
	}
	foffset=-fminy;
	
	for(i = 0; i < m_3DModel.numOfObjects; i++)
	{
		pObject = &m_3DModel.vctObjects[i];
		for(int j=0;j<pObject->numOfVerts;j++)
		{
			pObject->pVerts[j].y+=foffset;
		}
	}

}

void C3DSModel::GetColorRGB(double minY, double maxY, double y)
{

	m_Color_R=(y-minY)/(maxY-minY);
	m_Color_G=1-(y-minY)/(maxY-minY);
	m_Color_B=2*(y-minY)/(maxY-minY);
}
