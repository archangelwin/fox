#include "StdAfx.h"
#include "Resource.h"
#include "Information.h"
#include "DlgInsureCounter.h"
#include "UserItemElement.h"

//////////////////////////////////////////////////////////////////////////////////
#define IDC_SCORE_LINK				100
#define IDC_RECORD_DETAIL           101


//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgInsureSave, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_EN_CHANGE(IDC_SCORE, OnEnChangeScore)
	ON_BN_CLICKED(IDC_BT_SAVE_SCORE, OnBnClickedSaveScore)
	ON_BN_CLICKED(IDC_BT_TAKE_SCORE, OnBnClickedTakeScore)
	ON_STN_CLICKED(IDC_FORGET_INSURE, OnBnClickedForgetInsure)
	ON_COMMAND_RANGE(IDC_SCORE_LINK,IDC_SCORE_LINK+7,OnBnClickedScore)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDlgInsureRecord, CDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(1002, OnBnClickedQueryIn)
	ON_BN_CLICKED(1001, OnBnClickedQueryOut)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CDlgInsurePassword, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BT_SAVE_SCORE, OnBnClickedSaveScore)
	ON_BN_CLICKED(IDC_BT_TAKE_SCORE, OnBnClickedTakeScore)
END_MESSAGE_MAP()


BEGIN_MESSAGE_MAP(CDlgInsureTransfer, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_EN_CHANGE(IDC_SCORE, OnEnChangeScore)
	ON_EN_CHANGE(IDC_NICKNAME,OnEnChangeNick)
	ON_EN_KILLFOCUS(IDC_NICKNAME,OnEnKillFocus)
	ON_STN_CLICKED(IDC_FORGET_INSURE, OnBnClickedForgetInsure)
	ON_BN_CLICKED(IDC_BT_TRANSFER_SCORE, OnBnClickedTransferScore)
	ON_BN_CLICKED(IDC_BY_ID, OnBnClickedById)
	ON_BN_CLICKED(IDC_BY_NAME, OnBnClickedByName)
	ON_COMMAND_RANGE(IDC_SCORE_LINK,IDC_SCORE_LINK+5,OnBnClickedScore)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDlgInsureMain, CDialog)
	//ON_BN_CLICKED(IDC_BT_QUERY_INFO, OnBnClickedQueryInfo)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BT_QUERY_INFO, OnCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL, OnTcnSelchangeInsureMode)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDlgTransferResult, CSkinDialog)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

#define WM_INSUREPLAZA_UPDATA      (WM_USER+1680)             //���и�����Ϣ

struct tagInsurePlazaUpdata
{
	SCORE  lUserScore;
	SCORE  lUserInsure;
};

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureItem::CDlgInsureItem()
{
}

//��������
CDlgInsureItem::~CDlgInsureItem()
{
}

//��ȡ���ֶ�
SCORE CDlgInsureItem::GetUserControlScore(CWnd * pWndScore)
{
	//��������
	WORD wIndex=0;
	SCORE lScore=0L;

	//��ȡ��ֵ
	TCHAR szBuffer[32]=TEXT("");
	pWndScore->GetWindowText(szBuffer,CountArray(szBuffer));

	//������ֵ
	while (szBuffer[wIndex]!=0)
	{
		//��������
		WORD wCurrentIndex=wIndex++;

		//������ֵ
		if ((szBuffer[wCurrentIndex]>=TEXT('0'))&&(szBuffer[wCurrentIndex]<=TEXT('9')))
		{
			lScore=lScore*10L+(szBuffer[wCurrentIndex]-TEXT('0'));
		}
	}

	return lScore;
}

//�滭����
VOID CDlgInsureItem::DrawNumberString(CDC * pDC, SCORE lScore, INT nXPos, INT nYPos)
{
	//ת������
	TCHAR szControl[128]=TEXT("");
	SwitchScoreFormat(lScore,3L,szControl,CountArray(szControl));

	//��������
	INT nXDrawPos=nXPos;
	INT nScoreLength=lstrlen(szControl);

	//�滭�ж�
	if (nScoreLength>0L)
	{
		//������Դ
		CPngImage ImageNumber;
		ImageNumber.LoadImage(GetModuleHandle(SHARE_CONTROL_DLL_NAME),TEXT("SCORE_NUMBER"));

		//��ȡ��С
		CSize SizeNumber;
		SizeNumber.SetSize(ImageNumber.GetWidth()/12L,ImageNumber.GetHeight());

		//�滭����
		for (INT i=0;i<nScoreLength;i++)
		{
			//�滭����
			if (szControl[i]==TEXT(','))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*10L,0L);
			}

			//�滭���
			if (szControl[i]==TEXT('.'))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*11L,0L);
			}

			//�滭����
			if (szControl[i]>=TEXT('0')&&szControl[i]<=TEXT('9'))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*(szControl[i]-TEXT('0')),0L);
			}

			//����λ��
			nXDrawPos+=SizeNumber.cx;
		}
	}

	return;
}

