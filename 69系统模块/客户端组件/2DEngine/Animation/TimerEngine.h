
#ifndef TIMER_ENGINE_H_
#define TIMER_ENGINE_H_
#pragma once

#include <afxtempl.h>
#include "Thread.h"

#define TIMES_INFINITY		((DWORD)-1) // ���޴���
#define UM_TIMER_ENGINE		(0x7FEE)		// ��ʱ����Ϣ (WM_APP(0x8000) -- 0xBFFF)
#define UM_TIMER_END		(0x7FEF)		// 

// ������
class CTimerEngine;

// ��ʱ���߳�
class CTimerThread : public CThread
{
public:
	// ���캯��
	CTimerThread(void);
	// ��������
	virtual ~CTimerThread(void);

	// ���ܺ���
public:
	// ���ú���
	bool InitThread(CTimerEngine* pTimerEngine, DWORD dwTimerSpace);

	// ���غ���
private:
	// ���к���
	virtual bool OnEventThreadRun();

	// ��������
private:
	DWORD m_dwTimerSpace; // ʱ����
	CTimerEngine* m_pTimerEngine; // ��ʱ������
};

//////////////////////////////////////////////////////////////////////////

// ��ʱ������
struct tagTimerItem
{
	DWORD dwTimerID; // ��ʱ�� ID
	DWORD dwElapse; // ��ʱʱ��
	DWORD dwTimeLeave; // ����ʱ��
	DWORD dwRepeatTimes; // �ظ�����
	DWORD dwStartTime; //  ��ʼʱ��
	DWORD dwCurrentTime; // ��ǰʱ��
	WPARAM wBindParam; // �󶨲���
};

//  ��ʱ���������鶨��
typedef CArray<tagTimerItem*> CTimerItemPtr;

//  ��ʱ������
class CTimerEngine
{
	friend class CTimerThread;

public:
	// ���캯��
	CTimerEngine(void);
	// ��������
	virtual ~CTimerEngine(void);

	// �ӿں���
public:
	// ���ö�ʱ��
	bool SetTimer(DWORD dwTimerID, DWORD dwElapse, DWORD dwRepeatTimes, WPARAM wParam);
	// ɾ����ʱ��
	bool KillTimer(DWORD dwTimerID);
	// ɾ����ʱ��
	bool KillAllTimer();

	// ����ӿ�
public:
	// ��ʼ����
	bool InitTimerEngine(CWnd* pSinkWnd);
	// ֹͣ����
	bool UninitTimerEngine();

	// �ڲ�����
private:
	// ��ʱ��֪ͨ
	void OnTimerThreadSink();

	// ���ö���
private:
	DWORD m_dwTimerSpace; // ʱ����

	// ״̬����
private:
	bool m_bService; // ���б�־
	DWORD m_dwTimePass; // ����ʱ��
	DWORD m_dwTimeLeave; // ����ʱ��
	CTimerItemPtr m_TimerItemFree; // ��������
	CTimerItemPtr m_TimerItemActive; // �����

	// �������
private:
	CCriticalSection m_CriticalSection; // �߳�����
	CTimerThread m_TimerThread; // ��ʱ���߳�
	CWnd* m_pSinkWnd; // ֪ͨ����
};

#endif // TIMER_ENGINE_H_