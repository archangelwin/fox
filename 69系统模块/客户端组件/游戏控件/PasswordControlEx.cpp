#include "StdAfx.h"
#include "Winable.h"
#include "Resource.h"
#include "PasswordControlEx.h"

//////////////////////////////////////////////////////////////////////////////////

//λ�ö���
#define ITEM_POS_S					3									//��ť���
#define ITEM_POS_X					0									//��ťλ��
#define ITEM_POS_Y					0									//��ťλ��

//�رհ�ť
#define POS_BUTTON_X				5									//��ťλ��
#define POS_BUTTON_Y				8									//��ťλ��

//��������
#define ROW_BACK					0									//�˸�ť
#define ROW_CLEAN					1									//�л���ť
#define ROW_CAPITAL					2									//��д��ť
#define ROW_CLOSE_KEY				3									//�رհ�ť
#define LINE_FUNCTION				4									//���ܰ�ť

//�ؼ���ʶ
#define IDC_BT_KEYBOARD				100									//���̰�ť
#define IDC_ED_PASSWORD				200									//����ؼ�

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPasswordKeyboard2, CDialog)
	ON_WM_NCPAINT()
	ON_WM_KILLFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CPasswordKeyboard2::CPasswordKeyboard2() : CDialog(IDD_PASSWORD_KEYBOARD2)
{
	//���ñ���
	m_nRandLine[0]=rand()%14;
	m_nRandLine[1]=rand()%14;
	m_nRandLine[2]=rand()%8;

	//����״̬
	//m_bCapsLockStatus=false;
	m_bCapsLockStatus=(GetKeyState(VK_CAPITAL)&0x0F)>0;

	m_pKeyBoardSink=NULL;

	//״̬����
	m_bMouseDown=false;
	m_wHoverRow=INVALID_WORD;
	m_wHoverLine=INVALID_WORD;

	//�����ַ�
	m_nItemCount[0]=14;
	lstrcpyn(m_szKeyboradChar[0][0],TEXT("abcd1234567890"),CountArray(m_szKeyboradChar[0][0]));
	lstrcpyn(m_szKeyboradChar[0][1],TEXT("ABCD1234567890"),CountArray(m_szKeyboradChar[0][1]));

	//�����ַ�
	m_nItemCount[1]=14;
	lstrcpyn(m_szKeyboradChar[1][0],TEXT("efghijklmnopqr"),CountArray(m_szKeyboradChar[1][0]));
	lstrcpyn(m_szKeyboradChar[1][1],TEXT("EFGHIJKLMNOPQR"),CountArray(m_szKeyboradChar[1][1]));

	//�����ַ�
	m_nItemCount[2]=8;
	lstrcpyn(m_szKeyboradChar[2][0],TEXT("stuvwxyz"),CountArray(m_szKeyboradChar[2][0]));
	lstrcpyn(m_szKeyboradChar[2][1],TEXT("STUVWXYZ"),CountArray(m_szKeyboradChar[2][1]));

	//��������
	HINSTANCE hResInstance=GetModuleHandle(SHARE_CONTROL_DLL_NAME);

	//������Դ
	CImage ImageItem1;
	CImage ImageItem2;

	ImageItem1.LoadFromResource(hResInstance,IDB_KEYBOARD2_ITEM1);
	ImageItem2.LoadFromResource(hResInstance,IDB_KEYBOARD2_ITEM2);
	

	//���ô�С
	m_SizeImageItem1.SetSize(ImageItem1.GetWidth()/3,ImageItem1.GetHeight());
	m_SizeImageItem2.SetSize(ImageItem2.GetWidth()/3,ImageItem2.GetHeight());
	
	m_SizeBackGround.SetSize(322,70);

	return;
}

//��������
CPasswordKeyboard2::~CPasswordKeyboard2()
{
}


//������Ӧ
VOID CPasswordKeyboard2::SetKeyBoardSink(IKeyBoardSink* pSink)
{
	m_pKeyBoardSink=pSink;
}

//��Ϣ����
BOOL CPasswordKeyboard2::PreTranslateMessage(MSG * pMsg)
{
	//��д����
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_CAPITAL))
	{
		//���ñ���
		bool bCapsLockStatus=m_bCapsLockStatus;
		m_bCapsLockStatus=(GetKeyState(VK_CAPITAL)&0x0F)>0;

		//���½���
		if (bCapsLockStatus!=m_bCapsLockStatus)
		{
			RedrawWindow(NULL,NULL,RDW_FRAME|RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASENOW);
		}

		return TRUE;
	}


	return __super::PreTranslateMessage(pMsg);
}

//��������
BOOL CPasswordKeyboard2::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	m_bMouseDown=false;
	m_wHoverRow=INVALID_WORD;
	m_wHoverLine=INVALID_WORD;

	//��ȡ״̬
	m_bCapsLockStatus=(GetKeyState(VK_CAPITAL)&0x0F)>0;

	//����λ��
	CRect rcWindow;
	rcWindow.SetRect(0,0,m_SizeBackGround.cx,m_SizeBackGround.cy);

	//�ƶ�����
	CalcWindowRect(&rcWindow,CWnd::adjustBorder);
	SetWindowPos(NULL,0,0,rcWindow.Width(),rcWindow.Height(),SWP_NOMOVE|SWP_NOZORDER);

	return FALSE;
}

//����λ��
VOID CPasswordKeyboard2::SetCurrentStation(CPoint MousePoint)
{
	//��������
	WORD wHoverRow=INVALID_WORD;
	WORD wHoverLine=INVALID_WORD;

	//�ַ���ť
	if ((MousePoint.x>=ITEM_POS_X)&&(MousePoint.y>=ITEM_POS_Y))
	{
		//��������
		if (((MousePoint.x-ITEM_POS_X)%(m_SizeImageItem1.cx+ITEM_POS_S))<=m_SizeImageItem1.cx)
		{
			wHoverRow=(WORD)((MousePoint.x-ITEM_POS_X)/(m_SizeImageItem1.cx+ITEM_POS_S));
		}

		//��������
		if (((MousePoint.y-ITEM_POS_Y)%(m_SizeImageItem1.cy+ITEM_POS_S))<=m_SizeImageItem1.cy)
		{
			wHoverLine=(WORD)((MousePoint.y-ITEM_POS_Y)/(m_SizeImageItem1.cy+ITEM_POS_S));
		}

		//��������
		if (wHoverLine>=CountArray(m_nItemCount)) wHoverLine=INVALID_WORD;
		if ((wHoverLine==INVALID_WORD)||(wHoverRow>=m_nItemCount[wHoverLine])) wHoverRow=INVALID_WORD;
	}

	//���ܰ�ť
	//if ((wHoverLine<2)&&(wHoverRow==INVALID_WORD))
	{
		INT nYDrawPos=23*2;
		INT nXDrawPos=ITEM_POS_X+(m_SizeImageItem1.cx+ITEM_POS_S)*8;

		//ԭ��λ��
		CPoint ButtonPoint[3];
		ButtonPoint[0].SetPoint(nXDrawPos,nYDrawPos);
		nXDrawPos+=((m_SizeImageItem1.cx+ITEM_POS_S)*2);
		ButtonPoint[1].SetPoint(nXDrawPos,nYDrawPos);
		nXDrawPos+=((m_SizeImageItem1.cx+ITEM_POS_S)*2);
		ButtonPoint[2].SetPoint(nXDrawPos,nYDrawPos);

		//��ť����
		CRect rcCapital(ButtonPoint[0],m_SizeImageItem2);
		CRect rcBack(ButtonPoint[1],m_SizeImageItem2);
		CRect rcClean(ButtonPoint[2],m_SizeImageItem2);

		//�˸�ť
		if (rcBack.PtInRect(MousePoint))
		{
			wHoverRow=ROW_BACK;
			wHoverLine=LINE_FUNCTION;
		}

		//�л���ť
		if (rcClean.PtInRect(MousePoint))
		{
			wHoverRow=ROW_CLEAN;
			wHoverLine=LINE_FUNCTION;
		}

		//��д��ť
		if (rcCapital.PtInRect(MousePoint))
		{
			wHoverRow=ROW_CAPITAL;
			wHoverLine=LINE_FUNCTION;
		}
	}

	//���ñ���
	m_wHoverRow=wHoverRow;
	m_wHoverLine=wHoverLine;

	return;
}

//�������
WORD CPasswordKeyboard2::GetVirualKeyCode(WORD wHoverLine, WORD wHoverRow)
{
	//���ܽ���
	if (wHoverLine==LINE_FUNCTION)
	{
		switch (wHoverRow)
		{
		case ROW_BACK: { return VK_BACK; }
		case ROW_CLEAN: { return VK_SHIFT; }
		case ROW_CAPITAL: { return VK_CAPITAL; }
		}
	}

	//�ַ�����
	if ((wHoverLine<CountArray(m_nItemCount))&&(wHoverRow<m_nItemCount[wHoverLine]))
	{
		//��������
		bool bLowerChar=true;
		//if (m_bShiftStatus==true) bLowerChar=!bLowerChar;
		if ((m_bCapsLockStatus==true)) bLowerChar=!bLowerChar;

		//��ȡ�ַ�
		INT nItemCount=m_nItemCount[wHoverLine];
		INT nCharRowIndex=(wHoverRow+m_nRandLine[wHoverLine])%nItemCount;
		TCHAR chChar=m_szKeyboradChar[wHoverLine][(bLowerChar==true)?0:1][nCharRowIndex];

		return chChar;
	}

	return 0;
}

//����滭
VOID CPasswordKeyboard2::OnNcPaint()
{
	__super::OnNcPaint();

	////��ȡλ��
	//CRect rcWindow;
	//GetWindowRect(&rcWindow);

	////�滭�߿�
	//CWindowDC WindowDC(this);
	//COLORREF crBoradFrame=CSkinEdit::m_SkinAttribute.m_crEnableBorad;
	//WindowDC.Draw3dRect(0,0,rcWindow.Width(),rcWindow.Height(),crBoradFrame,crBoradFrame);

	return;
}

