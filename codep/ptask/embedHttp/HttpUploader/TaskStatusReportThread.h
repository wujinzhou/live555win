#pragma once
#include <string>
using namespace std;
#include "../Common/Thread/jthread.h"

//5.�ڵ�ע��ӿ�
//��ͨ�ڵ���Ҫ��ʱ���Լ���״̬�ϱ������ڵ㣬�������ڵ����֪�����ǵĴ����Լ�����״̬��
//���ڵ��ϣ��˽ӿ���/nodestatus�������У�addr��port��currtaskid��currtaskname��currtaskstate��waitingtaskcount�ȡ�
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
