#pragma once

//////////////////////////////////////////////////////////////////////////////////

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WINVER
#define WINVER 0x601
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x601
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0400
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#endif

#define _ATL_ATTRIBUTES
#define _AFX_ALL_WARNINGS
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

//////////////////////////////////////////////////////////////////////////////////

//MFC �ļ�
#include <AfxWin.h>
#include <AfxExt.h>
#include <AfxCmn.h>
#include <AfxDisp.h>
#include <afxmt.h>

//MFC �ļ�
#include <Nb30.h>
#include <AfxInet.h>
#include <GdiPlus.h>
#include <AtlImage.h>

//�����ռ�
using namespace Gdiplus;

//////////////////////////////////////////////////////////////////////////////////

//ƽ̨�ļ�
#include "..\..\ȫ�ֶ���\Platform.h"

//�ؼ��ļ�
#include "PngImage\PngImage.h"

//////////////////////////////////////////////////////////////////////////////////
//��������

//����Ŀ¼
bool GetWorkDirectory(TCHAR szWorkDirectory[], WORD wBufferCount);

//ѹ������
ULONG CompressData(LPBYTE pcbSourceData, ULONG lSourceSize, BYTE cbResultData[], ULONG lResultSize);

//��ѹ����
ULONG UnCompressData(LPBYTE pcbSourceData, ULONG lSourceSize, BYTE cbResultData[], ULONG lResultSize);

//////////////////////////////////////////////////////////////////////////////////
