#pragma once

#include "HgeHeader.h"

//HGE��Ч ֧�ֵĸ�ʽ��WAV, MP3, MP2, MP1 ��OGG��
class CHgeSound
{
	HEFFECT			m_Sound;			//��Ч���

	HCHANNEL		m_SoundChannel;		//���Ƶͨ�����

	HGE				*m_hge;


 static	int			m_iVolume;			//��ǰ����

public:
	CHgeSound(void);
	~CHgeSound(void);

	//��ȡ����·��
	void LoadSound(HGE *hge,char* sound);

	//��������
	void PlaySound();

	//��������EX   ��������-100~100   �����ٶ�Ĭ��1.0  �Ƿ�ѭ������
	void PlaySoundEX(int pan=0,float pitch=1.0f,bool loop=false);

	//��������
	void SetVolume(int volume);

	//��ȡ����
	int  GetVolume();

	//��ͣ
	void PauseSound();

	//�ָ�
	void ResumeSound();

	//ֹͣ
	void StopSound();

	//�Ƿ����ڲ���
	bool IsPlaying();

	//��������
	float GetLength();

	//���ò���λ��
	void SetPos(float fPos);

	//��ǰ����λ��
	float GetPos();

};
