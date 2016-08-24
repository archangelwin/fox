// GameTableToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameTableTool.h"
#include "GameTableToolDlg.h"
#include ".\gametabletooldlg.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameTableToolDlg �Ի���
//////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CGameTableToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_LOAD_IMAGE, OnLoadImage)
	ON_BN_CLICKED(IDC_LOAD_PARAMETER, OnLoadParameter)
	ON_BN_CLICKED(IDC_SAVE_PARAMETER, OnSaveParameter)
	ON_BN_CLICKED(IDC_TABLE_NOCOLOR, OnTableNocolor)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(IDC_LEFT, OnLeft)
	ON_BN_CLICKED(IDC_RIGHT, OnRight)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_BN_CLICKED(IDC_ADD_WIDTH, OnAddWidth)
	ON_BN_CLICKED(IDC_REDUCE_WIDTH, OnReduceWidth)
	ON_BN_CLICKED(IDC_ADD_HEIGHT, OnAddHeight)
	ON_BN_CLICKED(IDC_REDUCE_HEIGHT, OnReduceHeight)
	ON_BN_CLICKED(IDC_VALIGNMET_UP, OnValignmetUp)
	ON_BN_CLICKED(IDC_VALIGNMET_DOWN, OnValignmetDown)
	ON_BN_CLICKED(IDC_VALIGNMET_CENTER, OnValignmetCenter)
	ON_BN_CLICKED(IDC_HAVE_ACCOUNT, OnHaveAccount)
	ON_BN_CLICKED(IDC_HAVE_HEAD, OnHaveHead)
	ON_BN_CLICKED(IDC_HAVE_LOCK, OnHaveLock)
	ON_BN_CLICKED(IDC_FRAME_ACCOUNT, OnFrameAccount)
	ON_BN_CLICKED(IDC_FRAME_HEAD, OnFrameHead)
	ON_BN_CLICKED(IDC_FRAME_TABLENO, OnFrameTableno)
	ON_BN_CLICKED(IDC_HALIGNMET_RIGHT, OnHalignmetRight)
	ON_BN_CLICKED(IDC_HALIGNMET_CENTER, OnHalignmetCenter)
	ON_BN_CLICKED(IDC_HALIGNMET_LEFT, OnHalignmetLeft)
	ON_BN_CLICKED(IDC_LOCAL_LOCK, OnLocalLock)
	ON_BN_CLICKED(IDC_LOCAL_HAND, OnLocalHand)
	ON_BN_CLICKED(IDC_LOCAL_TABLENO, OnLocalTableno)
	ON_BN_CLICKED(IDC_LOCAL_ACCOUNT, OnLocalAccount)
	ON_BN_CLICKED(IDC_LOCAL_HEAD, OnLocalHead)
	ON_BN_CLICKED(IDC_ACCOUNT_COLOR, OnAccountColor)

	//}}AFX_MSG_MAP
	ON_CBN_SELENDOK(IDC_SEAT_COUNT, OnCbnSelendokSeatCount)
	ON_CBN_SELENDOK(IDC_USER_NAME, OnCbnSelendokUserName)
	ON_CBN_SELENDOK(IDC_CURRENT_SEAT, OnCbnSelendokCurrentSeat)
	ON_BN_CLICKED(IDC_FOUR_PIXEL, OnBnClickedFourPixel)
END_MESSAGE_MAP()



CGameTableToolDlg::CGameTableToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameTableToolDlg::IDD, pParent)
{
	m_bFourPixel = FALSE;
	m_bFrameAccount = FALSE;
	m_bFrameHead = FALSE;
	m_bFrameTableNo = FALSE;
	m_bHaveAccount = FALSE;
	m_bHaveHead = FALSE;
	m_bHaveLock = FALSE;

	CRect rt(0,0,0,0);
	CRect rtTableID(0,0,80,12);
	CRect rtChair(0,0,32,32);
	CRect rtName(0,0,49,37);
	m_ptLock=rt.TopLeft();
	m_rcNote=rt;
	m_ptTableID=rt.TopLeft();

	for(int i=0;i<MAX_CHAIR;i++)
	{
		m_ptReady[i]=rtChair.TopLeft();
		m_rcName[i]=rtName;
		m_ptChair[i]=rt.TopLeft();
		m_nDrawStyle[i]=0;
	}

	m_crName=RGB(0,0,0);
	m_crNote=RGB(0,0,0);
	m_crTableID=RGB(0,0,0);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	/*AllocConsole();
	freopen("CON","w",stdout);*/
}

void CGameTableToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACCOUNT_COLOR, m_AccountColor);
	DDX_Control(pDX, IDC_TABLE_NOCOLOR, m_TableNoColor);
	DDX_Control(pDX, IDC_SAVE_PARAMETER, m_SaveParameter);
	DDX_Control(pDX, IDC_LOAD_PARAMETER, m_LoadParameter);
	DDX_Control(pDX, IDC_REDUCE_WIDTH, m_ReduceWidth);
	DDX_Control(pDX, IDC_REDUCE_HEIGHT, m_ReduceHeight);
	DDX_Control(pDX, IDC_ADD_WIDTH, m_AddWidth);
	DDX_Control(pDX, IDC_ADD_HEIGHT, m_AddHeight);
	DDX_Control(pDX, IDC_CURRENT_SEAT, m_CurrentSeat);
	DDX_Control(pDX, IDC_USER_NAME, m_UserName);
	DDX_Control(pDX, IDC_SEAT_COUNT, m_SeatCount);
	DDX_Control(pDX, IDC_SHOW_WND, m_ShowWnd);
	DDX_Check(pDX, IDC_FOUR_PIXEL, m_bFourPixel);
	DDX_Check(pDX, IDC_FRAME_ACCOUNT, m_bFrameAccount);
	DDX_Check(pDX, IDC_FRAME_HEAD, m_bFrameHead);
	DDX_Check(pDX, IDC_FRAME_TABLENO, m_bFrameTableNo);
	DDX_Check(pDX, IDC_HAVE_ACCOUNT, m_bHaveAccount);
	DDX_Check(pDX, IDC_HAVE_HEAD, m_bHaveHead);
	DDX_Check(pDX, IDC_HAVE_LOCK, m_bHaveLock);
	DDX_Radio(pDX, IDC_LOCAL_HEAD, m_CurrentItem);
	DDX_Radio(pDX, IDC_HALIGNMET_LEFT, m_CurrentHAlignmet);
	DDX_Radio(pDX, IDC_VALIGNMET_UP, m_CurrentVAlignmet);
}

// CGameTableToolDlg ��Ϣ�������

BOOL CGameTableToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//�������������ӵĸ���
	for(int i=0;i<16;i++)
	{
		CString strSeatName;
		strSeatName.Format(TEXT("%d ��"),i+1);
		m_SeatCount.AddString(strSeatName);
	}
	m_SeatCount.SetCurSel(3);

	//�����û����Ƶ���ʽ
	m_UserName.AddString(TEXT("King"));
	m_UserName.AddString(TEXT("��������"));
	m_UserName.AddString(TEXT("����������������"));
	m_UserName.AddString(TEXT("������������������������"));
	m_UserName.AddString(TEXT("�������ֳ������ֳ������ֳ�������"));
	m_UserName.SetCurSel(0);
	
	//���õ�ǰ���������Ӻ�
	int nSeatCount=m_SeatCount.GetCurSel();
	if(nSeatCount!=CB_ERR)
	{
		nSeatCount=nSeatCount+1;
	}
	else
	{
		nSeatCount=10;
	}
	for(i=0;i<nSeatCount;i++)
	{
		CString strSeatName;
		strSeatName.Format(TEXT("%d"),i+1);
		m_CurrentSeat.AddString(strSeatName);
	}
	m_CurrentChairID=0;
	m_CurrentSeat.SetCurSel(m_CurrentChairID);

	//���ø�ѡ���ѡ��״̬
	m_bHaveAccount  =TRUE;
	m_bHaveHead     =TRUE;
	m_bHaveLock     =FALSE;
	m_bFrameAccount =TRUE;
	m_bFrameHead    =TRUE;
	m_bFrameTableNo =TRUE;

	//��ѡ��ĳ�ʼ������
	m_CurrentItem=0;
	m_CurrentHAlignmet=1;
	m_CurrentVAlignmet=0;

	//��ֹ������ť�Ĳ���
	m_AddHeight.EnableWindow(false);
	m_AddWidth.EnableWindow(false);
	m_ReduceHeight.EnableWindow(false);
	m_ReduceWidth.EnableWindow(false);

	m_LoadParameter.EnableWindow(false);
	m_SaveParameter.EnableWindow(false);
	m_TableNoColor.EnableWindow(false);
	m_AccountColor.EnableWindow(false);

	this->UpdateData(FALSE);

	m_bLoadParameter=false;
	m_ChairCount=0;

	CreateMyBitMap(&m_MemBitmap);
	m_ShowWnd.SetBitmap((HBITMAP)m_MemBitmap.Detach());

	//������Դ
	m_ImageReady.LoadImage(AfxGetInstanceHandle(),TEXT("TABLE_READY"));
	m_ImageLocker.LoadImage(AfxGetInstanceHandle(),TEXT("TABLE_LOCKER"));
	m_ImageNumberBK.LoadImage(AfxGetInstanceHandle(),TEXT("TABLE_NUMBER_BK"));
	m_ImageNumberNB.LoadImage(AfxGetInstanceHandle(),TEXT("TABLE_NUMBER_NB"));
	//for(int i=0;i<8;i++)
	//{
	//	m_ImagePeople[i].LoadFromResource(AfxGetInstanceHandle(),IDB_HEAD1+i);
	//}


	if(m_FaceItemControlHelper.GetInterface()==NULL)
	{
		m_FaceItemControlHelper.CreateInstance();
	}
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CGameTableToolDlg::CreateMyBitMap(CBitmap *pBitmap)
{
	CClientDC dc(this);

	//��ͼ׼������
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	MemDC.SetBkMode(TRANSPARENT);
	pBitmap->CreateCompatibleBitmap(&dc, 560, 470);
	MemDC.SelectObject(pBitmap);

	//��������
	CFont DrawFont;
	DrawFont.CreateFont(-12,0,0,0,400,0,0,0,134,3,2,1,2,TEXT("����"));
	MemDC.SelectObject(&DrawFont);

	//��䱳������
	MemDC.FillSolidRect(0,0,560,470,RGB(61,99,153));

	//��ʾ����ͼƬ
	DrawTableImage(&MemDC);

	//��ʾ�û�������ʶ
	DrawParameter(&MemDC);

	DrawFont.DeleteObject();
	MemDC.DeleteDC();
}

