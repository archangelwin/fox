#ifndef WND_LAST_PLAY_HEAD_FILE
#define WND_LAST_PLAY_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////////////

struct tagLastGameItem
{
	CRect rcArea;
	bool  bActive;
	WORD  wServerID;
};


//////////////////////////////////////////////////////////////////////////////////

//�û���Ϣ
class CWndLastGamePlay : public CWnd
{
	//״̬����
protected:
	bool							m_bClickFace;						//�����־
	bool							m_bMouseEvent;						//ע���־

	tagLastGameItem					m_LastGame[3];

	CLastGameServerList             m_LastPlayGameList;                 //��������Ϸ

	//������־
protected:
	bool							m_bHoverFace;						//������־

	CBitImage						m_ImgType;
	CPngImage						m_ImgArrow;

	CFont							m_FontBold;							//��������

	//����λ��
protected:
	CRect							m_rcFaceArea;						//ͷ������

	//��������
public:
	//���캯��
	CWndLastGamePlay();
	//��������
	virtual ~CWndLastGamePlay();

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�����Ϣ
	VOID OnLButtonUp(UINT nFlags, CPoint MousePoint);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint MousePoint);
	//�����Ϣ
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	//��Ϸ��¼
public:
	//���ؼ�¼
	void LoadLastPlayGame();
	//�����¼
	void SaveLastPlayGame();
	//��������Ϸ
	void AddLastPlayGame(WORD wServerID);
	//
	VOID GetGameResDirectory(TCHAR szProcessName[], TCHAR szResDirectory[], WORD wBufferCount);

	//�Զ���Ϣ
protected:
	//����뿪
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif