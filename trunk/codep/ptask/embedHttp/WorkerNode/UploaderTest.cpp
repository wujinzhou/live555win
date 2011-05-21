// UploaderTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "HttpUploader.h"

#include <string>
using namespace std;

#include "IUploader.h"
#include "..\HttpUploader\spserver\sphttpmsg.hpp"
#include "debug.h"
#include "httpCpp.h"

#include "SysData.h"
#include "NodeClient.h"
#include "HttpHelper.h"

void testHandler(SP_HttpRequest * request, SP_HttpResponse * response){
	const char *url = HttpHelper::SafeGetParam(request,"url");
	if(strlen(url)<=0){
		response->appendContent("add the param 'url', please!");
		return;
	}
	std::string strRes = httpCpp::httpget(url);
	response->appendContent(strRes.c_str());
	return;
}

void handlerTestIp(SP_HttpRequest * request, SP_HttpResponse * response){
	string strResp = (string)"<html><title>aaa</title><body><font color=red>hello,girl!" +
		request->getClientIP() +
		"</font></body></html>";
	response->appendContent(strResp.c_str());
	return;
}

void handlerAddTask(SP_HttpRequest * request, SP_HttpResponse * response){
		string type = request->getParamValue("type");
		string taskname = request->getParamValue("name");

		NodeClientMap::UpdateNode(request->getClientIP(),"0","",taskname,"",0);
		response->appendContent("['addtask',0,1234,'task added!']");
		return;
	}
void handlerGetStatus(SP_HttpRequest * request, SP_HttpResponse * response){
		string status = NodeClientMap::ToJson();
		response->appendContent(status.c_str());
		return;
	}
void handlerServerStatus(SP_HttpRequest * request, SP_HttpResponse * response){
	if(request->getParamValue("name")){
		string strName = request->getParamValue("name");
		if(string("mem")==strName){
			HttpHelper::RespJson(response,SysData::GetMem());
			return;
		}
	}
}

void handlerMain(SP_HttpRequest * request, SP_HttpResponse * response){
}

bool TestHTTP()
{
	HttpUploader uploader;
	uploader.StartServ();
	uploader.AddUrlHandler("/",handlerMain);
	uploader.AddUrlHandler("/addtask",handlerAddTask);
	uploader.AddUrlHandler("/getstatus",handlerGetStatus);
	uploader.AddUrlHandler("/serverstatus",handlerServerStatus);

	uploader.AddUrlHandler("/fetch",testHandler);
	uploader.AddUrlHandler("/test",handlerTestIp);

	getchar();
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	TestHTTP();
	getchar();
	return 0;
}

