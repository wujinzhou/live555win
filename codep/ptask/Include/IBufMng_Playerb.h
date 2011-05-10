// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_IBUFMNG_4A3DA21B03A9_INCLUDED
#define _INC_IBUFMNG_4A3DA21B03A9_INCLUDED
#define UINT  unsigned int
#define DWORD unsigned int
#define LONG long long
//##ModelId=4A3DA21B03A9
class IBufMng_player
{
public:
	IBufMng_player(){};
	//##ModelId=4A3DA7860198
	virtual ~IBufMng_player(){};
	/*如果没有数据返回0，播放器提示界面正在缓冲*/

	virtual void player_Open() = 0;
	//##ModelId=4A3DA78601B5
	virtual UINT player_Read(void* lpBuf, UINT nCount) = 0; 
	//##ModelId=4A3DA78601F4
	virtual LONG player_Seek(LONG lOff, UINT nFrom) = 0;
	virtual LONG player_GetNextPos() = 0;
	//##ModelId=4A3DA7860242
	virtual DWORD player_GetLength() = 0;
	//##ModelId=4A3DA7860280
	virtual void player_Close() = 0;

};

#endif /* _INC_IBUFMNG_4A3DA21B03A9_INCLUDED */
