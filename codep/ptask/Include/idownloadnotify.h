// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_IDOWNLOADNOTIFY_4A40EDCF02AF_INCLUDED
#define _INC_IDOWNLOADNOTIFY_4A40EDCF02AF_INCLUDED
#include "../Common/md5.h"
//##ModelId=4A40EDCF02AF
class IDownloadNotify 
{
public:
	//##ModelId=4A42508F014F
	inline virtual ~IDownloadNotify();

	//##ModelId=4A42508F0167
	virtual bool OnTaskComplet(MD5 fileHash) = 0;

	//##ModelId=4A4384F70167
	virtual bool OnState() = 0;

};


//##ModelId=4A42508F014F
inline IDownloadNotify::~IDownloadNotify()
{
	// TODO: Add your specialized code here.
}

#endif /* _INC_IDOWNLOADNOTIFY_4A40EDCF02AF_INCLUDED */
