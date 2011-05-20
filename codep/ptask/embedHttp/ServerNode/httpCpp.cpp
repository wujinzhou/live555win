//#include "stdafx.h"
#include ".\httpCpp.h"
#include <ATLTRACE.H>

//#ifdef _DEBUG
//#include <fstream>
//const char * debugLogFile = "out.htm";
//#endif

const char * serverPostUrl = "http://192.168.92.128/post.php";

httpCpp::httpCpp(const char * url)
: m_pPost(NULL)
, m_pLast(NULL)
, m_pCurl(NULL)
, m_strServerUrl(url)
{
}

size_t httpCpp::OnData( void *ptr, size_t size, size_t nmemb, void *pInstance)
{
	size_t len = size*nmemb;

	class httpCpp *post = (class httpCpp*)pInstance;
	post->resultBuffer.append((char *)ptr, size*nmemb);

//#ifdef _DEBUG
//	std::ofstream &ofs = post->m_ofs;
//	ofs.write((char *)ptr,len);
//#endif

	return len;
}


httpCpp::~httpCpp(void)
{
	if (NULL != m_pPost)
		curl_formfree(m_pPost);

	if (m_pCurl)
		curl_easy_cleanup(m_pCurl);

//#ifdef _DEBUG
//	m_ofs.close();
//#endif
}

bool httpCpp::doGet(void){
	if (!m_pCurl)
	{
		return false;
	}

	CURLcode res;
	curl_easy_setopt(m_pCurl, CURLOPT_HTTPGET, m_pPost);
	res = curl_easy_perform(m_pCurl);

	// 0 means everything was ok, non-zero means an error occurred as <curl/curl.h> defines.
	// see http://curl.haxx.se/libcurl/c/curl_easy_perform.html for details
	if (0 == res)
		return true;
	else
		return false;
}
bool httpCpp::doPost(void)
{
	if (!m_pCurl)
	{
		return false;
	}

	CURLcode res;
	curl_easy_setopt(m_pCurl, CURLOPT_HTTPPOST, m_pPost);
	res = curl_easy_perform(m_pCurl);

	// 0 means everything was ok, non-zero means an error occurred as <curl/curl.h> defines.
	// see http://curl.haxx.se/libcurl/c/curl_easy_perform.html for details
	if (0 == res)
		return true;
	else
		return false;
}

bool httpCpp::addBinField( const char* name, const char* value, int iValueLen )
{
	ATLASSERT(name);
	ATLASSERT(value);
	ATLASSERT(iValueLen>0);

	return CURL_FORMADD_OK == curl_formadd(
		&m_pPost, &m_pLast, 
		CURLFORM_COPYNAME, name,
		CURLFORM_COPYCONTENTS, value, 
		CURLFORM_CONTENTSLENGTH, iValueLen,
		CURLFORM_END);

}
// 为post增加一个field
bool httpCpp::addField(const char* name, const char* value, const char* mime_type)
{
	CURLFORMcode res;
	if (NULL == mime_type)
	{
		res = curl_formadd(&m_pPost, &m_pLast, CURLFORM_COPYNAME, name,
				CURLFORM_COPYCONTENTS, value, CURLFORM_END);
	}
	else
	{
		res = curl_formadd(&m_pPost, &m_pLast, CURLFORM_COPYNAME, name,
               CURLFORM_COPYCONTENTS, value,
               CURLFORM_CONTENTTYPE, mime_type, CURLFORM_END);
	}

	if (CURL_FORMADD_OK	== res)
		return true;
	else
		return false;
	
}

// initialize the post, if ok return true, otherwise return false
bool httpCpp::init(void)
{
	m_pCurl = curl_easy_init();
	if (!m_pCurl)
		return false;

	//curl_easy_setopt(m_pCurl, CURLOPT_POST, TRUE);
	curl_easy_setopt(m_pCurl, CURLOPT_URL,
			m_strServerUrl.c_str());

	curl_easy_setopt(m_pCurl, CURLOPT_COOKIEFILE,"c:\\curl_cookies.txt");
    curl_easy_setopt(m_pCurl, CURLOPT_COOKIEJAR,"c:\\curl_cookies.txt");   

//#ifdef _DEBUG
//	curl_easy_setopt(m_pCurl, CURLOPT_VERBOSE, 1);
//
//	try{
//		m_ofs.open(debugLogFile,std::ios_base::binary);
//	}catch (...)
//	{
//		m_ofs.close();
//		return false;
//	}
//#endif
	curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION, OnData);
	curl_easy_setopt(m_pCurl, CURLOPT_WRITEDATA, this); //这是传递给OnData的第四个参数

	return true;
}

std::string httpCpp::getResult(void)
{
	return resultBuffer;
}

//方便使用的阻塞式函数
std::string httpCpp::httpget(const char *url){
	httpCpp hp(url);
	hp.init();
	hp.doGet();
	return hp.getResult();
}