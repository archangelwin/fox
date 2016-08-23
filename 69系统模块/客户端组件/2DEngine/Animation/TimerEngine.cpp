#include "StdAfx.h"
#include "TimerEngine.h"
#include "Locker.h"

// �궨��
#define NO_TIME_LEFT	DWORD(-1)	// ����Ӧʱ��

// ���캯��
CTimerThread::CTimerThread()
{
	m_dwTimerSpace = 0L;
	m_pTimerEngine = NULL;
}

// ��������
CTimerThread::~CTimerThread()
{
}

// ���ú���
bool CTimerThread::InitThread(CTimerEngine* pTimerEngine, DWORD dwTimerSpace)
{
	// Ч�����
	ASSERT(dwTimerSpace >= 10L);
	ASSERT(pTimerEngine != NULL);
	if (pTimerEngine == NULL) return false;

	// ���ñ���
	m_dwTimerSpace = dwTimerSpace;
	m_pTimerEngine = pTimerEngine;

	return true;
}

// ���к���
bool CTimerThread::OnEventThreadRun()
{
	ASSERT(m_pTimerEngine != NULL);
	Sleep(m_dwTimerSpace);
	m_pTimerEngine->OnTimerThreadSink();
	return true;
}

//////////////////////////////////////////////////////////////////////////

// ���캯��
CTimerEngine::CTimerEngine(void)
{
	m_bService = false;
	m_dwTimePass = 0L;
	m_dwTimerSpace = 25L;
	m_dwTimeLeave = NO_TIME_LEFT;
	m_pSinkWnd = NULL;
}

// ��������
CTimerEngine::~CTimerEngine(void)
{
	// ֹͣ����
	UninitTimerEngine();

	// �����ڴ�
	tagTimerItem* pTimerItem = NULL;
	for (INT_PTR i = 0; i < m_TimerItemFree.GetCount(); i++)
	{
		pTimerItem = m_TimerItemFree[i];
		ASSERT(pTimerItem != NULL);
		if (pTimerItem != NULL)
		{
			delete pTimerItem;
			pTimerItem = NULL;
		}
	}
	for (INT_PTR i = 0; i < m_TimerItemActive.GetCount(); i++)
	{
		pTimerItem = m_TimerItemActive[i];
		ASSERT(pTimerItem != NULL);
		if (pTimerItem != NULL)
		{
			delete pTimerItem;
			pTimerItem = NULL;
		}
	}
	m_TimerItemFree.RemoveAll();
	m_TimerItemActive.RemoveAll();

	return;
}

// ���ö�ʱ��
bool CTimerEngine::SetTimer(DWORD dwTimerID, DWORD dwElapse, DWORD dwRepeatTimes, WPARAM wParam)
{
	// ������Դ
	CLocker Locker(m_CriticalSection);

	// Ч�����
	ASSERT(dwRepeatTimes > 0L);
	if (dwRepeatTimes == 0) return false;
	dwElapse = (dwElapse + m_dwTimerSpace - 1) / m_dwTimerSpace * m_dwTimerSpace;

	// ���Ҷ�ʱ��
	bool bTimerExist = false;
	tagTimerItem* pTimerItem = NULL;
	for (INT_PTR i = 0; i < m_TimerItemActive.GetCount(); i++)
	{
		pTimerItem = m_TimerItemActive[i];
		ASSERT(pTimerItem != NULL);
		if (pTimerItem->dwTimerID == dwTimerID) 
		{
			bTimerExist = true;
			break;
		}
	}

	// ������ʱ��
	if (bTimerExist == false)
	{
		INT_PTR nFreeCount = m_TimerItemFree.GetCount();
		if (nFreeCount > 0)
		{
			pTimerItem = m_TimerItemFree[nFreeCount - 1];
			ASSERT(pTimerItem != NULL);
			m_TimerItemFree.RemoveAt(nFreeCount - 1);
		}
		else
		{
			try
			{
				pTimerItem = new tagTimerItem;
				ASSERT(pTimerItem != NULL);
				if (pTimerItem == NULL) return false;
			}
			catch (...) 
			{ 
				return false; 
			}
		}
	}

	// ���ò���
	ASSERT(pTimerItem != NULL);
	pTimerItem->dwTimerID = dwTimerID;
	pTimerItem->wBindParam = wParam;
	pTimerItem->dwElapse = dwElapse;
	pTimerItem->dwRepeatTimes = dwRepeatTimes;
	pTimerItem->dwTimeLeave = dwElapse + m_dwTimePass;
	pTimerItem->dwStartTime = pTimerItem->dwCurrentTime = GetTickCount();

	// ���ʱ��
	m_dwTimeLeave = min(m_dwTimeLeave, dwElapse);
	if (bTimerExist == false) m_TimerItemActive.Add(pTimerItem);

	return false;
}

