#pragma once
#include "Stdafx.h"

class CSkinEditEx2 :
	public CEdit
{
public:
	CSkinEditEx2(void);
	~CSkinEditEx2(void);
	//��Ϣ���� 
protected:
	//�ػ���Ϣ
	VOID OnNcPaint();
	//�滭�ؼ�
	HBRUSH CtlColor(CDC * pDC, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
};
