
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algorithm"
//Constructor for main winddow that sets up the widgets and buttons as well as inital variables and the battery timer
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    measureTimer = new QTimer(this);
    exitTimer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    connect(measureTimer, SIGNAL(timeout()), this, SLOT(measureTick()));
    connect(exitTimer, SIGNAL(timeout()), this, SLOT(exitTick()));
    ui->infowidget->setVisible(false);
    ui->profilewidget->setVisible(false);
    ui->homewidget->setVisible(false);
    ui->measurewidget->setVisible(false);
    ui->resultswidget->setVisible(false);
    ui->recommendationwidget->setVisible(false);
    ui->graphwidget->setVisible(false);
    ui->statswidget->setVisible(false);
    ui->historywidget->setVisible(false);
    ui->exitwidget->setVisible(false);
    connect(ui->createProfileButton, SIGNAL(released()), this, SLOT(createProfile()));
    connect(ui->enterButton, SIGNAL(released()), this, SLOT(goProfile()));
    connect(ui->registerProfile, SIGNAL(released()), this, SLOT(inputInfo()));
    connect(ui->profile1Button, SIGNAL(released()),this, SLOT(goHome()));
    connect(ui->profile2Button, SIGNAL(released()),this, SLOT(goHome()));
    connect(ui->profile3Button, SIGNAL(released()),this, SLOT(goHome()));
    connect(ui->profile4Button, SIGNAL(released()),this, SLOT(goHome()));
    connect(ui->profile5Button, SIGNAL(released()),this, SLOT(goHome()));
    connect(ui->homeMeasureButton, SIGNAL(released()), this, SLOT(goMeasure()));
    connect(ui->homeProfilesButton, SIGNAL(released()), this, SLOT(goProfile()));
    connect(ui->homeHistoryButton, SIGNAL(released()), this, SLOT(goHistory()));
    connect(ui->homeGraphButton, SIGNAL(released()), this, SLOT(goGraph()));
    connect(ui->homeLogoutButton, SIGNAL(released()), this, SLOT(goStart()));
    connect(ui->modifyProfileButton, SIGNAL(released()), this, SLOT(addInfo()));
    connect(ui->deleteProfileButton, SIGNAL(released()), this, SLOT(deleteProfile()));
    connect(ui->graphHomeButton, SIGNAL(released()), this, SLOT(goHome()));
    connect(ui->measureButton, SIGNAL(released()), this, SLOT(measure()));
    connect(ui->resultsHomeButton, SIGNAL(released()), this, SLOT(goHome()));
    connect(ui->resultsRecButton, SIGNAL(released()), this, SLOT(goRec()));
    connect(ui->recBackButton, SIGNAL(released()), this, SLOT(goResults()));
    connect(ui->historyHomeButton, SIGNAL(released()), this, SLOT(goHome()));
    connect(ui->ApplyWater, SIGNAL(released()), this, SLOT(applyWater()));
    profileNum = 0;
    currProfile = profileNum;
    HistoryNum = 0;
    user = new User();
    timer->start(2000);
    battery = 100;
    isModifying= false;
    series = new QBarSeries();
    history = new QBarSet("Average");
    vector<string> abbr = {"H1L", "H2L", "H3L", "H4L", "H5L", "H6L", "F1L", "F2L", "F3L", "F4L", "F5L", "F6L", "H1R", "H2R", "H3R", "H4R", "H5R", "H6R", "F1R", "F2R", "F3R", "F4R", "F5R", "F6R"};
    for (const auto &a :  abbr) {
        xNames.append(QString::fromStdString(a));
    }
    series->append(history);
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Historic measurements");
    chart->legend()->setVisible(true);
    xAxis = new QBarCategoryAxis();
    xAxis->append(xNames);
    chart->addAxis(xAxis, Qt::AlignBottom);
    series->attachAxis(xAxis);
    yAxis = new QValueAxis();
    yAxis->setRange(0, 200);
    chart->addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(yAxis);
    chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setVisible(true);

    if (!ui->graphwidget->layout()) {
        ui->graphwidget->setLayout(new QVBoxLayout());
    }
    if (!ui->historylistwidget->layout()) {
        ui->historylistwidget->setLayout(new QVBoxLayout());
    }
    ui->graphwidget->layout()->addWidget(chartview);
    countDown = 5;
    ui->countdownLabel->setText(QString::number(countDown));
}

