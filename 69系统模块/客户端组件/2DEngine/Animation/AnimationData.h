
#ifndef ANIMATION_DATA_H_
#define ANIMATION_DATA_H_
#pragma once

#include "tween.h"

// ��������
class CAnimationData
{
public:
	// ���캯��
	CAnimationData();
	// ���캯��
	~CAnimationData();

	// ���ú���
public:
	// ��ʼ����
	void InitAnimationData(DWORD dwDuration, const CPoint& ptStartPos, const CPoint& ptTargetPos, Tween::Type type = Tween::LINEAR);
	// ���ó���ʱ��
	void SetDuration(DWORD dwDuration);
	// ������ʼλ��
	void SetStartPos(const CPoint& ptStartPos);
	// ����Ŀ��λ��
	void SetTargetPos(const CPoint& ptTargetPos);
	// ���ò�������
	void SetTweenType(Tween::Type type);
	// ��������
	void SetReverse(bool bReverse);
	// ����
	void ResetAnimationData();

	// ��ѯ����
public:
	// �õ���ǰλ��
	CPoint GetCurrentPos(DWORD dwStartTime, DWORD dwCurrentTime);
	// ��������
	bool IsAnimationEnd() { return m_bAnimationEnd; }
	// �õ���ʼλ��
	const CPoint& GetStartPos() const { return m_ptStartPos; }
	// �õ�Ŀ��λ��
	const CPoint& GetTargetPos() const { return m_ptTargetPos; }
	// �Ƿ�����
	bool IsReverse() { return m_bReverse; }

private:
	DWORD m_dwDuration; // ����ʱ��
	CPoint m_ptStartPos; // ��ʼλ��
	CPoint m_ptTargetPos; // Ŀ��λ��
	Tween::Type m_TweenType; // ��������
	bool m_bReverse; // ����(Ŀ��λ�õ���ʼλ��)
	bool m_bAnimationEnd; // ��������
};

#endif // ANIMATION_DATA_H_
