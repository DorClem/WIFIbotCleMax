#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>



typedef struct dataInType { // création du type dataintype
    int SpeedFront;
    qint8 BatLevel;
    int IR;
    int IR2;
    double odometry;
    int Current;
    int Version;
}
dataInType;


class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
    short Crc16(unsigned char *Adresse_tab, unsigned char Taille_max);
    void CrcAndSend();
    void MoveForward();
    void MoveBack();
    void MoveRight();
    void MoveLeft();
    // données du robot
    dataInType *dataL, *dataR;
    // vitesse
    void setSpeed(int speed);
    int _speed;


signals:
    void updateUI(const QByteArray Data);
    void readCompleted(dataInType* dataL, dataInType* dataR);

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();



private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;

};

#endif // MYROBOT_H
