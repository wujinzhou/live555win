#include "THttp.h"

Http::Http(QObject *parent):QObject(parent)
{
	downloadManager = new QNetworkAccessManager(this);
	connect(downloadManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
	//timeOut = new QTimer(this);
	//connect(timeOut, SIGNAL(timeout()), this, SLOT(handleTimeOut()));
	//qEvent=new QEventLoop();
	//reply=NULL;
}

Http::~Http()
{
	_rt.clear();
	delete downloadManager;
	//delete timeOut;
	//delete qEvent;
}

QByteArray& Http::GetDownLoadUrl(const QString& _url)
{
	_rt.clear();
	QUrl url(_url);
	if (!url.isValid()) return _rt;

	QNetworkRequest* request=new QNetworkRequest(url);
	reply = downloadManager->get(*request);

	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(slotError(QNetworkReply::NetworkError)));
	connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));

	//timeOut->start(18000);
	//qEvent->exec();
	//reply->close();
	//delete reply;
	//delete request;
	return _rt;
}

void Http::replyFinished(QNetworkReply*) /* download finished */
{
	_rt.append( reply->readAll() );
	//timeOut->stop();
	//qEvent->exit();
}

void Http::slotError(QNetworkReply::NetworkError)
{
	//timeOut->stop();
	//qEvent->exit();
}

/* ³¬Ê± */
void Http::handleTimeOut()
{
	//timeOut->stop();
	//qEvent->exit();

}

void Http::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	_rt.append( reply->readAll() );
	_rt.append( reply->readAll() );
}

