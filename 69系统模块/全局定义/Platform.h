#ifndef PLATFORM_HEAD_FILE
#define PLATFORM_HEAD_FILE

//////////////////////////////////////////////////////////////////////////////////
//�����ļ�

//�����ļ�
#include "Macro.h"
#include "Define.h"

//�ṹ�ļ�
#include "Struct.h"
#include "Packet.h"
#include "Property.h"

//ģ���ļ�
#include "Array.h"
#include "Module.h"
#include "PacketAide.h"
#include "ServerRule.h"
#include "RightDefine.h"

//////////////////////////////////////////////////////////////////////////////////

//����汾
#define VERSION_FRAME				PROCESS_VERSION(6,0,3)				//��ܰ汾
#define VERSION_PLAZA				PROCESS_VERSION(6,0,3)				//�����汾
#define VERSION_MOBILE_ANDROID		PROCESS_VERSION(6,0,3)				//�ֻ��汾
#define VERSION_MOBILE_IOS			PROCESS_VERSION(6,0,3)				//�ֻ��汾

//�汾����
#define VERSION_EFFICACY			0									//Ч��汾
#define VERSION_FRAME_SDK			INTERFACE_VERSION(6,3)				//��ܰ汾

//////////////////////////////////////////////////////////////////////////////////
//�����汾

#ifndef _DEBUG

//ƽ̨����
const TCHAR szProduct[]=TEXT("������Ϸ����");							//��Ʒ����
const TCHAR szPlazaClass[]=TEXT("GamePlaza");						//�㳡����
const TCHAR szProductKey[]=TEXT("GamePlatform");					        //��Ʒ����

//��ַ����
const TCHAR szCookieUrl[]=TEXT("http://www.85jn.com");						//��¼��ַ
const TCHAR szLogonServer[]=TEXT("www.85jn.com");					//��¼��ַ
const TCHAR szPlatformLink[]=TEXT("http://www.85jn.com");			//ƽ̨��վ
const TCHAR szDownloadLink[]=TEXT("http://www.85jn.com:5123");			//������վ

#else

//////////////////////////////////////////////////////////////////////////////////
//�ڲ�汾

//ƽ̨����
const TCHAR szProduct[]=TEXT("�¸���Ϸ����");							//��Ʒ����
const TCHAR szPlazaClass[]=TEXT("GamePlaza");						//�㳡����
const TCHAR szProductKey[]=TEXT("GamePlatform");					        //��Ʒ����

//��ַ����
const TCHAR szCookieUrl[]=TEXT("http://client.xf92.com");						//��¼��ַ
const TCHAR szLogonServer[]=TEXT("www.xf92.com");					//��¼��ַ
const TCHAR szPlatformLink[]=TEXT("http://client.xf92.com");			//ƽ̨��վ
const TCHAR szDownloadLink[]=TEXT("http://www.xf92.com");			//������վ


#endif

//////////////////////////////////////////////////////////////////////////////////

//���ݿ���
const TCHAR szPlatformDB[]=TEXT("QPPlatformDB");						//ƽ̨���ݿ�
const TCHAR szAccountsDB[]=TEXT("QPAccountsDB");						//�û����ݿ�
const TCHAR szTreasureDB[]=TEXT("QPTreasureDB");						//�Ƹ����ݿ�
const TCHAR szExerciseDB[]=TEXT("QPEducateDB");						    //��ϰ���ݿ�

//////////////////////////////////////////////////////////////////////////////////

//��Ȩ��Ϣ
const TCHAR szCompilation[]=TEXT("B88D16CB-B4C4-4DD3-B44D-2885C9BF8C74");

//////////////////////////////////////////////////////////////////////////////////

#endif