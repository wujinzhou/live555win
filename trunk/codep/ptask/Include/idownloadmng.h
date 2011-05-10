// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_IDOWNLOADMNG_4A40EB0001A5_INCLUDED
#define _INC_IDOWNLOADMNG_4A40EB0001A5_INCLUDED
#include <vector>
#include <string>
#include "RaProtocolStruct.h"
#include "Connection.h"
using namespace std;
class ITask;
typedef vector<RA_SC_UserInfo>  T_vectUser;
//##ModelId=4A40EB0001A5
class IDownloadMng 
{
public:
	IDownloadMng(en_Connect_Type  type){};
	//##ModelId=4A42508F01B5
	inline virtual ~IDownloadMng();

	virtual bool AddTask(MD5 hash,string filePath,T_vectUser userlist) = 0;
	//##ModelId=4A42508F01D4
	virtual bool DelTask(MD5 fileHash) = 0;
	virtual bool PauseTask(MD5 hash) = 0;

	//##ModelId=4A42508F0213
	virtual ITask* GetTask(MD5 fileHash) = 0;

};


//##ModelId=4A42508F01B5
inline IDownloadMng::~IDownloadMng()
{
	// TODO: Add your specialized code here.
}

#ifdef DOWNLOADMNG_EXPORTS
#define DOWNLOADMNG_CLASS __declspec(dllexport)
#else
#define DOWNLOADMNG_CLASS __declspec(dllimport)
#endif
extern "C" DOWNLOADMNG_CLASS IDownloadMng* CreateDownloadMng(UDT::TPeerMng* pMng,en_Connect_Type  type);
#endif /* _INC_IDOWNLOADMNG_4A40EB0001A5_INCLUDED */
