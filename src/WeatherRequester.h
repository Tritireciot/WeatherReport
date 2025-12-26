#pragma once

#include <QWidget>
#include <QUrl>
#include <QPushButton>
#include <QLabel>
#include <QJsonDocument>
#include "Requester.h"
#include "LampIndicator.h"

class QPushButton;
class QPlainTextEdit;

class WeatherRequester : public QWidget {
    Q_OBJECT

    private:
        Requester* requester;
        QPushButton* requestButton;
        LampIndicator* lampIndicator_;
        QString weatherLink;

        QLabel* tempBig_;
        QLabel* pressure_;
        QLabel* wind_ ;
        QLabel* humidity_;
        QLabel* feels_;
        QLabel* cond_;

        void resetForm();
        void applyWeatherJson(const QJsonDocument& doc);
        QVBoxLayout* createForm();


    public:
        WeatherRequester(QWidget* pwgt, LampIndicator* lampIndicator);
        void checkAuth(const QString& apiKey);

    private slots:
        void slotGo();
        void slotError(QString message, int httpStatus);
        void slotDone(const int&, const QByteArray&);
        void slotIsAuthed(int, QString);
};