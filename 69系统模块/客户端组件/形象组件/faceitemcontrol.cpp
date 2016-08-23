#include "StdAfx.h"
#include "Resource.h"
#include "FaceItemControl.h"

//////////////////////////////////////////////////////////////////////////////////
//��̬����

CFaceItemControl *	CFaceItemControl::m_pFaceItemControl=NULL;			//ͷ��ӿ�

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CFaceItemControl::CFaceItemControl()
{
	//���ö���
	ASSERT(m_pFaceItemControl==NULL);
	if (m_pFaceItemControl==NULL) m_pFaceItemControl=this;

	//������Դ
	HINSTANCE hResInstance=GetModuleHandle(AVATAR_CONTROL_DLL_NAME);
	m_ImageUserFace.LoadImage(hResInstance,TEXT("USER_FACE_IMAGE"));
	m_ImageItemFrame.LoadImage(hResInstance,TEXT("FACE_ITEM_FRAME"));

	m_ImageBigFace.LoadImage(hResInstance,TEXT("USER_FACE_BIG"));
	m_ImageSmallFace.LoadImage(hResInstance,TEXT("USER_FACE_SMALL"));
	m_ImageTableFace.LoadImage(hResInstance,TEXT("USER_FACE_TABLE"));

	//���ñ���
	m_wLineCount=m_ImageUserFace.GetWidth()/32;
	m_wFullCount=m_wLineCount*m_ImageUserFace.GetHeight()/(32*2);

	//���ô�С
	m_SizeItemFrame.SetSize(m_ImageItemFrame.GetWidth()/3,m_ImageItemFrame.GetHeight());

	return;
}

//��������
CFaceItemControl::~CFaceItemControl()
{
	//���ö���
	ASSERT(m_pFaceItemControl==this);
	if (m_pFaceItemControl==this) m_pFaceItemControl=NULL;

	return;
}

//�ӿڲ�ѯ
VOID * CFaceItemControl::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IFaceItemControl,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IFaceItemControl,Guid,dwQueryVer);
	return NULL;
}

//ͷ����Ŀ
WORD CFaceItemControl::GetFaceCount()
{
	return 2;
}

//��ȡ�ߴ�
VOID CFaceItemControl::GetFaceItemSize(CSize & SizeFace)
{
	//���ñ���
	SizeFace.SetSize(FACE_CX,FACE_CY);

	return;
}

//��ȡ��Դ
VOID CFaceItemControl::GetAvatarResource(tagAvatarResource & AvatarResource)
{
	//���ñ���
	AvatarResource.pszResource=TEXT("USER_FACE_IMAGE");
	AvatarResource.hResInstance=GetModuleHandle(AVATAR_CONTROL_DLL_NAME);

	return;
}

//�滭���
VOID CFaceItemControl::DrawFaceItemFrame(CDC * pDC, INT nXPos, INT nYPos, BYTE cbFrameKind)
{
	//Ч�����
	ASSERT(cbFrameKind<=ITEM_FRAME_HITDOWN);
	if (cbFrameKind>ITEM_FRAME_HITDOWN) return;

	//�滭���
	INT nXImagePos=m_SizeItemFrame.cx*cbFrameKind;
	m_ImageItemFrame.DrawImage(pDC,nXPos-5,nYPos-5,m_SizeItemFrame.cx,m_SizeItemFrame.cy,nXImagePos,0);

	return;
}

//�滭ͷ��
VOID CFaceItemControl::DrawFaceNormal(CDC * pDC, INT nXPos, INT nYPos, WORD wFaceID)
{
	//��������
	if (wFaceID>=m_wFullCount) wFaceID=0;

	//�滭ͷ��
	INT nXImagePos=wFaceID%m_wLineCount;
	INT nYImagePos=(wFaceID/m_wLineCount)*2L;
	m_ImageUserFace.DrawImage(pDC,nXPos,nYPos,FACE_CX,FACE_CY,nXImagePos*FACE_CX,nYImagePos*FACE_CY);

	return;
}

//�滭ͷ��
VOID CFaceItemControl::DrawFaceOffLine(CDC * pDC, INT nXPos, INT nYPos, WORD wFaceID)
{
	//��������
	if (wFaceID>=m_wFullCount) wFaceID=0;

	//�滭ͷ��
	INT nXImagePos=wFaceID%m_wLineCount;
	INT nYImagePos=(wFaceID/m_wLineCount)*2L;
	m_ImageUserFace.DrawImage(pDC,nXPos,nYPos,FACE_CX,FACE_CY,nXImagePos*FACE_CX,nYImagePos*FACE_CY+FACE_CY);

	return;
}

