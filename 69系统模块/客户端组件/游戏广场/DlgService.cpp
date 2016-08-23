#include "StdAfx.h"
#include "DlgService.h"
#include "GlobalUnits.h"
#include ".\dlgservice.h"

//////////////////////////////////////////////////////////////////////////////////
//�궨��

//�ߴ綨��
#define ITEM_IMAGE_CX				20									//ͼ����
#define ITEM_IMAGE_CY				20									//ͼ��߶� 

//�ߴ綨��
#define SERVICE_BAR_CX				150									//���ƿ��
#define SERVICE_BAR_CY				375									//���Ƹ߶� 

//�ߴ綨��
#define BAR_BT_SPACE				3									//��ť���
#define BAR_BT_EXCURSION			5									//��ťƫ��

//�ؼ���ʶ
#define IDC_SERVICE_BAR				100									//�������

#define IDC_BT_INDIVIDUAL			101									//��������
#define IDC_BT_PASSWORD				102									//�޸�����

#define	SERVICE_PAGE_1				0									//
#define	SERVICE_PAGE_2				1									//
#define	SERVICE_PAGE_3				2									//

#define SERVICE_PAGE_COUNT			3								
//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgServiceBar, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDlgService, CDialog)
	//ON_BN_CLICKED(IDC_BT_INDIVIDUAL,ShowIndividualPage)
	//ON_BN_CLICKED(IDC_BT_PASSWORD,ShowPasswordPage)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL, OnTcnSelchangeLogonMode)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgServiceBar::CDlgServiceBar()
{
	//���Ϣ
	m_bHovering=false;
	m_wItemDown=INVALID_WORD;
	m_wItemHover=INVALID_WORD;
	m_wItemActive=INVALID_WORD;

	//������Ϣ
	m_SizeButton.SetSize(0,0);
	m_rcItemCreate.SetRect(0,0,0,0);

	//������Դ
	CPngImage ImageButton;
	ImageButton.LoadImage(AfxGetInstanceHandle(),TEXT("SERVICE_BAR_BT"));
	m_SizeButton.SetSize(ImageButton.GetWidth()/3,ImageButton.GetHeight());

	return;
}

//��������
CDlgServiceBar::~CDlgServiceBar()
{
}

//��Ϣ����
BOOL CDlgServiceBar::PreTranslateMessage(MSG * pMsg)
{
	//��Ϣ����
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//��������
bool CDlgServiceBar::SetItemCreateRect(CRect rcItemCreate)
{
	//���ñ���
	m_rcItemCreate=rcItemCreate;

	//�����ؼ�
	for (INT_PTR i=0;i<m_DlgServiceItemArray.GetCount();i++)
	{
		CWnd * pWnd=m_DlgServiceItemArray[i];
		if (pWnd->m_hWnd!=NULL) pWnd->SetWindowPos(NULL,rcItemCreate.left,rcItemCreate.top,rcItemCreate.Width(),rcItemCreate.Height(),SWP_NOZORDER);
	}

	return true;
}

//��������
bool CDlgServiceBar::InsertServiceItem(CDlgServiceItem * pDlgServiceItem)
{
	//���ñ���
	m_DlgServiceItemArray.Add(pDlgServiceItem);

	//���½���
	if (m_hWnd!=NULL)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return true;
}

//��������
bool CDlgServiceBar::SetActiveServiceItem(CDlgServiceItem * pDlgServiceItem)
{
	//Ч�����
	ASSERT(pDlgServiceItem!=NULL);
	if (pDlgServiceItem==NULL) return false;

	//��������
	CDlgServiceItem * pServiceActive=NULL;

	//�л��ж�
	if (m_wItemActive!=INVALID_WORD)
	{
		//��ȡ����
		ASSERT(m_wItemActive<m_DlgServiceItemArray.GetCount());
		pServiceActive=m_DlgServiceItemArray[m_wItemActive];

		//�л��ж�
		if (pServiceActive==pDlgServiceItem) return true;
	}

	//��������
	for (INT_PTR i=0;i<m_DlgServiceItemArray.GetCount();i++)
	{
		if (m_DlgServiceItemArray[i]==pDlgServiceItem)
		{
			//��������
			if (pDlgServiceItem->m_hWnd==NULL)
			{
				pDlgServiceItem->CreateServiceItem(GetParent(),m_rcItemCreate);
			}

			//���ñ���
			m_wItemActive=(WORD)i;

			//��ʾ����
			pDlgServiceItem->ShowWindow(SW_SHOW);
			pDlgServiceItem->SetFocus();

			//���ؾ���
			if (pServiceActive->GetSafeHwnd()!=NULL)
			{
				pServiceActive->ShowWindow(SW_HIDE);
			}

			//���½���
			RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);

			return true;
		}
	}

	return false;
}

//�����л�
WORD CDlgServiceBar::SwitchToButtonIndex(CPoint MousePoint)
{
	//����λ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//�߽��ж�
	if (MousePoint.x<((rcClient.Width()-m_SizeButton.cx)/2)) return INVALID_WORD;
	if (MousePoint.x>((rcClient.Width()+m_SizeButton.cx)/2)) return INVALID_WORD;

	//�����ж�
	for (WORD i=0;i<m_DlgServiceItemArray.GetCount();i++)
	{
		//λ�ü���
		CRect rcButton;
		rcButton.left=(rcClient.Width()-m_SizeButton.cx)/2;
		rcButton.right=(rcClient.Width()+m_SizeButton.cx)/2;
		rcButton.top=(m_SizeButton.cy+BAR_BT_SPACE)*i+BAR_BT_EXCURSION;
		rcButton.bottom=(m_SizeButton.cy+BAR_BT_SPACE)*i+m_SizeButton.cy+BAR_BT_EXCURSION;

		//�����ж�
		if (rcButton.PtInRect(MousePoint)) return i;
	}

	return INVALID_WORD;
}

//�ػ���Ϣ
VOID CDlgServiceBar::OnPaint()
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CBitImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//�����豸
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//�����豸
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//������Դ
	CPngImage ImageButton;
	CPngImage ImageBarLogo;
	CPngImage ImageBarImage;
	ImageButton.LoadImage(AfxGetInstanceHandle(),TEXT("SERVICE_BAR_BT"));
	ImageBarLogo.LoadImage(AfxGetInstanceHandle(),TEXT("SERVICE_BAR_LOGO"));
	ImageBarImage.LoadImage(AfxGetInstanceHandle(),TEXT("SERVICE_BAR_IMAGE"));

	//�滭����
	pBufferDC->FillSolidRect(&rcClient,RGB(223,236,246));
	ImageBarLogo.DrawImage(pBufferDC,rcClient.Width()-ImageBarLogo.GetWidth(),rcClient.Height()-ImageBarLogo.GetHeight());

	//�滭��ť
	for (INT i=0;i<m_DlgServiceItemArray.GetCount();i++)
	{
		//��ȡ����
		CDlgServiceItem * pDlgServiceItem=m_DlgServiceItemArray[i];
		LPCTSTR pszServiceName=pDlgServiceItem->GetServiceItemName();

		//���м���
		INT nXButtomPos=0;
		if ((m_wItemHover==i)&&(m_wItemDown!=i)) nXButtomPos=m_SizeButton.cx;
		if ((m_wItemActive==i)||(m_wItemDown==i)) nXButtomPos=m_SizeButton.cx*2;

		//�滭��ť
		INT nXDrawPos=(rcClient.Width()-m_SizeButton.cx)/2;
		INT nYDrawPos=(m_SizeButton.cy+BAR_BT_SPACE)*i+BAR_BT_EXCURSION;
		ImageButton.DrawImage(pBufferDC,nXDrawPos,nYDrawPos,m_SizeButton.cx,m_SizeButton.cy,nXButtomPos,0L);

		//�滭ͼ��
		INT nXImagePos=pDlgServiceItem->m_cbImageIndex*ITEM_IMAGE_CX;
		ImageBarImage.DrawImage(pBufferDC,nXDrawPos+32,nYDrawPos+2,ITEM_IMAGE_CX,ITEM_IMAGE_CY,nXImagePos,0);

		//������ɫ
		if ((m_wItemHover!=i)&&(m_wItemDown!=i)) pBufferDC->SetTextColor(RGB(0,0,0));
		if ((m_wItemHover==i)&&(m_wItemDown!=i)) pBufferDC->SetTextColor(RGB(3,112,218));
		if ((m_wItemActive==i)||(m_wItemDown==i)) pBufferDC->SetTextColor(RGB(255,255,255));

		//�滭�ַ�
		CRect rcItem(nXDrawPos+25,nYDrawPos+1,m_SizeButton.cx+nXDrawPos,m_SizeButton.cy+nYDrawPos);
		pBufferDC->DrawText(pszServiceName,lstrlen(pszServiceName),rcItem,DT_VCENTER|DT_CENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
	}

	//�滭����
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return;
}

//������Ϣ
INT CDlgServiceBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//���ñ���
	m_bHovering=false;
	m_wItemDown=INVALID_WORD;
	m_wItemHover=INVALID_WORD;
	m_wItemActive=INVALID_WORD;

	//������Ϣ
	m_rcItemCreate.SetRect(0,0,0,0);
	m_DlgServiceItemArray.RemoveAll();

	return 0;
}

//�����Ϣ
VOID CDlgServiceBar::OnMouseMove(UINT nFlags, CPoint Point)
{
	__super::OnMouseMove(nFlags, Point);

	//����λ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//λ�ü���
	WORD wServiceHover=SwitchToButtonIndex(Point);

	//��������
	if (wServiceHover!=m_wItemHover)
	{
		//���ñ���
		m_wItemHover=wServiceHover;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	//�����ж�
	if (m_bHovering==false)
	{
		//���ñ���
		m_bHovering=true;

		//��������
		TRACKMOUSEEVENT TrackMouseEvent;
		ZeroMemory(&TrackMouseEvent,sizeof(TrackMouseEvent));

		//ע����Ϣ
		TrackMouseEvent.hwndTrack=m_hWnd;
		TrackMouseEvent.dwFlags=TME_LEAVE;
		TrackMouseEvent.dwHoverTime=HOVER_DEFAULT;
		TrackMouseEvent.cbSize=sizeof(TrackMouseEvent);

		//ע���¼�
		_TrackMouseEvent(&TrackMouseEvent);
	}

	return;
}

//�����Ϣ
VOID CDlgServiceBar::OnLButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnLButtonUp(nFlags,Point);

	//��������
	if ((m_wItemHover!=INVALID_WORD)&&(m_wItemHover==m_wItemDown))
	{
		SetActiveServiceItem(m_DlgServiceItemArray[m_wItemHover]);
	}

	//������
	if (m_wItemDown!=INVALID_WORD)
	{
		//�ͷ����
		ReleaseCapture();

		//���ñ���
		m_wItemDown=INVALID_WORD;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//�����Ϣ
VOID CDlgServiceBar::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//���ý���
	SetFocus();

	//���´���
	if ((m_wItemHover!=INVALID_WORD)&&(m_wItemHover!=m_wItemActive))
	{
		//����˻�
		SetCapture();

		//���ñ���
		m_wItemDown=m_wItemHover;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//�����Ϣ
LRESULT CDlgServiceBar::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	if (m_bHovering==true)
	{
		//���ñ���
		m_bHovering=false;
		m_wItemHover=INVALID_WORD;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return 0;
}

//�����Ϣ
BOOL CDlgServiceBar::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//���ù��
	if (m_wItemHover!=INVALID_WORD)
	{
		SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_HAND_CUR)));
		return TRUE;
	}

	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgService::CDlgService() : CDialog(IDD_DLG_SERVICE)
{
	m_wInitPage=SERVICE_PAGE_1;

	return;
}

//��������
CDlgService::~CDlgService()
{
}


void CDlgService::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//ģ�����
	if (point.y<30)
	{
		//ģ�����
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

		return;
	}

	__super::OnLButtonDown(nFlags, point);
}

