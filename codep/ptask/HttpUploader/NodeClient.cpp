#include "NodeClient.h"
#include <string>
#include <map>
using namespace std;

#include "Gfunction.h"

NodeClient::NodeClient(const string &addr,const string &port)
{
	m_strAddr = addr;
	m_strPort = port;
}

NodeClient::~NodeClient(void)
{
}


void NodeClient::Update(const string &curr_task_id, const string &curr_task_name,const string &curr_task_state, int i_waiting_task_count){
	m_strCurrtaskid = curr_task_id;
	m_strCurrtaskname = curr_task_name;
	m_strCurrtaskstate = curr_task_state;
	m_iWaitingtaskcount = i_waiting_task_count;
}

std::string NodeClient::toJson()
{
	return (string)"['" + m_strAddr + "','"
		+ m_strPort + "','"
		+ m_strCurrtaskid + "','"
		+ m_strCurrtaskname + "','"
		+ m_strCurrtaskstate + "','"
		+ GFunction::toString(m_iWaitingtaskcount) + "']";
}
void NodeClientMap::UpdateNode(const string &addr,const string &port, 
	const string &curr_task_id, const string &curr_task_name,const string &curr_task_state, int i_waiting_task_count)
{
	string name = addr+":"+port;
	T_mapClient::iterator it = m_mapClients.find(name);
	if(it==m_mapClients.end()){
		//it = m_mapClients.insert(map<string,NodeClient>::value_type(name,NodeClient(addr,port)));
		it = m_mapClients.insert(T_mapClient::value_type(name,NodeClient(addr,port))).first;
	}
	NodeClient &node = (*it).second;
	node.Update(curr_task_id,curr_task_name,curr_task_state,i_waiting_task_count);
}
string NodeClientMap::toJson(){
	string strJson = "[";
	T_mapClient::iterator it = m_mapClients.begin();
	for (;it!=m_mapClients.end();it++)
	{
		strJson += (*it).second.toJson();
	}
	return strJson + "]";
}

NodeClientMap::T_mapClient NodeClientMap::m_mapClients;