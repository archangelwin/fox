#pragma once


// CDlgModifyPassword �Ի���

class CDlgModifyPassword : public CDialog, public CMissionItem
{
	DECLARE_DYNAMIC(CDlgModifyPassword)

	//��������
protected:
	bool							m_bLogonMission;					//�޸�����
	CMissionManager					m_MissionManager;					//�������

	CPngImage						m_ImageBack;

	//��������
protected:
	TCHAR							m_szSrcPassword[LEN_PASSWORD];		//�û�����
	TCHAR							m_szDesPassword[LEN_PASSWORD];		//�û�����

	//�ؼ�����
protected:
	CEdit							m_edLogonPassword1;					//�ʺ�����
	CEdit							m_edLogonPassword2;					//�ʺ�����
	CEdit							m_edLogonPassword3;					//�ʺ�����

	//�ؼ�����
protected:
	CSkinButton						m_btLogonPassword;					//�޸İ�ť

public:
	CDlgModifyPassword();   // ��׼���캯��
	virtual ~CDlgModifyPassword();

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

	//��Ϣӳ��
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//��������
	VOID OnEnChangeLogonPassword();
	//�����޸�
	VOID OnBnClickedLogonPassword();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	DECLARE_MESSAGE_MAP()
};
