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

 
 
//  打開一個3ds文件，讀出其中的內容，並釋放內存
bool CLoad3DS::Import3DS(CLoad3DS::t3DModel *pModel, char *strFileName)
{
	char strMessage[255] = {0};
	tChunk currentChunk = {0};
	int i=0;

	// 打開一個3ds文件
	m_FilePointer = fopen(strFileName, "rb");

	
	// 確保所獲得的文件指針合法
	if(!m_FilePointer) 
	{
		sprintf(strMessage, "找不到文件: %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}

	// 當文件打開之後，首先應該將文件最開始的數據塊讀出以判斷是否是一個3ds文件
	// 如果是3ds文件的話，第一個塊ID應該是PRIMARY
	
	// 將文件的第一塊讀出並判斷是否是3ds文件
	ReadChunk(&currentChunk);

	// 確保是3ds文件
	if (currentChunk.ID != PRIMARY)
	{
		sprintf(strMessage, "Unable to load PRIMARY chuck from file: %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}

	
	// 現在開始讀入數據，ProcessNextChunk()是一個遞歸函數
	
	// 通過調用下面的遞歸函數，將對像讀出
	ProcessNextChunk(pModel, &currentChunk);

	
	// 在讀完整個3ds文件之後，計算頂點的法線
	ComputeNormals(pModel);

	// 釋放內存空間
	CleanUp();

	return true;
}


//  下面的函數釋放所有的內存空間，並關閉文件
void CLoad3DS::CleanUp()
{
	if (m_FilePointer) 
	{
		fclose(m_FilePointer);		// 關閉當前的文件指針				
		m_FilePointer = NULL;  //文件指針為空
	}
}

 
//  下面的函數讀出3ds文件的主要部分(是個遞歸函數)
void CLoad3DS::ProcessNextChunk(CLoad3DS::t3DModel *pModel, tChunk *pPreviousChunk)
{
	t3DObject newObject = {0};			// 用來添加到對像鏈表		
	tMaterialInfo newTexture = {0};		// 用來添加到材質鏈表		

	tChunk currentChunk = {0};			// 用來添加到當前塊鏈表		
	tChunk tempChunk = {0};			// 用來添加到臨時塊鏈表		

	//  下面每讀一個新塊，都要判斷一下塊的ID，如果該塊是需要的讀入的，則繼續進行
	//  如果是不需要讀入的塊，則略過

	// 繼續讀入子塊，直到達到預定的長度
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		
		ReadChunk(&currentChunk);	// 讀入下一個塊

		// 判斷塊的ID號
		switch (currentChunk.ID)
		{
		case VERSION:		// 文件版本號					
			// 在該塊中有一個無符號短整型數保存了文件的版本
			
			// 讀入文件的版本號，並將字節數添加到bytesRead變量中	
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
		
			// 如果文件版本號大於3，給出一個警告信息
			if ((currentChunk.length - currentChunk.bytesRead == 4) && (gBuffer[0] > 0x03)) 
			{
				MessageBox(NULL, "3DS文件版本號大於3，有可能讀取不正確！", "警告", MB_OK);
			}
			break;

		case OBJECTINFO:		 // 網格版本信息				
				
			ReadChunk(&tempChunk);// 讀入下一個塊
			
			// 獲得網格的版本號
			tempChunk.bytesRead += fread(gBuffer, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);

			// 增加讀入的字節數
			currentChunk.bytesRead += tempChunk.bytesRead;

			// 進入下一個塊
			ProcessNextChunk(pModel, &currentChunk);
			break;
		case MATERIAL:			// 材質信息				
	
			// 材質的數目遞增
			pModel->numOfMaterials++;
			
			// 在紋理鏈表中添加一個空白紋理結構
			pModel->vctMaterials.push_back(newTexture);
		
			// 進入材質裝入函數
			ProcessNextMaterialChunk(pModel, &currentChunk);
		
			break;

		case OBJECT:			// 對象的名稱			
			// 該塊是對像信息塊的頭部，保存了對象了名稱
			
			pModel->numOfObjects++;// 對像數遞增
		
			// 添加一個新的tObject節點到對像鏈表中
			pModel->vctObjects.push_back(newObject); 
		
			// 初始化對像和它的所有數據成員
			memset(&(pModel->vctObjects[pModel->numOfObjects - 1]), 0, sizeof(t3DObject));

			// 獲得並保存對象的名稱，然後增加讀入的字節數
			currentChunk.bytesRead += GetString(pModel->vctObjects[pModel->numOfObjects - 1].strName);
			
			// 進入其餘的對象信息的讀入
			ProcessNextObjectChunk(pModel, &(pModel->vctObjects[pModel->numOfObjects - 1]), &currentChunk);
			break;

		case EDITKEYFRAME:
			// 跳過關鍵幀塊的讀入，增加需要讀入的字節數
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;

		default: 
			//  跳過所有忽略的塊的內容的讀入，增加需要讀入的字節數
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
		}
	
		// 增加從最後塊讀入的字節數
		pPreviousChunk->bytesRead += currentChunk.bytesRead;
	}

}

//  下面的函數處理所有的文件中對象的信息
void CLoad3DS::ProcessNextObjectChunk(CLoad3DS::t3DModel *pModel, CLoad3DS::t3DObject *pObject, CLoad3DS::tChunk *pPreviousChunk)
{
	
	tChunk currentChunk = {0};// 用來添加到當前塊鏈表		
	vector<tMatREF*> vctMatIDS;
	
	// 繼續讀入塊的內容直至本子塊結束
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		// 讀入下一個塊
		ReadChunk(&currentChunk);

		// 區別讀入是哪種塊
		switch (currentChunk.ID)
		{
		case OBJECT_MESH:	 	// 正讀入的是一個新塊				
		
			// 使用遞歸函數調用，處理該新塊
			ProcessNextObjectChunk(pModel, pObject, &currentChunk);
			break;

		case OBJECT_VERTICES:		// 讀入是對像頂點		
			ReadVertices(pObject, &currentChunk);// 讀對像頂點
			break;

		case OBJECT_FACES:		// 讀入的是對象的面			
			ReadVertexIndices(pObject, &currentChunk);// 讀入對象的面
			break;

		case OBJECT_MATERIAL:			// 讀入的是對象的材質名稱		
			// 該塊保存了對象材質的名稱，可能是一個顏色，也可能是一個紋理映射。同時在該塊中也保存了
			// 紋理對像所賦予的面
			
			// 下面讀入對象的材質名稱
			ReadObjectMaterial(pModel, pObject, &currentChunk,&vctMatIDS);			
			break;

		case OBJECT_UV:				// 讀入對象的UV紋理坐標			

			// 讀入對象的UV紋理坐標
			ReadUVCoordinates(pObject, &currentChunk);
			break;

//		case 0x4111: 
//			
//			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
//			break;
		default:   	// 略過不需要讀入的塊
			
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
		}

		// 添加從最後塊中讀入的字節數到前面的讀入的字節中
		pPreviousChunk->bytesRead += currentChunk.bytesRead;

	}
	if(pPreviousChunk->ID!=OBJECT_MESH) return;
	
	int size=vctMatIDS.size();
	if(size)
	{
		pObject->numOfMaterials=size; //對象的材質數量
		pObject->pMaterialREFS=new tMatREF[size];
		for(int i=0;i<size;i++)
		{
			pObject->pMaterialREFS[i]=*(vctMatIDS[i]);
		}
		vctMatIDS.clear();
	}
}


//  下面的函數處理所有的材質信息
void CLoad3DS::ProcessNextMaterialChunk(CLoad3DS::t3DModel *pModel, CLoad3DS::tChunk *pPreviousChunk)
{
	
	tChunk currentChunk = {0};// 用來添加到當前塊鏈表	

	// 繼續讀入這些塊，直到該子塊結束
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		// 讀入下一塊
		ReadChunk(&currentChunk);

		// 判斷讀入的是什麼塊
		switch (currentChunk.ID)
		{
		case MATNAME:					// 材質的名稱			
			
			// 讀入材質的名稱
			currentChunk.bytesRead += fread(pModel->vctMaterials[pModel->numOfMaterials - 1].strName, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
			
		case MAT_AMBIENT:		//材質的環境光
			ReadColorChunk(&(pModel->vctMaterials[pModel->numOfMaterials - 1]), &currentChunk,MAT_AMBIENT);
			break;
		case MAT_SPECULAR:		//材質的鏡面光
			ReadColorChunk(&(pModel->vctMaterials[pModel->numOfMaterials - 1]), &currentChunk,MAT_SPECULAR);
			break;
		case MAT_EMISSIVE:		 //材質的出射光
			ReadColorChunk(&(pModel->vctMaterials[pModel->numOfMaterials - 1]), &currentChunk,MAT_EMISSIVE);
			break;
		case MATDIFFUSE:		//材質的漫反射光				
			ReadColorChunk(&(pModel->vctMaterials[pModel->numOfMaterials - 1]), &currentChunk,MATDIFFUSE);
			break;
		
		case MATMAP:			// 紋理信息的頭部					
			
			// 進入下一個材質塊信息
			ProcessNextMaterialChunk(pModel, &currentChunk);
			break;

		case MATMAPFILE:	// 材質文件的名稱					

			// 讀入材質的文件名稱
			currentChunk.bytesRead += fread(pModel->vctMaterials[pModel->numOfMaterials - 1].strFile, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
		
		default:  

			// 掠過不需要讀入的塊
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
		}

		// 添加從最後塊中讀入的字節數
		pPreviousChunk->bytesRead += currentChunk.bytesRead;
	}
}

//  下面函數讀入塊的ID號和它的字節長度
void CLoad3DS::ReadChunk(CLoad3DS::tChunk *pChunk)
{
	// 讀入塊的ID號，佔用了2個字節。塊的ID號象OBJECT或MATERIAL一樣，說明了在塊中所包含的內容
	pChunk->bytesRead = fread(&pChunk->ID, 1, 2, m_FilePointer);

	// 然後讀入塊佔用的長度，包含了四個字節
	pChunk->bytesRead += fread(&pChunk->length, 1, 4, m_FilePointer);
}


//  下面的函數讀入一個字符串
int CLoad3DS::GetString(char *pBuffer)
{
	int index = 0;

	
	// 讀入一個字節的數據
	fread(pBuffer, 1, 1, m_FilePointer);

	// 直到結束
	while (*(pBuffer + index++) != 0) 
	{
		// 讀入一個字符直到NULL
		fread(pBuffer + index, 1, 1, m_FilePointer);
	}

	// 返回字符串的長度
	return strlen(pBuffer) + 1;
}


//  下面的函數讀入RGB顏色
void CLoad3DS::ReadColorChunk(CLoad3DS::tMaterialInfo *pMaterial, CLoad3DS::tChunk *pChunk,USHORT typeFlag)
{
	tChunk tempChunk = {0};
	BYTE btmp[3];

	// 讀入顏色塊信息
	ReadChunk(&tempChunk);
	switch(typeFlag)
	{
	case MAT_AMBIENT://材質的環境光顏色
		tempChunk.bytesRead += fread(btmp, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);
		Bytes2Floats(btmp,pMaterial->ambient,3,1.0f/256.0f);
		pMaterial->ambient[3]=1.0f;
		break;		
	case MAT_SPECULAR://材質的鏡面光顏色
		tempChunk.bytesRead += fread(btmp, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);
		Bytes2Floats(btmp,pMaterial->specular,3,1.0f/256.0f);
		pMaterial->specular[3]=1.0f;
		break;
	case MAT_EMISSIVE://材質的出射光顏色
		tempChunk.bytesRead += fread(btmp, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);
		
		memset(btmp,0,3);
		
		Bytes2Floats(btmp,pMaterial->emissive,3,1.0f/256.0f);
		pMaterial->emissive[3]=1.0f;
		break;
	case MATDIFFUSE://材質的漫反射光顏色
	default:
		
		tempChunk.bytesRead += fread(pMaterial->color, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);
		Bytes2Floats(pMaterial->color,pMaterial->diffuse,3,1.0f/256.0f);
		pMaterial->diffuse[3]=1.0f;
		break;
	}

	// 增加讀入的字節數
	pChunk->bytesRead += tempChunk.bytesRead;
}

//  下面的函數讀入頂點索引
void CLoad3DS::ReadVertexIndices(CLoad3DS::t3DObject *pObject, CLoad3DS::tChunk *pPreviousChunk)
{
	unsigned short index = 0;		// 用於讀入當前面的索引				

	// 讀入該對像中面的數目
	pPreviousChunk->bytesRead += fread(&pObject->numOfFaces, 1, 2, m_FilePointer);

	// 分配所有面的存儲空間，並初始化結構
	pObject->pFaces = new tFace [pObject->numOfFaces];
	memset(pObject->pFaces, 0, sizeof(tFace) * pObject->numOfFaces);

	
	// 遍歷對像中所有的面
	for(int i = 0; i < pObject->numOfFaces; i++)
	{
		
		
		for(int j = 0; j < 4; j++)
		{
			// 讀入當前面的第一個點
			pPreviousChunk->bytesRead += fread(&index, 1, sizeof(index), m_FilePointer);

			if(j < 3)
			{
				// 將索引保存在面的結構中
				pObject->pFaces[i].vertIndex[j] = index;
			}
		}
	}
}


 
//  下面的函數讀入對象的UV坐標
void CLoad3DS::ReadUVCoordinates(t3DObject *pObject, tChunk *pPreviousChunk)
{
	
	// 為了讀入對象的UV坐標，首先需要讀入UV坐標的數量，然後才讀入具體的數據
	
	// 讀入UV坐標的數量
	pPreviousChunk->bytesRead += fread(&pObject->numTexVertex, 1, 2, m_FilePointer);

	// 分配保存UV坐標的內存空間
	pObject->pTexVerts = new CVector2 [pObject->numTexVertex];

	// 讀入紋理坐標
	pPreviousChunk->bytesRead += fread(pObject->pTexVerts, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);
}


//  讀入對象的頂點坐標
void CLoad3DS::ReadVertices(CLoad3DS::t3DObject *pObject, CLoad3DS::tChunk *pPreviousChunk)
{
	
	
	// 在讀入實際的頂點之前，首先必須確定需要讀入多少個頂點。
	
	// 讀入頂點的數目
	pPreviousChunk->bytesRead += fread(&(pObject->numOfVerts), 1, 2, m_FilePointer);

	// 分配頂點的存儲空間，然後初始化結構體
	pObject->pVerts = new CVector3 [pObject->numOfVerts];
	memset(pObject->pVerts, 0, sizeof(CVector3) * pObject->numOfVerts);

	
	// 讀入頂點序列
	pPreviousChunk->bytesRead += fread(pObject->pVerts, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);

	
	
   //初始化對象的最小和最大x,y,z坐標
	pObject->m_minX=999999; pObject->m_maxX=-99999;
	pObject->m_minY=999999; pObject->m_maxY=-99999;
	pObject->m_minZ=999999; pObject->m_maxZ=-99999;

	// 現在已經讀入了所有的頂點。
	// 因為3D Studio Max的模型的Z軸是指向上的，因此需要將y軸和z軸翻轉過來。
	// 具體的做法是將Y軸和Z軸交換，然後將Z軸反向。
	
	// 遍歷所有的頂點
	for(int i = 0; i < pObject->numOfVerts; i++)
	{
		
		// 保存Y軸的值
		float fTempY = pObject->pVerts[i].y;

		
		// 設置Y軸的值等於Z軸的值
		pObject->pVerts[i].y = pObject->pVerts[i].z;

		// 設置Z軸的值等於-Y軸的值
		pObject->pVerts[i].z = -fTempY;

		//計算對象的最小和最大x,y,z坐標
		if(pObject->m_minX>pObject->pVerts[i].x) pObject->m_minX=pObject->pVerts[i].x;
		if(pObject->m_maxX<pObject->pVerts[i].x) pObject->m_maxX=pObject->pVerts[i].x;
		if(pObject->m_minY>pObject->pVerts[i].y) pObject->m_minY=pObject->pVerts[i].y;
		if(pObject->m_maxY<pObject->pVerts[i].y) pObject->m_maxY=pObject->pVerts[i].y;
		if(pObject->m_minZ>pObject->pVerts[i].z) pObject->m_minZ=pObject->pVerts[i].z;
		if(pObject->m_maxZ<pObject->pVerts[i].z) pObject->m_maxZ=pObject->pVerts[i].z;
		
	}
}

//  下面的函數讀入對象的材質名稱
void CLoad3DS::ReadObjectMaterial(CLoad3DS::t3DModel *pModel,CLoad3DS::t3DObject *pObject, CLoad3DS::tChunk *pPreviousChunk,vector<tMatREF*> *pvmatids)
{
	char strMaterial[255] = {0};	// 用來保存對象的材質名稱		
	bool bmaterror=true;

	tMatREF *pMatref;
	pMatref=new tMatREF;
	
	// 材質或者是顏色，或者是對象的紋理，也可能保存了象明亮度、發光度等信息。
	
	// 下面讀入賦予當前對象的材質名稱	
	pPreviousChunk->bytesRead += GetString(strMaterial);


	// 遍歷所有的紋理
	for(int i = 0; i < pModel->numOfMaterials; i++)
	{
		//如果讀入的紋理與當前的紋理名稱匹配
		if(strcmp(strMaterial, pModel->vctMaterials[i].strName) == 0)
		{
			// 設置材質ID
			pObject->materialID = i;
			pMatref->nMaterialID=i;
			
			// 判斷是否是紋理映射，如果strFile是一個長度大於1的字符串，則是紋理
			if(strlen(pModel->vctMaterials[i].strFile) > 0) 
			{
				// 設置對象的紋理映射標誌
				pObject->bHasTexture = true;
				pMatref->bHasTexture=true;
			}	
			bmaterror=false;
			break;
		}
		else
		{
			// 如果該對像沒有材質，則設置ID為-1
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

 
 
//  下面的函數用於計算對象的法向量
void CLoad3DS::ComputeNormals(CLoad3DS::t3DModel *pModel)
{
	CVector3 vVector1, vVector2, vNormal, vPoly[3];

	// 如果模型中沒有對象，則返回	
	if(pModel->numOfObjects <= 0)
		return;

	
	// 遍歷模型中所有的對象
	for(int index = 0; index < pModel->numOfObjects; index++)
	{
		
		// 獲得當前的對象
		t3DObject *pObject = &(pModel->vctObjects[index]);

		// 分配需要的存儲空間
		CVector3 *pNormals		= new CVector3 [pObject->numOfFaces];
		CVector3 *pTempNormals	= new CVector3 [pObject->numOfFaces];
		pObject->pNormals		= new CVector3 [pObject->numOfVerts];

		// 遍歷對象的所有面
		for(int i=0; i < pObject->numOfFaces; i++)
		{												
			
			vPoly[0] = pObject->pVerts[pObject->pFaces[i].vertIndex[0]];
			vPoly[1] = pObject->pVerts[pObject->pFaces[i].vertIndex[1]];
			vPoly[2] = pObject->pVerts[pObject->pFaces[i].vertIndex[2]];

			
			// 計算面的法向量
			vVector1 = Vector(vPoly[0], vPoly[2]);	// 獲得多邊形的矢量	
			vVector2 = Vector(vPoly[2], vPoly[1]);// 獲得多邊形的第二個矢量		

			vNormal  = Cross(vVector1, vVector2);		// 獲得兩個矢量的叉積	
			pTempNormals[i] = vNormal;				// 保存非規範化法向量	
			vNormal  = Normalize(vNormal);		// 規範化獲得的叉積		

			pNormals[i] = vNormal;				// 將法向量添加到法向量列表中			
		}

		
		//  下面求頂點法向量
		CVector3 vSum (0.0, 0.0, 0.0);
		CVector3 vZero = vSum;
		int shared=0;

		// 遍歷所有的頂點
		for (i = 0; i < pObject->numOfVerts; i++)			
		{
			for (int j = 0; j < pObject->numOfFaces; j++)	// 遍歷所有的三角形面
			{												
				// 判斷該點是否與其它的面共享
				if (pObject->pFaces[j].vertIndex[0] == i || 
					pObject->pFaces[j].vertIndex[1] == i || 
					pObject->pFaces[j].vertIndex[2] == i)
				{
					vSum =vSum+pTempNormals[j];
					shared++;								
				}
			}      
			
			
			pObject->pNormals[i] = vSum/float(-shared);

			// 規範化最後的頂點法向
			pObject->pNormals[i] = Normalize(pObject->pNormals[i]);	

			vSum = vZero;									
			shared = 0;										
		}
	
		// 釋放存儲空間，開始下一個對像
		delete [] pTempNormals;
		delete [] pNormals;
	}
}

//字節數組到浮點轉化 
void CLoad3DS::Bytes2Floats(BYTE *pbs, float *pfs, int num, float fsk)
{
	if(num==0||num>100)return;
	for(int i=0;i<num;i++)
	{
		pfs[i]=float(pbs[i])*fsk;
	}
}


/*
值得注意的是OpenGL的坐標系和3DS Max的坐標系是不同的，3D Studio Max中的模型的Z軸是指向上的，
而OpenGL中模型的Z軸是垂直屏幕指向用戶的，因此需要將頂點的坐標的y和z翻轉過來。
什麼是塊？
塊ID是標識該塊中數據類型的獨一無二的代碼，同時也標識是否存在子塊。它佔用了兩個字節。
塊的長度表示的是緊跟在該塊後續的數據的長度。它佔用了四個字節。

*/