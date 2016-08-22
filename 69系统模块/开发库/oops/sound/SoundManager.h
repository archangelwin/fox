#ifndef _SoundManager_H_
#define _SoundManager_H_

/**
 * ����������
 */
class CSoundManager
	//: public CEventDispatcher
{
public:
	CSoundManager(void);
	~CSoundManager(void);
	/**
	 * ��ʼ��
	 */
	void Init();
	/**
	 * ��� 
	 */
	void Deinit();
	/**
	 * ��������
	 * @param filename:�ļ�·��
	 * @return ����id 0:����ʧ��
	 */
	unsigned int CreateSound(const char* filename);
	/**
	 * ����ȫ������
	 * @param volume:����ֵ[0-1.0]
	 */
	void SetVolume(float volume);
	/**
	 * ��������λ��(��������ϵ)
	 */
	void SetListenerPosition(float x, float y, float z);
	/**
	 * �������߷���(��������ϵ)
	 */
	void SetListenerOrientation(float x, float y, float z);
	/**
	 * ֹͣ������������
	 * @param type: 0:��ɾ���������� 1:ֻɾ����������ѭ������
	 */
	void StopAll(int type = 0);
	//////////////////////////////////////////////////////////////////////////
	/**
	 * ��������
	 * @param id:����id
	 * @param volume:����ֵ[0-1.0]
	 */
	void SetVolume(unsigned int id, float volume);
	/**
	 * ��������
	 * @param pitch:����ֵ[0-1.0]
	 */
	void SetPitch(unsigned int id, float pitch);
	/**
	 * �����Ƿ�ѭ������
	 * @param id:����id
	 * @param iRepeat:ѭ������ 0:��ʾ����ѭ��
	 */
	void SetRepeat(unsigned int id, unsigned int iRepeat);
	/** 
	 * ����λ��(��������ϵ)
	 * @param id:����id
	 * @param 
	 */
	void SetPosition(unsigned int id, float x, float y, float z);
	/** 
	 * ����
	 * @param id:����id
	 */
	void Play(unsigned int id);
	/**
	 * ��ͣ 
	 * @param id:����id
	 */
	void Pause(unsigned int id);
	/** 
	 * ֹͣ
	 * @param id:����id
	 */
	void Stop(unsigned int id);
private:
	CSoundManager(const CSoundManager&);
	CSoundManager& operator=(const CSoundManager&);
	/** ���µ�ѭ���б��� */
	void UpdateToLoopList(unsigned int id);
	/** ����״̬ */
	void Update();
	//�̺߳���
	static unsigned int __stdcall ThreadFunction(void* pData);
private:
	struct SData;
	SData* m_pData;
private:
	friend class CSoundChannel;
}; // CSoundManager

extern CSoundManager g_SoundManager;

#endif // _SoundManager_H_
