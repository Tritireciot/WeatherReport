#pragma once

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class QNetworkAccessManager;
class QNetworkReply;

class Requester : public QObject {
    Q_OBJECT

    private:

        QNetworkAccessManager* networkManager;

        QNetworkReply* generateReply(const QUrl& url, const QString& keyHeaderName, const QString& apiKey);

    public:

        Requester(QObject* pobj = nullptr);
        void getRequest(const QUrl& url, const QString& keyHeaderName, const QString& apiKey);
        void checkAuth(const QUrl& url, const QString& keyHeaderName, const QString& apiKey);

    signals:
        void done(int httpStatus, QByteArray body);
        void error(QString message, int httpStatus);
        void authResult(int httpStatus, QString message);
};