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
	av_register_all();

}
AvCore::~AvCore(void)
{

}
bool AvCore::encoder(char* inFile,char* outFiles,char* encoderargs) 
{

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
	//	QString arg = QString("D:\\Temp\\bin\\code\\bin\\debug\\win32\\ffmpeg -i %1 -i %2 -vcodec copy -sn -i %3 -acodec copy -y  %4 ").arg(inFiles[0]).arg(inFiles[1]).arg(originalFile).arg(outFile);
	QString arg = QString("\"D:\\Program Files\\MediaCoder\\codecs\\mencoder.exe\" -ovc copy  -nosound  %1  %2 -o %3 ").arg(inFiles[0]).arg(inFiles[1]).arg(outFile);

	QStringList str;
	str << "";
	process->start(arg);
	process->waitForFinished(50000); 



	 arg = QString("D:\\Temp\\bin\\code\\bin\\debug\\win32\\ffmpeg -i %1   -vcodec copy -sn -i %2 -acodec copy -y  d:\\f.flv  -y ").arg(outFile).arg(originalFile);
	str << "";
	process->start(arg);
	process->waitForFinished(50000); 
	delete process;
	process = NULL;

	return true;
 
	AVFormatContext* oc = av_alloc_format_context();


	AVFormatContext* pFormatCtx= NULL;

	if(av_open_input_file(&pFormatCtx,inFiles[0], NULL,0, NULL)!=0)
	{
		qDebug("+++++Couldn't open file++++++++++++\n");
		return -1; // Couldn't open file
	} 

	if(av_find_stream_info(pFormatCtx)<0)
		return -1; // Couldn't find stream information
	oc->oformat = guess_format("flv", NULL, NULL);
	sprintf(oc->filename,  "%s", outFile);
	int videoStreamID = -1;
	for(int i=0; i< pFormatCtx->nb_streams; i++)
	{
		if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) 
		{ 
			videoStreamID=i; 
			break;
		} 
	} 
	AVStream * st = av_new_stream(oc, 0);
	AVCodecContext * c = st->codec;
	avcodec_copy_context(c,pFormatCtx->streams[videoStreamID]->codec);
//    c->codec_id = pFormatCtx->streams[videoStreamID]->codec->codec_id;
//    c->codec_type = pFormatCtx->streams[videoStreamID]->codec->codec_type;
//	c->pix_fmt = pFormatCtx->streams[videoStreamID]->codec->pix_fmt;
//
//    /* put sample parameters */
//    c->bit_rate = pFormatCtx->streams[videoStreamID]->codec->bit_rate;
//    /* resolution must be a multiple of two */
//    c->width = pFormatCtx->streams[videoStreamID]->codec->width;  
//    c->height = pFormatCtx->streams[videoStreamID]->codec->height;
//	c->time_base = pFormatCtx->streams[videoStreamID]->codec->time_base;
//	c->has_b_frames = pFormatCtx->streams[videoStreamID]->codec->has_b_frames;
//    /* frames per second */
////   c->frame_rate = pFormatCtx->streams[videoStreamID]->codec->frame_rate;  
////    c->frame_rate_base = 1;
//    c->gop_size = 12; /* emit one intra frame every twelve frames at most */
//    if (c->codec_id == CODEC_ID_MPEG2VIDEO) {
//        /* just for testing, we also add B frames */
//        c->max_b_frames = 2;
//    }
//    if (c->codec_id == CODEC_ID_MPEG1VIDEO){
//        /* needed to avoid using macroblocks in which some coeffs overflow 
//           this doesnt happen with normal video, it just happens here as the 
//           motion of the chroma plane doesnt match the luma plane */
//        c->mb_decision=2;
//    }
//    // some formats want stream headers to be seperate
//    if(!strcmp(oc->oformat->name, "mp4") || !strcmp(oc->oformat->name, "mov") || !strcmp(oc->oformat->name, "3gp")|| !strcmp(oc->oformat->name, "flv"))
//        c->flags |= CODEC_FLAG_GLOBAL_HEADER;
    
//	st->codec = pFormatCtx->streams[videoStreamID]->codec; 
	if (av_set_parameters(oc, NULL) < 0) {
		fprintf(stderr, "Invalid output format parameters\n");
		exit(1);
	}
	 dump_format(oc, 0, outFile, 1);
	 if (url_fopen(&oc->pb, outFile, URL_WRONLY) < 0) {
		 fprintf(stderr, "Could not open '%s'\n", outFile);
		 exit(1);
	 }
	av_write_header(oc);
	AVPacket packet;
	while(1)
	{
		if(av_read_frame(pFormatCtx, &packet)>=0) 
		{
			if (packet.stream_index == videoStreamID)
			{  
				  av_write_frame(oc, &packet);
			}
		}
		else
		{
			break;
		}
	}
	 av_write_trailer(oc);
	// Retrieve stream information

	// Dump information about file onto standard error
 
	av_close_input_file(pFormatCtx); 
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