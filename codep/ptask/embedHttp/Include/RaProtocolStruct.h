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

//�û�ID����
typedef unsigned __int64 USERID;

const WORD c_dwProtoFlag = 0x1008;
const WORD c_byVersion = 0x0100;
 
//Э������
const BYTE c_byProtoType_C2C = 0x01;
const BYTE c_byProtoType_C2S = 0x02;

//���ֽڶ���
#pragma pack(push,1)
  
//��һ��Э��
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
 
    WORD   dwProtoFlag;		        // Э���־ 
	WORD   byVersion;               // Э��汾 
	USERID  dwSenderId;				// ������ID
	USERID  dwReceiverId;			// ������ID
	DWORD  dwCMDType;				// ������ 
	WORD   usLen;                   // Э��ĳ��ȣ�����ĳ������������ĳ���
	BYTE   ucData[];                // Э��������
}; 
struct RA_GetID3Info
{
	MD5   mdChannelHash;            //�ļ�hash
};
struct RA_GetID3Info_Ret
{
	MD5   mdChannelHash; 
	DWORD dwInfoLen;                //ID3��Ϣ����
	DWORD dwFileLen;                //�ļ����ȱ�
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

//��ping����������ping��
struct   RA_CS_Ping
{
	DWORD dwTime;                     //����PING����ʱ��
};
//ping����������ping��
struct   RA_CS_Ping_Ret
{
	DWORD dwTime;                       //����ping����ʱ��
};

////////////////////////////////////////////////////////////////
// ����ΪS - CЭ��
struct RA_SC_Login
{
	USERID dwID;            //�û�ID
	DWORD dwIp;            //����IP��ַ
	WORD  wUdpPort;        //UDP�˿ں�
	WORD  wTcpPort;        //TCP�˿ں�
	WORD  wWebPort;        //WebServer�˿�
	BYTE  byType;          //�û�����
};
struct RA_SC_LoginRet
{
	USERID dwID;            //�û�ID
	DWORD dwIp;            //����IP��ַ
	WORD  wUdpPort;        //UDP�˿ں�
	WORD  wLoginRet;       //��½���
	BYTE  byLoginType;     //�õ�½���õ�������������
};
struct RA_SC_LoginOut
{
	USERID dwID;            //�û�ID
};
struct RA_SC_Active
{
	USERID dwID;            //�û�ID
};
struct RA_SC_FileInfo
{
	MD5 mdFile;           //�ļ�MD5ֵ
};

struct RA_SC_UserInfo
{
	USERID dwUserID;
	DWORD dwIP;            //����IP��ַ
	WORD  wUdpPort;        //UDP�˿ں�
	WORD  wTcpPort;        //TCP�˿ں�
	WORD  wWebPort;        //WebServer�˿�
	BYTE  bLoginType;      //��½����,UDP,TCP,HTTP ?
	BYTE  byType;          //�û�����
};
struct RA_SC_GetFileUser
{
	MD5 mdFile;           //�ļ�MD5ֵ
};
struct RA_SC_RetFileUser
{
	MD5 mdFile;           //�ļ�MD5ֵ
	WORD usCounts;      //��������ӵ��û�����
	RA_SC_UserInfo user[];
};

struct RA_SC_AddFile
{
	USERID dwID;            //�û�ID
	DWORD dwCounts;       //��������ӵ��ļ�����
	RA_SC_FileInfo aFile[];
};
#pragma pack(pop)

#endif