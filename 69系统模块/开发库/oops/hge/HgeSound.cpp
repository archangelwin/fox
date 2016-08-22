#include "Stdafx.h"
#include "hgesound.h"


int  CHgeSound::m_iVolume=100;

CHgeSound::CHgeSound(void)
{
}

CHgeSound::~CHgeSound(void)
{
}
//��ȡ����·��
void CHgeSound::LoadSound(HGE *hge,char* sound)
{
	m_hge=hge;
	m_Sound=m_hge->Effect_Load(sound);
}

//��������
void CHgeSound::PlaySound()
{
	if (m_iVolume==0)
	{
		return;
	}

	m_SoundChannel=m_hge->Effect_Play(m_Sound);
	m_hge->Channel_SetVolume(m_SoundChannel,m_iVolume);
}

//��������EX     ��������-100~100   �����ٶ�Ĭ��1.0  �Ƿ�ѭ������
void CHgeSound::PlaySoundEX(int pan,float pitch,bool loop)
{
	m_SoundChannel=m_hge->Effect_PlayEx(m_Sound,m_iVolume,pan,pitch,loop);
}

//��������
void CHgeSound::SetVolume(int volume)
{
	m_iVolume=volume;

	m_hge->Channel_SetVolume(m_SoundChannel,volume);
}

//��ȡ����
int  CHgeSound::GetVolume()
{
	return m_iVolume;
}

//��ͣ
void CHgeSound::PauseSound()
{
	m_hge->Channel_Pause(m_SoundChannel);
}

//�ָ�
void CHgeSound::ResumeSound()
{
	m_hge->Channel_Resume(m_SoundChannel);
}

//ֹͣ
void CHgeSound::StopSound()
{
	m_hge->Channel_Stop(m_SoundChannel);
}

//�Ƿ����ڲ���
bool CHgeSound::IsPlaying()
{
	return m_hge->Channel_IsPlaying(m_SoundChannel);
}

//��������
float CHgeSound::GetLength()
{
	return m_hge->Channel_GetLength(m_SoundChannel);
}

//���ò���λ��
void CHgeSound::SetPos(float fPos)
{
	return m_hge->Channel_SetPos(m_SoundChannel,fPos);
}

//��ǰ����λ��
float CHgeSound::GetPos()
{
	return m_hge->Channel_GetPos(m_SoundChannel);
}