#include "StdAfx.h"
#include "GamePlaza.h"
#include "DlgRegister.h"
#include "MissionLogon.h"

//////////////////////////////////////////////////////////////////////////////////

//Բ�Ǵ�С
#define ROUND_CX					7									//Բ�ǿ��
#define ROUND_CY					7									//Բ�Ǹ߶�

//��Ļλ��
#define LAYERED_SIZE				5									//�ֲ��С
#define CAPTION_SIZE				35									//�����С

#define FLAG_HINT					0
#define FLAG_ERROR					1
#define FLAG_RIGHT					2

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgRegister, CDialog)

	//ϵͳ��Ϣ
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()

	//��ť��Ϣ
	ON_BN_CLICKED(IDC_QUIT, OnBnClickedQuit)
//	ON_BN_CLICKED(IDC_SELECT_FACE, OnBnClickedSelectFace)

	ON_BN_CLICKED(IDC_GENDER_FEMALE,OnBnSelectGender)
	ON_BN_CLICKED(IDC_GENDER_MANKIND,OnBnSelectGender)

	//������Ϣ
	ON_EN_CHANGE(IDC_LOGON_PASS1, OnEnChangeLogonPass)
	//ON_EN_CHANGE(IDC_INSURE_PASS1, OnEnChangeInsurePass)
	ON_STN_CLICKED(IDC_CHANGE_VALIDATE, OnBnClickedChangeValidate)

	ON_EN_CHANGE(IDC_ACCOUNTS, OnEnChangeAccounts)
	ON_EN_CHANGE(IDC_NICKNAME, OnEnChangeNickname)
	ON_EN_CHANGE(IDC_LOGON_PASS2, OnEnChangeLogonPass2)
	//ON_EN_CHANGE(IDC_INSURE_PASS2, OnEnChangeInsurePass2)
	ON_EN_CHANGE(IDC_COMPELLATION, OnEnChangeCompellation)
	ON_EN_CHANGE(IDC_PASSPORT_ID, OnEnChangePassportId)
	ON_EN_CHANGE(IDC_SPREADER, OnEnChangeSpreader)
    //ON_EN_CHANGE(IDC_QQ, OnEnChangeQQ)
	ON_EN_KILLFOCUS(IDC_ACCOUNTS, OnEnKillfocusAccount)
	ON_EN_KILLFOCUS(IDC_NICKNAME, OnEnKillfocusNickname)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgRegister::CDlgRegister() : CDialog(IDD_DLG_REGISTER)
{
	//���ñ���
	m_wFaceID=0;
	m_cbGender=0;
	m_szAccounts[0]=0;
	m_szNickName[0]=0;
	m_szSpreader[0]=0;
	m_szLogonPass[0]=0;
	m_szInsurePass[0]=0;
	m_szPassPortID[0]=0;
	m_szCompellation[0]=0;
    m_szQQ[0]=0;
	//���ñ���
	m_cbRemPassword=FALSE;
	m_cbLogonPassLevel=PASSWORD_LEVEL_0;
	m_cbInsurePassLevel=PASSWORD_LEVEL_0;

	//������ˢ
	m_brBrush.CreateSolidBrush(RGB(255,255,255));
	m_strTipString[0]=TEXT("�˺ų��Ȳ�������6λ�ַ�");//�˺ų��Ȳ�������6λ�ַ�
	m_strTipString[1]=TEXT("�ǳƳ��Ȳ�������6λ�ַ�");//�ǳƳ��Ȳ�������6λ�ַ�
	m_strTipString[2]=TEXT("���볤�Ȳ�������6λ�ַ�");//���볤�Ȳ�������6λ�ַ�
	m_strTipString[3]=TEXT("���볤�Ȳ�������6λ�ַ�");//���볤�Ȳ�������6λ�ַ�
	//m_strTipString[4]=TEXT("");//���볤�Ȳ�������6λ�ַ�
	//m_strTipString[5]=TEXT("");//���볤�Ȳ�������6λ�ַ�
	//m_strTipString[6]=TEXT("�ֻ�����(�һ��˺ź�������Чƾ֤)");//�ֻ�����(�һ��˺ź�������Чƾ֤)
	//m_strTipString[7]=TEXT("�ɲ���д");//�ɲ���д
	//m_strTipString[8]=TEXT("���֤��(�һ��˺ź�������Чƾ֤");//���֤��(�һ��˺ź�������Чƾ֤

	m_ptTipString[0].SetPoint(175,80+13);
	m_ptTipString[1].SetPoint(175,140+5);
	m_ptTipString[2].SetPoint(178,225+5);
	m_ptTipString[3].SetPoint(178,275+5);
	//m_ptTipString[4].SetPoint(160,323+5);
	//m_ptTipString[5].SetPoint(160,349+5);
	//m_ptTipString[6].SetPoint(160,315+5);
	//m_ptTipString[7].SetPoint(160,361+5);
	//m_ptTipString[8].SetPoint(160,408+5);

	for (int i=0; i<9; i++)
	{
		m_cbFlag[i]=FLAG_HINT;
	}

	return;
}

