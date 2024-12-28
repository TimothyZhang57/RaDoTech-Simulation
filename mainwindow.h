/*Heade for Mainwindow class. It will have a user object that represents the user that uses the RaDoTech device and app. It will have three timers for the battery, the scanning and the shutdown
 * It will have variables to store the current profile as well as the current historical data. It will have an vector of buttons for the history as well as a bar graph&*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>
#include <QDebug>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <vector>
#include "User.h"
#include <QtCharts>
using namespace std;

const int MAX_PROFILE = 5;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *measureTimer;
    QTimer *exitTimer;
    int countDown;
    int measureElapsed;
    int profileNum;
    int currProfile;
    int battery;
    int HistoryNum;
    User* user;
    vector<QPushButton*> historyButtons;
    QBarSeries* series;
    QBarSet* history;
    QStringList xNames;
    QChart* chart;
    QBarCategoryAxis* xAxis;
    QValueAxis* yAxis;
    QChartView* chartview;
    vector<Data*> currHistory;
    bool isModifying;
    void clearHistoryButtons();

private slots:
    void updateTimer();
    void createProfile();
    void addInfo();
    void goProfile();
    void inputInfo();
    void deleteProfile();
    void goHome();
    void goStart();
    void goHistory();
    void goGraph();
    void goMeasure();
    void measure();
    void goRec();
    void goResults();
    void measureTick();
    void updateSkinContact();
    void applyWater();
    void exitTick();
};



#endif // MAINWINDOW_H
