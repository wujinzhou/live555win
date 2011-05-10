// IBufMng_Download.h: interface for the IBufMng_Download class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IBUFMNG_DOWNLOAD_H__3B093041_C501_4348_8996_6D291F7D8537__INCLUDED_)
#define AFX_IBUFMNG_DOWNLOAD_H__3B093041_C501_4348_8996_6D291F7D8537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "md5.h"

using namespace std;


//##ModelId=4A3DA786017B
class IBufMng_Download
{
public:
	//##ModelId=4A3DA7860186
	IBufMng_Download(){};
	//##ModelId=4A3DA7860187
	virtual ~IBufMng_Download(){}; 

	//##ModelId=4A3DA78601F4
	//virtual unsigned __int64 Seek(__int64 lOff, unsigned int nFrom) = 0;
	//##ModelId=4A3DA7860242
	//virtual unsigned long GetLength() = 0;
	//##ModelId=4A3DA7860280
	virtual void Close() = 0;
	//##ModelId=4A3DA7860189
	//virtual unsigned int Write(const void* lpBuf, unsigned int nCount) = 0;
	virtual unsigned int Write(__int64 lOff, const void* lpBuf, unsigned int nCount) = 0;
	//##ModelId=4A3DA7860196
	virtual bool IsComplete() = 0;	
	virtual void Save() = 0;
	virtual bool ReloadUnfinishedFile() = 0;   
	virtual bool Delete() = 0;
};

#ifdef BUFFERMNG_EXPORTS
#define BUFFERMNG_DLL_EXPORTED __declspec(dllexport)
#else
#define BUFFERMNG_DLL_EXPORTED __declspec(dllimport)
#endif
extern "C"  BUFFERMNG_DLL_EXPORTED void CreateBUFMng(MD5& hash, string fileName, unsigned int fileLength, IBufMng_Download* &pBufMng_Download,  IBufMng_player* &pBufMng_player);
extern "C"  BUFFERMNG_DLL_EXPORTED void ReloadBUFMng(MD5& hash, IBufMng_Download* &pBufMng_Download,  IBufMng_player* &pBufMng_player);


#endif // !defined(AFX_IBUFMNG_DOWNLOAD_H__3B093041_C501_4348_8996_6D291F7D8537__INCLUDED_)