//��Ϣ����
BOOL CDlgService::PreTranslateMessage(MSG * pMsg)
{
	//��������
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//��������
BOOL CDlgService::OnInitDialog()
{
	__super::OnInitDialog();


	//���ñ���
	//SetWindowText(TEXT("��������"));

	m_ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("SERVICE_BACK"));

	SetWindowPos(NULL,0,0,m_ImageBack.GetWidth(),m_ImageBack.GetHeight(),SWP_NOMOVE);


	//���ÿؼ�
	m_TabControl.SetItemSize(CSize(150,25));
	m_TabControl.InsertItem(SERVICE_PAGE_1,TEXT("������Ϣ"));
	m_TabControl.InsertItem(SERVICE_PAGE_2,TEXT("�󶨻���"));
	m_TabControl.InsertItem(SERVICE_PAGE_3,TEXT("�޸�����"));

	//������ť
	CRect rcCreate(0,0,0,0);
	m_btClose.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDCANCEL);

	m_DlgServiceIndividual.Create(IDD_DLG_SERVICE_INDIVIDUAL,this);
	//m_DlgServicePassword.Create(IDD_DLG_SERVICE_PASSWORD,this);
	m_DlgServicePassword.Create(IDD_DLG_MODIFY_PASSWORD,this);

	m_DlgLockMachine.Create(IDD_DLG_LOCK_MACHINE,this);

	//����λ��
	CRect rcTabCtrl(14,36,m_ImageBack.GetWidth()-110,36+25);
	m_DlgLockMachine.SetWindowPos(NULL,14,63,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_DlgServiceIndividual.SetWindowPos(NULL,14,63,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_DlgServicePassword.SetWindowPos(NULL,14,63,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_TabControl.SetWindowPos(NULL,rcTabCtrl.left,rcTabCtrl.top,rcTabCtrl.Width(),rcTabCtrl.Height(),SWP_NOZORDER);

	m_TabControl.SetTabCtrlColor(RGB(196,219,231),RGB(131,192,219));

	if(m_wInitPage>=SERVICE_PAGE_COUNT) m_wInitPage=SERVICE_PAGE_1;

	switch(m_wInitPage)
	{
	case SERVICE_PAGE_1:	{	ShowIndividualPage(); break;	}
	case SERVICE_PAGE_2:	{	ShowLockMachine(); break;	}
	case SERVICE_PAGE_3:	{	ShowPasswordPage(); break;	}

	}

	//����ѡ��
	m_TabControl.SetCurSel(m_wInitPage);

	//���ð�ť
	HINSTANCE hInstance=AfxGetInstanceHandle();

	m_btClose.SetButtonImage(IDB_BT_SERVICE_CLOSE,hInstance,false,false);
	m_btClose.SetWindowPos(NULL,m_ImageBack.GetWidth()-40,3,0,0,SWP_NOZORDER|SWP_NOSIZE);


	//ShowIndividualPage();
	

	return TRUE;
}

//ȷ����Ϣ
VOID CDlgService::OnOK()
{
	return;
}

//�滭��Ϣ
VOID CDlgService::OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight)
{
//	pDC->Draw3dRect(8,63,457-8,257-63+40,RGB(210,210,210),RGB(210,210,210));
	//if(m_ImageBack.IsNull()!=true)	m_ImageBack.DrawImage(pDC,0,0);
}

VOID CDlgService::ShowIndividualPage()
{

	m_DlgServicePassword.ShowWindow(SW_HIDE);
	m_DlgLockMachine.ShowWindow(SW_HIDE);
	m_DlgServiceIndividual.ShowWindow(SW_SHOW);
}

VOID CDlgService::ShowPasswordPage()
{
	m_DlgServiceIndividual.ShowWindow(SW_HIDE);
	m_DlgLockMachine.ShowWindow(SW_HIDE);

	m_DlgServicePassword.ShowWindow(SW_SHOW);
}

VOID CDlgService::ShowLockMachine()
{
	m_DlgServiceIndividual.ShowWindow(SW_HIDE);
	m_DlgLockMachine.ShowWindow(SW_SHOW);

	m_DlgServicePassword.ShowWindow(SW_HIDE);
}
//////////////////////////////////////////////////////////////////////////

BOOL CDlgService::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(m_ImageBack.IsNull()!=true)	m_ImageBack.DrawImage(pDC,0,0);
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}

void CDlgService::DoDataExchange(CDataExchange* pDX)
{
	// TODO: �ڴ����ר�ô����/����û���

	DDX_Control(pDX, IDC_TAB_CONTROL, m_TabControl);

	CDialog::DoDataExchange(pDX);
}

//���͸ı�
VOID CDlgService::OnTcnSelchangeLogonMode(NMHDR * pNMHDR, LRESULT * pResult)
{
	switch (m_TabControl.GetCurSel())
	{
	case SERVICE_PAGE_1:		//������Ϣ
		{
			ShowIndividualPage();

			//����ѡ��
			m_TabControl.SetCurSel(SERVICE_PAGE_1);

			break;
		}
	case SERVICE_PAGE_2:		//�󶨻���
		{
			ShowLockMachine();
			//����ѡ��
			m_TabControl.SetCurSel(SERVICE_PAGE_2);

			break;
		}
	case SERVICE_PAGE_3:		//�޸�����
		{
			ShowPasswordPage();
			//����ѡ��
			m_TabControl.SetCurSel(SERVICE_PAGE_3);

			break;
		}
	default:
		{
			ASSERT(FALSE);
		}
	}

	return;
}
