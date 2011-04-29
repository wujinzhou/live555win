#pragma once
#include "IAvCore.h"
class AvCore:public IAvCore
{
	quint64  m_Duration;
public:
	AvCore(void);
	~AvCore(void);

	virtual	bool encoder(char* inFile,char* outFiles,char* encoderargs) ; 
	virtual bool start() ;
	virtual bool pause() ;
	virtual bool stop() ;

	virtual bool splitfile(char* inFile,int n,char* outFiles[]) ;
	virtual bool combination(int fileCount,char* inFiles[],char* originalFile,char* outFile) ;
private:
	quint64 getDuration(char* );
};
