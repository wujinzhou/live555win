// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_ICONSOLENOTIFY_4A3DB11E0263_INCLUDED
#define _INC_ICONSOLENOTIFY_4A3DB11E0263_INCLUDED
#include <WinSock2.h>
//##ModelId=4A3DB11E0263
class IConsoleNotify 
{
public:
	//##ModelId=4A3DB11E0264
	virtual void OnLogin(DWORD bRet) = 0;

	//##ModelId=4A3DB11E0266
	virtual void OnLogout() = 0;

};

#endif /* _INC_ICONSOLENOTIFY_4A3DB11E0263_INCLUDED */
