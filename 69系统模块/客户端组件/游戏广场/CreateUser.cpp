// CreateUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resource.h"
#include "CreateUser.h"
#include ".\createuser.h"


// CCreateUser �Ի���

IMPLEMENT_DYNAMIC(CCreateUser, CDialog)
CCreateUser::CCreateUser(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_CREATE_USER, pParent)
{
}

CCreateUser::~CCreateUser()
{
}

void CCreateUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDOK,m_btOk);
	DDX_Control(pDX,IDCANCEL,m_btCancel);
	DDX_Control(pDX,IDC_BT_CHECK,m_btCheck);
}


BEGIN_MESSAGE_MAP(CCreateUser, CDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCreateUser ��Ϣ�������

void CCreateUser::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnLButtonDown(nFlags, point);
}

void CCreateUser::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//ģ�����
	if (point.y<30)
	{
		//ģ�����
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

		return;
	}

	CDialog::OnMouseMove(nFlags, point);
}

BOOL CCreateUser::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_ImageBack.DrawImage(pDC,0,0);
	return TRUE;
}

BOOL CCreateUser::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("CREATE_BACK"));

	SetWindowPos(NULL,0,0,m_ImageBack.GetWidth(),m_ImageBack.GetHeight(),SWP_NOMOVE);

	return TRUE; 
}
