#include "StdAfx.h"
#include "Resource.h"
#include "SkinLayered.h"


//////////////////////////////////////////////////////////////////////////////////
//��������

//Բ�Ǵ�С
#define ROUND_CX					5									//Բ�ǿ��
#define ROUND_CY					5									//Բ�Ǹ߶�

//��Ӱ����
#define SHADOW_CX					5									//��Ӱ���
#define SHADOW_CY					5									//��Ӱ�߶�

//////////////////////////////////////////////////////////////////////////////////
//���ɱ���

//ʱ���ʶ
#define IDI_TRANSITION				10									//���ɱ�ʶ
#define TIME_TRANSITION				30									//����ʱ��

//��������
#define MIN_TRANSITION_INDEX		0									//��������
#define MAX_TRANSITION_INDEX		8									//��������

//////////////////////////////////////////////////////////////////////////////////

//ö�ٽṹ
struct tagEnumChildInfo
{
	CWnd *							pWndControl;						//���ƴ���
	CWnd *							pWndLayered;						//�ֲ㴰��
	CRgn *							pRegionResult;						//�������
};


//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CSkinLayered, CWnd)
	ON_WM_CLOSE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CSkinLayered::CSkinLayered()
{
	//���ñ���
	m_pWndControl=NULL;

	return;
}

//��������
CSkinLayered::~CSkinLayered()
{
}

//��������
VOID CSkinLayered::CreateLayered(CWnd * pWndControl, CRect & rcWindow)
{
	//Ч�����
	ASSERT((pWndControl!=NULL)&&(pWndControl->m_hWnd!=NULL));
	if ((pWndControl==NULL)||(pWndControl->m_hWnd==NULL)) return;

	//���ñ���
	m_pWndControl=pWndControl;

	//��������
	CreateEx(WS_EX_LAYERED,TEXT("STATIC"),TEXT(""),0,rcWindow,pWndControl,0L);

	return;
}

//��������
VOID CSkinLayered::InitLayeredArea(CDC * pDCImage, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild)
{
	//Ч�����
	ASSERT((pDCImage!=NULL)&&(pDCImage->m_hDC!=NULL));
	if ((pDCImage==NULL)||(pDCImage->m_hDC==NULL)) return;

	//��������
	BITMAP Bitmap;
	ZeroMemory(&Bitmap,sizeof(Bitmap));

	//��ȡͼ��
	CBitmap * pBitmap=pDCImage->GetCurrentBitmap();
	if (pBitmap!=NULL) pBitmap->GetBitmap(&Bitmap);

	//��ȡ��С
	CSize SizeImage;
	SizeImage.SetSize(Bitmap.bmWidth,Bitmap.bmHeight);

	//Ч���С
	ASSERT((SizeImage.cx>0)&&(SizeImage.cy>0));
	if ((SizeImage.cx==0)||(SizeImage.cy==0)) return;

	//��������
	BLENDFUNCTION BlendFunction;
	ZeroMemory(&BlendFunction,sizeof(BlendFunction));

	//���ò���
	BlendFunction.BlendOp=0;
	BlendFunction.BlendFlags=0;
	BlendFunction.AlphaFormat=AC_SRC_ALPHA;
	BlendFunction.SourceConstantAlpha=cbAlpha;

	//���÷ֲ�
	CPoint ImagePoint(0,0);
	CClientDC ClientDC(this);
	UpdateLayeredWindow(&ClientDC,NULL,&SizeImage,pDCImage,&ImagePoint,0L,&BlendFunction,ULW_ALPHA);

	//��������
	CRgn RegionResult;
	RegionResult.CreateRectRgn(0,0,SizeImage.cx,SizeImage.cy);

	//�����ų�
	if (bUnLayeredChild==true)
	{
		//��������
		tagEnumChildInfo EnumChildInfo;
		ZeroMemory(&EnumChildInfo,sizeof(EnumChildInfo));

		//���ñ���
		EnumChildInfo.pWndLayered=this;
		EnumChildInfo.pWndControl=m_pWndControl;
		EnumChildInfo.pRegionResult=&RegionResult;

		//ö�ٴ���
		ASSERT(m_pWndControl->GetSafeHwnd()!=NULL);
		EnumChildWindows(m_pWndControl->m_hWnd,EnumChildProc,(LPARAM)&EnumChildInfo);
	}

	//�����ų�
	if (rcUnLayered.IsRectEmpty()==FALSE)
	{
		//��������
		CRgn RegionUnLayered;
		RegionUnLayered.CreateRoundRectRgn(rcUnLayered.left,rcUnLayered.top,rcUnLayered.right+1,rcUnLayered.bottom+1,PointRound.x,PointRound.y);

		//�ϲ�����
		RegionResult.CombineRgn(&RegionResult,&RegionUnLayered,RGN_DIFF);
	}

	//��������
	SetWindowRgn(RegionResult,TRUE);

	return;
}

//��������
VOID CSkinLayered::InitLayeredArea(CPngImage & Image, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild)
{
	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(Image.GetWidth(),Image.GetHeight(),32);

	//�滭����
	CImageDC ImageDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(ImageDC);

	//�滭����
	ASSERT(pBufferDC!=NULL);
	if (pBufferDC!=NULL) Image.DrawImage(pBufferDC,0,0);

	//�����ֲ�
	InitLayeredArea(pBufferDC,cbAlpha,rcUnLayered,PointRound,bUnLayeredChild);

	return;
}

//�ر���Ϣ
VOID CSkinLayered::OnClose()
{
	//Ͷ����Ϣ
	if (m_pWndControl!=NULL)
	{
		m_pWndControl->PostMessage(WM_CLOSE);
	}

	return;
}

//������Ϣ
VOID CSkinLayered::OnSetFocus(CWnd * pOldWnd)
{
	//���ý���
	if (m_pWndControl!=NULL)
	{
		m_pWndControl->SetFocus();
	}
}

//ö�ٺ���
BOOL CALLBACK CSkinLayered::EnumChildProc(HWND hWndChild, LPARAM lParam)
{
	//��ȡλ��
	CRect rcWindow;
	::GetWindowRect(hWndChild,&rcWindow);

	//��������
	if ((rcWindow.Width()>0)&&(rcWindow.Height()>0))
	{
		//��������
		ASSERT(lParam!=0L);
		tagEnumChildInfo * pEnumChildInfo=(tagEnumChildInfo *)lParam;

		//�����ж�
		HWND hWndParent=::GetParent(hWndChild);
		if (hWndParent!=pEnumChildInfo->pWndControl->GetSafeHwnd())
		{
			return TRUE;
		}

		//ת��λ��
		ASSERT(pEnumChildInfo->pWndControl!=NULL);
		pEnumChildInfo->pWndControl->ScreenToClient(&rcWindow);

		//��������
		CRgn RgnChild;
		RgnChild.CreateRectRgn(rcWindow.left,rcWindow.top,rcWindow.right,rcWindow.bottom);

		//�ϲ�����
		ASSERT(pEnumChildInfo->pRegionResult!=NULL);
		pEnumChildInfo->pRegionResult->CombineRgn(pEnumChildInfo->pRegionResult,&RgnChild,RGN_DIFF);
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////
