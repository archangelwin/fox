#ifndef PASSWORD_CONTROLEX_HEAD_FILE
#define PASSWORD_CONTROLEX_HEAD_FILE

#pragma once

#include "ShareControlHead.h"

interface IKeyBoardSink
{
	virtual VOID OnKeyBoardChar(WORD wChar)=NULL;
	virtual VOID OnKeyBoardClean()=NULL;
};

//////////////////////////////////////////////////////////////////////////////////

//�������
class SHARE_CONTROL_CLASS CPasswordKeyboard2 : public CDialog
{
	//���ñ���
protected:
	INT								m_nRandLine[3];						//�������
	INT								m_nItemCount[3];					//�ַ���Ŀ
	TCHAR							m_szKeyboradChar[3][2][15];			//�����ַ�

	//����״̬
protected:
	bool							m_bCapsLockStatus;					//����״̬

	//״̬����
protected:
	WORD							m_wHoverRow;						//��������
	WORD							m_wHoverLine;						//��������
	bool							m_bMouseDown;						//����״̬

	IKeyBoardSink*					m_pKeyBoardSink;

	//��Դ��С
protected:
	CSize							m_SizeImageItem1;					//��Դ��С
	CSize							m_SizeImageItem2;					//��Դ��С
	CSize							m_SizeBackGround;					//������С

	//��������
public:
	//���캯��
	CPasswordKeyboard2();
	//��������
	virtual ~CPasswordKeyboard2();

	VOID SetKeyBoardSink(IKeyBoardSink* pSink);

	//���غ���
protected:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK() { return; }
	//ȡ����Ϣ
	virtual VOID OnCancel() { return; }

	//��������
protected:
	//����λ��
	VOID SetCurrentStation(CPoint MousePoint);
	//�������
	WORD GetVirualKeyCode(WORD wHoverLine, WORD wHoverRow);

	//��Ϣ����
protected:
	//����滭
	VOID OnNcPaint();
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//ʧȥ����
	VOID OnKillFocus(CWnd * pNewWnd);
	//�����Ϣ
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//�����Ϣ
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif