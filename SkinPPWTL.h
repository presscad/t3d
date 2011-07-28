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

//���s���A
enum BUTTONSTATE 
{
	NORMAL	= 0,
	PRESS	= 1,
	DISABLE	= 2,
	HOT		= 3,
	FOCUS   = 4,
	LAST	= 5
};

//ø�s����
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

//��o�ֽ��귽������
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

//�[���ֽ�
//SkinFile		:�ֽ����|,�`�N�i�H�O*.ssk,�]�i�H�O�ֽ��ؿ�����INI���.
//bFromIni		:�ӰѼƫ��w�ֽ����O�q*.sskŪ��,�٬O�qINI���Ū��.
SKINPPWTL_API BOOL  skinppLoadSkin(TCHAR* szSkinFile,BOOL bFromIni = FALSE);

SKINPPWTL_API BOOL skinppLoadSkinFromRes(HINSTANCE hInstance,LPCTSTR szResourceName,
										 LPCTSTR szResourceType,TCHAR* szSkinFileName);

//�����ֽ�
SKINPPWTL_API BOOL  skinppRemoveSkin();

//�h�X�ɭ��w�A���M�z�u�@�C
SKINPPWTL_API BOOL  skinppExitSkin();

//�]�mListBox���󪺦۵e�H��
//hWnd			: ListBox���󪺥y�`
//nIndex		: Item��������
//pListBoxItem	: Item���۵e�����c�H��
SKINPPWTL_API void skinppSetListBoxItemDrawInfo(HWND hWnd,int nIndex,struct ListBoxItem* pListBoxItem);

//��o�����᪺�t���C��
//nColorIndex	: �n������C������
SKINPPWTL_API COLORREF skinppGetSkinSysColor(int nColorIndex);

//��oWindows�t���q�{���C��
//nColorIndex	: �n������C������
SKINPPWTL_API COLORREF skinppGetDefaultSysColor(int nColorIndex);

//hWnd			: ��ܮص��f���y�`
//nResID		: ��ܮظ귽ID
SKINPPWTL_API BOOL skinppSetWindowResID(HWND hWnd,int nResID);//[�h�y��]

SKINPPWTL_API BOOL skinppSetFreeDlgID(HWND hWnd,int nResID);

SKINPPWTL_API BOOL skinppSetSkinResID(HWND hWnd,int nResID);

//�]�mListHeader���f���ƧǫH��
//hWnd			: ListHeader�����f�y�`
//nSortColumn	: �n��ListHeader�ƧǪ��C������
//bSortAscending: �O�_���ɧ�
SKINPPWTL_API void skinppSetListHeaderSortInfo(HWND hWnd,int nSortColumn,BOOL bSortAscending = TRUE);

//�b���w��HDC�W,���w������ø�s�����M���A,�b�������x�ΰϰ줤�i��ø�s.
//hdc			:�ؼ�DC
//rect			:ø�s�ϰ�
//eDrawType		:ø�s�����A�ثe���SPLITTERBARHORZ,SPLITTERBARVERT,SPLITTERBARBORDER
//nState		:���ø�s���A
SKINPPWTL_API void  skinppDrawSkinObject(HDC hdc,RECT rect,DRAWTYPE eDrawType,int nState);

//�q�L�귽ID,��o�����������ֽ��귽��ϥy�`
//nSkinObjType	: �ֽ�����,�ثe���	DIALOGTYPE,BUTTONTYPE,CHECKBOXTYPE,RADIOBOXTYPE
//nResID		: �귽ID
//nState		: ���A,��BUTTONTYPE,CHECKBOXTYPE,RADIOBOXTYPE����
SKINPPWTL_API HBITMAP skinppGetResFromID(SKINOBJTYPE nSkinObjType,int nResID,int nState =0 );

//�]�m�O�_�ۤv�e��ܮحI��,�Ӥ�k�Φb�ݭn�ۤv��I���i��B�z�����p�U.
//hWnd			: ��ܮت��y�`
//bErase		: TRUE ���ۤv�e�I��,FALSE ��Skin++�e,�p�G�S���եθӤ�k,Skin++�N�e��ܮحI��.
SKINPPWTL_API void skinppSetDialogEraseBkgnd(HWND hWnd,BOOL bErase);

