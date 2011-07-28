// OCIclass.cpp: implementation of the COCIclass class.
 
 

#include "stdafx.h"
 
#include "OCIclass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 
// Construction/Destruction
 

FILE *fp_OCI;	//FILE���w,�V�ӥ��}�~�����
ub4 Filelength_OCI; //�s�x���}�~����󪺪���

/*
���F���@���g�J�L�h�ƾڡA�����w�q�@�ӽw�İϤj�pLOB_BUF_LEN�A��p�W�w��8192�C 
�p�G�g�J�ƾڤj�p�]size�^�bLOB_BUF_LEN�d�򤺡A�h�i�@���g���C 
*/
#define LOB_BUF_LEN  131072  
 
#define MAXLENGTH    4294967296 //�@��LOB�r�q�̤j�s�x���r�`��

 
//�H�^�դ覡�g�J�ƾ�
sb4 callback_writes_OCI(dvoid *ctxp,dvoid *bufxp,ub4 *lenp, ub1 *piece)
{
	ub4 piecelen;	
	static ub4 len=LOB_BUF_LEN;
	
	if((Filelength_OCI-len)>LOB_BUF_LEN) //�p�G��󪺪���-�C��Ū�g������>LOB_BUF_LEN
		piecelen=LOB_BUF_LEN;	//����Ū�g������=LOB_BUF_LEN
	else  //�p��󪺪���<�C��Ū�g������
		piecelen=Filelength_OCI-len; //����Ū�g������=��󪺪���-LOB_BUF_LEN
	
	*lenp=piecelen;
	
	//�}�lŪ���
	if(fread((void*)bufxp,(size_t)piecelen,1,fp_OCI)!=1)
	{
		AfxMessageBox("Ū�ƾڤ��o�Ϳ��~!");
		*piece=OCI_LAST_PIECE;
		len=LOB_BUF_LEN;
		return OCI_CONTINUE;
		
	}
	len+=piecelen;//�wŪ�������ײ֥[
	
	if(len==Filelength_OCI)  //�p�G�wŪ��������=����`����,��������Ū�ާ@
	{
		*piece=OCI_LAST_PIECE;//��e�����̫�@���лx�A��ܼg�̫�@��ƾ� 
		len=LOB_BUF_LEN;
	}
	else
		*piece=OCI_NEXT_PIECE;//�_�h,��e�����U�@���лx,����~��g�A�����g�̫�@�� 
	
	return OCI_CONTINUE;
}

 
//�H�^�դ覡Ū�J�ƾ�
sb4 callback_Read_OCI(dvoid *ctxp,CONST dvoid *bufxp,ub4 len,ub1 piece)
{
	static ub4 piece_count=0;
	piece_count++;
	switch(piece)
	{
	case OCI_LAST_PIECE://��ܼg�̫�@��ƾ� 
		fwrite((void*)bufxp,(size_t)len,1,fp_OCI);
		piece_count=0;
		return OCI_CONTINUE;
	case OCI_FIRST_PIECE://��ܼg�Ĥ@��
	case OCI_NEXT_PIECE://����~��g�A�����g�̫�@��
		fwrite((void*)bufxp,(size_t)len,1,fp_OCI);
		break;
	default:
		return OCI_ERROR;
	}
	
	return OCI_CONTINUE;
	
}

COCIclass::COCIclass()
{

}

COCIclass::~COCIclass()
{

}


//��l��OCI
void COCIclass::Init_OCI()
{
	//�Ы�OCI����,�Y�ЫةM��l��OCI�u�@���ҡA��L��OCI��ƻݭnOCI���Ҥ~�����C
	if(status=OCIEnvCreate(&envhp,OCI_DEFAULT,(dvoid *)0, 
		(dvoid* (*)(dvoid*,size_t))0,(dvoid* (*)(dvoid*,dvoid*,size_t))0,
		(void (*)(dvoid *, dvoid *)) 0, (size_t) 0,(dvoid **) 0 ))
	{
		MessageBox(NULL,"�Ы�OCI���ҥ���!","��l��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return ;		
	}
	/*
	1�D�Ы�OCI���� 
	sword OCIEnvCreate(   
	OCIEnv **envhpp,  //OCI���ҥy�`���w 
	ub4 mode, //��l�ƼҦ��GOCI_DEFAULT/OCI_THREADED �� 
	CONST dvoid *ctxp, 
	CONST dvoid *(*malicfp)(dvoid *ctxp,size_t size), 
	CONST dvoid *(ralocfp)(dvoid *ctxp,dvoid *memptr,size_t newsize), 
	CONST void *(*mfreefp)(dvoid *ctxp,dvoid *memptr), 
	Size_t xstramemsz, 
	Dvoid **usrmempp 
	) 

OCI��Ƴ]�m���Ҧ����G 
	OCI_DEFUALT:�ϥ�OCI�q�{������ 
	OCI_THREADED�G�u�{���ҤU�ϥ�OCI 
	OCI_OBJECT�G�ﹳ�Ҧ� 
	OCI_SHARED�G�@�ɼҦ� 
	OCI_EVENTS 
	OCI_NO_UCB 
	OCI_ENV_NO_MUTEX�G�D�����X�ݼҦ� 
	�䤤�Ҧ��i�H���޿�B��Ŷi�歡�[�A�N��Ƴ]�m���h�h�ؼҦ��G�pmode=OCI_SHREADED| OCI_OBJECT 

	*/

	//�ӽп��~�y�`
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&errhp,(ub4)OCI_HTYPE_ERROR,
		(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"�ӽп��~�y�`����!","��l��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return ;		
	}

	//�ӽЪA�Ⱦ��y�`
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&srvhp,
		(ub4)OCI_HTYPE_SERVER,(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"�ӽЪA�Ⱦ��y�`����!","��l��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return ;		
	}
	
	//�ӽЪA�����ҥy�`
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&svchp,
		(ub4)OCI_HTYPE_SVCCTX,(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"�ӽЪA�����ҥy�`����!","��l��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return ;		
	}
	
	//�ӽз|�ܥy�`
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&authp,
		(ub4)OCI_HTYPE_SESSION,(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"�ӽз|�ܥy�`����!","��l��OIC",MB_ICONINFORMATION);		
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return ;		
	}
	
	//�ӽлy�y�y�`
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&stmthp,
		(ub4)OCI_HTYPE_STMT,(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"�ӽлy�y�y�`����!","��l��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return ;		
	}
	
	/*
	2�D�ӽ�/����y�` 
	sword OCIHandleAlloc( 
		CONST dvoid *parenth,  //�s�ӽХy�`�����y�`�A�@�묰OCI���ҥy�` 
		Dvoid **hndlpp,   //�ӽЪ��s�y�` 
		Ub4 type, type,  //�y�`���� 
		Size_t xtramem_sz,   //�ӽЪ����s�� 
		Dvoid **usrmempp  //�ӽШ쪺���s�����w 
	) 
	���G 
	�@��ݭn�ӽЪ��y�`���G 
	�A�Ⱦ��y�`OCIServer, �y�`����OCI_HTYPE_SERVER 
	���~�y�`OCIError�A�Ω���OCI���~�H��, �y�`����OCI_HTYPE_ERROR 
	�ưȥy�`OCISession, �y�`����OCI_HTYPE_SESSION 
	�W�U��y�`OCISvcCtx, �y�`����OCI_HTYPE_SVCCTX 
	SQL�y�y�y�`OCIStmt, �y�`����OCI_HTYPE_STMT 
	*/

	/*
	����y�` 
	sword OCIHandleFree( 
	dvoid *hndlp,  //�n���񪺥y�` 
	ub4 type   //�y�`���� 
	) 
	*/

	//�ӽ�2��LOB�����,�Ω��BLOB�����ƾڼg�J��Ū���ާ@�C�ΰѼ�OCI_DTYPE_LOB�A��o�@��LOB���y�`
	for(int i=0;i<2;i++)
	{
		if(status=OCIDescriptorAlloc((dvoid*)envhp,(dvoid**)&lob_loc[i],(ub4)OCI_DTYPE_LOB,
			(size_t)0,(dvoid**)0))
		{
			MessageBox(NULL,"�ӽ�LOB����ť���!","��l��OIC",MB_ICONINFORMATION);
			Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
			return ;		
		}
 	}

	/*
	12�D ���X����ũM���ܾ��ܶq�G 
	����šG�b�{�Ǥ��A�@��SQL�y�y�ݭn�b�{�ǹB��ɤ~��T�w�����y�y�ƾڡA�b�]�p��
	�i�Τ@�Ӧ���ŨӥN���A��{�ǹB��ɡA�b���ǳƦn�y�y��A�������C�Ӧ���ū��w�@���ܶq�A
	�Y�N����ŻP�{���ܶq�a�}���X�A����ɡAOracle�N�q�o���ܶq��Ū���ƾڡA�ñN����
	�PSQL�y�y�@�_�ǻ���Oracle�A�Ⱦ�����COCI���X����ŮɡA���N����ŻP�{��
	�ܶq���p�_�ӡA�æP�ɭn���X�{���ܶq���ƾ������M�ƾڪ��סC 
	�p�Gselect * from test where name=:p1 and age>:p2 
	�Gp1�M�Gp2������� 
	
	  ���ܾ��ܶq�G�ѩ�bOracle���A�C�ȥi�H��NULL�A���bC�y�����S��NULL�ȡA
	  ���F���OCI�{�Ǫ�FNULL�C�ȡAOCI��Ƥ��\�{�Ǭ��Ұ���y�y�������X�ܶq�P��
	  ���p�@�ӫ��ܲ��ܶq�Ϋ��ܲ��ܶq�ƲաA�H�����ҵ��X������ŬO�_��NULL�Ω�
	  Ū�����C�ȬO�_��NULL�A�H�Ω�Ū�����C�ȬO�_�Q�I���C 
	  ��SQLT��NTY�]SQL Named DataType�^�~�A���ܲ��ܶq�Ϋ��ܲ��ܶq�Ʋժ��ƾ�������sb2,��Ȼ����G 
	  �@����J�ܶq�ɡG�]�pinsert ,update�y�y���^ 
	  �@=-1�GOCI�{�ǱNNULL�ᵹOracle���C�A��������ŵ��X���{���ܶq�� 
	  >=0�G���ε{�ǱN�{���ܶq�Ƚᵹ���w�C 
	  �@����X�ܶq�ɡG�]�pselect�y�y���^ 
	  ��-2�G��Ū�����C�ƾڪ��פj��{���ܶq�����סA�h�Q�I���C 
	  =-1�G��Ū�����Ȭ�NULL,��X�ܶq���Ȥ��|�Q���ܡC 
	  =0�G�ƾڳQ����Ū�J����w���{���ܶq�� 
	  ��0�G��Ū�����C�ƾڪ��פj��{���ܶq�����סA�h�Q�I���A���ܲ��ܶq�Ȭ���Ū���ƾڳQ�I���e����ڪ��� 
	  
	*/
// 	theApp.m_servername="";//�w�q������oracle�ƾڮw�A�Ⱦ��W

	//�s���ƾڮw
	if(status=OCIServerAttach(srvhp,errhp,(text*)(LPCSTR)theApp.m_servername,strlen(theApp.m_servername),OCI_DEFAULT))
		{
		MessageBox(NULL,"�s���ƾڮw����!","��l��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return ;		
	}
/*
	4�D�s��/�_�}�A�Ⱦ� 
	�h�Τ�覡�s���G 
	sword  OCIServerAttach( 
	OCIServer     *srvhp,//����l�ƪ��A�Ⱦ��y�` 
	OCIError      *errhp, //���~�y�`
	CONST text    *dblink,//�A�Ⱦ�SID 
	sb4           dblink_len, //�A�Ⱦ��W����
	ub4           mode //=OCI_DEFAULT,�t�����ұN�]������覡 
	); 

	  OCI�s�����G�ؤ覡�GBlocking(����覡)�Mnon_Blocking(�D����覡)�A����覡�N�O
	  ��ե� OCI�ާ@�ɡA�������즹OCI�ާ@������A�Ⱦ��~��^�Ȥ�ݬ������H���A����
	  �O���\�٬O���ѡC�D����覡�O��Ȥ�ݴ���OCI�ާ@���A�Ⱦ���A�A�Ⱦ��ߧY
	  ��^OCI_STILL_EXECUTING�H���A�Өä����ݪA�Ⱥݪ��ާ@�����C 
	���non-blocking�覡�A���ε{�ǭY����@��OCI��ƪ���^�Ȭ� OCI_STILL_EXECUTING��
	�����A����C�@��OCI��ƪ���^�ȶi��P�_�A�P�_�䦨�\�P�_�C 
	�i�q�L�]�m�A�Ⱦ��ݩʬ�OCI_ATTR_NONBLOCKING_MODE�ӹ�{�C�t���q�{�覡������Ҧ�. 
	  
*/


	//�]�m�A�����Ҫ��A�Ⱦ��ݩ�(�Yoracle�ƾڮw���A�Ⱦ��W)	
	if(status= OCIAttrSet ((dvoid*)svchp, (ub4) OCI_HTYPE_SVCCTX, 
		(dvoid*)srvhp, (ub4) 0,OCI_ATTR_SERVER, errhp))
	{
		MessageBox(NULL,"�]�m�A�����Ҫ��A�Ⱦ��ݩʥ���!","��l��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return ;		
	}

	//�]�m�|�ܩҨϥΪ��Τ�W��(�Yoracle�ƾڮw�Τ�W)
	if(status= OCIAttrSet((dvoid*)authp,OCI_HTYPE_SESSION,
		(text*)(LPCSTR)theApp.m_username,(ub4)strlen(theApp.m_username),OCI_ATTR_USERNAME,errhp))
	{
		MessageBox(NULL,"�]�m�|�ܩҨϥΪ��Τ�b������!","��l��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return ;		
	}	
	
	//�]�m�|�ܩҨϥΪ��Τ�K�X(�Yoracle�ƾڮw�K�X)
	if(status= OCIAttrSet((dvoid*)authp,OCI_HTYPE_SESSION,
		(text*)(LPCSTR)theApp.m_userpassword,(ub4)strlen(theApp.m_userpassword),OCI_ATTR_PASSWORD,errhp))
	{
		MessageBox(NULL,"�]�m�|�ܩҨϥΪ��Τ�K�X����!","��l��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return ;		
	}

	/*
	5�DŪ��/�]�m�y�`�ݩ� 
	sword OCIAttrSet( 
	dvoid *trgthndlp,  //�ݳ]�m���y�`�W 
	ub4  trghndltyp, //�y�`���� 
	dvoid *attributep, //�]�m���ݩʦW 
	ub4 size, //�ݩʭȪ��� 
	ub4 attrtype,     //�ݩ����� 
	OCIError *errhp   //���~�y�` 
	) 
	���G�@��n�]�m���ݩʦ��G 
	�A�Ⱦ���ҡG 
	�y�`����OCI_HTYPE_SVCCTX�A�ݩ�����OCI_ATTR_SERVER 
	�s���ƾڪ��Τ�W�G 
	�y�`����OCI_HTYPE_SESSION�A�ݩ�����OCI_ATTR_USERNAME 
	�Τ�K�X 
    �y�`����OCI_HTYPE_SESSION�A�ݩ�����OCI_ATTR_PASSWORD 
	�ưȡG   
	�y�`����OCI_HTYPE_SVCCTX�A�ݩ�����OCI_ATTR_SESSION 
	
	
	*/
	
	//�}�l�@�ӷ|��(�Y�q�L�]�m��oracle�ƾڮw�Τ�W�M�K�X\)
	if(status= OCISessionBegin(svchp,errhp,authp,OCI_CRED_RDBMS,OCI_DEFAULT))
	{
		MessageBox(NULL,"�]�m�|�ܩҨϥΪ��Τ�b������!","��l��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return ;		
	}
	/*
	6�D�}�l/�����@�ӷ|��
	���{�ҥΤ�A�إߤ@�ӷ|�ܳs��
    sword OCISessionBegin ( 
	OCISvcCtx     *svchp,   //�A�����ҥy�`
	OCIError    *errhp,	//���~�y�`
	OCISession *usrhp, //�Τ�|�ܥy�`
	ub4           credt, //�{������
	ub4           mode //�ާ@�Ҧ�
	);
	
      *�{�������G 
	  OCI_CRED_RDBMS:�μƾڮw�Τ�W�M�K�X�i��{�ҡA�h���n�]�mOCI_ATTR_USERNAME�MOCI_ATTR_PASSWORD�ݩ�
	  OCI_CRED_EXT:�~���{�ҡA���ݭn�]�m�Τ�M�K�X
	  OCI_DEFAULT�G�Τ�|�����ҥu��Q���w���A�Ⱦ����ҥy�`�ҳ]�m
	  OCI_SYSDBA�G�Τ�n�㦳sysdba�v��
	  OCI_SYSOPER�G�Τ�n�㦳sysoper�v��
	  
	*/
	
	if(status= OCIAttrSet(svchp, OCI_HTYPE_SVCCTX,(dvoid*)authp, 0, 
		OCI_ATTR_SESSION, errhp))
	{
		MessageBox(NULL,"�]�m�|�ܩҨϥΪ��Τ�b������!","��l��OIC",MB_ICONINFORMATION);		
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return ;		
	}
}


/*
 OCI��ƪ�^�ȡG 
OCI_SUCCESS �V��ư��榨�\ (=0) 
OCI_SUCCESS_WITH_INFO �V���榨�\�A�����E�_������^�A�i��Oĵ�i�H�� 
OCI_NO_DATA�X��ư��槹���A���S����L�ƾ� 
OCI_ERROR�X��ư�����~ 
OCI_INVALID_HANDLE�X�ǻ�����ƪ��ѼƬ��L�ĥy�`�A�ζǦ^���y�`�L�� 
OCI_NEED_DATA�X�ݭn���ε{�Ǵ��ѹB��ɨ誺�ƾ� 
OCI_CONTINUE�X�^�ը�ƪ�^�N�X�A�����^�ը�ƻݭnOCI�w��_�䥿�`���B�z�ާ@ 
OCI_STILL_EXECUTING�X�A�����ҫإߦb�D����Ҧ��AOCI��ƽեΥ��b���椤�C 

  */
//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
void COCIclass::Error_proc(dvoid *errhp, sword status)
{
	text errbuf[512];
	sb4 errcode;
	CString errinfor;
	
	switch(status)
	{
	case OCI_SUCCESS://��ư��榨�\
		break;
	case OCI_SUCCESS_WITH_INFO:
		MessageBox(NULL,"���榨�\�A�����E�_������^�A�i��Oĵ�i�H��","���~�B�z",MB_ICONINFORMATION);
		break;
	case OCI_NEED_DATA:
		MessageBox(NULL,"�ݭn���ε{�Ǵ��ѹB��ɨ誺�ƾ�","���~�B�z",MB_ICONINFORMATION);
		break;
	case OCI_NO_DATA:
		MessageBox(NULL,"��ư��槹���A���S����L�ƾ�","���~�B�z",MB_ICONINFORMATION);
		break;
	case OCI_ERROR://��ư�����~
		OCIErrorGet ((dvoid *) errhp, (ub4) 1, (text *) NULL, 
			&errcode, errbuf, (ub4) sizeof(errbuf), (ub4) OCI_HTYPE_ERROR);
		errinfor.Format ("OCI ���~��: %d\n���~�H��:%s",errcode,errbuf);
		MessageBox(NULL,errinfor,"���~�B�z",MB_ICONINFORMATION);
		break;
	case OCI_INVALID_HANDLE: 
		MessageBox(NULL,"�ǻ�����ƪ��ѼƬ��L�ĥy�`�A�ζǦ^���y�`�L��","���~�B�z",MB_ICONINFORMATION);
		break;
	case OCI_STILL_EXECUTING:
		MessageBox(NULL,"�A�����ҫإߦb�D����Ҧ��AOCI��ƽեΥ��b���椤","���~�B�z",MB_ICONINFORMATION);
		break;
	default:
		break;
	}
}
/*
sword OCIErrorGet ( 
	dvoid      *hndlp, //���~�y�` 
	ub4        recordno,//�q����Ū�����~�O���A�q1�}�l 
	text       *sqlstate,//�w�����A=NULL 
	sb4        *errcodep, //���~�� 
	text       *bufp,  //���~���e 
	ub4        bufsiz,  //bufp���� 
	ub4        type //�ǻ������~�y�`���� 
	=OCI_HTYPE_ERROR:���~�y�` 
	=OCI_HTYPE_ENV�G���ҥy�` 
); 

*/
 
//�H�^�դ覡�NLOB�ƾڼg�JOracle�ƾڮw��
int COCIclass::CallbackWriteToLob()
{
	ub4 offset=1,loblength=0;
	ub4 bufp[LOB_BUF_LEN];
	
	ub4 piecelen;
	ub1 *piece=0;
	ub4 *lenp=0;
	
	CString tempstr;
	
	OCILobGetLength(svchp,errhp,lob_loc[0],&loblength);//��oLOB���ƾڪ���,�s�x��loblength�ܶq��
	
	fseek(fp_OCI,0,SEEK_SET);//���}fp_OCI���w���V�����
	
	if(Filelength_OCI>LOB_BUF_LEN) //�p�G�����פj��LOB_BUF_LEN
		piecelen=LOB_BUF_LEN;  //Ū����������=LOB_BUF_LEN
	else  //�p�G�����פp��LOB_BUF_LEN
		piecelen=Filelength_OCI; //Ū���������״N�������������
	
	if(fread((dvoid*)bufp,(size_t)piecelen,1,fp_OCI)!=1)//�p�GŪ���~
	{
		MessageBox(NULL,"Ū�J�ƾڵo�Ϳ��~!","�^�ռҦ��g�J�ƾ�",MB_ICONINFORMATION);
		return -1;
	}
	if(Filelength_OCI<LOB_BUF_LEN)   //�p�G�����פp��LOB_BUF_LEN
	{		
		if(status=OCILobWrite(svchp,errhp,lob_loc[0],&Filelength_OCI,offset,(dvoid*)bufp,(ub4)piecelen,
			OCI_ONE_PIECE,(dvoid*)0,(sb4(*)(dvoid*,dvoid*,ub4*,ub1*))0,(ub2)0,
			(ub1)SQLCS_IMPLICIT)!=OCI_SUCCESS)
		{
			Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
			return -1;
		}
		
	}
	else   //�p�G�����פj��LOB_BUF_LEN
	{
		if(status=OCILobWrite(svchp,errhp,lob_loc[0],&Filelength_OCI,offset,(dvoid*)bufp,
			(ub4)piecelen,OCI_FIRST_PIECE,(dvoid*)0,callback_writes_OCI,(ub2)0,SQLCS_IMPLICIT))
		{
			Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
			return -1;			
		}
	}
	
	return 0;
}
/*
OCILobGetLength(
	handle_service,//�A�����ҥy�`
	handle_error,//���~�y�`
	p_blob, //LOB�w���
	 &size //�s�xLOB���ƾڪ���
	 ) 

OCILobWrite()�G�л\���覡��ƾڼg����w�����q�B�C��^OCI_NEED_DATA��ܥ�
�g��LOB�ƾڪ������A������եΦ�����~��g�C�]�ϥ�ORACLE���y����A�̧֡B�ϥΧ�n���Ŷ��MREDO�^

*/
 
BOOL COCIclass::AddNormalDataToDB(CString strSQL)
{	
	//�ǳ�SQL�y�y
	if (status =OCIStmtPrepare(stmthp, errhp,(const unsigned char*)(LPCSTR)strSQL, strlen((char*)(LPCSTR)strSQL),OCI_NTV_SYNTAX,OCI_DEFAULT))
	{
		Error_proc(errhp, status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return FALSE;
	}
	/*
	7�D�ǳ�SQL�y�y 
	sword OCIStmtPrepare ( 
		OCIStmt       *stmtp,//�y�y�y�`   
		OCIError      *errhp, //���~�y�`
		CONST text    *stmt,  //SQL�y�y 
		ub4           stmt_len,   //�y�y���� 
		ub4           language,  //�y�y���y�k�榡=OCI_NTV_SYNTAX 
		ub4           mode //=OCI_DEFAULT 
		); 
	*/
	
	if (status =OCIStmtExecute(svchp, stmthp, errhp, (ub4 )1,0, NULL, NULL, OCI_DEFAULT))
	{
		Error_proc(errhp, status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return FALSE;
	}
	
	if (status =OCITransCommit(svchp, errhp, (ub4)0))
	{
		Error_proc(errhp, status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return FALSE;
	}

	return  TRUE;
}

 /*
 lob �ާ@���OCI���²�n�C��G
 
           OCILobOpen()���}�����Υ~��LOB
           OCILobFileOpen()���}�~��LOB�����
           OCILobClose()����LOB
           OCILobFileClose()�����~��LOB�����
           OCILobFileCloseAll()�����Ҧ��~��LOB�����
           OCILobGetLength()��oLOB���ƾڪ���
           OCILobRead()Ū��LOB�ƾڡA�i���wŪ�����w�����q�������w�j�p��LOB�ƾڨ줺�s�A
		              ��^OCI_NEED_DATA��ܥ�Ū��LOB�ƾڪ������A������եΦ�����~��Ū�C
           OCILobWrite()�H�л\���覡��ƾڼg����w�����q�B�C��^OCI_NEED_DATA
		              ��ܥ��g��LOB�ƾڪ������A������եΦ�����~��g�C
           OCILobWriteAppend()�H�l�[���覡�gLOB�ƾ�
           OCILobTrim()��LOB���j�p�I�_�����w�ȡA�u��ާ@����LOB
           OCILobErase()�R��LOB���w�����q�����w�j�p���ƾڡC
*/
 
//�NBLOB�����ƾ������g�Joralce�ƾڮw��
BOOL COCIclass::AddBOLBDataToDB(CString strFilename, CString strSQL,int m_ID)
{
	text *selectlocator;

	fp_OCI=fopen((const char*)(LPCSTR)strFilename,(const char *)"rb");
	fseek(fp_OCI,0,SEEK_END);
	Filelength_OCI=ftell(fp_OCI);
	if(Filelength_OCI<=0)
	{
		MessageBox(NULL,"�����׬�0,����g�J!","�g�J�ƾ�",MB_ICONSTOP);
		return FALSE;
	}
	selectlocator=(text*)(LPCTSTR)strSQL;
	
	
	//�ǳ�SQL�y�y
	if(status= OCIStmtPrepare(stmthp,errhp,selectlocator,
		(ub4)strlen((char*)selectlocator),(ub4)OCI_NTV_SYNTAX,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"�ǳ�SQL�y�y����!","�g�JLOB�ƾ�",MB_ICONSTOP);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return  FALSE;		
	}
	
	//����m�j�w,��ĳ�@������覡�j�w
	if(status= OCIBindByPos(stmthp,&bndhp,errhp,(ub4)1,(dvoid*)&m_ID,
		(sb4)sizeof(m_ID),SQLT_INT,(dvoid*)0,(ub2*)0,(ub2*)0,(ub4)0,(ub4*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"����m�j�w����!","�g�JLOB�ƾ�",MB_ICONSTOP);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return FALSE ;		
	}
	/*
	sword OCIBindByPos ( 
	OCIStmt      *stmtp, //SQL�y�y�y�`OCIStmt
	OCIBind      **bindpp, //���X�y�` 
	OCIError     *errhp, //���~�y�`
	ub4          position,// �j�w����m 
	dvoid        *valuep, //�j�w���ܶq�W
	sb4          value_sz,  //�j�w���ܶq�W���� 	
	ub2          dty, //�j�w������
	dvoid        *indp, //���ܲ��ܶq���w(sb2����),����j�w�ɬ�NULL, 	
	ub2          *alenp, //��������e��Q���X���Ʋ��ܶq���U�����ƾڹ�ڪ����סA����j�w�ɬ�NULL 	
	ub2          *rcodep, //�C�Ū�^�X�ƾګ��w�A����j�w�ɬ�NULL 	
	ub4          maxarr_len, //�̦h���O����,�p�G�O����j�w�A�h��0 	
	ub4          *curelep, //�C�Ū�^�X�ƾګ��w�A����j�w�ɬ�NULL 	
	ub4          mode	//=OCI_DEFAULT 
	); 
	*/


	//����m�j�w,��ĳ�@������覡�j�w
	if(status= OCIDefineByPos(stmthp,&defhp,errhp,(ub4)1,(dvoid*)&lob_loc[0],
		(sb4)-1,(ub2)SQLT_BLOB,(dvoid*)0,(ub2*)0,(ub2*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"����m�w�q����!","�g�JLOB�ƾ�",MB_ICONSTOP);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return  FALSE;		
	}
	
	//����SQL�y�y 
	if(status= OCIStmtExecute(svchp,stmthp,errhp,(ub4)1,(ub4)0,
		(CONST OCISnapshot*)0,(OCISnapshot*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"����SQL�y�y����!","�g�JLOB�ƾ�",MB_ICONSTOP);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return  FALSE;		
	}
	
	/*
	sword OCIStmtExecute ( 
	OCISvcCtx           *svchp,  //�A�����ҥy�` 
	OCIStmt             *stmtp,  //�y�y�y�` 
	OCIError            *errhp, //���~�y�`
	ub4                 iters, // ** 
	ub4                 rowoff, //** 
	CONST OCISnapshot   *snap_in, 
	OCISnapshot         *snap_out, 
	ub4                 mode //** 
	); 
	**���G 
	1. iters:���select�y�y�A�������@������Ū����buffer�����O����ơA�p�G����T�w
	select�y�y�Ҫ�^����ơA�i�Niters�]�m��0,�ӹ���L���y�y�Aiters��ܳo�ǻy�y
	�����榸�ơA����iters���ର0�C 
	2. rowoff:�b�h�����ɡA�ӰѼƪ�ܱq�ҵ��X���ƾ��ܶq�����ĴX���O���}�l����(�Y�O�������q)�C 
	3. mode�G=OCI_DEFAULT:default�Ҧ� 
	=OCI_DESCRIBE_ONLY�G�y�z�Ҧ��A�u��^��ܦC���y�z�H���A�Ӥ�����y�y 
	=OCI_COMMIT_ON_SUCCESS�G�۰ʴ���Ҧ��A����榨�\��A�۰ʴ���C 
	=OCI_EXACT_FETCH:��T�����Ҧ��C 
	=OCI_BATCH_ERRORS�G����~����Ҧ��G�Ω����Ʋդ覡���ާ@�A�b���Ҧ��U�A	��qinsert ,
	update,delete�ɡA����L�{������@���O�����~���|�ɭP���insert ,update,delete���ѡA
	�t�Φ۰ʷ|�������~�H���A�Ӧb�D����~�覡�U�A�䤤������@���O�����~�A�N�|�ɭP��Ӿާ@���ѡC 
	�Ҧp: 
	����@�� 
	swResult = OCIStmtExecute(svchp, stmtp,  errhp, 1, 0, NULL, NULL, OCI_DEFAULT); 
	��q����100���G 
	swResult = OCIStmtExecute(svchp, stmtp,  errhp,100, 0, NULL, NULL, OCI_DEFAULT); 
	
	*/


	CallbackWriteToLob(); 

	/*�����ζi�{�P�A�Ⱦ��_�}�s���ɡA�{�ǨS���ϥ�OCITransCommit()�i��ưȪ�
	����A�h�Ҧ����ʪ��ưȷ|�۰ʦ^�u�C*/
	if (status =OCITransCommit(svchp,errhp, (ub4)0))
	{
		Error_proc(errhp, status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return FALSE;
	}
	fclose(fp_OCI);

	return TRUE;
}

 
//�q�ƾڮw��Ū��BLOB�ƾ�
BOOL COCIclass::ReadBOLBDataFromDB(CString strFilename, CString strSQL, int m_ID)
{
	text *cp=NULL;
	text *selectlocator;
	
	selectlocator=(text*)(LPCTSTR)strSQL;
	

	//�ǳ�SQL�y�y
	if(status= OCIStmtPrepare(stmthp,errhp,selectlocator,
		(ub4)strlen((char*)selectlocator),(ub4)OCI_NTV_SYNTAX,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"�ǳ�SQL�y�y����!","Ū���ƾ�",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return  FALSE;		
	}
		
	
	//����m�j�w,��ĳ�@������覡�j�w
	if(status= OCIBindByPos(stmthp,&bndhp,errhp,(ub4)1,(dvoid*)&m_ID,
		(sb4)sizeof(m_ID),SQLT_INT,(dvoid*)0,(ub2*)0,(ub2*)0,(ub4)0,(ub4*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"����m�j�w����!","Ū���ƾ�",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return FALSE;		
	}
	
	
	//�w�q��X�ܶq 
	if(status= OCIDefineByPos(stmthp,&defhp,errhp,(ub4)1,(dvoid*)&lob_loc[0],
		(sb4)-1,(ub2)SQLT_BLOB,(dvoid*)0,(ub2*)0,(ub2*)0,(ub4)OCI_DEFAULT))
	{
			MessageBox(NULL,"����m�w�q����!","Ū���ƾ�",MB_ICONINFORMATION);
			Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return FALSE;		
	}
	/*
	sword OCIDefineByPos ( 
		OCIStmt     *stmtp, //�y�y�y�` 
		OCIDefine   **defnpp,//�w�q�y�`�X�Ω�Ʋ��ܶq 
		OCIError    *errhp, //���~�y�`
		ub4         position,//��m�Ǹ�(�q1 �}�l) 
		dvoid       *valuep, //��X���ܶq�W 
		sb4         value_sz, //�ܶq���� 
		ub2         dty,  //�ƾ����� 
		dvoid       *indp, //���ܾ��ܶq/���ܾ��ܶq�ƲաA�p�G���r�q�i��s�b�ŭȡA�h�n���ܾ��ܶq�A�_�h����B�z�ɬ�NULL 
		ub2         *rlenp, //�������ƾڪ��� 
		ub2         *rcodep, //�C�Ū�^�X�Ʋի��w 
		ub4         mode //OCI_DEFAULT 
	); 
	*/
	
	//����SQL�y�y
	if(status= OCIStmtExecute(svchp,stmthp,errhp,(ub4)1,(ub4)0,
		(CONST OCISnapshot*)0,(OCISnapshot*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"����SQL�y�y����!","Ū���ƾ�",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��ƪ�^�ȶi����~�P�_�õ��X���ܫH��
		return FALSE;		
	}

	//�����ζi�{�P�A�Ⱦ��_�}�s����,�{�ǨS���ϥ�OCITransCommit()
	//�i��ưȪ�����,�h�Ҧ����ʪ��ưȷ|�۰ʦ^�u
	OCITransCommit(svchp,errhp,(ub4)OCI_DEFAULT);//����@�Өư�
	/*
	sword OCITransCommit ( 
	OCISvcCtx    *svchp,  //�A�����ҥy�` 
	OCIError     *errhp, //���~�y�`
	ub4          flags ); //OCI_DEFAULT 	
		*/


	fp_OCI=fopen(strFilename,"wb"); //���}�~�����
	BOOL tb=TRUE;
	if(fp_OCI)
	{
		tb=CallbackReadLob();
	} 
	fclose(fp_OCI);	//�������
	return tb;

	
}

BOOL COCIclass::CallbackReadLob()
{
	ub4 offset=1,amtp=0;
	ub1 bufp[LOB_BUF_LEN];
	sword status;
	CString tt;
	ub4 loblengtht=0;	

	//��oLOB���ƾڪ���,�s�x��loblength�ܶq��
	OCILobGetLength(svchp,errhp,lob_loc[0],&loblengtht);

	if(loblengtht<=0) //�p�GLOB���ƾڪ���<=0�A��^���~�A
		return FALSE;

	amtp=loblengtht;
	//Ū��LOB�ƾ�
	if(status=OCILobRead(svchp,errhp,lob_loc[0],&amtp,offset,(dvoid*)bufp,
		(ub4)LOB_BUF_LEN,(dvoid*)0,callback_Read_OCI,(ub2)0,(ub1)SQLCS_IMPLICIT))
	{
		return FALSE;
		MessageBox(NULL,"���~�ƾ�!","Ū��LOB�ƾ�",MB_ICONSTOP);
	}	
	return TRUE;
}
/*
OCILobRead(handle_service,handle_error,p_blob,&amt,1,read_buf+offset-1, (ub4)LOB_BUF_LEN,NULL,NULL �K); 
//�[�G��1��ܲĤ@��Ū���첾�A�b�y�Ҧ��U�A���ѼƩMamt�@�ˡA�u���b�Ĥ@��Ū�ɦ��� 
//�[�G��NULL��ܦ^�ը�Ƭ��šA�o�ˬy�Ҧ��ϥν��ߡ]polling�^��k�Ӥ��O�^�ա]callback�^��k 
//���ߤ�k�U�A�p�G�S��Ū��blob�����A��ƪ�^OCI_NEED_DATA�AŪ�������A��^OCI_SUCCESS 
�p�GŪ�������]OCI_NEED_DATA�^�A���X�`�� 

*/