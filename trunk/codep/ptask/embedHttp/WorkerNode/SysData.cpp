#include "SysData.h"
#include <winsock2.h>
#include <iphlpapi.h>

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

//#include <DSetup.h>
//#include "CPUAssembly.h"
//#include "D3dx9core.h"

//ULONG WINAPI GetAdaptersAddresses(
//  __in     ULONG Family,
//  __in     ULONG Flags,
//  __in     PVOID Reserved,
//  __inout  PIP_ADAPTER_ADDRESSES AdapterAddresses,
//  __inout  PULONG SizePointer
//);

std::string SysData::GetMac()
{
	PIP_ADAPTER_INFO   pInfo=NULL,pNext=NULL;   
	DWORD   size=0,result = 0;
	
	result=GetAdaptersInfo(pInfo,&size);   
	if(result!=ERROR_BUFFER_OVERFLOW)   
	{   
		return "";
	}

	pInfo=(PIP_ADAPTER_INFO)malloc(size);   
	result=GetAdaptersInfo(pInfo,&size);   
	std::string strRes;
	if(result==ERROR_SUCCESS)   
	{   
		TCHAR   buffer[128];   
		for(int i=0;i<(int)pInfo->AddressLength;i++)
		{
			if(i==0)
			{
				sprintf_s(buffer,32,"%02X",pInfo->Address[i]);
			}
			else
			{
				sprintf_s(buffer,32,"-%02X",pInfo->Address[i]);
			}
			strRes += buffer;
		}
		return strRes;
	}   
	return "";

}


#define BUFSIZE 256
typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
typedef BOOL (WINAPI *PGPI)(DWORD, DWORD, DWORD, DWORD, PDWORD);

BOOL GetOSDisplayString_Num( LPTSTR pszOS)
{
   OSVERSIONINFOEX osvi;
   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

   if( !GetVersionEx ((OSVERSIONINFO *) &osvi) )
   {
	   return FALSE;
   }

   DWORD dwProductType = 0;
   if ( osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0 )
   {
	   //PGNSI pGNSI;
	   PGPI pGPI;
	   pGPI = (PGPI) GetProcAddress(
		   GetModuleHandle(TEXT("kernel32.dll")), 
		   "GetProductInfo");
	   pGPI( 6, 0, 0, 0, &dwProductType);
   }

   //平台号，主版本号，子版本号，sp主版本号，sp子版本号，编译号，版本类型码，套件掩码，产品类型
   sprintf_s(pszOS,64,"%d.%d.%d.%d.%d.%d.%d.%d.%d",osvi.dwPlatformId,
	   osvi.dwMajorVersion,osvi.dwMinorVersion,
	   osvi.wServicePackMajor,osvi.wServicePackMinor,
	   osvi.dwBuildNumber,
	   osvi.wProductType,
	   osvi.wSuiteMask,
	   dwProductType);

   return TRUE;
}

std::string SysData::GetOperaSystem()
{
    TCHAR szOS[BUFSIZE];

    if( GetOSDisplayString_Num( szOS ) )
	{
		return szOS;
	}
	return "";
}


std::string Reg_GetDirectXVersion()
{
	LONG result;
	char data[128];
	DWORD dataSize;
	HKEY hKey;

	result = ::RegOpenKeyEx (HKEY_LOCAL_MACHINE,"software\\microsoft\\directx", 0, KEY_QUERY_VALUE, &hKey);

	if (result == ERROR_SUCCESS) 
	{
		result = ::RegQueryValueEx(hKey, _T("version"),NULL, NULL,(LPBYTE)&data, &dataSize);
		return data;
	}

	return "";
}

std::string SysData::GetDirectXVersion()
{
	return Reg_GetDirectXVersion();
	//DWORD dwVersion;
	//DWORD dwRevision;
	//if (DirectXSetupGetVersion(&dwVersion, &dwRevision))
	//{
	//	TCHAR bufRes[1024];
	//	sprintf_s(bufRes,1024,"%d.%d.%d.%d",
	//		HIWORD(dwVersion), LOWORD(dwVersion),
	//		HIWORD(dwRevision), LOWORD(dwRevision));
	//	return bufRes;
	//}
	//return "";
}

