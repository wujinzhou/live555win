#pragma once
#include <vector>
#include <string>
/*
频道配置：子流数量、帧大小
传输块头：视频帧开始位置
文件头：是否关键帧
视频帧头：

这四者的关系是，一个频道的数据，由频道配置数据和频道传输数据组成；
频道传输数据由一个个长度固定的传输块组成。
传输块由传输块头和传输块体组成。
一个个传输块体按顺序组装起来，就是实际传输的媒体数据流。
媒体数据流是由多个顺序播放的视频文件组成的。
每一个视频文件都有文件头，保存它的文件格式和一些必要的播放信息，并且有文件索引号（在一路频道中，这个索引号是顺序递增的）。
视频文件是由一个个长度可变的视频帧组成的。视频帧也分为帧头和帧体。
*/

//==========================================
//BufferManager的对外接口
//==========================================


#ifdef BUFFERMAP_EXPORTS
#define BUFFERMAP_DLL_EXPORTED __declspec(dllexport)
#else
#define BUFFERMAP_DLL_EXPORTED __declspec(dllimport)
#endif

#ifndef __BUFFERMAP_H
#define __BUFFERMAP_H


#pragma warning( disable : 4200)	//关闭微软非标准扩展警告
#pragma pack(1)	//把字节对齐方式设为1字节

//数据块格式
struct TRawBlock
{
	int iBlockLen;         //块大小：注意，包括数据头大小sizeof(TRawBlock)
	int iFirstPackPos;     //第一个包的位置
	int iBlockIndex;       //本块序号
	char data[];
};


//数据包格式
struct TRawPack
{
	int iLen;              //包大小
	unsigned short usFileIndex;      //文件index：传输的数据由一个个文件组成，每个文件一个index
	unsigned short usFileSliceIndex; //文件片段index：一个文件的数据被分为一个个slice，每个slice一个index
	char type;	           //目前已定义的包类型有：帧头；关键帧；非关键帧；结束帧。见PACK_TYPE定义。
	char cReserved;        //保留字段
	char data[];

	//包类型定义
	enum PACK_TYPE{
		PT_HEADER = 0,      //文件头
		PT_KEYFRAME = 1,    //关键帧
		PT_NORMALFRAME = 2, //普通帧
		PT_STOPFRAME = 3,   //停止帧
	};
};

#pragma pack ()	//字节对齐方式设回默认值

//监听BufferManager的消息
class IBufferMonitor
{
public:
	virtual ~IBufferMonitor(){};

	//当有新的块到达
	virtual void OnBufferAdded(int iBlockIndex,const char *pData,int iLen) = 0;//缺少长度字段
};

class BlockBufferManager;

//BufferManager接口
class BUFFERMAP_DLL_EXPORTED IBufferManager
{
public:
	virtual ~IBufferManager(){};

	//写入数据：主要发布端用，其中WriteFileHeader下载端也会用
	virtual int WriteFileHeader(int iLen,const char *pHeader) = 0;
	virtual int WriteFileStream(int iLen,const char *pData) = 0;

	//根据文件id进行文件头读写操作
	//int GetMissedHeader(std::vector<int> &vecHeaderIndex);
	virtual int GetFileHeader(int iFileIndex,int &iLen, char *pHeader) = 0 ;	//pHeader为空取长度
	//virtual int GetFileHeaderByBlock(int iBlockIndex,int &iLen, char *pHeader)  = 0;	//pHeader为空取长度
	virtual int GetFileIndexByBlock(int iBlockIndex,int &iFileIndex) = 0;
	virtual int AddFileHeader(int iFileIndex,int iLen, char *pHeader) = 0 ;

	//读数据：播放器用
	virtual int ReadFileHeader(int &iLen,char *pHeader)  = 0; //
	virtual int ReadFileStream(char *pBuf,int &iLen)  = 0;  //-1是文件结束
	virtual int ReadFileStreamPack(TRawPack *pPackOut,int &iLen)  = 0;  //-1是文件结束

	//写入传输块：下载模块用
	virtual int WriteBlock(int iIndex, const char *pBlock,int iLen)  = 0; //pBlock的内容大小必须等于BlockSize。

	//读缓存状况：上传模块用
	//取某子流的最后块序号
	//正常返回大于0的数值，异常则返回-1（一般是没有任何数据的时候）
	virtual int GetSubstreamLastBlock(int iSubstream)  = 0;
	//读传输块：上传模块用
	virtual int ReadBlock(int iIndex,char *pBlock,int &iBlockLen)  = 0;//pBlock的大小必须大于或等于BlockSize，否则内存溢出！

	//通过此接口，监视缓存数据变化的通知消息：发布端和上传模块用
	virtual int AddBMMonitor(IBufferMonitor *pMonitor)  = 0;
	virtual int RemoveMonitor(const IBufferMonitor *pMonitor)  = 0;
};

//所有的接口函数都返回整数，0代表正常，其它数值代表出错，返回错误码
class BUFFERMAP_DLL_EXPORTED TBufferManager
	: public IBufferManager
{
public:
	TBufferManager(int iSubStreamCount,int BlockSize,const char *strBufferFile=NULL,int maxBufferSize=-1);
	virtual ~TBufferManager();

	//写入数据：主要发布端用，其中WriteFileHeader下载端也会用
	int WriteFileHeader(int iLen,const char *pHeader);
	int WriteFileStream(int iLen,const char *pData);

	//根据文件id进行文件头读写操作
	//int GetMissedHeader(std::vector<int> &vecHeaderIndex);
	int GetFileHeader(int iFileIndex,int &iLen, char *pHeader) ;	//pHeader为空取长度
	//int GetFileHeaderByBlock(int iBlockIndex,int &iLen, char *pHeader) ;	//pHeader为空取长度
	int GetFileIndexByBlock(int iBlockIndex,int &iFileIndex);
	int AddFileHeader(int iFileIndex,int iLen, char *pHeader) ;

	//读数据：播放器用
	int ReadFileHeader(int &iLen,char *pHeader) ; //读文件头
	int ReadFileStream(char *pBuf,int &iLen) ;    //读数据流内容。-1是文件结束
	int ReadFileStreamPack(TRawPack *pPackOut,int &iLen) ;  //读TRawPack。效果与ReadFileStream一致，只是返回信息多一些。-1是文件结束

	//写入传输块：下载模块用
	int WriteBlock(int iIndex, const char *pBlock,int iLen) ; //pBlock的内容大小必须等于BlockSize。

	//读缓存状况：上传模块用
	//正常返回大于0的数值，异常则返回-1（一般是没有任何数据的时候）
	int GetSubstreamLastBlock(int iSubstream) ;
	//读传输块：上传模块用
	int ReadBlock(int iIndex,char *pBlock,int &iBlockLen) ;//pBlock的大小必须大于或等于BlockSize，否则内存溢出！

	//通过此接口，监视缓存数据变化的通知消息：发布端和上传模块用
	int AddBMMonitor(IBufferMonitor *pMonitor) ;
	int RemoveMonitor(const IBufferMonitor *pMonitor) ;
private:
	BlockBufferManager *m_pImpBufferManager;
};

#endif //#ifndef __BUFFERMAP_H