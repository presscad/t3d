#ifndef _SKINPPWTL_H_
#define _SKINPPWTL_H_

#ifdef _SKINPP_STATIC
	#define SKINPPWTL_API
#else
	#ifdef SKINPPWTL_EXPORTS
		#define SKINPPWTL_API __declspec(dllexport)
	#else
		#define SKINPPWTL_API __declspec(dllimport)
	#endif
#endif

#define WM_TOOLBARPAINTPRE (WM_USER + 802)
#define WM_TOOLBARPAINTEND (WM_USER + 803)

#define SM_LBUTTONUP (WM_USER + 804)

//按鈕狀態
enum BUTTONSTATE 
{
	NORMAL	= 0,
	PRESS	= 1,
	DISABLE	= 2,
	HOT		= 3,
	FOCUS   = 4,
	LAST	= 5
};

//繪製類型
enum DRAWTYPE
{
	BUTTON = 0,
	SCROLLARROWUP = 1,
	SCROLLARROWDOWN = 2,
	SPLITTERBARHORZ = 3,
	SPLITTERBARVERT = 4,
	SPLITTERBARBORDER = 5,
	LISTHEAD = 6
};

//獲得皮膚資源的類型
enum SKINOBJTYPE
{
	DIALOGTYPE = 0,
	BUTTONTYPE = 1,
	CHECKBOXTYPE = 2,
	RADIOBOXTYPE = 3,
	STATICTYPE = 4,
	TRACKBARTYPE = 5,
};

struct ListBoxItem
{
	HIMAGELIST	hImageList;
	int			nImageIndex;

	ListBoxItem()
	{
		hImageList = NULL;
		nImageIndex = -1;
	}
};

#define REST_BITMAP      0x0001 //.bmp
#define REST_ICON        0x0002 //.ico
#define REST_CURSOR      0x0003 //.cur
#define REST_ANIMATE	 0x0004 //.ani

typedef struct _ResourceInfo
{
	HGDIOBJ hGdiObj;//[OUT]
	DWORD   dwType; //[OUT]
	int		nWidth; //[OUT]
	int		nHeight;//[OUT]

	TCHAR	szResImageName[_MAX_FNAME];//[IN]
	BOOL	bHorzSplit;//[IN]
	int		nLength;//[IN]
	int		nCount; //[IN]
	int		nIndex; //[IN]
	
	_ResourceInfo()
	{
		hGdiObj = NULL;
		dwType = REST_BITMAP;
		nWidth = 0;
		nHeight = 0;

		_tcscpy(szResImageName,_T(""));
		bHorzSplit = TRUE;
		nLength = -1;
		nCount = -1;
		nIndex = -1;
	}
	
}ResInfo,* PRESINFO;

//////////////////////////////////////////////////////////////////////////

//加載皮膚
//SkinFile		:皮膚路徑,注意可以是*.ssk,也可以是皮膚目錄中的INI文件.
//bFromIni		:該參數指定皮膚文件是從*.ssk讀取,還是從INI文件讀取.
SKINPPWTL_API BOOL  skinppLoadSkin(TCHAR* szSkinFile,BOOL bFromIni = FALSE);

SKINPPWTL_API BOOL skinppLoadSkinFromRes(HINSTANCE hInstance,LPCTSTR szResourceName,
										 LPCTSTR szResourceType,TCHAR* szSkinFileName);

//移除皮膚
SKINPPWTL_API BOOL  skinppRemoveSkin();

//退出界面庫，做清理工作。
SKINPPWTL_API BOOL  skinppExitSkin();

//設置ListBox控件的自畫信息
//hWnd			: ListBox控件的句柄
//nIndex		: Item項的索引
//pListBoxItem	: Item項自畫的結構信息
SKINPPWTL_API void skinppSetListBoxItemDrawInfo(HWND hWnd,int nIndex,struct ListBoxItem* pListBoxItem);

//獲得換膚後的系統顏色
//nColorIndex	: 要獲取的顏色類型
SKINPPWTL_API COLORREF skinppGetSkinSysColor(int nColorIndex);

//獲得Windows系統默認的顏色
//nColorIndex	: 要獲取的顏色類型
SKINPPWTL_API COLORREF skinppGetDefaultSysColor(int nColorIndex);

//hWnd			: 對話框窗口的句柄
//nResID		: 對話框資源ID
SKINPPWTL_API BOOL skinppSetWindowResID(HWND hWnd,int nResID);//[多語言]

SKINPPWTL_API BOOL skinppSetFreeDlgID(HWND hWnd,int nResID);

SKINPPWTL_API BOOL skinppSetSkinResID(HWND hWnd,int nResID);

//設置ListHeader窗口的排序信息
//hWnd			: ListHeader的窗口句柄
//nSortColumn	: 要對ListHeader排序的列的索引
//bSortAscending: 是否為升序
SKINPPWTL_API void skinppSetListHeaderSortInfo(HWND hWnd,int nSortColumn,BOOL bSortAscending = TRUE);

//在給定的HDC上,指定相應的繪製類型和狀態,在相應的矩形區域中進行繪製.
//hdc			:目標DC
//rect			:繪製區域
//eDrawType		:繪製類型，目前支持SPLITTERBARHORZ,SPLITTERBARVERT,SPLITTERBARBORDER
//nState		:選擇繪製狀態
SKINPPWTL_API void  skinppDrawSkinObject(HDC hdc,RECT rect,DRAWTYPE eDrawType,int nState);

