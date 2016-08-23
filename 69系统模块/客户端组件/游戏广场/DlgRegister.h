#ifndef DLG_REGISTER_HEAD_FILE
#define DLG_REGISTER_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "WndValidateCode.h"

//////////////////////////////////////////////////////////////////////////////////

//ע�ᴰ��
class CDlgRegister : public CDialog
{
	//��������
public:
	WORD							m_wFaceID;							//ͷ���ʶ
	BYTE							m_cbGender;							//�û��Ա�
	TCHAR							m_szAccounts[LEN_ACCOUNTS];			//ע���ʺ�
	TCHAR							m_szNickName[LEN_NICKNAME];			//ע���ǳ�
	TCHAR							m_szSpreader[LEN_MOBILE_PHONE];		//�Ƽ��ʺ�
	TCHAR							m_szLogonPass[LEN_PASSWORD];		//��¼����
	TCHAR							m_szInsurePass[LEN_PASSWORD];		//��������
	TCHAR							m_szPassPortID[LEN_PASS_PORT_ID];	//֤������
	TCHAR							m_szCompellation[LEN_COMPELLATION];	//��ʵ����
    TCHAR							m_szQQ[LEN_QQ];	        //QQ����
	//���ñ���
protected:
	BYTE							m_cbRemPassword;					//��ס����
	BYTE							m_cbLogonPassLevel;					//����ǿ��
	BYTE							m_cbInsurePassLevel;				//����ǿ��

	//�ؼ�����
public:
	CSkinEditEx						m_edAccounts;						//ע���ʺ�
	CSkinEditEx						m_edNickName;						//ע���ʺ�
	CSkinEditEx						m_edSpreader;						//�Ƽ��û�
	CSkinEditEx						m_edPassPortID;						//���֤��
	CSkinEditEx						m_edLogonPass1;						//��¼����
	CSkinEditEx						m_edLogonPass2;						//��¼����
	CSkinEditEx						m_edInsurePass1;					//��������
	CSkinEditEx						m_edInsurePass2;					//��������
	CSkinEditEx						m_edCompellation;					//��ʵ����
	CSkinEditEx						m_edQQ;					            //QQ����
	CSkinEditEx						m_edValidateCode;					//��֤����

	BYTE							m_cbFlag[9];						//��ʾ��Ϣ
	CPoint							m_ptTipString[9];					//��ʾ��Ϣ
	CString							m_strTipString[9];					//��ʾ��Ϣ


	//�ؼ�����
protected:
	CSkinButton						m_btQuit;							//ȡ����ť
	CSkinButton						m_btEnter;							//ע�ᰴť
	CSkinButton						m_btCancel;							//�رհ�ť
	CSkinButton						m_btSelectFace;						//ѡ��ť

	//�ؼ�����
protected:
	CBrush							m_brBrush;							//������ˢ
	CFaceItemView					m_FaceItemView;						//ͷ����ͼ
	CSkinHyperLink					m_ChangeValidate;					//������֤

	//�������
protected:
	CSkinLayered					m_SkinLayered;						//�ֲ㴰��
	CWndValidateCode				m_WndValidateCode;					//��֤�ؼ�
	CFaceSelectControlHelper		m_FaceSelectControl;				//ͷ��ѡ��

	//��������
public:
	//���캯��
	CDlgRegister();
	//��������
	virtual ~CDlgRegister();

	//���غ���
public:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//���ú���
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();
	//ȡ������
	virtual VOID OnCancel();

	//���ܺ���
public:
	//��������
	WORD ConstructRegisterPacket(BYTE cbBuffer[], WORD wBufferSize, BYTE cbValidateFlags);
	WORD ConstructCheckPacket(BYTE cbBuffer[], WORD wBufferSize, BYTE cbCheckFlags);

	//��������
private:
	//��ȡ��Ϣ
	bool GetInformation();
	//��ȡ�ַ�
	VOID GetControlString(UINT uControlID, TCHAR szString[], WORD wMaxCount);

	//��Ϣӳ��
public:
	//�رհ�ť
	VOID OnBnClickedQuit();
	//��������
	VOID OnEnChangeLogonPass();
	//��������
	VOID OnEnChangeInsurePass();
	//ͷ��ѡ��
	VOID OnBnClickedSelectFace();
	//������֤
	VOID OnBnClickedChangeValidate();
	//
	VOID OnBnSelectGender();

	afx_msg void OnEnKillfocusAccount();
	afx_msg void OnEnKillfocusNickname();

	//ϵͳ��Ϣ
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//��ʾ��Ϣ
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//λ�øı�
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeAccounts();
	afx_msg void OnEnChangeNickname();
	afx_msg void OnEnChangeLogonPass2();
	afx_msg void OnEnChangeInsurePass2();
	afx_msg void OnEnChangeCompellation();
	afx_msg void OnEnChangePassportId();
	afx_msg void OnEnChangeSpreader();
	afx_msg void OnEnChangeQQ();
};

//////////////////////////////////////////////////////////////////////////////////

#endif