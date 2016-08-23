
#ifndef ANIMATION_CTRL_H_
#define ANIMATION_CTRL_H_
#pragma once

// ǰ������
struct tagTimerItem;

// ��ʱ��������Ϣ����
class ITimerEngineProc
{
public:
	virtual void TimerEngineProc(DWORD dwTimerID, BYTE cbTimerEnd, tagTimerItem* pTimerItem) = 0;
};

// �����ؼ�,��Ϊ���ʹ�����������Ϣ���п��ܻ������Ϣͬ������,Ҳ���Բ�ռ�����������Ϣ����,�����ͬ��ûʲôҪ��Ļ�����ֱ�ӷ���Ϣ��������,��ʹ�ô���.
// ʵ�ִ���ר����������TimerEngine��������Ϣ,����ʵ�ֵĻ������������ͬ��������,�������Ա�����TimerEngine::OnTimerThreadSink��
// PostMessage֮ǰƵ����new,����һ�ط�Ƶ����delete��ͬ��ʵ��.
// ʹ�÷���(������):
// �̳�ITimerEngineProc, ����CAnimationCtrl m_AnimationCtrl;
// m_AnimationCtrl.Create(NULL, NULL, WS_CHILD, CRect(0, 0, 0, 0), this, 100);
// m_AnimationCtrl.SetTimerEngineProc(this);
// TimerEngineProc���������ʵ��
class CAnimationCtrl : public CWnd
{
	DECLARE_DYNAMIC(CAnimationCtrl)

public:
	CAnimationCtrl();
	virtual ~CAnimationCtrl();

public:
	// ���ü�ʱ��������
	void SetTimerEngineProc(ITimerEngineProc* pITimerEngineProc);

protected:
	// ��ʱ����Ϣ
	LRESULT OnTimerMessage(WPARAM wParam, LPARAM lParam);
	LRESULT OnTimerEndMessage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	ITimerEngineProc* m_pITimerEngineProc;
};

#endif // ANIMATION_CTRL_H_


