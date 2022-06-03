#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MyRobot.h"


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
}


void MainWindow::on_buttonDroite_clicked()
{
    robot.MoveRight();
}


void MainWindow::on_buttonGauche_clicked()
{
    robot.MoveLeft();
}

