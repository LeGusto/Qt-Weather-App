#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#ifndef WEATHERAPI_H
#define WEATHERAPI_H

class WeatherAPI : public QObject {
public:
    Q_OBJECT  // Required for Qt's signals/slots mechanism
public:
    explicit WeatherAPI(QObject *parent = nullptr);  // Constructor
    void fetchWeather();  // Public method to trigger API request

signals:
    void weatherUpdated(const QString &location, const QString &temp);  // Signal emitted when data is ready

private slots:
    void onReply(QNetworkReply *reply);  // Slot to handle API response

private:
    QNetworkAccessManager *manager;  // Manages network requests
};

#endif
