#include "Stdafx.h"
#include "GamePlaza.h"
#include "PlatformFrame.h"
#include "WndLasPlaytGame.h"

//////////////////////////////////////////////////////////////////////////////////

#define SHOW_LAST_COUNT				3

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CWndLastGamePlay, CWnd)

	//ϵͳ��Ϣ
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()

	//�Զ���Ϣ
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////

//���캯��
CWndLastGamePlay::CWndLastGamePlay()
{
	//״̬��־
	m_bClickFace=false;
	m_bMouseEvent=false;

	//������־
	m_bHoverFace=false;
	//��������
	m_rcFaceArea.SetRect(0,0,0,0);

	return;
}

//��������
CWndLastGamePlay::~CWndLastGamePlay()
{
}

//������Ϣ
INT CWndLastGamePlay::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;


	m_ImgType.LoadFromResource(AfxGetInstanceHandle(),IDB_SERVER_TYPE);

	m_ImgArrow.LoadImage(AfxGetInstanceHandle(),TEXT("TYPE_ARROW"));

	m_rcFaceArea.SetRect(0,0,m_ImgType.GetWidth()/3,m_ImgType.GetHeight());

	//��������
	m_FontBold.CreateFont(-12,0,0,0,600,0,0,0,134,3,2,ANTIALIASED_QUALITY,2,TEXT("����"));

	//�ƶ�����
	CRect rcUserInfo;
	GetWindowRect(&rcUserInfo);
	SetWindowPos(NULL,0,0,rcUserInfo.Width(),112,SWP_NOMOVE|SWP_NOZORDER);


	return 0;
}

//��ԴĿ¼
VOID CWndLastGamePlay::GetGameResDirectory(TCHAR szProcessName[], TCHAR szResDirectory[], WORD wBufferCount)
{
	//��������
	WORD wStringIndex=0;

	//����Ŀ¼
	ZeroMemory(szResDirectory,wBufferCount*sizeof(TCHAR));
	lstrcpyn(szResDirectory,szProcessName,wBufferCount);
	while ((szResDirectory[wStringIndex]!=0)&&(szResDirectory[wStringIndex]!=TEXT('.'))) wStringIndex++;

	//�ַ���ֹ
	szResDirectory[wStringIndex]=0;

	return;
}

