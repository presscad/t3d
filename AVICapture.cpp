// CAVICapture.cpp: implementation of the CCAVICapture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Render.h"
#include "AVICapture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAVICapture::CAVICapture() :
    width(-1),
    height(-1),
    frameRate(30.0f),
    frameCounter(0),
    capturing(false),
    aviFile(NULL),
    aviStream(NULL),
    compAviStream(NULL),
    image(NULL)
{
    AVIFileInit(); //AVI文件初始化
}


CAVICapture::~CAVICapture()
{
    cleanup();//清空內存
    AVIFileExit(); //關閉文件
}

//在錄製OpengL動畫之前，首先需要設置AVI文件名稱、錄製幀的大小、錄製幀率、AVI文件壓縮方式等信息，具體的源代碼如下：
bool CAVICapture::start(CString filename,int w, int h,float fps)
{
    if (capturing)
        return false;

    width = w;
    height = h;
    frameRate = fps;

    if (HIWORD(VideoForWindowsVersion()) < 0x010a)
    {
        // 版本號必須大於1.1
        return false;
    }

    int rowBytes = (width * 3 + 3) & ~0x3;
    image = new unsigned char[rowBytes * height]; 
	//  創建AVI文件
    HRESULT hr = AVIFileOpen(&aviFile,
                             filename,
                             OF_WRITE | OF_CREATE,
                             NULL);
    if (hr != AVIERR_OK)
    {
        MessageBox(NULL,"創建AVI文件失敗","錯誤",MB_OK);
        return false;
    }
	//  AVI文件的頭信息
    AVISTREAMINFO info;
    ZeroMemory(&info, sizeof info);
    info.fccType = streamtypeVIDEO;
    info.fccHandler = 0;
    info.dwScale = 1;
    info.dwRate = (DWORD) frameRate;
    info.dwSuggestedBufferSize = rowBytes * height;
    SetRect(&info.rcFrame, 0, 0, width, height);
    hr = AVIFileCreateStream(aviFile, &aviStream, &info);//創建AVI文件流
    if (hr != AVIERR_OK)
    {
        MessageBox(NULL,"創建AVI文件流失敗","錯誤",MB_OK);
        cleanup(); //清空內存
        return false;
    }

    // 允許用戶選擇壓縮方式
    AVICOMPRESSOPTIONS options;
    AVICOMPRESSOPTIONS* arrOptions[1] = { &options };
    ZeroMemory(&options, sizeof options);
    if (!AVISaveOptions(NULL, 0, 1, &aviStream, 
                        (LPAVICOMPRESSOPTIONS*) &arrOptions))
    {
         cleanup();//清空內存
        return false;
    }

	//設置AVI壓縮方式
    hr = AVIMakeCompressedStream(&compAviStream, aviStream, &options, NULL);
    if (hr != AVIERR_OK)
    {
        MessageBox(NULL,"設置AVI壓縮方式失敗", "錯誤",MB_OK);
        cleanup();//清空內存
        return false;
    }

    BITMAPINFOHEADER bi;
    ZeroMemory(&bi, sizeof bi);
    bi.biSize = sizeof bi;
    bi.biWidth = width;
    bi.biHeight = height;
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = rowBytes * height;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;
	//  設置數據格式
    hr = AVIStreamSetFormat(compAviStream, 0, &bi, sizeof bi);
	 
    if (hr != AVIERR_OK)
    {
        MessageBox(NULL,"設置AVI數據格式","錯誤",MB_OK);
        cleanup();//清空內存
        return false;
    }

    capturing = true;
    frameCounter = 0;

    return true;
}


bool CAVICapture::end()
{
    capturing = false;
    cleanup(); //清空內存

    return true;
}

//在設置AVI文件的錄製選項之後，就可以將具體捕捉到的幀數據寫入到AVI文件中，實現這部分的代碼如下：
bool CAVICapture::captureFrame()
{
    if (!capturing)
        return false;
    // 獲得當前視口的尺寸
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    int x = viewport[0] + (viewport[2] - width) / 2;
    int y = viewport[1] + (viewport[3] - height) / 2;

	//  讀入屏幕上捕捉區域的像素
    glReadPixels(x, y, width, height,GL_BGR_EXT, GL_UNSIGNED_BYTE,image);
    int rowBytes = (width * 3 + 3) & ~0x3;
    LONG samplesWritten = 0;
    LONG bytesWritten = 0;

	//  寫入像素數據到AVI文件中
    HRESULT hr = AVIStreamWrite(compAviStream,
                                frameCounter,
                                1,
                                image,
                                rowBytes * height,
                                AVIIF_KEYFRAME,
                                &samplesWritten,
                                &bytesWritten);
    if (hr != AVIERR_OK)
    {
        MessageBox(NULL,"AVIStreamWrite failed on frame.", "ERROR",MB_OK);
        return false;
    }
    frameCounter++;
    return true;
}


void CAVICapture::cleanup()
{
    if (aviStream != NULL)
    {
        AVIStreamRelease(aviStream);
        aviStream = NULL;
    }
    if (compAviStream != NULL)
    {
        AVIStreamRelease(compAviStream);
        compAviStream = NULL;
    }
    if (aviFile != NULL)
    {
        AVIFileRelease(aviFile);
        aviFile = NULL;
    }
    if (image != NULL)
    {
        delete[] image;
        image = NULL;
    }
}

//返回寬度
int CAVICapture::getWidth() const
{
    return width;
}

//返回高度
int CAVICapture::getHeight() const
{
    return height;
}

//得到錄製幀率
float CAVICapture::getFrameRate() const
{
    return frameRate;
}


