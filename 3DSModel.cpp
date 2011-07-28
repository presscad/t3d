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
	
	for(int i = 0; i < m_3DModel.numOfObjects; i++) // 遍歷模型中所有的對象
	{
		
		pObject = &m_3DModel.vctObjects[i];// 獲得當前顯示的對象
		
		for(int imat=0;imat<pObject->numOfMaterials;imat++)
		{
			
			pmatref=&pObject->pMaterialREFS[imat];
			
			pmat=&(m_3DModel.vctMaterials[pmatref->nMaterialID]);
			
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,pmat->ambient);
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,pmat->diffuse);
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,pmat->specular);
			glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,pmat->emissive);
			
			if(pmatref->bHasTexture) // 判斷該對象是否有紋理映射
			{
				glEnable(GL_TEXTURE_2D);// 打開紋理映射
				glEnable(GL_COLOR_MATERIAL); //激活材質顏色（給紋理映射加入顏色。如果不激活材質顏色,紋理將一直保持它本來的顏色。函數glColor3f(r,g,b)將對改變顏色不起任何作用。所以激活他是非常重要的）
				glColor3ub(255, 255, 255);
				glBindTexture(GL_TEXTURE_2D, m_3DModel.vctMaterials[pmatref->nMaterialID].texureId);
			} 
			else 
			{
				glDisable(GL_TEXTURE_2D);// 關閉紋理映射
				glDisable(GL_COLOR_MATERIAL);//關閉材質顏色
			}	
			
			if(m_drawStyle==3)
			{
				glDisable(GL_TEXTURE_2D); // 關閉紋理映射
			
			}
			
			
			
			glBegin(GL_TRIANGLES);// 開始繪製三角形
			
			for(int nfindex = 0,j=0; nfindex < pmatref->nFaceNum; nfindex++)// 遍歷所有的面
			{
				
				j=int(pmatref->pFaceIndexs[nfindex]);// 獲得每個面的索引
				
				// 遍歷三角形的所有點
				for(int whichVertex = 0; whichVertex < 3; whichVertex++)
				{
					
					int index = pObject->pFaces[j].vertIndex[whichVertex];// 獲得面對每個點的索引
					if(pObject->pVerts[ index ].z<=-3)
						int uu=0;
					
					// 給出法向量
					glNormal3f(pObject->pNormals[ index ].x, pObject->pNormals[ index ].y, pObject->pNormals[ index ].z);
					
					
					if(pmatref->bHasTexture)	// 如果具有紋理
					{
						if(pObject->pTexVerts) 	// 如果對像具有紋理
						{
							glTexCoord2f(pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);// 設置紋理坐標
						}
					} 
					
					if(m_drawStyle==3)
					{
						GetColorRGB(pObject->m_minY,pObject->m_maxY,pObject->pVerts[ index ].y);
						glColor3f(m_Color_R,m_Color_G,m_Color_B); //設置顏色
					}
					
					
					glVertex3f(pObject->pVerts[ index ].x, pObject->pVerts[ index ].y, pObject->pVerts[ index ].z);
					
				}
			}
			glEnd();	// 繪製結束			
		}
	}

	//獲得繪製對象的最小和最大x,y,z坐標
	*minx=pObject->m_minX;
	*maxx=pObject->m_maxX;
	*miny=pObject->m_minY;
	*maxy=pObject->m_maxY;
	*minz=pObject->m_minZ;
	*maxz=pObject->m_maxZ;
	
	return TRUE;

}

//從文件中加載3DS模型
BOOL C3DSModel::LoadModelFromFile(char* sfilename)
{

 
	static int ntextID=0;
	char stmp[512];
	
	strcpy(stmp,sfilename);//將字符型變量賦值給stmp
	
	CLoad3DS cLoad3ds;
	
	if(cLoad3ds.Import3DS(&m_3DModel, stmp)==false)	 //如果加載3DS模型失敗
	{
		m_bModelOK=FALSE; //標識加載失敗
		return FALSE; //返回FALSE
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
