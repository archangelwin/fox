#include "StdAfx.h"
#include "GamePlaza.h"
#include "DlgLockMachine.h"
#include ".\dlglockmachine.h"

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgLockMachine, CDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgLockMachine::CDlgLockMachine() : CDialog(IDD_DLG_USER_RECHARGE)
{
	//���ñ���
	m_cbMachine=FALSE;
	ZeroMemory(m_szPassword,sizeof(m_szPassword));

	//�������
	m_MissionManager.InsertMissionItem(this);

	return;
}

//��������
CDlgLockMachine::~CDlgLockMachine()
{
}

//�ؼ���
VOID CDlgLockMachine::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�󶨿ؼ�
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);
}

//��������
BOOL CDlgLockMachine::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	//SetWindowText(TEXT("�󶨻�������"));

	m_PasswordControl.SetLimitText(LEN_PASSWORD-1);

	m_ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("SERVICE_PAGE_2"));
	SetWindowPos(NULL,0,0,m_ImageBack.GetWidth(),m_ImageBack.GetHeight(),SWP_NOMOVE);

	////��ȡ��С
	//CRect rcClient;
	//GetClientRect(&rcClient);

	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//���ð�ť
	m_cbMachine=(pGlobalUserData->cbMoorMachine==0)?TRUE:FALSE;
	m_btOk.SetWindowText(TEXT("")/*pGlobalUserData->cbMoorMachine==0)?TEXT("�󶨱���"):TEXT("�����")*/);
	m_btOk.SetButtonImage((pGlobalUserData->cbMoorMachine==0)?IDB_BT_LOCK:IDB_BT_UNLOCK,AfxGetInstanceHandle(),false,false);

	//CRect rcButton(0,0,0,0);
	//m_btOk.GetWindowRect(&rcButton);
	//m_btOk.MoveWindow(rcClient.Width()/2-rcButton.Width()-30,rcClient.Height()-32,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);
	//m_btCancel.MoveWindow(rcClient.Width()/2+30,rcClient.Height()-32,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);

	return TRUE;
}

//ȷ������
VOID CDlgLockMachine::OnOK()
{
	//��ȡ��Ϣ
	m_PasswordControl.GetWindowText(m_szPassword,CountArray(m_szPassword));

	//�����ж�
	if (m_szPassword[0]==0)
	{
		//������ʾ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���벻��Ϊ�գ������뱣�չ�������а󶨻��߽���󶨣�"),MB_ICONERROR);

		//���ý���
		m_PasswordControl.SetFocus();

		return;
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
bool CDlgLockMachine::OnEventMissionLink(INT nErrorCode)
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
		CMD_GP_ModifyMachine ModifyMachine;
		ZeroMemory(&ModifyMachine,sizeof(ModifyMachine));

		//��������
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

		//���ñ���
		ModifyMachine.cbBind=m_cbMachine;
		ModifyMachine.dwUserID=pGlobalUserData->dwUserID;

		//��������
		CWHService::GetMachineIDEx(ModifyMachine.szMachineID);
		CWHEncrypt::MD5Encrypt(m_szPassword,ModifyMachine.szPassword);

		//��������
		ASSERT(GetMissionManager()!=NULL);
		GetMissionManager()->SendData(MDM_GP_USER_SERVICE,SUB_GP_MODIFY_MACHINE,&ModifyMachine,sizeof(ModifyMachine));
	}

	return true;
}

//�ر��¼�
bool CDlgLockMachine::OnEventMissionShut(BYTE cbShutReason)
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
bool CDlgLockMachine::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
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

				if(GetParent()!=NULL)	GetParent()->PostMessage(WM_CLOSE,0,0);
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

BOOL CDlgLockMachine::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	m_ImageBack.DrawImage(pDC,0,0);

	return TRUE;
	//return __super::OnEraseBkgnd(pDC);
}
