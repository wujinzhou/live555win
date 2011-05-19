#pragma once
#include <vector>
#include <string>
/*
Ƶ�����ã�����������֡��С
�����ͷ����Ƶ֡��ʼλ��
�ļ�ͷ���Ƿ�ؼ�֡
��Ƶ֡ͷ��

�����ߵĹ�ϵ�ǣ�һ��Ƶ�������ݣ���Ƶ���������ݺ�Ƶ������������ɣ�
Ƶ������������һ�������ȹ̶��Ĵ������ɡ�
������ɴ����ͷ�ʹ��������ɡ�
һ����������尴˳����װ����������ʵ�ʴ����ý����������
ý�����������ɶ��˳�򲥷ŵ���Ƶ�ļ���ɵġ�
ÿһ����Ƶ�ļ������ļ�ͷ�����������ļ���ʽ��һЩ��Ҫ�Ĳ�����Ϣ���������ļ������ţ���һ·Ƶ���У������������˳������ģ���
��Ƶ�ļ�����һ�������ȿɱ����Ƶ֡��ɵġ���Ƶ֡Ҳ��Ϊ֡ͷ��֡�塣
*/

//==========================================
//BufferManager�Ķ���ӿ�
//==========================================


#ifdef BUFFERMAP_EXPORTS
#define BUFFERMAP_DLL_EXPORTED __declspec(dllexport)
#else
#define BUFFERMAP_DLL_EXPORTED __declspec(dllimport)
#endif

#ifndef __BUFFERMAP_H
#define __BUFFERMAP_H


#pragma warning( disable : 4200)	//�ر�΢��Ǳ�׼��չ����
#pragma pack(1)	//���ֽڶ��뷽ʽ��Ϊ1�ֽ�

//���ݿ��ʽ
struct TRawBlock
{
	int iBlockLen;         //���С��ע�⣬��������ͷ��Сsizeof(TRawBlock)
	int iFirstPackPos;     //��һ������λ��
	int iBlockIndex;       //�������
	char data[];
};


//���ݰ���ʽ
struct TRawPack
{
	int iLen;              //����С
	unsigned short usFileIndex;      //�ļ�index�������������һ�����ļ���ɣ�ÿ���ļ�һ��index
	unsigned short usFileSliceIndex; //�ļ�Ƭ��index��һ���ļ������ݱ���Ϊһ����slice��ÿ��sliceһ��index
	char type;	           //Ŀǰ�Ѷ���İ������У�֡ͷ���ؼ�֡���ǹؼ�֡������֡����PACK_TYPE���塣
	char cReserved;        //�����ֶ�
	char data[];

	//�����Ͷ���
	enum PACK_TYPE{
		PT_HEADER = 0,      //�ļ�ͷ
		PT_KEYFRAME = 1,    //�ؼ�֡
		PT_NORMALFRAME = 2, //��ͨ֡
		PT_STOPFRAME = 3,   //ֹͣ֡
	};
};

#pragma pack ()	//�ֽڶ��뷽ʽ���Ĭ��ֵ

//����BufferManager����Ϣ
class IBufferMonitor
{
public:
	virtual ~IBufferMonitor(){};

	//�����µĿ鵽��
	virtual void OnBufferAdded(int iBlockIndex,const char *pData,int iLen) = 0;//ȱ�ٳ����ֶ�
};

class BlockBufferManager;

//BufferManager�ӿ�
class BUFFERMAP_DLL_EXPORTED IBufferManager
{
public:
	virtual ~IBufferManager(){};

	//д�����ݣ���Ҫ�������ã�����WriteFileHeader���ض�Ҳ����
	virtual int WriteFileHeader(int iLen,const char *pHeader) = 0;
	virtual int WriteFileStream(int iLen,const char *pData) = 0;

	//�����ļ�id�����ļ�ͷ��д����
	//int GetMissedHeader(std::vector<int> &vecHeaderIndex);
	virtual int GetFileHeader(int iFileIndex,int &iLen, char *pHeader) = 0 ;	//pHeaderΪ��ȡ����
	//virtual int GetFileHeaderByBlock(int iBlockIndex,int &iLen, char *pHeader)  = 0;	//pHeaderΪ��ȡ����
	virtual int GetFileIndexByBlock(int iBlockIndex,int &iFileIndex) = 0;
	virtual int AddFileHeader(int iFileIndex,int iLen, char *pHeader) = 0 ;

