#include "WeatherRequester.h"
#include "utils.h"
#include <QtWidgets>


const QString YandexHeaderKeyName = "X-Yandex-Weather-Key";

QVBoxLayout* WeatherRequester::createForm(){

    tempBig_ = new QLabel("-- °C", this);
    tempBig_->setStyleSheet("font-size: 40px; font-weight: 700;");
    tempBig_->setAlignment(Qt::AlignLeft);

    cond_ = new QLabel("--", this);
    cond_->setStyleSheet("font-size: 16px;");

    pressure_ = new QLabel("-- мм рт. ст.", this);
    wind_     = new QLabel("-- м/с, --", this);
    humidity_ = new QLabel("-- %", this);
    feels_    = new QLabel("Ощущается: -- °C", this);

    QFormLayout* form = new QFormLayout;
    form->setLabelAlignment(Qt::AlignLeft);
    form->setFormAlignment(Qt::AlignTop);
    form->setHorizontalSpacing(16);
    form->setVerticalSpacing(8);

    form->addRow("Давление:", pressure_);
    form->addRow("Ветер:", wind_);
    form->addRow("Влажность:", humidity_);
    form->addRow("Ощущается:", feels_);

    QGroupBox* box = new QGroupBox("Текущая погода", this);
    QVBoxLayout* v = new QVBoxLayout(box);
    v->addWidget(tempBig_);
    v->addWidget(cond_);
    v->addSpacing(8);
    v->addLayout(form);

    QVBoxLayout* root = new QVBoxLayout(this);
    root->addWidget(requestButton);
    root->addWidget(box);
    root->addStretch(1);
    return root;
}

void WeatherRequester::resetForm(){
    tempBig_->setText("-- °C");
    cond_->setText("--");
    pressure_->setText("-- мм рт. ст.");
    wind_->setText("-- м/с, --");
    humidity_->setText("-- %");
    feels_->setText("Ощущается: -- °C");
}


WeatherRequester::WeatherRequester(QWidget* pwgt, LampIndicator* lampIndicator) : QWidget(pwgt){
    const float lat = 55.753960;
    const float lon = 37.620393;

    lampIndicator_ = lampIndicator;
    requester = new Requester(this);
    requestButton = new QPushButton("Обновить");
    requestButton->setEnabled(false);
    weatherLink = QString("https://api.weather.yandex.ru/v2/forecast?lat=%1&lon=%2").arg(lat).arg(lon);

    connect(requestButton, SIGNAL(clicked()), this, SLOT(slotGo()));
    connect(requester, SIGNAL(done(const int&, const QByteArray&)), this, SLOT(slotDone(const int&, const QByteArray&)));
    connect(requester, SIGNAL(error(QString, int)), this, SLOT(slotError(QString, int)));
    connect(requester, SIGNAL(authResult(int, QString)), this, SLOT(slotIsAuthed(int, QString)));

    QVBoxLayout* requestLayout = createForm();
    setLayout(requestLayout);
}

void WeatherRequester::checkAuth(const QString& apiKey){
    requester->checkAuth(weatherLink, YandexHeaderKeyName, apiKey);
}

void WeatherRequester::slotIsAuthed(int httpStatus, QString message){
    bool success = httpStatus < 300 && httpStatus >= 200;
    if (success) {
        QSettings s;
        s.setValue("auth/apiKey", message);
    }
    resetForm();
    requestButton->setEnabled(success);
    lampIndicator_->setState(success);
}

void WeatherRequester::slotGo(){
    requestButton->setEnabled(false);
    QSettings s;
    QString YandexHeaderApiKey = s.value("auth/apiKey").toString();
    requester->getRequest(QUrl(weatherLink), YandexHeaderKeyName, YandexHeaderApiKey);
}

void WeatherRequester::slotDone(const int& http, const QByteArray& byteArray){
    requestButton->setEnabled(true);

    if (http < 200 || http >= 300) {
        slotError(QString("Bad HTTP request: %1").arg(http), http);
        return;
    }
    QJsonParseError pe{};
    const QJsonDocument doc = QJsonDocument::fromJson(byteArray, &pe);
    if (pe.error  != QJsonParseError::NoError) {
        slotError(pe.errorString(), http);
        return;
    }


    applyWeatherJson(doc);
}


void WeatherRequester::applyWeatherJson(const QJsonDocument& doc) {
    const QJsonObject root = doc.object();
    const QJsonObject fact = root.value("fact").toObject();
    if (fact.isEmpty()) {
        cond_->setText("Нет поля fact в ответе");
        return;
    }

    const int temp        = fact.value("temp").toInt();
    const int feelsLike   = fact.value("feels_like").toInt();
    const int pressureMm  = fact.value("pressure_mm").toInt();
    const int humidityPct = fact.value("humidity").toInt();
    const double windSp   = fact.value("wind_speed").toDouble();
    const QString windDir = fact.value("wind_dir").toString();
    const QString cond    = fact.value("condition").toString();

    tempBig_->setText(QString("%1 °C").arg(temp));
    cond_->setText(conditionRu(cond));

    pressure_->setText(QString("%1 мм рт. ст.").arg(pressureMm));
    humidity_->setText(QString("%1 %").arg(humidityPct));

    const QString dirRu = windDirRu(windDir);
    wind_->setText(QString("%1 м/с, %2").arg(windSp, 0, 'f', 1).arg(dirRu));

    feels_->setText(QString("%1 °C").arg(feelsLike));
}

void WeatherRequester::slotError(QString message, int httpStatus){
    QMessageBox::critical(this, QString("Error: %1").arg(httpStatus), message);
}

