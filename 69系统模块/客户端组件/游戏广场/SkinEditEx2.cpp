#include "StdAfx.h"
#include ".\skineditex2.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CSkinEditEx2, CEdit)
	ON_WM_NCPAINT()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////

CSkinEditEx2::CSkinEditEx2(void)
{
}

CSkinEditEx2::~CSkinEditEx2(void)
{
}

//�ػ���Ϣ
VOID CSkinEditEx2::OnNcPaint()
{
	////״̬����
	//COLORREF crColorBK=RGB(250,250,250);
	//COLORREF crColorBorad=RGB(250,250,250);

	////�滭�߿�
	//CClientDC ClientDC(this);
	//DrawControlView(&ClientDC,crColorBorad,crColorBK);

	return;
}

//�滭�ؼ�
HBRUSH CSkinEditEx2::CtlColor(CDC * pDC, UINT nCtlColor)
{
	pDC->SetBkColor(RGB(250,0,250));
	pDC->SetTextColor(RGB(10,10,10));

	AfxMessageBox(TEXT("xxx"));

	static CBrush crBrush;
	crBrush.CreateSolidBrush(RGB(250,250,250));

	return crBrush;
}