//�滭ͷ��
VOID CFaceItemControl::DrawFaceNormal(CDC * pDC, INT nXPos, INT nYPos, DWORD dwCustomFace[FACE_CX*FACE_CY])
{
	//����λͼ
	CImage ImageCustomFace;
	ImageCustomFace.Create(FACE_CX,FACE_CY,32);

	//��ȡ����
	INT nImagePitch=ImageCustomFace.GetPitch();
	LPBYTE cbBitCustomFace=(LPBYTE)ImageCustomFace.GetBits();

	//��������
	for (INT nYImagePos=0;nYImagePos<FACE_CY;nYImagePos++)
	{
		for (INT nXImagePos=0;nXImagePos<FACE_CX;nXImagePos++)
		{
			//������ɫ
			DWORD dwImageTarget=nYImagePos*nImagePitch+nXImagePos*4L;
			*(COLORREF *)(cbBitCustomFace+dwImageTarget)=dwCustomFace[nYImagePos*FACE_CX+nXImagePos];
		}
	}

	//�滭����
	ImageCustomFace.Draw(pDC->m_hDC,nXPos,nYPos);

	return;
}

//�滭ͷ��
VOID CFaceItemControl::DrawFaceOffLine(CDC * pDC, INT nXPos, INT nYPos, DWORD dwCustomFace[FACE_CX*FACE_CY])
{
	//����λͼ
	CImage ImageCustomFace;
	ImageCustomFace.Create(FACE_CX,FACE_CY,32);

	//��ȡ����
	INT nImagePitch=ImageCustomFace.GetPitch();
	LPBYTE cbBitCustomFace=(LPBYTE)ImageCustomFace.GetBits();

	//��������
	for (INT nYImagePos=0;nYImagePos<FACE_CY;nYImagePos++)
	{
		for (INT nXImagePos=0;nXImagePos<FACE_CX;nXImagePos++)
		{
			//������ɫ
			DWORD dwImageTarget=nYImagePos*nImagePitch+nXImagePos*4L;
			COLORREF crImageTarget=dwCustomFace[nYImagePos*FACE_CX+nXImagePos];

			//��ȡ��ɫ
			BYTE cbColorR=GetRValue(crImageTarget);
			BYTE cbColorG=GetGValue(crImageTarget);
			BYTE cbColorB=GetBValue(crImageTarget);
			BYTE cbColorGray=(BYTE)(cbColorR*0.30+cbColorG*0.59+cbColorB*0.11);

			//������ɫ
			*(COLORREF *)(cbBitCustomFace+dwImageTarget)=RGB(cbColorGray,cbColorGray,cbColorGray);
		}
	}

	//�滭����
	ImageCustomFace.Draw(pDC->m_hDC,nXPos,nYPos);

	return;
}

//�滭ͷ��
VOID CFaceItemControl::DrawFaceNormal(CDC * pDC, INT nXPos, INT nYPos, INT nWidth, INT nHeight, WORD wFaceID)
{
	//��������
	INT nYImagePos=0;
    if(wFaceID==1) 
	//�滭ͷ��
	{
	 nYImagePos=32;
	}
	else
	{
    nYImagePos=0;
	}
	m_ImageUserFace.DrawImage(pDC,nXPos,nYPos,32,32,nYImagePos,0);

	return;
}

//�滭ͷ��
VOID CFaceItemControl::DrawFaceOffLine(CDC * pDC, INT nXPos, INT nYPos, INT nWidth, INT nHeight, WORD wFaceID)
{
	//��������
	if (wFaceID>=m_wFullCount) wFaceID=0;

	//�滭ͷ��
	INT nXImagePos=wFaceID%m_wLineCount;
	INT nYImagePos=(wFaceID/m_wLineCount)*2L;
	m_ImageUserFace.DrawImage(pDC,nXPos,nYPos,nWidth,nHeight,nXImagePos*FACE_CX,nYImagePos*FACE_CY+FACE_CY,FACE_CX,FACE_CY);

	return;
}

