#pragma once
#include "..\HttpUploader\spserver\sphttpmsg.hpp"

#include <string>
using namespace std;

class HttpHelper
{
public:
	static void RespMsg(SP_HttpResponse * response,const string &msg,const string &head="");
	static void RespJson(SP_HttpResponse * response,const string &msg);
	static const char *SafeGetParam(SP_HttpRequest * request,const char *name);

};