//��������
CDlgRegister::~CDlgRegister()
{
}

//�ؼ���
VOID CDlgRegister::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//��ť�ؼ�
	DDX_Control(pDX, IDOK, m_btEnter);
	DDX_Control(pDX, IDC_QUIT, m_btQuit);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	//DDX_Control(pDX, IDC_SELECT_FACE, m_btSelectFace);

	//�༭�ؼ�
	DDX_Control(pDX, IDC_ACCOUNTS, m_edAccounts);
	DDX_Control(pDX, IDC_SPREADER, m_edSpreader);
	DDX_Control(pDX, IDC_NICKNAME, m_edNickName);
	DDX_Control(pDX, IDC_PASSPORT_ID, m_edPassPortID);
	DDX_Control(pDX, IDC_LOGON_PASS1, m_edLogonPass1);
	DDX_Control(pDX, IDC_LOGON_PASS2, m_edLogonPass2);
	DDX_Control(pDX, IDC_QQ, m_edQQ);
	//DDX_Control(pDX, IDC_INSURE_PASS1, m_edInsurePass1);
	//DDX_Control(pDX, IDC_INSURE_PASS2, m_edInsurePass2);
	DDX_Control(pDX, IDC_COMPELLATION, m_edCompellation);
	DDX_Control(pDX, IDC_VALIDATE_CODE, m_edValidateCode);

	//�����ؼ�
	//DDX_Control(pDX, IDC_FACE_ITEM, m_FaceItemView);
	DDX_Control(pDX, IDC_CHANGE_VALIDATE, m_ChangeValidate);
	DDX_Control(pDX, IDC_VALIDATE_CODE_WND, m_WndValidateCode);
}