//�滭����
BOOL CWndLastGamePlay::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	if(ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32) == FALSE) return TRUE;

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	pBufferDC->FillSolidRect(&rcClient,RGB(234,242,247));

	INT nTypeWidth=m_ImgType.GetWidth()/3,nTypeHeight=m_ImgType.GetHeight();
	INT nArrowWidth=m_ImgArrow.GetWidth()/2,nArrowHeight=m_ImgArrow.GetHeight();

	INT nIndex=0;
	if(m_bHoverFace) nIndex=2;
	if(m_bClickFace) nIndex=1;

	m_ImgType.BitBlt(pBufferDC->GetSafeHdc(),0,0,nTypeWidth,nTypeHeight,nIndex*nTypeWidth,0);
	m_ImgArrow.DrawImage(pBufferDC,6,6,nArrowWidth,nArrowHeight,nArrowWidth,0);

	//���û���
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(m_FontBold);
	pBufferDC->SetTextColor(RGB(13,61,88));
	//pBufferDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());
	pBufferDC->TextOut(21,5,TEXT("�����Ϸ"));

	//���������Ϸ
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	ZeroMemory(m_LastGame,sizeof(m_LastGame));
	int iLastGameCount=0;
	int iSpace=13;
	POSITION pos=m_LastPlayGameList.GetHeadPosition();
	while(pos!=NULL)
	{
		WORD wServerID=m_LastPlayGameList.GetNext(pos);
		CGameServerItem* pServerItem=CPlatformFrame::GetInstance()->SearchGameServer(wServerID);
		if(pServerItem!=NULL)
		{
			TCHAR szResDirectory[LEN_KIND]=TEXT("");
			GetGameResDirectory(pServerItem->m_pGameKindItem->m_GameKind.szProcessName,szResDirectory,CountArray(szResDirectory));

			TCHAR szIconPath[MAX_PATH]=TEXT("");
			//_sntprintf(szIconPath,CountArray(szIconPath),TEXT("%s\\GameKind\\Icon_%s.png"),szDirectory,szResDirectory);
			_sntprintf(szIconPath,CountArray(szIconPath),TEXT("%s\\GameKind\\GK_%d.png"),szDirectory,pServerItem->m_GameServer.wKindID);

			CPngImage ImageIcon;
			if(ImageIcon.LoadImage(szIconPath)!=true)
			{
				ImageIcon.LoadImage(AfxGetInstanceHandle(),TEXT("ICON_DEFAULT"));
			}

           //�޸�ͼƬ����������
			//INT nXPos=15+iLastGameCount*(ImageIcon.GetWidth()+15);
			//ImageIcon.DrawImage(pBufferDC,nXPos,24);

			//CRect rcText(nXPos,102-8,nXPos+70,132-8);
			//pBufferDC->DrawText(pServerItem->m_GameServer.szServerName,rcText,DT_CENTER|DT_SINGLELINE|DT_WORDBREAK);

			//m_LastGame[iLastGameCount].bActive=true;
			//m_LastGame[iLastGameCount].wServerID=wServerID;
			//m_LastGame[iLastGameCount].rcArea.left=nXPos+4;
			//m_LastGame[iLastGameCount].rcArea.top=22;
			//m_LastGame[iLastGameCount].rcArea.right=nXPos+70;
			//m_LastGame[iLastGameCount].rcArea.bottom=130;

			INT nXPos=15+iLastGameCount*(ImageIcon.GetWidth()+15);
			ImageIcon.DrawImage(pBufferDC,nXPos,230-198);

			CRect rcText(nXPos,230+70-198,nXPos+70,230+100-198);
			//pBufferDC->DrawText(pServerItem->m_GameServer.szServerName,rcText,DT_CENTER|DT_SINGLELINE|DT_WORDBREAK);

			m_LastGame[iLastGameCount].bActive=true;
			m_LastGame[iLastGameCount].wServerID=wServerID;
			m_LastGame[iLastGameCount].rcArea.left=nXPos+4;
			m_LastGame[iLastGameCount].rcArea.top=130;
			m_LastGame[iLastGameCount].rcArea.right=nXPos+4+66;
			m_LastGame[iLastGameCount].rcArea.bottom=130+86;

			iLastGameCount++;
		}
	}



	//���û���
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//���ؼ�¼
void CWndLastGamePlay::LoadLastPlayGame()
{
	//����Ŀ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//����·��
	TCHAR szFileName[MAX_PATH]={0};
	_sntprintf(szFileName,CountArray(szFileName),TEXT("%s\\ConstantlyPlayGame.wh"),szDirectory);

	//��ȡ�ļ�
	CFile file;
	if(file.Open(szFileName, CFile::modeRead))
	{
		//��ȡ����
		char buffer[128]={0};
		UINT uReadCount=file.Read(buffer, CountArray(buffer));
		uReadCount /= 2;

		//�����¼
		WORD *pServerIDArry = (WORD *)buffer;
		for(BYTE i=0; i<uReadCount; i++)
		{
			if(pServerIDArry[i]>0) m_LastPlayGameList.AddHead(pServerIDArry[i]);
		}

		//�ر��ļ�
		file.Close();
	}

	return;
}

//�����¼
void CWndLastGamePlay::SaveLastPlayGame()
{
	//����Ŀ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//����·��
	TCHAR szFileName[MAX_PATH]={0};
	_sntprintf(szFileName,CountArray(szFileName),TEXT("%s\\ConstantlyPlayGame.wh"),szDirectory);

	//д���ļ�
	CFile file;
	if(file.Open(szFileName, CFile::modeCreate|CFile::modeWrite))
	{
		//��������
		POSITION Position=m_LastPlayGameList.GetHeadPosition();
		WORD wServerIDArry[SHOW_LAST_COUNT]={0};
		for(BYTE i=0; i<SHOW_LAST_COUNT; i++)
		{
			if(Position == NULL) break;

			wServerIDArry[i]=m_LastPlayGameList.GetNext(Position);
		}

		//д������
		file.Write(wServerIDArry, sizeof(wServerIDArry));

		//�ر��ļ�
		file.Close();
	}

	return;
}

