#ifndef PASSWORD_CONTROLEXx_HEAD_FILE
#define PASSWORD_CONTROLEXx_HEAD_FILE

#pragma once


//����༭
class CPasswordControlEx : public CPasswordControl
{

	//��������
public:
	//���캯��
	CPasswordControlEx();
	//��������
	virtual ~CPasswordControlEx();

	//���غ���
protected:
	//�󶨺���
	virtual VOID PreSubclassWindow();

	afx_msg VOID OnSize(UINT nType, INT cx, INT cy);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif