// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_IFILEMNGNOTIFY_4A3DA86400CB_INCLUDED
#define _INC_IFILEMNGNOTIFY_4A3DA86400CB_INCLUDED

class FileMng;

//##ModelId=4A3DA86400CB
class IFileMngNotify 
{
public:
	//##ModelId=4A3DA8B60157
	//true表示校验成功，false表示校验失败
	//##ModelId=4A3DABD40138
	virtual void OnCheckComplete(bool b) = 0;

};

#endif /* _INC_IFILEMNGNOTIFY_4A3DA86400CB_INCLUDED */