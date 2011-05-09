#pragma once
#ifndef WIN32
#define WIN32
#endif

#include "spporting.hpp"
#include "spwin32iocp.hpp"
#include "spiocpserver.hpp"
#include "sphttp.hpp"
#include "sphttpmsg.hpp"
#include "spserver.hpp"

#pragma comment(lib,"ws2_32")
#pragma comment(lib,"mswsock")

#include "HttpUploader.h"
#include "md5.h"

//处理每个连接的缓冲区大小
//即每次读磁盘的大小。设置值太小可能导致读磁盘次数过多。太大则浪费内存。
const int c_iBUFFER_SIZE = 8*1024;

class UploadHandler :
	public SP_HttpHandler
{
public:
	UploadHandler(HttpUploader *pUploader);
	~UploadHandler(void);

	virtual void handle( SP_HttpRequest * request, SP_HttpResponse * response );
private:
	HttpUploader *m_pUploader;
	char m_pBuffer[c_iBUFFER_SIZE];
private:
	void ReturnEmptyBlock(SP_HttpResponse * response, const MD5 &fid, int iPos);
};