//��Ϣ����
BOOL CDlgRegister::PreTranslateMessage(MSG * pMsg)
{
	//��������
	if (pMsg->message==WM_CHAR)
	{
		//�������
		if ((m_edLogonPass1.m_hWnd==pMsg->hwnd)&&(pMsg->wParam>=0x80)) return TRUE;
		if ((m_edLogonPass2.m_hWnd==pMsg->hwnd)&&(pMsg->wParam>=0x80)) return TRUE;
		if ((m_edInsurePass1.m_hWnd==pMsg->hwnd)&&(pMsg->wParam>=0x80)) return TRUE;
		if ((m_edInsurePass2.m_hWnd==pMsg->hwnd)&&(pMsg->wParam>=0x80)) return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//���ú���
BOOL CDlgRegister::OnInitDialog()
{
	__super::OnInitDialog();

	//���ô���
	ModifyStyle(0, WS_MINIMIZEBOX);
	ModifyStyle(0, WS_MAXIMIZEBOX);

	//���ñ���
	SetWindowText(TEXT("�û�ע��"));

	//��������
	ASSERT(CFaceItemControl::GetInstance()!=NULL);
	IFaceItemControl * pIFaceItemControl=CFaceItemControl::GetInstance();

	//������Դ
	CPngImage ImageBack;
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_REGISTER_BACK"));

	//���ô�С
	CSize SizeWindow(ImageBack.GetWidth(),ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	//��֤�ؼ�
	m_WndValidateCode.RandValidateCode();
	m_edValidateCode.LimitText(VALIDATE_COUNT);
	m_ChangeValidate.SetBackGroundColor(RGB(215,223,238));

	//��������
	m_edAccounts.LimitText(LEN_ACCOUNTS-1);
	m_edNickName.LimitText(LEN_NICKNAME-1);
	m_edSpreader.LimitText(LEN_MOBILE_PHONE-1);
	m_edLogonPass1.LimitText(LEN_PASSWORD-1);
	m_edLogonPass2.LimitText(LEN_PASSWORD-1);
	m_edInsurePass1.LimitText(LEN_PASSWORD-1);
	m_edInsurePass2.LimitText(LEN_PASSWORD-1);
	m_edPassPortID.LimitText(LEN_PASS_PORT_ID-1);
	m_edCompellation.LimitText(LEN_COMPELLATION-1);
    m_edQQ.LimitText(LEN_QQ-1);
	m_edAccounts.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edNickName.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edSpreader.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edLogonPass1.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edLogonPass2.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edInsurePass1.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edInsurePass2.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edPassPortID.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edCompellation.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edValidateCode.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
    m_edQQ.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));

	//���ð�ť
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btCancel.SetButtonImage(IDB_BT_LOGON_QUIT,hInstance,false,false);
	m_btQuit.SetButtonImage(IDB_BT_REGISTER,TEXT("BT_REGISTER_QUIT"),hInstance,false,false);
	m_btEnter.SetButtonImage(IDB_BT_REGISTER,TEXT("BT_REGISTER_ENTER"),hInstance,false,false);

	//��ȡͷ��
	m_wFaceID=rand()%pIFaceItemControl->GetFaceCount();

	//����ͷ��
	m_FaceItemView.SetSystemFace(m_wFaceID);

	//�����Ա�
	((CButton *)GetDlgItem(IDC_GENDER_MANKIND))->SetCheck(BST_CHECKED);

	//GetDlgItem(IDC_STATIC_RIMAGE)->SetWindowPos(NULL,1,40,492,74,SWP_NOZORDER);

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
	//RgnWindow.CreateRoundRectRgn(LAYERED_SIZE,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE+1,SizeWindow.cy-LAYERED_SIZE+1,ROUND_CX,ROUND_CY);
	RgnWindow.CreateRoundRectRgn(0,0,SizeWindow.cx+1,SizeWindow.cy+1,6,6);

	//��������
	SetWindowRgn(RgnWindow,FALSE);

	////�ֲ㴰��
	//m_SkinLayered.CreateLayered(this,rcWindow);
	//m_SkinLayered.InitLayeredArea(ImageBack,255,rcUnLayered,CPoint(ROUND_CX,ROUND_CY),false);

	////��ȡĿ¼
	//TCHAR szPath[MAX_PATH]=TEXT("");
	//CWHService::GetWorkDirectory(szPath, sizeof(szPath));

	////��ȡ����
	//TCHAR szFileName[MAX_PATH]=TEXT("");
	//_sntprintf(szFileName,CountArray(szFileName),TEXT("%s\\Spreader.ini"),szPath);

	////��ȡ�Ƽ���
	//TCHAR szSpreader[LEN_ACCOUNTS]=TEXT("");
	//GetPrivateProfileString(TEXT("SpreaderInfo"),TEXT("SpreaderName"),TEXT(""),szSpreader,CountArray(szSpreader),szFileName);

	////��������
	//if (szSpreader[0]!=0)
	//{
	//	SetDlgItemText(IDC_SPREADER,szSpreader);
	//	((CEdit *)GetDlgItem(IDC_SPREADER))->SetReadOnly();
	//}

	return FALSE;
}

//ȷ������
VOID CDlgRegister::OnOK()
{
	//��ȡ��Ϣ
	if (GetInformation()==false) return;

	//���ش���
	ShowWindow(SW_HIDE);

	//ִ��ע��
	CMissionLogon * pMissionLogon=CMissionLogon::GetInstance();
	if (pMissionLogon!=NULL) pMissionLogon->PerformLogonMission(m_cbRemPassword==TRUE);

	return;
}

//ȡ������
VOID CDlgRegister::OnCancel()
{
	//���ش���
	ShowWindow(SW_HIDE);

	//��ʾ��¼
	ASSERT(CMissionLogon::GetInstance()!=NULL);
	if (CMissionLogon::GetInstance()!=NULL) CMissionLogon::GetInstance()->ShowLogon();
	
	return;
}

//���͵�¼
WORD CDlgRegister::ConstructRegisterPacket(BYTE cbBuffer[], WORD wBufferSize, BYTE cbValidateFlags)
{
	//��������
	TCHAR szLogonPass[LEN_MD5];
	TCHAR szInsurePass[LEN_MD5];
	CWHEncrypt::MD5Encrypt(m_szLogonPass,szLogonPass);
	CWHEncrypt::MD5Encrypt(m_szInsurePass,szInsurePass);

	//��������
	CMD_GP_RegisterAccounts * pRegisterAccounts=(CMD_GP_RegisterAccounts *)cbBuffer;

	//ϵͳ��Ϣ
	pRegisterAccounts->dwPlazaVersion=VERSION_PLAZA;

	//������ʶ
	CWHService::GetMachineIDEx(pRegisterAccounts->szMachineID);

	//������Ϣ
	pRegisterAccounts->wFaceID=m_wFaceID;
	pRegisterAccounts->cbGender=m_cbGender;
	lstrcpyn(pRegisterAccounts->szAccounts,m_szAccounts,CountArray(pRegisterAccounts->szAccounts));
	lstrcpyn(pRegisterAccounts->szNickName,m_szNickName,CountArray(pRegisterAccounts->szNickName));
	lstrcpyn(pRegisterAccounts->szSpreader,m_szSpreader,CountArray(pRegisterAccounts->szSpreader));
	lstrcpyn(pRegisterAccounts->szLogonPass,szLogonPass,CountArray(pRegisterAccounts->szLogonPass));
	lstrcpyn(pRegisterAccounts->szInsurePass,szInsurePass,CountArray(pRegisterAccounts->szInsurePass));
	lstrcpyn(pRegisterAccounts->szPassPortID,m_szPassPortID,CountArray(pRegisterAccounts->szPassPortID));
	lstrcpyn(pRegisterAccounts->szCompellation,m_szCompellation,CountArray(pRegisterAccounts->szCompellation));
	lstrcpyn(pRegisterAccounts->szQQ,m_szQQ,CountArray(pRegisterAccounts->szQQ));
	pRegisterAccounts->cbValidateFlags=cbValidateFlags;

	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	lstrcpyn(pGlobalUserData->szPassword,pRegisterAccounts->szLogonPass,CountArray(pGlobalUserData->szPassword));

	//��������
	return sizeof(CMD_GP_RegisterAccounts);
}

//�����������
WORD CDlgRegister::ConstructCheckPacket(BYTE cbBuffer[], WORD wBufferSize, BYTE cbCheckFlags)
{
	if(cbCheckFlags==CHECK_ACCOUNT)
	{
		CMD_GP_RegisterCheck* pRegisterCheck = (CMD_GP_RegisterCheck*)cbBuffer;
		lstrcpyn(pRegisterCheck->szCheckInfo,m_szAccounts,CountArray(pRegisterCheck->szCheckInfo));
		pRegisterCheck->cbCheckType = cbCheckFlags;
		pRegisterCheck->cbResult = 0;
	} 
	else if (cbCheckFlags==CHECK_NICK)
	{
		CMD_GP_RegisterCheck* pRegisterCheck = (CMD_GP_RegisterCheck*)cbBuffer;
		lstrcpyn(pRegisterCheck->szCheckInfo,m_szNickName,CountArray(pRegisterCheck->szCheckInfo));
		pRegisterCheck->cbCheckType = cbCheckFlags;
		pRegisterCheck->cbResult = 0;
	}

	return sizeof(CMD_GP_RegisterCheck);
}


//��ȡ��Ϣ
bool CDlgRegister::GetInformation()
{
	//��֤��Ϣ
	TCHAR szValidateCode[VALIDATE_COUNT+1]=TEXT("");
	GetDlgItemText(IDC_VALIDATE_CODE,szValidateCode,CountArray(szValidateCode));

	//������Ϣ
	TCHAR szLogonPass2[LEN_PASSWORD]=TEXT("");
	TCHAR szInsurePass2[LEN_PASSWORD]=TEXT("");
	GetDlgItemText(IDC_LOGON_PASS2,szLogonPass2,CountArray(szLogonPass2));
	GetDlgItemText(IDC_LOGON_PASS1,m_szLogonPass,CountArray(m_szLogonPass));
	GetDlgItemText(IDC_LOGON_PASS2,szInsurePass2,CountArray(szInsurePass2));
	GetDlgItemText(IDC_LOGON_PASS1,m_szInsurePass,CountArray(m_szInsurePass));

	//��ȡ�ַ�
	GetControlString(IDC_ACCOUNTS,m_szAccounts,CountArray(m_szAccounts));
	GetControlString(IDC_NICKNAME,m_szNickName,CountArray(m_szNickName));
	GetControlString(IDC_SPREADER,m_szSpreader,CountArray(m_szSpreader));
	GetControlString(IDC_PASSPORT_ID,m_szPassPortID,CountArray(m_szPassPortID));
	GetControlString(IDC_COMPELLATION,m_szCompellation,CountArray(m_szCompellation));
    GetControlString(IDC_QQ,m_szQQ,CountArray(m_szQQ));
	//��������
	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();

	//�ʺ��ж�
	if (pUserItemElement->EfficacyAccounts(m_szAccounts,szDescribe,CountArray(szDescribe))==false)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

		//���ý���
		m_edAccounts.SetFocus();

		return false;
	}

	//�ǳ��ж�
	if (pUserItemElement->EfficacyNickName(m_szNickName,szDescribe,CountArray(szDescribe))==false)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

		//���ý���
		m_edNickName.SetFocus();

		return false;
	}

	//�����ж�
	if (pUserItemElement->EfficacyPassword(m_szLogonPass,szDescribe,CountArray(szDescribe))==false)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

		//���ý���
		m_edLogonPass1.SetFocus();

		return false;
	}

	//�����ж�
	if (lstrcmp(m_szLogonPass,szLogonPass2)!=0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("������������ʺ����벻һ�£����������룡"),MB_ICONERROR,0);

		//���ý���
		m_edLogonPass1.SetFocus();

		return false;
	}

	//�����ж�
	if (pUserItemElement->EfficacyPassword(m_szInsurePass,szDescribe,CountArray(szDescribe))==false)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

		//���ý���
		m_edInsurePass1.SetFocus();

		return false;
	}

	//�����ж�
	/*if (lstrcmp(m_szInsurePass,szInsurePass2)!=0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("����������ı��չ����벻һ�£����������룡"),MB_ICONERROR,0);

		//���ý���
		m_edInsurePass1.SetFocus();

		return false;
	}*/

	//���֤��
	if (pUserItemElement->EfficacyPassPortID(m_szPassPortID,szDescribe,CountArray(szDescribe))==false)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(szDescribe,MB_ICONERROR,0);

		//���ý���
		m_edPassPortID.SetFocus();

		return false;
	}

	//Ч���ж�
	if (m_WndValidateCode.CheckValidateCode(szValidateCode)==false)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("Ч����Ч����֤ʧ�ܣ����������룡"),MB_ICONERROR,0);

		//���ý���
		m_edValidateCode.SetFocus();

		return false;
	}
    	//QQ
	if (lstrlen(m_szQQ) == 0)
	{
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("������QQ����"),MB_ICONERROR,0);

		//���ý���
		m_edCompellation.SetFocus();

		return false;
	}
	  	//�ֻ�����
	if (lstrlen(m_szSpreader) == 0)
	{
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�������ֻ�����"),MB_ICONERROR,0);

		//���ý���
		m_edCompellation.SetFocus();

		return false;
	}
	//�û��Ա�
	if (((CButton *)GetDlgItem(IDC_GENDER_FEMALE))->GetCheck()==BST_CHECKED) m_cbGender=GENDER_FEMALE;
	if (((CButton *)GetDlgItem(IDC_GENDER_MANKIND))->GetCheck()==BST_CHECKED) m_cbGender=GENDER_MANKIND;

	//������Ϣ
	//m_cbRemPassword=(((CButton *)GetDlgItem(IDC_REM_PASSWORD))->GetCheck()==BST_CHECKED);

	return true;
}

//��ȡ�ַ�
VOID CDlgRegister::GetControlString(UINT uControlID, TCHAR szString[], WORD wMaxCount)
{
	//��ȡ�ַ�
	CString strString;
	GetDlgItemText(uControlID,strString);

	//ȥ���ո�
	strString.TrimLeft();
	strString.TrimRight();

	//�����ַ�
	lstrcpyn(szString,strString,wMaxCount);

	return;
}

//�رհ�ť
VOID CDlgRegister::OnBnClickedQuit()
{
	//�رմ���
	OnCancel();

	return;
}


//ͷ��ѡ��
VOID CDlgRegister::OnBnClickedSelectFace()
{
	//�������
	if ((m_FaceSelectControl.GetInterface()==NULL)&&(m_FaceSelectControl.CreateInstance()==false))
	{
		CInformation Information(this);
		Information.ShowMessageBox(m_FaceSelectControl.GetErrorDescribe(),MB_ICONERROR);
		return;
	}

	//���ؽ���
	ShowWindow(SW_HIDE);

	//���ÿؼ�
	m_FaceSelectControl->SetAllowItemFull();

	//ѡ��ͷ��
	if (m_FaceSelectControl->GetSelectFaceID(m_wFaceID)==true)
	{
		m_FaceItemView.SetSystemFace(m_wFaceID);
	}

	//��ʾ����
	ShowWindow(SW_SHOW);

	return;
}

//������֤
VOID CDlgRegister::OnBnClickedChangeValidate()
{
	//������֤
	m_WndValidateCode.RandValidateCode();

	return;
}

VOID CDlgRegister::OnBnSelectGender()
{
	InvalidateRect(CRect(105,179,105+65,179+65),TRUE);
}

//�滭����
BOOL CDlgRegister::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//���û���
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//������Դ
	CPngImage ImageBack;
	CPngImage ImageTitle;
	ImageTitle.LoadImage(AfxGetInstanceHandle(),TEXT("REGISTER_TITLE"));
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_REGISTER_BACK"));

	////����ͼ��
	//CPngImage ImageLogo;
	//ImageLogo.LoadImage(GetModuleHandle(SKIN_CONTROL_DLL_NAME),TEXT("SKIN_WND_LOGO"));

	//�滭����
	ImageBack.DrawImage(pBufferDC,0,0);
	//ImageLogo.DrawImage(pBufferDC,11,6);
	ImageTitle.DrawImage(pBufferDC,40,6);

	//������Դ
	CPngImage ImageFlag;
	ImageFlag.LoadImage(AfxGetInstanceHandle(),TEXT("RIGISTER_CHECK_FLAG"));

	//��ȡ��С
	CSize SizeFlag;
	SizeFlag.SetSize(ImageFlag.GetWidth()/3,ImageFlag.GetHeight());

	pBufferDC->SetTextColor(RGB(0,0,0));

	for(int i=0; i<9; i++)
	{
		ImageFlag.DrawImage(pBufferDC,m_ptTipString[i].x-20,m_ptTipString[i].y-2,SizeFlag.cx,SizeFlag.cy,m_cbFlag[i]*SizeFlag.cx,0,SizeFlag.cx,SizeFlag.cy);

		pBufferDC->TextOut(m_ptTipString[i].x,m_ptTipString[i].y,m_strTipString[i]);
	}


	IFaceItemControl * pIFaceItemControl=CFaceItemControl::GetInstance();

	/*if (((CButton *)GetDlgItem(IDC_GENDER_FEMALE))->GetCheck()==BST_CHECKED)
	{
		pIFaceItemControl->DrawFaceBigNormal(pBufferDC,105+3,179+3,0);
	}
	else
	{
		pIFaceItemControl->DrawFaceBigNormal(pBufferDC,105+3,179+3,1);
	}*/


	////�滭�ȼ�
	//ImagePassword.DrawImage(pBufferDC,249,258,SizePassword.cx*3,SizePassword.cy,0,0);
	//ImagePassword.DrawImage(pBufferDC,249,311,SizePassword.cx*3,SizePassword.cy,0,0);

	////�滭����
	//if (m_cbLogonPassLevel>=PASSWORD_LEVEL_1)
	//{
	//	INT nImagePos=(m_cbLogonPassLevel-PASSWORD_LEVEL_1)*SizePassword.cx;
	//	ImagePassword.DrawImage(pBufferDC,249+nImagePos,258,SizePassword.cx,SizePassword.cy,nImagePos,SizePassword.cy);
	//}

	////�滭����
	//if (m_cbInsurePassLevel>=PASSWORD_LEVEL_1)
	//{
	//	INT nImagePos=(m_cbInsurePassLevel-PASSWORD_LEVEL_1)*SizePassword.cx;
	//	ImagePassword.DrawImage(pBufferDC,249+nImagePos,311,SizePassword.cx,SizePassword.cy,nImagePos,SizePassword.cy);
	//}

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//��ʾ��Ϣ
VOID CDlgRegister::OnShowWindow(BOOL bShow, UINT nStatus)
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
VOID CDlgRegister::OnLButtonDown(UINT nFlags, CPoint Point)
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
VOID CDlgRegister::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	//�ƶ��ֲ�
	if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}

	return;
}