//����ˢ�»���
void CGameTableToolDlg::UpdateShow()
{
	m_MemBitmap.DeleteObject();
	CreateMyBitMap(&m_MemBitmap);
	m_ShowWnd.SetBitmap((HBITMAP)m_MemBitmap.Detach());
}

//��ʾ����ͼƬ
void CGameTableToolDlg::DrawTableImage(CDC *pDC)
{
	if (!m_ImageTable.IsNull())
	{
		CRect rcShowWnd;
		m_ShowWnd.GetWindowRect(&rcShowWnd);
		int nWidth=m_ImageTable.GetWidth()/2;
		int nHeight=m_ImageTable.GetHeight();
		int nOffXPos=(rcShowWnd.Width()-nWidth)/2;
		int nOffYPos=(rcShowWnd.Height()-nHeight)/2;
		m_ImageTable.DrawImage(pDC,nOffXPos,nOffYPos,nWidth,nHeight,0,0);
		//�滭����
		pDC->Draw3dRect(nOffXPos,nOffYPos,nWidth,nHeight,RGB(255,0,255),RGB(255,0,255));

		CString strUserName;
		int Index=m_UserName.GetCurSel();
		int nLength=m_UserName.GetLBTextLen(Index);
		m_UserName.GetLBText(Index, strUserName.GetBuffer(nLength));
		strUserName.ReleaseBuffer();

		//�滭ͷ��
		for (int i=0;i<m_ChairCount;i++)
		{

			if (m_FaceItemControlHelper.GetInterface() != NULL)
			{
	//			m_FaceItemControlHelper->DrawFaceItemFrame(pDC,nOffXPos+m_ptChair[i].x,nOffYPos+m_ptChair[i].y,ITEM_FRAME_NORMAL);
				m_FaceItemControlHelper->DrawFaceNormal(pDC,nOffXPos+m_ptChair[i].x,nOffYPos+m_ptChair[i].y,i);
			}

			int nYPos=0;
			int nDrawStyte=m_nDrawStyle[i];
			CRect rcDrawRect=m_rcName[i];
			rcDrawRect.left+=nOffXPos;
			rcDrawRect.top+=nOffYPos;
			rcDrawRect.right+=nOffXPos;
			rcDrawRect.bottom+=nOffYPos;
		
		//	/*=m_rcName[i];*/
			int nDrawFormat=DT_WORDBREAK|DT_EDITCONTROL|DT_END_ELLIPSIS;
			int nNameLength=strUserName.GetLength();
		//	int nNameHeight=0;//pDC->DrawText(strUserName,nNameLength,&rcDrawRect,nDrawFormat|DT_CALCRECT);

			//����λ��
			if (nDrawStyte&NT_LEFT) nDrawFormat|=DT_LEFT;
			else if (nDrawStyte&NT_CENTER) nDrawFormat|=DT_CENTER;
			else nDrawFormat|=DT_RIGHT;
			if (nDrawStyte&NT_VCENTER) nDrawFormat|=DT_VCENTER;
			else if (nDrawStyte&NT_BOTTOM) nDrawFormat|=DT_BOTTOM;
			else nDrawFormat|=DT_TOP;
			nDrawFormat|=DT_SINGLELINE;
	
			//�û�����
			pDC->SetTextColor(m_crName);
			pDC->DrawText(strUserName,nNameLength,&rcDrawRect,nDrawFormat);

			if(m_bFrameAccount==TRUE)
			{
				pDC->Draw3dRect(&rcDrawRect,RGB(255,255,255),RGB(255,255,255));
			}

			//����λ��
			m_ImageReady.DrawImage(pDC,nOffXPos+m_ptReady[i].x,nOffYPos+m_ptReady[i].y);
		}
		//�滭��ͼ
	
		m_ImageLocker.DrawImage(pDC,nOffXPos+m_ptLock.x,nOffYPos+m_ptLock.y);

		m_ImageNumberBK.DrawImage(pDC,nOffXPos+m_ptTableID.x,nOffYPos+m_ptTableID.y);
		int nTableIDX=nOffXPos+m_ptTableID.x+m_ImageNumberBK.GetWidth()/2-m_ImageNumberNB.GetWidth()/20;
		int nTableIDY=nOffYPos+m_ptTableID.y+m_ImageNumberBK.GetHeight()/2-m_ImageNumberNB.GetHeight()/2;
		m_ImageNumberNB.DrawImage(pDC,nTableIDX,nTableIDY,m_ImageNumberNB.GetWidth()/10,m_ImageNumberNB.GetHeight(),0,0);
		
	}
}
//��ʾ�û�������ʶ
void CGameTableToolDlg::DrawParameter(CDC *pDC)
{
	
}

void CGameTableToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGameTableToolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CGameTableToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGameTableToolDlg::OnLoadImage() 
{
	//cout<<"left="<<m_rcName[0].left<<"top="<<m_rcName[0].top<<"right="<<m_rcName[0].right<<"bottom="<<m_rcName[0].bottom<<endl;
	//return;
	// TODO: Add your control notification handler code here
	//ѡ���ļ�
	LPCTSTR pszFilter=TEXT("֧�ָ�ʽ(*.png)|*.png|�����ļ� (*.*)|*.*||");
	CFileDialog FileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,pszFilter);

	if(IDOK == FileDlg.DoModal())
	{
		//����ͼƬ
		CString strName = FileDlg.GetPathName() ;

		//�ͷ��ж�
		if ( !m_ImageTable.IsNull() ) m_ImageTable.DestroyImage();

		HRESULT hResult = m_ImageTable.LoadImage(strName);

		//�ɹ��ж�
		if ( SUCCEEDED(hResult) )
		{
			UpdateShow();
		}
		else
		{
			AfxMessageBox(TEXT("����ͼƬʧ�ܣ�������ѡ��"));
			return ;
		}
		m_CurrentChairID=0;
		m_CurrentSeat.SetCurSel(m_CurrentChairID);

		//������ǰ���Ӻ����Ե��ı����뷽ʽ
		OnCbnSelendokSeatCount();

		//ˢ�½���
		m_bLoadParameter=true;
		UpdateShow();
	}

	m_LoadParameter.EnableWindow(true);
	m_SaveParameter.EnableWindow(true);
	m_TableNoColor.EnableWindow(true);
	m_AccountColor.EnableWindow(true);
}

void CGameTableToolDlg::OnLoadParameter() 
{
	//ѡ���ļ�
	LPCTSTR pszFilter=TEXT("֧�ָ�ʽ(*.ini;*.INI;)|*.INI; *.ini;|�����ļ� (*.*)|*.*||");
	CFileDialog FileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,pszFilter);

	CString szResourcePath;
	if(IDOK == FileDlg.DoModal())
	{
		szResourcePath = FileDlg.GetPathName() ;
	}
	if(szResourcePath.GetLength()>0 && szResourcePath.IsEmpty()==false)
	{
		try
		{
			//��ȡ����
			CWHIniData IniData;
			IniData.SetIniFilePath(szResourcePath);

			m_ChairCount = IniData.ReadInt(TEXT("Attribute"),TEXT("ChairItemCount"),0);

			IniData.ReadPoint(m_ptLock,TEXT("Position"),TEXT("Point_Lock"));
			IniData.ReadPoint(m_ptTableID,TEXT("Position"),TEXT("Point_TableID"));
			//���õ�ǰ���������Ӻ�
			m_CurrentSeat.ResetContent();
			TCHAR szBuffer[128];
			for(int i=0;i<m_ChairCount;i++)
			{
				_sntprintf(szBuffer,CountArray(szBuffer),TEXT("Point_Ready%d"),i+1);
				IniData.ReadPoint(m_ptReady[i],TEXT("Position"),szBuffer);

				_sntprintf(szBuffer,CountArray(szBuffer),TEXT("DrawStyle%d"),i+1);
				m_nDrawStyle[i]=IniData.ReadInt(TEXT("Position"),szBuffer,0);

				_sntprintf(szBuffer,CountArray(szBuffer),TEXT("Rect_Name%d"),i+1);
				IniData.ReadRect(m_rcName[i],TEXT("Position"),szBuffer);

				_sntprintf(szBuffer,CountArray(szBuffer),TEXT("Point_Chair%d"),i+1);
				IniData.ReadPoint(m_ptChair[i],TEXT("Position"),szBuffer);

			}
			m_CurrentChairID=0;
			m_CurrentSeat.SetCurSel(m_CurrentChairID);

			//������ǰ���Ӻ����Ե��ı����뷽ʽ
			OnCbnSelendokSeatCount();

			//ˢ�½���
			m_bLoadParameter=true;
			UpdateShow();
		}
		catch(...)
		{
			AfxMessageBox(TEXT("���ز���ʧ�ܣ�������ѡ��"));
			return ;
		}
	}
	
}

