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
	USERID udUserID;               //��½�û�ID
	GSIP ipLocal;                  //����IP��ַ
	GSIP ipServer;                 //��½������UDP IP��ַ
	GSIP ipNatServer;              //UDT�򶴷�����IP��ַ
	GSIP ipHttpServer;             //HTTP����IP��ַ
	LPCTSTR pszWebServer;           //HTTP��½��������ַ

	UDT::TPeerMng *pmng;            //UDT���ӹ�����
}INITPARAM;


#define CONS_CREATE_NAME		"CreateConsolObject"
#define CONS_DESTORY_NAME	"DestoryConsolObject"

class ICSProcessNotify
{
public:
	ICSProcessNotify(void){};
	virtual ~ICSProcessNotify(void){};

	//�����ļ�ӵ�����б�
	virtual void OnSource( MD5 mdFile ,USHORT usCounts , RA_SC_UserInfo *pList ) = 0;
	//�ж�����
	virtual void OnDisconnect()=0;
	//��½�ص�
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