//��������Ϸ
void CWndLastGamePlay::AddLastPlayGame(WORD wServerID)
{
	//���Ҽ�¼
	POSITION Position=m_LastPlayGameList.GetHeadPosition();
	while(Position != NULL)
	{
		POSITION temppos=Position;
		if(m_LastPlayGameList.GetNext(Position) == wServerID)
		{
			m_LastPlayGameList.RemoveAt(temppos);
			break;
		}
	}

	//��¼��Ϸ
	m_LastPlayGameList.AddHead(wServerID);

	//ɾ������
	if(m_LastPlayGameList.GetCount() > SHOW_LAST_COUNT)
	{
		//ɾ����¼
		WORD wDeleServerID=m_LastPlayGameList.GetTail();
		m_LastPlayGameList.RemoveTail();
	}

	return;
}


//�����Ϣ
VOID CWndLastGamePlay::OnLButtonUp(UINT nFlags, CPoint MousePoint)
{
	__super::OnLButtonUp(nFlags,MousePoint);

	if ((m_bHoverFace==true)&&(m_bClickFace==true))
	{
		//�ͷŲ���
		ReleaseCapture();

		//���ñ���
		m_bClickFace=false;

		//������Ϣ
		if (m_rcFaceArea.PtInRect(MousePoint)==TRUE)
		{
			RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
		}
	}

	return;
}

//�����Ϣ
VOID CWndLastGamePlay::OnLButtonDown(UINT nFlags, CPoint MousePoint)
{
	__super::OnLButtonDown(nFlags,MousePoint);

	//���ý���
	SetFocus();

	//��������
	if ((m_bHoverFace==true)&&(m_bClickFace==false))
	{
		//����˻�
		SetCapture();

		//���ñ���
		m_bClickFace=true;

		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	for(int i=0; i<3; i++)
	{
		if(m_LastGame[i].bActive!=true) continue;

		if(m_LastGame[i].rcArea.PtInRect(MousePoint))
		{
			CGameServerItem* pServerItem=CPlatformFrame::GetInstance()->SearchGameServer(m_LastGame[i].wServerID);
			CPlatformFrame::GetInstance()->EntranceServerItem(pServerItem);
		}
	}

	return;
}

//�����Ϣ
BOOL CWndLastGamePlay::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//��ȡ���
	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(&MousePoint);

	//��������
	bool bMouseEvent=false;
	bool bRedrawWindow=false;

	//�����ж�
	if ((m_bHoverFace==false)&&(m_rcFaceArea.PtInRect(MousePoint)==TRUE))
	{
		//���ñ���
		bMouseEvent=true;
		bRedrawWindow=true;

		//���ñ���
		m_bHoverFace=true;
	}

	//�뿪�ж�
	if ((m_bHoverFace==true)&&(m_rcFaceArea.PtInRect(MousePoint)==FALSE))
	{
		//���ñ���
		bRedrawWindow=true;

		//���ñ���
		m_bHoverFace=false;
	}


	//ע���¼�
	if ((m_bMouseEvent==false)&&(bMouseEvent==true))
	{
		//���ñ���
		m_bMouseEvent=true;

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

	//���½���
	if (bRedrawWindow==true)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	//���ù��
	if (m_bHoverFace==true)
	{
		SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_HAND_CUR)));
		return true;
	}

	for(int i=0; i<3; i++)
	{
		if(m_LastGame[i].bActive!=true) continue;

		if(m_LastGame[i].rcArea.PtInRect(MousePoint))
		{
			SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_HAND_CUR)));
			return true;
		}
	}

	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

//�����Ϣ
LRESULT CWndLastGamePlay::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	//���ñ���
	m_bMouseEvent=false;

	//�뿪����
	if (m_bHoverFace==true)
	{
		//���ñ���
		m_bMouseEvent=false;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