//通過資源ID,獲得相應類型的皮膚資源位圖句柄
//nSkinObjType	: 皮膚類型,目前支持	DIALOGTYPE,BUTTONTYPE,CHECKBOXTYPE,RADIOBOXTYPE
//nResID		: 資源ID
//nState		: 狀態,對BUTTONTYPE,CHECKBOXTYPE,RADIOBOXTYPE有效
SKINPPWTL_API HBITMAP skinppGetResFromID(SKINOBJTYPE nSkinObjType,int nResID,int nState =0 );

//設置是否自己畫對話框背景,該方法用在需要自己對背景進行處理的情況下.
//hWnd			: 對話框的句柄
//bErase		: TRUE 為自己畫背景,FALSE 為Skin++畫,如果沒有調用該方法,Skin++將畫對話框背景.
SKINPPWTL_API void skinppSetDialogEraseBkgnd(HWND hWnd,BOOL bErase);

//設置對話框背景是否剪切子控件區域。
//hWnd			: 對話框句柄
//bNoClip		: TRUE為不需要剪切,FALSE為需要剪切區域
//bAllChild		: TRUE為該窗體的所有子對話框都剪切.
SKINPPWTL_API void skinppSetDialogBkClipRgn(HWND hWnd,BOOL bClip,BOOL bAllChild = TRUE);

//通過皮膚資源名稱獲得皮膚資源中位圖
//szName		: 皮膚資源名稱
//HBITMAP		: 返回資源中的位圖
SKINPPWTL_API HBITMAP skinppGetBitmapRes(LPCTSTR szName);

//通過資源名稱取資源的內存指針
//szName		: 資源名稱
//nSize			: 資源大小
//pByte			: 返回值，成功返回非NULL，失敗返回NULL
SKINPPWTL_API BYTE*  skinppGetSkinResource(LPCTSTR szName,int& nSize);

//通過皮膚資源的名稱獲得位圖不被拉伸的區域值
//szName		: 皮膚資源名稱
//nTopHeight	: 返回不被拉伸的頂高
//nBottomHeight : 返回不被拉伸的底高
//nLeftWidth	: 返回不被拉伸的左寬
//nRightWidth	: 返回不被拉伸的右寬
SKINPPWTL_API BOOL skinppGetBitmapResRect(LPCTSTR szName,int& nTopHeight,int& nBottomHeight,
												   int& nLeftWidth,int& nRightWidth);

//設置窗口自畫是否自己來處理,該方法用於自畫部分需要自己處理的情況下
//hWnd			: 要自畫的窗口句柄
//bCustomDraw	: TRUE為自己處理自畫,FALSE為交給Skin++處理自畫
SKINPPWTL_API void skinppSetCustomDraw(HWND hWnd,BOOL bCustomDraw);

//設置菜單的皮膚標識
//hWnd			: 擁有菜單的窗口句柄
//nSkinObjectID	: 菜單皮膚的標識
SKINPPWTL_API void skinppSetMenuSkinObjectID(HWND hWnd,int nSkinObjectID);

//設置是否對自畫菜單進行換膚
//bSkin			: TRUE為換膚
SKINPPWTL_API void skinppSetSkinOwnerMenu(BOOL bSkin);

//對菜單進行換膚控制
//hMenu   : 想換膚的菜單句柄
//bNoSkin : 是否換膚,TRUE為不換膚,FALSE為換膚
SKINPPWTL_API void  skinppSetDrawMenu(HMENU hMenu,BOOL bNoSkin);
	
//對指定的窗口去掉皮膚,並且保證不會再被換膚,即使使用SetSkinHwnd也不會換膚.
//hWnd			: 指定的窗口句柄
//bChildNoSkin	: 是否對該窗口中的子窗口去掉皮膚
SKINPPWTL_API void skinppSetNoSkinHwnd(HWND hWnd,BOOL bChildNoSkin = TRUE);

//對指定的窗口進行換膚
//hWnd			: 指定的窗口句柄
//szClassName	: 要子類化的Skin類型 WC_DIALOGBOX/WC_CONTROLBAR等
SKINPPWTL_API void skinppSetSkinHwnd(HWND hWnd,LPCTSTR szClassName = NULL);

//對指定的窗口臨時去掉皮膚,可以通過SetSkinHwnd進行再次換膚
SKINPPWTL_API void skinppRemoveSkinHwnd(HWND hWnd);

//是對SetNoSkinHwnd的進一步處理,可以解決使用SetNoSkinHwnd引起的Debug版的斷言錯
#define SETNOSKINHWND(x) {\
    HWND w=(x).UnsubclassWindow();\
	skinppSetNoSkinHwnd(w);\
	(x).SubclassWindow(w);\
} 

//是對RemoveSkinHwnd的進一步處理,可以解決使用RemoveSkinHwnd引起的Debug版的斷言錯
#define REMOVESKINHWND(x){\
    HWND w=(x).UnsubclassWindow();\
	skinppRemoveSkinHwnd(w);\
	(x).SubclassWindow(w);\
}

SKINPPWTL_API HGDIOBJ skinppGetResFromID(PRESINFO pResInfo);


#endif //_SKINPPWTL_H_

