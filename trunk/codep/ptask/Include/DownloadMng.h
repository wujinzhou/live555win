// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_DOWNLOADMNG_4A40EB100290_INCLUDED
#define _INC_DOWNLOADMNG_4A40EB100290_INCLUDED

#include "IDownloadMng.h"
#include "IDownloadNotify.h"
#include "Task.h"

#include <map>
#include "udt.h"
using namespace UDT;
typedef map<MD5,ITask*>   T_mapTask;

#ifdef DOWNLOADMNG_EXPORTS
#define DOWNLOADMNG_CLASS __declspec(dllexport)
#else
#define DOWNLOADMNG_CLASS __declspec(dllimport)
#endif


//##ModelId=4A40EB100290
class DOWNLOADMNG_CLASS DownloadMng 
: public IDownloadMng
{
	en_Connect_Type   m_connectType;
	T_mapTask      m_mapTask;
	TPeerMng*      m_pMng;
public:
	DownloadMng(TPeerMng* pMng,en_Connect_Type  type);
	//##ModelId=4A422FE10000
	IDownloadNotify* theIDownloadNotify;
	virtual bool AddTask(MD5 hash,string filePath,T_vectUser userlist)  ;
	//##ModelId=4A42508F01D4
	virtual bool DelTask(MD5 fileHash) ;
	virtual bool PauseTask(MD5 hash) ;

	//##ModelId=4A42508F0213
	virtual ITask* GetTask(MD5 fileHash) ;
};

#endif /* _INC_DOWNLOADMNG_4A40EB100290_INCLUDED */
