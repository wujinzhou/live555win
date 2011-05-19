#pragma once

#include <curl/curl.h>
#include <string>

//#ifdef _DEBUG
//#include <fstream>
//#endif


/**
 * ����Http Post���ݵķ�װ
 *
 * ʹ�÷�������������init��Ȼ������һ��field��Ȼ��doPost������ͬ���ģ��������getResultȡ�÷��ؽ����
 * 
 *
 */
class httpCpp
{
public:
	httpCpp(const char * url);
	~httpCpp(void);

	// initialize the post, if ok return true, otherwise return false
	bool init(void);

	// Ϊpost����һ��field
	bool addBinField(const char* name, const char* value, int iValueLen); //����������
	bool addField(const char* name, const char* value, const char* mime_type=NULL);

	//������ʽ����post����
	bool doPost(void);
	bool doGet(void);

	//ȡpost֮��,���������ص�����
	std::string getResult(void);

private:
	//��������ַ
	std::string m_strServerUrl;

	//��curl���
	CURL* m_pCurl;

	// post���õ�ͷָ��,����curl_easy_setopt(curl, CURLOPT_httpCpp, post)�ĵ���������
	struct curl_httppost *m_pPost;

	// post�����βָ��,�������Ӳ������ݵ��ٶ�
	struct curl_httppost *m_pLast;

	//post��result��д�����buffer����,����ͨ��getResult()ȡ��
	std::string resultBuffer;

//#ifdef _DEBUG
//	//DEBUG�棬�Ὣ���������ص����ݱ����ڱ��ش�����
//	std::ofstream m_ofs;
//#endif

private:
	//�ص������������ݵ��д�������
	static size_t OnData( void *ptr, size_t size, size_t nmemb, void *pInstance);
public:
	//����ʹ�õ�����ʽ����
	static std::string httpget(const char *url);
};

