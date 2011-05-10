#pragma once

#include <string>
#include <winsock2.h>

class IBlockListener;

//Ƭ��������
//Ŀǰֻ������Ƭ����������UDT��HTTP��TCP��
class IBlockDownloader
{
public:
	//���캯�����ļ�ID��hash�룩���ļ���С���ֿ��С
	IBlockDownloader(IBlockListener *pListener,const std::string &strFileID,
		int iFileSize, int iBlockSize=8*1024){};
	virtual ~IBlockDownloader(void){};

	//�����Ľӿ����Ա�֤�̰߳�ȫ����˸�Ϊ���캯���д��� -tianzuo,6.25
	//������Ϣ���սӿڡ������Ҫɾ����������ΪNULL����
	//void SetListener(IBlockListener *pListener);

	//���Խ������ӣ��첽��
	virtual bool Connect(int iDistID,sockaddr *name=NULL,int iLen=0) = 0;
	//virtual bool Connect(int iDistID ) = 0; //�����麯��������Ҫ����������ȷ�����ĸ���̫�鷳������Ĭ�ϲ���

	//�����ļ�Ƭ�Σ��첽��
	//����ļ������ڣ�����OnConnectMsg�еõ�����
	virtual bool Download(int iBlockIndex) = 0;;
};

//IBlockDownloader��Ϣ�����������ӿ�
class IBlockListener
{
public:
	enum emDLMSG{
		DL_CONNECTED,
		DL_CONNECTFAIL,
		DL_FILENOTFOUND,
		DL_CONNECTBREAK,
	};
	//������Ϣ�����ӽ���������ʧ�ܣ��ļ������ڣ����ӶϿ���
	virtual void OnConnectMsg(IBlockDownloader *pDownloader,emDLMSG iMsgCode) = 0; 

	//���ݵ�����Ϣ��
	//ע��iDataLen���Ȳ�һ������BlockSize���ļ����һ��Ƭ�ε������
	virtual void OnBlock(int iuserID,int iBlockIndex,const char *pData,int iDataLen) = 0; //Ƭ���������
};