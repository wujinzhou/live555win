#pragma once
#include <string>
#include <map>
//#include <boost/shareptr.hpp>
using namespace std;

class NodeClient
{
public:
	NodeClient(string &addr,string &port);
	void Update(string &curr_task_id, string &curr_task_name,string &curr_task_state, int i_waiting_task_count);
	
	string getName(){
		return m_strAddr+":"+m_strPort;
	}
public:
	~NodeClient(void);
	
private:
	//addr、port、currtaskid、currtaskname、currtaskstate、waitingtaskcount吉。
	string m_strAddr;
	string m_strPort;
	string m_strCurrtaskid;
	string m_strCurrtaskname;
	string m_strCurrtaskstate;
	int m_iWaitingtaskcount;
};

class NodeClientMap
{
public:
	void UpdateNode(string &addr,string &port, 
		string &curr_task_id, string &curr_task_name,string &curr_task_state, int i_waiting_task_count);
	string ToJson();
private:
	map<string,NodeClient> m_mapClients;
};
