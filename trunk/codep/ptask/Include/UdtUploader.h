#pragma once
#include "iuploader.h"
#include "udt.h"
class GetFilePackHandler;
class UDT::TPeerMng;


#ifdef UDTUPLOADER_EXPORTS
#define UDTUPLOADER_DLL_EXPORTED __declspec(dllexport)
#else
#define UDTUPLOADER_DLL_EXPORTED __declspec(dllimport)
#endif

class UDTUPLOADER_DLL_EXPORTED UdtUploader :
	public IUploader,public UDT::IPeerDataListener
{
public:
	UdtUploader(UDT::TPeerMng *pPeerMng);
	~UdtUploader(void);

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

	IFileMng *GetFileMng();

public:
	//IPeerDataListener回调函数
	virtual void  OnPeerData(int iPeerId,const char* pData, int ilen);
private:
	UDT::TPeerMng *m_pPeerMng;
	IFileMng *m_pFileMng;
};

IUploader * UploaderFactory::CreateUdtUploader(UDT::TPeerMng *pPeerMng)
{
	return new UdtUploader(pPeerMng);
}
