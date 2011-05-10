// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_IPROCESSNOTIFY_4A3F8CA4032C_INCLUDED
#define _INC_IPROCESSNOTIFY_4A3F8CA4032C_INCLUDED

typedef vector<RA_SC_UserInfo>  T_vectUser;
//##ModelId=4A3F8CA4032C
class IProcessNotify 
{
public:
	//##ModelId=4A3F8D6F0000
	virtual void  OnLogin(en_Connect_Type type) = 0;
	//##ModelId=4A3F8D77005D
	virtual bool  OnAddFile() = 0;
	//##ModelId=4A3F8D830251
	virtual void  OnSource(string task,T_vectUser userlist) = 0;
};

#endif /* _INC_IPROCESSNOTIFY_4A3F8CA4032C_INCLUDED */
