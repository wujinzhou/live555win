#include ".\servthread.h"
#include "UploadHandler.h"
#include <assert.h>


class SP_HttpEchoHandlerFactory : public SP_HttpHandlerFactory {
public:
	SP_HttpEchoHandlerFactory(HttpUploader *pUploader){
		m_pUploader = pUploader;
	}
	virtual ~SP_HttpEchoHandlerFactory(){}

	virtual SP_HttpHandler * create() const {
		return new UploadHandler(m_pUploader);
	}
private:
	HttpUploader *m_pUploader;
};

ServThread::ServThread(HttpUploader *pUploader)
:m_threadTaskReport("http://localhost:8080/status","")
{
	m_pUploader = pUploader;

	m_pSpServer = NULL;
}

ServThread::~ServThread(void)
{
	m_threadTaskReport.Kill();
}

void * ServThread::Thread()
{
	ThreadStarted();
	m_threadTaskReport.Start();

	int port = 8080, maxThreads = 10;
	const char * serverType = "hahs";

	if( 0 != sp_initsock() ) assert( 0 );

	m_pSpServer = new SP_IocpServer( "", port, new SP_HttpHandlerAdapterFactory( new SP_HttpEchoHandlerFactory(m_pUploader) ) );

	m_pSpServer->setTimeout( 60 );
	m_pSpServer->setMaxThreads( maxThreads );
	m_pSpServer->setReqQueueSize( 100, "HTTP/1.1 500 Sorry, server is busy now!\r\n" );
	m_pSpServer->runForever();

	sp_closelog();

	return NULL;
}

void ServThread::shutdown()
{
	m_pSpServer->shutdown();
}