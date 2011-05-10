#pragma once
#include <string>
#include <winsock2.h>
#include "udt.h"
#include "IFileMng.h"

//////////////////////////////////////////////////////////////////////////
//上传器接口
//目前有三种上传器，其创建过程稍有不同，但使用流程类似
class IUploader
{
public:
	IUploader(void){};
	virtual ~IUploader(void){};

	//设置文件管理器指针。
	//Uploader使用它来查找文件在本地的保存位置
	//要拆除的时候，用SetFileMng(NULL)
	virtual void SetFileMng(IFileMng *pFileMng)=0;

	//启动服务（阻塞模式）
	virtual bool StartServ()=0;

	//停止服务（阻塞模式）
	virtual bool StopServ()=0;

	//获取服务地址。
	//iType代表服务协议类型，0为UDT，1为TCP，2为HTTP
	virtual bool GetServAddress(sockaddr *name, int &iLen, int &iType) = 0;
};

//class IFileMng
//{
//public:
//	//根据文件ID（hash）查找出文件本地保存路径。
//	//文件不存在则返回空路径。
//	virtual std::string FindFilePath(const std::string &strFileID) = 0;
//};

//////////////////////////////////////////////////////////////////////////
//IUploader工厂，不同的Uploader的创建参数不一样。
class TPeerMng;
class UploaderFactory
{
public:
	static IUploader *CreateTCPUploader(int iMyId, sockaddr *name, int iLen);
	static IUploader *CreateHttpUploader(int iMyId, sockaddr *name, int iLen);
	static IUploader *CreateUdtUploader(UDT::TPeerMng *pPeerMng);
};