/********************************************************************
	created:	2006/04/04
	created:	1:17:2007   11:18
	filename: 	e:\work\PPProject\source\Client\NetEngine\pub\ProtocolStruct.h
	file path:	e:\work\PPProject\source\Client\NetEngine\pub
	file base:	ProtocolStruct
	file ext:	h
	author:		gaocheng
	
	purpose:	
*********************************************************************/


#pragma warning (disable:4200)
#ifndef PROTOCOLSTRUCT_H
#define PROTOCOLSTRUCT_H
#include "MD5.h" 
#include  "Winsock2.h"

#define ID_P2P_ERROR		0
#define ID_P2P_SERVER		1
#define ID_P2P_USER_MIN		10000
#define ID_P2P_USER_MAX		-1
enum  en_Connect_Type
{
	HTTP_Connect,
	UDP_Connect,
	TCP_Connect
};
enum  en_Peer_Type
{
	peer_Client,
	peer_SuperClient
};

//用户ID类型
typedef unsigned __int64 USERID;

const WORD c_dwProtoFlag = 0x1008;
const WORD c_byVersion = 0x0100;
 
//协议类型
const BYTE c_byProtoType_C2C = 0x01;
const BYTE c_byProtoType_C2S = 0x02;

//按字节对齐
#pragma pack(push,1)
  
//第一层协议
struct RaPack
{
	void Pack(){ 
		dwProtoFlag = c_dwProtoFlag;
		byVersion = c_byVersion; 
	}
	bool CheckPack(WORD wLen){
		bool bRet = true;
		if (dwProtoFlag != c_dwProtoFlag)
		{ 
			bRet = false;
			return bRet;
		}
		if (byVersion != c_byVersion)
		{
			bRet = false;
			return bRet;
		}
		if (usLen != wLen )
		{
			bRet = false;
			return bRet;
		}
		switch(dwCMDType)
		{ 
		}
		return true;
	}
 
    WORD   dwProtoFlag;		        // 协议标志 
	WORD   byVersion;               // 协议版本 
	USERID  dwSenderId;				// 发送者ID
	USERID  dwReceiverId;			// 接收者ID
	DWORD  dwCMDType;				// 包类型 
	WORD   usLen;                   // 协议的长度，这里的长度是整个包的长度
	BYTE   ucData[];                // 协议命令体
}; 
struct RA_GetID3Info
{
	MD5   mdChannelHash;            //文件hash
};
struct RA_GetID3Info_Ret
{
	MD5   mdChannelHash; 
	DWORD dwInfoLen;                //ID3信息长度
	DWORD dwFileLen;                //文件长度比
	BYTE  byInfo[];           
};

struct RA_GetData
{
	MD5    mdChannelHash;

	//added by tianzuo,2009-6-27
	DWORD  dwPos;
	DWORD  dwLen;
}; 
struct RA_GetData_Ret 
{
	MD5      mdChannelHash;    
	DWORD    dwPos;  //added by tianzuo,2009-6-27
	DWORD    dwDataLen; 
	BYTE     byData[];
}; 

//向ping服务器发送ping包
struct   RA_CS_Ping
{
	DWORD dwTime;                     //发送PING包的时间
};
//ping服务器返回ping包
struct   RA_CS_Ping_Ret
{
	DWORD dwTime;                       //发送ping包的时间
};

////////////////////////////////////////////////////////////////
// 以下为S - C协议
struct RA_SC_Login
{
	USERID dwID;            //用户ID
	DWORD dwIp;            //内网IP地址
	WORD  wUdpPort;        //UDP端口号
	WORD  wTcpPort;        //TCP端口号
	WORD  wWebPort;        //WebServer端口
	BYTE  byType;          //用户类型
};
struct RA_SC_LoginRet
{
	USERID dwID;            //用户ID
	DWORD dwIp;            //内网IP地址
	WORD  wUdpPort;        //UDP端口号
	WORD  wLoginRet;       //登陆结果
	BYTE  byLoginType;     //用登陆采用的网络连接类型
};
struct RA_SC_LoginOut
{
	USERID dwID;            //用户ID
};
struct RA_SC_Active
{
	USERID dwID;            //用户ID
};
struct RA_SC_FileInfo
{
	MD5 mdFile;           //文件MD5值
};

struct RA_SC_UserInfo
{
	USERID dwUserID;
	DWORD dwIP;            //内网IP地址
	WORD  wUdpPort;        //UDP端口号
	WORD  wTcpPort;        //TCP端口号
	WORD  wWebPort;        //WebServer端口
	BYTE  bLoginType;      //登陆类型,UDP,TCP,HTTP ?
	BYTE  byType;          //用户类型
};
struct RA_SC_GetFileUser
{
	MD5 mdFile;           //文件MD5值
};
struct RA_SC_RetFileUser
{
	MD5 mdFile;           //文件MD5值
	WORD usCounts;      //包含的添加的用户个数
	RA_SC_UserInfo user[];
};

struct RA_SC_AddFile
{
	USERID dwID;            //用户ID
	DWORD dwCounts;       //包含的添加的文件个数
	RA_SC_FileInfo aFile[];
};
#pragma pack(pop)

#endif