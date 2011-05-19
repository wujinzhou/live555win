// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_BLOCKDOWNLOADUDP_4A3BB3A100DA_INCLUDED
#define _INC_BLOCKDOWNLOADUDP_4A3BB3A100DA_INCLUDED

#include "IBlockDownloader.h"
//#include "IBlockDowloadNotify.h" 
#include "Connection.h"

const int Buf_Len = 512;
#ifdef UDPBLOCKDOWNLOADER_EXPORTS
#define UDPBLOCKDOWNLOADER_DLL_EXPORTED __declspec(dllexport)
#else
#define UDPBLOCKDOWNLOADER_DLL_EXPORTED __declspec(dllimport)
#endif
#include "Connection.h"
using namespace UDT;
//##ModelId=4A3BB3A100DA
class UDPBLOCKDOWNLOADER_DLL_EXPORTED BlockDownloadUdp  
: public IBlockDownloader ,Notify
{
	TPeerMng*             m_pMng;
	IBlockListener*       m_pListener;
	std::string           m_strFileID;
	int                   m_iFileSize;
	int                   m_iBlockSize;//=8*1024
	TPeerPtr              m_peer;
	char*                 m_pBuf;
	int                   m_iDistID;
	int                   m_iMyID;
	
public:
	//构造函数：文件ID（hash码），文件大小，分块大小
	BlockDownloadUdp(TPeerMng* pMng, IBlockListener *pListener,const std::string &strFileID
		,int iFileSize,int iID, int iBlockSize=8*1024);
	virtual ~BlockDownloadUdp(void);
	
	//尝试建立连接（异步）
	bool Connect(int iDistID,sockaddr *name,int iLen);
	//bool Connect(int iDistID );
	
	//下载文件片段（异步）
	//如果文件不存在，会在OnConnectMsg中得到报告
	bool Download(int iBlockIndex);
public://回调函数
	 
	  void  OnPeerConnected(TPeerPtr pConnection,bool bSuccess) ;           
	  void  OnPeerDisConnected(TPeerPtr pConnection)  ;
	  void  OnPeerData(TPeerPtr pConnection,const char* pData, int ilen) ;
private:
 
};

#endif /* _INC_BLOCKDOWNLOADUDP_4A3BB3A100DA_INCLUDED */
