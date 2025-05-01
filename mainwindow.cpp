#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    weatherApi = new WeatherAPI(this);
    connect(weatherApi, &WeatherAPI::weatherUpdated, this, &MainWindow::onWeatherUpdated);
    connect(ui->refreshBtn, &QPushButton::clicked, this, &MainWindow::onRefreshClicked);
    weatherApi->fetchWeather(); // Fetch data on startup
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onWeatherUpdated(const QString &location, const QString &temp) {
    ui->locationLabel->setText(location);
    ui->tempLabel->setText(temp);
}

void MainWindow::onRefreshClicked() {
    QString currCity = ui->locSelect->currentText();
    weatherApi->setCity(currCity);
    weatherApi->fetchWeather();
}