	//�����ݣ���������
	virtual int ReadFileHeader(int &iLen,char *pHeader)  = 0; //
	virtual int ReadFileStream(char *pBuf,int &iLen)  = 0;  //-1���ļ�����
	virtual int ReadFileStreamPack(TRawPack *pPackOut,int &iLen)  = 0;  //-1���ļ�����

	//д�봫��飺����ģ����
	virtual int WriteBlock(int iIndex, const char *pBlock,int iLen)  = 0; //pBlock�����ݴ�С�������BlockSize��

	//������״�����ϴ�ģ����
	//ȡĳ�������������
	//�������ش���0����ֵ���쳣�򷵻�-1��һ����û���κ����ݵ�ʱ��
	virtual int GetSubstreamLastBlock(int iSubstream)  = 0;
	//������飺�ϴ�ģ����
	virtual int ReadBlock(int iIndex,char *pBlock,int &iBlockLen)  = 0;//pBlock�Ĵ�С������ڻ����BlockSize�������ڴ������

	//ͨ���˽ӿڣ����ӻ������ݱ仯��֪ͨ��Ϣ�������˺��ϴ�ģ����
	virtual int AddBMMonitor(IBufferMonitor *pMonitor)  = 0;
	virtual int RemoveMonitor(const IBufferMonitor *pMonitor)  = 0;
};

//���еĽӿں���������������0����������������ֵ����������ش�����
class BUFFERMAP_DLL_EXPORTED TBufferManager
	: public IBufferManager
{
public:
	TBufferManager(int iSubStreamCount,int BlockSize,const char *strBufferFile=NULL,int maxBufferSize=-1);
	virtual ~TBufferManager();

	//д�����ݣ���Ҫ�������ã�����WriteFileHeader���ض�Ҳ����
	int WriteFileHeader(int iLen,const char *pHeader);
	int WriteFileStream(int iLen,const char *pData);

	//�����ļ�id�����ļ�ͷ��д����
	//int GetMissedHeader(std::vector<int> &vecHeaderIndex);
	int GetFileHeader(int iFileIndex,int &iLen, char *pHeader) ;	//pHeaderΪ��ȡ����
	//int GetFileHeaderByBlock(int iBlockIndex,int &iLen, char *pHeader) ;	//pHeaderΪ��ȡ����
	int GetFileIndexByBlock(int iBlockIndex,int &iFileIndex);
	int AddFileHeader(int iFileIndex,int iLen, char *pHeader) ;

	//�����ݣ���������
	int ReadFileHeader(int &iLen,char *pHeader) ; //���ļ�ͷ
	int ReadFileStream(char *pBuf,int &iLen) ;    //�����������ݡ�-1���ļ�����
	int ReadFileStreamPack(TRawPack *pPackOut,int &iLen) ;  //��TRawPack��Ч����ReadFileStreamһ�£�ֻ�Ƿ�����Ϣ��һЩ��-1���ļ�����

	//д�봫��飺����ģ����
	int WriteBlock(int iIndex, const char *pBlock,int iLen) ; //pBlock�����ݴ�С�������BlockSize��

	//������״�����ϴ�ģ����
	//�������ش���0����ֵ���쳣�򷵻�-1��һ����û���κ����ݵ�ʱ��
	int GetSubstreamLastBlock(int iSubstream) ;
	//������飺�ϴ�ģ����
	int ReadBlock(int iIndex,char *pBlock,int &iBlockLen) ;//pBlock�Ĵ�С������ڻ����BlockSize�������ڴ������

	//ͨ���˽ӿڣ����ӻ������ݱ仯��֪ͨ��Ϣ�������˺��ϴ�ģ����
	int AddBMMonitor(IBufferMonitor *pMonitor) ;
	int RemoveMonitor(const IBufferMonitor *pMonitor) ;
private:
	BlockBufferManager *m_pImpBufferManager;
};

#endif //#ifndef __BUFFERMAP_H