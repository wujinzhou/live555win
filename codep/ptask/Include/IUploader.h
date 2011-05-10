#pragma once
#include <string>
#include <winsock2.h>
#include "udt.h"
#include "IFileMng.h"

//////////////////////////////////////////////////////////////////////////
//�ϴ����ӿ�
//Ŀǰ�������ϴ������䴴���������в�ͬ����ʹ����������
class IUploader
{
public:
	IUploader(void){};
	virtual ~IUploader(void){};

	//�����ļ�������ָ�롣
	//Uploaderʹ�����������ļ��ڱ��صı���λ��
	//Ҫ�����ʱ����SetFileMng(NULL)
	virtual void SetFileMng(IFileMng *pFileMng)=0;

	//������������ģʽ��
	virtual bool StartServ()=0;

	//ֹͣ��������ģʽ��
	virtual bool StopServ()=0;

	//��ȡ�����ַ��
	//iType�������Э�����ͣ�0ΪUDT��1ΪTCP��2ΪHTTP
	virtual bool GetServAddress(sockaddr *name, int &iLen, int &iType) = 0;
};

//class IFileMng
//{
//public:
//	//�����ļ�ID��hash�����ҳ��ļ����ر���·����
//	//�ļ��������򷵻ؿ�·����
//	virtual std::string FindFilePath(const std::string &strFileID) = 0;
//};

//////////////////////////////////////////////////////////////////////////
//IUploader��������ͬ��Uploader�Ĵ���������һ����
class TPeerMng;
class UploaderFactory
{
public:
	static IUploader *CreateTCPUploader(int iMyId, sockaddr *name, int iLen);
	static IUploader *CreateHttpUploader(int iMyId, sockaddr *name, int iLen);
	static IUploader *CreateUdtUploader(UDT::TPeerMng *pPeerMng);
};