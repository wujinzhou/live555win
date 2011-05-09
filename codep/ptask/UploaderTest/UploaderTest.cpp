// UploaderTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "HttpUploader.h"
#include "HttpBlockDownloader.h"
#include "IUploader.h"
//#include "udt.h"
//#include "UdtUploader.h"

#include "debug.h"

#include "RaProtocolStruct.h"
#include "RaProtoValue.h"

class TestFileMng
	:public IFileMng
{
public:
	//std::string FindFilePath(const std::string &strFileID)
	//{
	//	return "E:\\WILD.txt";
	//}


	//##ModelId=4A3DA85C033C
	virtual bool StartCheck(IFileMngNotify *pFileMngNotify){return 0;};
	//##ModelId=4A3DA8DA02BF
	virtual bool AbortCheck() {return 0;};

	//##ModelId=4A3DA8E80148
	virtual string GetFilePathFromHash(MD5& hash) 
	{
		return "E:\\WILD.txt";
	}

	//##ModelId=4A3DA902030D
	virtual bool AddFileRecord(MD5& hash,string& filePath) {return 0;};

	//##ModelId=4A3DA902030D
	//virtual bool AddFileRecords(MD5& hash,string& filePath) = 0;

	//##ModelId=4A3DA90A036B
	virtual bool DelFileRecord(MD5& hash) {return 0;};

	//##ModelId=4A3DA9490271
	virtual bool GetFileList(Vc_FileList& fileList) {return 0;};

};
class TestBlockListener:
	public IBlockListener
{
public:
	//连接消息：连接建立，连接失败，文件不存在，连接断开等
	virtual void OnConnectMsg(IBlockDownloader *pDownloader,emDLMSG iMsgCode)
	{

	}

	//数据到达消息。
	//注意iDataLen长度不一定等于BlockSize（文件最后一个片段的情况）
	virtual void OnBlock(int iuserID,int iBlockIndex,const char *pData,int iDataLen)  //片段下载完成
	{
		;
	}
 
};

bool TestHTTP()
{
	IFileMng *pFileMng = new TestFileMng();
	HttpUploader uploader;
	uploader.SetFileMng(pFileMng);
	uploader.StartServ();

	TestBlockListener listener;
	HttpBlockDownloader downloader(&listener,std::string("/static/sunbird.bmp"),10240);

	//SOCKADDR_IN addr;
	//addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//addr.sin_port = 8080;
	//downloader.Connect(0,(sockaddr *)&addr,sizeof(addr));
	//downloader.Download(0);

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