void CGameTableToolDlg::OnSaveParameter() 
{
	//ѡ���ļ�
	LPCTSTR pszFilter=TEXT("֧�ָ�ʽ(*.ini;*.INI;)|*.INI; *.ini;|�����ļ� (*.*)|*.*||");
	CFileDialog FileDlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,pszFilter);

	CString szResourcePath;
	if(IDOK == FileDlg.DoModal())
	{
		szResourcePath = FileDlg.GetPathName() ;
	}
	if(szResourcePath.GetLength()>0 && szResourcePath.IsEmpty()==false)
	{
		try
		{
			TCHAR szBuffer[128];
			//��������
			WritePrivateProfileString(TEXT("Attribute"),TEXT("TableItemCount"),TEXT("2"),szResourcePath);
			_sntprintf(szBuffer,CountArray(szBuffer),TEXT("%d"),m_ChairCount);
			WritePrivateProfileString(TEXT("Attribute"),TEXT("ChairItemCount"),szBuffer,szResourcePath);

			//��ɫ����
			WritePrivateProfileString(TEXT("Color"),TEXT("Color_Name"),TEXT("RGB(200,200,200)"),szResourcePath);
			WritePrivateProfileString(TEXT("Color"),TEXT("Color_Member"),TEXT("RGB(0,255,255)"),szResourcePath);
			WritePrivateProfileString(TEXT("Color"),TEXT("Color_Master"),TEXT("RGB(0,255,255)"),szResourcePath);

			//λ������
			_sntprintf(szBuffer,CountArray(szBuffer),TEXT("%d,%d"),m_ptLock.x,m_ptLock.y);
			WritePrivateProfileString(TEXT("Position"),TEXT("Point_Lock"),szBuffer,szResourcePath);
			_sntprintf(szBuffer,CountArray(szBuffer),TEXT("%d,%d"),m_ptTableID.x,m_ptTableID.y);
			WritePrivateProfileString(TEXT("Position"),TEXT("Point_TableID"),szBuffer,szResourcePath);

			TCHAR szBuffer1[128];
			for (int i=0;i<m_ChairCount;i++)
			{
				//׼��λ��
				_sntprintf(szBuffer1,CountArray(szBuffer1),TEXT("Point_Ready%d"),i+1);
				_sntprintf(szBuffer,CountArray(szBuffer),TEXT("%d,%d"),m_ptReady[i].x,m_ptReady[i].y);
				WritePrivateProfileString(TEXT("Position"),szBuffer1,szBuffer,szResourcePath);

				//�����ʽ
				_sntprintf(szBuffer1,CountArray(szBuffer1),TEXT("DrawStyle%d"),i+1);
				_sntprintf(szBuffer,CountArray(szBuffer),TEXT("%d"),m_nDrawStyle[i]);
				WritePrivateProfileString(TEXT("Position"),szBuffer1,szBuffer,szResourcePath);

				//����λ��
				_sntprintf(szBuffer1,CountArray(szBuffer1),TEXT("Rect_Name%d"),i+1);
				_sntprintf(szBuffer,CountArray(szBuffer),TEXT("%d,%d,%d,%d"),m_rcName[i].left,m_rcName[i].top,m_rcName[i].right,m_rcName[i].bottom);
				WritePrivateProfileString(TEXT("Position"),szBuffer1,szBuffer,szResourcePath);

				//����λ��
				_sntprintf(szBuffer1,CountArray(szBuffer1),TEXT("Point_Chair%d"),i+1);
				_sntprintf(szBuffer,CountArray(szBuffer),TEXT("%d,%d"),m_ptChair[i].x,m_ptChair[i].y);
				WritePrivateProfileString(TEXT("Position"),szBuffer1,szBuffer,szResourcePath);
			}
		
			


		}
		catch(...)
		{
			AfxMessageBox(TEXT("�����ļ�����!"));
		}
	}

}

void CGameTableToolDlg::OnTableNocolor() 
{
	CColorDialog ColorDialog(m_crTableID,CC_FULLOPEN);
	if (ColorDialog.DoModal()==IDOK)
	{
		m_crTableID=ColorDialog.GetColor();
	}
	UpdateShow();
}


void CGameTableToolDlg::OnOK() 
{
	CDialog::OnOK();
}

void CGameTableToolDlg::OnUp() 
{
	switch(m_CurrentItem)
	{
	case 0:
		if(m_bFourPixel==TRUE)
		{
			//m_ptChair[m_CurrentChairID].x-=40;
			m_ptChair[m_CurrentChairID].y-=40;
		}
		else
		{
			//m_ptChair[m_CurrentChairID].x-=1;
			m_ptChair[m_CurrentChairID].y-=1;
		}
		break;
	case 1:
		if(m_bFourPixel==TRUE)
		{
			m_rcName[m_CurrentChairID].top-=10;
			m_rcName[m_CurrentChairID].bottom-=10;
		}
		else
		{
			m_rcName[m_CurrentChairID].top-=1;
			m_rcName[m_CurrentChairID].bottom-=1;
		}
		break;
	case 2:
		if(m_bFourPixel==TRUE)
		{
			//m_ptTableID.x-=10;
			m_ptTableID.y-=10;
		}
		else
		{
			//m_ptTableID.x-=1;
			m_ptTableID.y-=1;
		}
		break;
	case 3:
		if(m_bFourPixel==TRUE)
		{
			m_ptReady[m_CurrentChairID].y-=10;
		}
		else
		{
			m_ptReady[m_CurrentChairID].y-=1;
		}
		break;
	case 4:
		if(m_bFourPixel==TRUE)
		{
			m_ptLock.y-=10;
		}
		else
		{
			m_ptLock.y-=1;
		}
		break;
	}
	UpdateShow();
}

void CGameTableToolDlg::OnLeft() 
{
	switch(m_CurrentItem)
	{
	case 0:
		if(m_bFourPixel==TRUE)
		{
			m_ptChair[m_CurrentChairID].x-=40;
			//m_ptChair[m_CurrentChairID].y-=40;
		}
		else
		{
			m_ptChair[m_CurrentChairID].x-=1;
			//m_ptChair[m_CurrentChairID].y-=1;
		}
		break;
	case 1:
		if(m_bFourPixel==TRUE)
		{
			m_rcName[m_CurrentChairID].left-=10;
			m_rcName[m_CurrentChairID].right-=10;
		}
		else
		{
			m_rcName[m_CurrentChairID].left-=1;
			m_rcName[m_CurrentChairID].right-=1;
		}
		break;
	case 2:
		if(m_bFourPixel==TRUE)
		{
			m_ptTableID.x-=10;
			//m_ptTableID.y-=10;
		}
		else
		{
			m_ptTableID.x-=1;
			//m_ptTableID.y-=1;
		}
		break;
	case 3:
		if(m_bFourPixel==TRUE)
		{
			m_ptReady[m_CurrentChairID].x-=10;
		}
		else
		{
			m_ptReady[m_CurrentChairID].x-=1;
		}
		break;
	case 4:
		if(m_bFourPixel==TRUE)
		{
			m_ptLock.x-=10;
		}
		else
		{
			m_ptLock.x-=1;
		}
		break;
	}
	UpdateShow();
}

void CGameTableToolDlg::OnRight() 
{
	switch(m_CurrentItem)
	{
	case 0:
		if(m_bFourPixel==TRUE)
		{
			m_ptChair[m_CurrentChairID].x+=40;
			//m_ptChair[m_CurrentChairID].y+=40;
		}
		else
		{
			m_ptChair[m_CurrentChairID].x+=1;
			//m_ptChair[m_CurrentChairID].y+=1;
		}
		break;
	case 1:
		if(m_bFourPixel==TRUE)
		{
			m_rcName[m_CurrentChairID].left+=10;
			m_rcName[m_CurrentChairID].right+=10;
		}
		else
		{
			m_rcName[m_CurrentChairID].left+=1;
			m_rcName[m_CurrentChairID].right+=1;
		}
		break;
	case 2:
		if(m_bFourPixel==TRUE)
		{
			m_ptTableID.x+=10;
			//m_ptTableID.y+=10;
		}
		else
		{
			m_ptTableID.x+=1;
			//m_ptTableID.y+=1;
		}
		break;
	case 3:
		if(m_bFourPixel==TRUE)
		{
			m_ptReady[m_CurrentChairID].x+=10;
		}
		else
		{
			m_ptReady[m_CurrentChairID].x+=1;
		}
		break;
	case 4:
		if(m_bFourPixel==TRUE)
		{
			m_ptLock.x+=10;
		}
		else
		{
			m_ptLock.x+=1;
		}
		break;
	}
	UpdateShow();
}

