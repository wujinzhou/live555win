#pragma once
#include "iuploader.h"
#include "udt.h"
class GetFilePackHandler;
class UDT::TPeerMng;


#ifdef UDTUPLOADER_EXPORTS
#define UDTUPLOADER_DLL_EXPORTED __declspec(dllexport)
#else
#define UDTUPLOADER_DLL_EXPORTED __declspec(dllimport)
#endif

class UDTUPLOADER_DLL_EXPORTED UdtUploader :
	public IUploader,public UDT::IPeerDataListener
{
public:
	UdtUploader(UDT::TPeerMng *pPeerMng);
	~UdtUploader(void);

	//�����ļ�������ָ�롣
	//Uploaderʹ�����������ļ��ڱ��صı���λ��
	//Ҫ�����ʱ����SetFileMng(NULL)
	void SetFileMng(IFileMng *pFileMng);

	//������������ģʽ��
	bool StartServ();

	//ֹͣ��������ģʽ��
	bool StopServ();

	//��ȡ�����ַ��
	//iType�������Э�����ͣ�0ΪUDT��1ΪTCP��2ΪHTTP
	bool GetServAddress(sockaddr *name, int &iLen, int &iType);

	IFileMng *GetFileMng();

public:
	//IPeerDataListener�ص�����
	virtual void  OnPeerData(int iPeerId,const char* pData, int ilen);
private:
	UDT::TPeerMng *m_pPeerMng;
	IFileMng *m_pFileMng;
};

IUploader * UploaderFactory::CreateUdtUploader(UDT::TPeerMng *pPeerMng)
{
	return new UdtUploader(pPeerMng);
}
