 
 

#if !defined(AFX_OCICLASS_H__47132327_6B59_4F52_91DA_E8A340543870__INCLUDED_)
#define AFX_OCICLASS_H__47132327_6B59_4F52_91DA_E8A340543870__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COCIclass  
{
public:

	OCIEnv *envhp;		//環境句柄
	OCIError *errhp;	//錯誤句柄
	OCIServer *srvhp;	//服務器句柄	
	OCISvcCtx *svchp;	//服務上下文句柄	
	OCISession *authp;	//任務句柄	
	OCIStmt *stmthp;	//描述句柄
	OCIDefine *defhp;	//定義句柄	
	OCILobLocator *lobsingle,*lob_loc[2];	//位置標識符句柄
	OCIBind *bndhp,*bndhp2;	//綁定句柄
	
	OCIDefine	*defhps[20];		
	OCIBind		*bidhp [20];	
	OCIParam	*colhp;			
	text		*colbuf[30];  	
	sb2			ind[30];		
	ub4			col_num;		
	sword status;           

	BOOL ReadBOLBDataFromDB(CString strFilename, CString strSQL,int m_ID);
	BOOL AddBOLBDataToDB(CString strFilename,CString strSQL,int m_ID);
	BOOL AddNormalDataToDB(CString strSQL);
	void Init_OCI();
	
	
	COCIclass();
	virtual ~COCIclass();

private:
	BOOL CallbackReadLob();
	int CallbackWriteToLob();
	void Error_proc(dvoid *errhp, sword status);
	
};

#endif // !defined(AFX_OCICLASS_H__47132327_6B59_4F52_91DA_E8A340543870__INCLUDED_)
