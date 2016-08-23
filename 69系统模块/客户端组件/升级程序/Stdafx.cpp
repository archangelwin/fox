#include "stdafx.h"

//ѹ���ļ�
#include "Compress\ZLib.h"

//�����ļ�
#ifndef _DEBUG
	#pragma comment(lib,"Version")
	#pragma comment(lib,"Compress\\ZLib.lib")
#else
	#pragma comment(lib,"Version")
	#pragma comment(lib,"Compress\\ZLibD.lib")
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////

//�궨��
#define XOR_TIMES					8									//���ܱ���
#define MAX_SOURCE_LEN				64									//��󳤶�
#define MAX_ENCRYPT_LEN				(MAX_SOURCE_LEN*XOR_TIMES)			//��󳤶�

//��Կ����
#define ENCRYPT_KEY_LEN				8									//��Կ����

/////////////////////////////////////////////////////////////////////////////////////////////////
//����Ŀ¼
bool GetWorkDirectory(TCHAR szWorkDirectory[], WORD wBufferCount)
{
	//ģ��·��
	TCHAR szModulePath[MAX_PATH]=TEXT("");
	GetModuleFileName(AfxGetInstanceHandle(),szModulePath,CountArray(szModulePath));

	//�����ļ�
	for (INT i=lstrlen(szModulePath);i>=0;i--)
	{
		if (szModulePath[i]==TEXT('\\'))
		{
			szModulePath[i]=0;
			break;
		}
	}

	//���ý��
	ASSERT(szModulePath[0]!=0);
	lstrcpyn(szWorkDirectory,szModulePath,wBufferCount);

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//ѹ������
ULONG CompressData(LPBYTE pcbSourceData, ULONG lSourceSize, BYTE cbResultData[], ULONG lResultSize)
{
	//ѹ������
	if (compress(cbResultData,&lResultSize,pcbSourceData,lSourceSize)==0L)
	{
		return lResultSize;
	}

	return 0L;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

//��ѹ����
ULONG UnCompressData(LPBYTE pcbSourceData, ULONG lSourceSize, BYTE cbResultData[], ULONG lResultSize)
{
	//��ѹ����
	if (uncompress(cbResultData,&lResultSize,pcbSourceData,lSourceSize)==0L)
	{
		return lResultSize;
	}

	return 0L;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

