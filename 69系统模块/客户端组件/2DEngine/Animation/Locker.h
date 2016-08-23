
#ifndef LOCKER_H_
#define LOCKER_H_
#pragma once

// ��������
class CLocker
{
	// ��������
public:
	// ���캯��
	CLocker(CCriticalSection& CriticalSection, bool bLockAtOnce = true);
	// ��������
	virtual ~CLocker();

	// ��������
public:
	// ��������
	VOID Lock();
	// �������� 
	VOID UnLock();

	// ״̬����
public:
	// ��������
	inline INT GetLockCount() { return m_nLockCount; }

	// ��������
private:
	INT m_nLockCount; // ��������
	CCriticalSection& m_CriticalSection; // ��������
};

#endif // LOCKER_H_