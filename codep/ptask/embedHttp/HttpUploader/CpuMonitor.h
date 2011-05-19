#pragma once
#include <string>
#include <windows.h>

#include "CpuUstage.h"

class CpuMonitor
{
public:
	CpuMonitor(void);
	~CpuMonitor(void);

	static int BeginMonitor();

	//��ɼ�¼���ܲ���
	static int EndMonitor();

	static std::string GetRes();
private:
	static FILETIME m_ftIdle;
	static FILETIME m_ftKernel;
	static FILETIME m_ftUser;
	static std::string m_strRes;

	//static CCpuUsage *m_pCupUsagek;

	static FILETIME m_ftProcessKernel;
	static FILETIME m_ftProcessUser;
	static DWORD m_dwBeginTime;
};