// ɾ����ʱ��
bool CTimerEngine::KillTimer(DWORD dwTimerID)
{
	// ������Դ
	CLocker Locker(m_CriticalSection);

	// ���Ҷ�ʱ��
	tagTimerItem* pTimerItem = NULL;
	for (INT_PTR i = 0; i < m_TimerItemActive.GetCount(); i++)
	{
		pTimerItem = m_TimerItemActive[i];
		ASSERT(pTimerItem != NULL);
		if (pTimerItem->dwTimerID == dwTimerID) 
		{
			m_TimerItemActive.RemoveAt(i);
			m_TimerItemFree.Add(pTimerItem);
			if (m_TimerItemActive.GetCount() == 0) 
			{
				m_dwTimePass = 0L;
				m_dwTimeLeave = NO_TIME_LEFT;
			}
			return true;;
		}
	}

	return false;
}

// ɾ����ʱ��
bool CTimerEngine::KillAllTimer()
{
	// ������Դ
	CLocker Locker(m_CriticalSection);

	// ɾ����ʱ��
	m_TimerItemFree.Append(m_TimerItemActive);
	m_TimerItemActive.RemoveAll();

	// ���ñ���
	m_dwTimePass = 0L;
	m_dwTimeLeave = NO_TIME_LEFT;

	return true;
}

// ��ʼ����
bool CTimerEngine::InitTimerEngine(CWnd* pSinkWnd)
{
	// Ч��״̬
	if (m_bService==true) 
	{
		return true;
	}

	// �жϰ�
	if (pSinkWnd == NULL)
	{
		return false;
	}
	m_pSinkWnd = pSinkWnd;

	// ���ñ���
	m_dwTimePass = 0L;
	m_dwTimeLeave = NO_TIME_LEFT;
	if (m_TimerThread.InitThread(this, m_dwTimerSpace) == false)
	{
		return false;
	}

	// ��������
	if (m_TimerThread.StartThread() == false)
	{
		return false;
	}

	// ���ñ���
	m_bService = true;

	return true;
}

// ֹͣ����
bool CTimerEngine::UninitTimerEngine()
{
	// ���ñ���
	m_bService = false;
	m_pSinkWnd = NULL;

	// ֹͣ�߳�
	m_TimerThread.ConcludeThread(INFINITE);

	// ���ñ���
	m_dwTimePass = 0L;
	m_dwTimeLeave = NO_TIME_LEFT;
	m_TimerItemFree.Append(m_TimerItemActive);
	m_TimerItemActive.RemoveAll();

	return true;
}

// ��ʱ��֪ͨ
void CTimerEngine::OnTimerThreadSink()
{
	// ������Դ
	CLocker Locker(m_CriticalSection);

	// ����ʱ��
	if (m_dwTimeLeave == NO_TIME_LEFT) 
	{
		ASSERT(m_TimerItemActive.GetCount() == 0);
		return;
	}

	// ����ʱ��
	ASSERT(m_dwTimeLeave >= m_dwTimerSpace);
	m_dwTimeLeave -= m_dwTimerSpace;
	m_dwTimePass += m_dwTimerSpace;

	// ��ѯ��ʱ��
	if (m_dwTimeLeave == 0)
	{
		bool bKillTimer = false;
		tagTimerItem* pTimerItem = NULL;
		DWORD dwTimeLeave = NO_TIME_LEFT;
		for (INT_PTR i = 0; i < m_TimerItemActive.GetCount() ;)
		{
			// Ч�����
			pTimerItem = m_TimerItemActive[i];
			ASSERT(pTimerItem != NULL);
			ASSERT(pTimerItem->dwTimeLeave >= m_dwTimePass);

			// ��ʱ������
			bKillTimer = false;
			pTimerItem->dwTimeLeave -= m_dwTimePass;
			if (pTimerItem->dwTimeLeave == 0L)
			{
				// ����֪ͨ
				if (m_pSinkWnd != NULL && m_pSinkWnd->GetSafeHwnd() != NULL)
				{
					// ���µ�ǰʱ��
					pTimerItem->dwCurrentTime = GetTickCount();
                    // (LPARAM)pTimerItem������ܻ���ͬ������,�����ͬ��Ҫ�����ʹ��CAnimationCtrl������Ϣ,��ȥռ�����̵߳���Ϣ����.
                    m_pSinkWnd->PostMessage(UM_TIMER_ENGINE, (WPARAM)pTimerItem->dwTimerID, (LPARAM)pTimerItem);
				}

				// ���ô���
				if (pTimerItem->dwRepeatTimes != TIMES_INFINITY)
				{
					ASSERT(pTimerItem->dwRepeatTimes > 0L);
					if (pTimerItem->dwRepeatTimes == 1L)
					{
						bKillTimer = true;
						m_TimerItemActive.RemoveAt(i);
						m_TimerItemFree.Add(pTimerItem);
						m_pSinkWnd->PostMessage(UM_TIMER_END, (WPARAM)pTimerItem->dwTimerID, (LPARAM)pTimerItem);
					}
					else pTimerItem->dwRepeatTimes--;
				}

				// ����ʱ��
				if (bKillTimer == false) pTimerItem->dwTimeLeave = pTimerItem->dwElapse;
			}

			// ��������
			if (bKillTimer == false) 
			{
				i++;
				dwTimeLeave = min(dwTimeLeave, pTimerItem->dwTimeLeave);
				ASSERT(dwTimeLeave % m_dwTimerSpace == 0);
			}
		}

		// ������Ӧ
		m_dwTimePass = 0L;
		m_dwTimeLeave = dwTimeLeave;
	}

	return;
}
