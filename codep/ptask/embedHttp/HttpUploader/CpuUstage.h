#pragma once

#include <windows.h>
#include <Winternl.h>

#define SystemBasicInformation 0 
#define SystemPerformanceInformation 2 
#define SystemTimeInformation 3 

#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart)) 

class CCpuUsage
{
public:
	CCpuUsage();
	~CCpuUsage();

public:
	int GetCpuUsage();                       //�õ�ϵͳcpu������
	int SetRefreshInterval(int milli_sec);   //��ʱˢ�¼��

private:
	//���Ͷ���
	typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);

	typedef struct
	{
		DWORD dwUnknown1;
		ULONG uKeMaximumIncrement;
		ULONG uPageSize;
		ULONG uMmNumberOfPhysicalPages;
		ULONG uMmLowestPhysicalPage;
		ULONG uMmHighestPhysicalPage;
		ULONG uAllocationGranularity;
		PVOID pLowestUserAddress;
		PVOID pMmHighestUserAddress;
		ULONG uKeActiveProcessors;
		BYTE bKeNumberProcessors;
		BYTE bUnknown2;
		WORD wUnknown3;
	} SYSTEM_BASIC_INFORMATION;

	typedef struct
	{
		LARGE_INTEGER liIdleTime;
		DWORD dwSpare[76];
	} SYSTEM_PERFORMANCE_INFORMATION;

	typedef struct
	{
		LARGE_INTEGER liKeBootTime;
		LARGE_INTEGER liKeSystemTime;
		LARGE_INTEGER liExpTimeZoneBias;
		ULONG uCurrentTimeZoneId;
		DWORD dwReserved;
	} SYSTEM_TIME_INFORMATION;

	//��������
	SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo;
	SYSTEM_TIME_INFORMATION SysTimeInfo;
	SYSTEM_BASIC_INFORMATION SysBaseInfo;

	double dbIdleTime;
	double dbSystemTime;

	LONG status;

	LARGE_INTEGER liOldIdleTime;
	LARGE_INTEGER liOldSystemTime;

	PROCNTQSI NtQuerySystemInformation;

	int m_nCpuUsage;

	//��ʱ
	HWND m_hWnd;
	int  m_nRefreshInterval;//Ĭ��Ϊ1000����
	int  m_nTimerID;

private:
	static void CalcCpuUsage(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	int OnTimer();
};
