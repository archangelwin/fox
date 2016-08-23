#ifndef SKIN_DIALOG_HEAD_FILE
#define SKIN_DIALOG_HEAD_FILE

#pragma once

#include "PngImage\PngImage.h"

//////////////////////////////////////////////////////////////////////////////////

//�ֲ㴰��
class CSkinLayered : public CWnd
{
	//��������
protected:
	CWnd *							m_pWndControl;						//�ؼ�����

	//��������
public:
	//���캯��
	CSkinLayered();
	//��������
	virtual ~CSkinLayered();

	//���ܺ���
public:
	//��������
	VOID CreateLayered(CWnd * pWndControl, CRect & rcWindow);
	//��������
	VOID InitLayeredArea(CDC * pDCImage, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);
	//��������
	VOID InitLayeredArea(CPngImage & Image, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);

	//��Ϣӳ��
protected:
	//�ر���Ϣ
	VOID OnClose();
	//������Ϣ
	VOID OnSetFocus(CWnd * pOldWnd);

	//��̬����
protected:
	//ö�ٺ���
	static BOOL CALLBACK EnumChildProc(HWND hWndChild, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif