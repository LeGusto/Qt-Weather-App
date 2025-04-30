#include "weatherapi.h"
#include <QJsonDocument>
#include <QJsonObject>
// #include <iostream>

WeatherAPI::WeatherAPI(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &WeatherAPI::onReply);
}

void WeatherAPI::fetchWeather() {
    QString apiKey = "b40b40a2ae0c40f0937155710253004";
    QString city = "London";
    QUrl url("http://api.weatherapi.com/v1/current.json?key=" + apiKey + "&q=" + city + "&aqi=no");
    manager->get(QNetworkRequest(url));
}

void WeatherAPI::onReply(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject allObj = doc.object();
        QJsonValue currVal = allObj.value(QString("current"));
        QJsonObject currObj = currVal.toObject();
        QJsonValue locVal = allObj.value(QString("location"));
        QJsonObject locObj = locVal.toObject();
        QString city = locObj["name"].toString();
        QString temp = QString::number(currObj["temp_c"].toDouble()) + "°C";
        emit weatherUpdated(city, temp);
        qDebug() <<city<<" "<<temp<<"\n";
    }
    reply->deleteLater();
}
