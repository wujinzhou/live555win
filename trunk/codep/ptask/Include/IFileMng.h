// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_IFILEMNG_4A3DA83D02BF_INCLUDED
#define _INC_IFILEMNG_4A3DA83D02BF_INCLUDED

#include "IFileMngNotify.h"
#include <vector>
#include <string>
#include "MD5.h"

using namespace  std;
//##ModelId=4A3DABD40179
typedef vector<MD5> Vc_FileList;
//##ModelId=4A3DA83D02BF
class IFileMng 
{
public:	
public:
	IFileMng(){};
	virtual ~IFileMng(){};

	//##ModelId=4A3DA85C033C
	virtual bool StartCheck(IFileMngNotify *pFileMngNotify) = 0;
	//##ModelId=4A3DA8DA02BF
	virtual bool AbortCheck() = 0;

	//##ModelId=4A3DA8E80148
	virtual string GetFilePathFromHash(MD5& hash) = 0;

	//##ModelId=4A3DA902030D
	virtual bool AddFileRecord(MD5& hash,string& filePath) = 0;

	//##ModelId=4A3DA902030D
	//virtual bool AddFileRecords(MD5& hash,string& filePath) = 0;

	//##ModelId=4A3DA90A036B
	virtual bool DelFileRecord(MD5& hash) = 0;

	//##ModelId=4A3DA9490271
	virtual bool GetFileList(Vc_FileList& fileList) = 0;
};

#ifdef FILEMNG_EXPORTS
#define FILEMNG_DLL_EXPORTED __declspec(dllexport)
#else
#define FILEMNG_DLL_EXPORTED __declspec(dllimport)
#endif
extern "C"  FILEMNG_DLL_EXPORTED IFileMng* CreateFileMng();
#endif /* _INC_IFILEMNG_4A3DA83D02BF_INCLUDED */
