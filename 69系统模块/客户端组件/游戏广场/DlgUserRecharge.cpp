#include "StdAfx.h"
#include "GamePlaza.h"
#include "DlgUserRecharge.h"


//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgUserRecharge, CDialog)
	ON_WM_ERASEBKGND()
	//ϵͳ��Ϣ
	
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////
//Բ�Ǵ�С
#define ROUND_CX					1									//Բ�ǿ��
#define ROUND_CY					1									//Բ�Ǹ߶�
//��Ļλ��
#define LAYERED_SIZE				5									//�ֲ��С
#define CAPTION_SIZE				60									//�����С
//���캯��
CDlgUserRecharge::CDlgUserRecharge() : CDialog(IDD_DLG_USER_RECHARGE)
{
	//���ñ���
	m_cbMachine=FALSE;
	
	ZeroMemory(m_szID,sizeof(m_szID));
	ZeroMemory(m_szCard,sizeof(m_szCard));
    ZeroMemory(m_szPassword,sizeof(m_szPassword));
	
	//�������
	m_MissionManager.InsertMissionItem(this);

	return;
}

//��������
CDlgUserRecharge::~CDlgUserRecharge()
{
}

//�ؼ���
VOID CDlgUserRecharge::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�󶨿ؼ�
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_ACCOUNTS, m_IDControl);
	DDX_Control(pDX, IDC_CARD_NUMBER, m_CardControl);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);
}

//��������
BOOL CDlgUserRecharge::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	//SetWindowText(TEXT("�󶨻�������"));

	m_PasswordControl.SetLimitText(LEN_PASSWORD-1);

	m_ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("BT_USER_INFO_CHONGZHI"));
	

	
     //���ô�С
	CSize SizeWindow(m_ImageBack.GetWidth(),m_ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);
	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	TCHAR szControl[128]=TEXT("");
	_sntprintf(szControl,CountArray(szControl),TEXT("%d"),pGlobalUserData->dwGameID);
    SetDlgItemText(IDC_ACCOUNTS,szControl);
	//���ð�ť
	//m_cbMachine=(pGlobalUserData->cbMoorMachine==0)?TRUE:FALSE;
	//m_btOk.SetWindowText(TEXT("")/*pGlobalUserData->cbMoorMachine==0)?TEXT("�󶨱���"):TEXT("�����")*/);
	//m_btOk.SetButtonImage((pGlobalUserData->cbMoorMachine==0)?IDB_BT_LOCK:IDB_BT_UNLOCK,AfxGetInstanceHandle(),false,false);
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btOk.SetButtonImage(IDB_BT_OK,hInstance,false,false);
    m_btCancel.SetButtonImage(IDB_BT_SERVICE_CLOSE,hInstance,false,false);
	//�رհ�ť
	CRect rcCancel;
	m_btCancel.GetWindowRect(&rcCancel);
	m_btCancel.SetWindowPos(NULL,SizeWindow.cx-rcCancel.Width()-15,4,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOREDRAW);
	m_btOk.SetWindowPos(NULL,210,240,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOREDRAW);
	//���д���
	CenterWindow(this);

	//��ȡ����
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//����λ��
	CRect rcUnLayered;
	rcUnLayered.top=LAYERED_SIZE;
	rcUnLayered.left=LAYERED_SIZE;
	rcUnLayered.right=rcWindow.Width()-LAYERED_SIZE;
	rcUnLayered.bottom=rcWindow.Height()-LAYERED_SIZE;

	//��������
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(LAYERED_SIZE,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE+1,SizeWindow.cy-LAYERED_SIZE+1,ROUND_CX,ROUND_CY);

	//��������
	SetWindowRgn(RgnWindow,FALSE);

	//�ֲ㴰��
	m_SkinLayered.CreateLayered(this,rcWindow);
	m_SkinLayered.InitLayeredArea(m_ImageBack,255,rcUnLayered,CPoint(ROUND_CX,ROUND_CY),false);
	return TRUE;
}

//ȷ������
VOID CDlgUserRecharge::OnOK()
{
	//��ȡ��Ϣ
	m_PasswordControl.GetWindowText(m_szPassword,CountArray(m_szPassword));
    m_IDControl.GetWindowText(m_szID,CountArray(m_szID));
	m_CardControl.GetWindowText(m_szCard,CountArray(m_szCard));
	//�����ж�
	if (m_szPassword[0]==0)
	{
		//������ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("��ֵ�����벻��Ϊ��"),MB_ICONERROR);

		//���ý���
		m_PasswordControl.SetFocus();

		return;
	}
    if(m_szID[0]==0)
	{
      //������ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�������ֵ��ID"),MB_ICONERROR);
		//���ý���
		m_IDControl.SetFocus();
	}
	if(m_szCard[0]==0)
	{
         //������ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�������ֵ�Ŀ���"),MB_ICONERROR);
		//���ý���
		m_CardControl.SetFocus();
	}
	//��������
	ASSERT(GetMissionManager()!=NULL);
	CMissionManager * pMissionManager=GetMissionManager();

	//��������
	if (pMissionManager->AvtiveMissionItem(this,false)==false)
	{
		//������ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("����������ʧ�ܣ��������������Լ���������״����"),MB_ICONERROR);

		return;
	}

	//���ÿؼ�
	m_btOk.EnableWindow(FALSE);

	return;
}

//�����¼�
bool CDlgUserRecharge::OnEventMissionLink(INT nErrorCode)
{
	//������
	if (nErrorCode!=0L)
	{
		//���ÿؼ�
		m_btOk.EnableWindow(TRUE);

		//��ʾ��ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���������еķ��������޷��ɹ����ӷ���������������վά�����棡"),MB_ICONERROR);
	}
	else
	{
		//��������
		CMD_GP_UserRecharge UserRecharge;
		ZeroMemory(&UserRecharge,sizeof(UserRecharge));

		//��������
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

		//���ñ���
		//UserRecharge.szID=m_szID;
		//UserRecharge.szCard=m_szCard;
        lstrcpyn(UserRecharge.szID,m_szID,CountArray(UserRecharge.szID));
		lstrcpyn(UserRecharge.szCard,m_szCard,CountArray(UserRecharge.szCard));
		//��������
		//CWHService::GetMachineIDEx(ModifyMachine.szMachineID);
		CWHEncrypt::MD5Encrypt(m_szPassword,UserRecharge.szPassword);
        
		//��������
		ASSERT(GetMissionManager()!=NULL);
		GetMissionManager()->SendData(MDM_GP_USER_SERVICE,SUB_GP_USER_RECHARGE,&UserRecharge,sizeof(UserRecharge));
	}

	return true;
}

//�ر��¼�
bool CDlgUserRecharge::OnEventMissionShut(BYTE cbShutReason)
{
	//�رմ���
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		//��������
		CMissionManager * pMissionManager=GetMissionManager();
		if (pMissionManager->AvtiveMissionItem(this,true)==true) return true;

		//���ÿؼ�
		m_btOk.EnableWindow(TRUE);

		//��ʾ��ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���ڵ�ǰ����������æ���ʺŰ󶨲�������ʧ�ܣ����Ժ������ԣ�"),MB_ICONERROR);
	}

	return true;
}

//��ȡ�¼�
bool CDlgUserRecharge::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
{
	//�����
	if (Command.wMainCmdID==MDM_GP_USER_SERVICE)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_OPERATE_FAILURE:	//����ʧ��
			{
				//Ч�����
				CMD_GP_OperateFailure * pOperateFailure=(CMD_GP_OperateFailure *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString))) return false;

				//�ر�����
				CMissionManager * pMissionManager=GetMissionManager();
				if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);

				//��ʾ��Ϣ
				if (pOperateFailure->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pOperateFailure->szDescribeString,MB_ICONERROR,60);
				}

				//���ÿؼ�
				m_btOk.EnableWindow(TRUE);
				m_PasswordControl.SetFocus();

				return true;
			}
		case SUB_GP_OPERATE_SUCCESS:	//�����ɹ�
			{
				//��������
				CMD_GP_OperateSuccess * pOperateSuccess=(CMD_GP_OperateSuccess *)pData;

				//Ч������
				ASSERT(wDataSize>=(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString))) return false;

				//�ر�����
				CMissionManager * pMissionManager=GetMissionManager();
				if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);

				//��������
				CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
				tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

				//���ñ���
				pGlobalUserData->cbMoorMachine=(m_cbMachine==TRUE)?TRUE:FALSE;

				//m_btOk.SetButtonImage((pGlobalUserData->cbMoorMachine==0)?IDB_BT_LOCK:IDB_BT_UNLOCK,AfxGetInstanceHandle(),false,false);

				//�����¼�
				CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
				if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_MOOR_MACHINE,0L);

				//��ʾ��Ϣ
				if (pOperateSuccess->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pOperateSuccess->szDescribeString,MB_ICONINFORMATION,60);
				}
				
				m_btOk.EnableWindow(TRUE);

				//if(GetParent()!=NULL)	GetParent()->PostMessage(WM_CLOSE,0,0);
				//�رմ���
			//	__super::OnCancel();

				return true;
			}
		}
	}

	//�������
	ASSERT(FALSE);

	return true;
}

//////////////////////////////////////////////////////////////////////////////////
//��ʾ��Ϣ
VOID CDlgUserRecharge::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	//��ʾ�ֲ�
	if (m_SkinLayered.m_hWnd!=NULL)
	{
		m_SkinLayered.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	}

	return;
}

//�����Ϣ
VOID CDlgUserRecharge::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//ģ�����
	if (Point.y<=CAPTION_SIZE)
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//λ�øı�
VOID CDlgUserRecharge::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	//�ƶ��ֲ�
	if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}

	return;
}
BOOL CDlgUserRecharge::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_ImageBack.DrawImage(pDC,0,0);

	return TRUE;
	//return __super::OnEraseBkgnd(pDC);
}
