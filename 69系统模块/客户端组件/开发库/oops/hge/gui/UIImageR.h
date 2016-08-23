#ifndef _UIImageR_H_
#define _UIImageR_H_

#include "UIComponent.h"

class CUIImageR
	: public CUIComponent
{
public:
	CUIImageR(int id = 0, HTEXTURE tex = 0, int rows = 1, int cols = 1);
	~CUIImageR();

	void SetTexture(HTEXTURE tex, int rows = 1, int cols = 1);
	void SetFrame(int index);
	void SetAngle(float fAngle);
	void SetColor(DWORD dwColor, int index = -1);

	int GetCurrentFrame() const;
	int GetFrames() const;
	float GetAngle() const;
	DWORD GetColor() const;
	
protected:	
	virtual void OnRender();
	virtual void OnUpdate();
	virtual bool IsInside(float x, float y) const;

protected:
	CUIImageR(const CUIImageR &go);
	CUIImageR&	operator= (const CUIImageR &go);
protected:
	HTEXTURE	m_tex;			// ����
	int			m_iFrameW;		// ֡���
	int			m_iFrameH;		// ֡�߶�
	int			m_iRows;		// ����
	int			m_iCols;		// ����
	int			m_iFrames;		// ֡��
	int			m_iCurFrame;	// ��ǰ֡
	hgeSprite	m_spt;			// ���ƾ���
	float		m_fAngle;
}; // CUIImageR
#endif // _UIImageR_H_