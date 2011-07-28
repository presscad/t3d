// Load3DS.cpp: implementation of the CLoad3DS class.
 
#include "stdafx.h"
#include "Load3DS.h"

static int gBuffer[50000] = {0};					
 

CLoad3DS::CLoad3DS()
{
	m_FilePointer = NULL;
}

CLoad3DS::~CLoad3DS()
{
	m_FilePointer = NULL;
}

 
 
//  ���}�@��3ds���AŪ�X�䤤�����e�A�����񤺦s
bool CLoad3DS::Import3DS(CLoad3DS::t3DModel *pModel, char *strFileName)
{
	char strMessage[255] = {0};
	tChunk currentChunk = {0};
	int i=0;

	// ���}�@��3ds���
	m_FilePointer = fopen(strFileName, "rb");

	
	// �T�O����o�������w�X�k
	if(!m_FilePointer) 
	{
		sprintf(strMessage, "�䤣����: %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}

	// ���󥴶}����A�������ӱN���̶}�l���ƾڶ�Ū�X�H�P�_�O�_�O�@��3ds���
	// �p�G�O3ds��󪺸ܡA�Ĥ@�Ӷ�ID���ӬOPRIMARY
	
	// �N��󪺲Ĥ@��Ū�X�çP�_�O�_�O3ds���
	ReadChunk(&currentChunk);

	// �T�O�O3ds���
	if (currentChunk.ID != PRIMARY)
	{
		sprintf(strMessage, "Unable to load PRIMARY chuck from file: %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}

	
	// �{�b�}�lŪ�J�ƾڡAProcessNextChunk()�O�@�ӻ��k���
	
	// �q�L�եΤU�������k��ơA�N�ﹳŪ�X
	ProcessNextChunk(pModel, &currentChunk);

	
	// �bŪ�����3ds��󤧫�A�p�⳻�I���k�u
	ComputeNormals(pModel);

	// ���񤺦s�Ŷ�
	CleanUp();

	return true;
}


//  �U�����������Ҧ������s�Ŷ��A���������
void CLoad3DS::CleanUp()
{
	if (m_FilePointer) 
	{
		fclose(m_FilePointer);		// ������e�������w				
		m_FilePointer = NULL;  //�����w����
	}
}

 
//  �U�������Ū�X3ds��󪺥D�n����(�O�ӻ��k���)
void CLoad3DS::ProcessNextChunk(CLoad3DS::t3DModel *pModel, tChunk *pPreviousChunk)
{
	t3DObject newObject = {0};			// �ΨӲK�[��ﹳ���		
	tMaterialInfo newTexture = {0};		// �ΨӲK�[��������		

	tChunk currentChunk = {0};			// �ΨӲK�[���e�����		
	tChunk tempChunk = {0};			// �ΨӲK�[���{�ɶ����		

	//  �U���CŪ�@�ӷs���A���n�P�_�@�U����ID�A�p�G�Ӷ��O�ݭn��Ū�J���A�h�~��i��
	//  �p�G�O���ݭnŪ�J�����A�h���L

	// �~��Ū�J�l���A����F��w�w������
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		
		ReadChunk(&currentChunk);	// Ū�J�U�@�Ӷ�

		// �P�_����ID��
		switch (currentChunk.ID)
		{
		case VERSION:		// ��󪩥���					
			// �b�Ӷ������@�ӵL�Ÿ��u�㫬�ƫO�s�F��󪺪���
			
			// Ū�J��󪺪������A�ñN�r�`�ƲK�[��bytesRead�ܶq��	
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
		
			// �p�G��󪩥����j��3�A���X�@��ĵ�i�H��
			if ((currentChunk.length - currentChunk.bytesRead == 4) && (gBuffer[0] > 0x03)) 
			{
				MessageBox(NULL, "3DS��󪩥����j��3�A���i��Ū�������T�I", "ĵ�i", MB_OK);
			}
			break;

		case OBJECTINFO:		 // ���檩���H��				
				
			ReadChunk(&tempChunk);// Ū�J�U�@�Ӷ�
			
			// ��o���檺������
			tempChunk.bytesRead += fread(gBuffer, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);

			// �W�[Ū�J���r�`��
			currentChunk.bytesRead += tempChunk.bytesRead;

			// �i�J�U�@�Ӷ�
			ProcessNextChunk(pModel, &currentChunk);
			break;
		case MATERIAL:			// ����H��				
	
			// ���誺�ƥػ��W
			pModel->numOfMaterials++;
			
			// �b���z����K�[�@�Ӫťկ��z���c
			pModel->vctMaterials.push_back(newTexture);
		
			// �i�J����ˤJ���
			ProcessNextMaterialChunk(pModel, &currentChunk);
		
			break;

		case OBJECT:			// ��H���W��			
			// �Ӷ��O�ﹳ�H�������Y���A�O�s�F��H�F�W��
			
			pModel->numOfObjects++;// �ﹳ�ƻ��W
		
			// �K�[�@�ӷs��tObject�`�I��ﹳ���
			pModel->vctObjects.push_back(newObject); 
		
			// ��l�ƹﹳ�M�����Ҧ��ƾڦ���
			memset(&(pModel->vctObjects[pModel->numOfObjects - 1]), 0, sizeof(t3DObject));

			// ��o�ëO�s��H���W�١A�M��W�[Ū�J���r�`��
			currentChunk.bytesRead += GetString(pModel->vctObjects[pModel->numOfObjects - 1].strName);
			
			// �i�J��l����H�H����Ū�J
			ProcessNextObjectChunk(pModel, &(pModel->vctObjects[pModel->numOfObjects - 1]), &currentChunk);
			break;

		case EDITKEYFRAME:
			// ���L����V����Ū�J�A�W�[�ݭnŪ�J���r�`��
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;

		default: 
			//  ���L�Ҧ��������������e��Ū�J�A�W�[�ݭnŪ�J���r�`��
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
		}
	
		// �W�[�q�̫��Ū�J���r�`��
		pPreviousChunk->bytesRead += currentChunk.bytesRead;
	}

}

//  �U������ƳB�z�Ҧ�����󤤹�H���H��
void CLoad3DS::ProcessNextObjectChunk(CLoad3DS::t3DModel *pModel, CLoad3DS::t3DObject *pObject, CLoad3DS::tChunk *pPreviousChunk)
{
	
	tChunk currentChunk = {0};// �ΨӲK�[���e�����		
	vector<tMatREF*> vctMatIDS;
	
	// �~��Ū�J�������e���ܥ��l������
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		// Ū�J�U�@�Ӷ�
		ReadChunk(&currentChunk);

		// �ϧOŪ�J�O���ض�
		switch (currentChunk.ID)
		{
		case OBJECT_MESH:	 	// ��Ū�J���O�@�ӷs��				
		
			// �ϥλ��k��ƽեΡA�B�z�ӷs��
			ProcessNextObjectChunk(pModel, pObject, &currentChunk);
			break;

		case OBJECT_VERTICES:		// Ū�J�O�ﹳ���I		
			ReadVertices(pObject, &currentChunk);// Ū�ﹳ���I
			break;

		case OBJECT_FACES:		// Ū�J���O��H����			
			ReadVertexIndices(pObject, &currentChunk);// Ū�J��H����
			break;

		case OBJECT_MATERIAL:			// Ū�J���O��H������W��		
			// �Ӷ��O�s�F��H���誺�W�١A�i��O�@���C��A�]�i��O�@�ӯ��z�M�g�C�P�ɦb�Ӷ����]�O�s�F
			// ���z�ﹳ�ҽᤩ����
			
			// �U��Ū�J��H������W��
			ReadObjectMaterial(pModel, pObject, &currentChunk,&vctMatIDS);			
			break;

		case OBJECT_UV:				// Ū�J��H��UV���z����			

			// Ū�J��H��UV���z����
			ReadUVCoordinates(pObject, &currentChunk);
			break;

//		case 0x4111: 
//			
//			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
//			break;
		default:   	// ���L���ݭnŪ�J����
			
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
		}

		// �K�[�q�̫����Ū�J���r�`�ƨ�e����Ū�J���r�`��
		pPreviousChunk->bytesRead += currentChunk.bytesRead;

	}
	if(pPreviousChunk->ID!=OBJECT_MESH) return;
	
	int size=vctMatIDS.size();
	if(size)
	{
		pObject->numOfMaterials=size; //��H������ƶq
		pObject->pMaterialREFS=new tMatREF[size];
		for(int i=0;i<size;i++)
		{
			pObject->pMaterialREFS[i]=*(vctMatIDS[i]);
		}
		vctMatIDS.clear();
	}
}


//  �U������ƳB�z�Ҧ�������H��
void CLoad3DS::ProcessNextMaterialChunk(CLoad3DS::t3DModel *pModel, CLoad3DS::tChunk *pPreviousChunk)
{
	
	tChunk currentChunk = {0};// �ΨӲK�[���e�����	

	// �~��Ū�J�o�Ƕ��A����Ӥl������
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		// Ū�J�U�@��
		ReadChunk(&currentChunk);

		// �P�_Ū�J���O�����
		switch (currentChunk.ID)
		{
		case MATNAME:					// ���誺�W��			
			
			// Ū�J���誺�W��
			currentChunk.bytesRead += fread(pModel->vctMaterials[pModel->numOfMaterials - 1].strName, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
			
		case MAT_AMBIENT:		//���誺���ҥ�
			ReadColorChunk(&(pModel->vctMaterials[pModel->numOfMaterials - 1]), &currentChunk,MAT_AMBIENT);
			break;
		case MAT_SPECULAR:		//���誺�譱��
			ReadColorChunk(&(pModel->vctMaterials[pModel->numOfMaterials - 1]), &currentChunk,MAT_SPECULAR);
			break;
		case MAT_EMISSIVE:		 //���誺�X�g��
			ReadColorChunk(&(pModel->vctMaterials[pModel->numOfMaterials - 1]), &currentChunk,MAT_EMISSIVE);
			break;
		case MATDIFFUSE:		//���誺���Ϯg��				
			ReadColorChunk(&(pModel->vctMaterials[pModel->numOfMaterials - 1]), &currentChunk,MATDIFFUSE);
			break;
		
		case MATMAP:			// ���z�H�����Y��					
			
			// �i�J�U�@�ӧ�����H��
			ProcessNextMaterialChunk(pModel, &currentChunk);
			break;

		case MATMAPFILE:	// �����󪺦W��					

			// Ū�J���誺���W��
			currentChunk.bytesRead += fread(pModel->vctMaterials[pModel->numOfMaterials - 1].strFile, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
		
		default:  

			// ���L���ݭnŪ�J����
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
		}

		// �K�[�q�̫����Ū�J���r�`��
		pPreviousChunk->bytesRead += currentChunk.bytesRead;
	}
}

//  �U�����Ū�J����ID���M�����r�`����
void CLoad3DS::ReadChunk(CLoad3DS::tChunk *pChunk)
{
	// Ū�J����ID���A���ΤF2�Ӧr�`�C����ID���HOBJECT��MATERIAL�@�ˡA�����F�b�����ҥ]�t�����e
	pChunk->bytesRead = fread(&pChunk->ID, 1, 2, m_FilePointer);

	// �M��Ū�J�����Ϊ����סA�]�t�F�|�Ӧr�`
	pChunk->bytesRead += fread(&pChunk->length, 1, 4, m_FilePointer);
}


//  �U�������Ū�J�@�Ӧr�Ŧ�
int CLoad3DS::GetString(char *pBuffer)
{
	int index = 0;

	
	// Ū�J�@�Ӧr�`���ƾ�
	fread(pBuffer, 1, 1, m_FilePointer);

	// ���쵲��
	while (*(pBuffer + index++) != 0) 
	{
		// Ū�J�@�Ӧr�Ū���NULL
		fread(pBuffer + index, 1, 1, m_FilePointer);
	}

	// ��^�r�Ŧꪺ����
	return strlen(pBuffer) + 1;
}


//  �U�������Ū�JRGB�C��
void CLoad3DS::ReadColorChunk(CLoad3DS::tMaterialInfo *pMaterial, CLoad3DS::tChunk *pChunk,USHORT typeFlag)
{
	tChunk tempChunk = {0};
	BYTE btmp[3];

	// Ū�J�C����H��
	ReadChunk(&tempChunk);
	switch(typeFlag)
	{
	case MAT_AMBIENT://���誺���ҥ��C��
		tempChunk.bytesRead += fread(btmp, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);
		Bytes2Floats(btmp,pMaterial->ambient,3,1.0f/256.0f);
		pMaterial->ambient[3]=1.0f;
		break;		
	case MAT_SPECULAR://���誺�譱���C��
		tempChunk.bytesRead += fread(btmp, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);
		Bytes2Floats(btmp,pMaterial->specular,3,1.0f/256.0f);
		pMaterial->specular[3]=1.0f;
		break;
	case MAT_EMISSIVE://���誺�X�g���C��
		tempChunk.bytesRead += fread(btmp, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);
		
		memset(btmp,0,3);
		
		Bytes2Floats(btmp,pMaterial->emissive,3,1.0f/256.0f);
		pMaterial->emissive[3]=1.0f;
		break;
	case MATDIFFUSE://���誺���Ϯg���C��
	default:
		
		tempChunk.bytesRead += fread(pMaterial->color, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);
		Bytes2Floats(pMaterial->color,pMaterial->diffuse,3,1.0f/256.0f);
		pMaterial->diffuse[3]=1.0f;
		break;
	}

	// �W�[Ū�J���r�`��
	pChunk->bytesRead += tempChunk.bytesRead;
}

//  �U�������Ū�J���I����
void CLoad3DS::ReadVertexIndices(CLoad3DS::t3DObject *pObject, CLoad3DS::tChunk *pPreviousChunk)
{
	unsigned short index = 0;		// �Ω�Ū�J��e��������				

	// Ū�J�ӹﹳ�������ƥ�
	pPreviousChunk->bytesRead += fread(&pObject->numOfFaces, 1, 2, m_FilePointer);

	// ���t�Ҧ������s�x�Ŷ��A�ê�l�Ƶ��c
	pObject->pFaces = new tFace [pObject->numOfFaces];
	memset(pObject->pFaces, 0, sizeof(tFace) * pObject->numOfFaces);

	
	// �M���ﹳ���Ҧ�����
	for(int i = 0; i < pObject->numOfFaces; i++)
	{
		
		
		for(int j = 0; j < 4; j++)
		{
			// Ū�J��e�����Ĥ@���I
			pPreviousChunk->bytesRead += fread(&index, 1, sizeof(index), m_FilePointer);

			if(j < 3)
			{
				// �N���ޫO�s�b�������c��
				pObject->pFaces[i].vertIndex[j] = index;
			}
		}
	}
}


 
//  �U�������Ū�J��H��UV����
void CLoad3DS::ReadUVCoordinates(t3DObject *pObject, tChunk *pPreviousChunk)
{
	
	// ���FŪ�J��H��UV���СA�����ݭnŪ�JUV���Ъ��ƶq�A�M��~Ū�J���骺�ƾ�
	
	// Ū�JUV���Ъ��ƶq
	pPreviousChunk->bytesRead += fread(&pObject->numTexVertex, 1, 2, m_FilePointer);

	// ���t�O�sUV���Ъ����s�Ŷ�
	pObject->pTexVerts = new CVector2 [pObject->numTexVertex];

	// Ū�J���z����
	pPreviousChunk->bytesRead += fread(pObject->pTexVerts, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);
}


//  Ū�J��H�����I����
void CLoad3DS::ReadVertices(CLoad3DS::t3DObject *pObject, CLoad3DS::tChunk *pPreviousChunk)
{
	
	
	// �bŪ�J��ڪ����I���e�A���������T�w�ݭnŪ�J�h�֭ӳ��I�C
	
	// Ū�J���I���ƥ�
	pPreviousChunk->bytesRead += fread(&(pObject->numOfVerts), 1, 2, m_FilePointer);

	// ���t���I���s�x�Ŷ��A�M���l�Ƶ��c��
	pObject->pVerts = new CVector3 [pObject->numOfVerts];
	memset(pObject->pVerts, 0, sizeof(CVector3) * pObject->numOfVerts);

	
	// Ū�J���I�ǦC
	pPreviousChunk->bytesRead += fread(pObject->pVerts, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);

	
	
   //��l�ƹ�H���̤p�M�̤jx,y,z����
	pObject->m_minX=999999; pObject->m_maxX=-99999;
	pObject->m_minY=999999; pObject->m_maxY=-99999;
	pObject->m_minZ=999999; pObject->m_maxZ=-99999;

	// �{�b�w�gŪ�J�F�Ҧ������I�C
	// �]��3D Studio Max���ҫ���Z�b�O���V�W���A�]���ݭn�Ny�b�Mz�b½��L�ӡC
	// ���骺���k�O�NY�b�MZ�b�洫�A�M��NZ�b�ϦV�C
	
	// �M���Ҧ������I
	for(int i = 0; i < pObject->numOfVerts; i++)
	{
		
		// �O�sY�b����
		float fTempY = pObject->pVerts[i].y;

		
		// �]�mY�b���ȵ���Z�b����
		pObject->pVerts[i].y = pObject->pVerts[i].z;

		// �]�mZ�b���ȵ���-Y�b����
		pObject->pVerts[i].z = -fTempY;

		//�p���H���̤p�M�̤jx,y,z����
		if(pObject->m_minX>pObject->pVerts[i].x) pObject->m_minX=pObject->pVerts[i].x;
		if(pObject->m_maxX<pObject->pVerts[i].x) pObject->m_maxX=pObject->pVerts[i].x;
		if(pObject->m_minY>pObject->pVerts[i].y) pObject->m_minY=pObject->pVerts[i].y;
		if(pObject->m_maxY<pObject->pVerts[i].y) pObject->m_maxY=pObject->pVerts[i].y;
		if(pObject->m_minZ>pObject->pVerts[i].z) pObject->m_minZ=pObject->pVerts[i].z;
		if(pObject->m_maxZ<pObject->pVerts[i].z) pObject->m_maxZ=pObject->pVerts[i].z;
		
	}
}

//  �U�������Ū�J��H������W��
void CLoad3DS::ReadObjectMaterial(CLoad3DS::t3DModel *pModel,CLoad3DS::t3DObject *pObject, CLoad3DS::tChunk *pPreviousChunk,vector<tMatREF*> *pvmatids)
{
	char strMaterial[255] = {0};	// �ΨӫO�s��H������W��		
	bool bmaterror=true;

	tMatREF *pMatref;
	pMatref=new tMatREF;
	
	// ����Ϊ̬O�C��A�Ϊ̬O��H�����z�A�]�i��O�s�F�H���G�סB�o���׵��H���C
	
	// �U��Ū�J�ᤩ��e��H������W��	
	pPreviousChunk->bytesRead += GetString(strMaterial);


	// �M���Ҧ������z
	for(int i = 0; i < pModel->numOfMaterials; i++)
	{
		//�p�GŪ�J�����z�P��e�����z�W�٤ǰt
		if(strcmp(strMaterial, pModel->vctMaterials[i].strName) == 0)
		{
			// �]�m����ID
			pObject->materialID = i;
			pMatref->nMaterialID=i;
			
			// �P�_�O�_�O���z�M�g�A�p�GstrFile�O�@�Ӫ��פj��1���r�Ŧ�A�h�O���z
			if(strlen(pModel->vctMaterials[i].strFile) > 0) 
			{
				// �]�m��H�����z�M�g�лx
				pObject->bHasTexture = true;
				pMatref->bHasTexture=true;
			}	
			bmaterror=false;
			break;
		}
		else
		{
			// �p�G�ӹﹳ�S������A�h�]�mID��-1
			pObject->materialID = -1;
			pMatref->nMaterialID=-1;
			bmaterror=true;
		}
	}
 	
	pPreviousChunk->bytesRead += fread(gBuffer, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);
	if(!bmaterror)
	{
		pMatref->nFaceNum=gBuffer[0]&0x0000FFFF;
		pMatref->pFaceIndexs=new USHORT[pMatref->nFaceNum];
		memcpy(pMatref->pFaceIndexs,2+(BYTE*)gBuffer,pMatref->nFaceNum*sizeof(USHORT));
		
		pvmatids->push_back(pMatref);
	}
 
}			

 
 
//  �U������ƥΩ�p���H���k�V�q
void CLoad3DS::ComputeNormals(CLoad3DS::t3DModel *pModel)
{
	CVector3 vVector1, vVector2, vNormal, vPoly[3];

	// �p�G�ҫ����S����H�A�h��^	
	if(pModel->numOfObjects <= 0)
		return;

	
	// �M���ҫ����Ҧ�����H
	for(int index = 0; index < pModel->numOfObjects; index++)
	{
		
		// ��o��e����H
		t3DObject *pObject = &(pModel->vctObjects[index]);

		// ���t�ݭn���s�x�Ŷ�
		CVector3 *pNormals		= new CVector3 [pObject->numOfFaces];
		CVector3 *pTempNormals	= new CVector3 [pObject->numOfFaces];
		pObject->pNormals		= new CVector3 [pObject->numOfVerts];

		// �M����H���Ҧ���
		for(int i=0; i < pObject->numOfFaces; i++)
		{												
			
			vPoly[0] = pObject->pVerts[pObject->pFaces[i].vertIndex[0]];
			vPoly[1] = pObject->pVerts[pObject->pFaces[i].vertIndex[1]];
			vPoly[2] = pObject->pVerts[pObject->pFaces[i].vertIndex[2]];

			
			// �p�⭱���k�V�q
			vVector1 = Vector(vPoly[0], vPoly[2]);	// ��o�h��Ϊ��ڶq	
			vVector2 = Vector(vPoly[2], vPoly[1]);// ��o�h��Ϊ��ĤG�ӥڶq		

			vNormal  = Cross(vVector1, vVector2);		// ��o��ӥڶq���e�n	
			pTempNormals[i] = vNormal;				// �O�s�D�W�d�ƪk�V�q	
			vNormal  = Normalize(vNormal);		// �W�d����o���e�n		

			pNormals[i] = vNormal;				// �N�k�V�q�K�[��k�V�q�C��			
		}

		
		//  �U���D���I�k�V�q
		CVector3 vSum (0.0, 0.0, 0.0);
		CVector3 vZero = vSum;
		int shared=0;

		// �M���Ҧ������I
		for (i = 0; i < pObject->numOfVerts; i++)			
		{
			for (int j = 0; j < pObject->numOfFaces; j++)	// �M���Ҧ����T���έ�
			{												
				// �P�_���I�O�_�P�䥦�����@��
				if (pObject->pFaces[j].vertIndex[0] == i || 
					pObject->pFaces[j].vertIndex[1] == i || 
					pObject->pFaces[j].vertIndex[2] == i)
				{
					vSum =vSum+pTempNormals[j];
					shared++;								
				}
			}      
			
			
			pObject->pNormals[i] = vSum/float(-shared);

			// �W�d�Ƴ̫᪺���I�k�V
			pObject->pNormals[i] = Normalize(pObject->pNormals[i]);	

			vSum = vZero;									
			shared = 0;										
		}
	
		// ����s�x�Ŷ��A�}�l�U�@�ӹﹳ
		delete [] pTempNormals;
		delete [] pNormals;
	}
}

//�r�`�Ʋը�B�I��� 
void CLoad3DS::Bytes2Floats(BYTE *pbs, float *pfs, int num, float fsk)
{
	if(num==0||num>100)return;
	for(int i=0;i<num;i++)
	{
		pfs[i]=float(pbs[i])*fsk;
	}
}


/*
�ȱo�`�N���OOpenGL�����Шt�M3DS Max�����Шt�O���P���A3D Studio Max�����ҫ���Z�b�O���V�W���A
��OpenGL���ҫ���Z�b�O�����̹����V�Τ᪺�A�]���ݭn�N���I�����Ъ�y�Mz½��L�ӡC
����O���H
��ID�O���ѸӶ����ƾ��������W�@�L�G���N�X�A�P�ɤ]���ѬO�_�s�b�l���C�����ΤF��Ӧr�`�C
�������ת�ܪ��O���b�Ӷ����򪺼ƾڪ����סC�����ΤF�|�Ӧr�`�C

*/