#include ".\httpuploader.h"
#include "ServThread.h"
#include "UploadHandler.h"

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

void HttpUploader::setHomePath(const char *strPath)
{
	UploadHandler::setHomePath(strPath);
}

void HttpUploader::addHandler( const char *url,pfunHandler handler )
{
}

bool HttpUploader::AddUrlHandler( const char *url,pHttpHandler handler )
{
	UploadHandler::addHandler(url,handler);
	return true;
}