//�滭����
BOOL CPasswordKeyboard2::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CDC BufferDC;
	CBitmap ImageBuffer;
	BufferDC.CreateCompatibleDC(pDC);
	ImageBuffer.CreateCompatibleBitmap(pDC,rcClient.Width(),rcClient.Height());

	//���û���
	BufferDC.SetBkMode(TRANSPARENT);
	BufferDC.SelectObject(&ImageBuffer);
	//BufferDC.SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//��������
	HINSTANCE hResInstance=GetModuleHandle(SHARE_CONTROL_DLL_NAME);
	CSkinRenderManager * pSkinRenderManager=CSkinRenderManager::GetInstance();

	//������Դ
	CImage ImageItem1;
	CImage ImageItem2;
	CImage ImageButton;
	
	ImageItem1.LoadFromResource(hResInstance,IDB_KEYBOARD2_ITEM1);
	ImageItem2.LoadFromResource(hResInstance,IDB_KEYBOARD2_ITEM2);

	//��Ⱦ��Դ
	pSkinRenderManager->RenderImage(ImageItem1);
	pSkinRenderManager->RenderImage(ImageItem2);

	BufferDC.FillSolidRect(&rcClient,RGB(255,255,255));

	//��������
	CFont DrawFont;
	DrawFont.CreateFont(14,0,0,0,600,0,0,0,134,3,2,1,2,TEXT("����"));
	BufferDC.SelectObject(DrawFont);

	//�ַ���ť
	for (INT nLine=0;nLine<CountArray(m_nItemCount);nLine++)
	{
		//�滭����
		for (INT nRow=0;nRow<m_nItemCount[nLine];nRow++)
		{
			//����λ��
			INT nXImageIndex=0;
			INT nCharItemIndex=(nRow+m_nRandLine[nLine])%m_nItemCount[nLine];
			if ((m_wHoverLine==nLine)&&(m_wHoverRow==nRow)) nXImageIndex=(m_bMouseDown==false)?1:2;

			//�滭����
			INT nXDrawPos=ITEM_POS_X+(m_SizeImageItem1.cx+ITEM_POS_S)*nRow;
			INT nYDrawPos=ITEM_POS_Y+(m_SizeImageItem1.cy+ITEM_POS_S)*nLine;
			ImageItem1.BitBlt(BufferDC,nXDrawPos,nYDrawPos,m_SizeImageItem1.cx,m_SizeImageItem1.cy,nXImageIndex*m_SizeImageItem1.cx,0);
			
			if(m_bCapsLockStatus!=true)
			{
				//�滭�ַ�
				BufferDC.SetTextColor(RGB(0,0,0));
				BufferDC.TextOut(nXDrawPos+4,nYDrawPos+4,&m_szKeyboradChar[nLine][0][nCharItemIndex],1);
			}
			else
			{
				//�滭�ַ�
				BufferDC.SetTextColor(RGB(0,0,0));
				BufferDC.TextOut(nXDrawPos+4,nYDrawPos+4,&m_szKeyboradChar[nLine][1][nCharItemIndex],1);
			}



			////�滭�ַ�
			//BufferDC.SetTextColor(RGB(0,0,0));
			//BufferDC.TextOut(nXDrawPos+15,nYDrawPos+3,&m_szKeyboradChar[nLine][1][nCharItemIndex],1);
		}
	}

	//��д��ť
	{
		//��Դλ��
		INT nXImageIndex=0;//(m_bCapsLockStatus==true)?1:0;
		if ((m_wHoverLine==LINE_FUNCTION)&&(m_wHoverRow==ROW_CAPITAL)) nXImageIndex=(m_bMouseDown==false)?1:2;

		//�滭����
		INT nYDrawPos=23*2;//+ITEM_POS_Y;
		INT nXDrawPos=ITEM_POS_X+(m_SizeImageItem1.cx+ITEM_POS_S)*8;
		ImageItem2.BitBlt(BufferDC,nXDrawPos,nYDrawPos,m_SizeImageItem2.cx,m_SizeImageItem2.cy,nXImageIndex*m_SizeImageItem2.cx,0);

		//��д��ť
		BufferDC.SetTextColor(RGB(0,0,0));
		BufferDC.TextOut(nXDrawPos+7,nYDrawPos+3,TEXT("��д"),2);
	}


	//�˸�ť
	{
		//��Դλ��
		INT nXImageIndex=0;
		if ((m_wHoverLine==LINE_FUNCTION)&&(m_wHoverRow==ROW_BACK)) nXImageIndex=(m_bMouseDown==false)?1:2;

		//�滭����
		INT nYDrawPos=23*2;//+ITEM_POS_Y;
		INT nXDrawPos=ITEM_POS_X+(m_SizeImageItem1.cx+ITEM_POS_S)*10;//m_nItemCount[0];
		ImageItem2.BitBlt(BufferDC,nXDrawPos,nYDrawPos,m_SizeImageItem2.cx,m_SizeImageItem2.cy,nXImageIndex*m_SizeImageItem2.cx,0);

		//�滭�ַ�
		BufferDC.SetTextColor(RGB(0,0,0));
		BufferDC.TextOut(nXDrawPos+7,nYDrawPos+3,TEXT("�˸�"),2);
	}

	//��հ�ť
	{
		//��Դλ��
		INT nXImageIndex=(m_bCapsLockStatus==true)?1:0;
		if ((m_wHoverLine==LINE_FUNCTION)&&(m_wHoverRow==ROW_CLEAN)) nXImageIndex=(m_bMouseDown==false)?1:2;

		//�滭����
		INT nYDrawPos=23*2;//+ITEM_POS_Y;
		INT nXDrawPos=ITEM_POS_X+(m_SizeImageItem1.cx+ITEM_POS_S)*12;
		ImageItem2.BitBlt(BufferDC,nXDrawPos,nYDrawPos,m_SizeImageItem2.cx,m_SizeImageItem2.cy,nXImageIndex*m_SizeImageItem2.cx,0);

		//��д��ť
		BufferDC.SetTextColor(RGB(0,0,0));
		BufferDC.TextOut(nXDrawPos+7,nYDrawPos+3,TEXT("���"),2);
	}

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),&BufferDC,0,0,SRCCOPY);

	//������Դ
	BufferDC.DeleteDC();
	ImageBuffer.DeleteObject();

	return TRUE;
}

