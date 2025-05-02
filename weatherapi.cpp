#include "weatherapi.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
// #include <iostream>

WeatherAPI::WeatherAPI(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
}

void WeatherAPI::fetchCurrent() {
    // connect(manager, &QNetworkAccessManager::finished, this, &WeatherAPI::onCurrentReply);
    QUrl url("http://api.weatherapi.com/v1/current.json?key=" + apiKey + "&q=" + city + "&aqi=no");
    QNetworkReply *reply = manager->get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, [=]() { onCurrentReply(reply); });
}

void WeatherAPI::fetchForecast() {
    // connect(manager, &QNetworkAccessManager::finished, this, &WeatherAPI::onForecastReply);
    QUrl url("http://api.weatherapi.com/v1/forecast.json?key=" + apiKey + "&q=" + city + "&aqi=no");
    QNetworkReply *reply = manager->get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, [=]() { onForecastReply(reply); });
}

void WeatherAPI::setCity(QString &newCity)
{
    city = newCity;
}

void WeatherAPI::onCurrentReply(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject allObj = doc.object();
        QJsonValue curr = allObj["current"].toObject();
        QJsonValue loc = allObj["location"].toObject();
        QString city = loc["name"].toString();
        QString temp = QString::number(curr["temp_c"].toDouble()) + "°C";
        emit weatherCurrentUpdated(city, temp);
    }
    reply->deleteLater();
}

void WeatherAPI::onForecastReply(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject allObj = doc.object();
        QJsonValue forecast = allObj["forecast"].toObject();
        QJsonArray forecastDays = forecast["forecastday"].toArray();
        QJsonObject firstDay = forecastDays[0].toObject();
        QJsonObject day = firstDay["day"].toObject();
        QString rainChance = QString::number(day["daily_chance_of_rain"].toInt()) + "%";
        emit weatherForecastUpdated(rainChance);
    }
    reply->deleteLater();
}