//ת���ַ�
VOID CDlgInsureItem::SwitchScoreString(SCORE lScore, LPTSTR pszBuffer, WORD wBufferSize)
{
	//��������
	LPCTSTR pszNumber[]={TEXT("��"),TEXT("Ҽ"),TEXT("��"),TEXT("��"),TEXT("��"),TEXT("��"),TEXT("½"),TEXT("��"),TEXT("��"),TEXT("��")};
	LPCTSTR pszWeiName[]={TEXT("ʰ"),TEXT("��"),TEXT("Ǫ"),TEXT("��"),TEXT("ʰ"),TEXT("��"),TEXT("Ǫ"),TEXT("��"),TEXT("ʰ"),TEXT("��"),TEXT("Ǫ"),TEXT("��")};

	//ת����ֵ
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%I64d"),lScore);

	//��������
	bool bNeedFill=false;
	bool bNeedZero=false;
	UINT uTargetIndex=0,uSourceIndex=0;

	//�ַ�����
	UINT uItemLength=lstrlen(pszNumber[0]);
	UINT uSwitchLength=lstrlen(szSwitchScore);

	//ת������
	for (UINT i=0;i<uSwitchLength;i++)
	{
		//��������
		WORD wNumberIndex=szSwitchScore[i]-TEXT('0');

		//�������
		if ((bNeedZero==true)&&(wNumberIndex!=0L))
		{
			bNeedZero=false;
			_tcsncat(pszBuffer,pszNumber[0],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//��������
		if (wNumberIndex!=0L)
		{
			_tcsncat(pszBuffer,pszNumber[wNumberIndex],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//����λ��
		if ((wNumberIndex!=0L)&&((uSwitchLength-i)>=2))
		{
			bNeedZero=false;
			_tcsncat(pszBuffer,pszWeiName[uSwitchLength-i-2],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//�����ж�
		if ((bNeedZero==false)&&(wNumberIndex==0))
		{
			bNeedZero=true;
		}

		//��λ�ж�
		if ((bNeedFill==false)&&(wNumberIndex!=0))
		{
			bNeedFill=true;
		}

		//�λ��
		if (((uSwitchLength-i)==5)||((uSwitchLength-i)==9))
		{
			//����λ��
			if ((bNeedFill==true)&&(wNumberIndex==0L))
			{
				_tcsncat(pszBuffer,pszWeiName[uSwitchLength-i-2],wBufferSize-lstrlen(pszBuffer)-1);
			}

			//���ñ���
			bNeedZero=false;
			bNeedFill=false;
		}
	}

	return;
}

//ת���ַ�
VOID CDlgInsureItem::SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize)
{
	//ת����ֵ
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%I64d"),lScore);

	//��������
	WORD wTargetIndex=0;
	WORD wSourceIndex=0;
	UINT uSwitchLength=lstrlen(szSwitchScore);

	//ת���ַ�
	while (szSwitchScore[wSourceIndex]!=0)
	{
		//�����ַ�
		pszBuffer[wTargetIndex++]=szSwitchScore[wSourceIndex++];

		//���붺��
		if ((uSwitchLength!=wSourceIndex)&&(((uSwitchLength-wSourceIndex)%uSpace)==0L))
		{
			pszBuffer[wTargetIndex++]=TEXT(',');
		}
	}

	//�����ַ�
	pszBuffer[wTargetIndex++]=0;

	return;
}
//////////////////////////////////////////////////////////////////////////////////
//���캯��
CDlgInsureRecord::CDlgInsureRecord(): CDialog(IDD_INSURE_RECORD)
{

}

//��������
CDlgInsureRecord::~CDlgInsureRecord()
{

}

BOOL CDlgInsureRecord::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ListDetail.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT, CRect(0, 0, 0, 0), this, 1000);
	m_HeadCtrl.SubclassWindow(m_ListDetail.GetHeaderCtrl()->GetSafeHwnd());
	m_ListDetail.InsertColumn(0, TEXT("�Է��ǳ�"), LVCFMT_LEFT, 80);
	m_ListDetail.InsertColumn(1, TEXT("�Է�I D"), LVCFMT_LEFT, 80);
	m_ListDetail.InsertColumn(2, TEXT("���׷���"), LVCFMT_LEFT, 80);
	m_ListDetail.InsertColumn(3, TEXT("����ʱ��"), LVCFMT_LEFT, 130);
	//m_ListDetail.InsertColumn(5, TEXT("��ز���"), LVCFMT_LEFT, 65);
	m_btnQueryOut.Create(TEXT("��ѯת��"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 1001);
	m_btnQueryIn.Create(TEXT("��ѯת��"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 1002);

	return TRUE; 
}

VOID CDlgInsureRecord::OnOK()
{

}

VOID CDlgInsureRecord::OnCancel()
{

}

void CDlgInsureRecord::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if(GetDlgItem(IDC_STRING_TIP)!=NULL)
		GetDlgItem(IDC_STRING_TIP)->SetWindowPos(NULL, 2, 0, 430, 14, SWP_NOZORDER);

	m_ListDetail.SetWindowPos(NULL, 2, 14, 435, 185, SWP_NOZORDER);
	m_btnQueryOut.SetWindowPos(NULL, (cx / 2 - 77) / 2, 202, 77, 24, SWP_NOZORDER);
	m_btnQueryIn.SetWindowPos(NULL, (cx / 2 - 77) / 2 + cx / 2, 202, 77, 24, SWP_NOZORDER);

}

//�����¼ �����¼ ������ϸ
void CDlgInsureRecord::InsertBankDetail(LPCTSTR lpszNickName, DWORD dwGameID, SCORE lSwapScore, LPCTSTR lpszTime, BYTE cbTransferIn)
{
	int nItemCount = m_ListDetail.GetItemCount();
	int nItem = m_ListDetail.InsertItem(nItemCount,lpszNickName);
	TCHAR sz[48] = TEXT("");
	_sntprintf(sz, sizeof(sz), TEXT("%u"), dwGameID);
	m_ListDetail.SetItemText(nItem,1,sz);
	//ת������
	TCHAR szControl[128]=TEXT("");
	m_DlgInsureItem.SwitchScoreFormat(lSwapScore,3L,szControl,CountArray(szControl));
	//_sntprintf(sz, sizeof(sz), TEXT("%I64d(%s)"), lSwapScore, cbTransferIn == FALSE ? TEXT("ת��") : TEXT("ת��"));
	_sntprintf(sz, sizeof(sz), TEXT("%s"), szControl);
	m_ListDetail.SetItemText(nItem,2,sz);
	m_ListDetail.SetItemText(nItem,3,lpszTime);
	//_sntprintf(sz, sizeof(sz), TEXT("%I64d(%s)"), lSwapScore, cbTransferIn == FALSE ? TEXT("ת��") : TEXT("ת��"));
	//m_ListDetail.SetItemText(nItem,4,sz);
	//GetDlgItem(IDC_STRING_TIP)->SetWindowText(cbTransferIn == FALSE ? TEXT("ת����¼") : TEXT("ת���¼"));
	
}


void CDlgInsureRecord::OnBnClickedQueryOut()
{
	DWORD dwCurrentTime = (DWORD)time(NULL);
	/*if ((dwCurrentTime - m_dwLastQueryTime) < 60)
	{
		AfxMessageBox(TEXT("���ѯ̫Ƶ���ˣ����Ժ��ٲ�ѯ"));
	}
	else*/
	GetDlgItem(IDC_STRING_TIP)->SetWindowText(TEXT(""));
	{
		m_ListDetail.DeleteAllItems();
		m_dwLastQueryTime = dwCurrentTime;
		m_pDlgInsureMain->OnMissionStart();
		m_pDlgInsureMain->PerformQueryRecord(0);
	}
}

void CDlgInsureRecord::OnBnClickedQueryIn()
{
	DWORD dwCurrentTime = (DWORD)time(NULL);
	/*if ((dwCurrentTime - m_dwLastQueryTime) < 60)
	{
		AfxMessageBox(TEXT("���ѯ̫Ƶ���ˣ����Ժ��ٲ�ѯ"));
	}
	else*/

	GetDlgItem(IDC_STRING_TIP)->SetWindowText(TEXT(""));
	{
		m_ListDetail.DeleteAllItems();
		m_dwLastQueryTime = dwCurrentTime;
		m_pDlgInsureMain->OnMissionStart();
		m_pDlgInsureMain->PerformQueryRecord(1);
	}
}


//�ؼ���ɫ
HBRUSH CDlgInsureRecord::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	//switch (nCtlColor)
	//{
	//case CTLCOLOR_DLG:
	//case CTLCOLOR_BTN:
	//case CTLCOLOR_STATIC:
	//	{
	//		pDC->SetBkMode(TRANSPARENT);
	//		pDC->SetTextColor(CSkinDialog::m_SkinAttribute.m_crControlText);
	//		return CSkinDialog::m_SkinAttribute.m_brBackGround;
	//	}
	//}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}


//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureSave::CDlgInsureSave() : CDialog(IDD_INSURE_SAVE)
{
	//���ñ���
	m_bSwitchIng=false;

	return;
}

//��������
CDlgInsureSave::~CDlgInsureSave()
{
}

//�ؼ���
VOID CDlgInsureSave::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//��ť�ؼ�
	DDX_Control(pDX, IDC_BT_TAKE_SCORE, m_btTakeScore);
	DDX_Control(pDX, IDC_BT_SAVE_SCORE, m_btSaveScore);

	//�ؼ�����
	DDX_Control(pDX, IDC_SCORE, m_edScore);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);
	DDX_Control(pDX, IDC_FORGET_INSURE, m_ForgetInsure);
	
	
}

//��������
BOOL CDlgInsureSave::OnInitDialog()
{
	__super::OnInitDialog();

	//���ô���
	m_SkinDPI.Attach(_AtlBaseModule.GetResourceInstance(),m_hWnd,m_lpszTemplateName,96.0);

	//��������
	CSkinDialog::SetWndFont(this,NULL);

	//���ÿؼ�
	m_edScore.LimitText(16L);

	//���ð�ť
	HINSTANCE hResInstance=GetModuleHandle(SHARE_CONTROL_DLL_NAME);
	m_btSaveScore.SetButtonImage(IDB_BT_SAVE,hResInstance,false,false);
	m_btTakeScore.SetButtonImage(IDB_BT_TAKE,hResInstance,false,false);

	m_ImageBack.LoadFromResource(hResInstance,IDB_TAKE_SAVE_BACK);
	SetWindowPos(NULL,0,0,m_ImageBack.GetWidth(),m_ImageBack.GetHeight(),SWP_NOMOVE);

	CRect rcCreate(0,0,0,0);
	m_bt100W.Create(TEXT("1����"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK);
	m_bt500W.Create(TEXT("5����"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK+1);
	m_bt1000W.Create(TEXT("1ǧ��"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK+2);
	m_bt5000W.Create(TEXT("5ǧ��"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK+3);
	m_bt1Y.Create(TEXT("1��"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK+4);
	m_bt5Y.Create(TEXT("5��"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK+5);
	m_btAllScore.Create(TEXT("ȫ����Ϸ��"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK+6);
	m_btAllInsure.Create(TEXT("ȫ��������"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK+7);

	m_bt100W.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));
	m_bt500W.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));
	m_bt1000W.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));
	m_bt5000W.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));
	m_bt1Y.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));
	m_bt5Y.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));
	m_btAllScore.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));
	m_btAllInsure.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));

	//m_bt100W.SetUnderLine(true);
	//m_bt500W.SetUnderLine(true);
	//m_bt1000W.SetUnderLine(true);
	//m_bt5000W.SetUnderLine(true);
	//m_bt1Y.SetUnderLine(true);
	//m_bt5Y.SetUnderLine(true);
	//m_btAllScore.SetUnderLine(true);
	//m_btAllInsure.SetUnderLine(true);
	////m_bt100W.SetWindowPos(NULL,253-16,137-65,30,14,SWP_NOZORDER);
	m_bt100W.SetWindowPos(NULL,237,71,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_bt1000W.SetWindowPos(NULL,237+40,71,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_bt1Y.SetWindowPos(NULL,237+80,71,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_btAllScore.SetWindowPos(NULL,237+110,71,0,0,SWP_NOZORDER|SWP_NOSIZE);

	m_bt500W.SetWindowPos(NULL,237,72+14,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_bt5000W.SetWindowPos(NULL,237+40,72+14,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_bt5Y.SetWindowPos(NULL,237+80,72+14,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_btAllInsure.SetWindowPos(NULL,237+110,72+14,0,0,SWP_NOZORDER|SWP_NOSIZE);

	//��ȡλ��
	CRect rcScore(0,0,0,0);
	m_edScore.GetWindowRect(&rcScore);

	//ת��λ��
	ScreenToClient(&rcScore);

	//����λ��
	m_edScore.MoveWindow(rcScore.left,rcScore.top,rcScore.Width(),14,SWP_NOZORDER|SWP_NOMOVE);

	return TRUE;
}

//
VOID CDlgInsureSave::OnBnClickedScore(UINT nID)
{
	LONGLONG lScore[]={1000000,5000000,10000000,50000000,100000000,500000000,0,0};
	lScore[6]=m_pUserInsureInfo->lUserScore;
	lScore[7]=m_pUserInsureInfo->lUserInsure;

	CString strScore;
	strScore.Format(TEXT("%I64d"),lScore[nID-IDC_SCORE_LINK]);
	m_edScore.SetWindowText(strScore);

}

//ȷ����ť
VOID CDlgInsureSave::OnOK()
{
	return;
}

//ȡ����ť
VOID CDlgInsureSave::OnCancel()
{
	return;
}

//������Ϣ
VOID CDlgInsureSave::OnEnChangeScore()
{
	//״̬����
	if (m_bSwitchIng==false)
	{
		//���ñ���
		m_bSwitchIng=true;

		//��������
		CWnd * pWndScore=GetDlgItem(IDC_SCORE);
		SCORE lScore=m_DlgInsureItem.GetUserControlScore(pWndScore);
		SCORE lMaxScore=__max(m_pUserInsureInfo->lUserScore, m_pUserInsureInfo->lUserInsure);
		if((m_pUserInsureInfo->lUserScore==0) || (m_pUserInsureInfo->lUserInsure==0))
			lMaxScore=__max(m_pUserInsureInfo->lUserScore, m_pUserInsureInfo->lUserInsure);

		//��������
		if(lScore > lMaxScore) lScore = lMaxScore;

		//���ý���
		if (lScore>0L)
		{
			//ת����ֵ
			TCHAR szString[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreString(lScore,szString,CountArray(szString));

			//ת������
			TCHAR szControl[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreFormat(lScore,3L,szControl,CountArray(szControl));

			//���ÿؼ�
			SetDlgItemText(IDC_SCORE,szControl);
			SetDlgItemText(IDC_SCORE_STRING,szString);

			//���ù��
			INT nScoreLength=m_edScore.GetWindowTextLength();
			m_edScore.SetSel(nScoreLength,nScoreLength,FALSE);
		}
		else
		{
			//���ÿؼ�
			SetDlgItemText(IDC_SCORE,TEXT(""));
			SetDlgItemText(IDC_SCORE_STRING,TEXT(""));
		}

		//���ñ���
		m_bSwitchIng=false;
	}

	return;
}

//ȡ�ť
VOID CDlgInsureSave::OnBnClickedTakeScore()
{
	//��ȡ����
	CWnd * pWndScore=GetDlgItem(IDC_SCORE);
	SCORE lTakeScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

	//��ȡ����
	TCHAR szPassword[LEN_PASSWORD];
	m_PasswordControl.GetUserPassword(szPassword);

	//��������
	TCHAR szInsurePass[LEN_MD5];
	CWHEncrypt::MD5Encrypt(szPassword,szInsurePass);

	//�����ж�
	if (lTakeScore<=0L)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("ȡ���Ļ��ֶ���������Ϊ�գ����������뻶�ֶ�������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//��Ŀ�ж�
	if (lTakeScore>m_pUserInsureInfo->lUserInsure)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�����չ��ֶ�����Ŀ���㣬���������뻶�ֶ�������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	////�����ж�
	//if (szPassword[0]==0)
	//{
	//	//��ʾ��Ϣ
	//	CInformation Information(this);
	//	Information.ShowMessageBox(TEXT("���չ����벻��Ϊ�գ����������뱣�չ����룡"),MB_ICONERROR,30);

	//	//���ý���
	//	m_PasswordControl.SetFocus();

	//	return;
	//}
	//
	//�¼�֪ͨ
	m_pDlgInsureMain->OnMissionStart();
	m_pDlgInsureMain->PerformTakeScore(lTakeScore,szInsurePass);

	return;
}

//��ť
VOID CDlgInsureSave::OnBnClickedSaveScore()
{
	//��������
	CWnd * pWndScore=GetDlgItem(IDC_SCORE);
	SCORE lSaveScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

	//�����ж�
	if (lSaveScore<=0L)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("����Ļ��ֶ���������Ϊ�գ����������뻶�ֶ�������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//��Ŀ�ж�
	if (lSaveScore>m_pUserInsureInfo->lUserScore)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("����Я�����ֶ�����Ŀ���㣬���������뻶�ֶ�������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//ִ�д��
	m_pDlgInsureMain->OnMissionStart();
	m_pDlgInsureMain->PerformSaveScore(lSaveScore);

	return;
}

//��������
VOID CDlgInsureSave::OnBnClickedForgetInsure()
{
	//�����ַ
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("%s/LogonLink4.aspx"),szPlatformLink);

	//��ҳ��
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);

	return;
}

//�滭����
BOOL CDlgInsureSave::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pDCBuffer=CDC::FromHandle(BufferDC);

	m_ImageBack.BitBlt(pDCBuffer->GetSafeHdc(),0,0);

	//���û���
	pDCBuffer->SetBkMode(TRANSPARENT);
	pDCBuffer->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	TCHAR szScore[100]=TEXT("");
	TCHAR szInsureScore[100]=TEXT("");

	m_DlgInsureItem.SwitchScoreFormat(m_pUserInsureInfo->lUserScore,3,szScore,CountArray(szScore));
	m_DlgInsureItem.SwitchScoreFormat(m_pUserInsureInfo->lUserInsure,3,szInsureScore,CountArray(szInsureScore));

	pDCBuffer->TextOut(98+8,48,szScore);
	pDCBuffer->TextOut(98+8,20,szInsureScore);

	////�滭����
	//pDCBuffer->FillSolidRect(&rcClient,CSkinDialog::m_SkinAttribute.m_crBackGround);

	////��ȡλ��
	//CRect rcScore;
	//m_edScore.GetWindowRect(&rcScore);

	////ת��λ��
	//ScreenToClient(&rcScore);

	////�滭����
	//COLORREF crColorBorad=CSkinEdit::m_SkinAttribute.m_crEnableBorad;
	//pDCBuffer->Draw3dRect(rcScore.left-6,rcScore.top-5,rcScore.Width()+12,24L,crColorBorad,crColorBorad);

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pDCBuffer,0,0,SRCCOPY);

	return TRUE;
}

//�ؼ���ɫ
HBRUSH CDlgInsureSave::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(CSkinDialog::m_SkinAttribute.m_crControlText);
			return CSkinDialog::m_SkinAttribute.m_brBackGround;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureTransfer::CDlgInsureTransfer() : CDialog(IDD_INSURE_TRANSFER)
{
	//���ñ���
	m_bSwitchIng=false;

	return;
}

//��������
CDlgInsureTransfer::~CDlgInsureTransfer()
{
}

//�ؼ���
VOID CDlgInsureTransfer::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�ؼ�����
	DDX_Control(pDX, IDC_SCORE, m_edScore);
	DDX_Control(pDX, IDC_NICKNAME, m_edNickName);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);
	DDX_Control(pDX, IDC_FORGET_INSURE, m_ForgetInsure);
	DDX_Control(pDX, IDC_BT_TRANSFER_SCORE, m_btTransferScore);
}

//��������
BOOL CDlgInsureTransfer::OnInitDialog()
{
	__super::OnInitDialog();

	//���ô���
	m_SkinDPI.Attach(_AtlBaseModule.GetResourceInstance(),m_hWnd,m_lpszTemplateName,96.0);

	//��������
	CSkinDialog::SetWndFont(this,NULL);

	//���ÿؼ�
	m_edScore.LimitText(16L);
	m_edNickName.LimitText(LEN_NICKNAME-1);

	//���ð�ť
	HINSTANCE hResInstance=GetModuleHandle(SHARE_CONTROL_DLL_NAME);
	m_btTransferScore.SetButtonImage(IDB_BT_TRANS,hResInstance,false,false);
	//((CButton *)GetDlgItem(IDC_BY_NAME))->SetCheck(1);
	((CButton *)GetDlgItem(IDC_BY_ID))->SetCheck(1);
	m_ImageBack.LoadFromResource(hResInstance,IDB_TRANS_BACK);
	SetWindowPos(NULL,0,0,m_ImageBack.GetWidth(),m_ImageBack.GetHeight(),SWP_NOMOVE);

	CRect rcCreate(0,0,0,0);
	m_bt100W.Create(TEXT("1����"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK);
	m_bt500W.Create(TEXT("5����"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK+1);
	m_bt1000W.Create(TEXT("1ǧ��"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK+2);
	m_bt5000W.Create(TEXT("5ǧ��"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK+3);
	m_bt1Y.Create(TEXT("1��"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK+4);
	m_bt5Y.Create(TEXT("5��"),WS_CHILD|WS_VISIBLE|SS_NOTIFY,rcCreate,this,IDC_SCORE_LINK+5);


	m_bt100W.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));
	m_bt500W.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));
	m_bt1000W.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));
	m_bt5000W.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));
	m_bt1Y.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));
	m_bt5Y.SetHyperLinkTextColor(RGB(84,82,82),RGB(84,82,82),RGB(84,82,82));


	m_bt100W.SetWindowPos(NULL,237+64,71+25,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_bt1000W.SetWindowPos(NULL,237+40+64,71+25,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_bt1Y.SetWindowPos(NULL,237+80+64,71+25,0,0,SWP_NOZORDER|SWP_NOSIZE);

	m_bt500W.SetWindowPos(NULL,237+64,72+14+25,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_bt5000W.SetWindowPos(NULL,237+40+64,72+14+25,0,0,SWP_NOZORDER|SWP_NOSIZE);
	m_bt5Y.SetWindowPos(NULL,237+80+64,72+14+25,0,0,SWP_NOZORDER|SWP_NOSIZE);


	//��ȡλ��
	CRect rcScore;
	CRect rcNickName;
	m_edScore.GetWindowRect(&rcScore);
	m_edNickName.GetWindowRect(&rcNickName);

	//ת��λ��
	ScreenToClient(&rcScore);
	ScreenToClient(&rcNickName);

	//����λ��
	m_edScore.MoveWindow(rcScore.left,rcScore.top,rcScore.Width(),14,SWP_NOZORDER|SWP_NOMOVE);
	m_edNickName.MoveWindow(rcNickName.left,rcNickName.top,rcNickName.Width(),14,SWP_NOZORDER|SWP_NOMOVE);

	return TRUE;
}

//ȷ����ť
VOID CDlgInsureTransfer::OnOK()
{
	//ת�˲���
	OnBnClickedTransferScore();

	return;
}

//ȡ����ť
VOID CDlgInsureTransfer::OnCancel()
{
	return;
}


//ʧȥ����
VOID CDlgInsureTransfer::OnEnKillFocus()
{
	CString strText;
	GetDlgItemText(IDC_NICKNAME,strText);
	if(strText.IsEmpty()) return;
	
	m_pDlgInsureMain->OnMissionStart();
	m_pDlgInsureMain->PerformTransferScore(0,strText,0,TEXT("0"));

}

//������Ϣ
VOID CDlgInsureTransfer::OnEnChangeNick()
{
	SetDlgItemText(IDC_NICKNAME2,TEXT(""));
}

VOID CDlgInsureTransfer::OnBnClickedScore(UINT nID)
{
	LONGLONG lScore[]={1000000,5000000,10000000,50000000,100000000,500000000,0,0};

	CString strScore;
	strScore.Format(TEXT("%I64d"),lScore[nID-IDC_SCORE_LINK]);
	m_edScore.SetWindowText(strScore);
}

//������Ϣ
VOID CDlgInsureTransfer::OnEnChangeScore()
{
	//״̬����
	if (m_bSwitchIng==false)
	{
		//���ñ���
		m_bSwitchIng=true;

		//��������
		CWnd * pWndScore=GetDlgItem(IDC_SCORE);
		SCORE lScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

		//��������
		if(lScore > m_pUserInsureInfo->lUserInsure) lScore = m_pUserInsureInfo->lUserInsure;

		//���ý���
		if (lScore>0L)
		{
			//ת����ֵ
			TCHAR szString[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreString(lScore,szString,CountArray(szString));

			//ת������
			TCHAR szControl[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreFormat(lScore,3L,szControl,CountArray(szControl));

			//���ÿؼ�
			SetDlgItemText(IDC_SCORE,szControl);
			SetDlgItemText(IDC_SCORE_STRING,szString);

			//���ù��
			INT nScoreLength=m_edScore.GetWindowTextLength();
			m_edScore.SetSel(nScoreLength,nScoreLength,FALSE);
		}
		else
		{
			//���ÿؼ�
			SetDlgItemText(IDC_SCORE,TEXT(""));
			SetDlgItemText(IDC_SCORE_STRING,TEXT(""));
		}

		//���ñ���
		m_bSwitchIng=false;
	}

	return;
}


//��������
VOID CDlgInsureTransfer::OnBnClickedForgetInsure()
{
	//�����ַ
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("%s/LogonLink4.aspx"),szPlatformLink);

	//��ҳ��
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);

	return;
}

//ת�˰�ť
VOID CDlgInsureTransfer::OnBnClickedTransferScore()
{
	//�����ж�
	if (m_pUserInsureInfo->lUserInsure < m_pUserInsureInfo->lTransferPrerequisite)
	{
		//��ʾ��Ϣ
		TCHAR szTipInfo[128]={0};
		_sntprintf(szTipInfo,CountArray(szTipInfo),TEXT("�����չ��ֶ�����Ŀ�������ת������ %I64d���޷�����ת�˲�����"),m_pUserInsureInfo->lTransferPrerequisite);
		CInformation Information(this);
		Information.ShowMessageBox(szTipInfo,MB_ICONERROR,30);

		return;
	}

	//��ȡ����
	CWnd * pWndScore=GetDlgItem(IDC_SCORE);
	SCORE lTransferScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

	//��ȡ����
	TCHAR szPassword[LEN_PASSWORD];
	m_PasswordControl.GetUserPassword(szPassword);

	//��������
	TCHAR szInsurePass[LEN_MD5];
	CWHEncrypt::MD5Encrypt(szPassword,szInsurePass);

	//��ȡ�ǳ�
	CString strNickName;
	GetDlgItemText(IDC_NICKNAME,strNickName);

	//��ʽ�ǳ�
	strNickName.TrimLeft();
	strNickName.TrimRight();

	//�ǳ��ж�
	if (strNickName.GetLength()==0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		if(((CButton *)GetDlgItem(IDC_BY_NAME))->GetCheck()==BST_CHECKED)
			Information.ShowMessageBox(TEXT("������Ҫ���͵�����ǳƣ�"),MB_ICONERROR,30);
		else
			Information.ShowMessageBox(TEXT("������Ҫ���͵����ID��"),MB_ICONERROR,30);

		//���ý���
		m_edNickName.SetFocus();

		return;
	}

	//ID���ж�
	if(((CButton *)GetDlgItem(IDC_BY_ID))->GetCheck()==BST_CHECKED)
	{
		int nlen = strNickName.GetLength();
		for(int i=0; i<nlen; i++)
		{
			if(strNickName[i] < '0' || strNickName[i] > '9')
			{
				//��ʾ��Ϣ
				CInformation Information(this);
				Information.ShowMessageBox(TEXT("��������ȷ�����ID��"),MB_ICONERROR,30);

				//���ý���
				m_edNickName.SetFocus();
				return;
			}
		}
	}

	//�����ж�
	if (lTransferScore<=0L)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���͵Ļ��ֶ���������Ϊ�գ����������뻶�ֶ�������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//��Ŀ�ж�
	if (lTransferScore>m_pUserInsureInfo->lUserInsure)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�����չ��ֶ�����Ŀ���㣬���������뻶�ֶ�������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//��Ŀ�ж�
	if (lTransferScore<m_pUserInsureInfo->lTransferPrerequisite)
	{
		//��ʾ��Ϣ
		TCHAR szTipInfo[128]={0};
		_sntprintf(szTipInfo,CountArray(szTipInfo),TEXT("�ӱ��չ�ת�˵Ļ��ֶ���Ŀ�������� %I64d���޷�����ת�˲�����"),m_pUserInsureInfo->lTransferPrerequisite);
		CInformation Information(this);
		Information.ShowMessageBox(szTipInfo,MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	////�����ж�
	//if (szPassword[0]==0)
	//{
	//	//��ʾ��Ϣ
	//	CInformation Information(this);
	//	Information.ShowMessageBox(TEXT("���չ����벻��Ϊ�գ����������뱣�չ����룡"),MB_ICONERROR,30);

	//	//���ý���
	//	m_PasswordControl.SetFocus();

	//	return;
	//}
	
	//�¼�֪ͨ
	m_pDlgInsureMain->OnMissionStart();
	m_pDlgInsureMain->PerformTransferScore(((CButton *)GetDlgItem(IDC_BY_NAME))->GetCheck(),strNickName,lTransferScore,szInsurePass);

	//���ý���
	m_PasswordControl.SetFocus();
	m_PasswordControl.SetUserPassword(TEXT(""));

	return;
}

//�滭����
BOOL CDlgInsureTransfer::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pDCBuffer=CDC::FromHandle(BufferDC);

	//���û���
	pDCBuffer->SetBkMode(TRANSPARENT);
	pDCBuffer->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());


	m_ImageBack.BitBlt(pDCBuffer->GetSafeHdc(),0,0);

	TCHAR szInsureScore[100]=TEXT("");

	m_DlgInsureItem.SwitchScoreFormat(m_pUserInsureInfo->lUserInsure,3,szInsureScore,CountArray(szInsureScore));
	pDCBuffer->TextOut(98+8,23,szInsureScore);



	////�滭����
	//pDCBuffer->FillSolidRect(&rcClient,CSkinDialog::m_SkinAttribute.m_crBackGround);

	////��ȡλ��
	//CRect rcScore;
	//CRect rcNickName;
	//m_edScore.GetWindowRect(&rcScore);
	//m_edNickName.GetWindowRect(&rcNickName);

	////ת��λ��
	//ScreenToClient(&rcScore);
	//ScreenToClient(&rcNickName);

	////�滭����
	//COLORREF crColorBorad=CSkinEdit::m_SkinAttribute.m_crEnableBorad;
	//pDCBuffer->Draw3dRect(rcScore.left-6,rcScore.top-5,rcScore.Width()+12,24L,crColorBorad,crColorBorad);
	//pDCBuffer->Draw3dRect(rcNickName.left-6,rcNickName.top-5,rcNickName.Width()+12,24L,crColorBorad,crColorBorad);

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pDCBuffer,0,0,SRCCOPY);

	return TRUE;
}

//�ؼ���ɫ
HBRUSH CDlgInsureTransfer::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(CSkinDialog::m_SkinAttribute.m_crControlText);
			return CSkinDialog::m_SkinAttribute.m_brBackGround;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

void CDlgInsureTransfer::OnBnClickedById()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_TRANSFER_TYPE_TIP)->SetWindowText(TEXT("������� I D��"));
	m_edNickName.SetFocus();
	m_edNickName.SetWindowText(TEXT(""));
}

