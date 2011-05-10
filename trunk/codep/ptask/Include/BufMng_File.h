// BufMng_File.h: interface for the CBufMng_File class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUFMNG_FILE_H__09FFCFD7_8AFD_40D7_8B39_02119E08F632__INCLUDED_)
#define AFX_BUFMNG_FILE_H__09FFCFD7_8AFD_40D7_8B39_02119E08F632__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MD5.h" 
#include "IBufMng_player.h"
#include "IBufMng_Download.h"
#include <map>
using namespace std;

class CBufMng_File : public IBufMng_Download, public IBufMng_player 
{
public:
	CBufMng_File(MD5& hash);  // used for unfinished task.
	CBufMng_File(MD5& hash, string fileName, unsigned int fileLength); 
	virtual ~CBufMng_File();

	/////////////////////////
	// IBufMng_player
	/////////////////////////
	virtual bool player_Open();
	//##ModelId=4A3DA78601B5
	virtual unsigned int player_Read(void* lpBuf, unsigned int nCount); 
	//##ModelId=4A3DA78601F4
	virtual unsigned __int64 player_Seek(__int64 lOff, unsigned int nFrom);
	virtual unsigned __int64 player_GetNextPos();
	//##ModelId=4A3DA7860242
	virtual unsigned __int64 player_GetLength();
	//##ModelId=4A3DA7860280
	virtual void player_Close();

	/////////////////////////
	// IBufMng_Download
	/////////////////////////
	//##ModelId=4A3DA78601F4
	virtual unsigned __int64 Seek(__int64 lOff, unsigned int nFrom);
	//##ModelId=4A3DA7860242
	//virtual unsigned __int64 GetLength();
	//##ModelId=4A3DA7860280
	virtual void Close();
	//##ModelId=4A3DA7860189
	virtual unsigned int Write(const void* lpBuf, unsigned int nCount); 
	//##ModelId=4A3DA7860196
	virtual bool IsComplete();
	virtual void Save();
	virtual bool ReloadUnfinishedFile();
	virtual bool Delete();
};

#endif // !defined(AFX_BUFMNG_FILE_H__09FFCFD7_8AFD_40D7_8B39_02119E08F632__INCLUDED_)
