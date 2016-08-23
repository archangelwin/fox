#ifndef _UIButton5_H_
#define _UIButton5_H_

#include "UIComponent.h"

class CUIButton5
	: public CUIComponent
{
public:
	CUIButton5(int id = 0);
	~CUIButton5();

	void SetTexture(HTEXTURE tex, int status);
	void SetAlign(unsigned int align);
	void SetFont(GfxFont* font);
	void SetLabel(const tstring& label);
	void SetLabelAlign(unsigned int align);
	void SetLabelOffset(float x, float y);
	void SetLabelColor(DWORD colText = 0xFFFFFFFF, DWORD colFrame = 0xFF000000);
protected:	
	void SetStateTexure(int status);
	virtual void OnRender();
	virtual void OnUpdate();
	virtual void OnMouseOver(bool bOver, float x, float y);
	
	void Enter();
	void Leave();
	void RenderText();
protected:
	CUIButton5(const CUIButton5 &go);
	CUIButton5&	operator= (const CUIButton5 &go);
protected:
	// ��ť����
	float      m_fAniElapsed;	// ����
	bool       m_isEntering;	// �Ƿ����ڽ���
	bool       m_isLeaving;		// �Ƿ������˳�

	// ��ť����
	int        m_iTexStatus;	// ����״̬
	HTEXTURE   m_tex;			// ����
	int		   m_iFrameW;		// ֡���
	int		   m_iFrameH;		// ֡�߶�
	hgeSprite  m_spt;			// ���ƾ���

	// ��ť��
	unsigned int m_align;		// �ڲ��ı����뷽ʽ
	GfxFont*     m_font;		// �ı�����
	tstring      m_label;		// ��ʾ�ı�
	unsigned int m_txtAlign;	// �ı����뷽ʽ
	float        m_txtOffsetX;	// �ı�x����ƫ��
	float        m_txtOffsetY;	// �ı�y����ƫ��
	DWORD        m_colText;		// �ı���ɫ
	DWORD        m_colFrame;	// �ı��߿���ɫ
}; // CUIButton5
#endif // _UIButton5_H_