void CDlgInsureTransfer::OnBnClickedByName()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_TRANSFER_TYPE_TIP)->SetWindowText(TEXT("��������ǳƣ�"));
	m_edNickName.SetFocus();
	m_edNickName.SetWindowText(TEXT(""));
}
//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureMain::CDlgInsureMain() : CDialog(IDD_INSURE_MAIN)
{
	//�������
	m_bSaveMission=false;
	m_bTakeMission=false;
	m_bQueryMission=false;
	m_bModifyPassword=false;
	m_bDetailMission=false;

	m_pInsurePass=NULL;

	//���ñ���
	m_bInitInfo=false;
	m_cbInsureMode=INSURE_SAVE;
	ZeroMemory(&m_UserInsureInfo,sizeof(m_UserInsureInfo));
	ZeroMemory(&m_TransInfo,sizeof(m_TransInfo));

	return;
}

//��������
CDlgInsureMain::~CDlgInsureMain()
{
}

VOID CDlgInsureMain::SetInsurePassword(LPTSTR lpInsure)
{
	m_pInsurePass=lpInsure;
}

//�ؼ���
VOID CDlgInsureMain::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�ؼ�����
	DDX_Control(pDX, IDC_TAB_CONTROL, m_TabControl);
	DDX_Control(pDX, IDC_BT_QUERY_INFO, m_btQueryInfo);
}

