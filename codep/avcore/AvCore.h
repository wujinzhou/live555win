#pragma once
#include <QLibrary>
#include "IAvCore.h"
#include "avfile.h"
typedef int (*FUN_setFileCallBack)(FUN_fopen o,FUN_fwrite w,FUN_fread r, FUN_fseek  s,FUN_ftell t,FUN_fclose c,FUN_stat Fstat,FUN_fstat fst);
typedef int (*FUNC_ffmpegMain)(int argc, char **argv);
class AvCore:public IAvCore
{
	
	FUNC_ffmpegMain av_ffmpegMain; 
	FUN_setFileCallBack  av_setFileCallBack; 
	quint64  m_Duration;
public:
	AvCore(void);
	~AvCore(void);

	virtual	bool encoder(char* inFile,char* outFiles,int ibegin,int iDuration,char*  size,int b,char* ffpreset,int ithreads )  ; 
	virtual bool start() ;
	virtual bool pause() ;
	virtual bool stop() ;

	virtual bool splitfile(char* inFile,int n,char* outFiles[]) ;
	virtual bool combination(int fileCount,char* inFiles[],char* originalFile,char* outFile) ;
private:
	quint64 getDuration(char* );
};
