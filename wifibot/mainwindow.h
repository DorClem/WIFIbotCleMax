#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QGridLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include <QSlider>
#include <QPushButton>
#include <QLabel>

#include "MyRobot.h"
#include "Move.h"





QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void updateBattery(quint8 battery);
    void updateIRSensor(quint8 lFront, quint8 rFront, quint8 back);
    void initGamepad();

    ~MainWindow();

public slots:
    //void updateWindows(const QByteArray);
    //void connectedDisconnted();


private slots:


    void on_buttonHaut_clicked();

    void on_buttonBas_clicked();

    void on_pushButton_clicked();

    void on_buttonDroite_clicked();

    void on_buttonGauche_clicked();

private:


    Ui::MainWindow *ui;
    MyRobot robot;
    //Move *widgetMove;



};
#endif // MAINWINDOW_H
