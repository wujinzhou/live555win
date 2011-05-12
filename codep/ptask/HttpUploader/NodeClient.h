#pragma once
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
using namespace std;
using namespace boost;

class NodeClient
{
public:
	NodeClient(const string &addr,const string &port);
	void Update(const string &curr_task_id, const string &curr_task_name,const string &curr_task_state, int i_waiting_task_count);
	
	string getName(){
		return m_strAddr+":"+m_strPort;
	}
	string toJson();
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
	//static shared_ptr<NodeClientMap> Instance(){
	//	if(m_ptrNodeClientMap.get()){
	//		return m_ptrNodeClientMap;
	//	}
	//	m_ptrNodeClientMap = shared_ptr<NodeClientMap>(new NodeClientMap());
	//	return m_ptrNodeClientMap;
	//}
	static void UpdateNode(const string &addr,const string &port, 
		const string &curr_task_id, const string &curr_task_name,const string &curr_task_state, int i_waiting_task_count);
	static string toJson();
private:
	typedef map<const string,NodeClient> T_mapClient;
	static T_mapClient m_mapClients;
	//static shared_ptr<NodeClientMap> m_ptrNodeClientMap;
};
