#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#ifndef WEATHERAPI_H
#define WEATHERAPI_H

class WeatherAPI : public QObject {
public:
    Q_OBJECT
public:
    explicit WeatherAPI(QObject *parent = nullptr);
    void fetchCurrent();
    void fetchForecast();
    void setCity(QString &newCity);
    void setWillRain(QString &willRain);

signals:
    void weatherCurrentUpdated(const QString &location, const QString &temp);
    void weatherForecastUpdated(const QString &willRain);

private slots:
    void onCurrentReply(QNetworkReply *reply);
    void onForecastReply(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    QString city = "London";
    QString apiKey = "b40b40a2ae0c40f0937155710253004";
    QString willRain = "Unknown";
};

#endif
