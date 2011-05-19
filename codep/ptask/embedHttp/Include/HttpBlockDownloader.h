#pragma once
#include "iblockdownloader.h"
#include <boost/shared_ptr.hpp>

#ifdef HTTPBLOCKDOWNLOADER_EXPORTS
#define HTTPBLOCKDOWNLOADER_DLL_EXPORTED __declspec(dllexport)
#else
#define HTTPBLOCKDOWNLOADER_DLL_EXPORTED __declspec(dllimport)
#endif

class ThreadFire;
class ThreadDownload;

class HTTPBLOCKDOWNLOADER_DLL_EXPORTED HttpBlockDownloader :
	public IBlockDownloader
{
public:
	//构造函数：文件ID（hash码），文件大小，分块大小
	HttpBlockDownloader(IBlockListener *pListener,const std::string &strFileID,int iFileSize, int iBlockSize=8*1024);;
	virtual ~HttpBlockDownloader(void);

	//尝试建立连接（异步）
	bool Connect(int iDistID,sockaddr *name=NULL,int iLen=0);

	//下载文件片段（异步）
	//如果文件不存在，会在OnConnectMsg中得到报告
	bool Download(int iBlockIndex);
private:
	boost::shared_ptr<ThreadFire> m_pThreadFire;
	boost::shared_ptr<ThreadDownload> m_pThreadDownload;
};
