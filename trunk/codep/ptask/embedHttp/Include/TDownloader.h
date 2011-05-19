#pragma once
#include "IDownloadMng.h"
#include "IDownloadNotify.h"
#include "udt.h"

class DownloaderImp;

#ifdef TDOWNLOADER_EXPORTS
#define TDOWNLOADER_DLL_EXPORTED __declspec(dllexport)
#else
#define TDOWNLOADER_DLL_EXPORTED __declspec(dllimport)
#endif

class TDOWNLOADER_DLL_EXPORTED TDownloader
	: public IDownloadMng
{
public:
	TDownloader(UDT::TPeerMng *pPeerMng);
	~TDownloader(void);

	//IDownloadMngµÄ½Ó¿Ú
	virtual bool AddTask(MD5 hash,string filePath,T_vectUser userlist);
	virtual bool DelTask(MD5 fileHash);
	virtual bool PauseTask(MD5 hash);
	virtual ITask* GetTask(MD5 fileHash);
private:
	DownloaderImp *m_pDownloaderImp;
};
