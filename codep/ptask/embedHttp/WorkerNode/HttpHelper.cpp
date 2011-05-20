#include "HttpHelper.h"
#include "..\HttpUploader\spserver\sphttpmsg.hpp"

void HttpHelper::RespMsg( SP_HttpResponse * response,const string &msg,const string &head/*=""*/ )
{
	std::string strResp = (string)"<html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=gbk\" /> <title>并行编译大师</title>" 
		+ head 
		+ "</head><body>" 
		+ msg 
		+ "</body></html>";
	response->addHeader("Content-Type","text/html; charset=GBK");
	response->appendContent((char *)strResp.c_str(),(int)strResp.size());
}

void HttpHelper::RespJson( SP_HttpResponse * response,const string &msg )
{
	response->appendContent((char *)msg.c_str(),(int)msg.size());
}

const char * HttpHelper::SafeGetParam( SP_HttpRequest * request,const char *name )
{
	const char *pData = request->getParamValue(name);
	if (pData)
	{
		return pData;
	}
	return "";
}