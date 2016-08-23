#include "StdAfx.h"
#include "Winable.h"
#include "Resource.h"
#include "PasswordControlEx.h"


BEGIN_MESSAGE_MAP(CPasswordControlEx, CPasswordControl)
	ON_WM_SIZE()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CPasswordControlEx::CPasswordControlEx()
{

	return;
}

//��������
CPasswordControlEx::~CPasswordControlEx()
{
}

//�󶨺���
VOID CPasswordControlEx::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	////��ȡλ��
	//CRect rcClient;
	//CRect rcWindow;
	//GetClientRect(&rcClient);
	//GetWindowRect(&rcWindow);

	////������ť
	//CRect rcButton(0,0,0,0);
	//m_btKeyboard.Create(NULL,WS_CHILD|WS_VISIBLE,rcButton,this,IDC_BT_KEYBOARD);
	//m_btKeyboard.SetButtonImage(IDB_BT_KEYBOARD,GetModuleHandle(SHARE_CONTROL_DLL_NAME),false,false);

	////�����ؼ�
	//CRect rcEditCreate;
	//rcEditCreate.top=4;
	//rcEditCreate.left=4;
	//rcEditCreate.bottom=16;
	//rcEditCreate.right=rcClient.Width()-23;
	//m_edPassword.Create(WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_PASSWORD,rcEditCreate,this,IDC_ED_PASSWORD);

	////���ÿؼ�
	//m_edPassword.LimitText(LEN_PASSWORD-1);
	//m_edPassword.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(92,100,105));
	//m_edPassword.SetFont(&CSkinResourceManager::GetInstance()->GetDefaultFont());

	////�ƶ�����
	//SetWindowPos(NULL,0,0,rcWindow.Width(),24,SWP_NOMOVE|SWP_NOZORDER|SWP_NOCOPYBITS);
	//m_btKeyboard.SetWindowPos(NULL,rcClient.Width()-20,3,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);

	return;
}

//������Ϣ
VOID CPasswordControlEx::OnSize(UINT nType, INT cx, INT cy)
{

	//��ȡλ��
	CRect rcClient;
	CRect rcWindow;
	GetClientRect(&rcClient);

	CRect rcEditCreate;
	rcEditCreate.top=1;
	rcEditCreate.left=1;
	rcEditCreate.bottom=16;
	rcEditCreate.right=rcClient.Width()-23;
	m_edPassword.SetWindowPos(NULL,rcEditCreate.left,rcEditCreate.top,rcEditCreate.Width(),rcEditCreate.Height(),SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);
	m_btKeyboard.SetWindowPos(NULL,rcClient.Width()-20,1,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);


	__super::OnSize(nType, cx, cy);
}

//////////////////////////////////////////////////////////////////////////////////
