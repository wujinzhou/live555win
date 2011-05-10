// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_ICONSOLE_4A3BB37B01C5_INCLUDED
#define _INC_ICONSOLE_4A3BB37B01C5_INCLUDED
#include <string>
#include "IBufMng_Player.h"
#include "IConsoleNotify.h"
using namespace std;
//##ModelId=4A3BB37B01C5 
class IConsole 
{
public:
	//##ModelId=4A3BB48C032C
	virtual void Login(int ID) = 0;

	//##ModelId=4A3BB4930280
	virtual void Logout() = 0;

	//##ModelId=4A3BB49D01F4
	virtual bool StartTask(string strTask,string strPath) = 0;

	//##ModelId=4A3BB4A9032C
	virtual bool StopTask(string strTask) = 0;

	//##ModelId=4A3BB4B7004E
	virtual bool PauseTask(string strTask) = 0;

	//##ModelId=4A3BB4C103A9
	virtual void StartAll() = 0;

	//##ModelId=4A3BB4C90119
	virtual void PauseAll() = 0;

	//##ModelId=4A3BB4D10186
	virtual void StopAll() = 0;

	//##ModelId=4A3DADC80109
	virtual  IBufMng_player* GetBufMng(string strhash) = 0;

};
 

#ifdef CONSOLEMAIN_EXPORTS
#define CONSOLE_API __declspec(dllexport)
#else
#define CONSOLE_API __declspec(dllimport)
#endif 
CONSOLE_API   IConsole* CreateConsel(IConsoleNotify* pNotify,int iID = 0);
CONSOLE_API   void      DestryConsel(IConsole* p);
#endif /* _INC_ICONSOLE_4A3BB37B01C5_INCLUDED */
