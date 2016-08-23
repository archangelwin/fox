#ifndef DLG_SERVICE_HEAD_FILE
#define DLG_SERVICE_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgServiceItem.h"
#include "DlgServicePassword.h"
#include "DlgServiceIndividual.h"
#include "DlgModifyPassword.h"
#include "DlgLockMachine.h"
//////////////////////////////////////////////////////////////////////////////////

//�û�����
#define SERVICE_ACCOUNTS			1									//�޸�����
#define SERVICE_INDIVIDUAL			2									//��������
#define SERVICE_PASSWORD			3									//�޸�����
#define SERVICE_PASSPROTECT			4									//���뱣��
#define SERVICE_SECURITY			5									//��ȫ����
#define SERVICE_MEMBER_PAYMENT		6									//��Ա��ֵ

//��Ա����
#define SERVICE_GAME_RECORD			10									//��Ϸ��¼
#define SERVICE_PAY_RECORD			11									//��ֵ��¼
#define SERVICE_CLEAN_FLEE			12									//��������
#define SERVICE_CLEAN_SCORE			13									//��������
#define SERVICE_MEMBER_INFO			14									//��Ա����

//////////////////////////////////////////////////////////////////////////////////

//����˵��
typedef CWHArray<CDlgServiceItem *> CDlgServiceItemArray;

//////////////////////////////////////////////////////////////////////////////////

//ѡ�����
class CDlgServiceBar : public CWnd
{
	//���Ϣ
protected:
	bool							m_bHovering;						//������־
	WORD							m_wItemDown;						//��������
	WORD							m_wItemHover;						//��������
	WORD							m_wItemActive;						//��������

	//������Ϣ
protected:
	CSize							m_SizeButton;						//��ť��С
	CRect							m_rcItemCreate;						//����λ��
	CDlgServiceItemArray			m_DlgServiceItemArray;				//��������

	//��������
public:
	//���캯��
	CDlgServiceBar();
	//��������
	virtual ~CDlgServiceBar();

	//���غ���
public:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//���ܺ���
public:
	//��������
	bool SetItemCreateRect(CRect rcItemCreate);
	//��������
	bool InsertServiceItem(CDlgServiceItem * pDlgServiceItem);
	//��������
	bool SetActiveServiceItem(CDlgServiceItem * pDlgServiceItem);

	//�ڲ�����
private:
	//�����л�
	WORD SwitchToButtonIndex(CPoint MousePoint);

	//��Ϣ����
protected:
	//�ػ���Ϣ
	VOID OnPaint();
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//����ƶ�
	VOID OnMouseMove(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//����뿪
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	//�����Ϣ
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

//����ר��
class CDlgService : public CDialog
{
	//�������
public:
	CPngImage						m_ImageBack;
	CSkinButton						m_btClose;
	CSkinTabCtrl					m_TabControl;						//
	CDlgModifyPassword				m_DlgServicePassword;				//�޸�����
	CDlgServiceIndividual			m_DlgServiceIndividual;				//��������
	CDlgLockMachine					m_DlgLockMachine;					//����

	WORD							m_wInitPage;

	//��������
public:
	//���캯��
	CDlgService();
	//��������
	virtual ~CDlgService();

	//���غ���
protected:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ����Ϣ
	virtual VOID OnOK();
	//
		
	//�滭��Ϣ
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);

	//���ܺ���
public:
	VOID SetInitPage(WORD wPage) { m_wInitPage=wPage;} ;
	VOID ShowIndividualPage();
	VOID ShowPasswordPage();
	VOID ShowLockMachine();
	VOID OnTcnSelchangeLogonMode(NMHDR * pNMHDR, LRESULT * pResult);
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//
	void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
};

//////////////////////////////////////////////////////////////////////////////////

#endif