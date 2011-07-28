// OCIclass.cpp: implementation of the COCIclass class.
 
 

#include "stdafx.h"
 
#include "OCIclass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 
// Construction/Destruction
 

FILE *fp_OCI;	//FILE指針,向來打開外部文件
ub4 Filelength_OCI; //存儲打開外部文件的長度

/*
為了不一次寫入過多數據，首先定義一個緩衝區大小LOB_BUF_LEN，比如規定為8192。 
如果寫入數據大小（size）在LOB_BUF_LEN範圍內，則可一次寫完。 
*/
#define LOB_BUF_LEN  131072  
 
#define MAXLENGTH    4294967296 //一個LOB字段最大存儲的字節數

 
//以回調方式寫入數據
sb4 callback_writes_OCI(dvoid *ctxp,dvoid *bufxp,ub4 *lenp, ub1 *piece)
{
	ub4 piecelen;	
	static ub4 len=LOB_BUF_LEN;
	
	if((Filelength_OCI-len)>LOB_BUF_LEN) //如果文件的長度-每次讀寫的長度>LOB_BUF_LEN
		piecelen=LOB_BUF_LEN;	//此時讀寫的長度=LOB_BUF_LEN
	else  //如文件的長度<每次讀寫的長度
		piecelen=Filelength_OCI-len; //此時讀寫的長度=文件的長度-LOB_BUF_LEN
	
	*lenp=piecelen;
	
	//開始讀文件
	if(fread((void*)bufxp,(size_t)piecelen,1,fp_OCI)!=1)
	{
		AfxMessageBox("讀數據文件發生錯誤!");
		*piece=OCI_LAST_PIECE;
		len=LOB_BUF_LEN;
		return OCI_CONTINUE;
		
	}
	len+=piecelen;//已讀的文件長度累加
	
	if(len==Filelength_OCI)  //如果已讀的文件長度=文件總長度,結束對文件的讀操作
	{
		*piece=OCI_LAST_PIECE;//當前塊為最後一塊標誌，表示寫最後一批數據 
		len=LOB_BUF_LEN;
	}
	else
		*piece=OCI_NEXT_PIECE;//否則,當前塊為下一塊標誌,表示繼續寫，但不寫最後一批 
	
	return OCI_CONTINUE;
}

 
//以回調方式讀入數據
sb4 callback_Read_OCI(dvoid *ctxp,CONST dvoid *bufxp,ub4 len,ub1 piece)
{
	static ub4 piece_count=0;
	piece_count++;
	switch(piece)
	{
	case OCI_LAST_PIECE://表示寫最後一批數據 
		fwrite((void*)bufxp,(size_t)len,1,fp_OCI);
		piece_count=0;
		return OCI_CONTINUE;
	case OCI_FIRST_PIECE://表示寫第一批
	case OCI_NEXT_PIECE://表示繼續寫，但不寫最後一批
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


//初始化OCI
void COCIclass::Init_OCI()
{
	//創建OCI環境,即創建和初始化OCI工作環境，其他的OCI函數需要OCI環境才能執行。
	if(status=OCIEnvCreate(&envhp,OCI_DEFAULT,(dvoid *)0, 
		(dvoid* (*)(dvoid*,size_t))0,(dvoid* (*)(dvoid*,dvoid*,size_t))0,
		(void (*)(dvoid *, dvoid *)) 0, (size_t) 0,(dvoid **) 0 ))
	{
		MessageBox(NULL,"創建OCI環境失敗!","初始化OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return ;		
	}
	/*
	1．創建OCI環境 
	sword OCIEnvCreate(   
	OCIEnv **envhpp,  //OCI環境句柄指針 
	ub4 mode, //初始化模式：OCI_DEFAULT/OCI_THREADED 等 
	CONST dvoid *ctxp, 
	CONST dvoid *(*malicfp)(dvoid *ctxp,size_t size), 
	CONST dvoid *(ralocfp)(dvoid *ctxp,dvoid *memptr,size_t newsize), 
	CONST void *(*mfreefp)(dvoid *ctxp,dvoid *memptr), 
	Size_t xstramemsz, 
	Dvoid **usrmempp 
	) 

OCI函數設置的模式有： 
	OCI_DEFUALT:使用OCI默認的環境 
	OCI_THREADED：線程環境下使用OCI 
	OCI_OBJECT：對像模式 
	OCI_SHARED：共享模式 
	OCI_EVENTS 
	OCI_NO_UCB 
	OCI_ENV_NO_MUTEX：非互斥訪問模式 
	其中模式可以用邏輯運算符進行迭加，將函數設置成多多種模式：如mode=OCI_SHREADED| OCI_OBJECT 

	*/

	//申請錯誤句柄
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&errhp,(ub4)OCI_HTYPE_ERROR,
		(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"申請錯誤句柄失敗!","初始化OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return ;		
	}

	//申請服務器句柄
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&srvhp,
		(ub4)OCI_HTYPE_SERVER,(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"申請服務器句柄失敗!","初始化OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return ;		
	}
	
	//申請服務環境句柄
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&svchp,
		(ub4)OCI_HTYPE_SVCCTX,(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"申請服務環境句柄失敗!","初始化OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return ;		
	}
	
	//申請會話句柄
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&authp,
		(ub4)OCI_HTYPE_SESSION,(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"申請會話句柄失敗!","初始化OIC",MB_ICONINFORMATION);		
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return ;		
	}
	
	//申請語句句柄
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&stmthp,
		(ub4)OCI_HTYPE_STMT,(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"申請語句句柄失敗!","初始化OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return ;		
	}
	
	/*
	2．申請/釋放句柄 
	sword OCIHandleAlloc( 
		CONST dvoid *parenth,  //新申請句柄的父句柄，一般為OCI環境句柄 
		Dvoid **hndlpp,   //申請的新句柄 
		Ub4 type, type,  //句柄類型 
		Size_t xtramem_sz,   //申請的內存數 
		Dvoid **usrmempp  //申請到的內存塊指針 
	) 
	註： 
	一般需要申請的句柄有： 
	服務器句柄OCIServer, 句柄類型OCI_HTYPE_SERVER 
	錯誤句柄OCIError，用於捕獲OCI錯誤信息, 句柄類型OCI_HTYPE_ERROR 
	事務句柄OCISession, 句柄類型OCI_HTYPE_SESSION 
	上下文句柄OCISvcCtx, 句柄類型OCI_HTYPE_SVCCTX 
	SQL語句句柄OCIStmt, 句柄類型OCI_HTYPE_STMT 
	*/

	/*
	釋放句柄 
	sword OCIHandleFree( 
	dvoid *hndlp,  //要釋放的句柄 
	ub4 type   //句柄類型 
	) 
	*/

	//申請2個LOB佔位符,用於對BLOB類型數據寫入或讀取操作。用參數OCI_DTYPE_LOB，獲得一個LOB的句柄
	for(int i=0;i<2;i++)
	{
		if(status=OCIDescriptorAlloc((dvoid*)envhp,(dvoid**)&lob_loc[i],(ub4)OCI_DTYPE_LOB,
			(size_t)0,(dvoid**)0))
		{
			MessageBox(NULL,"申請LOB佔位符失敗!","初始化OIC",MB_ICONINFORMATION);
			Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
			return ;		
		}
 	}

	/*
	12． 結合佔位符和指示器變量： 
	佔位符：在程序中，一些SQL語句需要在程序運行時才能確定它的語句數據，在設計時
	可用一個佔位符來代替，當程序運行時，在它準備好語句後，必須為每個佔位符指定一個變量，
	即將佔位符與程序變量地址結合，執行時，Oracle就從這些變量中讀取數據，並將它們
	與SQL語句一起傳遞給Oracle服務器執行。OCI結合佔位符時，它將佔位符與程序
	變量關聯起來，並同時要指出程序變量的數據類型和數據長度。 
	如：select * from test where name=:p1 and age>:p2 
	：p1和：p2為佔位符 
	
	  指示器變量：由於在Oracle中，列值可以為NULL，但在C語言中沒有NULL值，
	  為了能使OCI程序表達NULL列值，OCI函數允許程序為所執行語句中的結合變量同時
	  關聯一個指示符變量或指示符變量數組，以說明所結合的佔位符是否為NULL或所
	  讀取的列值是否為NULL，以及所讀取的列值是否被截取。 
	  除SQLTˍNTY（SQL Named DataType）外，指示符變量或指示符變量數組的數據類型為sb2,其值說明： 
	  作為輸入變量時：（如insert ,update語句中） 
	  　=-1：OCI程序將NULL賦給Oracle表的列，忽略佔位符結合的程序變量值 
	  >=0：應用程序將程序變量值賦給指定列 
	  作為輸出變量時：（如select語句中） 
	  ＝-2：所讀取的列數據長度大於程序變量的長度，則被截取。 
	  =-1：所讀取的值為NULL,輸出變量的值不會被改變。 
	  =0：數據被完整讀入到指定的程序變量中 
	  ＞0：所讀取的列數據長度大於程序變量的長度，則被截取，指示符變量值為所讀取數據被截取前的實際長度 
	  
	*/
// 	theApp.m_servername="";//定義的全局oracle數據庫服務器名

	//連接數據庫
	if(status=OCIServerAttach(srvhp,errhp,(text*)(LPCSTR)theApp.m_servername,strlen(theApp.m_servername),OCI_DEFAULT))
		{
		MessageBox(NULL,"連接數據庫失敗!","初始化OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return ;		
	}
/*
	4．連接/斷開服務器 
	多用戶方式連接： 
	sword  OCIServerAttach( 
	OCIServer     *srvhp,//未初始化的服務器句柄 
	OCIError      *errhp, //錯誤句柄
	CONST text    *dblink,//服務器SID 
	sb4           dblink_len, //服務器名長度
	ub4           mode //=OCI_DEFAULT,系統環境將設為阻塞方式 
	); 

	  OCI連接有二種方式：Blocking(阻塞方式)和non_Blocking(非阻塞方式)，阻塞方式就是
	  當調用 OCI操作時，必須等到此OCI操作完成後服務器才返回客戶端相應的信息，不管
	  是成功還是失敗。非阻塞方式是當客戶端提交OCI操作給服務器後，服務器立即
	  返回OCI_STILL_EXECUTING信息，而並不等待服務端的操作完成。 
	對於non-blocking方式，應用程序若收到一個OCI函數的返回值為 OCI_STILL_EXECUTING時
	必須再次對每一個OCI函數的返回值進行判斷，判斷其成功與否。 
	可通過設置服務器屬性為OCI_ATTR_NONBLOCKING_MODE來實現。系統默認方式為阻塞模式. 
	  
*/


	//設置服務環境的服務器屬性(即oracle數據庫的服務器名)	
	if(status= OCIAttrSet ((dvoid*)svchp, (ub4) OCI_HTYPE_SVCCTX, 
		(dvoid*)srvhp, (ub4) 0,OCI_ATTR_SERVER, errhp))
	{
		MessageBox(NULL,"設置服務環境的服務器屬性失敗!","初始化OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return ;		
	}

	//設置會話所使用的用戶名稱(即oracle數據庫用戶名)
	if(status= OCIAttrSet((dvoid*)authp,OCI_HTYPE_SESSION,
		(text*)(LPCSTR)theApp.m_username,(ub4)strlen(theApp.m_username),OCI_ATTR_USERNAME,errhp))
	{
		MessageBox(NULL,"設置會話所使用的用戶帳號失敗!","初始化OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return ;		
	}	
	
	//設置會話所使用的用戶密碼(即oracle數據庫密碼)
	if(status= OCIAttrSet((dvoid*)authp,OCI_HTYPE_SESSION,
		(text*)(LPCSTR)theApp.m_userpassword,(ub4)strlen(theApp.m_userpassword),OCI_ATTR_PASSWORD,errhp))
	{
		MessageBox(NULL,"設置會話所使用的用戶密碼失敗!","初始化OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return ;		
	}

	/*
	5．讀取/設置句柄屬性 
	sword OCIAttrSet( 
	dvoid *trgthndlp,  //需設置的句柄名 
	ub4  trghndltyp, //句柄類型 
	dvoid *attributep, //設置的屬性名 
	ub4 size, //屬性值長度 
	ub4 attrtype,     //屬性類型 
	OCIError *errhp   //錯誤句柄 
	) 
	註：一般要設置的屬性有： 
	服務器實例： 
	句柄類型OCI_HTYPE_SVCCTX，屬性類型OCI_ATTR_SERVER 
	連接數據的用戶名： 
	句柄類型OCI_HTYPE_SESSION，屬性類型OCI_ATTR_USERNAME 
	用戶密碼 
    句柄類型OCI_HTYPE_SESSION，屬性類型OCI_ATTR_PASSWORD 
	事務：   
	句柄類型OCI_HTYPE_SVCCTX，屬性類型OCI_ATTR_SESSION 
	
	
	*/
	
	//開始一個會話(即通過設置的oracle數據庫用戶名和密碼\)
	if(status= OCISessionBegin(svchp,errhp,authp,OCI_CRED_RDBMS,OCI_DEFAULT))
	{
		MessageBox(NULL,"設置會話所使用的用戶帳號失敗!","初始化OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return ;		
	}
	/*
	6．開始/結束一個會話
	先認證用戶再建立一個會話連接
    sword OCISessionBegin ( 
	OCISvcCtx     *svchp,   //服務環境句柄
	OCIError    *errhp,	//錯誤句柄
	OCISession *usrhp, //用戶會話句柄
	ub4           credt, //認證類型
	ub4           mode //操作模式
	);
	
      *認證類型： 
	  OCI_CRED_RDBMS:用數據庫用戶名和密碼進行認證，則先要設置OCI_ATTR_USERNAME和OCI_ATTR_PASSWORD屬性
	  OCI_CRED_EXT:外部認證，不需要設置用戶和密碼
	  OCI_DEFAULT：用戶會話環境只能被指定的服務器環境句柄所設置
	  OCI_SYSDBA：用戶要具有sysdba權限
	  OCI_SYSOPER：用戶要具有sysoper權限
	  
	*/
	
	if(status= OCIAttrSet(svchp, OCI_HTYPE_SVCCTX,(dvoid*)authp, 0, 
		OCI_ATTR_SESSION, errhp))
	{
		MessageBox(NULL,"設置會話所使用的用戶帳號失敗!","初始化OIC",MB_ICONINFORMATION);		
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return ;		
	}
}


/*
 OCI函數返回值： 
OCI_SUCCESS –函數執行成功 (=0) 
OCI_SUCCESS_WITH_INFO –執行成功，但有診斷消息返回，可能是警告信息 
OCI_NO_DATA—函數執行完成，但沒有其他數據 
OCI_ERROR—函數執行錯誤 
OCI_INVALID_HANDLE—傳遞給函數的參數為無效句柄，或傳回的句柄無效 
OCI_NEED_DATA—需要應用程序提供運行時刻的數據 
OCI_CONTINUE—回調函數返回代碼，說明回調函數需要OCI庫恢復其正常的處理操作 
OCI_STILL_EXECUTING—服務環境建立在非阻塞模式，OCI函數調用正在執行中。 

  */
//對COI函數返回值進行錯誤判斷並給出提示信息
void COCIclass::Error_proc(dvoid *errhp, sword status)
{
	text errbuf[512];
	sb4 errcode;
	CString errinfor;
	
	switch(status)
	{
	case OCI_SUCCESS://函數執行成功
		break;
	case OCI_SUCCESS_WITH_INFO:
		MessageBox(NULL,"執行成功，但有診斷消息返回，可能是警告信息","錯誤處理",MB_ICONINFORMATION);
		break;
	case OCI_NEED_DATA:
		MessageBox(NULL,"需要應用程序提供運行時刻的數據","錯誤處理",MB_ICONINFORMATION);
		break;
	case OCI_NO_DATA:
		MessageBox(NULL,"函數執行完成，但沒有其他數據","錯誤處理",MB_ICONINFORMATION);
		break;
	case OCI_ERROR://函數執行錯誤
		OCIErrorGet ((dvoid *) errhp, (ub4) 1, (text *) NULL, 
			&errcode, errbuf, (ub4) sizeof(errbuf), (ub4) OCI_HTYPE_ERROR);
		errinfor.Format ("OCI 錯誤號: %d\n錯誤信息:%s",errcode,errbuf);
		MessageBox(NULL,errinfor,"錯誤處理",MB_ICONINFORMATION);
		break;
	case OCI_INVALID_HANDLE: 
		MessageBox(NULL,"傳遞給函數的參數為無效句柄，或傳回的句柄無效","錯誤處理",MB_ICONINFORMATION);
		break;
	case OCI_STILL_EXECUTING:
		MessageBox(NULL,"服務環境建立在非阻塞模式，OCI函數調用正在執行中","錯誤處理",MB_ICONINFORMATION);
		break;
	default:
		break;
	}
}
/*
sword OCIErrorGet ( 
	dvoid      *hndlp, //錯誤句柄 
	ub4        recordno,//從那裡讀取錯誤記錄，從1開始 
	text       *sqlstate,//已取消，=NULL 
	sb4        *errcodep, //錯誤號 
	text       *bufp,  //錯誤內容 
	ub4        bufsiz,  //bufp長度 
	ub4        type //傳遞的錯誤句柄類型 
	=OCI_HTYPE_ERROR:錯誤句柄 
	=OCI_HTYPE_ENV：環境句柄 
); 

*/
 
//以回調方式將LOB數據寫入Oracle數據庫中
int COCIclass::CallbackWriteToLob()
{
	ub4 offset=1,loblength=0;
	ub4 bufp[LOB_BUF_LEN];
	
	ub4 piecelen;
	ub1 *piece=0;
	ub4 *lenp=0;
	
	CString tempstr;
	
	OCILobGetLength(svchp,errhp,lob_loc[0],&loblength);//獲得LOB的數據長度,存儲到loblength變量中
	
	fseek(fp_OCI,0,SEEK_SET);//打開fp_OCI指針指向的文件
	
	if(Filelength_OCI>LOB_BUF_LEN) //如果文件長度大於LOB_BUF_LEN
		piecelen=LOB_BUF_LEN;  //讀文件塊的長度=LOB_BUF_LEN
	else  //如果文件長度小於LOB_BUF_LEN
		piecelen=Filelength_OCI; //讀文件塊的長度就直接等於文件長度
	
	if(fread((dvoid*)bufp,(size_t)piecelen,1,fp_OCI)!=1)//如果讀錯誤
	{
		MessageBox(NULL,"讀入數據發生錯誤!","回調模式寫入數據",MB_ICONINFORMATION);
		return -1;
	}
	if(Filelength_OCI<LOB_BUF_LEN)   //如果文件長度小於LOB_BUF_LEN
	{		
		if(status=OCILobWrite(svchp,errhp,lob_loc[0],&Filelength_OCI,offset,(dvoid*)bufp,(ub4)piecelen,
			OCI_ONE_PIECE,(dvoid*)0,(sb4(*)(dvoid*,dvoid*,ub4*,ub1*))0,(ub2)0,
			(ub1)SQLCS_IMPLICIT)!=OCI_SUCCESS)
		{
			Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
			return -1;
		}
		
	}
	else   //如果文件長度大於LOB_BUF_LEN
	{
		if(status=OCILobWrite(svchp,errhp,lob_loc[0],&Filelength_OCI,offset,(dvoid*)bufp,
			(ub4)piecelen,OCI_FIRST_PIECE,(dvoid*)0,callback_writes_OCI,(ub2)0,SQLCS_IMPLICIT))
		{
			Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
			return -1;			
		}
	}
	
	return 0;
}
/*
OCILobGetLength(
	handle_service,//服務環境句柄
	handle_error,//錯誤句柄
	p_blob, //LOB定位符
	 &size //存儲LOB的數據長度
	 ) 

OCILobWrite()：覆蓋的方式把數據寫到指定偏移量處。返回OCI_NEED_DATA表示未
寫完LOB數據的全部，還應當調用此函數繼續寫。（使用ORACLE的流機制，最快、使用更好的空間和REDO）

*/
 
BOOL COCIclass::AddNormalDataToDB(CString strSQL)
{	
	//準備SQL語句
	if (status =OCIStmtPrepare(stmthp, errhp,(const unsigned char*)(LPCSTR)strSQL, strlen((char*)(LPCSTR)strSQL),OCI_NTV_SYNTAX,OCI_DEFAULT))
	{
		Error_proc(errhp, status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return FALSE;
	}
	/*
	7．準備SQL語句 
	sword OCIStmtPrepare ( 
		OCIStmt       *stmtp,//語句句柄   
		OCIError      *errhp, //錯誤句柄
		CONST text    *stmt,  //SQL語句 
		ub4           stmt_len,   //語句長度 
		ub4           language,  //語句的語法格式=OCI_NTV_SYNTAX 
		ub4           mode //=OCI_DEFAULT 
		); 
	*/
	
	if (status =OCIStmtExecute(svchp, stmthp, errhp, (ub4 )1,0, NULL, NULL, OCI_DEFAULT))
	{
		Error_proc(errhp, status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return FALSE;
	}
	
	if (status =OCITransCommit(svchp, errhp, (ub4)0))
	{
		Error_proc(errhp, status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return FALSE;
	}

	return  TRUE;
}

 /*
 lob 操作函數OCI函數簡要列表：
 
           OCILobOpen()打開內部或外部LOB
           OCILobFileOpen()打開外部LOB的文件
           OCILobClose()關閉LOB
           OCILobFileClose()完畢外部LOB的文件
           OCILobFileCloseAll()關閉所有外部LOB的文件
           OCILobGetLength()獲得LOB的數據長度
           OCILobRead()讀取LOB數據，可指定讀取指定偏移量除的給定大小的LOB數據到內存，
		              返回OCI_NEED_DATA表示未讀完LOB數據的全部，還應當調用此函數繼續讀。
           OCILobWrite()以覆蓋的方式把數據寫到指定偏移量處。返回OCI_NEED_DATA
		              表示未寫完LOB數據的全部，還應當調用此函數繼續寫。
           OCILobWriteAppend()以追加的方式寫LOB數據
           OCILobTrim()把LOB的大小截斷為指定值，只能操作內部LOB
           OCILobErase()刪除LOB指定偏移量的指定大小的數據。
*/
 
//將BLOB類型數據類型寫入oralce數據庫中
BOOL COCIclass::AddBOLBDataToDB(CString strFilename, CString strSQL,int m_ID)
{
	text *selectlocator;

	fp_OCI=fopen((const char*)(LPCSTR)strFilename,(const char *)"rb");
	fseek(fp_OCI,0,SEEK_END);
	Filelength_OCI=ftell(fp_OCI);
	if(Filelength_OCI<=0)
	{
		MessageBox(NULL,"文件長度為0,不能寫入!","寫入數據",MB_ICONSTOP);
		return FALSE;
	}
	selectlocator=(text*)(LPCTSTR)strSQL;
	
	
	//準備SQL語句
	if(status= OCIStmtPrepare(stmthp,errhp,selectlocator,
		(ub4)strlen((char*)selectlocator),(ub4)OCI_NTV_SYNTAX,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"準備SQL語句失敗!","寫入LOB數據",MB_ICONSTOP);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return  FALSE;		
	}
	
	//按位置綁定,建議一般按此方式綁定
	if(status= OCIBindByPos(stmthp,&bndhp,errhp,(ub4)1,(dvoid*)&m_ID,
		(sb4)sizeof(m_ID),SQLT_INT,(dvoid*)0,(ub2*)0,(ub2*)0,(ub4)0,(ub4*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"按位置綁定失敗!","寫入LOB數據",MB_ICONSTOP);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return FALSE ;		
	}
	/*
	sword OCIBindByPos ( 
	OCIStmt      *stmtp, //SQL語句句柄OCIStmt
	OCIBind      **bindpp, //結合句柄 
	OCIError     *errhp, //錯誤句柄
	ub4          position,// 綁定的位置 
	dvoid        *valuep, //綁定的變量名
	sb4          value_sz,  //綁定的變量名長度 	
	ub2          dty, //綁定的類型
	dvoid        *indp, //指示符變量指針(sb2類型),單條綁定時為NULL, 	
	ub2          *alenp, //說明執行前後被結合的數組變量中各元素數據實際的長度，單條綁定時為NULL 	
	ub2          *rcodep, //列級返回碼數據指針，單條綁定時為NULL 	
	ub4          maxarr_len, //最多的記錄數,如果是單條綁定，則為0 	
	ub4          *curelep, //列級返回碼數據指針，單條綁定時為NULL 	
	ub4          mode	//=OCI_DEFAULT 
	); 
	*/


	//按位置綁定,建議一般按此方式綁定
	if(status= OCIDefineByPos(stmthp,&defhp,errhp,(ub4)1,(dvoid*)&lob_loc[0],
		(sb4)-1,(ub2)SQLT_BLOB,(dvoid*)0,(ub2*)0,(ub2*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"按位置定義失敗!","寫入LOB數據",MB_ICONSTOP);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return  FALSE;		
	}
	
	//執行SQL語句 
	if(status= OCIStmtExecute(svchp,stmthp,errhp,(ub4)1,(ub4)0,
		(CONST OCISnapshot*)0,(OCISnapshot*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"執行SQL語句失敗!","寫入LOB數據",MB_ICONSTOP);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return  FALSE;		
	}
	
	/*
	sword OCIStmtExecute ( 
	OCISvcCtx           *svchp,  //服務環境句柄 
	OCIStmt             *stmtp,  //語句句柄 
	OCIError            *errhp, //錯誤句柄
	ub4                 iters, // ** 
	ub4                 rowoff, //** 
	CONST OCISnapshot   *snap_in, 
	OCISnapshot         *snap_out, 
	ub4                 mode //** 
	); 
	**註： 
	1. iters:對於select語句，它說明一次執行讀取到buffer中的記錄行數，如果不能確定
	select語句所返回的行數，可將iters設置為0,而對於其他的語句，iters表示這些語句
	的執行次數，此時iters不能為0。 
	2. rowoff:在多行執行時，該參數表示從所結合的數據變量中的第幾條記錄開始執行(即記錄偏移量)。 
	3. mode：=OCI_DEFAULT:default模式 
	=OCI_DESCRIBE_ONLY：描述模式，只返回選擇列表的描述信息，而不執行語句 
	=OCI_COMMIT_ON_SUCCESS：自動提交模式，當執行成功後，自動提交。 
	=OCI_EXACT_FETCH:精確提取模式。 
	=OCI_BATCH_ERRORS：批錯誤執行模式：用於執行數組方式的操作，在此模式下，	批量insert ,
	update,delete時，執行過程中任何一條記錄錯誤不會導致整個insert ,update,delete失敗，
	系統自動會收集錯誤信息，而在非批錯誤方式下，其中的任何一條記錄錯誤，將會導致整個操作失敗。 
	例如: 
	執行一次 
	swResult = OCIStmtExecute(svchp, stmtp,  errhp, 1, 0, NULL, NULL, OCI_DEFAULT); 
	批量執行100次： 
	swResult = OCIStmtExecute(svchp, stmtp,  errhp,100, 0, NULL, NULL, OCI_DEFAULT); 
	
	*/


	CallbackWriteToLob(); 

	/*當應用進程與服務器斷開連接時，程序沒有使用OCITransCommit()進行事務的
	提交，則所有活動的事務會自動回滾。*/
	if (status =OCITransCommit(svchp,errhp, (ub4)0))
	{
		Error_proc(errhp, status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return FALSE;
	}
	fclose(fp_OCI);

	return TRUE;
}

 
//從數據庫中讀取BLOB數據
BOOL COCIclass::ReadBOLBDataFromDB(CString strFilename, CString strSQL, int m_ID)
{
	text *cp=NULL;
	text *selectlocator;
	
	selectlocator=(text*)(LPCTSTR)strSQL;
	

	//準備SQL語句
	if(status= OCIStmtPrepare(stmthp,errhp,selectlocator,
		(ub4)strlen((char*)selectlocator),(ub4)OCI_NTV_SYNTAX,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"準備SQL語句失敗!","讀取數據",MB_ICONINFORMATION);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return  FALSE;		
	}
		
	
	//按位置綁定,建議一般按此方式綁定
	if(status= OCIBindByPos(stmthp,&bndhp,errhp,(ub4)1,(dvoid*)&m_ID,
		(sb4)sizeof(m_ID),SQLT_INT,(dvoid*)0,(ub2*)0,(ub2*)0,(ub4)0,(ub4*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"按位置綁定失敗!","讀取數據",MB_ICONINFORMATION);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return FALSE;		
	}
	
	
	//定義輸出變量 
	if(status= OCIDefineByPos(stmthp,&defhp,errhp,(ub4)1,(dvoid*)&lob_loc[0],
		(sb4)-1,(ub2)SQLT_BLOB,(dvoid*)0,(ub2*)0,(ub2*)0,(ub4)OCI_DEFAULT))
	{
			MessageBox(NULL,"按位置定義失敗!","讀取數據",MB_ICONINFORMATION);
			Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return FALSE;		
	}
	/*
	sword OCIDefineByPos ( 
		OCIStmt     *stmtp, //語句句柄 
		OCIDefine   **defnpp,//定義句柄—用於數組變量 
		OCIError    *errhp, //錯誤句柄
		ub4         position,//位置序號(從1 開始) 
		dvoid       *valuep, //輸出的變量名 
		sb4         value_sz, //變量長度 
		ub2         dty,  //數據類型 
		dvoid       *indp, //指示器變量/指示器變量數組，如果此字段可能存在空值，則要指示器變量，否則單條處理時為NULL 
		ub2         *rlenp, //提取的數據長度 
		ub2         *rcodep, //列級返回碼數組指針 
		ub4         mode //OCI_DEFAULT 
	); 
	*/
	
	//執行SQL語句
	if(status= OCIStmtExecute(svchp,stmthp,errhp,(ub4)1,(ub4)0,
		(CONST OCISnapshot*)0,(OCISnapshot*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"執行SQL語句失敗!","讀取數據",MB_ICONINFORMATION);
		Error_proc(errhp,status);//對COI函數返回值進行錯誤判斷並給出提示信息
		return FALSE;		
	}

	//當應用進程與服務器斷開連接時,程序沒有使用OCITransCommit()
	//進行事務的提交,則所有活動的事務會自動回滾
	OCITransCommit(svchp,errhp,(ub4)OCI_DEFAULT);//提交一個事務
	/*
	sword OCITransCommit ( 
	OCISvcCtx    *svchp,  //服務環境句柄 
	OCIError     *errhp, //錯誤句柄
	ub4          flags ); //OCI_DEFAULT 	
		*/


	fp_OCI=fopen(strFilename,"wb"); //打開外部文件
	BOOL tb=TRUE;
	if(fp_OCI)
	{
		tb=CallbackReadLob();
	} 
	fclose(fp_OCI);	//關閉文件
	return tb;

	
}

BOOL COCIclass::CallbackReadLob()
{
	ub4 offset=1,amtp=0;
	ub1 bufp[LOB_BUF_LEN];
	sword status;
	CString tt;
	ub4 loblengtht=0;	

	//獲得LOB的數據長度,存儲到loblength變量中
	OCILobGetLength(svchp,errhp,lob_loc[0],&loblengtht);

	if(loblengtht<=0) //如果LOB的數據長度<=0，返回錯誤，
		return FALSE;

	amtp=loblengtht;
	//讀取LOB數據
	if(status=OCILobRead(svchp,errhp,lob_loc[0],&amtp,offset,(dvoid*)bufp,
		(ub4)LOB_BUF_LEN,(dvoid*)0,callback_Read_OCI,(ub2)0,(ub1)SQLCS_IMPLICIT))
	{
		return FALSE;
		MessageBox(NULL,"錯誤數據!","讀取LOB數據",MB_ICONSTOP);
	}	
	return TRUE;
}
/*
OCILobRead(handle_service,handle_error,p_blob,&amt,1,read_buf+offset-1, (ub4)LOB_BUF_LEN,NULL,NULL …); 
//加亮的1表示第一次讀的位移，在流模式下，此參數和amt一樣，只有在第一次讀時有效 
//加亮的NULL表示回調函數為空，這樣流模式使用輪詢（polling）方法而不是回調（callback）方法 
//輪詢方法下，如果沒有讀到blob末尾，函數返回OCI_NEED_DATA，讀取完畢，返回OCI_SUCCESS 
如果讀取完畢（OCI_NEED_DATA），跳出循環 

*/