//��Ϣ����
BOOL CDlgInsureMain::PreTranslateMessage(MSG * pMsg)
{
	//��������
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

void CDlgInsureMain::OnLButtonDown(UINT nFlags, CPoint point)
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

//��������
BOOL CDlgInsureMain::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	SetWindowText(TEXT("���չ�"));

	//������Դ
	AfxSetResourceHandle(GetModuleHandle(NULL));

    
	//��������
	CSkinDialog::SetWndFont(this,NULL);

	//���ÿؼ�
	m_TabControl.SetItemSize(CSize(95,25));

	//��ȡ�ؼ�
	m_DlgInsureSave.m_pDlgInsureMain=this;
	m_DlgInsureSave.m_pUserInsureInfo=&m_UserInsureInfo;

	//ת�˿ؼ�
	m_DlgInsureTransfer.m_pDlgInsureMain=this;
	m_DlgInsureTransfer.m_pUserInsureInfo=&m_UserInsureInfo;

	//����ؼ�
	m_DlgInsurePassword.m_pDlgInsureMain=this;
	m_DlgInsurePassword.m_pUserInsureInfo=&m_UserInsureInfo;

	m_DlgInsureRecord.m_pDlgInsureMain=this;
	m_DlgInsureRecord.m_pUserInsureInfo=&m_UserInsureInfo;

	//�����ǩ
	m_TabControl.InsertItem(INSURE_SAVE,TEXT("���ֶ���ȡ"));
	m_TabControl.InsertItem(INSURE_TRANSFER,TEXT("���ֶ�����"));
	m_TabControl.InsertItem(INSURE_RECORD,TEXT("���ͼ�¼"));
	m_TabControl.InsertItem(INSURE_PASSWORD,TEXT("�����޸�"));

	//���ð�ť
	HINSTANCE hResInstance=GetModuleHandle(SHARE_CONTROL_DLL_NAME);
	//m_btQueryInfo.SetButtonImage(IDB_BT_QUERY_INFO,hResInstance,false,false);
	m_btQueryInfo.SetButtonImage(IDB_BT_CLOSE,hResInstance,false,false);

	m_ImageBack.LoadImage(hResInstance,TEXT("INSURE_MAIN_BACK"));

	SetWindowPos(NULL,0,0,m_ImageBack.GetWidth(),m_ImageBack.GetHeight(),SWP_NOMOVE);

	//��ѯ��Ϣ
	QueryUserInsureInfo();

	//��ȡ��С
	CRect rcClient;
	GetClientRect(&rcClient);

	//������Դ
	CPngImage ImageInsureInfo;
	ImageInsureInfo.LoadImage(GetModuleHandle(SHARE_CONTROL_DLL_NAME),TEXT("INFO_FRAME"));

	//�滭��Ϣ
	INT nYPosInfo=86L;
	INT nXPosInfo=(rcClient.Width()-ImageInsureInfo.GetWidth())/2L+350;

	//��ȡλ��
	CRect rcButton(0,0,0,0);
	m_TabControl.MoveWindow(26,33,300,27,SWP_NOZORDER|SWP_NOMOVE);
	m_btQueryInfo.GetWindowRect(&rcButton);
	//m_btQueryInfo.MoveWindow(nXPosInfo,nYPosInfo,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);
	m_btQueryInfo.MoveWindow(435,4,rcButton.Width(),rcButton.Height(),SWP_NOZORDER|SWP_NOMOVE);

	//��ȡģʽ
	SwitchInsureModeView(INSURE_SAVE);

	return FALSE;
}

VOID CDlgInsureMain::OnCancel()
{
	if(((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()==BST_CHECKED)
	{
		m_pInsurePass[0]=0;
	}

	__super::OnCancel();
}

//ȷ����ť
VOID CDlgInsureMain::OnOK()
{
	//Ĭ�϶���
	switch (m_cbInsureMode)
	{
	case INSURE_SAVE:		//��ȡ��ʽ
		{
			m_DlgInsureSave.OnOK();
			break;
		}
	case INSURE_TRANSFER:	//ת�˷�ʽ
		{
			m_DlgInsureTransfer.OnOK();
			break;
		}
	}

	return;
}

//�滭����
BOOL CDlgInsureMain::OnEraseBkgnd(CDC * pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	OnDrawClientArea(pDC,rcClient.Width(),rcClient.Height());

	return TRUE;
}

//�滭��Ϣ
VOID CDlgInsureMain::OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight)
{
	////��ȡλ��
	//CRect rcTabControl;
	//m_TabControl.GetWindowRect(&rcTabControl);

	////ת��λ��
	//ScreenToClient(&rcTabControl);

	////�滭����
	//INT nLBorder=m_SkinAttribute.m_EncircleInfoView.nLBorder;
	//INT nRBorder=m_SkinAttribute.m_EncircleInfoView.nRBorder;
	//pDC->FillSolidRect(nLBorder,rcTabControl.bottom-1L,nWidth-nLBorder-nRBorder,1,RGB(145,168,183));

	m_ImageBack.DrawImage(pDC,0,0);

	////������Դ
	//CPngImage ImageInsureInfo;
	//ImageInsureInfo.LoadImage(GetModuleHandle(SHARE_CONTROL_DLL_NAME),TEXT("INFO_FRAME"));

	////�滭��Ϣ
	//INT nYPosInfo=75L;
	//INT nXPosInfo=(nWidth-ImageInsureInfo.GetWidth())/2L;
	//ImageInsureInfo.DrawImage(pDC,nXPosInfo,nYPosInfo,ImageInsureInfo.GetWidth(),ImageInsureInfo.GetHeight(),0,0);

	////������Ϣ
	//if (m_bInitInfo==true)
	//{
	//	//������Դ
	//	CPngImage ImageInsureIcon;
	//	ImageInsureIcon.LoadImage(GetModuleHandle(SHARE_CONTROL_DLL_NAME),TEXT("INSURE_ICON"));

	//	//�滭��־
	//	ImageInsureIcon.DrawImage(pDC,nXPosInfo+10,nYPosInfo+17);

	//	//�滭����
	//	m_DlgInsureItem.DrawNumberString(pDC,m_UserInsureInfo.lUserScore,nXPosInfo+136,nYPosInfo+18L);
	//	m_DlgInsureItem.DrawNumberString(pDC,m_UserInsureInfo.lUserInsure,nXPosInfo+136,nYPosInfo+53L);

	//	//�滭��ʾ
	//	LPCTSTR pszScoreString=TEXT("���ֶ���");
	//	LPCTSTR pszInsureString=TEXT("���չ�");
	//	pDC->TextOut(nXPosInfo+83,nYPosInfo+20L,pszScoreString,lstrlen(pszScoreString));
	//	pDC->TextOut(nXPosInfo+83,nYPosInfo+55L,pszInsureString,lstrlen(pszInsureString));

	//	//������ʾ
	//	TCHAR szString[128]=TEXT("");
	//	_sntprintf(szString,CountArray(szString),TEXT("��ܰ��ʾ�����뻶�ֶ��������ѣ�ȡ�����۳�%ld��,���ͽ��۳�%ld���������"),m_UserInsureInfo.wRevenueTake,m_UserInsureInfo.wRevenueTransfer);

	//	//��ܰ��ʾ
	//	pDC->SetTextColor(RGB(50,50,50));
	//	pDC->TextOut(18,nHeight-28,szString,lstrlen(szString));
	//}
	//else
	//{
	//}

	return;
}

//��ʼ����
VOID CDlgInsureMain::OnMissionStart()
{
	return;
}

//��ֹ����
VOID CDlgInsureMain::OnMissionConclude()
{
	return;
}

//��ѯ����
VOID CDlgInsureMain::QueryUserInsureInfo()
{
	//���ñ���
	m_bSaveMission=false;
	m_bTakeMission=false;
	m_bQueryMission=true;
	m_bTransferMission=false;
	m_bModifyPassword=false;

	//�¼�����
	OnMissionStart();

	//ִ�в�ѯ
	PerformQueryInfo();

	return;
}

//����ģʽ
VOID CDlgInsureMain::SwitchInsureModeView(BYTE cbInsureMode)
{
	switch (cbInsureMode)
	{
	case INSURE_SAVE:			//��ȡ��ʽ
		{
			//���ñ���
			m_cbInsureMode=INSURE_SAVE;

			//���ÿؼ�
			if (m_DlgInsureSave.m_hWnd==NULL)
			{
				//��ȡλ��
				CRect rcClient;
				GetClientRect(&rcClient);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

				//�����ؼ�
				m_DlgInsureSave.Create(IDD_INSURE_SAVE,this);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(NULL));

				m_DlgInsureSave.SetWindowPos(NULL,16,65,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_SHOWWINDOW);
			}
			else
			{
				//��ʾ����
				m_DlgInsureSave.ShowWindow(SW_SHOW);
			}

			//���ÿؼ�
			if (m_DlgInsureTransfer.m_hWnd!=NULL) m_DlgInsureTransfer.ShowWindow(SW_HIDE);
			if (m_DlgInsureRecord.m_hWnd!=NULL) m_DlgInsureRecord.ShowWindow(SW_HIDE);
			if (m_DlgInsurePassword.m_hWnd!=NULL) m_DlgInsurePassword.ShowWindow(SW_HIDE);

			//���ý���
			m_DlgInsureSave.SetFocus();

			//����ѡ��
			m_TabControl.SetCurSel(m_cbInsureMode);

			break;
		}
	case INSURE_TRANSFER:		//ת�˷�ʽ
		{
			//���ñ���
			m_cbInsureMode=INSURE_TRANSFER;

			//���ÿؼ�
			if (m_DlgInsureTransfer.m_hWnd==NULL)
			{
				//��ȡλ��
				CRect rcClient;
				GetClientRect(&rcClient);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

				//�����ؼ�
				m_DlgInsureTransfer.Create(IDD_INSURE_TRANSFER,this);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(NULL));

				m_DlgInsureTransfer.SetWindowPos(NULL,16,65,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_SHOWWINDOW);
			}
			else
			{
				//��ʾ����
				m_DlgInsureTransfer.ShowWindow(SW_SHOW);
			}

			//���ÿؼ�
			if (m_DlgInsureSave.m_hWnd!=NULL) m_DlgInsureSave.ShowWindow(SW_HIDE);
			if (m_DlgInsureRecord.m_hWnd!=NULL) m_DlgInsureRecord.ShowWindow(SW_HIDE);
			if (m_DlgInsurePassword.m_hWnd!=NULL) m_DlgInsurePassword.ShowWindow(SW_HIDE);

			//���ý���
			m_DlgInsureTransfer.SetFocus();

			//����ѡ��
			m_TabControl.SetCurSel(m_cbInsureMode);

			break;
		}
	case INSURE_RECORD:
		{
			//���ñ���
			m_cbInsureMode=INSURE_RECORD;

			//���ÿؼ�
			if (m_DlgInsureRecord.m_hWnd==NULL)
			{
				//��ȡλ��
				CRect rcClient;
				GetClientRect(&rcClient);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

				//�����ؼ�
				m_DlgInsureRecord.Create(IDD_INSURE_RECORD,this);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(NULL));

				m_DlgInsureRecord.SetWindowPos(NULL,16,65,439,229,SWP_NOZORDER|SWP_SHOWWINDOW);
			}
			else
			{
				//��ʾ����
				m_DlgInsureRecord.ShowWindow(SW_SHOW);
			}

			//���ÿؼ�
			if (m_DlgInsureSave.m_hWnd!=NULL) m_DlgInsureSave.ShowWindow(SW_HIDE);
			if (m_DlgInsurePassword.m_hWnd!=NULL) m_DlgInsurePassword.ShowWindow(SW_HIDE);
			if (m_DlgInsureTransfer.m_hWnd!=NULL) m_DlgInsureTransfer.ShowWindow(SW_HIDE);


			//����ѡ��
			m_TabControl.SetCurSel(m_cbInsureMode);

			break;
		}
	case INSURE_PASSWORD:
		{
			//���ñ���
			m_cbInsureMode=INSURE_PASSWORD;

			//���ÿؼ�
			if (m_DlgInsurePassword.m_hWnd==NULL)
			{
				//��ȡλ��
				CRect rcClient;
				GetClientRect(&rcClient);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

				//�����ؼ�
				m_DlgInsurePassword.Create(IDD_INSURE_PASSWORD,this);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(NULL));

				m_DlgInsurePassword.SetWindowPos(NULL,16,65,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_SHOWWINDOW);
			}
			else
			{
				//��ʾ����
				m_DlgInsurePassword.ShowWindow(SW_SHOW);
			}

			//���ÿؼ�
			if (m_DlgInsureSave.m_hWnd!=NULL) m_DlgInsureSave.ShowWindow(SW_HIDE);
			if (m_DlgInsureRecord.m_hWnd!=NULL) m_DlgInsureRecord.ShowWindow(SW_HIDE);
			if (m_DlgInsureTransfer.m_hWnd!=NULL) m_DlgInsureTransfer.ShowWindow(SW_HIDE);

			//���ý���
			m_DlgInsurePassword.SetFocus();

			//����ѡ��
			m_TabControl.SetCurSel(m_cbInsureMode);


			break;
		}

	default:
		{
			ASSERT(FALSE);
		}
	}

	return;
}

