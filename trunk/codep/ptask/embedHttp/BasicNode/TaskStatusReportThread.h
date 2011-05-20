#pragma once
#include <string>
using namespace std;
#include "../Common/Thread/jthread.h"

//5.节点注册接口
//普通节点需要定时将自己的状态上报到主节点，这样主节点才能知道它们的存在以及运行状态。
//主节点上，此接口是/nodestatus，参数有：addr、port、currtaskid、currtaskname、currtaskstate、waitingtaskcount等。
class TaskStatusReportThread :
	public JThread
{
public:
	TaskStatusReportThread(const string &disturl,const string &baseinfo);
	virtual void *Thread();

	void updatecurrtask(const string &taskid,const string &taskname, const string &taskstate);
	void updatewaitingtaskcount(int icount);

public:
	~TaskStatusReportThread(void);
private:
	string m_disturl;
	string m_baseinfo;
	string m_taskid;
	string m_taskname;
	string m_taskstate;
	int m_itaskcount;

};