MainWindow::~MainWindow()
{

    delete ui;
}
//Functiion that decreases the battery as well as displays the low battery warrning and triggering the graceful shutdown
void MainWindow::updateTimer() {
    battery-= 1;
    if (battery  == 0) {
        exitTimer->start(1000);
        timer->stop();
        measureTimer->stop();
        ui->exitwidget->setVisible(true);
        ui->startwidget->setVisible(false);
        ui->infowidget->setVisible(false);
        ui->profilewidget->setVisible(false);
        ui->homewidget->setVisible(false);
        ui->measurewidget->setVisible(false);
        ui->resultswidget->setVisible(false);
        ui->recommendationwidget->setVisible(false);
        ui->graphwidget->setVisible(false);
        ui->statswidget->setVisible(false);
        ui->historywidget->setVisible(false);
    }
    else if(battery == 19){
        QMessageBox msgBox;
        msgBox.setText("Battery is low");
        msgBox.exec();
    }
     ui->battery_label->setText("Battery level: " + QString::number(battery));
}
//Function for gracefully shutting down
void MainWindow::exitTick() {
    if (countDown == 0) {
        qApp->exit();
    }
    qInfo() << countDown;
    ui->countdownLabel->setText(QString::number(countDown));
    countDown -= 1;
}
//Gets the profile ready for creation or modification
void MainWindow::createProfile() {
    currProfile = profileNum;
    profileNum++;
    addInfo();
}
//Goes to the profile creation screen
void MainWindow::addInfo()  {
    QPushButton* buttonSender =qobject_cast<QPushButton*>(sender());
    QString buttonText = buttonSender->text();
    if (currProfile < MAX_PROFILE) {
        ui->startwidget->setVisible(false);
        ui->homewidget->setVisible(false);
        ui->infowidget->setVisible(true);
    }
    else {
        qInfo("Profiles have reached max capacity");
        QMessageBox msgBox;
        msgBox.setText("Profiles have reached max capacity");
        msgBox.exec();
    }
    if(buttonText== "Modify profile"){
        isModifying = true;
    }

}
//Goes to the profile widget
void MainWindow::goProfile()  {
    ui->startwidget->setVisible(false);
    ui->homewidget->setVisible(false);
    ui->profilewidget->setVisible(true);
}
//Function for using the inputted info to create or modify a profile
void MainWindow::inputInfo() {
    ui->infowidget->setVisible(false);
    ui->homewidget->setVisible(true);
    QString firstName = ui->registerFirstInput->text();
    ui->registerFirstInput->setText("");
    QString lastName = ui->registerLastInput->text();
    ui->registerLastInput->setText("");
    QString weight = ui->registerWeightInput->text();
    QString height = ui->registerHeightInput->text();
    ui->registerWeightInput->setText("");
    ui->registerHeightInput->setText("");
    QString fullName = firstName + " " + lastName;
    if(isModifying == true){
         user->getApp()->modifyProfile(currProfile, fullName.toStdString(), weight.toInt(), height.toInt());
         isModifying=false;
    }else{
        user->getApp()->addProfile(fullName.toStdString(), weight.toInt(), height.toInt());
    }
    goHome();
}
//Deletes profile when delete button is pressed
void MainWindow::deleteProfile() {
    ui->homewidget->setVisible(false);
    ui->startwidget->setVisible(true);
    user->getApp()->deleteProfile(user->getApp()->getUsers()[currProfile]->getName());
    profileNum --;
}
//Goes to the home screen and sets the inofmraiton with the current profile
void MainWindow::goHome() {
    QPushButton* buttonSender =qobject_cast<QPushButton*>(sender());
    QString buttonText = buttonSender->text();
    if(buttonText != "Save and continue" && buttonText != "GO HOME"){
        QString profilenum = buttonText.mid(7,1);
        currProfile = profilenum.toInt() - 1;
    }
    if(currProfile < profileNum){
           ui->homeNameLabel->setText(QString::fromStdString((user->getApp()->getUsers()[currProfile]->getName())));
           ui->homewidget->setVisible(true);
           ui->profilewidget->setVisible(false);
           ui->graphwidget->setVisible(false);
           ui->resultswidget->setVisible(false);
           ui->historywidget->setVisible(false);
           ui->statswidget->setVisible(false);
       }else{
           QMessageBox msgBox;
           msgBox.setText("This profile has not been created. Please select another profile or create one");
           msgBox.exec();
           ui->startwidget->setVisible(true);
           ui->profilewidget->setVisible(false);
    }
}
//Goees to start screen
void MainWindow::goStart() {
    ui->homewidget->setVisible(false);
    ui->startwidget->setVisible(true);
}
//Goes to the history screen and creates the history buuttons
void MainWindow::goHistory() {
    ui->homewidget->setVisible(false);
    ui->historywidget->setVisible(true);
    ui->historylistwidget->setVisible(true);
    clearHistoryButtons();
    // loop through all history
    int y = 0;
    currHistory = user->getHistory(currProfile);
    int curr = 1;

    for (const auto &history : currHistory) {
        string name = "Data " + to_string(curr);
        QPushButton* newButton = new QPushButton(QString::fromStdString(name) ,ui->historylistwidget);
        connect(newButton, SIGNAL(released()), this, SLOT(goResults()));
        ui->historylistwidget->layout()->addWidget(newButton);
        newButton->move(0,0);
        y += 20;
        curr++;
        historyButtons.push_back(newButton);
    }
}
//Deletes all the history buttons
void MainWindow::clearHistoryButtons() {
    for (QPushButton*button : historyButtons) {
        ui->historylistwidget->layout()->removeWidget(button);
        delete button;
    }
    historyButtons.clear();
}
//Goes to the graph screen
void MainWindow::goGraph() {
    ui->homewidget->setVisible(false);
    ui->statswidget->setVisible(true);
    ui->graphwidget->setVisible(true);
    series->remove(history);
    history = new QBarSet("Average");
    series->append(history);
    array<int, 24> totalData = user->getApp()->getUsers()[currProfile]->getTotalData();
    vector<Data*> hist = user->getHistory(currProfile);
    if  (!hist.empty()) {
        for (int i = 0; i < 24; i++) {
            history->append(totalData[i]/hist.size());
        }
    }

}
//Goes to the measuring screen
void MainWindow::goMeasure() {
    ui->homewidget->setVisible(false);
    ui->measurewidget->setVisible(true);
    ui->measureButton->setVisible(true);
    ui->bodyMeasurementLabel->setText("0");
    ui->currBodyLabel->setText("BODY PART MEASURING: " + QString::fromStdString(user->getDevice()->getMeasurementPoints()[0]));
    if(user->getSkinContact() == true){
        ui->skinContactLabel->setText("on");
    }else{
        ui->skinContactLabel->setText("off");
    }
}
//Makes the user apply water when the button is pressed
void MainWindow::applyWater(){
    user->applyWater();
}
//Starts the measurement timer and checks if skin is wet
void MainWindow::measure() {
    measureElapsed =-1;
    if(user->isWet() == true){
        measureTimer->start(1000); // in milliseconds
        ui->measureButton->setVisible(false);
    }else{
        QMessageBox msgBox;
        msgBox.setText("Skin is not wet. Please apply water");
        msgBox.exec();
    }
}
//MMeasures each point and sets the user's data as well as modify the measure page accordingly. Also calls a singleshot timer for updating the skin contact
void MainWindow::measureTick() {
    measureElapsed++;
    if(measureElapsed != 0){
        QTimer::singleShot(500, this, SLOT(updateSkinContact()));
    }
    if(user->getSkinContact() == true){
        ui->skinContactLabel->setText("on");
    }else{
        ui->skinContactLabel->setText("off");
    }
    if (measureElapsed > 23) {
        user->finishAnalysis(currProfile);
        measureTimer->stop();
        user->setDry();
        goResults();
    }
    else {
        ui->currBodyLabel->setText("BODY PART MEASURING: " + QString::fromStdString(user->getDevice()->getMeasurementPoints()[measureElapsed]));
        user->pressAgainstPoint(measureElapsed);
        if(user->getSkinContact() == true){
            ui->skinContactLabel->setText("on");
        }else{
            ui->skinContactLabel->setText("off");
        }
        user->removeContact();
        ui->bodyMeasurementLabel->setText(QString::number(measureElapsed));
    }
}
//Updates the skin contact
void MainWindow::updateSkinContact(){
    if(user->getSkinContact() == true){
        ui->skinContactLabel->setText("on");
    }else{
        ui->skinContactLabel->setText("off");
    }
}
//Goes to the results page
void MainWindow::goResults() {
    ui->measurewidget->setVisible(false);
    ui->recommendationwidget->setVisible(false);
    ui->historywidget->setVisible(false);
    QPushButton* buttonSender =qobject_cast<QPushButton*>(sender());
    if (buttonSender != nullptr) {
        QString buttonText = buttonSender->text();
        if(buttonText != "GO BACK"){
            QString num = buttonText.mid(4);
            HistoryNum = num.toInt() - 1;
            ui->leftLung->setText("Right Lung: " + QString::fromStdString(ToString(currHistory[HistoryNum]->getStates()[0])));
            ui->rightLung->setText("Right Lung: " + QString::fromStdString(ToString(currHistory[HistoryNum]->getStates()[1])));
            ui->heart->setText("Heart: " + QString::fromStdString(ToString(currHistory[HistoryNum]->getStates()[2])));
            ui->stomach->setText("Stomach: " + QString::fromStdString(ToString(currHistory[HistoryNum]->getStates()[3])));
            ui->largeIntestine->setText("Large Intenstine: " + QString::fromStdString(ToString(currHistory[HistoryNum]->getStates()[4])));
            ui->smallIntestine->setText("Small Intenstine: " + QString::fromStdString(ToString(currHistory[HistoryNum]->getStates()[5])));
            ui->energyLevel->setText("Energy Level: " + QString::number(currHistory[HistoryNum]->getIndicators().energy));
            ui->metabolism->setText("Metabolism: " + QString::number(currHistory[HistoryNum]->getIndicators().metabolism));
            ui->immuneSystem->setText("Immune System: " + QString::number(currHistory[HistoryNum]->getIndicators().immune));
            ui->psychoemotional->setText("Psycho-emotional state: " + QString::number(currHistory[HistoryNum]->getIndicators().psychoemo));
            ui->musculoskeletal->setText("Musclo-skeletal system: " + QString::number(currHistory[HistoryNum]->getIndicators().musculoskeletal));
            ui->average->setText("Average: " + QString::number(currHistory[HistoryNum]->getIndicators().average));
            QString recommendations = QString::fromStdString(currHistory[HistoryNum]->getRecommendation());
            ui->recommendations->setText(recommendations);
        }
    }else {
        ui->leftLung->setText("Right Lung: " + QString::fromStdString(ToString(user->getApp()->getUsers()[currProfile]->getHistory()[HistoryNum]->getStates()[0])));
        ui->rightLung->setText("Right Lung: " + QString::fromStdString(ToString(user->getApp()->getUsers()[currProfile]->getHistory()[HistoryNum]->getStates()[1])));
        ui->heart->setText("Heart: " + QString::fromStdString(ToString(user->getApp()->getUsers()[currProfile]->getHistory()[HistoryNum]->getStates()[2])));
        ui->stomach->setText("Stomach: " + QString::fromStdString(ToString(user->getApp()->getUsers()[currProfile]->getHistory()[HistoryNum]->getStates()[3])));
        ui->largeIntestine->setText("Large Intenstine: " + QString::fromStdString(ToString(user->getApp()->getUsers()[currProfile]->getHistory()[HistoryNum]->getStates()[4])));
        ui->smallIntestine->setText("Small Intenstine: " + QString::fromStdString(ToString(user->getApp()->getUsers()[currProfile]->getHistory()[HistoryNum]->getStates()[5])));
        ui->energyLevel->setText("Energy Level: " + QString::number(user->getApp()->getUsers()[currProfile]->getHistory()[HistoryNum]->getIndicators().energy));
        ui->metabolism->setText("Metabolism: " + QString::number(user->getApp()->getUsers()[currProfile]->getHistory()[HistoryNum]->getIndicators().metabolism));
        ui->immuneSystem->setText("Immune System: " + QString::number(user->getApp()->getUsers()[currProfile]->getHistory()[HistoryNum]->getIndicators().immune));
        ui->psychoemotional->setText("Psycho-emotional state: " + QString::number(user->getApp()->getUsers()[currProfile]->getHistory()[HistoryNum]->getIndicators().psychoemo));
        ui->musculoskeletal->setText("Musclo-skeletal system: " + QString::number(user->getApp()->getUsers()[currProfile]->getHistory()[HistoryNum]->getIndicators().musculoskeletal));
        ui->average->setText("Average: " + QString::number(user->getApp()->getUsers()[currProfile]->getHistory()[HistoryNum]->getIndicators().average));
        QString recommendations = QString::fromStdString(user->getApp()->getUsers()[currProfile]->getHistory()[HistoryNum]->getRecommendation());
        ui->recommendations->setText(recommendations);
    }
    ui->resultswidget->setVisible(true);
}
//Goes to the reommendation name
void MainWindow::goRec() {
    ui->resultswidget->setVisible(false);
    ui->recommendationwidget->setVisible(true);
}
