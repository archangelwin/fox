#ifndef DLG_INSURE_COUNTER_HEAD_FILE
#define DLG_INSURE_COUNTER_HEAD_FILE

#pragma once

#include "MissionManager.h"
#include "PasswordControl.h"
#include "WebPublicize.h"
#include "ShareControlHead.h"
#include "PasswordControlEx.h"
//////////////////////////////////////////////////////////////////////////////////

//��˵��
class CDlgInsureItem;
class CDlgInsureMain;
class CDlgInsureSave;

//////////////////////////////////////////////////////////////////////////////////

//������ʽ
#define INSURE_SAVE					2									//��ȡ��ʽ
#define INSURE_TRANSFER				0									//ת�˷�ʽ
#define INSURE_PASSWORD				3									//�����޸�
#define INSURE_RECORD				1									//���ͼ�¼
//////////////////////////////////////////////////////////////////////////////////

//������Ϣ
struct tagUserInsureInfo
{
	WORD							wRevenueTake;						//˰�ձ���
	WORD							wRevenueTransfer;					//˰�ձ���
	WORD							wServerID;							//�����ʶ
	SCORE							lUserScore;							//�û���Ϸ��
	SCORE							lUserInsure;						//������Ϸ��
	SCORE							lTransferPrerequisite;				//ת������
};

//ת����Ϣ
struct tagTransInfo
{
	DWORD							dwSrcGameID;
	DWORD							dwTagGameID;
    
	TCHAR							szSrcNickName[LEN_NICKNAME];
	TCHAR							szTagNickName[LEN_NICKNAME];

	SCORE							lScore;
};
//////////////////////////////////////////////////////////////////////////////////

//���нӿ�
interface IInsureCounterAction
{
	//��ѯ�¼�
	virtual VOID PerformQueryInfo()=NULL;
	//�����¼�
	virtual VOID PerformSaveScore(SCORE lSaveScore)=NULL;
	//ȡ���¼�
	virtual VOID PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass)=NULL;
	//�޸�����
	virtual VOID PerformModifyInsurePassword(LPCTSTR szSrcPassword, LPCTSTR szDesPassword)=NULL;
	//ת���¼�
	virtual VOID PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass)=NULL;
};

//////////////////////////////////////////////////////////////////////////////////

//ҳ������
class CDlgInsureItem
{
	//��������
public:
	//���캯��
	CDlgInsureItem();
	//��������
	virtual ~CDlgInsureItem();

	//���ܺ���
public:
	//��ȡ��Ϸ��
	SCORE GetUserControlScore(CWnd * pWndScore);

	//���ܺ���
public:
	//�滭����
	VOID DrawNumberString(CDC * pDC, SCORE lScore, INT nXPos, INT nYPos);
	//ת���ַ�
	VOID SwitchScoreString(SCORE lScore, LPTSTR pszBuffer, WORD wBufferSize);
	//ת���ַ�
	VOID SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize);
};

//////////////////////////////////////////////////////////////////////////////////

//���׼�¼
class CDlgInsureRecord : public CDialog
{
public:
	CDlgInsureRecord();
	virtual ~CDlgInsureRecord();

protected:
	CWebPublicize		m_WebRecord;

protected:
	//ȷ����ť
	virtual VOID OnOK();
	//ȡ����ť
	virtual VOID OnCancel();


	DECLARE_MESSAGE_MAP()	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

//////////////////////////////////////////////////////////////////////////////////
//��ȡ��Ϸ��
class CDlgInsureSave : public CDialog
{
	//��Ԫ����
	friend class CDlgInsureMain;

	//��������
protected:
	bool							m_bSwitchIng;						//ת����־
	CSkintDPI                       m_SkinDPI;                          //����DPI
	CBitImage						m_ImageBack;

	//����ָ��
protected:
	CDlgInsureMain *				m_pDlgInsureMain;					//����ָ��
	tagUserInsureInfo *				m_pUserInsureInfo;					//�û���Ϣ

	//�ؼ�����
public:
	CSkinEditEx						m_edScore;							//������Ϸ��
	CSkinButton						m_btTakeScore;						//ȡ�ť
	CSkinButton						m_btSaveScore;						//��ť

	//�����ؼ�
public:
	CSkinHyperLink					m_ForgetInsure;						//��������
	CDlgInsureItem					m_DlgInsureItem;					//��������
	CPasswordControl				m_PasswordControl;					//�û�����
	CSkinHyperLink					m_bt100W;
	CSkinHyperLink					m_bt500W;
	CSkinHyperLink					m_bt1000W;
	CSkinHyperLink					m_bt5000W;
	CSkinHyperLink					m_bt1Y;
	CSkinHyperLink					m_bt5Y;
	CSkinHyperLink					m_btAllInsure;
	CSkinHyperLink					m_btAllScore;;


	//��������
public:
	//���캯��
	CDlgInsureSave();
	//��������
	virtual ~CDlgInsureSave();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ����ť
	virtual VOID OnOK();
	//ȡ����ť
	virtual VOID OnCancel();

