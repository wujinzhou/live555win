#pragma once
#include "RaProtocolStruct.h"
#include "MD5.h"
#include "Connection.h"
#ifdef CONSOL_EXPORTS
#define CONSOL_API __declspec(dllexport)
#else
#define CONSOL_API __declspec(dllimport)
#endif

typedef struct _tagGSIP
{
	DWORD dwIP;
	USHORT usPort;
}GSIP;
typedef struct _tagInitParam
{
	USERID udUserID;               //登陆用户ID
	GSIP ipLocal;                  //本地IP地址
	GSIP ipServer;                 //登陆服务器UDP IP地址
	GSIP ipNatServer;              //UDT打洞服务器IP地址
	GSIP ipHttpServer;             //HTTP下载IP地址
	LPCTSTR pszWebServer;           //HTTP登陆服务器网址

	UDT::TPeerMng *pmng;            //UDT连接管理类
}INITPARAM;


#define CONS_CREATE_NAME		"CreateConsolObject"
#define CONS_DESTORY_NAME	"DestoryConsolObject"

class ICSProcessNotify
{
public:
	ICSProcessNotify(void){};
	virtual ~ICSProcessNotify(void){};

	//返回文件拥有者列表
	virtual void OnSource( MD5 mdFile ,USHORT usCounts , RA_SC_UserInfo *pList ) = 0;
	//中断连接
	virtual void OnDisconnect()=0;
	//登陆回调
	virtual void OnLogin( DWORD dwUserID , DWORD dwRet ,BYTE  bLoginType )=0;
};

class ICSprocess
{
public:
	ICSprocess(ICSProcessNotify *pNotify , int nUserType ){};
	virtual ~ICSprocess(void){};

	virtual BOOL Init( const INITPARAM &param ) = 0;
	virtual BOOL Login( ) = 0;
	virtual BOOL Logout() = 0;

	virtual BOOL GetSource( MD5 mdFile ) = 0;
	virtual BOOL AddFile( MD5 *pmdFile , int nCounts ) = 0;
};


typedef ICSprocess* (*FUNCOSCREATE) ( ICSProcessNotify *  , BOOL );
typedef void (*FUNCOSDESTORY) ( ICSprocess * );

extern "C"
{
	CONSOL_API ICSprocess* CreateConsolObject(ICSProcessNotify *pNotify , BOOL bIsPub);
	CONSOL_API void DestoryConsolObject( ICSprocess *pCon );
}