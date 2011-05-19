// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_ITASK_4A42508F013B_INCLUDED
#define _INC_ITASK_4A42508F013B_INCLUDED
#include "IBufMng_Player.h"
//##ModelId=4A42508F013B
class ITask 
{
public: 

	//##ModelId=4A42508F0149
	virtual ~ITask(){};

	//##ModelId=4A42508F014B
	virtual IBufMng_player* GetBufMng() = 0;

	//##ModelId=4A42508F014D
	virtual int GetSpeed() = 0;

};

#endif /* _INC_ITASK_4A42508F013B_INCLUDED */
