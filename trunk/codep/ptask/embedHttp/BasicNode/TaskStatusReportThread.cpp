#include "TaskStatusReportThread.h"
#include <iostream>
#include <string>
using namespace std;

#include "httpCpp.h"

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

	return NULL;
	while(true){
		//std::string strApiUrl = "http://localhost:8080/status";
		//httpPost hp(strApiUrl.c_str());
		//hp.init();
		//hp.doGet();
		//std::string strRes = hp.getResult();
		std::string strRes = httpCpp::httpget("http://localhost:8080/status");
		std::cout<<strRes<<std::endl;
		Sleep(10*1000);
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