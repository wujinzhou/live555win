#pragma once

#include <QObject>
class IAvCore:public QObject
{
	Q_OBJECT
public:
	virtual	bool  encoder(char* inFile,char* outFiles,int ibegin,int iDuration,char*  size,int b,char* ffpreset,int ithreads )  = 0; 
	virtual bool start() = 0;
	virtual bool pause() = 0;
	virtual bool stop() = 0;
	virtual bool splitfile(char* inFile,int n,char* outFiles[]) = 0;
	virtual bool combination(int fileCount,char* inFiles[],char* originalFile,char* outFile) = 0;

Q_SIGNALS:
	void signalState();
	void signalProgress();
};
 