void CGameTableToolDlg::OnDown() 
{
	switch(m_CurrentItem)
	{
	case 0:
		if(m_bFourPixel==TRUE)
		{
			//m_ptChair[m_CurrentChairID].x+=40;
			m_ptChair[m_CurrentChairID].y+=40;
		}
		else
		{
			//m_ptChair[m_CurrentChairID].x+=1;
			m_ptChair[m_CurrentChairID].y+=1;
		}
		break;
	case 1:
		if(m_bFourPixel==TRUE)
		{
			m_rcName[m_CurrentChairID].top+=10;
			m_rcName[m_CurrentChairID].bottom+=10;
		}
		else
		{
			m_rcName[m_CurrentChairID].top+=1;
			m_rcName[m_CurrentChairID].bottom+=1;
		}
		break;
	case 2:
		if(m_bFourPixel==TRUE)
		{
			//m_ptTableID.x+=10;
			m_ptTableID.y+=10;
		}
		else
		{
			//m_ptTableID.x+=1;
			m_ptTableID.y+=1;
		}
		break;
	case 3:
		if(m_bFourPixel==TRUE)
		{
			m_ptReady[m_CurrentChairID].y+=10;
		}
		else
		{
			m_ptReady[m_CurrentChairID].y+=1;
		}
		break;
	case 4:
		if(m_bFourPixel==TRUE)
		{
			m_ptLock.y+=10;
		}
		else
		{
			m_ptLock.y+=1;
		}
		break;
	}
	UpdateShow();
}

void CGameTableToolDlg::OnAddWidth() 
{
	switch(m_CurrentItem)
	{
	case 1:
		m_rcName[m_CurrentChairID].left-=1;
		m_rcName[m_CurrentChairID].right+=1;
		break;
	case 2:
		m_ptTableID.x-=1;
		m_ptTableID.y+=1;
		break;
	}
	UpdateShow();	
}

void CGameTableToolDlg::OnReduceWidth() 
{
	switch(m_CurrentItem)
	{
	case 1:
		m_rcName[m_CurrentChairID].left+=1;
		m_rcName[m_CurrentChairID].right-=1;
		break;
	case 2:
		m_ptTableID.x+=1;
		m_ptTableID.y-=1;
		break;
	}
	UpdateShow();	
}

void CGameTableToolDlg::OnAddHeight() 
{
	switch(m_CurrentItem)
	{
	case 1:
		m_rcName[m_CurrentChairID].top-=1;
		m_rcName[m_CurrentChairID].bottom+=1;
		break;
	case 2:
		m_ptTableID.x-=1;
		m_ptTableID.y+=1;
		break;
	}
	UpdateShow();	
}

void CGameTableToolDlg::OnReduceHeight() 
{
	switch(m_CurrentItem)
	{
	case 1:
		m_rcName[m_CurrentChairID].top+=1;
		m_rcName[m_CurrentChairID].bottom-=1;
		break;
	case 2:
		m_ptTableID.x+=1;
		m_ptTableID.y-=1;
		break;
	}
	UpdateShow();	
}

void CGameTableToolDlg::OnValignmetUp() 
{
	m_nDrawStyle[m_CurrentChairID]&=0x0F;
	m_nDrawStyle[m_CurrentChairID]|=NT_TOP;
	UpdateShow();	
}

void CGameTableToolDlg::OnValignmetDown() 
{
	m_nDrawStyle[m_CurrentChairID]&=0x0F;
	m_nDrawStyle[m_CurrentChairID]|=NT_BOTTOM;
	UpdateShow();	
}

void CGameTableToolDlg::OnValignmetCenter() 
{
	m_nDrawStyle[m_CurrentChairID]&=0x0F;
	m_nDrawStyle[m_CurrentChairID]|=NT_VCENTER;
	UpdateShow();	
}

void CGameTableToolDlg::OnHaveAccount() 
{
	// TODO: Add your control notification handler code here
	m_bHaveAccount=!m_bHaveAccount;
	UpdateShow();
}

void CGameTableToolDlg::OnHaveHead() 
{
	// TODO: Add your control notification handler code here
	m_bHaveHead=!m_bHaveHead;
	UpdateShow();
}

void CGameTableToolDlg::OnHaveLock() 
{
	// TODO: Add your control notification handler code here
	m_bHaveLock=!m_bHaveLock;
	UpdateShow();
}

void CGameTableToolDlg::OnFrameAccount() 
{
	// TODO: Add your control notification handler code here
	m_bFrameAccount=!m_bFrameAccount;
	UpdateShow();
}

void CGameTableToolDlg::OnFrameHead() 
{
	// TODO: Add your control notification handler code here
	m_bFrameHead=!m_bFrameHead;
	UpdateShow();
}

void CGameTableToolDlg::OnFrameTableno() 
{
	// TODO: Add your control notification handler code here
	m_bFrameTableNo=!m_bFrameTableNo;
	UpdateShow();
}

void CGameTableToolDlg::OnHalignmetRight() 
{
	m_nDrawStyle[m_CurrentChairID]&=0xF0;
	m_nDrawStyle[m_CurrentChairID]|=NT_RIGHT;
	UpdateShow();
}

void CGameTableToolDlg::OnHalignmetCenter() 
{
	m_nDrawStyle[m_CurrentChairID]&=0xF0;
	m_nDrawStyle[m_CurrentChairID]|=NT_CENTER;
	//AfxMessageBox(L"sss");
	UpdateShow();
}

void CGameTableToolDlg::OnHalignmetLeft() 
{
	m_nDrawStyle[m_CurrentChairID]&=0xF0;
	m_nDrawStyle[m_CurrentChairID]|=NT_LEFT;
	UpdateShow();
}

void CGameTableToolDlg::OnLocalLock() 
{
	// TODO: Add your control notification handler code here
	m_AddHeight.EnableWindow(false);
	m_AddWidth.EnableWindow(false);
	m_ReduceHeight.EnableWindow(false);
	m_ReduceWidth.EnableWindow(false);

	m_CurrentItem=4;
	
}

void CGameTableToolDlg::OnLocalHand() 
{
	// TODO: Add your control notification handler code here
	m_AddHeight.EnableWindow(false);
	m_AddWidth.EnableWindow(false);
	m_ReduceHeight.EnableWindow(false);
	m_ReduceWidth.EnableWindow(false);

	m_CurrentItem=3;
	
}

void CGameTableToolDlg::OnLocalTableno() 
{
	// TODO: Add your control notification handler code here
	m_AddHeight.EnableWindow(true);
	m_AddWidth.EnableWindow(true);
	m_ReduceHeight.EnableWindow(true);
	m_ReduceWidth.EnableWindow(true);

	m_CurrentItem=2;
	
}

void CGameTableToolDlg::OnLocalAccount() 
{
	// TODO: Add your control notification handler code here
	m_AddHeight.EnableWindow(true);
	m_AddWidth.EnableWindow(true);
	m_ReduceHeight.EnableWindow(true);
	m_ReduceWidth.EnableWindow(true);

	m_CurrentItem=1;
	
}

void CGameTableToolDlg::OnLocalHead() 
{
	// TODO: Add your control notification handler code here
	m_AddHeight.EnableWindow(false);
	m_AddWidth.EnableWindow(false);
	m_ReduceHeight.EnableWindow(false);
	m_ReduceWidth.EnableWindow(false);

	m_CurrentItem=0;
	
}

void CGameTableToolDlg::OnAccountColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog ColorDialog(m_crName,CC_FULLOPEN);
	if (ColorDialog.DoModal()==IDOK)
	{
		m_crName=ColorDialog.GetColor();
	}
	UpdateShow();
}

void CGameTableToolDlg::OnCbnSelendokSeatCount()
{
	int nSeatCount=m_SeatCount.GetCurSel();

	if(nSeatCount!=CB_ERR)
	{
		m_ChairCount=nSeatCount+1;
	}
	else
	{
		m_ChairCount=4;
	}
	m_CurrentSeat.ResetContent();
	for(int i=0;i<m_ChairCount;i++)
	{
		CString strSeatName;
		strSeatName.Format(TEXT("%d"),i+1);
		m_CurrentSeat.AddString(strSeatName);
	}
	m_CurrentChairID=0;
	m_CurrentSeat.SetCurSel(m_CurrentChairID);	
	UpdateShow();
}

void CGameTableToolDlg::OnCbnSelendokUserName()
{
	UpdateShow();
}

void CGameTableToolDlg::OnCbnSelendokCurrentSeat()
{
	int index=m_CurrentSeat.GetCurSel();
	m_CurrentChairID=index;

	//�޶����ƵĶ��뷽ʽ
	switch(m_nDrawStyle[m_CurrentChairID]&0x0F)
	{
	case NT_RIGHT:
		m_CurrentHAlignmet=2;
		break;
	case NT_CENTER:
		m_CurrentHAlignmet=1;
		break;
	case NT_LEFT:
		m_CurrentHAlignmet=0;
		break;
	}
	switch(m_nDrawStyle[m_CurrentChairID]&0xF0)
	{
	case NT_TOP:
		m_CurrentVAlignmet=0;
		break;
	case NT_VCENTER:
		m_CurrentVAlignmet=1;
		break;
	case NT_BOTTOM:
		m_CurrentVAlignmet=2;
		break;
	}
	UpdateData(false);

	UpdateShow();
}

void CGameTableToolDlg::OnBnClickedFourPixel()
{
	UpdateData(TRUE);
}
