#include "Requester.h"
#include <QTimer>

Requester::Requester(QObject* pobj) : QObject(pobj){
    networkManager = new QNetworkAccessManager(this);
}

QNetworkReply* Requester::generateReply(const QUrl& url, const QString& keyHeaderName, const QString& apiKey){
    QNetworkRequest request(url);
    request.setRawHeader(keyHeaderName.toUtf8(), apiKey.toUtf8());
    QNetworkReply* reply = networkManager->get(request);
    QTimer* timeout = new QTimer(reply);
    timeout->setSingleShot(true);
    timeout->setInterval(20000);
    QObject::connect(timeout, &QTimer::timeout, reply, [reply] {
            if (reply->isRunning()) {
                reply->setProperty("timed_out", true);
                reply->abort();
            }
    });
    timeout->start();
    return reply;
}

void Requester::getRequest(const QUrl& url, const QString& keyHeaderName, const QString& apiKey){
    QNetworkReply* reply = generateReply(url, keyHeaderName, apiKey);
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        const bool timedOut = reply->property("timed_out").toBool();
        const int http = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (timedOut) {
            emit error(QString("Timeout"), http);
            reply->deleteLater();
            return;
        }
        const QByteArray body = reply->readAll();
        if (reply->error() != QNetworkReply::NoError) {
            emit error(reply->errorString(), http);
        } else {
            emit done(http, body);
        }
        reply->deleteLater();
    });
}

void Requester::checkAuth(const QUrl& url, const QString& keyHeaderName, const QString& apiKey) {
    QNetworkReply* reply = generateReply(url, keyHeaderName, apiKey);
    connect(reply, &QNetworkReply::finished, this, [this, reply, apiKey] {
        const int http = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        emit authResult(http, apiKey);
        reply->deleteLater();
    });
}