std::string SysData::GetScreen()
{
	int width = ::GetSystemMetrics(SM_CXSCREEN);
	int height = ::GetSystemMetrics(SM_CYSCREEN);
	TCHAR bufRes[1024];
	sprintf_s(bufRes,1024,"%d*%d",width,height);
	return bufRes;
}

std::string SysData::GetCpu()
{
	//SYSTEM_INFO siSysInfo; 
	//GetSystemInfo(&siSysInfo); 

	//CPUAssembly* assembly = new CPUAssembly;
	//if(!assembly->QueryCPUInfo())
	//	return "";

	////CPU架构、处理器层级、处理器个数、处理器版本号、主频
	//TCHAR bufRes[1024];
	//sprintf_s(bufRes,1024,"%u.%u.%u.%u.%u",
	//	siSysInfo.wProcessorArchitecture,
	//	siSysInfo.wProcessorLevel,
	//	siSysInfo.dwNumberOfProcessors,
	//	siSysInfo.wProcessorRevision ,
	//	assembly->GetSpeedMHz());

	//delete assembly;
	//return bufRes;
	return "";
}
std::string SysData::GetMem()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof (statex);
	GlobalMemoryStatusEx (&statex);
	TCHAR bufRes[1024];
	//总内存、可用内存、使用百分比
	sprintf_s(bufRes,1024,"[%u,%u,%u]",
		DWORD(statex.ullTotalPhys/(1024*1024)),
		DWORD(statex.ullAvailPhys/(1024*1024)),
		statex.dwMemoryLoad
		);
	return bufRes;
}

bool IsLocalAddr(in_addr addr)
{
    //A类私有地址：10.0.0.0～10.255.255.255
    //B类私有地址：172.16.0.0～172.31.255.255
    //C类私有地址：192.168.0.0～192.168.255.255
	//addr.S_un.S_un_b
	if(addr.S_un.S_un_b.s_b1==10)
	{
		return true;
	}
	else if(addr.S_un.S_un_b.s_b1==172)
	{
		return addr.S_un.S_un_b.s_b2>=16 && addr.S_un.S_un_b.s_b2<=31;
	}
	else if(addr.S_un.S_un_b.s_b1==192)
	{
		return addr.S_un.S_un_b.s_b2 == 168;
	}
	return false;
}

std::string SysData::GetLan()
{
	WSADATA   wsadata;   
	WORD   wVersionRequested;   
	int   iWSAStartup;   

	wVersionRequested   =   MAKEWORD(2,2);   

	iWSAStartup   =   WSAStartup(wVersionRequested,&wsadata);   
	if(iWSAStartup   !=   0)   
	{   
		//TRACE("无法初始化Windows套接字!!");   
		//return   false;   
		return "";
	}   
	//if(LOBYTE(wsadata.wVersion)!=2||HIBYTE(wsadata.wHighVersion)!=2)   
	//{   
	//	TRACE("找不到创建Windows套接字需要的动态链接库!!");   
	//	WSACleanup();   
	//	return   false;   
	//}   
	char   chostName[1024];   
	HOSTENT   *pHost;
	if(::gethostname(chostName,1024)   !=   0)   
	{
		return "";//WSAGetLastError();
	}   
	pHost=::gethostbyname(chostName);  
	TCHAR bufRes[1024];
	//std::string strAddr = inet_ntoa(*(struct   in_addr   *)*pHost->h_addr_list);
	bool bIsLocal = IsLocalAddr(*(struct   in_addr   *)*pHost->h_addr_list);
	//sprintf_s(bufRes,1024,"%s-%s",strAddr.c_str(),bIsLocal?"L":"G");
	sprintf_s(bufRes,1024,"%s",bIsLocal?"1":"2");
	return bufRes;
}