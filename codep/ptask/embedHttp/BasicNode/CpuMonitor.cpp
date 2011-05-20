//#include "stdafx.h"
#include "CpuMonitor.h"
#include "ErrorCode.h"

#include <windows.h>

CpuMonitor::CpuMonitor(void)
{
}

CpuMonitor::~CpuMonitor(void)
{
}

__int64 GetTimeNum(const FILETIME &ft)
{
	__int64 res = ft.dwHighDateTime;
	res = res<<32;
	res += ft.dwLowDateTime;
	return res;
}

int CpuMonitor::BeginMonitor()
{
	//if(m_pCupUsage!=NULL)
	//{
	//	delete m_pCupUsage;
	//	m_pCupUsage = NULL;
	//}

	//m_pCupUsage = new CCpuUsage();

	FILETIME cr,ex;
	GetProcessTimes(::GetCurrentProcess(),&cr,&ex,&m_ftProcessKernel,&m_ftProcessUser);
	m_dwBeginTime = GetTickCount();
	return 0;
}

	//完成记录性能参数
int CpuMonitor::EndMonitor()
{
	//FILETIME ftIdle, ftKernel, ftUser;
	//GetSystemTimes(&ftIdle, &ftKernel, &ftUser);

	//DWORD dwUsed = ((ftKernel.dwLowDateTime-m_ftKernel.dwLowDateTime) 
	//	+ (ftUser.dwLowDateTime-m_ftUser.dwLowDateTime));
	//DWORD dwIdle = ftIdle.dwLowDateTime-m_ftIdle.dwLowDateTime;
	//double dUstage = dwUsed*1.0/(dwUsed+dwIdle);

	//TCHAR bufRes[1024];
	//sprintf_s(bufRes,1024,"%d-%d,%d-%d,%d-%d:%g",
	//	ftIdle.dwHighDateTime-m_ftIdle.dwHighDateTime,
	//	ftIdle.dwLowDateTime-m_ftIdle.dwLowDateTime,
	//	ftKernel.dwHighDateTime-m_ftKernel.dwHighDateTime,
	//	ftKernel.dwLowDateTime-m_ftKernel.dwLowDateTime,
	//	ftUser.dwHighDateTime-m_ftUser.dwHighDateTime,
	//	ftUser.dwLowDateTime-m_ftUser.dwLowDateTime,
	//	dUstage);
	//m_strRes = bufRes;
	SYSTEM_INFO siSysInfo; 
	GetSystemInfo(&siSysInfo); 

	FILETIME cr,ex;
	FILETIME ftProcessKernel;
	FILETIME ftProcessUser;
	GetProcessTimes(::GetCurrentProcess(),&cr,&ex,&ftProcessKernel,&ftProcessUser);
	DWORD dwEndTime = GetTickCount();
	__int64 iKernelTime = GetTimeNum(ftProcessKernel)-GetTimeNum(m_ftProcessKernel);
	__int64 iUserTime = GetTimeNum(ftProcessUser)-GetTimeNum(m_ftProcessUser);
	DWORD dwTimeUsed = 100*( iKernelTime + iUserTime )/10000; //iKernelTime的单位是100ns，这里换算成ms，再乘以100，以计算百分比。
	DWORD dwTimePassed = (dwEndTime-m_dwBeginTime)*siSysInfo.dwNumberOfProcessors;//要考虑CPU个数
	DWORD dwUsetage = dwTimeUsed/dwTimePassed;

	TCHAR bufRes[1024];
	//sprintf_s(bufRes,1024,"%d",m_pCupUsage->GetCpuUsage());
	sprintf_s(bufRes,1024,"%d",dwUsetage);
	
	//if(m_pCupUsage!=NULL)
	//{
	//	delete m_pCupUsage;
	//	m_pCupUsage = NULL;
	//}

	m_strRes = bufRes;
	return 0;
}

std::string CpuMonitor::GetRes()
{
	return m_strRes;
}

FILETIME CpuMonitor::m_ftIdle = {0};

FILETIME CpuMonitor::m_ftKernel = {0};

FILETIME CpuMonitor::m_ftUser = {0};
std::string CpuMonitor::m_strRes = "";

//CCpuUsage *CpuMonitor::m_pCupUsage = NULL;

FILETIME CpuMonitor::m_ftProcessKernel = {0};
FILETIME CpuMonitor::m_ftProcessUser = {0};
DWORD CpuMonitor::m_dwBeginTime = 0;
