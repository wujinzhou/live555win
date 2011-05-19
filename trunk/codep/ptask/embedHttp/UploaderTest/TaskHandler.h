#pragma once
#include <string>
using namespace std;

#include "..\HttpUploader\spserver\sphttpmsg.hpp"

void TaskHandler(SP_HttpRequest * request, SP_HttpResponse * response);

class TaskHandler
{
public:
	TaskHandler(void);
public:
	~TaskHandler(void);
};
