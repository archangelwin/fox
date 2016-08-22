//////////////////////////////////////////////////////////////////////////
//
// �������������
//
// ���ߣ�΢���ƽ��(BOGY)
//
// �汾��For HGE v1.7
//
//////////////////////////////////////////////////////////////////////////
#ifndef GDIFONT_H
#define GDIFONT_H

class GfxFont
{
public:
	GfxFont(const char* lpsFontName, int nFaceSize, BOOL bBold = FALSE, BOOL bItalic = FALSE, BOOL bAntialias = TRUE);
	~GfxFont(void);

public:
	void Print( float x, float y, const wchar_t* format, ...);
	// ��Ⱦ�ı�
	void RenderEx( float x, float y, unsigned int align, const wchar_t* format, ...);
	void Render(float x, float y, unsigned int align, const wchar_t* text);

	//���  dwColor�ı���ɫ   DwStrokeColor�����ɫ
	void Print( float x, float y,DWORD dwColor,DWORD DwStrokeColor, const wchar_t* format, ...);

	void Render(float x, float y, unsigned int align, const wchar_t* text,DWORD dwColor,DWORD DwStrokeColor);

	// �������ȡ��ɫ
	virtual void	SetColor( DWORD dwColor, int i = -1 );
	virtual DWORD	GetColor( int i = 0 );
	virtual void	SetZ(float z);
	virtual float	GetZ( int i = 0 ) const;

	// ��ȡ�ı����
	virtual SIZE	GetTextSize( const wchar_t* text, int iFrame = 0);

	// ���������ȡ�ַ�
	virtual wchar_t	GetCharacterFromPos( const wchar_t* text, float pixel_x, float pixel_y );

	// �����ּ��
	virtual void	SetKerningWidth( float kerning );
	virtual void	SetKerningHeight( float kerning );

	// ��ȡ�ּ��
	virtual float	GetKerningWidth();
	virtual float	GetKerningHeight();

	// �����С
	virtual float	GetFontSize();
	
	// ��ȡ�ַ����
	inline float	GetWidthFromCharacter( wchar_t c, bool original = false );

private:
	virtual void	RealRender(float x, float y, const wchar_t* text);
	//���
	virtual void	RealRender(float x, float y, const wchar_t* text,DWORD dwColor,DWORD DwStrokeColor);
	// �����ַ���ȡ����
	unsigned int	GetGlyphByCharacter( wchar_t c );
	inline void		CacheCharacter(unsigned int idx, wchar_t c);

	typedef struct tagEngineFontGlyph
	{
		HTEXTURE	t;
		float		w;
		float		h;
		float		x;
		float		y;
		float		c;
	}TENGINEFONTGLYPH;

	static const unsigned int font_count = 0xFFFF;// = sizeof(wchar_t);
	TENGINEFONTGLYPH	m_Glyphs[font_count];
	UINT				m_nAntialias;//�����
	LONG				m_nAscent;//����
	DWORD				m_dwFontColor;
	float				m_nFontSize;
	float				m_nKerningWidth;
	float				m_nKerningHeight;

	class HGE*			m_pHGE;
	class hgeSprite*	m_pSprite;

	// GDI�豸
	HDC					m_hMemDC;
	HFONT				m_hFont;
};
#endif//GDIFONT_H
