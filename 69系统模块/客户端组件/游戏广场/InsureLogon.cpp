// InsureLogon.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "InsureLogon.h"
#include "resource.h"
#include "GlobalUnits.h"
// CInsureLogon �Ի���

IMPLEMENT_DYNAMIC(CInsureLogon, CDialog)
CInsureLogon::CInsureLogon(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_INSURE_LOGON, pParent)
{
	ZeroMemory(m_szInsurePassword,CountArray(m_szInsurePassword));

	//�������
	m_MissionManager.InsertMissionItem(this);

}

CInsureLogon::~CInsureLogon()
{
}

void CInsureLogon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_BT_CLOSE,m_btClose);
	DDX_Control(pDX,IDOK,m_btOk);
	DDX_Control(pDX,IDCANCEL,m_btCancle);
	DDX_Control(pDX,IDC_INSURE_PASSWORD1,m_edInsurePassword);
}


BEGIN_MESSAGE_MAP(CInsureLogon, CDialog)
ON_WM_LBUTTONDOWN()
ON_WM_ERASEBKGND()
ON_BN_CLICKED(IDC_BT_CLOSE,OnCancel)
ON_BN_CLICKED(IDOK,OnBnClickedOk)
END_MESSAGE_MAP()


// CInsureLogon ��Ϣ�������

BOOL CInsureLogon::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ImageBack.LoadImage(GetModuleHandle(SHARE_CONTROL_DLL_NAME),TEXT("INSURE_LOGON_BACK"));


	m_KeyBoard.Create(IDD_PASSWORD_KEYBOARD2,this);
	m_KeyBoard.SetKeyBoardSink(this);
	

	SetWindowPos(NULL,0,0,m_ImageBack.GetWidth(),m_ImageBack.GetHeight(),SWP_NOMOVE);

	m_btOk.SetButtonImage(IDB_BT_OK,AfxGetInstanceHandle(),false,false);
	m_btCancle.SetButtonImage(IDB_BT_CANCLE,AfxGetInstanceHandle(),false,false);
	m_btClose.SetButtonImage(IDB_BT_QUIT,AfxGetInstanceHandle(),false,false);

	m_btClose.SetWindowPos(NULL,435,4,0,0,SWP_NOSIZE);
	m_btOk.SetWindowPos(NULL,159,154,0,0,SWP_NOSIZE);
	m_btCancle.SetWindowPos(NULL,249,154,0,0,SWP_NOSIZE);

	m_KeyBoard.SetWindowPos(NULL,76,214,0,0,SWP_NOSIZE);

	GetDlgItem(IDC_INSURE_PASSWORD1)->SetFocus();

	return TRUE; 
}

VOID CInsureLogon::OnKeyBoardChar(WORD wChar)
{
	CWnd* pWnd=GetFocus();
	if(pWnd->GetSafeHwnd()==m_edInsurePassword.GetSafeHwnd())
	{
		m_edInsurePassword.SendMessage(WM_CHAR,wChar,0);
	}
}

VOID CInsureLogon::OnKeyBoardClean()
{
	CWnd* pWnd=GetFocus();
	if(pWnd->GetSafeHwnd()==m_edInsurePassword.GetSafeHwnd())
	{
		m_edInsurePassword.SetWindowText(TEXT(""));
	}
}

void CInsureLogon::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	//ģ�����
	if (point.y<30)
	{
		//ģ�����
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));

		return;
	}

	__super::OnLButtonDown(nFlags, point);

}

VOID CInsureLogon::OnBnClickedOk()
{
	ZeroMemory(m_szInsurePassword,CountArray(m_szInsurePassword));

	GetDlgItemText(IDC_INSURE_PASSWORD1,m_szInsurePassword,sizeof(m_szInsurePassword));
	//�����ж�
	if (m_szInsurePassword[0]==0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���չ�����������������룡"),MB_ICONERROR,0);

		GetDlgItem(IDC_INSURE_PASSWORD1)->SetFocus();

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

	m_btOk.EnableWindow(FALSE);
}

BOOL CInsureLogon::OnEraseBkgnd(CDC* pDC)
{
	m_ImageBack.DrawImage(pDC,0,0);

	return TRUE;
}

//�����¼�
bool CInsureLogon::OnEventMissionLink(INT nErrorCode)
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
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
		//��������
		CMD_GP_UserInsureLogon InsureLogon;
		ZeroMemory(&InsureLogon,sizeof(InsureLogon));

		//��������
		TCHAR szPassword[LEN_PASSWORD]=TEXT("");
		CWHEncrypt::MD5Encrypt(m_szInsurePassword,szPassword);

		//��������
		InsureLogon.dwUserID=pGlobalUserData->dwUserID;
		lstrcpyn(InsureLogon.szPassword,szPassword,CountArray(InsureLogon.szPassword));
		CWHService::GetMachineIDEx(InsureLogon.szMachineID);

		//��������
		ASSERT(GetMissionManager()!=NULL);
		GetMissionManager()->SendData(MDM_GP_USER_SERVICE,SUB_GP_USER_INSURE_LOGON,&InsureLogon,sizeof(InsureLogon));
	}

	return true;
}

//�ر��¼�
bool CInsureLogon::OnEventMissionShut(BYTE cbShutReason)
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
bool CInsureLogon::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
{
	//�����
	if (Command.wMainCmdID==MDM_GP_USER_SERVICE)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_USER_INSURE_LOGON_SUCCESS:	//��½�ɹ�
			{

				//�ر�����
				CMissionManager * pMissionManager=GetMissionManager();
				if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);

				//���ÿؼ�
				m_btOk.EnableWindow(TRUE);

				//��������
				TCHAR szPassword[LEN_PASSWORD]=TEXT("");
				CWHEncrypt::MD5Encrypt(m_szInsurePassword,szPassword);
				lstrcpy(CGlobalUnits::GetInstance()->m_szInsurePassword,szPassword);

				OnOK();

				return true; 
			}
		case SUB_GP_USER_INSURE_LOGON_FAILURE:	//����ʧ��
			{
				//Ч�����
				CMD_GP_UserInsureLogonFailure * pUserInsureLogonFailure=(CMD_GP_UserInsureLogonFailure *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_UserInsureLogonFailure)-sizeof(pUserInsureLogonFailure->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_UserInsureLogonFailure)-sizeof(pUserInsureLogonFailure->szDescribeString))) return false;

				//�ر�����
				CMissionManager * pMissionManager=GetMissionManager();
				if (pMissionManager!=NULL) pMissionManager->ConcludeMissionItem(this,false);

				if (pUserInsureLogonFailure->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pUserInsureLogonFailure->szDescribeString,MB_ICONERROR,60);					
				}

				//���ÿؼ�
				m_btOk.EnableWindow(TRUE);

				return true;
			}
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
				GetDlgItem(IDC_INSURE_PASSWORD1)->SetFocus();

				return true;
			}
		}
	}

	//�������
	ASSERT(FALSE);

	return true;
}
