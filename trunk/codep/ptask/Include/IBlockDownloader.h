#pragma once

#include <string>
#include <winsock2.h>

class IBlockListener;

//片段下载器
//目前只有三种片段下载器：UDT，HTTP，TCP。
class IBlockDownloader
{
public:
	//构造函数：文件ID（hash码），文件大小，分块大小
	IBlockDownloader(IBlockListener *pListener,const std::string &strFileID,
		int iFileSize, int iBlockSize=8*1024){};
	virtual ~IBlockDownloader(void){};

	//这样的接口难以保证线程安全，因此改为构造函数中传入 -tianzuo,6.25
	//设置消息接收接口。如果需要删除，将它设为NULL即可
	//void SetListener(IBlockListener *pListener);

	//尝试建立连接（异步）
	virtual bool Connect(int iDistID,sockaddr *name=NULL,int iLen=0) = 0;
	//virtual bool Connect(int iDistID ) = 0; //两个虚函数，父类要根据子类型确定调哪个，太麻烦。改用默认参数

	//下载文件片段（异步）
	//如果文件不存在，会在OnConnectMsg中得到报告
	virtual bool Download(int iBlockIndex) = 0;;
};

//IBlockDownloader消息和数据侦听接口
class IBlockListener
{
public:
	enum emDLMSG{
		DL_CONNECTED,
		DL_CONNECTFAIL,
		DL_FILENOTFOUND,
		DL_CONNECTBREAK,
	};
	//连接消息：连接建立，连接失败，文件不存在，连接断开等
	virtual void OnConnectMsg(IBlockDownloader *pDownloader,emDLMSG iMsgCode) = 0; 

	//数据到达消息。
	//注意iDataLen长度不一定等于BlockSize（文件最后一个片段的情况）
	virtual void OnBlock(int iuserID,int iBlockIndex,const char *pData,int iDataLen) = 0; //片段下载完成
};