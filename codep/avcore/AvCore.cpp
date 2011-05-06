#include "AvCore.h"

#include <QProcess>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include <stdio.h>
#include <libavcodec\avcodec.h>
#include <libavformat\avformat.h>
#include <libswscale\swscale.h>  
#include <math.h>
#include <string.h>  
}

AvCore::AvCore(void)
:m_Duration(0)
{
	//av_register_all();
 

}
AvCore::~AvCore(void)
{

}
bool AvCore::encoder(char* inFile,char* outFiles,int ibegin,int iDuration,char*  size,int b,char* ffpreset,int ithreads ) 
{

	QLibrary myLib("L:\\Projects\\svn\\codep\\avcore\\avcore.exe");
	av_setFileCallBack = (FUN_setFileCallBack) myLib.resolve("setFileCallBack"); 
	av_ffmpegMain = (FUNC_ffmpegMain) myLib.resolve("ffmpegMain");  
	{
		QString arg = QString("ffmpeg.exe -threads %1 -ss %2 -t %3 -i %4 -f flv -vcodec libx264 -s %5 -fpre %6 %7 r")\
			.arg(ithreads).arg(ibegin).arg(iDuration).arg(inFile).arg(size).arg(ffpreset).arg(outFiles);

		QStringList str;
		str = arg.split(" ");
		char** argc= new char*[str.size()];
		QByteArray *  pdata = new QByteArray[str.size()];
		for (int i = 0;i<str.size();i++)
		{
			pdata[i] = str.at(i).toLatin1();
			argc[i]  = pdata[i].data();
			qDebug("%s",argc[i]);
		}
		av_ffmpegMain(str.size(),argc);

	}  
	return true;
}
bool AvCore::start() 
{
	return true;

}
bool AvCore::pause() 
{

	return true;
}
bool AvCore::stop() 
{

	return true;
}

bool AvCore::splitfile(char* inFile,int n,char* outFiles[]) 
{

	QProcess *process = new QProcess;
	quint64 durarion = getDuration(inFile);
	quint64 iSplitTime = durarion/n/1000/1000;
	for (int i = 0;i<n;i++)
	{
		QString arg = QString("D:\\Temp\\bin\\code\\bin\\debug\\win32\\ffmpeg -i %1  -vcodec copy -an  -ss  %2 -t %3  %4  -y").arg(inFile).arg(i*iSplitTime).arg((i+1)*iSplitTime).arg(outFiles[i]);

		QStringList str;
		str << "";
		process->start(arg);
		process->waitForFinished(50000);
	}
	delete process;
	process = NULL;

	return true;
}
bool AvCore::combination(int fileCount,char* inFiles[],char* originalFile,char* outFile) 
{

	QProcess *process = new QProcess;  

	QString  infiles;
	for(int i = 0;i<fileCount;i++)
	{
		infiles += QString(inFiles[i]);
		infiles += QString(" "); 
	}

	QString arg = QString("mencoder.exe -ovc copy  -nosound  %1  %2 -o %3 ").arg(inFiles[0]).arg(inFiles[1]).arg(outFile);

	QStringList str;
	str << "";
	process->start(arg);
	process->waitForFinished(50000); 

 

	return true; 
}

quint64 AvCore::getDuration(char*  fileName)
{
	AVFormatContext* pFormatCtx= NULL;

	if(av_open_input_file(&pFormatCtx,fileName, NULL,0, NULL)!=0)
	{
		qDebug("+++++Couldn't open file++++++++++++\n");
		return -1; // Couldn't open file
	}
	// Retrieve stream information

	if(av_find_stream_info(pFormatCtx)<0)
		return -1; // Couldn't find stream information
	// Dump information about file onto standard error
 
	 m_Duration = pFormatCtx->duration;
	av_close_input_file(pFormatCtx);
	pFormatCtx = NULL;
	return m_Duration;
}