#ifndef GAME_FRAME_VIEW_HGE_HEAD_FILE
#define GAME_FRAME_VIEW_HGE_HEAD_FILE
#include "GfxFont.h"
//GAME_FRAME_CLASS
//��Ϸ��ͼ���
class CGameFrameViewHGE : public CGameFrameView
{
	//��������
public:
	//���캯��
	CGameFrameViewHGE();
	//��������
	virtual ~CGameFrameViewHGE();

	//���غ���
public:
	//���ý���
	virtual void ResetGameView();
	//�����ؼ�
	virtual void RectifyControl(int nWidth, int nHeight);
	//�������
	virtual void InvalidGameView(int nXPos, int nYPos, int nWidth, int nHeight);
	//������Ϣ
	virtual void AddGameTableMessage(LPCTSTR pszMessage,WORD wLen,WORD wType);
	//���ñ���ɫ
	virtual void SetBackgroundColor(DWORD argb);

	//��ϷԪ��
public:
	//�滭׼��
	void DrawUserReady(int x, int y, int align = 0);
	//�滭ʱ��
	void DrawUserClock(int x, int y, WORD wUserClock, int align = 0);
	//�滭��־
	void DrawOrderFlag(int x, int y, BYTE cbImageIndex, int align = 0);
	//�滭ͷ��
	void DrawUserAvatar(int x, int y, IClientUserItem * pIClientUserItem, int align = 0,float fzoom=1.0f);
	//�滭ͷ��
	void DrawAvatar(unsigned int faceId, int x, int y, bool isOnLine, unsigned int align = 0,float fzoom=1.0f);
	//�滭ͷ��
	void DrawAvatar(const DWORD (&dwCustomFace)[FACE_CX*FACE_CY], int x, int y, bool isOnLine, unsigned int align = 0,float fzoom=1.0f);

	//������Ϣ
	VOID DrawMatchInfo();

	void DrawNumberString(int nXPosition, int nYPosition,HTEXTURE btxNumber,int iNumber);

	//��Ϣӳ��
public:
	//������Ϣ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//������Ϣ
	afx_msg void OnDestroy();
	//�滭����
	afx_msg void OnPaint();
	//�滭����
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//λ�ñ仯
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//��ʱ����Ϣ
	afx_msg void OnTimer(UINT nIDEvent);
	
	DECLARE_MESSAGE_MAP()

	// ���ܺ���
public:
	static HTEXTURE GetDllTexture(HGE* hge, LPCTSTR type, LPCTSTR name, LPCTSTR dll);
	static HTEXTURE GetCustomTexture(DWORD* pChustomData, HGE* hge, int cx, int cy);

	// ��������
protected:
	// ��ʼ��
	virtual bool OnInit() {return true;}
	// �����ͷ�
	virtual void OnDeinit() {}
	// �ָ�
	virtual void OnRestore() {}
	// ����
	virtual void OnUpdate() {}
	// �滭����
	virtual void OnDrawView(){}

	// HGE 
private:
	// ��ʼ��HGE
	bool InitHge(HWND hWnd);
	// �ر�Hge
	void ShutDownHge();
	// ������Դ
	bool LoadResources();
	// ��̬����ӿ�
	static bool FrameFunc();
	// ��̬���ƽӿ�
	static bool RenderFunc();
	// ��̬�ָ��ӿ�
	static bool RestoreFunc();

	// HGE ����
protected:
	HGE*		m_pHge;					// HGEָ��

	//������Դ
public:
	CRect		m_RectDirtySurface;		// �ػ�����
	DWORD		m_dwClearColor;			// ������ɫ

	hgeSprite	m_spt;					// ���ƾ���

	// ͷ��
	unsigned int	m_iAvatarRows;		// ����
	unsigned int	m_iAvatarCols;		// ����
	unsigned int	m_iAvatarTotals;	// �ܸ���
	HTEXTURE		m_hTextureAvatar;	// ͷ������
	HTEXTURE		m_hCustomAvatar;	// �Զ�������

	//����
	HTEXTURE		m_MatchView;		//������Ϣ����ͼƬ
	HTEXTURE		m_WaitView;			//�ȴ�����ͼƬ
	HTEXTURE		m_GreenNumber;	
	HTEXTURE		m_OrangeNumber;
	HTEXTURE		m_WaitTip;
	HTEXTURE		m_Line;	
	


	// ��ұ�־		
	unsigned int	m_iMemberRows;		// ����
	unsigned int	m_iMemberCols;		// ����
	unsigned int	m_iMemberTotals;	// �ܸ���
	HTEXTURE		m_texMemberFlag;	// ��־����

	// ������־
	HTEXTURE     m_texReady;		// ׼������
	HTEXTURE     m_texClockBack;	// ����ʱ����
	HTEXTURE     m_texClockItem;	// ����ʱ����

public:
	GfxFont			*m_MatchFont;		//
	GfxFont			*m_MatchFont2;
	GfxFont			*m_MatchRoll;		//��������
	CPoint			m_ptRoll;			//��������λ��
};

//////////////////////////////////////////////////////////////////////////

#endif