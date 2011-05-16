#pragma once
#include <string>
#include <map>
using namespace std;

/*
����ID
��������
�������
����״̬��
����״̬˵��
*/
struct Task
{
	int id;         
	int iType;
	string param1;
	string param2;
	int iState;
	string detail;
public:
	static Task &CreateTask(int type,const string &param1,const string &param2,
		int state,const string &detail);
	static Task &getTask(int id);
	static bool updateTask(const Task &task);
	static string toJson();
private:
	typedef map<int,Task> T_mapTask;
	static T_mapTask m_mapTask;
};
