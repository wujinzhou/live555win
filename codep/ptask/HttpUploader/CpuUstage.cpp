//#include "stdafx.h"
#include "CpuUstage.h"


CCpuUsage::CCpuUsage()
{
	//
	m_hWnd = NULL;
	m_nRefreshInterval = 100;
	m_nTimerID = 1000;
	m_nCpuUsage = 0;

	//
	memset(&liOldIdleTime  ,   0, sizeof(LARGE_INTEGER));
	memset(&liOldSystemTime,   0, sizeof(LARGE_INTEGER)); 

	//
	NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(
		GetModuleHandle("ntdll") , "NtQuerySystemInformation");
	if (!NtQuerySystemInformation)
		return;

	// get number of processors in the system
	status = NtQuerySystemInformation(SystemBasicInformation,&SysBaseInfo,sizeof(SysBaseInfo),NULL);
	if (status != NO_ERROR)
		return;

	// create control for timer
	//m_hWnd = ::CreateWindow("static", "", 0, 0, 0, 0, 0, NULL, NULL, 0, NULL);
	//::SetWindowLong(m_hWnd , GWL_USERDATA , (long)(this) );

	//TIMERPROC tp = (TIMERPROC)CalcCpuUsage;
	//SetTimer(m_hWnd , m_nTimerID, m_nRefreshInterval, tp);

	OnTimer();

}

CCpuUsage::~CCpuUsage()
{
	KillTimer(m_hWnd , m_nTimerID);
	DestroyWindow(m_hWnd);
}

void CCpuUsage::CalcCpuUsage(
									HWND hwnd,
									UINT uMsg,
									UINT_PTR idEvent,
									DWORD dwTime
									)
{
	CCpuUsage* pCpu = (CCpuUsage*)::GetWindowLong(hwnd , GWL_USERDATA);

	if ( pCpu )
	{
		pCpu->OnTimer();
	}

}

int CCpuUsage::OnTimer()
{
	status = NtQuerySystemInformation(SystemTimeInformation,&SysTimeInfo,sizeof(SysTimeInfo),0);

	if (status!=NO_ERROR)
		return 0;

	// get new CPU's idle time
	status = NtQuerySystemInformation(SystemPerformanceInformation,&SysPerfInfo,sizeof(SysPerfInfo),NULL);
	if (status != NO_ERROR)
		return 0;

	// if it's a first call - skip it
	if (liOldIdleTime.QuadPart != 0)
	{
		// CurrentValue = NewValue - OldValue
		dbIdleTime = Li2Double(SysPerfInfo.liIdleTime) - Li2Double(liOldIdleTime);
		dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) - Li2Double(liOldSystemTime);

		// CurrentCpuIdle = IdleTime / SystemTime
		dbIdleTime = dbIdleTime / dbSystemTime;

		// CurrentCpuUsage% = 100 - (CurrentCpuIdle * 100) / NumberOfProcessors
		dbIdleTime = 100.0 - dbIdleTime * 100.0 / (double)SysBaseInfo.bKeNumberProcessors + 0.5;

		m_nCpuUsage = (UINT)dbIdleTime;
	}

	// store new CPU's idle and system time
	liOldIdleTime = SysPerfInfo.liIdleTime;
	liOldSystemTime = SysTimeInfo.liKeSystemTime;

	// wait one second

	return 0;
}

int CCpuUsage::GetCpuUsage()
{
	OnTimer();
	return m_nCpuUsage;
}

int CCpuUsage::SetRefreshInterval(int milli_sec)
{
	m_nRefreshInterval = milli_sec;

	if ( m_hWnd )
	{
		TIMERPROC tp = (TIMERPROC)CalcCpuUsage;
		SetTimer(m_hWnd, m_nTimerID, m_nRefreshInterval ,tp);
	}

	return 0;

}