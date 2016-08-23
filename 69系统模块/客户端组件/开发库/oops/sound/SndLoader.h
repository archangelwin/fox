#ifndef _SndLoader_H_
#define _SndLoader_H_

#define AL_ERR_RETURN_ZERO(msg) \
{\
	ALenum eErr = alGetError();\
	if (eErr != AL_NO_ERROR)\
	{\
		const char* str = "<"##__FUNCTION__##"> "##msg##" : %s\n";\
		printf(str, alutGetErrorString(eErr));\
		return 0;\
	}\
}

#define AL_ERR_RETURN(msg) \
{\
	ALenum eErr = alGetError();\
	if (eErr != AL_NO_ERROR)\
	{\
		const char* str = "<"##__FUNCTION__##"> "##msg##" : %s\n";\
		printf(str, alutGetErrorString(eErr));\
		return ;\
	}\
}

#define ERR_RETURN_ZERO(expression, msg) \
{\
	if (expression)\
	{\
		printf("<"##__FUNCTION__##"> "##msg##"\n");\
		return 0;\
	}\
}

#define ERR_RETURN(expression, msg) \
{\
	if (expression)\
	{\
	printf("<"##__FUNCTION__##"> "##msg##"\n");\
	return ;\
	}\
}

/**
 * �����ļ�������
 */
class CSndLoader
{
public:
	CSndLoader(void);
	~CSndLoader(void);
	static unsigned int Load(const char* filename);
private:
	/** ����wav �ļ� */
	static unsigned int LoadWav(const char* filename);
	/** ����ogg �ļ� */
	static unsigned int LoadOgg(const char* filename);
};


#endif // _SndLoader_H_

