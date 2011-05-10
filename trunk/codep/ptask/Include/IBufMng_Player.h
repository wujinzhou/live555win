// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_IBUFMNG_4A3DA21B03A9_INCLUDED
#define _INC_IBUFMNG_4A3DA21B03A9_INCLUDED

//##ModelId=4A3DA21B03A9
class IBufMng_player
{
public:
	IBufMng_player(){};
	//##ModelId=4A3DA7860198
	virtual ~IBufMng_player(){};
	/*如果没有数据返回0，播放器提示界面正在缓冲*/

	virtual bool player_Open() = 0;
	//##ModelId=4A3DA78601B5
	virtual unsigned int player_Read(void* lpBuf, unsigned int nCount) = 0; 
	//##ModelId=4A3DA78601F4
	virtual unsigned __int64 player_Seek(__int64 lOff, unsigned int nFrom) = 0;
	virtual unsigned __int64 player_GetNextPos() = 0;
	//##ModelId=4A3DA7860242
	virtual unsigned __int64 player_GetLength() = 0;
	//##ModelId=4A3DA7860280
	virtual void player_Close() = 0;

};

#endif /* _INC_IBUFMNG_4A3DA21B03A9_INCLUDED */
