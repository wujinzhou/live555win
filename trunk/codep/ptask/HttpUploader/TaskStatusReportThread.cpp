#include "TaskStatusReportThread.h"
#include <iostream>
#include <string>
using namespace std;

#include "httppost.h"

TaskStatusReportThread::TaskStatusReportThread(const string &disturl,const string &baseinfo)
{
	m_disturl = disturl;
	m_baseinfo = baseinfo;
	m_taskid = "";
	m_taskname = "";
	m_taskstate = "";
	m_itaskcount = 0;
}

TaskStatusReportThread::~TaskStatusReportThread(void)
{
}


void *TaskStatusReportThread::Thread(){
	this->ThreadStarted();

	while(true){
		std::string strApiUrl = m_disturl + "/status";
		httpPost hp(strApiUrl.c_str());
		hp.init();
		hp.doGet();
		std::string strRes = hp.getResult();
		std::cout<<strRes<<std::endl;
		Sleep(5*1000);
	}
}
void TaskStatusReportThread::updatecurrtask(const string &taskid,const string &taskname, const string &taskstate){
	m_taskid = taskid;
	m_taskname = taskname;
	m_taskstate = taskstate;

}
void TaskStatusReportThread::updatewaitingtaskcount(int icount){
	m_itaskcount = icount;
}

bool TaskStatusReportThread::setMainNode( const string &mainnode )
{
	m_disturl = mainnode;
	return true;
}