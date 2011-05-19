#pragma once
#include "iuploader.h"
#include <map>
//#include "ServThread.h"
class ServThread;

#ifdef HTTPUPLOADER_EXPORTS
#define HTTPUPLOADER_DLL_EXPORTED __declspec(dllexport)
#else
#define HTTPUPLOADER_DLL_EXPORTED __declspec(dllimport)
#endif

class SP_HttpRequest;
class SP_HttpResponse;

typedef void (*pHttpHandler)(SP_HttpRequest * request, SP_HttpResponse * response);
typedef string (*pfunHandler)() ;

class HTTPUPLOADER_DLL_EXPORTED HttpUploader :
	public IUploader
{
public:
	HttpUploader(void);
	~HttpUploader(void);

	//�����ļ�������ָ�롣
	//Uploaderʹ�����������ļ��ڱ��صı���λ��
	//Ҫ�����ʱ����SetFileMng(NULL)
	void SetFileMng(IFileMng *pFileMng);

	//������������ģʽ��
	bool StartServ();

	//ֹͣ��������ģʽ��
	bool StopServ();

	//��ȡ�����ַ��
	//iType�������Э�����ͣ�0ΪUDT��1ΪTCP��2ΪHTTP
	bool GetServAddress(sockaddr *name, int &iLen, int &iType);

	//���Ӵ�������url����Ϊ������ʽ��
	bool AddUrlHandler(const char *url,pHttpHandler handler);


	void addHandler(const char *url,pfunHandler handler);

	IFileMng *GetFileMng();
private:
	IFileMng *m_pFileMng;
	ServThread *m_pThreadServ;
};
//
//IUploader * UploaderFactory::CreateHttpUploader(int iMyId, sockaddr *name, int iLen)
//{
//	return new HttpUploader();
//}
