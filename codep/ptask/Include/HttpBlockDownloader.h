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
	//���캯�����ļ�ID��hash�룩���ļ���С���ֿ��С
	HttpBlockDownloader(IBlockListener *pListener,const std::string &strFileID,int iFileSize, int iBlockSize=8*1024);;
	virtual ~HttpBlockDownloader(void);

	//���Խ������ӣ��첽��
	bool Connect(int iDistID,sockaddr *name=NULL,int iLen=0);

	//�����ļ�Ƭ�Σ��첽��
	//����ļ������ڣ�����OnConnectMsg�еõ�����
	bool Download(int iBlockIndex);
private:
	boost::shared_ptr<ThreadFire> m_pThreadFire;
	boost::shared_ptr<ThreadDownload> m_pThreadDownload;
};
