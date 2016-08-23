#pragma once


// CInsureLogon �Ի���

class CInsureLogon : public CDialog, public CMissionItem,public IKeyBoardSink
{
	DECLARE_DYNAMIC(CInsureLogon)

public:
	CInsureLogon(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInsureLogon();

protected:
	CPngImage			m_ImageBack;

	TCHAR				m_szInsurePassword[LEN_PASSWORD];

	CSkinButton			m_btClose;
	CSkinButton			m_btOk;
	CSkinButton			m_btCancle;
	CEdit				m_edInsurePassword;				//��������

	CPasswordKeyboard2	m_KeyBoard;

	//�������
protected:
	CMissionManager					m_MissionManager;					//�������

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual	VOID OnKeyBoardChar(WORD wChar);
	virtual	VOID OnKeyBoardClean();

	VOID OnBnClickedOk();

	//���غ���
public:
	//�����¼�
	virtual bool OnEventMissionLink(INT nErrorCode);
	//�ر��¼�
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
