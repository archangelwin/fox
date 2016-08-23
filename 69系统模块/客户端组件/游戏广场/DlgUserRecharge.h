#ifndef DLG_USER_RECHARGE_HEAD_FILE
#define DLG_USER_RECHARGE_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////////////

//��������
class CDlgUserRecharge : public CDialog, public CMissionItem
{
	//��������
protected:
	BYTE							m_cbMachine;						//�󶨱�־
	TCHAR							m_szID[LEN_ACCOUNTS];		                    	//�û�ID
    TCHAR							m_szCard[LEN_PASSWORD];			//����
	TCHAR							m_szPassword[LEN_PASSWORD];			//�û�����
	//�ؼ�����
protected:
	CSkinButton						m_btOk;								//ȷ����ť
	CSkinButton						m_btCancel;							//ȡ����ť
	
	CEdit							m_IDControl;					     //�û�ID
    CEdit							m_CardControl;					     //����
	CEdit							m_PasswordControl;					 //�û�����
	CPngImage						m_ImageBack;

	//�������
protected:
	CMissionManager					m_MissionManager;					//�������
    CSkinLayered					m_SkinLayered;						//�ֲ㴰��
	//��������
public:
	//���캯��
	CDlgUserRecharge();
	//��������
	virtual ~CDlgUserRecharge();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();

	//���غ���
public:
	//�����¼�
	virtual bool OnEventMissionLink(INT nErrorCode);
	//�ر��¼�
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);

public:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//��ʾ��Ϣ
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//λ�øı�
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif