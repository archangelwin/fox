#ifndef MISSION_LOGON_HEAD_FILE
#define MISSION_LOGON_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgLogon.h"
#include "DlgStatus.h"
#include "DlgRegister.h"

//////////////////////////////////////////////////////////////////////////
//ע������
#define CHECK_NULL              0
#define CHECK_ACCOUNT           1
#define CHECK_NICK              2

//////////////////////////////////////////////////////////////////////////////////

//��¼����
class CMissionLogon : public CDlgStatus, public CMissionItem, public IStatusViewSink
{
	//��Ԫ����
	friend class CDlgLogon;
	friend class CDlgRegister;

	//��������
protected:
	bool							m_bRegister;						//ע���־
	bool							m_bRemPassword;						//��ס����
	bool                            m_bLowVerValidate;                  //�Ͱ汾Ч��
	BYTE                            m_bRegisterCheck;                   //��½���

	//�ؼ�ָ��
protected:
	CDlgLogon *						m_pDlgLogon;						//��¼����
	CDlgRegister *					m_pDlgRegister;						//ע�ᴰ��

	//��̬����
protected:
	static CMissionLogon *			m_pMissionLogon;					//����ָ��

	//��������
public:
	//���캯��
	CMissionLogon();
	//��������
	virtual ~CMissionLogon();

	//״̬�ӿ�
public:
	//ȡ������
	virtual VOID OnStatusCancel();

	//���غ���
public:
	//�����¼�
	virtual bool OnEventMissionLink(INT nErrorCode);
	//�ر��¼�
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);

	//���ܺ���
public:
	//��ʾ��¼
	VOID ShowLogon();
	//��ʾע��
	VOID ShowRegister();
	//������Ϣ
	bool SendLogonPacket(BYTE cbValidateFlags);
	//���ͼ���
	bool SendCheckPacket();

	//��������
protected:
	//�����û�
	VOID UpdateUserInfo();
	//ִ�е�¼
	bool PerformLogonMission(bool bRemPassword,BYTE cbRegisterCheck = 0);

	//�����¼�
protected:
	//������Ϣ
	bool OnSocketSubLogonNeedExtern(VOID * pData, WORD wDataSize);
	//��¼�ɹ�
	bool OnSocketSubLogonSuccess(VOID * pData, WORD wDataSize);
	//��¼ʧ��
	bool OnSocketSubLogonFailure(VOID * pData, WORD wDataSize);
	//��¼���
	bool OnSocketSubLogonFinish(VOID * pData, WORD wDataSize);
	//������ʾ
	bool OnSocketSubUpdateNotify(VOID * pData, WORD wDataSize);
	//��¼ʧ��
	bool OnSocketSubLogonValidateMBCard(VOID * pData, WORD wDataSize);
	//ע������
	bool OnSocketRegisterResult(VOID * pData, WORD wDataSize);

	//��̬����
public:
	//��ȡ����
	static CMissionLogon * GetInstance() { return m_pMissionLogon; }

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif