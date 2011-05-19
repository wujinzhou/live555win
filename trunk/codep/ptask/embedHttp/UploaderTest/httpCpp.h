#pragma once

#include <curl/curl.h>
#include <string>

//#ifdef _DEBUG
//#include <fstream>
//#endif


/**
 * 发送Http Post数据的封装
 *
 * 使用方法：创建对象、init，然后增加一个field，然后doPost（这是同步的），最后用getResult取得返回结果。
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

	// 为post增加一个field
	bool addBinField(const char* name, const char* value, int iValueLen); //二进制类型
	bool addField(const char* name, const char* value, const char* mime_type=NULL);

	//阻塞方式进行post数据
	bool doPost(void);
	bool doGet(void);

	//取post之后,服务器返回的数据
	std::string getResult(void);

private:
	//服务器地址
	std::string m_strServerUrl;

	//主curl句柄
	CURL* m_pCurl;

	// post所用的头指针,用于curl_easy_setopt(curl, CURLOPT_httpCpp, post)的第三个参数
	struct curl_httppost *m_pPost;

	// post链表的尾指针,用于增加插入数据的速度
	struct curl_httppost *m_pLast;

	//post的result将写到这个buffer里面,可以通过getResult()取得
	std::string resultBuffer;

//#ifdef _DEBUG
//	//DEBUG版，会将服务器返回的内容保存在本地磁盘中
//	std::ofstream m_ofs;
//#endif

private:
	//回调函数：当数据到达，写入磁盘里
	static size_t OnData( void *ptr, size_t size, size_t nmemb, void *pInstance);
public:
	//方便使用的阻塞式函数
	static std::string httpget(const char *url);
};

