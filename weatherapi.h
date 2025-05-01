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
    void setCity(QString &newCity);

signals:
    void weatherUpdated(const QString &location, const QString &temp);  // Signal emitted when data is ready

private slots:
    void onReply(QNetworkReply *reply);  // Slot to handle API response

private:
    QNetworkAccessManager *manager;  // Manages network requests
    QString city = "London";
    QString apiKey = "b40b40a2ae0c40f0937155710253004";
};

#endif
