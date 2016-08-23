#ifndef _UIImage_H_
#define _UIImage_H_

#include "UIComponent.h"

class CUIImage
	: public CUIComponent
{
public:
	CUIImage(int id = 0, HTEXTURE tex = 0, int rows = 1, int cols = 1);
	~CUIImage();

	void SetTexture(HTEXTURE tex, int rows = 1, int cols = 1);
	void SetFrame(int index);

	int GetCurrentFrame() const;
	int GetFrames() const;
	
protected:	
	virtual void OnRender();
	virtual void OnUpdate();

protected:
	CUIImage(const CUIImage &go);
	CUIImage&	operator= (const CUIImage &go);
protected:
	HTEXTURE	m_tex;			// ����
	int			m_iFrameW;		// ֡���
	int			m_iFrameH;		// ֡�߶�
	int			m_iRows;		// ����
	int			m_iCols;		// ����
	int			m_iFrames;		// ֡��
	int			m_iCurFrame;	// ��ǰ֡
	hgeSprite	m_spt;			// ���ƾ���
}; // CUIImage
#endif // _UIImage_H_