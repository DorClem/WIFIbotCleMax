#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MyRobot.h"
#include <QKeyEvent>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buttonHaut_clicked()
{
    robot.MoveForward();
}

void MainWindow::on_buttonBas_clicked()
{
    robot.MoveBack();
}


void MainWindow::on_pushButton_clicked()
{
    robot.doConnect();
    robot.readyRead();
}


void MainWindow::on_buttonDroite_clicked()
{
    robot.MoveRight();
}


void MainWindow::on_buttonGauche_clicked()
{
    robot.MoveLeft();
}

void MainWindow::keyPressEvent(QKeyEvent *ev) {

        if (ev->key() == Qt::Key_Z) {
            robot.MoveForward();
        }

        if (ev->key() == Qt::Key_S) {
            robot.MoveBack();
        }

        if (ev->key() == Qt::Key_Q) {
            robot.MoveLeft();
        }

        if (ev->key() == Qt::Key_D) {
            robot.MoveRight();
        }
}

void MainWindow::updateInfos(dataInType* dataL, dataInType* dataR){
    updateBatteryLevel();
    updateSpeedLabel();
}

void MainWindow::updateBatteryLevel(){
    QString danger = "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #FF0350,stop: 0.4999 #FF0020,stop: 0.5 #FF0019,stop: 1 #FF0000 );border-bottom-right-radius: 5px;border-bottom-left-radius: 5px;border: .px solid black;}";
    QString safe= "QProgressBar::chunk {background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #78d,stop: 0.4999 #46a,stop: 0.5 #45a,stop: 1 #238 );border-bottom-right-radius: 7px;border-bottom-left-radius: 7px;border: 1px solid black;}";

    ui->barreBatterie->setValue( robot.dataL->BatLevel*0.1*100/12.7);

    if (ui->barreBatterie->value() < 25){
        ui->barreBatterie->setStyleSheet(danger);
    }

    else {
        ui->barreBatterie->setStyleSheet(safe);
    }
}


void MainWindow::updateSpeedLabel(){

    int speedL = robot.dataL->SpeedFront/100;



    ui->speedLeft->display(speedL);
    if (speedL >70 && speedL <100){

        ui->speedLeft->setStyleSheet("background-color: yellow;  color: white;");

    }

    else if(speedL >100){

        ui->speedLeft->setStyleSheet("background-color: red; color: white;");
    }

    else {

        ui->speedLeft->setStyleSheet("background-color: black; color: white;");

    }


    int speedR = robot.dataR->SpeedFront/100;
    ui->speedRight->display(speedR);

    if (speedR > 70 && speedR < 100){

        ui->speedRight->setStyleSheet("background-color: orange; color: white;");

    }

    else if(speedR >100){

        ui->speedRight->setStyleSheet("background-color: orange; color: white;");
    }

    else {

        ui->speedRight->setStyleSheet("background-color: black; color: white;");
    }
}



void MainWindow::on_boutonBatterie_clicked()
{
    updateBatteryLevel();
    updateSpeedLabel();
}


void MainWindow::on_speedSlider_sliderMoved(int position)   // changement de la vitesse via slider
{
    qDebug() << "Vitesse choisie : " << position;
    robot.setSpeed(position);
}

void MainWindow::updateSpeed(int speed){
    ui->lcdSpeed->display(speed);
}


void MainWindow::on_barreBatterie_valueChanged(int value)
{

}

