#include "NodeClient.h"
#include <string>
#include <map>
using namespace std;

NodeClient::NodeClient(string &addr,string &port)
{
	m_strAddr = addr;
	m_strPort = port;
}

NodeClient::~NodeClient(void)
{
}


void NodeClient::Update(string &curr_task_id, string &curr_task_name,string &curr_task_state, int i_waiting_task_count){
	m_strCurrtaskid = curr_task_id;
	m_strCurrtaskname = curr_task_name;
	m_strCurrtaskstate = curr_task_state;
	m_iWaitingtaskcount = i_waiting_task_count;
}

void NodeClientMap::UpdateNode(string &addr,string &port, 
	string &curr_task_id, string &curr_task_name,string &curr_task_state, int i_waiting_task_count)
{
	string name = addr+":"+port;
	map<string,NodeClient>::iterator it = m_mapClients.find(name);
	if(it==m_mapClients.end()){
		//it = m_mapClients.insert(map<string,NodeClient>::value_type(name,NodeClient(addr,port)));
		m_mapClients.insert(T_mapClient::value_type(name,NodeClient(addr,port)));
	}
	NodeClient &node = (*it).second;
	node.Update(curr_task_id,curr_task_name,curr_task_state,i_waiting_task_count);
}
string NodeClientMap::ToJson(){
	return "[]";
}