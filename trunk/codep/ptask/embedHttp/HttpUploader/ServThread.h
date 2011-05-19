#pragma once
#include "../Common/Thread/jthread.h"

#include "spiocpserver.hpp"
#include "TaskStatusReportThread.h"

class HttpUploader;

class ServThread :
	public JThread
{
public:
	ServThread(HttpUploader *pUploader);
	~ServThread(void);

	virtual void *Thread();

	void shutdown();
private:
	HttpUploader *m_pUploader;
	SP_IocpServer *m_pSpServer;
	TaskStatusReportThread m_threadTaskReport;
};
