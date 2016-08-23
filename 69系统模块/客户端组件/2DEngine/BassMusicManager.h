
#ifndef BASS_MUSIC_MANAGER_H_
#define BASS_MUSIC_MANAGER_H_
#pragma once

#include <map>

//ǰ���������������bass.h
typedef DWORD HSTREAM;
typedef DWORD HSYNC;

// ������Դ�ṹ��
typedef struct
{
	// HSTREAM
	HSTREAM hStream;
	// �Ƿ�ѭ������, ע�⣺�˲���������bDeleteWhenStopͬʱΪtrue
	bool bLoop;
} tagMusicStream;

// ������Դ������
// �����Ե���ģʽʵ�ֵ�,���Թ������������������Դ�Ĳ��š���ͣ�Ȳ���
class CBassMusicManager
{
public:
	// ��������
	~CBassMusicManager();

	// ��ȡ�����������ָ��
	static CBassMusicManager* GetInstance();

	// ���ô��ھ��
	bool Init(HWND hWnd);

	// �ͷ���Դ
	void ReleaseAll();
	
	// ���ļ��м�������
	// nID: ������־ID�����ݴ˱�־�����Ժ���Ӧ�Ĳ������粥�ţ���ͣ��
	// lpszFileName: �ļ�·��
	// bLoop: �Ƿ�ѭ����Ĭ��:false
	bool LoadFromFile(const int nID, LPCTSTR lpszFileName, bool bLoop = false);

	// ���ڴ��м�������
	// nID: ������־ID�����ݴ˱�־�����Ժ���Ӧ�Ĳ������粥�ţ���ͣ��
	// pBuffer: �ڴ��ַ
	// dwLength: ����
	// bLoop: �Ƿ�ѭ����Ĭ��:false
	bool LoadFromMemory(const int nID, void* pBuffer, DWORD dwLength, bool bLoop = false);

	// ����Դ�м�������
	// nID: ������־ID�����ݴ˱�־�����Ժ���Ӧ�Ĳ������粥�ţ���ͣ��
	// lpszResourceName: ��Դ��
	// hInst: ��Դ���
	// lpszResourceType: ��Դ���� Ĭ��:TEXT("Sound")
	// bLoop: �Ƿ�ѭ����Ĭ��:false
	bool LoadFromResource(const int nID, LPCTSTR lpszResourceName, HINSTANCE hInst, bool bLoop = false, LPCTSTR lpszResourceType = TEXT("Sound"));

	// ����ָ����־������
	// nID: ������־ID
	// bDeleteWhenStop: ������ɺ��Ƿ�ɾ����Դ��Ĭ��false
	bool Play(const int nID, bool bDeleteWhenStop = false);

	// ��ͷ���²���ָ����־������
	// nID: ������־ID
	// bDeleteWhenStop ������ɺ��Ƿ�ɾ����Դ��Ĭ��false
	bool RePlay(const int nID, bool bDeleteWhenStop = false);

	// ��ͣ
	bool Pause(const int nID);

	// ֹͣ
	bool Stop(const int nID);

	// �Ƿ��ڲ���
	bool IsPlaying(const int nID);

	// ����������С
	// ������С��ȡֵ��Χ0~100
	bool SetVolumn(int nVolumn);
	//bool SetVolumn(const int nID, int nVolumn);

protected:
	// �ص�����
	static void CALLBACK MySyncProc(HSYNC handle, DWORD channel, DWORD data, DWORD user);

	bool _Play(const int nID, bool bReplay = false, bool bDeleteWhenStop = true);

protected:
	// ���캯��
	CBassMusicManager();

private:
	// HSTREAM����
	static std::map<int, tagMusicStream> m_mapPlayingStream;	
	// ��Ҫ�ͷ�HSTREAM��Դ������
	static std::map<int, tagMusicStream> m_mapNeedDeleteStream;
	// ��ָ��
	static CBassMusicManager* ms_Instance;
	// ����ָ��
	HWND m_hWnd;
};

#endif // BASS_MUSIC_MANAGER_H_
