// UploaderTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "HttpUploader.h"
//#include "HttpBlockDownloader.h"
#include "IUploader.h"
//#include "udt.h"
//#include "UdtUploader.h"
#include "..\HttpUploader\spserver\sphttpmsg.hpp"
#include "debug.h"
#include "httpCpp.h"

const char *SafeGetParam(SP_HttpRequest * request,const char *name){
	const char *pData = request->getParamValue(name);
	if (pData)
	{
		return pData;
	}
	return "";
}

void testHandler(SP_HttpRequest * request, SP_HttpResponse * response){
	const char *url = SafeGetParam(request,"url");
	if(strlen(url)<=0){
		response->appendContent("add the param 'name', please!");
		return;
	}
	std::string strRes = httpCpp::httpget(url);
	//std::cout<<strRes<<std::endl;
	response->appendContent(strRes.c_str());
	return;
}

void handlerMain(SP_HttpRequest * request, SP_HttpResponse * response){
	response->appendContent("<html><title>aaa</title><body><font color=red>hello,girl!</font></body></html>");
	return;
}

bool TestHTTP()
{

	//IFileMng *pFileMng = new TestFileMng();
	HttpUploader uploader;
	//uploader.SetFileMng(pFileMng);
	uploader.StartServ();
	uploader.AddUrlHandler("/fetch",testHandler);
	uploader.AddUrlHandler("/",handlerMain);
	getchar();
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	TestHTTP();
	//TestUdt();
	getchar();
	return 0;
}