//�滭ͷ��
VOID CFaceItemControl::DrawFaceNormal(CDC * pDC, INT nXPos, INT nYPos, INT nWidth, INT nHeight, DWORD dwCustomFace[FACE_CX*FACE_CY])
{
	//����λͼ
	CImage ImageCustomFace;
	ImageCustomFace.Create(FACE_CX,FACE_CY,32);

	//��ȡ����
	INT nImagePitch=ImageCustomFace.GetPitch();
	LPBYTE cbBitCustomFace=(LPBYTE)ImageCustomFace.GetBits();

	//��������
	for (INT nYImagePos=0;nYImagePos<FACE_CY;nYImagePos++)
	{
		for (INT nXImagePos=0;nXImagePos<FACE_CX;nXImagePos++)
		{
			//������ɫ
			DWORD dwImageTarget=nYImagePos*nImagePitch+nXImagePos*4L;
			*(COLORREF *)(cbBitCustomFace+dwImageTarget)=dwCustomFace[nYImagePos*FACE_CX+nXImagePos];
		}
	}

	//�滭����
	ImageCustomFace.Draw(pDC->m_hDC,nXPos,nYPos,nWidth,nHeight);

	return;
}

//�滭ͷ��
VOID CFaceItemControl::DrawFaceOffLine(CDC * pDC, INT nXPos, INT nYPos, INT nWidth, INT nHeight, DWORD dwCustomFace[FACE_CX*FACE_CY])
{
	//����λͼ
	CImage ImageCustomFace;
	ImageCustomFace.Create(FACE_CX,FACE_CY,32);

	//��ȡ����
	INT nImagePitch=ImageCustomFace.GetPitch();
	LPBYTE cbBitCustomFace=(LPBYTE)ImageCustomFace.GetBits();

	//��������
	for (INT nYImagePos=0;nYImagePos<FACE_CY;nYImagePos++)
	{
		for (INT nXImagePos=0;nXImagePos<FACE_CX;nXImagePos++)
		{
			//������ɫ
			DWORD dwImageTarget=nYImagePos*nImagePitch+nXImagePos*4L;
			COLORREF crImageTarget=dwCustomFace[nYImagePos*FACE_CX+nXImagePos];

			//��ȡ��ɫ
			BYTE cbColorR=GetRValue(crImageTarget);
			BYTE cbColorG=GetGValue(crImageTarget);
			BYTE cbColorB=GetBValue(crImageTarget);
			BYTE cbColorGray=(BYTE)(cbColorR*0.30+cbColorG*0.59+cbColorB*0.11);

			//������ɫ
			*(COLORREF *)(cbBitCustomFace+dwImageTarget)=RGB(cbColorGray,cbColorGray,cbColorGray);
		}
	}

	//�滭����
	ImageCustomFace.Draw(pDC->m_hDC,nXPos,nYPos,nWidth,nHeight);

	return;
}

//����ͷ��
VOID CFaceItemControl::DrawFaceBigNormal(CDC * pDC, INT nXPos, INT nYPos,WORD wGender)
{
	m_ImageBigFace.DrawImage(pDC,nXPos,nYPos,70,70,0,wGender*2*70);
}
//����ͷ��
VOID CFaceItemControl::DrawFaceSmallNormal(CDC * pDC, INT nXPos, INT nYPos,WORD wGender)
{
	m_ImageSmallFace.DrawImage(pDC,nXPos,nYPos,32,32,0,wGender*2*32);
}

//����ͷ��
//VOID CFaceItemControl::DrawFaceTableNormal(CDC * pDC, INT nXPos, INT nYPos,WORD wGender, WORD wFaceID)
//{
//	if(wFaceID>11) wFaceID=11;
//
//	m_ImageTableFace.DrawImage(pDC,nXPos,nYPos,32,32,wFaceID*32,wGender*32);
//
//
//}

VOID CFaceItemControl::DrawFaceTableNormal(CDC * pDC, INT nXPos, INT nYPos,BYTE cbGender, WORD wFaceID)
{
	//��������
	if (wFaceID>=11) 
		wFaceID=10;
	m_ImageTableFace.DrawImage(pDC,nXPos,nYPos,32,32,wFaceID*32,(cbGender==GENDER_MANKIND?1:0)*32);


}

//////////////////////////////////////////////////////////////////////////////////

//�����������
DECLARE_CREATE_MODULE(FaceItemControl);

//////////////////////////////////////////////////////////////////////////////////