//��ѯ��ť
VOID CDlgInsureMain::OnBnClickedQueryInfo()
{
	//��ѯ��Ϣ
	QueryUserInsureInfo();

	//���ý���
	switch (m_cbInsureMode)
	{
	case INSURE_SAVE:		//��ȡ��ʽ
		{
			m_DlgInsureSave.SetFocus();
			break;
		}
	case INSURE_TRANSFER:	//ת�˷�ʽ
		{
			m_DlgInsureTransfer.SetFocus();
			break;
		}
	}

	return;
}

//���͸ı�
VOID CDlgInsureMain::OnTcnSelchangeInsureMode(NMHDR * pNMHDR, LRESULT * pResult)
{
	switch (m_TabControl.GetCurSel())
	{
	case INSURE_SAVE:		//��ȡ��ʽ
		{
			SwitchInsureModeView(INSURE_SAVE);
			break;
		}
	case INSURE_TRANSFER:	//ת�˷�ʽ
		{
			SwitchInsureModeView(INSURE_TRANSFER);
			break;
		}
	case INSURE_PASSWORD:	//�����޸�
		{
			SwitchInsureModeView(INSURE_PASSWORD);
			break;
		}
	case INSURE_RECORD:		//��Ϸ��¼
		{
			SwitchInsureModeView(INSURE_RECORD);
			break;
		}
	default:
		{
			ASSERT(FALSE);
		}
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsurePlaza::CDlgInsurePlaza()
{
	//��������
	m_MissionManager.InsertMissionItem(this);

	//���ñ���
	m_lScore=0L;
	ZeroMemory(m_szNickName,sizeof(m_szNickName));
	ZeroMemory(m_szInsurePass,sizeof(m_szInsurePass));

	return;
}

//��������
CDlgInsurePlaza::~CDlgInsurePlaza()
{
}

//��ѯ�¼�
VOID CDlgInsurePlaza::PerformQueryInfo()
{
	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

	return;
}

//�����¼�
VOID CDlgInsurePlaza::PerformSaveScore(SCORE lSaveScore)
{
	//���ñ���
	m_bSaveMission=true;
	m_bTakeMission=false;
	m_bQueryMission=false;
	m_bTransferMission=false;
	m_bModifyPassword=false;
	m_bDetailMission=false;

	//���ñ���
	m_lScore=lSaveScore;

	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

	return;
}

//ȡ���¼�
VOID CDlgInsurePlaza::PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass)
{
	//���ñ���
	m_bTakeMission=true;
	m_bSaveMission=false;
	m_bQueryMission=false;
	m_bTransferMission=false;
	m_bModifyPassword=false;
	m_bDetailMission=false;

	//���ñ���
	m_lScore=lTakeScore;
	//lstrcpyn(m_szInsurePass,pszInsurePass,CountArray(m_szInsurePass));
	lstrcpyn(m_szInsurePass,m_pInsurePass,CountArray(m_szInsurePass));

	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

	return;
}

//ȡ���¼�
VOID CDlgInsurePlaza::PerformQueryRecord(BYTE cbTransferIn)
{

	//���ñ���
	m_bSaveMission=false;
	m_bTakeMission=false;
	m_bQueryMission=false;
	m_bTransferMission=false;
	m_bModifyPassword=false;
	m_bDetailMission=true;
	m_cbTransferIn = cbTransferIn;
	

	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

	return ;
}

//�޸�����
VOID CDlgInsurePlaza::PerformModifyInsurePassword(LPCTSTR szSrcPassword, LPCTSTR szDesPassword)
{
	//���ñ���
	m_bTakeMission=false;
	m_bSaveMission=false;
	m_bQueryMission=false;
	m_bTransferMission=false;
	m_bModifyPassword=true;
	m_bDetailMission=false;


	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

}

//ת���¼�
VOID CDlgInsurePlaza::PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass)
{
	//���ñ���
	m_bSaveMission=false;
	m_bTakeMission=false;
	m_bQueryMission=false;
	m_bTransferMission=true;
	m_bModifyPassword=false;
	m_bDetailMission=false;

	//���ñ���
	m_cbByNickName=cbByNickName;
	m_lScore=lTransferScore;
	lstrcpyn(m_szNickName,pszNickName,CountArray(m_szNickName));
	//lstrcpyn(m_szInsurePass,pszInsurePass,CountArray(m_szInsurePass));
	lstrcpyn(m_szInsurePass,m_pInsurePass,CountArray(m_szInsurePass));

	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

	return;
}

//�����¼�
bool CDlgInsurePlaza::OnEventMissionLink(INT nErrorCode)
{
	//���ӽ��
	if (nErrorCode!=0)
	{
		//��������
		if (m_MissionManager.AvtiveMissionItem(this,true)==true)
		{
			return true;
		}

		//�¼�����
		OnMissionConclude();

		//������ʾ
		if (m_bSaveMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("���ӷ�������ʱ�����ֶ�����ʧ�ܣ����Ժ��ٴ����ԣ�"),MB_OK|MB_ICONSTOP,30);
		}

		//������ʾ
		if (m_bTakeMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("���ӷ�������ʱ�����ֶ�ȡ��ʧ�ܣ����Ժ��ٴ����ԣ�"),MB_OK|MB_ICONSTOP,30);
		}

		//������ʾ
		if (m_bQueryMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("���ӷ�������ʱ�����չ����ϻ�ȡʧ�ܣ�"),MB_OK|MB_ICONSTOP,30);
		}

		//������ʾ
		if (m_bTransferMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("���ӷ�������ʱ�����ֶ�����ʧ�ܣ����Ժ��ٴ����ԣ�"),MB_OK|MB_ICONSTOP,30);
		}

		//������ʾ
		if (m_bModifyPassword==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("���ӷ�������ʱ�������޸�ʧ�ܣ����Ժ��ٴ����ԣ�"),MB_OK|MB_ICONSTOP,30);
		}

		return true;
	}

	//��������
	if (m_bSaveMission==true)
	{
		//��������
		CMD_GP_UserSaveScore UserSaveScore;
		ZeroMemory(&UserSaveScore,sizeof(UserSaveScore));

		//��������
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

		//���ñ���
		UserSaveScore.lSaveScore=m_lScore;
		UserSaveScore.dwUserID=pGlobalUserData->dwUserID;
		CWHService::GetMachineIDEx(UserSaveScore.szMachineID);

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_USER_SAVE_SCORE,&UserSaveScore,sizeof(UserSaveScore));

		return true;
	}

	//ȡ������
	if (m_bTakeMission==true)
	{
		//��������
		CMD_GP_UserTakeScore UserTakeScore;
		ZeroMemory(&UserTakeScore,sizeof(UserTakeScore));

		//��������
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

		//���ñ���
		UserTakeScore.lTakeScore=m_lScore;
		UserTakeScore.dwUserID=pGlobalUserData->dwUserID;
		CWHService::GetMachineIDEx(UserTakeScore.szMachineID);
		lstrcpyn(UserTakeScore.szPassword,m_szInsurePass,CountArray(UserTakeScore.szPassword));
		//lstrcpyn(UserTakeScore.szPassword,m_pInsurePass,CountArray(UserTakeScore.szPassword));

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_USER_TAKE_SCORE,&UserTakeScore,sizeof(UserTakeScore));

		return true;
	}

	//ת������
	if (m_bTransferMission==true)
	{
		//��������
		CMD_GP_QueryUserInfoRequest QueryUserInfoRequest;
		ZeroMemory(&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));

		//���ñ���
		QueryUserInfoRequest.cbByNickName=m_cbByNickName;
		lstrcpyn(QueryUserInfoRequest.szNickName,m_szNickName,CountArray(QueryUserInfoRequest.szNickName));

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_QUERY_USER_INFO_REQUEST,&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));
	}

	//��ѯ����
	if (m_bQueryMission==true)
	{
		//��������
		CMD_GP_QueryInsureInfo QueryInsureInfo;
		ZeroMemory(&QueryInsureInfo,sizeof(QueryInsureInfo));

		//���ñ���
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		QueryInsureInfo.dwUserID=pGlobalUserInfo->GetGlobalUserData()->dwUserID;
		lstrcpyn(QueryInsureInfo.szPassword,pGlobalUserInfo->GetGlobalUserData()->szPassword,CountArray(QueryInsureInfo.szPassword));

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_QUERY_INSURE_INFO,&QueryInsureInfo,sizeof(QueryInsureInfo));
	}

	//�����޸�
	if (m_bModifyPassword==true)
	{
		//��������
		CMD_GP_ModifyInsurePass ModifyInsurePass;
		ZeroMemory(&ModifyInsurePass,sizeof(ModifyInsurePass));

		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		ModifyInsurePass.dwUserID=pGlobalUserInfo->GetGlobalUserData()->dwUserID;

		//��������
		TCHAR szSrcPasswordEn[LEN_PASSWORD]=TEXT("");
		TCHAR szDesPasswordEn[LEN_PASSWORD]=TEXT("");
		CWHEncrypt::MD5Encrypt(m_DlgInsurePassword.m_szSrcPassword,szSrcPasswordEn);
		CWHEncrypt::MD5Encrypt(m_DlgInsurePassword.m_szDesPassword,szDesPasswordEn);

		//��������
		lstrcpyn(ModifyInsurePass.szScrPassword,szSrcPasswordEn,CountArray(ModifyInsurePass.szScrPassword));
		lstrcpyn(ModifyInsurePass.szDesPassword,szDesPasswordEn,CountArray(ModifyInsurePass.szDesPassword));

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_CHANGE_INSURE_PASSWORD,&ModifyInsurePass,sizeof(ModifyInsurePass));
	}

	//���׼�¼
	if(m_bDetailMission==true)
	{
		//��������
		CMD_GP_QueryBankDetail QueryBankDetail;
		ZeroMemory(&QueryBankDetail,sizeof(QueryBankDetail));
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		QueryBankDetail.dwUserID=pGlobalUserInfo->GetGlobalUserData()->dwUserID;
		QueryBankDetail.cbTransferIn = m_cbTransferIn;

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_QUERY_BANK_DETAIL,&QueryBankDetail,sizeof(QueryBankDetail));

	}

	return true;
}

