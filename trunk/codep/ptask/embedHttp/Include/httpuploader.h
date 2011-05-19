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

	//设置文件管理器指针。
	//Uploader使用它来查找文件在本地的保存位置
	//要拆除的时候，用SetFileMng(NULL)
	void SetFileMng(IFileMng *pFileMng);

	//启动服务（阻塞模式）
	bool StartServ();

	//停止服务（阻塞模式）
	bool StopServ();

	//获取服务地址。
	//iType代表服务协议类型，0为UDT，1为TCP，2为HTTP
	bool GetServAddress(sockaddr *name, int &iLen, int &iType);

	//增加处理器。url允许为正则表达式。
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
