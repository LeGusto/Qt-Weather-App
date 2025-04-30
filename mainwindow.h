#include <QMainWindow>
#include "weatherapi.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onWeatherUpdated(const QString &location, const QString &temp);
    void onRefreshClicked();

private:
    Ui::MainWindow *ui;
    WeatherAPI *weatherApi;
};
