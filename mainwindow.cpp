#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    weatherApi = new WeatherAPI(this);
    connect(weatherApi, &WeatherAPI::weatherCurrentUpdated, this, &MainWindow::onCurrentUpdated);
    connect(weatherApi, &WeatherAPI::weatherForecastUpdated, this, &MainWindow::onForecastUpdated);
    connect(ui->refreshBtn, &QPushButton::clicked, this, &MainWindow::onRefreshClicked);
    weatherApi->fetchCurrent();
    weatherApi->fetchForecast();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onCurrentUpdated(const QString &location, const QString &temp) {
    ui->locationLabel->setText(location);
    ui->tempLabel->setText(temp);
}

void MainWindow::onForecastUpdated(const QString &rainChance) {
    ui->rainLabel->setText(rainChance);
}

void MainWindow::onRefreshClicked() {
    QString currCity = ui->locSelect->currentText();
    weatherApi->setCity(currCity);
    weatherApi->fetchCurrent();
    weatherApi->fetchForecast();
}
