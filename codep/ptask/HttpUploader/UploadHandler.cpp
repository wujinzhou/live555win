#include ".\uploadhandler.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <map>
#include <windows.h>
using namespace std;

#include "RaProtocolStruct.h"
#include "RaProtoValue.h"
#include "debug.h"
#include "sysdata.h"
#include "httppost.h"
#include "nodeclient.h"

#include "mime.h"
//
//typedef FILE * (*FUN_fopen)(const char*, int, ...);
//typedef size_t (*FUN_fread)(int, void*, unsigned int);
//typedef size_t (*FUN_fwrite)(int, const void*, unsigned int);
//typedef int    (*FUN_fseek)(int, long, int);
//typedef  long  (*FUN_ftell)(int);
//typedef int    (*FUN_fclose)(int);
//typedef int    (*FUN_stat) (const char*, struct stat*);
//typedef  int   (*FUN_fstat) (int, struct stat*);


const string strServDir = "F:\\svn_mindmapdir\\Program\\gsdown_backup\\gsdown_090703\\bin\\debug\\website";

UploadHandler::UploadHandler(HttpUploader *pUploader)
{	
	//mimeinit();
	//string strMime = ext2mime("htm");
	m_pUploader = pUploader;
}

UploadHandler::~UploadHandler(void)
{
}

void RespMsg(SP_HttpResponse * response,const string &msg,const string &head=""){
	std::string strResp = (string)"<html><head><meta http-equiv=\"content-type\" content=\"text/html; charset=gbk\" /> <title>并行编译大师</title>" 
		+ head 
		+ "</head><body>" 
		+ msg 
		+ "</body></html>";
	response->addHeader("Content-Type","text/html; charset=GBK");
	response->appendContent((char *)strResp.c_str(),strResp.size());
}
void RespJson(SP_HttpResponse * response,const string &msg){
	//response->addHeader("Content-Type","text/html; charset=GBK");
	response->appendContent((char *)msg.c_str(),msg.size());
}


FILE *fp;
void findFile(const char filePath[], string &strRes )
{
	char szFind[MAX_PATH];//这是要找的
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	char szFile[MAX_PATH];

	strRes = "<ul>";

	strcpy(szFind,filePath);
	strcat(szFind,"\\*.*");//利用通配符找这个目录下的所以文件，包括目录

	hFind=FindFirstFile(szFind,&FindFileData);
	if(INVALID_HANDLE_VALUE == hFind)    return;

	while(TRUE)
	{

		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//这是目录
		{
			if(string(FindFileData.cFileName)!="."){
				strRes += (string)"<li><a href='" + FindFileData.cFileName + "/'>[目录]" + FindFileData.cFileName + "</a></li>";
			}
			
		}
		else
		{
			strRes += (string)"<li><a href='" + FindFileData.cFileName + "'>" + FindFileData.cFileName + "</a></li>";
		}
		
		if(!FindNextFile(hFind,&FindFileData))//寻找下一个文件
			break;
	}
	strRes += "</ul>";
	FindClose(hFind);//关闭句柄
}
//请求的格式如下："/getFile?id=%d&fid=%s&pos=%d&size=%d";
void UploadHandler::handle( SP_HttpRequest * request, SP_HttpResponse * response )
{

	string url = request->getURI();
	if(std::string("/")==url){
		url = "/index.htm"; //url重定向
	}
	else if(std::string("/nodestatus")==url){
		//addr、port、currtaskid、currtaskname、currtaskstate、waitingtaskcount等。
	}
	else if('/'==*url.rbegin()){
		string strRes;
		string strDir = strServDir + url;
		findFile(strDir.c_str(),strRes);
		RespMsg(response,strRes);
		return;
	}
	else if(std::string("/dir")==url){
		string strPath = request->getParamValue("path");
		string strRes;
		string strDir = strServDir + url;
		findFile(strDir.c_str(),strRes);
		RespMsg(response,strRes);
		return;
	}

	else if(std::string("/test")==url){
		std::string strApiUrl = "http://localhost:8080/status";
		httpPost hp(strApiUrl.c_str());
		hp.init();
		hp.doGet();
		std::string strRes = hp.getResult();
		std::cout<<strRes<<std::endl;
		response->appendContent(strRes.c_str());
		return;
	}

	else if(std::string("/status")==url){
		if(request->getParamValue("name")){
			string strName = request->getParamValue("name");
			if(string("mem")==strName){
				RespJson(response,SysData::GetMem());
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

		RespMsg(response,strRes,strHead);
		return;
	}
	//else{
		string full_path = strServDir + url;
		string ext = url.substr(url.rfind(".")+1);
		transform(ext.begin(),ext.end(),ext.begin(),tolower);
		string strMime = Mime::ext2mime(ext);
		if(!strMime.empty()){
			response->addHeader("Content-Type",strMime.c_str());
		}
		const char *fid = request->getParamValue("fid");
		const char *pos = request->getParamValue("pos");
		const char *size = request->getParamValue("size");
		int iPos = 0;
		unsigned int iSize = -1;
		if(pos){
			iPos = atoi(pos);
			iSize = atoi(size);
			if (iPos<0 || iSize<=0)
			{
				RespMsg(response,"文件位置或大小参数错误！");
				return;
			}
		}
		//////////////////////////////////////////////////////////////////////////
		//打开文件
		//////////////////////////////////////////////////////////////////////////
		std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
		if (!is)
		{
			RespMsg(response,"file not found!");
			return;
		}

		is.seekg(iPos);
		if(is.eof() || is.fail())  //fuck,seekg居然连个返回false都不做
		{
			RespMsg(response,"file error!");
			return;
		}		
		//发送数据体
		unsigned int iLeftSize = iSize;
		while (iLeftSize>0)
		{
			int iReadSize = is.read(m_pBuffer, min(iLeftSize,c_iBUFFER_SIZE)).gcount();
			iLeftSize -= iReadSize;
			if(iReadSize <= 0)
			{
				break;
			}
			response->appendContent(m_pBuffer, iReadSize);
		}
		return;
	//}
}

void UploadHandler::ReturnEmptyBlock( SP_HttpResponse * response, const MD5 &fid, int iPos)
{
	//构造数据包
	int iTotalReplyPackLen = sizeof(RaPack) +sizeof(RA_GetData_Ret);
	boost::shared_ptr<RaPack> pPackReply((RaPack *)malloc(iTotalReplyPackLen),free);
	pPackReply->byVersion = c_byVersion;
	pPackReply->dwCMDType = RA_C2C_GetData_Ret;
	pPackReply->dwProtoFlag = c_byProtoType_C2C;
	pPackReply->usLen = iTotalReplyPackLen;
	pPackReply->dwReceiverId = 0;
	pPackReply->dwSenderId = 0;

	RA_GetData_Ret *pGetDataRet = (RA_GetData_Ret *)pPackReply->ucData;
	pGetDataRet->mdChannelHash = fid;
	pGetDataRet->dwPos = iPos;
	pGetDataRet->dwDataLen = 0;

	response->appendContent((char *)pPackReply.get(),iTotalReplyPackLen);
}