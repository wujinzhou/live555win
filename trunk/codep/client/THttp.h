#pragma once

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>

#include <QTimer>
#include <QByteArray>
#include <QThread>
#include <QEventLoop>
#include <QtNetwork/QNetworkReply>
#include <QTcpSocket>

class Http:public QObject
{
	Q_OBJECT
public:
	Http(QObject *parent = 0);
	~Http();
	QByteArray& GetDownLoadUrl(const QString& _url); 
	public slots:
		void replyFinished(QNetworkReply*); /* download finished */
		void slotError(QNetworkReply::NetworkError); /* handle error */
		void handleTimeOut(); /* handle time out */
		void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
	QNetworkAccessManager    *downloadManager;
	QEventLoop*   qEvent;
	QTimer        *timeOut; 
	QByteArray _rt;
	QNetworkReply* reply;
};