//ʧȥ����
VOID CPasswordKeyboard2::OnKillFocus(CWnd * pNewWnd)
{
	__super::OnKillFocus(pNewWnd);

	//���ٴ���
	//DestroyWindow();

	return;
}

//�����Ϣ
VOID CPasswordKeyboard2::OnLButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnLButtonUp(nFlags,Point);

	//ȡ������
	if (m_bMouseDown==true)
	{
		//ȡ������
		ReleaseCapture();

		//���ñ���
		m_bMouseDown=false;

		//��ȡ���
		CPoint MousePoint;
		GetCursorPos(&MousePoint);
		ScreenToClient(&MousePoint);

		//����λ��
		WORD wHoverRow=m_wHoverRow;
		WORD wHoverLine=m_wHoverLine;
		SetCurrentStation(MousePoint);

		//�������
		if ((m_wHoverRow==wHoverRow)&&(m_wHoverLine==wHoverLine))
		{
			////�رհ�ť
			//if ((m_wHoverLine==LINE_FUNCTION)&&(m_wHoverRow==ROW_CLOSE_KEY))
			//{
			//	//���ý���
			//	CONTAINING_RECORD(this,CPasswordControl,m_PasswordKeyboard)->m_edPassword.SetFocus();

			//	//���ٴ���
			//	DestroyWindow();

			//	return;
			//}

			//�������
			WORD wViraulCode=GetVirualKeyCode(m_wHoverLine,m_wHoverRow);

			//��ť����
			switch (wViraulCode)
			{
			case VK_SHIFT:		//�л���ť
				{
					if(m_pKeyBoardSink!=NULL) m_pKeyBoardSink->OnKeyBoardClean();

					break;
				}
			case VK_CAPITAL:	//��д��ť
				{
					//��������
					INPUT Input[2];
					ZeroMemory(Input,sizeof(Input));

					//���ñ���
					Input[1].ki.dwFlags=KEYEVENTF_KEYUP;   
					Input[0].type=Input[1].type=INPUT_KEYBOARD;
					Input[0].ki.wVk=Input[1].ki.wVk=wViraulCode;

					//ģ������
					SendInput(CountArray(Input),Input,sizeof(INPUT));

					m_bCapsLockStatus=!m_bCapsLockStatus;

					//m_bCapsLockStatus=!m_bCapsLockStatus;
					//m_bCapsLockStatus=(GetKeyState(VK_CAPITAL)&0x0F)>0;

					break;
				}
			default:			//Ĭ�ϰ�ť
				{
					//������Ϣ
					//CDialog * pPasswordControl=CONTAINING_RECORD(this,CDialog,m_PasswordKeyboard2);
					//CWnd* pPasswordControl=GetParent();
					//if (pPasswordControl!=NULL) pPasswordControl->SendMessage(WM_CHAR,wViraulCode,0L);

					if(m_pKeyBoardSink!=NULL) m_pKeyBoardSink->OnKeyBoardChar(wViraulCode);

					break;
				}
			}
		}

		//���½���
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//�����Ϣ
VOID CPasswordKeyboard2::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//�����ť
	if ((m_wHoverLine!=INVALID_WORD)&&(m_wHoverRow!=INVALID_WORD))
	{
		//�������
		SetCapture();

		//���ñ���
		m_bMouseDown=true;

		//���½���
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//�����Ϣ
BOOL CPasswordKeyboard2::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//��ȡ���
	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(&MousePoint);

	//����λ��
	WORD wHoverRow=m_wHoverRow;
	WORD wHoverLine=m_wHoverLine;
	SetCurrentStation(MousePoint);

	//���½���
	if ((m_wHoverRow!=wHoverRow)||(m_wHoverLine!=wHoverLine))
	{
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	//���ù��
	if ((m_wHoverRow!=INVALID_WORD)&&(m_wHoverLine!=INVALID_WORD))
	{
		SetCursor(LoadCursor(GetModuleHandle(SHARE_CONTROL_DLL_NAME),MAKEINTRESOURCE(IDC_HAND_CUR)));
		return true;
	}

	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

//////////////////////////////////////////////////////////////////////////////////
