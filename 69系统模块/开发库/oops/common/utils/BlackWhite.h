#ifndef _utils_BlackWhite_H_
#define _utils_BlackWhite_H_
//�ڰ�����
namespace BW
{
	/**
	 * param config:·������
	 * param id:�û�id
	 * param code:0 ������, 1 ������, ����ɾ������
	 */
	inline bool Set(const TCHAR* config, DWORD id, unsigned char operate_code) 
	{
		TCHAR key[128]={0};
		_sntprintf(key, 128, TEXT("%d"), id);
		switch (operate_code)
		{
		case 0: return WritePrivateProfileString(TEXT("DATA"), key, TEXT("0"), config) == TRUE;
		case 1: return WritePrivateProfileString(TEXT("DATA"), key, TEXT("1"), config) == TRUE;
		default:
			break;
		}

		return WritePrivateProfileString(TEXT("DATA"), key, NULL, config) == TRUE;
	} // Set

	/**
	 * param config:·������
	 * param id:�û�id
	 * return int [0:������, 1:������, -1:������]
	 */
	inline int Get(const TCHAR* config, DWORD id) 
	{
		TCHAR key[128]={0};
		_sntprintf(key, 128, TEXT("%d"), id);
		int iRet = GetPrivateProfileInt(TEXT("DATA"), key, -1, config);
		switch (iRet)
		{
		case 0:
		case 1:
			return iRet;
		}

		return -1;
	} // Get
} // BW
#endif // _utils_BlackWhite_H_