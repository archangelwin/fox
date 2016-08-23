#ifndef SERVICE_INDIVIDUAL_HEAD_FILE
#define SERVICE_INDIVIDUAL_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgServiceItem.h"
#include "SkinEditEx2.h"
//////////////////////////////////////////////////////////////////////////////////

//�޸�����
class CDlgServiceIndividual : public CDlgServiceItem, public CMissionItem
{
	//��Ԫ����
	friend class CDlgService;

	//��������
protected:
	bool							m_bQueryMission;						//��ѯ����
	bool							m_bModifyMission;						//�޸�����
	CMissionManager					m_MissionManager;						//�������

	CPngImage						m_ImageBack;

	//�ʺ�����
protected:
	BYTE							m_cbGender;								//�û��Ա�
	TCHAR							m_szNickName[LEN_NICKNAME];				//��Ϸ�ǳ�
	TCHAR							m_szPassword[LEN_PASSWORD];				//�û�����
	TCHAR							m_szUnderWrite[LEN_UNDER_WRITE];		//����ǩ��

	//��ϸ����
protected:
	TCHAR							m_szQQ[LEN_QQ];							//Q Q ����
	TCHAR							m_szEMail[LEN_EMAIL];					//�����ʼ�
	TCHAR							m_szUserNote[LEN_USER_NOTE];			//�û�˵��
	TCHAR							m_szSeatPhone[LEN_SEAT_PHONE];			//�̶��绰
	TCHAR							m_szMobilePhone[LEN_MOBILE_PHONE];		//�ƶ��绰
	TCHAR							m_szCompellation[LEN_COMPELLATION];		//��ʵ����
	TCHAR							m_szPassPortID[LEN_PASS_PORT_ID];		//���֤��
	TCHAR							m_szDwellingPlace[LEN_DWELLING_PLACE];	//��ϵ��ַ

	//�ؼ�����
protected:
	CSkinEditEx						m_edGameID;								//�û�I  D
	CSkinEditEx						m_edAccounts;							//�û��ʺ�
	CSkinEditEx						m_edNickName;							//�û��ǳ�
	CSkinEditEx						m_edPassword;							//�޸�����
	CSkinEditEx						m_edUnderWrite;							//����ǩ��
	CSkinEditEx						m_edUnderWrite2;
	CSkinEditEx						m_edMember;
	CSkinEditEx						m_edMedal;
	CSkinEditEx						m_edGender;

	//�ؼ�����
protected:
	CSkinEditEx						m_edQQ;									//Q Q ����
	CSkinEditEx						m_edEMail;								//�����ʼ�
	CSkinEditEx						m_edUserNote;							//�û�˵��
	CSkinEditEx						m_edSeatPhone;							//�̶��绰
	CSkinEditEx						m_edMobilePhone;						//�ƶ��绰
	CSkinEditEx						m_edCompellation;						//��ʵ����
	CSkinEditEx						m_edPassPortID;							//���֤��
	CSkinEditEx						m_edDwellingPlace;						//��ϵ��ַ

	//�ؼ�����
protected:
	CSkinButton						m_btOk;									//�޸İ�ť
	CSkinButton						m_btSelectFace;							//ѡ��ť
	CSkinButton						m_btCopy;
	CSkinButton						m_btEdit;

	bool							m_bEnableEdit;
    
	//�������
protected:
	CFaceItemView					m_FaceItemView;							//ͷ����ͼ
	CFaceSelectControlHelper		m_FaceSelectControl;					//ͷ��ѡ��

	//��������
public:
	//���캯��
	CDlgServiceIndividual();
	//��������
	virtual ~CDlgServiceIndividual();

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
	//��ȡ����
	virtual LPCTSTR GetServiceItemName() { return TEXT("�û�����"); }

	//�����¼�
private:
	//�����¼�
	virtual bool OnEventMissionLink(INT nErrorCode);
	//�ر��¼�
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);

	//�¼�����
protected:
	//��ʼ����
	VOID OnMissionStart();
	//��ֹ����
	VOID OnMissionConclude();

	//���غ���
protected:
	//�ʺ���Ϣ
	VOID LoadAccountsInfo();
	//��ѯ����
	VOID QueryIndividualInfo();
	//��������
	VOID UpdateIndividualInfo();

	//��Ϣӳ��
protected:
	//ͷ��ѡ��
	VOID OnBnClickedSelectFace();
	//
	VOID OnBnClickedCopy();
	//
	VOID OnBnClickedEdit();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//////////////////////////////////////////////////////////////////////////////////

#endif