//�ر��¼�
bool CDlgInsurePlaza::OnEventMissionShut(BYTE cbShutReason)
{
	//��ʾ��Ϣ
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		//��������
		if (m_MissionManager.AvtiveMissionItem(this,true)==true)
		{
			return true;
		}

		//��������
		if (m_bSaveMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("��������������쳣�Ͽ��ˣ����ֶ�����ʧ�ܣ�"),MB_ICONERROR,30);
		}

		//ȡ������
		if (m_bTakeMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("��������������쳣�Ͽ��ˣ����ֶ�ȡ��ʧ�ܣ�"),MB_ICONERROR,30);
		}

		//��ѯ����
		if (m_bQueryMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("��������������쳣�Ͽ��ˣ����չ����ϻ�ȡʧ�ܣ�"),MB_ICONERROR,30);
		}

		//���׼�¼
		if (m_bDetailMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("��������������쳣�Ͽ��ˣ����׼�¼��ȡʧ�ܣ�"),MB_ICONERROR,30);
		}
	}

	//�¼�����
	OnMissionConclude();

	return true;
}

//��ȡ�¼�
bool CDlgInsurePlaza::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
{
	//�����
	if (Command.wMainCmdID==MDM_GP_USER_SERVICE)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_USER_INSURE_INFO:		//��������
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GP_UserInsureInfo));
				if (wDataSize<sizeof(CMD_GP_UserInsureInfo)) return false;

				//��������
				CMD_GP_UserInsureInfo * pUserInsureInfo=(CMD_GP_UserInsureInfo *)pData;

				//���ñ���
				m_bInitInfo=true;
				m_UserInsureInfo.wRevenueTake=pUserInsureInfo->wRevenueTake;
				m_UserInsureInfo.wRevenueTransfer=pUserInsureInfo->wRevenueTransfer;
				m_UserInsureInfo.wServerID=pUserInsureInfo->wServerID;
				m_UserInsureInfo.lUserScore=pUserInsureInfo->lUserScore;
				m_UserInsureInfo.lUserInsure=pUserInsureInfo->lUserInsure;
				m_UserInsureInfo.lTransferPrerequisite=pUserInsureInfo->lTransferPrerequisite;

				//�ر�����
				m_MissionManager.ConcludeMissionItem(this,false);

				//���´���
				tagInsurePlazaUpdata Updata;
				Updata.lUserScore=pUserInsureInfo->lUserScore;
				Updata.lUserInsure=pUserInsureInfo->lUserInsure;
				AfxGetMainWnd()->SendMessage(WM_INSUREPLAZA_UPDATA,(WPARAM)&Updata,0);

				if(m_DlgInsureSave.IsWindowVisible())m_DlgInsureSave.RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
				if(m_DlgInsureTransfer.IsWindowVisible())m_DlgInsureTransfer.RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

				//���½���
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

				return true;
			}
		case SUB_GP_USER_INSURE_SUCCESS:	//���гɹ�
			{
				//Ч�����
				CMD_GP_UserInsureSuccess * pUserInsureSuccess=(CMD_GP_UserInsureSuccess *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_UserInsureSuccess)-sizeof(pUserInsureSuccess->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_UserInsureSuccess)-sizeof(pUserInsureSuccess->szDescribeString))) return false;

				//���ñ���
				m_UserInsureInfo.lUserScore=pUserInsureSuccess->lUserScore;
				m_UserInsureInfo.lUserInsure=pUserInsureSuccess->lUserInsure;

				//�ر�����
				m_MissionManager.ConcludeMissionItem(this,false);

				//����ؼ�
				if(m_DlgInsureSave.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureSave.m_PasswordControl.SetFocus();
					m_DlgInsureSave.m_PasswordControl.SetUserPassword(TEXT(""));
				}
				if(m_DlgInsureTransfer.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureTransfer.m_PasswordControl.SetFocus();
					m_DlgInsureTransfer.m_PasswordControl.SetUserPassword(TEXT(""));
				}

				//���´���
				tagInsurePlazaUpdata Updata;
				Updata.lUserScore=pUserInsureSuccess->lUserScore;
				Updata.lUserInsure=pUserInsureSuccess->lUserInsure;
				AfxGetMainWnd()->SendMessage(WM_INSUREPLAZA_UPDATA,(WPARAM)&Updata,0);

				if(m_DlgInsureSave.IsWindowVisible())m_DlgInsureSave.RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
				if(m_DlgInsureTransfer.IsWindowVisible())m_DlgInsureTransfer.RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

				//���½���
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

				//ת�˳ɹ�����ʾ�Զ��崰��
				if(m_bTransferMission)
				{
				//	m_DlgInsureTransfer.Invalidate();

					CDlgTransferResult Result;
					Result.SetTransInfo(&m_TransInfo);
					Result.DoModal();
					return true;
				}

				//��ʾ��Ϣ
				if (pUserInsureSuccess->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pUserInsureSuccess->szDescribeString,MB_ICONINFORMATION,60);
				}

				return true;
			}
		case SUB_GP_USER_INSURE_FAILURE:	//����ʧ��
			{
				//Ч�����
				CMD_GP_UserInsureFailure * pUserInsureFailure=(CMD_GP_UserInsureFailure *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString))) return false;

				//ʧ�ܴ���
				OnMissionConclude();

				//�ر�����
				m_MissionManager.ConcludeMissionItem(this,false);

				//����ؼ�
				if(m_DlgInsureSave.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureSave.m_PasswordControl.SetFocus();
					m_DlgInsureSave.m_PasswordControl.SetUserPassword(TEXT(""));
				}
				if(m_DlgInsureTransfer.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureTransfer.m_PasswordControl.SetFocus();
					m_DlgInsureTransfer.m_PasswordControl.SetUserPassword(TEXT(""));
				}

				//��ʾ��Ϣ
				if (pUserInsureFailure->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pUserInsureFailure->szDescribeString,MB_ICONERROR,60);
				}

				return true;
			}
		case SUB_GP_QUERY_USER_INFO_RESULT:	//�û���Ϣ
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GP_UserTransferUserInfo));
				if (wDataSize<sizeof(CMD_GP_UserTransferUserInfo)) return false;

				//��������
				CMD_GP_UserTransferUserInfo * pTransferUserInfo=(CMD_GP_UserTransferUserInfo *)pData;

				if(m_lScore == 0)
				{
					m_DlgInsureTransfer.SetDlgItemText(IDC_NICKNAME2,pTransferUserInfo->szNickName);
				}
				else
				{
					//������Ϣ
					TCHAR szMessage[128]={0};
					_sntprintf(szMessage, CountArray(szMessage), TEXT("��ȷ��Ҫ��[%s], ID:%d ����%I64d ���ֶ���?"), pTransferUserInfo->szNickName, pTransferUserInfo->dwTargetGameID, m_lScore);

					//��ʾ��Ϣ
					CInformation Information(this);
					if (Information.ShowMessageBox(szMessage,MB_ICONQUESTION|MB_YESNO,0)==IDYES)
					{
						//��������
						CMD_GP_UserTransferScore UserTransferScore;
						ZeroMemory(&UserTransferScore,sizeof(UserTransferScore));

						//��������
						CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
						tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

						//���ñ���
						UserTransferScore.cbByNickName=m_cbByNickName;
						UserTransferScore.lTransferScore=m_lScore;
						UserTransferScore.dwUserID=pGlobalUserData->dwUserID;
						CWHService::GetMachineIDEx(UserTransferScore.szMachineID);
						lstrcpyn(UserTransferScore.szNickName,m_szNickName,CountArray(UserTransferScore.szNickName));
						lstrcpyn(UserTransferScore.szPassword,m_szInsurePass,CountArray(UserTransferScore.szPassword));
						//lstrcpyn(UserTransferScore.szPassword,m_pInsurePass,CountArray(UserTransferScore.szPassword));

						ZeroMemory(&m_TransInfo,sizeof(m_TransInfo));
						m_TransInfo.dwSrcGameID=pGlobalUserData->dwGameID;
						m_TransInfo.dwTagGameID=pTransferUserInfo->dwTargetGameID;
						lstrcpyn(m_TransInfo.szSrcNickName,pGlobalUserData->szNickName,CountArray(m_TransInfo.szSrcNickName));
						lstrcpyn(m_TransInfo.szTagNickName,pTransferUserInfo->szNickName,CountArray(m_TransInfo.szTagNickName));
						m_TransInfo.lScore=m_lScore;

						//��������
						m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_USER_TRANSFER_SCORE,&UserTransferScore,sizeof(UserTransferScore));
					}

				}
				return true;
			}
		case SUB_GP_OPERATE_FAILURE:		//����ʧ��
			{
				//Ч�����
				CMD_GP_OperateFailure * pOperateFailure=(CMD_GP_OperateFailure *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_OperateFailure)-sizeof(pOperateFailure->szDescribeString))) return false;

				//�ر�����
				m_MissionManager.ConcludeMissionItem(this,false);
				//ʧ�ܴ���
				OnMissionConclude();

				m_DlgInsurePassword.ResetControlStatus();

				//��ʾ��Ϣ
				if (pOperateFailure->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pOperateFailure->szDescribeString,MB_ICONERROR,60);
				}

				return true;
			}
		case SUB_GP_OPERATE_SUCCESS:		//�����ɹ�
			{
				//��������
				CMD_GP_OperateSuccess * pOperateSuccess=(CMD_GP_OperateSuccess *)pData;

				//Ч������
				ASSERT(wDataSize>=(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_OperateSuccess)-sizeof(pOperateSuccess->szDescribeString))) return false;

				//�ر�����
				m_MissionManager.ConcludeMissionItem(this,false);

				if(m_bModifyPassword)
				{
					//��������
					TCHAR szDesPasswordEn[LEN_PASSWORD]=TEXT("");
					CWHEncrypt::MD5Encrypt(m_DlgInsurePassword.m_szDesPassword,szDesPasswordEn);
					lstrcpy(m_pInsurePass,szDesPasswordEn);

				}

				m_DlgInsurePassword.ResetControlStatus();

				//��ʾ��Ϣ
				if (pOperateSuccess->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pOperateSuccess->szDescribeString,MB_ICONINFORMATION,60);
				}

				return true;
			}
		case SUB_GP_BANK_DETAIL_RESULT:	//����ϸ��
			{
				//Ч�����
				ASSERT(wDataSize%sizeof(CMD_GP_BankDetailResult)==0);
				if (wDataSize%sizeof(CMD_GP_BankDetailResult)!=0) return false;
				//��������
				WORD wItemCount=wDataSize/sizeof(CMD_GP_BankDetailResult);
				CMD_GP_BankDetailResult * pBankDetailResult=(CMD_GP_BankDetailResult *)(pData);

				if (wItemCount == 1 && pBankDetailResult->cbState == 0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(TEXT("������ϸ��ѯʧ��"),MB_ICONINFORMATION,60);
					//�ر�����
					m_MissionManager.ConcludeMissionItem(this,false);
				}
				else
				{
					for (WORD i = 0; i < wItemCount; ++i)
					{
						CMD_GP_BankDetailResult* pDetail = pBankDetailResult + i;
						m_DlgInsureRecord.InsertBankDetail(pDetail->szNickName, pDetail->dwGameID, pDetail->lSwapScore, pDetail->szDateTime, m_cbTransferIn);
						if (pDetail->cbState == 2)
						{
							//�ر�����
							m_MissionManager.ConcludeMissionItem(this,false);
						}
					}
				}

				//�ɹ�����
				OnMissionConclude();

				return true;
			}
		}
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsurePassword::CDlgInsurePassword() : CDialog(IDD_INSURE_PASSWORD)
{
	//���ñ���
	ZeroMemory(m_szSrcPassword,sizeof(m_szSrcPassword));
	ZeroMemory(m_szDesPassword,sizeof(m_szDesPassword));

	return;
}

//��������
CDlgInsurePassword::~CDlgInsurePassword()
{
}

//�ؼ���
VOID CDlgInsurePassword::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//��ť�ؼ�
	DDX_Control(pDX, IDC_BT_TAKE_SCORE, m_btTakeScore);
	DDX_Control(pDX, IDC_BT_SAVE_SCORE, m_btSaveScore);

	//�ؼ�����
	//��������
	DDX_Control(pDX, IDC_INSURE_PASSWORD1, m_edInsurePassword1);
	DDX_Control(pDX, IDC_INSURE_PASSWORD2, m_edInsurePassword2);
	DDX_Control(pDX, IDC_INSURE_PASSWORD3, m_edInsurePassword3);
}

VOID CDlgInsurePassword::ResetControlStatus()
{
	GetDlgItem(IDC_INSURE_PASSWORD1)->SetWindowText(TEXT(""));
	GetDlgItem(IDC_INSURE_PASSWORD2)->SetWindowText(TEXT(""));
	GetDlgItem(IDC_INSURE_PASSWORD3)->SetWindowText(TEXT(""));
}

//��������
BOOL CDlgInsurePassword::OnInitDialog()
{
	__super::OnInitDialog();

	//���ô���
	m_ImageBk.LoadFromResource(GetModuleHandle(SHARE_CONTROL_DLL_NAME),IDB_PASSWORD);

	m_btTakeScore.SetButtonImage(IDB_BT_MODIFY,GetModuleHandle(SHARE_CONTROL_DLL_NAME),false,false);

	m_KeyBoard.Create(IDD_PASSWORD_KEYBOARD2,this);
	m_KeyBoard.SetKeyBoardSink(this);

	SetWindowPos(NULL,0,0,m_ImageBk.GetWidth(),m_ImageBk.GetHeight(),SWP_NOMOVE);
	m_KeyBoard.SetWindowPos(NULL,60,150,0,0,SWP_NOSIZE);

	return TRUE;
}

VOID CDlgInsurePassword::OnKeyBoardChar(WORD wChar)
{
	CWnd* pWnd=GetFocus();
	if(pWnd->GetSafeHwnd()==m_edInsurePassword1.GetSafeHwnd())
	{
		m_edInsurePassword1.SendMessage(WM_CHAR,wChar,0);
	}

	if(pWnd->GetSafeHwnd()==m_edInsurePassword2.GetSafeHwnd())
	{
		m_edInsurePassword2.SendMessage(WM_CHAR,wChar,0);
	}

	if(pWnd->GetSafeHwnd()==m_edInsurePassword3.GetSafeHwnd())
	{
		m_edInsurePassword3.SendMessage(WM_CHAR,wChar,0);
	}
}

VOID CDlgInsurePassword::OnKeyBoardClean()
{
	CWnd* pWnd=GetFocus();
	if(pWnd->GetSafeHwnd()==m_edInsurePassword1.GetSafeHwnd())
	{
		m_edInsurePassword1.SetWindowText(TEXT(""));
	}

	if(pWnd->GetSafeHwnd()==m_edInsurePassword2.GetSafeHwnd())
	{
		m_edInsurePassword2.SetWindowText(TEXT(""));
	}

	if(pWnd->GetSafeHwnd()==m_edInsurePassword3.GetSafeHwnd())
	{
		m_edInsurePassword3.SetWindowText(TEXT(""));
	}
}

//ȷ����ť
VOID CDlgInsurePassword::OnOK()
{
	return;
}

//ȡ����ť
VOID CDlgInsurePassword::OnCancel()
{
	return;
}

//ȡ�ť
VOID CDlgInsurePassword::OnBnClickedTakeScore()
{

	//��������
	TCHAR szSrcPassword[LEN_PASSWORD];
	TCHAR szDesPassword[2][LEN_PASSWORD];

	//��ȡ��Ϣ
	GetDlgItemText(IDC_INSURE_PASSWORD1,szSrcPassword,sizeof(szSrcPassword));
	GetDlgItemText(IDC_INSURE_PASSWORD2,szDesPassword[0],sizeof(szDesPassword[0]));
	GetDlgItemText(IDC_INSURE_PASSWORD3,szDesPassword[1],sizeof(szDesPassword[1]));

	//�����ж�
	if (szSrcPassword[0]==0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("ԭ����������������룡"),MB_ICONERROR,0);

		m_edInsurePassword1.SetFocus();

		return;
	}

	//�����ж�
	if (lstrcmp(szDesPassword[0],szDesPassword[1])!=0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("��������������벻һ�£����������룡"),MB_ICONERROR,0);

		//���ý���
		m_edInsurePassword2.SetFocus();

		return;
	}

	//��������
	TCHAR szDescribe[128]=TEXT("");
	CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();

	//�����ж�
	if (pUserItemElement->EfficacyPassword(szDesPassword[0],szDescribe,CountArray(szDescribe))==false)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�����벻��Ϊ�գ����������룡"),MB_ICONERROR,0);

		//���ý���
		m_edInsurePassword2.SetFocus();

		return;
	}

	//һ���ж�
	if (lstrcmp(szSrcPassword,szDesPassword[0])==0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�����������������ԭ����һ�£����������������룡"),MB_ICONERROR,0);

		//���ý���
		m_edInsurePassword2.SetFocus();

		//��������
		m_edInsurePassword2.SetWindowText(TEXT(""));
		m_edInsurePassword3.SetWindowText(TEXT(""));

		return;
	}

	//���ñ���
	lstrcpyn(m_szSrcPassword,szSrcPassword,CountArray(m_szSrcPassword));
	lstrcpyn(m_szDesPassword,szDesPassword[0],CountArray(m_szDesPassword));

	//�¼�֪ͨ
	m_pDlgInsureMain->OnMissionStart();
	m_pDlgInsureMain->PerformModifyInsurePassword(m_szSrcPassword,m_szDesPassword);

	return;
}

//��ť
VOID CDlgInsurePassword::OnBnClickedSaveScore()
{
	//m_pDlgInsureMain->OnCancel();

	return;
}

//�滭����
BOOL CDlgInsurePassword::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pDCBuffer=CDC::FromHandle(BufferDC);

	//���û���
	pDCBuffer->SetBkMode(TRANSPARENT);
	pDCBuffer->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	m_ImageBk.BitBlt(pDCBuffer->GetSafeHdc(),0,0);

	////�滭����
	//pDCBuffer->FillSolidRect(&rcClient,RGB(238,242,245));


	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pDCBuffer,0,0,SRCCOPY);

	return TRUE;
}

//�ؼ���ɫ
HBRUSH CDlgInsurePassword::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(0,0,0));
			static CBrush brPass;
			brPass.CreateSolidBrush(RGB(238,242,245));
			return brPass;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureServer::CDlgInsureServer()
{
	//���ñ���
	m_pITCPSocket=NULL;
	m_pIMySelfUserItem=NULL;

	m_lScore=0L;

	return;
}

//��������
CDlgInsureServer::~CDlgInsureServer()
{
}

//��ѯ�¼�
VOID CDlgInsureServer::PerformQueryInfo()
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//��������
	CMD_GR_C_QueryInsureInfoRequest QueryInsureInfo;
	ZeroMemory(&QueryInsureInfo,sizeof(QueryInsureInfo));

	//���ñ���
	QueryInsureInfo.cbActivityGame=FALSE;
	lstrcpyn(QueryInsureInfo.szInsurePass,pGlobalUserData->szPassword,CountArray(QueryInsureInfo.szInsurePass));

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_QUERY_INSURE_INFO,&QueryInsureInfo,sizeof(QueryInsureInfo));

	return;
}

//�����¼�
VOID CDlgInsureServer::PerformSaveScore(SCORE lSaveScore)
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	m_bTransferMission=false;

	//��������
	CMD_GR_C_SaveScoreRequest SaveScoreRequest;
	ZeroMemory(&SaveScoreRequest,sizeof(SaveScoreRequest));

	//���ñ���
	SaveScoreRequest.lSaveScore=lSaveScore;

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_SAVE_SCORE_REQUEST,&SaveScoreRequest,sizeof(SaveScoreRequest));

	return;
}

//ȡ���¼�
VOID CDlgInsureServer::PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass)
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	m_bTransferMission=false;

	//��������
	CMD_GR_C_TakeScoreRequest TakeScoreRequest;
	ZeroMemory(&TakeScoreRequest,sizeof(TakeScoreRequest));

	//���ñ���
	TakeScoreRequest.lTakeScore=lTakeScore;
	//lstrcpyn(TakeScoreRequest.szInsurePass,pszInsurePass,CountArray(TakeScoreRequest.szInsurePass));
	lstrcpyn(TakeScoreRequest.szInsurePass,m_pInsurePass,CountArray(TakeScoreRequest.szInsurePass));

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_TAKE_SCORE_REQUEST,&TakeScoreRequest,sizeof(TakeScoreRequest));

	return;
}


//ȡ���¼�
VOID CDlgInsureServer::PerformQueryRecord(BYTE cbTransferIn)
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	//��������
	CMD_GR_QueryBankDetail QueryBankDetail;
	ZeroMemory(&QueryBankDetail,sizeof(QueryBankDetail));
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	QueryBankDetail.dwUserID=pGlobalUserInfo->GetGlobalUserData()->dwUserID;
	QueryBankDetail.cbTransferIn = cbTransferIn;

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_QUERY_BANK_DETAIL,&QueryBankDetail,sizeof(QueryBankDetail));

	return ;
}



//�޸�����
VOID CDlgInsureServer::PerformModifyInsurePassword(LPCTSTR szSrcPassword, LPCTSTR szDesPassword)
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	//��������
	CMD_GP_ModifyInsurePass ModifyInsurePass;
	ZeroMemory(&ModifyInsurePass,sizeof(ModifyInsurePass));

	//��������
	TCHAR szSrcPasswordEn[LEN_PASSWORD]=TEXT("");
	TCHAR szDesPasswordEn[LEN_PASSWORD]=TEXT("");
	CWHEncrypt::MD5Encrypt(szSrcPassword,szSrcPasswordEn);
	CWHEncrypt::MD5Encrypt(szDesPassword,szDesPasswordEn);

	//��������
	lstrcpyn(ModifyInsurePass.szScrPassword,szSrcPasswordEn,CountArray(ModifyInsurePass.szScrPassword));
	lstrcpyn(ModifyInsurePass.szDesPassword,szDesPasswordEn,CountArray(ModifyInsurePass.szDesPassword));

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_CHANGE_INSURE_PASSWORD,&ModifyInsurePass,sizeof(ModifyInsurePass));
}

//ת���¼�
VOID CDlgInsureServer::PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass)
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	m_bTransferMission=true;

	//���ñ���
	m_cbByNickName=cbByNickName;
	m_lScore=lTransferScore;
	lstrcpyn(m_szNickName,pszNickName,CountArray(m_szNickName));
	//lstrcpyn(m_szInsurePass,pszInsurePass,CountArray(m_szInsurePass));
	lstrcpyn(m_szInsurePass,m_pInsurePass,CountArray(m_szInsurePass));

	//��������
	CMD_GR_C_QueryUserInfoRequest QueryUserInfoRequest;
	ZeroMemory(&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));

	//���ñ���
	QueryUserInfoRequest.cbByNickName=cbByNickName;
	lstrcpyn(QueryUserInfoRequest.szNickName,pszNickName,CountArray(QueryUserInfoRequest.szNickName));

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_QUERY_USER_INFO_REQUEST,&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));

	return;
}

//��������
VOID CDlgInsureServer::Initialization(ITCPSocket * pITCPSocket, IClientUserItem * pIMySelfUserItem)
{
	//���ñ���
	m_pITCPSocket=pITCPSocket;
	m_pIMySelfUserItem=pIMySelfUserItem;

	return;
}

