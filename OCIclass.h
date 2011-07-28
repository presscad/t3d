 
 

#if !defined(AFX_OCICLASS_H__47132327_6B59_4F52_91DA_E8A340543870__INCLUDED_)
#define AFX_OCICLASS_H__47132327_6B59_4F52_91DA_E8A340543870__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COCIclass  
{
public:

	OCIEnv *envhp;		//���ҥy�`
	OCIError *errhp;	//���~�y�`
	OCIServer *srvhp;	//�A�Ⱦ��y�`	
	OCISvcCtx *svchp;	//�A�ȤW�U��y�`	
	OCISession *authp;	//���ȥy�`	
	OCIStmt *stmthp;	//�y�z�y�`
	OCIDefine *defhp;	//�w�q�y�`	
	OCILobLocator *lobsingle,*lob_loc[2];	//��m���Ѳťy�`
	OCIBind *bndhp,*bndhp2;	//�j�w�y�`
	
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