//�]�m��ܮحI���O�_�Ť��l����ϰ�C
//hWnd			: ��ܮإy�`
//bNoClip		: TRUE�����ݭn�Ť�,FALSE���ݭn�Ť��ϰ�
//bAllChild		: TRUE���ӵ��骺�Ҧ��l��ܮس��Ť�.
SKINPPWTL_API void skinppSetDialogBkClipRgn(HWND hWnd,BOOL bClip,BOOL bAllChild = TRUE);

//�q�L�ֽ��귽�W����o�ֽ��귽�����
//szName		: �ֽ��귽�W��
//HBITMAP		: ��^�귽�������
SKINPPWTL_API HBITMAP skinppGetBitmapRes(LPCTSTR szName);

//�q�L�귽�W�٨��귽�����s���w
//szName		: �귽�W��
//nSize			: �귽�j�p
//pByte			: ��^�ȡA���\��^�DNULL�A���Ѫ�^NULL
SKINPPWTL_API BYTE*  skinppGetSkinResource(LPCTSTR szName,int& nSize);

//�q�L�ֽ��귽���W����o��Ϥ��Q�Ԧ����ϰ��
//szName		: �ֽ��귽�W��
//nTopHeight	: ��^���Q�Ԧ�������
//nBottomHeight : ��^���Q�Ԧ�������
//nLeftWidth	: ��^���Q�Ԧ������e
//nRightWidth	: ��^���Q�Ԧ����k�e
SKINPPWTL_API BOOL skinppGetBitmapResRect(LPCTSTR szName,int& nTopHeight,int& nBottomHeight,
												   int& nLeftWidth,int& nRightWidth);

//�]�m���f�۵e�O�_�ۤv�ӳB�z,�Ӥ�k�Ω�۵e�����ݭn�ۤv�B�z�����p�U
//hWnd			: �n�۵e�����f�y�`
//bCustomDraw	: TRUE���ۤv�B�z�۵e,FALSE���浹Skin++�B�z�۵e
SKINPPWTL_API void skinppSetCustomDraw(HWND hWnd,BOOL bCustomDraw);

//�]�m��檺�ֽ�����
//hWnd			: �֦���檺���f�y�`
//nSkinObjectID	: ���ֽ�������
SKINPPWTL_API void skinppSetMenuSkinObjectID(HWND hWnd,int nSkinObjectID);

//�]�m�O�_��۵e���i�洫��
//bSkin			: TRUE������
SKINPPWTL_API void skinppSetSkinOwnerMenu(BOOL bSkin);

//����i�洫������
//hMenu   : �Q���������y�`
//bNoSkin : �O�_����,TRUE��������,FALSE������
SKINPPWTL_API void  skinppSetDrawMenu(HMENU hMenu,BOOL bNoSkin);
	
//����w�����f�h���ֽ�,�åB�O�Ҥ��|�A�Q����,�Y�Ϩϥ�SetSkinHwnd�]���|����.
//hWnd			: ���w�����f�y�`
//bChildNoSkin	: �O�_��ӵ��f�����l���f�h���ֽ�
SKINPPWTL_API void skinppSetNoSkinHwnd(HWND hWnd,BOOL bChildNoSkin = TRUE);

//����w�����f�i�洫��
//hWnd			: ���w�����f�y�`
//szClassName	: �n�l���ƪ�Skin���� WC_DIALOGBOX/WC_CONTROLBAR��
SKINPPWTL_API void skinppSetSkinHwnd(HWND hWnd,LPCTSTR szClassName = NULL);

//����w�����f�{�ɥh���ֽ�,�i�H�q�LSetSkinHwnd�i��A������
SKINPPWTL_API void skinppRemoveSkinHwnd(HWND hWnd);

//�O��SetNoSkinHwnd���i�@�B�B�z,�i�H�ѨM�ϥ�SetNoSkinHwnd�ް_��Debug�����_����
#define SETNOSKINHWND(x) {\
    HWND w=(x).UnsubclassWindow();\
	skinppSetNoSkinHwnd(w);\
	(x).SubclassWindow(w);\
} 

//�O��RemoveSkinHwnd���i�@�B�B�z,�i�H�ѨM�ϥ�RemoveSkinHwnd�ް_��Debug�����_����
#define REMOVESKINHWND(x){\
    HWND w=(x).UnsubclassWindow();\
	skinppRemoveSkinHwnd(w);\
	(x).SubclassWindow(w);\
}

SKINPPWTL_API HGDIOBJ skinppGetResFromID(PRESINFO pResInfo);


#endif //_SKINPPWTL_H_

