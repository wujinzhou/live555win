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

//����ÿ�����ӵĻ�������С
//��ÿ�ζ����̵Ĵ�С������ֵ̫С���ܵ��¶����̴������ࡣ̫�����˷��ڴ档
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
