
#include "StdAfx.h"
#include "Locker.h"

//���캯��
CLocker::CLocker(CCriticalSection& CriticalSection, bool bLockAtOnce) 
	: m_CriticalSection(CriticalSection)
{
	// ���ñ���
	m_nLockCount = 0;

	// ��������
	if (bLockAtOnce == true)
	{
		Lock();
	}

	return;
}

// ��������
CLocker::~CLocker()
{
	// �������
	while (m_nLockCount > 0)
	{
		UnLock();
	}

	return;
}

// ��������
VOID CLocker::Lock()
{
	// ��������
	m_CriticalSection.Lock();

	// ���ñ���
	m_nLockCount++;

	return;
}

// ��������
VOID CLocker::UnLock()
{
	// Ч��״̬
	ASSERT(m_nLockCount > 0);
	if (m_nLockCount == 0) return;

	// ���ñ���
	m_nLockCount--;

	// �������
	m_CriticalSection.Unlock();

	return;
}