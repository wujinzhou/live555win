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

void handlerMain(SP_HttpRequest * request, SP_HttpResponse * response){
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
void handlerStatus(SP_HttpRequest * request, SP_HttpResponse * response){
		if(request->getParamValue("name")){
			string strName = request->getParamValue("name");
			if(string("mem")==strName){
				HttpHelper::RespJson(response,SysData::GetMem());
				return;
			}
		}
		string strRes;
		strRes += "<table>";
		strRes += "<tr><td>CPU:</td><td>" + SysData::GetCpu() + "</td></tr>";
		strRes += "<tr><td>LAN:</td><td>" + SysData::GetLan() + "</td></tr>";
		strRes += "<tr><td>MAC:</td><td>" + SysData::GetMac() + "</td></tr>";
		strRes += "<tr><td>MEM:</td><td><span id='mem'>" + SysData::GetMem() + "</span></td></tr>";
		strRes += "<tr><td>SYS:</td><td>" + SysData::GetOperaSystem() + "</td></tr>";
		strRes += "<tr><td>SCR:</td><td>" + SysData::GetScreen() + "</td></tr>";
		strRes += "</table>";

		string strHead = "<script type=\"text/javascript\" src=\"/static/js/jquery-1.3.2.min.js\"></script>";
		strHead += "<script type=\"text/javascript\" src=\"/static/jtimer.js\"></script>";

		HttpHelper::RespMsg(response,strRes,strHead);
		return;
	}

bool TestHTTP()
{
	HttpUploader uploader;
	uploader.StartServ();
	uploader.AddUrlHandler("/fetch",testHandler);
	uploader.AddUrlHandler("/test",handlerMain);
	uploader.AddUrlHandler("/addtask",handlerAddTask);
	uploader.AddUrlHandler("/getstatus",handlerGetStatus);
	uploader.AddUrlHandler("/status",handlerStatus);

	getchar();
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	TestHTTP();
	getchar();
	return 0;
}

