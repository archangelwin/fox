#ifndef DLG_USERINFO_HEAD_FILE
#define DLG_USERINFO_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
//////////////////////////////////////////////////////////////////////////////////

//�رմ���
class CDlgUserInfo : public CDialog
{

	//������Դ
protected:
	IClientUserItem*                m_pUserData;					//�û���Ϣ
	CSkinLayered					m_SkinLayered;						//�ֲ㴰��
	CUserOrderParserHelper			m_UserOrderParserModule;
    IGameLevelParser *				m_pIGameLevelParser;				//�ȼ��ӿ�
	TCHAR							m_szStatus[100];
	//��������
public:
	//���캯��
	CDlgUserInfo();
	//��������
	virtual ~CDlgUserInfo();

    VOID SetGameLevelParser(IGameLevelParser * pIGameLevelParser) { m_pIGameLevelParser=pIGameLevelParser; }
	void ShowUserInfo(IClientUserItem*pUserData,LPCTSTR lpszStatus=NULL);
	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//���ú���
	virtual BOOL OnInitDialog();
	//��ť��Ϣ

	//��Ϣ����
public:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);

		//λ�øı�
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
		//��ʾ��Ϣ
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif