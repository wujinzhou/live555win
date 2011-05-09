#include ".\httpuploader.h"
#include "ServThread.h"

HttpUploader::HttpUploader(void)
{
	m_pThreadServ = new ServThread(this);
}

HttpUploader::~HttpUploader(void)
{
	if (m_pThreadServ)
	{
		delete m_pThreadServ;
	}
}

void HttpUploader::SetFileMng( IFileMng *pFileMng )
{
	m_pFileMng = pFileMng;
}

bool HttpUploader::StartServ()
{
	return 0==m_pThreadServ->Start();
}

bool HttpUploader::StopServ()
{
	m_pThreadServ->shutdown();
	return true;
}

bool HttpUploader::GetServAddress( sockaddr *name, int &iLen, int &iType )
{
	return false;
}

IFileMng * HttpUploader::GetFileMng()
{
	return m_pFileMng;
}