//������Ϣ
bool CDlgInsureServer::OnServerInsureMessage(WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize)
{
	//��Ϣ�ж�
	if (wMainCmdID==MDM_GR_INSURE)
	{
		switch (wSubCmdID)
		{
		case SUB_GR_USER_INSURE_INFO:		//��������
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GR_S_UserInsureInfo));
				if (wDataSize<sizeof(CMD_GR_S_UserInsureInfo)) return false;

				//��������
				CMD_GR_S_UserInsureInfo * pUserInsureInfo=(CMD_GR_S_UserInsureInfo *)pData;

				//���ñ���
				m_bInitInfo=true;
				m_UserInsureInfo.wRevenueTake=pUserInsureInfo->wRevenueTake;
				m_UserInsureInfo.wRevenueTransfer=pUserInsureInfo->wRevenueTransfer;
				m_UserInsureInfo.wServerID=pUserInsureInfo->wServerID;
				m_UserInsureInfo.lUserScore=pUserInsureInfo->lUserScore;
				m_UserInsureInfo.lUserInsure=pUserInsureInfo->lUserInsure;
				m_UserInsureInfo.lTransferPrerequisite=pUserInsureInfo->lTransferPrerequisite;

				if(m_DlgInsureSave.IsWindowVisible())m_DlgInsureSave.RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
				if(m_DlgInsureTransfer.IsWindowVisible())m_DlgInsureTransfer.RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
				//���½���
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
				return true;
			}
		case SUB_GR_USER_PASSWORD_RESULT:	//������
			{

				return true;
			}
		case SUB_GR_USER_CHANGE_RESULT:		//������
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GR_S_ChangeInsurePassword));
				if (wDataSize!=sizeof(CMD_GR_S_ChangeInsurePassword)) return false;

				CMD_GR_S_ChangeInsurePassword* pResult=(CMD_GR_S_ChangeInsurePassword*)pData;


				//if(m_bModifyPassword)
				{
					//��������
					TCHAR szDesPasswordEn[LEN_PASSWORD]=TEXT("");
					CWHEncrypt::MD5Encrypt(m_DlgInsurePassword.m_szDesPassword,szDesPasswordEn);
					lstrcpy(m_pInsurePass,szDesPasswordEn);

				}

				if(pResult->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pResult->szDescribeString,MB_ICONINFORMATION,60);
				}

				return true;
			}
		case SUB_GR_USER_INSURE_SUCCESS:	//���гɹ�
			{
				//Ч�����
				CMD_GR_S_UserInsureSuccess * pUserInsureSuccess=(CMD_GR_S_UserInsureSuccess *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GR_S_UserInsureSuccess)-sizeof(pUserInsureSuccess->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GR_S_UserInsureSuccess)-sizeof(pUserInsureSuccess->szDescribeString))) return false;

				//���ñ���
				m_UserInsureInfo.lUserScore=pUserInsureSuccess->lUserScore;
				m_UserInsureInfo.lUserInsure=pUserInsureSuccess->lUserInsure;

				if(m_DlgInsureSave.IsWindowVisible())m_DlgInsureSave.RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
				if(m_DlgInsureTransfer.IsWindowVisible())m_DlgInsureTransfer.RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
				
				//����ؼ�
				if(m_DlgInsureSave.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureSave.m_PasswordControl.SetFocus();
					m_DlgInsureSave.m_PasswordControl.SetUserPassword(TEXT(""));
				}
				if(m_DlgInsureTransfer.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureTransfer.m_PasswordControl.SetFocus();
					m_DlgInsureTransfer.m_PasswordControl.SetUserPassword(TEXT(""));
				}

				//���½���
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

				//ת�˳ɹ�����ʾ�Զ��崰��
				if(m_bTransferMission)
				{
					m_DlgInsureTransfer.Invalidate();

					CDlgTransferResult Result;
					Result.SetTransInfo(&m_TransInfo);
					Result.DoModal();
					return true;
				}

				//��ʾ��Ϣ
				if (pUserInsureSuccess->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pUserInsureSuccess->szDescribeString,MB_ICONINFORMATION,60);
				}

				return true;
			}
		case SUB_GR_USER_INSURE_FAILURE:	//����ʧ��
			{
				//Ч�����
				CMD_GR_S_UserInsureFailure * pUserInsureFailure=(CMD_GR_S_UserInsureFailure *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString))) return false;

				//ʧ�ܴ���
				OnMissionConclude();

				//����ؼ�
				if (m_bInitInfo==true)
				{
					if(m_DlgInsureSave.m_PasswordControl.m_hWnd != NULL)
					{
						m_DlgInsureSave.m_PasswordControl.SetFocus();
						m_DlgInsureSave.m_PasswordControl.SetUserPassword(TEXT(""));
					}
					if(m_DlgInsureTransfer.m_PasswordControl.m_hWnd != NULL)
					{
						m_DlgInsureTransfer.m_PasswordControl.SetFocus();
						m_DlgInsureTransfer.m_PasswordControl.SetUserPassword(TEXT(""));
					}
				}

				//��ʾ��Ϣ
				if (pUserInsureFailure->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pUserInsureFailure->szDescribeString,MB_ICONERROR,60);
				}

				return true;
			}
		case SUB_GR_USER_TRANSFER_USER_INFO:  //�û���Ϣ
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GR_S_UserTransferUserInfo));
				if (wDataSize<sizeof(CMD_GR_S_UserTransferUserInfo)) return false;

				//��������
				CMD_GR_S_UserTransferUserInfo * pTransferUserInfo=(CMD_GR_S_UserTransferUserInfo *)pData;



				if(m_lScore == 0)
				{
					CString strDbg;
					strDbg.Format(TEXT("%s"),pTransferUserInfo->szNickName);
					m_DlgInsureTransfer.SetDlgItemText(IDC_NICKNAME2,strDbg);
				}
				else
				{
					//������Ϣ
					TCHAR szMessage[128]={0};
					_sntprintf(szMessage, CountArray(szMessage), TEXT("��ȷ��Ҫ��[%s], ID:%d ����%I64d ���ֶ���?"), pTransferUserInfo->szNickName, pTransferUserInfo->dwTargetGameID, m_lScore);

					//��ʾ��Ϣ
					CInformation Information(this);
					if (Information.ShowMessageBox(szMessage,MB_ICONQUESTION|MB_YESNO,0)==IDYES)
					{
						//��������
						CMD_GP_C_TransferScoreRequest TransferScoreRequest;
						ZeroMemory(&TransferScoreRequest,sizeof(TransferScoreRequest));

						//��������
						CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
						tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

						//���ñ���
						TransferScoreRequest.cbByNickName=m_cbByNickName;
						TransferScoreRequest.lTransferScore=m_lScore;
						lstrcpyn(TransferScoreRequest.szNickName,m_szNickName,CountArray(TransferScoreRequest.szNickName));
						lstrcpyn(TransferScoreRequest.szInsurePass,m_szInsurePass,CountArray(TransferScoreRequest.szInsurePass));
						//lstrcpyn(TransferScoreRequest.szInsurePass,m_pInsurePass,CountArray(TransferScoreRequest.szInsurePass));

						ZeroMemory(&m_TransInfo,sizeof(m_TransInfo));
						m_TransInfo.dwSrcGameID=pGlobalUserData->dwGameID;
						m_TransInfo.dwTagGameID=pTransferUserInfo->dwTargetGameID;
						lstrcpyn(m_TransInfo.szSrcNickName,pGlobalUserData->szNickName,CountArray(m_TransInfo.szSrcNickName));
						lstrcpyn(m_TransInfo.szTagNickName,pTransferUserInfo->szNickName,CountArray(m_TransInfo.szTagNickName));
						m_TransInfo.lScore=m_lScore;

						//��������
						m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_TRANSFER_SCORE_REQUEST,&TransferScoreRequest,sizeof(TransferScoreRequest));
					}
				}
				return true;
			}
		case SUB_GR_BANK_DETAIL_RESULT:		//���׼�¼
			{
				//Ч�����
				ASSERT(wDataSize%sizeof(CMD_GR_BankDetailResult)==0);
				if (wDataSize%sizeof(CMD_GR_BankDetailResult)!=0) return false;
				//��������
				WORD wItemCount=wDataSize/sizeof(CMD_GR_BankDetailResult);
				CMD_GR_BankDetailResult * pBankDetailResult=(CMD_GR_BankDetailResult *)(pData);


				if (wItemCount == 1 && pBankDetailResult->cbState == 0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(TEXT("������ϸ��ѯʧ��"),MB_ICONINFORMATION,60);
				}
				else
				{
					for (WORD i = 0; i < wItemCount; ++i)
					{
						CMD_GR_BankDetailResult* pDetail = pBankDetailResult + i;
						m_DlgInsureRecord.InsertBankDetail(pDetail->szNickName, pDetail->dwGameID, pDetail->lSwapScore, pDetail->szDateTime, m_cbTransferIn);
						if (pDetail->cbState == 2)
						{
							////�ر�����
							//m_MissionManager.ConcludeMissionItem(this,false);
						}
					}
				}

				return true;
			}
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

CDlgTransferResult::CDlgTransferResult():CSkinDialog(IDD_TRANS_MESSAGE)
{
	m_pTransInfo=NULL;
	m_ImageBk.LoadFromResource(GetModuleHandle(SHARE_CONTROL_DLL_NAME),IDB_TRANS_BK);
}

CDlgTransferResult::~CDlgTransferResult()
{

}

VOID CDlgTransferResult::OnOK()
{

}

VOID CDlgTransferResult::SetTransInfo(tagTransInfo* pInfo)
{
	if(pInfo==NULL) return;

	m_pTransInfo=pInfo;

	
}

VOID CDlgTransferResult::OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight)
{
	m_ImageBk.BitBlt(pDC->GetSafeHdc(),20,40);

	if(m_pTransInfo==NULL) return;
	
	pDC->SetBkMode(1);
	pDC->SetTextColor(RGB(0,0,0));
	pDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	CString strSrcID,strTagID,strScore;
	strSrcID.Format(TEXT("%ld"),m_pTransInfo->dwSrcGameID);
	strTagID.Format(TEXT("%ld"),m_pTransInfo->dwTagGameID);
	strScore.Format(TEXT("%I64d"),m_pTransInfo->lScore);

	TCHAR szScore[128]=TEXT("");
	m_DlgInsureItem.SwitchScoreString(m_pTransInfo->lScore,szScore,CountArray(szScore));

	TCHAR szCurrentDateTime[128]=TEXT("");     
	CTime nowtime;     
	nowtime = CTime::GetCurrentTime();
	_stprintf(szCurrentDateTime, TEXT("%4d-%.2d-%.2d  %.2d:%.2d"),     
		nowtime.GetYear(), nowtime.GetMonth(), nowtime.GetDay(),     
		nowtime.GetHour(), nowtime.GetMinute()); 
    
	pDC->TextOut(160,59,m_pTransInfo->szSrcNickName);
	pDC->TextOut(160,83,strSrcID);
	pDC->TextOut(160,105,m_pTransInfo->szTagNickName);
	pDC->TextOut(160,128,strTagID);
	pDC->TextOut(160,151,strScore);
	pDC->TextOut(160,174,szScore);
	pDC->TextOut(160,199,szCurrentDateTime);
}
HBITMAP CDlgTransferResult::CopyScreenToBitmap(LPRECT lpRect)
{
	HDC hScrDC, hMemDC;
	// ��Ļ���ڴ��豸������
	CBitmap bm;
	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ��Ļ�ֱ���
	int xScrn, yScrn;
	// �����Ļ�ֱ���
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	// ѡ����������
	int nX, nY, nX2, nY2; 
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	//ȷ��ѡ�������ǿɼ���
	if(nX < 0)
		nX = 0;
	if(nY < 0)
		nY = 0;
	if(nX2 > xScrn)
		nX2 = xScrn;
	if(nY2 > yScrn)
		nY2 = yScrn;
	// λͼ��Ⱥ͸߶�
	int nWidth, nHeight; 
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// λͼ���
	HBITMAP hBitmap, hOldBitmap; 
	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	BitBlt(hMemDC, 0, 0, nWidth, nHeight,hScrDC, nX, nY, SRCCOPY);
	//�õ���Ļλͼ�ľ��
	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	//��� 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// ����λͼ���
	return hBitmap;
}
///////////////////////////////////////////////////////
bool CDlgTransferResult::SaveToCliboard(HBITMAP hBitmap)
{
	//�õ���Ļλͼ����Ժ�,���ǿ��԰���Ļ����ճ�����������ϡ�
	if (OpenClipboard()) 
		//hWndΪ���򴰿ھ��
	{
		//��ռ�����
		EmptyClipboard();
		//����Ļ����ճ������������,hBitmap Ϊ�ղŵ���Ļλͼ���
		SetClipboardData(CF_BITMAP, hBitmap);
		//�رռ�����
		CloseClipboard();
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////////

BOOL CDlgTransferResult::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

	SetWindowText(TEXT("����ƾ֤"));

	SetWindowPos(NULL,0,0,464,294,SWP_NOMOVE);

	return TRUE;  
}
