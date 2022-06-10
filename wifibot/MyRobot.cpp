#include "MyRobot.h"

MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    // reception de données
    dataL = (dataInType*) malloc(sizeof(dataInType));
    dataR = (dataInType*) malloc(sizeof(dataInType));

    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer

    _speed = 0;
}


void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);

}

void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void MyRobot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

/*
void MyRobot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
}
*/

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

short MyRobot::Crc16(unsigned char *Adresse_tab, unsigned char Taille_max)
{
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity = 0;
    Crc = 0xFFFF;
    Polynome = 0xA001;
    for (CptOctet = 0; CptOctet < Taille_max; CptOctet++)
    {
        Crc ^= *(Adresse_tab + CptOctet);
        for (CptBit = 0; CptBit <= 7; CptBit++)
        {
            Parity = Crc;
            Crc >>= 1;
            if (Parity % 2 == true)
                Crc ^= Polynome;
        }
    }
    return (Crc);
}

void MyRobot::CrcAndSend(){
    unsigned char *dat = (unsigned char *)DataToSend.data();
    short crc = Crc16(dat+1,6);
    DataToSend[7] = (char)crc;
    DataToSend[8] = (char) (crc >>8);
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));
}

// ========================= MOUVEMENTS DU ROBOT ============================

void MyRobot::MoveForward(){    // avancer
    DataToSend[2] = 120;
    DataToSend[3] = 120;
    DataToSend[4] = 120;
    DataToSend[5] = 120;
    DataToSend[6] = 0xF0;
    CrcAndSend();
}

void MyRobot::MoveBack(){   // reculer
    DataToSend[2] = 120;
    DataToSend[3] = 120;
    DataToSend[4] = 120;
    DataToSend[5] = 120;
    DataToSend[6] = 0xA0;
    CrcAndSend();
}

void MyRobot::MoveRight(){  // aller a droite
    DataToSend[2] = 120;
    DataToSend[3] = 120;
    DataToSend[4] = 120;
    DataToSend[5] = 120;
    DataToSend[6] = 0xE0;
    CrcAndSend();
}

void MyRobot::MoveLeft(){  // aller a gauche
    DataToSend[2] = 120;
    DataToSend[3] = 120;
    DataToSend[4] = 120;
    DataToSend[5] = 120;
    DataToSend[6] = 0xB0;
    CrcAndSend();
}

/*
void MyRobot::readyRead()
{
    qDebug() << "reading...";

    DataReceived = socket->readAll();

    dataL->SpeedFront = int(((DataReceived[1] << 8) + DataReceived[0]));

    if (dataL->SpeedFront > 32767)
        dataL->SpeedFront = dataL->SpeedFront - 65536;
    dataL->BatLevel = DataReceived[2];
    dataL->IR = DataReceived[3];
    dataL->IR2 = DataReceived[4];
    dataL->odometry = long(DataReceived[8] << 24) + long(DataReceived[7] << 16) + long(DataReceived[6] << 8) + long(DataReceived[5]);
    dataR->SpeedFront = int(DataReceived[10] << 8 + DataReceived[9]);

    if (dataR->SpeedFront > 32767)
        dataR->SpeedFront = dataR->SpeedFront - 65536;
    dataR->BatLevel = 0;
    dataR->IR = DataReceived[11];
    dataR->IR2 = DataReceived[12];
    dataR->odometry = ((((long)DataReceived[16] << 24)) + (((long)DataReceived[15] << 16)) + (((long)DataReceived[14] << 8)) + ((long)DataReceived[13]));
    dataL->Current = DataReceived[17];
    dataR->Current = DataReceived[17];
    dataL->Version = DataReceived[18];
    dataR->Version = DataReceived[18];
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
    qDebug() << DataReceived[0];
    emit readCompleted(dataL, dataR);
}*/

void MyRobot::readyRead() {

    DataReceived = socket->readAll();
    emit updateUI(DataReceived);

    if(int (DataReceived[0]) >= 0){
        qDebug() << "Vitesse : " << int (DataReceived[0]);
    }
    if(int (DataReceived[0]) < 0){
        qDebug() << "Vitesse : " << (256 + int (DataReceived[0]));
    }

    if(int (DataReceived[2]) >= 0){
        qDebug() << "Batterie : " << int (DataReceived[2]);
    }
    if(int (DataReceived[2]) < 0){
        qDebug() << "Batterie : " << ((256 + int (DataReceived[2]))*100)/256;
    }

    qDebug() << "Vitesse voulue : " << _speed;

}

void MyRobot::setSpeed(int speed){   // change la vitesse avec le slider
    _speed = speed;
}
