
#ifndef THREAD_H_
#define THREAD_H_
#pragma once

// �̶߳���
class CThread
{
	// ��������
protected:
	// ���캯��
	CThread();
	// ��������
	virtual ~CThread();

	// �ӿں���
public:
	// ��ȡ״̬
	virtual bool IsRuning();
	// �����߳�
	virtual bool StartThread();
	// ��ֹ�߳�
	virtual bool ConcludeThread(DWORD dwMillSeconds);

	// ���ܺ���
public:
	// �̱߳�ʶ
	UINT GetThreadID() { return m_uThreadID; }
	// �߳̾��
	HANDLE GetThreadHandle() { return m_hThreadHandle; }
	// Ͷ����Ϣ
	LRESULT PostThreadMessage(UINT uMessage, WPARAM wParam, LPARAM lParam);

	// �¼�����
protected:
	// �����¼�
	virtual bool OnEventThreadRun() { return true; }
	// ��ʼ�¼�
	virtual bool OnEventThreadStrat() { return true; }
	// ��ֹ�¼�
	virtual bool OnEventThreadConclude() { return true; }

	// �ڲ�����
private:
	// �̺߳���
	static unsigned __stdcall ThreadFunction(LPVOID pThreadData);

	// ״̬����
private:
	volatile bool m_bRun; // ���б�־

	// �̱߳���
private:
	UINT m_uThreadID; // �̱߳�ʶ
	HANDLE m_hThreadHandle;	// �߳̾��
};

#endif // THREAD_H_