//�ؼ���ɫ
HBRUSH CDlgRegister::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(10,10,10));
			return m_brBrush;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//////////////////////////////////////////////////////////////////////////////////

void CDlgRegister::OnEnChangeAccounts()
{
	//CString strString;
	//GetDlgItemText(IDC_ACCOUNTS,strString);

	//bool bRedraw=false;

	//if(strString.GetLength()<6 && m_cbFlag[0]!=FLAG_HINT)
	//{
	//	m_cbFlag[0]=FLAG_HINT;
	//	m_strTipString[0]=TEXT("�˺ų��Ȳ�������6λ�ַ�");
	//	bRedraw=true;
	//}

	//if(strString.GetLength()>=6 && strString.GetLength())
	//{
	//	m_cbFlag[0]=FLAG_RIGHT;
	//	m_strTipString[0]=TEXT("��ȷ");
	//	bRedraw=true;
	//}

	//if(bRedraw) RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}

void CDlgRegister::OnEnChangeNickname()
{
	//CString strString;
	//GetDlgItemText(IDC_NICKNAME,strString);

	//bool bRedraw=false;

	//if(strString.GetLength()<6 && m_cbFlag[1]!=FLAG_HINT)
	//{
	//	m_cbFlag[1]=FLAG_HINT;
	//	m_strTipString[1]=TEXT("�ǳƳ��Ȳ�������6λ�ַ�");
	//	bRedraw=true;
	//}

	//if(strString.GetLength()>=6 && strString.GetLength())
	//{
	//	m_cbFlag[1]=FLAG_RIGHT;
	//	m_strTipString[1]=TEXT("��ȷ");
	//	bRedraw=true;
	//}

	//if(bRedraw) RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}

//��������
VOID CDlgRegister::OnEnChangeLogonPass()
{
	CString strString;
	GetDlgItemText(IDC_LOGON_PASS1,strString);

	bool bRedraw=false;

	if(strString.GetLength()<6 && m_cbFlag[2]!=FLAG_HINT)
	{
		m_cbFlag[2]=FLAG_HINT;
		m_strTipString[2]=TEXT("���볤�Ȳ�������6λ�ַ�");
		bRedraw=true;
	}

	if(strString.GetLength()>=6 && strString.GetLength())
	{
		m_cbFlag[2]=FLAG_RIGHT;
		m_strTipString[2]=TEXT("��ȷ");
		bRedraw=true;
	}

	if(bRedraw) RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

	return;
}

void CDlgRegister::OnEnChangeLogonPass2()
{
	CString strString;
	GetDlgItemText(IDC_LOGON_PASS2,strString);

	bool bRedraw=false;

	if(strString.GetLength()<6 && m_cbFlag[3]!=FLAG_HINT)
	{
		m_cbFlag[3]=FLAG_HINT;
		m_strTipString[3]=TEXT("���볤�Ȳ�������6λ�ַ�");
		bRedraw=true;
	}

	if(strString.GetLength()>=6 && strString.GetLength())
	{
		CString strPass1;
		GetDlgItemText(IDC_LOGON_PASS1,strPass1);
		if(strPass1==strString)
		{
			m_cbFlag[3]=FLAG_RIGHT;
			m_strTipString[3]=TEXT("��ȷ");
			bRedraw=true;
		}
		else
		{
			m_cbFlag[3]=FLAG_ERROR;
			m_strTipString[3]=TEXT("�����������벻һ�£�");
			bRedraw=true;
		}
	}

	if(bRedraw) RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}


//��������
/*VOID CDlgRegister::OnEnChangeInsurePass()
{
	CString strString;
	GetDlgItemText(IDC_INSURE_PASS1,strString);

	bool bRedraw=false;

	if(strString.GetLength()<6 && m_cbFlag[4]!=FLAG_HINT)
	{
		m_cbFlag[4]=FLAG_HINT;
		m_strTipString[4]=TEXT("���볤�Ȳ�������6λ�ַ�");
		bRedraw=true;
	}

	if(strString.GetLength()>=6 && strString.GetLength())
	{
		m_cbFlag[4]=FLAG_RIGHT;
		m_strTipString[4]=TEXT("��ȷ");
		bRedraw=true;
	}

	if(bRedraw) RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);


	return;
}*/

/*void CDlgRegister::OnEnChangeInsurePass2()
{
	CString strString;
	GetDlgItemText(IDC_INSURE_PASS2,strString);

	bool bRedraw=false;

	if(strString.GetLength()<6 && m_cbFlag[5]!=FLAG_HINT)
	{
		m_cbFlag[5]=FLAG_HINT;
		m_strTipString[5]=TEXT("���볤�Ȳ�������6λ�ַ�");
		bRedraw=true;
	}

	if(strString.GetLength()>=6 && strString.GetLength())
	{
		CString strPass1;
		GetDlgItemText(IDC_INSURE_PASS1,strPass1);
		if(strPass1==strString)
		{
			m_cbFlag[5]=FLAG_RIGHT;
			m_strTipString[5]=TEXT("��ȷ");
			bRedraw=true;
		}
		else
		{
			m_cbFlag[5]=FLAG_ERROR;
			m_strTipString[5]=TEXT("�����������벻һ�£�");
			bRedraw=true;
		}
	}

	if(bRedraw) RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}*/

void CDlgRegister::OnEnChangeSpreader()
{
	CString strString;
	GetDlgItemText(IDC_SPREADER,strString);

	bool bRedraw=false;

	if(strString.GetLength()==0 && m_cbFlag[6]!=FLAG_HINT)
	{
		m_cbFlag[6]=FLAG_HINT;
		m_strTipString[6]=TEXT("�ֻ�����(�һ��˺ź�������Чƾ֤)");
		bRedraw=true;
	}

	if(strString.GetLength()>=1 && strString.GetLength()<11)
	{
		m_cbFlag[6]=FLAG_HINT;
		m_strTipString[6]=TEXT("��11λ����������ҷ��Ϲ��");
		bRedraw=true;
	}

	if(strString.GetLength()==11)
	{
		m_cbFlag[6]=FLAG_RIGHT;
		m_strTipString[6]=TEXT("��ȷ");
		bRedraw=true;
	}

	if(bRedraw) RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}


void CDlgRegister::OnEnChangeCompellation()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CDlgRegister::OnEnChangePassportId()
{
	CString strString;
	GetDlgItemText(IDC_PASSPORT_ID,strString);

	bool bRedraw=false;

	if(strString.GetLength()==0 && m_cbFlag[8]!=FLAG_HINT)
	{
		m_cbFlag[8]=FLAG_HINT;
		m_strTipString[8]=TEXT("���֤��(�һ��˺ź�������Чƾ֤)");
		bRedraw=true;
	}

	if(strString.GetLength()>=1 && strString.GetLength()!=15 && strString.GetLength()!=18)
	{
		m_cbFlag[8]=FLAG_HINT;
		m_strTipString[8]=TEXT("��15λ��18λ��������ҷ��Ϲ��");
		bRedraw=true;
	}

	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();

	if (pUserItemElement->EfficacyPassPortID(strString,szDescribe,CountArray(szDescribe))==true)
	{
		m_cbFlag[8]=FLAG_RIGHT;
		m_strTipString[8]=TEXT("��ȷ");
		bRedraw=true;
	}

	if(bRedraw) RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
}

void CDlgRegister::OnEnKillfocusAccount()
{
	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();

	//����˺�
	GetControlString(IDC_ACCOUNTS,m_szAccounts,CountArray(m_szAccounts));
	if(pUserItemElement->EfficacyAccounts(m_szAccounts,szDescribe,CountArray(szDescribe)))
	{
		if(GetFocus()->m_hWnd!=m_edAccounts.m_hWnd)
		{
			m_strTipString[0]=TEXT("���ڼ���˺��Ƿ����...");

			InvalidateRect(CRect(m_ptTipString[0].x,m_ptTipString[0].y,m_ptTipString[0].x+400,m_ptTipString[0].y+30),TRUE);

			//ִ�м��
			CMissionLogon * pMissionLogon=CMissionLogon::GetInstance();
			if(pMissionLogon!=NULL)pMissionLogon->PerformLogonMission(false,CHECK_ACCOUNT);
		}

	}
	else
	{
		m_strTipString[0]=TEXT("���ȱ������6λ�ַ�");
		InvalidateRect(CRect(m_ptTipString[0].x,m_ptTipString[0].y,m_ptTipString[0].x+400,m_ptTipString[0].y+30),TRUE);
	}
}



void CDlgRegister::OnEnKillfocusNickname()
{
	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();

	//����ǳ�
	GetControlString(IDC_NICKNAME,m_szNickName,CountArray(m_szNickName));
	if(pUserItemElement->EfficacyNickName(m_szNickName,szDescribe,CountArray(szDescribe)))
	{
		if(GetFocus()->m_hWnd!=m_edNickName.m_hWnd)
		{
			m_strTipString[1]=TEXT("���ڼ���ǳ��Ƿ����...");
			InvalidateRect(CRect(m_ptTipString[1].x,m_ptTipString[1].y,m_ptTipString[1].x+400,m_ptTipString[1].y+30),TRUE);

			//ִ�м��
			CMissionLogon * pMissionLogon=CMissionLogon::GetInstance();
			if(pMissionLogon!=NULL)pMissionLogon->PerformLogonMission(false,CHECK_NICK);
		}
	}
	else
	{
		m_strTipString[1]=TEXT("���ȱ������6λ�ַ�");
		InvalidateRect(CRect(m_ptTipString[1].x,m_ptTipString[1].y,m_ptTipString[1].x+400,m_ptTipString[1].y+30),TRUE);
	}
}