	//�ؼ�����
protected:
	//������Ϣ
	VOID OnEnChangeScore();
	//��ť
	VOID OnBnClickedSaveScore();
	//ȡ�ť
	VOID OnBnClickedTakeScore();
	//��������
	VOID OnBnClickedForgetInsure();
	//
	VOID OnBnClickedScore(UINT nID);

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////
//ת�˽��

class CDlgTransferResult : public CSkinDialog
{
public:
	CDlgTransferResult();
	virtual ~CDlgTransferResult();

protected:
	CBitImage			   m_ImageBk;

	CDlgInsureItem			m_DlgInsureItem;					//��������

	tagTransInfo		   *m_pTransInfo;
    
protected:
	//ȷ����ť
	virtual VOID OnOK();
	//�滭��Ϣ
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);

public:
	VOID SetTransInfo(tagTransInfo* pInfo);


	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

//////////////////////////////////////////////////////////////////////////////////

//ת�˽�
class CDlgInsureTransfer : public CDialog
{
	//��Ԫ����
	friend class CDlgInsureMain;

	//��������
protected:
	bool							m_bSwitchIng;						//ת����־
	CSkintDPI                       m_SkinDPI;                          //����DPI
	CBitImage						m_ImageBack;

	//����ָ��
protected:
	CDlgInsureMain *				m_pDlgInsureMain;					//����ָ��
	tagUserInsureInfo *				m_pUserInsureInfo;					//�û���Ϣ

	//�ؼ�����
public:
	CSkinEditEx						m_edScore;							//������Ϸ��
	CSkinEditEx						m_edNickName;						//�û��ǳ�
	CSkinButton						m_btTransferScore;					//ת�˰�ť

	//�����ؼ�
public:
	CSkinHyperLink					m_ForgetInsure;						//��������
	CDlgInsureItem					m_DlgInsureItem;					//��������
	CPasswordControl				m_PasswordControl;					//�û�����

	CSkinHyperLink					m_bt100W;
	CSkinHyperLink					m_bt500W;
	CSkinHyperLink					m_bt1000W;
	CSkinHyperLink					m_bt5000W;
	CSkinHyperLink					m_bt1Y;
	CSkinHyperLink					m_bt5Y;

	//��������
public:
	//���캯��
	CDlgInsureTransfer();
	//��������
	virtual ~CDlgInsureTransfer();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ����ť
	virtual VOID OnOK();
	//ȡ����ť
	virtual VOID OnCancel();

	//�ؼ�����
protected:
	//������Ϣ
	VOID OnEnChangeScore();
	//������Ϣ
	VOID OnEnChangeNick();
	//ʧȥ����
	VOID OnEnKillFocus();
	//��������
	VOID OnBnClickedForgetInsure();
	//ת�˰�ť
	VOID OnBnClickedTransferScore();
	//
	VOID OnBnClickedScore(UINT nID);

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedById();
	afx_msg void OnBnClickedByName();
};

/////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////

//��ȡ��Ϸ��
class CDlgInsurePassword : public CDialog,public IKeyBoardSink
{
	//��Ԫ����
	friend class CDlgInsureMain;
	friend class CDlgInsurePlaza;
	friend class CDlgInsureServer;

	//��������
protected:
	bool							m_bSwitchIng;						//ת����־
	CBitImage                       m_ImageBk;                          //����DPI

	//����ָ��
protected:
	CDlgInsureMain *				m_pDlgInsureMain;					//����ָ��
	tagUserInsureInfo *				m_pUserInsureInfo;					//�û���Ϣ


	//��������
protected:
	TCHAR							m_szSrcPassword[LEN_PASSWORD];		//�û�����
	TCHAR							m_szDesPassword[LEN_PASSWORD];		//�û�����

	//�ؼ�����
public:
	CEdit							m_edInsurePassword1;				//��������
	CEdit							m_edInsurePassword2;				//��������
	CEdit							m_edInsurePassword3;				//��������
	CSkinButton						m_btTakeScore;						//�޸İ�ť
	CSkinButton						m_btSaveScore;						//��ť
	CPasswordKeyboard2				m_KeyBoard;


	//�����ؼ�
public:
	CDlgInsureItem					m_DlgInsureItem;					//��������

	//��������
public:
	//���캯��
	CDlgInsurePassword();
	//��������
	virtual ~CDlgInsurePassword();

public:
	//���ý���
	VOID ResetControlStatus();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ����ť
	virtual VOID OnOK();
	//ȡ����ť
	virtual VOID OnCancel();

	virtual	VOID OnKeyBoardChar(WORD wChar);
	virtual	VOID OnKeyBoardClean();

	//�ؼ�����
protected:
	//������Ϣ
	VOID OnEnChangeScore();
	//��ť
	VOID OnBnClickedSaveScore();
	//ȡ�ť
	VOID OnBnClickedTakeScore();
	//��������
	VOID OnBnClickedForgetInsure();

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
};



//////////////////////////////////////////////////////////////////////////////////

//���չ���
class SHARE_CONTROL_CLASS CDlgInsureMain : public CDialog, public IInsureCounterAction
{
	//��������
protected:
	bool							m_bSaveMission;						//�������
	bool							m_bTakeMission;						//ȡ������
	bool							m_bQueryMission;					//��ѯ����
	bool							m_bTransferMission;					//ת������
	bool							m_bModifyPassword;					//�����޸�

	LPTSTR							m_pInsurePass;						//��������
	//��Դ����
protected:
	CPngImage						m_ImageBack;	

	//��ѯ����
protected:
	bool							m_bInitInfo;						//������Ϣ
	BYTE							m_cbInsureMode;						//����ģʽ
	tagUserInsureInfo				m_UserInsureInfo;					//������Ϣ

	tagTransInfo					m_TransInfo;

	//�����ؼ�
protected:
	CSkinTabCtrl					m_TabControl;						//����ѡ��
	CSkinButton						m_btQueryInfo;						//��ѯ��ť

	//�����
protected:
	CDlgInsureItem					m_DlgInsureItem;					//��������
	CDlgInsureSave					m_DlgInsureSave;					//��ȡ����
	CDlgInsureTransfer				m_DlgInsureTransfer;				//ת������
	CDlgInsureRecord				m_DlgInsureRecord;					//��¼����
	CDlgInsurePassword				m_DlgInsurePassword;				//��������
	//��������
public:
	//���캯��
	CDlgInsureMain();
	//��������
	virtual ~CDlgInsureMain();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ����ť
	virtual VOID OnOK();
	//
	virtual VOID OnCancel();

	//���ں���
protected:
	//�滭��Ϣ
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);

	//�¼�����
public:
	//��ʼ����
	VOID OnMissionStart();
	//��ֹ����
	VOID OnMissionConclude();

	//��������
public:
	VOID SetInsurePassword(LPTSTR lpInsure);

	//���ܺ���
protected:
	//��ѯ����
	VOID QueryUserInsureInfo();
	//����ģʽ
	VOID SwitchInsureModeView(BYTE cbInsureMode);

	//��Ϣ����
protected:
	//��ѯ��ť
	VOID OnBnClickedQueryInfo();
	//���͸ı�
	VOID OnTcnSelchangeInsureMode(NMHDR * pNMHDR, LRESULT * pResult);
	//
	void OnLButtonDown(UINT nFlags, CPoint point);
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

//�㳡����
class SHARE_CONTROL_CLASS CDlgInsurePlaza : public CDlgInsureMain, public CMissionItem
{
	//��������
protected:
	BYTE                            m_cbByNickName;                       //�ǳ�����
	SCORE							m_lScore;							//��Ϸ����Ŀ
	TCHAR							m_szNickName[LEN_NICKNAME];			//�û��ǳ�
	TCHAR							m_szInsurePass[LEN_PASSWORD];		//��������

	//�������
protected:
	CMissionManager					m_MissionManager;					//�������

	//��������
public:
	//���캯��
	CDlgInsurePlaza();
	//��������
	virtual ~CDlgInsurePlaza();

	//ִ�к���
protected:
	//��ѯ�¼�
	virtual VOID PerformQueryInfo();
	//�����¼�
	virtual VOID PerformSaveScore(SCORE lSaveScore);
	//ȡ���¼�
	virtual VOID PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass);
	//�޸�����
	virtual VOID PerformModifyInsurePassword(LPCTSTR szSrcPassword, LPCTSTR szDesPassword);
	//ת���¼�
	virtual VOID PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass);

	//�����¼�
private:
	//�����¼�
	virtual bool OnEventMissionLink(INT nErrorCode);
	//�ر��¼�
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);
};

//////////////////////////////////////////////////////////////////////////////////

//��������
class SHARE_CONTROL_CLASS CDlgInsureServer : public CDlgInsureMain
{
	//��������
protected:
	BYTE                            m_cbByNickName;                       //�ǳ�����
	SCORE							m_lScore;							//��Ϸ����Ŀ
	TCHAR							m_szNickName[LEN_NICKNAME];			//�û��ǳ�
	TCHAR							m_szInsurePass[LEN_PASSWORD];		//��������

	//��������
protected:
	ITCPSocket *					m_pITCPSocket;						//����ӿ�
	IClientUserItem *				m_pIMySelfUserItem;					//�Լ�ָ��

	//��������
public:
	//���캯��
	CDlgInsureServer();
	//��������
	virtual ~CDlgInsureServer();

	//ִ�к���
protected:
	//��ѯ�¼�
	virtual VOID PerformQueryInfo();
	//�����¼�
	virtual VOID PerformSaveScore(SCORE lSaveScore);
	//ȡ���¼�
	virtual VOID PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass);
	//�޸�����
	virtual VOID PerformModifyInsurePassword(LPCTSTR szSrcPassword, LPCTSTR szDesPassword);
	//ת���¼�
	virtual VOID PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass);

	//���ܺ���
public:
	//��������
	VOID Initialization(ITCPSocket * pITCPSocket, IClientUserItem * pIMySelfUserItem);
	//������Ϣ
	bool OnServerInsureMessage(WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize);
};

//////////////////////////////////////////////////////////////////////////////////

#endif