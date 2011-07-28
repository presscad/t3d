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
    AVIFileInit(); //AVI����l��
}


CAVICapture::~CAVICapture()
{
    cleanup();//�M�Ť��s
    AVIFileExit(); //�������
}

//�b���sOpengL�ʵe���e�A�����ݭn�]�mAVI���W�١B���s�V���j�p�B���s�V�v�BAVI������Y�覡���H���A���骺���N�X�p�U�G
bool CAVICapture::start(CString filename,int w, int h,float fps)
{
    if (capturing)
        return false;

    width = w;
    height = h;
    frameRate = fps;

    if (HIWORD(VideoForWindowsVersion()) < 0x010a)
    {
        // �����������j��1.1
        return false;
    }

    int rowBytes = (width * 3 + 3) & ~0x3;
    image = new unsigned char[rowBytes * height]; 
	//  �Ы�AVI���
    HRESULT hr = AVIFileOpen(&aviFile,
                             filename,
                             OF_WRITE | OF_CREATE,
                             NULL);
    if (hr != AVIERR_OK)
    {
        MessageBox(NULL,"�Ы�AVI��󥢱�","���~",MB_OK);
        return false;
    }
	//  AVI����Y�H��
    AVISTREAMINFO info;
    ZeroMemory(&info, sizeof info);
    info.fccType = streamtypeVIDEO;
    info.fccHandler = 0;
    info.dwScale = 1;
    info.dwRate = (DWORD) frameRate;
    info.dwSuggestedBufferSize = rowBytes * height;
    SetRect(&info.rcFrame, 0, 0, width, height);
    hr = AVIFileCreateStream(aviFile, &aviStream, &info);//�Ы�AVI���y
    if (hr != AVIERR_OK)
    {
        MessageBox(NULL,"�Ы�AVI���y����","���~",MB_OK);
        cleanup(); //�M�Ť��s
        return false;
    }

    // ���\�Τ������Y�覡
    AVICOMPRESSOPTIONS options;
    AVICOMPRESSOPTIONS* arrOptions[1] = { &options };
    ZeroMemory(&options, sizeof options);
    if (!AVISaveOptions(NULL, 0, 1, &aviStream, 
                        (LPAVICOMPRESSOPTIONS*) &arrOptions))
    {
         cleanup();//�M�Ť��s
        return false;
    }

	//�]�mAVI���Y�覡
    hr = AVIMakeCompressedStream(&compAviStream, aviStream, &options, NULL);
    if (hr != AVIERR_OK)
    {
        MessageBox(NULL,"�]�mAVI���Y�覡����", "���~",MB_OK);
        cleanup();//�M�Ť��s
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
	//  �]�m�ƾڮ榡
    hr = AVIStreamSetFormat(compAviStream, 0, &bi, sizeof bi);
	 
    if (hr != AVIERR_OK)
    {
        MessageBox(NULL,"�]�mAVI�ƾڮ榡","���~",MB_OK);
        cleanup();//�M�Ť��s
        return false;
    }

    capturing = true;
    frameCounter = 0;

    return true;
}


bool CAVICapture::end()
{
    capturing = false;
    cleanup(); //�M�Ť��s

    return true;
}

//�b�]�mAVI��󪺿��s�ﶵ����A�N�i�H�N���鮷���쪺�V�ƾڼg�J��AVI��󤤡A��{�o�������N�X�p�U�G
bool CAVICapture::captureFrame()
{
    if (!capturing)
        return false;
    // ��o��e���f���ؤo
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    int x = viewport[0] + (viewport[2] - width) / 2;
    int y = viewport[1] + (viewport[3] - height) / 2;

	//  Ū�J�̹��W�����ϰ쪺����
    glReadPixels(x, y, width, height,GL_BGR_EXT, GL_UNSIGNED_BYTE,image);
    int rowBytes = (width * 3 + 3) & ~0x3;
    LONG samplesWritten = 0;
    LONG bytesWritten = 0;

	//  �g�J�����ƾڨ�AVI���
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

//��^�e��
int CAVICapture::getWidth() const
{
    return width;
}

//��^����
int CAVICapture::getHeight() const
{
    return height;
}

//�o����s�V�v
float CAVICapture::getFrameRate() const
{
    return frameRate;
}


