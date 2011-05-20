#include "Task.h"
#include "Gfunction.h"

Task::T_mapTask Task::m_mapTask;

Task &Task::CreateTask(int type,const string &param1,const string &param2,
					   int state,const string &detail)
{
	Task task;
	task.id = (int)m_mapTask.size() + 1;
	task.iType  = type;
	task.param1 = param1;
	task.param2 = param2;
	task.iState = state;
	task.detail = detail;

	m_mapTask.insert(T_mapTask::value_type(task.id,task));
	return (*m_mapTask.find(task.id)).second;
}

Task &Task::getTask( int id )
{
	return Task();
	//T_mapTask::iterator it = m_mapTask.find(task.id);
	//if ()
	//{
	//}
	//return (*).second;
}

bool Task::updateTask( const Task &task )
{
	T_mapTask::iterator it = m_mapTask.find(task.id);
	if (it==m_mapTask.end())
	{
		return false;
	}
	(*it).second = task;
	return true;
}

std::string Task::toJson()
{
	string strJson = "[";
	T_mapTask::iterator it = m_mapTask.begin();
	if (it!=m_mapTask.end())
	{
		const Task &task = (*it).second;
		strJson += "[" +
			GFunction::toString(task.id) + "," + 
			GFunction::toString(task.iType) + ",'" + 
			task.param1 + "','" + 
			task.param2 + "'," + 
			GFunction::toString(task.iState) + ",'" + 
			task.detail + "']";
		it++;
	}
	for (;it!=m_mapTask.end();it++)
	{
		const Task &task = (*it).second;
		strJson += ",[" 
			+ GFunction::toString(task.id) + "," + 
			GFunction::toString(task.iType) + ",'" + 
			task.param1 + "','" + 
			task.param2 + "'," + 
			GFunction::toString(task.iState) + ",'" + 
			task.detail + "']";
	}
	return strJson + "]";
}